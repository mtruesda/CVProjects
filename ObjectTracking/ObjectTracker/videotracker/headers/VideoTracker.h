// VideoTracker.h
#include <opencv2/opencv.hpp>

#ifndef VIDEOTRACKER_H
#define VIDEOTRACKER_H

namespace VideoTracker {

	class Tracker {
	public:
		virtual ~Tracker() {}

		virtual void processImage(cv::Mat& img) = 0;
		virtual void start() = 0;
	};

	// Tracks based on color
	class ColorTracker : public Tracker {
	public:
		ColorTracker();
		~ColorTracker();

		void processImage(cv::Mat& img) override;
		void start() override;
	protected:
		struct Impl;
		std::unique_ptr<Impl> m_impl;
	};


	// Tracks the area contained within a region
	class BoxTracker {

	};

	// default class to ensure that opencv library is working and obtaining video
	class DefaultTracker : public Tracker {
	public:
		DefaultTracker() = default;
		~DefaultTracker() = default;

		void processImage(cv::Mat& img) override;

		void start() override;
	};

}

#endif