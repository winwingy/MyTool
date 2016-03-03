#include <windows.h>
#include <vector>
#include "CSTu.h"
#include "BSRect.h"
using namespace std;

void CSTu::turned0(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		Point point;
		point.x = 1;
		point.y = 0;
		point.bsp = new BSRect(hwnd, color);
		vt.push_back(point);
		for(int i=0;i<=2;i++)
		{
			Point point;
			point.x = i;
			point.y = 1;
			point.bsp = new BSRect(hwnd, color);
			vt.push_back(point);
		}
	}
	else
	{
		int idx = 0;
		vt[idx].x = 1;
		vt[idx++].y = 0;
		for(int i=0;i<=2;i++)
		{
			vt[idx].x = i;
			vt[idx++].y = 1;
		}
	}
}

void CSTu::turned1(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	vt[idx].x = 1;
	vt[idx++].y = 1;
	for(int j=0;j<=2;j++)
	{
		vt[idx].x = 0;
		vt[idx++].y = j;
	}
}

void CSTu::turned2(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	vt[idx].x = 1;
	vt[idx++].y = 1;
	for(int i=2;i>=0;i--)
	{
		vt[idx].x = i;
		vt[idx++].y = 0;
	}
}

void CSTu::turned3(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	vt[idx].x = 0;
	vt[idx++].y = 1;
	for(int j=2;j>=0;j--)
	{
		vt[idx].x = 1;
		vt[idx++].y = j;
	}
}
