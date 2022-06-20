#include "Player.h"

using namespace std;

int main()
{
	Player player;
	bool isRunning = true;

	while (isRunning)		// checking if game is over
	{
		isRunning = player.move();
	}
	player.getAnnounce();	// if game is over, each player get announcement

	cout << endl << "Thank you for playing!" << endl;
	system("pause");

	return 0;
}