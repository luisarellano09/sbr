import json
import threading
from queue import Queue 
from jetson_utils import videoOutput, cudaFromNumpy
from jetson_inference import detectNet
import pyrealsense2 as rs
import face_recognition
import pika
import numpy as np
import cv2
import time
import os


# ==================================================================================================
# Parameters
# ==================================================================================================

THREAD_QUEUE_CAPACITY = 1

COLOR_IMAGE_WIDTH = 1280
COLOR_IMAGE_HEIGHT = 720
COLOR_IMAGE_FPS = 30
DEPTH_IMAGE_WIDTH = 1280
DEPTH_IMAGE_HEIGHT = 720
DEPTH_IMAGE_FPS = 30

STREAMER_COMPUTER_VISION_PATH = "rtsp://@:6000/serv/computer_vision"

OBJECT_DETECTION_THRESHOLD = 0.5
OBJECT_DETECTION_TRACKING_MIN_FRAMES = 15
OBJECT_DETECTION_TRACKING_DROP_FRAMES = 30

FACE_RECOGNITION_TRAINING_PATH = "/face_detector/known_faces"
FACE_RECOGNITION_CONTINUOUS_FRAMES = 5
FACE_RECOGNITION_RECHECK_FRAMES = 50
FACE_RECOGNITION_CONTINUOUS_MATCHES = 3
FACE_RECOGNITION_TOLERANCE = 0.6

HEARTBEAT_INITIAL_DELAY = 30
HEARTBEAT_MAX_TIME_WITHOUT_IMAGE = 3


# ==================================================================================================
# Global definitions
# ==================================================================================================
class person:
    name: str
    name_processing: str
    matches: int
    counter: int


# ==================================================================================================
# Global variables
# ==================================================================================================
object_detection = []
person_recognition = {}
frame_number = 0


# ==================================================================================================
# Functions
# ==================================================================================================

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


# ==================================================================================================
# Task Read Camera
# ==================================================================================================
def task_read_camera(queue_to_streamer_computer_vision, queue_to_object_detection):

    try:

        global frame_number

        # Create pipeline
        pipe = rs.pipeline()
        cfg  = rs.config()

        # Enable streams
        cfg.enable_stream(rs.stream.color, COLOR_IMAGE_WIDTH, COLOR_IMAGE_HEIGHT, rs.format.rgb8, COLOR_IMAGE_FPS)
        cfg.enable_stream(rs.stream.depth, DEPTH_IMAGE_WIDTH, DEPTH_IMAGE_HEIGHT, rs.format.z16, DEPTH_IMAGE_FPS)

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

            # Increase frame number
            frame_number += 1

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
            queue_to_streamer_computer_vision.put((frame_number, color_image.copy()))
            queue_to_object_detection.put((frame_number, color_image.copy()))

    except Exception as e:
        print(e)
        exit(1)


# ==================================================================================================
# Task Streamer
# ==================================================================================================
def task_streamer(queue_from_streamer_camera):

    try:
        global object_detection
        global person_recognition

        time_stamp = time.time()
        fps_filt = 0

        # Create rstp stream
        streamer = videoOutput(STREAMER_COMPUTER_VISION_PATH)

        # Initial frame id
        frame_id_obj = 0

        while True:
            # Get image from queue
            frame_id, image = queue_from_streamer_camera.get()

            # Object detection
            for frame_id_obj, object_class, track_id, x1, y1, x2, y2 in object_detection.copy():
                # Draw a box around the face
                cv2.rectangle(image, (x1, y1), (x2, y2), (0, 0, 255), 2)

                # Draw a label with a name below the face
                cv2.rectangle(image, (x1, y2 - 25), (x2, y2), (0, 0, 255), cv2.FILLED)

                # Check if object is a person
                if object_class == "person":
                    # Check if person is in list
                    if track_id in person_recognition:
                        text = object_class + ": " + str(track_id) + " (" + person_recognition[track_id].name + ")"
                    else:
                        text = object_class + ": " + str(track_id) + " (Unknown)"
                else:
                    text = object_class + ": " + str(track_id)

                cv2.putText(image, text, (x1 + 6, y2 - 6), cv2.FONT_HERSHEY_DUPLEX, 0.5, (255, 255, 255), 1)
            
            # Calculate FPS
            dt = time.time() - time_stamp
            time_stamp = time.time()
            fps = 1 / dt
            fps_filt = 0.9 * fps_filt + 0.1 * fps

            # Add text
            text_info = "FPS: " + str(int(fps_filt)) + " - Frame: " + str(frame_id_obj) + "/" + str(frame_id)
            cv2.putText(image, text_info,  (5, 20), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 0), 2)

            # Render the image
            streamer.Render(cv2_to_cuda(image))

    except Exception as e:
        print(e)
        exit(1)


