#include "getData.h"
#include "internalLogging.h"
#include "passportScanner.h"
#include "utils.h"
#include "json/json.h"

#define LOG_TAG "PassportScanner"

using namespace std;

const string COMPILE_TIME = "2021-04-01,19:25:46";
const string WHITE_IMAGE_PATH = "/images/White.jpg";
const string CROP_HEAD_IMAGE_PATH = "/images/head.jpg";

bool connectionStatus = false;
bool scanning = false;
volatile bool cancelFlag = false;
int needSecondScan = 0;//0:不需要 1:需要正面 2:需要背面 正面指有mrz的面

Json::Value firstJSON;

int RFReaderFD;
int ScanFD;

string workFolder = "";

int setParam(string folder, string strDevPort, string strParam) {
    LOGI("setParam");
    workFolder = folder;
    return 0;
}

int openConnection(){
    LOG(INFO) << "版本号：CISReader-" << COMPILE_TIME;
    int ret = 0;
    if(workFolder == ""){
        LOGI("请先调用setParam设置工作目录folder");
        return -1;
    }
    if (connectionStatus) {
        LOGI("openConnection 已连接过");
        return 0;
    }
    //等待两个设备都加载好
    usleep(500*1000);
    LOGI("调用底层openConnection");
    int status = openConnect(workFolder, RFReaderFD, ScanFD);
    if(status == 0){
        LOGI("Sdk 初始化成功");
        beepBuzzer(1);
        connectionStatus = true;
        ret = 0;
    }
    else{
        LOGI("openConnection: 设备连接失败");
        ret = 1;
    }
    return ret;
}

int closeConnection(){
    LOGI("关闭连接");
    connectionStatus = false;
    closeConnect();
    return 0;
}

int getMediaStatus(int* status){
    status[0] = getMediaStatu();
    return 0;
}

int getVersion(char* psVersion,int* piRetLen){
    string versionStr = "CISReader-" + COMPILE_TIME;
    psVersion = (char*)versionStr.c_str();
    *piRetLen = versionStr.length();
    return 0;
}

string getCapabilities(){
    Json::Value result;
    Json::FastWriter writer;
    result["iret"] = RET_SUCCESS;
    result["msg"] = "RET_SUCCESS";
    result["bScanImage"] = true;
    result["bHeadImage"] = true;
    return writer.write(result);
}

std::string scanAndReadCardInfo(int timeout,int paramInt, string paramString){
    Json::FastWriter writer;

    if (!connectionStatus) {
        LOGE("设备未连接，请重新连接设备");
        Json::Value object;
        object["iret"] = RET_FAILURE;
        object["msg"] = "RET_FAILURE";
        return writer.write(object);
    }

    if (needSecondScan == 0) {
        firstJSON.clear();
        cancelFlag = false;
        //在每次扫描之前先删除之前的图片
        removeDir(workFolder + "/images");
        removeFile(workFolder + "/idcard/zp.bmp");
        setWorkingStatus(1);
    }
    scanning = true;
    beepBuzzer(1);
    int result = scanAndReadCard(timeout);
    scanning = false;
    Json::Value errjson;

    if (cancelFlag) {
        errjson["iret"] = RET_CANCEL;
        errjson["msg"] = "RET_CANCEL";
        cancelFlag = false;
        needSecondScan = 0;
        setWorkingStatus(0);
        return writer.write(errjson);
    }

    if (result != 0 && result != 7) {
        errjson["iret"] = result == -2 ? RET_TIMEOUT : RET_SCAN_FAILURE;
        errjson["msg"] = "RET_SCAN_FAILURE";
        beepBuzzer(3);
        setWorkingStatus(0);
        needSecondScan = 0;
        return writer.write(errjson);
    }

    if (result == 7) {//不支持的卡
        if (needSecondScan == 0) {
            errjson["iret"] = RET_INVALID_MEDIA;
            errjson["msg"] = "RET_INVALID_MEDIA";
            beepBuzzer(3);
            setWorkingStatus(0);
            return writer.write(errjson);
        } else {
            errjson["iret"] = RET_SCAN_NON_ATOMIC;
            errjson["msg"] = "RET_SCAN_NON_ATOMIC";
            return writer.write(errjson);
        }
    }

    string jsonInfo = getJson();
    //LOG(INFO) << "jsonInfo:" + jsonInfo;

    Json::Reader reader;
    Json::Value resjson;
    reader.parse(jsonInfo,resjson);
    if (!resjson["IDIssuingOrg"].isNull()) {
        string IDIssuingOrg = resjson["IDIssuingOrg"].asString();
        resjson["IDIssuingOrg"] = getTwoNationCodes(IDIssuingOrg);
    }
    int cardType = resjson["IDType"].asInt();
    if (cardType == CardType::ID_CARD) {
        getSFZImageURI(workFolder);
        resjson["iret"] = RET_SUCCESS;
        resjson["msg"] = "RET_SUCCESS";
        setWorkingStatus(0);
        beepBuzzer(2);
        resjson["PicBase64"] = getBase64Code(resjson["PicPath"].asString());
        return writer.write(resjson);
    } else if (cardType == CardType::PASSPORT || cardType == CardType::PASSPORT_WITHOUT_CHIP) {
        cropFace(workFolder + WHITE_IMAGE_PATH, workFolder + CROP_HEAD_IMAGE_PATH, cardType);
        setWorkingStatus(0);
        beepBuzzer(2);
        LOG(INFO) << "here" << endl;
        resjson["PicBase64"] = getBase64Code(resjson["PicPath"].asString());
        return writer.write(resjson);
    }
    if (cardType == CardType::UNKNOWN) {
        errjson["iret"] = RET_INVALID_MEDIA;
        errjson["msg"] = "RET_INVALID_MEDIA";
        beepBuzzer(3);
        setWorkingStatus(0);
        return writer.write(errjson);
    }
    resjson["iret"] = RET_SUCCESS;
    resjson["msg"] = "RET_SUCCESS";
    setWorkingStatus(0);
    beepBuzzer(2);
    resjson["PicBase64"] = getBase64Code(resjson["PicPath"].asString());
    return writer.write(resjson);
}

int cancel(){
    if (!connectionStatus) {
        LOGE("设备未连接，请重新连接设备");
        return -1;
    }
    if (scanning) {
        cancelFlag = true;
    }
    needSecondScan = 0;
    setWorkingStatus(0);
    return 0;
}

int reset(int iAction) {
    closeConnection();
    removeDir(workFolder + "/fix");
    if(workFolder != "")
        openConnection();
    return 0;
}