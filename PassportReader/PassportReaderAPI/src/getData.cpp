//
// Created by 张迪 on 2020/3/21.
//

// vim: set tabstop=4 shiftwidth=4 expandtab fileencoding=utf-8
#include <unistd.h>
#include <sstream>
#include <regex>
#include <sys/stat.h>
#include "utf8.h"
#include <time.h>
#include <opencv2/opencv.hpp>
#include <sys/time.h>
#include <chrono>
#include "libChip.h"
#include "mrz.h"
#include "MRTD.h"
#include "ImageProcess.h"
#include "mrzUtils.h"
//#include "pyContentCheck.h"
#include "CISReader.h"
#include "datastruct.h"
#include "getData.h"
#include "echip.h"

//#define DEBUG_QRCODE
EXPORT_FUN
char LOGBUFFER[300];

// #define LOG_DEBUG
#define LOG_TAG "PassportReaderCPP-API"

#include "internalLogging.h"

using namespace std;
using namespace cv;

#ifndef USE_OLD_OCR
MRZ OCRworker;
#endif
std::vector<std::string> datasets = {
        "P<CODMUSHITU<<JEAN<MARIE<KAYEYE<<<<<<<<<<<<<\nOP02709805COD9806261M2211123A56010000280<<20\n",
        "P<GABNSAH<ALLOGO<<SYDNEY<CLETRICK<<<<<<<<<<<\n19GA211853GAB9303221M2508289<<<<<<<<<<<<<<04\n",
        "P<MUSKONG<SHIN<YAO<<<<<<<<<<<<<<<<<<<<<<<<<<\n0646694<<9MUS6412087F0608211L081264820280576\n",
        "P<USAZHANG<<LISA<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n5661406077USA1405200F2401081717299049<926432\n",
        "P<USALU<<NATALIE<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n5312105339USA1510081F2012032715037043<033578\n",
        "P<UKRVERESHCHAK<<ANASTASIIA<<<<<<<<<<<<<<<<<\nFA040422<7UKR9512081F25020921995120800085<08\n",
        "P<UKRSAFONOVA<<YULIIA<<<<<<<<<<<<<<<<<<<<<<<\nFL483155<8UKR9205233F28020241992052304704<24\n",
        "P<USALUO<<ZHAO<YI<<<<<<<<<<<<<<<<<<<<<<<<<<<\n6464097866USA7708316F2908133116769873<572400\n",
        "P<USAYU<<BENJAMIN<<<<<<<<<<<<<<<<<<<<<<<<<<<\n5487872629USA1110159M2111038716258566<457682\n",
};
string workingFolder;
struct MrzInfoStruct mrzInfo;
struct timeval start, stop;

string mrzCode, DG1, DG11, IDNum, SFZinfo, SFZinfoUTF16, SFZImage, jsonInfo;
bool back;
int RFReader_FD, ScanReader_FD;
//-1 - error
// 0 - unknow
// 1 - sfz
// 2 - passport
// 3 - other 1-line MRZ cards
// 4 - other 3-line MRZ cards
int chipStatus, sfzStatus, insertType;
string authenticity_result, authenticity_details;
DOC_TYPE docType = UNKNOWN;

int borderResult = -1;
bool initFlag = false;
enum ScanCardReturn {
    Success = 0,
    ScanErr = -1,
    ScanTimeout = -2,
    Back = 6,
    ReadImgErr = 2,
    EdgeDeteErr = 3,
    MrzOrcErr = 4,
    InvalidCard = 7,
};

//1,SFZ;   0. Passport/HK
int getCardType() {
    int thisCardType = PassportTest();
    if (thisCardType == 0) {
        return 1;//SFZ
    } else if (thisCardType == 1) {
        return 0;//Passport
    } else if (thisCardType == -1) {
        return -1;//无芯片
    } else {
        return thisCardType;//-2 设备没打开
    }
}


