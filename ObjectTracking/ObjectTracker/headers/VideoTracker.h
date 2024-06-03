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

#endif