#include "StdAfx.h"
#include "DummyClient.h"
#include "testtoolDlg.h"
#include <map>
#include "settings.h"


CDummyClient::CDummyClient( const CLIENT_INFO &_clientInfo, int &retCreateClientError )
{
	m_clientInfo = _clientInfo;
	retCreateClientError = InitPython( _clientInfo.m_iIndex );
	if( retCreateClientError != CLIENT_CREATE_ERROR_NONE )
	{
		return;
	}

	thread = NULL;
	threadLogStr = L"";
	threadState = THREAD_NONE;
	receivingPacketPtr = -1;
	isConnected = false;
	
	if( initThread() == true )
	{
		threadState = THREAD_RUN;
		InitializeCriticalSection( &logCS );
		InitializeCriticalSection( &threadStateCS );
	}
	else
	{
		retCreateClientError = CLIENT_CREATE_ERROR_THREAD_CREATE_FAILED;
	}
}

CDummyClient::~CDummyClient(void)
{
	threadLogStr = L"";	// 메모리 릭 뜨길래;;
	
	if( threadState == THREAD_END )
	{
		DeleteCriticalSection( &logCS );
		DeleteCriticalSection( &threadStateCS );
	
		rcvPacketQueue.clear();
		sendFailPacketQueue.clear();
	}
}

////////	파이썬	/////////
int CDummyClient::InitPython( int _objectIndex )
{
	PyGILState_STATE gilState;
	gilState = PyGILState_Ensure();
	tstring sPy = ((cstr)m_clientInfo.dScriptFileName);

	module = PyImport_ImportModule(jA(sPy));
	if (module == NULL) 
	{ 
		PyErr_Clear();	
		PyGILState_Release( gilState );
		return CLIENT_CREATE_ERROR_SCRIPT_FILE_OPEN_FAILED;  
	}
	else
	{

		// 파이썬 함수 로드 - 
		pyFuncReceive = PyObject_GetAttrString(module, "cCallbackOnReceive");
		if (pyFuncReceive == NULL) 
		{ 
			PyErr_Clear();	
			PyGILState_Release( gilState );
			return CLIENT_CREATE_ERROR_SCRIPT_FUNCTION_LOAD_FAILED;  
		}

		// 함수 로드 - OnConnect
		pyFuncOnConnect = PyObject_GetAttrString(module, "cCallbackOnConnect");
		if( pyFuncOnConnect == NULL )
		{ 
			PyErr_Clear();	
			PyGILState_Release( gilState );
			return CLIENT_CREATE_ERROR_SCRIPT_FUNCTION_LOAD_FAILED;  
		}

		// 함수 로드 - OnDisconnect
		pyFuncOnDisconnect = PyObject_GetAttrString(module, "cCallbackOnDisconnect");
		if( pyFuncOnDisconnect == NULL )
		{ 
			PyErr_Clear();	
			PyGILState_Release( gilState );
			return CLIENT_CREATE_ERROR_SCRIPT_FUNCTION_LOAD_FAILED;  
		}

		// 함수 로드 - GetIsPlaying
		pyFuncGetIsPlaying = PyObject_GetAttrString(module, "cCallbackGetIsPlaying");
		if( pyFuncGetIsPlaying == NULL )
		{ 
			PyErr_Clear();	
			PyGILState_Release( gilState );
			return CLIENT_CREATE_ERROR_SCRIPT_FUNCTION_LOAD_FAILED;  
		}

		// 함수 로드 - pyFuncGetLocation
		pyFuncGetLocation = PyObject_GetAttrString(module, "cCallbackGetLocation");
		if( pyFuncGetLocation == NULL )
		{ 
			PyErr_Clear();	
			PyGILState_Release( gilState );
			return CLIENT_CREATE_ERROR_SCRIPT_FUNCTION_LOAD_FAILED;  
		}

		// 함수 로드 2
		PyObject *setupFunc = PyObject_GetAttrString(module, "cCallbackMakeClient");
		if( setupFunc == NULL )
		{ 
			PyErr_Clear();	
			PyGILState_Release( gilState );
			return CLIENT_CREATE_ERROR_SCRIPT_FUNCTION_LOAD_FAILED;  
		}
		else
		{
			PyObject_CallObject(setupFunc,  Py_BuildValue("(i)", _objectIndex) );
		}
	}
	
	PyGILState_Release( gilState );
	return CLIENT_CREATE_ERROR_NONE;
}

