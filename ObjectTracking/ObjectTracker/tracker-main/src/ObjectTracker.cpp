
#include <iostream>
#include <filesystem>
#include <json/value.h>
#include <fstream>
#include "VideoTracker.h"

namespace vt = VideoTracker;

int main()
{
    std::unique_ptr<vt::Tracker> tracker = std::make_unique<vt::DefaultTracker>();
    tracker->start(); // used with default -- debugging
}
