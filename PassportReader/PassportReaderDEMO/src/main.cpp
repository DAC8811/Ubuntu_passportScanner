// vim: set tabstop=4 shiftwidth=4 expandtab fileencoding=utf-8 
#include "PassportReaderAPI.h"
#include "internalLogging.h"
//#include "libChip.h"

#include <iostream>

#include <unistd.h>


int main(int argc, char **argv) {

    google::InitGoogleLogging(argv[0]);
    google::SetStderrLogging(google::GLOG_INFO);
    FLAGS_logtostderr = 0;
    FLAGS_colorlogtostderr = 1;

    LOGI("Hello, World! from main");
    LOGI("Demo APP Version: %s", "1.0-20190923b");

    string WorkingFolder;
    if (argc < 2)
        WorkingFolder = string(".");
    else
        WorkingFolder = string(argv[1]);

    //初始化SDK，连接设备
    if (SDKInit(WorkingFolder.c_str(), "mrz32_20190523.pb") != 0) {
        LOGE("SDK初始化失败，请检查设备是否连接，工作目录设置，以及相应文件权限");
        return 0;
    } else {
        LOGI("SDK 初始化成功");
        LOGI("API版本号： %s", getAPIversion().c_str());
    }

    //从内置储存载入校正参数，如果不存在，调用函数生成新的参数（注：需要放置校正纸）
    if (loadConfig() != 0) {
        LOGE("Load config failed, generating....");
        generateAndSaveConfig();
        LOGE("generated, exiting....");
        return 0;
    }

    LOGI("初始化完毕，开始检测插入证件");
    int detectResult  = 0;
    while (true) {
        //检测是否有证件插入 
        if (0) //不使用摄像头进行检测，无法检测护照，只可以读取身份证
            detectResult = inputDetect( false );
        else //使用摄像头进行检测，可以检测护照和身份证
            detectResult = inputDetect( true );

        if (detectResult == 0){
            // 没有检测到证件
            usleep(100000);
        }
        // 之前的通用读取接口，依旧可用，不过速度稍慢
        // else {
        //     LOGI("=============================START=============================");
        //     //读取包括图像和芯片的所有数据
        //     if (1) {
        //         // 不保存任何图像，速度快
        //         getUSBData();
        //     } else {
        //         // 保存图像，速度慢
        //         getUSBData(true);
        //         saveImage();
        //     }
        //     LOGI("=============================FINISH============================");
        //     LOGI("卡片种类：\t%d", getType());
        //     //调用函数获取图像保存的地址
        //     LOGI("白光图片地址：\t%s", getWhiteImageURI().c_str());
        //     LOGI("红外图片地址：\t%s", getIRImageURI().c_str());
        //     LOGI("紫外图片地址：\t%s", getUVImageURI().c_str());
        //     if (getType() == 1){
        //         //对于身份证，显示芯片包含的信息
        //         LOGI("身份证信息：\t%s", getSFZinfo().c_str());
        //         LOGI("身份证照片地址：\t%s", getSFZImageURI().c_str());
        //     }
        //     if (getType() >= 2){
        //         //对于其他证卡，显示OCR和芯片读取到的信息
        //         LOGI("OCR识别结果：\t%s", getOCRresult().c_str());
        //         LOGI("芯片照片地址：\t%s", getEChipImageURI().c_str());
        //         LOGI("DG1信息：\t%s", getEChipDG1().c_str());
        //         LOGI("DG11信息：\t%s", getEChipDG11().c_str());
        //     }
        // }
        else if (detectResult == 2){
            //检测到身份证
            LOGI("=============================START=============================");
            //读取包括图像和芯片的所有数据
            if (0) {
                // 不保存任何图像，速度快
                getUSBDataSFZ();
            } else {
                // 保存图像，速度慢
                getUSBDataSFZ(true);
                saveImage();
            }
            LOGI("=============================FINISH============================");

            LOGI("卡片种类：\t%d", getType());

            //调用函数获取图像保存的地址
            LOGI("白光图片地址：\t%s", getWhiteImageURI().c_str());
            LOGI("红外图片地址：\t%s", getIRImageURI().c_str());
            LOGI("紫外图片地址：\t%s", getUVImageURI().c_str());
            if (getType() == 1){
                //对于身份证，显示芯片包含的信息
                LOGI("身份证信息：\t%s", getSFZinfo().c_str());
                LOGI("身份证照片地址：\t%s", getSFZImageURI().c_str());
                LOGI("身份证信息解析：\t%s", getInfoJson().c_str());
            }
        }
        else if (detectResult) {
            //检测到其他证件
            LOGI("=============================START=============================");
            //读取包括图像和芯片的所有数据
            if (0) {
                // 不保存任何图像，速度快
                getUSBDataPassport();
            } else {
                // 保存图像，速度慢
                getUSBDataPassport(true);
                saveImage();
            }
            LOGI("=============================FINISH============================");

            LOGI("卡片种类：\t%d", getType());

            //调用函数获取图像保存的地址
            LOGI("白光图片地址：\t%s", getWhiteImageURI().c_str());
            LOGI("红外图片地址：\t%s", getIRImageURI().c_str());
            LOGI("紫外图片地址：\t%s", getUVImageURI().c_str());

            if (getType() >= 2){
                //对于其他证卡，显示OCR和芯片读取到的信息
                LOGI("OCR识别结果：\t%s", getOCRresult().c_str());
                LOGI("芯片照片地址：\t%s", getEChipImageURI().c_str());
                LOGI("DG1信息：\t%s", getEChipDG1().c_str());
                LOGI("DG11信息：\t%s", getEChipDG11().c_str());
                LOGI("护照信息解析：\t%s", getInfoJson().c_str());
            }
            LOGI("==============================END=============================");
        }
    }

    SDKClose();

    return 0;
}
