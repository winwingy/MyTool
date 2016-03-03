// CloseSomeWin.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 0; i < 10; ++i)
	{
		HWND hWnd = FindWindow(nullptr, L"调试");
		if (!hWnd)
		{
			hWnd = FindWindow(nullptr, L"调式");
			if (!hWnd)
			{
				break;
			}
		}
		SendMessage(hWnd, WM_CLOSE, 0, 0);
		Sleep(2000);
	}

	return 0;
}

