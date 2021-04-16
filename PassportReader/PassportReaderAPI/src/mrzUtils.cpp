//
// Created by 张迪 on 2020/5/15.
//

#include "mrzUtils.h"
#include <sys/stat.h>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <internalLogging.h>

std::map<std::string, std::string> ETHNICITY{
        {"01", "汉族"},
        {"02", "蒙古族"},
        {"03", "回族"},
        {"04", "藏族"},
        {"05", "维吾尔族"},
        {"06", "苗族"},
        {"07", "彝族"},
        {"08", "壮族"},
        {"09", "布依族"},
        {"10", "朝鲜族"},
        {"11", "满族"},
        {"12", "侗族"},
        {"13", "瑶族"},
        {"14", "白族"},
        {"15", "土家族"},
        {"16", "哈尼族"},
        {"17", "哈萨克族"},
        {"18", "傣族"},
        {"19", "黎族"},
        {"20", "傈傈族"},
        {"21", "佤族"},
        {"22", "畲族"},
        {"23", "高山族"},
        {"24", "拉祜族"},
        {"25", "水族"},
        {"26", "东乡族"},
        {"27", "纳西族"},
        {"28", "景颇族"},
        {"29", "柯尔克孜族"},
        {"30", "土族"},
        {"31", "达斡尔族"},
        {"32", "仫佬族"},
        {"33", "羌族"},
        {"34", "布朗族"},
        {"35", "撒拉族"},
        {"36", "毛难族"},
        {"37", "仡佬族"},
        {"38", "锡伯族"},
        {"39", "阿昌族"},
        {"40", "普米族"},
        {"41", "塔吉克族"},
        {"42", "怒族"},
        {"43", "乌孜别克族"},
        {"44", "俄罗斯族"},
        {"45", "鄂温克族"},
        {"46", "崩龙族"},
        {"47", "保安族"},
        {"48", "裕固族"},
        {"49", "京族"},
        {"50", "塔塔尔族"},
        {"51", "独龙族"},
        {"52", "鄂伦春族"},
        {"53", "赫哲族"},
        {"54", "门巴族"},
        {"55", "珞巴族"},
        {"56", "基洛族"},
        {"57", "其他"},
        {"58", "外国血统中国籍人士"},
        {"59", "港澳台"}};
std::map<std::string, std::string> GENDER{
        {"F", "F"},
        {"M", "M"},
        {"1", "M"},
        {"0", "F"}};

void split(const std::string &s, std::vector<std::string> &tokens, const std::string &delimiters) {
    std::string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    std::string::size_type pos = s.find_first_of(delimiters, lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos) {
        tokens.push_back(s.substr(lastPos, pos - lastPos));//use emplace_back after C++11
        lastPos = s.find_first_not_of(delimiters, pos);
        pos = s.find_first_of(delimiters, lastPos);
    }
}

std::string trim(std::string &s, std::string match = " ") {
    if (s.empty()) {
        return s;
    }
    s.erase(0, s.find_first_not_of(match));
    s.erase(s.find_last_not_of(match) + 1);
    return s;
}

//工具：判断year(只有年份的后两位)的前两位是20还是19
bool isTwentiethCentury(std::string year) {
    if (strncmp(year.c_str(), "50", 2) < 0)
        return true;
    return false;

}

std::string getYearPre(std::string year) {
    // 基于当前系统的当前日期/时间
    time_t now = time(0);

    // 把 now 转换为 tm 结构
    tm *gmtm = localtime(&now);
    int res = (1900 + gmtm->tm_year - std::stoi(year)) / 100;
    return std::to_string(res);
}

std::string changeDateFormat(std::string dateStr) {//把日期变成DD/MM/YYYY格式
    return dateStr.substr(6, 2) + '/' + dateStr.substr(4, 2) + '/' + dateStr.substr(0, 4);
}

time_t mkgmtime(tm *pTm) {
    unsigned int year = pTm->tm_year + 1900;
    unsigned int mon = pTm->tm_mon + 1;
    unsigned int day = pTm->tm_mday;
    unsigned int hour = pTm->tm_hour;
    unsigned int min = pTm->tm_min;
    unsigned int sec = pTm->tm_sec;

    if (0 >= (int) (mon -= 2)) {    /* 1..12 -> 11,12,1..10 */
        mon += 12;      /* Puts Feb last since it has leap day */
        year -= 1;
    }

    return ((((unsigned long) (year / 4 - year / 100 + year / 400 + 367 * mon / 12 + day) +
              year * 365 - 719499
             ) * 24 + hour /* now have hours */
            ) * 60 + min /* now have minutes */
           ) * 60 + sec; /* finally seconds */
}

time_t str2time(const std::string &dateStr, const std::string &format) {
    tm t;
    memset(&t, 0, sizeof(tm));

    strptime(dateStr.c_str(), format.c_str(), &t);// windows下用不了

    return mkgmtime(&t);
}

time_t NowTime() {
    time_t t_Now = time(0);
    struct tm *tm_Now = localtime(&t_Now);
    tm_Now->tm_hour = 0;
    tm_Now->tm_min = 0;
    tm_Now->tm_sec = 0;
    return mktime(tm_Now);
}

