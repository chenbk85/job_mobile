/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_baseball_table_db.h"



//현제 모듈의 Sys테이블에 대해 배열형 필드를 사용할때는 아래 코드를 구현해야 한다.
#if 0

#ifndef jNOT_USE_SQ_BIND_CODE
#endif //jNOT_USE_SQ_BIND_CODE


namespace nMech
{
	namespace nEXCEL
	{
	}//namespace nEXCEL
}//namespace nMech
#endif //구현되어야 하는 코드 끝.

#ifndef jNOT_USE_SQ_BIND_CODE

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_baseball_table_db_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_baseball_table_db_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_baseball_table_db_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE

#ifdef jEXCEL_SERVER_SIDE_CODE

	for_each_nEXCEL_excel_baseball_table_db_Tbl_STRUCT_LIST(jEXCEL_SQL_BIND_FUNC_DEFINE);
#endif //jEXCEL_SERVER_SIDE_CODE

namespace nMech {
	namespace nEXCEL {


#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Tbl__BasicScore
	jEXCEL_TABLE_COMMON_CODE_CPP_Tbl__BasicScore();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Tbl__BasicScore


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	int32 Tbl__BasicScore::Get_win_tot()	{		return (int32)m_win_tot;}
	void Tbl__BasicScore::Set_win_tot(int32 v)
	{
		if(v<0) v = 0;
		m_win_tot=v;
	}

	int32 Tbl__BasicScore::Get_lose_tot()	{		return (int32)m_lose_tot;}
	void Tbl__BasicScore::Set_lose_tot(int32 v)
	{
		if(v<0) v = 0;
		m_lose_tot=v;
	}

	int32 Tbl__BasicScore::Get_win_season()	{		return (int32)m_win_season;}
	void Tbl__BasicScore::Set_win_season(int32 v)
	{
		if(v<0) v = 0;
		m_win_season=v;
	}

	int32 Tbl__BasicScore::Get_lose_season()	{		return (int32)m_lose_season;}
	void Tbl__BasicScore::Set_lose_season(int32 v)
	{
		if(v<0) v = 0;
		m_lose_season=v;
	}

	int16 Tbl__BasicScore::Get_win_continue()	{		return (int16)m_win_continue;}
	void Tbl__BasicScore::Set_win_continue(int16 v)
	{
		m_win_continue=v;
	}

	int32 Tbl__BasicScore::Get_win_tot_single()	{		return (int32)m_win_tot_single;}
	void Tbl__BasicScore::Set_win_tot_single(int32 v)
	{
		if(v<0) v = 0;
		m_win_tot_single=v;
	}

	int32 Tbl__BasicScore::Get_lose_tot_single()	{		return (int32)m_lose_tot_single;}
	void Tbl__BasicScore::Set_lose_tot_single(int32 v)
	{
		if(v<0) v = 0;
		m_lose_tot_single=v;
	}

	int32 Tbl__BasicScore::Get_win_season_single()	{		return (int32)m_win_season_single;}
	void Tbl__BasicScore::Set_win_season_single(int32 v)
	{
		if(v<0) v = 0;
		m_win_season_single=v;
	}

	int32 Tbl__BasicScore::Get_lose_season_single()	{		return (int32)m_lose_season_single;}
	void Tbl__BasicScore::Set_lose_season_single(int32 v)
	{
		if(v<0) v = 0;
		m_lose_season_single=v;
	}

	int16 Tbl__BasicScore::Get_win_continue_single()	{		return (int16)m_win_continue_single;}
	void Tbl__BasicScore::Set_win_continue_single(int16 v)
	{
		m_win_continue_single=v;
	}

	db_uid_type_ref Tbl__PlayerBase::Get_db_id()	{		return (db_uid_type_ref)m_db_id;}
	void Tbl__PlayerBase::Set_db_id(db_uid_type_ref v)
	{
		m_db_id=v;
	}

	Sys_PlayerCard_id_t Tbl__PlayerBase::Get_sid()	{		return (Sys_PlayerCard_id_t)m_sid;}
	void Tbl__PlayerBase::Set_sid(uint16 v)
	{
		m_sid=v;
	}

	int64 Tbl__PlayerBase::Get_uid()	{		return (int64)m_uid;}
	void Tbl__PlayerBase::Set_uid(int64 v)
	{
		m_uid=v;
	}

	acstr Tbl__PlayerBase::Get_pname()	{		return (acstr)m_pname;}
	void Tbl__PlayerBase::Set_pname(acstr v)
	{
		if(!v){ throw _T("Tbl__PlayerBase::Set_pname( val = NULL )");}
		nExcelUtil::jSetter(m_pname , v, 32);
	}

