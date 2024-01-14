import threading
from queue import Queue 
from jetson_utils import videoOutput, cudaFromNumpy
import pyrealsense2 as rs
import numpy as np
import cv2
import time

# Function to convert cv2 image to cuda image
def cv2_to_cuda(cv_image):
    # Convert image to cuda
    return cudaFromNumpy(cv_image)


def task_read_camera(queue_streamer_camera, queue_streamer_camera_depth):
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
        queue_streamer_camera.put(color_image)
        queue_streamer_camera_depth.put(depth_image)

        # get the end time
        et = time.time()
        # get the execution time
        elapsed_time = et - st
        print('Execution time:', elapsed_time, 'seconds')



def task_streamer_camera(queue_streamer_camera):
    # Create rstp stream
    streamerCameraRGB = videoOutput("rtsp://@:6000/d435/rgb")

    while True:

        # Get image from queue
        color_image = queue_streamer_camera.get()

        # Render the image
        streamerCameraRGB.Render(cv2_to_cuda(color_image))


def task_streamer_camera_depth(queue_streamer_camera_depth):
    # Create rstp stream
    streamerCameraDepth = videoOutput("rtsp://@:6001/d435/depth")

    while True:

        # Get image from queue
        depth_image = queue_streamer_camera_depth.get()

        # Divide the distance (one channel) into 3 channels. For example 600 => (90,255,255)
        depth_image_1 = np.where(depth_image > 255, 255, depth_image)

        depth_image_temp = np.add(depth_image, -255)
        depth_image_temp = np.where(depth_image_temp < 0, 0, depth_image_temp)
        depth_image_2 = np.where(depth_image_temp > 255, 255, depth_image_temp)

        depth_image_temp = np.add(depth_image, -510)
        depth_image_temp = np.where(depth_image_temp < 0, 0, depth_image_temp)
        depth_image_3 = np.where(depth_image_temp > 255, 255, depth_image_temp)

        # Merge the 3 channels into one image
        depth_image = np.dstack((depth_image_3, depth_image_2, depth_image_1)) 

        # Render the image
        streamerCameraDepth.Render(cv2_to_cuda(depth_image))


# Main
if __name__ == '__main__':

    # Create queue
    queue_streamer_camera = Queue(5)
    queue_streamer_camera_depth = Queue(5)

    # Create threads
    thread_read_camera = threading.Thread(target=task_read_camera, args=(queue_streamer_camera, queue_streamer_camera_depth))
    thread_streamer_camera = threading.Thread(target=task_streamer_camera, args=(queue_streamer_camera,))
    thread_streamer_camera_depth = threading.Thread(target=task_streamer_camera_depth, args=(queue_streamer_camera_depth,))

    # Start threads
    thread_read_camera.start()
    thread_streamer_camera.start()
    thread_streamer_camera_depth.start()

    # Wait threads
    thread_read_camera.join()
    thread_streamer_camera.join()
    thread_streamer_camera_depth.join()