bool isExpired(std::string dateStr) {
    time_t now = NowTime();
    time_t expireTime = str2time(dateStr, "%d/%m/%Y");
    return now > expireTime;
}

int getAge(std::string dateStr) {
    time_t birth = str2time(dateStr, "%d/%m/%Y");
    time_t now = NowTime();
    int age = (difftime(now, birth) + 86400L / 2) / 86400L / 365;
    return age;
}

int getFileSize(std::string path) {
    struct stat info;
    if (stat(path.c_str(), &info) == -1) {
        return -1;
    }
    return info.st_size;
}

std::string delN(std::string ocrInfo) {
    ocrInfo.erase(remove(ocrInfo.begin(), ocrInfo.end(), '\n'), ocrInfo.end());
    ocrInfo.erase(remove(ocrInfo.begin(), ocrInfo.end(), '\r'), ocrInfo.end());
    return ocrInfo;
}

std::string
processMRZ(std::string mrzCode, DOC_TYPE docType, std::string headImage, std::string scanImage,
           std::string irImage, std::string uvImage, std::string uvImageBack) {
    if (mrzCode.empty() || mrzCode.length() == 0)
        return "{\"iret\":-9}";
    std::string jsonStr;
    switch (docType) {
        case PASSPORT: {
            jsonStr = processPassportJson(mrzCode, "", headImage, scanImage, irImage, uvImage,
                                          docType, -1);
            break;
        }
        case PASSPORT_WITHOUT_CHIP: {
            jsonStr = processPassportJson(mrzCode, "", headImage, scanImage, irImage, uvImage,
                                          docType, -1);
            break;
        }
        case HKMO_EXIT_ENTRY_PERMIT: {
            jsonStr = processEEPJson(mrzCode, "", headImage, scanImage, irImage, uvImage, docType,
                                     -1);
            break;
        }
        case HKMO_HOME_RETURN_PERMIT: {
            jsonStr = processHKMOHRPJson(mrzCode, "", headImage, scanImage, irImage, uvImageBack,
                                         docType, -1);
            break;
        }
        case HKMO_HOME_RETURN_PERMIT_NOCHIP: {
            jsonStr = processHKMOHRPJson(mrzCode, "", headImage, scanImage, irImage, uvImageBack,
                                         docType, -1);
            break;
        }
        case TW_HOME_RETURN_PERMIT: {
            jsonStr = processTWHRPJson(mrzCode, "", headImage, scanImage, irImage, uvImageBack,
                                       docType, -1);
            break;
        }
        case TAIWAN_PASSPORT: {
            jsonStr = processEEPJson(mrzCode, "", headImage, scanImage, irImage, uvImage, docType,
                                     -1);
            break;
        }
        default: {
            return "{\"iret\":-9}";
        }
    }
    return jsonStr;
}

std::string processDG(std::string DG1, std::string DG11, DOC_TYPE docType, std::string headImage,
                      std::string scanImage, std::string irImage, std::string uvImage,
                      std::string uvImageBack) {
    if (DG1.empty() || DG1.length() == 0)
        return "{\"iret\":-9}";
    std::string jsonStr;
    switch (docType) {
        case PASSPORT: {
            jsonStr = processPassportJson(DG1, DG11, headImage, scanImage, irImage, uvImage,
                                          docType, 1);
            break;
        }
        case HKMO_EXIT_ENTRY_PERMIT: {
            jsonStr = processEEPJson(DG1, DG11, headImage, scanImage, irImage, uvImage, docType,
                                     1);
            break;
        }
        case HKMO_HOME_RETURN_PERMIT: {
            jsonStr = processHKMOHRPJson(DG1, DG11, headImage, scanImage, irImage, uvImageBack,
                                         docType,
                                         1);
            break;
        }
        case TW_HOME_RETURN_PERMIT: {
            jsonStr = processTWHRPJson(DG1, DG11, headImage, scanImage, irImage, uvImageBack,
                                       docType,
                                       1);
            break;
        }
        case TAIWAN_PASSPORT: {
            jsonStr = processEEPJson(DG1, DG11, headImage, scanImage, irImage, uvImage, docType,
                                     1);
            break;
        }
        default: {
            return "{\"iret\":-9}";
        }
    }
    return jsonStr;
}
//"张迪             10119970503河南省方城县博望镇杨岗村张八庄５０号                 411322199705032911方城县公安局         2013071620230716                  \0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
//15                1 2   8             35                                          18                15                           8 8

std::string utf16Toutf8(std::string str) {
    if (str.empty() || str.length() == 0)
        return "";
    try {
        std::vector<unsigned short> utf16line((unsigned short *) str.data(),
                                              (unsigned short *) str.data() + str.size() / 2);
        str.clear();
        utf8::utf16to8(utf16line.begin(), utf16line.end(), back_inserter(str));

    }
    catch (const utf8::invalid_utf16 &) {
        // bad UTF-16 data!
    }
    return str;
}

