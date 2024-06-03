import cv2
import numpy as np
from Rect import Rectangle

class Feature():
    def __init__(self, point, confidence=0):
        self.point = point
        self.confidence = confidence

    def setConfidence(self, confidence):
        self.confidence = confidence

class Tracker():
    def __init__(self, gate=None):
        self.max_features = 7
        self.referenceFrame = None
        self.features = []
        self.gate = gate
        self.trackerState = False
        self.prevFrame = None
        self.prevFeatures = None

    def setGate(self, gate : Rectangle) -> None:
        self.gate = gate
        self.trackerState = True
    
    def stop(self):
        self.trackerState = False
        self.gate = None

    def processFrame(self, frame : cv2.Mat) -> None:
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        if self.prevFrame is None or self.prevFeatures is None:
            # Find initial features in the entire frame
            self.prevFeatures = cv2.goodFeaturesToTrack(gray, self.max_features, 0.01, 10)
            self.prevFrame = gray
            return

        # Find new features in the current frame
        currentFeatures = cv2.goodFeaturesToTrack(gray, self.max_features, 0.01, 10)

        # Attempt to match new features with previous ones
        # This will be a simple and naive matching based on minimum distance, without considering optical flow
        if currentFeatures is not None:
            displacements = []
            for prevFeature in self.prevFeatures.reshape(-1, 2):
                # Calculate distances to all current features
                distances = np.linalg.norm(currentFeatures.reshape(-1, 2) - prevFeature, axis=1)
                # Find the closest feature in the current frame to this previous feature
                minIndex = np.argmin(distances)
                displacement = currentFeatures[minIndex].ravel() - prevFeature
                displacements.append(displacement)

            # Calculate average displacement if we have any valid matches
            if displacements:
                averageDisplacement = np.mean(displacements, axis=0)
                # Move the gate based on average displacement
                self.gate.x += averageDisplacement[0]
                self.gate.y += averageDisplacement[1]
            
            # Replace previous features with current ones
            self.prevFeatures = currentFeatures

        self.prevFrame = gray