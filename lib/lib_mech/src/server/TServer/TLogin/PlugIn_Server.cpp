/* file : PlugIn_Server.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TLogin.h"

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
	// 버젼체크 파일로딩
	//nFileSystem::jFolder dir;
	//tstring ver_file = tstring(pv_SERVER_RESOUCE->Get_cstr())+_T("av.lvf");
	//m_isClientVerCheck = GetAqVer(jA(ver_file.c_str()), m_ClientVer);
}

bool PlugIn_Server::ParseCmd(tcstr szCommand)
{
	jPS_COMMON_ParseCmd(L);
}

// CIocp의 가상함수들
VOID PlugIn_Server::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoConnected_fromClient(L_HELLO);// jIGridNode* pGN, szIP,nswb256_t buf
}


VOID PlugIn_Server::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromClient(); //jIGridNode* pServer
}
