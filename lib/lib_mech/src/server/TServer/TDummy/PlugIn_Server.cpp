/* file : PlugIn_Server.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TDummy.h"
#include "PlugIn_Server.h"

jPLUGIN_CPP_CODE_START_Server(PlugIn_Server)
{

}
jPLUGIN_CPP_CODE_STOP(PlugIn_Server)
{

}
jPLUGIN_CPP_CODE_END_Server(PlugIn_Server);


PlugIn_Server::PlugIn_Server()
{
}

bool PlugIn_Server::ParseCmd(tcstr szCommand)
{
	jPS_COMMON_ParseCmd(DT);
}

// CIocp의 가상함수들
VOID PlugIn_Server::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	// DummyServer에서는 m_sid를 dummy client id(식별자)로 쓴다.
	++g_SG.m_MyInfo.m_sid;
	jFE_OnIoConnected_fromServer(DT_HELLO);// jIGridNode* pGN, szIP,nswb256_t buf
}


VOID PlugIn_Server::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromServer(); //jIGridNode* pGN ,jServerInfo* si 
}


