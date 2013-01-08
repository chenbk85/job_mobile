/* file : make_default_table.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-17 13:42:04
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "AqDBQuery.h"


void make_default_Hero(IN jUserZoneInfo_DC* pUser, IN Sys_Hero* pH , OUT Use_Hero* pHero)
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




void make_Insert_table(WCHAR* szSQL, nAQ::Use_Hero* p )
{

jw_sprintf(szSQL, L"INSERT INTO Use_Hero ( \
hsid\
,uid\
,tuid\
,exp_domestic\
,exp_combat\
,exp_total\
,level\
,work_state\
,slot_horse\
,slot_weapon\
,slot_armor\
,slot_accessory1\
,slot_accessory2\
) VALUES ( \
%d,\
%I64d,\
%I64d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d,\
%d)"
,p->Get_hsid() 
,p->Get_uid().m_db_id
,p->Get_tuid().m_db_id
,p->Get_exp_domestic() 
,p->Get_exp_combat() 
,p->Get_exp_total() 
,p->Get_level() 
,p->Get_work_state() 
,p->Get_slot_horse() 
,p->Get_slot_weapon() 
,p->Get_slot_armor() 
,p->Get_slot_accessory1() 
,p->Get_slot_accessory2() 
);

}



void make_update_table(WCHAR*szSQL , nAQ::Use_Hero* p)
{
jw_sprintf(szSQL, L"UPDATE Use_Hero SET \
 [tuid]=%I64d \
 ,[exp_domestic]=%d \
 ,[exp_combat]=%d \
 ,[exp_total]=%d \
 ,[level]=%d \
 ,[work_state]=%d \
 ,[slot_horse]=%d \
 ,[slot_weapon]=%d \
 ,[slot_armor]=%d \
 ,[slot_accessory1]=%d \
 ,[slot_accessory2]=%d \
 WHERE [huid]=%I64d "
 ,p->Get_tuid()
 ,p->Get_exp_domestic()
 ,p->Get_exp_combat()
 ,p->Get_exp_total()
 ,p->Get_level()
 ,p->Get_work_state()
 ,p->Get_slot_horse()
 ,p->Get_slot_weapon()
 ,p->Get_slot_armor()
 ,p->Get_slot_accessory1()
 ,p->Get_slot_accessory2()
 ,p->Get_huid().m_db_id
 );

}
