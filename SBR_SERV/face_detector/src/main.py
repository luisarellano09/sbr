from jetson_utils import videoSource, videoOutput, cudaFromNumpy, cudaAllocMapped, cudaConvertColor, cudaToNumpy, cudaDeviceSynchronize
import cv2
import time
import os
import face_recognition


# Init frame rate calculation
time_stamp = time.time()
fps_filt = 0

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
    

# Main
if __name__ == '__main__':

    # Create encoding list of known faces
    known_faces_encoding = []
    known_faces_name = []

    # Train faces
    train_faces("/face_detector/known_faces", known_faces_encoding, known_faces_name)

    # Create Video Source
    cameraRGB = videoSource("rtsp://sbrnx:6001/d435/rgb")

    # Create Video Output
    streamerObjectDetector = videoOutput("rtsp://@:6003/serv/face_detector")

    while True:
        # Read frame from RRSP stream
        cuda_image = cameraRGB.Capture()

        # Check if there is a valid image
        if cuda_image is None:
            continue

        # Convert image to numpy (opencv format)
        cv_image = cuda_to_cv2(cuda_image)

        # Convert the image from BGR color (which OpenCV uses) to RGB color (which face_recognition uses)
        detect_image = cv2.cvtColor(cv_image, cv2.COLOR_RGB2BGR)
        detect_image = cv2.resize(detect_image, (0, 0), fx=0.25, fy=0.25)

        # Find all the faces and face encodings in the image
        face_locations = face_recognition.face_locations(detect_image, model="cnn")
        face_encodings = face_recognition.face_encodings(detect_image, face_locations, model="small")

        # Loop into each face
        for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
            # See if the face is a match for the known face(s)
            matches = face_recognition.compare_faces(known_faces_encoding, face_encoding)

            # If no match was found in known_face_encodings, use the name "Unknown"
            name = "Unknown"

            # If a match was found in known_face_encodings, just use the first one.
            if True in matches:
                first_match_index = matches.index(True)
                name = known_faces_name[first_match_index]

            top *= 4
            right *= 4
            bottom *= 4
            left *= 4

            # Draw a box around the face
            cv2.rectangle(cv_image, (left, top), (right, bottom), (0, 0, 255), 2)

            # Draw a label with a name below the face
            cv2.rectangle(cv_image, (left, bottom - 25), (right, bottom), (0, 0, 255), cv2.FILLED)
            cv2.putText(cv_image, name, (left + 6, bottom - 6), cv2.FONT_HERSHEY_DUPLEX, 0.5, (255, 255, 255), 1)


        # Calculate FPS
        dt = time.time() - time_stamp
        time_stamp = time.time()
        fps = 1 / dt
        fps_filt = 0.9 * fps_filt + 0.1 * fps

        # Add text
        cv2.putText(cv_image, str(int(fps_filt)) + 'fps',  (5, 20), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 0), 2)
        
        # Render the image
        streamerObjectDetector.Render(cv2_to_cuda(cv_image))