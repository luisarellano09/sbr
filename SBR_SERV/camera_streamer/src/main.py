from jetson_utils import videoOutput, cudaFromNumpy
import pyrealsense2 as rs
import numpy as np
import cv2

# Function to convert cv2 image to cuda image
def cv2_to_cuda(cv_image):
    # Convert image to cuda
    return cudaFromNumpy(cv_image)


# Main
if __name__ == '__main__':
    # Create rstp streams
    streamerCameraDepth = videoOutput("rtsp://@:6000/d435/depth")
    streamerCameraRGB = videoOutput("rtsp://@:6000/d435/rgb")

    # Create pipeline
    pipe = rs.pipeline()
    cfg  = rs.config()

    # Enable streams
    cfg.enable_stream(rs.stream.color, 1280, 720, rs.format.rgb8, 30)
    cfg.enable_stream(rs.stream.depth, 1280, 720, rs.format.z16, 30)

    # Start streaming
    profile = pipe.start(cfg)

    # Getting the depth sensor's depth scale (see rs-align example for explanation)
    depth_sensor = profile.get_device().first_depth_sensor()
    depth_scale = depth_sensor.get_depth_scale()
    print("Depth Scale is: " , depth_scale)

    #  Factor to convert to cm
    distance_factor = 0.1


    # Create an align object
    # rs.align allows us to perform alignment of depth frames to others frames
    # The "align_to" is the stream type to which we plan to align depth frames.
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
        depth_image = np.dstack((depth_image,depth_image,depth_image)) #depth image is 1 channel, color is 3 channels
        depth_image = cv2.multiply(depth_image, distance_factor)

        

        # test
        print(depth_image[360, 640])
        depth_image_mod = cv2.circle(depth_image, (640, 360), 10, (255, 0, 0), -1)
        
        ##


        # Adjust image
        # depth_image = cv2.applyColorMap(cv2.convertScaleAbs(depth_image, alpha=0.03), cv2.COLORMAP_JET)
        color_image = cv2.addWeighted( color_image, 1, color_image, 0, 15)

        # Render the image
        streamerCameraDepth.Render(cv2_to_cuda(depth_image_mod))
        streamerCameraRGB.Render(cv2_to_cuda(color_image))
