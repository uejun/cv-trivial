#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    double alpha, beta, input;

    while (true) {
        cout << " Simple Linear Blender " << endl;
        cout << " Enter alpha [0-1]: " << flush;
        cin >> input;
        if (input >= 0.0 && input <= 1.0) {
            alpha = input;
            break;
        }
        cout << endl;
    }

    beta = 1 - alpha;

    Mat a, b, dst;
    Size dsize{200, 200};
    resize(imread("test.jpg", IMREAD_COLOR), a, dsize, 0, 0, false);
    resize(imread("kiss.jpg", IMREAD_COLOR), b, dsize, 0, 0, false);

    if (a.empty()) cout << "Error loading test.jpg" << endl;
    if (b.empty()) cout << "Error loading kiss.jpg" << endl;

    namedWindow("Blending", WINDOW_AUTOSIZE);

    addWeighted(a, alpha, b, beta, 0.0, dst);



    imshow("Blending", dst);

    waitKey(0);

    return 0;
}