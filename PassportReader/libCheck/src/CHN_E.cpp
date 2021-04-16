//#include "CHN.h"
#include "ContentCheck.h"

const static int ValidCharMax = 4500;	//�ַ��������Чֵ�����ֵ
const static int ValidCharMin = 1500;	//�ַ��������Чֵ����Сֵ
const static int CharHeightMax = 45;	//�ַ�����Ŀ�ȵ����ֵ
const static int CharHeightMin = 20;	//�ַ�����Ŀ�ȵ���Сֵ
const static int CharWidthMax = 300;	//�ַ�����ĸ߶ȵ����ֵ
const static int CharWidthMin = 200;	//�ַ�����ĸ߶ȵ���Сֵ

const static int CharHeightOffsite = 5;	//�ַ�����ĸ߶ȵ��ض���
const static int CharWidthOffsite = 5;	//�ַ�����Ŀ�ȵ��ض���

/*���CHN���ҵ�E�ͻ��յ��������ģ��*/
bool ContentCheck::CHN_E(cv::Mat wi, cv::Mat uv, cv::Mat ir, char* mrz, int nationCode, int typeCode, int(&rCode)[14], char* CodePath)
{
	//MicroFaceAuthentication(wi, ir);

	//�����������ģ��Ľ��
	rCode[1] = Mode2_Data(uv, nationCode, typeCode, CodePath);

	rCode[8] = Mode14_Data(ir, nationCode, typeCode, CodePath);

	//rCode[9] = PassportCodeAuthentication(wi, uv, ir, 1);

	int doubleState = PassportCodeAuthentication(wi, uv, ir, 1);

	rCode[2] = doubleState % 10;

	rCode[9] = doubleState / 10;

	rCode[10] = Mode16_Data(ir, nationCode, typeCode, CodePath);

	rCode[13] = Mode19_Data(mrz);

	//for (auto m : rCode)
	//{
	//	std::cout << m << " ";	//��ӡ�����
	//}
	//std::cout << std::endl;

	return true;	//������
}

/*ͼ�����ȵ���ģ��*/
void ContentCheck::HSVequalize(cv::Mat& src)
{
	cv::Mat temp;
	medianBlur(src, temp, 3);
	cvtColor(temp, temp, CV_RGB2HSV);

	cv::Mat hsv[3];
	split(temp, hsv);
	//for (int i = 0; i < 3; i++)
	//{
	//	equalizeHist(imageRGB[i], imageRGB[i]);
	//}
	equalizeHist(hsv[2], hsv[2]);
	merge(hsv, 3, temp);
	cvtColor(temp, src, CV_HSV2RGB);

	return;
}

