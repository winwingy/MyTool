#ifndef CSTWO_H_
#define CSTWO_H_

#include <windows.h>
#include <vector>
#include "CombinShape.h"
using namespace std;

class CSTwo : public CombinShape
{
	private:
		COLORREF color;
	protected:
		virtual void turned0(vector<Point>&);
		virtual void turned1(vector<Point>&);
		virtual void turned2(vector<Point>&);
		virtual void turned3(vector<Point>&);
	public:
		CSTwo(HWND hwnd, COLORREF color) : CombinShape(hwnd), color(color) {}
		virtual ~CSTwo() {}
};

#endif /* CSTWO_H_ */
