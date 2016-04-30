#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

double alpha; /* Simple contrast control */
int beta;  /* simple brightness control */

int main(int argc, char* argv[]) {

    string imageFile = argc >= 2 ? argv[1] : "test.jpg";

    Mat image = imread(imageFile, IMREAD_COLOR);
    Mat newImage = Mat::zeros(image.size(), image.type());

    while(true) {
        cout << "Basic Linear Transforms" << endl;
        cout << "Enter the alpha value[1.0-3.0]:" << flush;
        cin >> alpha;
        cout << "Enter the beta balue[0-100]:" << flush;
        cin >> beta;

        if (alpha >= 1.0 && alpha <=3.0 && beta >= 0 && beta <= 100) {
            break;
        }
    }

    for(int y = 0; y < image.rows; y++ ) {
        for(int x = 0; x < image.cols; x++) {
            for (int c = 0; c < 3; c++ ) {
                newImage.at<Vec3b>(y, x)[c] =
                        saturate_cast<uchar>( alpha*(image.at<Vec3b>(y,x)[c] + beta));
            }
        }
    }

    // This command works in same way
    //image.convertTo(newImage, -1, alpha, beta);

    namedWindow("original", WINDOW_AUTOSIZE);
    namedWindow("new", WINDOW_AUTOSIZE);

    imshow("original", image);
    imshow("new", newImage);

    waitKey(0);

    return 0;
}