/*֤���������֤ģ��*/
int ContentCheck::PassportCodeAuthentication(cv::Mat wi, cv::Mat uv, cv::Mat ir, int mode)
{
	if (!PassportCodeArea(wi, uv, ir))	//�ָ�����
		return 2;

	//cv::imshow("��һ�ηָ�İ׹�ͼ��", wi);
	//cv::imshow("��һ�ηָ������ͼ��", uv);
	//cv::imshow("��һ�ηָ�ĺ���ͼ��", ir);

	//HSVequalize(wi);	//�����׹�ͼ������
	HSVequalize(uv);	//��������ͼ������
	//HSVequalize(ir);	//��������ͼ������

	//cv::imshow("��һ�ε����İ׹�ͼ��", wi);
	//cv::imshow("��һ�ε���������ͼ��", uv);
	//cv::imshow("��һ�ε����ĺ���ͼ��", ir);
	//cv::imwrite("��һ�ε����������ͼ��.jpg", uv);

	cv::Mat resultWI, resultUV, resultIR;

	//resultUV = CHAR_UV_REMOVE_COLOR(uv, 2, -70, 2);	//����ͼ���ֵ��
	//resultIR = CHAR_WI_PROSCESS(ir, 2, 70, 3);		//����ͼ���ֵ��
	resultWI = CHAR_WI_PROSCESS(wi, 4, 90, 3);			//�׹�ͼ���ֵ��
	//resultWI = CHAR_WI_PROSCESS(wi, 2, 70, 3);			//�׹�ͼ���ֵ��

	//cv::imshow("��һ�ζ�ֵ��ͼ��", resultWI);

	if (!CharAreaRsize(resultWI, wi, uv, ir)) //�ַ����طָ�
		return 2;
	//std::cout <//< std::endl;
	//std::cout <//< std::endl;

	//cv::imshow("�ڶ��ηָ�İ׹�ͼ��", wi);
	//cv::imshow("�ڶ��ηָ������ͼ��", uv);
	//cv::imshow("�ڶ��ηָ�ĺ���ͼ��", ir);

	resultWI = CHAR_WI_PROSCESS(wi, 2, 30, 3);			//�׹�ͼ���ֵ��
	resultUV = CHAR_UV_REMOVE_COLOR(uv, 2, -110, 2);	//����ͼ���ֵ��
	resultIR = CHAR_WI_PROSCESS(ir, 2, 40, 3);			//����ͼ���ֵ��

	//cv::imshow("��ֵ���İ׹�ͼ��", resultWI);
	//cv::imshow("��ֵ��������ͼ��", resultUV);
	//cv::imshow("��ֵ���ĺ���ͼ��", resultIR);

	//Mat resultChar = resultUV ^ resultIR;	//���⡢����ͼ��������

	//Mat openWind = getStructuringElement(MORPH_RECT, Size(3, 3));
	//morphologyEx(resultChar, resultChar, MORPH_OPEN, openWind);
	//�ղ���
	//Mat closeWind = getStructuringElement(MORPH_RECT, Size(3, 3));
	//morphologyEx(resultChar, resultChar, MORPH_CLOSE, closeWind);
	//cv::imshow("resultUV_OR_IR", resultChar);
	//resultChar = resultChar & resultWI;	//��������õ������ģ��������ٵ��ַ�ͼ��
	//cv::imshow("���⡢�������ͼ��", resultChar);

	int numWI = cv::countNonZero(resultWI);	//�׹�ͼ����Ч����
	int resultState1 = 5;
	int resultState2 = 5;
	switch (mode)	//���ͼ����Чֵ�Ƿ���Ϲ淶
	{
		case 1:
		{
			//std::cout << "resultWI" << std::endl;
			if (!CheckValid(resultWI, ValidCharMax, ValidCharMin))	//���׹��ֵ��ͼ��
			{
				resultState1 = 2;
				resultState2 = 2;
			}
			//std::cout << "resultUV" << std::endl;
			if (!CheckValid(resultUV, numWI * 4 / 5, numWI * 1 / 5)) //��������ֵ��ͼ��
			{
				resultState1 = 2;
			}
			else
			{
				resultState1 = 1;
			}
			//std::cout << "resultIR" << std::endl;
			if (!CheckValid(resultIR, numWI * 4 / 5, numWI * 1 / 5)) //�������ֵ��ͼ��
			{
				resultState2 = 2;
			}
			else
			{
				resultState2 = 1;
			}
			//std::cout << "resultChar" << std::endl;
			//if (!CheckValid(resultChar, ValidCharMax * 3 / 2, ValidCharMin))	//����ַ���ֵ��ͼ��
			//	return 2;

			//cout << "�׹����������ƶ�: " <<ImageMatch(resultWI, resultUV) << endl;
			//cout << "�׹�ͺ�������ƶ�: " << ImageMatch(resultWI, resultIR) << endl;
			break;
		}
		default:
			break;
	}

	//std::cout << "ͼ��ƥ����:" << std::endl;
	//if (ImageMatch(resultWI, resultChar) < 0.50)		//�ַ�ͼ����׹�ͼ��ƥ��
		//return 2;	//���ƶȲ�ƥ��

	return resultState1 + resultState2 * 10;	//���ƶ�ƥ��
}

