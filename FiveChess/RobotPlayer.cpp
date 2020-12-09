#include "RobotPlayer.h"
#include<vector>
RobotPlayer::RobotPlayer(Board* ChessBoard, int PlayerId, int NumNodeInLine) : IsForbiddenPoint(ChessBoard) {
	this->ChessBoard = ChessBoard;
	this->PlayerId = PlayerId;
	this->NumNodeInLine = NumNodeInLine;
	this->ChessBoardSize = ChessBoard->GetBoardSize();
	this->count = this->ChessBoardSize * (this->ChessBoardSize - this->NumNodeInLine + 1) * 2 + \
		(this->ChessBoardSize - this->NumNodeInLine + 1) * (this->ChessBoardSize - this->NumNodeInLine + 1) * 2;
	int num = 0;
	this->wins = new bool** [this->ChessBoardSize];
	for (int i = 0; i < ChessBoardSize; i++) {
		this->wins[i] = new bool* [this->ChessBoardSize];
		for (int j = 0; j < ChessBoardSize; j++) {
			this->wins[i][j] = new bool[count];
		}
	}

	//初始化可以赢的所有位置
	//横着五连子 可以赢的所有位置
	for (int i = 0; i < this->ChessBoardSize; i++) {
		for (int j = 0; j < this->ChessBoardSize - this->NumNodeInLine + 1; j++) {
			for (int k = 0; k < this->NumNodeInLine; k++) {
				this->wins[i][j + k][num] = true;
			}
			num++;
		}
	}
	//竖着五连子 可以赢的所有位置
	for (int i = 0; i < this->ChessBoardSize; i++) {
		for (int j = 0; j < this->ChessBoardSize - this->NumNodeInLine + 1; j++) {
			for (int k = 0; k < this->NumNodeInLine; k++) {
				this->wins[j + k][i][num] = true;
			}
			num++;
		}
	}

	//斜着 \ 可以赢的所有位置
	for (int i = 0; i < this->ChessBoardSize - this->NumNodeInLine + 1; i++) {
		for (int j = 0; j < this->ChessBoardSize - this->NumNodeInLine + 1; j++) {
			for (int k = 0; k < this->NumNodeInLine; k++) {
				this->wins[i + k][j + k][num] = true;
			}
			num++;
		}
	}
	// 斜着 / 可以赢的所有位置
	for (int i = 0; i < ChessBoardSize - this->NumNodeInLine + 1; i++) {
		for (int j = ChessBoardSize - 1; j > this->NumNodeInLine - 2; j--) {
			for (int k = 0; k < this->NumNodeInLine; k++) {
				this->wins[i + k][j - k][num] = true;
			}
			num++;
		}
	}
	//printf("count=%d\n", count);
	this->BlackWin = new int[count];
	this->WhiteWin = new int[count];
	for (int i = 0; i < count; i++) {
		this->BlackWin[i] = 0;
		this->WhiteWin[i] = 0;
	}

}

RobotPlayer::~RobotPlayer()
{
	delete[]BlackWin;
	delete[]WhiteWin;
	for (int i = 0; i < ChessBoardSize; i++) {
		for (int j = 0; j < ChessBoardSize; j++) {
			delete[]wins[i][j];
		}
		delete[]wins[i];
	}
	delete[]wins;
}

