/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "LocalizingTable.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nTESTSERVER_LocalizingTable_Sys_STRUCT_LIST)
		for_each_nTESTSERVER_LocalizingTable_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nTESTSERVER_LocalizingTable_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE


for_each_nTESTSERVER_LocalizingTable_ENUM(jEXCEL_SQ_DECLARE_ENUM_TYPE);
namespace nMech {
	namespace nTESTSERVER {

jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ETextCategory[] = 
{
	{ 5 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_ETextCategory_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_LocalizingText
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_LocalizingText();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_LocalizingText


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	uint16 Sys_LocalizingText::Get_id()	{		return (uint16)m_id;}
	void Sys_LocalizingText::Set_id(uint16 v)
	{
		m_id=v;
	}

	ETextCategory Sys_LocalizingText::Get_category()	{		return (ETextCategory)m_category;}
	void Sys_LocalizingText::Set_category(ETextCategory v)
	{
		if(v<eBEGIN_ETextCategory || v>=eEND_ETextCategory)
		{
			jERROR(_T("Sys_LocalizingText::Set_category(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ETextCategory,eEND_ETextCategory,v);
		}
		m_category=v;
	}

	tcstr Sys_LocalizingText::Get_name()	{		return (tcstr)m_name;}
	void Sys_LocalizingText::Set_name(tcstr v)
	{
		if(!v){ throw _T("Sys_LocalizingText::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 256);
	}

	wcstr Sys_LocalizingText::Get_name_kor()	{		return (wcstr)m_name_kor;}
	void Sys_LocalizingText::Set_name_kor(wcstr v)
	{
		if(!v){ throw _T("Sys_LocalizingText::Set_name_kor( val = NULL )");}
		nExcelUtil::jSetter(m_name_kor , v, 256);
	}

	wcstr Sys_LocalizingText::Get_name_loc()	{		return (wcstr)m_name_loc;}
	void Sys_LocalizingText::Set_name_loc(wcstr v)
	{
		if(!v){ throw _T("Sys_LocalizingText::Set_name_loc( val = NULL )");}
		nExcelUtil::jSetter(m_name_loc , v, 256);
	}

	uint16 Sys_LocalizingWord::Get_id()	{		return (uint16)m_id;}
	void Sys_LocalizingWord::Set_id(uint16 v)
	{
		m_id=v;
	}

	tcstr Sys_LocalizingWord::Get_name()	{		return (tcstr)m_name;}
	void Sys_LocalizingWord::Set_name(tcstr v)
	{
		if(!v){ throw _T("Sys_LocalizingWord::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	wcstr Sys_LocalizingWord::Get_name_kor()	{		return (wcstr)m_name_kor;}
	void Sys_LocalizingWord::Set_name_kor(wcstr v)
	{
		if(!v){ throw _T("Sys_LocalizingWord::Set_name_kor( val = NULL )");}
		nExcelUtil::jSetter(m_name_kor , v, 32);
	}

	wcstr Sys_LocalizingWord::Get_name_loc()	{		return (wcstr)m_name_loc;}
	void Sys_LocalizingWord::Set_name_loc(wcstr v)
	{
		if(!v){ throw _T("Sys_LocalizingWord::Set_name_loc( val = NULL )");}
		nExcelUtil::jSetter(m_name_loc , v, 32);
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nTESTSERVER_LocalizingTable_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_LocalizingText g_Sys_LocalizingText;


tcstr Sys_LocalizingText::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_id(FromString(out[index++],m_id) );
	Set_category(FromString(out[index++],m_category) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getT());
	szKEY = Get_name();
	Set_name_kor(nExcelUtil_StringConverter(out[index++]).getW());
	Set_name_loc(nExcelUtil_StringConverter(out[index++]).getW());
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_LocalizingWord g_Sys_LocalizingWord;


tcstr Sys_LocalizingWord::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
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
	Set_name_kor(nExcelUtil_StringConverter(out[index++]).getW());
	Set_name_loc(nExcelUtil_StringConverter(out[index++]).getW());
	return szKEY;
}

void Sys_LocalizingText::DebugPrint()
{	tname1024_t szBuf;

	for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_LocalizingWord::DebugPrint()
{	tname1024_t szBuf;

	for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nTESTSERVER 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nTESTSERVER;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_LocalizingText>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_LocalizingWord>);

	namespace nMech { namespace nTESTSERVER
	{
		jSQ_REGIST_BIND(nMech_nTESTSERVER_LocalizingTable)
		{
			{
				SquirrelObject enumRoot= nSQ::jSQ_GetEnumTable();
				for_each_nTESTSERVER_LocalizingTable_ENUM(jEXCEL_SQ_bind_EnumField_BEGIN);
				for_each_nTESTSERVER_ETextCategory_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
			}
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_LocalizingText>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_LocalizingText*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_LocalizingText*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_LocalizingText*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_LocalizingText)
			for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_LocalizingText)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_LocalizingText>* p = &g_Sys_LocalizingText;
				jSQ_g_var(p , g_Sys_LocalizingText);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_LocalizingWord>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_LocalizingWord*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_LocalizingWord*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_LocalizingWord*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_LocalizingWord)
			for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_LocalizingWord)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_LocalizingWord>* p = &g_Sys_LocalizingWord;
				jSQ_g_var(p , g_Sys_LocalizingWord);
			}

		}
	} /*namespace nTESTSERVER */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

