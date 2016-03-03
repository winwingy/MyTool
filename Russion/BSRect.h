#ifndef BSRECT_H_
#define BSRECT_H_

#include <windows.h>
#include "BaseShape.h"

class BSRect : public BaseShape
{
	private:
		COLORREF color;
	public:
		BSRect(HWND hwnd, COLORREF color) : BaseShape(hwnd), color(color) {}
		virtual ~BSRect() {}
		virtual void draw(int, int);
		virtual void erase(int, int);
};


#endif /* BSRECT_H_ */
