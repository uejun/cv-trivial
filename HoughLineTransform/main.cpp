#include <vector>
#include <string>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

static void help() {
    cout << "\nThis program demonstrates line finding with the Hough transform.\n"
    << "Usage:\n"
    << "./HoughLineTransform <image_name>" << endl;
}
int main(int argc, char** argv) {

    CommandLineParser parser(argc, argv, "{help h||}{@image|../data/pic1.png|}");

    if (parser.has("help")) {
        help();
        return 0;
    }

    string filename = parser.get<string>("@image");
    if (filename.empty()) {
        help();
        cout << "no image provided" << endl;
        return -1;
    }

    Mat src = imread(filename, 0);
    if(src.empty()) {
        help();
        cout << "can not open " << filename << endl;
        return -1;
    }

   Mat dst, cdst;
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, COLOR_GRAY2BGR);

#if 0
    vector<Vec2f> lines;
    HoughLines(dst, lines, 1, CV_PI/180, 100, 0,0);

    for(size_t i=0; i<lines.size(); i++) {

        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 + 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA );
    }
    return 0;
}