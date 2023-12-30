from jetson_utils import videoOutput, cudaFromNumpy
import numpy as np
import cv2


# Create Viceo Capture object with GStreamer pipeline
stream_path = "rtsp://sbrnx:6000/d435/rgb"
cam = cv2.VideoCapture(stream_path, cv2.CAP_GSTREAMER)
if not cam.isOpened():
    print("Error opening stream: " + stream_path)
    exit(1)

# Create rstp
streamerObject = videoOutput("rtsp://@:6001/object_detector/t1")


while True:
    _, frame = cam.read()
    cv2.imshow("test", frame)
    frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gsFrame= cudaFromNumpy(frame_gray)
    
