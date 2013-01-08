/* file : Recv_SM_agent.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-05-08 21:33:43
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "mech/util/sm/jRoC_SharedMemory.h"
using namespace nSM;

#include "MythServerApp.h"
#include "BlockedNickname.h"


#include "AvLoginMain.h"
#include "AvZoneMain.h"

#include "AvLStatic.h"
#include "AvZStatic.h"


#include "JlStringFilter.h"
#include "AvEvent.h"
#include "SfBaseData.h"
#include "JlNetInfo.h"
#include "AvStatusObject.h"
#include "JlCrypt.h"
#include "Profile.h"
#include "AvZCharPcObject.h"
#include "AvZoneIOControl.h"
#include "AvLoginIOControl.h"
#include "Mythology.h"
#include "MythologyApp.h"
#include "AvScheduler.h"
#include <ShellAPI.h>
#include "AvProtocolPool.h"
#include "AvPacketBroadMgr.h"
#include "AvParamObjectList.h"
#include "ShareValue.h"
#include "IPTree.h"

#include "encryptor/EncryptorFactory.h"
#include <algorithm>
#include <sstream>

jDBQ_EVENT_RECEIVER(eAGENT_ECHO)
{
	jPARSE_SM(); //jSM_server* pSM ,wcstr sz , vector<wstring> arg
	pSM->WritePacket(eAGENT_ECHO,sz);
}

#define jSendWinMsg(NIC,LOGIN_CMD,ZONE_CMD)\
if(pSM==g_jSM[jS(eLOGIN)])\
{\
	if (!g_PartsServer[SERVER_LOGIN].GetHWND())  return;\
	if( LOGIN_CMD==NULL) return;\
	SendMessage(g_PartsServer[SERVER_LOGIN].GetHWND(), WM_COMMAND, LOGIN_CMD, 0);\
}\
else if(pSM==g_jSM[jS(eZONE)])\
{\
	if (!g_PartsServer[SERVER_ZONE].GetHWND()) return; \
	if( ZONE_CMD==NULL) return;\
	SendMessage(g_PartsServer[SERVER_ZONE].GetHWND(), WM_COMMAND, ZONE_CMD, 0);\
}\



jDBQ_EVENT_RECEIVER(eA2S_SERVER_MENU_CMD_RQ)
{
	jPARSE_SM();
	#define winmsg43(NIC,LOGIN_CMD,ZONE_CMD) if( arg[0]==_jW(NIC)) jSendWinMsg(NIC,LOGIN_CMD, ZONE_CMD);
	for_each_MYTHOLOGY_MENU_CMD(winmsg43);
}


jDBQ_EVENT_RECEIVER(eA2SS_CMD)
{
	jPARSE_SM(); //jSM_server* pSM ,wcstr sz , vector<wstring> arg
	if(arg[0]==L"REFRESH_EServerState")
	{
		wcstr szServer=0;
		if(pSM == nSM::g_jSM[jS(eLOGIN)])
			szServer=L"eLOGIN";
		else if(pSM == nSM::g_jSM[jS(eZONE)])
			szServer=L"eZONE";

		if(szServer)
		{
			nSM::jServerInfo &si = pSM->GetMyServerInfo();
			pSM->WritePacket(nSM::eSS2A_CMD_RS, L"%s#REFRESH_EServerState#%s" ,szServer, jW(si.m_eServerState) );
		}
	}

}

jDBQ_EVENT_RECEIVER(eA2S_PROCESS_INFO_UPDATE)
{
	jPARSE_SM(); //jSM_server* pSM ,wcstr sz , vector<wstring> arg
	enum {eKey,eValue,eMAX};
	jRETURN(arg.size()>=eMAX);
	pSM->GetMyServerInfo().m_Data[arg[eKey]]=arg[eValue];
}

/*
jDBQ_EVENT_RECEIVER(aaa)
{
jPARSE_SM(); //jSM_server* pSM ,wcstr sz , vector<wstring> arg

}
*/

