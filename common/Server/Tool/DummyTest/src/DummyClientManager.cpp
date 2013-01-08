#include "StdAfx.h"
#include "DummyClientManager.h"
#include "settings.h"
#include "testtoolDlg.h"


CDummyClientManager *g_dummyClientManager=0;

// ���̽� ���� �ݹ�

static PyObject *pythonCallbackSend(PyObject *self, PyObject *args)
{
	int index = 0;
	char *returnValue = 0;
	int length = 0;
	PyArg_ParseTuple(args, "is#", &index, &returnValue, &length);
	std::string returnStr;
	returnStr.assign( returnValue, length );

	CDummyClient *client = g_dummyClientManager->GetDummyClientByIndex( index );
	if( client != NULL )
	{
		client->clientToServer( returnStr );
	}
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *pythonCallbackLog(PyObject *self, PyObject *args)
{
	int index = 0;
	char *returnValue = 0;
	int length = 0;
	PyArg_ParseTuple(args, "is#", &index, &returnValue, &length);
	std::string returnStr;
	returnStr.assign( returnValue, length );

	CDummyClient *client = g_dummyClientManager->GetDummyClientByIndex( index );
	if( client != NULL )
	{
		TCHAR logStr[MAX_MULTIBYTE_TO_UNICODE_BUFFER];
		MultiByteToWideChar(CP_ACP, 0, returnValue, -1, logStr, MAX_MULTIBYTE_TO_UNICODE_BUFFER);
		client->addLog( logStr );
	}
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *pythonCallbackGetUserID(PyObject *self, PyObject *args)
{
	int index = 0;
	PyArg_ParseTuple(args, "i", &index);
	
	CDummyClient *client = g_dummyClientManager->GetDummyClientByIndex( index );
	if( client != NULL )
	{
		char charBuf[256];
		WideCharToMultiByte(CP_ACP, 0, client->m_clientInfo.GetName(), -1, charBuf, 256, 0, 0);
		return Py_BuildValue("s", charBuf);
	}
	else
	{
		return Py_BuildValue("s", "");
	}
}

static PyObject *pythonCallbackGetUserPassword(PyObject *self, PyObject *args)
{
	int index = 0;
	PyArg_ParseTuple(args, "i", &index);
	
	CDummyClient *client = g_dummyClientManager->GetDummyClientByIndex( index );
	if( client != NULL )
	{
		char charBuf[256];
		WideCharToMultiByte(CP_ACP, 0, client->m_clientInfo.dPwd, -1, charBuf, 256, 0, 0);
		return Py_BuildValue("s", charBuf);
	}
	else
	{
		Py_INCREF(Py_None);
		return Py_None;
	}
}

static PyObject *pythonCallbackResetLog(PyObject *self, PyObject *args)
{
	int index = 0;
	PyArg_ParseTuple(args, "i", &index);
	
	CDummyClient *client = g_dummyClientManager->GetDummyClientByIndex( index );
	if( client != NULL )
	{
		client->ClearLog();
	}

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *pythonCallbackResetIPAndPort(PyObject *self, PyObject *args)
{
	int index = 0;
	
	char *returnValue = 0;
	int length = 0;
	UINT port = 0;
	PyArg_ParseTuple(args, "is#i", &index, &returnValue, &length, &port);
	std::string returnStr;
	returnStr.assign( returnValue, length );

	CDummyClient *client = g_dummyClientManager->GetDummyClientByIndex( index );
	if( client != NULL )
	{
		TCHAR ipString[MAX_MULTIBYTE_TO_UNICODE_BUFFER];
		MultiByteToWideChar(CP_ACP, 0, returnValue, -1, ipString, MAX_MULTIBYTE_TO_UNICODE_BUFFER);
		client->SetIPAndPort( ipString, port );
	}

	Py_INCREF(Py_None);
	return Py_None;
}

static PyMethodDef modules[] = {
	{"CFunc_Send",				pythonCallbackSend,		METH_VARARGS},
	{"CFunc_Log",				pythonCallbackLog,	METH_VARARGS},
	{"CFunc_GetUserID",			pythonCallbackGetUserID,	METH_VARARGS},
	{"CFunc_GetUserPassword",	pythonCallbackGetUserPassword,	METH_VARARGS},
	{"CFunc_ResetLog",			pythonCallbackResetLog,	METH_VARARGS},
	{"CFunc_ResetIPAndPort",	pythonCallbackResetIPAndPort,	METH_VARARGS},
 	{NULL,		NULL}
};




// �ʱ�ȭ
CDummyClientManager::CDummyClientManager(void)
{
	g_dummyClientManager = this;

	m_highestIndex = 0;
	m_curIndex = 0;	
	m_maxLimitIndex = 999999;	

	// ���̽� �ʱ�ȭ
	Py_Initialize();
	PyEval_InitThreads();
	mainThreadState = PyEval_SaveThread();
	PyGILState_STATE gilState;

	gilState = PyGILState_Ensure();

	PyImport_AddModule("pythonCallbackModule");
	Py_InitModule("pythonCallbackModule", modules);

	PyRun_SimpleString("import sys\n");
	PyRun_SimpleString("sys.path.append('.\\Python')\n");
	
	PyGILState_Release( gilState );

	// ���� ��ũ��Ʈ �ε�
	CString log = ( SetMainScript() == false ) ? L"mainscript �ε� ����" : L"mainscript �ε� ����";	
	CtesttoolDlg* dlg = (CtesttoolDlg*)AfxGetApp()->m_pMainWnd;
	dlg->addMainLog( log );
	dlg->showMainLog();
}

CDummyClientManager::~CDummyClientManager(void)
{
	DeleteDummyClient( 0, m_highestIndex - 1 );
	
	while(1)
	{
		int count = dummyClientToDeleteList.size();
		if( count == 0 )
		{
			break;
		}
		DeleteThreadEndedClient();
		Sleep(50);
	}
	
	PyEval_RestoreThread( mainThreadState );
	Py_Finalize();
}

// ���� ��ũ��Ʈ �ε�
bool CDummyClientManager::SetMainScript()
{
	bool bSuccess = true;
	PyGILState_STATE gilState;
	gilState = PyGILState_Ensure();
	
	mainScriptmodule = PyImport_ImportModule("mainscript");
	if (mainScriptmodule == NULL) 
	{ 
		PyErr_Clear();	
		bSuccess = false;
	}	
	PyGILState_Release( gilState );
	return bSuccess;
}

// Ŭ���̾�Ʈ ����
int CDummyClientManager::MakeDummyClient( int _count )
{
	return MakeDummyClient( _count, m_clientInfoSetting );
}

int CDummyClientManager::MakeDummyClient( int _count, CLIENT_INFO _clientInfo )
{
	DeleteThreadEndedClient();	// dummyCilent ������, ������ ������� �������� ���� �������� ���� dummyClient���� �����Ѵ�.

	int startIndex = m_curIndex;
	int endIndex = m_curIndex + _count - 1;
	endIndex = ( endIndex > m_maxLimitIndex ) ? m_maxLimitIndex : endIndex;
	int createCount = 0;
	int clientError;
	CtesttoolDlg* dlg = (CtesttoolDlg*)AfxGetApp()->m_pMainWnd;

	for( int i = startIndex; i <= endIndex; i++ )
	{	
		// �ʿ� Ŭ���̾�Ʈ�� �̹� �ִ��� Ȯ��
		_clientInfo.m_iIndex = m_curIndex;
		std::tstring dName =  _clientInfo.GetName().GetString();
		if( dummyClientMapByIndex.find( i ) != dummyClientMapByIndex.end() ||
			dummyClientMapByName.find( dName ) != dummyClientMapByName.end() )	// �̹� �ش� threadID�� map�� �ִ� ���
		{
			dlg->addMainLog(L"���� Ŭ���̾�Ʈ �޴����� �ߺ� �ε��� �߻�");
			dlg->showMainLog();
			continue;
		}

		// Ŭ���̾�Ʈ ����
		CDummyClient * dummyClient = new CDummyClient( _clientInfo, clientError );

		if( clientError == CLIENT_CREATE_ERROR_NONE )	// ���������� ����
		{
			dummyClientMapByIndex[i] = dummyClient;
			dummyClientMapByName[dummyClient->m_clientInfo.GetName().GetString()] = dummyClient;
		
			createCount++;
			m_curIndex++;
			m_highestIndex = ( m_curIndex > m_highestIndex ) ? m_curIndex : m_highestIndex;

		}
		else											// ���� ����
		{
			switch( clientError )
			{
			case CLIENT_CREATE_ERROR_THREAD_CREATE_FAILED:
				dlg->addMainLog(L"������ ���� ����");
				break;
			case CLIENT_CREATE_ERROR_SCRIPT_FILE_OPEN_FAILED:
				dlg->addMainLog(L"��ũ��Ʈ ���� �ε� ����");
				break;
			case CLIENT_CREATE_ERROR_SCRIPT_FUNCTION_LOAD_FAILED:
				dlg->addMainLog(L"��ũ��Ʈ �Լ� �ε� ����");
				break;
			default:
				dlg->addMainLog(L"���� Ŭ���̾�Ʈ ���� ����");
			}
			dlg->showMainLog();
			delete dummyClient;
		}
	}
	return createCount;
}

// Ŭ���̾�Ʈ ����
int CDummyClientManager::DeleteDummyClient( int _startIndex, int _endIndex )
{
	DeleteThreadEndedClient();	// dummyCilent ������, ������ ������� �������� ���� �������� ���� dummyClient���� �����Ѵ�.
	int deleteCount = 0;
	for( int i = _startIndex; i <= _endIndex; i++ )
	{
		if( dummyClientMapByIndex.find( i ) != dummyClientMapByIndex.end() )	// �ʿ� �ش� _index�� ������
		{
			CDummyClient *dummyClient = dummyClientMapByIndex[i];

			dummyClientToDeleteList.push_back( dummyClient );	// �����尡 ���� �� delete ���ֱ� ����, ���� ����Ʈ�� ����
			dummyClient->endThread();

			dummyClientMapByIndex.erase( i );
			dummyClientMapByName.erase( dummyClient->m_clientInfo.GetName().GetString() );
				
			deleteCount++;
		}
	}
	return deleteCount;
}

// Ŭ���̾�Ʈ ���

CDummyClient *CDummyClientManager::GetDummyClientByIndex( int _index )
{
	if( dummyClientMapByIndex.find( _index ) == dummyClientMapByIndex.end() )	// �ʿ� �ش� _index�� ������
	{
		return NULL;
	}
	else
	{
		return dummyClientMapByIndex[_index];
	}
}

CDummyClient *CDummyClientManager::GetDummyClientByName( CString _name )
{
	std::tstring clientName = _name.GetString();
	if( dummyClientMapByName.find( clientName ) == dummyClientMapByName.end() )	// �ʿ� �ش� clientName�� ������
	{
		return NULL;
	}
	else
	{
		return dummyClientMapByName[clientName];
	}
}

// Ŭ���̾�Ʈ ����
int CDummyClientManager::ConnectAllClient( int _per, int _delayMSec )
{
	return Connect( 0, 0, _per, _delayMSec );
}

void Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();


	while(GetTickCount() - dwStart < dwMillisecond)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

int CDummyClientManager::Connect( int _startIndex, int _endIndex, int _per, int _delayMSec )
{
	int connectCount = 0;
	int connectPerCount = 1;

	for( int i = _startIndex; i <= _endIndex; i++ )
	{
		if( dummyClientMapByIndex.find( i ) != dummyClientMapByIndex.end() )
		{
			connectCount++;
			CDummyClient *dummyClient = dummyClientMapByIndex[i];
			dummyClient->ConnectToServer();

			CtesttoolDlg* dlg = (CtesttoolDlg*)AfxGetApp()->m_pMainWnd;
			CString logStr;
			
			logStr.Format(L"%s ���ӽõ�\r\n", dummyClient->m_clientInfo.GetName() );
			dlg->showLog( logStr );

			if( connectPerCount == _per )
			{
				CString logStr2;
				logStr2.Format(L"sleep %d\r\n", _delayMSec );
				dlg->showLog( logStr + logStr2 );

				connectPerCount = 1;
				Sleep( _delayMSec );
			}
			else
			{	
				connectPerCount++;
			}
		}
	}
	
	return connectCount;
}

// Ŭ���̾�Ʈ ���� ����
int CDummyClientManager::DisconnectAllClient( int _per, int _delayMSec )
{
	return Disconnect( 0, 0, _per, _delayMSec );
}

int CDummyClientManager::Disconnect( int _startIndex, int _endIndex, int _per, int _delayMSec )
{
	int disconnectCount = 0;
	int disconnectPerCount = 1;
	for( int i = _startIndex; i <= _endIndex; i++ )
	{
		if( dummyClientMapByIndex.find( i ) != dummyClientMapByIndex.end() )
		{
			disconnectCount++;
			CDummyClient *dummyClient = dummyClientMapByIndex[i];
			dummyClient->DisconnectToServer();

			CString logStr;
			logStr.Format(L"%s �������� �õ�\r\n", dummyClient->m_clientInfo.GetName() );
			CtesttoolDlg* dlg = (CtesttoolDlg*)AfxGetApp()->m_pMainWnd;
			dlg->showLog( logStr );
						
			if( disconnectPerCount == _per )
			{
				disconnectPerCount = 1;
				Sleep( _delayMSec );
			}
			else
			{
				disconnectPerCount++;
			}
		}
	}
	return disconnectCount;
}

// Ŭ���̾�Ʈ ���� ���
void CDummyClientManager::PrintClientStatus( int _startIndex, int _endIndex )
{
	CtesttoolDlg* dlg = (CtesttoolDlg*)AfxGetApp()->m_pMainWnd;
	CString logStr;

	dlg->addMainLog( L"Ŭ���̾�Ʈ ���� ���.\r\n" );
	for( int i = _startIndex; i <= _endIndex; i++ )
	{
		CDummyClient *targetClient = GetDummyClientByIndex( i );
		if( targetClient != NULL )
		{
			logStr.Format(L"name : %s index : %i location : %s\r\n", targetClient->m_clientInfo.GetName(), targetClient->m_clientInfo.m_iIndex, targetClient->GetLocation() );
			dlg->addMainLog( logStr );
		}
		else
		{
			logStr.Format(L"[���� - PrintClientStatus - dindex:%d] �ش� Ŭ���̾�Ʈ�� �����ϴ�.\r\n", i );
			dlg->addMainLog( logStr );
		}
	}
	dlg->showMainLog();
}

// Ŭ���̾�Ʈ ��ũ��Ʈ �Լ� ȣ��
void CDummyClientManager::CallMainScriptFunction( CString _funcName, CString _format, ... )
{
	va_list valist;
	va_start( valist, _format );
	CallFunctionVa( MAINSCRIPT, MAINSCRIPT, jA(_funcName), jA(_format), valist );
	va_end( valist );
}

void CDummyClientManager::CallMainScriptFunctionVa( CString _funcName, CString _format, va_list _vaList )
{
	CallFunctionVa( MAINSCRIPT, MAINSCRIPT, jA(_funcName), jA(_format), _vaList );
}

void CDummyClientManager::CallFunction( int _startIndex, int _endIndex, CString _funcName, CString _format, ...)
{
	va_list valist;
	va_start( valist, _format );
	CallFunctionVa( _startIndex, _endIndex, jA(_funcName), jA(_format), valist );
	va_end( valist );
}

void CDummyClientManager::CallFunctionVa( acstr _funcName, CStringA _format, va_list _vaList )
{
	if( dummyClientMapByIndex.empty() == false )
	{
		std::pair<int, CDummyClient*>pair = *(dummyClientMapByIndex.begin());
		CallFunctionVa( pair.first, pair.first, _funcName, _format, _vaList );
	}
	else
	{
		// ����ó��
	}
}

void CDummyClientManager::CallFunctionVa( int _startIndex, int _endIndex, acstr _funcName, CStringA _format, va_list _vaList )
{
	PyObject *module;
	CtesttoolDlg* dlg = (CtesttoolDlg*)AfxGetApp()->m_pMainWnd;
	CString logStr;
	
	std::vector<int> variableIndexArray;
	int formatLength = _format.GetLength();
	for( int i = 0; i < formatLength; i++ )
	{
		if( _format.GetAt(i) == 'v' )
		{
			variableIndexArray.push_back(i);
			_format.SetAt(i, 'i');
		}
	}

	CStringA format = "(" + _format + ")";
	int variableIndexArraySize = variableIndexArray.size();

	PyObject *parameters;
	CDummyClient *targetClient;

	for( int i = _startIndex; i <= _endIndex; i++ )
	{
		// ��� �ε�
		for( int j = 0; j < variableIndexArraySize; j++ )
		{
			int *pList = (int *)_vaList;
			pList[variableIndexArray[j]] = i;
		}

		parameters = Py_VaBuildValue( format, _vaList );

		if( i == MAINSCRIPT )
		{
			if( mainScriptmodule != NULL )
			{
				module = mainScriptmodule;
			}
			else
			{		
				dlg->addMainLog( L"[���� - CallFunction] ���� ��ũ��Ʈ�� �����ϴ�." );
				dlg->showMainLog();
				continue;
			}
		}
		else
		{
			targetClient =  GetDummyClientByIndex( i );
			if( targetClient != NULL )
			{
				module = targetClient->module;
			}
			else
			{
				CString logStr;
				logStr.Format( L"[���� - CallFunction] %d Ŭ���̾�Ʈ�� �����ϴ�.", i );
				dlg->addMainLog( logStr );
				dlg->showMainLog();
				continue;
			}
		}
			
		// �Լ� �ε�
		PyGILState_STATE gilState;
		gilState = PyGILState_Ensure();

		PyObject *function = PyObject_GetAttrString(module, _funcName);

		if( function != NULL )
		{ 
			PyObject_CallObject(function, parameters );
			Py_DECREF(parameters);
			PyGILState_Release( gilState );
		}
		else
		{
			targetClient->addLog( L"[���� - CallFunction] �Լ� �ε� ����." );
			PyErr_Clear();	
			PyGILState_Release( gilState );
			continue;  
		}
	}
	
}


// �׿�
int CDummyClientManager::GetCurIndex()
{
	return m_curIndex;
}

bool CDummyClientManager::SetIndexRange( int _startIndex, int _endIndex )
{
	if( _startIndex < m_highestIndex )
	{
		return false;
	}
	else
	{
		m_curIndex = _startIndex;
		m_maxLimitIndex = _endIndex;
		return true;
	}
}

void CDummyClientManager::SetClientInfoSetting( CLIENT_INFO _clientInfoSetting )
{
	CtesttoolDlg* dlg = (CtesttoolDlg*)AfxGetApp()->m_pMainWnd;
	dlg->addMainLog( L"BeforeInfo" );
	dlg->addMainLog( m_clientInfoSetting.GetInfoString() );

	m_clientInfoSetting = _clientInfoSetting;

	dlg->addMainLog( L"NewInfo" );
	dlg->addMainLog( _clientInfoSetting.GetInfoString() );
	dlg->showMainLog();
}

void CDummyClientManager::DeleteThreadEndedClient()
{
	for( unsigned i = 0; i < dummyClientToDeleteList.size(); i++ )
	{
		CDummyClient *dummyClient = dummyClientToDeleteList[i];
		if( dummyClient->threadState == THREAD_NONE || dummyClient->threadState == THREAD_END )
		{
			delete dummyClient;
			std::vector<CDummyClient *>::iterator iter = dummyClientToDeleteList.begin() + i;
			dummyClientToDeleteList.erase( iter );
			i--;
		}
	}
}