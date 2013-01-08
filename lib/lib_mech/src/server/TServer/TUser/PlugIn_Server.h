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

	jLIST_TYPEDEF_vector_typedef(astring,userid_list);
	typedef serverid_t worldserver_id_t;
	jLIST_TYPEDEF_map(worldserver_id_t,userid_list_t,m_DisconnectedUsers);
	nUtil::jCriticalSection m_DisconnectedUsers_CS;
};

#endif // __PlugIn_Server_header__
