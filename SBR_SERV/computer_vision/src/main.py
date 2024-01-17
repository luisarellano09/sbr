import threading
from queue import Queue 
from jetson_utils import videoOutput, cudaFromNumpy
from jetson_inference import detectNet
import pyrealsense2 as rs
import face_recognition
import numpy as np
import cv2
import time
import os


# Object detection
object_detector_network = detectNet("ssd-mobilenet-v2", threshold=0.5)

# Create encoding list of known faces
known_faces_encoding = []
known_faces_name = []

# Detections
object_detection = []
person_recognition = []

# Create rstp stream
streamer = videoOutput("rtsp://@:6000/serv/computer_vision")


# Function to convert cv2 image to cuda image
def cv2_to_cuda(cv_image):
    # Convert image to cuda
    return cudaFromNumpy(cv_image)


# Train faces
def train_faces(path):

    global known_faces_encoding
    global known_faces_name

    # Loop into folder  and encode faces from "./faces" folder
    for file in os.listdir(path):
        # Load face
        face_image = face_recognition.load_image_file(path + "/" + file)

        # Encode face
        encoding = face_recognition.face_encodings(face_image)[0]

        # Get name
        name = os.path.splitext(file)[0]

        # Add to lists
        known_faces_encoding.append(encoding)
        known_faces_name.append(name)


# Read camera
def loop_read_camera():

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

        # Adjust image RGB
        color_image = cv2.addWeighted( color_image, 1, color_image, 0, 15)

        # Thread detect objects
        threading.Thread(target=task_object_detector, args=(color_image.copy(),)).start()

        # Thread streamer
        threading.Thread(target=task_streamer, args=(color_image.copy(),)).start()


# Task streamer
def task_streamer(image):

    global object_detection
    global face_detection

    # Object detection
    for object_name, (x1, y1), (x2, y2) in object_detection.copy():
        # Draw a box around the face
        cv2.rectangle(image, (x1, y1), (x2, y2), (0, 0, 255), 2)

        # Draw a label with a name below the face
        cv2.rectangle(image, (x1, y2 - 25), (x2, y2), (0, 0, 255), cv2.FILLED)
        cv2.putText(image, object_name, (x1 + 6, y2 - 6), cv2.FONT_HERSHEY_DUPLEX, 0.5, (255, 255, 255), 1)
    
    # Person detection
    for name, (x1, y1), (x2, y2) in face_detection.copy():
        # Draw a box around the person
        cv2.rectangle(image, (x1, y1), (x2, y2), (255, 0, 0), 2)

        # Draw a label with a name below the person
        cv2.rectangle(image, (x1, y2 - 25), (x2, y2), (255, 0, 0), cv2.FILLED)
        cv2.putText(image, name, (x1 + 6, y2 - 6), cv2.FONT_HERSHEY_DUPLEX, 0.5, (255, 255, 255), 1)

    # Render the image
    streamer.Render(cv2_to_cuda(image))


# Task object detector
def task_object_detector(image):

    global object_detection

    # Temporal detection
    object_detection_temp = []

    # List of Persons
    persons = []

    # Detect objects
    detections = object_detector_network.Detect(cv2_to_cuda(image))

    # Loop into each detection
    for detection in detections:
        # Get class name
        object_name = object_detector_network.GetClassDesc(detection.ClassID)

        # Get bounding box
        x1, y1, x2, y2 = int(detection.Left), int(detection.Top), int(detection.Right), int(detection.Bottom)

        # Add to list
        object_detection_temp.append((object_name, (x1, y1), (x2, y2)))

        # Person recognition
        if object_name == "person":
            # Add to list
            persons.append((x1, y1, x2, y2))

    # Copy list
    object_detection = object_detection_temp.copy()

    # Thread face detector
    threading.Thread(target=task_face_detector, args=(image.copy(), persons)).start()



def task_face_detector(image, persons):

    global face_detection
    global known_faces_encoding
    global known_faces_name

    # Temporal detection
    face_detection_temp = []

    
    # Loop into each person
    for x1, y1, x2, y2 in persons:
        # Crop image
        face_image = image[y1:y2, x1:x2]

        # Convert the image from BGR color (which OpenCV uses) to RGB color (which face_recognition uses)
        face_image = cv2.cvtColor(face_image, cv2.COLOR_RGB2BGR)
        # face_image = cv2.resize(face_image, (0, 0), fx=0.5, fy=0.5)

        # Find all the faces and face encodings in the image
        face_locations = face_recognition.face_locations(face_image, model="cnn")
        face_encodings = face_recognition.face_encodings(face_image, face_locations)

        # Loop into each face
        for face_encoding in zip(face_locations, face_encodings):
            # See if the face is a match for the known face(s)
            matches = face_recognition.compare_faces(known_faces_encoding, face_encoding)

            # If no match was found in known_face_encodings, use the name "Unknown"
            name = "Unknown"

            # If a match was found in known_face_encodings, just use the first one.
            if True in matches:
                first_match_index = matches.index(True)
                name = known_faces_name[first_match_index]

            # Add to list
            face_detection_temp.append((name, (x1, y1), (x2, y2)))


    # Copy list
    face_detection = face_detection_temp.copy()



# Main
if __name__ == '__main__':

    # Train faces
    train_faces("/face_detector/known_faces")

    # Loop camera
    loop_read_camera()


