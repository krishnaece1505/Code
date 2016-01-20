#---------------------------------------------------------------------------------------------------------------
#
# Module : Home Surveillance using Raspberry Pi 2 and Pi-NoIR Camera
#
# Author : Krishnaswamy Kannan
#
# Copyright (c) 2016, Krishnaswamy Kannan
# All rights reserved.
#
#---------------------------------------------------------------------------------------------------------------

# --------------- Import the required libraries ---------------
from subprocess import call # Spawn a process for Dropbox-Uploader Bash script
import picamera # Raspberry Pi-NoIR Camera
import time # System time for timestamps

# --------------- Set the timestamp format here --------------- 
timestamp = time.strftime("%d-%m-%Y_%H:%M")
# --------------- Create an instance of PiCamera class i.e. camera object ---------------
camera = picamera.PiCamera()
# --------------- Flip the image (Camera was flipped in my setup) ---------------
camera.rotation=180
# --------------- Brightness adjusted to suit indoor lighting conditions ---------------
camera.brightness=55
# --------------- Capture the image and save with timestamp ---------------
camera.capture("/home/pi/surveillance/"+timestamp+".jpg")
# --------------- Store the command line argument to initiate the uploader script  ---------------
photofile = "/home/pi/Dropbox-Uploader/dropbox_uploader.sh upload /home/pi/surveillance/"+timestamp+".jpg "+timestamp+".jpg "
# --------------- Spawn the subprocess by calling the command line argument via Shell ---------------
call([photofile], shell=True)
