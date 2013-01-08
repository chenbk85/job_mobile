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
	PyObject  *mainScriptmodule;										// ���̽� ���� ��ũ��Ʈ
	PyThreadState *mainThreadState;										// ���̽� ���� ������ ������Ʈ	(��Ƽ������ ȯ�� ���̽� �Ӻ����� ���)

	std::map< int, CDummyClient* > dummyClientMapByIndex;				// �� - ( Ŭ���̾�Ʈ �ε���, Ŭ���̾�Ʈ ��ü ������) 
	std::map< std::tstring, CDummyClient* > dummyClientMapByName;		// �� - ( Ŭ���̾�Ʈ �̸�, Ŭ���̾�Ʈ ��ü ������) 
	std::vector<CDummyClient *> dummyClientToDeleteList;				// ���� �������� ���� (������ ���Ḧ ��ٸ��� �ִ�) Ŭ���̾�Ʈ�� ����Ʈ

	CLIENT_INFO m_clientInfoSetting;									// ������ ����� Ŭ���̾�Ʈ ���ð�
	int m_highestIndex;													// m_curIndex�� ���� ���Ҵ� �ε��� ( ���� m_curIndex�� �缳�� �ϴ���, m_highestIndex ���ٴ� ���ų� ���ƾ� ��(�ߺ�����) )
	int m_curIndex;														// �̹��� ������ Ŭ���̾�Ʈ �ε���
	int m_maxLimitIndex;												// ���������� �ε��� ����Ʈ

public:
	CDummyClientManager(void);
	~CDummyClientManager(void);

	// ���� ��ũ��Ʈ �ε�
	bool SetMainScript();

	// Ŭ���̾�Ʈ ����
	int MakeDummyClient( int _count );									// ���������� m_clientInfoSetting ���
	int MakeDummyClient( int _count, CLIENT_INFO _clientInfo );			// Ŭ���̾�Ʈ ����. ���� ������ ������ return.

	// Ŭ���̾�Ʈ ����
	int DeleteDummyClient( int _startIndex, int _endIndex );

	// Ŭ���̾�Ʈ ���
	CDummyClient *GetDummyClientByIndex( int _index );					// index�� Ŭ���̾�Ʈ�� ���
	CDummyClient *GetDummyClientByName( CString _name );				// name���� Ŭ���̾�Ʈ ���

	// Ŭ���̾�Ʈ ����
	int ConnectAllClient( int _per, int _delayMSec );								// ��� Ŭ���̾�Ʈ�� ���ӽõ��Ѵ� ex) 10������ 0.1�ʰ��� ������ => ConnectAllClient( 10, 100 )
	int Connect( int _startIndex, int _endIndex, int _per, int _delayMSec );		// �ش� ������ Ŭ���̾�Ʈ�� ���� �õ��Ѵ�
	
	// Ŭ���̾�Ʈ ���� ����
	int DisconnectAllClient( int _per, int _delayMSec );							// ��� Ŭ���̾�Ʈ�� ������ �����Ѵ�
	int Disconnect( int _startIndex, int _endIndex, int _per, int _delayMSec );		// �ش� ������ Ŭ���̾�Ʈ�� ���� �����Ѵ�

	// Ŭ���̾�Ʈ ���� ���
	void PrintClientStatus( int _startIndex, int _endIndex );						// �ش� ������ Ŭ���̾�Ʈ ���¸� ����Ѵ�.

	// Ŭ���̾�Ʈ ��ũ��Ʈ �Լ� ȣ��
	void CallMainScriptFunction( CString _funcName, CString _format, ... );
	void CallMainScriptFunctionVa( CString _funcName, CString _format, va_list _vaList );
	void CallFunction( int _startIndex, int _endIndex, CString _funcName, CString _format, ... );
	void CallFunctionVa( acstr _funcName, CStringA _format, va_list _vaList );
	void CallFunctionVa( int _startIndex, int _endIndex, acstr _funcName, CStringA _format, va_list _vaList );
	
	
	// �׿�
	int GetCurIndex();
	bool SetIndexRange( int _startIndex, int _endIndex );				// ���� �����Ҷ� ���� index�� ������ ����
	void SetClientInfoSetting( CLIENT_INFO _clientInfoSetting );		// Ŭ���̾�Ʈ ���ð� ����

	void DeleteThreadEndedClient();										// ���� �������� ���� Ŭ���̾�Ʈ�� ��ȸ�ϸ�, �����尡 ����� Ŭ���̾�Ʈ�� �����Ѵ�
};

extern CDummyClientManager *g_dummyClientManager;
