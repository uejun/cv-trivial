#include <sstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

Mat& ScanAndReduceC(Mat& I, const uchar* const table) {

    CV_Assert(I.depth() == CV_8U);

    int channels = I.channels();

    int nRows = I.rows;
    int nCols = I.cols * channels;

    if (I.isContinuous()) {
        nCols *= nRows;
        nRows = 1;
    }

    int i,j;
    uchar* p;
    for(i = 0; i < nRows; i++) {
        p = I.ptr<uchar>(i);
        for (j = 0; j < nCols; j++) {
            p[j] = table[p[j]];
        }
    }
    return I;
}

Mat& ScanAndReducIterator(Mat& I, const uchar* const table) {
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch(channels) {
        case 1: {
            MatIterator_<uchar> it, end;
            for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; it++) {
                *it = table[*it];
            }
            break;
        }
        case 3: {
            MatIterator_<Vec3b> it, end;
            for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; it++) {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
            break;
        }
    }
    return I;
}

Mat& ScanAndReduceRandomAccess(Mat& I, const uchar* const table) {
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();
    switch(channels) {
        case 1: {
            for(int i=0; i<I.rows; i++) {
                for (int j=0; j<I.cols; j++) {
                    I.at<uchar>(i,j) = table[I.at<uchar>(j,j)];
                }
            }
            break;
        }
        case 3: {
            Mat_<Vec3b> _I = I;
            for(int i=0; i<_I.rows; i++) {
                for(int j=0; j<_I.cols; j++) {
                    _I(i,j)[0] = table[_I(i,j)[0]];
                    _I(i,j)[1] = table[_I(i,j)[1]];
                    _I(i,j)[2] = table[_I(i,j)[2]];
                }
            }
            I = _I;
            break;
        }
    }

    return I;
}

static void help() {
    cout
        << "\n-----------------------------------------------------" << endl
        << "This program shows how to scan image objects in OpenCV." << endl
        << "As use case we take an input image and divide the native " << endl
        << " color palette (255) with the input." << endl
        << "Shows C operator[] method, iterators and at function for on-the-fly item address calculation." << endl
        << "Usage:" << endl
        << "./ScanImages imageName divideWith [G]" << endl
        << "if you add a G  parameter the imagge is processed in gray scale" << endl
        << "------------------------------------------------------" << endl
        << endl;

}

int main(int argc, char* argv[]) {

    help();

    if(argc < 3) {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    Mat I, J;
    if (argc == 4 && !strcmp(argv[3], "G")) {
        I =imread(argv[1], IMREAD_GRAYSCALE);
    } else {
        I = imread(argv[1], IMREAD_COLOR);
    }

    if(I.empty()) {
        cout << "The image" << argv[1] << " could not be loaded." << endl;
        return -1;
    }

    int divideWith = 0;
    stringstream s;
    s << argv[2];
    s >> divideWith;

    if (!s || !divideWith) {
        cout << "Invalid number entered for divideWith" << endl;
        return -1;
    }

    uchar table[256];
    for (int i = 0; i < 256; i++) {
        table[i] = (uchar) (divideWith * (i / divideWith));
    }

    const int times = 100;
    double t = (double) getTickCount();

    for (int i=0; i < times; ++i) {
        Mat clone_i = I.clone();
        J = ScanAndReduceC(clone_i, table);
    }

    t = 1000*((double) getTickCount() - t) / getTickFrequency();
    t /= times;

    cout << "Time of reducing with the C operrator [] passed " << t << "ms" << endl;

    t = (double)getTickCount();

    for (int i = 0; i < times; i++) {
        Mat clone_i = I.clone();
        J = ScanAndReducIterator(clone_i, table);
    }

    t = 1000*((double) getTickCount() -t) / getTickFrequency();
    t /= times;

    cout << "Time of reducing with the iterator passed " << t << "ms" << endl;

    t = (double)getTickCount();

    for (int i = 0; i < times; i++) {
        Mat clone_i = I.clone();
        J = ScanAndReduceRandomAccess(clone_i, table);
    }

    t = 1000*((double) getTickCount() -t )/ getTickFrequency();
    t /= times;


    cout << "Time of reducing with the on-the-fly address generation at function passed " << t << "ms" << endl;


    Mat lookupTable(1, 256, CV_8U);
    uchar* p = lookupTable.ptr();
    for (int i = 0; i < 256; i++) {
        p[i] = table[i];
    }

    t = (double)getTickCount();

    for (int i = 0; i < times; i++) {
        LUT(I, lookupTable, J);
    }

    t = 1000*((double)getTickCount() -t) / getTickFrequency();
    t /= times;


    cout << "Time of reducing with the LUT function passed " << t << "ms" << endl;
    return 0;
}

