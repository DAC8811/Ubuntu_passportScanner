#include "pyContentCheck.h"
#include "ResultWeight.h"

 /*int pySourceSeperate(char* ImageLoc, char* nation, char* type, int mode)
{
	 ContentCheck M;
	 return M.SourceSeperate(ImageLoc, nation, type, mode);
}*/

 long long pyTrueResult(char* WIImageLoc, char* NIRImageLoc, char* UVImageLoc, char* nation, char* CodePath)
 {
     ContentCheck M;

     return M.TrueResult(WIImageLoc, NIRImageLoc, UVImageLoc, nation, CodePath);
 }

int pyTrueResult(char* WIImageLoc, char* NIRImageLoc, char* UVImageLoc, char* nation, char* CodePath, int(&RCode)[14])
{
	ContentCheck M;

	return M.TrueResult(WIImageLoc, NIRImageLoc, UVImageLoc, nation,CodePath,RCode);
}

long long pySourceSeperate_WI_UV_IR(char* WIImageLoc, char* NIRImageLoc, char* UVImageLoc, char* nation, char* CodePath)
 {
	 ContentCheck M;
	 int temp[14];
	 for (int m = 0; m < 14; ++m)
		 temp[m] = 5;

	 M.SourceSeperate_New(WIImageLoc, NIRImageLoc, UVImageLoc, nation, CodePath,temp);

	 long long result = 0;

	 for (int m = 13; m >= 0; --m)
		 result = result * 10 + temp[m];
	 return result;
 }

int pySourceSeperate_New(char* WIImageLoc, char* NIRImageLoc, char* UVImageLoc, char* nation, char* CodePath, int(&RCode)[14])
{
	ContentCheck M;
	return M.SourceSeperate_New(WIImageLoc, NIRImageLoc, UVImageLoc, nation, CodePath,RCode);
}

 int pyUVImageCheck(char* UVImageLoc)
 {
	 ContentCheck M;
	 return M.UVImageCheck(UVImageLoc);
 }
