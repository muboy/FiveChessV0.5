#include "Game.h"
#include"Board.h"
#include"Judge.h"
#include"RobotPlayer.h"
#include"Player.h"

Game::Game(int ChessBoardSize, int NumNodeInLine) {
	system("color F0");
	this->ChessBoardSize = ChessBoardSize;
	this->NumNodeInLine = NumNodeInLine;
	this->ChessBoard = new Board(ChessBoardSize);
	int x = this->ChessBoard->GetBoardSize();
	int select = 0;
	int ChessNodeColor = 0;

	while (true)
	{
		printf("��ӭ���������壡\n\n1 �˻���Ϸ  \n2 �������Լ���\n\n��ѡ��ģʽ(���� 1 ���� 2): ");
		std::cin >> select;
		if (select == 1) {// �˻�ģʽ �����ʼ��
			this->mode = 1;
			while (true)
			{
				printf("1 ֵ����\n2 ֵ����\n\n��ѡ��ģʽ(���� 1 ���� 2): ");
				std::cin >> ChessNodeColor;
				if (ChessNodeColor == 1) {
					this->BLACKorWHITE = 1;
					human = new Player(BLACK, ChessBoard);
					robot = new RobotPlayer(ChessBoard, WHITE, this->NumNodeInLine);
					judge = new Judge(ChessBoard, this->NumNodeInLine);
					break;
				}
				else if (ChessNodeColor == 2)
				{
					this->BLACKorWHITE = 2;
					human = new Player(WHITE, ChessBoard);
					robot = new RobotPlayer(ChessBoard, BLACK, this->NumNodeInLine);
					judge = new Judge(ChessBoard, this->NumNodeInLine);
					break;
				}
				else
				{
					printf("������������������: ");
				}

			}
		}
		else if (select == 2) {// �������Լ��� �����ʼ��
			this->mode = 2;
			robot = new RobotPlayer(ChessBoard, BLACK, this->NumNodeInLine);
			robot_2 = new RobotPlayer(ChessBoard, WHITE, this->NumNodeInLine);
			judge = new Judge(ChessBoard, this->NumNodeInLine);
			break;
		}
		if (select == 1 || select == 2) {
			break;
		}
		else
		{
			printf("������������������: ");
		}
	}
}

Game::~Game() {
	if (this->mode == 1) {
		delete human;
		delete robot;
		delete judge;
		delete ChessBoard;
	}
	else if (this->mode == 2)
	{
		delete robot;
		delete robot_2;
		delete judge;
		delete ChessBoard;
	}

}

void Game::run() {

	int HunmanStep, RobotStep;
	this->ChessBoard->DisplayBoard();
	if (this->mode == 1) { // �˻�ģʽ
		switch (this->BLACKorWHITE)
		{
		case 1:
			while (true)
			{
				system("cls");
				this->ChessBoard->DisplayBoard();

				HunmanStep = human->DoNext();
				this->ChessBoard->PlcaeNode(HunmanStep, BLACK);
				if (judge->SimpleScan(HunmanStep) == 1) {
					system("cls");
					std::cout << "You" << " Win!" << std::endl;
					this->ChessBoard->DisplayBoard();
					break;
				}
				if (judge->SimpleScan(HunmanStep) == -1) {
					printf("������\n");
					this->ChessBoard->DisplayBoard();
					break;
				}

				RobotStep = robot->ComputeAI(HunmanStep);
				this->ChessBoard->PlcaeNode(RobotStep, WHITE);
				if (judge->SimpleScan(RobotStep) == 1) {
					system("cls");
					std::cout << "Robot" << " Win!" << std::endl;
					this->ChessBoard->DisplayBoard();
					break;
				}
				if (judge->SimpleScan(RobotStep) == -1) {
					printf("������\n");
					this->ChessBoard->DisplayBoard();
					break;
				}
			}
			break;
		case 2:
			HunmanStep = XY2P(8, 8, 15);
			while (true)
			{
				system("cls");
				//this->ChessBoard->DisplayBoard();

				RobotStep = robot->ComputeAI(HunmanStep);
				this->ChessBoard->PlcaeNode(RobotStep, BLACK);
				this->ChessBoard->DisplayBoard();
				if (judge->SimpleScan(RobotStep) == 1) {
					system("cls");
					std::cout << "Robot" << " Win!" << std::endl;
					this->ChessBoard->DisplayBoard();
					break;
				}
				if (judge->SimpleScan(RobotStep) == -1) {
					printf("������\n");
					this->ChessBoard->DisplayBoard();
					break;
				}

				HunmanStep = human->DoNext();
				this->ChessBoard->PlcaeNode(HunmanStep, WHITE);
				if (judge->SimpleScan(HunmanStep) == 1) {
					system("cls");
					std::cout << "You" << " Win!" << std::endl;
					this->ChessBoard->DisplayBoard();
					break;
				}
				if (judge->SimpleScan(HunmanStep) == -1) {
					printf("������\n");
					this->ChessBoard->DisplayBoard();
					break;
				}
			}
			break;
		default:
			break;
		}

	}
	else { // �������Լ���
		srand((unsigned)time(NULL));
		int RandomStart = rand() % ((this->ChessBoardSize - 1) * (this->ChessBoardSize - 1)) + this->ChessBoardSize;
		int RobotStep1, RobotStep2;// Robot BLACK Robot_2 WHITE
		RobotStep2 = RandomStart;
		while (true)
		{
			system("cls");

			RobotStep1 = robot->ComputeAI(RobotStep2);
			this->ChessBoard->PlcaeNode(RobotStep1, BLACK);
			if (judge->SimpleScan(RobotStep1) == 1) {
				std::cout << "Robot 1 BLACK " << " Win!" << std::endl;
				this->ChessBoard->DisplayBoard();
				break;
			}
			if (judge->SimpleScan(RobotStep1) == -1) {
				printf("������\n");
				this->ChessBoard->DisplayBoard();
				break;
			}

			RobotStep2 = robot_2->ComputeAI(RobotStep1);
			this->ChessBoard->PlcaeNode(RobotStep2, WHITE);
			ChessBoard->PlcaeNode(RobotStep2, BLACK);
			if (judge->SimpleScan(RobotStep2) == 1) {
				std::cout << "Robot 2 WHITE " << " Win!" << std::endl;
				this->ChessBoard->DisplayBoard();
				break;
			}
			if (judge->SimpleScan(RobotStep2) == -1) {
				printf("������\n");
				this->ChessBoard->DisplayBoard();
				break;
			}

			this->ChessBoard->DisplayBoard();
			Sleep(50);
		}
	}

}
