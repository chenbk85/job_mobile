/* file : PlugIn_Server.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TChannel.h"


jPLUGIN_CPP_CODE_START_Server(PlugIn_Server)
{
	m_pMM->Regist_TimeBase(0 , jMsg_C4_USER_CONNECTION_NOTIFY, 0,pv_C4_USER_CONNECTION_NOTIFY->Get_float())->DoWakeUp();

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
	jPS_COMMON_ParseCmd(CH);
}


// CIocp의 가상함수들
VOID PlugIn_Server::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoConnected_fromClient(CH_HELLO);// jIGridNode* pGN, szIP,nswb256_t buf
}


VOID PlugIn_Server::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromClient();
}

