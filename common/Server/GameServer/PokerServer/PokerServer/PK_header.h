/* file : PK_header.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-05 11:02:12
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __PokerServer_header_header__
#define __PokerServer_header_header__
#pragma once

#include "config_all_server.h"
namespace nPOKER
{

	const int iMAX_ROOM_USER = 5; // 방당 유저수는 최대 5명.
	const int iMAX_ROOM_COUNT = 1000; // 방의 최대 갯수는 1000개
	const int iMAX_USER_COUNT=iMAX_ROOM_COUNT*iMAX_ROOM_USER ;


#	define for_each_EUserState(X)\
	X(eUSER_ROOM_WAIT		," 확인 되었습니다.")\
	X(eUSER_ROOM_RUN		,"확인불가. 잘못된 키입니다.")\
	X(eUSER_GAME_READY		,"서비스 에러")\
	X(eUSER_STATE_ZERO		,"서비스 접근 아이피 아님")\

	jDEFINE_ENUM_CODE2(EUserState);

}

using namespace nPOKER;

struct PK_Plugin_Connection;
struct PK_Room;
struct PK_Plugin_NetIOModel;


#define PK_ROOM(CONN,pRoom) MOB_ROOM(CONN,PK_Room,pRoom);
#define PK_ROOM_ret(ret,CONN,pRoom) MOB_ROOM_ret(ret,CONN,PK_Room,pRoom);

#define PK_ROOM_RID(pRoom,rid) PK_Room* pRoom=g_PK_Plugin_NetIOModel.Room_Find(rid);jRETURN(pRoom);
#define PK_ROOM_RID_ret(ret,pRoom,rid) PK_Room* pRoom=g_PK_Plugin_NetIOModel.Room_Find(rid);jRETURN_ret(ret,pRoom);


#endif // __PokerServer_header_header__