	EPlayerNationType Tbl__PlayerBase::Get_city()	{		return (EPlayerNationType)m_city;}
	void Tbl__PlayerBase::Set_city(EPlayerNationType v)
	{
		if(v<eBEGIN_EPlayerNationType || v>=eEND_EPlayerNationType)
		{
			jERROR(_T("Tbl__PlayerBase::Set_city(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerNationType,eEND_EPlayerNationType,v);
		}
		m_city=v;
	}

	acstr Tbl__PlayerBase::Get_initial_name()	{		return (acstr)m_initial_name;}
	void Tbl__PlayerBase::Set_initial_name(acstr v)
	{
		if(!v){ throw _T("Tbl__PlayerBase::Set_initial_name( val = NULL )");}
		nExcelUtil::jSetter(m_initial_name , v, 32);
	}

	int16 Tbl__PlayerBase::Get_back_number()	{		return (int16)m_back_number;}
	void Tbl__PlayerBase::Set_back_number(int16 v)
	{
		m_back_number=v;
	}

	int16 Tbl__PlayerBase::Get_age()	{		return (int16)m_age;}
	void Tbl__PlayerBase::Set_age(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<1) v = 1;
		m_age=v;
	}

	EPlayerBodyType Tbl__PlayerBase::Get_body_type()	{		return (EPlayerBodyType)m_body_type;}
	void Tbl__PlayerBase::Set_body_type(EPlayerBodyType v)
	{
		if(v<eBEGIN_EPlayerBodyType || v>=eEND_EPlayerBodyType)
		{
			jERROR(_T("Tbl__PlayerBase::Set_body_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerBodyType,eEND_EPlayerBodyType,v);
		}
		m_body_type=v;
	}

	bool Tbl__PlayerBase::Get_is_left()	{		return (bool)m_is_left;}
	void Tbl__PlayerBase::Set_is_left(bool v)
	{
		m_is_left=v;
	}

	int64 Tbl__PlayerBase::Get_exp()	{		return (int64)m_exp;}
	void Tbl__PlayerBase::Set_exp(int64 v)
	{
		m_exp=v;
	}

	Sys_Quest_id_t Tbl__PlayerBase::Get_questcomplete_count()	{		return (Sys_Quest_id_t)m_questcomplete_count;}
	void Tbl__PlayerBase::Set_questcomplete_count(uint16 v)
	{
		m_questcomplete_count=v;
	}

	db_uid_type_ref Tbl__PlayerBase::Get_last_game_result()	{		return (db_uid_type_ref)m_last_game_result;}
	void Tbl__PlayerBase::Set_last_game_result(db_uid_type_ref v)
	{
		m_last_game_result=v;
	}

	acstr Tbl__PlayerBase::Get_skill_sticker()	{		return (acstr)m_skill_sticker;}
	void Tbl__PlayerBase::Set_skill_sticker(acstr v)
	{
		if(!v){ throw _T("Tbl__PlayerBase::Set_skill_sticker( val = NULL )");}
		nExcelUtil::jSetter(m_skill_sticker , v, 1024);
	}

	int16 Tbl__PlayerBase::Get_is_deleted()	{		return (int16)m_is_deleted;}
	void Tbl__PlayerBase::Set_is_deleted(int16 v)
	{
		m_is_deleted=v;
	}

	SYSTEMTIME Tbl__PlayerBase::Get_date_insert()	{		return (SYSTEMTIME)m_date_insert;}
	void Tbl__PlayerBase::Set_date_insert(SYSTEMTIME v)
	{
		m_date_insert=v;
	}

	SYSTEMTIME Tbl__PlayerBase::Get_date_update()	{		return (SYSTEMTIME)m_date_update;}
	void Tbl__PlayerBase::Set_date_update(SYSTEMTIME v)
	{
		m_date_update=v;
	}

	int32 Tbl__PlayerBase::Get_elo_point()	{		return (int32)m_elo_point;}
	void Tbl__PlayerBase::Set_elo_point(int32 v)
	{
		if(v>10000) v = (int32)10000;
		if(v<1) v = 1;
		m_elo_point=v;
	}

	db_uid_type_ref Tbl__PlayerBase::Get_team()	{		return (db_uid_type_ref)m_team;}
	void Tbl__PlayerBase::Set_team(db_uid_type_ref v)
	{
		m_team=v;
	}

	db_uid_type_ref Tbl_Friend::Get_db_id()	{		return (db_uid_type_ref)m_db_id;}
	void Tbl_Friend::Set_db_id(db_uid_type_ref v)
	{
		m_db_id=v;
	}

	int64 Tbl_Friend::Get_uid()	{		return (int64)m_uid;}
	void Tbl_Friend::Set_uid(int64 v)
	{
		m_uid=v;
	}

	int64 Tbl_Friend::Get_uid_fiend()	{		return (int64)m_uid_fiend;}
	void Tbl_Friend::Set_uid_fiend(int64 v)
	{
		m_uid_fiend=v;
	}

	acstr Tbl_Friend::Get_nic_fiend()	{		return (acstr)m_nic_fiend;}
	void Tbl_Friend::Set_nic_fiend(acstr v)
	{
		if(!v){ throw _T("Tbl_Friend::Set_nic_fiend( val = NULL )");}
		nExcelUtil::jSetter(m_nic_fiend , v, 32);
	}

	bool Tbl_Friend::Get_is_blocked()	{		return (bool)m_is_blocked;}
	void Tbl_Friend::Set_is_blocked(bool v)
	{
		m_is_blocked=v;
	}

	int16 Tbl_Friend::Get_is_deleted()	{		return (int16)m_is_deleted;}
	void Tbl_Friend::Set_is_deleted(int16 v)
	{
		m_is_deleted=v;
	}

	int32 Tbl_Friend::Get_win_tot()	{		return (int32)m_win_tot;}
	void Tbl_Friend::Set_win_tot(int32 v)
	{
		if(v<0) v = 0;
		m_win_tot=v;
	}

	int32 Tbl_Friend::Get_lose_tot()	{		return (int32)m_lose_tot;}
	void Tbl_Friend::Set_lose_tot(int32 v)
	{
		if(v<0) v = 0;
		m_lose_tot=v;
	}

	int32 Tbl_Friend::Get_win_season()	{		return (int32)m_win_season;}
	void Tbl_Friend::Set_win_season(int32 v)
	{
		if(v<0) v = 0;
		m_win_season=v;
	}

	int32 Tbl_Friend::Get_lose_season()	{		return (int32)m_lose_season;}
	void Tbl_Friend::Set_lose_season(int32 v)
	{
		if(v<0) v = 0;
		m_lose_season=v;
	}

	int16 Tbl_Friend::Get_win_continue()	{		return (int16)m_win_continue;}
	void Tbl_Friend::Set_win_continue(int16 v)
	{
		m_win_continue=v;
	}

	db_uid_type_ref Tbl_Item::Get_db_id()	{		return (db_uid_type_ref)m_db_id;}
	void Tbl_Item::Set_db_id(db_uid_type_ref v)
	{
		m_db_id=v;
	}

	Sys__ItemBase_id_t Tbl_Item::Get_sid()	{		return (Sys__ItemBase_id_t)m_sid;}
	void Tbl_Item::Set_sid(uint16 v)
	{
		m_sid=v;
	}

	EItemCategory Tbl_Item::Get_category()	{		return (EItemCategory)m_category;}
	void Tbl_Item::Set_category(EItemCategory v)
	{
		if(v<eBEGIN_EItemCategory || v>=eEND_EItemCategory)
		{
			jERROR(_T("Tbl_Item::Set_category(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemCategory,eEND_EItemCategory,v);
		}
		m_category=v;
	}

	int64 Tbl_Item::Get_uid()	{		return (int64)m_uid;}
	void Tbl_Item::Set_uid(int64 v)
	{
		m_uid=v;
	}

	db_uid_type_ref Tbl_Item::Get_used_player_id()	{		return (db_uid_type_ref)m_used_player_id;}
	void Tbl_Item::Set_used_player_id(db_uid_type_ref v)
	{
		m_used_player_id=v;
	}

	bool Tbl_Item::Get_is_better()	{		return (bool)m_is_better;}
	void Tbl_Item::Set_is_better(bool v)
	{
		m_is_better=v;
	}

	acstr Tbl_Item::Get_upgrade_level()	{		return (acstr)m_upgrade_level;}
	void Tbl_Item::Set_upgrade_level(acstr v)
	{
		if(!v){ throw _T("Tbl_Item::Set_upgrade_level( val = NULL )");}
		nExcelUtil::jSetter(m_upgrade_level , v, 32);
	}

	SYSTEMTIME Tbl_Item::Get_date_end_upgrade()	{		return (SYSTEMTIME)m_date_end_upgrade;}
	void Tbl_Item::Set_date_end_upgrade(SYSTEMTIME v)
	{
		m_date_end_upgrade=v;
	}

	acstr Tbl_Item::Get_etc_info()	{		return (acstr)m_etc_info;}
	void Tbl_Item::Set_etc_info(acstr v)
	{
		if(!v){ throw _T("Tbl_Item::Set_etc_info( val = NULL )");}
		nExcelUtil::jSetter(m_etc_info , v, 256);
	}

	bool Tbl_Item::Get_is_equiped()	{		return (bool)m_is_equiped;}
	void Tbl_Item::Set_is_equiped(bool v)
	{
		m_is_equiped=v;
	}

	SYSTEMTIME Tbl_Item::Get_date_expire()	{		return (SYSTEMTIME)m_date_expire;}
	void Tbl_Item::Set_date_expire(SYSTEMTIME v)
	{
		m_date_expire=v;
	}

	SYSTEMTIME Tbl_Item::Get_date_insert()	{		return (SYSTEMTIME)m_date_insert;}
	void Tbl_Item::Set_date_insert(SYSTEMTIME v)
	{
		m_date_insert=v;
	}

	SYSTEMTIME Tbl_Item::Get_date_update()	{		return (SYSTEMTIME)m_date_update;}
	void Tbl_Item::Set_date_update(SYSTEMTIME v)
	{
		m_date_update=v;
	}

	int16 Tbl_Item::Get_is_deleted()	{		return (int16)m_is_deleted;}
	void Tbl_Item::Set_is_deleted(int16 v)
	{
		m_is_deleted=v;
	}

	EItemState Tbl_Item::Get_state()	{		return (EItemState)m_state;}
	void Tbl_Item::Set_state(EItemState v)
	{
		m_state=v;
	}

	int16 Tbl_Item::Get_use_count()	{		return (int16)m_use_count;}
	void Tbl_Item::Set_use_count(int16 v)
	{
		m_use_count=v;
	}

	db_uid_type_ref Tbl_Item_Admin::Get_db_id()	{		return (db_uid_type_ref)m_db_id;}
	void Tbl_Item_Admin::Set_db_id(db_uid_type_ref v)
	{
		m_db_id=v;
	}

	db_uid_type_ref Tbl_Item_Admin::Get_rid()	{		return (db_uid_type_ref)m_rid;}
	void Tbl_Item_Admin::Set_rid(db_uid_type_ref v)
	{
		m_rid=v;
	}

	int32 Tbl_Item_Admin::Get_bought_real_money()	{		return (int32)m_bought_real_money;}
	void Tbl_Item_Admin::Set_bought_real_money(int32 v)
	{
		m_bought_real_money=v;
	}

	int32 Tbl_Item_Admin::Get_bought_point_money()	{		return (int32)m_bought_point_money;}
	void Tbl_Item_Admin::Set_bought_point_money(int32 v)
	{
		m_bought_point_money=v;
	}

	int32 Tbl_Item_Admin::Get_bought_game_money()	{		return (int32)m_bought_game_money;}
	void Tbl_Item_Admin::Set_bought_game_money(int32 v)
	{
		m_bought_game_money=v;
	}

	EItemBuyType Tbl_Item_Admin::Get_item_buy_type()	{		return (EItemBuyType)m_item_buy_type;}
	void Tbl_Item_Admin::Set_item_buy_type(EItemBuyType v)
	{
		m_item_buy_type=v;
	}

	Sys_Shop_id_t Tbl_Item_Admin::Get_shop_id()	{		return (Sys_Shop_id_t)m_shop_id;}
	void Tbl_Item_Admin::Set_shop_id(uint16 v)
	{
		m_shop_id=v;
	}

	db_uid_type_ref Tbl_Package::Get_db_id()	{		return (db_uid_type_ref)m_db_id;}
	void Tbl_Package::Set_db_id(db_uid_type_ref v)
	{
		m_db_id=v;
	}

	Sys_Package_id_t Tbl_Package::Get_sid_package()	{		return (Sys_Package_id_t)m_sid_package;}
	void Tbl_Package::Set_sid_package(uint16 v)
	{
		m_sid_package=v;
	}

	int64 Tbl_Package::Get_uid()	{		return (int64)m_uid;}
	void Tbl_Package::Set_uid(int64 v)
	{
		m_uid=v;
	}

	acstr Tbl_Package::Get_etc_info()	{		return (acstr)m_etc_info;}
	void Tbl_Package::Set_etc_info(acstr v)
	{
		if(!v){ throw _T("Tbl_Package::Set_etc_info( val = NULL )");}
		nExcelUtil::jSetter(m_etc_info , v, 256);
	}

	SYSTEMTIME Tbl_Package::Get_date_insert()	{		return (SYSTEMTIME)m_date_insert;}
	void Tbl_Package::Set_date_insert(SYSTEMTIME v)
	{
		m_date_insert=v;
	}

	SYSTEMTIME Tbl_Package::Get_date_update()	{		return (SYSTEMTIME)m_date_update;}
	void Tbl_Package::Set_date_update(SYSTEMTIME v)
	{
		m_date_update=v;
	}

	int16 Tbl_Package::Get_is_deleted()	{		return (int16)m_is_deleted;}
	void Tbl_Package::Set_is_deleted(int16 v)
	{
		m_is_deleted=v;
	}

	EItemState Tbl_Package::Get_state()	{		return (EItemState)m_state;}
	void Tbl_Package::Set_state(EItemState v)
	{
		m_state=v;
	}

	db_uid_type_ref Tbl_PitcherSkill::Get_db_id()	{		return (db_uid_type_ref)m_db_id;}
	void Tbl_PitcherSkill::Set_db_id(db_uid_type_ref v)
	{
		m_db_id=v;
	}

	int64 Tbl_PitcherSkill::Get_uid()	{		return (int64)m_uid;}
	void Tbl_PitcherSkill::Set_uid(int64 v)
	{
		m_uid=v;
	}

	db_uid_type_ref Tbl_PitcherSkill::Get_pid()	{		return (db_uid_type_ref)m_pid;}
	void Tbl_PitcherSkill::Set_pid(db_uid_type_ref v)
	{
		m_pid=v;
	}

	EGestureType Tbl_PitcherSkill::Get_gesture()	{		return (EGestureType)m_gesture;}
	void Tbl_PitcherSkill::Set_gesture(EGestureType v)
	{
		if(v<eBEGIN_EGestureType || v>=eEND_EGestureType)
		{
			jERROR(_T("Tbl_PitcherSkill::Set_gesture(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EGestureType,eEND_EGestureType,v);
		}
		m_gesture=v;
	}

	int16 Tbl_PitcherSkill::Get_is_deleted()	{		return (int16)m_is_deleted;}
	void Tbl_PitcherSkill::Set_is_deleted(int16 v)
	{
		m_is_deleted=v;
	}

	int32 Tbl_PitcherSkill::Get_exp()	{		return (int32)m_exp;}
	void Tbl_PitcherSkill::Set_exp(int32 v)
	{
		m_exp=v;
	}

	EPlayerBreakingBall Tbl_PitcherSkill::Get_type()	{		return (EPlayerBreakingBall)m_type;}
	void Tbl_PitcherSkill::Set_type(EPlayerBreakingBall v)
	{
		if(v<eBEGIN_EPlayerBreakingBall || v>=eEND_EPlayerBreakingBall)
		{
			jERROR(_T("Tbl_PitcherSkill::Set_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerBreakingBall,eEND_EPlayerBreakingBall,v);
		}
		m_type=v;
	}

	int16 Tbl_PlayerBetter::Get_batting_average()	{		return (int16)m_batting_average;}
	void Tbl_PlayerBetter::Set_batting_average(int16 v)
	{
		if(v<0) v = 0;
		m_batting_average=v;
	}

	int16 Tbl_PlayerBetter::Get_continue_homerun_count()	{		return (int16)m_continue_homerun_count;}
	void Tbl_PlayerBetter::Set_continue_homerun_count(int16 v)
	{
		if(v<0) v = 0;
		m_continue_homerun_count=v;
	}

	int16 Tbl_PlayerBetter::Get_homeruntotal_count()	{		return (int16)m_homeruntotal_count;}
	void Tbl_PlayerBetter::Set_homeruntotal_count(int16 v)
	{
		if(v<0) v = 0;
		m_homeruntotal_count=v;
	}

	int16 Tbl_PlayerBetter::Get_single_homerun_count()	{		return (int16)m_single_homerun_count;}
	void Tbl_PlayerBetter::Set_single_homerun_count(int16 v)
	{
		if(v<0) v = 0;
		m_single_homerun_count=v;
	}

	int16 Tbl_PlayerBetter::Get_tworun_homerun_count()	{		return (int16)m_tworun_homerun_count;}
	void Tbl_PlayerBetter::Set_tworun_homerun_count(int16 v)
	{
		if(v<0) v = 0;
		m_tworun_homerun_count=v;
	}

	int16 Tbl_PlayerBetter::Get_threerun_homerun_count()	{		return (int16)m_threerun_homerun_count;}
	void Tbl_PlayerBetter::Set_threerun_homerun_count(int16 v)
	{
		if(v<0) v = 0;
		m_threerun_homerun_count=v;
	}

	int16 Tbl_PlayerBetter::Get_grandslam_homerun_count()	{		return (int16)m_grandslam_homerun_count;}
	void Tbl_PlayerBetter::Set_grandslam_homerun_count(int16 v)
	{
		if(v<0) v = 0;
		m_grandslam_homerun_count=v;
	}

	int16 Tbl_PlayerBetter::Get_one_hit_count()	{		return (int16)m_one_hit_count;}
	void Tbl_PlayerBetter::Set_one_hit_count(int16 v)
	{
		if(v<0) v = 0;
		m_one_hit_count=v;
	}

	int16 Tbl_PlayerBetter::Get_double_hit_count()	{		return (int16)m_double_hit_count;}
	void Tbl_PlayerBetter::Set_double_hit_count(int16 v)
	{
		if(v<0) v = 0;
		m_double_hit_count=v;
	}

	int16 Tbl_PlayerBetter::Get_triple_hit_count()	{		return (int16)m_triple_hit_count;}
	void Tbl_PlayerBetter::Set_triple_hit_count(int16 v)
	{
		if(v<0) v = 0;
		m_triple_hit_count=v;
	}

	int16 Tbl_PlayerBetter::Get_foul_hit_count()	{		return (int16)m_foul_hit_count;}
	void Tbl_PlayerBetter::Set_foul_hit_count(int16 v)
	{
		if(v<0) v = 0;
		m_foul_hit_count=v;
	}

	int16 Tbl_PlayerBetter::Get_out_hit_count()	{		return (int16)m_out_hit_count;}
	void Tbl_PlayerBetter::Set_out_hit_count(int16 v)
	{
		if(v<0) v = 0;
		m_out_hit_count=v;
	}

	int16 Tbl_PlayerBetter::Get_score_count()	{		return (int16)m_score_count;}
	void Tbl_PlayerBetter::Set_score_count(int16 v)
	{
		if(v<0) v = 0;
		m_score_count=v;
	}

	EBatterAbility Tbl_PlayerBetter::Get_betting_type()	{		return (EBatterAbility)m_betting_type;}
	void Tbl_PlayerBetter::Set_betting_type(EBatterAbility v)
	{
		if(v<eBEGIN_EBatterAbility || v>=eEND_EBatterAbility)
		{
			jERROR(_T("Tbl_PlayerBetter::Set_betting_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBatterAbility,eEND_EBatterAbility,v);
		}
		m_betting_type=v;
	}

	EBatterForm Tbl_PlayerBetter::Get_betting_form()	{		return (EBatterForm)m_betting_form;}
	void Tbl_PlayerBetter::Set_betting_form(EBatterForm v)
	{
		if(v<eBEGIN_EBatterForm || v>=eEND_EBatterForm)
		{
			jERROR(_T("Tbl_PlayerBetter::Set_betting_form(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBatterForm,eEND_EBatterForm,v);
		}
		m_betting_form=v;
	}

	int16 Tbl_PlayerBetter::Get_better_power()	{		return (int16)m_better_power;}
	void Tbl_PlayerBetter::Set_better_power(int16 v)
	{
		if(v>30) v = (int16)30;
		if(v<0) v = 0;
		m_better_power=v;
	}

	int16 Tbl_PlayerBetter::Get_better_focus()	{		return (int16)m_better_focus;}
	void Tbl_PlayerBetter::Set_better_focus(int16 v)
	{
		if(v>30) v = (int16)30;
		if(v<0) v = 0;
		m_better_focus=v;
	}

	int16 Tbl_PlayerBetter::Get_better_power_buff()	{		return (int16)m_better_power_buff;}
	void Tbl_PlayerBetter::Set_better_power_buff(int16 v)
	{
		if(v>30) v = (int16)30;
		if(v<0) v = 0;
		m_better_power_buff=v;
	}

	int16 Tbl_PlayerBetter::Get_better_focus_buff()	{		return (int16)m_better_focus_buff;}
	void Tbl_PlayerBetter::Set_better_focus_buff(int16 v)
	{
		if(v>30) v = (int16)30;
		if(v<0) v = 0;
		m_better_focus_buff=v;
	}

	int16 Tbl_PlayerPitcher::Get_pitching_average()	{		return (int16)m_pitching_average;}
	void Tbl_PlayerPitcher::Set_pitching_average(int16 v)
	{
		if(v<0) v = 0;
		m_pitching_average=v;
	}

	int16 Tbl_PlayerPitcher::Get_hit_count()	{		return (int16)m_hit_count;}
	void Tbl_PlayerPitcher::Set_hit_count(int16 v)
	{
		if(v<0) v = 0;
		m_hit_count=v;
	}

	int16 Tbl_PlayerPitcher::Get_strikeout_count()	{		return (int16)m_strikeout_count;}
	void Tbl_PlayerPitcher::Set_strikeout_count(int16 v)
	{
		if(v<0) v = 0;
		m_strikeout_count=v;
	}

	int16 Tbl_PlayerPitcher::Get_homerun_pitching_count()	{		return (int16)m_homerun_pitching_count;}
	void Tbl_PlayerPitcher::Set_homerun_pitching_count(int16 v)
	{
		if(v<0) v = 0;
		m_homerun_pitching_count=v;
	}

	int16 Tbl_PlayerPitcher::Get_continue_strikeout_count()	{		return (int16)m_continue_strikeout_count;}
	void Tbl_PlayerPitcher::Set_continue_strikeout_count(int16 v)
	{
		if(v<0) v = 0;
		m_continue_strikeout_count=v;
	}

	int16 Tbl_PlayerPitcher::Get_continue_homerun_pitching_count()	{		return (int16)m_continue_homerun_pitching_count;}
	void Tbl_PlayerPitcher::Set_continue_homerun_pitching_count(int16 v)
	{
		if(v<0) v = 0;
		m_continue_homerun_pitching_count=v;
	}

	EPitcherAbility Tbl_PlayerPitcher::Get_pitcher_type()	{		return (EPitcherAbility)m_pitcher_type;}
	void Tbl_PlayerPitcher::Set_pitcher_type(EPitcherAbility v)
	{
		if(v<eBEGIN_EPitcherAbility || v>=eEND_EPitcherAbility)
		{
			jERROR(_T("Tbl_PlayerPitcher::Set_pitcher_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPitcherAbility,eEND_EPitcherAbility,v);
		}
		m_pitcher_type=v;
	}

	EPitcherForm Tbl_PlayerPitcher::Get_pitcher_form()	{		return (EPitcherForm)m_pitcher_form;}
	void Tbl_PlayerPitcher::Set_pitcher_form(EPitcherForm v)
	{
		if(v<eBEGIN_EPitcherForm || v>=eEND_EPitcherForm)
		{
			jERROR(_T("Tbl_PlayerPitcher::Set_pitcher_form(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPitcherForm,eEND_EPitcherForm,v);
		}
		m_pitcher_form=v;
	}

	int16 Tbl_PlayerPitcher::Get_pitcher_control()	{		return (int16)m_pitcher_control;}
	void Tbl_PlayerPitcher::Set_pitcher_control(int16 v)
	{
		if(v>30) v = (int16)30;
		if(v<0) v = 0;
		m_pitcher_control=v;
	}

	int16 Tbl_PlayerPitcher::Get_pitcher_ballspeed()	{		return (int16)m_pitcher_ballspeed;}
	void Tbl_PlayerPitcher::Set_pitcher_ballspeed(int16 v)
	{
		if(v>30) v = (int16)30;
		if(v<0) v = 0;
		m_pitcher_ballspeed=v;
	}

	int16 Tbl_PlayerPitcher::Get_pitcher_control_buff()	{		return (int16)m_pitcher_control_buff;}
	void Tbl_PlayerPitcher::Set_pitcher_control_buff(int16 v)
	{
		if(v>30) v = (int16)30;
		if(v<0) v = 0;
		m_pitcher_control_buff=v;
	}

	int16 Tbl_PlayerPitcher::Get_pitcher_ballspeed_buff()	{		return (int16)m_pitcher_ballspeed_buff;}
	void Tbl_PlayerPitcher::Set_pitcher_ballspeed_buff(int16 v)
	{
		if(v>30) v = (int16)30;
		if(v<0) v = 0;
		m_pitcher_ballspeed_buff=v;
	}

	int16 Tbl_PlayerPitcher::Get_pitcher_breakingball_value_buff()	{		return (int16)m_pitcher_breakingball_value_buff;}
	void Tbl_PlayerPitcher::Set_pitcher_breakingball_value_buff(int16 v)
	{
		if(v>30) v = (int16)30;
		if(v<0) v = 0;
		m_pitcher_breakingball_value_buff=v;
	}

	db_uid_type_ref Tbl_Quest::Get_db_id()	{		return (db_uid_type_ref)m_db_id;}
	void Tbl_Quest::Set_db_id(db_uid_type_ref v)
	{
		m_db_id=v;
	}

	Sys_Quest_id_t Tbl_Quest::Get_quest_sid()	{		return (Sys_Quest_id_t)m_quest_sid;}
	void Tbl_Quest::Set_quest_sid(uint16 v)
	{
		m_quest_sid=v;
	}

	int64 Tbl_Quest::Get_uid()	{		return (int64)m_uid;}
	void Tbl_Quest::Set_uid(int64 v)
	{
		m_uid=v;
	}

	SYSTEMTIME Tbl_Quest::Get_date_insert()	{		return (SYSTEMTIME)m_date_insert;}
	void Tbl_Quest::Set_date_insert(SYSTEMTIME v)
	{
		m_date_insert=v;
	}

	SYSTEMTIME Tbl_Quest::Get_date_done()	{		return (SYSTEMTIME)m_date_done;}
	void Tbl_Quest::Set_date_done(SYSTEMTIME v)
	{
		m_date_done=v;
	}

	acstr Tbl_Quest::Get_info()	{		return (acstr)m_info;}
	void Tbl_Quest::Set_info(acstr v)
	{
		if(!v){ throw _T("Tbl_Quest::Set_info( val = NULL )");}
		nExcelUtil::jSetter(m_info , v, 256);
	}

	int32 Tbl_Quest::Get_done_count()	{		return (int32)m_done_count;}
	void Tbl_Quest::Set_done_count(int32 v)
	{
		m_done_count=v;
	}

	db_uid_type_ref Tbl_Result::Get_db_id()	{		return (db_uid_type_ref)m_db_id;}
	void Tbl_Result::Set_db_id(db_uid_type_ref v)
	{
		m_db_id=v;
	}

	bool Tbl_Result::Get_is_singlemode()	{		return (bool)m_is_singlemode;}
	void Tbl_Result::Set_is_singlemode(bool v)
	{
		m_is_singlemode=v;
	}

	int64 Tbl_Result::Get_win_uid()	{		return (int64)m_win_uid;}
	void Tbl_Result::Set_win_uid(int64 v)
	{
		m_win_uid=v;
	}

	db_uid_type_ref Tbl_Result::Get_win_better()	{		return (db_uid_type_ref)m_win_better;}
	void Tbl_Result::Set_win_better(db_uid_type_ref v)
	{
		m_win_better=v;
	}

	db_uid_type_ref Tbl_Result::Get_win_pitcher()	{		return (db_uid_type_ref)m_win_pitcher;}
	void Tbl_Result::Set_win_pitcher(db_uid_type_ref v)
	{
		m_win_pitcher=v;
	}

	db_uid_type_ref Tbl_Result::Get_win_team()	{		return (db_uid_type_ref)m_win_team;}
	void Tbl_Result::Set_win_team(db_uid_type_ref v)
	{
		m_win_team=v;
	}

	int8 Tbl_Result::Get_win_score()	{		return (int8)m_win_score;}
	void Tbl_Result::Set_win_score(int8 v)
	{
		m_win_score=v;
	}

	int32 Tbl_Result::Get_win_reward_exp()	{		return (int32)m_win_reward_exp;}
	void Tbl_Result::Set_win_reward_exp(int32 v)
	{
		m_win_reward_exp=v;
	}

	int32 Tbl_Result::Get_win_reward_gamemoney()	{		return (int32)m_win_reward_gamemoney;}
	void Tbl_Result::Set_win_reward_gamemoney(int32 v)
	{
		m_win_reward_gamemoney=v;
	}

	int64 Tbl_Result::Get_lose_uid()	{		return (int64)m_lose_uid;}
	void Tbl_Result::Set_lose_uid(int64 v)
	{
		m_lose_uid=v;
	}

	db_uid_type_ref Tbl_Result::Get_lose_better()	{		return (db_uid_type_ref)m_lose_better;}
	void Tbl_Result::Set_lose_better(db_uid_type_ref v)
	{
		m_lose_better=v;
	}

	db_uid_type_ref Tbl_Result::Get_lose_pitcher()	{		return (db_uid_type_ref)m_lose_pitcher;}
	void Tbl_Result::Set_lose_pitcher(db_uid_type_ref v)
	{
		m_lose_pitcher=v;
	}

	db_uid_type_ref Tbl_Result::Get_lose_team()	{		return (db_uid_type_ref)m_lose_team;}
	void Tbl_Result::Set_lose_team(db_uid_type_ref v)
	{
		m_lose_team=v;
	}

	int8 Tbl_Result::Get_lose_score()	{		return (int8)m_lose_score;}
	void Tbl_Result::Set_lose_score(int8 v)
	{
		m_lose_score=v;
	}

	int32 Tbl_Result::Get_lose_reward_exp()	{		return (int32)m_lose_reward_exp;}
	void Tbl_Result::Set_lose_reward_exp(int32 v)
	{
		m_lose_reward_exp=v;
	}

	int32 Tbl_Result::Get_lose_reward_gamemoney()	{		return (int32)m_lose_reward_gamemoney;}
	void Tbl_Result::Set_lose_reward_gamemoney(int32 v)
	{
		m_lose_reward_gamemoney=v;
	}

	int32 Tbl_Result::Get_play_time_sec()	{		return (int32)m_play_time_sec;}
	void Tbl_Result::Set_play_time_sec(int32 v)
	{
		m_play_time_sec=v;
	}

	int64 Tbl_Result::Get_pp_point()	{		return (int64)m_pp_point;}
	void Tbl_Result::Set_pp_point(int64 v)
	{
		m_pp_point=v;
	}

	SYSTEMTIME Tbl_Result::Get_time_end()	{		return (SYSTEMTIME)m_time_end;}
	void Tbl_Result::Set_time_end(SYSTEMTIME v)
	{
		m_time_end=v;
	}

	db_uid_type_ref Tbl_RoundResult::Get_db_id()	{		return (db_uid_type_ref)m_db_id;}
	void Tbl_RoundResult::Set_db_id(db_uid_type_ref v)
	{
		m_db_id=v;
	}

	db_uid_type_ref Tbl_RoundResult::Get_grid()	{		return (db_uid_type_ref)m_grid;}
	void Tbl_RoundResult::Set_grid(db_uid_type_ref v)
	{
		m_grid=v;
	}

	int8 Tbl_RoundResult::Get_round_number()	{		return (int8)m_round_number;}
	void Tbl_RoundResult::Set_round_number(int8 v)
	{
		m_round_number=v;
	}

	bool Tbl_RoundResult::Get_is_left()	{		return (bool)m_is_left;}
	void Tbl_RoundResult::Set_is_left(bool v)
	{
		m_is_left=v;
	}

	EPlayerBreakingBall Tbl_RoundResult::Get_used_breakingball()	{		return (EPlayerBreakingBall)m_used_breakingball;}
	void Tbl_RoundResult::Set_used_breakingball(EPlayerBreakingBall v)
	{
		m_used_breakingball=v;
	}

	int16 Tbl_RoundResult::Get_used_breakingball_speed()	{		return (int16)m_used_breakingball_speed;}
	void Tbl_RoundResult::Set_used_breakingball_speed(int16 v)
	{
		m_used_breakingball_speed=v;
	}

	EPitcherAbility Tbl_RoundResult::Get_used_pitcherability()	{		return (EPitcherAbility)m_used_pitcherability;}
	void Tbl_RoundResult::Set_used_pitcherability(EPitcherAbility v)
	{
		m_used_pitcherability=v;
	}

	ERhythmJudge Tbl_RoundResult::Get_pitching_rhythm_judge()	{		return (ERhythmJudge)m_pitching_rhythm_judge;}
	void Tbl_RoundResult::Set_pitching_rhythm_judge(ERhythmJudge v)
	{
		m_pitching_rhythm_judge=v;
	}

	EItemCategoryEquipment Tbl_RoundResult::Get_used_pitcher_itemcategoryequipment()	{		return (EItemCategoryEquipment)m_used_pitcher_itemcategoryequipment;}
	void Tbl_RoundResult::Set_used_pitcher_itemcategoryequipment(EItemCategoryEquipment v)
	{
		m_used_pitcher_itemcategoryequipment=v;
	}

	bool Tbl_RoundResult::Get_used_pitcher_counter()	{		return (bool)m_used_pitcher_counter;}
	void Tbl_RoundResult::Set_used_pitcher_counter(bool v)
	{
		m_used_pitcher_counter=v;
	}

	EBatterAbility Tbl_RoundResult::Get_used_batterability()	{		return (EBatterAbility)m_used_batterability;}
	void Tbl_RoundResult::Set_used_batterability(EBatterAbility v)
	{
		m_used_batterability=v;
	}

	EHitType Tbl_RoundResult::Get_used_batting_fullpower()	{		return (EHitType)m_used_batting_fullpower;}
	void Tbl_RoundResult::Set_used_batting_fullpower(EHitType v)
	{
		m_used_batting_fullpower=v;
	}

	EHitTimmingType Tbl_RoundResult::Get_batting_timing_judge()	{		return (EHitTimmingType)m_batting_timing_judge;}
	void Tbl_RoundResult::Set_batting_timing_judge(EHitTimmingType v)
	{
		m_batting_timing_judge=v;
	}

	EItemCategoryEquipment Tbl_RoundResult::Get_used_batter_itemcategoryequipment()	{		return (EItemCategoryEquipment)m_used_batter_itemcategoryequipment;}
	void Tbl_RoundResult::Set_used_batter_itemcategoryequipment(EItemCategoryEquipment v)
	{
		m_used_batter_itemcategoryequipment=v;
	}

	bool Tbl_RoundResult::Get_used_batter_counter()	{		return (bool)m_used_batter_counter;}
	void Tbl_RoundResult::Set_used_batter_counter(bool v)
	{
		m_used_batter_counter=v;
	}

	int64 Tbl_RoundResult::Get_uid_attack()	{		return (int64)m_uid_attack;}
	void Tbl_RoundResult::Set_uid_attack(int64 v)
	{
		m_uid_attack=v;
	}

	int8 Tbl_RoundResult::Get_score()	{		return (int8)m_score;}
	void Tbl_RoundResult::Set_score(int8 v)
	{
		m_score=v;
	}

	int8 Tbl_RoundResult::Get_base_runner_state()	{		return (int8)m_base_runner_state;}
	void Tbl_RoundResult::Set_base_runner_state(int8 v)
	{
		m_base_runner_state=v;
	}

	EBatterHitType Tbl_RoundResult::Get_hit_type()	{		return (EBatterHitType)m_hit_type;}
	void Tbl_RoundResult::Set_hit_type(EBatterHitType v)
	{
		if(v<eBEGIN_EBatterHitType || v>=eEND_EBatterHitType)
		{
			jERROR(_T("Tbl_RoundResult::Set_hit_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBatterHitType,eEND_EBatterHitType,v);
		}
		m_hit_type=v;
	}

	db_uid_type_ref Tbl_Team::Get_db_id()	{		return (db_uid_type_ref)m_db_id;}
	void Tbl_Team::Set_db_id(db_uid_type_ref v)
	{
		m_db_id=v;
	}

	acstr Tbl_Team::Get_name()	{		return (acstr)m_name;}
	void Tbl_Team::Set_name(acstr v)
	{
		if(!v){ throw _T("Tbl_Team::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	int64 Tbl_Team::Get_uid()	{		return (int64)m_uid;}
	void Tbl_Team::Set_uid(int64 v)
	{
		m_uid=v;
	}

	db_uid_type_ref Tbl_Team::Get_pid_better()	{		return (db_uid_type_ref)m_pid_better;}
	void Tbl_Team::Set_pid_better(db_uid_type_ref v)
	{
		m_pid_better=v;
	}

	db_uid_type_ref Tbl_Team::Get_pid_pitcher()	{		return (db_uid_type_ref)m_pid_pitcher;}
	void Tbl_Team::Set_pid_pitcher(db_uid_type_ref v)
	{
		m_pid_pitcher=v;
	}

	int16 Tbl_Team::Get_is_deleted()	{		return (int16)m_is_deleted;}
	void Tbl_Team::Set_is_deleted(int16 v)
	{
		m_is_deleted=v;
	}

	db_uid_type_ref Tbl_Title::Get_db_id()	{		return (db_uid_type_ref)m_db_id;}
	void Tbl_Title::Set_db_id(db_uid_type_ref v)
	{
		m_db_id=v;
	}

	db_uid_type_ref Tbl_Title::Get_qid()	{		return (db_uid_type_ref)m_qid;}
	void Tbl_Title::Set_qid(db_uid_type_ref v)
	{
		m_qid=v;
	}

	Sys_Title_id_t Tbl_Title::Get_title_sid()	{		return (Sys_Title_id_t)m_title_sid;}
	void Tbl_Title::Set_title_sid(uint16 v)
	{
		m_title_sid=v;
	}

	int32 Tbl_Title::Get_group()	{		return (int32)m_group;}
	void Tbl_Title::Set_group(int32 v)
	{
		m_group=v;
	}

	EBaseballObjectType Tbl_Title::Get_object_type()	{		return (EBaseballObjectType)m_object_type;}
	void Tbl_Title::Set_object_type(EBaseballObjectType v)
	{
		if(v<eBEGIN_EBaseballObjectType || v>=eEND_EBaseballObjectType)
		{
			jERROR(_T("Tbl_Title::Set_object_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBaseballObjectType,eEND_EBaseballObjectType,v);
		}
		m_object_type=v;
	}

	int64 Tbl_Title::Get_oid()	{		return (int64)m_oid;}
	void Tbl_Title::Set_oid(int64 v)
	{
		m_oid=v;
	}

	SYSTEMTIME Tbl_Title::Get_date_update()	{		return (SYSTEMTIME)m_date_update;}
	void Tbl_Title::Set_date_update(SYSTEMTIME v)
	{
		m_date_update=v;
	}

	SYSTEMTIME Tbl_Title::Get_date_insert()	{		return (SYSTEMTIME)m_date_insert;}
	void Tbl_Title::Set_date_insert(SYSTEMTIME v)
	{
		m_date_insert=v;
	}

	int64 Tbl_User::Get_db_id()	{		return (int64)m_db_id;}
	void Tbl_User::Set_db_id(int64 v)
	{
		m_db_id=v;
	}

	acstr Tbl_User::Get_uname()	{		return (acstr)m_uname;}
	void Tbl_User::Set_uname(acstr v)
	{
		if(!v){ throw _T("Tbl_User::Set_uname( val = NULL )");}
		nExcelUtil::jSetter(m_uname , v, 32);
	}

	int32 Tbl_User::Get_discon_tot()	{		return (int32)m_discon_tot;}
	void Tbl_User::Set_discon_tot(int32 v)
	{
		m_discon_tot=v;
	}

	int16 Tbl_User::Get_pitcher_tot_strikeout()	{		return (int16)m_pitcher_tot_strikeout;}
	void Tbl_User::Set_pitcher_tot_strikeout(int16 v)
	{
		m_pitcher_tot_strikeout=v;
	}

	int16 Tbl_User::Get_pitcher_tot_average_level()	{		return (int16)m_pitcher_tot_average_level;}
	void Tbl_User::Set_pitcher_tot_average_level(int16 v)
	{
		m_pitcher_tot_average_level=v;
	}

	int16 Tbl_User::Get_better_tot_homerun()	{		return (int16)m_better_tot_homerun;}
	void Tbl_User::Set_better_tot_homerun(int16 v)
	{
		m_better_tot_homerun=v;
	}

	int16 Tbl_User::Get_better_tot__average_level()	{		return (int16)m_better_tot__average_level;}
	void Tbl_User::Set_better_tot__average_level(int16 v)
	{
		m_better_tot__average_level=v;
	}

	int16 Tbl_User::Get_cash_item_buy_count()	{		return (int16)m_cash_item_buy_count;}
	void Tbl_User::Set_cash_item_buy_count(int16 v)
	{
		m_cash_item_buy_count=v;
	}

	SYSTEMTIME Tbl_User::Get_time_last_login()	{		return (SYSTEMTIME)m_time_last_login;}
	void Tbl_User::Set_time_last_login(SYSTEMTIME v)
	{
		m_time_last_login=v;
	}

	SYSTEMTIME Tbl_User::Get_time_last_logout()	{		return (SYSTEMTIME)m_time_last_logout;}
	void Tbl_User::Set_time_last_logout(SYSTEMTIME v)
	{
		m_time_last_logout=v;
	}

	int16 Tbl_User::Get_day_continue_attend()	{		return (int16)m_day_continue_attend;}
	void Tbl_User::Set_day_continue_attend(int16 v)
	{
		m_day_continue_attend=v;
	}

	SYSTEMTIME Tbl_User::Get_date_insert()	{		return (SYSTEMTIME)m_date_insert;}
	void Tbl_User::Set_date_insert(SYSTEMTIME v)
	{
		m_date_insert=v;
	}

	SYSTEMTIME Tbl_User::Get_date_update()	{		return (SYSTEMTIME)m_date_update;}
	void Tbl_User::Set_date_update(SYSTEMTIME v)
	{
		m_date_update=v;
	}

	db_uid_type_ref Tbl_User::Get_default_tid()	{		return (db_uid_type_ref)m_default_tid;}
	void Tbl_User::Set_default_tid(db_uid_type_ref v)
	{
		m_default_tid=v;
	}

	acstr Tbl_User::Get_option()	{		return (acstr)m_option;}
	void Tbl_User::Set_option(acstr v)
	{
		if(!v){ throw _T("Tbl_User::Set_option( val = NULL )");}
		nExcelUtil::jSetter(m_option , v, 1024);
	}

	int16 Tbl_User::Get_singleplay_gift_count()	{		return (int16)m_singleplay_gift_count;}
	void Tbl_User::Set_singleplay_gift_count(int16 v)
	{
		m_singleplay_gift_count=v;
	}

	int16 Tbl_User::Get_is_deleted()	{		return (int16)m_is_deleted;}
	void Tbl_User::Set_is_deleted(int16 v)
	{
		m_is_deleted=v;
	}

	int64 Tbl_User::Get_game_money()	{		return (int64)m_game_money;}
	void Tbl_User::Set_game_money(int64 v)
	{
		m_game_money=v;
	}

	acstr Tbl_User::Get_client_os()	{		return (acstr)m_client_os;}
	void Tbl_User::Set_client_os(acstr v)
	{
		if(!v){ throw _T("Tbl_User::Set_client_os( val = NULL )");}
		nExcelUtil::jSetter(m_client_os , v, 32);
	}

	acstr Tbl_User::Get_client_networ()	{		return (acstr)m_client_networ;}
	void Tbl_User::Set_client_networ(acstr v)
	{
		if(!v){ throw _T("Tbl_User::Set_client_networ( val = NULL )");}
		nExcelUtil::jSetter(m_client_networ , v, 32);
	}

	int64 Tbl_User::Get_playtime_tot()	{		return (int64)m_playtime_tot;}
	void Tbl_User::Set_playtime_tot(int64 v)
	{
		m_playtime_tot=v;
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Tbl
	for_each_nEXCEL_excel_baseball_table_db_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Tbl);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Tbl

void Tbl__BasicScore::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Tbl__PlayerBase::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Tbl_Friend::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Tbl_Item::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Tbl_Item_Admin::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Tbl_Package::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Tbl_PitcherSkill::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Tbl_PlayerBetter::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Tbl_PlayerPitcher::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Tbl_Quest::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Tbl_Result::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Tbl_RoundResult::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Tbl_Team::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Tbl_Title::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Tbl_User::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Tbl_User_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
















	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_baseball_table_db)
		{
			jSQ_Interface(Tbl__BasicScore)
			for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl__BasicScore)
			jSQ_end();

			jSQ_Interface(Tbl__PlayerBase)
			for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
				jSQ_fn(GetBase_Tbl__BasicScore,"Tbl__BasicScore*()","Get base Table")
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl__PlayerBase)
			jSQ_end();

			jSQ_Interface(Tbl_Friend)
			for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl_Friend)
			jSQ_end();

			jSQ_Interface(Tbl_Item)
			for_each_nEXCEL_Tbl_Item_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl_Item)
			jSQ_end();

			jSQ_Interface(Tbl_Item_Admin)
			for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl_Item_Admin)
			jSQ_end();

			jSQ_Interface(Tbl_Package)
			for_each_nEXCEL_Tbl_Package_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl_Package)
			jSQ_end();

			jSQ_Interface(Tbl_PitcherSkill)
			for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl_PitcherSkill)
			jSQ_end();

			jSQ_Interface(Tbl_PlayerBetter)
			for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
				jSQ_fn(GetBase_Tbl__PlayerBase,"Tbl__PlayerBase*()","Get base Table")
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl_PlayerBetter)
			jSQ_end();

			jSQ_Interface(Tbl_PlayerPitcher)
			for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
				jSQ_fn(GetBase_Tbl__PlayerBase,"Tbl__PlayerBase*()","Get base Table")
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl_PlayerPitcher)
			jSQ_end();

			jSQ_Interface(Tbl_Quest)
			for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl_Quest)
			jSQ_end();

			jSQ_Interface(Tbl_Result)
			for_each_nEXCEL_Tbl_Result_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl_Result)
			jSQ_end();

			jSQ_Interface(Tbl_RoundResult)
			for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl_RoundResult)
			jSQ_end();

			jSQ_Interface(Tbl_Team)
			for_each_nEXCEL_Tbl_Team_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
				jSQ_fn(GetBase_Tbl__BasicScore,"Tbl__BasicScore*()","Get base Table")
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl_Team)
			jSQ_end();

			jSQ_Interface(Tbl_Title)
			for_each_nEXCEL_Tbl_Title_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl_Title)
			jSQ_end();

			jSQ_Interface(Tbl_User)
			for_each_nEXCEL_Tbl_User_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
				jSQ_fn(GetBase_Tbl__BasicScore,"Tbl__BasicScore*()","Get base Table")
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl_User)
			jSQ_end();

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

