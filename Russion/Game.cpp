#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <typeinfo>
#include "resource.h"
#include "Game.h"
#include "BSRect.h"
#include "BSBmp.h"
#include "BaseShape.h"
#include "CombinShape.h"
#include "CSRect.h"
#include "CSVerHor.h"
#include "CSHorVer.h"
#include "CSVer.h"
#include "CSVHV.h"
#include "CSReVHV.h"
#include "CSTu.h"
#include "CSOne.h"
#include "CSTwo.h"
using namespace std;

const int Game::GAME_STATUS_START = 0;
const int Game::GAME_STATUS_PAUSE = 1;
const int Game::GAME_STATUS_OVER = 2;
const int Game::GAME_LOG_SCORE = 0;
const int Game::GAME_LOG_LEVEL = 1;
const int Game::GAME_LOG_BOTTOM = 2;
const int Game::GAME_TIME_ID = 1;
const int Game::GAME_TREASURE_SLOW_TIME_ID = 2;
const int Game::GAME_TIME_OUT = 100;
const int Game::GAME_BASESCORE = 10;
const int Game::GAME_LEVELUP_BASESCORE = 100;
const int Game::GAME_LEVEL_MAX = 4;
const int Game::GAME_TREASURE_RATE = 10;

const int Game::GAME_LOGIC_WIDTH = 10;
const int Game::GAME_LOGIC_HEIGHT = 16;
const int Game::GAME_WIDTH_RESERVE = 100;
const int Game::GAME_SCOREPANLE_HEIGHT = 20;
const int Game::GAME_BOTTOMPANLE_HEIGHT = 20;

int Game::getClientWidth()
{
	// 保留区 边框 空格1 实际画图区 空格1 边框 保留区
	return GAME_LOGIC_WIDTH*BaseShape::BASESHAPE_WIDTH+(GAME_LOGIC_WIDTH-1)*CombinShape::COMBINSHAPE_GAP+2+2+GAME_WIDTH_RESERVE*2;
}

int Game::getClientHeight()
{
	return GAME_LOGIC_HEIGHT*BaseShape::BASESHAPE_HEIGHT+(GAME_LOGIC_HEIGHT-1)*CombinShape::COMBINSHAPE_GAP+2+2+GAME_SCOREPANLE_HEIGHT+GAME_BOTTOMPANLE_HEIGHT;
}

Game::Game(HINSTANCE hInstance, HWND hwnd) : hInstance(hInstance), hwnd(hwnd), gameStatus(GAME_STATUS_OVER), score(0), level(1), timeCount(0), curCS(NULL), curLogicX(0), curLogicY(0), bsVector(NULL), nextShape(-1), treasure_slowTime(0), offLevel(-1)
{
	bsVector = new vector<vector<BaseShape*> >(GAME_LOGIC_WIDTH, vector<BaseShape*>(GAME_LOGIC_HEIGHT));
}

void Game::freeVector()
{
	for(int i=0;i<GAME_LOGIC_WIDTH;i++)
	{
		for(int j=0;j<GAME_LOGIC_HEIGHT;j++)
		{
			if((*bsVector)[i][j]!=NULL)
			{
				delete (*bsVector)[i][j];
				(*bsVector)[i][j] = NULL;
			}
		}
	}
}

Game::~Game()
{
	freeVector();
	delete bsVector;
}

