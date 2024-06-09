// VideoTracker.h
#include <opencv2/opencv.hpp>

#ifndef VIDEOTRACKER_H
#define VIDEOTRACKER_H

class VideoTracker {
public:
	// Constructor
	VideoTracker();

	void processFrame(cv::Mat& frame);
};

// Tracks based on color
class ColorTracker : public VideoTracker {

};


// Tracks the area contained within a region
class BoxTracker : public VideoTracker {
protected:
	struct Impl;
	Impl* m_impl;
};

// Tracks Edges
class EdgeTracker : public VideoTracker {

};

#endif