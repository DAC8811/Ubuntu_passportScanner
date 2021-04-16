//
// Created by Comic Chang on 2018/8/24.
//

#ifndef PASSPORTREADER_INTERNAL_H
#define PASSPORTREADER_INTERNAL_H

#include <glog/logging.h>
#include <stdio.h>
#include <iostream>
using std::endl;
extern char LOGBUFFER[300];

#define LOGV(...) asm("nop")
#define LOGD(...) asm("nop")
#define LOGI(...) snprintf(LOGBUFFER, 300, __VA_ARGS__) && LOG(INFO) << LOGBUFFER << endl
#define LOGW(...) snprintf(LOGBUFFER, 300, __VA_ARGS__) && LOG(WARNING) << LOGBUFFER << endl
#define LOGE(...) snprintf(LOGBUFFER, 300, __VA_ARGS__) && LOG(ERROR) << LOGBUFFER << endl
#define LOGF(...) snprintf(LOGBUFFER, 300, __VA_ARGS__) && LOG(FATAL) << LOGBUFFER << endl

#endif //PASSPORTREADER_INTERNAL_H
