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
#define jNET_COMMON_LIB_API T_SERVER_LIB_API
#endif


// excel StringID header용
#define jSTRING_ID_LIB_API T_SERVER_LIB_API 

#pragma warning( error : 4715 )


#define jOBJECT_NAME 31 // 모든 게임 오브젝트의 이름은 32-1이다.

//! --------------------------------------------------------------------------
//!  기본 상수 선언. 
//! --------------------------------------------------------------------------
#include "../TCommonClient/excel/table_const.h"

const int jMAX_TOWN_SLOT = 14;//aq_table.xls 의 EItemInventoryType참고
const int iMAX_TOWN_ITEM = 200; //소유 아이템 최대갯수



//! --------------------------------------------------------------------------
//! 기본 자료형 선언.
//! --------------------------------------------------------------------------

typedef nMech::uint32 dummy_id_t; // 테스트 더미의 고유아이디.
typedef nMech::wname64_t player_name_t;//유저 ID이름.
typedef nMech::wcstr	 player_name_ct;	
typedef std::wstring	 player_name_string_t;
const size_t			player_name_SIZE = 64;


typedef nMech::uint8 channelid_t; // 메모리DB에서의 index , 서버로 부터 받은 리스트에서의 인덱스.
typedef nMech::uint16 itemid_t;// 메모리DB에서의 index , 서버로 부터 받은 리스트에서의 인덱스. 인덱스는 1부터시작. 0은 사용하지 않는다.
typedef nMech::uint16 inven_slot_t;//인벤토리는 0~1000 , 창고는 1000부터...
typedef nMech::uint8 skillid_t; // skid 배열에 대해 1부터시작

typedef nMech::uint16 serverid_t;//central server에서 부여.

jLIST_TYPEDEF_vector_typedef(astring,astrings);
jLIST_TYPEDEF_vector_typedef(wstring,wstrings);
#ifdef UNICODE
jLIST_TYPEDEF_vector_typedef(tstring,wstrings);
#else
jLIST_TYPEDEF_vector_typedef(tstring,astrings);
#endif

#include "interface/db/db_uid_type.h"
#include "../TCommonClient/excel/table_type.h"
#include "../TCommonBase/player_id_t.h"

//! --------------------------------------------------------------------------
//!  기본 구조체 선언
//! --------------------------------------------------------------------------

//! W_ERROR, DC_ERROR, L_ERROR, T_ERROR, D_ERROR , U_ERROR , C_ERROR에서 사용.
enum EErrorActionType
{
	eEAT_SKIP // 해당 로그만 남기고 아무 액션을 취하지 않음.
	,eEAT_NOTIFY_TO_CLIENT // 유저에게 에러메시지를 전달한다.
	,eEAT_NOTIFY_ALL_CLIENT // 유저에게 모든 에러메시지를 전달한다.
	,eEAT_NOTIFY_AND_DISCON_USER // 에러메세지 전달후 해당 클라이언트 접속을 끊는다.
	,eEAT_DISCON_USER // 이 메세지를 서버가 받으면 해당 클라이언트 접속을 즉시 끊는다.
};
struct jErrorInfo // 네트웍통신간의 에러 응답정보.
{

	jError		e; //에러 발생한곳에서 보내는 에러 정보.
	player_id_t	pid;
	uint8		eAction; // EErrorActionType , 에러메시지를 받고 관련 socket에 대한 처리(disconnect or skip or log)
	void SetAction(EErrorActionType e){ eAction=(EErrorActionType)e;}
	EErrorActionType GetAction() { return (EErrorActionType)eAction;}
	bool IsAction(EErrorActionType e){ return eAction==e;}
	astring		sFunction;

	jErrorInfo(){}
	jErrorInfo(jError _e,EErrorActionType _eAction,acstr _sFunction,player_id_t _pid):sFunction(_sFunction),e(_e),pid(_pid){SetAction(_eAction);}
	jErrorInfo(jError_Creator_arg_t s, jError_Creator_arg_t c,EErrorActionType _eAction,acstr _sFunction,player_id_t _pid)
		:sFunction(_sFunction),e(s,c),pid(_pid){SetAction(_eAction);}
};

struct jServerUserID // 서버간에 유저 요청을 처리할때 해당유저가 접속되어 있는 서버정보를 포함한 user id
{
	player_id_t uid;
	serverid_t sid;
	jServerUserID(player_id_t u,serverid_t s): sid(s){uid = u;}
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



struct jChannelPlayerCookie
{
	player_id_t uid;
	nMech::wname32_t channel_id;
};

enum EChannelPlayerMovement
{
	eTPM_STOP,
	eTPM_WALK,
	eTPM_RUN
};


struct jWorldServerInfo
{
	aname32_t szName;
	uint8			iBusy;
};

inline cstr ToString(jWorldServerInfo* p, fname_t buf)
{
	jt_sprintf_s(buf, 256,_T("name:%s busy:%s"), p->szName, p->iBusy);
	return buf;
}


#endif // __common_AQ_header_header__
