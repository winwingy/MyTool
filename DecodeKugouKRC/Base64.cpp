// Base64.cpp: implementation of the Base64 class.
//
//////////////////////////////////////////////////////////////////////

//#ifdef VC_EXTRALEAN
#include "stdafx.h"
//#endif

#include "Base64.h"

#define UChar( Ch )							\
	unsigned char( Ch )

// 解码宏
#define SRC64( Base64Ch )					\
	( ( Base64Ch ) == 'A' ? 0				\
	: ( Base64Ch ) == 'B' ? 1				\
	: ( Base64Ch ) == 'C' ? 2				\
	: ( Base64Ch ) == 'D' ? 3				\
	: ( Base64Ch ) == 'E' ? 4				\
	: ( Base64Ch ) == 'F' ? 5				\
	: ( Base64Ch ) == 'G' ? 6				\
	: ( Base64Ch ) == 'H' ? 7				\
	: ( Base64Ch ) == 'I' ? 8				\
	: ( Base64Ch ) == 'J' ? 9				\
	: ( Base64Ch ) == 'K' ? 10				\
	: ( Base64Ch ) == 'L' ? 11				\
	: ( Base64Ch ) == 'M' ? 12				\
	: ( Base64Ch ) == 'N' ? 13				\
	: ( Base64Ch ) == 'O' ? 14				\
	: ( Base64Ch ) == 'P' ? 15				\
	: ( Base64Ch ) == 'Q' ? 16				\
	: ( Base64Ch ) == 'R' ? 17				\
	: ( Base64Ch ) == 'S' ? 18				\
	: ( Base64Ch ) == 'T' ? 19				\
	: ( Base64Ch ) == 'U' ? 20				\
	: ( Base64Ch ) == 'V' ? 21				\
	: ( Base64Ch ) == 'W' ? 22				\
	: ( Base64Ch ) == 'X' ? 23				\
	: ( Base64Ch ) == 'Y' ? 24				\
	: ( Base64Ch ) == 'Z' ? 25				\
	: ( Base64Ch ) == 'a' ? 26				\
	: ( Base64Ch ) == 'b' ? 27				\
	: ( Base64Ch ) == 'c' ? 28				\
	: ( Base64Ch ) == 'd' ? 29				\
	: ( Base64Ch ) == 'e' ? 30				\
	: ( Base64Ch ) == 'f' ? 31				\
	: ( Base64Ch ) == 'g' ? 32				\
	: ( Base64Ch ) == 'h' ? 33				\
	: ( Base64Ch ) == 'i' ? 34				\
	: ( Base64Ch ) == 'j' ? 35				\
	: ( Base64Ch ) == 'k' ? 36				\
	: ( Base64Ch ) == 'l' ? 37				\
	: ( Base64Ch ) == 'm' ? 38				\
	: ( Base64Ch ) == 'n' ? 39				\
	: ( Base64Ch ) == 'o' ? 40				\
	: ( Base64Ch ) == 'p' ? 41				\
	: ( Base64Ch ) == 'q' ? 42				\
	: ( Base64Ch ) == 'r' ? 43				\
	: ( Base64Ch ) == 's' ? 44				\
	: ( Base64Ch ) == 't' ? 45				\
	: ( Base64Ch ) == 'u' ? 46				\
	: ( Base64Ch ) == 'v' ? 47				\
	: ( Base64Ch ) == 'w' ? 48				\
	: ( Base64Ch ) == 'x' ? 49				\
	: ( Base64Ch ) == 'y' ? 50				\
	: ( Base64Ch ) == 'z' ? 51				\
	: ( Base64Ch ) == '0' ? 52				\
	: ( Base64Ch ) == '1' ? 53				\
	: ( Base64Ch ) == '2' ? 54				\
	: ( Base64Ch ) == '3' ? 55				\
	: ( Base64Ch ) == '4' ? 56				\
	: ( Base64Ch ) == '5' ? 57				\
	: ( Base64Ch ) == '6' ? 58				\
	: ( Base64Ch ) == '7' ? 59				\
	: ( Base64Ch ) == '8' ? 60				\
	: ( Base64Ch ) == '9' ? 61				\
	: ( Base64Ch ) == '+' ? 62				\
	: ( Base64Ch ) == '/' ? 63				\
	: ( Base64Ch ) == '=' ? 64				\
	: -1 )

// 编码表
const char CBase64::strBase64EnCode[ BASE64ENCODECOUNT ]
=
{
	'A', 'B', 'C', 'D'
	, 'E', 'F', 'G', 'H'
	, 'I', 'J', 'K', 'L'
	, 'M', 'N', 'O', 'P'
	, 'Q', 'R', 'S', 'T'
	, 'U', 'V', 'W', 'X'
	, 'Y', 'Z', 'a', 'b'
	, 'c', 'd', 'e', 'f'
	, 'g', 'h', 'i', 'j'
	, 'k', 'l', 'm', 'n'
	, 'o', 'p', 'q', 'r'
	, 's', 't', 'u', 'v'
	, 'w', 'x', 'y', 'z'
	, '0', '1', '2', '3'
	, '4', '5', '6', '7'
	, '8', '9', '+', '/'
	, '='
};

