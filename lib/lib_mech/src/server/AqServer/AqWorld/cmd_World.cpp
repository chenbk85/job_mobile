/* file : cmd_World.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-02 19:43:12
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "AqWorld.h"
//#include "header/jBoost.h"

jCONSOLE_CMD_AUTO(jSERVER_NAME , servers,0,"print server's xml","<file | con> [file_tag]")
{
	#define jCONSOLE_PARAM_servers(X,Y) X(outType,tcstr) Y(file_tag,tcstr,0)
	jCONSOLE_PARAM_END(servers);

	jBE_ret(false);
	vector<tstring> servers;
	servers.push_back(jT(pBE->m_eServers->Find(pv_WORLD_NAME->Get_cstr())->ToString()));
	pBE->m_eServers->ToString_Free();

	if(tstring(outType)==jS(file))
	{
		fname_t szFileName;
		fname_t szOutFile;
		if(file_tag)
			jt_sprintf(szOutFile, _T("world_servers_%s"), file_tag);
		else
			jt_strcpy(szOutFile, _T("world_servers"));

		FILE* fp = g_jAqCommon.open_file_for_console_cmd_logging(szOutFile,szFileName);
		if(!fp) return false;

		jFOR_EACH(servers, vector_string_to_file(fp));
		fclose(fp);

		g_jAqCommon.file_open_by_notepad(szFileName, !(file_tag&&jt_strlen(file_tag)) );
		return true;
	}

	if(tstring(outType)==jS(con))
	{
		jFOR_EACH(servers, vector_string_to_console());
		return true;
	}
	return false;

}

jCONSOLE_CMD_AUTO(jSERVER_NAME,user_list, 0 ,"print user list" , "<file | con> [file_tag]")
{
#define jCONSOLE_PARAM_user_list(X,Y) X(outType,tcstr) Y(file_tag,tcstr,0)
	jCONSOLE_PARAM_END(user_list);
	jFE_ret(false);

	vector<tstring> users;
	{
		jAUTO_LOCK_CS1(g_Users.m_CS);
		g_Users.for_each(jUserZoneInfoList::to_string(users));
	}

	bool is = g_jAqCommon.output_string_to_file_or_con(outType, jS(w_user_list), file_tag, users);
	GetjILog()->Log(_T("tot user= %d"),users.size());
	return is;

}


