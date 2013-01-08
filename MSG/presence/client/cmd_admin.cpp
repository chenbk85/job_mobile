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



#define jFIRST_USER(peSession,pSession)\
	g_SessionList_it it = g_SessionList.begin();\
	jRETURN_ret(true, it!=g_SessionList.end());\
	TestSession *pSession = &it->second;\
	jIE* peSession = pSession->m_peSession;\


	jCONSOLE_CMD_AUTO(admin,bs_get_cvar,0,"baseball serer req_get_cvar","<name>")
	{
#define jCONSOLE_PARAM_bs_get_cvar(X,Y) X(name,acstr)
		jCONSOLE_PARAM_END(bs_get_cvar);

		jFIRST_USER(peSession,pSession);

		return true;
	}

	jCONSOLE_CMD_AUTO(admin,bs_set_cvar,0,"baseball serer req_set_cvar","<name> <value>")
	{
#define jCONSOLE_PARAM_bs_set_cvar(X,Y) X(name,acstr) X(value,acstr)
		jCONSOLE_PARAM_END(bs_set_cvar);

		jFIRST_USER(peSession,pSession);

		return true;
	}




}//namespace nCmdAdmin

#if 0

jCONSOLE_CMD_AUTO(admin,asdf,0,"asdf","<uid>")
{
#define jCONSOLE_PARAM_asdf(X,Y) X(uid,tcstr)
	jCONSOLE_PARAM_END(asdf);
	jFIND_USER(peSession,pSession,uid);

	jMAKE_MESSAGE_X2BS(pSession,sendMsg,sd,asdf);
	g_pPlugIn->send_to_bs(peSession,sendMsg);

	return true;
}

#endif

