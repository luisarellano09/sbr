from jetson_utils import videoSource, videoOutput, cudaFromNumpy, cudaAllocMapped, cudaConvertColor, cudaToNumpy, cudaDeviceSynchronize
import cv2


# Function to convert cuda image to cv2 image
def cuda_to_cv2(cuda_image):
    # Allocate new image
    image = cudaAllocMapped(width=cuda_image.width, height=cuda_image.height, format='rgb8')

    # Convert image to RGB
    cudaConvertColor(cuda_image, image)

    # Convert image to numpy (opencv format)
    cv_image = cudaToNumpy(image)

    # Synchonize Cuda
    cudaDeviceSynchronize()

    return cv_image


# Function to convert cv2 image to cuda image
def cv2_to_cuda(cv_image):
    # Convert image to cuda
    return cudaFromNumpy(cv_image)


# Main
if __name__ == '__main__':

    # Create Video Source
    cameraRGB = videoSource("rtsp://sbrnx:6000/d435/rgb")

    # Create Video Output
    streamerObjectDetector = videoOutput("rtsp://@:6001/serv/object_detector")

    while True:
        # Read frame from RRSP stream
        cuda_image = cameraRGB.Capture()

        # Check if there is a valid image
        if cuda_image is None:
            continue

        # Convert image to numpy (opencv format)
        cv_image = cuda_to_cv2(cuda_image)

        # Add text
        cv_image_text = cv2.putText(cv_image, "Hello World", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
        
        # Render the image
        streamerObjectDetector.Render(cudaFromNumpy(cv_image_text))