#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace  cv;

int main(int argc, char* argv[]) {

    string imageName = "./test.jpg";

    Mat image = imread(imageName, IMREAD_COLOR);
    Mat grayImage = imread(imageName, IMREAD_GRAYSCALE);
    Mat handyMat(300, 300, CV_8UC3, Scalar(200, 100, 0));

    Scalar intensity = grayImage.at<uchar>(30, 10);
    cout << "Gray image intensity x 10, y 30 = " << intensity.val[0] << endl;

    Vec3b intentsity3b = image.at<Vec3b>(30, 30);
    uchar blue = intentsity3b.val[0];
    uchar green = intentsity3b.val[1];
    uchar red = intentsity3b.val[2];
    cout << "color intensity" << blue << " " << green << " " << red << endl;

    Mat sobelx;
    Sobel(image, sobelx, CV_32F, 1, 0);

    double minVal, maxVal;
    minMaxLoc(sobelx, &minVal, &maxVal);
    Mat sobelDraw;
    sobelx.convertTo(sobelDraw, CV_8U, 255.0/(maxVal-minVal), -minVal*255.0/(maxVal-minVal));


    Mat black = grayImage.clone();
    black = Scalar(0);

    Rect r(10, 10, 100, 100);
    Mat smallImg = image(r);

    Mat greyConverted;
    cvtColor(image, greyConverted, COLOR_BGR2GRAY);

    Mat dst;
    image.convertTo(dst, CV_32F);

    namedWindow("Output", WINDOW_AUTOSIZE);
    namedWindow("OutputGray", WINDOW_AUTOSIZE);
    namedWindow("OutputHandy", WINDOW_AUTOSIZE);
    namedWindow("OutputSobel", WINDOW_AUTOSIZE);
    namedWindow("OutputBlack", WINDOW_AUTOSIZE);
    namedWindow("OutputSmall", WINDOW_AUTOSIZE);
    namedWindow("ConvertedGray", WINDOW_AUTOSIZE);
    namedWindow("Convert232F", WINDOW_AUTOSIZE);

    imshow("Output", image);
    imshow("OutputGray", grayImage);
    imshow("OutputHandy", handyMat);
    imshow("OutputSobel", sobelDraw);
    imshow("OutputBlack", black);
    imshow("OutputSmall", smallImg);
    imshow("ConvertedGray", greyConverted);
    imshow("Convert232F", dst);


    imwrite("testcopy.jpg", image);

    waitKey(0);
    return 0;
}