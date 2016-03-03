#ifndef SHAPE_H_
#define SHAPE_H_ 1

#include <windows.h>

class Shape
{
	protected:
		HWND hwnd;
		Shape(HWND hwnd) : hwnd(hwnd) {}
	public:
		virtual ~Shape() {}
		virtual void draw(int, int) = 0;
		virtual void erase(int, int) = 0;
};

#endif
