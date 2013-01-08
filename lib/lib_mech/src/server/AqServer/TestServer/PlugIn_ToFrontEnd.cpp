/* file : PlugIn_ToFrontEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToFrontEnd.h"
#include <boost/bind.hpp>
#include "network/protocal/PT_TestServer_Enum.h"
using namespace nMech::nNET::nTestServer;

PlugIn_ToFrontEnd* g_pCurrPlugInFE=0;

jPLUGIN_FRONT_END_cpp_code_Start(PlugIn_ToFrontEnd,AqTestClientNode);
{
	m_pMM = nEVENT::jIMsgManager::Get(jS(TestServer), true);

}
jPLUGIN_cpp_code_Stop(PlugIn_ToFrontEnd);
{
	if(m_pMM){m_pMM->clear();m_pMM=0;}


}
jPLUGIN_FRONT_END_cpp_code_End(PlugIn_ToFrontEnd,AqTestClientNode);


PlugIn_ToFrontEnd::PlugIn_ToFrontEnd()
{
	g_pCurrPlugIn = g_pCurrPlugInFE= this;
}

bool PlugIn_ToFrontEnd::ParseCmd(tcstr szCommand)
{
	//nswb1024_t buf;
	std::tstring str = _T("FromTS:");
	str += szCommand;
	net_string256 sendStr = str.c_str();
	nswb256_t buf;
	send_all(nTestServer::WRITE_TS_ECHO(buf, 0,sendStr ), 0 );	
	return false;
}

void jSocketDebugger(jIPacketSocket_IOCP* pS)
{

}

// CIocp의 가상함수들
VOID PlugIn_ToFrontEnd::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	nswb256_t buf;
	AqTestClientNode* pUser = push_back_if_not_found(pS);
	fname_t szIP;

	GetjILog()->Log(_T("OnIoConnected = %s did=%d"), pS->GetAddressString(szIP),pUser->iHandle);
	pS->WritePacket(&WRITE_TS_HELLO(buf,pUser->iHandle , pv_TEST_ID_NAME->Get_cstr()) );
}


VOID PlugIn_ToFrontEnd::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	if(!pS) return;
	fname_t szIP;pS->GetIP(szIP);
	AqTestClientNode* pUser = get_user(pS);
	if(!pUser)
	{
		GetjILog()->Warning(jFUNC1 _T(" pUser==null"));
		return;
	}

	if(pUser->IsTestClient())
	{
		nswb256_t buf;
		tname256_t szBuf;
		jt_sprintf(szBuf ,_T("^logout TestClient:%u"),pUser->iHandle);
		jFOR_EACH(m_listAqMonitor , boost::bind(&AqTestClientNode::Write_Packet, _1,WRITE_TS_ECHO(buf,0,szBuf)) );
	}
	else if(pUser->IsAqMonitor())
	{
		m_listAqMonitor_it it = jFIND(m_listAqMonitor,pUser);
		if(it!=m_listAqMonitor.end())
		{
			m_listAqMonitor.erase(it);
		}
	}

	nswb256_t buf;
	GetjILog()->Log(jFUNC1 _T("user: %s(%s)"), pUser->m_szID ,pUser->GetTypeName());
	erase(pUser);
}
