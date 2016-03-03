#include "StrAssist.h"
#include <sstream>

/***********************************************************************************
* name       : StrFormat
* description: 根据传入的格式进行字符串的格式化;该接口只能格式化后长度为1024的字符串
* input      : szFormat 字符串的格式，... 可变参数
* output     : NA
* return     : 转化后的字符串
* remark     : NA
***********************************************************************************/
string CStrAssist::StrFormat( const char* szFormat, ... )
{
	va_list va;
	va_start( va, szFormat );
	char szTemp [ 0x400 ] = { 0 };
	vsprintf( szTemp, szFormat, va );
	va_end( va );

	string strRet;
	strRet.assign( szTemp );
	return strRet;
}

/***********************************************************************************
* name       : IntToStr
* description: 将整数转化为字符串
* input      : iValue 要转化的整型数值，bHex 是否是十六进制整型数
* output     : NA
* return     : 转化后的字符串
* remark     : NA
***********************************************************************************/
string CStrAssist::IntToStr( int iValue, bool bHex /*= false*/ )
{
	char szTmp[ 0x7f ] = { 0 };
	if( bHex )
	{
		_itoa( iValue, szTmp, 0x10 );
	}
	else
	{
		_itoa( iValue, szTmp, 0x0a );
	}	

	return string( szTmp );
}

/***********************************************************************************
* name       : StrToInt
* description: 将整数转化为字符串
* input      : strSrc 要转化的字符串，bHex 是否是十六进制整型数
* output     : NA
* return     : 转化后的整型数
* remark     : NA
***********************************************************************************/
int CStrAssist::StrToInt( const string& strSrc, bool bHex /*= false*/ )
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
* name       : LongToStr
* description: 将整数转化为字符串
* input      : iValue 要转化的整型数值，bHex 是否是十六进制整型数
* output     : NA
* return     : 转化后的字符串
* remark     : NA
***********************************************************************************/
string CStrAssist::LongToStr ( long iValue, bool bHex /*= false*/ )
{
	char szTmp[ 0x400 ];
	if( bHex )
	{
		_ltoa( iValue, szTmp, 0x10 );
	}
	else
	{
		_ltoa( iValue, szTmp, 0x0a );
	}	

	return string( szTmp );
}

/***********************************************************************************
* name       : CharToHex
* description: 将字符转化为16进制编码
* input      : szChar 要转化的字符
* output     : NA
* return     : 返回的十六进制编码
* remark     : NA
***********************************************************************************/
int CStrAssist::CharToHex( const char szChar )
{
	if( '0' <= szChar && '9' >= szChar )
	{
		return szChar - '0';
	}
	if( 'a' <= szChar && 'f' >= szChar )
	{
		return szChar - 'a' + 10;
	}
	else
	if( 'A' <= szChar && 'F' >= szChar )
	{
		return szChar - 'A' + 10;
	}

	return -1;
}

/***********************************************************************************
* name       : StrToHex
* description: 将一般字符串转换为十六进制字符串编码
* input      : strSrc 要转化的字符串;
* output     : NA
* return     : 返回的十六进制编码的字符串
* remark     : NA
***********************************************************************************/
string CStrAssist::StrToHex( const string& strData )
{
	string strRet;
	strRet.reserve( strData.size() << 1 );

	for( size_t i = 0; i < strData.size(); ++i )
	{
		char szBuffer[ 10 ];
		sprintf( szBuffer, "%02x", ( unsigned char )strData[ i ] );
		strRet.append( szBuffer, 2 );
	}

	return strRet;
}

/***********************************************************************************
* name       : HexToStr
* description: 将十六进制的字符串转化为一般字符串
* input      : strSrc 要转化的字符串
* output     : NA
* return     : 转化后的字符串
* remark     : NA
***********************************************************************************/
string CStrAssist::HexToStr( const string& strData )
{
	string strRet;
	strRet.assign( ( strData.size() + 1 ) >> 1, '\0' );

	for( size_t i = 0; i < strData.size(); ++i )
	{
		int m = CharToHex( strData[ i ] );
		if ( m >= 0 )
		{
			if ( i % 2 == 0 )
			{
				strRet[ i >>  1 ] |= ( m & 0xf ) << 4;
			}
			else
			{
				strRet[ i >>  1 ] |= ( m & 0xf );
			}
		} // end of if ( m >= 0 ) ...          		        
	} // end of for ( size_t i = 0; ...

	return strRet;
}

