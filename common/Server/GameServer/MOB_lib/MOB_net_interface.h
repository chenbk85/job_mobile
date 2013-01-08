/* file : MOB_net_interface.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2011-12-26 16:58:46
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __MOB_net_interface_header__
#define __MOB_net_interface_header__
#pragma once

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "config_all_server.h"

namespace nMOB
{
	typedef int32 pp_game_id_t;	//축약변수명 gid	: 피망플러스 유저id.    -1은 INVALID VALUE로 취급
	typedef int32 ug_room_id_t;	//축약변수명 rid	: UserGate에서 날라오는 룸 식별자.
	typedef int32 ug_category_id_t;// GReqGameEnter에서 날라오는 값.
	typedef int8 room_user_id_t; //변수명 ruid. GameServer내부에서 관리되는 식별자.(게임룸에서의 index)
	const	pp_game_id_t INVALID_pp_game_id = -1;
	const	ug_room_id_t INVALID_ug_room_id = -1;

	enum ESendAllType
	{
		eSAT_SkipMe,
		eSAT_SendAll,
	};


	const int BUFFER_SIZE =1024*2;

	struct Plugin_IConnection;
	struct Plugin_INetIOModel;
	struct MOB_IConnection;
	struct MOB_INetIOModel;
	//struct MOB_IRoom;

	struct MOB_ITimer
	{
	};

	struct PPacketHeader
	{
		int data_length;
	};
	struct MOB_NetPacketBuffer
	{
		PPacketHeader header;
		char pBody[nMOB::BUFFER_SIZE];
	};

	//#--------------------------------------------------------------------------
	struct MOB_IConnection // logic(Plugin_IConnection)에서 core(MOB_Connection)쪽 접근시 
	//#--------------------------------------------------------------------------
	{
		MOB_NetPacketBuffer m_writeBuff;
		Plugin_IConnection* m_pPlugin;
		MOB_INetIOModel* m_pParent;
		virtual bool WritePacket(MOB_NetPacketBuffer*)=0;
		virtual void DoDisconnect(acstr szErrorReason,int iErrorReason)=0;
	};

	typedef boost::function<void()> MOB_Timer_handler_t;
	//#--------------------------------------------------------------------------
	struct MOB_INetIOModel// logic(Plugin_INetIOModel)에서 core(MOB_NetIOModel_TcpServer)쪽 접근시 
	//#--------------------------------------------------------------------------
	{
		Plugin_INetIOModel* m_pPlugin;
		virtual MOB_ITimer*			Timer_Create(int iTime,MOB_Timer_handler_t& func)=0;
		virtual void				Timer_Delete(MOB_ITimer*)=0;
		virtual void				for_each(boost::function<void (MOB_IConnection*)> &func)=0;// 
		virtual Plugin_IConnection*	find_if(boost::function<bool (MOB_IConnection*)> &func)=0;
		virtual void				erase_if(boost::function<bool (MOB_IConnection*)> &func)=0;// func이 true를 리턴 하면 해당 Connection삭제후 루프탈출.
	};

	void run_tcp_server(Plugin_INetIOModel*,int port);

	//--------------------------------------------------------------------------
	//아래는 로직에서 구현해야 할 클래스.
	//--------------------------------------------------------------------------
	//#--------------------------------------------------------------------------
	struct Plugin_IConnection
	//#--------------------------------------------------------------------------
	{
		pp_game_id_t				m_gid;
		Plugin_INetIOModel*			m_pParent;
		MOB_IConnection*			m_pMOB_IConnection;//접속이 해제 되면 NULL됨
		virtual acstr				MOB_GetRTTI()									=0;
		virtual bool				MOB_OnReadPacket( char* pBody, int iLengthBody )=0;
		virtual void				MOB_OnDisconnect(acstr szErrorReason,int iErrorReason)=0;
		virtual void				MOB_OnConnect(Plugin_INetIOModel* p)=0;
	};

	//#--------------------------------------------------------------------------
	struct Plugin_INetIOModel
	//#--------------------------------------------------------------------------
	{
		MOB_INetIOModel*			m_pMOB_INetIOModel;//접속이 해제 되면 NULL됨
		virtual acstr				MOB_GetRTTI()=0;
		virtual Plugin_IConnection* Connection_Create()=0;
		virtual void				Connection_Delete(Plugin_IConnection*)=0;
	};



}//namespace nMOB



using namespace nMOB;

#endif // __MOB_net_interface_header__
