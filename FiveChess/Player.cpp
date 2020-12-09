#include "Player.h"

Player::Player(int PlayerId, Board* ChessBoard) : IsForbiddenPoint(ChessBoard) {
	this->PlayerId = PlayerId;
	this->ChessBoard = ChessBoard;
	this->ChessBoardSize = this->ChessBoard->GetBoardSize();
}

int Player::DoNext() {
	if (this->PlayerId == BLACK) {// ֵ���� �н���
		int x, y;//����
		char tmp;
		while (true) {
			printf("�����������ӵ�����(����: 5 f): ");
			std::cin >> x >> tmp;
			y = toupper(tmp) - '0' - 16;
			if (x > 0 && x <= ChessBoardSize && y > 0 && y <= ChessBoardSize \
				&& this->ChessBoard->ShowNode(x, y).GetPlayerId() == EMPTY) {

				if (this->CheckPoint(x, y)) {
					printf("%d %c �����ǽ��ֵ�\n", x, y + '0' + 16);
					continue;
				}
				return XY2P(x, y, ChessBoardSize);
			}
			else
			{
				printf("�������� ");
			}
		}
	}
	else if (this->PlayerId == WHITE) //ֵ���� �޽���
	{
		int x, y;//����
		char tmp;
		while (true) {
			printf("�����������ӵ�����(����: 5 f): ");
			std::cin >> x >> tmp;
			y = toupper(tmp) - '0' - 16;
			if (x > 0 && x <= ChessBoardSize && y > 0 && y <= ChessBoardSize \
				&& this->ChessBoard->ShowNode(x, y).GetPlayerId() == EMPTY) {

				return XY2P(x, y, ChessBoardSize);
			}
			else
			{
				printf("�������� ");
			}
		}
	}

}
/* ����
int Player::GoBackStep() {
	return 0;
}
*/
