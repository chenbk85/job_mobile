/* file : jPlugIn_BE_Helper.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-28 17:45:32
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __AqServerUserBase_header__
#define __AqServerUserBase_header__
#pragma once




// dbcache , user, world server에서 서버접속 소켓노드.
struct _ConnectedServerNode : public jConnectUser<jIPacketSocket_IOCP*,serverid_t> , public jServerInfoBase
{
	serverid_t Get_sid(){ return GetUID();}
	void Set_sid(serverid_t s){ m_uid = s;}
	cstr Get_ServerName(){ return GetUserName();}

#define _AqServerNodeBase_HEADER()\
	virtual void Create()\
	{\
		m_E.clear();\
		m_pS=0;\
		m_uid=0;\
		m_sName.clear();\
	}\
	virtual void Destroy()\
	{\
		m_pS=0;\
		m_uid=0;\
	}\
	virtual void CopyFrom(const _ConnectedServerNode& o)\
	{\
		jAssert0(0 && "AqConnectedServerNode::CopyFrom");\
	}\
	virtual void Write_Packet(jPacket_Base& pk){if(m_pS)m_pS->WritePacket(&pk);}\
	virtual void WritePacket(jPacket_Base* pk){if(m_pS)m_pS->WritePacket(pk);}\

};

#define for_each_ToBackEnd(X)\
	X(Central)\
	X(User)\
	X(World)\

#pragma warning(disable:4275)
#pragma warning(disable:4251)
//--------------------------------------------------------------------------
struct AQ_SERVER_LIB_API jPlugIn_BE_Helper : public jIPlugIn_Connection
//--------------------------------------------------------------------------
{
	nXML::jE m_eServers;
	jServerInfoBase m_MyInfo;
private:
	jLIST_TYPEDEF_map(astring,bool,m_mapU4_USER_CONNECTION_NOTIFY);
	nUtil::jCriticalSection m_mapU4_USER_CONNECTION_NOTIFY_CS;
	jLIST_TYPEDEF_map(serverid_t,jIPacketSocket_IOCP*,m_listToDBCache);
public:
	void test_dc_echo();
#pragma warning(default:4251)
#pragma warning(default:4275)
	void Set_U4_USER_CONNECTION_NOTIFY_CS(userid_t uid, acstr id,bool isConnect);
	bool Make_U4_USER_CONNECTION_NOTIFY(vector<astring>& uid_connect , vector<astring>& uid_disconnect);

	void erase_DBCache(jIPacketSocket_IOCP* pS);
	void insert_DBCache(serverid_t sid, jIPacketSocket_IOCP* pS){ m_listToDBCache[sid]=pS;}
	void clear_DBCache(){m_listToDBCache.clear();}
	jIPacketSocket_IOCP* find_DBCache(serverid_t sid);
	jIPacketSocket_IOCP* find_DBCache(userid_t uid){ return find_DBCache(uid.m_dc_sid);}

	serverid_t m_sid;
	jPlugIn_BE_Helper():m_sid(0){}

	#define jxSocket_declare33(X) jIPacketSocket_IOCP* m_pTo##X;
	for_each_ToBackEnd(jxSocket_declare33);

	jIPacketSocket_IOCP* Start_ClientSocket(cstr szServer ,nXML::jE e);
	jIPacketSocket_IOCP* ConnectToUserServer(nXML::jE e){return this->Start_ClientSocket(jS(ToUser),e);}
	jIPacketSocket_IOCP* ConnectToWorldServer(nXML::jE e);
	jIPacketSocket_IOCP* ConnectToDBCacheServer(nXML::jE e);
	
	static nXML::jE		GetServerInfo_jIE(jIPacketSocket_IOCP*pS){ 	return (jIE*)pS->Get_jIE()->GetUserData(jS(jServerInfo_jIE)); 	}
	void				SetServerInfo_UserCount(serverid_t sid, uint16 userCnt);
	jIE*				Find_Server(serverid_t sid);
	jIE*				Find_WorldServer(cstr szWorld);

	virtual int Get_CURR_USER()=0;

	virtual bool Call_C_ECHO(wcstr szMsg);
};

extern jPlugIn_BE_Helper* g_pjPlugIn_BE_Helper;


#endif // __AqServerUserBase_header__
