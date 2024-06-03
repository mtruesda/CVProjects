import cv2
from typing import Tuple

class Rectangle:
    def __init__(self, x : float, y : float, width : float, height : float):
        """
            Initialize Rect struct type object

            Params:
                x (float): x coordinate (tl)
                y (float): y coordinate (tl)
                width (float): width of the rect
                height (float): height of the rect

        """
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.center = (
            x + (width) / 2, 
            y + (height / 2)
        )

    def getRoi(self, frame : cv2.Mat) -> cv2.Mat:
        """
        Extract the ROI from the given frame.
        """
        return frame[
            int(self.y):int(self.y + self.height), 
            int(self.x):int(self.x + self.width)
        ]
    
    def getCenter(self) -> Tuple[int, int]:
        """
            Center returner
        """
        return self.center
    
    def tl(self) -> Tuple[int, int]:
        """
        Returns top-left coordinate of the rect struct
        """
        return (int(self.x), int(self.y))

    def br(self) -> Tuple[int, int]:
        """
        Returns bottom-right coordinate of the rect struct
        """
        return (int(self.x + self.width), int(self.y + self.height))

    def draw(self, frame : cv2.Mat) -> None:
        """
            Draws the rect struct on the frame (green)

            Params:
                frame (Mat): frame to draw
            
            Returns:
                (Mat): frame with the rect drawn on
        """
        cv2.rectangle(frame, self.tl(), self.br(), (0, 255, 0), 5)
        return frame
    
    def setTlWithCenter(self, newCenter) -> None:
        """
        Readjusts the x and y coordinates based on the new center.
        
        Params:
            newCenter (tuple<int, int>): New center (x, y) for the rectangle.
        """
        # Update the center
        self.center = newCenter
        
        # Calculate the new top-left corner based on the new center
        # Subtract half the width and half the height from the new center coordinates
        self.x = newCenter[0] - self.width // 2
        self.y = newCenter[1] - self.height // 2