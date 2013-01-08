/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_baseball_table.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_baseball_table_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_baseball_table_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_baseball_table_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

	PROTOS_ENUM_TYPE_csv(Sys_PlayerSkillSticker);
	PROTOS_ENUM_TYPE_COMPLAX_csv(vector<Sys_PlayerSkillSticker*>);

	PROTOS_ENUM_TYPE_csv(Sys_Title);
	PROTOS_ENUM_TYPE_COMPLAX_csv(vector<Sys_Title*>);

#endif //jNOT_USE_SQ_BIND_CODE

namespace nMech {
	static tcstr ToString(IN Sys_PlayerSkillSticker_ptr v      , tname1024_t szBuf)
	{
		if(v) jt_strcpy(szBuf,v->Get_name());
		else jt_strcpy(szBuf,jS(NULL) );
		return szBuf;
	}
	namespace nEXCEL{void Excel_PostLoader_registe(Sys_PlayerSkillSticker_ptr_vec* v,excel_wcstr sz,int iArrayMax,tcstr szHelp);}
	static tcstr ToString(IN Sys_PlayerSkillSticker_ptr_vec& v , tname1024_t szBuf)
	{
		tstring str;
		for(size_t i=0; i< v.size() ; ++i){if(!v[i]){str+=_T("NULL;"); continue;};str += v[i]->Get_name();str += _T(";");}
		jt_strncpy(szBuf,str.c_str(),1024-4);
		szBuf[1024-4]=0;
		return szBuf;
	}

	static tcstr ToString(IN Sys_Title_ptr v      , tname1024_t szBuf)
	{
		if(v) jt_strcpy(szBuf,v->Get_name());
		else jt_strcpy(szBuf,jS(NULL) );
		return szBuf;
	}
	namespace nEXCEL{void Excel_PostLoader_registe(Sys_Title_ptr_vec* v,excel_wcstr sz,int iArrayMax,tcstr szHelp);}
	static tcstr ToString(IN Sys_Title_ptr_vec& v , tname1024_t szBuf)
	{
		tstring str;
		for(size_t i=0; i< v.size() ; ++i){if(!v[i]){str+=_T("NULL;"); continue;};str += v[i]->Get_name();str += _T(";");}
		jt_strncpy(szBuf,str.c_str(),1024-4);
		szBuf[1024-4]=0;
		return szBuf;
	}

	namespace nEXCEL {


#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Base_PlayerStat
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Base_PlayerStat();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Base_PlayerStat


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	int16 Sys_Base_PlayerStat::Get_sid()	{		return (int16)m_sid;}
	void Sys_Base_PlayerStat::Set_sid(int16 v)
	{
		m_sid=v;
	}