/*΢����������֤ģ��*/
int ContentCheck::MicroFaceAuthentication(cv::Mat wi, cv::Mat ir)
{
	MicroFaceArea(wi, ir);	//�ָ�����

	//Mat resultWI = CHAR_WI_PROSCESS(wi, 2, -50, 3);	//�׹�ͼ���ֵ��
	//Mat resultIR = CHAR_WI_PROSCESS(ir, 2, 70, 2);	//����ͼ���ֵ��

	Mat resultWI ;
	cvtColor(wi, resultWI, CV_RGB2GRAY);
	//cv::imwrite("D:\\project\\�й�����\\�ָ�ͼ��.jpg", resultWI);

	//cv::imshow("resultWI", resultWI);
	//cv::imshow("resultIR", resultIR);

	return 1;	//ִ�гɹ�
}

/*֤����������ָ�ģ��*/
bool ContentCheck::PassportCodeArea(cv::Mat& wi, cv::Mat& uv, cv::Mat& ir)
{
	int pointX = 0, pointY = 0, width = 0, height = 0;
	if (Location_NIR(ir, pointX, pointY) != 1)	//��ȡ�ο����������
		return false;

	//�������ꡢ����Ȳ���
	//pointX = ((pointX + 770) > 1250) ? 950 : (pointX + 770);
	//pointY = ((pointY - 730) < 0) ? 0 : (pointY - 730);
	//width = ((1250 - pointX) > 370) ? 370 : (1250 - pointX);
	//height = ((900 - pointY) > 160) ? 160 : (900 - pointY);

	pointX = ((pointX + 760) > 1250) ? 950 : (pointX + 760);
	pointY = ((pointY - 710) < 0) ? 0 : (pointY - 710);
	width = ((1250 - pointX) > 370) ? 370 : (1250 - pointX);
	height = ((900 - pointY) > 180) ? 180 : (900 - pointY);

	//�ڰ׹⡢���⡢����ͼ���зָ����Ӧ������
	Mat segWI(wi, Rect(pointX, pointY, width, height));
	Mat segUV(uv, Rect(pointX, pointY, width, height));
	Mat segIR(ir, Rect(pointX, pointY, width, height));

	if (segWI.empty() || segUV.empty() || segIR.empty())
		return false;

	//����ʾ��Ӧ������
	//cv::imshow("SegWI", segWI);
	//cv::imshow("SegUV", segUV);
	//cv::imshow("SegIR", segIR);

	//���طָ�������
	wi = segWI.clone();
	uv = segUV.clone();
	ir = segIR.clone();

	return true;
}

/*΢����������ָ�ģ��*/
void ContentCheck::MicroFaceArea(cv::Mat& wi, cv::Mat& ir)
{
	int pointX = 0, pointY = 0, width = 0, height = 0;
	int check = Location_NIR(ir, pointX, pointY);	//��ȡ�ο����������

	//�������ꡢ����Ȳ���
	pointX = ((pointX + 950) > 1250) ? 950 : (pointX + 950);
	pointY = ((pointY - 580) < 0) ? 0 : (pointY - 580);
	width = ((1250 - pointX) > 260) ? 260 : (1250 - pointX);
	height = ((900 - pointY) > 280) ? 280 : (900 - pointY);

	//�ڰ׹⡢���⡢����ͼ���зָ����Ӧ������
	Mat segWI(wi, Rect(pointX, pointY, width, height));
	Mat segIR(ir, Rect(pointX, pointY, width, height));

	//����ʾ��Ӧ������
	//cv::imshow("SegWI", segWI);
	//cv::imshow("SegIR", segIR);

	wi = segWI.clone();
	ir = segIR.clone();
}

