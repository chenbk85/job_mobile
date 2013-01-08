#include "stdafx.h"
#include <stdio.h> 
#include <string.h> 
#include "winsock2.h"
#include "conio.h"
#if 0
void main() {

	//---------------------------------------
	// Declare variables
	WSADATA wsaData;
	SOCKET ListenSocket;

	//---------------------------------------
	// Initialize Winsock
	int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
	if( iResult != NO_ERROR )
		printf("Error at WSAStartup\n");

	//---------------------------------------
	// Create a listening socket
	ListenSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket()\n");
		WSACleanup();
		return;
	}
	int bufsize=0; 
	int rn=0; 

	rn = sizeof(int); 
	// 현재 RCVBUF 값을 얻어온다. 
	if (getsockopt(ListenSocket, SOL_SOCKET, SO_RCVBUF, (char*)&bufsize, (int *)&rn) < 0) 
	{ 
		perror("Set Error"); 
		return ; 
	} 
	printf("Socket SO_RCVBUF Buf Size is %d\n", bufsize); 
	if (getsockopt(ListenSocket, SOL_SOCKET, SO_SNDBUF, (char*)&bufsize, (int *)&rn) < 0) 
	{ 
		perror("Set Error"); 
		return ; 
	} 
	printf("Socket SO_SNDBUF Buf Size is %d\n", bufsize); 

// 	// 버퍼의 크기를 100000 으로 만든다. 
// 	bufsize = 100000; 
// 	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (const char*)&bufsize, (int)rn) < 0) 
// 	{ 
// 		perror("Set Error"); 
// 		return ; 
// 	} 


	WSACleanup();
	if(__argc==1)
	{
		printf("\npress any key to end!!");
		_getch();
	}
	return;
}
#endif