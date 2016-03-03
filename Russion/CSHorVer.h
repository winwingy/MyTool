#ifndef CSHORVER_H_
#define CSHORVER_H_

#include <windows.h>
#include <vector>
#include "CombinShape.h"
using namespace std;

class CSHorVer : public CombinShape
{
	private:
		COLORREF color;
	protected:
		virtual void turned0(vector<Point>&);
		virtual void turned1(vector<Point>&);
		virtual void turned2(vector<Point>&);
		virtual void turned3(vector<Point>&);
	public:
		CSHorVer(HWND hwnd, COLORREF color) : CombinShape(hwnd), color(color) {}
		virtual ~CSHorVer() {}
};

#endif /* CSHORVER_H_ */