void Game::startGame()
{
	if(gameStatus==GAME_STATUS_START)
	{
		log(GAME_LOG_BOTTOM, "游戏已经开始!");
	}
	else if(gameStatus==GAME_STATUS_PAUSE)
	{
		log(GAME_LOG_BOTTOM, "游戏已经开始!");
	}
	else if(gameStatus==GAME_STATUS_OVER)
	{
		gameStatus = GAME_STATUS_START;
		EnableMenuItem(popupMenu, ID_BEGIN, MF_GRAYED);
		EnableMenuItem(popupMenu, ID_PAUSE, MF_ENABLED);
		EnableMenuItem(popupMenu, ID_CONTINUE, MF_GRAYED);
		EnableMenuItem(popupMenu, ID_OVER, MF_ENABLED);
		SetTimer(hwnd, GAME_TIME_ID, GAME_TIME_OUT/level, NULL);

		RECT rect;
		rect.left = GAME_WIDTH_RESERVE;
		rect.top = GAME_SCOREPANLE_HEIGHT;
		rect.right = GAME_WIDTH_RESERVE+2+GAME_LOGIC_WIDTH*BaseShape::BASESHAPE_WIDTH+(GAME_LOGIC_WIDTH-1)*CombinShape::COMBINSHAPE_GAP+1;
		rect.bottom = GAME_SCOREPANLE_HEIGHT+2+GAME_LOGIC_HEIGHT*BaseShape::BASESHAPE_HEIGHT+(GAME_LOGIC_HEIGHT-1)*CombinShape::COMBINSHAPE_GAP+1;
		InvalidateRect(hwnd, &rect, TRUE);
		PAINTSTRUCT ps = {0};
		HDC hdc = BeginPaint(hwnd, &ps);
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
		EndPaint(hwnd, &ps);
		log(GAME_LOG_BOTTOM, "游戏开始");
		CHAR szText[256];
		sprintf(szText, "当前等级: %d", level);
		log(GAME_LOG_LEVEL, szText);
		sprintf(szText, "分数: %d", score);
		log(GAME_LOG_SCORE, szText);
		srand((unsigned int)time(NULL));
	}
}

void Game::pauseGame()
{
	if(gameStatus==GAME_STATUS_OVER)
	{
		log(GAME_LOG_BOTTOM, "游戏未开始, 不需要暂停!");
	}
	else if(gameStatus==GAME_STATUS_PAUSE)
	{
		log(GAME_LOG_BOTTOM, "游戏已经暂停!");
	}
	else if(gameStatus==GAME_STATUS_START)
	{
		gameStatus = GAME_STATUS_PAUSE;
		EnableMenuItem(popupMenu, ID_BEGIN, MF_GRAYED);
		EnableMenuItem(popupMenu, ID_PAUSE, MF_GRAYED);
		EnableMenuItem(popupMenu, ID_CONTINUE, MF_ENABLED);
		EnableMenuItem(popupMenu, ID_OVER, MF_ENABLED);
		KillTimer(hwnd, GAME_TIME_ID);
	}
}

void Game::continueGame()
{
	if(gameStatus==GAME_STATUS_OVER)
	{
		log(GAME_LOG_BOTTOM, "游戏未开始, 不需要继续!");
	}
	else if(gameStatus==GAME_STATUS_PAUSE)
	{
		gameStatus = GAME_STATUS_START;
		EnableMenuItem(popupMenu, ID_BEGIN, MF_GRAYED);
		EnableMenuItem(popupMenu, ID_PAUSE, MF_ENABLED);
		EnableMenuItem(popupMenu, ID_CONTINUE, MF_GRAYED);
		EnableMenuItem(popupMenu, ID_OVER, MF_ENABLED);
		SetTimer(hwnd, GAME_TIME_ID, GAME_TIME_OUT/level, NULL);
	}
	else if(gameStatus==GAME_STATUS_START)
	{
		log(GAME_LOG_BOTTOM, "游戏没有暂停, 不需要继续!");
	}
}

void Game::stopGame()
{
	if(gameStatus==GAME_STATUS_OVER)
	{
		log(GAME_LOG_BOTTOM, "游戏已经结束!");
	}
	else
	{
		gameStatus = GAME_STATUS_OVER;
		EnableMenuItem(popupMenu, ID_BEGIN, MF_ENABLED);
		EnableMenuItem(popupMenu, ID_PAUSE, MF_GRAYED);
		EnableMenuItem(popupMenu, ID_CONTINUE, MF_GRAYED);
		EnableMenuItem(popupMenu, ID_OVER, MF_GRAYED);
		KillTimer(hwnd, GAME_TIME_ID);
		if(curCS!=NULL) delete curCS;
		curCS = NULL;
		freeVector();
	}
}

