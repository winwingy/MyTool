// CloseSomeWin.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include <string>

BOOL CALLBACK WndEnumProc(HWND hWnd, LPARAM lParam)
{
	TCHAR szBuf[1024] = {0};
	GetWindowText(hWnd, szBuf, 1024);
	if ( _tcscmp(szBuf, L"忽略(&I)") == 0)
	{
		SendMessage(hWnd, WM_LBUTTONDOWN, MK_LBUTTON, 0);
		SendMessage(hWnd, WM_LBUTTONUP, MK_LBUTTON, 0);
		return FALSE;
	}
	return TRUE;
}

std::wstring FindCongfigFile(const std::wstring& configName)
{
	TCHAR szBuf[1024];
	GetModuleFileName(nullptr, szBuf, 1024);
	std::wstring path(szBuf);
	for (int i = 0; i < 3; ++i)
	{
		size_t pos = path.rfind(L'\\');
		if (pos != std::wstring::npos)
		{
			path.erase(pos);
			std::wstring filePath(path+ L"\\" + std::wstring(configName));
			FILE* fp = nullptr;
			_tfopen_s(&fp, filePath.c_str(), L"rb");
			if (fp)
			{
				fclose(fp);
				return filePath;
			}
		}

	}
	return L"";
}

int _tmain(int argc, _TCHAR* argv[])
{
	int timeGo = 0;
	const std::wstring ConfigName =  L"CloseSomeWinConfig.ini";
	std::wstring configPath = FindCongfigFile(ConfigName);
	timeGo = GetPrivateProfileInt(L"Config", L"Time",
		60, configPath.c_str());

	for (int i = 0; i < timeGo * 60 / 2; ++i)
	{
		{
			HWND hWnd = FindWindow(nullptr, L"调试");
			if (!hWnd)
			{
				hWnd = FindWindow(nullptr, L"调式");
				if (!hWnd)
				{
					//break;				
				}
			}
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}

		{
			HWND debugWindow = FindWindow(nullptr, 
				L"Microsoft Visual C++ Runtime Library");
// 			SendMessage(debugWindow, WM_CLOSE, 0, 0);
// 			SendMessage(debugWindow, WM_QUIT, -1, 0);
			if (debugWindow)
			{
				EnumChildWindows(debugWindow, WndEnumProc, 0);
			}
		}
		Sleep(2000);
	}

	return 0;
}

