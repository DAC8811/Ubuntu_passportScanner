#include "FileProcess.h"
#include <dirent.h>

/*char������תint�����ֵ�ģ��*/
int str2int(std::string strNum)
{
	if (strNum.empty())
		return -1;
	int ret = 0;
	int count = 1;
	for (int i = strNum.size() - 1; i >= 0; --i)
	{
		ret += (int(strNum[i] - '0')*count);
		count *= 10;
	}
	return ret;
}

/*��ȡdll����·���ĵݹ�ģ��*/
//HMODULE GetSelfModuleHandle()
//{
//	MEMORY_BASIC_INFORMATION mbi;
//	return ((::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0) ? (HMODULE)mbi.AllocationBase : NULL);
//}

/*�����ļ��������ݸ�����ģ��*/
int FileVisit(std::string filepath, int layer)
{
//	struct _finddata_t   filefind;
//	std::string  curr = filepath + "\\*.*";
//	int   done = 0, handle;
//	int filenum = 0;
//	if ((handle = _findfirst(curr.c_str(), &filefind)) == -1)return -1;
//	while (!(done = _findnext(handle, &filefind)))
//	{
//		//printf("%s\n", filefind.name);
//		if (!strcmp(filefind.name, "..")) {
//			continue;
//		}
//		//for (i = 0; i < layer; i++)cout << "     ";
//		if ((_A_SUBDIR == filefind.attrib)) //��Ŀ¼
//		{
//			//printf("----------%s\n", filefind.name);
//			//cout << filefind.name << "(dir)" << endl;
//			curr = filepath + "\\" + filefind.name;
//			//filenum += 1;
//		}
//		else//����Ŀ¼�����ļ�
//		{
//			filenum += 1;
//			//cout << path + "\\" + filefind.name << endl;
//		}
//	}
//	_findclose(handle);
//	return filenum;
	int file_count = 0;
	DIR * dirp;
	struct dirent * entry;

	dirp = opendir(filepath.c_str()); /* There should be error handling after this */
	while ((entry = readdir(dirp)) != NULL) {
		if (entry->d_type == DT_REG) { /* If the entry is a regular file */
			file_count++;
		}
	}
	closedir(dirp);

	return file_count;
}
