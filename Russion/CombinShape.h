#ifndef COMBINSHAPE_H_
#define COMBINSHAPE_H_

#include <windows.h>
#include <vector>
#include "Shape.h"
#include "BaseShape.h"
using namespace std;

class CombinShape : public Shape
{
	public:
		static const int COMBINSHAPE_GAP;
		class Point
		{
			public:
				int x;
				int y;
				BaseShape* bsp;
		};
	private:
		int width;
		int height;
	protected:
		int turnCount;
		CombinShape(HWND hwnd) : Shape(hwnd), width(0), height(0), turnCount(0) {}
		vector<Point> shapeVector;
		virtual void turned0(vector<Point>&) = 0;
		virtual void turned1(vector<Point>&) = 0;
		virtual void turned2(vector<Point>&) = 0;
		virtual void turned3(vector<Point>&) = 0;
		virtual void destroyVector();
		virtual void doTurn();
		virtual bool canTurn(vector<vector<BaseShape*> >&, int, int);
	public:
		virtual void initShapeVector() {doTurn();}
		virtual ~CombinShape() {}
		virtual void turn(vector<vector<BaseShape*> >&, int, int);
		virtual void draw(int, int);
		virtual void erase(int, int);
		virtual bool isReach(vector<vector<BaseShape*> >&, int, int, int, int);
		virtual int getLogicWidth();
		virtual int getLogicHeight();
		virtual int getHeight();
		virtual int getWidth();
		virtual vector<Point>& getShapeVector() {return shapeVector;}
		virtual void setTreasure(BaseShape*);
};

#endif /* COMBINSHAPE_H_ */
