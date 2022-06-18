#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <WS2tcpip.h>
#include "PlayerData.h"
#include "Board.h"

#pragma comment(lib, "Ws2_32.lib")
#define MAX 4096
#define MAXPLAYER 2
#define PORT 8080

class GameManager
{
	SOCKET server;
	SOCKET player[MAXPLAYER];
	SOCKET currentPlayer;
	SOCKET winningPlayer;

	PlayerData playersData[MAXPLAYER];
	PlayerData currentPlayerData;

	Board board;
	bool isWin = false;
	bool isDraw = false;
	bool isRunning;

public:
	GameManager();
	void createServerSocket();
	void closeServerSocket(SOCKET);

	void changeTurn();
	bool move();
	bool checkWin();
	void broadcastBoard();
	void announceResult();

};

