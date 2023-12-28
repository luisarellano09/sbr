import threading
from jetson_utils import videoSource, videoOutput

# create video sources & outputs
cameraIR = videoSource("/dev/video0")
cameraRGB = videoSource("/dev/video1")

streamerCameraIR = videoOutput("rtsp://@:6000/d435/ir")
streamerCameraRGB = videoOutput("rtsp://@:6000/d435/rgb")

def task_camera_process(camera, streamer):
    # Number of frames captured
    numFramesIR = 0

    # process frames until the user exits
    while True:
        # capture the next image
        image = camera.Capture()

        # Check if there is image
        if image is None:
            continue

        numFramesIR += 1

        # Render the image
        streamer.Render(image)
    
        # update the title bar
        if numFramesIR % 50 == 0:
            print(f" {threading.current_thread().name}: {image.width}x{image.height} | {streamer.GetFrameRate()} FPS")

        # exit on input/output EOS
        if not camera.IsStreaming() or not streamer.IsStreaming():
            break


if __mame__ == "__main__":

    # Define the threads
    threadIR = threading.Thread(target=task_camera_process, args=(cameraIR, streamerCameraIR), name="IR")
    threadRGB = threading.Thread(target=task_camera_process, args=(cameraRGB, streamerCameraRGB), name="RGB")

    # start the threads
    threadIR.start()
    threadRGB.start()

    # wait for the threads to finish
    threadIR.join()
    threadRGB.join()