from jetson_utils import videoSource, videoOutput

# create video sources & outputs
input = videoSource("/dev/video0")
output = videoOutput("rtsp://@:8554/d435/rgb")

# capture frames until EOS or user exits
numFrames = 0

while True:
    # capture the next image
    img = input.Capture()

    if img is None: # timeout
        continue  

    numFrames += 1

    # render the image
    output.Render(img)
    
    # update the title bar
    if numFrames % 50 == 0:
        print(f" {img.width}x{img.height} | {output.GetFrameRate()} FPS")

    # exit on input/output EOS
    if not input.IsStreaming() or not output.IsStreaming():
        break