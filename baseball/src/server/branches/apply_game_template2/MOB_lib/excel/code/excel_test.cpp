/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_test.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_test_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_test_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_test_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE

namespace nMech {
	namespace nEXCEL {


#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys__T_Base
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys__T_Base();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys__T_Base


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	Sys__T_Base_id_t Sys__T_Base::Get_level()	{		return (Sys__T_Base_id_t)m_level_u16;}
	void Sys__T_Base::Set_level(uint16 v)
	{
		m_level_u16=v;
	}

	EBuildType_test Sys__T_Base::Get_base_type()	{		return (EBuildType_test)m_base_type_e;}
	void Sys__T_Base::Set_base_type(EBuildType_test v)
	{
		if(v<eBEGIN_EBuildType_test || v>=eEND_EBuildType_test)
		{
			jERROR(_T("Sys__T_Base::Set_base_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBuildType_test,eEND_EBuildType_test,v);
		}
		m_base_type_e=v;
	}

	tcstr Sys__T_Base::Get_name()	{		return (tcstr)m_name_t32;}
	void Sys__T_Base::Set_name(tcstr v)
	{
		if(!v){ throw _T("Sys__T_Base::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name_t32 , v, 32);
	}

	uint32 Sys__T_Base::Get_upgradetime()	{		return (uint32)m_upgradetime_i32;}
	void Sys__T_Base::Set_upgradetime(uint32 v)
	{
		m_upgradetime_i32=v;
	}

	int16 Sys__T_Base::Get_tree_num()	{		return (int16)m_tree_num_i16;}
	void Sys__T_Base::Set_tree_num(int16 v)
	{
		m_tree_num_i16=v;
	}

	int16 Sys__T_Base::Get_stone_num()	{		return (int16)m_stone_num_i16;}
	void Sys__T_Base::Set_stone_num(int16 v)
	{
		m_stone_num_i16=v;
	}

	int16 Sys__T_Base::Get_iron_num()	{		return (int16)m_iron_num_i16;}
	void Sys__T_Base::Set_iron_num(int16 v)
	{
		m_iron_num_i16=v;
	}

	int16 Sys__T_Base::Get_silk_num()	{		return (int16)m_silk_num_i16;}
	void Sys__T_Base::Set_silk_num(int16 v)
	{
		m_silk_num_i16=v;
	}

	int16 Sys__T_Base::Get_population_num()	{		return (int16)m_population_num_i16;}
	void Sys__T_Base::Set_population_num(int16 v)
	{
		m_population_num_i16=v;
	}

	int16 Sys_T_Test::Get_maxbuild()	{		return (int16)m_maxbuild_i16;}
	void Sys_T_Test::Set_maxbuild(int16 v)
	{
		m_maxbuild_i16=v;
	}

	int16 Sys_T_Test::Get_downlevel()	{		return (int16)m_downlevel_i16;}
	void Sys_T_Test::Set_downlevel(int16 v)
	{
		m_downlevel_i16=v;
	}

	int16 Sys_T_Test::Get_populationreturn()	{		return (int16)m_populationreturn_i16;}
	void Sys_T_Test::Set_populationreturn(int16 v)
	{
		m_populationreturn_i16=v;
	}

	EBuildType_test Sys_T_Test::Get_test()	{		return (EBuildType_test)m_test_e;}
	void Sys_T_Test::Set_test(EBuildType_test v)
	{
		if(v<eBEGIN_EBuildType_test || v>=eEND_EBuildType_test)
		{
			jERROR(_T("Sys_T_Test::Set_test(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBuildType_test,eEND_EBuildType_test,v);
		}
		m_test_e=v;
	}

	int16 Sys_T_Test::Get_getgold()	{		return (int16)m_getgold_i16;}
	void Sys_T_Test::Set_getgold(int16 v)
	{
		m_getgold_i16=v;
	}

	int16 Sys_T_Test2::Get_maxbuild2()	{		return (int16)m_maxbuild2_i16;}
	void Sys_T_Test2::Set_maxbuild2(int16 v)
	{
		m_maxbuild2_i16=v;
	}

	int16 Sys_T_Test2::Get_downlevel2()	{		return (int16)m_downlevel2_i16;}
	void Sys_T_Test2::Set_downlevel2(int16 v)
	{
		m_downlevel2_i16=v;
	}

	int16 Sys_T_Test2::Get_treereturn2()	{		return (int16)m_treereturn2_i16;}
	void Sys_T_Test2::Set_treereturn2(int16 v)
	{
		m_treereturn2_i16=v;
	}

	EOutput_test Sys_T_Test2::Get_stonereturn2()	{		return (EOutput_test)m_stonereturn2_e;}
	void Sys_T_Test2::Set_stonereturn2(EOutput_test v)
	{
		if(v<eBEGIN_EOutput_test || v>=eEND_EOutput_test)
		{
			jERROR(_T("Sys_T_Test2::Set_stonereturn2(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EOutput_test,eEND_EOutput_test,v);
		}
		m_stonereturn2_e=v;
	}

	int16 Sys_T_Test2::Get_populationreturn2()	{		return (int16)m_populationreturn2_i16;}
	void Sys_T_Test2::Set_populationreturn2(int16 v)
	{
		m_populationreturn2_i16=v;
	}

	EBuildType_test Sys_T_Test2::Get_test2()	{		return (EBuildType_test)m_test2_e;}
	void Sys_T_Test2::Set_test2(EBuildType_test v)
	{
		if(v<eBEGIN_EBuildType_test || v>=eEND_EBuildType_test)
		{
			jERROR(_T("Sys_T_Test2::Set_test2(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBuildType_test,eEND_EBuildType_test,v);
		}
		m_test2_e=v;
	}

	int16 Sys_T_Test2::Get_getgold2()	{		return (int16)m_getgold2_i16;}
	void Sys_T_Test2::Set_getgold2(int16 v)
	{
		m_getgold2_i16=v;
	}

	int16 Sys_T_Test3::Get_maxbuild2()	{		return (int16)m_maxbuild2_i16;}
	void Sys_T_Test3::Set_maxbuild2(int16 v)
	{
		m_maxbuild2_i16=v;
	}

	EOutput_test Sys_T_Test3::Get_stonereturn2()	{		return (EOutput_test)m_stonereturn2_e;}
	void Sys_T_Test3::Set_stonereturn2(EOutput_test v)
	{
		if(v<eBEGIN_EOutput_test || v>=eEND_EOutput_test)
		{
			jERROR(_T("Sys_T_Test3::Set_stonereturn2(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EOutput_test,eEND_EOutput_test,v);
		}
		m_stonereturn2_e=v;
	}

	int16 Sys_T_Test3::Get_populationreturn2()	{		return (int16)m_populationreturn2_i16;}
	void Sys_T_Test3::Set_populationreturn2(int16 v)
	{
		m_populationreturn2_i16=v;
	}

	EBuildType_test Sys_T_Test3::Get_test2()	{		return (EBuildType_test)m_test2_e;}
	void Sys_T_Test3::Set_test2(EBuildType_test v)
	{
		if(v<eBEGIN_EBuildType_test || v>=eEND_EBuildType_test)
		{
			jERROR(_T("Sys_T_Test3::Set_test2(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBuildType_test,eEND_EBuildType_test,v);
		}
		m_test2_e=v;
	}

	int16 Sys_T_Test3::Get_getgold2()	{		return (int16)m_getgold2_i16;}
	void Sys_T_Test3::Set_getgold2(int16 v)
	{
		m_getgold2_i16=v;
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_test_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

OUT nMech::nUtil::jCSV_File<Sys__T_Base> g_Sys__T_Base;


tcstr Sys__T_Base::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_level(FromString(&m_level_u16,out[index++]) );
	Set_base_type(FromString(&m_base_type_e,out[index++]) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getT());
	szKEY = Get_name();
	Set_upgradetime(FromString(&m_upgradetime_i32,out[index++]) );
	Set_tree_num(FromString(&m_tree_num_i16,out[index++]) );
	Set_stone_num(FromString(&m_stone_num_i16,out[index++]) );
	Set_iron_num(FromString(&m_iron_num_i16,out[index++]) );
	Set_silk_num(FromString(&m_silk_num_i16,out[index++]) );
	Set_population_num(FromString(&m_population_num_i16,out[index++]) );
	return szKEY;
}

OUT nMech::nUtil::jCSV_File<Sys_T_Test> g_Sys_T_Test;


tcstr Sys_T_Test::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	szKEY = Sys__T_Base::ReadCSV(iRecord ,out,index,false);
	Set_maxbuild(FromString(&m_maxbuild_i16,out[index++]) );
	Set_downlevel(FromString(&m_downlevel_i16,out[index++]) );
	Set_populationreturn(FromString(&m_populationreturn_i16,out[index++]) );
	Set_test(FromString(&m_test_e,out[index++]) );
	Set_getgold(FromString(&m_getgold_i16,out[index++]) );
	return szKEY;
}

OUT nMech::nUtil::jCSV_File<Sys_T_Test2> g_Sys_T_Test2;


tcstr Sys_T_Test2::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	szKEY = Sys_T_Test::ReadCSV(iRecord ,out,index,false);
	Set_maxbuild2(FromString(&m_maxbuild2_i16,out[index++]) );
	Set_downlevel2(FromString(&m_downlevel2_i16,out[index++]) );
	Set_treereturn2(FromString(&m_treereturn2_i16,out[index++]) );
	Set_stonereturn2(FromString(&m_stonereturn2_e,out[index++]) );
	Set_populationreturn2(FromString(&m_populationreturn2_i16,out[index++]) );
	Set_test2(FromString(&m_test2_e,out[index++]) );
	Set_getgold2(FromString(&m_getgold2_i16,out[index++]) );
	return szKEY;
}

OUT nMech::nUtil::jCSV_File<Sys_T_Test3> g_Sys_T_Test3;


tcstr Sys_T_Test3::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	szKEY = Sys__T_Base::ReadCSV(iRecord ,out,index,false);
	Set_maxbuild2(FromString(&m_maxbuild2_i16,out[index++]) );
	Set_stonereturn2(FromString(&m_stonereturn2_e,out[index++]) );
	Set_populationreturn2(FromString(&m_populationreturn2_i16,out[index++]) );
	Set_test2(FromString(&m_test2_e,out[index++]) );
	Set_getgold2(FromString(&m_getgold2_i16,out[index++]) );
	return szKEY;
}

void Sys__T_Base::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_T_Test::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_T_Test2::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_T_Test3::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	typedef nMech::nUtil::jCSV_File<nMech::nEXCEL::Sys__T_Base> Sys__T_Base_csv_file_t;
	DECLARE_INSTANCE_TYPE(Sys__T_Base_csv_file_t);

	typedef nMech::nUtil::jCSV_File<nMech::nEXCEL::Sys_T_Test> Sys_T_Test_csv_file_t;
	DECLARE_INSTANCE_TYPE(Sys_T_Test_csv_file_t);

	typedef nMech::nUtil::jCSV_File<nMech::nEXCEL::Sys_T_Test2> Sys_T_Test2_csv_file_t;
	DECLARE_INSTANCE_TYPE(Sys_T_Test2_csv_file_t);

	typedef nMech::nUtil::jCSV_File<nMech::nEXCEL::Sys_T_Test3> Sys_T_Test3_csv_file_t;
	DECLARE_INSTANCE_TYPE(Sys_T_Test3_csv_file_t);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_test)
		{
			jSQ_Interface(Sys__T_Base_csv_file_t)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys__T_Base*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys__T_Base*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys__T_Base*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys__T_Base)
			for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys__T_Base)
			jSQ_end();
			jSQ_g_var(&g_Sys__T_Base,g_Sys__T_Base);

			jSQ_Interface(Sys_T_Test_csv_file_t)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_T_Test*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_T_Test*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_T_Test*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_T_Test)
			for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
				jSQ_fn(GetBase_Sys__T_Base,"Sys__T_Base*()","Get base Table")
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_T_Test)
			jSQ_end();
			jSQ_g_var(&g_Sys_T_Test,g_Sys_T_Test);

			jSQ_Interface(Sys_T_Test2_csv_file_t)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_T_Test2*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_T_Test2*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_T_Test2*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_T_Test2)
			for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
				jSQ_fn(GetBase_Sys_T_Test,"Sys_T_Test*()","Get base Table")
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_T_Test2)
			jSQ_end();
			jSQ_g_var(&g_Sys_T_Test2,g_Sys_T_Test2);

			jSQ_Interface(Sys_T_Test3_csv_file_t)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_T_Test3*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_T_Test3*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_T_Test3*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_T_Test3)
			for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
				jSQ_fn(GetBase_Sys__T_Base,"Sys__T_Base*()","Get base Table")
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_T_Test3)
			jSQ_end();
			jSQ_g_var(&g_Sys_T_Test3,g_Sys_T_Test3);

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

