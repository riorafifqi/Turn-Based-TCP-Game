#include "GameManager.h"

using namespace std;

GameManager::GameManager()
{
    createServerSocket();
    
    // TODO? Randomize first turn
    currentPlayer = player[0];
    currentPlayerData = playersData[0];
}

void GameManager::createServerSocket()
{
    sockaddr_in servaddr, cliaddr[2];

    // Initialize winsock
    static WSADATA wsaData;
    int wsatest = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsatest)
        exit(1);

    // Create socket
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == INVALID_SOCKET) {
        cout << "Socket creation failed" << endl;
        exit(0);
    }
    else
        cout << "Socket succesfully created" << endl;
    memset(&servaddr, 0, sizeof(servaddr));

    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.S_un.S_addr = INADDR_ANY;     // Assign to
    //all available interface, not just localhost
    servaddr.sin_port = htons(PORT);

    // Bind socket and check if socket succesfully binded
    if ((bind(server, (sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
        cout << "Socket binding failed" << endl;
        exit(0);
    }
    else
        cout << "Socket succesfully binded" << endl;

    // listen and check if server is ready for listening
    if ((listen(server, 2)) != 0) {
        cout << "Listening failed" << endl;
        exit(0);
    }
    else
        cout << "Server is listening" << endl;

    // Accept client socket
    for (int i = 0; i < 2; i++)
    {
        int lenClient = sizeof(cliaddr[i]);
        player[i] = accept(server, (sockaddr*)&cliaddr[i], &lenClient);
        if (player[i] == INVALID_SOCKET) {
            cout << "Server accept failed" << endl;
            exit(0);
        }
        else
        {
            // Ask name to player
            string askName = "Enter your name";
            char bufName[MAX];
            send(player[i], askName.c_str(), sizeof(askName), 0);
            
            // Receive name from player and save it to local data
            recv(player[i], bufName, MAX, 0);
            playersData[i].setName(bufName);
            
            // Set mark to each player
            if (i == 0)
                playersData[i].setMark('X');
            else
                playersData[i].setMark('O');

            cout << "Player " << playersData[i].getName() << " join the game" << endl;
            
        }
            
    }

    cout << "Starting Game.... " << endl;
    // broadcast empty board
    broadcastBoard();
}

void GameManager::changeTurn()
{
    if (currentPlayer == player[0])
    {
        // Change to player[1]
        currentPlayer = player[1];
        currentPlayerData = playersData[1];
    }
    else if (currentPlayer == player[1])
    {
        // Change to player[0]
        currentPlayer = player[0];
        currentPlayerData = playersData[0];
    }
}

bool GameManager::move()
{
    int turn;

    if (checkWin())     // if someone win or board is full, return false
        return false;

    for (int i = 0; i < MAXPLAYER; i++)
    {
        if (currentPlayer == player[i])
        {
            turn = 1;   // Sign for currentPlayer to make a move
        }
        else
        {
            turn = 0;   // Else, another player get the waiting message
        }
        send(player[i], (const char*)&turn, sizeof(turn), 0);
    }

    // recv data from currentPlayer about movement
    int moveBufX = 0, moveBufY = 0;
    recv(currentPlayer, (char*)&moveBufX, sizeof(moveBufX), 0);     // receive 'X' Coordinate from player
    recv(currentPlayer, (char*)&moveBufY, sizeof(moveBufY), 0);     // receive 'Y' Coordinate from player
    board.setMark(currentPlayerData.getMark(), moveBufX, moveBufY); // input coordinate received to local board

    broadcastBoard();   // broadcast changed local board

    changeTurn();

    return true;
}

bool GameManager::checkWin()
{
    if (board.getDiagonal() || board.getHorizontal() || board.getVertical())    // if there are same mark in diagonal, horizontal, or vertical
    {
        cout << "Someone is winning" << endl;
        isWin = true;   
        changeTurn();   // change turn to winning player
        winningPlayer = currentPlayer;
        return true;
    }
    else if (board.isFull())
    {
        cout << "The game is draw" << endl;
        isDraw = true;
        return true;
    }
    else
    {
        return false;
    }
}

void GameManager::closeServerSocket(SOCKET server)
{
    // Close the socket
    closesocket(server);

    // Close Winsock
    WSACleanup();
}

void GameManager::broadcastBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // send each mark in row and column one by one to each player
            char boardBuf[MAX];
            memset(boardBuf, 0, MAX);
            *boardBuf = board.getMark(i, j);    
            send(player[0], boardBuf, MAX, 0);
            send(player[1], boardBuf, MAX, 0);
        }
    }
}

void GameManager::announceResult()
{
    cout << "Game has ended" << endl;
    int turn = 2;   // to give a clue to player if game is ended
    string winMsg = "Congratulation! you win! ";    // message for winner
    string drawMsg = "It's a draw! ";   // message for both player if game is draw
    char loseMsg[MAX] = "You lose! better luck next time!"; // message for loser

    for (int i = 0; i < MAXPLAYER; i++)
    {
        if (send(player[i], (const char*)&turn, sizeof(turn), 0))   // send a clue to each player if game is ended
        {
            cout << "Announcement sended" << endl;
        }
    }

    if (isWin)  // if there is a winner
    {
        send(winningPlayer, winMsg.c_str(), sizeof(winMsg), 0); // send winning player a winning message
        changeTurn();
        send(currentPlayer, loseMsg, MAX, 0);   // send losing player a losing message
    }
    else if (isDraw)    // if board is full and no winner
    {
        for (int i = 0; i < MAXPLAYER; i++)
        {
            send(player[i], drawMsg.c_str(), sizeof(drawMsg), 0);   // send each player a draw message
        }
    }

    for (int i = 0; i < MAXPLAYER; i++)
    {
        char checkBuf[MAX];
        if (!recv(player[i], checkBuf, MAX, 0))     // waiting for players to close first
        {
            closeServerSocket(server);  // close server socket
        }
    }
}
