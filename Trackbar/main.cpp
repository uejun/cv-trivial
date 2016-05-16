#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

const int alpha_slider_max = 100;
int alpha_slider;
double alpha;
double beta;

Mat src1;
Mat src2;
Mat dst;

void on_trackbar(int, void*) {
    alpha = (double) alpha_slider / alpha_slider_max;
    beta = (1.0 - alpha);

    addWeighted(src1, alpha, src2, beta, 0.0, dst);
    imshow("Linear Blend", dst);
}

int main(int argc, char** argv) {
    src1 = imread(argv[1], IMREAD_COLOR);
    src2 = imread(argv[2], IMREAD_COLOR);
    resize(src2, src2, src1.size());

    if (src1.empty()) {
        cerr << "src1 is empty." << endl;
        return -1;
    }
    if (src2.empty()) {
        cerr << "src2 is empty." << endl;
        return -1;
    }

    alpha_slider = 0;

    namedWindow("Linear Blend", 1);

    string trackbarName = "Track";
    //sprintf(trackbarName, "Alpha x %d", alpha_slider_max);

    createTrackbar(trackbarName, "Linear Blend", &alpha_slider, alpha_slider_max, on_trackbar);

    on_trackbar(alpha_slider, 0);

    waitKey(0);
    return 0;
}