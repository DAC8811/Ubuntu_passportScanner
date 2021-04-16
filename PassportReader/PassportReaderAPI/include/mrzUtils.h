//
// Created by 张迪 on 2020/5/15.
//

#ifndef PASSPORTREADER_MRZUTILS_H
#define PASSPORTREADER_MRZUTILS_H

#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "utf8.h"

enum DOC_TYPE{
    UNKNOWN = -1,                 //未知
    ID_CARD = 0,                  //二代证
    PASSPORT = 3,                 //护照         2行
    PASSPORT_WITHOUT_CHIP = 6,
    HKMO_EXIT_ENTRY_PERMIT = 2,        //港澳通行证    1行
    HKMO_HOME_RETURN_PERMIT = 4,  //回乡证，港澳居民来往内地通行证    3行, 这个会在processHXZJson里面再进行区分
    HKMO_HOME_RETURN_PERMIT_NOCHIP = 7,  //无芯片旧版回乡证，港澳居民来往内地通行证    3行
    HK_HOME_RETURN_PERMIT = 47,
    MO_HOME_RETURN_PERMIT = 48,
    TW_HOME_RETURN_PERMIT = 49,     //台胞证，台湾居民来往大陆通行证   3行
    TAIWAN_PASSPORT = 5            //台湾通行证    1行机读码
};
enum OCR_TYPE{
    UNKNOWN_LINE = -1,
    ONE_LINE = 1,
    TWO_LINE = 2,
    THREE_LINE = 3
};
extern std::map<std::string, std::string> ETHNICITY;
extern std::map<std::string, std::string> GENDER;
/**************切割字符串的方法 ****************/
void split(const std::string &s, std::vector<std::string> &tokens, const std::string &delimiters = " ");
/*************将mrzCode中间的\n 剔除，得到一行字符串*****************/
std::string delN(std::string mrzCode);
/***********处理mrzCode的方法，得到的是一定格式的json字符串，读卡失败，OCR成功会调用***********/
std::string processMRZ(std::string mrzCode, DOC_TYPE docType, std::string headImage, std::string scanImage,std::string irImage,std::string uvImage, std::string uvImageBack);
/***********处理DG1,GD11的方法，得到的是一定格式的json字符串，读卡成功会调用***********/
std::string processDG(std::string DG1, std::string DG11, DOC_TYPE docType, std::string headImage, std::string scanImage,std::string irImage,std::string uvImage, std::string uvImageBack);
/***********处理身份证电子信息的方法****************/
std::string processIDCARDInfo(std::string sfzInfo, std::string headImage);

//港澳回乡证
std::string processHKMOHRPJson(std::string mrzCode, std::string DG11, std::string headImage, std::string scanImage, std::string irImage, std::string uvImage, DOC_TYPE docType, int chipStatus);
void parseName(std::string nameLine, std::string &firstName, std::string &lastName);
//护照
std::string processPassportJson(std::string mrzCode, std::string DG11, std::string headImage, std::string scanImage,std::string irImage,std::string uvImage,DOC_TYPE docType, int chipStatus);
//台湾居民往来大陆（台胞证）台湾回乡证
std::string processTWHRPJson(std::string mrzCode, std::string DG11, std::string headImage, std::string scanImage, std::string irImage, std::string uvImage, DOC_TYPE docType, int chipStatus);
//处理港澳台通行证
std::string processEEPJson(std::string mrzCode, std::string DG11, std::string headImage, std::string scanImage, std::string irImage, std::string uvImage, DOC_TYPE docType, int chipStatus);
std::vector<int> str2num1(std::string s);
bool PassportCheck(std::string number, char checkBit);
bool checkPassportMRZ(std::string mrzcode);
bool checkHKMOHRPMRZ(std::string mrzCode);
bool checkTWHRPMRZ(std::string mrzcode);
bool checkEEPMRZ(std::string mrzcode);
bool checkHKMOHRPOLDMRZ(std::string mrzCode);
void correctPassportMrz(std::string &mrzCode);
#endif //PASSPORTREADER_MRZUTILS_H
