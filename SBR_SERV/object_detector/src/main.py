from jetson_utils import videoSource, videoOutput, cudaFromNumpy
import numpy as np
import cv2


# Create Video Source
cameraRGB = videoSource("rtsp://sbrnx:6000/d435/rgb")

# Create Video Output
streamerObjectDetector = videoOutput("rtsp://@:6001/serv/object_detector")

while True:
    image = cameraRGB.Capture()
    frame = np.asanyarray(image)
    frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    print(frame_gray.shape)
    streamerObjectDetector.Render(cudaFromNumpy(frame))
    
