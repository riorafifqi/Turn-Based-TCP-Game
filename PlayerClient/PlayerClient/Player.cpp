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

    recvBoard();
    board.Display();
}

char* Player::receiveData()
{
    char buf[MAX];

    recv(server, buf, MAX, 0);

    return buf;
}

void Player::sendData(char* buf)
{
    send(server, buf, MAX, 0);

}

bool Player::move()
{
    int moveBufX = 0, moveBufY = 0;
    int turnBuf;

    recv(server, (char*)&turnBuf, sizeof(turnBuf), 0);
    if (turnBuf == 2)
    {
        return false;
    }
    else if (turnBuf == 1)
    {
        while(true) {
            cout << "Your turn" << endl;

            cout << "X : ";
            cin >> moveBufX;

            cout << "Y : ";
            cin >> moveBufY;

            if (board.isValid(moveBufX, moveBufY) == true)
            {
                break;
            }
            else if (board.isValid(moveBufX, moveBufY) == false){
                cout << "Move is illegal" << endl;
            }
        }

        send(server, (const char*)&moveBufX, sizeof(moveBufX), 0);
        send(server, (const char*)&moveBufY, sizeof(moveBufY), 0);

    }
    else if (turnBuf == 0)
    {
        cout << "Waiting for opponent's turn " << endl;
    }

    else
    {
        cout << "Server is down" << endl;
        closeSocket();
        return false;
    }

    recvBoard();
    board.Display();

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

    char bufAnnounce[MAX];
    memset(bufAnnounce, 0, MAX);
    recv(server, bufAnnounce, MAX, 0);
    cout << bufAnnounce << endl;
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
            char bufMark[MAX];
            recv(server, bufMark, MAX, 0);
            board.setMark(*bufMark, i, j);
        }
    }
}
