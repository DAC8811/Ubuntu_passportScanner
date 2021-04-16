#pragma once

#include <string>
#include <opencv2/highgui/highgui.hpp>

//////////////////////////////////////////////////////////////////
/*-------------------��ȡ��д���ļ���ͷ�ļ�---------------------*/
//////////////////////////////////////////////////////////////////

class imageCoder {
public:

	imageCoder();
	~imageCoder();

	/*ͼ�����ģ��*/
	int img2code(cv::Mat img);	//The input img should be binary. 
	/*����ģ��*/
	int code2img();
	/*�ļ���ȡ��ģ��*/
	int exportCode(std::string filePath);
	/*�ļ�д���ģ��*/
	int importCode(std::string filePath);

	//private:
	int raw2rl();	//Raw code 2 run length code.
	int rl2raw();

	//private:
	cv::Mat m_rawImg;
	std::string m_rawCode;
	std::string m_rlCode;
	std::string m_head;  //The head include the information for height and width of the image.
};
