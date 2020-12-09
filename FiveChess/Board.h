#pragma once
#include"ChessNode.h"
#define BLACK 1
#define WHITE 2
#define EMPTY -1
#define XY2P(x,y,ChessBoardSize) (x)*(ChessBoardSize)+(y) 

class Board
{
public:
	Board(int ChessBoardSize);
	~Board();
	int GetBoardSize();
	bool PlcaeNode(int p, int id);
	ChessNode ShowNode(int x, int y);
	//ChessNode ShowGoBackStep();
	//void GoBackStep();
	void SubstitutePreFlag();
	void DisplayBoard();
private:
	int ChessBoardSize;
	ChessNode** board;
	//stack<ChessNode> route;
};

