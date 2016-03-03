#ifndef CSVHV_H_
#define CSVHV_H_

#include <windows.h>
#include <vector>
#include "CombinShape.h"
using namespace std;

class CSVHV : public CombinShape
{
	private:
		COLORREF color;
	protected:
		virtual void turned0(vector<Point>&);
		virtual void turned1(vector<Point>&);
		virtual void turned2(vector<Point>&);
		virtual void turned3(vector<Point>&);
	public:
		CSVHV(HWND hwnd, COLORREF color) : CombinShape(hwnd), color(color) {}
		virtual ~CSVHV() {};
};

#endif /* CSVHV_H_ */
