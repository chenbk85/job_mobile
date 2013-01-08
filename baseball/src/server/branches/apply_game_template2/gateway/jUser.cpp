/* file : jUser.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-05-22 13:23:54
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jUser.h"


bool jUser::is_abilable_item_buy(Sys_ItemBase_id_t sid,EItemCategory eCategory, const string& etc_info)
{
	//jTODO : 살수 있는 레벨인지.
	//jTODO : 돈은 충분한지.
	//jTODO : 현제 살수 있는 아이템?

	return true;
}


s_tbl_title* jUser::find_tbl_title_by_group(int32 title_group)
{
	for(int i=0; i< size_tbl_title(); ++i)
	{
		s_tbl_title* title = get_tbl_title(i);
		jCONTINUE(title);
		Sys_Title* pTitle = jCSV(Sys_Title).Index(title->title_sid());
		jCONTINUE(pTitle);
		if( pTitle->Get_group()==title_group)
			return title;
	}
	return 0;
}