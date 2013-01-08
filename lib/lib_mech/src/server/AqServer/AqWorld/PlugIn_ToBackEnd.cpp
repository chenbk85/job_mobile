/* file : PlugIn_ToBackEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:13
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "AqWorld.h"
#include "PlugIn_ToBackEnd.h"
#include "TownUsingList.h"
#include "../AqCommon/jXmlSaveManager.h"


jPLUGIN_BACK_END_cpp_code_Start(PlugIn_ToBackEnd)
{

}
jPLUGIN_cpp_code_Stop(PlugIn_ToBackEnd);
{
}
jPLUGIN_BACK_END_cpp_code_End(PlugIn_ToBackEnd);


//DECLARE_INSTANCE_TYPE(S_TA_SET_TEST_ENV);
jSQ_REGIST_BIND(PLUGIN)
//jSQ_REGIST_BIND_jINetPlugIn_CLIENT(PlugIn_ToBackEnd)
{
	jSQ_Interface(PlugIn_ToBackEnd)
		jSQ_end();

	//jSQ_g_var(&g_TestInfo,g_TestInfo);
}

void _OnPacketSize_UsageInfo(tcstr szPlugIn,uint64 packet_size,tname1024_t info)
{
	g_jAqCommon.OnPacketSize_UsageInfo(szPlugIn,packet_size);
#if 0
	jBE();;
	if(!pBE->m_pToCentral) return;
	nswb256_t buf;
	pBE->m_pToCentral->WritePacket(&nCentralServer::WRITE_C4_SERVER_STATUS(buf, g_jAqCommon.Get_PacketUsage() , Get_CURR_USER() ) );
#endif

}

PlugIn_ToBackEnd::PlugIn_ToBackEnd()
{
	m_pToCentral=0;

}
PlugIn_ToBackEnd::~PlugIn_ToBackEnd()
{
}

bool PlugIn_ToBackEnd::ParseCmd(tcstr szCommand)
{
	if(!m_pToCentral) return false;
	if(!m_pToCentral->IsConnected()) return false;
	name256_t buf;
	jt_sprintf(buf,_T("%d-%s>%s") , m_sid, jT(g_ExeEnv.m_szComputerName),jT(szCommand));
	nswb1024_t sendBuf;
	m_pToCentral->WritePacket(&nCentralServer::WRITE_C_ECHO(sendBuf,jW(buf)));
	return false;
}

VOID PlugIn_ToBackEnd::OnIoConnected(jIPacketSocket_IOCP* pS)
{
	jInit_PlugIn_ToBackEnd_OnIoConnected();
}

VOID PlugIn_ToBackEnd::OnIoDisconnected(jIPacketSocket_IOCP* pS)
{
	jInit_PlugIn_ToBackEnd_OnIoDisconnected();
}