# ==================================================================================================
# Task Object Detection
# ==================================================================================================
def task_object_detection(queue_from_streamer_camera, queue_to_face_recognition):
    
    try:

        global object_detection

        # Detector
        net = detectNet("ssd-mobilenet-v2", threshold=OBJECT_DETECTION_THRESHOLD)

        # Configure tracker
        # minFrames         the number of re-identified frames for a track to be considered valid (default: 3)
        # dropFrames        number of consecutive lost frames before a track is dropped (default: 15)
        # overlapThreshold  how much IOU overlap is required for a bounding box to be matched (default: 0.5)
        net.SetTrackingEnabled(True)
        net.SetTrackingParams(minFrames=OBJECT_DETECTION_TRACKING_MIN_FRAMES, dropFrames=OBJECT_DETECTION_TRACKING_DROP_FRAMES, overlapThreshold=OBJECT_DETECTION_THRESHOLD)

        while True:

            # Temporal detection
            object_detection_temp = []

            # Persons
            persons = []

            # Get image from queue
            frame_id, image = queue_from_streamer_camera.get()

            # Detect objects
            detections = net.Detect(cv2_to_cuda(image))

            # Loop into each detection
            for detection in detections:
                # Get class name
                object_class = net.GetClassDesc(detection.ClassID)

                # Get TrackID
                track_id = detection.TrackID

                # Get bounding box
                x1, y1, x2, y2 = int(detection.Left), int(detection.Top), int(detection.Right), int(detection.Bottom)

                # Add to list
                object_detection_temp.append((frame_id, object_class, track_id, x1, y1, x2, y2))

                # Persons
                if object_class == "person":
                    persons.append((track_id, x1, y1, x2, y2))

            # Copy lists
            object_detection = object_detection_temp.copy()

            # Face detection
            if len(persons) > 0:
                # Send image to face recognition
                queue_to_face_recognition.put((image.copy(), persons.copy()))

    except Exception as e:
        print(e)
        exit(1)


