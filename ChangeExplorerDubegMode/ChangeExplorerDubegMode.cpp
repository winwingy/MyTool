// ChangeExplorerDubegMode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	printf("不用重启explorer.exe进行shell调试的方法:\n");
	printf("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer");
	printf("DesktopProcess DWORD:设置值(0关闭 1打开) \n");
	DWORD iExporerMode=0;
	scanf("%d", &iExporerMode);
	HKEY hKey;
	LONG lRet(-1);
	lRet = RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer", 0, KEY_WRITE,&hKey);	
	if ( lRet == ERROR_SUCCESS )
	{
		DWORD dwLen = sizeof(iExporerMode);
		lRet = RegSetValueEx(hKey,"DesktopProcess",NULL,REG_DWORD,(BYTE*)(&iExporerMode), dwLen );
	}

	if (  lRet == ERROR_SUCCESS )
	{
		printf("设置成功\n");
	}
	else
	{
		printf("设置失败\n");
	}	
	system("pause");
	return 0;
}

