#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

const int NUMBER = 100;
const int DELAY = 5;

const int window_width = 900;
const int window_height = 600;
int x_1 = -window_width/2;
int x_2 = window_width*3/2;
int y_1 = -window_width/2;
int y_2 = window_width*3/2;

static Scalar randomColor(RNG& rng) {
    int icolor = (unsigned) rng;
    return Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

int Drawing_Random_Lines(Mat image, char* window_name, RNG rng) {
    Point pt1, pt2;

    for(int i=0; i<NUMBER; i++) {
        pt1.x = rng.uniform(x_1, x_2);
        pt1.y = rng.uniform( y_1, y_2 );
        pt2.x = rng.uniform( x_1, x_2 );
        pt2.y = rng.uniform( y_1, y_2 );

        line(image, pt1, pt2, randomColor(rng), rng.uniform(1, 10), 8);
        imshow(window_name, image);
        if (waitKey(DELAY) >= 0) {
            return -1;
        }
    }

    return 0;
}

int Drawing_Random_Rectangles(Mat image, char* window_name, RNG rng) {
    Point pt1, pt2;
    int lineType = 8;
    int thickness = rng.uniform(-3, 10);

    for(int i=0; i<NUMBER; i++) {
        pt1.x = rng.uniform(x_1, x_2);
        pt1.y = rng.uniform( y_1, y_2 );
        pt2.x = rng.uniform( x_1, x_2 );
        pt2.y = rng.uniform( y_1, y_2 );
    }

    rectangle(image, pt1, pt2, randomColor(rng), MAX(thickness, -1), lineType);

    imshow(window_name, image);
    if(waitKey(DELAY) >= 0) {
        return -1;
    }

    return 0;
}

int Drawing_Random_Ellipses(Mat image, char* window_name, RNG rng) {
    int lineType = 8;

    for(int i=0; i<NUMBER; i++) {
        Point center;
        center.x = rng.uniform(x_1, x_2);
        center.y = rng.uniform(y_1, y_2);

        Size axes;
        axes.width = rng.uniform(0, 200);
        axes.height = rng.uniform(0, 200);

        double angle = rng.uniform(0, 180);

        ellipse(image, center, axes, angle, angle -100, angle + 200, randomColor(rng), rng.uniform(-1, 9), lineType);

        imshow(window_name, image);

        if (waitKey(DELAY >= 0)) {
            return -1;
        }

    }

    return 0;
}


int main() {

    int c;

    char window_name[] = "RandomDrawing";

    RNG rng(0xFFFFFFFF);

    Mat image = Mat::zeros(window_height, window_width, CV_8UC3);
    imshow(window_name, image);
    waitKey(DELAY);

    c = Drawing_Random_Lines(image, window_name, rng);
    if (c != 0) return 0;

    c = Drawing_Random_Rectangles(image, window_name, rng);
    if(c != 0) return 0;

    c = Drawing_Random_Ellipses(image, window_name, rng);
    if(c != 0) return 0;

    waitKey(0);
    return 0;


    return 0;

}