std::string processIDCARDInfo(std::string sfzInfo, std::string headImage) {
    if (sfzInfo.empty() || sfzInfo.length() == 0)
        return "";
    std::string name, address, authority, birthday, ethnicity, idnumber, validate, gender;

    name = utf16Toutf8(sfzInfo.substr(0, 30));
    address = utf16Toutf8(sfzInfo.substr(52, 70));
    authority = utf16Toutf8(sfzInfo.substr(158, 30));

    trim(name);
    trim(address);
    trim(authority);

    birthday = utf16Toutf8(sfzInfo.substr(36, 16));
    ethnicity = utf16Toutf8(sfzInfo.substr(32, 4));
    idnumber = utf16Toutf8(sfzInfo.substr(122, 36));
    validate = utf16Toutf8(sfzInfo.substr(188, 32));
    gender = utf16Toutf8(sfzInfo.substr(30, 2));

    if (gender == "1")
        gender = "M";
    else
        gender = "F";
    //std::vector<std::string> buffers;
    std::stringstream json;
    //split(sfzInfo,buffers," ");
    json << "{"
         << "\"iret\":" << 0 << ","
         << "\"IDType\":" << 0 << ","
         << "\"PicPath\":\"" << headImage << "\","
         << "\"Address\":\"" << address << "\","
         << "\"Authority\":\"" << authority << "\","
         << "\"Birthdate\":\"" << birthday << "\","
         << "\"Ethnicity\":\"" << ETHNICITY[ethnicity] << "\","
         << "\"Gender\":\"" << gender << "\","
         << "\"IDnumber\":\"" << idnumber << "\","
         << "\"Name\":\"" << name << "\","
         << "\"Validity_Start\":\"" << validate.substr(0, 8) << "\","
         << "\"Validity_Termi\":\"" << validate.substr(8, std::string::npos) << "\""
         << "}" << std::ends;
    return json.str();
}


void parseName(std::string nameLine, std::string &firstName, std::string &lastName) {
    int index = nameLine.find("<<");
    if (index < 0) { return; }
    std::string lastnameLine = nameLine.substr(0, index);//姓
    std::string firstnameLine = nameLine.substr(index, std::string::npos);//名
    std::vector<std::string> buffers1;
    std::vector<std::string> buffers2;
    split(lastnameLine, buffers1, "<");
    split(firstnameLine, buffers2, "<");
    for (int i = 0; i < buffers2.size(); i++) {
        firstName = firstName + buffers2[i] + " ";
    }
    firstName = firstName.substr(0, firstName.length() - 1);
    for (int i = 0; i < buffers1.size(); i++) {
        lastName = lastName + buffers1[i] + " ";
    }
    lastName = lastName.substr(0, lastName.length() - 1);
}

