#pragma once
#include "Board.h"

class IsForbiddenPoint
{
public:
	IsForbiddenPoint(Board* ChessBoard);
	~IsForbiddenPoint();
	bool CheckPoint(int x, int y);
protected:
	Board* ChessBoard;
	int ChessBoardSize;
private:
	//落一个假棋子，用于预判。（加入这里有一个棋子是否能形成否中状态）
	void SetFlagChessNode(int x, int y, int id);
	
	//是否可五连获胜
	bool IsWin(int x, int y);

	//是否能形成五连
	bool IsFive(int x, int y, int dir);
	//是否能形成四连
	bool IsFour(int const x, int const y, int dir);
	
	//活三
	bool IsDoubleThree(int x, int y, int dir);
	//活四
	int IsDoubleFour(int x, int y, int dir);
	
	//双三禁手
	bool IsForbiddenDoubleThree(int x, int y);
	//双四禁手
	bool IsForbiddenDoubleFour(int x, int y);
	//长连禁手
	bool IsForbiddenLongLink(int x, int y);
};

