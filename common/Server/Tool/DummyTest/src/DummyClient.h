#pragma once
#include "gameMessage.h"
#include <list>

#pragma comment(lib, "libprotobuf.lib")
#pragma comment(lib, "libprotobuf-lite.lib")
#pragma comment(lib, "libprotoc.lib")

#include "Python.h"

#pragma comment(lib, "libprotobuf.lib")
#pragma comment(lib, "libprotobuf-lite.lib")
#pragma comment(lib, "libprotoc.lib")

#include "CommonDef.h"
#include "settings.h"

typedef enum _THREAD_STATE
{
	THREAD_NONE = 0,
	THREAD_RUN,
	THREAD_END_REQUEST,
	THREAD_END
} THREAD_STATE;

class CDummyClient : public CWinThread, public CAsyncSocket
{
private:
	CWinThread *thread;
	bool isConnected;

	std::list<std::string> rcvPacketQueue;
	std::list<std::string> sendFailPacketQueue;

	// packetProcess
	int receivingPacketPtr;				// -1 이면 받고있는(처리 안된) 패킷 없음
	char receiveingBuffer[BUFFER_SIZE];	// 받고있는 패킷을 저장할 버퍼

	bool initThread();
	static UINT runLoop( LPVOID pParam );
	void rcvPacketProcess( std::string str );

public:

	CLIENT_INFO m_clientInfo;

	CRITICAL_SECTION threadStateCS;
	CRITICAL_SECTION logCS;
	CString threadLogStr;
	THREAD_STATE threadState;

	PyObject  *module, *pyFuncReceive, *pyFuncOnConnect, *pyFuncOnDisconnect, *pyFuncGetIsPlaying, *pyFuncGetLocation;

	CDummyClient( const CLIENT_INFO &_clientInfo, int &retCreateClientError );
	~CDummyClient();
	int InitPython( int _objectIndex );
	void update();

	void endThread();
	void GetLog( CString &returnLog );
	void addLog( CString log );
	void ClearLog();

	bool GetIsPlaying();
	CString GetLocation();

	// 네트워크
	void OnReceive(int nErrorCode);
	void OnConnect(int nErrorCode);
	void OnClose(int nErrorCode);
	void OnSend(int nErrorCode);

	void ConnectToServer();
	void DisconnectToServer();

	void clientToServer( std::string str );

	void ChangeConnectState(bool isConnected);

	void SetIPAndPort(CString ipString, UINT port);
};