void Game::setLevel(int level)
{
	this->level = level;
	CHAR szText[256];
	sprintf(szText, "当前等级: %d", level);
	log(GAME_LOG_LEVEL, szText);
	if(gameStatus==GAME_STATUS_START)
	{
		SetTimer(hwnd, GAME_TIME_ID, GAME_TIME_OUT/level, NULL);
	}
}

CombinShape* Game::getNewCS(int randShape, COLORREF color)
{
	CombinShape* temp = NULL;
	switch(randShape)
	{
		case 0:
		{
			temp = new CSHorVer(hwnd, color);
			break;
		}
		case 1:
		{
			temp = new CSRect(hwnd, color);
			break;
		}
		case 2:
		{
			temp = new CSReVHV(hwnd, color);
			break;
		}
		case 3:
		{
			temp = new CSTu(hwnd, color);
			break;
		}
		case 4:
		{
			temp = new CSVer(hwnd, color);
			break;
		}
		case 5:
		{
			temp = new CSVerHor(hwnd, color);
			break;
		}
		case 6:
		{
			temp = new CSVHV(hwnd, color);
			break;
		}
	}
	if(temp!=NULL) temp->initShapeVector();
	return temp;
}

void Game::setTreasure(CombinShape* cs)
{
	HBITMAP hBmp = 0;
	int bmpId = 0;
	int tType = rand()%4;
	switch(tType)
	{
		case 0:
			bmpId = IDB_CLOCK;
			break;
		case 1:
			bmpId = IDB_BOMB;
			break;
		case 2:
			bmpId = IDB_ONE;
			break;
		case 3:
			bmpId = IDB_TWO;
			break;
	}
	if(bmpId!=0)
	{
		BaseShape* bs = new BSBmp(hInstance, hwnd, bmpId);
		cs->setTreasure(bs);
	}
}

void Game::generatorCombinShape()
{
	if(curCS!=NULL)
	{
		delete curCS;
		curCS = NULL;
		curLogicX = 0;
		curLogicY = 0;
	}
	if(nextShape==-1)
	{
		nextShape = rand()%7;
	}
	COLORREF color = RGB(rand()%256,rand()%256,rand()%256);
	if(specialBsQueue.size()!=0)
	{
		int special = specialBsQueue.front();
		specialBsQueue.pop();
		switch(special)
		{
			case IDB_ONE:
				curCS = new CSOne(hwnd, color);
				break;
			case IDB_TWO:
				curCS = new CSTwo(hwnd, color);
				break;
		}
		curCS->initShapeVector();
	}
	else
	{
		curCS = getNewCS(nextShape, color);
		if(rand()%100<GAME_TREASURE_RATE)
		{
			setTreasure(curCS);
		}
		nextShape = rand()%7;
		drawNextShape();
	}
	curLogicX = GAME_LOGIC_WIDTH/2-curCS->getLogicWidth()/2;
	curLogicY = -1;
}

void Game::drawNextShape()
{
	RECT rect;
	rect.left = 0;
	rect.right = GAME_WIDTH_RESERVE-1;
	rect.top = GAME_SCOREPANLE_HEIGHT+1;
	rect.bottom = getClientHeight()-GAME_BOTTOMPANLE_HEIGHT-1;
	InvalidateRect(hwnd, &rect, TRUE);
	rect.left = getClientWidth()-GAME_WIDTH_RESERVE;
	rect.right = getClientWidth()-1;
	InvalidateRect(hwnd, &rect, TRUE);
	CombinShape* temp = getNewCS(nextShape, RGB(0,0,0));
	int tempWidth = temp->getWidth();
	int tempHeight = temp->getHeight();
	int x = (GAME_WIDTH_RESERVE-tempWidth)/2-1;
	int y = (getClientHeight()-tempHeight)/2-1;
	temp->draw(x, y);
	x += getClientWidth()-GAME_WIDTH_RESERVE;
	temp->draw(x, y);
	delete temp;
}

void Game::addCurCSToVector(int logicX, int logicY)
{
	vector<CombinShape::Point>& vt = curCS->getShapeVector();
	vector<CombinShape::Point>::iterator iter = vt.begin();
	while(iter!=vt.end())
	{
		(*bsVector)[logicX+iter->x][logicY+iter->y] = iter->bsp;
		iter++;
	}
}

