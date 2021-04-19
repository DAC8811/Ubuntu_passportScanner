#include <iostream>
#include <stdio.h>
//#include "getData.h"
#include <dlfcn.h>
using namespace std;

typedef int(*p_init)(const char*);
typedef int(*p_get)(const char*,const char*,const char*,const char*,const char*,const char*);
typedef int(*p_close)();
typedef int(*p_findO)();
typedef const char*(*p_json)();
int main(void){
    void* handle0 = dlopen("/home/gwi/桌面/passport/demo_WI_A/user/libwlt2019.so",RTLD_NOW | RTLD_GLOBAL);
    void* handle1 = dlopen("/home/gwi/桌面/passport/demo_WI_A/user/libtensorflow_cc.so",RTLD_NOW | RTLD_GLOBAL);
    void* handle2 = dlopen("/home/gwi/桌面/passport/demo_WI_A/user/libtensorflow_framework.so",RTLD_NOW | RTLD_GLOBAL);
    void* handle = dlopen("/home/gwi/桌面/passport/demo_WI_A/user/libgetData.so",RTLD_NOW);
    if(!handle){
        cout << "open error" << endl;
        cout << dlerror() << endl;
    }
    p_init initProgram = (p_init)dlsym(handle,"initProgram");
    int result1 =  (initProgram)("/home/gwi/桌面/passport/demo_WI_A/user");//初始化程序，在调用getData前调用，并且仅可调用一次
    if (result1 < 0)
        //初始化失败，程序退出
        return -1;
    //OCR test
    //采集数据（Ocr、读卡)
    //传入参数string irPath：红外图像完整路径
    p_get getData = (p_get)dlsym(handle,"getData");
    int result2 = (getData)("/home/gwi/桌面/passport/testPhotos/tx1A.bmp","/home/gwi/桌面/passport/testPhotos/tx1B.bmp",NULL,NULL,NULL,NULL);
//    if (result2 < 0){
        //读取失败
        cout << result2 << endl;
        //return -1;
//    }
	p_findO findOrientation = (p_findO)dlsym(handle,"findOrientation");
	int Orientation = findOrientation();
	cout << "Orientation: " << Orientation << endl;
    //获取证件各项信息，以Json格式返回一个字符串
    p_json getJsonNew = (p_json)dlsym(handle,"getJsonNew");
    string jsonInfo = (getJsonNew)();
    if (jsonInfo.length() != 0)
        cout << "getJsonNew() :" << jsonInfo << endl;
    //关闭程序，仅可调用一次
    p_close closeProgram = (p_close)dlsym(handle,"closeProgram");
    (closeProgram)();
	dlclose(handle0);
	dlclose(handle1);
	dlclose(handle2);
    dlclose(handle);
    return 0;
}