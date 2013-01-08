
class CClientSession
{
public:
	SOCKET			mSocket;
	BOOL			BeginTcp(LPSTR remoteAddress, USHORT remotePort);
	BOOL			End(VOID);

	BOOL			Write(BYTE *data, DWORD dataLength);
	BOOL			Read(BYTE buff, size_t size);
};

BOOL CClientSession::BeginTcp(LPSTR remoteAddress, USHORT remotePort)
{
	if (!remoteAddress || remotePort <= 0)
		return FALSE;

	if (mSocket)
		return FALSE;

	mSocket	= WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	if (mSocket == INVALID_SOCKET)
		return FALSE;


	SOCKADDR_IN RemoteAddressInfo;

	RemoteAddressInfo.sin_family			= AF_INET;
	RemoteAddressInfo.sin_port				= htons(remotePort);
	RemoteAddressInfo.sin_addr.S_un.S_addr	= inet_addr(remoteAddress);

	if (WSAConnect(mSocket, (LPSOCKADDR) &RemoteAddressInfo, sizeof(SOCKADDR_IN), NULL, NULL, NULL, NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			End();

			return FALSE;
		}
	}

	return TRUE;
}

BOOL CClientSession::End(VOID)
{
	closesocket(mSocket);

	return TRUE;
}


BOOL CClientSession::Write(BYTE *data, DWORD dataLength)
{
	if (!mSocket)
		return FALSE;

	if (!data || dataLength <=0)
		return FALSE;

	WSABUF	WsaBuf;
	DWORD	WriteBytes	= 0;
	DWORD	WriteFlag	= 0;

	WsaBuf.buf			= (CHAR*) data;
	WsaBuf.len			= dataLength;

	INT		ReturnValue	= WSASend(mSocket,
		&WsaBuf,
		1,
		&WriteBytes,
		WriteFlag,
		0,
		NULL);

	if (ReturnValue == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING && WSAGetLastError() != WSAEWOULDBLOCK)
	{
		End();

		return FALSE;
	}

	return TRUE;
}

BOOL CClientSession::Read(BYTE buff, size_t size)
{
	if (!mSocket)
		return FALSE;

	WSABUF	WsaBuf;
	DWORD	ReadBytes	= 0;
	DWORD	ReadFlag	= 0;
	WsaBuf.buf			= (CHAR*) buff;
	WsaBuf.len			= size;

	INT		ReturnValue = WSARecv(mSocket,
		&WsaBuf,
		1,
		&ReadBytes,
		&ReadFlag,
		0,
		NULL);

	if (ReturnValue == SOCKET_ERROR && WSAGetLastError() != WSA_IO_PENDING && WSAGetLastError() != WSAEWOULDBLOCK)
	{
		End();

		return FALSE;
	}

	return TRUE;
}


void yd_monitor_send_loop()
{
	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);	// 2.2 버전을 로드합니다.

}

