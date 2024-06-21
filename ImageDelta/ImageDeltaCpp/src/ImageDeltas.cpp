#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "../headers/ImageDeltas.h"

using namespace cv;
using namespace std;

void createTestImages() {
    // Create a white background
    Mat img1 = Mat::zeros(100, 100, CV_8UC3);
    img1.setTo(Scalar(255, 255, 255));

    Mat img2 = img1.clone();

    // draw point at 50, 50
    rectangle(img1, Point(50, 50), Point(60, 60), Scalar(0, 0, 0), -1);

    // draw point at 55, 50
    rectangle(img2, Point(75, 50), Point(85, 60), Scalar(0, 0, 0), -1);

    // write them to vars
    imwrite("image1.jpg", img1);
    imwrite("image2.jpg", img2);
}

int main() {
    createTestImages();

    // Load images
    Mat img1 = imread("image1.jpg");
    Mat img2 = imread("image2.jpg");

    // Check if images are loaded
    if (img1.empty() || img2.empty()) {
        cout << "Could not open or find the images!" << endl;
        return -1;
    }

    // Convert to grayscale
    Mat gray1, gray2;
    cvtColor(img1, gray1, COLOR_BGR2GRAY);
    cvtColor(img2, gray2, COLOR_BGR2GRAY);

    // Compute absolute difference
    Mat diff;
    absdiff(gray1, gray2, diff);

    // Threshold the difference image
    Mat thresh;
    threshold(diff, thresh, 30, 255, THRESH_BINARY);

    // Find contours
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Draw contours and extract data
    Mat result = img1.clone();
    for (size_t i = 0; i < contours.size(); i++) {
        // Draw contours on the result image
        drawContours(result, contours, (int)i, Scalar(0, 0, 255), 2, LINE_8, hierarchy, 0);

        // Calculate the bounding box of each contour
        Rect boundingBox = boundingRect(contours[i]);

        // Draw the bounding box on the result image
        rectangle(result, boundingBox.tl(), boundingBox.br(), Scalar(0, 255, 0), 2);

        // Print the size and location of the bounding box
        cout << "Contour #" << i + 1 << ": " << endl;
        cout << "  Location: " << boundingBox.tl() << " - " << boundingBox.br() << endl;
        cout << "  Size: " << boundingBox.width << " x " << boundingBox.height << endl;
    }

    // Show the result
    imshow("Differences", result);
    waitKey(0);

    return 0;
}