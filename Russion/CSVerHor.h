#ifndef CSVERHOR_H_
#define CSVERHOR_H_

#include <windows.h>
#include <vector>
#include "CombinShape.h"
using namespace std;

class CSVerHor : public CombinShape
{
	private:
		COLORREF color;
	protected:
		virtual void turned0(vector<Point>&);
		virtual void turned1(vector<Point>&);
		virtual void turned2(vector<Point>&);
		virtual void turned3(vector<Point>&);
	public:
		CSVerHor(HWND hwnd, COLORREF color) : CombinShape(hwnd), color(color) {}
		virtual ~CSVerHor() {}
};

#endif /* CSVERHOR_H_ */
