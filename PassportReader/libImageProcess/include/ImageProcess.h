//
// Created by 张迪 on 2020/3/31.
//

#ifndef PASSPORTREADER_IMAGEPROCESS_H
#define PASSPORTREADER_IMAGEPROCESS_H

#include <opencv2/opencv.hpp>

#include <string>
#include <iostream>
#include <fstream>

using cv::Mat;
using cv::Size;
using cv::Rect;
using std::fstream;
using std::string;

Mat edgeDetectionAny2(int &docType, Size &outputSize, Mat& inputIr);
Mat edgeDetectionAny(int &docType, Size &outputSize, Mat &inputWhite, Mat &inputIr, bool &back);//返回仿射变换矩阵
int PassportBorderCut(const Mat &input, Mat &output, Mat &AffineTransform, Size &outputSize, int & docType);

void serializeMat(const string &filename, Mat &mat);
void deserializeMat(Mat &mat, const string &filename);

int MergeImages(Mat &output, const Mat &imgLeft, const Mat &imgRight, const Mat &offset);

//int MergeImages(Mat &output, Mat &imgLeft, Mat &imgLeft2, Mat &imgRight, Mat &imgRight2, const Mat &offset);
int GenerateMask(Mat &output, const Mat &input);

int GenerateMaskColor(Mat &output, const Mat &input);

int ApplyMask(Mat &output, const Mat &offset);
int ApplyMaskColor(Mat &output, const Mat &offset);

Mat GenerateIrBin(const Mat &IrRefer);

Mat GenerateBin(const Mat &merged);

Mat ir_offset(Mat &img);
//方向对返回true，颠倒返回false
bool JudgeUproDown(const cv::Mat inputIr, const cv::Mat inputWhite);

Mat white_merge(const Mat &imgLeft, const Mat &imgRight);
#endif //PASSPORTREADER_IMAGEPROCESS_H
