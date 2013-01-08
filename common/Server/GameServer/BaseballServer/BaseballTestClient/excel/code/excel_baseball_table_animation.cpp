/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_baseball_table_animation.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_baseball_table_animation_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_baseball_table_animation_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_baseball_table_animation_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE


for_each_nEXCEL_excel_baseball_table_animation_ENUM(jEXCEL_SQ_DECLARE_ENUM_TYPE);
namespace nMech {
	namespace nEXCEL {

jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBatterAnimationType[] = 
{
	{ 11 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EBatterAnimationType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ECatcherAnimationType[] = 
{
	{ 8 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_ECatcherAnimationType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EEumpireAnimationType[] = 
{
	{ 6 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EEumpireAnimationType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPitcherAnimationType[] = 
{
	{ 10 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EPitcherAnimationType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Batter_Animation
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Batter_Animation();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Batter_Animation


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	int16 Sys_Batter_Animation::Get_index()	{		return (int16)m_index;}
	void Sys_Batter_Animation::Set_index(int16 v)
	{
		m_index=v;
	}

	EPlayerBodyType Sys_Batter_Animation::Get_body_type()	{		return (EPlayerBodyType)m_body_type;}
	void Sys_Batter_Animation::Set_body_type(EPlayerBodyType v)
	{
		if(v<eBEGIN_EPlayerBodyType || v>=eEND_EPlayerBodyType)
		{
			jERROR(_T("Sys_Batter_Animation::Set_body_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerBodyType,eEND_EPlayerBodyType,v);
		}
		m_body_type=v;
	}

	EBatterForm Sys_Batter_Animation::Get_better_form()	{		return (EBatterForm)m_better_form;}
	void Sys_Batter_Animation::Set_better_form(EBatterForm v)
	{
		if(v<eBEGIN_EBatterForm || v>=eEND_EBatterForm)
		{
			jERROR(_T("Sys_Batter_Animation::Set_better_form(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBatterForm,eEND_EBatterForm,v);
		}
		m_better_form=v;
	}

	EBatterAnimationType Sys_Batter_Animation::Get_batter_animation()	{		return (EBatterAnimationType)m_batter_animation;}
	void Sys_Batter_Animation::Set_batter_animation(EBatterAnimationType v)
	{
		if(v<eBEGIN_EBatterAnimationType || v>=eEND_EBatterAnimationType)
		{
			jERROR(_T("Sys_Batter_Animation::Set_batter_animation(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBatterAnimationType,eEND_EBatterAnimationType,v);
		}
		m_batter_animation=v;
	}

	int16 Sys_Batter_Animation::Get_animation_number()	{		return (int16)m_animation_number;}
	void Sys_Batter_Animation::Set_animation_number(int16 v)
	{
		m_animation_number=v;
	}

	acstr Sys_Batter_Animation::Get_animation_filename()	{		return (acstr)m_animation_filename;}
	void Sys_Batter_Animation::Set_animation_filename(acstr v)
	{
		if(!v){ throw _T("Sys_Batter_Animation::Set_animation_filename( val = NULL )");}
		nExcelUtil::jSetter(m_animation_filename , v, 32);
	}

	int16 Sys_Catcher_Animation::Get_index()	{		return (int16)m_index;}
	void Sys_Catcher_Animation::Set_index(int16 v)
	{
		m_index=v;
	}

	ECatcherAnimationType Sys_Catcher_Animation::Get_catcher_animation()	{		return (ECatcherAnimationType)m_catcher_animation;}
	void Sys_Catcher_Animation::Set_catcher_animation(ECatcherAnimationType v)
	{
		if(v<eBEGIN_ECatcherAnimationType || v>=eEND_ECatcherAnimationType)
		{
			jERROR(_T("Sys_Catcher_Animation::Set_catcher_animation(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ECatcherAnimationType,eEND_ECatcherAnimationType,v);
		}
		m_catcher_animation=v;
	}

	int16 Sys_Catcher_Animation::Get_animation_number()	{		return (int16)m_animation_number;}
	void Sys_Catcher_Animation::Set_animation_number(int16 v)
	{
		m_animation_number=v;
	}

	acstr Sys_Catcher_Animation::Get_animation_filename()	{		return (acstr)m_animation_filename;}
	void Sys_Catcher_Animation::Set_animation_filename(acstr v)
	{
		if(!v){ throw _T("Sys_Catcher_Animation::Set_animation_filename( val = NULL )");}
		nExcelUtil::jSetter(m_animation_filename , v, 32);
	}

	int16 Sys_Pitcher_Animation::Get_index()	{		return (int16)m_index;}
	void Sys_Pitcher_Animation::Set_index(int16 v)
	{
		m_index=v;
	}

	EPlayerBodyType Sys_Pitcher_Animation::Get_body_type()	{		return (EPlayerBodyType)m_body_type;}
	void Sys_Pitcher_Animation::Set_body_type(EPlayerBodyType v)
	{
		if(v<eBEGIN_EPlayerBodyType || v>=eEND_EPlayerBodyType)
		{
			jERROR(_T("Sys_Pitcher_Animation::Set_body_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerBodyType,eEND_EPlayerBodyType,v);
		}
		m_body_type=v;
	}

	EPitcherForm Sys_Pitcher_Animation::Get_pitcher_form()	{		return (EPitcherForm)m_pitcher_form;}
	void Sys_Pitcher_Animation::Set_pitcher_form(EPitcherForm v)
	{
		if(v<eBEGIN_EPitcherForm || v>=eEND_EPitcherForm)
		{
			jERROR(_T("Sys_Pitcher_Animation::Set_pitcher_form(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPitcherForm,eEND_EPitcherForm,v);
		}
		m_pitcher_form=v;
	}

	EPitcherAnimationType Sys_Pitcher_Animation::Get_pitcher_animation()	{		return (EPitcherAnimationType)m_pitcher_animation;}
	void Sys_Pitcher_Animation::Set_pitcher_animation(EPitcherAnimationType v)
	{
		if(v<eBEGIN_EPitcherAnimationType || v>=eEND_EPitcherAnimationType)
		{
			jERROR(_T("Sys_Pitcher_Animation::Set_pitcher_animation(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPitcherAnimationType,eEND_EPitcherAnimationType,v);
		}
		m_pitcher_animation=v;
	}

	int16 Sys_Pitcher_Animation::Get_animation_number()	{		return (int16)m_animation_number;}
	void Sys_Pitcher_Animation::Set_animation_number(int16 v)
	{
		m_animation_number=v;
	}

	acstr Sys_Pitcher_Animation::Get_animation_filename()	{		return (acstr)m_animation_filename;}
	void Sys_Pitcher_Animation::Set_animation_filename(acstr v)
	{
		if(!v){ throw _T("Sys_Pitcher_Animation::Set_animation_filename( val = NULL )");}
		nExcelUtil::jSetter(m_animation_filename , v, 32);
	}

	int16 Sys_Umpire_Animation::Get_index()	{		return (int16)m_index;}
	void Sys_Umpire_Animation::Set_index(int16 v)
	{
		m_index=v;
	}

	EEumpireAnimationType Sys_Umpire_Animation::Get_umpire_animation()	{		return (EEumpireAnimationType)m_umpire_animation;}
	void Sys_Umpire_Animation::Set_umpire_animation(EEumpireAnimationType v)
	{
		if(v<eBEGIN_EEumpireAnimationType || v>=eEND_EEumpireAnimationType)
		{
			jERROR(_T("Sys_Umpire_Animation::Set_umpire_animation(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EEumpireAnimationType,eEND_EEumpireAnimationType,v);
		}
		m_umpire_animation=v;
	}

	int16 Sys_Umpire_Animation::Get_animation_number()	{		return (int16)m_animation_number;}
	void Sys_Umpire_Animation::Set_animation_number(int16 v)
	{
		m_animation_number=v;
	}

	acstr Sys_Umpire_Animation::Get_animation_filename()	{		return (acstr)m_animation_filename;}
	void Sys_Umpire_Animation::Set_animation_filename(acstr v)
	{
		if(!v){ throw _T("Sys_Umpire_Animation::Set_animation_filename( val = NULL )");}
		nExcelUtil::jSetter(m_animation_filename , v, 32);
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_baseball_table_animation_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_Batter_Animation g_Sys_Batter_Animation;


tcstr Sys_Batter_Animation::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_index(FromString(out[index++],m_index) );
	Set_body_type(FromString(out[index++],m_body_type) );
	Set_better_form(FromString(out[index++],m_better_form) );
	Set_batter_animation(FromString(out[index++],m_batter_animation) );
	Set_animation_number(FromString(out[index++],m_animation_number) );
	Set_animation_filename(nExcelUtil_StringConverter(out[index++]).getA());
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_Catcher_Animation g_Sys_Catcher_Animation;


tcstr Sys_Catcher_Animation::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_index(FromString(out[index++],m_index) );
	Set_catcher_animation(FromString(out[index++],m_catcher_animation) );
	Set_animation_number(FromString(out[index++],m_animation_number) );
	Set_animation_filename(nExcelUtil_StringConverter(out[index++]).getA());
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_Pitcher_Animation g_Sys_Pitcher_Animation;


tcstr Sys_Pitcher_Animation::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_index(FromString(out[index++],m_index) );
	Set_body_type(FromString(out[index++],m_body_type) );
	Set_pitcher_form(FromString(out[index++],m_pitcher_form) );
	Set_pitcher_animation(FromString(out[index++],m_pitcher_animation) );
	Set_animation_number(FromString(out[index++],m_animation_number) );
	Set_animation_filename(nExcelUtil_StringConverter(out[index++]).getA());
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_Umpire_Animation g_Sys_Umpire_Animation;


tcstr Sys_Umpire_Animation::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_index(FromString(out[index++],m_index) );
	Set_umpire_animation(FromString(out[index++],m_umpire_animation) );
	Set_animation_number(FromString(out[index++],m_animation_number) );
	Set_animation_filename(nExcelUtil_StringConverter(out[index++]).getA());
	return szKEY;
}

void Sys_Batter_Animation::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_Catcher_Animation::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_Pitcher_Animation::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_Umpire_Animation::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Batter_Animation>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Catcher_Animation>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Pitcher_Animation>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Umpire_Animation>);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_baseball_table_animation)
		{
			{
				SquirrelObject enumRoot= nSQ::jSQ_GetEnumTable();
				for_each_nEXCEL_excel_baseball_table_animation_ENUM(jEXCEL_SQ_bind_EnumField_BEGIN);
				for_each_nEXCEL_EBatterAnimationType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_ECatcherAnimationType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EEumpireAnimationType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EPitcherAnimationType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
			}
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Batter_Animation>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Batter_Animation*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Batter_Animation*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Batter_Animation*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Batter_Animation)
			for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Batter_Animation)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Batter_Animation>* p = &g_Sys_Batter_Animation;
				jSQ_g_var(p , g_Sys_Batter_Animation);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Catcher_Animation>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Catcher_Animation*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Catcher_Animation*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Catcher_Animation*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Catcher_Animation)
			for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Catcher_Animation)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Catcher_Animation>* p = &g_Sys_Catcher_Animation;
				jSQ_g_var(p , g_Sys_Catcher_Animation);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Pitcher_Animation>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Pitcher_Animation*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Pitcher_Animation*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Pitcher_Animation*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Pitcher_Animation)
			for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Pitcher_Animation)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Pitcher_Animation>* p = &g_Sys_Pitcher_Animation;
				jSQ_g_var(p , g_Sys_Pitcher_Animation);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Umpire_Animation>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Umpire_Animation*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Umpire_Animation*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Umpire_Animation*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Umpire_Animation)
			for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Umpire_Animation)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Umpire_Animation>* p = &g_Sys_Umpire_Animation;
				jSQ_g_var(p , g_Sys_Umpire_Animation);
			}

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

