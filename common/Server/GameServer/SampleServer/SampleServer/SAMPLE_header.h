/* file : SAMPLE_header.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-11 14:43:06
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __SAMPLE_header_header__
#define __SAMPLE_header_header__
#pragma once


class SAMPLE_header
{
public:

};


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

struct SAMPLE_Plugin_Connection;
struct SAMPLE_Room;
struct SAMPLE_Plugin_NetIOModel;

#define SAMPLE_ROOM(CONN,pRoom) MOB_ROOM(CONN,SAMPLE_Room,pRoom);
#define SAMPLE_ROOM_ret(ret,CONN,pRoom) MOB_ROOM_ret(ret,CONN,SAMPLE_Room,pRoom);




#endif // __SAMPLE_header_header__
