#ifndef CSRECT_H_
#define CSRECT_H_

#include <windows.h>
#include <vector>
#include "CombinShape.h"
using namespace std;

class CSRect : public CombinShape
{
	private:
		COLORREF color;
	protected:
		virtual void turned0(vector<Point>&);
		virtual void turned1(vector<Point>&);
		virtual void turned2(vector<Point>&);
		virtual void turned3(vector<Point>&);
	public:
		CSRect(HWND hwnd, COLORREF color) : CombinShape(hwnd), color(color) {}
		virtual ~CSRect() {}
};

#endif /* CSRECT_H_ */
