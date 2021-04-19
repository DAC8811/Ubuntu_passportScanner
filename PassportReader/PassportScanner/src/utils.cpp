#include <string>
#include <fstream>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

#include "utils.h"
#include "internalLogging.h"
#include "getData.h"

using namespace std;

void removeFile(const string& filePath) {
    ifstream file;
    file.open(filePath.c_str(), ios::in);

    if (file.is_open())
    {
        file.close();
        //删除
        remove(filePath.c_str());
    }
}

bool removeDir(const string& szFileDir){
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(szFileDir.c_str())) == NULL){
        printf("[func:RemoveDir]cannot open directory:%s\n",szFileDir);
        return -1;
    }
    chdir(szFileDir.c_str());
    while((entry = readdir(dp)) != NULL){
        lstat(entry->d_name,&statbuf);
        if(S_ISREG(statbuf.st_mode))
            remove(entry->d_name);
    }
    return 0;
}

string getSFZImageURI(const string& workingFolder) {
    string imgPath = workingFolder + "/idcard";
    DIR * dir;
    if((dir = opendir(imgPath.c_str())) == NULL)
        mkdir(imgPath.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    char var[] ={5,  0,  1,  0,  91,  3,  51,  1,  90,  -77,  30,  0};
    string wlt = getSFZImageData();
    int ret = 1;
    //int ret = IDCReaderSDK.wltGetBMP(wlt, var);
    if (ret == 1) {
        LOGI("身份证照片解码成功");
        return imgPath + "/zp.bmp";
    } else {
        LOGE("身份证照片解码失败，错误代码：" + ret);
    }
    return "";
}

string getTwoNationCodes(string str) {
    int len = sizeof(NationThreeNationCodes)/sizeof(NationThreeNationCodes[0]);
    for (int i = 0; i < len; i++) {
        if (str == NationThreeNationCodes[i]) {
            return NationTwoNationCodes[i];
        }
    }
    return str;
}

