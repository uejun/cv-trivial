#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {

    Mat src, src_gray,  dst;
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    const char* window_name = "Laplace Demo";

    src = imread(argv[1]);
    if(src.empty()) {
        return -1;
    }

    GaussianBlur(src, src, Size(3,3), 0, 0, BORDER_DEFAULT);

    cvtColor(src, src_gray, COLOR_RGB2GRAY);

    namedWindow(window_name, WINDOW_AUTOSIZE);

    Mat abs_dst;

    Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(dst, abs_dst);

    imshow(window_name, abs_dst);

    waitKey(0);
    return 0;
}