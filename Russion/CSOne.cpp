#include <windows.h>
#include <vector>
#include "CSOne.h"
#include "BSRect.h"
using namespace std;

void CSOne::turned0(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		Point point;
		point.x = 0;
		point.y = 0;
		point.bsp = new BSRect(hwnd, color);
		vt.push_back(point);
	}
}

void CSOne::turned1(vector<Point>& vt)
{
	turned0(vt);
}

void CSOne::turned2(vector<Point>& vt)
{
	turned0(vt);
}

void CSOne::turned3(vector<Point>& vt)
{
	turned0(vt);
}
