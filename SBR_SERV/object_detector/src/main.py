from jetson_utils import videoOutput, cudaFromNumpy
import numpy as np
import cv2


# Create Viceo Capture object with GStreamer pipeline
stream_path_D435_RGB = "rtsp://sbrnx:6000/d435/rgb "
cam = cv2.VideoCapture(stream_path_D435_RGB, cv2.CAP_GSTREAMER)
if not cam.isOpened():
    print("Error opening stream: " + stream_path_D435_RGB)
    exit(1)

# Create rstp stream
stream_path_ObjectDetector = "rtsp://@:6000/serv/object_detector --output-codec=h265 --output-encoder=v4l2"
streamerObjectDetector = videoOutput("rtsp://@:6001/serv/object_detector")

while True:
    _, frame = cam.read()
    frame_cv = cv2.putText(frame, "Hello World", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 10, (0, 0, 255), 2)
    streamerObjectDetector.Render(cudaFromNumpy(frame_cv))
    