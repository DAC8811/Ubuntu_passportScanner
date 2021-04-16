#include <jni.h>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include "PassportReader/PassportReaderAPI/include/getData.h"

#include <android/log.h>

#ifndef LOG_TAG
#define LOG_TAG "PassportReaderJNI"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG ,__VA_ARGS__) // 定义LOGV类型
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,LOG_TAG ,__VA_ARGS__) // 定义LOGF类型
#endif


//extern MvCamera camera;
extern  "C"
JNIEXPORT jstring JNICALL
Java_com_boc_devices_passportscanner_hs_PassportScanner_getJson(JNIEnv *env,
                                                                jclass){
    return env->NewStringUTF(getJson().c_str());
    //return (jstring) "a";
}
extern  "C"
JNIEXPORT jint JNICALL
Java_com_boc_devices_passportscanner_hs_PassportScanner_getAuthentic(JNIEnv *env,
                                                                     jclass){
    char* wh = "/storage/emulated/0/Android/data/com.dscvlab.ooxx.passportreader/files/USB_TEMP/whiteP.bmp";
    char* ir = "/storage/emulated/0/Android/data/com.dscvlab.ooxx.passportreader/files/USB_TEMP/irP.bmp";
    char* uv = "/storage/emulated/0/Android/data/com.dscvlab.ooxx.passportreader/files/USB_TEMP/uvP.bmp";
    //return getAuthenticity(wh,ir,uv);
    //return (jstring) "a";
}


extern "C" JNIEXPORT jint JNICALL
Java_com_boc_devices_passportscanner_hs_PassportScanner_getMediaStatus(JNIEnv *env, jclass clazz) {
    return getMediaStatus();
}


extern "C" JNIEXPORT jint JNICALL
Java_com_boc_devices_passportscanner_hs_PassportScanner_setWorkingStatus(JNIEnv *env, jclass clazz, jint status) {
    return setWorkingStatus(status);
}

extern "C" JNIEXPORT jint JNICALL
Java_com_boc_devices_passportscanner_hs_PassportScanner_beepBuzzer(JNIEnv *env, jclass clazz, jint times) {
//    return 1;
    return beepBuzzer(times);
}


extern "C" JNIEXPORT jint JNICALL
Java_com_boc_devices_passportscanner_hs_PassportScanner_closeConnect(JNIEnv *env, jclass clazz) {
    return closeConnection();
}
extern "C" JNIEXPORT jint JNICALL
Java_com_boc_devices_passportscanner_hs_PassportScanner_openConnect(JNIEnv *env, jclass clazz,
                                                                    jstring folder,
                                                                    jint RFReaderFD,
                                                                    jint scanFD) {
    string workingFolderC = env->GetStringUTFChars(folder, NULL);
    return openConnection(workingFolderC,RFReaderFD,scanFD);
}
extern "C" JNIEXPORT jint JNICALL
Java_com_boc_devices_passportscanner_hs_PassportScanner_scanAndReadCard(JNIEnv *env, jclass clazz,
                                                                        jint timeout) {
    return scanAndReadCard(timeout);
}
//extern "C"
//JNIEXPORT jint JNICALL
//Java_com_boc_devices_passportscanner_hs_PassportScanner_generateConfig(JNIEnv *env, jclass clazz) {
//    return generateConfig();
//}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_boc_devices_passportscanner_hs_PassportScanner_getDeviceID(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF(getDeviceID().c_str());
}
extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_boc_devices_passportscanner_hs_PassportScanner_getSFZimage(JNIEnv *env,
                                                                      jclass
) {
//    return env->NewStringUTF(getSFZimage().c_str());
    int size = 1024;
    char img[1024];
    const char* img2 = getSFZImageData();
    for(int i = 0; i <1024; i++){
        img[i] = img2[i];
    }


    jbyteArray result = env->NewByteArray(size);

    if (result == NULL) {
        return NULL; /* out of memory error thrown */
    }

    jbyte fill[1024];
    for (int i = 0; i < size; i++) {
        fill[i] = img[i]; // put whatever logic you want to populate the values here.
    }

    env->SetByteArrayRegion(result, 0, size, fill);

    return result;
}