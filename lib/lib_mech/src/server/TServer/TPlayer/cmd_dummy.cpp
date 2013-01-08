/* file : cmd_Client.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-02 21:12:31
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TPlayer.h"


jCONSOLE_CMD_AUTO(jSERVER_NAME,dummy_state,0,"현제 더미 정보출력.","")
{
	jCHECK_CurrUser();
	tname1024_t szBuf;
	jLOG1(ToString(g_pCurrUser,szBuf));
	return true;
}
jCONSOLE_CMD_AUTO(jSERVER_NAME,dummy_state_all,0,"print all dummy state"," ")
{
	jPC_ret(false);
	nswb2048_t buf;
//	tname1024_t szBuf;

// 	nUtil::jCriticalSection::Auto a(&g_PL.m_listDummy_CS);
// 	PlugIn_Connect::m_listDummy_it it = g_PL.m_listDummy.begin() , ie = g_PL.m_listDummy.end();
// 	int iTot=0;
// 	for(;it!=ie;++it)
// 	{
// 		++iTot;
// 		jt_sprintf(szBuf, _T("login_result %s=%s"),jT(it->m_szID), it->GetString_EGamePlayerState());
// 		jNET_SEND2(g_SG.m_Dummy,TS_ECHO,szBuf,1));
// 		jLOG1(szBuf);
// 	}
	return true;
}



jCONSOLE_CMD_AUTO(jSERVER_NAME,dummy_world,0,"현제 더미를 통해 월드 리스트를 가져옴.","")
{
	jCHECK_CurrUser();
//	jNET_SEND(g_pCurrUser->m_pGrid[eLogin],X2L_GET_WORLD_LIST);
	return true;
}




jCONSOLE_CMD_AUTO(jSERVER_NAME,dummy_channel,0,"현제 더미를 통해 채널리스트를 가져옴.","<world>")
{
	jCHECK_CurrUser();
// 	#define jCONSOLE_PARAM_dummy_channel(X,Y) 	X(world_name,acstr)
// 	jCONSOLE_PARAM_END(dummy_channel);
// 
// 	jNET_SEND(g_pCurrUser->m_pGrid[eLogin],X2L_GET_CHANNEL_LIST,world_name);
	return true;
}
