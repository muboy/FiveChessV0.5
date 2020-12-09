#include "Board.h"
Board::Board(int ChessBoardSize) {
	this->ChessBoardSize = ChessBoardSize;
	board = new ChessNode * [ChessBoardSize + 2];
	for (int i = 0; i < ChessBoardSize + 2; i++) {
		board[i] = new ChessNode[ChessBoardSize + 2];
		for (int j = 0; j < ChessBoardSize + 2; j++) {
			if (i == 0) {
				this->board[i][j].SetChessNode(i * ChessBoardSize + j, -1, j);
			}
			else if (j == 0)
			{
				this->board[i][j].SetChessNode(i * ChessBoardSize + j, -1, i);
			}
			else if (i == 1) {
				this->board[i][j].SetChessNode(i * ChessBoardSize + j, -1, 6);
			}
			else if (j == 1) {
				this->board[i][j].SetChessNode(i * ChessBoardSize + j, -1, 5);
			}
			else if (i == ChessBoardSize) {
				this->board[i][j].SetChessNode(i * ChessBoardSize + j, -1, 8);
			}
			else if (j == ChessBoardSize)
			{
				this->board[i][j].SetChessNode(i * ChessBoardSize + j, -1, 7);
			}
			else
			{
				this->board[i][j].SetChessNode(i * ChessBoardSize + j, -1, 9);
			}
		}
	}

	this->board[1][1].SetChessNode(1 * ChessBoardSize + 1, -1, 1);
	this->board[ChessBoardSize][1].SetChessNode((ChessBoardSize)*ChessBoardSize + 1, -1, 4);
	this->board[1][ChessBoardSize].SetChessNode(1 * ChessBoardSize + ChessBoardSize, -1, 2);
	this->board[ChessBoardSize][ChessBoardSize].SetChessNode((ChessBoardSize)*ChessBoardSize + (ChessBoardSize), -1, 3);
}

Board::~Board() {
	for (int i = 0; i < this->ChessBoardSize; i++) {
		delete[]board[i];
	}
	delete[]board;
}

int Board::GetBoardSize() {
	return this->ChessBoardSize;
}
/*
	void AddStep(ChessNode c) {
		route.push(c);
	}
*/
bool Board::PlcaeNode(int p, int id) {
	int x = p / this->ChessBoardSize;
	int y = p % this->ChessBoardSize;
	if (y == 0) {
		x--;
		y = this->ChessBoardSize;
	}
	int status = 0;
	if (id == BLACK) {
		status = 11;
	}
	else if (id == WHITE)
	{
		status = 21;
	}
	else if (id == EMPTY) {// 恢复为空
		if (x == 1 && y == 1) {
			this->board[x][y].SetChessNode(x * ChessBoardSize + y, -1, 1);
		}
		else if (x == 1 && y == ChessBoardSize)
		{
			this->board[x][y].SetChessNode(x * ChessBoardSize + y, -1, 2);
		}
		else if (x == 1 && y != ChessBoardSize && y != 0)
		{
			this->board[x][y].SetChessNode(x * ChessBoardSize + y, -1, 6);
		}
		else if (x != 1 && x != ChessBoardSize && y == 1)
		{
			this->board[x][y].SetChessNode(x * ChessBoardSize + y, -1, 5);
		}
		else if (x != 1 && x != ChessBoardSize && y == ChessBoardSize)
		{
			this->board[x][y].SetChessNode(x * ChessBoardSize + y, -1, 7);
		}
		else if (x == ChessBoardSize && y == 1)
		{
			this->board[x][y].SetChessNode(x * ChessBoardSize + y, -1, 4);
		}
		else if (x == ChessBoardSize && y == ChessBoardSize)
		{
			this->board[x][y].SetChessNode(x * ChessBoardSize + y, -1, 3);
		}
		else if (x == ChessBoardSize && y != 1 && y != ChessBoardSize)
		{
			this->board[x][y].SetChessNode(x * ChessBoardSize + y, -1, 8);
		}
		else
		{
			this->board[x][y].SetChessNode(x * ChessBoardSize + y, -1, 9);
		}
		return true;
	}

	if (board[x][y].GetPlayerId() != -1)
		return false;
	if (x >= 1 && x <= this->ChessBoardSize + 1 && y >= 1 && y <= this->ChessBoardSize + 1) {
		this->board[x][y].SetChessNode(x * ChessBoardSize + y, id, status);
		//AddStep(board[x][y]);
		return true;
	}
	return false;
}

ChessNode Board::ShowNode(int x, int y) {
	if (x >= 1 && x <= this->ChessBoardSize && y >= 1 && y <= this->ChessBoardSize) {
		return this->board[x][y];
	}
	return this->board[0][0];
}
/*
ChessNode Board::ShowGoBackStep() {
	if (!this->route.empty()) {
		return this->route.top();
	}
}

void Board::GoBackStep() {
	if (!route.empty()) {
		ChessNode tmp = route.top();
		board[tmp.GetLocationX()][tmp.GetLocationY()].SetChessNode(tmp.GetLocationX(), tmp.GetLocationX(), -1);
		route.pop();
	}
}
*/
void Board::SubstitutePreFlag() {
	for (int i = 1; i <= this->ChessBoardSize; i++)
	{
		for (int j = 1; j <= this->ChessBoardSize; j++)
		{
			if (this->board[i][j].GetChessNodeStatus() == 11) {
				this->board[i][j].SetChessNodeStatus(10);
			}

			if (this->board[i][j].GetChessNodeStatus() == 21) {
				this->board[i][j].SetChessNodeStatus(20);
			}
		}
	}
}
void Board::DisplayBoard()
{
	for (int i = 0; i <= this->ChessBoardSize; i++)
	{
		for (int j = 0; j <= this->ChessBoardSize; j++)
		{
			if (i == 0 && j == 0)
			{
				printf("   ");
				continue;
			}

			if (i == 0 && j != 0)
			{
				printf("%c ", this->board[i][j].GetChessNodeStatus() + 16 + '0');
				if (j == this->ChessBoardSize) printf("\n");
				continue;
			}

			if (j == 0)
			{
				printf("%2d", this->board[i][j].GetChessNodeStatus());
				continue;
			}

			switch (this->board[i][j].GetChessNodeStatus() % 100)//%100为了适应将来有分值的情形
			{
			case 0:
				printf("*");
				break;
			case 1:
				printf("┏");
				break;

			case 2:
				printf("┓");
				break;

			case 3:
				printf("┛");
				break;

			case 4:
				printf("┗");
				break;

			case 5:
				printf("┠");
				break;

			case 6:
				printf("┯");
				break;

			case 7:
				printf("┨");
				break;

			case 8:
				printf("┷");
				break;

			case 9:
				printf("┼");
				break;

			case 10:
				printf("●");
				break;

			case 11:
				printf("▲");
				break;

			case 20:
				printf("◎");
				break;

			case 21:
				printf("△");
				break;
			}
			if (j == this->ChessBoardSize)
			{
				printf("\n");
			}
		}
	}
	SubstitutePreFlag();
}