/***********************************************************************************
* name       : Utf8ToUnicode
* description: 字符集转换: UTF8 - Unicode	
* input      : strSrc 要转化的Utf8字符集编码的字符串
* output     : NA
* return     : 转化后的Unicode字符集编码的字符串
* remark     : NA
***********************************************************************************/
wstring CStrAssist::Utf8ToUnicode( const string& strSrc )
{
	/*!< 分配目标空间 */
	int iAllocSize = static_cast< int >( strSrc.size() + 10 );
	WCHAR* pwszBuffer = new WCHAR[ iAllocSize ];
	if( NULL == pwszBuffer )
	{
		return L"";
	}
	int iCharsRet = MultiByteToWideChar( CP_UTF8, 0, strSrc.c_str(), 
		static_cast< int >( strSrc.size() ),
		pwszBuffer, iAllocSize );
	/*!< 成功 */
	wstring wstrRet;
	if( 0 < iCharsRet  )
	{
		wstrRet.assign( pwszBuffer, static_cast< size_t >( iCharsRet ) );
	}

	/*!< 释放内存 */
	delete[] pwszBuffer;

	return wstrRet;
}

/***********************************************************************************
* name       : UnicodeToUtf8
* description: 字符集转换: Unicode - UTF8	
* input      : wstrSrc 要转化的Unicode字符集编码的字符串
* output     : NA
* return     : 转化后的UTF8字符集编码的字符串
* remark     : NA
***********************************************************************************/
string CStrAssist::UnicodeToUtf8( const wstring& wstrSrc )
{	
	/*!< 分配目标空间, 一个16位Unicode字符最多可以转为4个字节 */
	int iAllocSize = static_cast< int >( ( wstrSrc.size() << 2 ) + 10 );
	char* pszBuffer = new char[ iAllocSize ];
	if( NULL == pszBuffer )
	{
		return "";
	}
	int iCharsRet = WideCharToMultiByte( CP_UTF8, 0, wstrSrc.c_str(), 
		static_cast< int >( wstrSrc.size() ),
		pszBuffer, iAllocSize, NULL, NULL );
	/*!< 成功 */
	string strRet;
	if( 0 < iCharsRet )
	{
		strRet.assign( pszBuffer, static_cast< size_t >( iCharsRet ) );
	}

	/*!< 释放内存 */
	delete[] pszBuffer;

	return strRet;
}

/***********************************************************************************
* name       : Utf8ToAnsi
* description: 字符集转换: UTF8 - Ansi
* input      : strSrc 要转化的UTF8字符集编码的字符串
* output     : NA
* return     : 转化后的Ansi字符集编码的字符串
* remark     : NA
***********************************************************************************/
string CStrAssist::Utf8ToAnsi( const string& strSrc )
{
	wstring wstrTemp = Utf8ToUnicode( strSrc );

	/*!< 分配目标空间, 长度为 Ansi 编码的两倍 */
	int iAllocSize = static_cast< int >( ( strSrc.size() << 1 ) + 10 );
	char* pszBuffer = new char[ iAllocSize ];
	if( NULL == pszBuffer )
	{
		return "";
	}
	int iCharsRet = WideCharToMultiByte( CP_ACP, 0, wstrTemp.c_str(), 
		static_cast< int >( wstrTemp.size() ),
		pszBuffer, iAllocSize, NULL, NULL );
	/*!< 成功 */
	string strRet;
	if( 0 < iCharsRet )
	{
		strRet.assign( pszBuffer, static_cast< size_t >( iCharsRet ) );
	}

	/*!< 释放内存 */
	delete[] pszBuffer;

	return strRet;
}

/***********************************************************************************
* name       : AnsiToUtf8
* description: 字符集转换: Ansi - UTF8
* input      : strSrc 要转化的Ansi字符集编码的字符串
* output     : NA
* return     : 转化后的UTF8字符集编码的字符串
* remark     : NA
***********************************************************************************/
string CStrAssist::AnsiToUtf8( const string& strSrc )
{
	/*!< 分配目标空间, 长度为 Ansi 编码的两倍 */
	int iAllocSize = static_cast< int >( ( strSrc.size() << 1 ) + 10 );
	WCHAR* pwszBuffer = new WCHAR[ iAllocSize ];
	if( NULL == pwszBuffer )
	{
		return "";
	}
	int iCharsRet = MultiByteToWideChar( CP_ACP, 0, strSrc.c_str(),
		static_cast< int >( strSrc.size() ),
		pwszBuffer, iAllocSize );
	/*!< 成功 */
	wstring wstrTemp;
	if( 0 < iCharsRet )
	{
		wstrTemp.assign( pwszBuffer, static_cast< size_t >( iCharsRet ) );
	}

	/*!< 释放内存 */
	delete[] pwszBuffer;

	return UnicodeToUtf8( wstrTemp );
}

