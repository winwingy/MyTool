// DeleteFile.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

void DeleteFiles(char* pDir)
{
	CHAR pszPath[1024] = {0};
	sprintf(pszPath, "%s\\*.*", pDir);
	WIN32_FIND_DATA findData = {0};
	HANDLE hFind = FindFirstFile(pszPath, &findData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do 
	{
		if (findData.cFileName[0] == '.')
		{
			continue;
		}
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
// 				TCHAR szFile[1024];
// 				sprintf(szFile, "%s\\%s", pDir, findData.cFileName);								
// 				DeleteFiles(szFile);
		}
		else
		{
			TCHAR szFile[1024];
			sprintf(szFile, "%s\\%s", pDir, findData.cFileName);
			if ( strstr(szFile,  "0testCloseHandle") )
			{
				DeleteFile(szFile);
			}	

		}
	} while (FindNextFile(hFind, &findData));
}

int _tmain(int argc, _TCHAR* argv[])
{
	char szDir[] = "C:";
	DeleteFiles(szDir);


	return 0;
}

