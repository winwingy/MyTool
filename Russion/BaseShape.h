#ifndef BASESHAPE_H_
#define BASESHAPE_H_

#include <windows.h>
#include "Shape.h"

class BaseShape : public Shape
{
	public:
		static const int BASESHAPE_WIDTH;
		static const int BASESHAPE_HEIGHT;
	protected:
		BaseShape(HWND hwnd) : Shape(hwnd) {}
	public:
		virtual ~BaseShape() {}
		virtual void draw(int, int) = 0;
		virtual void erase(int, int) = 0;
};

#endif /* BASESHAPE_H_ */
