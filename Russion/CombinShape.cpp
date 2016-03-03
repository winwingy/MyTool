#include <vector>
#include "Game.h"
#include "CombinShape.h"
#include "BaseShape.h"
using namespace std;

const int CombinShape::COMBINSHAPE_GAP = 1;

void CombinShape::destroyVector()
{
	vector<Point>::iterator iter = shapeVector.begin();
	while(iter!=shapeVector.end())
	{
		delete iter->bsp;
		iter++;
	}
	shapeVector.clear();
}

int CombinShape::getLogicWidth()
{
	vector<Point>::iterator iter = shapeVector.begin();
	int maxX = -1;
	while(iter!=shapeVector.end())
	{
		if(iter->x>maxX)
		{
			maxX = iter->x;
		}
		iter++;
	}
	return maxX+1;
}

int CombinShape::getLogicHeight()
{
	vector<Point>::iterator iter = shapeVector.begin();
	int maxY = -1;
	while(iter!=shapeVector.end())
	{
		if(iter->y>maxY)
		{
			maxY = iter->y;
		}
		iter++;
	}
	return maxY+1;
}

int CombinShape::getWidth()
{
	if(width==0)
	{
		int maxX = getLogicWidth();
		width = maxX*BaseShape::BASESHAPE_WIDTH+(maxX-1)*COMBINSHAPE_GAP;
	}
	return width;
}

int CombinShape::getHeight()
{
	if(height==0)
	{
		int maxY = getLogicHeight();
		height = maxY*BaseShape::BASESHAPE_HEIGHT+(maxY-1)*COMBINSHAPE_GAP;
	}
	return height;
}

void CombinShape::draw(int x, int y)
{
	vector<Point>::iterator iter = shapeVector.begin();
	while(iter!=shapeVector.end())
	{
		int posx = x+iter->x*BaseShape::BASESHAPE_WIDTH;
		if(iter->x!=0)
		{
			posx += iter->x*COMBINSHAPE_GAP;
		}
		int posy = y+iter->y*BaseShape::BASESHAPE_HEIGHT;
		if(iter->y!=0)
		{
			posy += iter->y*COMBINSHAPE_GAP;
		}
		iter->bsp->draw(posx, posy);
		iter++;
	}
}

void CombinShape::erase(int x, int y)
{
	vector<Point>::iterator iter = shapeVector.begin();
	while(iter!=shapeVector.end())
	{
		int posx = x+iter->x*BaseShape::BASESHAPE_WIDTH;
		if(iter->x!=0)
		{
			posx += iter->x*COMBINSHAPE_GAP;
		}
		int posy = y+iter->y*BaseShape::BASESHAPE_HEIGHT;
		if(iter->y!=0)
		{
			posy += iter->y*COMBINSHAPE_GAP;
		}
		iter->bsp->erase(posx, posy);
		iter++;
	}
}

bool CombinShape::isReach(vector<vector<BaseShape*> >& bss, int logicX, int logicY, int offLogicX, int offLogicY)
{
	bool reach = false;
	vector<Point>::iterator iter = shapeVector.begin();
	while(iter!=shapeVector.end())
	{
		if(offLogicY==0)
		{
			if(bss[iter->x+logicX+offLogicX][iter->y+logicY+offLogicY]!=NULL)
			{
				reach = true;
				break;
			}
		}
		else
		{
			if((iter->y+logicY)==Game::GAME_LOGIC_HEIGHT-1 || bss[iter->x+logicX+offLogicX][iter->y+logicY+offLogicY]!=NULL)
			{
				reach = true;
				break;
			}
		}
		iter++;
	}
	return reach;
}

void CombinShape::turn(vector<vector<BaseShape*> >& bss, int logicX, int logicY)
{
	if(canTurn(bss, logicX, logicY))
	{
		turnCount++;
		erase(Game::getXFromLogicX(logicX), Game::getYFromLogicY(logicY));
		doTurn();
		draw(Game::getXFromLogicX(logicX), Game::getYFromLogicY(logicY));
	}
}

bool CombinShape::canTurn(vector<vector<BaseShape*> >& bss, int logicX, int logicY)
{
	bool can = true;
	int count = turnCount+1;
	vector<Point> vt;
	if(count%4==0)
	{
		turned0(vt);
	}
	else if(count%4==1)
	{
		turned1(vt);
	}
	else if(count%4==2)
	{
		turned2(vt);
	}
	else if(count%4==3)
	{
		turned3(vt);
	}
	vector<Point>::iterator it = vt.begin();
	while(it!=vt.end())
	{
		int toX = logicX+it->x;
		int toY = logicY+it->y;
		if(toX>Game::GAME_LOGIC_WIDTH-1||toY>Game::GAME_LOGIC_HEIGHT-1||bss[toX][toY]!=NULL)
		{
			can = false;
			break;
		}
		it++;
	}
	return can;
}

void CombinShape::doTurn()
{
	//destroyVector();
	if(turnCount%4==0)
	{
		turned0(shapeVector);
	}
	else if(turnCount%4==1)
	{
		turned1(shapeVector);
	}
	else if(turnCount%4==2)
	{
		turned2(shapeVector);
	}
	else if(turnCount%4==3)
	{
		turned3(shapeVector);
	}
}

void CombinShape::setTreasure(BaseShape* treasureBS)
{
	int idx = rand()%shapeVector.size();
	delete shapeVector[idx].bsp;
	shapeVector[idx].bsp = treasureBS;
}
