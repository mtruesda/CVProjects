# ImageDeltas

## Objective

## Included Functions

### createTestImages()

args: None
returns: None

Generates two test photos that can be used for comparison. The photos will include a dot that is placed differently in each image

### findContoursInImage(const Mat& threshold)

Arguments:
    const Mat& threshold: The threshold to extract contours from
Returns: 
    vector<vector<Point>> contours: A vector of contours from the threshold produced from the two images

Creates a list of contours from the difference and thresholding of the two images

### calculateDistances()

Still in development

### findAndFilterContours(const Mat& threshold, double minArea, double maxArea = DBL_MAX)

Arguments:
    const Mat& threshold: Threshold image
    double minArea: The minimum area of contours to be included
    double maxArea: The maximum area of contours to be included (defaulted to inf)
Returns:
    vector<vector<Point>> contours: new list of filtered contours

Filters the contour list to meet area constraints

### showContourFocus(Mat img1, Mat img2, Mat result, vector<vector<Point>>& contours, int contourIndex)

Arguments:
Returns:
    None

## Included Images