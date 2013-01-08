
#include "stdafx.h"


#include <memory.h>
#include <string.h>
#include <stdio.h>

char str1[32] = "aabbcc";

void del_vec(char* str1 , int del,int tot)
{
	memmove( str1 + del, str1+del+1, tot-del );
	memset(str1 + tot-1 , 0 , 1 );
}

void asdf2_main( void )
{
	printf( "The string: %s\n", str1 );
	memcpy( str1 + 2, str1, 4 );
	printf( "New string: %s\n", str1 );

	strcpy_s( str1, sizeof(str1), "0123456789" );   // reset string
	printf( "The string: %s\n", str1 );
	del_vec(str1,0,10);
	printf( "New string: %s\n", str1 );
}



#if 0
//http://www.tech-archive.net/Archive/Development/microsoft.public.win32.programmer.networks/2006-10/msg00355.html
#define _WIN32_WINNT 0x400 // make sure windows.h includes winsock 2,
#include <windows.h>
#include <process.h> // _beginthreadex
#include <iostream>
#include "winsock.h"

#define BUFSZ 4096
#define NBUFS 1

bool InitIO() {
	// initialize winsock
	WSADATA wd = { 0 };
	int e;
	e = WSAStartup( MAKEWORD( 2, 0 ), &wd );
	if( e != 0 ) {
		std::cerr << "WSAStartup()" << std::endl;
		return false;
	}
	if( LOBYTE( wd.wVersion ) < 2 ) {
		std::cerr << "WSAStartup()" << std::endl;
		return false;
	}
	return true;
}

void CloseIO() {
	WSACleanup();
}

void DisableNagle(SOCKET s) {
	const char chOpt = 1;
	setsockopt( s, IPPROTO_TCP, TCP_NODELAY, &chOpt, sizeof(char) );
}

SOCKET OpenServerConnection(const char *server, short port, HANDLE
							hiocp, DWORD key) {
								short err = 0;

								SOCKET s = WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0,
									WSA_FLAG_OVERLAPPED );
								if( s == INVALID_SOCKET ) {
									err = WSAGetLastError();
									return INVALID_SOCKET;
								}
								HANDLE h = CreateIoCompletionPort( (HANDLE)s, hiocp, key, 0 );
								if( h != hiocp ) {
									std::cerr << "Failed to associate IOCP with socket" << std::endl;
									return INVALID_SOCKET;
								}

								DisableNagle( s );

								struct sockaddr_in sockAddr;
								sockAddr.sin_family = AF_INET;
								sockAddr.sin_port = htons( port );
								struct in_addr inetadd;
								inetadd.s_addr = inet_addr( server );
								sockAddr.sin_addr.s_addr = inetadd.s_addr;

								if( 0 == WSAConnect( s, (struct sockaddr *)&sockAddr,
									sizeof(struct sockaddr_in), 0,0, 0,0 ) )
									return s; // connect succeeded on the first try!
								else
									return INVALID_SOCKET;
}

unsigned int __stdcall ThreadProc(void* paramPtr) {
	BOOL status;
	DWORD bytesXmit = 0;
	DWORD key = 15;
	LPOVERLAPPED ovlpdPtr;
	HANDLE hiocp = paramPtr;

	while( true ) {
		// Worker Thread will be waiting on IO Completion Port
		// to process IO Completion packets.
		status = GetQueuedCompletionStatus( hiocp, &bytesXmit, &key,
			&ovlpdPtr, INFINITE );

		if( !status && (ovlpdPtr == 0) ) {
			std::cerr << "::GetQueuedCompletionStatus Failed::" << std::endl;
			return E_FAIL;
		}
		std::cout << "ThreadProc Got overlapped data!" << std::endl;
	}
	return S_OK;
}

int main(int argc, char* argv[])
{
	// If there's no WSOCK 2, exit immediately
	if( !InitIO() ) return 1;

	// Allocate receive buffers
	DWORD inbytes = 0;
	WSABUF bufs[NBUFS];
	for(int i=0; i<NBUFS; i++) {
		bufs[i].len = BUFSZ;
		bufs[i].buf = new char[BUFSZ];
	}

	// Create the IOCP
	HANDLE hiocp = CreateIoCompletionPort( INVALID_HANDLE_VALUE, 0, 0, 0
		);
	if( hiocp == INVALID_HANDLE_VALUE ) {
		std::cerr << "Failed to create IOCP" << std::endl;
		CloseIO();
		return 0;
	}
	unsigned int threadID = 0;
	HANDLE threadHdl = (HANDLE)_beginthreadex( 0, 0, &ThreadProc, hiocp,
		0, &threadID );

	// Create and associate socket with IO Completion Port.
	DWORD key = 15;
	SOCKET sock = OpenServerConnection( "192.168.0.2", 8765, hiocp, key );
	if( sock != INVALID_SOCKET ) {

		OVERLAPPED ovlpd;
		DWORD flags = 0;
		WSARecv( sock, bufs, NBUFS, &inbytes, &flags, &ovlpd, 0 );

		WaitForSingleObject( threadHdl, INFINITE );
	}

	// Cleanup
	closesocket( sock );
	CloseHandle( hiocp );
	for(int j=0; j<NBUFS; j++) {
		delete[] bufs[j].buf;
	}
	CloseIO();

	return 0;
}
#endif