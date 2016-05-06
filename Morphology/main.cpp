#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

Mat src, dst;

int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;

string window_name = "Mofphology Transformation Demo";

void morphologyOperations(int, void*);

int main(int argc, char* argv[]) {

   src = imread(argv[1]);

    if(!src.data) {
        return -1;
    }

    namedWindow(window_name, WINDOW_AUTOSIZE);

    createTrackbar("Operator:\n 0: Opening - 1: Closing \n 2: Grdient - 3: Top Hat \n 4: Black Hat", window_name,
    &morph_operator, max_operator, morphologyOperations);

    createTrackbar("Element:\n 0: Rect - 1: Cross -2: Ellipse", window_name,
    &morph_elem, max_elem, morphologyOperations);

    createTrackbar("Kernel size:\n 2n + 1", window_name,
    &morph_size, max_kernel_size, morphologyOperations);

    morphologyOperations(0, 0);

    waitKey(0);

    return 0;
}

void morphologyOperations(int, void*) {
    // Since MORPH_X : 2, 3, 4, 5 and 6
    int operation = morph_operator + 2;

    Mat element = getStructuringElement(morph_elem, Size(2*morph_size + 1, 2*morph_size + 1), Point(morph_size, morph_size));

    morphologyEx(src, dst, operation, element);

    imshow(window_name, dst);
}