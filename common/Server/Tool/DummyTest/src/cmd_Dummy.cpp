#include "stdafx.h"
#include "testtoolDlg.h"
#include "DummyClientManager.h"
 

// 클라이언트 환경 설정
jCONSOLE_CMD_AUTO(dummy,get_env,0,"get env for dummy","")
{
	CString str = g_dummyClientManager->m_clientInfoSetting.GetInfoString();		// 클라이언트 셋팅값 설정
	jLOG(str);
	return true;
}

jCONSOLE_CMD_AUTO(dummy,set_env,0,"set env for dummy","< dname_tag > <start_dindex> <end_dindex> <pwd> <ip> <port> <python>")
{
	// X()는 <생략불가능 param>
	// Y()는 [생략가능 param]에 대응된다.
	#define jCONSOLE_PARAM_set_env(X,Y) X(dname_tag,tcstr) X(start_dindex,int) X(end_dindex,int) X(pwd,tcstr) X(ip,tcstr) X(port,int) X(python,tcstr) 
	jCONSOLE_PARAM_END(set_env);

	g_dummyClientManager->SetIndexRange(  start_dindex, end_dindex );
	CLIENT_INFO ci;

	ci.dNameTag=dname_tag;			// 더미 클라이언트 태그 
	ci.dPwd=pwd;				// 더미 클라이언트 패스워드
	ci.dScriptFileName=python;	// 더미 클라이언트 스크립트 파일 이름
	ci.dServerIP=ip;			// 더미 클라이언트 서버 IP
	ci.m_iServerPort=port;			// 더미 클라이언트 서버 Port

	g_dummyClientManager->SetClientInfoSetting( ci );		// 클라이언트 셋팅값 설정
	return true;
}



// 클라이언트 생성

jCONSOLE_CMD_AUTO(dummy,Create,0,"create dummy","<dummy_count>")
{
	// X()는 <생략불가능 param>
	// Y()는 [생략가능 param]에 대응된다.
	#define jCONSOLE_PARAM_Create(X,Y) X(dummy_count,int) 
	jCONSOLE_PARAM_END(Create);

	int createCount = 0;
	int startIndex = g_dummyClientManager->GetCurIndex();
	createCount = g_dummyClientManager->MakeDummyClient( dummy_count );
	int endIndex = startIndex + createCount;

	CtesttoolDlg* dlg = (CtesttoolDlg*)AfxGetApp()->m_pMainWnd;
	dlg->AddListBox( startIndex, endIndex );
	CString logStr;
	logStr.Format( L"더미 클라이언트 생성 완료 (요청 %d개 / 실제 생성 %d개)", dummy_count, createCount );
	dlg->addMainLog( logStr );
	dlg->showMainLog();

	return true;
}
	


// 클라이언트 삭제

jCONSOLE_CMD_AUTO(dummy, Delete, 0, "delete dummy","<_startIndex> [_endIndex=-1]")
{
	// X()는 <생략불가능 param>
	// Y()는 [생략가능 param]에 대응된다.
	#define jCONSOLE_PARAM_Delete(X,Y) X(_startIndex,int) Y(_endIndex,int,-1) 
	jCONSOLE_PARAM_END(Delete);

	if(_endIndex==-1)
		_endIndex = _startIndex;

	g_dummyClientManager->DeleteDummyClient( _startIndex, _endIndex );	
	return true;
}



// 클라이언트 접속

jCONSOLE_CMD_AUTO(dummy,Connect,0,"Connect dummy","<_startIndex> [_endIndex=-1] [_per=1] [_delayMSec=20]")
{
	// X()는 <생략불가능 param>
	// Y()는 [생략가능 param]에 대응된다.
	#define jCONSOLE_PARAM_Connect(X,Y) X(_startIndex,int) Y(_endIndex,int,-1) Y(_per,int,1) Y(_delayMSec,int,20)
	jCONSOLE_PARAM_END(Connect);

	if(_endIndex==-1)
		_endIndex = _startIndex;

	g_dummyClientManager->Connect( _startIndex, _endIndex, _per, _delayMSec );

	return true;
}

jCONSOLE_CMD_AUTO(dummy, ConnectAll, 0, "Connect All dummy","[_per=1] [_delayMSec=20]")
{
	// X()는 <생략불가능 param>
	// Y()는 [생략가능 param]에 대응된다.
	#define jCONSOLE_PARAM_ConnectAll(X,Y) Y(_per,int,1) Y(_delayMSec,int,20)
	jCONSOLE_PARAM_END(ConnectAll);

	g_dummyClientManager->ConnectAllClient( _per, _delayMSec );

	return true;
}



// 클라이언트 접속 해제

jCONSOLE_CMD_AUTO(dummy,Disconnect,0,"Disconnect dummy","<_startIndex> [_endIndex=-1] [_per=1] [_delayMSec=20]")
{
	// X()는 <생략불가능 param>
	// Y()는 [생략가능 param]에 대응된다.
	#define jCONSOLE_PARAM_Disconnect(X,Y) X(_startIndex,int) Y(_endIndex,int,-1) Y(_per,int,1) Y(_delayMSec,int,20)
	jCONSOLE_PARAM_END(Disconnect);

	if(_endIndex==-1)
		_endIndex = _startIndex;

	g_dummyClientManager->Disconnect( _startIndex, _endIndex, _per, _delayMSec );

	return true;
}

