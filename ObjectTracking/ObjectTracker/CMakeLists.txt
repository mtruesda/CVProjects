# CMakeList.txt : CMake project for ObjectTracker, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# project name
project ("ObjectTracker")

# Find OpenCV package
find_package(OpenCV REQUIRED)

# source files
set(SOURCE
	src/ObjectTracker.cpp
	src/VideoTracker.cpp
)

# header files
set(HEADER
	headers/VideoTracker.h
) 

# Add source to this project's executable.
add_executable(ObjectTracker ${SOURCE} ${HEADER})

# set C++ standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ObjectTracker PROPERTY CXX_STANDARD 20)
endif()

# set build type because can
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Include OpenCV directories
include_directories(${OpenCV_INCLUDE_DIRS})

# Link OpenCV libraries
target_link_libraries(ObjectTracker ${OpenCV_LIBS})

# set startup project as my project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ObjectTracker)