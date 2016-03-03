#ifndef BSBMP_H_
#define BSBMP_H_

#include <windows.h>
#include "BaseShape.h"

class BSBmp : public BaseShape
{
	private:
		HINSTANCE hInstance;
		int bmpId;
	public:
		BSBmp(HINSTANCE hInstance, HWND hwnd, int bmpId) : hInstance(hInstance), BaseShape(hwnd), bmpId(bmpId) {}
		virtual ~BSBmp() {}
		virtual void draw(int, int);
		virtual void erase(int, int);
		virtual int getBmpId() {return bmpId;}
};


#endif /* BSBMP_H_ */
