//
// Created by 张迪 on 2020/9/14.
//

#ifndef PASSPORTREADER_CISREADER_H
#define PASSPORTREADER_CISREADER_H

#include "datastruct.h"
#include <string>

#define EXPORT_FUN __attribute__((visibility("default")))

int openConnect(std::string folder);

void checkRevision(std::string workFolder, std::string deviceID);

void *reviseThread(void *);

extern "C" EXPORT_FUN int closeConnection();
extern "C" EXPORT_FUN int getMediaStatus();

resultdata scanData(int timeout);

//extern "C" EXPORT_FUN int generateConfig();
extern "C" EXPORT_FUN bool setWorkingStatus(int status);//status false:waiting true:working
extern "C" EXPORT_FUN bool beepBuzzer(int times);//times 响的次数，目前只支持1~3次
#endif //PASSPORTREADER_CISREADER_H
