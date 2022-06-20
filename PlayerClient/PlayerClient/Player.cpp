#include "Player.h"

using namespace std;
Player::Player()
{
    connectToServer();
    char bufName[MAX];
    memset(bufName, 0, MAX);
    // player receive "Enter your name" from server
    recv(server, bufName, MAX, 0);
    
    // print "Enter your name"
    cout << bufName << endl;

    // Input name and send it to server
    memset(bufName, 0, MAX);
    cin >> bufName;
    send(server, bufName, 4096, 0);

    recvBoard();        // receive empty board from server
    board.Display();    // display board
}

bool Player::move()
{
    int moveBufX = 0, moveBufY = 0;
    int turnBuf;

    recv(server, (char*)&turnBuf, sizeof(turnBuf), 0);      // receive sign for player's act
    if (turnBuf == 2)       // sign for player when game is ended and ready to receive annnouncement
    {
        return false;
    }
    else if (turnBuf == 1)  // sign for player to move
    {
        while(true) {
            cout << "Your turn" << endl;

            cout << "X : ";
            cin >> moveBufX;    // asking for 'X' coordinate

            cout << "Y : ";
            cin >> moveBufY;    // asking for 'Y' coordinate

            if (board.isValid(moveBufX, moveBufY))
            {
                break;  // if coordinate is valid, break out of while loop
            }
            else if (!board.isValid(moveBufX, moveBufY)){
                cout << "Move is illegal" << endl;  // else, send message and loop back to input 'X' and 'Y' coordinate again
            }
        }

        // send 'X' and 'Y' coordinate to server
        send(server, (const char*)&moveBufX, sizeof(moveBufX), 0);
        send(server, (const char*)&moveBufY, sizeof(moveBufY), 0);

    }
    else if (turnBuf == 0)
    {
        cout << "Waiting for opponent's turn " << endl;     // other player is waiting for turn
    }

    else // if player doesn't recv aign for server
    {
        cout << "Server is down" << endl;   
        closeSocket();
        return false;
    }

    recvBoard();    // receive board broadcasted by server
    board.Display();    // display board

    return true;
}

void Player::connectToServer()
{
    struct sockaddr_in servaddr;

    // Initialize winsock
    static WSADATA wsaData;
    int wsatest = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsatest)
        exit(1);

    // Socket create and verification
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    memset(&servaddr, 0, sizeof(servaddr));

    // Assign structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    // Connect to server socket
    if (connect(server, (sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
}

void Player::getAnnounce()
{
    cout << "Game has ended" << endl;

    char bufAnnounce[MAX];      // preparing buffer for anouncement message
    memset(bufAnnounce, 0, MAX);
    recv(server, bufAnnounce, MAX, 0);      // receive announcement message from server
    cout << bufAnnounce << endl;    // print announcement message
}

void Player::closeSocket()
{
    // Close the socket
    closesocket(server);

    // Close Winsock
    WSACleanup();
}

void Player::recvBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // receive mark in each row and column from server and assign it to local board one by one
            char bufMark[MAX];
            recv(server, bufMark, MAX, 0);
            board.setMark(*bufMark, i, j);
        }
    }
}