/*ͼ��RGBͨ������ģ��*/
void ContentCheck::RGBSplit(const cv::Mat& src, cv::Mat& dst, int select)
{
	vector<Mat> rgb;

	split(src, rgb); //ͨ������

	//imshow("R", rgb[2]);
	dst = rgb[select].clone();
}

/*�׹�ͼ���ַ�������ģ��*/
Mat ContentCheck::CHAR_WI_PROSCESS(const cv::Mat& src, int scale, int value, int mode)
{
	Mat single;
	switch (mode)
	{
		case 0:
		case 1:
		case 2:
		{
			RGBSplit(src, single, mode);
			break;
		}
		case 3:
			cvtColor(src, single, CV_RGB2GRAY);	//�ҶȻ�
			break;
		default:
			cvtColor(src, single, CV_RGB2GRAY);	//�ҶȻ�
			break;
	}

	Mat temp;
	medianBlur(single, temp, 3);	//��ֵ�˲�
	//imshow("��ֵ�˲����ͼ��", temp);

	temp = ContrastStretch(temp);	//ֱ��ͼ����	
	//imshow("�����ͨ��ͼ��", temp);

	int pointMin = (temp.rows > temp.cols) ? temp.cols : temp.rows;	//���ô��ڴ�С

	//int blockSize = 2 * (pointMin / 8) + 1;
	//int constValue = 30;
	int blockSize = 2 * (pointMin / scale) + 1;	//���ô��ڴ�С
	int constValue = value;	//�̶�ֵ
	Mat resultImage;
	adaptiveThreshold(temp, resultImage, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, blockSize, constValue);	//��ֵ��

	return resultImage;		//���ض�ֵ��ͼ��
}

/*�ַ������ض���ɫȥ����ģ��*/
cv::Mat ContentCheck::CHAR_UV_REMOVE_COLOR(const cv::Mat& src, int scale, int value, int mode)
{
	cv::Mat red = Pattern_UV_PROCESS2(src, scale, value, 2);	//��ɫͨ���µ�ͼ��

	//Mat green = Pattern_UV_PROCESS2(src, scale , value / 4, 1);	//��ɫͨ���µ�ͼ��

	cv::Mat green = Pattern_UV_PROCESS2(src, scale, value, 1);	//��ɫͨ���µ�ͼ��

	//Mat blue = CHAR_WI_PROSCESS(src , scale, - value / 10, 0);	//��ɫͨ���µ�ͼ��


	//Mat singleResult = (cv::countNonZero(green) > (cv::countNonZero(red))) ? red : (red - ((cv::countNonZero(blue) > (5 * cv::countNonZero(green))) ? green : (green - blue)));	//����ɫ��ͼ��

	//������
	Mat openWind = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(green, green, MORPH_OPEN, openWind);
	//�ղ���
	Mat closeWind = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(green, green, MORPH_CLOSE, closeWind);

	cv::Mat singleResult = red - green;

	//std::cout << "���ͼ����Чֵ:" << cv::countNonZero(red) << std::endl;
	//std::cout << "����ͼ����Чֵ:" << cv::countNonZero(blue) << std::endl;
	//std::cout << "�̹�ͼ����Чֵ:" << cv::countNonZero(green) << std::endl;
	//cv::imshow("��ɫͨ���Ķ�ֵ��ͼ��", red);
	//cv::imshow("��ɫͨ���Ķ�ֵ��ͼ��", green);
	//cv::imshow("��ɫͨ���Ķ�ֵ��ͼ��", blue);
	//cv::imshow("ͨ�����ͼ��", singleResult);

	//������
	morphologyEx(singleResult, singleResult, MORPH_OPEN, openWind);
	//�ղ���
	morphologyEx(singleResult, singleResult, MORPH_CLOSE, closeWind);

	return singleResult;
}


