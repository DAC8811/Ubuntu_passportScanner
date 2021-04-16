#ifndef PASSPORTSCANNER_INTERNALLOGGING_H
#define PASSPORTSCANNER_INTERNALLOGGING_H

 #define GLOG_NO_ABBREVIATED_SEVERITIES
  #include <glog/logging.h>
  #include <stdio.h>
  using std::endl;
  //#define DEBUG
  extern char LOGBUFFER[300];

  #ifdef LOG_DEBUG
    #define LOGV(...) snprintf(LOGBUFFER, 300, __VA_ARGS__) && LOG(INFO) << LOGBUFFER << endl
    #define LOGD(...) snprintf(LOGBUFFER, 300, __VA_ARGS__) && LOG(INFO) << LOGBUFFER << endl
  #else
    #define LOGV(...) asm("nop")
    #define LOGD(...) asm("nop")
  #endif
  #define LOGI(...) snprintf(LOGBUFFER, 300, __VA_ARGS__) && LOG(INFO) << LOGBUFFER << endl
  #define LOGW(...) snprintf(LOGBUFFER, 300, __VA_ARGS__) && LOG(WARNING) << LOGBUFFER << endl
  #define LOGE(...) snprintf(LOGBUFFER, 300, __VA_ARGS__) && LOG(ERROR) << LOGBUFFER << endl
  #define LOGF(...) snprintf(LOGBUFFER, 300, __VA_ARGS__) && LOG(FATAL) << LOGBUFFER << endl


  #endif