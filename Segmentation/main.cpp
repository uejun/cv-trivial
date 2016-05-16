#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

    Mat src = imread(argv[1], IMREAD_COLOR);
    if(!src.data) {
        return -1;
    }

    imshow("Source Image", src);

    for(int x = 0; x < src.rows; x++) {
        for(int y = 0; y < src.cols; y++) {
            if(src.at<Vec3b>(x,y) == Vec3b(255,255,255)) {
                src.at<Vec3b>(x,y)[0] = 0;
                src.at<Vec3b>(x,y)[1] = 0;
                src.at<Vec3b>(x,y)[2] = 0;
            }
        }
    }

    imshow("Black Background Img", src);

    Mat kernel = (Mat_<float>(3,3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);

    Mat imgLaplacian;
    Mat sharp = src;
    filter2D(sharp, imgLaplacian, CV_32F, kernel);
    src.convertTo(sharp, CV_32F);
    Mat imgResult = sharp - imgLaplacian;
    return 0;
}