#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

int main(int argc, char** argv) {
    if(argc != 3) {
        return -1;
    }

    Mat img_1 = imread(argv[1], IMREAD_GRAYSCALE);
    Mat img_2 = imread(argv[2], IMREAD_GRAYSCALE);

    if(!img_1.data || !img_2.data) {
        return -1;
    }

    int minHessian = 400;

    Ptr<SURF> detector = SURF::create();
    detector->setHessianThreshold(minHessian);

    vector<KeyPoint> keypoints_1, keypoints_2;
    Mat descriptors_1, descriptors_2;

    detector->detectAndCompute(img_1, Mat(), keypoints_1, descriptors_1);
    detector->detectAndCompute(img_2, Mat(), keypoints_2, descriptors_2);

    BFMatcher matcher(NORM_L2);
    vector<DMatch> matches;
    matcher.match(descriptors_1, descriptors_2, matches);

    Mat img_matches;
    drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_matches);

    imshow("Matches", img_matches);

    waitKey(0);
    return 0;
}