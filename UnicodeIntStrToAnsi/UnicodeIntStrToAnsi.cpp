// UnicodeIntStrToAnsi.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <Windows.h>
#include <xstring>
using namespace std;
string UnicodeIntStrToAnsi( const std::string& strIntStr, bool bHex /*= false*/ );
int _tmain(int argc, _TCHAR* argv[])
{

	string strSrc = "\u1234 QQ\uabcds";
	string strRet = UnicodeIntStrToAnsi( strSrc, true);
	printf("%s\n", strRet.c_str());

	system("PAUSE");
	return 0;
}


/***********************************************************************************
* name       : StrToInt
* description: 将整数转化为字符串
* input      : strSrc 要转化的字符串，bHex 是否是十六进制整型数
* output     : NA
* return     : 转化后的整型数
* remark     : NA
***********************************************************************************/
int StrToInt ( const string& strSrc, bool bHex /*= false*/ )
{
	int iRet = 0;	
	if( bHex )
	{
		sscanf( strSrc.c_str(), "%x", &iRet );
	}
	else
	{
		sscanf( strSrc.c_str(), "%d", &iRet );
	}	

	return iRet;
}


/***********************************************************************************
* name       : UnicodeToAnsi
* description: 字符集转换: Unicode - Ansi
* input      : strSrc 要转化的Unicode字符集编码的字符串
* output     : NA
* return     : 转化后的Ansi字符集编码的字符串
* remark     : NA
***********************************************************************************/
string UnicodeToAnsi ( const wstring& wstrSrc )
{
	/*!< 分配目标空间, 一个16位Unicode字符最多可以转为4个字节*/
	int iAllocSize = static_cast< int >( ( wstrSrc.size() << 2 ) + 10 );
	char* pwszBuffer = new char[ iAllocSize ];
	if ( NULL == pwszBuffer )
	{
		return "";
	}	
	int iCharsRet = WideCharToMultiByte( CP_ACP, 0, wstrSrc.c_str(), 
		static_cast< int >( wstrSrc.size() ),
		pwszBuffer, iAllocSize, NULL, NULL );
	/*!< 成功 */
	string strRet;
	if( 0 < iCharsRet )
	{
		strRet.assign( pwszBuffer, static_cast< size_t >( iCharsRet ) );
	}

	/*!< 释放内存 */
	delete[] pwszBuffer;

	return strRet;
}

//\Uab12QQ\u2387pp -> Ansi 
string UnicodeIntStrToAnsi( const std::string& strIntStr, bool bHex /*= false*/ )
{
	string strRet;
	for ( int i(0); i < strIntStr.size(); i++ )
	{
		string::const_iterator itor = strIntStr.begin() + i;
		if ( *itor == '\\' )
		{
			itor++;
			if ( *itor == 'u' ||  *itor == 'U' )//  \u79fb\u52a8QQ(\u624b\u673a\u53f7\u7801)
			{
				itor++;
				string strTempName(itor, itor + 4);	
				WCHAR wc = (WCHAR)StrToInt( strTempName, bHex );	
				wstring strAnsi;
				strAnsi.push_back(wc);						
				strRet +=UnicodeToAnsi(strAnsi) ;
				i = i + 5;
			}
			else
			{
				itor--;
				strRet += *itor;

			}
		}
		else
		{
			strRet += *itor;
		}	

	}
	return strRet;
}