/*vector���ˮƽͶӰģ��*/
bool ContentCheck::HorizonProjection_Vector(const cv::Mat& src, std::vector<int>& hp)
{
	//std::cout << "����ˮƽͶӰģ��" << std::endl;

	if (src.empty() || hp.size() != src.rows || src.channels() != 1) //��鴫�������Ƿ�ϸ�
		return false;

	const uchar* p;

	//std::cout << "��ʼˮƽͶӰ" << std::endl;
	for (int i = 0; i < src.rows; i++)
	{
		hp[i] = 0;	//����
		p = src.ptr<uchar>(i);
		for(int j = 0; j < src.cols; j++)
		{
			if(p[j] != 0)
				++hp[i];	//��Ч�����

		}
	}
	//std::cout << "����ˮƽͶӰ" << std::endl;

	return true;
}

/*vector��ͼ��ڱ���������ģ��*/
bool ContentCheck::BlackRemove_Vector(std::vector<int>& src)
{
	//std::cout << "����ˮƽͶӰģ��" << std::endl;

	if (src.empty()) //��鴫�������Ƿ�ϸ�
		return false;

	int num = src.size();
	int black = num * 9 / 10;

	//std::cout << "��ʼ����������" << std::endl;
	for (int m = 0; m < num; m++)
	{
		if (src[m] >= black)
			src[m] = 0;
	}
	//std::cout << "��������" << std::endl;

	return true;
}

/*vector���ˮƽ�ָ�ģ��*/
bool ContentCheck::HorizonSegmentation_Vector(std::vector<int>& hp, int& topEdge, int& bottomEdge)
{
	//std::cout << "����ˮƽ�ָ�ģ��" << std::endl;

	if (hp.size() == 0 ) //��鴫�������Ƿ�ϸ�
		return false;

	//std::cout << "��ʼˮƽ�ָ�" << std::endl;
	size_t aver = std::accumulate(hp.begin(), hp.end(), 0.0);
	aver = aver * 2 / (3 * hp.size());//�����ֵ
	//aver = aver * 3 / (5 * hp.size());//�����ֵ
	//std::cout << "ˮƽͶӰ��ƽ��ֵ:" << aver << std::endl;

	topEdge = 0, bottomEdge = 0;
	for (auto start = hp.rbegin(); true;)
	{
		auto n = find_if(start, hp.rend(), [&aver](int& i) {return (i > aver); });	//�����ַ����±߽�
		//std::cout << "�ַ����±߽�:" << hp.rend() - n << std::endl;
		if (n == hp.rend())
			break;
		auto m = find_if(n, hp.rend(), [&aver](int& i) {return (i <= aver); });	//�����ַ����ϱ߽�
		//std::cout << "�ַ����ϱ߽�:" << hp.rend() - m << std::endl;
		if (m == hp.rend())
			break;

		//std::cout << "�ַ����߶�:" << m - n << std::endl;
		if (m - n > CharHeightMin && m - n < CharHeightMax)	//����ַ����߽��Ƿ�ϸ�
		{
			topEdge = hp.rend() - m;	//�ַ����ϱ߽�
			bottomEdge = hp.rend() - n; //�ַ����±߽�
			break;
		}
		start = m;
	}
	//std::cout << "����ˮƽ�ָ�" << std::endl;
	if (!topEdge && !bottomEdge)
	{
		return false;
	}
	return true;
}

/*vector��Ĵ�ֱͶӰģ��*/
bool ContentCheck::VerticalProjection_Vector(const cv::Mat& src, std::vector<int>& dst)
{
	//std::cout << "���봹ֱͶӰģ��" << std::endl;
	if (src.empty() || dst.size() != src.cols || src.channels() != 1) //��鴫�������Ƿ�ϸ�
		return false;

	const uchar* p;

	//std::cout << "��ʼ��ֱͶӰ" << std::endl;
	for (int i = 0; i < src.cols; i++)
	{
		dst[i] = 0;	//����
		for (int j = 0; j < src.rows; j++)
		{
			p = src.ptr<uchar>(j);
			if (p[i] != 0)
				++dst[i];	//��Ч�����
		}
	}
	//std::cout << "������ֱͶӰ" << std::endl;
	return true;
}

