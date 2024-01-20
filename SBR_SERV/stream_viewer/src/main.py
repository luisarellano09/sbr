import cv2

stream_path = "rtsp://sbrnx:6000/serv/computer_vision"

stream = cv2.VideoCapture(stream_path, cv2.CAP_GSTREAMER)
    
# Check if stream is opened
if not stream.isOpened():
    print("Error opening stream")
    exit(1)

# Create window
cv2.namedWindow(stream_path)

# Loop
while True:
    # Read frame
    _, frame = stream.read()
    
    # Show frame
    cv2.imshow(stream_path, frame)
    
    # Wait for key
    key = cv2.waitKey(1)
    if key == 27:  # Press ESC to exit/close each window.
        break

cv2.destroyWindow(stream_path)