# Suraj Ilavala
# CMSC 403: Assignment 7
# Due Date: April 16th, 202-
# Assignment7.py
# 
# Make sure rectangle packer is installed with the command
# $ pip3 install rectangle-packer
# #

# utilities imported
import sys
import tkinter
from tkinter import Tk, Canvas
#rectangle packer must be installed to import this package
import rpack

#canvas class
class CustomCanvas(object):
    # stores variables for the class
    def __init__(self, height, width):
        # makes list of rects to store width and length
        self.rects: List[Rectangle] = []
        #stores canvas lengths and widths and packs it
        self.master = Tk()
        self.canvas = Canvas(self.master, width=width, height=height)
        self.canvas.pack()
    #draws all rectangles stored before hand the color of the rectangle is blue with black outline
    def draw(self, allRec):
        for rect in allRec:
            self.rects.append(self.canvas.create_rectangle(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height, outline="black",fill="blue"))

        self.master.mainloop()
#rectangle class
class Rectangle(object):
    #stores height width x and y 
    #makes sure all the variables are a int and stores it
    def __init__(self, height, width, x, y):
        self.height: int = int(height)
        self.width: int = int(width)
        self.x: int = int(x)
        self.y: int = int(y)
#packs the allrect 
def pack(allRect, canvasSize):
    #stores width and height from allRect which was given 
    rects = [(rect.width, rect.height) for rect in allRect]
    location = rpack.pack(rects)
    #zip of tuple iterators to place in appropriate locations when drawn
    for locat, rect in zip(location, allRect):
        rect.x = locat[0]
        rect.y = locat[1]
#main function that reads in rectangle variables, stores it and runs it
def main():
    #checks to make sure there is a file name given before continuing 
    if len(sys.argv) > 1:
        filepath = sys.argv[1]
    else:
        exit(1)
    #storage variables for all information given
    height = 0
    width = 0
    #opens file reads line to line and stores it
    with open(filepath) as f:
        canvas_size = tuple(f.readline().strip().split(","))
        allRects = [Rectangle(*line.strip().split(","), 0, 0) for line in f]
    #calls pack and packs all rectangles
    pack(allRects, canvas_size)
    #draws the rectangles
    CustomCanvas(*canvas_size).draw(allRects)

#runs main()
if __name__ == "__main__":
    main()
