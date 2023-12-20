#ifndef CAMERA_H
#define CAMERA_H

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <algorithm>
#include <vector>

using namespace cv;

class node {
public:
    Point point;
    Scalar HSV;
    Scalar BGR;
    int size;

    int color2num() {

        double h = HSV[0] / 2;
        double s = HSV[1] * 255 / 100;
        int color;

        if (h < 10) {
            if (h > 5 && s < 180)
                color = 5;         
            else
                color = 4;
        }
        else if (h > 165)
            color = 4;

        else if (s < 70)
            color = 3;

        else if (h > 25 && h < 35)
            color = 2;

        else if (h > 35 && h < 80)
            color = 1;

        else if (h > 10 && h < 25)
            color = 5;

        else
            color = 0;

        return color;
    }

    std::string color2string() {

        double h = HSV[0] / 2;
        double s = HSV[1] * 255 / 100;
        std::string color = "";

        if (h < 10) {
            if (h > 5 && s < 180)
                color = "O";            
            else
                color = "R";
        }
        else if (h > 165)
            color = "R";

        else if (s < 70)
            color = "W";

        else if (h > 25 && h < 35)
            color = "Y";

        else if (h > 35 && h < 80)
            color = "G";

        else if (h > 10 && h < 25)
            color = "O";

        else
            color = "B";

        return color;
    }
};

Scalar bgr2hsv(Scalar bgr);

bool compareX(node a, node b);

bool compareY(node a, node b);

double angle(Point pt1, Point pt2, Point pt0);

std::vector<node> drawSquares(Mat& image, const std::vector<std::vector<Point>>& squares);

void findSquares(const Mat& image, std::vector<std::vector<Point> >& squares);

std::vector<node> sqColor(Mat& image, int w, int h);

void cameraInput(int *map);


#endif // CAMERA_H
