#ifndef PASSPORTSCANNER_PASSPORTSCANNER_H
#define PASSPORTSCANNER_PASSPORTSCANNER_H

#include "getData.h"
#include <string>

#define EXPORT_FUN __attribute__((visibility("default")))

extern "C" EXPORT_FUN int openConnection();

extern "C" EXPORT_FUN int closeConnection();

extern "C" EXPORT_FUN int getMediaStatus(int* status);

extern "C" EXPORT_FUN int getVersion(char* psVersion,int* piRetLen);

extern "C" EXPORT_FUN std::string getCapabilities();

extern "C" EXPORT_FUN std::string scanAndReadCardInfo(int timeout);

extern "C" EXPORT_FUN int cancel();

extern "C" EXPORT_FUN int reset(int iAction);

#endif