/* file : PlugIn_ToFrontEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"

jCONSOLE_CMD_AUTO(jSERVER_NAME,load_client_version,0,"클라이언트 버젼체크파일 리로드","")
{
	PlugIn_ToFrontEnd* pP = PlugIn_ToFrontEnd::Get();
	if(!pP) return false;
#if 0
	nFileSystem::jFolder dir;
	tstring ver_file = tstring(pv_SERVER_RESOUCE->Get_cstr())+_T("av.lvf");
	memset(&pP->m_ClientVer, 0, sizeof(pP->m_ClientVer));
	pP->m_isClientVerCheck = GetAqVer(jA(ver_file.c_str()), pP->m_ClientVer);
	if(pP->m_isClientVerCheck)
	{
		GetjILog()->Log(_T("%s load ok"),ver_file.c_str());
	}
	else
	{
		GetjILog()->Warning(_T("%s load Fail"),ver_file.c_str());
	}
#endif
	return true;
}




jPLUGIN_FRONT_END_cpp_code_Start(PlugIn_ToFrontEnd,AqClientUser_L)
{
	m_pMM->Regist_TimeBase(0 , jMsg_C4_USER_CONNECTION_NOTIFY, 0,pv_C4_USER_CONNECTION_NOTIFY->Get_float())->DoWakeUp();

}
jPLUGIN_cpp_code_Stop(PlugIn_ToFrontEnd)
{

}
jPLUGIN_FRONT_END_cpp_code_End(PlugIn_ToFrontEnd,AqClientUser_L);


PlugIn_ToFrontEnd::PlugIn_ToFrontEnd()
:m_isClientVerCheck(false)
,m_pMM(0)
{
	// 버젼체크 파일로딩
	//nFileSystem::jFolder dir;
	//tstring ver_file = tstring(pv_SERVER_RESOUCE->Get_cstr())+_T("av.lvf");
	//m_isClientVerCheck = GetAqVer(jA(ver_file.c_str()), m_ClientVer);
}

bool PlugIn_ToFrontEnd::ParseCmd(tcstr szCommand)
{
	//nswb1024_t buf;
	std::tstring str = _T("FromAqCentral:");
	str += szCommand;
	net_string256 sendStr = str.c_str();
	//jPacket_Base pk = nTestCentralServer::WRITE_TS_ECHO(buf, sendStr );
	//jIPacketSocket_IOCP* p =0;
	//send_all(&pk, p );	
	return false;
}

void jSocketDebugger(jIPacketSocket_IOCP* pS)
{

}

// CIocp의 가상함수들
VOID PlugIn_ToFrontEnd::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoConnected_fromClient(L);
}


VOID PlugIn_ToFrontEnd::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromClient(L);

	erase(pUser);
}