int RobotPlayer::ComputeAI(int p) {
	int m = p / this->ChessBoardSize;
	int n = p % this->ChessBoardSize;
	if (n == 0) {
		m--;
		n = this->ChessBoardSize;
	}

	int** BlackScore = new int* [ChessBoardSize];
	int** WhiteScore = new int* [ChessBoardSize];
	int max = 0;  // 保存棋盘点上的最高的分数
	int x = 0, y = 0;   // 保存最高分数所在的点

	//记录此次所有最高分的打分点
	// max x y
	std::vector<std::vector<int>> MaxPointArray;
	MaxPointArray.push_back({ -1, -1, -1 });

	for (int i = 0; i < ChessBoardSize; i++) {
		BlackScore[i] = new int[ChessBoardSize];
		WhiteScore[i] = new int[ChessBoardSize];
		for (int j = 0; j < ChessBoardSize; j++) {
			BlackScore[i][j] = 0;
			WhiteScore[i][j] = 0;
		}
	}

	for (int k = 0; k < count; k++) {
		if (wins[m - 1][n - 1][k] == true) {
			BlackWin[k]++;
			WhiteWin[k] = 100;
		}
	}

	for (int i = 0; i < ChessBoardSize; i++) {
		for (int j = 0; j < ChessBoardSize; j++) {
			if (this->ChessBoard->ShowNode(i + 1, j + 1).GetPlayerId() == EMPTY) {
				for (int k = 0; k < count; k++) {
					if (wins[i][j][k] == true) {
						if (BlackWin[k] == 1) {
							BlackScore[i][j] += 200;
						}
						else if (BlackWin[k] == 2) {
							BlackScore[i][j] += 400;
						}
						else if (BlackWin[k] == 3) {
							BlackScore[i][j] += 2000;
						}
						else if (BlackWin[k] == 4) {
							BlackScore[i][j] += 10000;
						}

						if (WhiteWin[k] == 1) {
							WhiteScore[i][j] += 220;
						}
						else if (WhiteWin[k] == 2) {
							WhiteScore[i][j] += 420;
						}
						else if (WhiteWin[k] == 3) {
							WhiteScore[i][j] += 2100;
						}
						else if (WhiteWin[k] == 4) {
							WhiteScore[i][j] += 20000;
						}
					}
				}

				if (this->PlayerId == BLACK && this->CheckPoint(x + 1, y + 1)) {//如果是黑棋的禁手点 必须低分
					BlackScore[i][j] = -1;
				}
				//else if(this->PlayerId == WHITE && this->CheckPoint(x + 1, y + 1))//如果是白棋的禁手点 必须高分
				//{
				//	WhiteScore[i][j] += 20000
				//}

				if (BlackScore[i][j] > max) {
					max = BlackScore[i][j];
					x = i;
					y = j;
				}
				else if (BlackScore[i][j] == max) {
					if (WhiteScore[i][j] > WhiteScore[x][y]) {
						x = i;
						y = j;
					}
				}
				if (WhiteScore[i][j] > max) {
					max = WhiteScore[i][j];
					x = i;
					y = j;
				}
				else if (WhiteScore[i][j] == max) {
					if (BlackScore[i][j] > BlackScore[x][y]) {
						x = i;
						y = j;
					}

				}
			}

			// 从MaxList中以max为键排序，取最大max 的三元组，如果 三元组不唯一 说明这些位置的评分一样，则随机选取一个作为落子点
			// 1 A 说明, 遍历完棋盘后发现所有位置评分都一样低， 此时随机一个位置返回 再有一个函数来判断该位置是否已经有子

			//将 max x y 三元组 收集起来存入一个表（MaxList）中
			if (max > MaxPointArray[0][0]) {
				MaxPointArray.clear();
				MaxPointArray.push_back({ max,x,y });
			}
			else if (max == MaxPointArray[0][0] && \
				(x != MaxPointArray[MaxPointArray.size() - 1][1] || y != MaxPointArray[MaxPointArray.size() - 1][2])) {
				MaxPointArray.push_back({ max,x,y });
			}
		}
	}
	if (max == 0) {//没找到合适的打分点
		for (int i = 0; i < this->ChessBoardSize; i++) {
			for (int j = 0; j < this->ChessBoardSize; j++) {
				if (this->ChessBoard->ShowNode(i + 1, j + 1).GetPlayerId() == EMPTY) {
					x = i;
					y = j;
					max = 200;
					break;
				}
			}
		}
		if (max == 0) {
			//棋盘满了
			return -1;
		}
	}
	if (MaxPointArray.size() >= 1) {
		srand((unsigned)time(NULL));
		int RandomPoint = rand() % MaxPointArray.size();
		x = MaxPointArray[RandomPoint][1];
		y = MaxPointArray[RandomPoint][2];
	}

	//for (int i = 0; i < MaxPointArray.size(); i++) {
	//	printf("\n%d %d %d  ", MaxPointArray[i][0], MaxPointArray[i][1], MaxPointArray[i][2]);
	//}


	//释放计分数组
	for (int i = 0; i < this->ChessBoardSize; i++) {
		delete[]BlackScore[i];
		delete[]WhiteScore[i];
	}
	delete[]BlackScore;
	delete[]WhiteScore;


	//this->ChessBoard->PlcaeNode(XY2P(x + 1, y + 1, this->ChessBoardSize), this->PlayerId);
	for (int k = 0; k < count; k++) {
		if (wins[x][y][k] == true) {
			WhiteWin[k]++;
			BlackWin[k] = 100;
		}
	}
	printf("id=%d x=%d y=%c max=%d\n", this->PlayerId, x + 1, y + 1 + 16 + '0', max);
	return (x + 1) * ChessBoardSize + y + 1;
}