/* file : PlugIn_Server.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:37
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __PlugIn_Server_header__
#define __PlugIn_Server_header__
#pragma once


class PlugIn_Server: public jIPlugIn_Server_IOCP
{
public:
	jPLUGIN_HEADER_CODE(PlugIn_Server);

	virtual tcstr GetPlugInNicName()
	{ 
		return _T("PlugIn_TCentral");
	}

	nXML::jE m_eServers;

	jLIST_TYPEDEF_map(serverid_t,uint16,m_mapC2_USER_CONNECTION_NOTIFY_Channel);
	nUtil::jCriticalSection m_mapC2_USER_CONNECTION_NOTIFY_CS_Channel;

	jLIST_TYPEDEF_map_typedef(serverid_t,uint16,serverid_and_cnt);
	jLIST_TYPEDEF_map(tstring,serverid_and_cnt_t,m_mapC2_USER_CONNECTION_NOTIFY_Game);
	nUtil::jCriticalSection m_mapC2_USER_CONNECTION_NOTIFY_CS_Game;


};


#endif // __PlugIn_Server_header__
