#include"Game.h"
//#include "IsForbiddenPoint.h"
int main(void) {

	Game game(15,5);//自定义棋盘大小（10-26 字母有限），多少连子为胜
	game.run();
	system("pause");
	return 0;
}