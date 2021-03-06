#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <iostream>
#include  <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

// define the corner points
//    Note that GDAL library can natively determine this
cv::Point2d tl( -122.441017, 37.815664 );
cv::Point2d tr( -122.370919, 37.815311 );
cv::Point2d bl( -122.441533, 37.747167 );
cv::Point2d br( -122.3715,   37.746814 );

// determine dem corners
cv::Point2d dem_bl( -122.0, 38);
cv::Point2d dem_tr( -123.0, 37);

// range of  the heat map colors
vector<pair<Vec3b, double>> color_range;

Point2d lerp(const Point2d&, const Point2d&, const double&);
Vec3b get_dem_color(const double&);
Point2d world2dem(const Point2d&, const Size&);
Point2d pixel2world(const int&, const int&, const Size&);
void add_color(Vec3b& pix, const uchar& b, const uchar& g, const uchar& r);

/*
 * Linear Interpolation
 * p1 - Point 1
 * p2 - Point 2
 * t - Ratio from Point 1 to Point 2
 */
Point2d lerp(Point2d const& p1, Point2d const& p2, const double& t) {
    return Point2d( ((1-t)*p1.x) + (t*p2.x), ((1-t)*p1.y) + (t*p2.y));
}

/*
 * Interpolate Colors
 */
template <typename DATATYPE, int N>
Vec<DATATYPE, N> lerp(Vec<DATATYPE, N> const& minColor, Vec<DATATYPE, N> const& maxColor, double const& t) {
    Vec<DATATYPE, N> output;
    for(int i = 0; i < N; i++) {
        output[i] = (uchar)( ((1-t)*minColor[i]) + (t*maxColor[i]) );
    }
    return output;
};

/*
 * Compute the dem color
 */
Vec3b get_dem_color(const double& elevation) {

    if(elevation < color_range[0].second) {
        return color_range[0].first;
    }
    if(elevation > color_range.back().second) {
        return color_range.back().first;
    }

    // otherwise, find the proper starting index
    int idx = 0;
    double t = 0;
    for (int x = 0; x < (int)(color_range.size() -1 ); x++) {
        if(elevation < color_range[x+1].second) {
            idx = x;
            t = (color_range[x+1].second -elevation) / (color_range[x+1].second - color_range[x].second);
            break;
        }
    }

    return lerp(color_range[idx].first, color_range[idx+1].first, t);
}

/*
 * Given a pixel coordinate and the size of the input image, compute the pixel location on the DEM image.
 */
Point2d world2dem(Point2d const& coordinate, const Size& dem_size) {
    // relate this to the dem points
    // ASSUMING THAT DEM DATA IS ORTHORECTIFIED
    double demRatioX = ((dem_tr.x - coordinate.x)/(dem_tr.x - dem_bl.x));
    double demRatioY = 1 - ((dem_tr.y - coordinate.y)/(dem_tr.y - dem_bl.y));

    Point2d output;
    output.x = demRatioX * dem_size.width;
    output.y = demRatioY * dem_size.height;

    return output;
}

/*
 * Convert a pixel coordinate to world coordinates
 */
Point2d pixel2world(const int& x, const int& y, const Size& size) {
    // compute the ratio of the pixel location to its dimension
    double rx = (double)x / size.width;
    double ry = (double)y / size.height;

    // compute LERP of each coordinate
    Point2d rightSide = lerp(tr, br, ry);
    Point2d leftSide = lerp(tl, bl, ry);

    return lerp(leftSide, rightSide, rx);
}

/*
 * Add color to a specific pixel color value
 */
void add_color(Vec3b& pix, const uchar& b, const uchar& g, const uchar& r) {
    if(pix[0] + b < 255 && pix[0] + b >= 0) {pix[0] += b;}
    if(pix[1] + g < 255 && pix[1] + g >=0) {pix[1] += g;}
    if(pix[2] + r < 255 && pix[2] + r >=0) {pix[2] += r;}
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cout << "usage: " << argv[0] << " <image> <dem>" << endl;
        return -1;
    }

    Mat image = imread(argv[1], IMREAD_LOAD_GDAL | IMREAD_COLOR);
    Mat dem = imread(argv[2], IMREAD_LOAD_GDAL | IMREAD_ANYDEPTH);

    Mat output_dem(image.size(), CV_8UC3);
    Mat output_dem_flood(image.size(), CV_8UC3);

    if (dem.type() != CV_16SC1) { throw runtime_error("DEM image type must be CV_16SC1");}

    color_range.push_back(pair<Vec3b, double>(Vec3b(188, 154, 46), -1));
    color_range.push_back(pair<Vec3b, double>(Vec3b(110, 220, 110), 0.25));
    color_range.push_back(pair<Vec3b, double>(Vec3b(150, 250, 230), 20));
    color_range.push_back( pair<Vec3b,double>(Vec3b( 160, 220, 200),   75));
    color_range.push_back( pair<Vec3b,double>(Vec3b( 220, 190, 170),  100));
    color_range.push_back( pair<Vec3b,double>(Vec3b( 250, 180, 140),  200));

    double minElevation = -10;

    for(int y=0; y<image.rows; y++) {
        for(int x=0; x<image.cols; x++) {

            Point2d coordinate = pixel2world(x, y, image.size());
            Point2d dem_coordinate = world2dem(coordinate, dem.size());

            //extract the elevation
            double dz;
            if(dem_coordinate.x >= 0 && dem_coordinate.y >= 0 && dem_coordinate.x < dem.cols && dem_coordinate.y < dem.rows) {
                dz = dem.at<short>(dem_coordinate);
            } else {
                dz = minElevation;
            }

            output_dem_flood.at<Vec3b>(y,x) = image.at<Vec3b>(y,x);

            Vec3b actualColor = get_dem_color(dz);
            output_dem.at<Vec3b>(y,x) = actualColor;

            if(dz < 10) {
                add_color(output_dem_flood.at<Vec3b>(y,x), 90, 0, 0);
            } else if(dz < 50) {
                add_color(output_dem_flood.at<Vec3b>(y,x), 0, 90, 0);
            } else if(dz < 100) {
                add_color(output_dem_flood.at<Vec3b>(y,x), 0, 0, 90);
            }

        }
    }

    imshow("heat-map", output_dem);
    imshow("flooded", output_dem_flood);

    waitKey(0);
    return 0;
}