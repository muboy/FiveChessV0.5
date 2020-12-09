#include "Player.h"

Player::Player(int PlayerId, Board* ChessBoard) : IsForbiddenPoint(ChessBoard) {
	this->PlayerId = PlayerId;
	this->ChessBoard = ChessBoard;
	this->ChessBoardSize = this->ChessBoard->GetBoardSize();
}

int Player::DoNext() {
	if (this->PlayerId == BLACK) {// 值黑棋 有禁手
		int x, y;//行列
		char tmp;
		while (true) {
			printf("请输入你落子的坐标(例如: 5 f): ");
			std::cin >> x >> tmp;
			y = toupper(tmp) - '0' - 16;
			if (x > 0 && x <= ChessBoardSize && y > 0 && y <= ChessBoardSize \
				&& this->ChessBoard->ShowNode(x, y).GetPlayerId() == EMPTY) {

				if (this->CheckPoint(x, y)) {
					printf("%d %c 这里是禁手点\n", x, y + '0' + 16);
					continue;
				}
				return XY2P(x, y, ChessBoardSize);
			}
			else
			{
				printf("输入有误！ ");
			}
		}
	}
	else if (this->PlayerId == WHITE) //值白棋 无禁手
	{
		int x, y;//行列
		char tmp;
		while (true) {
			printf("请输入你落子的坐标(例如: 5 f): ");
			std::cin >> x >> tmp;
			y = toupper(tmp) - '0' - 16;
			if (x > 0 && x <= ChessBoardSize && y > 0 && y <= ChessBoardSize \
				&& this->ChessBoard->ShowNode(x, y).GetPlayerId() == EMPTY) {

				return XY2P(x, y, ChessBoardSize);
			}
			else
			{
				printf("输入有误！ ");
			}
		}
	}

}
/* 悔棋
int Player::GoBackStep() {
	return 0;
}
*/
