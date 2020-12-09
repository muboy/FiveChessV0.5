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
		//printf("%d %c �����ǳ�������\n", x, y + '0' + 16);
		return true;
	}
	if (IsForbiddenDoubleFour(x, y)) {
		//printf("%d %c ������˫�Ľ���\n", x, y + '0' + 16);
		return true;
	}
	if (IsForbiddenDoubleThree(x, y)) {
		//printf("%d %c ������˫������\n", x, y + '0' + 16);
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


/* ���� */
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


/* ���� */
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
		case 1:             /* ˮƽ */
			i = y - 1;      /* ���� */
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

			i = y + 1; /* ���� */
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
		case 2:             /* ��ֱ */
			i = x + 1;      /* ���� */
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

			i = x + 1; /* ���� */
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
			i = x - 1;        /* ���� */
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

			i = x + 1; /* ���� */
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
			i = x - 1;        /* ���� */
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

			i = x + 1; /* ���� */
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


/* ���� */
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


/* ���� */
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
		case 1:   /* ˮƽ */
			NumLine = 1;
			i = y - 1;        /* ���� */
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

			i = y + 1; /* ���� */
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
		case 2:               /* ��ֱ */
			NumLine = 1;
			i = x - 1;        /* ���� */
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

			i = x + 1; /* ���� */
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
			i = x - 1;        /* ���� */
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

			i = x + 1; /* ���� */
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
			i = x - 1;        /* ���� */
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

			i = x + 1; /* ���� */
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


/* ���� */
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
		case 1:             /* ˮƽ */

			i = y - 1;      /* ���� */
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
			i = y + 1; /* ���� */
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
		case 2:             /* ��ֱ */
			i = x - 1;      /* ���� */
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

			i = x + 1; /* ���� */
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
			i = x - 1;        /* ���� */
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

			i = x + 1; /* ���� */
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
			i = x - 1;        /* ���� */
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

			i = x + 1; /* ���� */
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


/* �Ƿ���Ի�ʤ */
bool IsForbiddenPoint::IsWin(int x, int y)
{
	if (this->ChessBoard->ShowNode(x, y).GetPlayerId() != EMPTY)
	{
		return false;
	}

	SetFlagChessNode(x, y, BLACK);

	int i, j;

	/* ˮƽ */
	int NumLine = 1;
	i = y - 1; /* ���� */
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
	i = y + 1; /* ���� */
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

	/* ��ֱ */

	NumLine = 1;
	i = x - 1; /* ���� */
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
	i = y + 1; /* ���� */
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
	i = x - 1; /* ���� */
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

	i = x + 1; /* ���� */
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
	i = x - 1; /* ���� */
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

	i = x + 1; /* ���� */
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


/* ���� */
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
	case 1:               /* ���� */
		NumLine = 1;
		i = y - 1;        /* ���� */
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

		i = y + 1; /* ���� */
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
	case 2:               /* ��ֱ */
		NumLine = 1;
		i = x - 1;        /* ���� */
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

		i = x + 1; /* ���� */
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
	case 3:               /* б�� '\' */
		NumLine = 1;
		i = x - 1;        /* ���� */
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

		i = x + 1; /* ���� */
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
	case 4:               /* б�� '/' */
		NumLine = 1;
		i = x - 1;        /* ���� */
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

		i = x + 1; /* ���� */
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


/* �������� */
bool IsForbiddenPoint::IsForbiddenLongLink(int x, int y)
{
	if (this->ChessBoard->ShowNode(x, y).GetPlayerId() != EMPTY)
		return false;

	SetFlagChessNode(x, y, BLACK);

	int	i, j;
	bool LongLink = false;

	/* ˮƽ */
	int NumLine = 1;
	i = y - 1; /* ���� */
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
	i = y + 1; /* ���� */
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

	/* ��ֱ */
	NumLine = 1;
	i = x - 1; /* ���� */
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
	i = x + 1; /* ���� */
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
	i = x - 1; /* ���� */
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
	i = x + 1; /* ���� */
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
	i = x - 1; /* ���� */
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
	i = x + 1; /* ���� */
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