

/* file : SAMPLE_Room.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-10 18:43:21
comp.: www.neowiz.com
title : 
desc : 


PT_UserGateServer.proto에서 message Client_UserGateServer에 포함된 메세지를 처리.
: UMLPAD에서 Client -> UserGateServer로 보낸 패킷을 받는 부분이다.

*/

#include <gateway/database.hpp>
#include <sstream>
#include <boost/format.hpp>
#include <stdlib.h>
#include "protocol/ug.pb.h"
#include "stdafx.h"



using namespace std;
using namespace MSG;


#define jRECV_FROM_CLIENT_TO_UG(X) bool CB_Client_UserGateServer(jUser* pUser,const s_##X& rd,UserGateServer_Client& sendMsg ,::Database& db)
#define jNOT_REFERANCED_VARIABLE_DONT_WARRY(X) X;
/* -------------------------------------------------------------------------- */


#if 1
#	define jRETURN_ans_ug_error_EUserGPS(MENU)	
#else
#	define jRETURN_ans_ug_error_EUserGPS(MENU)	\
	if(!(pUser->m_eEUserGPS==eUGPS_##MENU))\
{\
	jPREPARE_PACKET_UG2X(sd , ans_ug_error);\
	sd->set_sys_error_id(jMAKE_ERR(ERR_##MENU));\
	jWARN("%s",  #MENU );\
	return true;\
}\

#endif//1

#define jRETURN_ans_ug_error(is,ERROR_SYS_ID)	\
	if(!(is))\
	{\
		jPREPARE_PACKET_UG2X(sd , ans_ug_error);\
		sd->set_sys_error_id(jMAKE_ERR(ERROR_SYS_ID));\
		jWARN("%lld , %s", pUser->db_id(), #ERROR_SYS_ID );\
		return true;\
	}\

// iError==0 아니면 클라에 에러 패킷 보냄.
#define jRETURN_ans_ug_error_BY_ID(iError)	\
	if(iError)\
	{\
		jPREPARE_PACKET_UG2X(sd , ans_ug_error);\
		sd->set_sys_error_id(iError);\
		jWARN("%s",  nError::ToString(iError) );\
		return true;\
	}\


jRECV_FROM_CLIENT_TO_UG(x2ug_echo) //pUser,s_x2ug_echo& rd , sendMsg , db
{
	jPREPARE_PACKET_UG2X(sd , ug2x_echo);
	sd->set_type(rd.type() );
	sd->set_msg(rd.msg());
	sd->set_client_time_msec(rd.client_time_msec());
	sd->set_ug_time_msec(nOS::get_curr_time_msec());
	return true;
}

#if 0

#define jRECV_FROM_CLIENT_TO_UG__goto_menu(MENU)\
jRECV_FROM_CLIENT_TO_UG(MENU)\
{\
	pUser->m_eEUserGPS_prev= pUser->m_eEUserGPS;\
	pUser->m_eEUserGPS = eUGPS_##MENU;\
	jPREPARE_PACKET_UG2X(sd , ug2x_goto_ok);\
	sd->set_state(#MENU);\
	sd->set_prev_level(rd.prev_level());\
	sd->set_next_level(rd.next_level());\
	return true;\
}\

for_each_menu_window(jRECV_FROM_CLIENT_TO_UG__goto_menu);

#endif


jRECV_FROM_CLIENT_TO_UG(x2ug_get_client_version) //pUser,s_asdf& rd , sendMsg , db
{
	// _SIMPLE_MODE
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_);
	jRETURN_ans_ug_error( 1, ERR_);

	jPREPARE_PACKET_UG2X(sd , ug2x_client_version);

	return true;// false이면 접속해제한다.
}

/*

템플릿입니다.

jRECV_FROM_CLIENT_TO_UG(asdf) //pUser,s_asdf& rd , sendMsg , db
{
	jRETURN_ans_ug_error_EUserGPS(x2ug_goto_);
	jRETURN_ans_ug_error( 1, ERR_);

	jPREPARE_PACKET_UG2X(sd , ans_asdf);

	return true;// false이면 접속해제한다.
}
*/
