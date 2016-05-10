#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int _ratio = 3;
int kernel_size = 3;
const char* window_name = "Edge map";

static void CannyThreshold(int, void*) {
    blur(src_gray, detected_edges, Size(3,3));

    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*_ratio, kernel_size);

    dst = Scalar::all(0);

    src.copyTo(dst, detected_edges);
    imshow(window_name, dst);
}

int main(int, char** argv) {
    src = imread(argv[1]);
    if(src.empty()) {
        return -1;
    }

    dst.create(src.size(), src.type());

    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    namedWindow(window_name, WINDOW_AUTOSIZE);

    createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

    CannyThreshold(0, 0);

    waitKey(0);
    return 0;
}