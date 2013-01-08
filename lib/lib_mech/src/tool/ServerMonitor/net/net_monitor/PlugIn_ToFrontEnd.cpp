/* file : PlugIn_ToFrontEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToFrontEnd.h"
#include "../protocal/PT_MonitorServer_Enum.h"
using namespace nMech::nNET::nMonitorServer;

PlugIn_ToFrontEnd* g_pCurrPlugInFE=0;

jPLUGIN_FRONT_END_cpp_code_Start(PlugIn_ToFrontEnd,jAgentNode);
{
	m_pMM = nEVENT::jIMsgManager::Get(jS(test_Server), true);

}
jPLUGIN_cpp_code_Stop(PlugIn_ToFrontEnd);
{
	if(m_pMM){m_pMM->clear();m_pMM=0;}


}
jPLUGIN_FRONT_END_cpp_code_End(PlugIn_ToFrontEnd,jAgentNode);


PlugIn_ToFrontEnd::PlugIn_ToFrontEnd()
{
	g_pCurrPlugIn = g_pCurrPlugInFE= this;
}

bool PlugIn_ToFrontEnd::ParseCmd(tcstr szCommand)
{
	//nswb1024_t buf;
	std::tstring str = _T("FromTS:");
	str += szCommand;
	nswb256_t buf;
	send_all(nMonitorServer::WRITE_S_ECHO(buf, 0 , jW(str.c_str())), 0 );	
	return false;
}

void jSocketDebugger(jIPacketSocket_IOCP* pS)
{

}

// CIocp의 가상함수들
VOID PlugIn_ToFrontEnd::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	nswb256_t buf;
	jAgentNode* pUser = push_back_if_not_found(pS);
	jLOG(_T("OnIoConnected = %s did=%d"), pS->GetAddressString(pUser->m_szIP),pUser->iHandle);
	pS->WritePacket(&WRITE_S_HELLO(buf) );
}


VOID PlugIn_ToFrontEnd::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	if(!pS) return;
	jAgentNode* pUser = get_user(pS);
	if(!pUser)
	{
		jWARN(_T(" pUser==null"));
		return;
	}
	nswb256_t buf;
	jLOG(jFUNC1 _T("user: %s(%s)"), pUser->m_szComputerName ,pUser->m_szIP);
	Get_jIServerMonitor()->OnIoDisconnected(pUser->m_uid, pS);
	erase(pUser);
}
