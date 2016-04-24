#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

    if (argc != 2) {
        cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
        return -1;
    }

    Mat image;
    image = imread("./test.jpg");

    if(! image.data ) {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow("Hello Image", WINDOW_AUTOSIZE);
    imshow("Hello Image", image);

    waitKey(0);

    return 0;
}