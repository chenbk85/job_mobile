
#include <boost/bind.hpp>
#ifndef jEXCEL_SERVER_SIDE_CODE
#define jEXCEL_SERVER_SIDE_CODE
#endif


#define JBASE_API
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include "common/header/jHeader.h"
#include "common/jILog.h"
#include "excel/db_type.h"
#include "excel/excel_all.h"
#include "common/jILog.h"
#include "protoHelper.h"

#include "../MOB_lib/DBHelper.h"
#include "../MOB_lib/nMOB.h"

#include "nBASE_BALL.h"




#define jMAKE_MSG_BS2X(sendMsg, sd ,NAME)\
	BaseballServer_Client sendMsg;\
	sendMsg.set_type(::BaseballServer_Client_Type_##NAME);\
	s_##NAME* sd = sendMsg.mutable_m_##NAME();\
	jLOG("%s>send message : " #NAME , jFUNC);\



#define jMAKE_MSG_BS2UG(sendMsg, sd ,NAME)\
	BaseballServer_UserGateServer sendMsg;\
	sendMsg.set_type(::BaseballServer_UserGateServer_Type_##NAME);\
	s_##NAME* sd = sendMsg.mutable_m_##NAME();\
	jLOG("%s>send message : " #NAME , jFUNC);\



#ifdef DEF_RELEASE
#define ILLEGAL_USER_BAN(pUser)\
	pUser->set_m_e_user_gps(eUGPS_BS_USER_IS_ILLEGAL);\
	pUser->quit(GAnsGameLeave::SYSTEM_ERROR);\

#else
#define ILLEGAL_USER_BAN(pUser)
#endif

#define jRETURN_ERROR_ret(ret,exp , __ERROR_NAME, ...) if(!(exp)) \
{\
	jWARN( _T("jvRETURN_ERROR(") #__ERROR_NAME " : " _T(#exp) _T(") : user db_id=%d") ,pUser->db_id() ) ;\
	jMAKE_MSG_BS2X(sendMsg,sd,ans_bs_error);\
	sd->set_sys_error_id(jMAKE_ERR(__ERROR_NAME));\
	pUser->room()->send(pUser->db_id(), sendMsg);\
	ILLEGAL_USER_BAN(pUser);\
	return ret;\
}\

#define jRETURN_ERROR(exp , __ERROR_NAME, ...) if(!(exp)) \
{\
	jWARN( _T("jvRETURN_ERROR(") #__ERROR_NAME " : " _T(#exp) _T(") : user db_id=%d") ,pUser->db_id() ) ;\
	jMAKE_MSG_BS2X(sendMsg,sd,ans_bs_error);\
	sd->set_sys_error_id(jMAKE_ERR(__ERROR_NAME));\
	pUser->room()->send(pUser->db_id(), sendMsg);\
	ILLEGAL_USER_BAN(pUser);\
	return;\
}\


#define jDEFAULT_CHECK_BS(pUser,pRoom) \
	jRETURN(pUser);\
	baseball::Room*pRoom=pUser->room();\
	jRETURN_ERROR(pRoom,ERR_SERVER_DATA);\
	jRETURN_ERROR(!pUser->is_illegal(),ERR_USER_STATE_ILLEGAL);\


