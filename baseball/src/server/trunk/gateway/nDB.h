/* file : nDB.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-16 11:05:25
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __nDB_header__
#define __nDB_header__
#pragma once


struct jUser;
namespace nDB
{
	bool player_name_find(cstr szName);//true이면 이름중복.
	void player_name_add(cstr szName);
	void player_name_erase(cstr szName);
	bool check_name(const string& str);
}//namespace nDB



#endif // __nDB_header__
