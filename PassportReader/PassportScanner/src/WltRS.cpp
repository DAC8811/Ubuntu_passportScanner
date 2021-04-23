#include "WltRS.h"
#include <string.h>
#include <iostream>

int WltRs::getBmp(char *inBuf, const int &inBufsize, char *OutBuf, int &outBufsize)
{
	if(!inBuf || !OutBuf || inBufsize < IN_SIZE || outBufsize < OUT_SIZE)
	{
#if DEBUG
		log::logPutDebug(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		return -2;
	}


/**************ARM-32**************/
#if CURRENT_FRAME == FRAME_ARM_32
	/***********************************************
	char cTransitionData[RAW_SIZE] = {0x00};
	
	int iRet = unpack(inBuf, cTransitionData, 602);
	if(1 != iRet)
	{
#if DEBUG
		log::logPutDebug(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		return -1;
	}

	//转换出来的数据再进行转换
	int iBmpPos = 0;
	int iTransitionPos = 0;
	memcpy(OutBuf, bmpHeader, sizeof(bmpHeader));
	iBmpPos += sizeof(bmpHeader);

	unsigned char temp;
	for(int i=0;i<RAW_SIZE;i+=3)
	{
		temp = cTransitionData[i];
		cTransitionData[i] = cTransitionData[i+2];
		cTransitionData[i+2] = temp;
	}

	for (int i=0;i<126;i++)
	{
		memcpy(OutBuf + iBmpPos, cTransitionData + iTransitionPos, 306);
		iBmpPos += 306;
		iTransitionPos += 306;
		
		OutBuf[iBmpPos++] = 0;
		OutBuf[iBmpPos++] = 0;
	}
	**********************************************/
	int iRet = iDR220S_Dewlt((unsigned char *)inBuf, (unsigned char*)OutBuf);
	if(iRet != 1)
	{
#if DEBUG
		log::logPutDebug(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		return -1;
	}
/**************ARM-32结束**************/

/**************ARM-64**************/
#elif CURRENT_FRAME == FRAME_ARM_64
	char cTransitionData[RAW_SIZE] = {0x00};
	
	int iRet = unpack(inBuf, cTransitionData, 602);
	if(1 != iRet)
	{
#if DEBUG
		log::logPutDebug(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		return -1;
	}

	//转换出来的数据再进行转换
	int iBmpPos = 0;
	int iTransitionPos = 0;
	memcpy(OutBuf, bmpHeader, sizeof(bmpHeader));
	iBmpPos += sizeof(bmpHeader);

	unsigned char temp;
	for(int i=0;i<RAW_SIZE;i+=3)
	{
		temp = cTransitionData[i];
		cTransitionData[i] = cTransitionData[i+2];
		cTransitionData[i+2] = temp;
	}

	for (int i=0;i<126;i++)
	{
		memcpy(OutBuf + iBmpPos, cTransitionData + iTransitionPos, 306);
		iBmpPos += 306;
		iTransitionPos += 306;
		
		OutBuf[iBmpPos++] = 0;
		OutBuf[iBmpPos++] = 0;
	}
/**************ARM-64结束**************/

/**************X86-32**************/
#elif CURRENT_FRAME == FRAME_X86_32
	char arrPhotoTemp[80000] = {0x00};	//此处大小必须要大于38862很多才不会奔溃
	int iRet = Unpack((char *)inBuf, arrPhotoTemp, IN_SIZE);
	if(0 == iRet)	//照片解析失败
	{
#if DEBUG
		log::logPutDebug(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		return -1;
	}

	if(outBufsize < iRet)
	{
#if DEBUG
		log::logPutDebug(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		return -2;
	}
	memcpy(OutBuf, arrPhotoTemp, iRet);
/**************X86-32结束**************/

/**************X86-64**************/
#elif CURRENT_FRAME == FRAME_X86_64
	char cTransitionData[RAW_SIZE] = {0x00};
	int iRet = unpack(inBuf, cTransitionData, 158);
	if(1 != iRet)
	{
#if DEBUG
		log::logPutDebug(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		return -1;
	}
	//转换出来的数据再进行转换
	int iBmpPos = 0;
	int iTransitionPos = 0;
	memcpy(OutBuf, bmpHeader, sizeof(bmpHeader));
	iBmpPos += sizeof(bmpHeader);

	unsigned char temp;
	for(int i=0;i<RAW_SIZE;i+=3)
	{
		temp = cTransitionData[i];
		cTransitionData[i] = cTransitionData[i+2];
		cTransitionData[i+2] = temp;
	}

	for (int i=0;i<126;i++)
	{
		memcpy(OutBuf + iBmpPos, cTransitionData + iTransitionPos, 306);
		iBmpPos += 306;
		iTransitionPos += 306;
		
		OutBuf[iBmpPos++] = 0;
		OutBuf[iBmpPos++] = 0;
	}
/**************X86-64结束**************/

/**************armhf**************/
#elif CURRENT_FRAME == FRAME_ARMHF
//这个库有点问题，会莫名其妙的导致崩溃
	char arrWltTemp[2048] = {0x00};
	char arrPhotoTemp[38862+1024] = {0x00};
	
	memcpy(arrWltTemp, inBuf, inBufsize);
	
	int iRet = WltToBmp(arrWltTemp, arrPhotoTemp);
	if(0 == iRet)
	{
#if DEBUG
		log::logPutDebug(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		return -1;
	}

	if(outBufsize < OUT_SIZE)
	{
#if DEBUG
		log::logPutDebug(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		return -2;
	}
	memcpy(OutBuf, arrPhotoTemp, OUT_SIZE);
/**************armhf结束**************/

/**************MIPS64**************/
#elif CURRENT_FRAME == FRAME_MIPS_64
	char arrWltTemp[2048] = {0x00};
	char arrPhotoTemp[38862+1024] = {0x00};
	
	memcpy(arrWltTemp, inBuf, inBufsize);
	
	int iRet = WltToBmp(arrWltTemp, arrPhotoTemp);
	if(0 == iRet)
	{
#if DEBUG
		log::logPutDebug(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		return -1;
	}

	if(outBufsize < OUT_SIZE)
	{
#if DEBUG
		log::logPutDebug(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		return -2;
	}
	memcpy(OutBuf, arrPhotoTemp, OUT_SIZE);
	
/**************MIPS64结束**************/

#else
	return -99;
#endif

#if DEBUG
	log::logPutDebug(__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	return outBufsize = OUT_SIZE;
}


