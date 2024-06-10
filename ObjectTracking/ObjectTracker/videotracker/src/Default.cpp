#include "../headers/VideoTracker.h"

namespace VideoTracker {

    void DefaultTracker::start() {

        // Windows pathing
        //std::string videoPath = "C:\\Users\\Maize\\source\\repos\\CVProjects\\ObjectTracking\\videos\\RaceCar2.mp4";
        // Mac Pathing
        std::string videoPath = "/Users/MyronT/Documents/GitHub/CVProjects/ObjectTracking/videos/RaceCar2.mp4";
        cv::VideoCapture cap(videoPath);

        if (!cap.isOpened()) {
            std::cerr << "Error: Unable to open video file" << std::endl;
            return;
        }

        cv::Mat frame;

        // Read until video is completed
        while (cap.isOpened()) {
            // Capture frame-by-frame
            cap >> frame;

            // If frame is empty, the video has ended
            if (frame.empty())
                break;

            // Display the frame
            cv::imshow("Frame", frame);

            // Press 'q' to exit
            if (cv::waitKey(25) == 'q')
                break;
        }

        // Release the video capture object
        cap.release();

        // Close all OpenCV windows
        cv::destroyAllWindows();
        return;
    }

    void DefaultTracker::processImage(cv::Mat& img) {
        return;
    }
}