//
// Created by ooxx on 9/21/18.
//

#ifndef PROJECT_LIBCHIP_H
#define PROJECT_LIBCHIP_H

#include <string>
#include "MRTD.h"
using namespace std;

int PassportTest(void);

int EchipOneCardRead(string code,
                     string &DG1,
                     string &DG11,
                     string path,
                     struct MrzInfoStruct & mrzInfo);
int EchipTwoCardRead(string code,
                     string &DG1,
                     string &DG11,
                     string path,
                     struct MrzInfoStruct & mrzInfo);
int EchipThreeCardRead(string code,
                       string &DG1,
                       string &DG11,
                       string path,
                     struct MrzInfoStruct & mrzInfo);
int IDCardRead(string &IDInfo,
               string &path);
int ReadChipUID(char *chipUID);
int CloseWire();

int AuthDev();

#endif //PROJECT_LIBCHIP_H
