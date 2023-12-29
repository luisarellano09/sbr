import threading
from jetson_utils import videoSource, videoOutput, cudaFromNumpy
import pyrealsense2 as rs
import numpy as np
import cv2

# create video sources & outputs
cameraIR = videoSource("/dev/video2")
cameraRGB = videoSource("/dev/video4")

streamerCameraIR = videoOutput("rtsp://@:6000/d435/ir")
streamerCameraRGB = videoOutput("rtsp://@:6000/d435/rgb")
streamerCameraDepth = videoOutput("rtsp://@:6000/d435/depth")

def task_camera_process(camera, streamer):
    # Number of frames captured
    numFrames = 0

    # process frames until the user exits
    while True:
        # capture the next image
        image = camera.Capture()

        # Check if there is image
        if image is None:
            continue

        numFrames += 1

        # Render the image
        streamer.Render(image)
    
        # update the title bar
        if numFrames % 50 == 0:
            print(f" {threading.current_thread().name}: {image.width}x{image.height} | {streamer.GetFrameRate()} FPS")

        # exit on input/output EOS
        if not camera.IsStreaming() or not streamer.IsStreaming():
            break


def task_camera_depth_process(streamerDepth):

    pipe = rs.pipeline()
    cfg  = rs.config()

    cfg.enable_stream(rs.stream.color, 1280,720, rs.format.rgb8, 30)
    cfg.enable_stream(rs.stream.depth, 1280,720, rs.format.z16, 30)

    pipe.start(cfg)

    # Number of frames captured
    numFrames = 0

    while True:
        frame = pipe.wait_for_frames()
        depth_frame = frame.get_depth_frame()
        color_frame = frame.get_color_frame()

        depth_image = np.asanyarray(depth_frame.get_data())
        color_image = np.asanyarray(color_frame.get_data())

        adjustedRGB = cv2.addWeighted( color_image, 0.5, color_image, 0, 12)
        
        gsFrameRGB = cudaFromNumpy(adjustedRGB)
        gsFrameDepth = cudaFromNumpy(depth_image)

        # Render the image
        streamerDepth.Render(gsFrameRGB)
        #streamerDepth.Render(gsFrameDepth)


if __name__ == '__main__':

    # Define the threads
    # threadIR = threading.Thread(target=task_camera_process, args=(cameraIR, streamerCameraIR), name="IR")
    # threadRGB = threading.Thread(target=task_camera_process, args=(cameraRGB, streamerCameraRGB), name="RGB")
    threadDepth = threading.Thread(target=task_camera_depth_process, args=(streamerCameraDepth,), name="Depth")

    # start the threads
    # threadIR.start()
    # threadRGB.start()
    threadDepth.start()

    # wait for the threads to finish
    # threadIR.join()
    # threadRGB.join()
    threadDepth.join()