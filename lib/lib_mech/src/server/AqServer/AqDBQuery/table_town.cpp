/* file : db_update_code.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-12 15:30:05
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"


#define jUPDATE_SQL_C_TYPE_TIMESTAMP(t) t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond

void make_update_table(WCHAR*szSQL , nAQ::Use_User* p)
{
	jw_sprintf(szSQL, L"UPDATE Use_User SET \
[nic_name] = N'%s'\
,[last_logout_time] = GETDATE()\
,[joined_world] = '%s'\
,[capital_tuid] = %I64d\
,[faim] = %d\
,[bad_faim] = %d\
,[cash_money] = %d\
 WHERE [uid] = %I64d "
,p->Get_nic_name()
,jT(p->Get_joined_world())
,p->Get_capital_tuid()
,p->Get_faim()
,p->Get_bad_faim()
,p->Get_cash_money()
,p->Get_uid().m_db_id
										 );
}


void make_update_table(WCHAR*szSQL , nAQ::Use_Town* p)
{
	jw_sprintf(szSQL, L"UPDATE Use_Town SET \
[name]='%s' \
,[village_con]=%d \
,[town_hero_huid]=%I64d \
,[gold_num]=%d \
,[food_num]=%d \
,[tree_num]=%d \
,[stone_num]=%d \
,[iron_num]=%d \
,[silk_num]=%d \
,[population_num]=%d \
,[soldier_num]=%d \
,[pike_num]=%d \
,[heavy_num]=%d \
,[halberd_num]=%d \
,[bow_num]=%d \
,[crossbow_num]=%d \
,[bowgun_num]=%d \
,[ballista_num]=%d \
,[chariot_num]=%d \
,[wagon_num]=%d \
,[horse_num]=%d \
,[wheelbarrow_num]=%d \
,[cart_num]=%d \
,[ladder_num]=%d \
,[ram_num]=%d \
,[tower_num]=%d \
,[trebuchet_num]=%d \
,[help]='%s' \
 WHERE [tuid]=%I64d "
,p->Get_name()
,p->Get_village_con()
,p->Get_town_hero_huid()
,p->Get_gold_num()
,p->Get_food_num()
,p->Get_tree_num()
,p->Get_stone_num()
,p->Get_iron_num()
,p->Get_silk_num()
,p->Get_population_num()
,p->Get_soldier_num()
,p->Get_pike_num()
,p->Get_heavy_num()
,p->Get_halberd_num()
,p->Get_bow_num()
,p->Get_crossbow_num()
,p->Get_bowgun_num()
,p->Get_ballista_num()
,p->Get_chariot_num()
,p->Get_wagon_num()
,p->Get_horse_num()
,p->Get_wheelbarrow_num()
,p->Get_cart_num()
,p->Get_ladder_num()
,p->Get_ram_num()
,p->Get_tower_num()
,p->Get_trebuchet_num()
,p->Get_help()
,p->Get_tuid().m_db_id
);

}

void make_Insert_table(WCHAR* szSQL, nAQ::Use_Town* p )
{
	jAssert0(0 && "make_Insert_table(WCHAR* szSQL, nAQ::Use_Town* p )");
}