std::string
processHKMOHRPJson(std::string mrzCode, std::string DG11, std::string headImage,
                   std::string scanImage,
                   std::string irImage, std::string uvImage, DOC_TYPE docType, int chipStatus) {
    std::stringstream json;
    std::string jsonStr;
    mrzCode = delN(mrzCode);//把OCR字符串中间的换行符号去除
    if (mrzCode.size() != 90) { return "{\"iret\":-9}"; }//如果长度不对直接返回空
    std::string firstLine = mrzCode.substr(0, 30);
    std::string secondLine = mrzCode.substr(30, 30);
    std::string nameLine = mrzCode.substr(60, 30);//这个是第三行，我把它给分割
    std::string firstname = "";
    std::string lastname = "";
    std::string birthPre = "";
    std::string validPre = "";
    parseName(nameLine, firstname, lastname);
    if (mrzCode.substr(0, 2).compare("C<") == 0) {
        if (!checkHKMOHRPOLDMRZ(mrzCode)) { return "{\"iret\":-9}"; }
        //老版回乡证
        if (secondLine.substr(27, 1) == "0") {
            birthPre = "18";
        } else if (secondLine.substr(27, 1) == "1") {
            birthPre = "19";
        } else {
            birthPre = "20";
        }
        if (secondLine.substr(28, 1) == "0") {
            validPre = "18";
        } else if (secondLine.substr(28, 1) == "1") {
            validPre = "19";
        } else {
            validPre = "20";
        }
        std::string expiredDate = changeDateFormat(validPre + secondLine.substr(8, 6));
        std::string birthDate = changeDateFormat(birthPre + secondLine.substr(0, 6));
        if (firstLine.substr(15, 1) == "M")
            docType = MO_HOME_RETURN_PERMIT;
        else
            docType = HK_HOME_RETURN_PERMIT;
        json << "{"
             << "\"iret\":" << 0 << ","
             << "\"IDType\":" << docType << ","
             << "\"PicPath\":\"" << headImage << "\","
             << "\"FrontPicPath\":\"" << scanImage << "\","
             << "\"BackPicPath\":\"" << "" << "\","
             << "\"PicDataLen\":" << getFileSize(headImage) << ","
             << "\"FrontDataLen\":" << getFileSize(scanImage) << ","
             << "\"BackDataLen\":" << 0 << ","
             << "\"RedImage\":\"" << irImage << "\","
             << "\"VioletImage\":\"" << uvImage << "\","
             << "\"OtherFirstName\":\"" << firstname << "\","
             << "\"OtherLastName\":\"" << lastname << "\","
             << "\"EnglishName\":\"" << firstname + " " + lastname << "\","
             << "\"CustName\":\"" << DG11 << "\","
             << "\"Gender\":\"" << GENDER[secondLine.substr(7, 1)] << "\","
             << "\"Birthday\":\"" << birthDate << "\","
             << "\"Age\":" << getAge(birthDate) << ","
             << "\"IDIssueDate\":\"" << "" << "\","
             << "\"IDExpiryDate\":\"" << expiredDate << "\","
             << "\"IsExpired\":\"" << (isExpired(expiredDate) ? "true" : "false") << "\","
             << "\"Nationality\":\"" << "CHN" << "\","
             << "\"Nation\":\"" << "" << "\","
             << "\"IDIssuingOrg\":\"" << firstLine.substr(2, 3) << "\","
             << "\"IDNum\":\"" << secondLine.substr(15, 11) << "\","
             << "\"LocalIDCardNo\":\"" << "" << "\","
             << "\"MRZ1\":\"" << firstLine << "\","
             << "\"MRZ2\":\"" << secondLine << "\","
             << "\"MRZ3\":\"" << nameLine << "\","
             << "\"Authenticy\":\"" << "" << "\","
             << "\"IssuingCount\":\"" << "" << "\","
             << "\"MediaType\":\"" << (chipStatus == 1 ? "RFID" : "OCR") << "\""
             << "}" << std::ends;

        jsonStr = json.str();
        return jsonStr;
    }
    if (!checkHKMOHRPMRZ(mrzCode)) { return "{\"iret\":-9}"; }
    if (secondLine.substr(18, 1) == "A") {
        birthPre = "18";
    } else if (secondLine.substr(18, 1) == "B") {
        birthPre = "19";
    } else {
        birthPre = "20";
    }
    if (isTwentiethCentury(firstLine.substr(15, 2))) {
        validPre = "20";
    } else {
        validPre = "19";
    }
    std::string hkid = secondLine.substr(19, 9);
    if (hkid.find("<") != std::string::npos) {
        hkid = secondLine.substr(19, 8);
    }

    std::string expiredDate = changeDateFormat(validPre + firstLine.substr(15, 6));
    std::string birthDate = changeDateFormat(birthPre + firstLine.substr(23, 6));

    if (firstLine.substr(2, 1) == "M")
        docType = MO_HOME_RETURN_PERMIT;
    else
        docType = HK_HOME_RETURN_PERMIT;
    json << "{"
         << "\"iret\":" << 0 << ","
         << "\"IDType\":" << docType << ","
         << "\"PicPath\":\"" << headImage << "\","
         << "\"FrontPicPath\":\"" << scanImage << "\","
         << "\"BackPicPath\":\"" << "" << "\","
         << "\"PicDataLen\":" << getFileSize(headImage) << ","
         << "\"FrontDataLen\":" << getFileSize(scanImage) << ","
         << "\"BackDataLen\":" << 0 << ","
         << "\"RedImage\":\"" << irImage << "\","
         << "\"VioletImage\":\"" << uvImage << "\","
         << "\"OtherFirstName\":\"" << firstname << "\","
         << "\"OtherLastName\":\"" << lastname << "\","
         << "\"EnglishName\":\"" << firstname + " " + lastname << "\","
         << "\"CustName\":\"" << DG11 << "\","
         << "\"Gender\":\"" << GENDER[firstLine.substr(22, 1)] << "\","
         << "\"Birthday\":\"" << birthDate << "\","
         << "\"Age\":" << getAge(birthDate) << ","
         << "\"IDIssueDate\":\"" << "" << "\","
         << "\"IDExpiryDate\":\"" << expiredDate << "\","
         << "\"IsExpired\":\"" << (isExpired(expiredDate) ? "true" : "false") << "\","
         << "\"Nationality\":\"" << "CHN" << "\","
         << "\"Nation\":\"" << "" << "\","
         << "\"IDIssuingOrg\":\"" << "CHN" << "\","
         << "\"IDNum\":\"" << firstLine.substr(2, 9) << "\","
         << "\"LocalIDCardNo\":\"" << hkid << "\","
         << "\"MRZ1\":\"" << firstLine << "\","
         << "\"MRZ2\":\"" << secondLine << "\","
         << "\"MRZ3\":\"" << nameLine << "\","
         << "\"Authenticy\":\"" << "" << "\","
         << "\"IssuingCount\":\"" << firstLine.substr(12, 2) << "\","
         << "\"MediaType\":\"" << (chipStatus == 1 ? "RFID" : "OCR") << "\""
         << "}" << std::ends;
    jsonStr = json.str();
    return jsonStr;
}