/*vector��Ĵ�ֱ�ָ�ģ��*/
bool ContentCheck::VerticalSegmentation_Vector(std::vector<int>& vp, int& leftEdge, int& rightEdge)
{
	//std::cout << "���봹ֱ�ָ�ģ��" << std::endl;

	if (vp.size() == 0) //��鴫�������Ƿ�ϸ�
		return false;

	//std::cout << "��ʼ��ֱ�ָ�" << std::endl;
	int aver = static_cast<int>(std::accumulate(vp.begin(), vp.end(), 0.0) / vp.size());	//�����ֵ
	//std::cout << "��ֱͶӰ��ƽ��ֵ:" << aver << std::endl;

	leftEdge = 0, rightEdge = 0;

	auto n = find_if(vp.begin(), vp.end(), [&aver](int& i) {return (i > aver); });	//�����ַ����±߽�
	//std::cout << "�ַ����±߽�:" << n - vp.begin() << std::endl;
	if (n == vp.end())
		return false;
	auto m = find_if(vp.rbegin(), vp.rend(), [&aver](int& i) {return (i > aver); });	//�����ַ����ϱ߽�
	//std::cout << "�ַ����ϱ߽�:" << vp.rend() - m << std::endl;
	if (m == vp.rend())
		return false;

	//std::cout << "������ֱ�ָ�" << std::endl;

	//std::cout << "�ַ������:" << (vp.rend() - m) - (n - vp.begin()) << std::endl;
	if (((vp.rend() - m) - (n - vp.begin())) > CharWidthMin && ((vp.rend() - m) - (n - vp.begin())) < CharWidthMax)	//����ַ����߽��Ƿ�ϸ�
	{
		leftEdge = n - vp.begin();	//�ַ����ϱ߽�
		rightEdge = vp.rend() - m; //�ַ����±߽�
		return true;
	}
	return false;
}

/*�ַ��������ģ��*/
bool ContentCheck::CharAreaFind(const cv::Mat& src, int& topEdge, int& bottomEdge, int& leftEdge, int& rightEdge)
{
	//std::cout << "�����ַ��������ģ��" << std::endl;
	std::vector<int> hp(src.rows, 0);	//ˮƽͶӰ�����ݼ�

	if (!HorizonProjection_Vector(src, hp))	//ˮƽͶӰ
		return false;

	if (!BlackRemove_Vector(hp))
		return false;

	if (!HorizonSegmentation_Vector(hp, topEdge, bottomEdge))	//ˮƽ�ָ�
		return false;

	cv::Mat segSrc(src, Rect(0, topEdge, src.cols, bottomEdge - topEdge));
	//imshow("ˮƽ�ָ���ͼ��", segSrc);

	std::vector<int> vp(segSrc.cols, 0);
	if (!VerticalProjection_Vector(segSrc, vp))	//��ֱͶӰ
		return false;

	if (!VerticalSegmentation_Vector(vp, leftEdge, rightEdge))
		return false;

	//cv::Mat resultWI(segWI, Rect(leftEdge, 0, rightEdge - leftEdge, segWI.rows));
	//imshow("��ֱ�ָ���ͼ��", resultWI);
	//std::cout << "�����ַ��������ģ��" << std::endl;

	return true;
}


