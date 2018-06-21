// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>

#include <Windows.h>
#include <GdiPlus.h>
#include <string>

using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")

using std::string;

void testScopeDefine()
{
}

int _tmain(int argc, _TCHAR* argv[])
{
	Bitmap bitmap(L"D:\\test\\test.png");
	int width = bitmap.GetWidth();
	int height = bitmap.GetHeight();
	Rect rect(0, 0, width, height);
	BitmapData* data = new BitmapData;
	Status sta = Ok;
	sta = bitmap.LockBits(&rect, ImageLockModeRead|ImageLockModeWrite, 
		PixelFormat32bppARGB, data);
	BYTE* lockData = reinterpret_cast<BYTE*>(data->Scan0);

	system("PAUSE");
	return 0;
}

