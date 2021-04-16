#ifndef PASSPORTSCANNER_UTILS_H
#define PASSPORTSCANNER_UTILS_H

enum DOC_TYPE{
    UNKNOWN = -1,                 //未知
    ID_CARD = 0,                  //二代证
    PASSPORT = 3,                 //护照         2行
    PASSPORT_WITHOUT_CHIP = 6,
    HKMO_EXIT_ENTRY_PERMIT = 2,        //港澳通行证    1行
    HKMO_HOME_RETURN_PERMIT = 4,  //回乡证，港澳居民来往内地通行证    3行, 这个会在processHXZJson里面再进行区分
    HKMO_HOME_RETURN_PERMIT_NOCHIP = 7,  //无芯片旧版回乡证，港澳居民来往内地通行证    3行
    HK_HOME_RETURN_PERMIT = 47,
    MO_HOME_RETURN_PERMIT = 48,
    TW_HOME_RETURN_PERMIT = 49,     //台胞证，台湾居民来往大陆通行证   3行
    TAIWAN_PASSPORT = 5            //台湾通行证    1行机读码
};

#endif