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


#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Tbl_Quest
	jEXCEL_TABLE_COMMON_CODE_CPP_Tbl_Quest();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Tbl_Quest


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
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

	int8 Tbl_Result::Get_win_score()	{		return (int8)m_win_score;}
	void Tbl_Result::Set_win_score(int8 v)
	{
		m_win_score=v;
	}

	int32 Tbl_Result::Get_win_elo_point()	{		return (int32)m_win_elo_point;}
	void Tbl_Result::Set_win_elo_point(int32 v)
	{
		if(v>10000) v = (int32)10000;
		if(v<1) v = 1;
		m_win_elo_point=v;
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

	int8 Tbl_Result::Get_lose_score()	{		return (int8)m_lose_score;}
	void Tbl_Result::Set_lose_score(int8 v)
	{
		m_lose_score=v;
	}

	int32 Tbl_Result::Get_lose_elo_point()	{		return (int32)m_lose_elo_point;}
	void Tbl_Result::Set_lose_elo_point(int32 v)
	{
		if(v>10000) v = (int32)10000;
		if(v<1) v = 1;
		m_lose_elo_point=v;
	}

	int32 Tbl_Result::Get_play_time_sec()	{		return (int32)m_play_time_sec;}
	void Tbl_Result::Set_play_time_sec(int32 v)
	{
		m_play_time_sec=v;
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

	Sys_Better_id_t Tbl_RoundResult::Get_used_batter_id()	{		return (Sys_Better_id_t)m_used_batter_id;}
	void Tbl_RoundResult::Set_used_batter_id(uint16 v)
	{
		m_used_batter_id=v;
	}

	Sys_Pitcher_id_t Tbl_RoundResult::Get_used_pitcher_id()	{		return (Sys_Pitcher_id_t)m_used_pitcher_id;}
	void Tbl_RoundResult::Set_used_pitcher_id(uint16 v)
	{
		m_used_pitcher_id=v;
	}

	int8 Tbl_RoundResult::Get_round_number()	{		return (int8)m_round_number;}
	void Tbl_RoundResult::Set_round_number(int8 v)
	{
		m_round_number=v;
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

	EGestureType Tbl_RoundResult::Get_used_gesturetype()	{		return (EGestureType)m_used_gesturetype;}
	void Tbl_RoundResult::Set_used_gesturetype(EGestureType v)
	{
		m_used_gesturetype=v;
	}

	int16 Tbl_RoundResult::Get_gesturetype_input_error()	{		return (int16)m_gesturetype_input_error;}
	void Tbl_RoundResult::Set_gesturetype_input_error(int16 v)
	{
		m_gesturetype_input_error=v;
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

	EBatterHitType Tbl_RoundResult::Get_batting_hittype()	{		return (EBatterHitType)m_batting_hittype;}
	void Tbl_RoundResult::Set_batting_hittype(EBatterHitType v)
	{
		m_batting_hittype=v;
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

	int64 Tbl_User::Get_db_id()	{		return (int64)m_db_id;}
	void Tbl_User::Set_db_id(int64 v)
	{
		m_db_id=v;
	}

	int64 Tbl_User::Get_pp_id()	{		return (int64)m_pp_id;}
	void Tbl_User::Set_pp_id(int64 v)
	{
		m_pp_id=v;
	}

	acstr Tbl_User::Get_host_type()	{		return (acstr)m_host_type;}
	void Tbl_User::Set_host_type(acstr v)
	{
		if(!v){ throw _T("Tbl_User::Set_host_type( val = NULL )");}
		nExcelUtil::jSetter(m_host_type , v, 32);
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

	int32 Tbl_User::Get_win_tot()	{		return (int32)m_win_tot;}
	void Tbl_User::Set_win_tot(int32 v)
	{
		if(v<0) v = 0;
		m_win_tot=v;
	}

	int32 Tbl_User::Get_win_tot_continue()	{		return (int32)m_win_tot_continue;}
	void Tbl_User::Set_win_tot_continue(int32 v)
	{
		m_win_tot_continue=v;
	}

	int32 Tbl_User::Get_win_tot_continue_max()	{		return (int32)m_win_tot_continue_max;}
	void Tbl_User::Set_win_tot_continue_max(int32 v)
	{
		m_win_tot_continue_max=v;
	}

	int32 Tbl_User::Get_lose_tot()	{		return (int32)m_lose_tot;}
	void Tbl_User::Set_lose_tot(int32 v)
	{
		if(v<0) v = 0;
		m_lose_tot=v;
	}

	int32 Tbl_User::Get_win_season()	{		return (int32)m_win_season;}
	void Tbl_User::Set_win_season(int32 v)
	{
		if(v<0) v = 0;
		m_win_season=v;
	}

	int32 Tbl_User::Get_lose_season()	{		return (int32)m_lose_season;}
	void Tbl_User::Set_lose_season(int32 v)
	{
		if(v<0) v = 0;
		m_lose_season=v;
	}

	int16 Tbl_User::Get_batter_tot_homerun()	{		return (int16)m_batter_tot_homerun;}
	void Tbl_User::Set_batter_tot_homerun(int16 v)
	{
		m_batter_tot_homerun=v;
	}

	int16 Tbl_User::Get_pitcher_tot_strikeout()	{		return (int16)m_pitcher_tot_strikeout;}
	void Tbl_User::Set_pitcher_tot_strikeout(int16 v)
	{
		m_pitcher_tot_strikeout=v;
	}

	int16 Tbl_User::Get_batter_tot_homerun_season()	{		return (int16)m_batter_tot_homerun_season;}
	void Tbl_User::Set_batter_tot_homerun_season(int16 v)
	{
		m_batter_tot_homerun_season=v;
	}

	int16 Tbl_User::Get_pitcher_tot_strikeout_season()	{		return (int16)m_pitcher_tot_strikeout_season;}
	void Tbl_User::Set_pitcher_tot_strikeout_season(int16 v)
	{
		m_pitcher_tot_strikeout_season=v;
	}

	int32 Tbl_User::Get_elo_point()	{		return (int32)m_elo_point;}
	void Tbl_User::Set_elo_point(int32 v)
	{
		if(v>10000) v = (int32)10000;
		if(v<1) v = 1;
		m_elo_point=v;
	}

	int64 Tbl_User::Get_cash_item_buy_money_amount()	{		return (int64)m_cash_item_buy_money_amount;}
	void Tbl_User::Set_cash_item_buy_money_amount(int64 v)
	{
		m_cash_item_buy_money_amount=v;
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

			jSQ_Interface(Tbl_User)
			for_each_nEXCEL_Tbl_User_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Tbl_User)
			jSQ_end();

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

