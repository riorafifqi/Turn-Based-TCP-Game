#pragma once
#include <string>
#include <iostream>

#define MAX 4096


class PlayerData
{
	char name[MAX];
	char mark;
public:
	void setName(char*);
	char* getName();
	void setMark(char);
	char getMark();
};

