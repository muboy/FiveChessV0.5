#pragma once
#include"Board.h"
#include"IsForbiddenPoint.h"
class RobotPlayer:public IsForbiddenPoint
{
public:
	RobotPlayer(Board* ChessBoard, int BLACKorWHITE, int NumNodeInLine);
	~RobotPlayer();
	int ComputeAI(int p);
private:
	int PlayerId;
	Board* ChessBoard;
	int ChessBoardSize;
	int NumNodeInLine;
	int count = 0;
	bool*** wins;
	int* BlackWin;
	int* WhiteWin;
};

