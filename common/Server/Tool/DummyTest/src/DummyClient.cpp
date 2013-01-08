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
	threadLogStr = L"";	// �޸� �� �߱淡;;
	
	if( threadState == THREAD_END )
	{
		DeleteCriticalSection( &logCS );
		DeleteCriticalSection( &threadStateCS );
	
		rcvPacketQueue.clear();
		sendFailPacketQueue.clear();
	}
}

////////	���̽�	/////////
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

		// ���̽� �Լ� �ε� - 
		pyFuncReceive = PyObject_GetAttrString(module, "cCallbackOnReceive");
		if (pyFuncReceive == NULL) 
		{ 
			PyErr_Clear();	
			PyGILState_Release( gilState );
			return CLIENT_CREATE_ERROR_SCRIPT_FUNCTION_LOAD_FAILED;  
		}

		// �Լ� �ε� - OnConnect
		pyFuncOnConnect = PyObject_GetAttrString(module, "cCallbackOnConnect");
		if( pyFuncOnConnect == NULL )
		{ 
			PyErr_Clear();	
			PyGILState_Release( gilState );
			return CLIENT_CREATE_ERROR_SCRIPT_FUNCTION_LOAD_FAILED;  
		}

		// �Լ� �ε� - OnDisconnect
		pyFuncOnDisconnect = PyObject_GetAttrString(module, "cCallbackOnDisconnect");
		if( pyFuncOnDisconnect == NULL )
		{ 
			PyErr_Clear();	
			PyGILState_Release( gilState );
			return CLIENT_CREATE_ERROR_SCRIPT_FUNCTION_LOAD_FAILED;  
		}

		// �Լ� �ε� - GetIsPlaying
		pyFuncGetIsPlaying = PyObject_GetAttrString(module, "cCallbackGetIsPlaying");
		if( pyFuncGetIsPlaying == NULL )
		{ 
			PyErr_Clear();	
			PyGILState_Release( gilState );
			return CLIENT_CREATE_ERROR_SCRIPT_FUNCTION_LOAD_FAILED;  
		}

		// �Լ� �ε� - pyFuncGetLocation
		pyFuncGetLocation = PyObject_GetAttrString(module, "cCallbackGetLocation");
		if( pyFuncGetLocation == NULL )
		{ 
			PyErr_Clear();	
			PyGILState_Release( gilState );
			return CLIENT_CREATE_ERROR_SCRIPT_FUNCTION_LOAD_FAILED;  
		}

		// �Լ� �ε� 2
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

