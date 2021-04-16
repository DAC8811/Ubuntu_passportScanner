#pragma once

#ifdef CONTENTCHECK_EXPORTS
#define CHECKPOINT_API __declspec(dllexport) 
#else
#define CHECKPOINT_API __declspec(dllimport) 
#endif




#include "ContentCheck.h"


//extern"C" CHECKPOINT_API int pySourceSeperate(char* ImageLoc, char* nation, char* type, int mode);
long long pyTrueResult(char* WIImageLoc, char* NIRImageLoc, char* UVImageLoc, char* nation, char* CodePath);

int pyTrueResult(char* WIImageLoc, char* NIRImageLoc, char* UVImageLoc, char* nation, char* CodePath,int(&RCode)[14]);

long long pySourceSeperate_WI_UV_IR(char* WIImageLoc, char* NIRImageLoc, char* UVImageLoc, char* nation,
                                    char* CodePath);

int pySourceSeperate_New(char* WIImageLoc, char* NIRImageLoc, char* UVImageLoc, char* nation, char* CodePath, int(&RCode)[14]);

int pyUVImageCheck(char* UVImageLoc);