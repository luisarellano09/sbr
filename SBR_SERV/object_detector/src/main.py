import numpy as np
import cv2


# Create Viceo Capture object with GStreamer pipeline
stream_path_D435_RGB = "rtsp://sbrnx:6000/d435/rgb"
cam = cv2.VideoCapture(stream_path_D435_RGB, cv2.CAP_GSTREAMER)
if not cam.isOpened():
    print("Error opening stream: " + stream_path_D435_RGB)
    exit(1)

# Create rstp stream
stream_path_ObjectDetector = "rtsp://@:6000/serv/object_detector"


fps = 30
width = 1280
height = 720

out = cv2.VideoWriter('appsrc ! videoconvert' + \
    ' ! video/x-raw,format=I420' + \
    ' ! x264enc speed-preset=ultrafast bitrate=600 key-int-max=' + str(fps * 2) + \
    ' ! video/x-h264,profile=baseline' + \
    ' ! rtspclientsink location=rtsp://localhost:6000/serv/object_detector',
    cv2.CAP_GSTREAMER, 0, fps, (width, height), True)
if not out.isOpened():
    raise Exception("can't open video writer")


while True:
    _, frame = cam.read()
    frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    print(frame_gray.shape)
    out.write(frame)
    
