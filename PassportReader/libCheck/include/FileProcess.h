#pragma once
#include <string>
#include <Cstring>
//#include <windows.h>
#include <opencv2/core/core.hpp> 
//#include "atlstr.h"
//#include <io.h>
#include <string>

//////////////////////////////////////////////////////////////////
/*-------------------�ļ������������ͷ�ļ�---------------------*/
//////////////////////////////////////////////////////////////////

/*char������תint�����ֵ�ģ��*/
int str2int(std::string strNum);
/*��ȡdll����·���ĵݹ�ģ��*/
//HMODULE GetSelfModuleHandle();
/*�����ļ��������ݸ�����ģ��*/
int FileVisit(std::string filepath, int layer);