void Game::gameOver()
{
	stopGame();
	BSRect bsRect(hwnd, RGB(192, 192, 192));
	for(int y=GAME_LOGIC_HEIGHT-1;y>=0;y--)
	{

		int x = 0;
		int endX = GAME_LOGIC_WIDTH;
		int off = 1;
		if(y%2==0)
		{
			x = GAME_LOGIC_WIDTH-1;
			endX = -1;
			off = -1;
		}
		while(x!=endX)
		{
			bsRect.draw(getXFromLogicX(x), getYFromLogicY(y));
			x += off;
			Sleep(10);
		}
	}
	MessageBox(hwnd, "Game Over", "提示", MB_OK);
}

void Game::down()
{
	if(gameStatus==GAME_STATUS_START&&curCS!=NULL&&!curCS->isReach(*bsVector, curLogicX, curLogicY, 0, 1))
	{
		if(curLogicY>=0) curCS->erase(getXFromLogicX(curLogicX), getYFromLogicY(curLogicY));
		curLogicY++;
		curCS->draw(getXFromLogicX(curLogicX), getYFromLogicY(curLogicY));
	}
}

void Game::left()
{
	if(gameStatus==GAME_STATUS_START&&curCS!=NULL&&curLogicX>0&&!curCS->isReach(*bsVector, curLogicX, curLogicY, -1, 0))
	{
		if(curLogicY>=0) curCS->erase(getXFromLogicX(curLogicX), getYFromLogicY(curLogicY));
		curLogicX--;
		curCS->draw(getXFromLogicX(curLogicX), getYFromLogicY(curLogicY));
	}
}

void Game::right()
{
	if(gameStatus==GAME_STATUS_START&&curCS!=NULL&&(curLogicX+curCS->getLogicWidth())<GAME_LOGIC_WIDTH&&!curCS->isReach(*bsVector, curLogicX, curLogicY, 1, 0))
	{
		if(curLogicY>=0) curCS->erase(getXFromLogicX(curLogicX), getYFromLogicY(curLogicY));
		curLogicX++;
		curCS->draw(getXFromLogicX(curLogicX), getYFromLogicY(curLogicY));
	}
}

void Game::reduction()
{
	vector<int> reductionVector;
	vector<CombinShape::Point>& vt = curCS->getShapeVector();
	vector<CombinShape::Point>::iterator iter = vt.begin();
	while(iter!=vt.end())
	{
		bool had = false;
		vector<int>::iterator intIter = reductionVector.begin();
		while(intIter!=reductionVector.end())
		{
			if(*intIter==curLogicY+iter->y)
			{
				had = true;
				break;
			}
			intIter++;
		}
		if(!had)
		{
			bool needReduction = true;
			for(int i=0;i<GAME_LOGIC_WIDTH;i++)
			{
				if((*bsVector)[i][curLogicY+iter->y]==NULL)
				{
					needReduction = false;
					break;
				}
			}
			if(needReduction) reductionVector.push_back(curLogicY+iter->y);
		}
		iter++;
	}
	sort(reductionVector.begin(), reductionVector.end());
	int removeCount = 1;
	int lastNum = -2;
	for(int i=0;i<reductionVector.size();i++)
	{
		if(lastNum==-2)
		{
			lastNum = reductionVector[i];
		}
		else if(reductionVector[i]==lastNum+1)
		{
			removeCount++;
			lastNum = reductionVector[i];
		}
		else
		{
			doReduction(lastNum, removeCount);
			removeCount = 1;
			lastNum = reductionVector[i];
		}
	}
	if(lastNum!=-2) doReduction(lastNum, removeCount);
	// 重画消除之后的区域
	if(reductionVector.size()>0)
	{
		RECT rect;
		rect.left = GAME_WIDTH_RESERVE+1;
		rect.top = GAME_SCOREPANLE_HEIGHT+1;
		rect.right = GAME_WIDTH_RESERVE+2+GAME_LOGIC_WIDTH*BaseShape::BASESHAPE_WIDTH+(GAME_LOGIC_WIDTH-1)*CombinShape::COMBINSHAPE_GAP;
		rect.bottom = GAME_SCOREPANLE_HEIGHT+2+(lastNum+1)*BaseShape::BASESHAPE_HEIGHT+lastNum*CombinShape::COMBINSHAPE_GAP;
		InvalidateRect(hwnd, &rect, TRUE);
		for(int x=0;x<GAME_LOGIC_WIDTH;x++)
		{
			for(int y=0;y<=lastNum;y++)
			{
				if((*bsVector)[x][y]!=NULL)
				{
					(*bsVector)[x][y]->draw(getXFromLogicX(x), getYFromLogicY(y));
				}
			}
		}
		addScore(reductionVector.size());
	}
}

