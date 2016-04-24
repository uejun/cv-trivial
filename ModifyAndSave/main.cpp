#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    char* imageName = argv[1];

    Mat image;
    image = imread(imageName, 1);

    if (argc != 2 || ! image.data) {
        printf( " No image data \n " );
        return -1;
    }

    Mat gray_image;
    cvtColor(image, gray_image, COLOR_BGR2GRAY);

    imwrite("./gray_image.jpg", gray_image);

    namedWindow("Input Image", WINDOW_AUTOSIZE);
    namedWindow("Gray Image", WINDOW_AUTOSIZE);

    imshow("Input Image", image);
    imshow("Gray Image", gray_image);

    waitKey(0);

    return 0;
}