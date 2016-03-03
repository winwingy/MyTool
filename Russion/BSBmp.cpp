#include <windows.h>
#include "BSBmp.h"

void BSBmp::draw(int x, int y)
{
	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x+BaseShape::BASESHAPE_WIDTH;
	rect.bottom = y+BaseShape::BASESHAPE_HEIGHT;
	InvalidateRect(hwnd, &rect, TRUE);
	PAINTSTRUCT ps = {0};
	HDC hdc = BeginPaint(hwnd, &ps);
	HBITMAP hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(bmpId));
	BITMAP bitmap;
	GetObject(hBitmap, sizeof(bitmap), &bitmap); // 获得位图的信息
	HDC hBitmapDC = CreateCompatibleDC(hdc);
	HGDIOBJ hOldBmp = SelectObject(hBitmapDC, hBitmap);
	StretchBlt(hdc, x, y, BASESHAPE_WIDTH, BASESHAPE_HEIGHT, hBitmapDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	SelectObject(hBitmapDC, hOldBmp);
	DeleteObject(hBitmap);
	DeleteDC(hBitmapDC);
	EndPaint(hwnd, &ps);
}

void BSBmp::erase(int x, int y)
{
	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x+BaseShape::BASESHAPE_WIDTH;
	rect.bottom = y+BaseShape::BASESHAPE_HEIGHT;
	InvalidateRect(hwnd, &rect, TRUE);
}