# ==================================================================================================
# Task Face Recognition
# ==================================================================================================
def task_face_recognition(queue_from_object_detection):

    try:

        global person_recognition

        # Create encoding list of known faces
        known_faces_encoding = []
        known_faces_name = []

        # Train faces
        train_faces(FACE_RECOGNITION_TRAINING_PATH, known_faces_encoding, known_faces_name)

        while True:
            # Read frame from RRSP stream
            image, persons = queue_from_object_detection.get()

            # Loop into each person
            for track_id, x1, y1, x2, y2 in persons:

                # Check if person is not already in list
                if track_id not in person_recognition:
                    # Create person
                    person_recognition[track_id] = person()
                    person_recognition[track_id].name = "Unknown"
                    person_recognition[track_id].name_processing = "Unknown"
                    person_recognition[track_id].matches = 0
                    person_recognition[track_id].counter = 0
                
                # Check if person does not have a name
                if person_recognition[track_id].name == "Unknown":

                    # Increase counter
                    person_recognition[track_id].counter += 1

                    # Check counter
                    if person_recognition[track_id].counter < FACE_RECOGNITION_CONTINUOUS_FRAMES or (person_recognition[track_id].counter > FACE_RECOGNITION_CONTINUOUS_FRAMES and person_recognition[track_id].counter % FACE_RECOGNITION_RECHECK_FRAMES == 0):
                
                        # Crop image
                        person_image = image[y1:y2, x1:x2]

                        # Convert the image from BGR color (which OpenCV uses) to RGB color (which face_recognition uses)
                        person_image = cv2.cvtColor(person_image, cv2.COLOR_RGB2BGR)

                        # Find all the faces and face encodings in the current frame of video
                        face_locations = face_recognition.face_locations(person_image, model="cnn")
                        face_encodings = face_recognition.face_encodings(person_image, face_locations)

                        # Loop into each face
                        for face_encoding in face_encodings:
                            # See if the face is a match for the known face(s)
                            matches = face_recognition.compare_faces(known_faces_encoding, face_encoding, FACE_RECOGNITION_TOLERANCE)

                            # If no match was found in known_face_encodings, use the name "Unknown"
                            name = "Unknown"

                            # If a match was found in known_face_encodings, just use the first one.
                            if True in matches:
                                first_match_index = matches.index(True)
                                name = known_faces_name[first_match_index]

                            # Analyse result: When name is not unknown
                            if name != "Unknown":
                                if person_recognition[track_id].matches > 0 and person_recognition[track_id].name_processing == name:
                                    person_recognition[track_id].name_processing = name
                                    person_recognition[track_id].matches += 1
                                    person_recognition[track_id].counter = 0
                                elif person_recognition[track_id].matches > 0 and person_recognition[track_id].name_processing != name:
                                    person_recognition[track_id].name_processing = name
                                    person_recognition[track_id].matches = 1
                                    person_recognition[track_id].counter = 0
                                elif person_recognition[track_id].matches == 0:
                                    person_recognition[track_id].name_processing = name
                                    person_recognition[track_id].matches += 1
                                    person_recognition[track_id].counter = 0

                                # Check if matches are reached
                                if person_recognition[track_id].matches == FACE_RECOGNITION_CONTINUOUS_MATCHES:
                                    person_recognition[track_id].name = name

    except Exception as e:
        print(e)
        exit(1)


# ==================================================================================================
# Task Heartbeat
# ==================================================================================================
def task_heartbeat():
    try:

        global frame_number

        # Initial delay
        time.sleep(HEARTBEAT_INITIAL_DELAY)

        # Time without image
        timeWithoutImage = 0

        # Get current frame number
        previous_frame_number = 0

        while True:
            # Check if frame number has changed
            if previous_frame_number == frame_number:
                # Increase time without image
                timeWithoutImage += 1

                # Check if time without image is greater than max time
                if timeWithoutImage > HEARTBEAT_MAX_TIME_WITHOUT_IMAGE:
                    print("Error: No image received")
                    # Exit program
                    exit(1)
            else:
                
                # Reset time without image
                timeWithoutImage = 0

            # Get current frame number
            previous_frame_number = frame_number

            print("[Heartbeat]: " + str(frame_number))

            # Delay 1s
            time.sleep(1)

    except Exception as e:
        print(e)
        exit(1)    


