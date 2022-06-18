#include "PlayerData.h"

using namespace std;

void PlayerData::setName(char* temp)
{
	strcpy_s(name, temp);
}

char* PlayerData::getName()
{
	char temp[MAX];
	strcpy_s(temp, name);
	
	return temp;
}

void PlayerData::setMark(char mark)
{
	this->mark = mark;
}

char PlayerData::getMark()
{
	return mark;
}