/***********************************************************************************
* name       : AnsiToUnicode
* description: 字符集转换: Ansi - Unicode
* input      : strSrc 要转化的Ansi字符集编码的字符串
* output     : NA
* return     : 转化后的Unicode字符集编码的字符串
* remark     : NA
***********************************************************************************/
wstring CStrAssist::AnsiToUnicode (const string& strSrc )
{
	/*!< 分配目标空间 */
	int iAllocSize = static_cast< int >( strSrc.size() + 10 );
	WCHAR* pwszBuffer = new WCHAR[ iAllocSize ];
	if( NULL == pwszBuffer )
	{
		return L"";
	}	
	int iCharsRet = MultiByteToWideChar( CP_ACP, 0, strSrc.c_str(), 
		static_cast< int >( strSrc.size() ),
		pwszBuffer, iAllocSize );
	/*!< 成功 */
	wstring wstrRet;
	if( 0 < iCharsRet )
	{
		wstrRet.assign( pwszBuffer, static_cast< size_t >( iCharsRet ) );
	}

	/*!< 释放内存 */
	delete[] pwszBuffer;

	return wstrRet;
}

/***********************************************************************************
* name       : UnicodeToAnsi
* description: 字符集转换: Unicode - Ansi
* input      : strSrc 要转化的Unicode字符集编码的字符串
* output     : NA
* return     : 转化后的Ansi字符集编码的字符串
* remark     : NA
***********************************************************************************/
string CStrAssist::UnicodeToAnsi ( const wstring& wstrSrc )
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

/***********************************************************************************
* name       : Utf8ToBSTR
* description: 字符集转换: UTF8 - BSTR
* input      : strSrc 要转化的UTF8字符集编码的字符串
* output     : NA
* return     : 转化后的的BSTR字符串
* remark     : NA
***********************************************************************************/
BSTR CStrAssist::Utf8ToBSTR( const string& strSrc )
{
	BSTR strRet = NULL;

	/*!< 获得目标空间的大小 */
	int iSize = static_cast< int >( strSrc.size() );
	int iAllocSize = MultiByteToWideChar( CP_UTF8, 0, strSrc.c_str(), iSize, NULL, NULL );
	if ( 0 < iAllocSize )
	{
		/*!< 分配目标空间 */
		strRet = ::SysAllocStringByteLen( NULL, iAllocSize );
		if ( NULL != strRet )
		{
			int iResult = MultiByteToWideChar( CP_UTF8, 0, strSrc.c_str(), iSize, strRet, iAllocSize );
			if ( iResult != iAllocSize )
			{
				SysFreeString( strRet );
				strRet = NULL;
			}
		} // end of if ( NULL !- strRet ) ...
	} // end of if ( 0 < iAllocSize ) ...

	/*!< 避免返回空指针 */
	if( NULL == strRet )
	{
		strRet = ::SysAllocString( L"" );
	}

	return strRet;
}

/***********************************************************************************
* name       : BSTRToUtf8
* description: 字符集转换: BSTR - UTF8
* input      : bstrSrc 要转化的BSTR字符串
* output     : NA
* return     : 转化后的UTF8字符集编码的字符串
* remark     : NA
***********************************************************************************/
string CStrAssist::BSTRToUtf8( const BSTR& bstrSrc )
{
	/*!< 获得目标空间的大小 */
	int iAllocSize = WideCharToMultiByte( CP_UTF8, 0, bstrSrc, -1, NULL, NULL, NULL, FALSE ) - 1;
	if ( 0 >= iAllocSize )
	{
		return "";
	}

	/*!< 返回值 */
	string strRet( iAllocSize, '\0' );

	/*!< 进行转换 */
	int nResult = WideCharToMultiByte( CP_UTF8, 0, bstrSrc, -1, const_cast< char* >( strRet.c_str() ),
		iAllocSize, NULL, FALSE );

	return strRet;
}

