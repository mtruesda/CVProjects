#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "../headers/ImageDeltas.h"

using namespace cv;
using namespace std;

///////////////////////////////

// functions to write:

// 1) Obtain contours

// 2) Obtain distances

// 3) View specific Contours

///////////////////////////////

// generates two jpeg images that contain a dot each that is just slightly moved
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
    imwrite("images/generated/image1.jpg", img1);
    imwrite("images/generated/image2.jpg", img2);
}

// this may need to be improved
void showContourFocus(Mat img1, Mat img2, Mat result, vector<vector<Point>>& contours, int contourIndex) {
    if (contourIndex < 0 || contourIndex >= contours.size()) {
        cout << "Invalid contour index!" << endl;
        return;
    }

    // Draw only the specified contour
    Mat focus1 = img1.clone();
    Mat focus2 = img2.clone();
    Mat focusResult = Mat::zeros(result.size(), result.type());

    // Draw the contour on the original images with bounding boxes
    drawContours(focus1, contours, contourIndex, Scalar(0, 0, 255), 2, LINE_8);
    drawContours(focus2, contours, contourIndex, Scalar(0, 0, 255), 2, LINE_8);
    
    Rect boundingBox = boundingRect(contours[contourIndex]);
    rectangle(focus1, boundingBox.tl(), boundingBox.br(), Scalar(0, 255, 0), 2);
    rectangle(focus2, boundingBox.tl(), boundingBox.br(), Scalar(0, 255, 0), 2);

    // Copy the contour area to the result image
    result(boundingBox).copyTo(focusResult(boundingBox));

    // Crop the result image to the bounding box
    Mat croppedResult = focusResult(boundingBox);

    // Show the images with the focused contour
    imshow("Focused Image 1", focus1);
    imshow("Focused Image 2", focus2);
    imshow("Focused Differences", croppedResult);
    waitKey(0);
}

int main() {

    Mat img1 = imread("Images/Table/image1.png");
    Mat img2 = imread("Images/Table/image2.png");

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
    imshow("Image1", img1);
    imshow("Image2", img2);

    showContourFocus(img1, img2, result, contours, 50);
    showContourFocus(img1, img2, result, contours, 55);
    showContourFocus(img1, img2, result, contours, 60);

    waitKey(0);

    return 0;
}