void Game::addScore(int count)
{
	score += count*GAME_BASESCORE;
	CHAR szText[256];
	sprintf(szText, "分数: %d", score);
	log(GAME_LOG_SCORE, szText);
	int sumlevel = 0;
	if(offLevel==-1)
	{
		for(int i=1;i<=level-1;i++)
		{
			sumlevel += i;
		}
		if(level<GAME_LEVEL_MAX&&score-GAME_LEVELUP_BASESCORE*sumlevel==level*GAME_LEVELUP_BASESCORE)
		{
			log(GAME_LOG_BOTTOM, "恭喜进入下一个等级!");
			setLevel(level+1);
		}
	}
	else
	{
		for(int i=1;i<=level+offLevel-1;i++)
		{
			sumlevel += i;
		}
		if(level+offLevel<GAME_LEVEL_MAX&&score-GAME_LEVELUP_BASESCORE*sumlevel==(level+offLevel)*GAME_LEVELUP_BASESCORE)
		{
			log(GAME_LOG_BOTTOM, "恭喜进入下一个等级!");
			offLevel++;
		}
	}
}

void CALLBACK slowTimerProc(HWND, UINT, UINT, DWORD);

void Game::slowTimer(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	treasure_slowTime--;
	if(treasure_slowTime==0)
	{
		log(GAME_LOG_BOTTOM, "减缓时间结束!");
		if(offLevel!=-1)
		{
			setLevel(level+offLevel);
			offLevel = -1;
		}
		KillTimer(hwnd, GAME_TREASURE_SLOW_TIME_ID);
	}
	else
	{
		CHAR szText[128];
		sprintf(szText, "减缓时间剩余%d秒", treasure_slowTime);
		log(GAME_LOG_BOTTOM, szText);
	}
}

void Game::doTreasure(BaseShape* treasureBS, int logicX, int logicY)
{
	typeid(*treasureBS);
	typeid(BSBmp);
	if(typeid(*treasureBS)==typeid(BSBmp))
	{
		BSBmp* temp = (BSBmp*) treasureBS;
		if(temp->getBmpId()==IDB_CLOCK)
		{
			treasure_slowTime += 20;
			if(offLevel==-1)
			{
				offLevel = level-1;
				setLevel(1);
			}
			SetTimer(hwnd, GAME_TREASURE_SLOW_TIME_ID, 1000, slowTimerProc);
		}
		else if(temp->getBmpId()==IDB_BOMB)
		{
			int bombCount = 5;
			CSOne tempCS(hwnd, RGB(192,192,192));
			tempCS.initShapeVector();
			for(int j=0;j<Game::GAME_LOGIC_HEIGHT;j++)
			{
				for(int i=0;i<GAME_LOGIC_WIDTH;i++)
				{
					if((*bsVector)[i][j]!=NULL&&i!=logicX&&j!=logicY)
					{

						tempCS.draw(getXFromLogicX(i), getYFromLogicY(j));
						Sleep(200);
						tempCS.erase(getXFromLogicX(i), getYFromLogicY(j));
						Sleep(200);
						delete (*bsVector)[i][j];
						(*bsVector)[i][j] = NULL;
						bombCount--;
					}
					if(bombCount==0) break;
				}
				if(bombCount==0) break;
			}
		}
		else if(temp->getBmpId()==IDB_ONE)
		{
			specialBsQueue.push(IDB_ONE);
		}
		else if(temp->getBmpId()==IDB_TWO)
		{
			specialBsQueue.push(IDB_TWO);
		}
		// TODO
	}
}

