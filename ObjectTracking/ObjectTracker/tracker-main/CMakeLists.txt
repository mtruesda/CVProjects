﻿# Tracker-Main/CMakeLists.txt

# Source files
set(SOURCE_FILES
    src/ObjectTracker.cpp
)

# Add source to this project's executable.
add_executable(Tracker-Main ${SOURCE_FILES})

# Set C++ standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Tracker-Main PROPERTY CXX_STANDARD 20)
endif()

# Include Tracker library headers
target_include_directories(Tracker-Main PRIVATE ${CMAKE_SOURCE_DIR}/videotracker/headers)

# Link libraries
target_link_libraries(Tracker-Main PRIVATE VideoTracker) # opencv inherited from tracker
