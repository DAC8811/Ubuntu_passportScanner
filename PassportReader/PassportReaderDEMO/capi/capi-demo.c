// vim: set tabstop=4 shiftwidth=4 expandtab fileencoding=utf-8 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "PassportReaderCAPI.h"

int main(void)
{
    printf("Hello, World! from main");

    char path[256] = {0};
    //初始化SDK，连接设备

    if (CSDKInit("/mnt/WorkingFolder/", "mrz32_20190523.pb") != 0)
    {
        printf("SDK初始化失败，请检查设备是否连接，工作目录设置，以及相应文件权限");
        return 0;
    }
    else
    {
        memset(path, 0, 256);
        CgetAPIversion(path);
        printf("SDK 初始化成功");
        printf("版本号： %s", path);
    }

    //从内置储存载入校正参数，如果不存在，调用函数生成新的参数（注：需要放置校正纸）
    if (CloadConfig() != 0)
    {
        printf("Load config failed, generating....");
        CgenerateAndSaveConfig();
        printf("generated, exiting....");
        return 0;
    }

    while (1)
    {
        //检测是否有证件插入
        int detectResult = CinputDetect(false);
        if (detectResult == 0)
        {
            usleep(50000);
        }
        else if (detectResult == 2)
        {
            //检测到身份证
            printf("=============================START=============================");
            //读取包括图像和芯片的所有数据
            CgetUSBDataSFZ(0);
            // CsaveImage();
            printf("=============================FINISH============================");

            printf("卡片种类：\t%d", CgetType());

            //调用函数获取图像保存的地址
            memset(path, 0, 256);
            CgetWhiteImageURI(path);
            printf("白光图片地址：\t%s", path);

            memset(path, 0, 256);
            CgetIRImageURI(path);
            printf("红外图片地址：\t%s", path);

            memset(path, 0, 256);
            CgetUVImageURI(path);
            printf("紫外图片地址：\t%s", path);

            if (CgetType() == 1)
            {
                //对于身份证，显示芯片包含的信息
                memset(path, 0, 256);
                CgetSFZinfo(path);
                printf("身份证信息：\t%s", path);

                memset(path, 0, 256);
                CgetSFZImageURI(path);
                printf("身份证照片地址：\t%s", path);
            }
            printf("==============================END=============================");
        }
        else
        {
            //检测到非身份证证卡，使用护照流程读取
            printf("=============================START=============================");
            //读取包括图像和芯片的所有数据
            CgetUSBDataPassport(0);
            // CsaveImage();
            printf("=============================FINISH============================");

            printf("卡片种类：\t%d", CgetType());

            //调用函数获取图像保存的地址
            memset(path, 0, 256);
            CgetWhiteImageURI(path);
            printf("白光图片地址：\t%s", path);

            memset(path, 0, 256);
            CgetIRImageURI(path);
            printf("红外图片地址：\t%s", path);

            memset(path, 0, 256);
            CgetUVImageURI(path);
            printf("紫外图片地址：\t%s", path);

            if (CgetType() > 1)
            {
                //对于其他证卡，显示OCR和芯片读取到的信息

                memset(path, 0, 256);
                CgetOCRresult(path);
                printf("OCR识别结果：\t%s", path);

                memset(path, 0, 256);
                CgetEChipImageURI(path);
                printf("芯片照片地址：\t%s", path);

                memset(path, 0, 256);
                CgetEChipDG1(path);
                printf("DG1信息：\t%s", path);

                memset(path, 0, 256);
                CgetEChipDG11(path);
                printf("DG11信息：\t%s", path);
            }
            printf("==============================END=============================");
        }
    }

    CSDKClose();

    return 0;
}
