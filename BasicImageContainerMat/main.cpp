#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {

    Mat m(2,2, CV_8UC3, Scalar(0,0,255));
    cout << "m= " << endl << " " << m << endl << endl;


    m.create(2,3, CV_8UC(2));
    cout << "m= " << endl << " " << m << endl << endl;

    Mat e = Mat::eye(3, 3, CV_64F);
    cout << "e= " << endl << " " << e << endl  << endl;

    Mat o = Mat::ones(3, 3, CV_32F);
    cout << "o= " << endl << " " << o << endl << endl;

    Mat z = Mat::zeros(3, 3, CV_8UC1);
    cout << "z= " << endl << " " << z << endl << endl;

    Mat rowClone = m.row(1).clone();
    cout << "clone= " << endl << " " << rowClone << endl << endl;

    Mat R = Mat(3, 3, CV_8UC3);
    randu(R, Scalar::all(0), Scalar::all(255));
    cout << "R= " << endl << " " << R << endl << endl;

    // Output Format
    cout << "R (default) = " << endl << R << endl << endl;
    cout << "R (python) = " << endl << format(R, Formatter::FMT_PYTHON) << endl << endl;
    cout << "R (csv) = " << endl << format(R, Formatter::FMT_CSV) << endl << endl;
    cout << "R (numpy) = " << endl << format(R, Formatter::FMT_NUMPY) << endl << endl;
    cout << "R (c) = " << endl << format(R, Formatter::FMT_C) << endl << endl;

    // Output of other common items
    Point2f P(5, 1);
    cout << "Point (2D) = " << P  << endl << endl;

    Point3f P3f(3,4,5);
    cout << "Point (3D) = " << P3f << endl << endl;

    vector<float> f;
    f.push_back((float)CV_PI); f.push_back(2); f.push_back(3.01f);
    cout << "Vector of float via Mat = " << Mat(f) << endl << endl;

    vector<Point2f> points(20);
    for(size_t i =0; i < points.size(); i++) {
        points[i] = Point2f((float)(i*5), (float)(i%7));
    }
    cout << "A Vector of 2d point = " << points << endl << endl;
    return 0;
}