std::string
processTWHRPJson(std::string mrzCode, std::string DG11, std::string headImage,
                 std::string scanImage,
                 std::string irImage, std::string uvImage, DOC_TYPE docType, int chipStatus) {
    mrzCode = delN(mrzCode);//把OCR字符串中间的换行符号去除
    if (mrzCode.size() != 90) { return "{\"iret\":-9}"; }//如果长度不对直接返回空
    if (!checkTWHRPMRZ(mrzCode)) { return "{\"iret\":-9}"; }

    std::string firstLine = mrzCode.substr(0, 30);
    std::string secondLine = mrzCode.substr(30, 30);
    std::string thirdLine = mrzCode.substr(60, 30);

    std::stringstream json;
    std::string jsonStr;
    std::string firstname = "";
    std::string lastname = "";
    std::string birthPre = "";
    std::string validPre = "";
    if (secondLine.substr(18, 1) == "A") {
        birthPre = "18";
    } else if (secondLine.substr(18, 1) == "B") {
        birthPre = "19";
    } else {
        birthPre = "20";
    }
    if (isTwentiethCentury(firstLine.substr(15, 2))) {
        validPre = "20";
    } else {
        validPre = "19";
    }
    parseName(thirdLine.substr(0, 26), firstname, lastname);

    std::string twid = secondLine.substr(19, 10);
    //剔除后面的<
    if (twid.find("<") != std::string::npos) {
        //hkid = hkid.substr(0, 8);
        int index = twid.find("<");
        twid = twid.substr(0, index);
    }


    std::string expiredDate = changeDateFormat(validPre + firstLine.substr(15, 6));
    std::string birthDate = changeDateFormat(birthPre + firstLine.substr(23, 6));

    json << "{"
         << "\"iret\":" << 0 << ","
         << "\"IDType\":" << docType << ","
         << "\"PicPath\":\"" << headImage << "\","
         << "\"FrontPicPath\":\"" << scanImage << "\","
         << "\"BackPicPath\":\"" << "" << "\","
         << "\"PicDataLen\":" << getFileSize(headImage) << ","
         << "\"FrontDataLen\":" << getFileSize(scanImage) << ","
         << "\"BackDataLen\":" << 0 << ","
         << "\"RedImage\":\"" << irImage << "\","
         << "\"VioletImage\":\"" << uvImage << "\","
         << "\"OtherFirstName\":\"" << firstname << "\","
         << "\"OtherLastName\":\"" << lastname << "\","
         << "\"EnglishName\":\"" << firstname + " " + lastname << "\","
         << "\"CustName\":\"" << DG11 << "\","
         << "\"Gender\":\"" << GENDER[firstLine.substr(22, 1)] << "\","
         << "\"Birthday\":\"" << birthDate << "\","
         << "\"Age\":" << getAge(birthDate) << ","
         << "\"IDIssueDate\":\"" << "" << "\","
         << "\"IDExpiryDate\":\"" << expiredDate << "\","
         << "\"IsExpired\":\"" << (isExpired(expiredDate) ? "true" : "false") << "\","
         << "\"Nationality\":\"" << "CHN" << "\","
         << "\"Nation\":\"" << "" << "\","
         << "\"IDIssuingOrg\":\"" << thirdLine.substr(26, 4) << "\","
         << "\"IDNum\":\"" << firstLine.substr(2, 8) << "\","
         << "\"LocalIDCardNo\":\"" << twid << "\","
         << "\"MRZ1\":\"" << firstLine << "\","
         << "\"MRZ2\":\"" << secondLine << "\","
         << "\"MRZ3\":\"" << thirdLine << "\","
         << "\"Authenticy\":\"" << "" << "\","
         << "\"IssuingCount\":\"" << firstLine.substr(12, 2) << "\","
         << "\"MediaType\":\"" << (chipStatus == 1 ? "RFID" : "OCR") << "\""
         << "}" << std::ends;


    jsonStr = json.str();
    return jsonStr;
}

