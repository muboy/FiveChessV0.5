#pragma once
#include"Board.h"

class Judge
{
public:
	Judge(Board* ChessBoard, int NumNodeInLine);
	int SimpleScan(int p);
	//bool DFS(Board board, int ChessBoardSize, int x, int y, int id, int count);
private:
	Board* ChessBoard;
	int ChessBoardSize;
	int NumNodeInLine;// 多少连子算获胜
};

