#-------------------------------------------------------------------------------
# Name:        Simple Coolers using Python Turtle
#
# Author:      Krishnaswamy Kannan
#
#-------------------------------------------------------------------------------
import turtle
def main():
    window = turtle.Screen() # create a window to draw
    coolers = turtle.Turtle() # create a new turtle

    coolers.left(180)
    coolers.forward(100)
    coolers.right(90)
    # Fill the circle with green color and black line
    coolers.color("black","green")
    coolers.begin_fill() #begin color fill
    coolers.circle(50)
    coolers.end_fill() #end color fill
    coolers.right(90)
    coolers.forward(100)
    coolers.right(90)
     # Fill the other circle with green color and black line
    coolers.color("black","green")
    coolers.begin_fill() #begin fill
    coolers.circle(50)
    coolers.end_fill() #end fill
    coolers.circle(50,180)
    coolers.forward(100)
    coolers.right(180)
    coolers.forward(100)
    coolers.circle(-50,180)
    coolers.left(90)
    coolers.forward(100)
    coolers.right(90)
    coolers.circle(50,180)
    coolers.right(180)
    coolers.forward(100)

    window.exitonclick()

if __name__ == '__main__':
    main()