std::string processPassportJson(std::string mrzCode, std::string DG11, std::string headImage,
                                std::string scanImage, std::string irImage, std::string uvImage,
                                DOC_TYPE docType, int chipStatus) {
    //如果是MRZ，会删除换行，如果是DG1，没有变化
    mrzCode = delN(mrzCode);
    std::stringstream json;
    std::string jsonStr;
    if (mrzCode.size() != 88) { return "{\"iret\":-9}"; }//如果长度不对直接返回
    if (!checkPassportMRZ(mrzCode)) { return "{\"iret\":-9}"; }
    std::string firstLine = mrzCode.substr(0, 44);
    std::string secondLine = mrzCode.substr(44, 44);
    std::string firstname = "";
    std::string lastname = "";
    std::string birthPre = "";
    std::string validPre = "";
    birthPre = getYearPre(secondLine.substr(13, 2));
    if (isTwentiethCentury(secondLine.substr(21, 2))) {
        validPre = "20";
    } else {
        validPre = "19";
    }
    parseName(firstLine.substr(5, 39), firstname, lastname);

    std::string expiredDate = changeDateFormat(validPre + secondLine.substr(21, 6));
    std::string birthDate = changeDateFormat(birthPre + secondLine.substr(13, 6));
    std::string idnum = secondLine.substr(0, 9);
    std::string nationality = secondLine.substr(10, 3);
    std::string issuingAuthority = firstLine.substr(2, 3);
//    trim(idnum, "<");
//    replace(idnum.begin(), idnum.end(), "<", " ");
    idnum.erase(remove(idnum.begin(), idnum.end(), '<'), idnum.end());
    trim(nationality, "<");
    trim(issuingAuthority, "<");
    if (nationality != "CHN")DG11 = "";
    json << "{"
         << "\"iret\":" << 0 << ","
         << "\"IDType\":" << docType << ","
         << "\"PicPath\":\"" << headImage << "\","
         << "\"FrontPicPath\":\"" << scanImage << "\","
         << "\"BackPicPath\":\"" << "" << "\","
         << "\"PicDataLen\":" << getFileSize(headImage) << ","
         << "\"FrontDataLen\":" << getFileSize(scanImage) << ","
         << "\"BackDataLen\":" << 0 << ","
         << "\"RedImage\":\"" << irImage << "\","
         << "\"VioletImage\":\"" << uvImage << "\","
         << "\"OtherFirstName\":\"" << firstname << "\","
         << "\"OtherLastName\":\"" << lastname << "\","
         << "\"EnglishName\":\"" << firstname + " " + lastname << "\","
         << "\"CustName\":\"" << DG11 << "\","
         << "\"Gender\":\"" << GENDER[secondLine.substr(20, 1)] << "\","
         << "\"Birthday\":\"" << birthDate << "\","
         << "\"Age\":" << getAge(birthDate) << ","
         << "\"IDIssueDate\":\"" << "" << "\","
         << "\"IDExpiryDate\":\"" << expiredDate << "\","
         << "\"IsExpired\":\"" << (isExpired(expiredDate) ? "true" : "false") << "\","
         << "\"Nationality\":\"" << nationality << "\","
         << "\"Nation\":\"" << "" << "\","
         << "\"IDIssuingOrg\":\"" << issuingAuthority << "\","
         << "\"IDNum\":\"" << idnum << "\","
         << "\"LocalIDCardNo\":\"" << "" << "\","
         << "\"MRZ1\":\"" << firstLine << "\","
         << "\"MRZ2\":\"" << secondLine << "\","
         << "\"MRZ3\":\"" << "" << "\","
         << "\"Authenticy\":\"" << "" << "\","
         << "\"IssuingCount\":\"" << "" << "\","
         << "\"MediaType\":\"" << (chipStatus == 1 ? "RFID" : "OCR") << "\""
         << "}" << std::ends;
    jsonStr = json.str();
    return jsonStr;
}

std::string
processEEPJson(std::string mrzCode, std::string DG11, std::string headImage, std::string scanImage,
               std::string irImage, std::string uvImage, DOC_TYPE docType, int chipStatus) {
    std::stringstream json;
    std::string jsonStr;

    std::string firstname = "";
    std::string lastname = "";
    std::string birthPre = "";
    std::string validPre = "";
    std::string gender = "";
    mrzCode = delN(mrzCode);
    if (mrzCode.size() != 90 && mrzCode.size() != 30) { return "{\"iret\":-9}"; }//如果长度不对直接返回空
    if (!checkEEPMRZ(mrzCode)) { return "{\"iret\":-9}"; }
    std::string firstLine = mrzCode.substr(0, 30);
    std::string secondLine = "";
    std::string thirdLine = "";
    if (chipStatus == 1) {
        //判断是芯片
        secondLine = mrzCode.substr(30, 30);
        thirdLine = mrzCode.substr(60, 30);
        gender = GENDER[thirdLine.substr(0, 1)];
        parseName(secondLine.substr(12, 18), firstname, lastname);
    }
    birthPre = getYearPre(firstLine.substr(21, 2));
    if (isTwentiethCentury(firstLine.substr(13, 2))) {
        validPre = "20";
    } else {
        validPre = "19";
    }
    std::string expiredDate = changeDateFormat(validPre + firstLine.substr(13, 6));
    std::string birthDate = changeDateFormat(birthPre + firstLine.substr(21, 6));
    json << "{"
         << "\"iret\":" << 0 << ","
         << "\"IDType\":" << docType << ","
         << "\"PicPath\":\"" << headImage << "\","
         << "\"FrontPicPath\":\"" << scanImage << "\","
         << "\"BackPicPath\":\"" << "" << "\","
         << "\"PicDataLen\":" << getFileSize(headImage) << ","
         << "\"FrontDataLen\":" << getFileSize(scanImage) << ","
         << "\"BackDataLen\":" << 0 << ","
         << "\"RedImage\":\"" << irImage << "\","
         << "\"VioletImage\":\"" << uvImage << "\","
         << "\"OtherFirstName\":\"" << firstname << "\","
         << "\"OtherLastName\":\"" << lastname << "\","
         << "\"EnglishName\":\"" << firstname + " " + lastname << "\","
         << "\"CustName\":\"" << DG11 << "\","
         << "\"Gender\":\"" << gender << "\","
         << "\"Birthday\":\"" << birthDate << "\","
         << "\"Age\":" << getAge(birthDate) << ","
         << "\"IDIssueDate\":\"" << "" << "\","
         << "\"IDExpiryDate\":\"" << expiredDate << "\","
         << "\"IsExpired\":\"" << (isExpired(expiredDate) ? "true" : "false") << "\","
         << "\"Nationality\":\"" << "CHN" << "\","
         << "\"Nation\":\"" << "" << "\","
         << "\"IDIssuingOrg\":\"" << "CHN" << "\","
         << "\"IDNum\":\"" << firstLine.substr(2, 9) << "\","
         << "\"LocalIDCardNo\":\"" << "" << "\","
         << "\"MRZ1\":\"" << firstLine << "\","
         << "\"MRZ2\":\"" << "" << "\","
         << "\"MRZ3\":\"" << "" << "\","
         << "\"Authenticy\":\"" << "" << "\","
         << "\"IssuingCount\":\"" << "" << "\","
         << "\"MediaType\":\"" << (chipStatus == 1 ? "RFID" : "OCR") << "\""
         << "}" << std::ends;
    jsonStr = json.str();
    return jsonStr;
}

