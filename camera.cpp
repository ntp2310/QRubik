#include "camera.h"

Scalar bgr2hsv(Scalar bgr) {

    double hue = 0, sat = 0, value = 0;
    double maxval, minval;
    double red, green, blue;

    red = bgr[2] / 255.0;
    green = bgr[1] / 255.0;
    blue = bgr[0] / 255.0;

    maxval = MAX(red, MAX(green, blue));
    minval = MIN(red, MIN(green, blue));

    double difference = maxval - minval;

    if (difference == 0)
        hue = 0;
    else if (red == maxval)
        hue = fmod(((60 * ((green - blue) / difference)) + 360), 360.0);
    else if (green == maxval)
        hue = fmod(((60 * ((blue - red) / difference)) + 120), 360.0);
    else if (blue == maxval)
        hue = fmod(((60 * ((red - green) / difference)) + 240), 360.0);

    if (maxval == 0)
        sat = 0;
    else
        sat = 100 * (difference / maxval);

    value = maxval * 100;

    return Scalar(hue, sat, value);
}

bool compareX(node a, node b) {
    return (a.point.x < b.point.x);
}

bool compareY(node a, node b) {
    return (a.point.y < b.point.y);
}

double angle(Point pt1, Point pt2, Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1 * dx2 + dy1 * dy2) / sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2) + 1e-10);
}

std::vector<node> drawSquares(Mat& image, const std::vector<std::vector<Point>>& squares)
{
    std::vector<node> list;
    for (size_t i = 0; i < squares.size(); i++)
    {
        node t;
        int shift = 1;

        Rect r = boundingRect(Mat(squares[i]));

        int size = MIN(r.width, r.height);
        Rect rect(r.x, r.y, size, size);
        Mat roi = image(r);

        Scalar color = mean(roi);

        Point center(r.x + size / 2, r.y + size / 2);
        t.point = center;
        t.HSV = bgr2hsv(color);
        t.BGR = color;
        t.size = (float)size;

        if ((float)r.width / (float)r.height < 1.2 && (float)r.height / (float)r.width < 1.2) {
            rectangle(image, rect, Scalar(255, 255, 255), 2, LINE_AA);
            list.push_back(t);
        }
    }

    int check = 0;
    int index = 0;
    for (int i = 0; i < list.size(); i++) {
        int num = 0;
        for (int j = 0; j < list.size(); j++) {

            float a = (float)(list[i].point.x - list[j].point.x);
            float b = (float)(list[i].point.y - list[j].point.y);

            if (sqrt(a * a + b * b) <= 2 * (float)(list[i].size / 2 + list[j].size / 2) && j != i)
                num++;

            if (num == 8) {
                check == 1;
                index = i;
                break;
            }
        }
        if (check == 1)
            break;      
    }

    std::vector<node> listFace;
    for (int i = 0; i < list.size(); i++) {

        float a = (float)(list[index].point.x - list[i].point.x);
        float b = (float)(list[index].point.y - list[i].point.y);

        if (sqrt(a * a + b * b) <= 2 * (list[index].size / 2 + list[i].size / 2))
            listFace.push_back(list[i]);
    }

    if (listFace.size() == 9) {
        node pnt[9];

        for (int j = 0; j < 9; j++)
            pnt[j] = listFace[j];

        std::sort(pnt, pnt + 9, compareY);
        std::sort(pnt, pnt + 3, compareX);
        std::sort(pnt + 3, pnt + 6, compareX);
        std::sort(pnt + 6, pnt + 9, compareX);

        float a = (float)abs(pnt[0].point.x - pnt[2].point.x);
        float b = (float)abs(pnt[6].point.x - pnt[8].point.x);
        float c = (float)abs(pnt[0].point.y - pnt[6].point.y);
        float d = (float)abs(pnt[2].point.y - pnt[8].point.y);
        float e = (float)abs(pnt[3].point.x - pnt[5].point.x);
        float f = (float)abs(pnt[1].point.y - pnt[7].point.y);
        float g = (float)abs(pnt[1].point.y - pnt[4].point.y);
        float h = (float)abs(pnt[7].point.y - pnt[4].point.y);
        float i = (g + h) / f;

        int cx = pnt[4].point.x;
        int cy = pnt[4].point.y;

        bool check1 = (i > 1.15 || i < 0.8);
        bool check = (cx < pnt[3].point.x || cx > pnt[5].point.x || cy < pnt[1].point.y || cy > pnt[7].point.y || check1);

        if (a / b > 1.15 || a / b < 0.8 || c / d > 1.15 || c / d < 0.8 || a / c > 1.15 || a / c < 0.8 || f / e > 1.15 || f / e < 0.8 || a / f > 1.15 || a / f < 0.8 || check)
        {
            listFace.clear();
        }
    }

    return listFace;
}


