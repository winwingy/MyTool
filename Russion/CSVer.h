#ifndef CSVER_H_
#define CSVER_H_

#include <windows.h>
#include <vector>
#include "CombinShape.h"
using namespace std;

class CSVer : public CombinShape
{
	private:
		COLORREF color;
	protected:
		virtual void turned0(vector<Point>&);
		virtual void turned1(vector<Point>&);
		virtual void turned2(vector<Point>&);
		virtual void turned3(vector<Point>&);
	public:
		CSVer(HWND hwnd, COLORREF color) : CombinShape(hwnd), color(color) {}
		virtual ~CSVer() {}
};

#endif /* CSVER_H_ */
