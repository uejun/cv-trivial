#include <vector>
#include <string>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

static void help() {
    cout << "\nThis program demonstrates circle finding with the Hough transform.\n"
        "Usage:\n"
            "./houghcircles <image_name>" << endl;
}

int main(int argc, const char* const argv[]) {

    string filename = "test.jpg";
    Mat src = imread(filename, IMREAD_COLOR);
    if(src.empty()) {
        cout << "can not open" << filename << endl;
        return -1;
    }

    Mat src_gray;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    GaussianBlur(src_gray, src_gray, Size(9,9), 2, 2);

    vector<Vec3f> circles;
    HoughCircles(src_gray, circles, HOUGH_GRADIENT, 2, src_gray.rows/4, 200, 100);

    for(size_t i = 0; i < circles.size(); i++ ) {
        Point center(circles[i][0], circles[i][1]);
        int radius = circles[i][2];
        circle(src, center, 3, Scalar(0,0,255), -1, 8, 0);
        circle(src, center, radius, Scalar(0,255,0), 3, 8, 0);
    }

    imshow("detected circles", src);
    waitKey();
    return 0;
}