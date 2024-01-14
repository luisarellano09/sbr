import threading
from queue import Queue 
from jetson_utils import videoOutput, cudaFromNumpy
import jetson.inference
import pyrealsense2 as rs
import numpy as np
import cv2
import time

# Function to convert cv2 image to cuda image
def cv2_to_cuda(cv_image):
    # Convert image to cuda
    return cudaFromNumpy(cv_image)


def task_read_camera(queue_to_streamer_camera, queue_to_object_detector):
     # Create pipeline
    pipe = rs.pipeline()
    cfg  = rs.config()

    # Enable streams
    cfg.enable_stream(rs.stream.color, 1280, 720, rs.format.rgb8, 30)
    cfg.enable_stream(rs.stream.depth, 1280, 720, rs.format.z16, 30)

    # Start streaming
    pipe.start(cfg)

    #  Factor to convert to cm
    distance_factor = 0.1

    # Create an align object
    # rs.align allows us to perform alignment of depth frames to others frames
    # The "align_to" is the stream type to which we plan to align depth frames.
    align_to = rs.stream.color
    align = rs.align(align_to)

    while True:

        st = time.time()

        # Wait for a coherent pair of frames: depth and color
        frame = pipe.wait_for_frames()
        
        # Align the depth frame to color frame
        aligned_frame = align.process(frame)
        depth_frame = aligned_frame.get_depth_frame()
        color_frame = aligned_frame.get_color_frame()

        # Convert images to numpy arrays
        depth_image = np.asanyarray(depth_frame.get_data())
        color_image = np.asanyarray(color_frame.get_data())

        # Normalice depth image
        depth_image = cv2.multiply(depth_image, distance_factor)

        # Flip images horizontally
        depth_image = cv2.flip(depth_image, 1)
        color_image = cv2.flip(color_image, 1)

        # Adjust image RGB
        # color_image = cv2.addWeighted( color_image, 1, color_image, 0, 15)

        # Render the image
        queue_to_streamer_camera.put(color_image)
        queue_to_object_detector.put(color_image)

        # get the end time
        et = time.time()
        # get the execution time
        elapsed_time = et - st
        print('Execution time:', elapsed_time, 'seconds')


def task_streamer_camera(queue_image, streamerPath):
    # Create rstp stream
    streamer = videoOutput(streamerPath)

    while True:

        # Get image from queue
        image = queue_image.get()

        # Render the image
        streamer.Render(cv2_to_cuda(image))



def task_object_detector(queue_from_streamer_camera, queue_to_streamer_object_detector):

    # Detector
    net = jetson.inference.detectNet("ssd-mobilenet-v2", threshold=0.5)

    while True:

        # Get image from queue
        color_image = queue_from_streamer_camera.get()

        # Detect objects
        detections = net.Detect(cv2_to_cuda(color_image))

        # Loop into each detection
        for detection in detections:
            # Get class name
            object_name = net.GetClassDesc(detection.ClassID)

            # Get bounding box
            x1, y1, x2, y2 = int(detection.Left), int(detection.Top), int(detection.Right), int(detection.Bottom)
            cv2.rectangle(color_image, (x1, y1), (x2, y2), (0, 255, 0), 1)
            cv2.putText(color_image, object_name, (x1, y1), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2)

        # Render the image
        queue_to_streamer_object_detector.put(color_image)

# Main
if __name__ == '__main__':

    # Create queue
    queue_streamer_camera = Queue(1)
    queue_streamer_object_detector = Queue(1)
    queue_object_detector = Queue(1)

    # Create threads
    thread_read_camera = threading.Thread(target=task_read_camera, args=(queue_streamer_camera, queue_object_detector,))
    thread_streamer_camera = threading.Thread(target=task_streamer_camera, args=(queue_streamer_camera,))
    thread_object_detector = threading.Thread(target=task_object_detector, args=(queue_object_detector, queue_streamer_object_detector,))
    thread_streamer_object_detector = threading.Thread(target=task_streamer_camera, args=(queue_streamer_object_detector,))


    # Start threads
    thread_read_camera.start()
    thread_streamer_camera.start()
    thread_object_detector.start()
    thread_streamer_object_detector.start()


    # Wait threads
    thread_read_camera.join()
    thread_streamer_camera.join()
    thread_object_detector.join()
    thread_streamer_object_detector.join()



