#ifndef GAME_H_
#define GAME_H_

#include <windows.h>
#include <vector>
#include <queue>
#include "CombinShape.h"
#include "BaseShape.h"
using namespace std;

class Game
{
	private:
		static const int GAME_STATUS_START;
		static const int GAME_STATUS_PAUSE;
		static const int GAME_STATUS_OVER;
		static const int GAME_LOG_SCORE;
		static const int GAME_LOG_LEVEL;
		static const int GAME_LOG_BOTTOM;
		static const int GAME_TIME_ID;
		static const int GAME_TIME_OUT;
		static const int GAME_BASESCORE;
		static const int GAME_LEVELUP_BASESCORE;
		static const int GAME_LEVEL_MAX;
		static const int GAME_TREASURE_RATE;
		static const int GAME_TREASURE_SLOW_TIME_ID;
	public:
		static const int GAME_LOGIC_WIDTH;
		static const int GAME_LOGIC_HEIGHT;
		static const int GAME_WIDTH_RESERVE;
		static const int GAME_SCOREPANLE_HEIGHT;
		static const int GAME_BOTTOMPANLE_HEIGHT;

		static int getClientWidth();
		static int getClientHeight();
	private:
		HINSTANCE hInstance;
		HWND hwnd;
		HMENU popupMenu;
		unsigned long timeCount;
		int gameStatus;
		int score;
		int level;
		CombinShape* curCS;
		int curLogicX;
		int curLogicY;
		int nextShape;
		int treasure_slowTime;
		vector<vector<BaseShape*> >* bsVector;
		int offLevel;
		queue<int> specialBsQueue;
		void generatorCombinShape();
		void addCurCSToVector(int, int);
		void gameOver();
		void freeVector();
		void reduction();
		void doReduction(int, int);
		void addScore(int);
		void drawNextShape();
		CombinShape* getNewCS(int, COLORREF);
		void setTreasure(CombinShape*);
		void doTreasure(BaseShape*, int, int);
	public:
		Game(HINSTANCE, HWND);
		virtual ~Game();
		void startGame();
		void pauseGame();
		void continueGame();
		void stopGame();
		void setLevel(int);
		void draw();
		void log(int, LPCTSTR);
		void setPopupMenu(HMENU);
		void turn();
		void down();
		void left();
		void right();
		void slowTimer(HWND, UINT, UINT, DWORD);
		static int getXFromLogicX(int);
		static int getYFromLogicY(int);
};

#endif /* GAME_H_ */
