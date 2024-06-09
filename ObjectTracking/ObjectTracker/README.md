# ObjectTracker

## Objective

## Building ObjectTracker

### Prerequisites

- CMake 3.8 or higher
- OpenCV (installation instructions below)

### Installing OpenCV

#### Windows

1. Download and install the prebuilt OpenCV library from [OpenCV's official website](https://opencv.org/releases/).
2. Set the `OpenCV_DIR` environment variable to the directory containing the OpenCVConfig.cmake file, usually something like `C:\path\to\opencv\build`.

#### macOS

1. Install OpenCV using Homebrew:
    ```sh
    brew install ffmpeg@6
    brew install opencv
    ```

#### Linux

1. Install OpenCV using your package manager, for example, on Ubuntu:
    ```sh
    sudo apt-get install libopencv-dev
    ```

### Building the Project

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/ObjectTracker.git
    cd ObjectTracker
    ```

2. Create a build directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

3. Run CMake to configure the project:
    ```sh
    cmake ..
    ```

4. Build the project:
    ```sh
    cmake --build .
    ```

5. Run the executable:
    ```sh
    ./ObjectTracker
    ```

## Included Files
