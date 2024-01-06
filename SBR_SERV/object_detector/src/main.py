from jetson_utils import videoSource, videoOutput, cudaFromNumpy, cudaAllocMapped, cudaConvertColor, cudaToNumpy, cudaDeviceSynchronize
import numpy as np
import cv2


# Create Video Source
cameraRGB = videoSource("rtsp://sbrnx:6000/d435/rgb")

# Create Video Output
streamerObjectDetector = videoOutput("rtsp://@:6001/serv/object_detector")

while True:
    image = cameraRGB.Capture()
    bgr_img = cudaAllocMapped(width=image.width, height=image.height, format='bgr8')
    cudaConvertColor(image, bgr_img)
    cv_img = cudaToNumpy(bgr_img)
    cudaDeviceSynchronize()
    frame = cv2.putText(cv_img, "Hello World", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 10, (0, 0, 255), 2)
    streamerObjectDetector.Render(cudaFromNumpy(frame))