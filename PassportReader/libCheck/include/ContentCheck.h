#pragma once


#include <iostream> 
#include <cstring>
#include <string>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>  
#include "Country.h"
#include "ImageCode.h"
#include "FileProcess.h"
//#include "tchar.h"
#include "UVCheck.h"
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;
//////////////////////////////////////////////////////////////////
/*-----------------------�������ͷ�ļ�-------------------------*/
//////////////////////////////////////////////////////////////////
//������ɸ��������
extern "C"
{ 

	class  ContentCheck
	{
	public:
		//////////////////////////////////////////////////////////////////
		/*-------------------------����ģ��-----------------------------*/
		//////////////////////////////////////////////////////////////////
		/*�ɰ汾�ӿ�*/
		//int SourceSeperate(char* ImageLoc, char* nation, char* type, int mode);
		/*�°汾�ӿ�*/
		long long TrueResult(char* WIImageLoc, char* NIRImageLoc, char* UVImageLoc, char* nation, char* CodePath);
		int TrueResult(char* WIImageLoc, char* NIRImageLoc, char* UVImageLoc, char* nation, char* CodePath, int(&RCode)[14]);
		/*�°汾�ӿ�*/
		int SourceSeperate_New(char* WIImageLoc, char* NIRImageLoc, char* UVImageLoc, char* nation, char* CodePath, int(&RCode)[14]);
		/*�°汾�ӿ�*/
		int UVImageCheck(char* UVImageLoc);
	private:

		//////////////////////////////////////////////////////////////////
		/*------------------------�ڶ���ģ��----------------------------*/
		//////////////////////////////////////////////////////////////////

		/*-----------------------����ģ�鲿��---------------------------*/
		/*�������ͼ���л���������*/
		int Mode1_Data(Mat& src, int nation, int type, char* ImageLoc);
		/*�������ͼ���л��Ʋ�������α*/
		int Mode2_Data(Mat& src, int nation, int type, char* ImageLoc);
		/*�������ͼ����֤����*/
		int Mode3_Data(Mat& src, int nation, int type, char* ImageLoc);
		/*�������ͼ��������ʶ����Ϣ*/
		int Mode4_Data(Mat& src, int nation, int type, char* ImageLoc);
		/*�������ͼ����������Ƭ*/
		int Mode5_Data(Mat& src, int nation, int type, char* ImageLoc);
		/*�������ͼ�����������Ʊ���*/
		int Mode6_Data(Mat& src, int nation, int type, char* ImageLoc);
		/*�������ͼ����֤����ʶ*/
		int Mode7_Data(Mat& src, int nation, int type, char* ImageLoc);
		/*�������ͼ���л�����������ӫ����ά*/
		int Mode8_Data(Mat& src, int nation, int type, char* ImageLoc);//��ɫ
		int Mode9_Data(Mat& src, int nation, int type, char* ImageLoc);//����ɫ
		int Mode10_Data(Mat& src, int nation, int type, char* ImageLoc);//��ɫ
		int Mode11_Data(Mat& src, int nation, int type, char* ImageLoc);//��ɫ
		/*�������ͼ������Ƭ����ӫ����ά*/
		int Mode12_Data(Mat& src, int nation, int type, char* ImageLoc);//��ɫ
		int Mode13_Data(Mat& src, int nation, int type, char* ImageLoc);//����ɫ

		/*------------------------����ģ�鲿��--------------------------*/
		/*������ͼ���л�����Ĳ��ֱ���*/
		int Mode14_Data(Mat& src, int nation, int type, char* ImageLoc);
		/*������ͼ����֤����*/
		int Mode15_Data(Mat& src, int nation, int type, char* ImageLoc);
		/*������ͼ���и�����Ϣ*/
		int Mode16_Data(Mat& src, int nation, int type, char* ImageLoc);
		/*������ͼ���и�����Ƭ*/
		int Mode17_Data(Mat& src, int nation, int type, char* ImageLoc);
		/*������ͼ����֤����ʶ*/
		int Mode18_Data(Mat& src, int nation, int type, char* ImageLoc);
		/*�����������żУ��λ*/
		int Mode19_Data(char* MRZ);

		/*------------------------�ϲ�ģ�鲿��--------------------------*/
		/*������Ƭ���ģ�飺ģ��5��6�ĺϲ�ģ��*/
		int Mode_Mix_5_6(Mat& src, int nation, int type, char* ImageLoc);
		/*������������ӫ����ά���ģ�飺ģ��8��9��10�ĺϲ�ģ��*/
		int Mode_Mix_8_9_10_11(Mat& src, int nation, int type, char* ImageLoc);
		/*������Ƭ����ӫ����ά���ģ�飺ģ��11��12��13�ĺϲ�ģ��*/
		int Mode_Mix_12_13(Mat& src, int nation, int type, char* ImageLoc);

		//////////////////////////////////////////////////////////////////
		/*------------------------������ģ��----------------------------*/
		//////////////////////////////////////////////////////////////////

		/*------------�����������ģ�飨��������ͺ��⣩--------------*/
		/*����ͼ���л�������ģ��*/
		int MRZ_UV(const Mat& src, int select);
		/*����ͼ���л����벿�ֱ�����ģ��*/
		int Authenticator_NIR(const Mat& src);
		/*������У��λ���ģ��*/
		int MRZParityCheck1(int* MRZ, int start, int end);
		int MRZParityCheck2(int* MRZ);
		/*�������ֵ��ģ��*/
		int MRZ_UV_PROSCESS(const Mat& src, Mat& dst, int select);
		int MRZ2_UV_PROSCESS(const Mat& src, Mat& dst, int select);//��ʧЧ
		/*����ͼ���л������ָ���ģ��*/
		bool UV_ImageSegmentation(const Mat& src, Mat& dst1, Mat& dst2);
		/*����ͼ���л�����鴹ֱ�ָ�ģ��*/
		bool VerticalSegmentattion(const Mat& src, int* MatPro, Mat& dst, int param1, int param2);
		/*����ͼ���л������ˮƽ�ָ�ģ��*/
		bool HorizonSegmentattion(const Mat& src, int* MatPro, Mat& dst1, Mat& dst2);
		
		/*----------------------���Ƽ�����ģ��------------------------*/
		/*����ͼ���еĻ��Ƽ����ģ��*/
		int Pattern_UV(const Mat& src, int VALID_MAX, int VALID_MIN, int value);
		/*����ͼ���еĻ���ƥ��ģ��*/
		int PatternMtach_UV(Mat& src, int nation, char const* ImageLoc);
		/*����ͼ���еĻ�����ӫ����ά�б�ģ��*/
		int Pattern_Search_UV(const Mat& src);
		/*ͼ��ƥ��ģ��*/
		double ImageMatch(Mat src1, Mat src2);
		/*ͼ����ģ��*/
		int IFDO(Mat src, Mat& dst);
		/*����ͼ����ӫ����ά���ģ��*/
		int Thread_UV(Mat& src, int select);
		/*ӫ����ά��ֵ��ģ��*/
		int Thread_UV_Process(Mat& src, Mat& dst, int mode);
		/*���⻨�ƶ�ֵ��ģ��*/
		Mat Pattern_UV_PROSCESS(const Mat& src, int value);
		Mat Pattern_UV_PROCESS2(const Mat& src, int param1, int value, int mode);

		/*��ͬ�����������⻨�Ƽ��ģ��*/
		int Circle_Detect_USA(Mat & src);
		int Pattern_Check_CHN_E(Mat& src, int value);
		int Pattern_Check_CAN(Mat& src);
		int Pattern_Check_IDN(Mat& src);
		int Pattern_Check_PAN(Mat& src);
		int Pattern_Check_NPL(Mat& src);
		int Pattern_Check_HND(Mat& src);
		int Pattern_Check_MDA(Mat& src);
		int Pattern_Check_MUS(Mat& src);
		int Pattern_Check_BLZ(Mat& src);
		int Pattern_Check_AUS(Mat& src);
		int Pattern_Check_ARG(Mat& src);
		int Pattern_Check_BEL(Mat& src);
		int Pattern_Check_IRL(Mat& src);
		int Pattern_Check_GRC(Mat& src);
		int Pattern_Check_MAR(Mat& src);
		int Pattern_Check_LSO(Mat& src);
		int Pattern_Check_LIE(Mat& src);

		/*---------------------�������������ģ��----------------------*/
		/*����֤������ģ��*/
		int PassNum_UV(const Mat& src, int select1, int select2);
		/*�����������ģ��*/
		int Photo_Shape_UV(const Mat& src, int VALID_MAX, int VALID_MIN);
		/*����������Ƭ�������Ƽ��ģ��*/
		int Photo_BG_UV(const Mat& src, int VALID_MAX, int VALID_MIN);
		Mat PHOTO_UV_PROSCESS(const Mat& src);//��Ч
		int Photo_Color_UV(const Mat& src, int mode);//��Ч
		/*����������Ƭ����ӫ����ά���ģ��*/
		int Pattern_Thread_UV(const Mat& src, int select1, int select2, int select3);
		/*��������ʶ����Ϣ���ģ��*/
		int DATA_UV(const Mat& src);
		/*����֤����ʶ������֤���룩���ģ��*/
		int Pattern_Code_UV(const Mat& src);

		/*---------------------�������������ģ��----------------------*/
		/*��������ʶ����Ϣ���ģ��*/
		int DATA_NIR(const Mat& src);
		/*����֤������ģ��*/
		int PassNum_NIR(const Mat& src);
		/*�������ϼ��ģ��*/
		int FamilyName_NIR(const Mat& src);//��Ч
		/*����������Ƭ���ģ��*/
		int Photo_NIR(const Mat& src);
		/*����֤����ʶ���ģ��*/
		int Pattern_Code_NIR(const Mat& src);

		/*--------------------------�ײ�ģ��-----------------------------*/
		/*����ģ��*/
		int PointCount(const Mat& src);
		/*�ж�������Ч��ģ��*/
		bool CheckValid(const Mat& src, int ValidMax, int VAlidMin);


		/*�����������������ָ���ģ��*/
		bool AT_NIR_ImageSegmentation(const Mat& src, Mat& dst);
		/*����������������ˮƽ�ָ�ģ��*/
		bool AT_HorizonSegmentattion(const Mat& src, int* MatPro, Mat& dst, int param1, int param2);
		bool AT_HorizonSegmentattion2(const Mat& src, int* MatPro, Mat& dst, int param1, int param2);
		/*������������������ֱ�ָ�ģ��*/
		bool AT_VerticalSegmentattion(const Mat& src, int* MatPro, Mat& dst);
		

		/*����֤�������ָ���ģ��*/
		bool PN_UV_ImageSegmentation(const Mat& src, Mat& dst);
		/*����֤������ˮƽ�ָ�ģ��*/
		bool PN_HorizonSegmentattion(const Mat& src, int* MatPro, Mat& dst);
		

		/*����֤�������ָ���ģ��*/
		bool PN_NIR_ImageSegmentation(const Mat& src, Mat& dst);
		/*����֤������ˮƽ�ָ�ģ��*/
		bool PN_NIR_HorizonSegmentattion(const Mat& src, int* MatPro, Mat& dst);
		

		/*�����������ָ���ģ��*/
		bool FN_NIR_ImageSegmentation(const Mat& src, Mat& dst);
		/*������������ֱ�ָ�ģ��*/
		bool FN_VerticalSegmentattion(const Mat& src, int* MatPro, Mat& dst);		


		/*����ʶ����Ϣ���ָ���ģ��*/
		bool DATA_ImageSegmentation(const Mat& src, Mat& dst, int param1, int param2);


		/*ˮƽͶӰģ��*/
		void HorizonProjection(const Mat& src, int* dst);
		/*��ֱͶӰģ��*/
		void VerticalProjection(const Mat& src, int* dst);

		/*ͼ��Ҷ�����ģ��*/
		Mat ContrastStretch(Mat src);
		/*��������ʶ����Ϣ���Ķ�ֵ��ģ��*/
		Mat DATA_NIR_PROSCESS(const Mat& src);
		/*�������������Ķ�ֵ��ģ��*/
		Mat PHOTO_NIR_PROSCESS(const Mat& src);

		/*�ض���ɫͨ���µĶ�ֵ��ģ��*/
		int RGB_Red_Process(Mat& src, Mat& dst);//��ɫͨ��
		int RGB_Green_Process(Mat& src, Mat& dst);//��ɫͨ��
		int RGB_Blue_Process(Mat& src, Mat& dst);//��ɫͨ��
		int RGB_Black_Process(Mat& src, Mat& dst);//��ɫͨ��
		

		/*-------------------------���⸽��ģ��---------------------------*/
		/*�������������λģ��*/
		int Location_NIR(const Mat src, int& DstX, int& DstY);
		/*�������������λģ��*/
		int Location_UV(const Mat src, int& DstX, int& DstY, int select);


		/*��������Ϣ��ȡģ��*/
		int GetInfo(char* MRZ, char* nation, char* type);
		int DateDetect(int* num, char* date);//��Ч
		/*������ת��ģ��*/
		int NationDetect(char* nation);
		/*��������ת��ģ��*/
		int PassportType(char* type);
		
		
		/*ͼ��У��ģ��*/
		int Image_Modification(Mat& WIImg, Mat& UVImg, Mat& NIRImg);
		/*ͼ��ӳ��ģ��*/
		void ImageTransform(Mat const& src, Mat& dst, int dx, int dy);
		/*��ת�Ƕȼ���ģ��*/
		int GetTheta(Mat src, double & theta, int & dev);
		/*ͼ����תģ��*/
		Mat ImageRotate(Mat src, double theta);
		/*����������ֵ��ģ��*/
		Mat MRZ_NIR_PROSCESS(const Mat& src);
		
		/*ͼ�������Ϣ����ģ��*/
		int SaveError(char* ImageLoc, char* ImageName, Mat src, int PointX, int PointY, int width, int height);

		//int PatternMtach_UV(const Mat& src1, const Mat& src2);
		//int Pattern_Check_SAU(Mat& src);
		//int ImageSeg(const Mat& src, Mat& dst, int SegNum);
		//int HanmingDistance(string &str1, string &str2);
		//string pHashValue(Mat &src);
		//int Mode18_Data(Mat& src, int nation, int type);
		//int Mode_Select(int mode, Mat& src, int param1, int param2, int param3, int param4);

		//int CHN_E_DATA(int mode, Mat& src, Mat& dst, int PointX, int PointY, int& param1, int& param2, int& param3);
		//int CHN_G_DATA(int mode, Mat& src, Mat& dst, int PointX, int PointY, int& param1, int& param2, int& param3, int& param4);
		//int CHN_W_DATA(int mode, Mat& src, Mat& dst, int PointX, int PointY, int& param1, int& param2, int& param3);
		//int CHN_P_DATA(int mode, Mat& src, Mat& dst, int PointX, int PointY, int& param1, int& param2, int& param3);
		//int AIT_DATA(int mode, Mat& src, Mat& dst, int PointX, int PointY, int& param1, int& param2, int& param3, int& param4);
		//int NLD_DATA(int mode, Mat& src, Mat& dst, int PointX, int PointY, int& param1, int& param2, int& param3);
		//int USA_DATA(int mode, Mat& src, Mat& dst, int PointX, int PointY, int& param1, int& param2, int& param3);
		//int AUS_DATA(int mode, Mat& src, Mat& dst, int PointX, int PointY, int& param1, int& param2, int& param3);
		//int JPN_DATA(int mode, Mat& src, Mat& dst, int PointX, int PointY, int& param1, int& param2, int& param3);
		//double ssim(Mat &i1, Mat & i2);

		bool CHN_E(cv::Mat wi, cv::Mat uv, cv::Mat ir, char* mrz, int nationCode, int typeCode, int(&rCode)[14], char* CodePath);

		int PassportCodeAuthentication(cv::Mat wi, cv::Mat uv, cv::Mat ir, int mode);
		int MicroFaceAuthentication(cv::Mat wi, cv::Mat ir);

		bool PassportCodeArea(cv::Mat& wi, cv::Mat& uv, cv::Mat& ir);
		void MicroFaceArea(cv::Mat& wi, cv::Mat& ir);

		cv::Mat CHAR_WI_PROSCESS(const cv::Mat& src, int scale, int value, int mode = 1);
		cv::Mat CHAR_UV_REMOVE_COLOR(const cv::Mat& src, int scale, int value, int mode = 3);
		bool HorizonProjection_Vector(const cv::Mat& src, std::vector<int>& dst);
		bool BlackRemove_Vector(std::vector<int>& hp);
		bool HorizonSegmentation_Vector(std::vector<int>& hp, int& topEdge, int& bottomEdge);
		bool VerticalProjection_Vector(const cv::Mat& src, std::vector<int>& hp);
		bool VerticalSegmentation_Vector(std::vector<int>& vp, int& rightEdge, int& leftEdge);
		bool CharAreaFind(const cv::Mat& wi, int& topEdge, int& bottomEdge, int& rightEdge, int& leftEdge);
		bool CharAreaRsize(const cv::Mat& src, cv::Mat& wi, cv::Mat& uv, cv::Mat& ir);

		cv::Mat AreaRsize(const cv::Mat& src, int area[4]);
		cv::Mat CHAR_UV_PROSCESS_HSV(const cv::Mat& src, int mode);
		void RGBSplit(const cv::Mat& src, cv::Mat& dst, int select);
		void HSVequalize(cv::Mat& src);
	
	};
}