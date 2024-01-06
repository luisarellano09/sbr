from jetson_utils import videoSource, videoOutput, cudaFromNumpy, cudaAllocMapped, cudaConvertColor, cudaToNumpy, cudaDeviceSynchronize
import numpy as np
import cv2


# Create Video Source
cameraRGB = videoSource("rtsp://sbrnx:6000/d435/rgb")

# Create Video Output
streamerObjectDetector = videoOutput("rtsp://@:6001/serv/object_detector")

while True:
    cuda_image = cameraRGB.Capture()
    rgb_image = cudaAllocMapped(width=cuda_image.width, height=cuda_image.height, format='bgr8')
    cudaConvertColor(cuda_image, rgb_image)
    cv_rgb_image = cudaToNumpy(rgb_image)
    cudaDeviceSynchronize()
    cv_image = cv2.cvtColor(cv_rgb_image, cv2.COLOR_RGB2BGR)
    cv_image_text = cv2.putText(cv_image, "Hello World", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
    streamerObjectDetector.Render(cudaFromNumpy(cv_image_text))