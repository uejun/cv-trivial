#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    Mat src_base, hsv_base;
    Mat src_test1, hsv_test1;
    Mat src_test2, hsv_test2;
    Mat hsv_half_down;

    if(argc < 4) {
        cout << "** Error. Usage: ./HistogramComparison <image_settings0> <image_setting1> <image_settings2>" << endl;
        return -1;
    }

    src_base = imread(argv[1], 1);
    src_test1 = imread(argv[2], 1);
    src_test2 = imread(argv[3], 1);

    cvtColor(src_base, hsv_base, COLOR_BGR2HSV);
    cvtColor(src_test1, hsv_test1, COLOR_BGR2HSV);
    cvtColor(src_test2, hsv_test2, COLOR_BGR2HSV);

    hsv_half_down = hsv_base(Range(hsv_base.rows/2, hsv_base.rows -1), Range(0, hsv_base.cols - 1));

    int h_bins = 50;
    int s_bins = 60;
    int histSize[] = {h_bins, s_bins};

    float h_ranges[] = {0, 180};
    float s_ranges[] = {0, 256};

    const float* ranges[] = {h_ranges, s_ranges};

    int channels[] = { 0, 1};

    MatND hist_base;
    MatND hist_half_down;
    MatND hist_test1;
    MatND hist_test2;

    calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
    normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());


    return 0;
}