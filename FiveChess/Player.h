#pragma once
#include"Board.h"
#include"IsForbiddenPoint.h"
class Player:public IsForbiddenPoint
{
public:
	Player(int PlayId, Board* ChessBoard);

	int DoNext();
private:
	int PlayerId;
	Board* ChessBoard;
	int ChessBoardSize;
};

