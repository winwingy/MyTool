#ifndef CSONE_H_
#define CSONE_H_

#include <windows.h>
#include <vector>
#include "CombinShape.h"
using namespace std;

class CSOne : public CombinShape
{
	private:
		COLORREF color;
	protected:
		virtual void turned0(vector<Point>&);
		virtual void turned1(vector<Point>&);
		virtual void turned2(vector<Point>&);
		virtual void turned3(vector<Point>&);
	public:
		CSOne(HWND hwnd, COLORREF color) : CombinShape(hwnd), color(color) {}
		virtual ~CSOne() {}
};

#endif /* CSONE_H_ */
