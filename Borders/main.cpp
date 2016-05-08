#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

Mat src, dst;
int top, bottom;
int borderType;
const char* window_name = "copyMakeBorder Demo";
RNG rng(12345);

int main(int argc, char* argv[]) {
    int c;

    src = imread(argv[1]);
    if (src.empty()) {
        cout << "No data entered" << endl;
    }

    namedWindow(window_name, WINDOW_AUTOSIZE);

    top = (int) (0.05*src.rows);
    bottom = (int) (0.05*src.rows);

    int left = static_cast<int>(0.05 * src.cols);
    int right = int(0.05*src.cols);

    dst = src;

    imshow(window_name, dst);

    for(;;) {
        c = waitKey(500);

        if((char) c == 27) {
            break;
        }else if((char) c == 'c') {
            borderType = BORDER_CONSTANT;
        }else if((char) c == 'r') {
            borderType = BORDER_REPLICATE;
        }

        Scalar value(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        copyMakeBorder(src, dst, top, bottom, left, right, borderType, value);

        imshow(window_name, dst);
    }
    cout << "Hello, World!" << endl;
    return 0;
}