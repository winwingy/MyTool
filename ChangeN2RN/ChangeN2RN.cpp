// ChangeN2RN.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <string>
using std::string;
bool ChangeNToRN(string strOldFile)
{
	FILE* pFile = fopen( strOldFile.c_str(), "r" );
	if ( pFile == NULL )
	{
		return false;
	}

	int iLastPoint = strOldFile.find_last_of('.');//返回 的是下标
	char pszNewName[300];
	int iNameLen = 0;
	for ( ; iNameLen < iLastPoint; iNameLen++ )
	{
		pszNewName[iNameLen] = strOldFile[iNameLen];
	}
	char pszAdd[] = "_new";
	int iAddLen = strlen(pszAdd);
	for ( int i = iNameLen, int j = 0; i < iNameLen + iAddLen; i++, j++)
	{
		pszNewName[i] = pszAdd[j];
	}
	iNameLen += iAddLen; 
	pszNewName[iNameLen++] = '.';
	while (  strOldFile[++iLastPoint] != 0 )
	{
		pszNewName[iNameLen++] = strOldFile[iLastPoint];
	}
	pszNewName[iNameLen] = 0;

	FILE* pFileWrite = fopen( pszNewName, "w" );
	if ( pFileWrite == NULL )
	{
		return false;
	}

	char chRead;
	int iReadCnt;
	while( ( iReadCnt = fread ( &chRead, 1, 1, pFile ) ) > 0 )
	{
		if ( chRead == '\r\n' )
		{		
			chRead = '\n';
		}
		fwrite( &chRead, 1, 1, pFileWrite );		
	}
	fclose(pFile);
	fclose(pFileWrite);
	return true;
}


int _tmain(int argc, _TCHAR* argv[])
{
	ChangeNToRN("D:\\workspace\\Note\\优先级.txt");
	ChangeNToRN("C:\\test.txt");
	return 0;
}

