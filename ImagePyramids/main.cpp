#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat src, dst, tmp;

const string windowName = "Pyramids Demo";

int main() {

    cout << "Zoom In-Out demo" << endl;
    cout << "* [u] -> Zoom in" << endl;
    cout << "* [d] -> Zoom out" << endl;
    cout << "* [ESC] -> Close program" << endl << endl;

    src = imread("test.jpg", IMREAD_COLOR);

    if(src.empty()) {
        cout << "No data!" << endl;
        return -1;
    }

    tmp = src;
    dst = tmp;

    namedWindow(windowName, WINDOW_AUTOSIZE);
    imshow(windowName, dst);

    for(;;) {
        int c;
        c = waitKey(10);
        if((char)c == 27) {
            break;
        }
        if((char)c == 'u') {
            pyrUp(tmp, dst, Size(tmp.cols*2, tmp.rows*2));
            cout << "** Zoom In: Image x 2" << endl;
        }
        else if((char)c == 'd') {
            pyrDown(tmp, dst, Size(tmp.cols/2, tmp.rows/2));
            cout << "** Zoom out: Image / 2" << endl;
        }
        imshow(windowName, dst);
        tmp = dst;
    }
    return 0;
}