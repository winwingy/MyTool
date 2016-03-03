// Russion.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "CSRect.h"
#include "Game.h"

HINSTANCE g_hInstance = 0;
HANDLE g_hOutput = 0;
Game* gamep;

void OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch(LOWORD(wParam))
	{
		case ID_BEGIN:
			gamep->startGame();
			break;
		case ID_PAUSE:
			gamep->pauseGame();
			break;
		case ID_CONTINUE:
			gamep->continueGame();
			break;
		case ID_OVER:
			gamep->stopGame();
			break;
		case ID_EXIT:
			PostQuitMessage(0);
			break;
		case ID_LEVEL1:
			gamep->setLevel(1);
			break;
		case ID_LEVEL2:
			gamep->setLevel(2);
			break;
		case ID_LEVEL3:
			gamep->setLevel(3);
			break;
		case ID_LEVEL4:
			gamep->setLevel(4);
			break;
	}
}

void OnCreate(HWND hwnd)
{
	HMENU hSys = GetSystemMenu(hwnd, FALSE);
	// 不允许改变窗口大小
	RemoveMenu(hSys, SC_SIZE, MF_BYCOMMAND);
}

void OnInitMenuPopup(WPARAM wParam)
{
	gamep->setPopupMenu((HMENU)wParam);
}

void OnTimer()
{
	gamep->draw();
}

void OnKeyDown(WPARAM wParam)
{
	switch(wParam)
	{
		case VK_SPACE:
			gamep->turn();
			break;
		case VK_DOWN:
			gamep->down();
			break;
		case VK_LEFT:
			gamep->left();
			break;
		case VK_RIGHT:
			gamep->right();
			break;
	}
}

void CALLBACK slowTimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	gamep->slowTimer(hwnd, uMsg, idEvent, dwTime);
}

LRESULT CALLBACK MainProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam) // CALLBACK 标准调用方式
{
	switch(nMsg)
	{
		case WM_KEYDOWN:
			OnKeyDown(wParam);
			break;
		case WM_TIMER:
			OnTimer();
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_COMMAND:
			OnCommand(hwnd, wParam, lParam);
			break;
		case WM_CREATE:
			OnCreate(hwnd);
			break;
		case WM_INITMENUPOPUP:
			OnInitMenuPopup(wParam);
			break;
	}
	return DefWindowProc(hwnd, nMsg, wParam,lParam);
}

// 注册窗口类
BOOL Register(LPSTR pszClassName, WNDPROC pfWndProc)
{
	WNDCLASSEX wce = {0};
	wce.cbSize = sizeof(wce);
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hbrBackground = (HBRUSH) COLOR_WINDOWFRAME;
	wce.hIcon = NULL;
	wce.hCursor = NULL;
	wce.hIconSm = NULL;
	wce.hInstance = g_hInstance;
	wce.lpfnWndProc = pfWndProc;
	wce.lpszClassName = pszClassName;
	wce.lpszMenuName = MAKEINTRESOURCE(IDR_MAINFRM);
	wce.style = CS_HREDRAW|CS_VREDRAW;
	ATOM nAtom = RegisterClassEx(&wce);
	if(nAtom==0)
	{
		return FALSE;
	}
	return TRUE;
}

// 创建主窗口
HWND CreateMain(LPSTR pszClassName)
{
	HWND hwnd = CreateWindow(pszClassName, "Main", WS_OVERLAPPEDWINDOW,
		 CW_USEDEFAULT, CW_USEDEFAULT, Game::getClientWidth()+5*2, Game::getClientHeight()+51+5,
		 NULL, NULL, g_hInstance, NULL);
	return hwnd;
}

void Display(HWND hwnd)
{
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
}

void Message()
{
	MSG msg = {0};
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	g_hInstance = hInstance;
	AllocConsole();
	g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	Register("MAINWND", MainProc);
	HWND hMain = CreateMain("MAINWND");
	gamep = new Game(hInstance, hMain);
	Display(hMain);
	Message();
	delete gamep;
	return 0;
}
