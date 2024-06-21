cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  if (MSVC)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue,ProgramDatabase>")
  endif()
endif()

# Project name
project(ImageDeltas LANGUAGES CXX)

# Add OpenCV
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

# Include OpenCV directories
# target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})

# Source files
set(SOURCE_FILES
    src/ImageDeltas.cpp
)

set(INCLUDES
    headers/ImageDeltas.h    
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link OpenCV libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})