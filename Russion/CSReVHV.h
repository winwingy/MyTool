#ifndef CSREVHV_H_
#define CSREVHV_H_

#include <windows.h>
#include <vector>
#include "CombinShape.h"
using namespace std;

class CSReVHV : public CombinShape
{
	private:
		COLORREF color;
	protected:
		virtual void turned0(vector<Point>&);
		virtual void turned1(vector<Point>&);
		virtual void turned2(vector<Point>&);
		virtual void turned3(vector<Point>&);
	public:
		CSReVHV(HWND hwnd, COLORREF color) : CombinShape(hwnd), color(color) {}
		virtual ~CSReVHV() {}
};

#endif /* CSREVHV_H_ */
