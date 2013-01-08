/* file : cmd_DBCache.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-08 21:02:46
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"


jCONSOLE_CMD_AUTO(jSERVER_NAME, user_list, 0 ,"print user list" , "<file | con> [file_tag]")
{
#define jCONSOLE_PARAM_lists(X,Y) X(outType,tcstr) Y(file_tag,tcstr,0)
	jCONSOLE_PARAM_END(lists);
	jFE_ret(false);

	vector<tstring> users;
	fname_t buf;
	for( int i=0; i<g_Users_DC.m_vecUsersSM.size(); ++i)
	{
		AqDBCacheUser& user = g_Users_DC.m_vecUsersSM[i];
		if(user.m_pjDBUserInfo->m_eUsingState==jUserZoneInfo_DC::eNOT_USE) continue;
		ToString(&user,buf);
		users.push_back(buf);
	}
	bool is = g_jAqCommon.output_string_to_file_or_con(outType, jS(dc_user_list), file_tag, users);
	GetjILog()->Log(_T("tot user= %d"),users.size());
	return is;
}


