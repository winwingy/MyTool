#include <windows.h>
#include "BSRect.h"

void BSRect::draw(int x, int y)
{
	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x+BaseShape::BASESHAPE_WIDTH;
	rect.bottom = y+BaseShape::BASESHAPE_HEIGHT;
	InvalidateRect(hwnd, &rect, TRUE);
	PAINTSTRUCT ps = {0};
	HDC hdc = BeginPaint(hwnd, &ps);
	HPEN hPen = CreatePen(PS_SOLID, 1, color);
	HGDIOBJ hOldPen = SelectObject(hdc, hPen);
	HBRUSH hBrush = CreateSolidBrush(color);
	HGDIOBJ hOldBrush = SelectObject(hdc, hBrush);
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
	EndPaint(hwnd, &ps);
}

void BSRect::erase(int x, int y)
{
	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x+BaseShape::BASESHAPE_WIDTH;
	rect.bottom = y+BaseShape::BASESHAPE_HEIGHT;
	InvalidateRect(hwnd, &rect, TRUE);
}
