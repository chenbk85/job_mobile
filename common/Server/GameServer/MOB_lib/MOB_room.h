/* file : MOB_room.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-16 15:47:44
comp.: www.neowiz.com
title : 
desc :  ug�� ���� ������� �����ڵ�.

*/

#ifndef __MOB_room_header__
#define __MOB_room_header__
#pragma once


#define MOB_INTERFACE_Plugin_IConnection_HELP_CODE()\
	void OnReadPacket_GReqGameEnter(GReqGameEnter* packet);\
	void OnReadPacket_GReqGameLeave(GReqGameLeave* packet);\
	void OnReadPacket_GLReqGameProtocol(GLReqGameProtocol* packet);\
	void OnReadPacket_Unkown(GReqProtocol *packet);\
	\
	void send_me(GAnsProtocol& msg);/*�ڽſ��� �ٽ� ��Ŷ�� ������.*/\
	void send_to(GAnsProtocol& msg, pp_game_id_t gid); /*��Ŷ�� �ٸ� ������� ������.*/\
	void send_to_all(GAnsProtocol& msg,ESendAllType eSkipMe);/*��Ŷ�� ��� ������.*/\
	\
	void send_to_room_user(GAnsProtocol& msg,ESendAllType eSkipMe);/*��Ŷ�� ��� ������.*/\
	ug_room_id_t	Get_room_id()	{ return m_MyInfo.roomid();}\
	\
	GReqGameEnter	m_MyInfo;\




#define MOB_ROOM(CONN,ROOM,pRoom) ROOM* pRoom=CONN->GetParent()->Room_Find(CONN->Get_room_id());jRETURN(pRoom);
#define MOB_ROOM_ret(ret,CONN,ROOM,pRoom) ROOM* pRoom=CONN->GetParent()->Room_Find(CONN->Get_room_id());jRETURN_ret(ret,pRoom)


#endif // __MOB_room_header__