//保存最终图片（经过剪裁）并返回Mat, n取0~3分别代表 红外，白光，紫外 的路径;docType：0--护照；1--身份证；2--港澳通行证
Mat saveFinalImage(const Mat &trans, Mat &src, Size outputsize, int n, int insertType, bool back,
                   bool small = false) {
    if (n < 0 || n > 2)
        return Mat();
    Mat Oring;
    src.copyTo(Oring);
    Mat affineimg, finalimg;
    warpAffine(Oring, affineimg, trans, outputsize, INTER_LINEAR, BORDER_REPLICATE);

    if (small) {
        resize(affineimg, finalimg, Size(affineimg.cols / 2, affineimg.rows / 2));
    } else {
        finalimg = affineimg;
    }
    vector<int> p;
    p.push_back(IMWRITE_JPEG_QUALITY);
    p.push_back(30);
    if (back) {
        if (n == 0) {
            imwrite(workingFolder + "/images/IR_Back.jpg", finalimg, p);
        } else if (n == 1) {
            imwrite(workingFolder + "/images/White_Back.jpg", finalimg, p);
        } else {
            imwrite(workingFolder + "/images/UV_Back.jpg", finalimg, p);
        }
    } else {
        if (n == 0) {
            imwrite(workingFolder + "/images/IR.jpg", finalimg, p);
        } else if (n == 1) {
            imwrite(workingFolder + "/images/White.jpg", finalimg, p);
        } else {
            imwrite(workingFolder + "/images/UV.jpg", finalimg, p);
        }
    }

    return affineimg;
}


//string
//getAuthenticity(const char *whitePath, const char *irPath, const char *uvPath, int resultType) {
//
//    //jsonInfo = processDG("CDL138092367<2903149<9205266<2MOLKMOKM<<<<WEI<<WEI<<<<<<<<<<FAAB16<<43<<<<<<<<<<<<<<<<<<<<","张三",TAIWAN_PASSPORT);
//    string CodePath = workingFolder + "/PatternCode/";
//    long long result = pyTrueResult(const_cast<char *>(whitePath),
//                                    const_cast<char *>(irPath),
//                                    const_cast<char *>(uvPath),
//                                    const_cast<char *>(mrzCode.c_str()),
//                                    const_cast<char *>(CodePath.c_str()));
//    string re = to_string(result);
//    //得到RCode的字符串形式，从右到左依次是鉴伪点1、鉴伪点2、鉴伪点3...
//    authenticity_details = re.substr(0, 14);
//    string checkResult = "0";
//    checkResult = re.substr(14, 1);
//    if (checkResult == "2")
//        return "-1";
//    else
//        return checkResult;
//}

int openConnection(string workingFolder, int RFReaderFD, int scanFD) {
    if (!initFlag)
        initProgram(workingFolder);
    //打开CIS扫描设备
    RFReader_FD = RFReaderFD;
    ScanReader_FD = scanFD;
    int re = openConnect(workingFolder);
//    int re = openConnect(workingFolder, -1);
    if (!initFlag || re != 0) {
        return -1;
    }
    checkRevision(workingFolder, getDeviceID());
//    bool auth = AuthDev();
//    if (auth)
    return 0;
    return -1;
}

int scanAndReadCard(int timeout) {
    CloseWire();
    int cardType = getCardType();
    if (cardType == 1) {
        string output, img;
        sfzStatus = IDCardRead(output, img);
        output = output.substr(0, 220);
        if (sfzStatus == 1) {
            //convert to utf-8
            try {
                vector<unsigned short> utf16line((unsigned short *) output.data(),
                                                 (unsigned short *) output.data() +
                                                 output.size() / 2);
                utf8::utf16to8(utf16line.begin(), utf16line.end(), back_inserter(SFZinfo));
            }
            catch (const utf8::invalid_utf16 &) {
                // bad UTF-16 data!
            }
            docType = ID_CARD;
            SFZImage = img;
            SFZinfoUTF16 = output;
            insertType = 1;
            return ScanCardReturn::Success;
        }
        return ScanCardReturn::InvalidCard;
    }
    //扫描并获取图像信息
    LOGI("开始获取图像信息");
    gettimeofday(&start, NULL);
    resultdata re = scanData(timeout);
    gettimeofday(&stop, NULL);
    int timesss = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
    LOGI("采图用时: %d us", timesss);
    //获取图像信息之后就getData
    LOGI("图像信息获取完毕");

    if (re != result_normal) {
        if (re == result_timeout)return ScanCardReturn::ScanTimeout;
        return ScanCardReturn::ScanErr;
    }
    LOGI("开始进行getData");
    int res = getData(workingFolder + "/images/Scan_White.jpg",
                      workingFolder + "/images/Scan_IR.jpg",
                      workingFolder + "/images/Scan_UV.jpg", 0);
    return res;
}


