//
// Created by 张迪 on 2020/3/21.
//

#ifndef PASSPORTREADER_GETDATA_H
#define PASSPORTREADER_GETDATA_H

#include <string>

using namespace std;

#define EXPORT_FUN __attribute__((visibility("default")))


/******************************************************/
// 函数名   : initProgram
// 功能描述 : 设备SDK初始化，在调用任何SDK其他接口前，必须先调用该接口进行初始化。该函数在整个进程运行期间只需要调用一次。
// 参数     : WorkingFolder 工作目录，字符串
// 返回值   : 成功时，返回0
//            否则参考日志输出
/******************************************************/
EXPORT_FUN int initProgram(string Folder);
EXPORT_FUN int openConnect(string workingFolder, int RFReaderFD, int scanFD);
/******************************************************/
// 函数名   :closeConnect
// 功能描述 :关闭设备
// 参数     :无
//
// 返回值   :0 成功； -1 失败
//
/******************************************************/
EXPORT_FUN int closeConnect();
EXPORT_FUN string getDeviceID();
EXPORT_FUN int getMediaStatu();
EXPORT_FUN bool setWorkingStatus(int status);//status 0:waiting 1:working
EXPORT_FUN bool beepBuzzer(int times);//times 响的次数，目前只支持1~3次
//extern "C" EXPORT_FUN int generateConfig();
EXPORT_FUN
int scanAndReadCard(int timeout);
//extern "C" EXPORT_FUN
//int secondScanCard(int timeout);
/******************************************************/
// 函数名   : getData
// 功能描述 :采集数据（Ocr、读卡)
// 参数     :whitePath 白光图像完整路径
//           irPath 红外图像完整路径
//           uvPath  紫外图像完整路径
//           authenFlag  鉴伪标志，0：不进行鉴伪，getJsonNew得到的鉴伪结果为0；
//                             1：进行护照鉴伪，getJsonNew得到的鉴伪结果为1或2，-1代表证件为假，0代表14个鉴伪点都没有进行鉴伪（这种情况很少见），1代表鉴伪结果为真；没有鉴伪的详细信息
//                             2：进行护照鉴伪，getJsonNew可以得到鉴伪结果和鉴伪的详细信息，鉴伪的详细信息是一个长度为14的字符串，表示14个鉴伪点每一点的鉴伪结果；
//                                  例如得到的鉴伪信息是15511155555511，从 右 到 左 依次是模块1（鉴伪点1）、模块2（鉴伪点2）、...模块14（鉴伪点14）的结果
//                                  其中：数值1表示鉴伪点为真，2表示鉴伪点为假，5表示没有对该鉴伪点鉴伪
//                                  模块1:MRZ_UV 机读码区特征鉴伪
//                                  模块2:Pattern_UV /Thread_UV/Pattern_Thread_UV  紫外花纹特征鉴伪
//                                  模块3:PassNum_UV 证件号码区域鉴伪
//                                  模块4:DATA_UV 个人信息区域鉴伪
//                                  模块5:Photo_Shape_UV/Photo_BG_UV 个人照片特征鉴伪
//                                  模块6:Pattern_Code_UV 证件标识特征鉴伪
//                                  模块7:Thread_UV  机读码区荧光纤维鉴伪
//                                  模块8:Thread_UV 照片区域荧光纤维鉴伪
//                                  模块9:Authenticator_NIR 机读码区编码鉴伪
//                                  模块10:PassNum_NIR 证件号码区域鉴伪
//                                  模块11:DATA_NIR 个人信息区域鉴伪
//                                  模块12:Photo_NIR 个人照片特征鉴伪
//                                  模块13:Pattern_Code_NIR 证件标识特征鉴伪
//                                  模块14:MRZParityCheck1/MRZParityCheck2 MRZ检验位比对
//返回值   :0 护照读取成功；-1 失败
//
/******************************************************/
EXPORT_FUN int getData(string whitePath, string irPath, string uvPath, int authenFlag);


/******************************************************/
// 函数名   :getJson
// 功能描述 :获取证件各项信息
// 参数     :无
// 返回值   :Json字符串
//
/******************************************************/
EXPORT_FUN string getJson();
EXPORT_FUN string getEChipDG1();
EXPORT_FUN string getEChipDG11();
/******************************************************/
// 函数名   :getSFZImage
// 功能描述 :获取身份证电子头像的原始数据
// 参数     :无
// 返回值   :1024字节数据
//
/******************************************************/
EXPORT_FUN const char* getSFZImageData();
EXPORT_FUN int cropFace(string srcImgPath, string faceImgPath, int cardType);
#endif //PASSPORTREADER_GETDATA_H
