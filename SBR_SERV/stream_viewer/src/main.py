#from jetson_utils import videoOutput, cudaFromNumpy
import threading
import cv2


def task_camera_process(stream_path):
    stream = cv2.VideoCapture(stream_path, cv2.CAP_GSTREAMER)
    if not stream.isOpened():
        print("Error opening stream: " + stream_path)
        return
    cv2.namedWindow(stream_path)
    while True:
        _, frame = stream.read()
        cv2.imshow(stream_path, frame)
        key = cv2.waitKey(1)
        if key == 27:  # Press ESC to exit/close each window.
            break
    
    cv2.destroyWindow(stream_path)  


if __name__ == '__main__':
    # Create threads
    thread_stream_d435_rgb = threading.Thread(target=task_camera_process, args=("rtsp://sbrnx:6000/d435/rgb",))
    thread_stream_d435_depth = threading.Thread(target=task_camera_process, args=("rtsp://sbrnx:6000/d435/depth",))
    
    # Start threads
    thread_stream_d435_rgb.start()
    thread_stream_d435_depth.start()
    
    # Wait threads
    thread_stream_d435_rgb.join()
    thread_stream_d435_depth.join()