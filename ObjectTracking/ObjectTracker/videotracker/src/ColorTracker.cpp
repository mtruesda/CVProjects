#include "../headers/ColorTracker.h"

namespace VideoTracker {
    
    ColorTracker::ColorTracker() {
        m_impl = std::make_unique<ColorTracker::Impl>();

    }

     // Definition of ColorTracker destructor
    ColorTracker::~ColorTracker() = default;

    void ColorTracker::processImage(cv::Mat& img) {
        return;
    }

    void ColorTracker::start() {
        return;
    }

}