void findSquares(const Mat& image, std::vector<std::vector<Point> >& squares)
{
    squares.clear();

    Mat gray, gray0, gray1, hu, gray2;

    std::vector<std::vector<Point> > contours;

    cvtColor(image, gray0, COLOR_BGR2GRAY);
    //morphologyEx(gray0, gray0, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(2, 2)), Point(-1, -1), 2);
    //morphologyEx(gray0, gray0, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(2, 2)), Point(-1, -1), 2);
    medianBlur(gray0, gray0, 5);
    //GaussianBlur(gray0, gray0, Size(3, 3), 0);
    adaptiveThreshold(gray0, gray1, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);
    erode(gray1, gray1, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 2);
    Canny(gray1, gray, 0, 10, 3);

    dilate(gray, gray, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 2);
    //morphologyEx(gray, gray, MORPH_DILATE, getStructuringElement(MORPH_RECT, Size(3, 3)), Point(-1, -1), 2);
    findContours(gray, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    std::vector<Point> approx;

    // test each contour
    for (size_t i = 0; i < contours.size(); i++)
    {
        // approximate contour with accuracy proportional
        // to the contour perimeter
        approxPolyDP(Mat(contours[i]), approx, 9, true);

        if (approx.size() == 4 &&
            fabs(contourArea(Mat(approx))) > 100 && fabs(contourArea(Mat(approx))) < 9000 &&
            isContourConvex(Mat(approx)))
        {
            double maxCosine = 0;

            for (int j = 2; j < 5; j++)
            {
                // find the maximum cosine of the angle between joint edges
                double cosine = fabs(angle(approx[j % 4], approx[j - 2], approx[j - 1]));
                maxCosine = MAX(maxCosine, cosine);
            }

            if (maxCosine < 0.3)
                squares.push_back(approx);          
        }
    }
}

std::vector<node> sqColor(Mat& image, int w, int h) {

    std::vector<node> list;
    int center_x = w / 2;
    int center_y = 0.5 * h;
    int center_xs = w / 2 + 1;
    int center_ys = 0.5 * h + 1;
    int size = 40;
    int size1 = 34;

    Rect r0(center_x - 3 * size, center_y - 3 * size, size, size);
    Rect r1(center_x, center_y - 3 * size, size, size);
    Rect r2(center_x + 3 * size, center_y - 3 * size, size, size);
    Rect r3(center_x - 3 * size, center_y, size, size);
    Rect r4(center_x, center_y, size, size);
    Rect r5(center_x + 3 * size, center_y, size, size);
    Rect r6(center_x - 3 * size, center_y + 3 * size, size, size);
    Rect r7(center_x, center_y + 3 * size, size, size);
    Rect r8(center_x + 3 * size, center_y + 3 * size, size, size);

    Rect r9(center_xs - 3 * size, center_ys - 3 * size, size1, size1);
    Rect r10(center_xs, center_ys - 3 * size, size1, size1);
    Rect r11(center_xs + 3 * size, center_ys - 3 * size, size1, size1);
    Rect r12(center_xs - 3 * size, center_ys, size1, size1);
    Rect r13(center_xs, center_ys, size1, size1);
    Rect r14(center_xs + 3 * size, center_ys, size1, size1);
    Rect r15(center_xs - 3 * size, center_ys + 3 * size, size1, size1);
    Rect r16(center_xs, center_ys + 3 * size, size1, size1);
    Rect r17(center_xs + 3 * size, center_ys + 3 * size, size1, size1);

    rectangle(image, r0, Scalar(0, 0, 0), 2, LINE_AA);
    rectangle(image, r1, Scalar(0, 0, 0), 2, LINE_AA);
    rectangle(image, r2, Scalar(0, 0, 0), 2, LINE_AA);
    rectangle(image, r3, Scalar(0, 0, 0), 2, LINE_AA);
    rectangle(image, r4, Scalar(0, 0, 0), 2, LINE_AA);
    rectangle(image, r5, Scalar(0, 0, 0), 2, LINE_AA);
    rectangle(image, r6, Scalar(0, 0, 0), 2, LINE_AA);
    rectangle(image, r7, Scalar(0, 0, 0), 2, LINE_AA);
    rectangle(image, r8, Scalar(0, 0, 0), 2, LINE_AA);

    Mat roi0 = image(r9);  Scalar c0 = mean(roi0);
    Mat roi1 = image(r10); Scalar c1 = mean(roi1);
    Mat roi2 = image(r11); Scalar c2 = mean(roi2);
    Mat roi3 = image(r12); Scalar c3 = mean(roi3);
    Mat roi4 = image(r13); Scalar c4 = mean(roi4);
    Mat roi5 = image(r14); Scalar c5 = mean(roi5);
    Mat roi6 = image(r15); Scalar c6 = mean(roi6);
    Mat roi7 = image(r16); Scalar c7 = mean(roi7);
    Mat roi8 = image(r17); Scalar c8 = mean(roi8);

    node t0; t0.point = Point(center_x - 3 * size, center_y - 3 * size); t0.HSV = bgr2hsv(c0);
    node t1; t1.point = Point(center_x, center_y - 3 * size);            t1.HSV = bgr2hsv(c1);
    node t2; t2.point = Point(center_x + 3 * size, center_y - 3 * size); t2.HSV = bgr2hsv(c2);
    node t3; t3.point = Point(center_x - 3 * size, center_y);            t3.HSV = bgr2hsv(c3);
    node t4; t4.point = Point(center_x, center_y);                       t4.HSV = bgr2hsv(c4);
    node t5; t5.point = Point(center_x + 3 * size, center_y);            t5.HSV = bgr2hsv(c5);
    node t6; t6.point = Point(center_x - 3 * size, center_y + 3 * size); t6.HSV = bgr2hsv(c6);
    node t7; t7.point = Point(center_x, center_y + 3 * size);            t7.HSV = bgr2hsv(c7);
    node t8; t8.point = Point(center_x + 3 * size, center_y + 3 * size); t8.HSV = bgr2hsv(c8);

    list.push_back(t0);
    list.push_back(t1);
    list.push_back(t2);
    list.push_back(t3);
    list.push_back(t4);
    list.push_back(t5);
    list.push_back(t6);
    list.push_back(t7);
    list.push_back(t8);

    return list;
}

void cameraInput(int *map)
{
    const int n = 1;
    namedWindow("Rubix", WINDOW_AUTOSIZE);
    int mode = 0;
    int index = 0;
    bool allow;

    std::vector<node> tmp, cur, cur1;

    VideoCapture cap;
    Mat frame;

    cap.open(0, cv::CAP_ANY);

    if (!cap.isOpened())
    {
        cap.release();
        destroyWindow("Rubix");
        return;
    }

    int h = cap.get(CAP_PROP_FRAME_HEIGHT);
    int w = cap.get(CAP_PROP_FRAME_WIDTH);

    std::vector<std::vector<Point>> squares;

    for (int t = 0; t < 6; t++) {

        cap.open(0, cv::CAP_ANY);

        allow = false;

        while (!allow)
        {
            cur.clear();
            cur1.clear();
            squares.clear();

            cap.read(frame);

            while (frame.empty())
                cap.read(frame);

            std::string s;

            switch (t)
            {
                case 0:
                    s = "Show F face";
                    break;
                case 1:
                    s = "Show R face";
                    break;
                case 2:
                    s = "Show B face";
                    break;
                case 3:
                    s = "Show L face";
                    break;
                case 4:
                    s = "Show U face";
                    break;
                case 5:
                    s = "Show D face";
                    break;
            }

            putText(frame, s, Point(30, 30), FONT_HERSHEY_DUPLEX, 0.8, Scalar(10, 10, 10), 2, LINE_AA);
            putText(frame, "Press (q) to quit", Point(30, 60), FONT_HERSHEY_DUPLEX, 0.8, Scalar(10, 10, 10), 2, LINE_AA);

            int k = waitKey(1);

            if (k == 113) {
                cap.release();
                destroyWindow("Rubix");
                return;
            }
            else if (k == 49)
                mode = 0;

            else if (k == 50)
                mode = 1;

            if (mode == 0) {
                findSquares(frame, squares);
                cur = drawSquares(frame, squares);
            }
            else {
                cur1 = sqColor(frame, w, h);
                for (int i = 0; i < cur1.size(); i++)
                    putText(frame, cur1[i].color2string(), cur1[i].point, FONT_HERSHEY_DUPLEX, 0.5, Scalar(255, 255, 255), 1, LINE_AA);
            }

            if (cur.size() == 9 * n && mode == 0) {

                putText(frame, "Press (y) to continue, (n) to try again", Point(0.2 * w, 0.9 * h), FONT_HERSHEY_DUPLEX, 0.6, Scalar(255, 255, 255), 1, LINE_AA);
                imshow("Rubix", frame);

                while (true)
                {
                    int k = waitKey(0);
                    if (k == 121) {
                        allow = true;
                        break;
                    }

                    else if (k == 110)
                        break;

                    else if (k == 113) {
                        cap.release();
                        destroyWindow("Rubix");
                        return;
                    }
                }

                break;
            }

            else if (mode == 1 && k == 32) {

                putText(frame, "Press (y) to continue, (n) to try again", Point(0.2 * w, 0.9 * h), FONT_HERSHEY_DUPLEX, 0.6, Scalar(255, 255, 255), 1, LINE_AA);
                imshow("Rubix", frame);

                while (true) {
                    int k = waitKey(0);
                    if (k == 121) {
                        allow = true;
                        break;
                    }

                    else if (k == 110)
                        break;

                    else if (k == 113) {
                        cap.release();
                        destroyWindow("Rubix");
                        return;
                    }
                }
                break;
            }

            else
                imshow("Rubix", frame);
        }

        if (allow) {
            node pnt1[9 * n];

            if (mode == 0)
                tmp = cur;
            else
                tmp = cur1;


            for (int i = 0; i < 9 * n; i++)
                pnt1[i] = tmp[i];

            std::sort(pnt1, pnt1 + 9 * n, compareY);
            std::sort(pnt1, pnt1 + 3 * n, compareX);
            std::sort(pnt1 + 3 * n, pnt1 + 6 * n, compareX);
            std::sort(pnt1 + 6 * n, pnt1 + 9 * n, compareX);

            for (int k = 0; k < 9 * n; k++) {
                map[index] = pnt1[k].color2num();
                index++;
            }
        }
        else
            t--;
    }

    cap.release();

    destroyWindow("Rubix");
}
