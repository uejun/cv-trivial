#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat src = imread("acker.jpg", IMREAD_COLOR);
    imshow("Mat12Test", src);
    waitKey(0);
    return 0;
}