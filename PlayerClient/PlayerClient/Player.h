#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <WS2tcpip.h>
#include "Board.h"

#pragma comment(lib, "Ws2_32.lib")
#define MAX 4096
#define PORT 8080

class Player
{
	SOCKET server;
	Board board;
public:
	Player();
	char* receiveData();
	void sendData(char*);
	bool move();
	void connectToServer();
	void getAnnounce();
	void closeSocket();

	void recvBoard();
};

