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
profile = pipe.start(cfg)

# Getting the depth sensor's depth scale (see rs-align example for explanation)
depth_sensor = profile.get_device().first_depth_sensor()
depth_scale = depth_sensor.get_depth_scale()
print("Depth Scale is: " , depth_scale)

#  clipping_distance_in_meters meters away
clipping_distance_in_meters = 1 #1 meter
clipping_distance = clipping_distance_in_meters / depth_scale

while True:
    frame = pipe.wait_for_frames()
    depth_frame = frame.get_depth_frame()
    color_frame = frame.get_color_frame()

    depth_image = np.asanyarray(depth_frame.get_data())
    color_image = np.asanyarray(color_frame.get_data())

     # Remove background - Set pixels further than clipping_distance to grey
    grey_color = 153
    depth_image_3d = np.dstack((depth_image,depth_image,depth_image)) #depth image is 1 channel, color is 3 channels
    bg_removed = np.where((depth_image_3d > clipping_distance) | (depth_image_3d <= 0), grey_color, color_image)

    # Render images:
    #   depth align to color on left
    #   depth on right
    depth_colormap = cv2.applyColorMap(cv2.convertScaleAbs(depth_image, alpha=0.03), cv2.COLORMAP_JET)
    adjustedDepth = np.hstack((bg_removed, depth_colormap))
    
    adjustedRGB = cv2.addWeighted( color_image, 1, color_image, 0, 15)

    gsFrameDepth = cudaFromNumpy(adjustedDepth)
    gsFrameRGB = cudaFromNumpy(adjustedRGB)

    # Render the image
    streamerCameraDepth.Render(gsFrameDepth)
    streamerCameraRGB.Render(gsFrameRGB)


# Info: To receive the stream use the following command
# gst-launch-1.0 -v rtspsrc location=rtsp://sbrnx:6000/d435/depth latency=0 ! rtph264depay ! h264parse ! avdec_h264 ! autovideosink
# gst-launch-1.0 -v rtspsrc location=rtsp://sbrnx:6000/d435/rgb latency=0 ! rtph264depay ! h264parse ! avdec_h264 ! autovideosink