jCONSOLE_CMD_AUTO(dummy, DisconnectAll, 0, "Disconnect All dummy","[_per=1] [_delayMSec=20]")
{
	// X()는 <생략불가능 param>
	// Y()는 [생략가능 param]에 대응된다.
	#define jCONSOLE_PARAM_DisconnectAll(X,Y) Y(_per,int,1) Y(_delayMSec,int,20)
	jCONSOLE_PARAM_END(Disconnect);

	g_dummyClientManager->DisconnectAllClient( _per, _delayMSec );

	return true;
}



// 클라이언트 상태 출력

jCONSOLE_CMD_AUTO(dummy, PrintStatus, 0, "PrintStatus dummy","<_startIndex> [_endIndex=-1]")
{
	// X()는 <생략불가능 param>
	// Y()는 [생략가능 param]에 대응된다.
	#define jCONSOLE_PARAM_PrintStatus(X,Y) X(_startIndex,int) Y(_endIndex,int,-1) 
	jCONSOLE_PARAM_END(PrintStatus);

	if(_endIndex==-1)
		_endIndex = _startIndex;

	g_dummyClientManager->PrintClientStatus( _startIndex, _endIndex );	

	return true;
}

	

// 메인스크립트 함수 호출

jCONSOLE_CMD_AUTO(dummy, CallMainPython, 0, "CallMainPython dummy","<_funcName> <_format> [_arg1] [_arg2] [_arg3] [_arg4] [_arg5] [_arg6] [_arg7] [_arg8] [_arg9] [_arg10]")
{
	CString _funcName = arg[0].c_str();
	CString _format = arg[1].c_str();

	int argSize = arg.size();
	int fixedArgSize = 2;
	int varArgSize = argSize - fixedArgSize;
	int *valist = new int[varArgSize];

	if( _format.GetLength() == varArgSize )
	{
		for( int i = 0; i < varArgSize; i++ )
		{
			const TCHAR *value = arg[i + fixedArgSize].c_str();
			TCHAR format = _format.GetAt( i );
			switch( format )
			{
			case L'i':
				valist[i] = jt_atoi( value );
				break;
			case L's':
				valist[i] = (int)value;
				break;
			}
		}
		g_dummyClientManager->CallMainScriptFunctionVa( _funcName, _format, ( va_list )valist ); 
	}
	else
	{
		//에러처리
	}
	delete[] valist;
	return true;
}


// 클라이언트 스크립트 함수 호출

jCONSOLE_CMD_AUTO(dummy, CallPython, 0, "CallPython dummy","<_funcName> <_format> [_arg1] [_arg2] [_arg3] [_arg4] [_arg5] [_arg6] [_arg7] [_arg8] [_arg9] [_arg10]")
{
	enum{e_funcname,e_format,e_arg_start};
	vector<astring> arg1;
	for(unsigned int i =0; i< arg.size();++i)
	{
		arg1.push_back(jA(arg[i]));
	}

	CStringA _format = arg1[e_format].c_str();

	int argSize = arg1.size();
	int varArgSize = argSize - e_arg_start;
	int *valist = new int[varArgSize];

	if( _format.GetLength() == varArgSize )
	{
		for( int i = 0; i < varArgSize; i++ )
		{
			acstr value = arg1[i + e_arg_start].c_str();
			char format = _format.GetAt( i );
			switch( format )
			{
			case 'i':
			case 'v':
				valist[i] = ja_atoi( value );
				break;
			case 's':
				valist[i] = (int)value;
				break;
			}
		}
		g_dummyClientManager->CallFunctionVa( arg1[e_funcname].c_str(), _format, ( va_list )valist );
	}
	else
	{
		//에러처리
	}
	delete[] valist;
	return true;
}

jCONSOLE_CMD_AUTO(dummy, CallPythonMultiple, 0, "CallPython dummy","<_startIndex> <_endIndex> <_funcName> <_format> [_arg1] [_arg2] [_arg3] [_arg4] [_arg5] [_arg6] [_arg7] [_arg8] [_arg9] [_arg10]")
{
	enum{e_startindex,e_endindex,e_funcname,e_format,e_arg_start};
	vector<astring> arg1;
	for(unsigned int i =0; i< arg.size();++i)
	{
		arg1.push_back(jA(arg[i]));
	}

	int _startIndex = ja_atoi( arg1[e_startindex].c_str() );
	int _endIndex = ja_atoi( arg1[e_endindex].c_str() );
	CStringA _format = arg1[e_format].c_str();

	int argSize = arg1.size();
	int varArgSize = argSize - e_arg_start;
	int *valist = new int[varArgSize];

	if( _format.GetLength() == varArgSize )
	{
		for( int i = 0; i < varArgSize; i++ )
		{
			acstr value = arg1[i + e_arg_start].c_str();
			char format = _format.GetAt( i );
			switch( format )
			{
			case 'i':
			case 'v':
				valist[i] = ja_atoi( value );
				break;
			case 's':
				valist[i] = (int)value;
				break;
			}
		}
		g_dummyClientManager->CallFunctionVa( _startIndex, _endIndex, arg1[e_funcname].c_str(), _format, ( va_list )valist );
	}
	else
	{
		//에러처리
	}
	delete[] valist;
	return true;
}

/*
s
i (integer) [int] 
b (integer) [char] 
h (integer) [short int] 
l (integer) [long int] 
B (integer) [unsigned char] 
H (integer) [unsigned short int] 
I (integer/long) [unsigned int] 
k (integer/long) [unsigned long] 
L (long) [PY_LONG_LONG] 
K (long) [unsigned PY_LONG_LONG] 
n (int) [Py_ssize_t] 
d (float) [double] 
f (float) [float] 
D (complex) [Py_complex *] 
*/






