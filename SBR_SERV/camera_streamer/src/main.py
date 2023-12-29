from jetson_utils import videoSource, videoOutput, cudaFromNumpy
import pyrealsense2 as rs
import numpy as np
import cv2

# Create rstp streams
streamerCameraDepth = videoOutput("rtsp://@:6000/d435/depth")
streamerCameraRGB = videoOutput("rtsp://@:6000/d435/rgb")

# Create pipeline
pipe = rs.pipeline()
cfg  = rs.config()

# Enable streams
cfg.enable_stream(rs.stream.color, 848,480, rs.format.rgb8, 60)
cfg.enable_stream(rs.stream.depth, 848,480, rs.format.z16, 60)

# Start streaming
pipe.start(cfg)

while True:
    frame = pipe.wait_for_frames()
    depth_frame = frame.get_depth_frame()
    color_frame = frame.get_color_frame()

    depth_image = np.asanyarray(depth_frame.get_data())
    color_image = np.asanyarray(color_frame.get_data())

    adjustedDepth = cv2.applyColorMap(cv2.convertScaleAbs(depth_image, alpha=0.5), cv2.COLORMAP_JET)
    adjustedRGB = cv2.addWeighted( color_image, 1, color_image, 0, 15)

    gsFrameDepth = cudaFromNumpy(adjustedDepth)
    gsFrameRGB = cudaFromNumpy(adjustedRGB)

    # Render the image
    streamerCameraDepth.Render(gsFrameDepth)
    streamerCameraRGB.Render(gsFrameRGB)
