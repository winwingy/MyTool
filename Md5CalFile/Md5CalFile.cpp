// Md5CalFile.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "md5.h"
#include <Windows.h>
#include <string>
using std::string;

const int PER_MD5 = 10/* * 1024*/;

string Md5Partially( unsigned char* szInput, int iLength, int iPer )//abcde 2
{	
	MD5_CTX mc = {0};
	MD5Init( &mc );	
	for (; iLength >= iPer ; szInput += iPer, iLength -= iPer)
	{
		MD5Update(&mc, szInput, iPer);
	}
	if ( iLength >= 0 )
	{
		MD5Update(&mc, szInput, iLength);
	}	
	MD5Final(&mc);

	char szRet[3] = {0};

	string strRet;

	for (int i = 0; i < 16; ++i)
	{
		sprintf(szRet, "%02X", mc.digest[i]);
		strRet += szRet;
	}
	return strRet;
}


string Md5PartiallyMd5( unsigned char* szInput, int iLength, int iPer )//abcde 2
{	
	MD5_CTX mc = {0};
	MD5Init( &mc );	
	string strAllMd5;
	for (; iLength >= iPer ; szInput += iPer, iLength -= iPer)
	{
_LastOne:
		MD5Update(&mc, szInput, iPer);
		MD5Final(&mc);

		char szRet[3] = {0};

		string strTemp;

		for (int i = 0; i < 16; ++i)
		{
			sprintf(szRet, "%02X", mc.digest[i]);
			strTemp += szRet;
		}
		strAllMd5 += strTemp;
	}
	if ( iLength > 0 )
	{
		iLength = 0;
		goto _LastOne;	
	}

	MD5_CTX mcAll = {0};
	MD5Init( &mcAll );
	MD5Update(&mcAll, (unsigned char*)strAllMd5.c_str(), strAllMd5.size());
	MD5Final(&mcAll);


	char szRet[3] = {0};

	string strRet;

	for (int i = 0; i < 16; ++i)
	{
		sprintf(szRet, "%02X", mcAll.digest[i]);
		strRet += szRet;
	}
	return strRet;
}


char* FileMapping( char* szPath, LARGE_INTEGER& liSize  )
{
	HANDLE hFile = CreateFile( szPath, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if ( hFile == INVALID_HANDLE_VALUE )
	{
		printf("INVALID_HANDLE_VALUE\n");
	}


	GetFileSizeEx( hFile, &liSize );
	unsigned __int64 ullSize = liSize.QuadPart;

	HANDLE hFileMapping = CreateFileMapping( hFile, NULL, PAGE_READWRITE, DWORD( liSize.HighPart ), DWORD( liSize.LowPart ), NULL );
	if( !hFileMapping )
	{
		printf("hFileMapping Fail\n");
	}
	char* lpBuffer = (char*)MapViewOfFileEx( hFileMapping, FILE_MAP_WRITE, 0, 0, ullSize, NULL );

	if( !lpBuffer )
	{
		printf("lpBuffer Fail\n");
	}
	return lpBuffer;
}


int _tmain(int argc, _TCHAR* argv[])
{
	LARGE_INTEGER liSize = { 0 };
	char* lpBuffer = FileMapping("C:\\TestBig.txt", liSize);

	string strRet = Md5Partially((unsigned char*)lpBuffer, liSize.LowPart, PER_MD5);

	printf("%s\n", strRet.c_str());

	strRet = Md5Partially((unsigned char*)lpBuffer, liSize.LowPart, 1000*1024);

	printf("%s\n", strRet.c_str());

	strRet = Md5PartiallyMd5((unsigned char*)lpBuffer, liSize.LowPart, PER_MD5);

	printf("%s\n", strRet.c_str());

	system("pause");




	return 0;
}

