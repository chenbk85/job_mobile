/* file : MOB_net_helper.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2011-12-29 13:52:51
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __MOB_net_helper_header__
#define __MOB_net_helper_header__
#pragma once

#include "MOB_net_interface.h"

#define MOB_TIMER_SAFE_DELETE(t,plugin) if(t && plugin && plugin->m_pMOB_INetIOModel) { plugin->m_pMOB_INetIOModel->Timer_Delete(t); t=0;}


#define jLAMDA_find_by_cid(X,Z) Z(pp_game_id_t,gid)
jLAMDA_find_if(find_by_cid,MOB_IConnection*)
{
	return (it->m_pPlugin&& it->m_pPlugin->m_gid == gid);
}
jLAMDA_end();
/* 예제 : 
	boost::function<bool(MOB_IConnection*)> func = find_by_cid(gameID);\
	return (CONN*)m_pMOB_INetIOModel->find_if(func);\
*/

// Plugin_IConnection를 상속받는 클래스내부에 정의.
#define MOB_INTERFACE_Plugin_IConnection(IOMODEL)	public:\
	virtual acstr				MOB_GetRTTI();\
	virtual bool				MOB_OnReadPacket( char* pBody, int iLengthBody );\
	virtual void				MOB_OnDisconnect(acstr szErrorReason,int iErrorReason);\
	virtual void				MOB_OnConnect(Plugin_INetIOModel* p);\
	IOMODEL*					GetParent(){return (IOMODEL*)m_pParent;}\

// Plugin_IConnection를 상속받는 cpp에 정의


/* 예제

MOB_CONNECT_Plugin_IConnection(DG_Plugin_NetIOModel,DG_Plugin_Connection)
{//네트웍 접속 연결되어  메모리 활당된후 값초기화 하는 부분.
	setUserState(eUSER_STATE_ZERO);
	m_JoinInfo.set_roomid(ERROR_VALUE);
}
MOB_DISCONNECT_Plugin_IConnection(DG_Plugin_NetIOModel,DG_Plugin_Connection)
{//네트웍 접속 끊어져 메모리해제되는 상황.

}
MOB_END_Plugin_IConnection();

*/


//#--------------------------------------------------------------------------
// Plugin_INetIOModel를 상속받는 클래스내부에 정의.
//#--------------------------------------------------------------------------
#define MOB_DECLEAR_CONNECTION_MANAGER(CONN) public:\
	virtual acstr						MOB_GetRTTI() ;\
	virtual nMOB::Plugin_IConnection*	Connection_Create();\
	virtual void						Connection_Delete(nMOB::Plugin_IConnection*);\
	virtual CONN*						Connection_Find(nMOB::pp_game_id_t gameID);\

#define MOB_DECLARE_ROOM_MANAGER(ROOM) public:\
	virtual ROOM*		Room_Create(nMOB::ug_room_id_t rid);\
	virtual void		Room_Delete(ROOM*);\
	virtual ROOM*		Room_Find(nMOB::ug_room_id_t rid);\


//#--------------------------------------------------------------------------
// Plugin_INetIOModel를 상속받는 클래스 cpp에 정의.
//#--------------------------------------------------------------------------
#define MOB_IMPLEMENT_CONNECTION_MANAGER(IOMODEL,CONN,MAX_CONNECTION)\
	IOMODEL g_##IOMODEL;\
	acstr	CONN::MOB_GetRTTI(){return #CONN;}\
	acstr	IOMODEL::MOB_GetRTTI(){return #IOMODEL;}\
	typedef std::deque<CONN*> CONN##_queue_t;\
	static CONN##_queue_t s_queue_##CONN;\
	static CONN s_##CONN[MAX_CONNECTION];\
	jONCE_RUN(CONN##_queue_tmp){for( int i=0; i< MAX_CONNECTION; ++i)s_queue_##CONN.push_back(s_##CONN+i);}\
	Plugin_IConnection* IOMODEL::Connection_Create()\
	{	if(!s_queue_##CONN.size()) return 0;\
		CONN* p = s_queue_##CONN.front();\
		s_queue_##CONN.pop_front();\
		return p;\
	}\
	void IOMODEL::Connection_Delete(Plugin_IConnection* p)\
	{\
		if(!p) return; \
		CONN* pCon=(CONN*)p;\
		s_queue_##CONN.push_back(pCon);\
	}\
	CONN*  IOMODEL::Connection_Find(pp_game_id_t gameID)\
	{\
		jRETURN_ret(0,m_pMOB_INetIOModel);\
		boost::function<bool(MOB_IConnection*)> func = find_by_cid(gameID);\
		return (CONN*)m_pMOB_INetIOModel->find_if(func);\
	}\



#define MOB_HEADER_ROOM(USER_TYPE)\
	GameRoomInfo m_info;\
	bool		m_isUse;\
	typedef USER_TYPE RoomUser_t;\
	jLIST_TYPEDEF_vector(RoomUser_t*,m_UserList);\
	\
	void		MOB_OnCreate();\
	void		MOB_OnDelete();\
	void		for_each(boost::function<void(RoomUser_t*)>& func);\
	RoomUser_t* find_if(boost::function<bool(RoomUser_t*)>& func);\
	void		send_to(GAnsProtocol& msg,nMOB::pp_game_id_t gid);\
	void		send_to_all(GAnsProtocol& msg,ESendAllType eSkipMe,nMOB::pp_game_id_t gid);\





#define MOB_RECV_PACKET(CONN,PACKET_NAME) void On_##PACKET_NAME(CONN* pCon,s_##PACKET_NAME* pRecvData)

#define jMOB_RECV_PACKET(CONN,PACKET_NAME) void On_##PACKET_NAME(CONN* pCon,s_##PACKET_NAME* pRecvData){\
	jLOG(#CONN "::" #PACKET_NAME " gid=%d" , pCon->m_gid);\

#define jMOB_RECV_PACKET_END(CONN,PACKET_NAME) }



#define MOB_SEND_PACKET_START(sendMsg,pSendData,PACKET_NAME)\
	GAnsProtocol sendMsg;\
	sendMsg.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);\
	GLAnsGameProtocol sendMsg_GLAnsGameProtocol;\
	sendMsg_GLAnsGameProtocol.set_type(::GLAnsGameProtocol_Type_##PACKET_NAME);\
	s_##PACKET_NAME* pSendData = sendMsg_GLAnsGameProtocol.mutable_m_##PACKET_NAME();\


#define MOB_SEND_PACKET_END(sendMsg) 	sendMsg.set_ansgameprotocol(sendMsg##_GLAnsGameProtocol.SerializeAsString());


#include "MOB_room.h"

#endif // __MOB_net_helper_header__

