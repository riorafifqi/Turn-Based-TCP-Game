#include "GameManager.h"

int main()
{
	GameManager server;
	bool isRunning = true;

	while (isRunning)
	{
		isRunning = server.move();
	}
	server.announceResult();

	system("pause");	// to prevent program auto close after exit
	return 0;
}