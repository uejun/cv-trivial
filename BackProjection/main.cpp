#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

Mat src;
Mat hsv;
Mat hue;
int bins = 25;

void Hist_and_Backproj(int, void*);

int main(int argc, char* argv[]) {
    src = imread(argv[1], IMREAD_COLOR);
    cvtColor(src, hsv, COLOR_BGR2HSV);

    hue.create(hsv.size(), hsv.depth());
    int ch[] = {0, 0};
    mixChannels(&hsv, 1, &hue, 1, ch, 1);

    const char* window_name = "Src image";
    namedWindow(window_name, WINDOW_AUTOSIZE);
    createTrackbar("* Hue bins", window_name, &bins, 180, Hist_and_Backproj);
    Hist_and_Backproj(0,0);

    imshow(window_name, src);

    waitKey(0);

    return 0;
}

void Hist_and_Backproj(int, void*) {
    MatND hist;
    int histSize = MAX(bins, 2);
    float hue_range[] = {0, 180};
    const float* ranges = {hue_range};

    calcHist(&hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
    normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

    MatND backproj;
    calcBackProject(&hue, 1, 0, hist, backproj, &ranges, 1, true);

    imshow("BackProj", backproj);

    int w = 400;
    int h = 400;
    int bin_w = cvRound((double) w/ histSize);
    Mat histImg = Mat::zeros(w, h, CV_8UC3);

    for(int i=0; i<bins; i++) {
        rectangle(histImg, Point(i*bin_w, h), Point((i+1)*bin_w, h - cvRound(hist.at<float>(i)*h/255.0)), Scalar(0,0,255), -1);
    }

    imshow("Histgram", histImg);
}