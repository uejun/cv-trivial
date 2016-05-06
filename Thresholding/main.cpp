#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
const string window_name = "Threshold demmo";

const string trackbar_type = "Type: 0:Binary 1:Binary Inverted 2:Truncatte 3:ToZero 4:ToZeroInverted";
const string trackbar_value = "Value";


void Threshold_Demo(int, void*);

int main(int argc, char* argv[]) {

    src = imread(argv[1], IMREAD_COLOR);

    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    namedWindow(window_name, WINDOW_AUTOSIZE);

    createTrackbar(trackbar_type,
                    window_name, &threshold_type, max_type, Threshold_Demo);

    createTrackbar(trackbar_value,
                    window_name, &threshold_value, max_value, Threshold_Demo);

    Threshold_Demo(0,0);

    for(;;) {
        int c;
        c = waitKey(20);
        if ((char)c == 27) {
            break;
        }
    }

    return 0;
}

void Threshold_Demo(int, void*) {
    /* 0: Binary
    1: Binary Inverted
    2: Threshold Truncated
    3: Threshold to Zero
    4: Threshold to Zero Inverted
  */

    threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);

    imshow(window_name, dst);
}