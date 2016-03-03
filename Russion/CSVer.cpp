#include <windows.h>
#include <vector>
#include "CSVer.h"
#include "BaseShape.h"
#include "BSRect.h"
using namespace std;

void CSVer::turned0(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		for(int j=0;j<4;j++)
		{
			Point point;
			point.x = 0;
			point.y = j;
			point.bsp = new BSRect(hwnd, color);
			vt.push_back(point);
		}
	}
	else
	{
		int idx = 0;
		for(int j=0;j<4;j++)
		{
			vt[idx].x = 0;
			vt[idx++].y = j;
		}
	}
}

void CSVer::turned1(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	for(int i=3;i>=0;i--)
	{
		vt[idx].x = i;
		vt[idx++].y = 0;
	}
}

void CSVer::turned2(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	for(int j=3;j>=0;j--)
	{
		vt[idx].x = 0;
		vt[idx++].y = j;
	}
}

void CSVer::turned3(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	for(int i=0;i<=3;i++)
	{
		vt[idx].x = i;
		vt[idx++].y = 0;
	}
}
