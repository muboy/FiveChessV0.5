#pragma once
#include"Board.h"
#include"Judge.h"
#include"Player.h"
#include"RobotPlayer.h"

class Game
{
public:
	/*
	1 人机游戏  默认玩家值黑子
	2 机器人自己玩
	*/
	Game(int ChessBoardSize, int NumNodeInLine);
	~Game();
	void run();
private:
	int ChessBoardSize;
	int NumNodeInLine;
	int mode;
	int BLACKorWHITE;
	Board* ChessBoard;
	Player* human;
	RobotPlayer* robot, * robot_2;
	Judge* judge;
};

