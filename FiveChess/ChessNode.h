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
	int location;// ���ӵ�λ�� location = x*ChessBoardSize + y
	int Name;//��������壬ÿ���������ֲ�ͬ
	int playerid;// �ڷ� 1  �׷� 2
	int status;//���� 10 �������µĺ��� 11 ���� 20 �������µİ��� 21
};

