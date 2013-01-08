/* file : PlugIn_ToFrontEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToFrontEnd.h"
#include "../protocal/PT_TestServer_Enum.h"
using namespace nMech::nNET::nTestServer;

PlugIn_ToFrontEnd* g_pCurrPlugInFE=0;

jPLUGIN_FRONT_END_cpp_code_Start(PlugIn_ToFrontEnd,AqTestClientNode);
{
	m_pMM = nEVENT::jIMsgManager::Get(jS(test_Server), true);

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
	nswb256_t buf;
	send_all(nTestServer::WRITE_S_ECHO(buf, 0 , jW(str.c_str())), 0 );	
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

	jLOG(_T("OnIoConnected = %s did=%d"), pS->GetAddressString(szIP),pUser->iHandle);
	pS->WritePacket(&WRITE_S_HELLO(buf) );
	jLOG(jFUNC1 _T("current user count = %d"), this->size() );

}


VOID PlugIn_ToFrontEnd::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	if(!pS) return;
	fname_t szIP;pS->GetIP(szIP);
	AqTestClientNode* pUser = get_user(pS);
	if(!pUser)
	{
		jWARN(_T(" pUser==null"));
		return;
	}

	//jLOG(jFUNC1 _T("current user= %d: %s(%s)"), this->size() , pUser->m_szID ,pUser->GetTypeName());
	erase(pUser);
	jLOG(jFUNC1 _T("current user count = %d"), this->size() );
}
