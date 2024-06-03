import cv2
import sys
import numpy as np

from Tracker import Tracker
from Rect import Rectangle as rect

def main():
    objTracker = Tracker()  # create the tracker object
    videoPath = None    # initialize path
    gate = rect(0, 350, 400, 200)
    
    if len(sys.argv) > 1:   # if there's an argument set the path to that argument
        videoPath = sys.argv[1]
    elif len(sys.argv) == 6: # need all rect items to do this
        # map converts strs to ints, then list types it 
        # and then passes them all as individual params
        gate = rect(*list(map(int, sys.argv[2:])))
    else:
        videoPath = '../RaceCar2.mp4'
        # check in case of laziness with launch.json

        # Rect Sizes
        # 0 350 400 200 - ../RaceCar2.mp4
        # 
        #
        check = input('Do you want to manually enter path and rect? (y/n): ')
        if check == 'y':
            videoPath = input('Enter path to video file: ')
            gate = rect(list(map(int, input("Enter rect params (x y w l): ").split(' '))))

    cap = cv2.VideoCapture(videoPath) # begin capturing video data

    if not cap.isOpened():  # if the video capture doesn't work, exit
        print("Error: Could not open video.")
        exit()

    frame_number = 0        # count the frames
    while True:
        # Read the next frame
        ret, frame = cap.read()
        
        # If there are no more frames, break the loop
        if not ret:
            break

        frame_number += 1
        print(f"Showing frame {frame_number}")

        frame = gate.draw(frame)
        cv2.imshow('Original', frame)
        
        objTracker.setGate(gate)
        objTracker.processFrame(frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):  # Break the loop on 'q' key press
            break

if __name__ == '__main__':
    main()