////////	쓰레드	/////////
bool CDummyClient::initThread()
{
	thread = AfxBeginThread( runLoop, ( LPVOID )this );
	if( thread == NULL )
	{
		// 스레드 생성 실패 예외처리
		return false;
	}
	return true;
}

void CDummyClient::endThread()
{
	EnterCriticalSection( &threadStateCS );
	if( threadState == THREAD_RUN )
	{
		threadState = THREAD_END_REQUEST;
	}
	LeaveCriticalSection( &threadStateCS );
}

UINT CDummyClient::runLoop( LPVOID pParam )
{
	CDummyClient *dummyClient = ( CDummyClient * )pParam;
	while( 1 )
	{
		EnterCriticalSection( &dummyClient->threadStateCS );
		if( dummyClient->threadState == THREAD_END_REQUEST )
		{
			dummyClient->threadState = THREAD_END;
			break;
		}
		LeaveCriticalSection( &dummyClient->threadStateCS );

		dummyClient->update();
		Sleep( RUNLOOP_INTRERVAL );
	}
	return 0;
}

void CDummyClient::update()
{
	if( rcvPacketQueue.empty() == false )
	{
		std::string str = (* rcvPacketQueue.begin());
		rcvPacketQueue.pop_front();
		rcvPacketProcess( str );			
	}
}

////////	로그	/////////
void CDummyClient::addLog( CString log )
{
	#ifndef NO_SHOWLOG
	EnterCriticalSection( &logCS );
	threadLogStr = threadLogStr + log + L"\r\n";
	LeaveCriticalSection( &logCS );
	#endif
}

void CDummyClient::GetLog( CString &returnLog )
{
	EnterCriticalSection( &logCS );
	returnLog = threadLogStr;
	LeaveCriticalSection( &logCS );
}

void CDummyClient::ClearLog()
{
	EnterCriticalSection( &logCS );
	threadLogStr = "";
	LeaveCriticalSection( &logCS );
}

bool CDummyClient::GetIsPlaying()
{
	bool isPlaying;
	PyObject *parameters;
	PyGILState_STATE gilState;
	gilState = PyGILState_Ensure();
	parameters = Py_BuildValue("(i)", m_clientInfo.m_iIndex );

	PyObject *returnValue = PyObject_CallObject(pyFuncGetIsPlaying,  parameters );
	Py_DECREF(parameters);

	if (returnValue == NULL) 
	{	
		PyErr_Print(); 
	}
	else 
	{
		PyArg_Parse( returnValue, "b", &isPlaying );
		Py_DECREF(returnValue);
	}

	PyGILState_Release( gilState );	
	return isPlaying;
}

CString CDummyClient::GetLocation()
{
	CString location = L"위치 얻기 실패";
	PyObject *parameters;
	PyGILState_STATE gilState;
	gilState = PyGILState_Ensure();
	parameters = Py_BuildValue("(i)", m_clientInfo.m_iIndex );

	PyObject *returnValue = PyObject_CallObject(pyFuncGetLocation,  parameters );
	Py_DECREF(parameters);

	if (returnValue == NULL) 
	{	
		PyErr_Print(); 
	}
	else 
	{
		char *locationString = 0;
		PyArg_Parse( returnValue, "s", &locationString );
		Py_DECREF(returnValue);

		location = locationString;
	}

	PyGILState_Release( gilState );	
	return location;
}

////////	네트워크	/////////
void CDummyClient::ConnectToServer()
{
	if( isConnected == false )
	{
		addLog(L"접속 시도");
		Create();
		BOOL is = Connect(m_clientInfo.dServerIP, m_clientInfo.m_iServerPort);
		if(!is)
		{
			//jLOG(L"접속 실패");
		}
		else
		{
			addLog(L"접속 성공");
		}
	}
}

void CDummyClient::DisconnectToServer()
{
	if( isConnected == true )
	{
		isConnected = false;

		addLog(L"접속 종료");
		ShutDown(2);
		Close();
		ChangeConnectState( false );
		sendFailPacketQueue.clear();
	}
}

