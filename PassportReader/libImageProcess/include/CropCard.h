//
// Created by Phoenix on 2020/9/18.
//

#ifndef PASSPORTREADER_CROPCARD_H
#define PASSPORTREADER_CROPCARD_H

#include <opencv2/opencv.hpp>
#define TopOffset  25
#define LeftOffset  10
//#define PassportThreshold -5
cv::RotatedRect CropCard(cv::Mat oimg);

#endif //PASSPORTREADER_CROPCARD_H