/*�ַ����ض�λģ��*/
bool ContentCheck::CharAreaRsize(const cv::Mat& src, cv::Mat& wi, cv::Mat& uv, cv::Mat& ir)
{
	if (src.empty() || wi.empty() || uv.empty() || ir.empty())	//��������Ƿ�Ϊ��
		return false;

	//std::cout << "�����ַ������ض���ģ��" << std::endl;
	int area[4];	//�ַ�����߽�
	int temp[4];
	if (!CharAreaFind(src, area[0], area[1], area[2], area[3])) //�����ַ��߽�����
		return false;

	temp[0] = area[0];
	temp[1] = area[1];
	temp[2] = area[2];
	temp[3] = area[3];
	cv::Mat resultWI = AreaRsize(wi, temp);
	//cv::imshow("�׹���ͼ��", resultWI);

	temp[0] = (3 * area[0] - area[1]) / 2;
	temp[1] = (area[0] + area[1]) / 2;
	cv::Mat resultUV = AreaRsize(uv, temp);
	//cv::imshow("������ͼ��", resultUV);

	temp[0] = (area[0] + area[1]) / 2;
	temp[1] = (3 * area[1] - area[0]) / 2;
	cv::Mat resultIR = AreaRsize(ir, temp);
	//cv::imshow("������ͼ��", resultIR);

	if(resultWI.empty() || resultUV.empty() || resultIR.empty())
		return false;

	wi = resultWI.clone();
	uv = resultUV.clone();
	ir = resultIR.clone();

	//std::cout << "�����ַ������ض���ģ��" << std::endl;
	return true;
}

/*�ַ����ض�λģ��*/
cv::Mat ContentCheck::AreaRsize(const cv::Mat& src, int area[4])
{
	area[0] = (area[0] - CharHeightOffsite > 0) ? (area[0] - CharHeightOffsite) : 0; //�ϱ߽�����
	area[1] = (area[1] + CharHeightOffsite < src.rows - 1) ? (area[1] + CharHeightOffsite) : (src.rows - 1); //�±߽�����
	area[2] = (area[2] - CharWidthOffsite > 0) ? (area[2] - CharWidthOffsite) : 0; //��߽�����
	area[3] = (area[3] + CharWidthOffsite < src.cols - 1) ? (area[3] + CharWidthOffsite) : (src.cols - 1); //�ұ߽�����

	cv::Mat result(src, Rect(area[2], area[0], area[3] - area[2], area[1] - area[0]));
	//cv::imshow("�׹���ͼ��", resultWI);

	//std::cout << "�����ַ������ض���ģ��" << std::endl;
	return result.clone();
}

cv::Mat ContentCheck::CHAR_UV_PROSCESS_HSV(const cv::Mat& src, int mode)
{
	int HL, HH, SL, SH, VL, VH;

	switch (mode)
	{
	case 1://red
	{
		HL = 130;
		HH = 180;
		SL = 80;
		SH = 255;
		VL = 50;
		VH = 255;
		break;
	}
	case 2://red
	{
		HL = 0;
		HH = 20;
		SL = 130;
		SH = 255;
		VL = 60;
		VH = 255;
		break;
	}
	default:return src; break;
	}

	Mat imageHSV;
	vector<Mat> hsv;
	cvtColor(src, hsv, COLOR_BGR2HSV);


	split(imageHSV, hsv);
	//equalizeHist(HSVSplit[2], HSVSplit[2]);
	//equalizeHist(HSVSplit[1], HSVSplit[1]);
	merge(hsv, imageHSV);


	Mat result;

	inRange(imageHSV, Scalar(HL, SL, VL), Scalar(HH, SH, VH), result);
	//imshow("ImageHSV3 Image", ResultImage);

	Mat element = getStructuringElement(MORPH_RECT, Size(2, 2));
	//Mat element = getStructuringElement(MORPH_RECT, Size(4, 4));
	morphologyEx(result, result, MORPH_OPEN, element);
	//Mat element1 = getStructuringElement(MORPH_RECT, Size(7, 7));
	Mat element1 = getStructuringElement(MORPH_RECT, Size(2, 2));
	morphologyEx(result, result, MORPH_CLOSE, element1);
	//imshow("ResultImage Image", ResultImage);

	hsv.clear();
	hsv.shrink_to_fit();

	return result;
}