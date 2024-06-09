# Driver/CMakeLists.txt

# Source files
set(SOURCE_FILES
    src/ObjectTracker.cpp
)

# Add source to this project's executable.
add_executable(Driver ${SOURCE_FILES})

# Set C++ standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Driver PROPERTY CXX_STANDARD 20)
endif()

# Include Tracker library headers
include_directories(${CMAKE_SOURCE_DIR}/Tracker/headers)

# Link libraries
target_link_libraries(Driver Tracker) # opencv inherited from tracker
