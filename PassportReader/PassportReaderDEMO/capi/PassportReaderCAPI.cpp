// vim: set tabstop=4 shiftwidth=4 expandtab fileencoding=utf-8
#include "PassportReaderAPI.h"
#include "internalLogging.h"
#include "PassportReaderCAPI.h"

#include <iostream>

#include <unistd.h>

int CSDKInit(char *path, char *file)
{
    return SDKInit(path, file);
}
int CgetAPIversion(char *uri)
{
    strcpy(uri, getAPIversion().c_str());
    // printf("getAPIversion uri = %s\n",uri);
}

int CgetWhiteImageURI(char *uri)
{
    strcpy(uri, getWhiteImageURI().c_str());
    // printf("mygetWhiteImageURI uri = %s\n",uri);
}

int CgetIRImageURI(char *uri)
{
    strcpy(uri, getIRImageURI().c_str());
    // printf("mygetIRImageURI uri = %s\n",uri);
}

int CgetUVImageURI(char *uri)
{
    strcpy(uri, getUVImageURI().c_str());
    // printf("mygetUVImageURI uri = %s\n",uri);
}

int CgetSFZinfo(char *uri)
{
    strcpy(uri, getSFZinfo().c_str());
    // printf("mygetSFZinfo uri = %s\n",uri);
}

int CgetSFZImageURI(char *uri)
{
    strcpy(uri, getSFZImageURI().c_str());
    // printf("mygetSFZImageURI uri = %s\n",uri);
}

int CloadConfig()
{
    return loadConfig();
}

int CinputDetect(int cameraDetect)
{
    return inputDetect(cameraDetect);
}

int CgenerateAndSaveConfig()
{
    return generateAndSaveConfig();
}

int CgetUSBData(int captureImage)
{
    return getUSBData(captureImage);
}
int CgetUSBDataSFZ(int captureImage)
{
    return getUSBDataSFZ(captureImage);
}
int CgetUSBDataPassport(int captureImage)
{
    return getUSBDataPassport(captureImage);
}

int CsaveImage()
{
    return saveImage();
}
int CgetType()
{
    return getType();
}

int CgetOCRresult(char *uri)
{
    strcpy(uri, getOCRresult().c_str());
    // printf("getOCRresult uri = %s\n",uri);
}

int CgetEChipImageURI(char *uri)
{
    strcpy(uri, getEChipImageURI().c_str());
    // printf("getEChipImageURI uri = %s\n",uri);
}

int CgetEChipDG1(char *uri)
{
    strcpy(uri, getEChipDG1().c_str());
    // printf("getEChipDG1 uri = %s\n",uri);
}

int CgetEChipDG11(char *uri)
{
    strcpy(uri, getEChipDG11().c_str());
    // printf("getEChipDG11 uri = %s\n",uri);
}

int CSDKClose()
{
    int ret = SDKClose();
    return ret;
}
