// GeneralRandom.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <time.h>


//产生随机数 iWay 0:只产生数字  1:产生数字和字母(只小写)
void generalRandom( char* szOut, int iBits, int iWay )
{
	if ( 0 == iWay )
	{
		for( int i(0); i < iBits; ++i )
		{
			int iRD = rand() % 10;			
			szOut[i] = '0' + iRD;			
		}
	}
	else	// 1:产生数字和字母(只小写)  0-9 a-z 10+26 = 36
	{
		for ( int i(0); i < iBits; ++i )
		{
			int iRD = rand() % 36;
			if ( iRD <= 9 )
			{
				szOut[i] = '0' + iRD;
			}
			else
			{
				szOut[i] = 'a' + iRD - 10;
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	for ( int i(0); i < 100; i++ )
	{
		char szRan[13] = {0};
		generalRandom(szRan, 12, 1);
		printf("%s\n", szRan);
	}

	system("pause");

	return 0;
}

