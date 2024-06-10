#include "VideoTracker.h"

namespace VideoTracker {

    struct ColorTracker::Impl {
        cv::Rect m_gate;
        cv::Point2f center;
        std::vector<cv::Point2f> features;
    };
    
}