void Game::doReduction(int lastNum, int removeCount)
{
	for(int j=lastNum-removeCount+1;j<=lastNum;j++)
	{
		for(int i=0;i<GAME_LOGIC_WIDTH;i++)
		{
			if((*bsVector)[i][j]!=NULL)
			{
				doTreasure((*bsVector)[i][j], i, j);
				delete (*bsVector)[i][j];
				(*bsVector)[i][j] = NULL;
			}
		}
	}
	for(int x=0;x<GAME_LOGIC_WIDTH;x++)
	{
		for(int y=lastNum-removeCount;y>=0;y--)
		{
			if((*bsVector)[x][y]!=NULL)
			{
				(*bsVector)[x][y+removeCount] = (*bsVector)[x][y];
				(*bsVector)[x][y] = NULL;
			}
		}
	}
}

void Game::draw()
{
	if(curCS==NULL)
	{
		generatorCombinShape();
	}
	timeCount++;
	if(timeCount%5==0)
	{
		if(curLogicY>=0&&curCS->isReach(*bsVector, curLogicX, curLogicY, 0, 1))
		{
			if(curLogicY==0)
			{
				gameOver();
				return;
			}
			addCurCSToVector(curLogicX, curLogicY);
			reduction();
			delete curCS;
			curCS = NULL;
		}
		else
		{
			if(curLogicY>=0) curCS->erase(getXFromLogicX(curLogicX), getYFromLogicY(curLogicY));
			curCS->draw(getXFromLogicX(curLogicX), getYFromLogicY(++curLogicY));
		}
	}
}

void Game::turn()
{
	if(gameStatus==GAME_STATUS_START&&curCS!=NULL)
	{
		curCS->turn(*bsVector, curLogicX, curLogicY);
	}
}

void Game::log(int logPos, LPCTSTR str)
{
	RECT rect = {0};
	UINT uFormat = DT_SINGLELINE|DT_VCENTER;
	if(logPos==GAME_LOG_SCORE)
	{
		rect.left = getClientWidth()/2+1;
		rect.top = 0;
		rect.right = getClientWidth();
		rect.bottom = GAME_SCOREPANLE_HEIGHT;
		uFormat |= DT_RIGHT;
	}
	else if(logPos==GAME_LOG_LEVEL)
	{
		rect.left = 0;
		rect.top = 0;
		rect.right = getClientWidth()/2;
		rect.bottom = GAME_SCOREPANLE_HEIGHT;
		uFormat |= DT_LEFT;
	}
	else if(logPos==GAME_LOG_BOTTOM)
	{
		rect.left = 0;
		rect.top = getClientHeight()-GAME_BOTTOMPANLE_HEIGHT;
		rect.right = getClientWidth();
		rect.bottom = getClientHeight();
		uFormat |= DT_LEFT;
	}
	InvalidateRect(hwnd, &rect, TRUE);
	PAINTSTRUCT ps = {0};
	HDC hdc = BeginPaint(hwnd, &sp);
	SetBkMode(hdc, TRANSPARENT);
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	DrawText(hdc, str, strlen(str), &rect, uFormat);
	EndPaint(hwnd, &ps);
}

void Game::setPopupMenu(HMENU popupMenu)
{
	this->popupMenu = popupMenu;
}

int Game::getXFromLogicX(int logicX)
{
	return GAME_WIDTH_RESERVE + 2 + logicX*BaseShape::BASESHAPE_WIDTH+logicX*CombinShape::COMBINSHAPE_GAP;
}

int Game::getYFromLogicY(int logicY)
{
	return GAME_SCOREPANLE_HEIGHT + 2 + logicY*BaseShape::BASESHAPE_HEIGHT+logicY*CombinShape::COMBINSHAPE_GAP;
}
