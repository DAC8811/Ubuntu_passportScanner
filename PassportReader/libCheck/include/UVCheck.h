#pragma once

#include <iostream> 
#include <cstring>
#include <string.h>
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>  

using namespace cv;
using namespace std;

//////////////////////////////////////////////////////////////////
/*-------------------�������ͼ���ͷ�ļ�-------------------*/
//////////////////////////////////////////////////////////////////

/*������ά����*/
int ** CreateArray(int dim1, int dim2);
/*ע����ά����*/
void DeleteArray(int ** Array, int dim1);
/*ֱ��ͼ����*/
Mat ContrastStretch_New(Mat src);
/*����ͼ���е�ͼ�����ֽ�б�ģ��*/
int UV_Search(Mat& src);
/*����ͼ����ֵ��*/
Mat UV_PROSCESS(Mat& src, int value);
/*����ͼ�����*/
int UV_Check(Mat& src);

