/* file : cmd_UserServer.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-08 17:22:55
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToFrontEnd.h"
#include "PlugIn_ToBackEnd.h"

jCONSOLE_CMD_AUTO(jSERVER_NAME,user_list, 0 ,"print user list" , "<file | con> [file_tag]")
{
	#define jCONSOLE_PARAM_lists(X,Y) X(outType,tcstr) Y(file_tag,tcstr,0)
	jCONSOLE_PARAM_END(lists);
	jFE_ret(false);

	vector<tstring> users;
	{
		jAUTO_LOCK_CS1(g_Users.m_CS);
		g_Users.for_each(jUserZoneInfoList::to_string(users));
	}
	bool is = g_jAqCommon.output_string_to_file_or_con(outType, jS(u_user_list), file_tag, users);
	GetjILog()->Log(_T("tot user= %d"),users.size());
	return is;
}


