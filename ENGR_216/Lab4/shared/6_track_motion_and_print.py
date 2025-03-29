#!/usr/bin/env python3
__version__ = '2.0'

'''
Demo of using TrackingCamera class.
Get motions from camera and prints motion data in terminal.
The data and video are saved (`example_6.csv` and `example_6.csv`)
'''

from lab.tracking import TrackingCamera
import time # just for formatting time

def run_camera():

    # Set TrackingCamera arguments. 
    camera_kwargs = {
        'input_source': 0,                    # camera id, set this to 0 if you want to read live camera data
        'output_video': 'example_6.mp4',      # optional, save the output video file (`mp4` format only)
        'output_data' : 'example_6.csv',      # optional, save the tracking data (to `.csv` files)
        'mode': 'motion',                     # optional, the camera mode [recording, tracking (default), motion, calibration]
        'camera_settings': (1024, 1024, 90),  # optional (width, height, fps), (1920, 1080, 30) by default
        'flip-method' : 2,                    # 0=no rotation, 2= rotate 180 degrees, 4=horizontal flip, 6=vertical-flip
        'camera_distance': .76                # camera distance (in METERS) to stickers, required for tracking and motion modes
                                              # This must be set correctly to calculate acceleration or velocity reliably
    }

    # Create & run TrackingCamera instance.
    with TrackingCamera(**camera_kwargs) as camera:
        while camera.is_running:

            # Read a frame and any frame data
            #  the contents of the frame_data depends on the 'mode' selected above 
            #  if the read failed (due to hardware or driver issues, ...), return values are None
            frame, frame_data = camera.read_frame()
    
            # Make sure this is not empty
            if frame is None:
                continue

            # display to screen and save to output file as needed
            camera.display_frame(frame,frame_data)
            
            # get the frame number from the tracking data and report every so many frames
            if (frame_data["frame_no"] % 90 == 0 ):
                
                # convert time in ms to HH:MM:SS format
                elapsed_time_str = time.strftime('%H:%M:%S', time.gmtime(frame_data["time"]/1000))

                # print the frame and stickers found
                print("Frame {} : elapsed time = {} ms ".format(frame_data["frame_no"], elapsed_time_str))
                for marker_name, marker_arr in frame_data["markers"].items():
                    print("\t {} : ".format(marker_name),end='')
                    for m in marker_arr:
                        print(" {}, ".format(m["pos_pixel"]),end='')
                    print("")#
            

# Run main.
if __name__ == "__main__":
    run_camera()
