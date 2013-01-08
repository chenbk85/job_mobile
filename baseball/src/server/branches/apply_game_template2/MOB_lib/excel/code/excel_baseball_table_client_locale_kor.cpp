/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_baseball_table_client_locale_kor.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_baseball_table_client_locale_kor_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_baseball_table_client_locale_kor_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_baseball_table_client_locale_kor_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE

namespace nMech {
	namespace nEXCEL {


#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Dialog_Kor
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Dialog_Kor();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Dialog_Kor


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	int16 Sys_Dialog_Kor::Get_index()	{		return (int16)m_index;}
	void Sys_Dialog_Kor::Set_index(int16 v)
	{
		m_index=v;
	}

	ENpcString Sys_Dialog_Kor::Get_npc()	{		return (ENpcString)m_npc;}
	void Sys_Dialog_Kor::Set_npc(ENpcString v)
	{
		if(v<eBEGIN_ENpcString || v>=eEND_ENpcString)
		{
			jERROR(_T("Sys_Dialog_Kor::Set_npc(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ENpcString,eEND_ENpcString,v);
		}
		m_npc=v;
	}

	acstr Sys_Dialog_Kor::Get_image_type()	{		return (acstr)m_image_type;}
	void Sys_Dialog_Kor::Set_image_type(acstr v)
	{
		if(!v){ throw _T("Sys_Dialog_Kor::Set_image_type( val = NULL )");}
		nExcelUtil::jSetter(m_image_type , v, 1024);
	}

	ENpcSituationString Sys_Dialog_Kor::Get_situation()	{		return (ENpcSituationString)m_situation;}
	void Sys_Dialog_Kor::Set_situation(ENpcSituationString v)
	{
		if(v<eBEGIN_ENpcSituationString || v>=eEND_ENpcSituationString)
		{
			jERROR(_T("Sys_Dialog_Kor::Set_situation(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ENpcSituationString,eEND_ENpcSituationString,v);
		}
		m_situation=v;
	}

	acstr Sys_Dialog_Kor::Get_text()	{		return (acstr)m_text;}
	void Sys_Dialog_Kor::Set_text(acstr v)
	{
		if(!v){ throw _T("Sys_Dialog_Kor::Set_text( val = NULL )");}
		nExcelUtil::jSetter(m_text , v, 1024);
	}

	int16 Sys_String_Kor::Get_index()	{		return (int16)m_index;}
	void Sys_String_Kor::Set_index(int16 v)
	{
		m_index=v;
	}

	ECategoryString Sys_String_Kor::Get_category()	{		return (ECategoryString)m_category;}
	void Sys_String_Kor::Set_category(ECategoryString v)
	{
		if(v<eBEGIN_ECategoryString || v>=eEND_ECategoryString)
		{
			jERROR(_T("Sys_String_Kor::Set_category(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ECategoryString,eEND_ECategoryString,v);
		}
		m_category=v;
	}

	acstr Sys_String_Kor::Get_name()	{		return (acstr)m_name;}
	void Sys_String_Kor::Set_name(acstr v)
	{
		if(!v){ throw _T("Sys_String_Kor::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 1024);
	}

	acstr Sys_String_Kor::Get_text1()	{		return (acstr)m_text1;}
	void Sys_String_Kor::Set_text1(acstr v)
	{
		if(!v){ throw _T("Sys_String_Kor::Set_text1( val = NULL )");}
		nExcelUtil::jSetter(m_text1 , v, 1024);
	}

	acstr Sys_String_Kor::Get_text2()	{		return (acstr)m_text2;}
	void Sys_String_Kor::Set_text2(acstr v)
	{
		if(!v){ throw _T("Sys_String_Kor::Set_text2( val = NULL )");}
		nExcelUtil::jSetter(m_text2 , v, 1024);
	}

	acstr Sys_String_Kor::Get_text3()	{		return (acstr)m_text3;}
	void Sys_String_Kor::Set_text3(acstr v)
	{
		if(!v){ throw _T("Sys_String_Kor::Set_text3( val = NULL )");}
		nExcelUtil::jSetter(m_text3 , v, 1024);
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_baseball_table_client_locale_kor_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_Dialog_Kor g_Sys_Dialog_Kor;


tcstr Sys_Dialog_Kor::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_index(FromString(out[index++],m_index) );
	Set_npc(FromString(out[index++],m_npc) );
	Set_image_type(nExcelUtil_StringConverter(out[index++]).getA());
	Set_situation(FromString(out[index++],m_situation) );
	Set_text(nExcelUtil_StringConverter(out[index++]).getA());
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_String_Kor g_Sys_String_Kor;


tcstr Sys_String_Kor::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
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
	Set_name(nExcelUtil_StringConverter(out[index++]).getA());
	szKEY = Get_name();
	Set_text1(nExcelUtil_StringConverter(out[index++]).getA());
	Set_text2(nExcelUtil_StringConverter(out[index++]).getA());
	Set_text3(nExcelUtil_StringConverter(out[index++]).getA());
	return szKEY;
}

void Sys_Dialog_Kor::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Dialog_Kor_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_String_Kor::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_String_Kor_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Dialog_Kor>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_String_Kor>);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_baseball_table_client_locale_kor)
		{
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Dialog_Kor>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Dialog_Kor*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Dialog_Kor*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Dialog_Kor*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Dialog_Kor)
			for_each_nEXCEL_Sys_Dialog_Kor_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Dialog_Kor)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Dialog_Kor>* p = &g_Sys_Dialog_Kor;
				jSQ_g_var(p , g_Sys_Dialog_Kor);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_String_Kor>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_String_Kor*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_String_Kor*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_String_Kor*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_String_Kor)
			for_each_nEXCEL_Sys_String_Kor_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_String_Kor)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_String_Kor>* p = &g_Sys_String_Kor;
				jSQ_g_var(p , g_Sys_String_Kor);
			}

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

