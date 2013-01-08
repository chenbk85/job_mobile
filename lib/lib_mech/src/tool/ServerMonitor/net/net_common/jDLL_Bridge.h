/* file : jDLL_Bridge.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-05-12 23:14:57
comp.: rocworks.co.kr
title : 
desc : 

*/

#ifndef __jDLL_Bridge_header__
#define __jDLL_Bridge_header__
#pragma once

#include "../protocal/PT_MonitorServer_Enum.h"
using namespace nMech::nNET::nMonitorServer;

#define jINTERFACE_jIServerMonitor(X) public:	\
	virtual int32 On_X2S_LOGIN(S_X2S_LOGIN& Data,int32 did,jIPacketSocket_IOCP* pS) ##X\
	virtual void OnIoDisconnected(int32 did,jIPacketSocket_IOCP* pS) ##X\

jINTERFACE_END(jIServerMonitor);


#define jINTERFACE_jINetMonitor(X) public:	\

jINTERFACE_END(jINetMonitor);

#define jINTERFACE_jIServerAgent(X) public:	\

jINTERFACE_END(jIServerAgent);


#define jINTERFACE_jINetAgent(X) public:	\

jINTERFACE_END(jINetAgent);

extern jNET_COMMON_LIB_API jIServerMonitor* g_pjIServerMonitor;
extern jNET_COMMON_LIB_API jINetMonitor* g_pjINetMonitor;
extern jNET_COMMON_LIB_API jIServerAgent* g_pjIServerAgent;
extern jNET_COMMON_LIB_API jINetAgent* g_pjINetAgent;

#define Get_jIServerMonitor() if(g_pjIServerMonitor)g_pjIServerMonitor

#endif // __jDLL_Bridge_header__
