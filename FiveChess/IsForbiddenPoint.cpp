#include "IsForbiddenPoint.h"

IsForbiddenPoint::IsForbiddenPoint(Board* ChessBoard)
{
	this->ChessBoard = ChessBoard;
	this->ChessBoardSize = ChessBoard->GetBoardSize();
}


IsForbiddenPoint::~IsForbiddenPoint()
{

}

bool IsForbiddenPoint::CheckPoint(int x, int y)
{
	if (IsWin(x, y)) {
		return false;
	}
	if (IsForbiddenLongLink(x, y)) {
		//printf("%d %c 这里是长连禁手\n", x, y + '0' + 16);
		return true;
	}
	if (IsForbiddenDoubleFour(x, y)) {
		//printf("%d %c 这里是双四禁手\n", x, y + '0' + 16);
		return true;
	}
	if (IsForbiddenDoubleThree(x, y)) {
		//printf("%d %c 这里是双三禁手\n", x, y + '0' + 16);
		return true;
	}
	else {
		return false;
	}
}

void IsForbiddenPoint::SetFlagChessNode(int x, int y, int id)
{
	//int static xx = 0;
	this->ChessBoard->PlcaeNode(XY2P(x, y, ChessBoardSize), id);
	//if (id == BLACK) {
	//	xx++;
	//	//printf("%3d ",xx);
	//}
	//else if (id == EMPTY)
	//{
	//	xx--;
	//	//printf("%3d ", xx);
	//}
}


/* 禁三 */
bool IsForbiddenPoint::IsForbiddenDoubleThree(int x, int y)
{
	if (this->ChessBoard->ShowNode(x, y).GetPlayerId() != EMPTY)
		return false;
	if (IsWin(x, y))
	{
		return false;
	}

	int NumThree = 0;

	for (int i = 1; i <= 4; ++i)
	{
		if (IsDoubleThree(x, y, i))
			NumThree++;
	}

	if (NumThree >= 2)
	{
		return true;
	}
	else {
		return false;
	}
}


