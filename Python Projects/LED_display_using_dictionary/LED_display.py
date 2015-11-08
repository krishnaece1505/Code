#--------------------------------------------------------------------------
# Module : Animated LED Banner Program v1.0 (ALPHABETS)
#
# Author : Krishnaswamy Kannan
#--------------------------------------------------------------------------
#allows us to clear the console screen.
import sys #for import from another python file
import os #for clear screen
import time #to adjust speed of the banner

#import the python file containing the character dictionary for the alphabets
#replace the file path to the path where led_array.py is present
sys.path.append(os.path.abspath("C:\Users\Krishnaswamy Kannan"))
from LED_array import *

# The windows console is 79 characters wide
WIDTH = 79
os.system("cls")
print("\n-----------------------------------------------------------")
print("\n              LED DISPLAY v1.0 (ALPHABETS)                 ")
print("\n-----------------------------------------------------------")
print("\n NOTE : Press \"CTRL+C\" to close the program............\n")

#Get input form the user
while True:
        text = raw_input(" Enter the text to display : ")
        if text.isdigit() == True or any(c in text for c in '!@#$%^&*()_+') == True:
            print("\n Only alphabets are supported in v1.0.... Please Try again!\n")
        else:
            break

#the message we wish to print
message = text.upper()

#create an empty list for the message, intially
printedMessage = [ "","","","","","","" ]

#build up the printed banner. to do this, the 1st row of the
#display is created for each character in the message, followed by
#the second rowand so on......
for row in range(7):
    for char in message:
        printedMessage[row] += (str(characters[char][row]) + "  ")

#the offset is how far to the right we want to print the message.
#initially, we want to print the message just off the display.
offset = WIDTH

while True:
    os.system("cls")

    #print each line of the message, including the offset.
    for row in range(7):
        print(" " * offset + printedMessage[row][max(0,offset*-1):WIDTH - offset])

    #move the message a little to the left.
    offset -=1

    #if the entire message has moved 'through' the display then
    #start again from the right hand side.
    if offset <= ((len(message)+2)*6) * -1:
        offset = WIDTH

    #Adjust the value to speed up / slow down the display banner/marquee
    time.sleep(0.015)

#-------------------------------------------------------------------------------------
# Reference : usingpython.com/programs
#
# This program is an extension to the program found on the above website
#-------------------------------------------------------------------------------------