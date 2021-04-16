#pragma once
#ifndef USBHANDLER_H
#define USBHANDLER_H
#define MEDIA_STATUS_EXIST 0
#define MEDIA_STATUS_NOTEXIST 1

#include "datastruct.h"
#include <ezusbAPI.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <semaphore.h>

class UsbHandler {
public:
    UsbHandler();

    ~UsbHandler();

    bool setLight(int, int, int, int, int, int);

    void init(std::string folder);

    STATUS closeUsb() {
        return usbDevice.close();
    }

    STATUS openUsb() {
        return usbDevice.open();
    }

    //true is disconnected,false is connected
    bool isDeviceDisconnected() {
        return usbDevice.isConnect();
    }

    int mediaStatusTrue = MEDIA_STATUS_NOTEXIST;
    int mediaStatus = MEDIA_STATUS_NOTEXIST;

    void setJZ(double a) {
        JZ = a;
    }

    cv::Mat *getPictures() {
        return pictures;
    }

    resultdata acquireImage(int timeout = 10000);



    bool calibrate(std::string id);

    void setRevisionPara(FILE *black, FILE *k);

    bool getAcquireState() {
        return getImg;
    }

    void setAcquireState(bool a) {
        getImg = a;
        if (!a) {
            printf("in\n");
        }
    }

    void beginListenData();

    void clearUSBSerial();

    static void *USBDataListener(void *p);

    bool sendSignal(UCHAR low, UCHAR high);

private:
    UCHAR *databuf = new unsigned char[DATALENGTH * 9];
    UCHAR (*mat0)[3 * PICLENGTH] = new unsigned char[6][3 * PICLENGTH];

    Ezusb usbDevice;
    std::string workFolder;
    UCHAR rLight[2];
    UCHAR gLight[2];
    UCHAR bLight[2];
    UCHAR irLight[2];
    UCHAR uv1Light[2];
    UCHAR uv2Light[2];

    cv::Mat pictures[3];

    bool lightChangeOn;
    bool firstin;
    bool getImg;

    resultdata result;
    mode getPicMode;
    int fd;

    double JZ;
    bool scanning = false;
    sem_t imgSem;
    unsigned char *inbuf[BUFSIZE];
    unsigned char *throwbuf;
    std::string deviceID;
    int *blackPix = new int[9 * PICWIDTH];
    int *kArr = new int[9 * PICWIDTH];

    bool startCap();

    bool endCap();
    long long getTimeStamp();
    int MyImageProcess(unsigned char *data);

    void DataExtractToImg(unsigned char *data, unsigned char mat0[][3 * PICLENGTH], int len = 3);

    void ReviseImage(unsigned char mat0[][3 * PICLENGTH], int len = 3);

    void getReviseData(unsigned char mat0[][3 * PICLENGTH]);

    bool setLightChangeOn(bool i) {
        lightChangeOn = i;
        return true;
    }

    bool setMode(mode i) {
        getPicMode = i;
        return true;
    }

};

#endif // USBHANDLER_H
