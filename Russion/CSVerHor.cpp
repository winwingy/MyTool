#include <windows.h>
#include <vector>
#include "CSVerHor.h"
#include "BaseShape.h"
#include "BSRect.h"
using namespace std;

void CSVerHor::turned0(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		for(int j=0;j<=2;j++)
		{
			Point point;
			point.x = 0;
			point.y = j;
			point.bsp = new BSRect(hwnd, color);
			vt.push_back(point);
		}
		Point point;
		point.x = 1;
		point.y = 2;
		point.bsp = new BSRect(hwnd, color);
		vt.push_back(point);
	}
	else
	{
		int idx = 0;
		for(int j=0;j<=2;j++)
		{
			vt[idx].x = 0;
			vt[idx++].y = j;
		}
		vt[idx].x = 1;
		vt[idx++].y = 2;
	}
}

void CSVerHor::turned1(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	for(int i=2;i>=0;i--)
	{
		vt[idx].x = i;
		vt[idx++].y = 0;
	}
	vt[idx].x = 0;
	vt[idx++].y = 1;
}

void CSVerHor::turned2(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	for(int j=2;j>=0;j--)
	{
		vt[idx].x = 1;
		vt[idx++].y = j;
	}
	vt[idx].x = 0;
	vt[idx++].y = 0;
}

void CSVerHor::turned3(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	for(int i=0;i<=2;i++)
	{
		vt[idx].x = i;
		vt[idx++].y = 1;
	}
	vt[idx].x = 2;
	vt[idx++].y = 0;
}
