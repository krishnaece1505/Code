#-------------------------------------------------------------------------------
# Name:        List Basic operations
#
# Author:      Krishnaswamy Kannan
#
#-------------------------------------------------------------------------------

def main():

    courses = ["HDL","SystemC"]
    courses.append("Research Methodology")
    print ("\n Courses : ",courses)
    courses.pop(2) # to remove based on index
    print ("\n Courses : ",courses)
    courses.insert(0,"Research Methodology")
    courses.remove("Research Methodology") # to remove based on element
    print ("\n Courses : ",courses)

    list = [1,2,3,4,5,6,7,8,9,10]
    for i in list:
        if (i%2 == 0):
            print ("\nEVEN NUMBERS IN LIST : ",i) # list[start:end:step]
        else:
            print ("\nODD NUMBERS IN LIST : ",i)


if __name__ == '__main__':
    main()
