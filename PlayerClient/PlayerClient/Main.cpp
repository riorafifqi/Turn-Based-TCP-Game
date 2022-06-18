#include "Player.h"

using namespace std;

int main()
{
	Player player;
	bool isRunning = true;

	while (isRunning)
	{
		isRunning = player.move();
	}
	player.getAnnounce();

	cout << endl << "Thank you for playing!" << endl;
	system("pause");

	return 0;
}