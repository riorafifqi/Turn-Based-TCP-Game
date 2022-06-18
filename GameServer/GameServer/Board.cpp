#include "Board.h"

Board::Board()
{
	reset();
}

void Board::setMark(char mark, int x, int y)
{
	board[x][y] = mark;
}

char Board::getMark(int x, int y)
{
	return board[x][y];
}

void Board::reset()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j] = ' ';
		}
	}
}

bool Board::getHorizontal()
{
	bool retVal = false;
	for (int i = 0; i < 3; i++)
	{
		if (getMark(i, 0) == getMark(i, 1) && getMark(i, 0) == getMark(i, 2))
		{
			char temp = getMark(i, 0);
			if (temp != ' ')
			{
				retVal = true;
			}
		}
	}

	return retVal;
}

bool Board::getVertical()
{
	bool retVal = false;
	for (int i = 0; i < 3; i++)
	{
		if (getMark(1, i) == getMark(2, i) && getMark(0, i) == getMark(2, i))
		{
			char temp = getMark(1, i);
			if (temp != ' ')
			{
				retVal = true;
			}
		}
	}

	return retVal;
}

bool Board::getDiagonal()
{
	bool retVal = false;
	if (getMark(0, 0) == getMark(1, 1) && getMark(0, 0) == getMark(2, 2))
	{
		char temp = getMark(0, 0);
		if (temp != ' ')
		{
			retVal = true;
		}
	}

	if (getMark(0, 2) == getMark(1, 1) && getMark(0, 2) == getMark(2, 0))
	{
		char temp = getMark(0, 2);
		if (temp != ' ')
		{
			retVal = true;
		}
	}

	return retVal;
}

bool Board::isFull()
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == ' ')
			{
				count++;
			}
		}
	}

	if (count >= 1)
		return false;
	else
		return true;
}
