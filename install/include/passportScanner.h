#ifndef PASSPORTSCANNER_PASSPORTSCANNER_H
#define PASSPORTSCANNER_PASSPORTSCANNER_H

#include <string>

#define EXPORT_FUN __attribute__((visibility("default")))

extern "C" EXPORT_FUN int setParam(std::string folder, std::string strDevPort = "", std::string strParam = "");

extern "C" EXPORT_FUN int openConnection();

extern "C" EXPORT_FUN int closeConnection();

extern "C" EXPORT_FUN int getMediaStatus(int* status);

extern "C" EXPORT_FUN int getVersion(char* psVersion,int* piRetLen);

extern "C" EXPORT_FUN std::string getCapabilities();

extern "C" EXPORT_FUN std::string scanAndReadCardInfo(int timeout,int paramInt = 0, std::string paramString = "");

extern "C" EXPORT_FUN int cancel();

extern "C" EXPORT_FUN int reset(int iAction);

#endif