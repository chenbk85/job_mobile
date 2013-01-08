/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_baseball_table2.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_baseball_table2_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_baseball_table2_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_baseball_table2_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE

namespace nMech {
	namespace nEXCEL {


#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_BreakingBallUpgrade
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_BreakingBallUpgrade();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_BreakingBallUpgrade


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	Sys_BreakingBallState_id_t Sys_BreakingBallUpgrade::Get_id()	{		return (Sys_BreakingBallState_id_t)m_id_u16;}
	void Sys_BreakingBallUpgrade::Set_id(uint16 v)
	{
		m_id_u16=v;
	}

	acstr Sys_BreakingBallUpgrade::Get_name()	{		return (acstr)m_name_a32;}
	void Sys_BreakingBallUpgrade::Set_name(acstr v)
	{
		if(!v){ throw _T("Sys_BreakingBallUpgrade::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name_a32 , v, 32);
	}

	EPlayerBreakingBall Sys_BreakingBallUpgrade::Get_breakingball_name()	{		return (EPlayerBreakingBall)m_breakingball_name_e;}
	void Sys_BreakingBallUpgrade::Set_breakingball_name(EPlayerBreakingBall v)
	{
		if(v<eBEGIN_EPlayerBreakingBall || v>=eEND_EPlayerBreakingBall)
		{
			jERROR(_T("Sys_BreakingBallUpgrade::Set_breakingball_name(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerBreakingBall,eEND_EPlayerBreakingBall,v);
		}
		m_breakingball_name_e=v;
	}

	EPlayerBreakingBall Sys_BreakingBallUpgrade::Get_breakingball_result()	{		return (EPlayerBreakingBall)m_breakingball_result_e;}
	void Sys_BreakingBallUpgrade::Set_breakingball_result(EPlayerBreakingBall v)
	{
		if(v<eBEGIN_EPlayerBreakingBall || v>=eEND_EPlayerBreakingBall)
		{
			jERROR(_T("Sys_BreakingBallUpgrade::Set_breakingball_result(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerBreakingBall,eEND_EPlayerBreakingBall,v);
		}
		m_breakingball_result_e=v;
	}

	int16 Sys_BreakingBallUpgrade::Get_breaking_need_level()	{		return (int16)m_breaking_need_level_i16;}
	void Sys_BreakingBallUpgrade::Set_breaking_need_level(int16 v)
	{
		if(v>100) v = (int16)100;
		if(v<0) v = 0;
		m_breaking_need_level_i16=v;
	}

	EBreakingBallPitch Sys_BreakingBallUpgrade::Get_breaking_pitch()	{		return (EBreakingBallPitch)m_breaking_pitch_e;}
	void Sys_BreakingBallUpgrade::Set_breaking_pitch(EBreakingBallPitch v)
	{
		if(v<eBEGIN_EBreakingBallPitch || v>=eEND_EBreakingBallPitch)
		{
			jERROR(_T("Sys_BreakingBallUpgrade::Set_breaking_pitch(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBreakingBallPitch,eEND_EBreakingBallPitch,v);
		}
		m_breaking_pitch_e=v;
	}

	EBreakingBallRotation Sys_BreakingBallUpgrade::Get_ball_rotation()	{		return (EBreakingBallRotation)m_ball_rotation_e;}
	void Sys_BreakingBallUpgrade::Set_ball_rotation(EBreakingBallRotation v)
	{
		if(v<eBEGIN_EBreakingBallRotation || v>=eEND_EBreakingBallRotation)
		{
			jERROR(_T("Sys_BreakingBallUpgrade::Set_ball_rotation(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBreakingBallRotation,eEND_EBreakingBallRotation,v);
		}
		m_ball_rotation_e=v;
	}

	int32 Sys_BreakingBallUpgrade::Get_breaking_open_date()	{		return (int32)m_breaking_open_date_i32;}
	void Sys_BreakingBallUpgrade::Set_breaking_open_date(int32 v)
	{
		m_breaking_open_date_i32=v;
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_baseball_table2_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

OUT nMech::nUtil::jCSV_File<Sys_BreakingBallUpgrade> g_Sys_BreakingBallUpgrade;


tcstr Sys_BreakingBallUpgrade::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_id(FromString(&m_id_u16,out[index++]) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getA());
	szKEY = Get_name();
	Set_breakingball_name(FromString(&m_breakingball_name_e,out[index++]) );
	Set_breakingball_result(FromString(&m_breakingball_result_e,out[index++]) );
	Set_breaking_need_level(FromString(&m_breaking_need_level_i16,out[index++]) );
	Set_breaking_pitch(FromString(&m_breaking_pitch_e,out[index++]) );
	Set_ball_rotation(FromString(&m_ball_rotation_e,out[index++]) );
	Set_breaking_open_date(FromString(&m_breaking_open_date_i32,out[index++]) );
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

	typedef nMech::nUtil::jCSV_File<nMech::nEXCEL::Sys_BreakingBallUpgrade> Sys_BreakingBallUpgrade_csv_file_t;
	DECLARE_INSTANCE_TYPE(Sys_BreakingBallUpgrade_csv_file_t);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_baseball_table2)
		{
			jSQ_Interface(Sys_BreakingBallUpgrade_csv_file_t)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_BreakingBallUpgrade*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_BreakingBallUpgrade*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_BreakingBallUpgrade*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_BreakingBallUpgrade)
			for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_BreakingBallUpgrade)
			jSQ_end();
			jSQ_g_var(&g_Sys_BreakingBallUpgrade,g_Sys_BreakingBallUpgrade);

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

