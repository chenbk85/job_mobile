/* file : ReadMe.txt
Coder : by icandoit ( mech12@nate.com)
Date : 2007-08-24 12:14:00
comp.: jgame.co.kr
title : 
desc : 

Mail 문서는 다음과 같다.
z:\job_taebak\src\base\Interface\net\jINet_OGS.txt

*/





//--------------------------------------------------------------------------
p2p용 샘플 예제
//--------------------------------------------------------------------------




struct jP2P_PlugIn_TestClient : public jIPlugIn_Connection
{
	JNET_PLUGIN_SINGTONE_DECL(jP2P_PlugIn_TestClient);
public:
	jDECLARE_RTTIOBJ(jP2P_PlugIn_TestClient);
	virtual void	OnIoRead(jIPacketSocket_IOCP*pCaller)			
	{
		jERROR(_T("jP2P_PlugIn_TestClient::()"));
	}
	virtual void	OnIoWrote(jIPacketSocket_IOCP* pS)			
	{
	}
	virtual void	OnIoConnected(jIPacketSocket_IOCP* pS);
	virtual void	OnIoDisconnected(jIPacketSocket_IOCP* pS);
	virtual void Start();
	virtual void Stop();

};



jDEFINE_RTTIOBJ_BY_SCOPE(jP2P_PlugIn_TestClient,jNet, 1,1);
JNET_PLUGIN_SINGTONE_DEFINE(jP2P_PlugIn_TestClient);



void jP2P_PlugIn_TestClient::Start()
{
	jP2P_PlugIn_TestClient::Set(this);
}

void jP2P_PlugIn_TestClient::Stop()
{
	jP2P_PlugIn_TestClient::Set(0);
}
void	jP2P_PlugIn_TestClient::OnIoConnected(jIPacketSocket_IOCP* pS)	 
{
	jASSERT0(jP2P_PlugIn_TestClient::Get());
	fname_t buf;
	GetjILogLT(jx(jNet),jx(CLIENT))->Log(_T("jP2P_PlugIn_TestClient::OnIoConnected : %s(sockType=%d)"
		, pS->GetAddressString(buf)
		,pS->GetType()
		);
}

void	jP2P_PlugIn_TestClient::OnIoDisconnected(jIPacketSocket_IOCP* pS)
{
	jASSERT0(jP2P_PlugIn_TestClient::Get());
	fname_t buf;
	GetjILogLT(jx(jNet),jx(CLIENT))->Log(_T("jP2P_PlugIn_TestClient::OnIoDisconnected : %s(sockType=%d)"
		, pS->GetAddressString(buf)
		,pS->GetType()
		);
}






//--------------------------------------------------------------------------
// tcp서버용 샘플
//--------------------------------------------------------------------------





struct _LoginServerUserInfo
{
	const char* m_szRealAdress;
	std::string m_sRealIP;
	int m_iRealPort;
	std::string m_sVirtualAddress;
};


// CIocp를 상속 받습니다.
class jTcpServerPlugIn_Field : public jIPlugIn_Server_IOCP
{
public :
	JNET_PLUGIN_SINGTONE_DECL(jTcpServerPlugIn_Field);
	jDECLARE_RTTIOBJ(jTcpServerPlugIn_Field);

	VOID OnIoRead(jIPacketSocket_IOCP* pSocket,DWORD dwProtocol, BYTE *pReadBuff, DWORD dwPacketLength)	
	{	
		jERROR(_T("jTcpServerPlugIn_Field::OnIoRead()"));
	}
	virtual VOID OnIoWrote(jIPacketSocket_IOCP*pObject, DWORD dwDataLength);
	virtual VOID OnIoConnected(jIPacketSocket_IOCP* pPlugIn);
	virtual VOID OnIoDisconnected(jIPacketSocket_IOCP*);
	virtual void Start()
	{
		jTcpServerPlugIn_Field::Set(this);
	}
	virtual void Stop()
	{
		m_TcpUsers.clear();
		jTcpServerPlugIn_Field::Set(0);
	}

	struct jTCP_USER : public _LoginServerUserInfo
	{
		jIPacketSocket_IOCP* pSocket;
	};
	// jTCP_USER를 관리하는 map
	jLIST_TYPEDEF_map(jIPacketSocket_IOCP*, jTCP_USER, m_TcpUsers);

	void SendString_AllUser_TCP(cstr szMsg,jIPacketSocket_IOCP* pSockOwner);
};




jDEFINE_RTTIOBJ_BY_SCOPE(jTcpServerPlugIn_Field,jNet, 1,1);
JNET_PLUGIN_SINGTONE_DEFINE(jTcpServerPlugIn_Field);



// CIocp의 가상함수들
VOID jTcpServerPlugIn_Field::OnIoConnected(jIPacketSocket_IOCP *pObject)
{
	jLOG(_T("jTcpServerPlugIn_Field::OnIoConnected"));
	jIPString buf;
	m_TcpUsers[pObject].pSocket=pObject;
	m_TcpUsers[pObject].m_sRealIP= pObject->GetAddressString(buf);
	m_TcpUsers[pObject].m_iRealPort = pObject->GetPort();
	pObject->SetUserData(&m_TcpUsers[pObject]);

}

VOID jTcpServerPlugIn_Field::OnIoDisconnected(jIPacketSocket_IOCP *pObject)
{
	if(!pObject) return;
	m_TcpUsers_it it = m_TcpUsers.find(pObject);
	assert(it!=m_TcpUsers.end());
	m_TcpUsers.erase(it);
	jLOG(_T(" jTcpServerPlugIn_Field::OnIoDisconnected"));
}


using namespace nMech::nNET::nCentral;


VOID jTcpServerPlugIn_Field::OnIoWrote(jIPacketSocket_IOCP* pSocket, DWORD dwDataLength)
{
	GetjILogLT(jx(jNet),jx(CLIENT))->Log(_T(" jTcpServerPlugIn_Field::OnIoWrote"));

}

void jTcpServerPlugIn_Field::SendString_AllUser_TCP(cstr szMsg,jIPacketSocket_IOCP* pSock)
{
	nUNI::StringConvertBuffer<256> wzBuf(szMsg);
	wzBuf.update();
	m_TcpUsers_it itUser = m_TcpUsers.find(pSock);
	jTCP_USER* pUser =0;
	if(itUser!=m_TcpUsers.end())
	{
		pUser = &itUser->second;
	}

	m_TcpUsers_it it = m_TcpUsers.begin(),ie= m_TcpUsers.end();
	BYTE buf[1024];
	cstr szOwnerRealIp =  pUser? pUser->m_sRealIP.c_str() : "server R");
	cstr szOwnerVirtualIP = pUser? pUser->m_sVirtualAddress.c_str() : "server V");
	jPacket_Base pk = WRITE_C_ECHO(buf, szOwnerRealIp, wzBuf.getW() );
	for( ; it!=ie ;++it)
	{

		using namespace nMech::nNET::nCentral;
		jTCP_USER* pUser = &it->second;
		if(pUser->pSocket==pSock) continue;
		pUser->pSocket->WritePacket(&pk );
	}
}

