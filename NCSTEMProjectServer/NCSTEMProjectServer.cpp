#include <stdio.h>
#include <tchar.h>
#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>

#include "Serial.h"
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

int main() {

	WSADATA wsaData;
	WSAStartup(0x202, &wsaData);

	int server_port = 55000;
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.50.255", &serverAddr.sin_addr.s_addr);
	serverAddr.sin_port = htons(server_port);

	int clientSock = socket(PF_INET, SOCK_DGRAM, 0);
	
	char message[650];
	size_t messagesize = sizeof(message);

	tstring COMPort(TEXT("COM3"));
	Serial SerialPort(COMPort, 9600);

	bool KeepSending = true;	

	while (KeepSending)
	{

		SerialPort.read(message, messagesize);
		printf("\nMessage: %.*s", sizeof(message), message);

		if (sendto(clientSock, message, sizeof(message), 0, (LPSOCKADDR)&serverAddr, sizeof(struct sockaddr)) == SOCKET_ERROR)
		{

			KeepSending = false;

		}

		Sleep(865);

	}

	closesocket(clientSock);

	WSACleanup();

	return 0;

}