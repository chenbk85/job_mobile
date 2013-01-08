/* file : recv_UserGateServer_Client.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-10 18:50:36
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"

#define jRECV_PACKET_FROM_UG(MSG,...) bool On_UserGateServer_Client(RECV_PARAM_PlugIn_BaseballClient,const s_##MSG & rd)



jRECV_PACKET_FROM_UG(ug2x_echo,pPlugIn,jIE* peSession,jUser* pUser, rd) 
{
	static int64 server_time=rd.ug_time_msec();
	jLOG_USER_T("ug2x_echo : client_time=%d , ug_time=%I64d , %s" 
		,timeGetTime()-rd.client_time_msec()
		,rd.ug_time_msec()-server_time
		,rd.msg().c_str()
		);
	server_time = rd.ug_time_msec();
	return true;
}
   


jRECV_PACKET_FROM_UG(ans_ug_error,pPlugIn,jIE* peSession,jUser* pUser,rd) 
{
	jRETURN_ret(true,rd.sys_error_id()!=0);

	Sys_Error_id_t iError = rd.sys_error_id() ;
	Sys_Error* p = jCSV(Sys_Error).Index( iError);
	if(p)
	{
		jWARN_T("%s : %s", p->Get_name(), p->Get_help());
	}
	else
	{
		jWARN_T("unkown error : %d", rd.sys_error_id());
	}
	pUser->m_iAutoMatchCount=-1; // stop auto play.
	return true;
}
#if 0   
jRECV_PACKET_FROM_UG(ug2x_goto_ok,pPlugIn,jIE* peSession,jUser* pUser,rd) 
{
	jLOG_USER_T("state = %s",rd.state().c_str());
	return true;
}
#endif

jRECV_PACKET_FROM_UG(ug2x_client_version, pPlugIn,jIE* peSession,jUser* pUser,rd) 
{
	jLOG_USER_T("version = %s",rd.version().c_str());
	return true;
}



#if 0

jRECV_PACKET_FROM_UG(asdf,pPlugIn,jIE* peSession,jUser* pUser,rd) 
{
	return true;
}

#endif
