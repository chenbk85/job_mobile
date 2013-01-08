/* file : jDBCacheConnection.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-02-12 14:17:06
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jDBCacheConnection_header__
#define __jDBCacheConnection_header__
#pragma once

struct jDBCacheInfo : public jServerInfo
{
	bool m_isOnline;
	jServerInfo& Base(){ return *this;}
	jIPacketSocket_IOCP* m_pS;
	jDBCacheInfo():m_isOnline(false){}
};

class AQ_SERVER_LIB_API jDBCacheConnection
{
#pragma warning ( disable:4251)
	jLIST_TYPEDEF_map(serverid_t, jDBCacheInfo,m_Servers);
#pragma  warning ( default:4251 )
public:

	serverid_t my_sid;//내서버의 sid

	void clear(){m_Servers.clear();}
	bool erase(jIPacketSocket_IOCP* pS);
	jDBCacheInfo* insert(jServerInfo &s,jIPlugIn_Connection* pP);
	jDBCacheInfo* insertCentral(jServerInfo &s);
	jDBCacheInfo* get_free_server();
	jDBCacheInfo* find(serverid_t sid)
	{
		m_Servers_it it = m_Servers.find(sid);
		if(it==m_Servers.end()) return 0;
		return &it->second;
	}
	static bool IsValidSocket(jIPacketSocket_IOCP* pS)
	{
		return jt_strstr(pS->Get_jIE()->GetTagName() ,jS(ToDBCache) );
	}

};

#endif // __jDBCacheConnection_header__
