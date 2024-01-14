import threading
from jetson_utils import videoOutput, cudaFromNumpy
import pyrealsense2 as rs
import numpy as np
import cv2
import time

# Function to convert cv2 image to cuda image
def cv2_to_cuda(cv_image):
    # Convert image to cuda
    return cudaFromNumpy(cv_image)


def task_read_camera():
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

        # Adjust image RGB
        color_image = cv2.addWeighted( color_image, 1, color_image, 0, 15)

        # get the end time
        et = time.time()
        # get the execution time
        elapsed_time = et - st
        print('Execution time:', elapsed_time, 'seconds')

    


# Main
if __name__ == '__main__':

    # Create threads
    thread_read_camera = threading.Thread(target=task_read_camera, args=())

    # Start threads
    thread_read_camera.start()

    # Wait threads
    thread_read_camera.join()


    # Create rstp streams
    # streamerCameraDepth = videoOutput("rtsp://@:6000/d435/depth")
    # streamerCameraRGB = videoOutput("rtsp://@:6001/d435/rgb")

   

        
        
        
    # Render the image
    streamerCameraDepth.Render(cv2_to_cuda(depth_image))
    streamerCameraRGB.Render(cv2_to_cuda(color_image))




