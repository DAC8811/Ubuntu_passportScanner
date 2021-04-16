//
// Created by Phoenix on 2020/9/18.
//

#include "CropCard.h"
#include <algorithm>
#include "internalLogging.h"


using namespace std;
using namespace cv;
//#define CROP_CARD_DEBUG_DISPLAY
#ifdef CROP_CARD_DEBUG_DISPLAY

void waitKey() {}

void destroyWindow(string) {}

void imshow(string name, Mat img) {
//    string testPath = "/sdcard/passport_lib/com.dscvlab.passportreader/";
    string testPath = "/sdcard/Android/data/com.dscvlab.ooxx.passportreader/files/";
    imwrite(testPath + name + ".jpg", img);
}

#endif

int sumOfSquares(const Point &pt1, const Point &pt2) {
    return (pt1.x - pt2.x) * (pt1.x - pt2.x) + (pt1.y - pt2.y) * (pt1.y - pt2.y);
}

//去掉突起，即找到最接近的两个凹陷点连接起来即可
vector<Point> removeHump(const vector<Point> &contour, const vector<int> &defectsIdx) {
    int minDist = INT_MAX;
    int startIdx;
    int endIdx;

    // Find nearest defects
    for (int i = 0; i < defectsIdx.size(); ++i) {
        for (int j = i + 1; j < defectsIdx.size(); ++j) {
            float dist = sumOfSquares(contour[defectsIdx[i]], contour[defectsIdx[j]]);
            if (minDist > dist) {
                minDist = dist;
                startIdx = defectsIdx[i];
                endIdx = defectsIdx[j];
            }
        }
    }
    // Check if intervals are swapped
    if (startIdx <= endIdx) {
        //int len11 = endIdx - startIdx;
        vector<Point> inside(contour.begin() + startIdx, contour.begin() + endIdx);
        int len1 = (inside.empty()) ? 0 : arcLength(inside, false);

        //int len22 = contour.size() - endIdx + startIdx;
        vector<Point> outside1(contour.begin(), contour.begin() + startIdx);
        vector<Point> outside2(contour.begin() + endIdx, contour.end());
        int len2 = (outside1.empty() ? 0 : arcLength(outside1, false)) +
                   (outside2.empty() ? 0 : arcLength(outside2, false));

        if (len2 < len1) {
            swap(startIdx, endIdx);
        }
    } else {
        //int len1 = startIdx - endIdx;
        vector<Point> inside(contour.begin() + endIdx, contour.begin() + startIdx);
        int len1 = (inside.empty()) ? 0 : arcLength(inside, false);


        //int len2 = contour.size() - startIdx + endIdx;
        vector<Point> outside1(contour.begin(), contour.begin() + endIdx);
        vector<Point> outside2(contour.begin() + startIdx, contour.end());
        int len2 = (outside1.empty() ? 0 : arcLength(outside1, false)) +
                   (outside2.empty() ? 0 : arcLength(outside2, false));

        if (len1 < len2) {
            swap(startIdx, endIdx);
        }
    }
    // Remove unwanted points
    vector<Point> out;
    if (startIdx <= endIdx) {
        out.insert(out.end(), contour.begin(), contour.begin() + startIdx);
        out.insert(out.end(), contour.begin() + endIdx, contour.end());
    } else {
        out.insert(out.end(), contour.begin() + endIdx, contour.begin() + startIdx);
    }

    return out;
}

