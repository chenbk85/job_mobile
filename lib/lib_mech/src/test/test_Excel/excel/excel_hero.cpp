/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_hero.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_hero_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_hero_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_hero_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE


for_each_nEXCEL_excel_hero_ENUM(jEXCEL_SQ_DECLARE_ENUM_TYPE);
namespace nMech {
	namespace nEXCEL {

jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EDeckYear[] = 
{
	{ 2 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EDeckYear_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroCategory[] = 
{
	{ 2 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EHeroCategory_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroEngagementtype[] = 
{
	{ 2 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EHeroEngagementtype_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroFacetype[] = 
{
	{ 4 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EHeroFacetype_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroPersonality[] = 
{
	{ 4 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EHeroPersonality_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroSex[] = 
{
	{ 2 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EHeroSex_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroWorkState[] = 
{
	{ 4 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EHeroWorkState_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Hero
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Hero();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Hero


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	Sys_Hero_id_t Sys_Hero::Get_hsid()	{		return (Sys_Hero_id_t)m_hsid;}
	void Sys_Hero::Set_hsid(uint16 v)
	{
		m_hsid=v;
	}

	EHeroCategory Sys_Hero::Get_category()	{		return (EHeroCategory)m_category;}
	void Sys_Hero::Set_category(EHeroCategory v)
	{
		if(v<eBEGIN_EHeroCategory || v>=eEND_EHeroCategory)
		{
			jERROR(_T("Sys_Hero::Set_category(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EHeroCategory,eEND_EHeroCategory,v);
		}
		m_category=v;
	}

	EDeckYear Sys_Hero::Get_deck_year()	{		return (EDeckYear)m_deck_year;}
	void Sys_Hero::Set_deck_year(EDeckYear v)
	{
		if(v<eBEGIN_EDeckYear || v>=eEND_EDeckYear)
		{
			jERROR(_T("Sys_Hero::Set_deck_year(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EDeckYear,eEND_EDeckYear,v);
		}
		m_deck_year=v;
	}

	tcstr Sys_Hero::Get_name()	{		return (tcstr)m_name;}
	void Sys_Hero::Set_name(tcstr v)
	{
		if(!v){ throw _T("Sys_Hero::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	wcstr Sys_Hero::Get_name_kor()	{		return (wcstr)m_name_kor;}
	void Sys_Hero::Set_name_kor(wcstr v)
	{
		if(!v){ throw _T("Sys_Hero::Set_name_kor( val = NULL )");}
		nExcelUtil::jSetter(m_name_kor , v, 32);
	}

	tcstr Sys_Hero::Get_image_file()	{		return (tcstr)m_image_file;}
	void Sys_Hero::Set_image_file(tcstr v)
	{
		if(!v){ throw _T("Sys_Hero::Set_image_file( val = NULL )");}
		nExcelUtil::jSetter(m_image_file , v, 256);
	}

	int32 Sys_Hero::Get_grade()	{		return (int32)m_grade;}
	void Sys_Hero::Set_grade(int32 v)
	{
		m_grade=v;
	}

	int32 Sys_Hero::Get_age()	{		return (int32)m_age;}
	void Sys_Hero::Set_age(int32 v)
	{
		if(v>99) v = (int32)99;
		if(v<1) v = 1;
		m_age=v;
	}

	int32 Sys_Hero::Get_leadership()	{		return (int32)m_leadership;}
	void Sys_Hero::Set_leadership(int32 v)
	{
		if(v>200) v = (int32)200;
		if(v<1) v = 1;
		m_leadership=v;
	}

	int32 Sys_Hero::Get_power()	{		return (int32)m_power;}
	void Sys_Hero::Set_power(int32 v)
	{
		if(v>200) v = (int32)200;
		if(v<1) v = 1;
		m_power=v;
	}

	int32 Sys_Hero::Get_intelligent()	{		return (int32)m_intelligent;}
	void Sys_Hero::Set_intelligent(int32 v)
	{
		if(v>200) v = (int32)200;
		if(v<1) v = 1;
		m_intelligent=v;
	}

	int32 Sys_Hero::Get_politic()	{		return (int32)m_politic;}
	void Sys_Hero::Set_politic(int32 v)
	{
		if(v>200) v = (int32)200;
		if(v<1) v = 1;
		m_politic=v;
	}

	int32 Sys_Hero::Get_charm()	{		return (int32)m_charm;}
	void Sys_Hero::Set_charm(int32 v)
	{
		if(v>200) v = (int32)200;
		if(v<1) v = 1;
		m_charm=v;
	}

	bool Sys_Hero::Get_is_male()	{		return (bool)m_is_male;}
	void Sys_Hero::Set_is_male(bool v)
	{
		m_is_male=v;
	}

	EHeroPersonality Sys_Hero::Get_personality()	{		return (EHeroPersonality)m_personality;}
	void Sys_Hero::Set_personality(EHeroPersonality v)
	{
		if(v<eBEGIN_EHeroPersonality || v>=eEND_EHeroPersonality)
		{
			jERROR(_T("Sys_Hero::Set_personality(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EHeroPersonality,eEND_EHeroPersonality,v);
		}
		m_personality=v;
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_hero_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_Hero g_Sys_Hero;


tcstr Sys_Hero::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_hsid(FromString(out[index++],m_hsid) );
	Set_category(FromString(out[index++],m_category) );
	Set_deck_year(FromString(out[index++],m_deck_year) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getT());
	szKEY = Get_name();
	Set_name_kor(nExcelUtil_StringConverter(out[index++]).getW());
	Set_image_file(nExcelUtil_StringConverter(out[index++]).getT());
	Set_grade(FromString(out[index++],m_grade) );
	Set_age(FromString(out[index++],m_age) );
	Set_leadership(FromString(out[index++],m_leadership) );
	Set_power(FromString(out[index++],m_power) );
	Set_intelligent(FromString(out[index++],m_intelligent) );
	Set_politic(FromString(out[index++],m_politic) );
	Set_charm(FromString(out[index++],m_charm) );
	FromString(&m_is_male,out[index++]);
	Set_personality(FromString(out[index++],m_personality) );
	return szKEY;
}

void Sys_Hero::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Hero_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Hero>);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_hero)
		{
			{
				SquirrelObject enumRoot= nSQ::jSQ_GetEnumTable();
				for_each_nEXCEL_excel_hero_ENUM(jEXCEL_SQ_bind_EnumField_BEGIN);
				for_each_nEXCEL_EDeckYear_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EHeroCategory_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EHeroEngagementtype_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EHeroFacetype_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EHeroPersonality_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EHeroSex_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EHeroWorkState_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
			}
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Hero>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Hero*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Hero*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Hero*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Hero)
			for_each_nEXCEL_Sys_Hero_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Hero)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Hero>* p = &g_Sys_Hero;
				jSQ_g_var(p , g_Sys_Hero);
			}

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

