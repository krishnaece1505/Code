#---------------------------------------------------------------------------------------------------------------
#
# Module : PiChat v1.0- A server using Raspberry Pi 2 - Client Module (Windows PC)
#
# Author : Krishnaswamy Kannan
#
# Copyright (c) 2015, Krishnaswamy Kannan
# All rights reserved.
#
#---------------------------------------------------------------------------------------------------------------
import socket
import os

os.system("cls") #change 'cls' to 'clear' if client is linux
print '\n---------------------- Welcome to PiChat v1.0 ----------------------'

# --------------- Define the host IP and Port number for the Socket connection ---------------
host = '192.168.1.6'# ip of raspberry pi
port = 5002

while True:
    # --------------- Create the socket ---------------
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # --------------- Connect to the socket at ADDR given by host ---------------
    s.connect((host, port))
    text = raw_input('You : ')
    # --------------- Send the text input over the socket using TCP ---------------
    s.send(text)
    print "Raspberry Pi :",s.recv(4096)
    # --------------- Close the socket connection ---------------
    s.close()