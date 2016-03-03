// DivideString.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
using std::string;
void devideString(const string& strString, char chDevide)
{
	//strString = "||ab|ee|||ffff|p"
	string strTemp;
	int i = 0;
	while (chDevide == strString[i])
	{
		++i;
	}
	int j = 0;
	for (; i < strString.size(); i++)
	{
		if (chDevide == strString[i])
		{
			strTemp[j] = 0;
			j = 0;
			printf("%s\n", strTemp.c_str());
			strTemp.clear();
			while (chDevide == strString[i])
			{
				++i;
			}
			--i;
		}
		else
		{
			strTemp[j] = strString[i];
			j++;
		}
		
	}
	if (chDevide != strString[i - 1])
	{
		strTemp[j] = 0;
		printf("%s\n", strTemp.c_str());
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	string strString = "||ab|ee|||ffff|p";
	devideString(strString, '|');
	getchar();
	return 0;
}

