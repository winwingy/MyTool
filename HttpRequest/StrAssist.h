#pragma once
#include <Windows.h>
// 使用标准库
#include <string>
using namespace std;

class CStrAssist
{

private:
	CStrAssist( void )
	{

	}

	~CStrAssist( void )
	{

	}

public:
	/***********************************************************************************
	* name       : StrFormat
	* description: 根据传入的格式进行字符串的格式化;该接口只能格式化后长度为1024的字符串
	* input      : szFormat:字符串的格式; ...:可变参数;
	* output     : NA
	* return     : 转化后的字符串
	* remark     : NA
	***********************************************************************************/
	static string StrFormat( const char* szFormat, ... );

	// Int->Str
	static string IntToStr( int iValue, bool bHex = false );

	// Str->Int
	static int StrToInt( const string& strSrc, bool bHex = false );

	// Long->Str
	static string LongToStr( long iValue, bool bHex = false );

	// Char->Hex
	static int CharToHex( const char szChar );

	// Str->Hex
	static string StrToHex( const string& strSrc );

	// Hex->Str
	static string HexToStr( const string& strSrc );

	// Utf8->Unicode
	static wstring Utf8ToUnicode( const string& strSrc );

	// Unicode->Utf8
	static string UnicodeToUtf8( const wstring& wstrSrc );

	// Utf8->Ansi
	static string Utf8ToAnsi( const string& strSrc );

	// Ansi->Utf8
	static string AnsiToUtf8( const string& strSrc );

	// Ansi->Unicode
	static wstring AnsiToUnicode(const string& strSrc );

	// Unicode->Ansi
	static string UnicodeToAnsi( const wstring& wstrSrc );

	// Utf8->BSTR
	static BSTR Utf8ToBSTR( const string& strSrc );

	// BSTR->Utf8
	static string BSTRToUtf8( const BSTR& bstrSrc );

	// Gbk->Utf8
	static string GbkToUtf8( const std::string& strGbk );

	// Utf8->Gbk
	static string Utf8ToGbk( const std::string& strUtf8 );

	//\Uab12QQ\u2387pp -> Ansi 
	static string UnicodeIntStrToAnsi( const std::string& strTempFriendName, bool bHex = false );

	/**
	* change unsafe characters(rfc 1945, rfc 2616)to style %2X format
	* @return: success 0, failed -1
	* @para normal: url in utf-8 format
	* @para dec: after encoded
	*/
	static string UrlEncode( const std::string& normal );

	/**
	* reverse method of @see{UrlEncode}
	* @return: success 0, failed -1
	* @para normal: encoded url
	* @para dec: after decoded
	*/
	static int UrlDecode( const std::string& normal, string &dec );
};
