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
	//��һ�������ӣ�����Ԥ�С�������������һ�������Ƿ����γɷ���״̬��
	void SetFlagChessNode(int x, int y, int id);
	
	//�Ƿ��������ʤ
	bool IsWin(int x, int y);

	//�Ƿ����γ�����
	bool IsFive(int x, int y, int dir);
	//�Ƿ����γ�����
	bool IsFour(int const x, int const y, int dir);
	
	//����
	bool IsDoubleThree(int x, int y, int dir);
	//����
	int IsDoubleFour(int x, int y, int dir);
	
	//˫������
	bool IsForbiddenDoubleThree(int x, int y);
	//˫�Ľ���
	bool IsForbiddenDoubleFour(int x, int y);
	//��������
	bool IsForbiddenLongLink(int x, int y);
};