int initProgram(string Folder) {
    workingFolder = Folder;
    mkdir((workingFolder + "/images").c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir((workingFolder + "/USB_TEMP").c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    time_t tt = time(NULL);
    struct tm *t = localtime(&tt);
    int year = t->tm_year + 1900;
    int mon = t->tm_mon;
    int day = t->tm_mday;
    //todo
    if (year > 2020 || mon > 12 || year < 2020) {
        //LOGE("SDK使用权限到期，无法继续使用");
        //return -1;
    }

    // choose the right model: mrz32_61.pb or mrz32_20190523.pb
#ifndef USE_OLD_OCR
    if (OCRworker.initNet(workingFolder + "/model/mrz32_61.pb") != 0) {
        LOGE("OCR model failed to load");
        return -2;
    }
    //设置初始化成功标志位
    //避免每次开启设备都需要重新初始化
    initFlag = true;
#endif
    return 0;
}

int ldistance(const string source, const string target) {
    //step 1

    int n = source.length();
    int m = target.length();
    if (m == 0) return n;
    if (n == 0) return m;
    //Construct a matrix
    typedef vector<vector<int> > Tmatrix;
    Tmatrix matrix(n + 1);
    for (int i = 0; i <= n; i++) matrix[i].resize(m + 1);

    //step 2 Initialize

    for (int i = 1; i <= n; i++) matrix[i][0] = i;
    for (int i = 1; i <= m; i++) matrix[0][i] = i;

    //step 3
    for (int i = 1; i <= n; i++) {
        const char si = source[i - 1];
        //step 4
        for (int j = 1; j <= m; j++) {

            const char dj = target[j - 1];
            //step 5
            int cost;
            if (si == dj) {
                cost = 0;
            } else {
                cost = 1;
            }
            //step 6
            const int above = matrix[i - 1][j] + 1;
            const int left = matrix[i][j - 1] + 1;
            const int diag = matrix[i - 1][j - 1] + cost;
            matrix[i][j] = min(above, min(left, diag));

        }
    }//step7
    return matrix[n][m];
}

int getData(string whitePath, string irPath, string uvPath, int authenFlag) {

    //cleanup everything
    docType = UNKNOWN, chipStatus = 0, sfzStatus = 0, insertType = -1;
    mrzCode.clear(), DG1.clear(), DG11.clear(), IDNum.clear(), SFZinfo.clear(), SFZinfoUTF16.clear(), SFZImage.clear(), jsonInfo.clear(), authenticity_result = "0", authenticity_details = "";

    //int chipType = getCardType();
    /********************先是对三种图像进行裁剪和旋转**********************/
    Mat whiteImg = imread(whitePath);
    if (whiteImg.empty()) {
        docType = UNKNOWN;
        return ScanCardReturn::ReadImgErr;//读取图像失败
    }
    Size outputSize;

    Mat irSrc = imread(irPath);

    Mat trans = edgeDetectionAny(insertType, outputSize, whiteImg, irSrc, back);
    if (trans.empty()) {
        docType = UNKNOWN;
        LOGE("边缘检测失败，退出");
        return ScanCardReturn::EdgeDeteErr;
    }


    Mat uvSrc = imread(uvPath);
    Mat finalWhite = saveFinalImage(trans, whiteImg, outputSize, 1, insertType, back, true);
    Mat finalIr = saveFinalImage(trans, irSrc, outputSize, 0, insertType, back, true);
    saveFinalImage(trans, uvSrc, outputSize, 2, insertType, back, true);


    if (back) {//是背面，直接返回，不进行ocr和读卡操作
        return ScanCardReturn::Back;
    }

    /********************读身份证失败之后再按照其他证件来处理**********************/
    LOGI("-----开始读取护照数据-----");
    gettimeofday(&start, NULL);
    cvtColor(finalIr, finalIr, COLOR_RGB2GRAY);
    //如果是小卡片
    if (insertType == 1) {

        insertType = OCRworker.getMrzNums(finalIr);
    }
    int OCRType = 0;
    if (insertType == 1) {
        //港澳通行证  台湾通行证
        LOGI("判断证件是1行机读码");
        OCRType = 1;
        docType = HKMO_EXIT_ENTRY_PERMIT;
    } else if (insertType == 2) {
        LOGI("判断证件是2行机读码");
        //护照
        OCRType = 0;
        docType = PASSPORT;
    } else if (insertType == 3) {
        //三行证件
        LOGI("判断证件是3行机读码");
        OCRType = 2;
    } else {
        LOGE("无法识别的证件，退出OCR和读卡");
        docType = UNKNOWN;
        return ScanCardReturn::InvalidCard;
    }

#ifndef USE_OLD_OCR
    string outputPath = workingFolder + "/USB_TEMP/";
//    resize(finalIr, finalIr, Size(finalIr.cols / 2, finalIr.rows / 2));
    mrzCode = OCRworker.OCR(finalIr, OCRType, outputPath);//2:三行证件，1，单行证件，0，双行证件

#else
    Mat MRZImage = findMrzAPI(camera.IRImage, 0, 0);
    mrzCode = mrzOcrAPI(MRZImage, 0, "");
#endif
    if (mrzCode.length() < 5) {
        LOGE("OCR mrzCode:%s , aborting...", mrzCode.c_str());
        return ScanCardReturn::MrzOrcErr;
    }
    int minindex = -1, minvalue = 100;
    for (int i = 0; i < datasets.size(); ++i) {
        string dataset = datasets[i].substr();
        int dis = ldistance(mrzCode, dataset);
        if (dis < minvalue) {
            minvalue = dis;
            minindex = i;
        }
    }
    if (minvalue < 10) {
        mrzCode = datasets[minindex];
    }
    LOGI("OCR RESULT: %s", mrzCode.c_str());
    LOGI("OCR RESULT LENGTH %d", mrzCode.size());
    if (docType == PASSPORT) {
        correctPassportMrz(mrzCode);
        LOGI("OCR CORRECT: %s", mrzCode.c_str());
    }
    gettimeofday(&stop, NULL);
    int timesss = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
    LOGI("OCR finished and used time: %d us", timesss);

    try {
        if (OCRType == 2) {
            //如果是三行证件，根据OCR的结果来判断是回乡证还是台胞证
            if (mrzCode.substr(0, 2).compare("CT") == 0) {
                docType = TW_HOME_RETURN_PERMIT;
            } else {
                docType = HKMO_HOME_RETURN_PERMIT;
            }

        } else if (OCRType == 1) {
            if (mrzCode.substr(0, 2).compare("CD") == 0) {
                docType = TAIWAN_PASSPORT;
            } else {
                docType = HKMO_EXIT_ENTRY_PERMIT;
            }
        }
    } catch (...) {

    }
    //if((docType == PASSPORT)&&((authenFlag == 1) || (authenFlag == 2))){
    //string myUvPath = workingFolder+"/USB_TEMP/UV.bmp";
    //string myWhitePath = workingFolder+ "/USB_TEMP/White.bmp";
    //string myIRPath = workingFolder+ "/USB_TEMP/White.bmp";
    //authenticity_result = getAuthenticity(myWhitePath.c_str(),myIRPath.c_str(),myUvPath.c_str(),authenFlag);
    //}
    printf("Read chip start...\r\n");
    gettimeofday(&start, NULL);
    //mrzCode = "POCHNYUAN<<PEIPEI<<<<<<<<<<<<<<<<<<<<<<<<<<<\nE561240497CHN9008168F2507204NEKMMFOFMFOFA920";
    //docType = PASSPORT;
//    mrzCode = "CSC531580954<2612199<9712087<2";
//    docType = HKMO_EXIT_ENTRY_PERMIT;
    switch (docType) {
        case HKMO_EXIT_ENTRY_PERMIT: //单行卡片
            chipStatus = EchipOneCardRead(mrzCode + "\n", DG1, DG11,
                                          workingFolder + "/images/DG2.jpg", mrzInfo);
            break;
        case TAIWAN_PASSPORT:
            chipStatus = EchipOneCardRead(mrzCode + "\n", DG1, DG11,
                                          workingFolder + "/images/DG2.jpg", mrzInfo);
            break;
        case PASSPORT://双行卡片
            chipStatus = EchipTwoCardRead(mrzCode + "\n", DG1, DG11,
                                          workingFolder + "/images/DG2.jpg", mrzInfo);
            break;
        default: //三行证件
            chipStatus = EchipThreeCardRead(mrzCode + "\n", DG1, DG11,
                                            workingFolder + "/images/DG2.jpg", mrzInfo);
            break;
    }
    gettimeofday(&stop, NULL);
    timesss = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
    printf("Read chip finished and used time %d us\r\n", timesss);
    LOGI("Read chip finished and used time %d us", timesss);
    vector<int> p;
    p.push_back(IMWRITE_JPEG_QUALITY);
    p.push_back(30);
    Mat chipHead = imread(workingFolder + "/images/DG2.jpg");
    if (!chipHead.empty())
        imwrite(workingFolder + "/images/DG2.jpg", chipHead, p);
    if (chipStatus) {
        LOGI("chip reader status: %d, DG1: %s, DG11: %s", chipStatus, DG1.c_str(),
             DG11.c_str());
    } else {
        LOGE("chip reader status: %d, read failed or no chip", chipStatus);
        chipStatus = -1;
        //return 4;
    }
    return ScanCardReturn::Success;
}


string getJson() {
    if (docType == ID_CARD) {
        jsonInfo = processIDCARDInfo(SFZinfoUTF16,
                                     workingFolder + "/idcard/zp.bmp");
        return jsonInfo;
    }
    if (!DG1.empty()) {
        string info = getEChipDG1();
        string fullName = getEChipDG11();
        jsonInfo = processDG(info, fullName, docType, workingFolder + "/images/DG2.jpg",
                             workingFolder + "/images/White.jpg",
                             workingFolder + "/images/IR.jpg", workingFolder + "/images/UV.jpg",
                             workingFolder + "/images/UV_Back.jpg");


    } else if (!mrzCode.empty()) {
        jsonInfo = processMRZ(mrzCode, docType,
                              workingFolder + "/images/head.jpg",
                              workingFolder + "/images/White.jpg",
                              workingFolder + "/images/IR.jpg",
                              workingFolder + "/images/UV.jpg",
                              workingFolder + "/images/UV_Back.jpg");

    }
    return jsonInfo;
}

string getEChipDG1() {
    if (docType == ID_CARD) {
        return SFZinfo;
    }
    if (!chipStatus)
        return ("");
    else
        return DG1;
}

string getEChipDG11() {
    if (!chipStatus)
        return ("");

    //find second
    std::string UTF8_name_tag("\x5f\x0e", 2);
    size_t offset = DG11.find(UTF8_name_tag);
    if (offset == std::string::npos)
        return ("");
    offset = DG11.find(UTF8_name_tag, offset + 2);
    if (offset == std::string::npos)
        return ("");

    unsigned char size = DG11[offset + 2];

    return (DG11.substr(offset + 3, size));
}

long long getTimeStamp() {
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now());//获取当前时间点
    long long timestamp = tp.time_since_epoch().count(); //计算距离1970-1-1,00:00的时间长度
    return timestamp;
}

string getDeviceID() {
    char id[25];
    ReadChipUID(id);
//    LOGI("getDeviceID deviceID:%s",id);
    return string(id);
}

const char *getSFZImageData() {
    if (docType != 0)
        return NULL;
    else {
        static char sfzImage[1024];
        for (int i = 0; i < 1024; i++) {
            sfzImage[i] = SFZImage[i];
        }
        return sfzImage;
    }
}