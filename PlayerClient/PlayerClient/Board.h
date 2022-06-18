#pragma once
class Board
{
	char board[3][3];

public:
	Board();
	void setMark(char, int, int);
	char getMark(int, int);
	bool isValid(int, int);
	void Display();
	void reset();
};

