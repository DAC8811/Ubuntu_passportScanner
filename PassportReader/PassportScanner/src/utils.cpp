#include <string>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fstream>
#include <fcntl.h>
#include <iostream>

#include "utils.h"
#include "internalLogging.h"
#include "getData.h"
#include "WltRS.h"


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
    // char var[] ={5,  0,  1,  0,  91,  3,  51,  1,  90,  -77,  30,  0};
    string SFZImage = getSFZImageData();
    // int ret = 1;
    // //int ret = IDCReaderSDK.wltGetBMP(wlt, var);
    int inBufsize = 1024;
    int iPhotoDataLen = 38862;
    char arrPhotoData[iPhotoDataLen];
    char test[1024];
    int iRet = WltRs::getBmp((char *)SFZImage.c_str(), 1024, arrPhotoData, iPhotoDataLen);
    //int len = getBmp((char*)SFZImage.c_str(),inBufsize,test,outBufsize,soPath.c_str());
    //printf("\niRet == %d\n",iRet);
    if(iRet > 0){
            string imagePath = imgPath + "/zp.bmp";
            FILE* fp_photo = fopen(imagePath.c_str(),"wb+");
            if(fp_photo == NULL)
            {
                LOGE(" write Photo error");
                return "";
            }
            fwrite(arrPhotoData, 1, iPhotoDataLen, fp_photo);
            fclose(fp_photo);
            LOGI("身份证照片解码成功");
            return imgPath + "/zp.bmp";
    }
    else{
        LOGE("身份证照片解码失败，错误代码：" + iRet);
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

inline bool isBase64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64Encode(char const* bytes_to_encode, int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i < 4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

std::string base64Decode(std::string & encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && isBase64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}

string getBase64Code(const string& picPath){
    char* buf_recv = new char[RECV_SIZE];
    ifstream inputStream(picPath, ios::in | ios::binary);
    inputStream.read(buf_recv,RECV_SIZE);
    long size = inputStream.gcount();
    cout << "picPath: " << picPath << endl;
    cout << "size: " << size << endl;
    return base64Encode(buf_recv,size);
}

