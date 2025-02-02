#include <iostream>
#include <stdio.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <cstring>
#endif
#include <vector>

#include "include/producer.h"

using namespace std;

vector <char> convert(vector <char> result, string s)
{
    size_t l = s.length();
    for(int i = l - 1; i > -1; i--)
    {
        result.emplace(result.begin(), s.at(i));
        result.erase(result.end() - 1);
    }
    return result;
}

vector <char> clearBuf(vector <char> result)
{
    result.erase(result.begin(), result.end());
    const short BUFF_SIZE = 1024;
    for(int i = BUFF_SIZE - 1; i > -1; i--)
        result.emplace(result.begin(), '\0');
    return result;
}

int main(void)
{
#ifdef test1
    const char IP_SERV[] = "10.124.40.14";
    const int PORT_NUM = 615;
    const short BUFF_SIZE = 1024;

    int erStat;
    in_addr ip_to_num;
    erStat = inet_pton(AF_INET, IP_SERV, &ip_to_num);
    if (erStat <= 0)
    {
        cout << "Error in IP translation to special numeric format" << endl;
        return 1;
    }

#ifdef _WIN32
    WSADATA wsData;
    erStat = WSAStartup(MAKEWORD(2,2), &wsData);
    if ( erStat != 0 )
    {
        cout << "Error WinSock version initializaion #";
        cout << WSAGetLastError();
        return 1;
    }
    else
        cout << "WinSock initialization is OK" << endl;
    SOCKET ServSock = socket(AF_INET, SOCK_STREAM, 0);
    if (ServSock == INVALID_SOCKET)
    {
        cout << "Error initialization socket # " << WSAGetLastError() << endl;
        closesocket(ServSock);
        WSACleanup();
        return 1;
    }
    else
        cout << "Server socket initialization is OK" << endl;
    sockaddr_in servInfo;
    ZeroMemory(&servInfo, sizeof(servInfo));
#else
    int ServSock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servInfo;
    memset(&servInfo, '0', sizeof(servInfo));
#endif

    servInfo.sin_family = AF_INET;
    servInfo.sin_addr = ip_to_num;
    servInfo.sin_port = htons(PORT_NUM);

#ifdef _WIN32
    erStat = bind(ServSock, (sockaddr*)&servInfo, sizeof(servInfo));
    if ( erStat != 0 )
    {
        cout << "Error Socket binding to server info. Error # " << WSAGetLastError() << endl;
        closesocket(ServSock);
        WSACleanup();
        return 1;
    }
    else
        cout << "Binding socket to Server info is OK" << endl;
#else
    bind(ServSock, (struct sockaddr*)&servInfo, sizeof(servInfo)); 
#endif

#ifdef _WIN32
    erStat = listen(ServSock, SOMAXCONN);
    if ( erStat != 0 )
    {
        cout << "Can't start to listen to. Error # " << WSAGetLastError() << endl;
        closesocket(ServSock);
        WSACleanup();
        return 1;
    }
    else
        cout << "Listening..." << endl;
#else
    listen(ServSock , SOMAXCONN);
#endif

#ifdef _WIN32
    sockaddr_in clientInfo;
    ZeroMemory(&clientInfo, sizeof(clientInfo));
#else
    struct sockaddr_in clientInfo;
    memset(&clientInfo, '0', sizeof(clientInfo));
#endif

#ifdef _WIN32
    int clientInfo_size = sizeof(clientInfo);
    SOCKET ClientConn = accept(ServSock, (sockaddr*)&clientInfo, &clientInfo_size);
    if (ClientConn == INVALID_SOCKET)
    {
        cout << "Client detected, but can't connect to a client. Error # " << WSAGetLastError() << endl;
        closesocket(ServSock);
        closesocket(ClientConn);
        WSACleanup();
        return 1;
    }
    else
    {
        cout << "Connection to a client established successfully" << endl;
        char clientIP[22];

        inet_ntop(AF_INET, &clientInfo.sin_addr, clientIP, INET_ADDRSTRLEN);

        cout << "Client connected with IP address " << clientIP << endl;
    }
#else
    socklen_t clientInfo_size = sizeof(clientInfo);
    int ClientConn = accept(ServSock, (sockaddr*)&clientInfo, &clientInfo_size);
#endif

    vector <char> servBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);
    short packet_size = 0;

    producer a1;
    a1.start_game();

    while (true)
    {
        packet_size = recv(ClientConn, servBuff.data(), servBuff.size(), 0);
        cout << "Client's message: " << servBuff.data() << endl;
        std::cout << "Testing server methods..." << std::endl;
        a1.test_game(servBuff);

        cout << "Your (host) message: ";
        string anser = "ok!";
        clientBuff = convert(clientBuff, anser);
        cout << clientBuff.data() << endl;
        std::cout << std::endl;

        if (clientBuff[0] == 'o' && clientBuff[1] == 'u' && clientBuff[2] == 't')
        {
#ifdef _WIN32
            shutdown(ClientConn, SD_BOTH);
            closesocket(ServSock);
            closesocket(ClientConn);
            WSACleanup();
#else
            close(ServSock);
            close(ClientConn);
#endif
            return 0;
        }

        packet_size = send(ClientConn, clientBuff.data(), clientBuff.size(), 0);

#ifdef _WIN32
        if (packet_size == SOCKET_ERROR)
        {
            cout << "Can't send message to Client. Error # " << WSAGetLastError() << endl;
            closesocket(ServSock);
            closesocket(ClientConn);
            WSACleanup();
            return 1;
        }
#else
        if (packet_size == SO_ERROR)
        {
            close(ServSock);
            close(ClientConn);
            return 1;
        }
#endif
    }

#ifdef _WIN32
        closesocket(ServSock);
        closesocket(ClientConn);
        WSACleanup();
#else
        close(ServSock);
        close(ClientConn);
#endif
#endif
    return 0;
}