/***********************************************************************************
* name       : GbkToUtf8
* description: 字符集转换: GBK - UTF8
* input      : strGBK:要转化的GBK字符串;
* output     : NA
* return     : 转化后的UTF8字符集编码的字符串
* remark     : NA
***********************************************************************************/
string CStrAssist::GbkToUtf8( const std::string& strGbk )
{
	string strOutUtf8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar( CP_ACP, 0, strGbk.c_str(), -1, NULL, 0 );
	str1 = new WCHAR[ n ];
	MultiByteToWideChar( CP_ACP, 0, strGbk.c_str(), -1, str1, n );
	n = WideCharToMultiByte( CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL );
	char * str2 = new char[ n ];
	WideCharToMultiByte( CP_UTF8, 0, str1, -1, str2, n, NULL, NULL );
	strOutUtf8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUtf8;
}

/***********************************************************************************
* name       : Utf8ToGbk
* description: 字符集转换: UTF8 - GBK
* input      : strUTF8 要转化的UTF8字符串
* output     : NA
* return     : 转化后的GBK字符集编码的字符串
* remark     : NA
***********************************************************************************/
string CStrAssist::Utf8ToGbk( const std::string& strUtf8 )
{
	int len = MultiByteToWideChar( CP_UTF8, 0, strUtf8.c_str(), -1, NULL, 0 );	
	WCHAR * wszGbk = new WCHAR[ len + 1 ];
	memset( wszGbk, 0, ( len << 1 ) + 2 );
	MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)strUtf8.c_str(), -1, wszGbk, len );

	len = WideCharToMultiByte( CP_ACP, 0, wszGbk, -1, NULL, 0, NULL, NULL );
	char* szGbk = new char[ len + 1 ];
	memset( szGbk, 0, len + 1 );
	WideCharToMultiByte( CP_ACP, 0, wszGbk, -1, szGbk, len, NULL, NULL );

	std::string strTemp( szGbk );
	delete[]szGbk;
	delete[]wszGbk;
	return strTemp;
}

//\Uab12QQ\u2387pp -> Ansi 
string CStrAssist::UnicodeIntStrToAnsi( const std::string& strIntStr, bool bHex /*= false*/ )
{
	string strRet;
	for ( int i(0); i < (int)strIntStr.size(); i++ )
	{
		string::const_iterator itor = strIntStr.begin() + i;
		if ( *itor == '\\' )
		{
			itor++;
			if ( *itor == 'u' ||  *itor == 'U' )//  \u79fb\u52a8QQ(\u624b\u673a\u53f7\u7801)
			{
				itor++;
				string strTempName(itor, itor + 4);	
				WCHAR wc = (WCHAR)CStrAssist::StrToInt( strTempName, bHex );	
				wstring strAnsi;
				strAnsi.push_back(wc);						
				strRet += CStrAssist::UnicodeToAnsi(strAnsi) ;
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

string CStrAssist::UrlEncode( const std::string& normal )
{
	std::stringstream ss;
	char tmp[4] = {0};
	const char* p = normal.c_str();
	for(; *p; ++p){
		if (isalnum(*p)){
			ss<<*p;
		} else if (*p == ' '){
			ss<<'+';
		} else {
			sprintf(tmp, "%%%2X", (int)*p);
			ss<<tmp;
		}	
	}

	return ss.str();
}

bool hexDidit(int c)
{
	char up = toupper(c);
	return (isdigit(c) || (up >= 'A' && up <= 'F'));
}
int CStrAssist::UrlDecode( const std::string& normal, string &dec )
{
	stringstream ss;
	int hh;
	char tmp[5] = "0X";
	const char* p = normal.c_str();
	const char* end = p+normal.length();
	for(; *p; ++p){
		if (*p != '%'){
			ss<<*p;
		} else if(*p == '+'){
			ss<<' ';
		} else {
			if(p+2 > end)
				return -1;
			tmp[2] = toupper(*(p+1));
			tmp[3] = toupper(*(p+2));
			if (!hexDidit(tmp[2]) || !hexDidit(tmp[3]))
				return -1;
			if(sscanf(tmp, "%X", &hh) == 1)
				ss<<char(hh);
			else
				return -1;
			p += 2;
		}			
	}
	dec = ss.str();
	return 0;
}