#-------------------------------------------------------------------------------
# Name:        Calendar
#
# Author:      Krishnaswamy Kannan
#
#-------------------------------------------------------------------------------

import calendar

# Get the month and year
yy = int(input("Enter year: "))
mm = int(input("Enter month: "))

# Display the calendar
print(calendar.month(yy,mm))