std::vector<int> str2num1(std::string s) {
    std::vector<int> num;

    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            num.push_back(c - '0');
        } else if (c >= 'A' && c <= 'Z') {
            num.push_back(c - 'A' + 10);
        } else if ('<' == c) {
            num.push_back(0);
        } else {
            return std::vector<int>(0);
        }
    }
    return num;
}

bool PassportCheck(std::string number, char checkBit) {
    int sum = 0;
    int check = checkBit - '0';
    if (checkBit == '<') check = 0;
    int BaseWeight[] = {7, 3, 1};

    std::vector<int> intNumber = str2num1(number);
    for (int i = 0, k = 0; i < intNumber.size(); i++) {
        sum += intNumber[i] * BaseWeight[k];
        k = (k + 1) % 3;
    }
    return ((sum % 10) == check);
}

bool checkPassportMRZ(std::string mrzcode) {
    mrzcode = delN(mrzcode);
    //读护照的机读码进行校验位比对
    //注意： 第一行没有校验位，所以OCR错误无法识别出来
    if (mrzcode.size() != 88) { return false; }//如果长度不对直接返回
    //机读码分行,并判断每一行的长度
    std::vector<std::string> splitstr;
    splitstr.push_back(std::string(mrzcode, 0, 44));
    splitstr.push_back(std::string(mrzcode, 44, 44));

    if (splitstr[1].length() < 44) {
        return false;
    }

    //对证件号码进行校验
//    bool idNumCheck = PassportCheck(splitstr[1].substr(0, 9), splitstr[1].substr(9, 1).at(0));
    //对证件出生日期进行校验
    bool birthCheck = PassportCheck(splitstr[1].substr(13, 6), splitstr[1].substr(19, 1).at(0));
    //对证件有效日期进行校验
    bool validCheck = PassportCheck(splitstr[1].substr(21, 6), splitstr[1].substr(27, 1).at(0));
    //附加校验位
//    bool additionCheck = PassportCheck(splitstr[1].substr(28, 14), splitstr[1].substr(42, 1).at(0));
    //第2行整个校验位
//    std::string temp =
//            splitstr[1].substr(0, 10) + splitstr[1].substr(13, 7) + splitstr[1].substr(21, 22);
//    bool fullCheck = PassportCheck(temp, splitstr[1].substr(43, 1).at(0));
    return birthCheck && validCheck;

}

void mrzInt2char(std::string &input, int startPos, int endPos) {
    std::replace(input.begin() + startPos, input.begin() + endPos, '0', 'O');
    std::replace(input.begin() + startPos, input.begin() + endPos, '1', 'I');
    std::replace(input.begin() + startPos, input.begin() + endPos, '2', 'Z');
    std::replace(input.begin() + startPos, input.begin() + endPos, '5', 'S');
    std::replace(input.begin() + startPos, input.begin() + endPos, '8', 'B');
}

void mrzChar2int(std::string &input, int startPos, int endPos) {
    std::replace(input.begin() + startPos, input.begin() + endPos, 'O', '0');
    std::replace(input.begin() + startPos, input.begin() + endPos, 'D', '0');
    std::replace(input.begin() + startPos, input.begin() + endPos, 'I', '1');
    std::replace(input.begin() + startPos, input.begin() + endPos, 'Z', '2');
    std::replace(input.begin() + startPos, input.begin() + endPos, 'U', '0');
    std::replace(input.begin() + startPos, input.begin() + endPos, 'S', '5');
    std::replace(input.begin() + startPos, input.begin() + endPos, 'B', '8');
}

void correctPassportMrz(std::string &mrzCode) {
    if (mrzCode.size() < 89) { return; }
    mrzInt2char(mrzCode, 0, 44);
    mrzChar2int(mrzCode, 45 + 13, 45 + 13 + 7);
    mrzChar2int(mrzCode, 45 + 21, 45 + 21 + 7);
    if (mrzCode[45 + 20] == 'H') {
        mrzCode[45 + 20] = 'M';
    }
}

