#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;

void readme() {
   cout << "Usage:./FeatureDetection <img1> <img2>" << endl;
}

int main(int argc, char** argv) {
    if(argc != 3) {
        readme();
        return -1;
    }

    Mat img_1 = imread(argv[1], IMREAD_GRAYSCALE);
    Mat img_2 = imread(argv[2], IMREAD_GRAYSCALE);

    if(!img_1.data || !img_2.data) {
        cout << "Error: reading images" << endl;
        return -1;
    }

    int minHessian = 400;

    Ptr<xfeatures2d::SURF> detector = xfeatures2d::SURF::create(minHessian);

    vector<KeyPoint> keypoints_1, keypoints_2;

    detector->detect(img_1, keypoints_1);
    detector->detect(img_2, keypoints_2);

    Mat img_keypoints_1, img_keypoints_2;
    drawKeypoints(img_1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    drawKeypoints(img_2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

    imshow("Keypoints 1", img_keypoints_1);
    imshow("Keypoints 2", img_keypoints_2);

    waitKey(0);

    return 0;
}