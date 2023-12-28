from jetson_utils import videoSource, videoOutput

# create video sources & outputs
cameraIR = videoSource("/dev/video0")
cameraRGB = videoSource("/dev/video1")

streamerCameraIR = videoOutput("rtsp://@:6000/d435/ir")
streamerCameraRGB = videoOutput("rtsp://@:6000/d435/rgb")

numFramesIR = 0
numFramesRGB = 0

while True:
    # capture the next images
    imageIR = cameraIR.Capture()
    imageRGB = cameraRGB.Capture()

    if imageIR is not None: # timeout
        numFramesIR += 1

        # render the image
        streamerCameraIR.Render(imageIR)
    
        # update the title bar
        if numFramesIR % 50 == 0:
            print(f" {imageIR.width}x{imageIR.height} | {streamerCameraIR.GetFrameRate()} FPS")

    if imageRGB is not None: # timeout
        numFramesRGB += 1

        # render the image
        streamerCameraRGB.Render(imageRGB)
    
        # update the title bar
        if numFramesRGB % 50 == 0:
            print(f" {imageRGB.width}x{imageRGB.height} | {streamerCameraRGB.GetFrameRate()} FPS")

    # exit on input/output EOS
    if not cameraIR.IsStreaming() or not cameraRGB.IsStreaming() or  not streamerCameraIR.IsStreaming() or not streamerCameraRGB.IsStreaming():
        break