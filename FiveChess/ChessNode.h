#pragma once
#include <iostream>
#include <stack>
#include<stdio.h>
#include <cstdlib>
#include <ctime>
#include<stdlib.h>
#include<ctype.h>
#include<Windows.h>

//using namespace std;

class ChessNode
{
public:
	ChessNode();
	ChessNode(int x);
	void SetChessNodeStatus(int status);
	void SetLocatoin(int p);
	void SetPlayerId(int id);
	void SetChessNode(int p, int id, int status);
	int GetLocation();
	int GetPlayerId();
	int GetChessNodeStatus();
private:
	int location;// 棋子的位置 location = x*ChessBoardSize + y
	int Name;//如果是象棋，每个棋子名字不同
	int playerid;// 黑方 1  白方 2
	int status;//黑子 10 最新落下的黑子 11 白子 20 最新落下的白字 21
};

