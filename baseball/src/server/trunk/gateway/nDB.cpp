/* file : database_func.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-16 11:04:21
comp.: www.neowiz.com
title : 
desc : 

*/

#include <gateway/database.hpp>
#include <sqlrelay/sqlrclient.h>
#include <sstream>
#include <boost/format.hpp>
#include <stdlib.h>
#include "stdafx.h"
#include "../../MOB_lib/common/header/UFile.h"
#include "baseball_db.h" 
#include "logdef.h"


namespace nDB
{
// _SIMPLE_MODE
	tcstr g_szPLAYER_NAME_FILE = "../etc/file_db/player_name_find.temp.txt";
	bool player_name_find(cstr szName)
	{
		//jTODO DB에서 플레이어 이름 중복체크. 
		string sBuf;
		if(!nOS::is_exist_file(g_szPLAYER_NAME_FILE)) 
			return false;
		nFileSystem::read_file(g_szPLAYER_NAME_FILE , sBuf);
		if(!sBuf.size()) return false;
		return ja_strstr(sBuf.c_str(), szName);
	}
	void player_name_add(cstr szName)
	{
		LOG_DEBUG(szName);
		std::tofstream of(g_szPLAYER_NAME_FILE);
		of << szName<< endl ;
		of.close();
	}

	bool check_name(const string& str)
	{
		//jTODO Sys_InvalidWord체크 필요.
		return true;
	}

}//namespace nDB
