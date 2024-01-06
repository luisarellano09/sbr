from jetson_utils import videoSource, videoOutput, cudaFromNumpy, cudaAllocMapped, cudaConvertColor, cudaToNumpy, cudaDeviceSynchronize
import cv2


# Function to convert cuda image to cv2 image
def cuda_to_cv2(cuda_image):
    # Allocate new image
    rgb_image = cudaAllocMapped(width=cuda_image.width, height=cuda_image.height, format='bgr8')

    # Convert image to RGB
    cudaConvertColor(cuda_image, rgb_image)

    # Convert image to numpy (opencv format)
    cv_rgb_image = cudaToNumpy(rgb_image)

    # Synchonize Cuda
    cudaDeviceSynchronize()

    # Convert image to BGR
    cv_image = cv2.cvtColor(cv_rgb_image, cv2.COLOR_RGB2BGR)

    return cv_image


# Main
if __name__ == '__main__':

    # Create Video Source
    cameraRGB = videoSource("rtsp://sbrnx:6000/d435/rgb")

    # Create Video Output
    streamerObjectDetector = videoOutput("rtsp://@:6001/serv/object_detector")

    while True:
        # Read frame from RRSP stream
        cuda_image = cameraRGB.Capture()

        # Convert image to numpy (opencv format)
        cv_image = cuda_to_cv2(cuda_image)

        # Add text
        cv_image_text = cv2.putText(cv_image, "Hello World", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
        
        # Render the image
        streamerObjectDetector.Render(cudaFromNumpy(cv_image_text))