void CDummyClient::rcvPacketProcess( std::string str )
{
	PyObject *parameters;
	PyGILState_STATE gilState;
	gilState = PyGILState_Ensure();
	parameters = Py_BuildValue("(is#)", m_clientInfo.m_iIndex , str.data(), str.size() );
	PyObject_CallObject(pyFuncReceive,  parameters );
	Py_DECREF(parameters);

	PyGILState_Release( gilState );
}

void CDummyClient::clientToServer( std::string str )
{	
	int size = str.size();
	char *sendBuffer = new char[size + 4];
	memcpy( sendBuffer, &size, 4 );
	memcpy( sendBuffer + 4, str.data(), size );
	int sendSize = Send( sendBuffer, size + 4);
	delete sendBuffer;

	if( sendSize != size + 4 )
	{
		int remainSize = size + 4 - sendSize;
		std::string sendFailStr;
		sendFailStr.assign(sendBuffer + sendSize, remainSize);
		sendFailPacketQueue.push_back(sendFailStr);
	}
}

void CDummyClient::OnReceive(int nErrorCode)
{
	char buf[BUFFER_SIZE];
	int bufferPtr = 0;
	int rcvSize = Receive(buf,BUFFER_SIZE);

	if( rcvSize == BUFFER_SIZE )	// 받은 사이즈가 넘겨준 BUFFER_SIZE 와 같을 경우 => 버퍼 오버플로우 알림
	{
		CString logStr;
		logStr.Format( L"패킷 receive 오류. 버퍼 사이즈가 작습니다. 버퍼를 늘려주세요 (현재 버퍼 사이즈 : %d)", BUFFER_SIZE );
		addLog(logStr);
		return;
	}

	if( rcvSize == 0 )
	{
		addLog( L"패킷 receive 오류. rcvSize : 0");
	}
	else if( rcvSize == SOCKET_ERROR )
	{
		CString logStr;
		logStr.Format( L"패킷 receive 오류. SOCKET_ERROR. errorCode : %d)", GetLastError() );
		addLog(logStr);
	}
	else
	{
		// 1. 기존에 받고있던 패킷이 있으면 채운다
		if( receivingPacketPtr != -1 )
		{
			int receivingPacketSize;

			// a. msg 사이즈 구하기
			if( receivingPacketPtr < 4 )	// 기존패킷이 헤더도 다 못받은 경우
			{
				int remainHeaderSize = 4 - receivingPacketPtr;
				if( rcvSize <= remainHeaderSize )	// 헤더크기 이상은 받았다
				{
					memcpy( receiveingBuffer, buf, remainHeaderSize ); // 헤더 완성
					memcpy( &receivingPacketSize, receiveingBuffer, 4 );
				}
				else								// 또 헤더크기조차 못받았다
				{
					memcpy( receiveingBuffer, buf, rcvSize );				// 새로받은 패킷 -> 기존패킷에 복사하고 끝
					receivingPacketPtr += rcvSize;
					return;
				}
			}
			else
			{
				memcpy( &receivingPacketSize, receiveingBuffer, 4 );
			}
			
			// b. 패킷 복사
			int remainSize = receivingPacketSize - receivingPacketPtr;	// 기존패킷의 남은 크기

			if( rcvSize < remainSize )	 // 새로받은 패킷의 크기 < 기존패킷의 남은크기
			{
				memcpy( receiveingBuffer + receivingPacketPtr, buf, rcvSize );				// 새로받은 패킷 -> 기존패킷에 복사하고 끝
				receivingPacketPtr += rcvSize;
				return;
			}
			else	// 새로받은 패킷크기 >= 기존패킷의 남은크기
			{
				memcpy( receiveingBuffer + receivingPacketPtr, buf, remainSize );			// 새로받은 패킷 -> 기존패킷의 남은 부분만큼만 복사
				receivingPacketPtr = -1;
				bufferPtr += remainSize;								//버퍼 포인터 이동
				
				//기존패킷을 receive queue에 넣어준다
				std::string rcvDataStr;
				rcvDataStr.assign( receiveingBuffer + 4, receivingPacketSize );
				rcvPacketQueue.push_back( rcvDataStr );
			}
		}
		
		while( 1 )
		{
			char *packet = buf + bufferPtr;
			int packetSize = rcvSize - bufferPtr;

			if( packetSize <= 0 )
				break;

			if( packetSize < 4 )	// 헤더도 다 못받은 경우
			{
				memcpy( receiveingBuffer, packet, packetSize );				// 새로받은 패킷 -> 기존패킷에 복사하고 끝
				receivingPacketPtr = rcvSize;
				break;		
			}
			else
			{
				int msgSize;
				memcpy( &msgSize, packet, 4 );
				bufferPtr += 4;
				packetSize -= 4;
				if( msgSize > BUFFER_SIZE - 4 )
				{
					CString logStr;
					logStr.Format( L"패킷 receive 오류. 버퍼 사이즈가 작습니다. 버퍼를 늘려주세요 (현재 버퍼 사이즈 : %d)", BUFFER_SIZE );
					addLog(logStr);
					return;
				}

				if( packetSize < msgSize )		// 패킷사이즈가 헤더에 있는 메시지 사이즈보다 작은 경우
				{
					memcpy( receiveingBuffer, packet, packetSize );				// 있는부분까지만 카피 후 종료
					receivingPacketPtr = packetSize;
					break;	
				}
				else
				{
					memcpy( receiveingBuffer, packet + 4, msgSize );			// 새로받은 패킷 -> 기존패킷의 남은 부분만큼만 복사
					receivingPacketPtr = -1;
					bufferPtr += msgSize;										// 버퍼 포인터 이동
					
					//기존패킷을 receive queue에 넣어준다
					std::string rcvDataStr;
					rcvDataStr.assign( receiveingBuffer, msgSize );
					rcvPacketQueue.push_back( rcvDataStr );
				}
			}
		}
	}
}

