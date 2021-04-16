#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include <string>
//#include <iostream>
#include <fstream>
#include <time.h>

using cv::Mat;
using cv::Rect;
using cv::Size;
using std::fstream;
using std::string;

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

Mat white_merge(const Mat &imgLeft, const Mat &imgRight);

//HMODULE GetSelfModuleHandle();

#endif
