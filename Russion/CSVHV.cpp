#include <windows.h>
#include <vector>
#include "CSVHV.h"
#include "BaseShape.h"
#include "BSRect.h"
using namespace std;

void CSVHV::turned0(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		int j;
		for(j=0;j<=1;j++)
		{
			Point point;
			point.x = 0;
			point.y = j;
			point.bsp = new BSRect(hwnd, color);
			vt.push_back(point);
		}
		for(j=1;j<=2;j++)
		{
			Point point;
			point.x = 1;
			point.y = j;
			point.bsp = new BSRect(hwnd, color);
			vt.push_back(point);
		}
	}
	else
	{
		int idx = 0;
		int j;
		for(j=0;j<=1;j++)
		{
			vt[idx].x = 0;
			vt[idx++].y = j;
		}
		for(j=1;j<=2;j++)
		{
			vt[idx].x = 1;
			vt[idx++].y = j;
		}
	}
}

void CSVHV::turned1(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	int i;
	for(i=2;i>=1;i--)
	{
		vt[idx].x = i;
		vt[idx++].y = 0;
	}
	for(i=1;i>=0;i--)
	{
		vt[idx].x = i;
		vt[idx++].y = 1;
	}
}

void CSVHV::turned2(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	int j;
	for(j=2;j>=1;j--)
	{
		vt[idx].x = 1;
		vt[idx++].y = j;
	}
	for(j=1;j>=0;j--)
	{
		vt[idx].x = 0;
		vt[idx++].y = j;
	}
}

void CSVHV::turned3(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	int i;
	for(i=0;i<=1;i++)
	{
		vt[idx].x = i;
		vt[idx++].y = 1;
	}
	for(i=1;i<=2;i++)
	{
		vt[idx].x = i;
		vt[idx++].y = 0;
	}
}
