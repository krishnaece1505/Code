#---------------------------------------------------------------------------------------------------------------
#
# Module : PiChat v1.0- A server using Raspberry Pi 2 - Server Module (Pi running debian)
#
# Author : Krishnaswamy Kannan
#
# Copyright (c) 2015, Krishnaswamy Kannan
# All rights reserved.
#
#---------------------------------------------------------------------------------------------------------------

import socket
import sys
import os

os.system("clear")
print '\n---------------------- Welcome to PiChat v1.0 ----------------------'

# --------------- Create the socket ---------------
s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
# --------------- Define the host IP and Port number ---------------
host='192.168.1.6'
port=5002

# --------------- Bind the socket ---------------
try:
     # --------------- the bind may throw an error if unsuccessful ---------------
    s.bind((host, port))
except socket.error , msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()

# --------------- Listen for connections made to the socket ---------------
s.listen(1) #1 is 'backlog' which specifies the max number of queued connections

# --------------- Run the server continuously ---------------
while True:
    socket.socket()
    conn, addr = s.accept()
    message = conn.recv (1024)
    print "Peer : ", message
    text = raw_input('You : ')
    conn.send(text)
    conn.close()

