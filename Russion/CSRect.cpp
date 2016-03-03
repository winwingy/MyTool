#include <windows.h>
#include <vector>
#include "CSRect.h"
#include "BSRect.h"
using namespace std;

void CSRect::turned0(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		for(int j=0;j<=1;j++)
		{
			for(int i=0;i<=1;i++)
			{
				Point point;
				point.x = i;
				point.y = j;
				point.bsp = new BSRect(hwnd, color);
				vt.push_back(point);
			}
		}
	}
	else
	{
		int idx = 0;
		for(int j=0;j<=1;j++)
		{
			for(int i=0;i<=1;i++)
			{
				vt[idx].x = i;
				vt[idx++].y = j;
			}
		}
	}
}

void CSRect::turned1(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	for(int i=1;i>=0;i--)
	{
		for(int j=0;j<=1;j++)
		{
			vt[idx].x = i;
			vt[idx++].y = j;
		}
	}
}

void CSRect::turned2(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	for(int j=1;j>=0;j--)
	{
		for(int i=1;i>=0;i--)
		{
			vt[idx].x = i;
			vt[idx++].y = j;
		}
	}
}

void CSRect::turned3(vector<Point>& vt)
{
	if(vt.size()==0)
	{
		turned0(vt);
	}
	int idx = 0;
	for(int i=0;i<=1;i++)
	{
		for(int j=1;j>=0;j--)
		{
			vt[idx].x = i;
			vt[idx++].y = j;
		}
	}
}
