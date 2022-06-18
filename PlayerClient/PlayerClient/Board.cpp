#include "Board.h"
#include <iostream>

using namespace std;



Board::Board()
{
	//reset();
}

void Board::setMark(char mark, int x, int y)
{
	board[x][y] = mark;
}

char Board::getMark(int x, int y)
{
	return board[x][y];
}

bool Board::isValid(int x, int y)
{
	if (board[x][y] == ' ')
	{
		return true;
	}
	else
		return false;
}

void Board::Display()
{
	cout << endl << "      (0)  (1)  (2)  ";
	cout << endl << "(0) || " << getMark(0, 0) << " |" << "| " << getMark(0, 1) << " |" << "| " << getMark(0, 2) << " ||";
	cout << endl << "(1) || " << getMark(1, 0) << " |" << "| " << getMark(1, 1) << " |" << "| " << getMark(1, 2) << " ||";
	cout << endl << "(2) || " << getMark(2, 0) << " |" << "| " << getMark(2, 1) << " |" << "| " << getMark(2, 2) << " ||";
	cout << endl;
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