bool checkHKMOHRPOLDMRZ(std::string mrzCode) {
    //对回乡证的机读码进行校验, 不支持老版回乡证
    mrzCode = delN(mrzCode);//把OCR字符串中间的换行符号去除
    if (mrzCode.size() < 60) { return false; }//如果长度不对直接返回
    std::string firstLine = mrzCode.substr(0, 30);
    std::string secondLine = mrzCode.substr(30, 30);
    //std::string thirdLine = mrzCode.substr(60,30);


//    bool nameCheck = PassportCheck(firstLine.substr(5, 21), mrzCode.substr(26, 1).at(0));
//    bool firstlineCheck = PassportCheck(firstLine.substr(0, 29), mrzCode.substr(29, 1).at(0));
//    证件号校验
//    bool idNumCheck = PassportCheck(secondLine.substr(15, 11), secondLine.substr(26, 1).at(0));

//    bool secondlineCheck = PassportCheck(secondLine.substr(0, 29), secondLine.substr(29, 1).at(0));
    //证件有效期校验
    bool validCheck = PassportCheck(secondLine.substr(8, 6), secondLine.substr(14, 1).at(0));
    //生日校验
    bool birthCheck = PassportCheck(secondLine.substr(0, 6), secondLine.substr(6, 1).at(0));

    if (birthCheck && validCheck)
        return true;
    return false;

}

bool checkHKMOHRPMRZ(std::string mrzCode) {
    //对回乡证的机读码进行校验, 不支持老版回乡证
    mrzCode = delN(mrzCode);//把OCR字符串中间的换行符号去除
    if (mrzCode.size() < 60) { return false; }//如果长度不对直接返回
    std::string firstLine = mrzCode.substr(0, 30);
    std::string secondLine = mrzCode.substr(30, 30);
    //std::string thirdLine = mrzCode.substr(60,30);

    //证件号校验
//    bool idNumCheck = PassportCheck(firstLine.substr(2, 9), mrzCode.substr(11, 1).at(0));
    //签发次数校验
//    bool renewalTimesCheck = PassportCheck(firstLine.substr(12, 2), mrzCode.substr(14, 1).at(0));
    //证件有效期校验
    bool validCheck = PassportCheck(firstLine.substr(15, 6), mrzCode.substr(21, 1).at(0));
    //生日校验
    bool birthCheck = PassportCheck(firstLine.substr(23, 6), mrzCode.substr(29, 1).at(0));
    //香港身份证号校验
//    bool hkidCheck = PassportCheck(secondLine.substr(19, 9), secondLine.substr(28, 1).at(0));

    //总校验 第一行3-22位、24-30位，第二行20-29位
//    std::string temp =
//            firstLine.substr(2, 20) + firstLine.substr(23, 7) + secondLine.substr(19, 10);
//    bool fullCheck = PassportCheck(temp, secondLine.substr(29, 1).at(0));
    if (birthCheck && validCheck)
        return true;
    return false;

}

bool checkTWHRPMRZ(std::string mrzcode) {
    //对台湾居民往来大陆通行证的机读码进行校验. 传入的mrzcode均包含换行符
    mrzcode = delN(mrzcode);//把OCR字符串中间的换行符号去除
    if (mrzcode.size() < 60) { return false; }//如果长度不对直接返回
    std::string firstLine = mrzcode.substr(0, 30);
    std::string secondLine = mrzcode.substr(30, 30);
    //std::string thirdLine = mrzcode.substr(60,30);

    //证件号校验
//    bool idNumCheck = PassportCheck(firstLine.substr(2, 8), mrzcode.substr(11, 1).at(0));
    //签发次数校验
//    bool renewalTimesCheck = PassportCheck(firstLine.substr(12, 2), mrzcode.substr(14, 1).at(0));
    //证件有效期校验
    bool validCheck = PassportCheck(firstLine.substr(15, 6), mrzcode.substr(21, 1).at(0));
    //生日校验
    bool birthCheck = PassportCheck(firstLine.substr(23, 6), mrzcode.substr(29, 1).at(0));

    //总校验 第一行3-22位、24-30位，第二行20-29位
//    std::string temp =
//            firstLine.substr(2, 20) + firstLine.substr(23, 7) + secondLine.substr(19, 10);
//    bool fullCheck = PassportCheck(temp, secondLine.substr(29, 1).at(0));
    if (birthCheck && validCheck)
        return true;
    return false;

}

bool checkEEPMRZ(std::string mrzcode) {
    //对港澳通行证和台湾通行证的校验位进行校验
    if (mrzcode.length() < 30)
        return false;
//    bool idNumCheck = PassportCheck(mrzcode.substr(2, 9), mrzcode.substr(11, 1).at(0));
    bool validCheck = PassportCheck(mrzcode.substr(13, 6), mrzcode.substr(19, 1).at(0));
    bool birthCheck = PassportCheck(mrzcode.substr(21, 6), mrzcode.substr(27, 1).at(0));
//    std::string temp = mrzcode.substr(2, 10) + mrzcode.substr(13, 7) + mrzcode.substr(21, 7);
//    bool fullCheck = PassportCheck(temp, mrzcode.substr(29, 1).at(0));
    if (birthCheck && validCheck)
        return true;
    return false;

}