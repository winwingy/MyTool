#include <stdio.h>
#include <string.h>

#pragma comment(linker, "/align:32")
#pragma comment(linker, "/merge:.data=.text")
#pragma comment(linker, "/merge:.rdata=.text")
#pragma comment(linker, "/ENTRY:main")

#define SDKCONFIG_INI "sdkconfig.ini"
#define CONFIG_INI "Config.ini"
#define CONFIG_BUF_LENTH 2048
#define LOG_LEVEL "LogLevel=" 

int ChangeLevelFun(const char* pFileName, const char* pFindWhat, char cLevel)
{
	FILE* fp = fopen(pFileName, "r+");
	int iRet = 0;
	if ( fp == NULL )
	{
		printf("找不到%s\n", pFileName);
		iRet = -1;
		goto _END;
	}
	char szBuf[CONFIG_BUF_LENTH+1] = {0};
	size_t stRead = fread(szBuf, 1, CONFIG_BUF_LENTH, fp);
	if ( stRead <= 0 )
	{
		printf("%s读取错误\n", pFileName);
		iRet = -2;
		goto _END;
	}
	char* pFind = strstr(szBuf, pFindWhat);
	if ( pFind == NULL )
	{
		printf("找不到%s\n", pFindWhat);
		iRet = -3;
		goto _END;
	}
	*(pFind+strlen(pFindWhat)) = cLevel;
	size_t stWr = fwrite(szBuf, 1, strlen(szBuf), fp);
	if ( stWr <= 0 )
	{
		printf("写文件%s失败\n", pFileName);
		iRet = -4;
		goto _END;
	}
_END:
	if ( fp )
	{
		fclose(fp);
	}
	return iRet;
}


int main()
{
	int iRetSDK = 0, iRetConfg = 0;
	iRetSDK = ChangeLevelFun(SDKCONFIG_INI, LOG_LEVEL, '0');
	iRetConfg = ChangeLevelFun(CONFIG_INI, LOG_LEVEL, '0');
	if ( iRetSDK == 0 && iRetConfg == 0 )
	{
		printf("修改成功\n");
	}
	else
	{
		printf("修改失败\n");
	}
	getchar();
	return 0;
}