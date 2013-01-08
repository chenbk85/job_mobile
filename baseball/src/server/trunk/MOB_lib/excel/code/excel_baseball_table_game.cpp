/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_baseball_table_game.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_baseball_table_game_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_baseball_table_game_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_baseball_table_game_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE


for_each_nEXCEL_excel_baseball_table_game_ENUM(jEXCEL_SQ_DECLARE_ENUM_TYPE);
namespace nMech {
	namespace nEXCEL {

jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ERunnerStateRound[] = 
{
	{ 8 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_ERunnerStateRound_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ERunnerStateType[] = 
{
	{ 3 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_ERunnerStateType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Runner_State
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Runner_State();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Runner_State


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	Sys_Runner_State_id_t Sys_Runner_State::Get_index()	{		return (Sys_Runner_State_id_t)m_index;}
	void Sys_Runner_State::Set_index(uint16 v)
	{
		m_index=v;
	}

	ERunnerStateType Sys_Runner_State::Get_category()	{		return (ERunnerStateType)m_category;}
	void Sys_Runner_State::Set_category(ERunnerStateType v)
	{
		if(v<eBEGIN_ERunnerStateType || v>=eEND_ERunnerStateType)
		{
			jERROR(_T("Sys_Runner_State::Set_category(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ERunnerStateType,eEND_ERunnerStateType,v);
		}
		m_category=v;
	}

	ERunnerStateRound Sys_Runner_State::Get_state_1r()	{		return (ERunnerStateRound)m_state_1r;}
	void Sys_Runner_State::Set_state_1r(ERunnerStateRound v)
	{
		if(v<eBEGIN_ERunnerStateRound || v>=eEND_ERunnerStateRound)
		{
			jERROR(_T("Sys_Runner_State::Set_state_1r(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ERunnerStateRound,eEND_ERunnerStateRound,v);
		}
		m_state_1r=v;
	}

	ERunnerStateRound Sys_Runner_State::Get_state_2r()	{		return (ERunnerStateRound)m_state_2r;}
	void Sys_Runner_State::Set_state_2r(ERunnerStateRound v)
	{
		if(v<eBEGIN_ERunnerStateRound || v>=eEND_ERunnerStateRound)
		{
			jERROR(_T("Sys_Runner_State::Set_state_2r(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ERunnerStateRound,eEND_ERunnerStateRound,v);
		}
		m_state_2r=v;
	}

	ERunnerStateRound Sys_Runner_State::Get_state_3r()	{		return (ERunnerStateRound)m_state_3r;}
	void Sys_Runner_State::Set_state_3r(ERunnerStateRound v)
	{
		if(v<eBEGIN_ERunnerStateRound || v>=eEND_ERunnerStateRound)
		{
			jERROR(_T("Sys_Runner_State::Set_state_3r(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ERunnerStateRound,eEND_ERunnerStateRound,v);
		}
		m_state_3r=v;
	}

	ERunnerStateRound Sys_Runner_State::Get_state_4r()	{		return (ERunnerStateRound)m_state_4r;}
	void Sys_Runner_State::Set_state_4r(ERunnerStateRound v)
	{
		if(v<eBEGIN_ERunnerStateRound || v>=eEND_ERunnerStateRound)
		{
			jERROR(_T("Sys_Runner_State::Set_state_4r(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ERunnerStateRound,eEND_ERunnerStateRound,v);
		}
		m_state_4r=v;
	}

	ERunnerStateRound Sys_Runner_State::Get_state_5r()	{		return (ERunnerStateRound)m_state_5r;}
	void Sys_Runner_State::Set_state_5r(ERunnerStateRound v)
	{
		if(v<eBEGIN_ERunnerStateRound || v>=eEND_ERunnerStateRound)
		{
			jERROR(_T("Sys_Runner_State::Set_state_5r(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ERunnerStateRound,eEND_ERunnerStateRound,v);
		}
		m_state_5r=v;
	}

	ERunnerStateRound Sys_Runner_State::Get_state_6r()	{		return (ERunnerStateRound)m_state_6r;}
	void Sys_Runner_State::Set_state_6r(ERunnerStateRound v)
	{
		if(v<eBEGIN_ERunnerStateRound || v>=eEND_ERunnerStateRound)
		{
			jERROR(_T("Sys_Runner_State::Set_state_6r(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ERunnerStateRound,eEND_ERunnerStateRound,v);
		}
		m_state_6r=v;
	}

	ERunnerStateRound Sys_Runner_State::Get_state_7r()	{		return (ERunnerStateRound)m_state_7r;}
	void Sys_Runner_State::Set_state_7r(ERunnerStateRound v)
	{
		if(v<eBEGIN_ERunnerStateRound || v>=eEND_ERunnerStateRound)
		{
			jERROR(_T("Sys_Runner_State::Set_state_7r(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ERunnerStateRound,eEND_ERunnerStateRound,v);
		}
		m_state_7r=v;
	}

	ERunnerStateRound Sys_Runner_State::Get_state_8r()	{		return (ERunnerStateRound)m_state_8r;}
	void Sys_Runner_State::Set_state_8r(ERunnerStateRound v)
	{
		if(v<eBEGIN_ERunnerStateRound || v>=eEND_ERunnerStateRound)
		{
			jERROR(_T("Sys_Runner_State::Set_state_8r(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ERunnerStateRound,eEND_ERunnerStateRound,v);
		}
		m_state_8r=v;
	}

	ERunnerStateRound Sys_Runner_State::Get_state_9r()	{		return (ERunnerStateRound)m_state_9r;}
	void Sys_Runner_State::Set_state_9r(ERunnerStateRound v)
	{
		if(v<eBEGIN_ERunnerStateRound || v>=eEND_ERunnerStateRound)
		{
			jERROR(_T("Sys_Runner_State::Set_state_9r(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ERunnerStateRound,eEND_ERunnerStateRound,v);
		}
		m_state_9r=v;
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_baseball_table_game_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_Runner_State g_Sys_Runner_State;


tcstr Sys_Runner_State::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_index(FromString(out[index++],m_index) );
	Set_category(FromString(out[index++],m_category) );
	Set_state_1r(FromString(out[index++],m_state_1r) );
	Set_state_2r(FromString(out[index++],m_state_2r) );
	Set_state_3r(FromString(out[index++],m_state_3r) );
	Set_state_4r(FromString(out[index++],m_state_4r) );
	Set_state_5r(FromString(out[index++],m_state_5r) );
	Set_state_6r(FromString(out[index++],m_state_6r) );
	Set_state_7r(FromString(out[index++],m_state_7r) );
	Set_state_8r(FromString(out[index++],m_state_8r) );
	Set_state_9r(FromString(out[index++],m_state_9r) );
	return szKEY;
}

void Sys_Runner_State::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Runner_State>);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_baseball_table_game)
		{
			{
				SquirrelObject enumRoot= nSQ::jSQ_GetEnumTable();
				for_each_nEXCEL_excel_baseball_table_game_ENUM(jEXCEL_SQ_bind_EnumField_BEGIN);
				for_each_nEXCEL_ERunnerStateRound_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_ERunnerStateType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
			}
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Runner_State>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Runner_State*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Runner_State*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Runner_State*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Runner_State)
			for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Runner_State)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Runner_State>* p = &g_Sys_Runner_State;
				jSQ_g_var(p , g_Sys_Runner_State);
			}

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

