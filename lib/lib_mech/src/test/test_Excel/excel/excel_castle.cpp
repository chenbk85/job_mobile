/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_castle.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_castle_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_castle_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_castle_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE


for_each_nEXCEL_excel_castle_ENUM(jEXCEL_SQ_DECLARE_ENUM_TYPE);
namespace nMech {
	namespace nEXCEL {

jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_Evillage_Condition[] = 
{
	{ 5 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_Evillage_Condition_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Castle
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Castle();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Castle


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	uint16 Sys_Castle::Get_csid()	{		return (uint16)m_csid;}
	void Sys_Castle::Set_csid(uint16 v)
	{
		m_csid=v;
	}

	tcstr Sys_Castle::Get_name()	{		return (tcstr)m_name;}
	void Sys_Castle::Set_name(tcstr v)
	{
		if(!v){ throw _T("Sys_Castle::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	tcstr Sys_Castle::Get_name_kor()	{		return (tcstr)m_name_kor;}
	void Sys_Castle::Set_name_kor(tcstr v)
	{
		if(!v){ throw _T("Sys_Castle::Set_name_kor( val = NULL )");}
		nExcelUtil::jSetter(m_name_kor , v, 32);
	}

	Sys_Hero_id_t Sys_Castle::Get_default_gsid()	{		return (Sys_Hero_id_t)m_default_gsid;}
	void Sys_Castle::Set_default_gsid(uint16 v)
	{
		m_default_gsid=v;
	}

	tcstr Sys_Castle::Get_force_gen_name()	{		return (tcstr)m_force_gen_name;}
	void Sys_Castle::Set_force_gen_name(tcstr v)
	{
		if(!v){ throw _T("Sys_Castle::Set_force_gen_name( val = NULL )");}
		nExcelUtil::jSetter(m_force_gen_name , v, 32);
	}

	Sys_Castle_id_t Sys_CastlePos::Get_cpsid()	{		return (Sys_Castle_id_t)m_cpsid;}
	void Sys_CastlePos::Set_cpsid(uint16 v)
	{
		m_cpsid=v;
	}

	uint16 Sys_CastlePos::Get_x()	{		return (uint16)m_x;}
	void Sys_CastlePos::Set_x(uint16 v)
	{
		m_x=v;
	}

	uint16 Sys_CastlePos::Get_y()	{		return (uint16)m_y;}
	void Sys_CastlePos::Set_y(uint16 v)
	{
		m_y=v;
	}

	tcstr Sys_CastlePos::Get_castle_map()	{		return (tcstr)m_castle_map;}
	void Sys_CastlePos::Set_castle_map(tcstr v)
	{
		if(!v){ throw _T("Sys_CastlePos::Set_castle_map( val = NULL )");}
		nExcelUtil::jSetter(m_castle_map , v, 32);
	}

	Sys_TownPos_id_t Sys_TownPos::Get_tpsid()	{		return (Sys_TownPos_id_t)m_tpsid;}
	void Sys_TownPos::Set_tpsid(uint16 v)
	{
		m_tpsid=v;
	}

	uint16 Sys_TownPos::Get_x()	{		return (uint16)m_x;}
	void Sys_TownPos::Set_x(uint16 v)
	{
		m_x=v;
	}

	uint16 Sys_TownPos::Get_y()	{		return (uint16)m_y;}
	void Sys_TownPos::Set_y(uint16 v)
	{
		m_y=v;
	}

	tcstr Sys_TownPos::Get_town_map_type()	{		return (tcstr)m_town_map_type;}
	void Sys_TownPos::Set_town_map_type(tcstr v)
	{
		if(!v){ throw _T("Sys_TownPos::Set_town_map_type( val = NULL )");}
		nExcelUtil::jSetter(m_town_map_type , v, 32);
	}

	uint16 Sys_TownPos::Get_object_id()	{		return (uint16)m_object_id;}
	void Sys_TownPos::Set_object_id(uint16 v)
	{
		m_object_id=v;
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_castle_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_Castle g_Sys_Castle;


tcstr Sys_Castle::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_csid(FromString(out[index++],m_csid) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getT());
	szKEY = Get_name();
	Set_name_kor(nExcelUtil_StringConverter(out[index++]).getT());
	Set_default_gsid(FromString(out[index++],m_default_gsid) );
	Set_force_gen_name(nExcelUtil_StringConverter(out[index++]).getT());
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_CastlePos g_Sys_CastlePos;


tcstr Sys_CastlePos::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_cpsid(FromString(out[index++],m_cpsid) );
	Set_x(FromString(out[index++],m_x) );
	Set_y(FromString(out[index++],m_y) );
	Set_castle_map(nExcelUtil_StringConverter(out[index++]).getT());
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_TownPos g_Sys_TownPos;


tcstr Sys_TownPos::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_tpsid(FromString(out[index++],m_tpsid) );
	Set_x(FromString(out[index++],m_x) );
	Set_y(FromString(out[index++],m_y) );
	Set_town_map_type(nExcelUtil_StringConverter(out[index++]).getT());
	Set_object_id(FromString(out[index++],m_object_id) );
	return szKEY;
}

void Sys_Castle::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Castle_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_CastlePos::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_TownPos::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Castle>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_CastlePos>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_TownPos>);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_castle)
		{
			{
				SquirrelObject enumRoot= nSQ::jSQ_GetEnumTable();
				for_each_nEXCEL_excel_castle_ENUM(jEXCEL_SQ_bind_EnumField_BEGIN);
				for_each_nEXCEL_Evillage_Condition_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
			}
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Castle>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Castle*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Castle*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Castle*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Castle)
			for_each_nEXCEL_Sys_Castle_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Castle)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Castle>* p = &g_Sys_Castle;
				jSQ_g_var(p , g_Sys_Castle);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_CastlePos>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_CastlePos*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_CastlePos*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_CastlePos*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_CastlePos)
			for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_CastlePos)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_CastlePos>* p = &g_Sys_CastlePos;
				jSQ_g_var(p , g_Sys_CastlePos);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_TownPos>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_TownPos*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_TownPos*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_TownPos*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_TownPos)
			for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_TownPos)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_TownPos>* p = &g_Sys_TownPos;
				jSQ_g_var(p , g_Sys_TownPos);
			}

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

