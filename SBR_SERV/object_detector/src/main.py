from jetson_utils import videoOutput, cudaFromNumpy
import numpy as np
import cv2


# Create Viceo Capture object with GStreamer pipeline
stream_path_D435_RGB = "rtsp://sbrnx:6000/d435/rgb"
cam = cv2.VideoCapture(stream_path_D435_RGB, cv2.CAP_GSTREAMER)
if not cam.isOpened():
    print("Error opening stream: " + stream_path_D435_RGB)
    exit(1)

# Create rstp stream
stream_path_ObjectDetector = "rtsp://sbrnx:6001/object_detector/t1"
streamerObjectDetector = videoOutput(stream_path_ObjectDetector)
if not streamerObjectDetector.isOpened():
    print("Error opening stream: " + stream_path_ObjectDetector)
    exit(1)


while True:
    _, frame = cam.read()
    frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    print(frame_gray.shape)
    streamerObjectDetector.Render(cudaFromNumpy(frame))
    