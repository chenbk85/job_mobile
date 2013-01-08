/* file : jRoC_SharedMemory_header.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-06-09 22:42:43
comp.: rocworks.co.kr
title : 
desc : 

*/

#ifndef __jRoC_SharedMemory_header_header__
#define __jRoC_SharedMemory_header_header__
#pragma once


namespace nSM
{

	const int SM_QUEUE_MAX_COUNT= 100;

//App_Monitor.xml의 <EServerState_Color>중의 하나여야 한다.
//  Mythology.exe 메뉴
// X(NIC,LOGIN_CMD,ZONE_CMD)
#define for_each_MYTHOLOGY_MENU_CMD(X)\
	X(eSS_StartUp,ID_LOGIN_STARTUP,ID_ZONESERVER_STARTUP)\
	X(eSS_Accept,ID_LOGIN_ENABLEACCEPT,ID_ZONESERVER_ENABLEACCEPT)\
	X(eSS_SOS,ID_LOGIN_ENABLESOS,ID_ZONESERVER_ENABLEACCEPT_SOS)\
	X(eSS_DisAccept,ID_LOGIN_DISABLEACCEPT,ID_ZONESERVER_DISABLEACCEPT)\
	X(eSS_DisUser,NULL,ID_ZONESERVER_DISCONNECT_ALL_USER)\
	X(eSS_ShutDown,ID_LOGINSERVER_SHUTDOWN,ID_ZONESERVER_SHUTDOWN)\

	// A : AGENT
	// S : SERVERS ( Login, Zone , PbRms , Chat ... )
#define for_each_Enum_jSM_net_agent(X)\
	X(eAGENT_ECHO			,"<TYPE>#<MSG>")\
	\
	X(eA2S_ONLINE_RQ		,"<AGENT PROCESS ID> AGENT가 나중에 실행될때이용. 즉시eS2A_ONLINE_RQ를 보낸다.")\
	\
	X(eS2A_ONLINE_RQ		,"<ServerExeListNode>#<SERVER PROCESS ID>")\
	X(eA2S_ONLINE_RS		,"<AGENT PROCESS ID>")\
	\
	X(eAGENT_OFFLINE		,"")\
	X(eSERVER_OFFLINE		,"<ServerExeListNode>")\
	\
	X(eA2S_SERVER_MENU_CMD_RQ,"<EServerState>")\
	X(eS2A_SERVER_MENU_CMD_RS,"<ServerExeListNode>#<EServerState>")\
	\
	X(eA2SS_CMD				,"<cmd>#<arg1>#<arg2>#<arg3>#<arg4>")\
	X(eSS2A_CMD_RS			,"<ServerExeListNode>#<cmd>#<result>")\
	\
	X(eA2S_PROCESS_INFO_UPDATE,"<name>#<value>")\
	X(eS2A_PROCESS_INFO_UPDATE,"<ServerExeListNode>#<name>#<value>")\
	\
	X(eS2A_SEND_ERROR_LOG,"<ServerExeListNode>#<tag>#<log>")\
	X(eA2S_RUN_EXE,"<option>#<cmd>")\
	

	jDEFINE_ENUM_CODE2(Enum_jSM_net_agent);



#define for_each_ERROR_LOG_GAME(X)\
	X(L"[ADO ERROR]",log_AdoError)\
	X(L"[CRITICAL]",log_CRITICAL)\
	X(L"[ERROR]",log_ERROR)\

#define for_each_ERROR_LOG_PBRMS(X)\
	X(L"[ERROR]",ErrorLog)\



}//namespace nSM



#endif // __jRoC_SharedMemory_header_header__
