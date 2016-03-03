#include <windows.h>
#include <vector>
#include "CSTwo.h"
#include "BSRect.h"
using namespace std;

void CSTwo::turned0(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		for(int i=0;i<=1;i++)
		{
			Point point;
			point.x = i;
			point.y = 0;
			point.bsp = new BSRect(hwnd, color);
			vt.push_back(point);
		}
	}
	else
	{
		int idx = 0;
		for(int i=0;i<=1;i++)
		{
			vt[idx].x = i;
			vt[idx++].y = 0;
		}
	}
}

void CSTwo::turned1(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	for(int j=0;j<=1;j++)
	{
		vt[idx].x = 0;
		vt[idx++].y = j;
	}
}

void CSTwo::turned2(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	for(int i=1;i>=0;i--)
	{
		vt[idx].x = i;
		vt[idx++].y = 0;
	}
}

void CSTwo::turned3(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	for(int j=1;j>=0;j--)
	{
		vt[idx].x = 0;
		vt[idx++].y = j;
	}
}
