#include "ChessNode.h"

ChessNode::ChessNode() {
	this->location = 0;
	this->playerid = -1;
	this->status = 0;
}

ChessNode::ChessNode(int x) {
	this->location = 0;
	this->playerid = -1;
	this->status = 0;
	this->Name = x;//如果是象棋，棋子名字不同
}
void ChessNode::SetChessNodeStatus(int status) {
	this->status = status;
}

void ChessNode::SetLocatoin(int p) {
	this->location = p;
}

void ChessNode::SetPlayerId(int id) {
	this->playerid = id;
}

void ChessNode::SetChessNode(int p, int id, int status) {
	this->location = p;
	this->playerid = id;
	this->status = status;
}

int ChessNode::GetLocation() {
	return this->location;
}

int ChessNode::GetPlayerId() {
	//int pid = this->playerid;
	return this->playerid;
}

int ChessNode::GetChessNodeStatus() {
	return this->status;
}
