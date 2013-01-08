/* file : jServerInfo.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-04 21:08:59
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TCommonServer_Header.h"
#include "jServerInfo.h"

serverid_t g_start_serverid[EServerType_END+1];
jONCE_RUN(jONCE_RUN_g_start_serverid)
{
	memset(g_start_serverid,0,sizeof(g_start_serverid));

	#define g_start_serverid_setval123(name,idStart,TAG) g_start_serverid[e##name]= idStart;
	for_each_SERVER_TYPE(g_start_serverid_setval123);
	g_start_serverid[EServerType_END]=MAX_SERVER_ID;
}

serverid_t jServerInfo::get_max_sid(EServerType eType)
{
	int i=(int)eType;
	++i;
	while(!g_start_serverid[i])
	{
		++i;
		jAssert0(i<=EServerType_END);
	}
	return g_start_serverid[i]-1;
}
serverid_t jServerInfo::get_min_sid(EServerType eType)
{

	#define get_min_sid_server_id_START_432(name,idStart,TAG) if(eType==e##name) return iSTART_SERVERID_##name;
	for_each_SERVER_TYPE(get_min_sid_server_id_START_432);
	jERROR(" not found eType=%d",eType);
	return 1;
}
