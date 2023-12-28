import sys
from jetson_utils import videoSource, videoOutput, Log

# create video sources & outputs
input = videoSource("/dev/video1", argv=["--input-width=1280", "--input-height=720", "--input-rate=30", "--input-codec=H264"])
output = videoOutput("rtsp://@:6000/d435/rgb", argv=[""])

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
        Log.Verbose(f"video-viewer:  captured {numFrames} frames ({img.width} x {img.height})")
        print(f" {img.width}x{img.height} | {output.GetFrameRate()} FPS")

    # exit on input/output EOS
    if not input.IsStreaming() or not output.IsStreaming():
        break