	acstr Sys_Base_PlayerStat::Get_name()	{		return (acstr)m_name;}
	void Sys_Base_PlayerStat::Set_name(acstr v)
	{
		if(!v){ throw _T("Sys_Base_PlayerStat::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	int16 Sys_Base_PlayerStat::Get_better_power()	{		return (int16)m_better_power;}
	void Sys_Base_PlayerStat::Set_better_power(int16 v)
	{
		if(v>30) v = (int16)30;
		if(v<0) v = 0;
		m_better_power=v;
	}

	int16 Sys_Base_PlayerStat::Get_better_focus()	{		return (int16)m_better_focus;}
	void Sys_Base_PlayerStat::Set_better_focus(int16 v)
	{
		if(v>30) v = (int16)30;
		if(v<0) v = 0;
		m_better_focus=v;
	}

	int16 Sys_Base_PlayerStat::Get_pitcher_control()	{		return (int16)m_pitcher_control;}
	void Sys_Base_PlayerStat::Set_pitcher_control(int16 v)
	{
		if(v>30) v = (int16)30;
		if(v<0) v = 0;
		m_pitcher_control=v;
	}

	int16 Sys_Base_PlayerStat::Get_pitcher_ballspeed()	{		return (int16)m_pitcher_ballspeed;}
	void Sys_Base_PlayerStat::Set_pitcher_ballspeed(int16 v)
	{
		if(v>50) v = (int16)50;
		if(v<-50) v = -50;
		m_pitcher_ballspeed=v;
	}

	int16 Sys_Base_PlayerStat::Get_pitcher_breakingball_value()	{		return (int16)m_pitcher_breakingball_value;}
	void Sys_Base_PlayerStat::Set_pitcher_breakingball_value(int16 v)
	{
		if(v>50) v = (int16)50;
		if(v<-50) v = -50;
		m_pitcher_breakingball_value=v;
	}

	EPlayerBreakingBall Sys_Base_PlayerStat::Get_pitcher_breakingball_type()	{		return (EPlayerBreakingBall)m_pitcher_breakingball_type;}
	void Sys_Base_PlayerStat::Set_pitcher_breakingball_type(EPlayerBreakingBall v)
	{
		if(v<eBEGIN_EPlayerBreakingBall || v>=eEND_EPlayerBreakingBall)
		{
			jERROR(_T("Sys_Base_PlayerStat::Set_pitcher_breakingball_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerBreakingBall,eEND_EPlayerBreakingBall,v);
		}
		m_pitcher_breakingball_type=v;
	}

	bool Sys_PlayerCard::Get_player_leftright()	{		return (bool)m_player_leftright;}
	void Sys_PlayerCard::Set_player_leftright(bool v)
	{
		m_player_leftright=v;
	}

	EBatterForm Sys_PlayerCard::Get_better_form()	{		return (EBatterForm)m_better_form;}
	void Sys_PlayerCard::Set_better_form(EBatterForm v)
	{
		if(v<eBEGIN_EBatterForm || v>=eEND_EBatterForm)
		{
			jERROR(_T("Sys_PlayerCard::Set_better_form(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBatterForm,eEND_EBatterForm,v);
		}
		m_better_form=v;
	}

	EPitcherForm Sys_PlayerCard::Get_pitcher_form()	{		return (EPitcherForm)m_pitcher_form;}
	void Sys_PlayerCard::Set_pitcher_form(EPitcherForm v)
	{
		if(v<eBEGIN_EPitcherForm || v>=eEND_EPitcherForm)
		{
			jERROR(_T("Sys_PlayerCard::Set_pitcher_form(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPitcherForm,eEND_EPitcherForm,v);
		}
		m_pitcher_form=v;
	}

	EPlayerNationType Sys_PlayerCard::Get_player_nation()	{		return (EPlayerNationType)m_player_nation;}
	void Sys_PlayerCard::Set_player_nation(EPlayerNationType v)
	{
		if(v<eBEGIN_EPlayerNationType || v>=eEND_EPlayerNationType)
		{
			jERROR(_T("Sys_PlayerCard::Set_player_nation(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerNationType,eEND_EPlayerNationType,v);
		}
		m_player_nation=v;
	}

	int16 Sys_PlayerCard::Get_player_year()	{		return (int16)m_player_year;}
	void Sys_PlayerCard::Set_player_year(int16 v)
	{
		if(v>2020) v = (int16)2020;
		if(v<1970) v = 1970;
		m_player_year=v;
	}

	EPlayerGradeType Sys_PlayerCard::Get_player_grade()	{		return (EPlayerGradeType)m_player_grade;}
	void Sys_PlayerCard::Set_player_grade(EPlayerGradeType v)
	{
		if(v<eBEGIN_EPlayerGradeType || v>=eEND_EPlayerGradeType)
		{
			jERROR(_T("Sys_PlayerCard::Set_player_grade(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerGradeType,eEND_EPlayerGradeType,v);
		}
		m_player_grade=v;
	}

	EPlayerBodyType Sys_PlayerCard::Get_body_type()	{		return (EPlayerBodyType)m_body_type;}
	void Sys_PlayerCard::Set_body_type(EPlayerBodyType v)
	{
		if(v<eBEGIN_EPlayerBodyType || v>=eEND_EPlayerBodyType)
		{
			jERROR(_T("Sys_PlayerCard::Set_body_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerBodyType,eEND_EPlayerBodyType,v);
		}
		m_body_type=v;
	}

	int16 Sys_PlayerCard::Get_player_level()	{		return (int16)m_player_level;}
	void Sys_PlayerCard::Set_player_level(int16 v)
	{
		if(v>150) v = (int16)150;
		if(v<1) v = 1;
		m_player_level=v;
	}

	EPlayerType Sys_PlayerCard::Get_player_type()	{		return (EPlayerType)m_player_type;}
	void Sys_PlayerCard::Set_player_type(EPlayerType v)
	{
		if(v<eBEGIN_EPlayerType || v>=eEND_EPlayerType)
		{
			jERROR(_T("Sys_PlayerCard::Set_player_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerType,eEND_EPlayerType,v);
		}
		m_player_type=v;
	}

	EItemPriceType Sys_PlayerCard::Get_price_type()	{		return (EItemPriceType)m_price_type;}
	void Sys_PlayerCard::Set_price_type(EItemPriceType v)
	{
		if(v<eBEGIN_EItemPriceType || v>=eEND_EItemPriceType)
		{
			jERROR(_T("Sys_PlayerCard::Set_price_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemPriceType,eEND_EItemPriceType,v);
		}
		m_price_type=v;
	}

	int32 Sys_PlayerCard::Get_price_money()	{		return (int32)m_price_money;}
	void Sys_PlayerCard::Set_price_money(int32 v)
	{
		m_price_money=v;
	}

	int32 Sys_PlayerCard::Get_price_cash()	{		return (int32)m_price_cash;}
	void Sys_PlayerCard::Set_price_cash(int32 v)
	{
		m_price_cash=v;
	}

	EItemSellStatus Sys_PlayerCard::Get_sell_status()	{		return (EItemSellStatus)m_sell_status;}
	void Sys_PlayerCard::Set_sell_status(EItemSellStatus v)
	{
		if(v<eBEGIN_EItemSellStatus || v>=eEND_EItemSellStatus)
		{
			jERROR(_T("Sys_PlayerCard::Set_sell_status(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemSellStatus,eEND_EItemSellStatus,v);
		}
		m_sell_status=v;
	}

	SYSTEMTIME Sys_PlayerCard::Get_sell_start_date()	{		return (SYSTEMTIME)m_sell_start_date;}
	void Sys_PlayerCard::Set_sell_start_date(SYSTEMTIME v)
	{
		m_sell_start_date=v;
	}

	SYSTEMTIME Sys_PlayerCard::Get_sell_end_date()	{		return (SYSTEMTIME)m_sell_end_date;}
	void Sys_PlayerCard::Set_sell_end_date(SYSTEMTIME v)
	{
		m_sell_end_date=v;
	}

	int16 Sys_PlayerCard::Get_player_level_min()	{		return (int16)m_player_level_min;}
	void Sys_PlayerCard::Set_player_level_min(int16 v)
	{
		m_player_level_min=v;
	}

	int16 Sys_PlayerCard::Get_player_level_max()	{		return (int16)m_player_level_max;}
	void Sys_PlayerCard::Set_player_level_max(int16 v)
	{
		m_player_level_max=v;
	}

	int8 Sys_PlayerCard::Get_sticker_slot_count()	{		return (int8)m_sticker_slot_count;}
	void Sys_PlayerCard::Set_sticker_slot_count(int8 v)
	{
		if(v>12) v = (int8)12;
		if(v<1) v = 1;
		m_sticker_slot_count=v;
	}

	Sys_PlayerSkillSticker_ptr_vec_ref Sys_PlayerCard::Get_skill_sticker()	{			return m_skill_sticker_ptr_vec;}
	void Sys_PlayerCard::Set_skill_sticker(Sys_PlayerSkillSticker_ptr_vec_ref v)
	{
		m_skill_sticker_ptr_vec = v;
	}

	bool Sys_PlayerCard::Get_player_onoff()	{		return (bool)m_player_onoff;}
	void Sys_PlayerCard::Set_player_onoff(bool v)
	{
		m_player_onoff=v;
	}

	int16 Sys_PlayerLevel::Get_sid()	{		return (int16)m_sid;}
	void Sys_PlayerLevel::Set_sid(int16 v)
	{
		m_sid=v;
	}

	acstr Sys_PlayerLevel::Get_name()	{		return (acstr)m_name;}
	void Sys_PlayerLevel::Set_name(acstr v)
	{
		if(!v){ throw _T("Sys_PlayerLevel::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	int8 Sys_PlayerLevel::Get_level()	{		return (int8)m_level;}
	void Sys_PlayerLevel::Set_level(int8 v)
	{
		if(v>100) v = (int8)100;
		if(v<1) v = 1;
		m_level=v;
	}

	int64 Sys_PlayerLevel::Get_max_exp()	{		return (int64)m_max_exp;}
	void Sys_PlayerLevel::Set_max_exp(int64 v)
	{
		m_max_exp=v;
	}

	int64 Sys_PlayerLevel::Get_max_cum_exp()	{		return (int64)m_max_cum_exp;}
	void Sys_PlayerLevel::Set_max_cum_exp(int64 v)
	{
		m_max_cum_exp=v;
	}

	int16 Sys_PlayerLevel::Get_better_accuracy_sq()	{		return (int16)m_better_accuracy_sq;}
	void Sys_PlayerLevel::Set_better_accuracy_sq(int16 v)
	{
		m_better_accuracy_sq=v;
	}

	int16 Sys_PlayerLevel::Get_better_accuracy_op()	{		return (int16)m_better_accuracy_op;}
	void Sys_PlayerLevel::Set_better_accuracy_op(int16 v)
	{
		m_better_accuracy_op=v;
	}

	int16 Sys_PlayerLevel::Get_better_accuracy_cl()	{		return (int16)m_better_accuracy_cl;}
	void Sys_PlayerLevel::Set_better_accuracy_cl(int16 v)
	{
		m_better_accuracy_cl=v;
	}

	int16 Sys_PlayerLevel::Get_better_power_sq()	{		return (int16)m_better_power_sq;}
	void Sys_PlayerLevel::Set_better_power_sq(int16 v)
	{
		m_better_power_sq=v;
	}

	int16 Sys_PlayerLevel::Get_better_power_op()	{		return (int16)m_better_power_op;}
	void Sys_PlayerLevel::Set_better_power_op(int16 v)
	{
		m_better_power_op=v;
	}

	int16 Sys_PlayerLevel::Get_better_power_cl()	{		return (int16)m_better_power_cl;}
	void Sys_PlayerLevel::Set_better_power_cl(int16 v)
	{
		m_better_power_cl=v;
	}

	float Sys_PlayerLevel::Get_pitcher_speed_ov()	{		return (float)m_pitcher_speed_ov;}
	void Sys_PlayerLevel::Set_pitcher_speed_ov(float v)
	{
		m_pitcher_speed_ov=v;
	}

	float Sys_PlayerLevel::Get_pitcher_speed_tq()	{		return (float)m_pitcher_speed_tq;}
	void Sys_PlayerLevel::Set_pitcher_speed_tq(float v)
	{
		m_pitcher_speed_tq=v;
	}

	float Sys_PlayerLevel::Get_pitcher_speed_sa()	{		return (float)m_pitcher_speed_sa;}
	void Sys_PlayerLevel::Set_pitcher_speed_sa(float v)
	{
		m_pitcher_speed_sa=v;
	}

	float Sys_PlayerLevel::Get_pitcher_speed_un()	{		return (float)m_pitcher_speed_un;}
	void Sys_PlayerLevel::Set_pitcher_speed_un(float v)
	{
		m_pitcher_speed_un=v;
	}

	int16 Sys_PlayerLevel::Get_pitcher_focus_ov()	{		return (int16)m_pitcher_focus_ov;}
	void Sys_PlayerLevel::Set_pitcher_focus_ov(int16 v)
	{
		m_pitcher_focus_ov=v;
	}

	int16 Sys_PlayerLevel::Get_pitcher_focus_tq()	{		return (int16)m_pitcher_focus_tq;}
	void Sys_PlayerLevel::Set_pitcher_focus_tq(int16 v)
	{
		m_pitcher_focus_tq=v;
	}

	int16 Sys_PlayerLevel::Get_pitcher_focus_sa()	{		return (int16)m_pitcher_focus_sa;}
	void Sys_PlayerLevel::Set_pitcher_focus_sa(int16 v)
	{
		m_pitcher_focus_sa=v;
	}

	int16 Sys_PlayerLevel::Get_pitcher_focus_un()	{		return (int16)m_pitcher_focus_un;}
	void Sys_PlayerLevel::Set_pitcher_focus_un(int16 v)
	{
		m_pitcher_focus_un=v;
	}

	int16 Sys_PlayerLevel::Get_pitcher_breakingball_ov()	{		return (int16)m_pitcher_breakingball_ov;}
	void Sys_PlayerLevel::Set_pitcher_breakingball_ov(int16 v)
	{
		m_pitcher_breakingball_ov=v;
	}

	int16 Sys_PlayerLevel::Get_pitcher_breakingball_tq()	{		return (int16)m_pitcher_breakingball_tq;}
	void Sys_PlayerLevel::Set_pitcher_breakingball_tq(int16 v)
	{
		m_pitcher_breakingball_tq=v;
	}

	int16 Sys_PlayerLevel::Get_pitcher_breakingball_sa()	{		return (int16)m_pitcher_breakingball_sa;}
	void Sys_PlayerLevel::Set_pitcher_breakingball_sa(int16 v)
	{
		m_pitcher_breakingball_sa=v;
	}

	int16 Sys_PlayerLevel::Get_pitcher_breakingball_un()	{		return (int16)m_pitcher_breakingball_un;}
	void Sys_PlayerLevel::Set_pitcher_breakingball_un(int16 v)
	{
		m_pitcher_breakingball_un=v;
	}

	EBatterAbility Sys_PlayerSkillSticker::Get_better_skill1_type()	{		return (EBatterAbility)m_better_skill1_type;}
	void Sys_PlayerSkillSticker::Set_better_skill1_type(EBatterAbility v)
	{
		if(v<eBEGIN_EBatterAbility || v>=eEND_EBatterAbility)
		{
			jERROR(_T("Sys_PlayerSkillSticker::Set_better_skill1_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBatterAbility,eEND_EBatterAbility,v);
		}
		m_better_skill1_type=v;
	}

	EPitcherAbility Sys_PlayerSkillSticker::Get_Pitcher_skill1_type()	{		return (EPitcherAbility)m_Pitcher_skill1_type;}
	void Sys_PlayerSkillSticker::Set_Pitcher_skill1_type(EPitcherAbility v)
	{
		if(v<eBEGIN_EPitcherAbility || v>=eEND_EPitcherAbility)
		{
			jERROR(_T("Sys_PlayerSkillSticker::Set_Pitcher_skill1_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPitcherAbility,eEND_EPitcherAbility,v);
		}
		m_Pitcher_skill1_type=v;
	}

	int8 Sys_PlayerSkillSticker::Get_unlock_player_level()	{		return (int8)m_unlock_player_level;}
	void Sys_PlayerSkillSticker::Set_unlock_player_level(int8 v)
	{
		m_unlock_player_level=v;
	}

	Sys_Quest_id_t Sys_Quest::Get_sid()	{		return (Sys_Quest_id_t)m_sid;}
	void Sys_Quest::Set_sid(uint16 v)
	{
		m_sid=v;
	}

	acstr Sys_Quest::Get_name()	{		return (acstr)m_name;}
	void Sys_Quest::Set_name(acstr v)
	{
		if(!v){ throw _T("Sys_Quest::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	EQuestType Sys_Quest::Get_quest_type()	{		return (EQuestType)m_quest_type;}
	void Sys_Quest::Set_quest_type(EQuestType v)
	{
		if(v<eBEGIN_EQuestType || v>=eEND_EQuestType)
		{
			jERROR(_T("Sys_Quest::Set_quest_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EQuestType,eEND_EQuestType,v);
		}
		m_quest_type=v;
	}

	int32 Sys_Quest::Get_reward_money()	{		return (int32)m_reward_money;}
	void Sys_Quest::Set_reward_money(int32 v)
	{
		m_reward_money=v;
	}

	int32 Sys_Quest::Get_reward_exp()	{		return (int32)m_reward_exp;}
	void Sys_Quest::Set_reward_exp(int32 v)
	{
		m_reward_exp=v;
	}

	Sys_Title_ptr Sys_Quest::Get_title()	{			return m_title_ptr;}
	void Sys_Quest::Set_title(Sys_Title_ptr v)
	{
		m_title_ptr = v;
	}

	acstr Sys_Quest::Get_help()	{		return (acstr)m_help;}
	void Sys_Quest::Set_help(acstr v)
	{
		if(!v){ throw _T("Sys_Quest::Set_help( val = NULL )");}
		nExcelUtil::jSetter(m_help , v, 1024);
	}

	EQuestConditionType Sys_Quest::Get_condition_type1()	{		return (EQuestConditionType)m_condition_type1;}
	void Sys_Quest::Set_condition_type1(EQuestConditionType v)
	{
		if(v<eBEGIN_EQuestConditionType || v>=eEND_EQuestConditionType)
		{
			jERROR(_T("Sys_Quest::Set_condition_type1(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EQuestConditionType,eEND_EQuestConditionType,v);
		}
		m_condition_type1=v;
	}

	acstr Sys_Quest::Get_condition1()	{		return (acstr)m_condition1;}
	void Sys_Quest::Set_condition1(acstr v)
	{
		if(!v){ throw _T("Sys_Quest::Set_condition1( val = NULL )");}
		nExcelUtil::jSetter(m_condition1 , v, 1024);
	}

	int32 Sys_Quest::Get_condition_value1()	{		return (int32)m_condition_value1;}
	void Sys_Quest::Set_condition_value1(int32 v)
	{
		m_condition_value1=v;
	}

	EQuestConditionType Sys_Quest::Get_condition_type2()	{		return (EQuestConditionType)m_condition_type2;}
	void Sys_Quest::Set_condition_type2(EQuestConditionType v)
	{
		if(v<eBEGIN_EQuestConditionType || v>=eEND_EQuestConditionType)
		{
			jERROR(_T("Sys_Quest::Set_condition_type2(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EQuestConditionType,eEND_EQuestConditionType,v);
		}
		m_condition_type2=v;
	}

	acstr Sys_Quest::Get_condition2()	{		return (acstr)m_condition2;}
	void Sys_Quest::Set_condition2(acstr v)
	{
		if(!v){ throw _T("Sys_Quest::Set_condition2( val = NULL )");}
		nExcelUtil::jSetter(m_condition2 , v, 1024);
	}

	int32 Sys_Quest::Get_condition_value2()	{		return (int32)m_condition_value2;}
	void Sys_Quest::Set_condition_value2(int32 v)
	{
		m_condition_value2=v;
	}

	EItemCategory Sys_Quest::Get_quest_reward_item1()	{		return (EItemCategory)m_quest_reward_item1;}
	void Sys_Quest::Set_quest_reward_item1(EItemCategory v)
	{
		if(v<eBEGIN_EItemCategory || v>=eEND_EItemCategory)
		{
			jERROR(_T("Sys_Quest::Set_quest_reward_item1(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemCategory,eEND_EItemCategory,v);
		}
		m_quest_reward_item1=v;
	}

	EItemGradeType Sys_Quest::Get_quest_reward_item_grade1()	{		return (EItemGradeType)m_quest_reward_item_grade1;}
	void Sys_Quest::Set_quest_reward_item_grade1(EItemGradeType v)
	{
		if(v<eBEGIN_EItemGradeType || v>=eEND_EItemGradeType)
		{
			jERROR(_T("Sys_Quest::Set_quest_reward_item_grade1(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemGradeType,eEND_EItemGradeType,v);
		}
		m_quest_reward_item_grade1=v;
	}

	int16 Sys_Quest::Get_quest_reward_percent1()	{		return (int16)m_quest_reward_percent1;}
	void Sys_Quest::Set_quest_reward_percent1(int16 v)
	{
		if(v>1000) v = (int16)1000;
		if(v<0) v = 0;
		m_quest_reward_percent1=v;
	}

	EItemCategory Sys_Quest::Get_quest_reward_item2()	{		return (EItemCategory)m_quest_reward_item2;}
	void Sys_Quest::Set_quest_reward_item2(EItemCategory v)
	{
		if(v<eBEGIN_EItemCategory || v>=eEND_EItemCategory)
		{
			jERROR(_T("Sys_Quest::Set_quest_reward_item2(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemCategory,eEND_EItemCategory,v);
		}
		m_quest_reward_item2=v;
	}

	EItemGradeType Sys_Quest::Get_quest_reward_item_grade2()	{		return (EItemGradeType)m_quest_reward_item_grade2;}
	void Sys_Quest::Set_quest_reward_item_grade2(EItemGradeType v)
	{
		if(v<eBEGIN_EItemGradeType || v>=eEND_EItemGradeType)
		{
			jERROR(_T("Sys_Quest::Set_quest_reward_item_grade2(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemGradeType,eEND_EItemGradeType,v);
		}
		m_quest_reward_item_grade2=v;
	}

	int16 Sys_Quest::Get_quest_reward_percent2()	{		return (int16)m_quest_reward_percent2;}
	void Sys_Quest::Set_quest_reward_percent2(int16 v)
	{
		if(v>1000) v = (int16)1000;
		if(v<-1) v = -1;
		m_quest_reward_percent2=v;
	}

	Sys_Title_id_t Sys_Title::Get_sid()	{		return (Sys_Title_id_t)m_sid;}
	void Sys_Title::Set_sid(uint16 v)
	{
		m_sid=v;
	}

	acstr Sys_Title::Get_name()	{		return (acstr)m_name;}
	void Sys_Title::Set_name(acstr v)
	{
		if(!v){ throw _T("Sys_Title::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	int32 Sys_Title::Get_group()	{		return (int32)m_group;}
	void Sys_Title::Set_group(int32 v)
	{
		m_group=v;
	}

	EBaseballObjectType Sys_Title::Get_object_type()	{		return (EBaseballObjectType)m_object_type;}
	void Sys_Title::Set_object_type(EBaseballObjectType v)
	{
		if(v<eBEGIN_EBaseballObjectType || v>=eEND_EBaseballObjectType)
		{
			jERROR(_T("Sys_Title::Set_object_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBaseballObjectType,eEND_EBaseballObjectType,v);
		}
		m_object_type=v;
	}

	acstr Sys_Title::Get_help()	{		return (acstr)m_help;}
	void Sys_Title::Set_help(acstr v)
	{
		if(!v){ throw _T("Sys_Title::Set_help( val = NULL )");}
		nExcelUtil::jSetter(m_help , v, 256);
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_baseball_table_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_Base_PlayerStat g_Sys_Base_PlayerStat;


tcstr Sys_Base_PlayerStat::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_sid(FromString(out[index++],m_sid) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getA());
	szKEY = Get_name();
	Set_better_power(FromString(out[index++],m_better_power) );
	Set_better_focus(FromString(out[index++],m_better_focus) );
	Set_pitcher_control(FromString(out[index++],m_pitcher_control) );
	Set_pitcher_ballspeed(FromString(out[index++],m_pitcher_ballspeed) );
	Set_pitcher_breakingball_value(FromString(out[index++],m_pitcher_breakingball_value) );
	Set_pitcher_breakingball_type(FromString(out[index++],m_pitcher_breakingball_type) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_PlayerCard g_Sys_PlayerCard;


tcstr Sys_PlayerCard::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	szKEY = Sys_Base_PlayerStat::ReadCSV(iRecord ,out,index,false);
	FromString(&m_player_leftright,out[index++]);
	Set_better_form(FromString(out[index++],m_better_form) );
	Set_pitcher_form(FromString(out[index++],m_pitcher_form) );
	Set_player_nation(FromString(out[index++],m_player_nation) );
	Set_player_year(FromString(out[index++],m_player_year) );
	Set_player_grade(FromString(out[index++],m_player_grade) );
	Set_body_type(FromString(out[index++],m_body_type) );
	Set_player_level(FromString(out[index++],m_player_level) );
	Set_player_type(FromString(out[index++],m_player_type) );
	Set_price_type(FromString(out[index++],m_price_type) );
	Set_price_money(FromString(out[index++],m_price_money) );
	Set_price_cash(FromString(out[index++],m_price_cash) );
	Set_sell_status(FromString(out[index++],m_sell_status) );
	FromString(&m_sell_start_date,out[index++]);
	FromString(&m_sell_end_date,out[index++]);
	Set_player_level_min(FromString(out[index++],m_player_level_min) );
	Set_player_level_max(FromString(out[index++],m_player_level_max) );
	Set_sticker_slot_count(FromString(out[index++],m_sticker_slot_count) );
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_baseball_table)Sys_PlayerCard::skill_sticker"),(int32)iRecord);
	Excel_PostLoader_registe(&m_skill_sticker_ptr_vec , out[index++].c_str() ,0 , szHelp ) ;
	FromString(&m_player_onoff,out[index++]);
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_PlayerLevel g_Sys_PlayerLevel;


tcstr Sys_PlayerLevel::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_sid(FromString(out[index++],m_sid) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getA());
	szKEY = Get_name();
	Set_level(FromString(out[index++],m_level) );
	Set_max_exp(FromString(out[index++],m_max_exp) );
	Set_max_cum_exp(FromString(out[index++],m_max_cum_exp) );
	Set_better_accuracy_sq(FromString(out[index++],m_better_accuracy_sq) );
	Set_better_accuracy_op(FromString(out[index++],m_better_accuracy_op) );
	Set_better_accuracy_cl(FromString(out[index++],m_better_accuracy_cl) );
	Set_better_power_sq(FromString(out[index++],m_better_power_sq) );
	Set_better_power_op(FromString(out[index++],m_better_power_op) );
	Set_better_power_cl(FromString(out[index++],m_better_power_cl) );
	Set_pitcher_speed_ov(FromString(out[index++],m_pitcher_speed_ov) );
	Set_pitcher_speed_tq(FromString(out[index++],m_pitcher_speed_tq) );
	Set_pitcher_speed_sa(FromString(out[index++],m_pitcher_speed_sa) );
	Set_pitcher_speed_un(FromString(out[index++],m_pitcher_speed_un) );
	Set_pitcher_focus_ov(FromString(out[index++],m_pitcher_focus_ov) );
	Set_pitcher_focus_tq(FromString(out[index++],m_pitcher_focus_tq) );
	Set_pitcher_focus_sa(FromString(out[index++],m_pitcher_focus_sa) );
	Set_pitcher_focus_un(FromString(out[index++],m_pitcher_focus_un) );
	Set_pitcher_breakingball_ov(FromString(out[index++],m_pitcher_breakingball_ov) );
	Set_pitcher_breakingball_tq(FromString(out[index++],m_pitcher_breakingball_tq) );
	Set_pitcher_breakingball_sa(FromString(out[index++],m_pitcher_breakingball_sa) );
	Set_pitcher_breakingball_un(FromString(out[index++],m_pitcher_breakingball_un) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_PlayerSkillSticker g_Sys_PlayerSkillSticker;


tcstr Sys_PlayerSkillSticker::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	szKEY = Sys_Base_PlayerStat::ReadCSV(iRecord ,out,index,false);
	Set_better_skill1_type(FromString(out[index++],m_better_skill1_type) );
	Set_Pitcher_skill1_type(FromString(out[index++],m_Pitcher_skill1_type) );
	Set_unlock_player_level(FromString(out[index++],m_unlock_player_level) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_Quest g_Sys_Quest;


tcstr Sys_Quest::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_sid(FromString(out[index++],m_sid) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getA());
	szKEY = Get_name();
	Set_quest_type(FromString(out[index++],m_quest_type) );
	Set_reward_money(FromString(out[index++],m_reward_money) );
	Set_reward_exp(FromString(out[index++],m_reward_exp) );
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_baseball_table)Sys_Quest::title"),(int32)iRecord);
	Excel_PostLoader_registe(&m_title_ptr, out[index++].c_str()  , szHelp );
	Set_help(nExcelUtil_StringConverter(out[index++]).getA());
	Set_condition_type1(FromString(out[index++],m_condition_type1) );
	Set_condition1(nExcelUtil_StringConverter(out[index++]).getA());
	Set_condition_value1(FromString(out[index++],m_condition_value1) );
	Set_condition_type2(FromString(out[index++],m_condition_type2) );
	Set_condition2(nExcelUtil_StringConverter(out[index++]).getA());
	Set_condition_value2(FromString(out[index++],m_condition_value2) );
	Set_quest_reward_item1(FromString(out[index++],m_quest_reward_item1) );
	Set_quest_reward_item_grade1(FromString(out[index++],m_quest_reward_item_grade1) );
	Set_quest_reward_percent1(FromString(out[index++],m_quest_reward_percent1) );
	Set_quest_reward_item2(FromString(out[index++],m_quest_reward_item2) );
	Set_quest_reward_item_grade2(FromString(out[index++],m_quest_reward_item_grade2) );
	Set_quest_reward_percent2(FromString(out[index++],m_quest_reward_percent2) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_Title g_Sys_Title;


tcstr Sys_Title::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_sid(FromString(out[index++],m_sid) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getA());
	szKEY = Get_name();
	Set_group(FromString(out[index++],m_group) );
	Set_object_type(FromString(out[index++],m_object_type) );
	Set_help(nExcelUtil_StringConverter(out[index++]).getA());
	return szKEY;
}

void Sys_Base_PlayerStat::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_PlayerCard::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_PlayerLevel::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_PlayerSkillSticker::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_Quest::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_Title::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Title_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Base_PlayerStat>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_PlayerCard>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_PlayerLevel>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_PlayerSkillSticker>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Quest>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Title>);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_baseball_table)
		{
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Base_PlayerStat>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Base_PlayerStat*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Base_PlayerStat*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Base_PlayerStat*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Base_PlayerStat)
			for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Base_PlayerStat)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Base_PlayerStat>* p = &g_Sys_Base_PlayerStat;
				jSQ_g_var(p , g_Sys_Base_PlayerStat);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_PlayerCard>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_PlayerCard*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_PlayerCard*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_PlayerCard*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_PlayerCard)
			for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
				jSQ_fn(GetBase_Sys_Base_PlayerStat,"Sys_Base_PlayerStat*()","Get base Table")
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_PlayerCard)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_PlayerCard>* p = &g_Sys_PlayerCard;
				jSQ_g_var(p , g_Sys_PlayerCard);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_PlayerLevel>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_PlayerLevel*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_PlayerLevel*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_PlayerLevel*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_PlayerLevel)
			for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_PlayerLevel)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_PlayerLevel>* p = &g_Sys_PlayerLevel;
				jSQ_g_var(p , g_Sys_PlayerLevel);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_PlayerSkillSticker>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_PlayerSkillSticker*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_PlayerSkillSticker*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_PlayerSkillSticker*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_PlayerSkillSticker)
			for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
				jSQ_fn(GetBase_Sys_Base_PlayerStat,"Sys_Base_PlayerStat*()","Get base Table")
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_PlayerSkillSticker)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_PlayerSkillSticker>* p = &g_Sys_PlayerSkillSticker;
				jSQ_g_var(p , g_Sys_PlayerSkillSticker);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Quest>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Quest*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Quest*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Quest*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Quest)
			for_each_nEXCEL_Sys_Quest_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Quest)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Quest>* p = &g_Sys_Quest;
				jSQ_g_var(p , g_Sys_Quest);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Title>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Title*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Title*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Title*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Title)
			for_each_nEXCEL_Sys_Title_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Title)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Title>* p = &g_Sys_Title;
				jSQ_g_var(p , g_Sys_Title);
			}

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

