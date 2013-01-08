/* file : cmd_Client.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-02 21:12:31
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "../AqCommon/AqCommon.h"


jCONSOLE_CMD_AUTO(jSERVER_NAME,dummy_state,0,"현제 더미 정보출력.","")
{
	check_Dummy();
	tname1024_t szBuf;
	GetjILog()->Log(ToString(g_pCurrUser,szBuf));
	return true;
}
jCONSOLE_CMD_AUTO(jSERVER_NAME,dummy_state_all,0,"print all dummy state"," ")
{
	jBE_ret(false);
	nswb2048_t sendBuf;
	tname1024_t szBuf;

	nUtil::jCriticalSection::Auto a(&pBE->m_listDummy_CS);
	PlugIn_ToBackEnd::m_listDummy_it it = pBE->m_listDummy.begin() , ie = pBE->m_listDummy.end();
	int iTot=0;
	for(;it!=ie;++it)
	{
		++iTot;
		jt_sprintf(szBuf, _T("%s=%s"),jT(it->m_szID), it->GetString_EGamePlayerState());
#if 0
		pBE->m_pS_TestServer->WritePacket(&nTestCentralServer::WRITE_TS_ECHO(sendBuf,"login_result",szBuf,1));
#endif
		GetjILog()->Log(szBuf);
	}
	return true;
}



jCONSOLE_CMD_AUTO(jSERVER_NAME,dummy_world,0,"현제 더미를 통해 월드 리스트를 가져옴.","")
{
	check_Dummy();
	g_pCurrUser->Write_Packet_Login(WRITE_X2L_GET_WORLD_LIST(buf));
	return true;
}




jCONSOLE_CMD_AUTO(jSERVER_NAME,dummy_channel,0,"현제 더미를 통해 채널리스트를 가져옴.","<world>")
{
	check_Dummy();
	#define jCONSOLE_PARAM_dummy_channel(X,Y) 	X(world_name,acstr)
	jCONSOLE_PARAM_END(dummy_channel);

	g_pCurrUser->Write_Packet_Login(WRITE_X2L_GET_CHANNEL_LIST(buf,world_name));
	return true;
}
