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

class PlugIn_ToFrontEnd: public jIPlugIn_Server_IOCP ,public jServerUsers<AqClientUser>
{
public:

	jDECLARE_RTTIOBJ(PlugIn_ToFrontEnd);
	//JNET_PLUGIN_SINGTONE_DECL_FOR_USERS(PlugIn_ToFrontEnd,AqClientUser,jIPacketSocket_IOCP*);
	JNET_PLUGIN_SINGTONE_DECL(PlugIn_ToFrontEnd);
	virtual void Start();
	virtual void Stop();
	jLIST_TYPEDEF_map_typedef(jIPacketSocket_IOCP*, AqClientUser, m_ConnectUsers);

	VOID OnIoRead(jNETARG_SOCK_NUM_BUFF_LEN_IP);
	VOID OnIoWrote(jIPacketSocket_IOCP*pObject);
	VOID OnIoConnected(jIPacketSocket_IOCP* pPlugIn);
	VOID OnIoDisconnected(jIPacketSocket_IOCP*);

	PlugIn_ToFrontEnd();
	virtual bool ParseCmd(tcstr szCommand);

	bool m_isClientVerCheck;
	nEVENT::jIMsgManager* m_pMM;

};

struct _jxFindUser_by_name
{
	acstr szID;
	_jxFindUser_by_name(acstr sz):szID(sz){}
	bool operator()(AqClientUser& pUser){return !ja_stricmp(pUser .m_szID , szID);}
};


#endif // __PlugIn_ToFrontEnd_header__