# ==================================================================================================
# Task RabbitMQ Publisher
# ==================================================================================================
def task_rabbitmq_publisher_objects():
    try:

        global frame_number
        global object_detection
        global person_recognition

        # Get environment variables
        rabbitmq_host = os.environ['RABBITMQ_HOST']
        rabbitmq_user = os.environ['RABBITMQ_USER']
        rabbitmq_pass = os.environ['RABBITMQ_PASS']

        # Create connection
        connection = pika.BlockingConnection(pika.ConnectionParameters(host=rabbitmq_host, credentials=pika.PlainCredentials(rabbitmq_user, rabbitmq_pass)))
        channel = connection.channel()

        # Declare exchange
        channel.exchange_declare(
            exchange='SBR_EXCH_COMPUTER_VISION', 
            exchange_type='topic',
            durable=False,
            auto_delete=False,
            internal=False,
        )

        # Declare queue
        channel.queue_declare(queue='Q_SBR_FROM_COMPUTER_VISION_OBJECTS', exclusive=True)

        # Previous frame number
        previous_frame_number = 0

        # Previous object frame id
        previous_object_frame_id = 0

        # Loop
        while True:
            if frame_number != previous_frame_number:
                # Get objects
                objects = object_detection.copy()
                persons = person_recognition.copy()

                # Check if objetcs is not empty
                if len(objects) > 0:
                    object_frame_id = objects[0][0]

                    # Check if frame id has changed
                    if object_frame_id != previous_object_frame_id:
                        # On each object
                        for frame_id, object_class, track_id, x1, y1, x2, y2 in objects:
                            # Check if object is a person
                            if object_class == "person":
                                # Check if person is in list
                                if track_id in persons:
                                    name = persons[track_id].name
                                else:
                                    name = "Unknown"
                            else:
                                name = object_class
                            
                            # Create message
                            message = {
                                "frame_id": frame_id,
                                "object_class": object_class,
                                "track_id": track_id,
                                "x1": x1,
                                "y1": y1,
                                "x2": x2,
                                "y2": y2,
                                "name": name
                            }

                            # Publish message persons
                            if object_class == "person":
                                routing_key = "PERSONS." + name
                                channel.basic_publish(exchange='SBR_EXCH_COMPUTER_VISION', routing_key=routing_key, body=json.dumps(message))
                            else:
                                channel.basic_publish(exchange='SBR_EXCH_COMPUTER_VISION', routing_key='OBJECTS', body=json.dumps(message))

                        # Save previous object frame id
                        previous_object_frame_id = object_frame_id
                
            # Save previous frame number
            previous_frame_number = frame_number

    except Exception as e:
        print(e)
        exit(1)

# ==================================================================================================
# Main function
# ==================================================================================================
if __name__ == '__main__':

    try:

        # Create queue
        queue_from_camera_to_streamer_computer_vision = Queue(THREAD_QUEUE_CAPACITY)
        queue_from_camera_to_object_detection = Queue(THREAD_QUEUE_CAPACITY)
        queue_from_object_detection_to_face_recognition = Queue(THREAD_QUEUE_CAPACITY)

        # Create threads
        thread_read_camera = threading.Thread(target=task_read_camera, args=(queue_from_camera_to_streamer_computer_vision, queue_from_camera_to_object_detection,))
        thread_streamer_computer_vision = threading.Thread(target=task_streamer, args=(queue_from_camera_to_streamer_computer_vision,))
        thread_object_detection = threading.Thread(target=task_object_detection, args=(queue_from_camera_to_object_detection, queue_from_object_detection_to_face_recognition,))
        thread_face_recognition = threading.Thread(target=task_face_recognition, args=(queue_from_object_detection_to_face_recognition,))
        thread_heartbeat = threading.Thread(target=task_heartbeat)
        thread_rabbitmq_publisher_objects = threading.Thread(target=task_rabbitmq_publisher_objects)

        # Start threads
        thread_read_camera.start()
        thread_streamer_computer_vision.start()
        thread_object_detection.start()
        thread_face_recognition.start()
        thread_heartbeat.start()
        thread_rabbitmq_publisher_objects.start()

        # Wait threads
        thread_read_camera.join()
        thread_streamer_computer_vision.join()
        thread_object_detection.join()
        thread_face_recognition.join()
        thread_heartbeat.join()
        thread_rabbitmq_publisher_objects.join()

    except Exception as e:
        print(e)
        exit(1)
    