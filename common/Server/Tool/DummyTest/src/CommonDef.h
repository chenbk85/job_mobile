#pragma once

typedef enum _CLIENT_CREATE_ERROR
{
	CLIENT_CREATE_ERROR_NONE = 0,
	CLIENT_CREATE_ERROR_THREAD_CREATE_FAILED,
	CLIENT_CREATE_ERROR_SCRIPT_FILE_OPEN_FAILED,
	CLIENT_CREATE_ERROR_SCRIPT_FUNCTION_LOAD_FAILED,
	CLIENT_CREATE_ERROR_INDEX_ALREADY_EXIST_FAILED,
} CLIENT_CREATE_ERROR;


struct CLIENT_INFO
{
	int m_iIndex;					// ���� Ŭ���̾�Ʈ �ε���
	CString dNameTag;			// ���� Ŭ���̾�Ʈ �±� 
	CString dPwd;				// ���� Ŭ���̾�Ʈ �н�����
	CString dScriptFileName;	// ���� Ŭ���̾�Ʈ ��ũ��Ʈ ���� �̸�
	CString dServerIP;			// ���� Ŭ���̾�Ʈ ���� IP
	UINT m_iServerPort;			// ���� Ŭ���̾�Ʈ ���� Port
	CString dState;				// ���� Ŭ���̾�Ʈ ����

	CString dName;				// ���� Ŭ���̾�Ʈ �̸� ( �ش簪�� �������� �ʾ��� ��� dNameTag + m_iIndex�� �����Ѵ�. )

	CLIENT_INFO()
	{
		m_iIndex = -1;
		dNameTag = pv_ClientID->Get_cstr();
		dPwd = pv_ClientPassword->Get_cstr();
		dScriptFileName = pv_PythonScript->Get_cstr();
		dServerIP = pv_ServerIP->Get_cstr();
		m_iServerPort = pv_ServerPort->Get_int();
		dState = L"";
		dName = L"";
	}

	CString GetName()			// ���� Ŭ���̾�Ʈ �̸� getter �Լ� (�̸��� �������� �ݵ�� �� �Լ��� ���Ұ�)
	{
		if( dName.GetLength() == 0 )
		{
			CString nameStr;
			nameStr.Format( L"%s%d", dNameTag, m_iIndex );
			return nameStr;
		}
		else
		{
			return dName;
		}
	}

	CString GetInfoString()
	{
		CString infoString;
		infoString.Format( L"m_iIndex : %d\r\n dNameTag : %s\r\n dPwd : %s\r\n dScriptFileName : %s\r\n dServerIP : %s\r\n m_iServerPort : %d\r\n dName : %s\r\n", 
							 m_iIndex, dNameTag, dPwd, dScriptFileName, dServerIP, m_iServerPort, GetName() );
		return infoString;
	}
};

	