// GetDriverStrings.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

vector<string> GetDriverStrings()
{
	vector<string> vecRet;
	TCHAR pszPerDriver[10];
	TCHAR szBuf[100];
	memset(szBuf, 0, sizeof(szBuf));
	DWORD dwLenth = GetLogicalDriveStrings(sizeof(szBuf)/sizeof(TCHAR), szBuf);
	for (TCHAR* pTemp = szBuf; *pTemp; pTemp += _tcslen(pTemp) + 1)//"C:\<>D:\<><>"
	{
		sprintf(szBuf, "%s",pTemp);
		vecRet.push_back(szBuf);
	}
	return vecRet;
}



int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> vecDrivers = GetDriverStrings();
	vector<string>::iterator iter = vecDrivers.begin();
	for (; iter != vecDrivers.end(); iter++)
	{
		cout<<*iter<<"\t";
	}
	getchar();
	return 0;
}