// 解码表
const char CBase64::strBase64DeCode[ BASE64DECODECOUNT ]
=
{
	SRC64( 0 ), SRC64( 1 ), SRC64( 2 ), SRC64( 3 )
	, SRC64( 4 ), SRC64( 5 ), SRC64( 6 ), SRC64( 7 )
	, SRC64( 8 ), SRC64( 9 ), SRC64( 10 ), SRC64( 11 )
	, SRC64( 12 ), SRC64( 13 ), SRC64( 14 ), SRC64( 15 )
	, SRC64( 16 ), SRC64( 17 ), SRC64( 18 ), SRC64( 19 )
	, SRC64( 20 ), SRC64( 21 ), SRC64( 22 ), SRC64( 23 )
	, SRC64( 24 ), SRC64( 25 ), SRC64( 26 ), SRC64( 27 )
	, SRC64( 28 ), SRC64( 29 ), SRC64( 30 ), SRC64( 31 )
	, SRC64( 32 ), SRC64( 33 ), SRC64( 34 ), SRC64( 35 )
	, SRC64( 36 ), SRC64( 37 ), SRC64( 38 ), SRC64( 39 )
	, SRC64( 40 ), SRC64( 41 ), SRC64( 42 ), SRC64( 43 )
	, SRC64( 44 ), SRC64( 45 ), SRC64( 46 ), SRC64( 47 )
	, SRC64( 48 ), SRC64( 49 ), SRC64( 50 ), SRC64( 51 )
	, SRC64( 52 ), SRC64( 53 ), SRC64( 54 ), SRC64( 55 )
	, SRC64( 56 ), SRC64( 57 ), SRC64( 58 ), SRC64( 59 )
	, SRC64( 60 ), SRC64( 61 ), SRC64( 62 ), SRC64( 63 )
	, SRC64( 64 ), SRC64( 65 ), SRC64( 66 ), SRC64( 67 )
	, SRC64( 68 ), SRC64( 69 ), SRC64( 70 ), SRC64( 71 )
	, SRC64( 72 ), SRC64( 73 ), SRC64( 74 ), SRC64( 75 )
	, SRC64( 76 ), SRC64( 77 ), SRC64( 78 ), SRC64( 79 )
	, SRC64( 80 ), SRC64( 81 ), SRC64( 82 ), SRC64( 83 )
	, SRC64( 84 ), SRC64( 85 ), SRC64( 86 ), SRC64( 87 )
	, SRC64( 88 ), SRC64( 89 ), SRC64( 90 ), SRC64( 91 )
	, SRC64( 92 ), SRC64( 93 ), SRC64( 94 ), SRC64( 95 )
	, SRC64( 96 ), SRC64( 97 ), SRC64( 98 ), SRC64( 99 )
	, SRC64( 100 ), SRC64( 101 ), SRC64( 102 ), SRC64( 103 )
	, SRC64( 104 ), SRC64( 105 ), SRC64( 106 ), SRC64( 107 )
	, SRC64( 108 ), SRC64( 109 ), SRC64( 110 ), SRC64( 111 )
	, SRC64( 112 ), SRC64( 113 ), SRC64( 114 ), SRC64( 115 )
	, SRC64( 116 ), SRC64( 117 ), SRC64( 118 ), SRC64( 119 )
	, SRC64( 120 ), SRC64( 121 ), SRC64( 122 ), SRC64( 123 )
	, SRC64( 124 ), SRC64( 125 ), SRC64( 126 ), SRC64( 127 )
	, SRC64( 128 ), SRC64( 129 ), SRC64( 130 ), SRC64( 131 )
	, SRC64( 132 ), SRC64( 133 ), SRC64( 134 ), SRC64( 135 )
	, SRC64( 136 ), SRC64( 137 ), SRC64( 138 ), SRC64( 139 )
	, SRC64( 140 ), SRC64( 141 ), SRC64( 142 ), SRC64( 143 )
	, SRC64( 144 ), SRC64( 145 ), SRC64( 146 ), SRC64( 147 )
	, SRC64( 148 ), SRC64( 149 ), SRC64( 150 ), SRC64( 151 )
	, SRC64( 152 ), SRC64( 153 ), SRC64( 154 ), SRC64( 155 )
	, SRC64( 156 ), SRC64( 157 ), SRC64( 158 ), SRC64( 159 )
	, SRC64( 160 ), SRC64( 161 ), SRC64( 162 ), SRC64( 163 )
	, SRC64( 164 ), SRC64( 165 ), SRC64( 166 ), SRC64( 167 )
	, SRC64( 168 ), SRC64( 169 ), SRC64( 170 ), SRC64( 171 )
	, SRC64( 172 ), SRC64( 173 ), SRC64( 174 ), SRC64( 175 )
	, SRC64( 176 ), SRC64( 177 ), SRC64( 178 ), SRC64( 179 )
	, SRC64( 180 ), SRC64( 181 ), SRC64( 182 ), SRC64( 183 )
	, SRC64( 184 ), SRC64( 185 ), SRC64( 186 ), SRC64( 187 )
	, SRC64( 188 ), SRC64( 189 ), SRC64( 190 ), SRC64( 191 )
	, SRC64( 192 ), SRC64( 193 ), SRC64( 194 ), SRC64( 195 )
	, SRC64( 196 ), SRC64( 197 ), SRC64( 198 ), SRC64( 199 )
	, SRC64( 200 ), SRC64( 201 ), SRC64( 202 ), SRC64( 203 )
	, SRC64( 204 ), SRC64( 205 ), SRC64( 206 ), SRC64( 207 )
	, SRC64( 208 ), SRC64( 209 ), SRC64( 210 ), SRC64( 211 )
	, SRC64( 212 ), SRC64( 213 ), SRC64( 214 ), SRC64( 215 )
	, SRC64( 216 ), SRC64( 217 ), SRC64( 218 ), SRC64( 219 )
	, SRC64( 220 ), SRC64( 221 ), SRC64( 222 ), SRC64( 223 )
	, SRC64( 224 ), SRC64( 225 ), SRC64( 226 ), SRC64( 227 )
	, SRC64( 228 ), SRC64( 229 ), SRC64( 230 ), SRC64( 231 )
	, SRC64( 232 ), SRC64( 233 ), SRC64( 234 ), SRC64( 235 )
	, SRC64( 236 ), SRC64( 237 ), SRC64( 238 ), SRC64( 239 )
	, SRC64( 240 ), SRC64( 241 ), SRC64( 242 ), SRC64( 243 )
	, SRC64( 244 ), SRC64( 245 ), SRC64( 246 ), SRC64( 247 )
	, SRC64( 248 ), SRC64( 249 ), SRC64( 250 ), SRC64( 251 )
	, SRC64( 252 ), SRC64( 253 ), SRC64( 254 ), SRC64( 255 )
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBase64::CBase64()
{

}

CBase64::~CBase64()
{

}

//////////////////////////////////////////////////////////////////////

// Base64编码
char* CBase64::Base64EnCode( const char* strSrc, char* strBase64 )
{
	char* strRet = strBase64;

	size_t iLen = strlen( strSrc );						// 字符长度
	if( strSrc != NULL && iLen != 0 )					// 源字符串不为空
	{
		while( iLen )
		{
			// 010101_01 1010_1010 01_010101
			// 00010101 00011010 00101001 00010101
			*strBase64++ = strBase64EnCode[ UChar( strSrc[ BYTEFST ] ) >> BYTEMOVE2 ];										// 处理第一个字节

			*strBase64++ = strBase64EnCode[ ( ( UChar( strSrc[ BYTEFST ] ) << BYTEMOVE4 )
				+ ( --iLen ? ( UChar( strSrc[ BYTESEC ] ) >> BYTEMOVE4 ) : 0 ) ) & BASE64ENCODEMASK ];						// 处理第二个字节

			*strBase64++ = strBase64EnCode[ iLen ? ( ( UChar( strSrc[ BYTESEC ] ) << BYTEMOVE2 )
				+ ( --iLen ? ( UChar( strSrc[ BYTETHR ] ) >> BYTEMOVE6 ) : 0 ) ) & BASE64ENCODEMASK : SRC64( '=' ) ];		// 处理第三个字节

			*strBase64++ = strBase64EnCode[ iLen ? UChar( strSrc[ BYTETHR ] ) & BASE64ENCODEMASK : SRC64( '=' ) ];			// 处理第四个字节

			if( iLen )
			{
				--iLen;
				strSrc += BASE64SRCCOUNT;
			}
		}
		*strBase64 = 0;
	}

	return strRet;
}

// Base64编码分配内存
bool CBase64::Base64EnCodeAlloc( const char* strSrc, char** pStrBase64 )
{
	bool bRet( true );

	int iLenSrc = (int)strlen( strSrc );									// 字符长度
	int iLenBase64 = iLenSrc / BASE64SRCCOUNT * BASE64CODECOUNT 
		+ ( iLenSrc % BASE64SRCCOUNT ? BASE64CODECOUNT : 0 ) + 1;			// 原码长度

	*pStrBase64 = new char[ iLenBase64 ];									// 分配Base64编码内存
	
	if( *pStrBase64 == NULL )
	{
		bRet = false;
	}
	else
	{
		memset( *pStrBase64, 0, iLenBase64 );
	}

	return bRet;
}

// Base64编码分配内存
bool CBase64::Base64EnCodeFree( char* strBase64 )
{
	bool bRet( true );

	delete[] strBase64;
		
	return bRet;
}

// Base64解码
char* CBase64::Base64DeCode( const char* strBase64, char* strSrc )
{
	char* strRet = strSrc;

	int iLen = (int)strlen( strBase64 );						// 字符长度
	if( strBase64 != NULL && iLen != 0 && iLen % 4 == 0 )			// 源字符串不为空
	{
		while( iLen )
		{
			// 00010101 00011010 00101001 00010101
			// 010101_01 1010_1010 01_010101
			*strSrc++ = ( strBase64DeCode[ UChar( strBase64[ BYTEFST ] ) ] << BYTEMOVE2 )
				+ ( strBase64DeCode[ UChar( strBase64[ BYTESEC ] ) ] >> BYTEMOVE4 );				// 处理第一个字节
			
			*strSrc++ = ( strBase64DeCode[ UChar( strBase64[ BYTESEC ] ) ] << BYTEMOVE4 )
				+ ( strBase64DeCode[ UChar( strBase64[ BYTETHR ] ) ] == strBase64DeCode[ '=' ] 
				? 0 : strBase64DeCode[ UChar( strBase64[ BYTETHR ] ) ] >> BYTEMOVE2 );			// 处理第二个字节
			
			*strSrc++ = ( strBase64DeCode[ UChar( strBase64[ BYTETHR ] ) ] << BYTEMOVE6 )
				+ ( strBase64DeCode[ UChar( strBase64[ BYTEFOURTH ] ) ] == strBase64DeCode[ '=' ]
				? 0 : strBase64DeCode[ UChar( strBase64[ BYTEFOURTH ] ) ] );							// 处理第三个字节
			
			if( iLen )
			{
				iLen -= BASE64CODECOUNT;
				strBase64 += BASE64CODECOUNT;
			}
		}
	}
	return strRet;
}


int CBase64::Base64DecodeEx(const char *input, char *des)
{
	char *start = des;
	static int map64[256] = {0};
	static unsigned char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int inplen = (int)strlen(input);
	int words = (inplen+3)/4;
	int i=0, j=0;
	int word = 0;
	const char *p = input;
	int padnum = 0;

	for (i = 0; i < 64; ++i)
	{
		map64[(int)b64[i]]=i;
	}
	if(input[inplen - 1] == '=') padnum = 1;
	if(input[inplen - 1] == '=' && input[inplen - 2] == '=') padnum = 2;

	for(i=0; i<words; i++)
	{
		word = 0;
		word |= map64[(int)*p++];
		word <<= 6;
		word |= map64[(int)*p++];
		word <<= 6;
		word |= map64[(int)*p++];
		word <<= 6;
		word |= map64[(int)*p++];
		*des++ =  word >> 16 & 0xFF;

		if (i + 1 == words && padnum == 2) 
			break;
		*des++ =  word >> 8 & 0xFF;

		if (i + 1 == words && padnum == 1) 
			break;
		*des++ =  word & 0xFF;
	}

	return (int)(des - start);
}

// Base64解码分配内存
bool CBase64::Base64DeCodeAlloc( const char* strBase64, char** pStrSrc )
{
	bool bRet( true );
	
	int iLenBase64 = (int)strlen( strBase64 );									// 字符长度
	int iLenSrc = ( iLenBase64 / BASE64CODECOUNT + 1 ) * BASE64SRCCOUNT;	// 原码长度
	
	*pStrSrc = new char[ iLenSrc ];											// 分配Base64原码内存
	
	if( *pStrSrc == NULL )
	{
		bRet = false;
	}
	else
	{
		memset( *pStrSrc, 0, iLenSrc );
	}
	
	return bRet;
}

// Base64解码分配内存
bool CBase64::Base64DeCodeAllocEx( const char* strBase64, char** pStrSrc, int& len)
{
    bool bRet( true );

    int iLenBase64 = (int)strlen( strBase64 );									// 字符长度
    int iLenSrc = ( iLenBase64 / BASE64CODECOUNT + 1 ) * BASE64SRCCOUNT;	// 原码长度

    *pStrSrc = new char[ iLenSrc ];											// 分配Base64原码内存

    if( *pStrSrc == NULL )
    {
        bRet = false;
    }
    else
    {
        memset( *pStrSrc, 0, iLenSrc );
    }

    len = iLenSrc;
    return bRet;
}


// Base64解码分配内存
bool CBase64::Base64DeCodeFree( char* strSrc )
{	
	bool bRet( true );
	
	delete[] strSrc;
	
	return bRet;
}