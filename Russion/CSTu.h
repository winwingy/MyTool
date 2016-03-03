#ifndef CSTU_H_
#define CSTU_H_

#include <windows.h>
#include <vector>
#include "CombinShape.h"
using namespace std;

class CSTu : public CombinShape
{
	private:
		COLORREF color;
	protected:
		virtual void turned0(vector<Point>&);
		virtual void turned1(vector<Point>&);
		virtual void turned2(vector<Point>&);
		virtual void turned3(vector<Point>&);
	public:
		CSTu(HWND hwnd, COLORREF color) : CombinShape(hwnd), color(color) {}
		virtual ~CSTu() {}
};

#endif /* CSTU_H_ */
