#pragma once
#include"Board.h"
#include"Judge.h"
#include"Player.h"
#include"RobotPlayer.h"

class Game
{
public:
	/*
	1 �˻���Ϸ  Ĭ�����ֵ����
	2 �������Լ���
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

