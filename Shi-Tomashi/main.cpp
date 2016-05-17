#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat src, src_gray;

int maxCorners = 23;
int maxTrackbar = 100;

RNG rng(12345);
char* source_window = "Image";

void goodFeatureToTrack_Demo(int, void*);


int main(int argc, char** argv) {

    src = imread(argv[1], IMREAD_COLOR);
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    namedWindow(source_window, WINDOW_AUTOSIZE);
    createTrackbar("Max corners", source_window, &maxCorners, maxTrackbar, goodFeatureToTrack_Demo);

    imshow(source_window, src);

    goodFeatureToTrack_Demo(0,0);

    waitKey(0);
    return 0;
}

void goodFeatureToTrack_Demo(int, void*) {
    if(maxCorners < 1) {
        maxCorners = 1;
    }

    vector<Point2f> corners;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;

    Mat copy;
    copy = src.clone();

    goodFeaturesToTrack(src_gray,
        corners,
        maxCorners,
        qualityLevel,
        minDistance,
        Mat(),
        blockSize,
        useHarrisDetector,
        k);

    cout << "** Numeber of corners detected:" << corners.size() << endl;
    int r = 4;
    for(size_t i = 0; i < corners.size(); i++) {
        circle(copy, corners[i], r, Scalar(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0, 255)), -1, 8, 0);
    }

    namedWindow(source_window, WINDOW_AUTOSIZE);
    imshow(source_window, copy);
}