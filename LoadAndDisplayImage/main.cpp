#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

    string imageName("./test.jpg");
    if (argc > 1) {
        imageName = argv[1];
        return -1;
    }

    Mat image;
    image = imread(imageName.c_str(), CV_LOAD_IMAGE_COLOR);

    if( image.empty() ) {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow("Hello Image", WINDOW_AUTOSIZE);
    imshow("Hello Image", image);

    waitKey(0);

    return 0;
}