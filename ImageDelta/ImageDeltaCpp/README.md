# ImageDeltas

## Objective

## Included Functions

### createTestImages()

args: None
returns: None

Generates two test photos that can be used for comparison. The photos will include a dot that is placed differently in each image

### calculateDistances()

Still in development

### vector<vector<Point>> findContours(const Mat& threshold, double minArea = 0, double maxArea = DBL_MAX)

Arguments:
    - const Mat& threshold: Threshold image
    - double minArea: The minimum area of contours to be included
    - double maxArea: The maximum area of contours to be included (defaulted to inf)
Returns:
    - vector<vector<Point>> contours: new list of filtered contours

Filters the contour list to meet area constraints

### void showContourFocus(Mat img1, Mat img2, Mat result, vector<Point> contour)

Arguments:
    - Mat img1: image 1
    - Mat img2: image 2
    - Mat result: original result
    - vector<Point> contour: contour to be displayed
Returns: None

### int contourDistance(Mat img, vector<Point> contour)

Arguments:
    - Mat img: the image containing the contour
    - vector<Point> contour: the contour in question
Returns:
    - distance in pixels from the camera


## Included Images

## References

- https://stackoverflow.com/questions/27035672/cv-extract-differences-between-two-images