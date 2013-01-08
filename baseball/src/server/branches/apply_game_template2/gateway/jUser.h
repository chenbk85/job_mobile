/* file : jUser.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-20 15:36:37
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __jUser_header__
#define __jUser_header__
#pragma once




struct jUser : public jUser_base
{
	bool is_inited;
	
	
	time_t m_timer_game_start;
	jUser()
	{
		m_timer_game_start=0;
		is_inited=false;
	}
	~jUser();
	bool is_abilable_item_buy(Sys_ItemBase_id_t sid,EItemCategory eCategory, const string& etc_info);
	s_tbl_title* find_tbl_title_by_group(int32 title_group);

};


extern jUser g_jUser;


#endif // __jUser_header__
