//
// Created by 张迪 on 2020/9/14.
//

#include "CISReader.h"
#include "UsbHandler.h"
#include "internalLogging.h"
#include <sys/stat.h>
#include <sys/types.h>

UsbHandler myUsbHandler;
std::string myDeviceID;
int openConnect(std::string folder) {
    myUsbHandler.init(folder);
    int res = myUsbHandler.openUsb();
    if (res == 0) {
        myUsbHandler.beginListenData();
    }
    return res;
}

int closeConnect() {
    myUsbHandler.closeUsb();
    return 0;
}

void checkRevision(std::string workFolder, std::string deviceID) {
    myDeviceID = deviceID;
    FILE *bfile = NULL;
    FILE *kfile = NULL;
    std::string bpath = workFolder + "/fix/" + deviceID + "/black";
    std::string kpath = workFolder + "/fix/" + deviceID + "/kArr";
    bfile = fopen(bpath.c_str(), "rb");
    kfile = fopen(kpath.c_str(), "rb");
    if (NULL == bfile || NULL == kfile) {
        LOGE("Revision file read false, begin auto revise\n");
        mkdir((workFolder + "/fix").c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        mkdir((workFolder + "/fix/" + deviceID).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        pthread_t t;;
        pthread_create(&t, NULL, reviseThread, NULL);
    } else {
        myUsbHandler.setRevisionPara(bfile, kfile);
        fclose(bfile);
        fclose(kfile);
    }
}

void *reviseThread(void *) {
    usleep(500000);
    myUsbHandler.calibrate(myDeviceID);
    return NULL;
}

//int generateConfig() {
//    myUsbHandler.calibrate();
//    return 0;
//}

int getMediaStatu() {
    return myUsbHandler.mediaStatusTrue;
}

resultdata scanData(int timeout) {
    resultdata re = myUsbHandler.acquireImage(timeout);
    return re;
}

//status 0:waiting 1:working
bool setWorkingStatus(int status) {
    bool res;
    switch (status) {
        case 0: {
            res = myUsbHandler.sendSignal(FpgaStatusLightGreen, FpgaStatusLightHigh);
            break;
        }
        case 1: {
            res = myUsbHandler.sendSignal(FpgaStatusLightBlue, FpgaStatusLightHigh);
            break;
        }
        default: {
            res = myUsbHandler.sendSignal(FpgaStatusLightGreen, FpgaStatusLightHigh);
            break;
        }
    }
    return res;
}

//times 响的次数，目前只支持1~3次
bool beepBuzzer(int times) {
    bool res;
    switch (times) {
        case 1: {
            res = myUsbHandler.sendSignal(FpgaBuzzerOne, FpgaBuzzerHigh);
            break;
        }
        case 2: {
            res = myUsbHandler.sendSignal(FpgaBuzzerTwo, FpgaBuzzerHigh);
            break;
        }
        case 3: {
            res = myUsbHandler.sendSignal(FpgaBuzzerThree, FpgaBuzzerHigh);
            break;
        }
        default: {
            res = myUsbHandler.sendSignal(FpgaBuzzerOne, FpgaBuzzerHigh);
            break;
        }
    }
    return res;
}