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


# Global variables
object_detection = []
person_detection = []
person_recognition = []


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
        encoding = face_recognition.face_encodings(face_image)[0]

        # Get name
        name = os.path.splitext(file)[0]

        # Add to lists
        known_faces_encoding.append(encoding)
        known_faces_name.append(name)



def task_read_camera(queue_to_streamer_computer_vision, queue_to_object_detection):

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

        try:
            # Wait for a coherent pair of frames: depth and color
            frame = pipe.wait_for_frames()
        except:
            exit(1)
        
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

        # Render the image
        queue_to_streamer_computer_vision.put(color_image.copy())
        queue_to_object_detection.put(color_image.copy())



def task_streamer(queue_from_streamer_camera, streamerPath):

    global object_detection
    global person_recognition

    time_stamp = time.time()
    fps_filt = 0

    # Create rstp stream
    streamer = videoOutput(streamerPath)

    while True:

        # Get image from queue
        image = queue_from_streamer_camera.get()

        # Object detection
        for object_name, track_id, x1, y1, x2, y2 in object_detection.copy():
            # Draw a box around the face
            cv2.rectangle(image, (x1, y1), (x2, y2), (0, 0, 255), 2)

            # Draw a label with a name below the face
            cv2.rectangle(image, (x1, y2 - 25), (x2, y2), (0, 0, 255), cv2.FILLED)
            text = object_name + ": " + str(track_id)
            cv2.putText(image, text, (x1 + 6, y2 - 6), cv2.FONT_HERSHEY_DUPLEX, 0.5, (255, 255, 255), 1)
        
        # Face detection
        for name, x1, y1, x2, y2 in person_recognition.copy():
            # Draw a box around the face
            cv2.rectangle(image, (x1, y1), (x2, y2), (0, 255, 0), 2)

            # Draw a label with a name below the face
            # cv2.rectangle(image, (x1, y2 - 25), (x2, y2), (0, 255, 0), cv2.FILLED)
            cv2.putText(image, name, (x1 + 6, y2 - 25), cv2.FONT_HERSHEY_DUPLEX, 0.5, (255, 255, 255), 1)

        # Calculate FPS
        dt = time.time() - time_stamp
        time_stamp = time.time()
        fps = 1 / dt
        fps_filt = 0.9 * fps_filt + 0.1 * fps

        # Add text
        cv2.putText(image, str(int(fps_filt)) + 'fps',  (5, 20), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 0), 2)

        # Render the image
        streamer.Render(cv2_to_cuda(image))



def task_object_detection(queue_from_streamer_camera, queue_to_face_recognition):

    global object_detection
    global person_detection

    # Detector
    net = detectNet("ssd-mobilenet-v2", threshold=0.5)

    # Configure tracker
    # minFrames         the number of re-identified frames for a track to be considered valid (default: 3)
    # dropFrames        number of consecutive lost frames before a track is dropped (default: 15)
    # overlapThreshold  how much IOU overlap is required for a bounding box to be matched (default: 0.5)
    net.SetTrackingEnabled(True)
    net.SetTrackingParams(minFrames=5, dropFrames=15, overlapThreshold=0.5)

    while True:

        # Temporal detection
        object_detection_temp = []

        # Persons
        persons = []

        # Get image from queue
        image = queue_from_streamer_camera.get()

        # Detect objects
        detections = net.Detect(cv2_to_cuda(image))

        # Loop into each detection
        for detection in detections:
            # Get class name
            object_name = net.GetClassDesc(detection.ClassID)

            # Get TrackID
            track_id = detection.TrackID

            # Get bounding box
            x1, y1, x2, y2 = int(detection.Left), int(detection.Top), int(detection.Right), int(detection.Bottom)

            # Add to list
            object_detection_temp.append((object_name, track_id, x1, y1, x2, y2))

            # Persons
            if object_name == "person":
                persons.append((x1, y1, x2, y2))

        # Copy lists
        object_detection = object_detection_temp.copy()
        person_detection = persons.copy()

        # Face detection
        if len(person_detection) > 0:
            # Send image to face recognition
            queue_to_face_recognition.put(image.copy())



def task_face_recognition(queue_from_object_detection):

    global person_detection
    global person_recognition

   # Create encoding list of known faces
    known_faces_encoding = []
    known_faces_name = []

    # Train faces
    train_faces("/face_detector/known_faces", known_faces_encoding, known_faces_name)


    while True:

        # Temporal recognition
        person_recognition_temp = []

        # Read frame from RRSP stream
        image = queue_from_object_detection.get()

        # Loop into each person
        for x1, y1, x2, y2 in person_detection.copy():

            # Crop image
            person_image = image[y1:y2, x1:x2]

            # Convert the image from BGR color (which OpenCV uses) to RGB color (which face_recognition uses)
            person_image = cv2.cvtColor(person_image, cv2.COLOR_RGB2BGR)
            person_image = cv2.resize(person_image, (0, 0), fx=0.5, fy=0.5)

            # Find all the faces and face encodings in the current frame of video
            face_locations = face_recognition.face_locations(person_image, model="cnn")
            face_encodings = face_recognition.face_encodings(person_image, face_locations)

            # Loop into each face
            for face_encoding in face_encodings:
                # See if the face is a match for the known face(s)
                matches = face_recognition.compare_faces(known_faces_encoding, face_encoding)

                # If no match was found in known_face_encodings, use the name "Unknown"
                name = "Unknown"

                # If a match was found in known_face_encodings, just use the first one.
                if True in matches:
                    first_match_index = matches.index(True)
                    name = known_faces_name[first_match_index]

                # Add to list
                person_recognition_temp.append((name, x1, y1, x2, y2))

        # Copy list
        person_recognition = person_recognition_temp.copy()



# Main
if __name__ == '__main__':

    # Create queue
    queue_from_camera_to_streamer_computer_vision = Queue(1)
    queue_from_camera_to_object_detection = Queue(1)
    queue_from_object_detection_to_face_recognition = Queue(1)

    # Create threads
    thread_read_camera = threading.Thread(target=task_read_camera, args=(queue_from_camera_to_streamer_computer_vision, queue_from_camera_to_object_detection,))
    thread_streamer_computer_vision = threading.Thread(target=task_streamer, args=(queue_from_camera_to_streamer_computer_vision, "rtsp://@:6000/serv/computer_vision",))
    thread_object_detection = threading.Thread(target=task_object_detection, args=(queue_from_camera_to_object_detection, queue_from_object_detection_to_face_recognition,))
    thread_face_recognition = threading.Thread(target=task_face_recognition, args=(queue_from_object_detection_to_face_recognition,))

    # Start threads
    thread_read_camera.start()
    thread_streamer_computer_vision.start()
    thread_object_detection.start()
    thread_face_recognition.start()

    # Wait threads
    thread_read_camera.join()
    thread_streamer_computer_vision.join()
    thread_object_detection.join()
    thread_face_recognition.join()
    