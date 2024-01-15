import threading
from queue import Queue 
from jetson_utils import videoOutput, cudaFromNumpy
import jetson.inference
import pyrealsense2 as rs
import face_recognition
import numpy as np
import cv2
import time
import os

# Function to convert cv2 image to cuda image
def cv2_to_cuda(cv_image):
    # Convert image to cuda
    return cudaFromNumpy(cv_image)


# Train faces
def train_faces(path, known_faces_encoding, known_faces_name):
    # Loop into folder  and encode faces from "./faces" folder
    for file in os.listdir(path):
        # Load face
        face_image = face_recognition.load_image_file(path + "/" + file)

        # Encode face
        encoding = face_recognition.face_encodings(face_image, model="small")[0]

        # Get name
        name = os.path.splitext(file)[0]

        # Add to lists
        known_faces_encoding.append(encoding)
        known_faces_name.append(name)


def task_read_camera(queue_to_streamer_camera, queue_to_object_detector, queue_to_face_detector):

    time.sleep(10)

     # Create pipeline
    pipe = rs.pipeline()
    cfg  = rs.config()

    # Enable streams
    cfg.enable_stream(rs.stream.color, 1280, 720, rs.format.rgb8, 30)
    cfg.enable_stream(rs.stream.depth, 1280, 720, rs.format.z16, 30)

    # Start streaming
    pipe.start(cfg)

    #  Factor to convert to cm
    distance_factor = 0.1

    # Create an align object
    # rs.align allows us to perform alignment of depth frames to others frames
    # The "align_to" is the stream type to which we plan to align depth frames.
    align_to = rs.stream.color
    align = rs.align(align_to)

    while True:
        # Wait for a coherent pair of frames: depth and color
        frame = pipe.wait_for_frames()
        
        # Align the depth frame to color frame
        aligned_frame = align.process(frame)
        depth_frame = aligned_frame.get_depth_frame()
        color_frame = aligned_frame.get_color_frame()

        # Convert images to numpy arrays
        depth_image = np.asanyarray(depth_frame.get_data())
        color_image = np.asanyarray(color_frame.get_data())

        # Normalice depth image
        depth_image = cv2.multiply(depth_image, distance_factor)

        # Flip images horizontally
        depth_image = cv2.flip(depth_image, 1)
        color_image = cv2.flip(color_image, 1)

        # Adjust image RGB
        # color_image = cv2.addWeighted( color_image, 1, color_image, 0, 15)

        # Render the image
        queue_to_streamer_camera.put(color_image)
        queue_to_object_detector.put(color_image)
        queue_to_face_detector.put(color_image)


def task_streamer(queue_image, streamerPath):

    time.sleep(10)

    time_stamp = time.time()
    fps_filt = 0

    # Create rstp stream
    streamer = videoOutput(streamerPath)

    while True:

        # Get image from queue
        image = queue_image.get()

        # Calculate FPS
        dt = time.time() - time_stamp
        time_stamp = time.time()
        fps = 1 / dt
        fps_filt = 0.9 * fps_filt + 0.1 * fps

        # Add text
        cv2.putText(image, str(int(fps_filt)) + 'fps',  (5, 20), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 0), 2)

        # Render the image
        streamer.Render(cv2_to_cuda(image))


def task_object_detector(queue_from_streamer_camera, queue_to_streamer_object_detector):

    # Detector
    net = jetson.inference.detectNet("ssd-mobilenet-v2", threshold=0.5)

    while True:

        # Get image from queue
        color_image = queue_from_streamer_camera.get()

        # Detect objects
        detections = net.Detect(cv2_to_cuda(color_image))

        # Loop into each detection
        for detection in detections:
            # Get class name
            object_name = net.GetClassDesc(detection.ClassID)

            # Get bounding box
            x1, y1, x2, y2 = int(detection.Left), int(detection.Top), int(detection.Right), int(detection.Bottom)
            cv2.rectangle(color_image, (x1, y1), (x2, y2), (0, 255, 0), 1)
            cv2.putText(color_image, object_name, (x1, y1), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2)

        # Render the image
        queue_to_streamer_object_detector.put(color_image)


def task_face_detector(queue_from_streamer_camera, queue_to_streamer_face_detector):

   # Create encoding list of known faces
    known_faces_encoding = []
    known_faces_name = []

    # Train faces
    train_faces("/face_detector/known_faces", known_faces_encoding, known_faces_name)


    while True:

        # Read frame from RRSP stream
        image = queue_from_streamer_camera.get()

        # # Convert the image from BGR color (which OpenCV uses) to RGB color (which face_recognition uses)
        # detect_image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
        # detect_image = cv2.resize(detect_image, (0, 0), fx=0.5, fy=0.5)

        # # Find all the faces and face encodings in the image
        # face_locations = face_recognition.face_locations(detect_image, model="cnn")
        # face_encodings = face_recognition.face_encodings(detect_image, face_locations, model="small")

        # # Loop into each face
        # for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
        #     # See if the face is a match for the known face(s)
        #     matches = face_recognition.compare_faces(known_faces_encoding, face_encoding)

        #     # If no match was found in known_face_encodings, use the name "Unknown"
        #     name = "Unknown"

        #     # If a match was found in known_face_encodings, just use the first one.
        #     if True in matches:
        #         first_match_index = matches.index(True)
        #         name = known_faces_name[first_match_index]

        #     top *= 2
        #     right *= 2
        #     bottom *= 2
        #     left *= 2

        #     # Draw a box around the face
        #     cv2.rectangle(image, (left, top), (right, bottom), (0, 0, 255), 2)

        #     # Draw a label with a name below the face
        #     cv2.rectangle(image, (left, bottom - 25), (right, bottom), (0, 0, 255), cv2.FILLED)
        #     cv2.putText(image, name, (left + 6, bottom - 6), cv2.FONT_HERSHEY_DUPLEX, 0.5, (255, 255, 255), 1)

        queue_to_streamer_face_detector.put(image)



# Main
if __name__ == '__main__':

    # Create queue
    queue_streamer_camera = Queue(1)
    queue_object_detector = Queue(1)
    queue_streamer_object_detector = Queue(1)
    queue_face_detector = Queue(1)
    queue_streamer_face_detector = Queue(1)

    # Create threads
    thread_read_camera = threading.Thread(target=task_read_camera, args=(queue_streamer_camera, queue_object_detector, queue_face_detector,))
    thread_streamer_camera = threading.Thread(target=task_streamer, args=(queue_streamer_camera, "rtsp://@:6000/d435/rgb",))
    thread_object_detector = threading.Thread(target=task_object_detector, args=(queue_object_detector, queue_streamer_object_detector,))
    thread_streamer_object_detector = threading.Thread(target=task_streamer, args=(queue_streamer_object_detector, "rtsp://@:6002/serv/object_detector",))
    thread_face_detector = threading.Thread(target=task_face_detector, args=(queue_face_detector, queue_streamer_face_detector,))
    thread_streamer_face_detector = threading.Thread(target=task_streamer, args=(queue_streamer_face_detector, "rtsp://@:6003/serv/face_detector",))

    # Start threads
    thread_read_camera.start()
    thread_streamer_camera.start()
    thread_object_detector.start()
    thread_streamer_object_detector.start()
    thread_face_detector.start()
    thread_streamer_face_detector.start()


    # Wait threads
    thread_read_camera.join()
    thread_streamer_camera.join()
    thread_object_detector.join()
    thread_streamer_object_detector.join()
    thread_face_detector.join()
    thread_streamer_face_detector.join()



