# VideoTracker/CMakeLists.txt

# Source files
set(TRACKER_SOURCE_FILES
    src/VideoTracker.cpp
)

# Header files
set(TRACKER_HEADER_FILES
    headers/VideoTracker.h
)

# Add library or executable
add_library(VideoTracker ${TRACKER_SOURCE_FILES} ${TRACKER_HEADER_FILES})

# Set C++ standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET VideoTracker PROPERTY CXX_STANDARD 20)
endif()

# Link any required libraries
target_link_libraries(VideoTracker ${OpenCV_LIBS}) # this will probably later need cv
