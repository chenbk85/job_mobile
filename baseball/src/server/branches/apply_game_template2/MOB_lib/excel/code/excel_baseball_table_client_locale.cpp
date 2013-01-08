/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_baseball_table_client_locale.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_baseball_table_client_locale_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_baseball_table_client_locale_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_baseball_table_client_locale_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE

namespace nMech {
	namespace nEXCEL {


#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Dialog_Usa
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Dialog_Usa();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Dialog_Usa


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	int16 Sys_Dialog_Usa::Get_index()	{		return (int16)m_index_i16;}
	void Sys_Dialog_Usa::Set_index(int16 v)
	{
		m_index_i16=v;
	}

	ENpcString Sys_Dialog_Usa::Get_npc()	{		return (ENpcString)m_npc_e;}
	void Sys_Dialog_Usa::Set_npc(ENpcString v)
	{
		if(v<eBEGIN_ENpcString || v>=eEND_ENpcString)
		{
			jERROR(_T("Sys_Dialog_Usa::Set_npc(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ENpcString,eEND_ENpcString,v);
		}
		m_npc_e=v;
	}

	acstr Sys_Dialog_Usa::Get_image_type()	{		return (acstr)m_image_type_a32;}
	void Sys_Dialog_Usa::Set_image_type(acstr v)
	{
		if(!v){ throw _T("Sys_Dialog_Usa::Set_image_type( val = NULL )");}
		nExcelUtil::jSetter(m_image_type_a32 , v, 32);
	}

	ENpcSituationString Sys_Dialog_Usa::Get_situation()	{		return (ENpcSituationString)m_situation_e;}
	void Sys_Dialog_Usa::Set_situation(ENpcSituationString v)
	{
		if(v<eBEGIN_ENpcSituationString || v>=eEND_ENpcSituationString)
		{
			jERROR(_T("Sys_Dialog_Usa::Set_situation(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ENpcSituationString,eEND_ENpcSituationString,v);
		}
		m_situation_e=v;
	}

	acstr Sys_Dialog_Usa::Get_text()	{		return (acstr)m_text_a1024;}
	void Sys_Dialog_Usa::Set_text(acstr v)
	{
		if(!v){ throw _T("Sys_Dialog_Usa::Set_text( val = NULL )");}
		nExcelUtil::jSetter(m_text_a1024 , v, 1024);
	}

	int16 Sys_String_Usa::Get_index()	{		return (int16)m_index_i16;}
	void Sys_String_Usa::Set_index(int16 v)
	{
		m_index_i16=v;
	}

	ECategoryString Sys_String_Usa::Get_category()	{		return (ECategoryString)m_category_e;}
	void Sys_String_Usa::Set_category(ECategoryString v)
	{
		if(v<eBEGIN_ECategoryString || v>=eEND_ECategoryString)
		{
			jERROR(_T("Sys_String_Usa::Set_category(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ECategoryString,eEND_ECategoryString,v);
		}
		m_category_e=v;
	}

	acstr Sys_String_Usa::Get_name()	{		return (acstr)m_name_a32;}
	void Sys_String_Usa::Set_name(acstr v)
	{
		if(!v){ throw _T("Sys_String_Usa::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name_a32 , v, 32);
	}

	acstr Sys_String_Usa::Get_text1()	{		return (acstr)m_text1_a1024;}
	void Sys_String_Usa::Set_text1(acstr v)
	{
		if(!v){ throw _T("Sys_String_Usa::Set_text1( val = NULL )");}
		nExcelUtil::jSetter(m_text1_a1024 , v, 1024);
	}

	acstr Sys_String_Usa::Get_text2()	{		return (acstr)m_text2_a1024;}
	void Sys_String_Usa::Set_text2(acstr v)
	{
		if(!v){ throw _T("Sys_String_Usa::Set_text2( val = NULL )");}
		nExcelUtil::jSetter(m_text2_a1024 , v, 1024);
	}

	acstr Sys_String_Usa::Get_text3()	{		return (acstr)m_text3_a1024;}
	void Sys_String_Usa::Set_text3(acstr v)
	{
		if(!v){ throw _T("Sys_String_Usa::Set_text3( val = NULL )");}
		nExcelUtil::jSetter(m_text3_a1024 , v, 1024);
	}

	int16 Sys_Dialog_Kor::Get_index()	{		return (int16)m_index_i16;}
	void Sys_Dialog_Kor::Set_index(int16 v)
	{
		m_index_i16=v;
	}

	ENpcString Sys_Dialog_Kor::Get_npc()	{		return (ENpcString)m_npc_e;}
	void Sys_Dialog_Kor::Set_npc(ENpcString v)
	{
		if(v<eBEGIN_ENpcString || v>=eEND_ENpcString)
		{
			jERROR(_T("Sys_Dialog_Kor::Set_npc(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ENpcString,eEND_ENpcString,v);
		}
		m_npc_e=v;
	}

	acstr Sys_Dialog_Kor::Get_image_type()	{		return (acstr)m_image_type_a1024;}
	void Sys_Dialog_Kor::Set_image_type(acstr v)
	{
		if(!v){ throw _T("Sys_Dialog_Kor::Set_image_type( val = NULL )");}
		nExcelUtil::jSetter(m_image_type_a1024 , v, 1024);
	}

	ENpcSituationString Sys_Dialog_Kor::Get_situation()	{		return (ENpcSituationString)m_situation_e;}
	void Sys_Dialog_Kor::Set_situation(ENpcSituationString v)
	{
		if(v<eBEGIN_ENpcSituationString || v>=eEND_ENpcSituationString)
		{
			jERROR(_T("Sys_Dialog_Kor::Set_situation(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ENpcSituationString,eEND_ENpcSituationString,v);
		}
		m_situation_e=v;
	}

	acstr Sys_Dialog_Kor::Get_text()	{		return (acstr)m_text_a1024;}
	void Sys_Dialog_Kor::Set_text(acstr v)
	{
		if(!v){ throw _T("Sys_Dialog_Kor::Set_text( val = NULL )");}
		nExcelUtil::jSetter(m_text_a1024 , v, 1024);
	}

	int16 Sys_String_Kor::Get_index()	{		return (int16)m_index_i16;}
	void Sys_String_Kor::Set_index(int16 v)
	{
		m_index_i16=v;
	}

	ECategoryString Sys_String_Kor::Get_category()	{		return (ECategoryString)m_category_e;}
	void Sys_String_Kor::Set_category(ECategoryString v)
	{
		if(v<eBEGIN_ECategoryString || v>=eEND_ECategoryString)
		{
			jERROR(_T("Sys_String_Kor::Set_category(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ECategoryString,eEND_ECategoryString,v);
		}
		m_category_e=v;
	}

	acstr Sys_String_Kor::Get_name()	{		return (acstr)m_name_a1024;}
	void Sys_String_Kor::Set_name(acstr v)
	{
		if(!v){ throw _T("Sys_String_Kor::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name_a1024 , v, 1024);
	}

	acstr Sys_String_Kor::Get_text1()	{		return (acstr)m_text1_a1024;}
	void Sys_String_Kor::Set_text1(acstr v)
	{
		if(!v){ throw _T("Sys_String_Kor::Set_text1( val = NULL )");}
		nExcelUtil::jSetter(m_text1_a1024 , v, 1024);
	}

	acstr Sys_String_Kor::Get_text2()	{		return (acstr)m_text2_a1024;}
	void Sys_String_Kor::Set_text2(acstr v)
	{
		if(!v){ throw _T("Sys_String_Kor::Set_text2( val = NULL )");}
		nExcelUtil::jSetter(m_text2_a1024 , v, 1024);
	}

	acstr Sys_String_Kor::Get_text3()	{		return (acstr)m_text3_a1024;}
	void Sys_String_Kor::Set_text3(acstr v)
	{
		if(!v){ throw _T("Sys_String_Kor::Set_text3( val = NULL )");}
		nExcelUtil::jSetter(m_text3_a1024 , v, 1024);
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_baseball_table_client_locale_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_Dialog_Usa g_Sys_Dialog_Usa;


tcstr Sys_Dialog_Usa::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_index(FromString(out[index++],m_index_i16) );
	Set_npc(FromString(out[index++],m_npc_e) );
	Set_image_type(nExcelUtil_StringConverter(out[index++]).getA());
	Set_situation(FromString(out[index++],m_situation_e) );
	Set_text(nExcelUtil_StringConverter(out[index++]).getA());
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_String_Usa g_Sys_String_Usa;


tcstr Sys_String_Usa::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_index(FromString(out[index++],m_index_i16) );
	Set_category(FromString(out[index++],m_category_e) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getA());
	szKEY = Get_name();
	Set_text1(nExcelUtil_StringConverter(out[index++]).getA());
	Set_text2(nExcelUtil_StringConverter(out[index++]).getA());
	Set_text3(nExcelUtil_StringConverter(out[index++]).getA());
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_Dialog_Kor g_Sys_Dialog_Kor;


tcstr Sys_Dialog_Kor::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_index(FromString(out[index++],m_index_i16) );
	Set_npc(FromString(out[index++],m_npc_e) );
	Set_image_type(nExcelUtil_StringConverter(out[index++]).getA());
	Set_situation(FromString(out[index++],m_situation_e) );
	Set_text(nExcelUtil_StringConverter(out[index++]).getA());
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_String_Kor g_Sys_String_Kor;


tcstr Sys_String_Kor::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_index(FromString(out[index++],m_index_i16) );
	Set_category(FromString(out[index++],m_category_e) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getA());
	szKEY = Get_name();
	Set_text1(nExcelUtil_StringConverter(out[index++]).getA());
	Set_text2(nExcelUtil_StringConverter(out[index++]).getA());
	Set_text3(nExcelUtil_StringConverter(out[index++]).getA());
	return szKEY;
}

void Sys_Dialog_Usa::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_String_Usa::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
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

	typedef CSV_Sys_Dialog_Usa Sys_Dialog_Usa_csv_file_t;
	DECLARE_INSTANCE_TYPE(Sys_Dialog_Usa_csv_file_t);

	typedef CSV_Sys_String_Usa Sys_String_Usa_csv_file_t;
	DECLARE_INSTANCE_TYPE(Sys_String_Usa_csv_file_t);

	typedef CSV_Sys_Dialog_Kor Sys_Dialog_Kor_csv_file_t;
	DECLARE_INSTANCE_TYPE(Sys_Dialog_Kor_csv_file_t);

	typedef CSV_Sys_String_Kor Sys_String_Kor_csv_file_t;
	DECLARE_INSTANCE_TYPE(Sys_String_Kor_csv_file_t);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_baseball_table_client_locale)
		{
			jSQ_Interface(Sys_Dialog_Usa_csv_file_t)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Dialog_Usa*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Dialog_Usa*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Dialog_Usa*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Dialog_Usa)
			for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Dialog_Usa)
			jSQ_end();
			jSQ_g_var(&g_Sys_Dialog_Usa,g_Sys_Dialog_Usa);

			jSQ_Interface(Sys_String_Usa_csv_file_t)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_String_Usa*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_String_Usa*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_String_Usa*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_String_Usa)
			for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_String_Usa)
			jSQ_end();
			jSQ_g_var(&g_Sys_String_Usa,g_Sys_String_Usa);

			jSQ_Interface(Sys_Dialog_Kor_csv_file_t)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Dialog_Kor*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Dialog_Kor*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Dialog_Kor*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Dialog_Kor)
			for_each_nEXCEL_Sys_Dialog_Kor_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Dialog_Kor)
			jSQ_end();
			jSQ_g_var(&g_Sys_Dialog_Kor,g_Sys_Dialog_Kor);

			jSQ_Interface(Sys_String_Kor_csv_file_t)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_String_Kor*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_String_Kor*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_String_Kor*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_String_Kor)
			for_each_nEXCEL_Sys_String_Kor_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_String_Kor)
			jSQ_end();
			jSQ_g_var(&g_Sys_String_Kor,g_Sys_String_Kor);

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