////////	������	/////////
bool CDummyClient::initThread()
{
	thread = AfxBeginThread( runLoop, ( LPVOID )this );
	if( thread == NULL )
	{
		// ������ ���� ���� ����ó��
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

////////	�α�	/////////
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
	CString location = L"��ġ ��� ����";
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

////////	��Ʈ��ũ	/////////
void CDummyClient::ConnectToServer()
{
	if( isConnected == false )
	{
		addLog(L"���� �õ�");
		Create();
		BOOL is = Connect(m_clientInfo.dServerIP, m_clientInfo.m_iServerPort);
		if(!is)
		{
			//jLOG(L"���� ����");
		}
		else
		{
			addLog(L"���� ����");
		}
	}
}

void CDummyClient::DisconnectToServer()
{
	if( isConnected == true )
	{
		isConnected = false;

		addLog(L"���� ����");
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

	if( rcvSize == BUFFER_SIZE )	// ���� ����� �Ѱ��� BUFFER_SIZE �� ���� ��� => ���� �����÷ο� �˸�
	{
		CString logStr;
		logStr.Format( L"��Ŷ receive ����. ���� ����� �۽��ϴ�. ���۸� �÷��ּ��� (���� ���� ������ : %d)", BUFFER_SIZE );
		addLog(logStr);
		return;
	}

	if( rcvSize == 0 )
	{
		addLog( L"��Ŷ receive ����. rcvSize : 0");
	}
	else if( rcvSize == SOCKET_ERROR )
	{
		CString logStr;
		logStr.Format( L"��Ŷ receive ����. SOCKET_ERROR. errorCode : %d)", GetLastError() );
		addLog(logStr);
	}
	else
	{
		// 1. ������ �ް��ִ� ��Ŷ�� ������ ä���
		if( receivingPacketPtr != -1 )
		{
			int receivingPacketSize;

			// a. msg ������ ���ϱ�
			if( receivingPacketPtr < 4 )	// ������Ŷ�� ����� �� ������ ���
			{
				int remainHeaderSize = 4 - receivingPacketPtr;
				if( rcvSize <= remainHeaderSize )	// ���ũ�� �̻��� �޾Ҵ�
				{
					memcpy( receiveingBuffer, buf, remainHeaderSize ); // ��� �ϼ�
					memcpy( &receivingPacketSize, receiveingBuffer, 4 );
				}
				else								// �� ���ũ������ ���޾Ҵ�
				{
					memcpy( receiveingBuffer, buf, rcvSize );				// ���ι��� ��Ŷ -> ������Ŷ�� �����ϰ� ��
					receivingPacketPtr += rcvSize;
					return;
				}
			}
			else
			{
				memcpy( &receivingPacketSize, receiveingBuffer, 4 );
			}
			
			// b. ��Ŷ ����
			int remainSize = receivingPacketSize - receivingPacketPtr;	// ������Ŷ�� ���� ũ��

			if( rcvSize < remainSize )	 // ���ι��� ��Ŷ�� ũ�� < ������Ŷ�� ����ũ��
			{
				memcpy( receiveingBuffer + receivingPacketPtr, buf, rcvSize );				// ���ι��� ��Ŷ -> ������Ŷ�� �����ϰ� ��
				receivingPacketPtr += rcvSize;
				return;
			}
			else	// ���ι��� ��Ŷũ�� >= ������Ŷ�� ����ũ��
			{
				memcpy( receiveingBuffer + receivingPacketPtr, buf, remainSize );			// ���ι��� ��Ŷ -> ������Ŷ�� ���� �κи�ŭ�� ����
				receivingPacketPtr = -1;
				bufferPtr += remainSize;								//���� ������ �̵�
				
				//������Ŷ�� receive queue�� �־��ش�
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

			if( packetSize < 4 )	// ����� �� ������ ���
			{
				memcpy( receiveingBuffer, packet, packetSize );				// ���ι��� ��Ŷ -> ������Ŷ�� �����ϰ� ��
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
					logStr.Format( L"��Ŷ receive ����. ���� ����� �۽��ϴ�. ���۸� �÷��ּ��� (���� ���� ������ : %d)", BUFFER_SIZE );
					addLog(logStr);
					return;
				}

				if( packetSize < msgSize )		// ��Ŷ����� ����� �ִ� �޽��� ������� ���� ���
				{
					memcpy( receiveingBuffer, packet, packetSize );				// �ִºκб����� ī�� �� ����
					receivingPacketPtr = packetSize;
					break;	
				}
				else
				{
					memcpy( receiveingBuffer, packet + 4, msgSize );			// ���ι��� ��Ŷ -> ������Ŷ�� ���� �κи�ŭ�� ����
					receivingPacketPtr = -1;
					bufferPtr += msgSize;										// ���� ������ �̵�
					
					//������Ŷ�� receive queue�� �־��ش�
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
	// send�� ���������� �̷������ ���� ��, �ٽ� send�Ҽ� ������ �Ҹ���
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
		addLog(L"���� ����");
		
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
		addLog(L"���� ����");
		ChangeConnectState( false );
	}
}

void CDummyClient::OnClose(int nErrorCode)
{
	isConnected = false;

	addLog(L"�����κ��� ���� ����");
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
		m_clientInfo.dState = L"������";
	}
	else
	{
		m_clientInfo.dState = L"���� ����";
	}
	CtesttoolDlg* dlg = (CtesttoolDlg*)AfxGetApp()->m_pMainWnd;
	dlg->UpdateSelectedClientInfo();
}

void CDummyClient::SetIPAndPort(CString ipString, UINT port)
{
	m_clientInfo.dServerIP = ipString;
	m_clientInfo.m_iServerPort = port;
}