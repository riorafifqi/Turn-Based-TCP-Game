#pragma once
class Board
{
	char board[3][3];

public:
	Board();
	void setMark(char, int, int);
	char getMark(int, int);
	void reset();

	bool getHorizontal();
	bool getVertical();
	bool getDiagonal();

	bool isFull();
};

