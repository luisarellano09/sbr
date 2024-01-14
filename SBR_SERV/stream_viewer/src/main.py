import threading
import cv2


def task_camera_process(stream_path):
    # Create rstp stream
    stream = cv2.VideoCapture(stream_path, cv2.CAP_GSTREAMER)
    
    # Check if stream is opened
    if not stream.isOpened():
        print("Error opening stream: " + stream_path)
        return
    
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


if __name__ == '__main__':
    # Create threads
    thread_stream_d435_rgb = threading.Thread(target=task_camera_process, args=("rtsp://sbrnx:6000/d435/rgb",))
    thread_stream_d435_depth = threading.Thread(target=task_camera_process, args=("rtsp://sbrnx:6000/d435/depth",))
    thread_stream_object_detector = threading.Thread(target=task_camera_process, args=("rtsp://sbrnx:6001/serv/object_detector",))
    thread_stream_face_detector = threading.Thread(target=task_camera_process, args=("rtsp://sbrnx:6002/serv/face_detector",))
    
    # Start threads
    thread_stream_d435_rgb.start()
    thread_stream_d435_depth.start()
    thread_stream_object_detector.start()
    thread_stream_face_detector.start()
    
    # Wait threads
    thread_stream_d435_rgb.join()
    thread_stream_d435_depth.join()
    thread_stream_object_detector.join()
    thread_stream_face_detector.join()