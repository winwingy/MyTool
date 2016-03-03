// Base64.h: interface for the Base64 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE64_H__CC677E12_2906_4796_9395_D0E7A34C1E6F__INCLUDED_)
#define AFX_BASE64_H__CC677E12_2906_4796_9395_D0E7A34C1E6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBase64  
{
public:
	CBase64();
	virtual ~CBase64();

	enum
	{
		BASE64SRCCOUNT		= 3					// 原文字节数
		, BASE64CODECOUNT	= 4					// 编码字节数

		, BASE64ENCODECOUNT	= 66				// 编码表个数
		, BASE64DECODECOUNT	= 256				// 解码表个数

		, BASE64ENCODEMASK	= 0x3f				// 编码掩码
		, BASE64DECODEMASK	= 0x3f				// 解码掩码

		, BYTEFST			= 0					// 第一个字节
		, BYTESEC			= 1					// 第二个字节
		, BYTETHR			= 2					// 第三个字节
		, BYTEFOURTH		= 3					// 第四个字节	// 解码用到

		, BYTEMOVE2			= 2					// 字节移动2个位
		, BYTEMOVE4			= 4					// 字节移动4个位
		, BYTEMOVE6			= 6					// 字节移动6个位
	};

	// 操作函数

	// 编码

	static const char strBase64EnCode[ BASE64ENCODECOUNT ];		// 编码表

	// Base64编码
	static char* Base64EnCode( const char* strSrc, char* strBase64 );

	// Base64编码分配内存
	static bool Base64EnCodeAlloc( const char* strSrc, char** pStrBase64 );
	
	// Base64编码分配内存
	static bool Base64EnCodeFree( char* strBase64 );

	// 解码
	static const char strBase64DeCode[ BASE64DECODECOUNT ];		// 解码表

	// Base64解码解码
	static char* Base64DeCode( const char* strBase64, char* strSrc );

	static int Base64DecodeEx(const char *input, char *des);

	// Base64解码分配内存
	static bool Base64DeCodeAlloc( const char* strBase64, char** pStrSrc );
    static bool Base64DeCodeAllocEx( const char* strBase64, char** pStrSrc, int& len);

	// Base64解码分配内存
	static bool Base64DeCodeFree( char* strSrc );

};

#endif // !defined(AFX_BASE64_H__CC677E12_2906_4796_9395_D0E7A34C1E6F__INCLUDED_)
