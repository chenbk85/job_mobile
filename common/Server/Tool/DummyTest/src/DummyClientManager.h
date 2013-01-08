#pragma once
#include "DummyClient.h"
#include "Python.h"
#include "CommonDef.h"

#include <map>
#include <vector>

#define MAINSCRIPT -99


class CDummyClientManager
{
public:
	
//private:
	//python
	PyObject  *mainScriptmodule;										// 파이썬 메인 스크립트
	PyThreadState *mainThreadState;										// 파이썬 메인 스레드 스테이트	(멀티스레드 환경 파이썬 임베딩에 사용)

	std::map< int, CDummyClient* > dummyClientMapByIndex;				// 맵 - ( 클라이언트 인덱스, 클라이언트 객체 포인터) 
	std::map< std::tstring, CDummyClient* > dummyClientMapByName;		// 맵 - ( 클라이언트 이름, 클라이언트 객체 포인터) 
	std::vector<CDummyClient *> dummyClientToDeleteList;				// 아직 지워지지 않은 (스레드 종료를 기다리고 있는) 클라이언트의 리스트

	CLIENT_INFO m_clientInfoSetting;									// 생성에 사용할 클라이언트 세팅값
	int m_highestIndex;													// m_curIndex중 가장 높았던 인덱스 ( 추후 m_curIndex를 재설정 하더라도, m_highestIndex 보다는 같거나 높아야 함(중복방지) )
	int m_curIndex;														// 이번에 생성될 클라이언트 인덱스
	int m_maxLimitIndex;												// 생성가능한 인덱스 리미트

public:
	CDummyClientManager(void);
	~CDummyClientManager(void);

	// 메인 스크립트 로드
	bool SetMainScript();

	// 클라이언트 생성
	int MakeDummyClient( int _count );									// 설정값으로 m_clientInfoSetting 사용
	int MakeDummyClient( int _count, CLIENT_INFO _clientInfo );			// 클라이언트 생성. 실제 생성된 갯수를 return.

	// 클라이언트 삭제
	int DeleteDummyClient( int _startIndex, int _endIndex );

	// 클라이언트 얻기
	CDummyClient *GetDummyClientByIndex( int _index );					// index로 클라이언트를 얻기
	CDummyClient *GetDummyClientByName( CString _name );				// name으로 클라이언트 얻기

	// 클라이언트 접속
	int ConnectAllClient( int _per, int _delayMSec );								// 모든 클라이언트를 접속시도한다 ex) 10개마다 0.1초간의 딜레이 => ConnectAllClient( 10, 100 )
	int Connect( int _startIndex, int _endIndex, int _per, int _delayMSec );		// 해당 구간의 클라이언트를 접속 시도한다
	
	// 클라이언트 접속 해제
	int DisconnectAllClient( int _per, int _delayMSec );							// 모든 클라이언트의 접속을 해제한다
	int Disconnect( int _startIndex, int _endIndex, int _per, int _delayMSec );		// 해당 구간의 클라이언트를 접속 해제한다

	// 클라이언트 상태 출력
	void PrintClientStatus( int _startIndex, int _endIndex );						// 해당 구간의 클라이언트 상태를 출력한다.

	// 클라이언트 스크립트 함수 호출
	void CallMainScriptFunction( CString _funcName, CString _format, ... );
	void CallMainScriptFunctionVa( CString _funcName, CString _format, va_list _vaList );
	void CallFunction( int _startIndex, int _endIndex, CString _funcName, CString _format, ... );
	void CallFunctionVa( acstr _funcName, CStringA _format, va_list _vaList );
	void CallFunctionVa( int _startIndex, int _endIndex, acstr _funcName, CStringA _format, va_list _vaList );
	
	
	// 그외
	int GetCurIndex();
	bool SetIndexRange( int _startIndex, int _endIndex );				// 새로 생성할때 사용될 index의 범위를 설정
	void SetClientInfoSetting( CLIENT_INFO _clientInfoSetting );		// 클라이언트 셋팅값 설정

	void DeleteThreadEndedClient();										// 아직 지워지지 않은 클라이언트를 순회하며, 스래드가 종료된 클라이언트를 삭제한다
};

extern CDummyClientManager *g_dummyClientManager;