/* 活三 */
bool IsForbiddenPoint::IsDoubleThree(int x, int y, int dir)
{
	if (this->ChessBoard->ShowNode(x, y).GetPlayerId() != EMPTY)
		return false;
	if (IsWin(x, y))
		return false;
	else if (IsForbiddenLongLink(x, y))
		return false;
	else {
		int c = BLACK;

		SetFlagChessNode(x, y, c);

		int i, j;

		switch (dir)
		{
		case 1:             /* 水平 */
			i = y - 1;      /* 向左 */
			while (i > 0)
			{
				if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == c)
				{
					--i;
					continue;
				}
				else if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == EMPTY)
				{
					if ((IsDoubleFour(x, i, dir) == 1) && (!IsForbiddenDoubleFour(x, i)) && (!IsForbiddenDoubleThree(x, i)))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}

			i = y + 1; /* 向右 */
			while (i < (ChessBoardSize + 1))
			{
				if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == c)
				{
					++i;
					continue;
				}
				else if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == EMPTY)
				{
					if ((IsDoubleFour(x, i, dir) == 1) && (!IsForbiddenDoubleFour(x, i)) && (!IsForbiddenDoubleThree(x, i)))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}
			SetFlagChessNode(x, y, EMPTY);
			return false;
			break;
		case 2:             /* 竖直 */
			i = x + 1;      /* 向上 */
			while (i > 0)
			{
				if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == c)
				{
					--i;
					continue;
				}
				else if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == EMPTY)
				{
					if ((IsDoubleFour(i, y, dir) == 1) && (!IsForbiddenDoubleFour(i, y)) && (!IsForbiddenDoubleThree(i, y)))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}

			i = x + 1; /* 向下 */
			while (i < (ChessBoardSize + 1))
			{
				if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == c)
				{
					++i;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == EMPTY)
				{
					if ((IsDoubleFour(i, y, dir) == 1) && (!IsForbiddenDoubleFour(i, y)) && (!IsForbiddenDoubleThree(i, y)))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}
			SetFlagChessNode(x, y, EMPTY);
			return false;
			break;
		case 3:               /* '\' */
			i = x - 1;        /* 左上 */
			j = y - 1;
			while ((i > 0) && (j > 0))
			{
				if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
				{
					--i;
					--j;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == EMPTY)
				{
					if ((IsDoubleFour(i, j, dir) == 1) && (!IsForbiddenDoubleFour(i, j)) && (!IsForbiddenDoubleThree(i, j)))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}

			i = x + 1; /* 右下 */
			j = y + 1;
			while ((i < (ChessBoardSize + 1)) && (j < (ChessBoardSize + 1)))
			{
				if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
				{
					++i;
					++j;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == EMPTY)
				{
					if ((IsDoubleFour(i, j, dir) == 1) && (!IsForbiddenDoubleFour(i, j)) && (!IsForbiddenDoubleThree(i, j)))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}
			SetFlagChessNode(x, y, EMPTY);
			return false;
			break;
		case 4:               /* '/' */
			i = x - 1;        /* 右上 */
			j = y + 1;
			while ((i > 0) && (j < (ChessBoardSize + 1)))
			{
				if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
				{
					--i;
					++j;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == EMPTY)
				{
					if ((IsDoubleFour(i, j, dir) == 1) && (!IsForbiddenDoubleFour(i, j)) && (!IsForbiddenDoubleThree(i, j)))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}

			i = x + 1; /* 左下 */
			j = y - 1;
			while ((i < (ChessBoardSize + 1)) && (j > 0))
			{
				if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
				{
					++i;
					--j;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == EMPTY)
				{
					if ((IsDoubleFour(i, j, dir) == 1) && (!IsForbiddenDoubleFour(i, j)) && (!IsForbiddenDoubleThree(i, j)))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}
			SetFlagChessNode(x, y, EMPTY);
			return false;
			break;
		default:
			SetFlagChessNode(x, y, EMPTY);
			return false;
			break;
		}
	}
}


/* 禁四 */
bool IsForbiddenPoint::IsForbiddenDoubleFour(int x, int y)
{
	if (this->ChessBoard->ShowNode(x, y).GetPlayerId() != EMPTY)
		return false;
	if (IsFive(x, y, BLACK))
		return false;
	int NumFour = 0;

	for (int i = 1; i <= 4; ++i)
	{
		if (IsDoubleFour(x, y, i) == 2)
			NumFour += 2;
		else if (IsFour(x, y, i))
			NumFour++;
	}

	if (NumFour >= 2)
		return true;
	else
		return false;
}


/* 活四 */
int IsForbiddenPoint::IsDoubleFour(int x, int y, int dir)
{
	if (this->ChessBoard->ShowNode(x, y).GetPlayerId() != EMPTY)
		return 0;

	if (IsWin(x, y))
		return 0;
	else if (IsForbiddenLongLink(x, y))
		return 0;
	else {
		int c = BLACK;

		SetFlagChessNode(x, y, c);

		int	i, j;
		int	NumLine;

		switch (dir)
		{
		case 1:   /* 水平 */
			NumLine = 1;
			i = y - 1;        /* 向左 */
			while (i > 0)
			{
				if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == c)
				{
					--i;
					NumLine++;
					continue;
				}
				else if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == EMPTY)
				{
					if (!IsFive(x, i, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return 0;
					}
					else {
						break;
					}
				}
				else {
					SetFlagChessNode(x, y, EMPTY);
					return 0;
				}
			}

			i = y + 1; /* 向右 */
			while (i < (ChessBoardSize + 1))
			{
				if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == c)
				{
					++i;
					NumLine++;
					continue;
				}
				else if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == EMPTY)
				{
					if (IsFive(x, i, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return(NumLine == 4 ? 1 : 2);
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}
			SetFlagChessNode(x, y, EMPTY);
			return 0;
			break;
		case 2:               /* 竖直 */
			NumLine = 1;
			i = x - 1;        /* 向上 */
			while (i > 0)
			{
				if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == c)
				{
					--i;
					NumLine++;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == EMPTY)
				{
					if (!IsFive(i, y, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return 0;
					}
					else {
						break;
					}
				}
				else {
					SetFlagChessNode(x, y, EMPTY);
					return 0;
				}
			}

			i = x + 1; /* 向下 */
			while (i < (ChessBoardSize + 1))
			{
				if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == c)
				{
					++i;
					NumLine++;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == EMPTY)
				{
					if (IsFive(i, y, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return(NumLine == 4 ? 1 : 2);
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}
			SetFlagChessNode(x, y, EMPTY);
			return 0;
			break;
		case 3:                /* '\' */
			NumLine = 1;
			i = x - 1;        /* 左上 */
			j = y - 1;
			while ((i > 0) && (j > 0))
			{
				if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
				{
					--i;
					--j;
					NumLine++;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == EMPTY)
				{
					if (!IsFive(i, j, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return 0;
					}
					else {
						break;
					}
				}
				else {
					SetFlagChessNode(x, y, EMPTY);
					return 0;
				}
			}

			i = x + 1; /* 右下 */
			j = y + 1;
			while ((i < (ChessBoardSize + 1)) && (j < (ChessBoardSize + 1)))
			{
				if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
				{
					++i;
					++j;
					NumLine++;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == EMPTY)
				{
					if (IsFive(i, j, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return(NumLine == 4 ? 1 : 2);
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}
			SetFlagChessNode(x, y, EMPTY);
			return 0;
			break;
		case 4:               /* '/' */
			NumLine = 1;
			i = x - 1;        /* 右上 */
			j = y + 1;
			while ((i > 0) && (j < (ChessBoardSize + 1)))
			{
				if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
				{
					--i;
					++j;
					NumLine++;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == EMPTY)
				{
					if (!IsFive(i, j, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return 0;
					}
					else {
						break;
					}
				}
				else {
					SetFlagChessNode(x, y, EMPTY);
					return 0;
				}
			}

			i = x + 1; /* 左下 */
			j = y - 1;
			while ((i < (ChessBoardSize + 1)) && (j > 0))
			{
				if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
				{
					++i;
					--j;
					NumLine++;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == EMPTY)
				{
					if (IsFive(i, j, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return(NumLine == 4 ? 1 : 2);
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}
			SetFlagChessNode(x, y, EMPTY);
			return 0;
			break;
		default:
			SetFlagChessNode(x, y, EMPTY);
			return 0;
			break;
		}
	}
}


/* 四连 */
bool IsForbiddenPoint::IsFour(int const x, int const y, int dir)
{
	if (this->ChessBoard->ShowNode(x, y).GetPlayerId() != EMPTY)
		return false;

	if (IsWin(x, y))
		return false;
	else if (IsForbiddenLongLink(x, y))
		return false;
	else {
		int c = BLACK;
		SetFlagChessNode(x, y, c);

		int i, j;
		switch (dir)
		{
		case 1:             /* 水平 */

			i = y - 1;      /* 向左 */
			while (i > 0)
			{
				if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == c)
				{
					--i;
					continue;
				}
				else if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == EMPTY)
				{
					if (IsFive(x, i, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}
			i = y + 1; /* 向右 */
			while (i < (ChessBoardSize + 1))
			{
				if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == c)
				{
					++i;
					continue;
				}
				else if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == EMPTY)
				{
					if (IsFive(x, i, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}

			SetFlagChessNode(x, y, EMPTY);
			return false;
			break;
		case 2:             /* 竖直 */
			i = x - 1;      /* 向上 */
			while (i > 0)
			{
				if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == c)
				{
					--i;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == EMPTY)
				{
					if (IsFive(i, y, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}

			i = x + 1; /* 向下 */
			while (i < (ChessBoardSize + 1))
			{
				if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == c)
				{
					++i;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == EMPTY)
				{
					if (IsFive(i, y, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}
			SetFlagChessNode(x, y, EMPTY);
			return false;
			break;
		case 3:               /* '\' */
			i = x - 1;        /* 左上 */
			j = y - 1;
			while ((i > 0) && (j > 0))
			{
				if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
				{
					--i;
					--j;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == EMPTY)
				{
					if (IsFive(i, j, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}

			i = x + 1; /* 右下 */
			j = y + 1;
			while ((i < (ChessBoardSize + 1)) && (j < (ChessBoardSize + 1)))
			{
				if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
				{
					++i;
					++j;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == EMPTY)
				{
					if (IsFive(i, j, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}
			SetFlagChessNode(x, y, EMPTY);
			return false;
			break;
		case 4:               /* '/' */
			i = x - 1;        /* 右上 */
			j = y + 1;
			while ((i > 0) && (j < (ChessBoardSize + 1)))
			{
				if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
				{
					--i;
					++j;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == EMPTY)
				{
					if (IsFive(i, j, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}

			i = x + 1; /* 左下 */
			j = y - 1;
			while ((i < (ChessBoardSize + 1)) && (j > 0))
			{
				if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
				{
					++i;
					--j;
					continue;
				}
				else if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == EMPTY)
				{
					if (IsFive(i, j, dir))
					{
						SetFlagChessNode(x, y, EMPTY);
						return true;
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}
			SetFlagChessNode(x, y, EMPTY);
			return false;
			break;
		default:
			SetFlagChessNode(x, y, EMPTY);
			return false;
			break;
		}
	}
}


/* 是否可以获胜 */
bool IsForbiddenPoint::IsWin(int x, int y)
{
	if (this->ChessBoard->ShowNode(x, y).GetPlayerId() != EMPTY)
	{
		return false;
	}

	SetFlagChessNode(x, y, BLACK);

	int i, j;

	/* 水平 */
	int NumLine = 1;
	i = y - 1; /* 向左 */
	while (i > 0)
	{
		if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == BLACK)
		{
			--i;
			NumLine++;
		}
		else {
			break;
		}
	}
	i = y + 1; /* 向右 */
	while (i < (ChessBoardSize + 1))
	{
		if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == BLACK)
		{
			++i;
			NumLine++;
		}
		else {
			break;
		}
	}
	if (NumLine == 5)
	{
		SetFlagChessNode(x, y, EMPTY);
		return true;
	}

	/* 竖直 */

	NumLine = 1;
	i = x - 1; /* 向上 */
	while (i > 0)
	{
		if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == BLACK)
		{
			--i;
			NumLine++;
		}
		else {
			break;
		}
	}
	i = y + 1; /* 向下 */
	while (i < (ChessBoardSize + 1))
	{
		if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == BLACK)
		{
			i++;
			NumLine++;
		}
		else {
			break;
		}
	}
	if (NumLine == 5)
	{
		SetFlagChessNode(x, y, EMPTY);
		return true;
	}

	/* '\' */
	NumLine = 1;
	i = x - 1; /* 左上 */
	j = y - 1;
	while ((i > 0) && (j > 0))
	{
		if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == BLACK)
		{
			i--;
			j--;
			NumLine++;
		}
		else {
			break;
		}
	}

	i = x + 1; /* 右下 */
	j = y + 1;
	while ((i < (ChessBoardSize + 1)) && (j < (ChessBoardSize + 1)))
	{
		if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == BLACK)
		{
			i++;
			j++;
			NumLine++;
		}
		else {
			break;
		}
	}
	if (NumLine == 5)
	{
		SetFlagChessNode(x, y, EMPTY);
		return true;
	}

	/* '/' */
	NumLine = 1;
	i = x - 1; /* 右上 */
	j = y + 1;
	while ((i > 0) && (j < (ChessBoardSize + 1)))
	{
		if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == BLACK)
		{
			i--;
			j++;
			NumLine++;
		}
		else {
			break;
		}
	}

	i = x + 1; /* 左下 */
	j = y - 1;
	while ((i < (ChessBoardSize + 1)) && (j > 0))
	{
		if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == BLACK)
		{
			i++;
			j--;
			NumLine++;
		}
		else {
			break;
		}
	}
	if (NumLine == 5)
	{
		SetFlagChessNode(x, y, EMPTY);
		return true;
	}

	SetFlagChessNode(x, y, EMPTY);
	return false;
}


/* 五连 */
bool IsForbiddenPoint::IsFive(int x, int y, int dir)
{
	if (this->ChessBoard->ShowNode(x, y).GetPlayerId() != EMPTY)
		return false;

	int c = BLACK;

	SetFlagChessNode(x, y, c);

	int	i, j;
	int	NumLine;

	switch (dir)
	{
	case 1:               /* 横向 */
		NumLine = 1;
		i = y - 1;        /* 向左 */
		while (i > 0)
		{
			if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == c)
			{
				i--;
				NumLine++;
			}
			else {
				break;
			}
		}

		i = y + 1; /* 向右 */
		while (i < (ChessBoardSize + 1))
		{
			if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == c)
			{
				i++;
				NumLine++;
			}
			else {
				break;
			}
		}
		if (NumLine == 5)
		{
			SetFlagChessNode(x, y, EMPTY);
			return true;
		}
		else {
			SetFlagChessNode(x, y, EMPTY);
			return false;
		}
		break;
	case 2:               /* 竖直 */
		NumLine = 1;
		i = x - 1;        /* 向上 */
		while (i > 0)
		{
			if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == c)
			{
				i--;
				NumLine++;
			}
			else {
				break;
			}
		}

		i = x + 1; /* 向下 */
		while (i < (ChessBoardSize + 1))
		{
			if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == c)
			{
				i++;
				NumLine++;
			}
			else {
				break;
			}
		}
		if (NumLine == 5)
		{
			SetFlagChessNode(x, y, EMPTY);
			return true;
		}
		else {
			SetFlagChessNode(x, y, EMPTY);
			return false;
		}
		break;
	case 3:               /* 斜向 '\' */
		NumLine = 1;
		i = x - 1;        /* 左上 */
		j = y - 1;
		while ((i > 0) && (j > 0))
		{
			if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
			{
				i--;
				j--;
				NumLine++;
			}
			else {
				break;
			}
		}

		i = x + 1; /* 右下 */
		j = y + 1;
		while ((i < (ChessBoardSize + 1)) && (j < (ChessBoardSize + 1)))
		{
			if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
			{
				i++;
				j++;
				NumLine++;
			}
			else {
				break;
			}
		}
		if (NumLine == 5)
		{
			SetFlagChessNode(x, y, EMPTY);
			return true;
		}
		else {
			SetFlagChessNode(x, y, EMPTY);
			return false;
		}
		break;
	case 4:               /* 斜向 '/' */
		NumLine = 1;
		i = x - 1;        /* 右上 */
		j = y + 1;
		while ((i > 0) && (j < (ChessBoardSize + 1)))
		{
			if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
			{
				i--;
				j++;
				NumLine++;
			}
			else {
				break;
			}
		}

		i = x + 1; /* 左下 */
		j = y - 1;
		while ((i < (ChessBoardSize + 1)) && (j > 0))
		{
			if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == c)
			{
				i++;
				j--;
				NumLine++;
			}
			else {
				break;
			}
		}
		if (NumLine == 5)
		{
			SetFlagChessNode(x, y, EMPTY);
			return true;
		}
		else {
			SetFlagChessNode(x, y, EMPTY);
			return false;
		}
		break;
	default:
		SetFlagChessNode(x, y, EMPTY);
		return false;
		break;
	}
}


/* 长连禁手 */
bool IsForbiddenPoint::IsForbiddenLongLink(int x, int y)
{
	if (this->ChessBoard->ShowNode(x, y).GetPlayerId() != EMPTY)
		return false;

	SetFlagChessNode(x, y, BLACK);

	int	i, j;
	bool LongLink = false;

	/* 水平 */
	int NumLine = 1;
	i = y - 1; /* 向左 */
	while (i > 0)
	{
		if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == BLACK)
		{
			i--;
			NumLine++;
		}
		else {
			break;
		}
	}
	i = y + 1; /* 向右 */
	while (i < (ChessBoardSize + 1))
	{
		if (this->ChessBoard->ShowNode(x, i).GetPlayerId() == BLACK)
		{
			i++;
			NumLine++;
		}
		else {
			break;
		}
	}
	if (NumLine == 5)
	{
		SetFlagChessNode(x, y, EMPTY);
		return false;
	}
	else
		LongLink |= (NumLine >= 6);

	/* 竖直 */
	NumLine = 1;
	i = x - 1; /* 向上 */
	while (i > 0)
	{
		if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == BLACK)
		{
			i--;
			NumLine++;
		}
		else {
			break;
		}
	}
	i = x + 1; /* 向下 */
	while (i < (ChessBoardSize + 1))
	{
		if (this->ChessBoard->ShowNode(i, y).GetPlayerId() == BLACK)
		{
			i++;
			NumLine++;
		}
		else {
			break;
		}
	}
	if (NumLine == 5)
	{
		SetFlagChessNode(x, y, EMPTY);
		return false;
	}
	else
		LongLink |= (NumLine >= 6);

	/* '\' */
	NumLine = 1;
	i = x - 1; /* 左上 */
	j = y - 1;
	while ((i > 0) && (j > 0))
	{
		if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == BLACK)
		{
			i--;
			j--;
			NumLine++;
		}
		else {
			break;
		}
	}
	i = x + 1; /* 右下 */
	j = y + 1;
	while ((i < (ChessBoardSize + 1)) && (j < (ChessBoardSize + 1)))
	{
		if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == BLACK)
		{
			i++;
			j++;
			NumLine++;
		}
		else {
			break;
		}
	}
	if (NumLine == 5)
	{
		SetFlagChessNode(x, y, EMPTY);
		return false;
	}
	else
		LongLink |= (NumLine >= 6);

	/* '/' */
	NumLine = 1;
	i = x - 1; /* 右上 */
	j = y + 1;
	while ((i > 0) && (j < (ChessBoardSize + 1)))
	{
		if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == BLACK)
		{
			i--;
			j++;
			NumLine++;
		}
		else {
			break;
		}
	}
	i = x + 1; /* 左下 */
	j = y - 1;
	while ((i < (ChessBoardSize + 1)) && (j > 0))
	{
		if (this->ChessBoard->ShowNode(i, j).GetPlayerId() == BLACK)
		{
			i++;
			j--;
			NumLine++;
		}
		else {
			break;
		}
	}
	if (NumLine == 5)
	{
		SetFlagChessNode(x, y, EMPTY);
		return false;
	}
	else
		LongLink |= (NumLine >= 6);

	SetFlagChessNode(x, y, EMPTY);
	return LongLink;
}