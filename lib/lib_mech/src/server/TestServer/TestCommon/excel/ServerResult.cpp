/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "ServerResult.h"



//현제 모듈의 Sys테이블에 대해 배열형 필드를 사용할때는 아래 코드를 구현해야 한다.
#if 0

#ifndef jNOT_USE_SQ_BIND_CODE
#endif //jNOT_USE_SQ_BIND_CODE


namespace nMech
{
	namespace nTESTSERVER
	{
	}//namespace nTESTSERVER
}//namespace nMech
#endif //구현되어야 하는 코드 끝.

#ifndef jNOT_USE_SQ_BIND_CODE

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nTESTSERVER_ServerResult_Sys_STRUCT_LIST)
		for_each_nTESTSERVER_ServerResult_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nTESTSERVER_ServerResult_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE

namespace nMech {
	namespace nTESTSERVER {


#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_ServerResult
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_ServerResult();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_ServerResult


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	uint16 Sys_ServerResult::Get_id()	{		return (uint16)m_id;}
	void Sys_ServerResult::Set_id(uint16 v)
	{
		m_id=v;
	}

	tcstr Sys_ServerResult::Get_eng_name()	{		return (tcstr)m_eng_name;}
	void Sys_ServerResult::Set_eng_name(tcstr v)
	{
		if(!v){ throw _T("Sys_ServerResult::Set_eng_name( val = NULL )");}
		nExcelUtil::jSetter(m_eng_name , v, 32);
	}

	tcstr Sys_ServerResult::Get_description()	{		return (tcstr)m_description;}
	void Sys_ServerResult::Set_description(tcstr v)
	{
		if(!v){ throw _T("Sys_ServerResult::Set_description( val = NULL )");}
		nExcelUtil::jSetter(m_description , v, 128);
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nTESTSERVER_ServerResult_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_ServerResult g_Sys_ServerResult;


tcstr Sys_ServerResult::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_id(FromString(out[index++],m_id) );
	Set_eng_name(nExcelUtil_StringConverter(out[index++]).getT());
	Set_description(nExcelUtil_StringConverter(out[index++]).getT());
	return szKEY;
}

void Sys_ServerResult::DebugPrint()
{	tname1024_t szBuf;

	for_each_nTESTSERVER_Sys_ServerResult_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nTESTSERVER 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nTESTSERVER;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_ServerResult>);

	namespace nMech { namespace nTESTSERVER
	{
		jSQ_REGIST_BIND(nMech_nTESTSERVER_ServerResult)
		{
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_ServerResult>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_ServerResult*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_ServerResult*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_ServerResult*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_ServerResult)
			for_each_nTESTSERVER_Sys_ServerResult_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_ServerResult)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_ServerResult>* p = &g_Sys_ServerResult;
				jSQ_g_var(p , g_Sys_ServerResult);
			}

		}
	} /*namespace nTESTSERVER */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