RotatedRect CropCard(Mat oimg) {
    Mat cropedimg = oimg(Rect(LeftOffset, TopOffset, oimg.cols - LeftOffset * 2,
                              oimg.rows - TopOffset));//裁剪掉两边和上边干扰
    Mat img;
    cvtColor(cropedimg, img, COLOR_BGR2GRAY);
    //统计像素点
    int whiteHeight = 0;
    int minwhite = INT_MAX;
    int minindex = -1;
    for (int i = 0; i <= 50; i++) {
        uchar *data = img.ptr<uchar>(i);
        int lineWihte = 0;
        for (int j = 0; j < img.cols; j++) {
            if (data[j] >= 220)lineWihte++;
        }
        if (lineWihte < minwhite) {
            minwhite = lineWihte;
            minindex = i;
        }
    }
    whiteHeight = minindex + 2;
    cropedimg = cropedimg(Rect(0, whiteHeight, cropedimg.cols, cropedimg.rows - whiteHeight));

    Mat gray, image_blur, img_binary, image_open;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    cvtColor(cropedimg, gray, COLOR_BGR2GRAY);

    //平滑去噪
    blur(gray, image_blur, Size(5, 5));

    //二值化
    int img_threshold = threshold(image_blur, img_binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
    if (img_threshold < 20) {
        return RotatedRect();
    }
    morphologyEx(img_binary, img_binary, MORPH_CLOSE, Mat::ones(15, 15, CV_8UC1));

    findContours(img_binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//寻找轮廓

    //定位最大区块
    int max_size = -1;
    vector<Point> max_size_contour;
    for (vector<Point> contour : contours) {
        int size = contourArea(contour);
        if (size > max_size) {
            max_size = size;
            max_size_contour = contour;
#ifdef CROP_CARD_DEBUG_DISPLAY
            vector<vector<Point>> tmp = {contour};
            Mat testout;
            cropedimg.copyTo(testout);
            drawContours(testout, tmp, -1, Scalar(255, 0, 0), 3);
#endif // CROP_CARD_DEBUG_DISPLAY
        }
    }
    if (max_size == -1) return RotatedRect();
    vector<Point> pts = max_size_contour;
#ifdef CROP_CARD_DEBUG_DISPLAY
    Mat test;
    cvtColor(img_binary, test, COLOR_GRAY2BGR);
    {
        vector<vector<Point>> tmpContour = {pts};
        drawContours(test, tmpContour, -1, Scalar(255, 127, 0), 5);
    }
    imshow("最大轮廓", test);
    waitKey();
    destroyWindow("最大轮廓");
#endif // CROP_CARD_DEBUG_DISPLAY
    //以下是切除突出部分，即消除凸度缺陷
    //找到凸包，用于计算凸度缺陷
    vector<int> hullIdx;
    convexHull(pts, hullIdx, false);

#ifdef CROP_CARD_DEBUG_DISPLAY
    vector<Point> hull;
    convexHull(pts, hull, false);
    {
        vector<vector<Point>> tmp = {hull};
        drawContours(test, tmp, -1, Scalar(127, 255, 0), 5);
    }
    imshow("凸包", test);
    waitKey();
    destroyWindow("凸包");
#endif // CROP_CARD_DEBUG_DISPLAY

    vector<Vec4i> defects;
    sort(hullIdx.begin(), hullIdx.end(),
         [](int a, int b) { return a > b; });//必须排序，不然convexityDefects会crash
    convexityDefects(pts, hullIdx, defects);//找到凹陷处

    while (true) {
#ifdef CROP_CARD_DEBUG_DISPLAY
        Mat dbg;
        cvtColor(img_binary, dbg, COLOR_GRAY2BGR);
        vector<vector<Point>> tmp = {pts};
        drawContours(dbg, tmp, 0, Scalar(255, 127, 0), 5);
#endif // CROP_CARD_DEBUG_DISPLAY


        vector<int> defectsIdx;
        for (const Vec4i &v : defects) {
            float depth = float(v[3]) / 256.f;
            if (depth > 10) //找到比较深的凹陷点
            {
                defectsIdx.push_back(v[2]);

#ifdef CROP_CARD_DEBUG_DISPLAY
                int startidx = v[0];
                Point ptStart(pts[startidx]);
                int endidx = v[1];
                Point ptEnd(pts[endidx]);
                int faridx = v[2];
                Point ptFar(pts[faridx]);

                line(dbg, ptStart, ptEnd, Scalar(255, 0, 0), 5);
                line(dbg, ptStart, ptFar, Scalar(0, 255, 0), 5);
                line(dbg, ptEnd, ptFar, Scalar(0, 0, 255), 5);
                circle(dbg, ptFar, 4, Scalar(0, 255, 255), 5);
#endif // CROP_CARD_DEBUG_DISPLAY

            }
        }
#ifdef CROP_CARD_DEBUG_DISPLAY
        imshow("凸度缺陷", dbg);
        waitKey();
        destroyWindow("凸度缺陷");
#endif // CROP_CARD_DEBUG_DISPLAY

        if (defectsIdx.size() < 2)//缺陷点少于两个就不需要去掉凸起了
        {
            break;
        }

        //去掉突起，即找到最接近的两个凹陷点连接起来即可
        pts = removeHump(pts, defectsIdx);
        convexHull(pts, hullIdx, false);
        sort(hullIdx.begin(), hullIdx.end(), [](int a, int b) { return a > b; });
        convexityDefects(pts, hullIdx, defects);
    }


    RotatedRect box = minAreaRect(pts);//找到最终轮廓
#ifdef CROP_CARD_DEBUG_DISPLAY
    vector<vector<Point>> tmp = {max_size_contour};
    Mat testout;
    cropedimg.copyTo(testout);
    drawContours(testout, tmp, -1, Scalar(255, 0, 0), 3);
#endif // CROP_CARD_DEBUG_DISPLAY
    box.center = box.center + Point2f(LeftOffset, TopOffset + whiteHeight);//因为最开始有裁切，现在需要平移回去
    return box;
}