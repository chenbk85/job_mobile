/* file : PlugIn_ToFrontEnd.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:37
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __PlugIn_ToFrontEnd_header__
#define __PlugIn_ToFrontEnd_header__
#pragma once

#include "AqClientUser.h"
#include "../AqCommon/jServerUser.h"
#include "../AqCommon/jUserZoneInfo.h"

struct jUserZoneList_U : public jUserZoneInfoList 
{
	nUtil::jCriticalSection m_CS;
};

extern jUserZoneList_U g_Users;

class PlugIn_ToFrontEnd: public jServerUsers<AqConnectedServerNode,serverid_t> 
{
public:
	jPLUGIN_header_code(PlugIn_ToFrontEnd);
	jLIST_TYPEDEF_vector_typedef(astring,userid_list);
	typedef serverid_t worldserver_id_t;
	jLIST_TYPEDEF_map(worldserver_id_t,userid_list_t,m_DisconnectedUsers);
	nUtil::jCriticalSection m_DisconnectedUsers_CS;
};

#endif // __PlugIn_ToFrontEnd_header__
