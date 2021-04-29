#include <dlfcn.h>
#include <string>
#include <iostream>

using namespace std;

typedef int(*p_setParam)(string folder, string strDevPort, string strParam);
typedef int(*p_openConnection)();
typedef string(*p_scanAndReadCardInfo)(int timeout,int paramInt, std::string paramString);
typedef int(*p_closeConnection)();

int main(){
    void* wlt = dlopen("/home/ash1/lab_pro/Ubuntu_16_passportScanner/ubuntu/Demo_passportScanner/libwlt.so",RTLD_NOW | RTLD_GLOBAL);
    if( !wlt ){
        cout << "open wlt failed" << endl;
    }
    void* handle = dlopen("/home/ash1/lab_pro/Ubuntu_16_passportScanner/ubuntu/Demo_passportScanner/libpassportScanner.so",RTLD_NOW);
    if( !wlt ){
        cout << "open passportScanner failed" << endl;
    }
    p_setParam setParam = (p_setParam)dlsym(handle,"setParam");
    if(!setParam){
        cout << "dlsym failed" << endl;
        cout << "dlopen err: " << dlerror() << endl; 
    }
    p_openConnection openConnection = (p_openConnection)dlsym(handle,"openConnection");
    p_scanAndReadCardInfo scanAndReadCardInfo = (p_scanAndReadCardInfo)dlsym(handle,"scanAndReadCardInfo");
    p_closeConnection closeConnection = (p_closeConnection)dlsym(handle,"closeConnection");

    setParam("/home/ash1/lab_pro/Ubuntu_16_passportScanner/ubuntu/Demo_passportScanner/user","","");
    openConnection();
    scanAndReadCardInfo(10000,0,"");
    closeConnection();
    dlclose(handle);
    dlclose(wlt);
}


