// PopupPictureOnDesktop.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "PopupPictureOnDesktop.h"
#include <GdiPlus.h>
#include "DesktopItem.h"
#include "LayerWindow.h"
#include <assert.h>
#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;
ULONG_PTR g_token = 0;
LayerWindow g_layerWindow;

#define MAX_LOADSTRING 100
#define WM_SHOW_POPUP WM_USER + 100

enum TIMER_IDS
{
    TIMER_GETPOS,
    TIMER_SHOWPOPUP,
};

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_POPUPPICTUREONDESKTOP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_POPUPPICTUREONDESKTOP));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POPUPPICTUREONDESKTOP));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_POPUPPICTUREONDESKTOP);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
        {
            PostQuitMessage(0);
            GdiplusShutdown(g_token);
            break;
        }
    case WM_CREATE:
        {
            GdiplusStartupInput gidStart;
            GdiplusStartup(&g_token, &gidStart, nullptr);
            SetTimer(hWnd, TIMER_GETPOS, 1000, nullptr);
            break;
        }
    case WM_TIMER:
        {  
            KillTimer(hWnd, wParam);
            if (wParam == TIMER_GETPOS)
            {
                ShowWindow(hWnd, SW_HIDE);
                RECT rc = {0};
                if (!DesktopItem::GetDesktopIcon(L"酷狗音乐", &rc))
                {
                    assert(FALSE);
                    break;
                }
                int createWidth = 300;
                int createHeight = 200;
                int createTop = rc.top  - createHeight/2 + (rc.bottom - rc.top)/2;
                HWND hwndCreate = g_layerWindow.Create(
                    DesktopItem::GetDesktopTreeHwnd(), 
                    rc.right, createTop, createWidth, createHeight);
                SetTimer(hWnd, TIMER_SHOWPOPUP, 1000, nullptr);
            }
            else if (wParam == TIMER_SHOWPOPUP)
            {
                g_layerWindow.Show(L"D:\\test\\left.png",
                    L"D:\\test\\mainPng.png",
                    L"D:\\test\\Close.png");
//                 SetParent(g_layerWindow.GetHWND(), DesktopItem::GetDesktopProgmanHwnd());
//                 
//                 LONG style = GetWindowLongPtrW(g_layerWindow.GetHWND(), GWL_STYLE);
//                 SetWindowLongPtr(g_layerWindow.GetHWND(), GWL_STYLE, style | WS_POPUP);

                UpdateWindow(g_layerWindow.GetHWND());
                SetWindowPos( g_layerWindow.GetHWND(),
                    HWND_BOTTOM, 
                    0, 0, 0, 0,
                    SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
                SetWindowPos( DesktopItem::GetDesktopProgmanHwnd(),
                    g_layerWindow.GetHWND(), 
                    0, 0, 0, 0,
                    SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
            }
            break;
        }
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
