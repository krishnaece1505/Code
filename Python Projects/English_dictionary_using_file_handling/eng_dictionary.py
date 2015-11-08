#-------------------------------------------------------------------------------
# Name:        Simple English Dictionary v1.0
#
# Author:      Krishnaswamy Kannan
#-------------------------------------------------------------------------------
import os
def main():
    entered_text = ""
    os.system("cls")
    print "----------------------------------------------------------------------"
    print "\t\t\tENGLISH DICTIONARY v1.0 "
    print "----------------------------------------------------------------------"
    fp = open("C:/Kannan/Python/Testing/Dictionary.txt","a")
    word = raw_input("\n Enter the word : ")
    fp.write("\n\t* ")
    fp.write(word.upper())
    meaning = raw_input("\n Enter the meaning : ")
    fp.write("\t : \t")
    fp.write(meaning)
    fp = open("C:/Kannan/Python/Testing/dictionary.txt","r")
    text = fp.readlines()
    fp.close()
    for i in text[-1]:
        if  i != "*" :
            entered_text += i

    print "\n The text you entered is ->",entered_text
    print "\n Enter \"Dictionary.txt\" to view the file"
if __name__ == '__main__':
    main()
