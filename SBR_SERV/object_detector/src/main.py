
import numpy as np
import cv2

fps = 15
width = 800
height = 600
colors = [
    (0, 0, 255),
    (255, 0, 0),
    (0, 255, 0),
]
curcolor = 0


# Create Viceo Capture object with GStreamer pipeline
stream_path = "rtsp://sbrnx:6000/d435/rgb"
cam = cv2.VideoCapture(stream_path, cv2.CAP_GSTREAMER)
if not cam.isOpened():
    print("Error opening stream: " + stream_path)
    exit(1)

# Create rstp
#streamerObject = videoOutput("rtsp://@:6001/object_detector/t1")
out = cv2.VideoWriter('appsrc ! videoconvert ! video/x-raw,format=I420 ! x264enc tune=zerolatency bitrate=600 speed-preset=superfast key-int-max=60 ! video/x-h264,profile=baseline  ! rtspclientsink location=rtsp://sbrnx:6001/object_detector/t1', cv2.CAP_GSTREAMER, 0, 30, (1280, 720), True)
if not out.isOpened():
    raise Exception("can't open video writer")

while True:
    # _, frame = cam.read()
    # frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # print(frame_gray.shape)
    
    frame = np.zeros((height, width, 3), np.uint8)

    # create a rectangle
    color = colors[curcolor]
    curcolor += 1
    curcolor %= len(colors)
    for y in range(0, int(frame.shape[0] / 2)):
        for x in range(0, int(frame.shape[1] / 2)):
            frame[y][x] = color
    out.write(frame)
    
