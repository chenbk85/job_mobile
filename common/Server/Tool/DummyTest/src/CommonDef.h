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
	int m_iIndex;					// 더미 클라이언트 인덱스
	CString dNameTag;			// 더미 클라이언트 태그 
	CString dPwd;				// 더미 클라이언트 패스워드
	CString dScriptFileName;	// 더미 클라이언트 스크립트 파일 이름
	CString dServerIP;			// 더미 클라이언트 서버 IP
	UINT m_iServerPort;			// 더미 클라이언트 서버 Port
	CString dState;				// 더미 클라이언트 상태

	CString dName;				// 더미 클라이언트 이름 ( 해당값이 설정되지 않았을 경우 dNameTag + m_iIndex를 리턴한다. )

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

	CString GetName()			// 더미 클라이언트 이름 getter 함수 (이름을 얻을때는 반드시 이 함수를 통할것)
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

	