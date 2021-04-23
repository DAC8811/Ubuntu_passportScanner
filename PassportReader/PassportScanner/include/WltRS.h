/*************************
照片解码库

记录：
2019/12/31 陈聪 创建
*************************/
#ifndef __WLTRS_H__
#define __WLTRS_H__

#include "globalMacro.h"

#define RAW_SIZE	38556
#define IN_SIZE		1024
#define OUT_SIZE	38862



#if CURRENT_FRAME == FRAME_ARM_32
/*************************************
 * 函数功能：照片解码。
 * 参数说明：pwlt - 原始数据；pbmp - 解码后的照片数据
 * 返回值：1 - 表示成功；其他 - 表示失败
 备注：对应库LibPhoto/其他公司的/libidr220s_reader-arm-32.so
 *************************************/
extern "C" int iDR220S_Dewlt(unsigned char* pwlt, unsigned char* pbmp);

#elif CURRENT_FRAME == FRAME_ARM_64
/************************************
函数名：unpack
功能：公安部照片解码接口,此接口不完善，调用后还需自己做处理
参数说明：
   char *src：wlt文件数据,1024字节
   char *dst：解析的RGB数据，102*126*3字节，可根据需求生成BMP或者JPG，图像数据BGR格式，需要将B、R值互换。
   int bmpSave：603: bmp file save,
               602: bmp file doesn't save（在内存读写）
               603\602是厂商唯一代码值，请妥善保存。
返回：1：正确
      0：bmpSave参数错误
  备注：对应库LibPhoto/华视照片解码库/libwlt2019.so
************************************/
extern "C" int unpack(char *src, char *dst, int bmpSave);

#elif CURRENT_FRAME == FRAME_X86_32
/************************************
函数名：Unpack
功能：解码bmp图片数据，可直接由原始数据转为bmp数据
参数说明：
   infile：wlt文件数据,1024字节
   Outfile：bmp图片缓冲区
   bufsize：wlt文件数据的长度
返回：输出图片的长度
备注：1.对应库LibPhoto/其他公司的/libwlt2bmp-x86-32.a
	  2.这个函数有点问题，bufsize不能给38862的长度，要给一个大于38862较多的长度才不崩溃
************************************/
extern "C" int Unpack(char *infile, char *Outfile, int bufsize); 

#elif CURRENT_FRAME == FRAME_X86_64
/************************************
函数名：unpack
功能：公安部照片解码接口,此接口不完善，调用后还需自己做处理
参数说明：
   char *src：wlt文件数据,1024字节
   char *dst：解析的RGB数据，102*126*3字节，可根据需求生成BMP或者JPG，图像数据BGR格式，需要将B、R值互换。
   int bmpSave：159: bmp file save,
               158: bmp file doesn't save（在内存读写）
               159\158是厂商唯一代码值，请妥善保存。
返回：1：正确
      0：bmpSave参数错误
 备注：对应库LibPhoto/其他公司的/libwlt-x86-64.so
************************************/
extern "C" int unpack(char *src, char *dst, int bmpSave);

#elif CURRENT_FRAME == FRAME_ARMHF
/************************************
函数名：WltToBmp
功能：解码bmp图片数据，可直接由原始数据转为bmp数据
参数说明：
	szWlt：wlt文件数据,1024字节
	szBmp：bmp图片缓冲区，38862字节
返回：1：正确
      0：错误
备注：1.对应库LibPhoto/其他公司的/libtermbhf-armhf.so
	  2.这个函数有点问题，bufsize不能给38862的长度，要给一个大于38862较多的长度才不崩溃
************************************/
extern "C" int WltToBmp(char* szWlt, char* szBmp);

#elif CURRENT_FRAME == FRAME_MIPS_64
extern "C" int WltToBmp(char* szWlt, char* szBmp);


#else
//待加入默认图片解码库

#endif


//BMP图片头部
const unsigned char bmpHeader[54] = {0x42, 0x4D, 0xCE, 0x97, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,\
						 0x00, 0x00, 0x66, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00,\
						 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
						 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

class WltRs
{
public:
	/****************************
	函数名：getBmp
	功能：bmp照片解码，调用公安部接口后，再进行转换
	参数：
		infile：输入原始数据 1024字节
		inBufsize: 输入原始数据长度
		Outfile：输出bmp图片数据
		outBufsize：Outfile的长度,成功返回输出图片的长度
	返回值：
		0：解析失败
		>0：输出图片的长度
		-2：传入参数为空指针或缓冲区大小不够
		-1：调用第三方照片解码接口失败
		-99：未知错误
	*****************************/
	static int getBmp(char *inBuf, const int &inBufsize, char *OutBuf, int &outBufsize); 	
};


#endif