void CDummyClient::OnSend(int nErrorCode)
{
	// send가 정상적으로 이루어지지 않은 후, 다시 send할수 있을때 불린다
	if( sendFailPacketQueue.empty() == false )
	{
		std::list<std::string>::iterator iter = sendFailPacketQueue.begin();
		for(; iter != sendFailPacketQueue.end(); iter++ )
		{
			clientToServer(*iter);
		}
		Sleep(20);
	}
}

void CDummyClient::OnConnect(int nErrorCode)
{
	if( nErrorCode == 0 )
	{
		isConnected = true;
		addLog(L"접속 성공");
		
		ChangeConnectState( true );

		PyObject *parameters;
		PyGILState_STATE gilState;
		gilState = PyGILState_Ensure();
		parameters = Py_BuildValue("(i)", m_clientInfo.m_iIndex );
		PyObject_CallObject(pyFuncOnConnect,  parameters );
		Py_DECREF(parameters);

		PyGILState_Release( gilState );
	}
	else
	{
		addLog(L"접속 실패");
		ChangeConnectState( false );
	}
}

void CDummyClient::OnClose(int nErrorCode)
{
	isConnected = false;

	addLog(L"서버로부터 접속 종료");
	ChangeConnectState( false );

	PyObject *parameters;
	PyGILState_STATE gilState;
	gilState = PyGILState_Ensure();
	parameters = Py_BuildValue("(i)", m_clientInfo.m_iIndex );
	PyObject_CallObject(pyFuncOnDisconnect,  parameters );
	Py_DECREF(parameters);

	PyGILState_Release( gilState );

	ShutDown(2);
	Close();
	sendFailPacketQueue.clear();
}

void CDummyClient::ChangeConnectState(bool isConnected)
{
	if( isConnected == true )
	{
		m_clientInfo.dState = L"접속중";
	}
	else
	{
		m_clientInfo.dState = L"접속 해제";
	}
	CtesttoolDlg* dlg = (CtesttoolDlg*)AfxGetApp()->m_pMainWnd;
	dlg->UpdateSelectedClientInfo();
}

void CDummyClient::SetIPAndPort(CString ipString, UINT port)
{
	m_clientInfo.dServerIP = ipString;
	m_clientInfo.m_iServerPort = port;
}