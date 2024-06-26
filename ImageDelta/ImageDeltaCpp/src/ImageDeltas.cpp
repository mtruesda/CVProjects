#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <cfloat> // For DBL_MAX

#include "../headers/ImageDeltas.h"

using namespace cv;
using namespace std;

// generates two jpeg images that contain a dot each that is just slightly moved
void createTestImages() {
    // Create a white background
    Mat img1 = Mat::zeros(100, 100, CV_8UC3);
    img1.setTo(Scalar(255, 255, 255));

    Mat img2 = img1.clone();

    // draw point at 50, 50
    rectangle(img1, Point(50, 50), Point(60, 60), Scalar(0, 0, 0), -1);

    // draw point at 75, 50
    rectangle(img2, Point(75, 50), Point(85, 60), Scalar(0, 0, 0), -1);

    // write them to vars
    imwrite("images/generated/image1.jpg", img1);
    imwrite("images/generated/image2.jpg", img2);
}

// Function to calculate distances between contours
//TODO: May want to specify which contours we're measuring between
vector<double> calculateDistances(const vector<vector<Point>>& contours) {
    vector<double> distances;
    for (size_t i = 0; i < contours.size(); ++i) {
        Rect boundingBox = boundingRect(contours[i]);
        Point center = (boundingBox.tl() + boundingBox.br()) * 0.5;
        double distance = norm(center);
        distances.push_back(distance);
    }
    return distances;
}

// Function to find and filter contours based on area
vector<vector<Point>> findContours(const Mat& threshold, double minArea = 0, double maxArea = DBL_MAX) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(threshold, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> filteredContours;
    for (const auto& contour : contours) {
        double area = contourArea(contour);
        if (area >= minArea && area <= maxArea) {
            filteredContours.push_back(contour);
        }
    }
    return filteredContours;
}

// Function to show specific contours in focus
void showContourFocus(Mat img1, Mat img2, Mat result, vector<Point> contour) {
    if (img1.empty() || img2.empty() || result.empty()) {
        cout << "One of the input images is empty." << endl;
        return;
    }

    Mat focus1, focus2, croppedResult;
    Rect boundingBox = boundingRect(contour); // obtain contour information

    // clone images for changes
    focus1 = img1.clone();
    focus2 = img2.clone();
    croppedResult = result.clone();

    // obtain crop info
    int x_start = boundingBox.tl().x;
    int y_start = boundingBox.tl().y; // corrected to boundingBox.tl().y
    int width = boundingBox.width;
    int height = boundingBox.height;

    cout << "Debug info:\nx_start: " << x_start <<
        "\ny_start: " << y_start << "\nwidth: " << width << "\nheight: " << height << endl;

    // Check if the crop rectangle is within the image bounds
    if (x_start < 0 || y_start < 0 || x_start + width > img1.cols || y_start + height > img1.rows) {
        cout << "Crop rectangle is out of bounds." << endl;
        return;
    }

    Rect cropRect(x_start, y_start, width, height);

    // crop them
    focus1 = focus1(cropRect);
    focus2 = focus2(cropRect);
    croppedResult = croppedResult(cropRect);

    // Show the images with the focused contour
    imshow("Focused Image 1", focus1);
    imshow("Focused Image 2", focus2);
    imshow("Focused Differences", croppedResult);

    // display information about the contour
    cout << "Displaying Contour info" << endl;
    cout << "  Location: " << boundingBox.tl() << " - " << boundingBox.br() << endl;
    cout << "  Size: " << width << " x " << height << endl;
    waitKey(0); // wait until user is done
}

// This will return a distance from the contour to the camera
// TODO: Implement
int contourDistance(Mat img, vector<Point> contour) {
    return 0;
}

int main() {

    bool debug = true;

    // set test images
    // TODO: use json for this when testing
    // for now, hardcode works
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

    if (debug) {
        imshow("Threshold", thresh);
    }

    // Find contours
    vector<vector<Point>> contours = findContours(thresh, 15000); // specify min size
    
    // Draw contours and extract data
    Mat result = img1.clone();
    for (size_t i = 0; i < contours.size(); i++) {
        // Draw contours on the result image
        drawContours(result, contours, (int)i, Scalar(0, 0, 255), 2, LINE_8);

        // Calculate the bounding box of each contour
        Rect boundingBox = boundingRect(contours[i]);

        // Draw the bounding box on the result image
        rectangle(result, boundingBox.tl(), boundingBox.br(), Scalar(0, 255, 0), 2);

        // Print the size and location of the bounding box
        if (debug) {
            cout << "Contour #" << i + 1 << ": " << endl;
            cout << "  Location: " << boundingBox.tl() << " - " << boundingBox.br() << endl;
            cout << "  Size: " << boundingBox.width << " x " << boundingBox.height << endl;
        }
    }

    // Calculate example distances
    // vector<double> distances = calculateDistances(contours);
    // for (size_t i = 0; i < distances.size(); ++i) {
    //     cout << "Distance of contour #" << i + 1 << ": " << distances[i] << endl;
    // }

    // Show the results of comparison
    imshow("Differences", result);
    imshow("Image1", img1);
    imshow("Image2", img2);

    // Show specific contours
    showContourFocus(img1, img2, result, contours[0]);
    showContourFocus(img1, img2, result, contours[1]);

    waitKey(0); // wait until user prompts ending

    return 0;
}
