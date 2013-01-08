/* file : cmd_admin.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-27 16:19:23
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "excel/code/excel_enum.h"


namespace nCmdAdmin
{



#define jFIRST_USER(peSession,pUser)\
	g_Users_it it = g_Users.begin();\
	jRETURN_ret(true, it!=g_Users.end());\
	jUser *pUser = &it->second;\
	jIE* peSession = pUser->m_peSession;\


	jCONSOLE_CMD_AUTO(admin,bs_get_cvar,0,"baseball serer req_get_cvar","<name>")
	{
#define jCONSOLE_PARAM_bs_get_cvar(X,Y) X(name,acstr)
		jCONSOLE_PARAM_END(bs_get_cvar);

		jFIRST_USER(peSession,pUser);

		jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_get_cvar);
		sd->set_name(name);
		g_pPlugIn->send_to_bs(peSession,sendMsg);
		return true;
	}

	jCONSOLE_CMD_AUTO(admin,bs_set_cvar,0,"baseball serer req_set_cvar","<name> <value>")
	{
#define jCONSOLE_PARAM_bs_set_cvar(X,Y) X(name,acstr) X(value,acstr)
		jCONSOLE_PARAM_END(bs_set_cvar);

		jFIRST_USER(peSession,pUser);

		jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,req_set_cvar);
		sd->set_name(name);
		sd->set_val(value);
		g_pPlugIn->send_to_bs(peSession,sendMsg);
		return true;
	}




}//namespace nCmdAdmin

#if 0

jCONSOLE_CMD_AUTO(admin,asdf,0,"asdf","<uid>")
{
#define jCONSOLE_PARAM_asdf(X,Y) X(uid,tcstr)
	jCONSOLE_PARAM_END(asdf);
	jFIND_USER(peSession,pUser,uid);

	jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,asdf);
	g_pPlugIn->send_to_bs(peSession,sendMsg);

	return true;
}

#endif

