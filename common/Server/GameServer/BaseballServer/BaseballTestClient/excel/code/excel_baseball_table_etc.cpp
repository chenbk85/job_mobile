/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_baseball_table_etc.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_baseball_table_etc_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_baseball_table_etc_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_baseball_table_etc_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE

namespace nMech {
	namespace nEXCEL {


#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_BreakingBallUpgrade
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_BreakingBallUpgrade();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_BreakingBallUpgrade


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	Sys_BreakingBallState_id_t Sys_BreakingBallUpgrade::Get_id()	{		return (Sys_BreakingBallState_id_t)m_id;}
	void Sys_BreakingBallUpgrade::Set_id(uint16 v)
	{
		m_id=v;
	}

	tcstr Sys_BreakingBallUpgrade::Get_name()	{		return (tcstr)m_name;}
	void Sys_BreakingBallUpgrade::Set_name(tcstr v)
	{
		if(!v){ throw _T("Sys_BreakingBallUpgrade::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	EPlayerBreakingBall Sys_BreakingBallUpgrade::Get_type()	{		return (EPlayerBreakingBall)m_type;}
	void Sys_BreakingBallUpgrade::Set_type(EPlayerBreakingBall v)
	{
		if(v<eBEGIN_EPlayerBreakingBall || v>=eEND_EPlayerBreakingBall)
		{
			jERROR(_T("Sys_BreakingBallUpgrade::Set_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerBreakingBall,eEND_EPlayerBreakingBall,v);
		}
		m_type=v;
	}

	EPitcherForm Sys_BreakingBallUpgrade::Get_need_basicskill1()	{		return (EPitcherForm)m_need_basicskill1;}
	void Sys_BreakingBallUpgrade::Set_need_basicskill1(EPitcherForm v)
	{
		if(v<eBEGIN_EPitcherForm || v>=eEND_EPitcherForm)
		{
			jERROR(_T("Sys_BreakingBallUpgrade::Set_need_basicskill1(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPitcherForm,eEND_EPitcherForm,v);
		}
		m_need_basicskill1=v;
	}

	EPitcherForm Sys_BreakingBallUpgrade::Get_need_basicskill2()	{		return (EPitcherForm)m_need_basicskill2;}
	void Sys_BreakingBallUpgrade::Set_need_basicskill2(EPitcherForm v)
	{
		if(v<eBEGIN_EPitcherForm || v>=eEND_EPitcherForm)
		{
			jERROR(_T("Sys_BreakingBallUpgrade::Set_need_basicskill2(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPitcherForm,eEND_EPitcherForm,v);
		}
		m_need_basicskill2=v;
	}

	EPlayerBreakingBall Sys_BreakingBallUpgrade::Get_need_upgrade1()	{		return (EPlayerBreakingBall)m_need_upgrade1;}
	void Sys_BreakingBallUpgrade::Set_need_upgrade1(EPlayerBreakingBall v)
	{
		if(v<eBEGIN_EPlayerBreakingBall || v>=eEND_EPlayerBreakingBall)
		{
			jERROR(_T("Sys_BreakingBallUpgrade::Set_need_upgrade1(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerBreakingBall,eEND_EPlayerBreakingBall,v);
		}
		m_need_upgrade1=v;
	}

	EPlayerBreakingBall Sys_BreakingBallUpgrade::Get_need_upgrade2()	{		return (EPlayerBreakingBall)m_need_upgrade2;}
	void Sys_BreakingBallUpgrade::Set_need_upgrade2(EPlayerBreakingBall v)
	{
		if(v<eBEGIN_EPlayerBreakingBall || v>=eEND_EPlayerBreakingBall)
		{
			jERROR(_T("Sys_BreakingBallUpgrade::Set_need_upgrade2(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerBreakingBall,eEND_EPlayerBreakingBall,v);
		}
		m_need_upgrade2=v;
	}

	int16 Sys_BreakingBallUpgrade::Get_need_player_level()	{		return (int16)m_need_player_level;}
	void Sys_BreakingBallUpgrade::Set_need_player_level(int16 v)
	{
		if(v>100) v = (int16)100;
		if(v<1) v = 1;
		m_need_player_level=v;
	}

	int16 Sys_BreakingBallUpgrade::Get_equip_player_level()	{		return (int16)m_equip_player_level;}
	void Sys_BreakingBallUpgrade::Set_equip_player_level(int16 v)
	{
		if(v>100) v = (int16)100;
		if(v<1) v = 1;
		m_equip_player_level=v;
	}

	int16 Sys_BreakingBallUpgrade::Get_upgrade_need_time1()	{		return (int16)m_upgrade_need_time1;}
	void Sys_BreakingBallUpgrade::Set_upgrade_need_time1(int16 v)
	{
		if(v>100) v = (int16)100;
		if(v<0) v = 0;
		m_upgrade_need_time1=v;
	}

	int16 Sys_BreakingBallUpgrade::Get_upgrade_need_time2()	{		return (int16)m_upgrade_need_time2;}
	void Sys_BreakingBallUpgrade::Set_upgrade_need_time2(int16 v)
	{
		if(v>100) v = (int16)100;
		if(v<0) v = 0;
		m_upgrade_need_time2=v;
	}

	int32 Sys_BreakingBallUpgrade::Get_need_money()	{		return (int32)m_need_money;}
	void Sys_BreakingBallUpgrade::Set_need_money(int32 v)
	{
		m_need_money=v;
	}

	EBreakingBallPitch Sys_BreakingBallUpgrade::Get_breaking_pitch()	{		return (EBreakingBallPitch)m_breaking_pitch;}
	void Sys_BreakingBallUpgrade::Set_breaking_pitch(EBreakingBallPitch v)
	{
		if(v<eBEGIN_EBreakingBallPitch || v>=eEND_EBreakingBallPitch)
		{
			jERROR(_T("Sys_BreakingBallUpgrade::Set_breaking_pitch(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBreakingBallPitch,eEND_EBreakingBallPitch,v);
		}
		m_breaking_pitch=v;
	}

	EBreakingBallRotation Sys_BreakingBallUpgrade::Get_ball_rotation()	{		return (EBreakingBallRotation)m_ball_rotation;}
	void Sys_BreakingBallUpgrade::Set_ball_rotation(EBreakingBallRotation v)
	{
		if(v<eBEGIN_EBreakingBallRotation || v>=eEND_EBreakingBallRotation)
		{
			jERROR(_T("Sys_BreakingBallUpgrade::Set_ball_rotation(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBreakingBallRotation,eEND_EBreakingBallRotation,v);
		}
		m_ball_rotation=v;
	}

	SYSTEMTIME Sys_BreakingBallUpgrade::Get_open_date()	{		return (SYSTEMTIME)m_open_date;}
	void Sys_BreakingBallUpgrade::Set_open_date(SYSTEMTIME v)
	{
		m_open_date=v;
	}

	bool Sys_BreakingBallUpgrade::Get_first_open_breakingball()	{		return (bool)m_first_open_breakingball;}
	void Sys_BreakingBallUpgrade::Set_first_open_breakingball(bool v)
	{
		m_first_open_breakingball=v;
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_baseball_table_etc_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_BreakingBallUpgrade g_Sys_BreakingBallUpgrade;


tcstr Sys_BreakingBallUpgrade::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_id(FromString(out[index++],m_id) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getT());
	szKEY = Get_name();
	Set_type(FromString(out[index++],m_type) );
	Set_need_basicskill1(FromString(out[index++],m_need_basicskill1) );
	Set_need_basicskill2(FromString(out[index++],m_need_basicskill2) );
	Set_need_upgrade1(FromString(out[index++],m_need_upgrade1) );
	Set_need_upgrade2(FromString(out[index++],m_need_upgrade2) );
	Set_need_player_level(FromString(out[index++],m_need_player_level) );
	Set_equip_player_level(FromString(out[index++],m_equip_player_level) );
	Set_upgrade_need_time1(FromString(out[index++],m_upgrade_need_time1) );
	Set_upgrade_need_time2(FromString(out[index++],m_upgrade_need_time2) );
	Set_need_money(FromString(out[index++],m_need_money) );
	Set_breaking_pitch(FromString(out[index++],m_breaking_pitch) );
	Set_ball_rotation(FromString(out[index++],m_ball_rotation) );
	FromString(&m_open_date,out[index++]);
	FromString(&m_first_open_breakingball,out[index++]);
	return szKEY;
}

void Sys_BreakingBallUpgrade::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_BreakingBallUpgrade>);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_baseball_table_etc)
		{
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_BreakingBallUpgrade>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_BreakingBallUpgrade*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_BreakingBallUpgrade*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_BreakingBallUpgrade*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_BreakingBallUpgrade)
			for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_BreakingBallUpgrade)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_BreakingBallUpgrade>* p = &g_Sys_BreakingBallUpgrade;
				jSQ_g_var(p , g_Sys_BreakingBallUpgrade);
			}

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

