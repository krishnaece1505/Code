#-------------------------------------------------------------------------------
# Name:        Simple English Dictionary v1.0
#
# Author:      Krishnaswamy Kannan
#-------------------------------------------------------------------------------
import os #to use clear screen and popen to open dictionary from cmd

def engdict(word,meaning):
    fp = open("C:/Kannan/Python/Testing/Dictionary.txt","a") #give the file path and name for the dictionary
    fp.write("\n\t* ")
    fp.write(word.upper())
    fp.write("\t : \t")
    fp.write(meaning)
    fp.close()

def main():
    command = "N"
    os.system("cls")
    print "----------------------------------------------------------------------"
    print "\t\t\tENGLISH DICTIONARY "
    print "----------------------------------------------------------------------"

    while command.upper() == 'N' or not command.isalpha(): # to avoid exit of program when ENTER is pressed
        word = raw_input("\n Enter the word : ")
        meaning = raw_input("\n Enter the meaning : ")
        command = " "
        while not command.isalpha():
            print "\n The text you entered ->",word," : ",meaning
            command = raw_input("\n Is the data correct? \n\n Enter \"Y\" to SAVE or \"N\" to EDIT : ")
        if command.upper() == 'Y':
            engdict(word,meaning)
        else:
            os.system("cls")

    dict_open = raw_input("\n Do you want to view the Dictionary? \n\n Enter \"Y\" to OPEN or \"ENTER\" to EXIT : ")
    if dict_open.upper() == "Y":
        os.popen("Dictionary.txt")

if __name__ == '__main__':
    main()
