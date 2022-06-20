#include "GameManager.h"

int main()
{
	GameManager server;
	bool isRunning = true;

	while (isRunning)	// check if game is over
	{
		isRunning = server.move();
	}
	server.announceResult();	// when game is over, send message to each player

	system("pause");	// to prevent program auto close after exit
	return 0;
}