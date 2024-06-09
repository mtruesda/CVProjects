// VideoTracker.h
#include <opencv2/opencv.hpp>

#ifndef VIDEOTRACKER_H
#define VIDEOTRACKER_H

class VideoTracker {
public:
	VideoTracker();
	void processFrame(cv::Mat& frame);
};

// Tracks based on color
class ColorTracker : public VideoTracker {

};


// Tracks the area contained within a region
class BoxTracker : public VideoTracker {
public:
	
protected:
	struct Impl;
	Impl* m_impl;
};

// Tracks Edges
class EdgeTracker : public VideoTracker {
	
};

// default class to ensure that opencv library is working and obtaining video
class DefaultTracker {
public:
    DefaultTracker();
    void start();
};

#endif