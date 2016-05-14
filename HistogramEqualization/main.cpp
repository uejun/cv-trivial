#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    Mat src, dst;
    const char* source_window = "Source image";
    const char* equalized_window = "Equalized image";

    src = imread(argv[1], 1);

    if(src.empty()) {
        cout << "Usage: ./HistogramEqualization <path_to_image>" << endl;
    }

    cvtColor(src, src, COLOR_BGR2GRAY);

    equalizeHist(src, dst);

    namedWindow(source_window, WINDOW_AUTOSIZE);
    namedWindow(equalized_window, WINDOW_AUTOSIZE);

    imshow(source_window, src);
    imshow(equalized_window, dst);

    waitKey(0);

    return 0;
}