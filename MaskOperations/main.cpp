#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

static void help(char* progName) {
    cout << endl
        << "This program shows how to filter images with mask: the write it yourself and the filter2d way." << endl
        << "Usage:" << endl
        << progName << "[image_name --default ./test.jpg] [G -- grayscale]" << endl << endl;
}

void Sharpen(const Mat& myImage, Mat& Result) {

    CV_Assert(myImage.depth() == CV_8U);

    Result.create(myImage.size(), myImage.type());
    int nChannels = myImage.channels();

    for (int j = 1; j < myImage.rows - 1; ++j) {
        const uchar* previous = myImage.ptr<uchar>(j-1);
        const uchar* current  = myImage.ptr<uchar>(j);
        const uchar* next     = myImage.ptr<uchar>(j+1);

        uchar* output = Result.ptr<uchar>(j);

        for (int i = nChannels; i < nChannels * (myImage.cols -1); ++i) {
            *output++ = saturate_cast<uchar>( 5* current[i]
                                              - current[i-nChannels] - current[i+nChannels] - previous[i] - next[i]);
        }
    }

    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows-1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols-1).setTo(Scalar(0));
}

int main(int argc, char* argv[]) {
    help(argv[0]);
    const char* filename = argc >=2 ? argv[1] : "./test.jpg";

    Mat I, J, K;

    if (argc >=3 && !strcmp("G", argv[2]))
        I = imread(filename, IMREAD_GRAYSCALE);
    else
        I = imread(filename, IMREAD_COLOR);

    namedWindow("Input", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);

    imshow("Input", I);
    double t = (double)getTickCount();

    Sharpen(I, J);

    t = ((double)getTickCount()-t)/getTickFrequency();
    cout << "Hand writtern function times passed in seconds " << t << endl;

    Mat kern = (Mat_<char>(3,3) << 0, -1,  0,
                                  -1,  5, -1,
                                   0, -1,  0);

    t = (double)getTickCount();
    filter2D(I, K, I.depth(), kern);

    t = ((double)getTickCount() - t) / getTickFrequency();
    cout << "Build-in filter2D time passed in seconds: " << t << endl;

    imshow("Output", K);

    waitKey(0);

    return 0;

}