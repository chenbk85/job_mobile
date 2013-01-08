/* file : make_default_table.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-17 13:42:04
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "TDBQuery.h"
#include "PlugIn_DBCache.h"


void make_default_Hero(IN jPlayerDBSM* pUser, IN Sys_Hero* pH , OUT Use_Hero* pHero)
{
	memset(pHero,0,sizeof(*pHero));
	db_uid_type _Uid;
	_Uid.m_db_id=0;
	pHero->Set_huid(_Uid);
	pHero->Set_hsid(pH->Get_hsid());
	pHero->Set_uid(pUser->m_User.Get_uid());
	pHero->Set_tuid(_Uid);
	pHero->Set_exp_domestic(0);
	pHero->Set_exp_combat(0);
	pHero->Set_exp_total(0);
	pHero->Set_level(1);
	pHero->Set_work_state(nAQ::eHWS_REST);
	pHero->Set_slot_horse(0);
	pHero->Set_slot_weapon(0);
	pHero->Set_slot_armor(0);
	pHero->Set_slot_accessory1(0);
	pHero->Set_slot_accessory2(0);
}



