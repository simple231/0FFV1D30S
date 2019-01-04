#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

int main() {
	int port = 8080;
	WSAData wsa;
	SOCKET server, client;
	SOCKADDR_IN serverAddr, clientAddr;
	//-----------------------------------
	WSAStartup(MAKEWORD(2,0), &wsa);
	server = socket(AF_INET,SOCK_STREAM,0);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port = port;
	//------------------------------------
	bind(server,(SOCKADDR * )&serverAddr, sizeof(serverAddr));
	listen(server,0);
	cout << "Listening for incoming connections..." << endl;
	
	char buffer[1024];
    int clientAddrSize = sizeof(clientAddr);
    while(true){
    	if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET) {
	        cout << "Client connected!" << endl;
	        recv(client, buffer, sizeof(buffer), 0);
	        cout << "Client says: " << buffer << endl;
	        memset(buffer, 0, sizeof(buffer));
	        closesocket(client);
	        cout << "Client disconnected." << endl;
	    }
	}
	return 0; 
}
