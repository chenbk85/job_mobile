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

#define nGame nMech




#define PT_TestServer_LIB_API AQ_SERVER_LIB_API
#define jxDECL_TestServer jxDECL_NET
#define jxDEFINE_TestServer jxDEFINE_NET

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

typedef nMech::uint16 dummyclient_id_t; // did, test client  식별  id
typedef nMech::uint32 dummy_id_t; // 테스트 더미의 고유아이디.
typedef nMech::aname32_t username_t;//유저 ID이름.


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



#endif // __common_AQ_header_header__
