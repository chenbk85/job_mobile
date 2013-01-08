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

struct jUserZoneList_W : public jUserZoneInfoList 
{
	nUtil::jCriticalSection m_CS;
};


extern jUserZoneList_W g_Users;

class PlugIn_ToFrontEnd: public jServerUsers<AqConnectedServerNode,serverid_t>  
{
public:
	jPLUGIN_header_code(PlugIn_ToFrontEnd);

	// 비정상적인 상황에서 town, dungeon서버에 접속한 유저를 강제 접속해제시킴.
	void Send_UserDisconnection(jUserZoneInfo * pUser, jServerInfo::EServerType eType, jError e , userid_t uid);
	AqConnectedServerNode* FindServer_by_User(jUserZoneInfo *pUser ,jServerInfo::EServerType eType);

	void Send_W2DC_USER_DISCONNECT(vector<astring>& uid);

	AqConnectedServerNode* GetServerByUserZone(jUserZoneInfo*,jServerInfo::EServerType);

};

#endif // __PlugIn_ToFrontEnd_header__
