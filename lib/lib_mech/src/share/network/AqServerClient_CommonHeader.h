/* file : common_AQ_header.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-08-13 16:06:06
comp.: actoz.com
title : 
desc : 

*/

#ifndef __common_AQ_header_header__
#define __common_AQ_header_header__
#pragma once

#ifndef jNET_COMMON_LIB_API
#define jNET_COMMON_LIB_API AQ_SERVER_LIB_API
#endif
#define TR_SERVER_SIDE_CODE
#define nTR_net nMech
#define nGame nMech




#define PT_TownServer_LIB_API AQ_SERVER_LIB_API
#define jxDECL_TownServer jxDECL_NET
#define jxDEFINE_TownServer jxDEFINE_NET

#define PT_DungeonServer_LIB_API AQ_SERVER_LIB_API
#define jxDECL_DungeonServer jxDECL_NET
#define jxDEFINE_DungeonServer jxDEFINE_NET

// excel 코드용
#define TR_SERVER_LIB_API AQ_SERVER_LIB_API 

// excel StringID header용
#define jSTRING_ID_LIB_API AQ_SERVER_LIB_API 

#pragma warning( error : 4715 )


typedef nMech::uint16 serverid_t;//central server에서 부여.
jLIST_TYPEDEF_vector_typedef(astring,id_list);

//--------------------------------------------------------------------------
// aq const 
//--------------------------------------------------------------------------
const int jMAX_TOWN_SLOT = 14;//aq_table.xls 의 EItemInventoryType참고
const int iMAX_TOWN_ITEM = 200; //소유 아이템 최대갯수

#include "network/userid_t.h"
#include "network/db_uid_type.h"
#include "network/excel/table_const.h"
#include "network/excel/table_type.h"

typedef nMech::uint16 dummyclient_id_t; // did, test client  식별  id
typedef nMech::uint32 dummy_id_t; // 테스트 더미의 고유아이디.
typedef nMech::aname32_t username_t;//유저 ID이름.

typedef nMech::uint8 townid_t; // 메모리DB에서의 index , 서버로 부터 받은 리스트에서의 인덱스.
typedef nMech::uint16 itemid_t;// 메모리DB에서의 index , 서버로 부터 받은 리스트에서의 인덱스. 인덱스는 1부터시작. 0은 사용하지 않는다.
typedef nMech::uint16 inven_slot_t;//인벤토리는 0~1000 , 창고는 1000부터...
typedef nMech::uint8 skillid_t; // skid 배열에 대해 1부터시작

struct jServerUserID // 서버간에 유저 요청을 처리할때 해당유저가 접속되어 있는 서버정보를 포함한 user id
{
	userid_t uid;
	serverid_t sid;
	jServerUserID(userid_t u,serverid_t s): sid(s){uid = u;}
	jServerUserID() : sid(0){uid.m_id = 0;}
};

struct jNoticeInfo
{
	nMech::uint8 type; //공지 타입
	nMech::uint8 color;//원하는 출력 글자 색
	nMech::uint16 reserve_min; //해당 분이 지난 후 공지를 클라이언트에 출력.
	nMech::uint16 repeat_count; //해당 공지를 몇번 반복해서 출력
};


// 
#define for_each_USER_GPS(X)\
	X(NULL , "초기화상태")\
	X(L_CONNECTED,"로긴서버접속완료.인증은안되었음.")\
	X(L_CERTIFICATION,"로긴서버 인증 완료.")\
	X(T_USER_CONNECT,"타운서버 접속 완료.")\
	X(T_PERSONALROOM,"퍼서널 룸에 입장.")\
	X(T_TOWN,"마을에 입장.")\

enum EUserGPS
{
	#define enum_USER_GPS23(name,help) eGPS_##name,
	for_each_USER_GPS(enum_USER_GPS23)
	EUserGPS_END,
};

inline nMech::tcstr ToString(EUserGPS e)
{
	#define ToString_USER_GPS23(name,help) if(e==eGPS_##name) return _T(#name);
	for_each_USER_GPS(ToString_USER_GPS23);
	return jS(EUserGPS_Unkown);
}



struct jTownPlayerCookie
{
	userid_t uid;
	nMech::wname32_t town_id;
};

enum ETownPlayerMovement
{
	eTPM_STOP,
	eTPM_WALK,
	eTPM_RUN
};


//W_ERROR, DC_ERROR, L_ERROR, T_ERROR, D_ERROR , U_ERROR , C_ERROR에서 사용.
enum EServer_Common_Error
{
	eSEND_Disconn_User // 즉시 서버가 클라이언트 접속을끊는다.
	,eSEND_jError_ToClient // 유저에게 에러메시지를 전달한다.
	,eSEND_jError_and_User_Do_Disconn // 에러메세지 전달후 클라이언트는 접속을 끊는다.
};


struct jWorldServerInfo
{
	aname32_t szName;
	uint8			iBusy;
};

inline cstr ToString(jWorldServerInfo* p, fname_t buf)
{
	jt_sprintf(buf, _T("name:%s busy:%s"), p->szName, p->iBusy);
	return buf;
}


#endif // __common_AQ_header_header__
