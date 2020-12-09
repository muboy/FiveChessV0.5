#include "Judge.h"

Judge::Judge(Board* ChessBoard, int NumNodeInLine) {
	this->ChessBoard = ChessBoard;
	this->ChessBoardSize = this->ChessBoard->GetBoardSize();
	this->NumNodeInLine = NumNodeInLine;
}
// ���� 1 ��λ��ʤ�������� 0 ��λ���޷���ʤ�� ���� -1 ����
int Judge::SimpleScan(int p) {
	if (p == -1) {//����
		//printf("������\n");
		return -1;
	}
	int x = p / this->ChessBoardSize;
	int y = p % this->ChessBoardSize;
	if (y == 0) {
		x--;
		y = this->ChessBoardSize;
	}
	//printf("p=%d,x=%d,y=%d\n", p, x, y);
	int num[4] = { 1,1,1,1 };//num[4] ={���� ���� ��б\ б��/}
	int DirectVectorX[8] = { 0,0,-1,1,-1,1,1,-1 };//�������£��������ϣ���������
	int DirectVectorY[8] = { -1,1,0,0,-1,1,-1,1 };
	int mx = x;
	int my = y;
	for (int i = 0; i < 8; i++) {//ָ�����ְ˸�����ɨ��,����	
		mx = x;
		my = y;
		if (x + DirectVectorX[i] >= 1 && x + DirectVectorX[i] <= this->ChessBoardSize && y + \
			DirectVectorY[i] >= 1 && y + DirectVectorY[i] <= this->ChessBoardSize)
			for (int j = 0; j <= this->NumNodeInLine; j++) {//ָ��ɨ�����ӵĸ���,���
				mx += DirectVectorX[i];
				my += DirectVectorY[i];
				if (mx >= 1 && mx <= this->ChessBoardSize && my >= 1 && my <= this->ChessBoardSize) {
					if (this->ChessBoard->ShowNode(x, y).GetPlayerId() == this->ChessBoard->ShowNode(mx, my).GetPlayerId()) {
						num[i / 2] += 1;
					}
					else
					{
						break;
					}
				}
			}
	}
	for (int i = 0; i < 4; i++) {
		if (num[i] >= this->NumNodeInLine)
			return 1;
	}
	return 0;
}
/*
	bool Judge::DFS(Board board, int ChessBoardSize, int x, int y, int id, int count) {
		static int dirvectorx[8] = { 0,0,-1,1,-1,1,1,-1 };//�������£��������ϣ���������
		static int dirvectory[8] = { -1,1,0,0,-1,1,-1,1 };
		static int i = 0;
		if (count <= 0) {
			i = 0;
			return true;
		}
		else {
			if (board.ShowNode(x, y).GetPlayerId() == id && x >= 1 && x <= ChessBoardSize && y >= 1 && y <= ChessBoardSize) {
				i++;
				DFS(board, ChessBoardSize, x + dirvectorx[i], y + dirvectory[i], id, count++);
			}
			else {
				i = 0;
				return false;
			}
		}
	}
*/