// vim: set tabstop=4 shiftwidth=4 expandtab fileencoding=utf-8
#ifndef DEMO_H_
#define DEMO_H_

#ifdef __cplusplus
extern "C"
{
#endif
    int CSDKInit(char *path, char *file);
    int CgetAPIversion(char *uri);
    int CgetWhiteImageURI(char *uri);
    int CgetIRImageURI(char *uri);
    int CgetUVImageURI(char *uri);
    int CgetSFZinfo(char *uri);
    int CgetSFZImageURI(char *uri);
    int CloadConfig();
    int CgenerateAndSaveConfig();
    int CinputDetect(int);
    int CgenerateAndSaveConfig();
    int CgetUSBData(int);
    int CgetUSBDataSFZ(int);
    int CgetUSBDataPassport(int);
    int CsaveImage();
    //证件类型
    //-1 - 错误
    // 0 - 未知
    // 1 - 身份证
    // 2 - 护照
    // 3 - 单行MRZ证卡
    // 4 - 三行MRZ证卡
    int CgetType();
    int CgetSFZImageURI(char *);
    int CgetOCRresult(char *);
    int CgetEChipImageURI(char *);
    int CgetEChipDG1(char *);
    int CgetEChipDG11(char *);
    int CSDKClose();

#ifdef __cplusplus
}
#endif

#endif //PASSPORTREADER_PASSPORTREADERAPI_H
