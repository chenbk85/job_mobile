/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_user.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_user_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_user_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_user_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE


for_each_nEXCEL_excel_user_ENUM(jEXCEL_SQ_DECLARE_ENUM_TYPE);
namespace nMech {
	namespace nEXCEL {

jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBuildType[] = 
{
	{ 22 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EBuildType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EOutput[] = 
{
	{ 24 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EOutput_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys__T_BuildObj
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys__T_BuildObj();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys__T_BuildObj


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	EBuildType Sys__T_BuildObj::Get_base_type()	{		return (EBuildType)m_base_type;}
	void Sys__T_BuildObj::Set_base_type(EBuildType v)
	{
		if(v<eBEGIN_EBuildType || v>=eEND_EBuildType)
		{
			jERROR(_T("Sys__T_BuildObj::Set_base_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBuildType,eEND_EBuildType,v);
		}
		m_base_type=v;
	}

	tcstr Sys__T_BuildObj::Get_name()	{		return (tcstr)m_name;}
	void Sys__T_BuildObj::Set_name(tcstr v)
	{
		if(!v){ throw _T("Sys__T_BuildObj::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	uint32 Sys__T_BuildObj::Get_upgradetime()	{		return (uint32)m_upgradetime;}
	void Sys__T_BuildObj::Set_upgradetime(uint32 v)
	{
		m_upgradetime=v;
	}

	int16 Sys__T_BuildObj::Get_tree_num()	{		return (int16)m_tree_num;}
	void Sys__T_BuildObj::Set_tree_num(int16 v)
	{
		m_tree_num=v;
	}

	int16 Sys__T_BuildObj::Get_stone_num()	{		return (int16)m_stone_num;}
	void Sys__T_BuildObj::Set_stone_num(int16 v)
	{
		m_stone_num=v;
	}

	int16 Sys__T_BuildObj::Get_iron_num()	{		return (int16)m_iron_num;}
	void Sys__T_BuildObj::Set_iron_num(int16 v)
	{
		m_iron_num=v;
	}

	int16 Sys__T_BuildObj::Get_silk_num()	{		return (int16)m_silk_num;}
	void Sys__T_BuildObj::Set_silk_num(int16 v)
	{
		m_silk_num=v;
	}

	int16 Sys__T_BuildObj::Get_population_num()	{		return (int16)m_population_num;}
	void Sys__T_BuildObj::Set_population_num(int16 v)
	{
		m_population_num=v;
	}

	Sys_T_Bar_id_t Sys_T_Bar::Get_isid()	{		return (Sys_T_Bar_id_t)m_isid;}
	void Sys_T_Bar::Set_isid(uint16 v)
	{
		m_isid=v;
	}

	tcstr Sys_T_Bar::Get_client_file()	{		return (tcstr)m_client_file;}
	void Sys_T_Bar::Set_client_file(tcstr v)
	{
		if(!v){ throw _T("Sys_T_Bar::Set_client_file( val = NULL )");}
		nExcelUtil::jSetter(m_client_file , v, 256);
	}

	uint32 Sys_T_Bar::Get_upgradetime()	{		return (uint32)m_upgradetime;}
	void Sys_T_Bar::Set_upgradetime(uint32 v)
	{
		m_upgradetime=v;
	}

	int16 Sys_T_Bar::Get_tree_num()	{		return (int16)m_tree_num;}
	void Sys_T_Bar::Set_tree_num(int16 v)
	{
		m_tree_num=v;
	}

	int16 Sys_T_Bar::Get_stone_num()	{		return (int16)m_stone_num;}
	void Sys_T_Bar::Set_stone_num(int16 v)
	{
		m_stone_num=v;
	}

	int16 Sys_T_Bar::Get_iron_num()	{		return (int16)m_iron_num;}
	void Sys_T_Bar::Set_iron_num(int16 v)
	{
		m_iron_num=v;
	}

	int16 Sys_T_Bar::Get_silk_num()	{		return (int16)m_silk_num;}
	void Sys_T_Bar::Set_silk_num(int16 v)
	{
		m_silk_num=v;
	}

	int16 Sys_T_Bar::Get_population_num()	{		return (int16)m_population_num;}
	void Sys_T_Bar::Set_population_num(int16 v)
	{
		m_population_num=v;
	}

	int16 Sys_T_Bar::Get_maxbuild()	{		return (int16)m_maxbuild;}
	void Sys_T_Bar::Set_maxbuild(int16 v)
	{
		m_maxbuild=v;
	}

	int16 Sys_T_Bar::Get_downlevel()	{		return (int16)m_downlevel;}
	void Sys_T_Bar::Set_downlevel(int16 v)
	{
		m_downlevel=v;
	}

	int16 Sys_T_Bar::Get_treereturn()	{		return (int16)m_treereturn;}
	void Sys_T_Bar::Set_treereturn(int16 v)
	{
		m_treereturn=v;
	}

	int16 Sys_T_Bar::Get_stonereturn()	{		return (int16)m_stonereturn;}
	void Sys_T_Bar::Set_stonereturn(int16 v)
	{
		m_stonereturn=v;
	}

	int16 Sys_T_Bar::Get_ironreturn()	{		return (int16)m_ironreturn;}
	void Sys_T_Bar::Set_ironreturn(int16 v)
	{
		m_ironreturn=v;
	}

	int16 Sys_T_Bar::Get_silkreturn()	{		return (int16)m_silkreturn;}
	void Sys_T_Bar::Set_silkreturn(int16 v)
	{
		m_silkreturn=v;
	}

	int16 Sys_T_Bar::Get_populationreturn()	{		return (int16)m_populationreturn;}
	void Sys_T_Bar::Set_populationreturn(int16 v)
	{
		m_populationreturn=v;
	}

	int16 Sys_T_Bar::Get_hideHero()	{		return (int16)m_hideHero;}
	void Sys_T_Bar::Set_hideHero(int16 v)
	{
		m_hideHero=v;
	}

	uint32 Sys_T_Bar::Get_resettime()	{		return (uint32)m_resettime;}
	void Sys_T_Bar::Set_resettime(uint32 v)
	{
		m_resettime=v;
	}

	int16 Sys_T_Bar::Get_itemnum()	{		return (int16)m_itemnum;}
	void Sys_T_Bar::Set_itemnum(int16 v)
	{
		m_itemnum=v;
	}

	Sys_T_Barrack_id_t Sys_T_Barrack::Get_isid()	{		return (Sys_T_Barrack_id_t)m_isid;}
	void Sys_T_Barrack::Set_isid(uint16 v)
	{
		m_isid=v;
	}

	tcstr Sys_T_Barrack::Get_client_file()	{		return (tcstr)m_client_file;}
	void Sys_T_Barrack::Set_client_file(tcstr v)
	{
		if(!v){ throw _T("Sys_T_Barrack::Set_client_file( val = NULL )");}
		nExcelUtil::jSetter(m_client_file , v, 256);
	}

	uint32 Sys_T_Barrack::Get_upgradetime()	{		return (uint32)m_upgradetime;}
	void Sys_T_Barrack::Set_upgradetime(uint32 v)
	{
		m_upgradetime=v;
	}

	int16 Sys_T_Barrack::Get_tree_num()	{		return (int16)m_tree_num;}
	void Sys_T_Barrack::Set_tree_num(int16 v)
	{
		m_tree_num=v;
	}

	int16 Sys_T_Barrack::Get_stone_num()	{		return (int16)m_stone_num;}
	void Sys_T_Barrack::Set_stone_num(int16 v)
	{
		m_stone_num=v;
	}

	int16 Sys_T_Barrack::Get_iron_num()	{		return (int16)m_iron_num;}
	void Sys_T_Barrack::Set_iron_num(int16 v)
	{
		m_iron_num=v;
	}

	int16 Sys_T_Barrack::Get_silk_num()	{		return (int16)m_silk_num;}
	void Sys_T_Barrack::Set_silk_num(int16 v)
	{
		m_silk_num=v;
	}

	int16 Sys_T_Barrack::Get_population_num()	{		return (int16)m_population_num;}
	void Sys_T_Barrack::Set_population_num(int16 v)
	{
		m_population_num=v;
	}

	int16 Sys_T_Barrack::Get_maxbuild()	{		return (int16)m_maxbuild;}
	void Sys_T_Barrack::Set_maxbuild(int16 v)
	{
		m_maxbuild=v;
	}

	int16 Sys_T_Barrack::Get_downlevel()	{		return (int16)m_downlevel;}
	void Sys_T_Barrack::Set_downlevel(int16 v)
	{
		m_downlevel=v;
	}

	int16 Sys_T_Barrack::Get_treereturn()	{		return (int16)m_treereturn;}
	void Sys_T_Barrack::Set_treereturn(int16 v)
	{
		m_treereturn=v;
	}

	int16 Sys_T_Barrack::Get_stonereturn()	{		return (int16)m_stonereturn;}
	void Sys_T_Barrack::Set_stonereturn(int16 v)
	{
		m_stonereturn=v;
	}

	int16 Sys_T_Barrack::Get_ironreturn()	{		return (int16)m_ironreturn;}
	void Sys_T_Barrack::Set_ironreturn(int16 v)
	{
		m_ironreturn=v;
	}

	int16 Sys_T_Barrack::Get_silkreturn()	{		return (int16)m_silkreturn;}
	void Sys_T_Barrack::Set_silkreturn(int16 v)
	{
		m_silkreturn=v;
	}

	int16 Sys_T_Barrack::Get_populationreturn()	{		return (int16)m_populationreturn;}
	void Sys_T_Barrack::Set_populationreturn(int16 v)
	{
		m_populationreturn=v;
	}

	int16 Sys_T_Barrack::Get_s_p_speed()	{		return (int16)m_s_p_speed;}
	void Sys_T_Barrack::Set_s_p_speed(int16 v)
	{
		m_s_p_speed=v;
	}

	int16 Sys_T_Barrack::Get_s_p_cost()	{		return (int16)m_s_p_cost;}
	void Sys_T_Barrack::Set_s_p_cost(int16 v)
	{
		m_s_p_cost=v;
	}

	int16 Sys_T_Barrack::Get_s_output()	{		return (int16)m_s_output;}
	void Sys_T_Barrack::Set_s_output(int16 v)
	{
		m_s_output=v;
	}

	Sys_T_Camp_id_t Sys_T_Camp::Get_isid()	{		return (Sys_T_Camp_id_t)m_isid;}
	void Sys_T_Camp::Set_isid(uint16 v)
	{
		m_isid=v;
	}

	tcstr Sys_T_Camp::Get_client_file()	{		return (tcstr)m_client_file;}
	void Sys_T_Camp::Set_client_file(tcstr v)
	{
		if(!v){ throw _T("Sys_T_Camp::Set_client_file( val = NULL )");}
		nExcelUtil::jSetter(m_client_file , v, 256);
	}

	uint32 Sys_T_Camp::Get_upgradetime()	{		return (uint32)m_upgradetime;}
	void Sys_T_Camp::Set_upgradetime(uint32 v)
	{
		m_upgradetime=v;
	}

	int16 Sys_T_Camp::Get_tree_num()	{		return (int16)m_tree_num;}
	void Sys_T_Camp::Set_tree_num(int16 v)
	{
		m_tree_num=v;
	}

	int16 Sys_T_Camp::Get_stone_num()	{		return (int16)m_stone_num;}
	void Sys_T_Camp::Set_stone_num(int16 v)
	{
		m_stone_num=v;
	}

	int16 Sys_T_Camp::Get_iron_num()	{		return (int16)m_iron_num;}
	void Sys_T_Camp::Set_iron_num(int16 v)
	{
		m_iron_num=v;
	}

	int16 Sys_T_Camp::Get_silk_num()	{		return (int16)m_silk_num;}
	void Sys_T_Camp::Set_silk_num(int16 v)
	{
		m_silk_num=v;
	}

	int16 Sys_T_Camp::Get_population_num()	{		return (int16)m_population_num;}
	void Sys_T_Camp::Set_population_num(int16 v)
	{
		m_population_num=v;
	}

	int16 Sys_T_Camp::Get_maxbuild()	{		return (int16)m_maxbuild;}
	void Sys_T_Camp::Set_maxbuild(int16 v)
	{
		m_maxbuild=v;
	}

	int16 Sys_T_Camp::Get_downlevel()	{		return (int16)m_downlevel;}
	void Sys_T_Camp::Set_downlevel(int16 v)
	{
		m_downlevel=v;
	}

	int16 Sys_T_Camp::Get_treereturn()	{		return (int16)m_treereturn;}
	void Sys_T_Camp::Set_treereturn(int16 v)
	{
		m_treereturn=v;
	}

	int16 Sys_T_Camp::Get_stonereturn()	{		return (int16)m_stonereturn;}
	void Sys_T_Camp::Set_stonereturn(int16 v)
	{
		m_stonereturn=v;
	}

	int16 Sys_T_Camp::Get_ironreturn()	{		return (int16)m_ironreturn;}
	void Sys_T_Camp::Set_ironreturn(int16 v)
	{
		m_ironreturn=v;
	}

	int16 Sys_T_Camp::Get_silkreturn()	{		return (int16)m_silkreturn;}
	void Sys_T_Camp::Set_silkreturn(int16 v)
	{
		m_silkreturn=v;
	}

	int16 Sys_T_Camp::Get_populationreturn()	{		return (int16)m_populationreturn;}
	void Sys_T_Camp::Set_populationreturn(int16 v)
	{
		m_populationreturn=v;
	}

	int16 Sys_T_Camp::Get_f_r_spend()	{		return (int16)m_f_r_spend;}
	void Sys_T_Camp::Set_f_r_spend(int16 v)
	{
		m_f_r_spend=v;
	}

	int32 Sys_T_Camp::Get_f_storage()	{		return (int32)m_f_storage;}
	void Sys_T_Camp::Set_f_storage(int32 v)
	{
		m_f_storage=v;
	}

	Sys_T_Depot_id_t Sys_T_Depot::Get_isid()	{		return (Sys_T_Depot_id_t)m_isid;}
	void Sys_T_Depot::Set_isid(uint16 v)
	{
		m_isid=v;
	}

	tcstr Sys_T_Depot::Get_client_file()	{		return (tcstr)m_client_file;}
	void Sys_T_Depot::Set_client_file(tcstr v)
	{
		if(!v){ throw _T("Sys_T_Depot::Set_client_file( val = NULL )");}
		nExcelUtil::jSetter(m_client_file , v, 256);
	}

	uint32 Sys_T_Depot::Get_upgradetime()	{		return (uint32)m_upgradetime;}
	void Sys_T_Depot::Set_upgradetime(uint32 v)
	{
		m_upgradetime=v;
	}

	int16 Sys_T_Depot::Get_tree_num()	{		return (int16)m_tree_num;}
	void Sys_T_Depot::Set_tree_num(int16 v)
	{
		m_tree_num=v;
	}

	int16 Sys_T_Depot::Get_stone_num()	{		return (int16)m_stone_num;}
	void Sys_T_Depot::Set_stone_num(int16 v)
	{
		m_stone_num=v;
	}

	int16 Sys_T_Depot::Get_iron_num()	{		return (int16)m_iron_num;}
	void Sys_T_Depot::Set_iron_num(int16 v)
	{
		m_iron_num=v;
	}

	int16 Sys_T_Depot::Get_silk_num()	{		return (int16)m_silk_num;}
	void Sys_T_Depot::Set_silk_num(int16 v)
	{
		m_silk_num=v;
	}

	int16 Sys_T_Depot::Get_population_num()	{		return (int16)m_population_num;}
	void Sys_T_Depot::Set_population_num(int16 v)
	{
		m_population_num=v;
	}

	int16 Sys_T_Depot::Get_maxbuild()	{		return (int16)m_maxbuild;}
	void Sys_T_Depot::Set_maxbuild(int16 v)
	{
		m_maxbuild=v;
	}

	int16 Sys_T_Depot::Get_downlevel()	{		return (int16)m_downlevel;}
	void Sys_T_Depot::Set_downlevel(int16 v)
	{
		m_downlevel=v;
	}

	int16 Sys_T_Depot::Get_treereturn()	{		return (int16)m_treereturn;}
	void Sys_T_Depot::Set_treereturn(int16 v)
	{
		m_treereturn=v;
	}

	int16 Sys_T_Depot::Get_stonereturn()	{		return (int16)m_stonereturn;}
	void Sys_T_Depot::Set_stonereturn(int16 v)
	{
		m_stonereturn=v;
	}

	int16 Sys_T_Depot::Get_ironreturn()	{		return (int16)m_ironreturn;}
	void Sys_T_Depot::Set_ironreturn(int16 v)
	{
		m_ironreturn=v;
	}

	int16 Sys_T_Depot::Get_silkreturn()	{		return (int16)m_silkreturn;}
	void Sys_T_Depot::Set_silkreturn(int16 v)
	{
		m_silkreturn=v;
	}

	int16 Sys_T_Depot::Get_populationreturn()	{		return (int16)m_populationreturn;}
	void Sys_T_Depot::Set_populationreturn(int16 v)
	{
		m_populationreturn=v;
	}

	int32 Sys_T_Depot::Get_storage()	{		return (int32)m_storage;}
	void Sys_T_Depot::Set_storage(int32 v)
	{
		m_storage=v;
	}

	Sys_T_Farm_id_t Sys_T_Farm::Get_isid()	{		return (Sys_T_Farm_id_t)m_isid;}
	void Sys_T_Farm::Set_isid(uint16 v)
	{
		m_isid=v;
	}

	tcstr Sys_T_Farm::Get_client_file()	{		return (tcstr)m_client_file;}
	void Sys_T_Farm::Set_client_file(tcstr v)
	{
		if(!v){ throw _T("Sys_T_Farm::Set_client_file( val = NULL )");}
		nExcelUtil::jSetter(m_client_file , v, 256);
	}

	uint32 Sys_T_Farm::Get_upgradetime()	{		return (uint32)m_upgradetime;}
	void Sys_T_Farm::Set_upgradetime(uint32 v)
	{
		m_upgradetime=v;
	}

	int16 Sys_T_Farm::Get_tree_num()	{		return (int16)m_tree_num;}
	void Sys_T_Farm::Set_tree_num(int16 v)
	{
		m_tree_num=v;
	}

	int16 Sys_T_Farm::Get_stone_num()	{		return (int16)m_stone_num;}
	void Sys_T_Farm::Set_stone_num(int16 v)
	{
		m_stone_num=v;
	}

	int16 Sys_T_Farm::Get_iron_num()	{		return (int16)m_iron_num;}
	void Sys_T_Farm::Set_iron_num(int16 v)
	{
		m_iron_num=v;
	}

	int16 Sys_T_Farm::Get_silk_num()	{		return (int16)m_silk_num;}
	void Sys_T_Farm::Set_silk_num(int16 v)
	{
		m_silk_num=v;
	}

	int16 Sys_T_Farm::Get_population_num()	{		return (int16)m_population_num;}
	void Sys_T_Farm::Set_population_num(int16 v)
	{
		m_population_num=v;
	}

	int16 Sys_T_Farm::Get_maxbuild()	{		return (int16)m_maxbuild;}
	void Sys_T_Farm::Set_maxbuild(int16 v)
	{
		m_maxbuild=v;
	}

	int16 Sys_T_Farm::Get_downlevel()	{		return (int16)m_downlevel;}
	void Sys_T_Farm::Set_downlevel(int16 v)
	{
		m_downlevel=v;
	}

	int16 Sys_T_Farm::Get_treereturn()	{		return (int16)m_treereturn;}
	void Sys_T_Farm::Set_treereturn(int16 v)
	{
		m_treereturn=v;
	}

	int16 Sys_T_Farm::Get_stonereturn()	{		return (int16)m_stonereturn;}
	void Sys_T_Farm::Set_stonereturn(int16 v)
	{
		m_stonereturn=v;
	}

	int16 Sys_T_Farm::Get_ironreturn()	{		return (int16)m_ironreturn;}
	void Sys_T_Farm::Set_ironreturn(int16 v)
	{
		m_ironreturn=v;
	}

	int16 Sys_T_Farm::Get_silkreturn()	{		return (int16)m_silkreturn;}
	void Sys_T_Farm::Set_silkreturn(int16 v)
	{
		m_silkreturn=v;
	}

	int16 Sys_T_Farm::Get_populationreturn()	{		return (int16)m_populationreturn;}
	void Sys_T_Farm::Set_populationreturn(int16 v)
	{
		m_populationreturn=v;
	}

	int16 Sys_T_Farm::Get_foodoutput()	{		return (int16)m_foodoutput;}
	void Sys_T_Farm::Set_foodoutput(int16 v)
	{
		m_foodoutput=v;
	}

	Sys_T_House_id_t Sys_T_House::Get_isid()	{		return (Sys_T_House_id_t)m_isid;}
	void Sys_T_House::Set_isid(uint16 v)
	{
		m_isid=v;
	}

	tcstr Sys_T_House::Get_client_file()	{		return (tcstr)m_client_file;}
	void Sys_T_House::Set_client_file(tcstr v)
	{
		if(!v){ throw _T("Sys_T_House::Set_client_file( val = NULL )");}
		nExcelUtil::jSetter(m_client_file , v, 256);
	}

	uint32 Sys_T_House::Get_upgradetime()	{		return (uint32)m_upgradetime;}
	void Sys_T_House::Set_upgradetime(uint32 v)
	{
		m_upgradetime=v;
	}

	int16 Sys_T_House::Get_tree_num()	{		return (int16)m_tree_num;}
	void Sys_T_House::Set_tree_num(int16 v)
	{
		m_tree_num=v;
	}

	int16 Sys_T_House::Get_stone_num()	{		return (int16)m_stone_num;}
	void Sys_T_House::Set_stone_num(int16 v)
	{
		m_stone_num=v;
	}

	int16 Sys_T_House::Get_iron_num()	{		return (int16)m_iron_num;}
	void Sys_T_House::Set_iron_num(int16 v)
	{
		m_iron_num=v;
	}

	int16 Sys_T_House::Get_silk_num()	{		return (int16)m_silk_num;}
	void Sys_T_House::Set_silk_num(int16 v)
	{
		m_silk_num=v;
	}

	int16 Sys_T_House::Get_population_num()	{		return (int16)m_population_num;}
	void Sys_T_House::Set_population_num(int16 v)
	{
		m_population_num=v;
	}

	int16 Sys_T_House::Get_maxbuild()	{		return (int16)m_maxbuild;}
	void Sys_T_House::Set_maxbuild(int16 v)
	{
		m_maxbuild=v;
	}

	int16 Sys_T_House::Get_downlevel()	{		return (int16)m_downlevel;}
	void Sys_T_House::Set_downlevel(int16 v)
	{
		m_downlevel=v;
	}

	int16 Sys_T_House::Get_treereturn()	{		return (int16)m_treereturn;}
	void Sys_T_House::Set_treereturn(int16 v)
	{
		m_treereturn=v;
	}

	int16 Sys_T_House::Get_stonereturn()	{		return (int16)m_stonereturn;}
	void Sys_T_House::Set_stonereturn(int16 v)
	{
		m_stonereturn=v;
	}

	int16 Sys_T_House::Get_ironreturn()	{		return (int16)m_ironreturn;}
	void Sys_T_House::Set_ironreturn(int16 v)
	{
		m_ironreturn=v;
	}

	int16 Sys_T_House::Get_silkreturn()	{		return (int16)m_silkreturn;}
	void Sys_T_House::Set_silkreturn(int16 v)
	{
		m_silkreturn=v;
	}

	int16 Sys_T_House::Get_populationreturn()	{		return (int16)m_populationreturn;}
	void Sys_T_House::Set_populationreturn(int16 v)
	{
		m_populationreturn=v;
	}

	int16 Sys_T_House::Get_maxpopulation()	{		return (int16)m_maxpopulation;}
	void Sys_T_House::Set_maxpopulation(int16 v)
	{
		m_maxpopulation=v;
	}

	Sys_T_HQ_id_t Sys_T_HQ::Get_isid()	{		return (Sys_T_HQ_id_t)m_isid;}
	void Sys_T_HQ::Set_isid(uint16 v)
	{
		m_isid=v;
	}

	tcstr Sys_T_HQ::Get_client_file()	{		return (tcstr)m_client_file;}
	void Sys_T_HQ::Set_client_file(tcstr v)
	{
		if(!v){ throw _T("Sys_T_HQ::Set_client_file( val = NULL )");}
		nExcelUtil::jSetter(m_client_file , v, 256);
	}

	uint32 Sys_T_HQ::Get_upgradetime()	{		return (uint32)m_upgradetime;}
	void Sys_T_HQ::Set_upgradetime(uint32 v)
	{
		m_upgradetime=v;
	}

	int16 Sys_T_HQ::Get_tree_num()	{		return (int16)m_tree_num;}
	void Sys_T_HQ::Set_tree_num(int16 v)
	{
		m_tree_num=v;
	}

	int16 Sys_T_HQ::Get_stone_num()	{		return (int16)m_stone_num;}
	void Sys_T_HQ::Set_stone_num(int16 v)
	{
		m_stone_num=v;
	}

	int16 Sys_T_HQ::Get_iron_num()	{		return (int16)m_iron_num;}
	void Sys_T_HQ::Set_iron_num(int16 v)
	{
		m_iron_num=v;
	}

	int16 Sys_T_HQ::Get_silk_num()	{		return (int16)m_silk_num;}
	void Sys_T_HQ::Set_silk_num(int16 v)
	{
		m_silk_num=v;
	}

	int16 Sys_T_HQ::Get_population_num()	{		return (int16)m_population_num;}
	void Sys_T_HQ::Set_population_num(int16 v)
	{
		m_population_num=v;
	}

	int16 Sys_T_HQ::Get_maxbuild()	{		return (int16)m_maxbuild;}
	void Sys_T_HQ::Set_maxbuild(int16 v)
	{
		m_maxbuild=v;
	}

	int16 Sys_T_HQ::Get_downlevel()	{		return (int16)m_downlevel;}
	void Sys_T_HQ::Set_downlevel(int16 v)
	{
		m_downlevel=v;
	}

	int16 Sys_T_HQ::Get_treereturn()	{		return (int16)m_treereturn;}
	void Sys_T_HQ::Set_treereturn(int16 v)
	{
		m_treereturn=v;
	}

	int16 Sys_T_HQ::Get_stonereturn()	{		return (int16)m_stonereturn;}
	void Sys_T_HQ::Set_stonereturn(int16 v)
	{
		m_stonereturn=v;
	}

	int16 Sys_T_HQ::Get_ironreturn()	{		return (int16)m_ironreturn;}
	void Sys_T_HQ::Set_ironreturn(int16 v)
	{
		m_ironreturn=v;
	}

	int16 Sys_T_HQ::Get_silkreturn()	{		return (int16)m_silkreturn;}
	void Sys_T_HQ::Set_silkreturn(int16 v)
	{
		m_silkreturn=v;
	}

	int16 Sys_T_HQ::Get_populationreturn()	{		return (int16)m_populationreturn;}
	void Sys_T_HQ::Set_populationreturn(int16 v)
	{
		m_populationreturn=v;
	}

	int16 Sys_T_HQ::Get_getgold()	{		return (int16)m_getgold;}
	void Sys_T_HQ::Set_getgold(int16 v)
	{
		m_getgold=v;
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_user_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys__T_BuildObj g_Sys__T_BuildObj;


tcstr Sys__T_BuildObj::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_base_type(FromString(out[index++],m_base_type) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getT());
	szKEY = Get_name();
	Set_upgradetime(FromString(out[index++],m_upgradetime) );
	Set_tree_num(FromString(out[index++],m_tree_num) );
	Set_stone_num(FromString(out[index++],m_stone_num) );
	Set_iron_num(FromString(out[index++],m_iron_num) );
	Set_silk_num(FromString(out[index++],m_silk_num) );
	Set_population_num(FromString(out[index++],m_population_num) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_T_Bar g_Sys_T_Bar;


tcstr Sys_T_Bar::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_isid(FromString(out[index++],m_isid) );
	Set_client_file(nExcelUtil_StringConverter(out[index++]).getT());
	Set_upgradetime(FromString(out[index++],m_upgradetime) );
	Set_tree_num(FromString(out[index++],m_tree_num) );
	Set_stone_num(FromString(out[index++],m_stone_num) );
	Set_iron_num(FromString(out[index++],m_iron_num) );
	Set_silk_num(FromString(out[index++],m_silk_num) );
	Set_population_num(FromString(out[index++],m_population_num) );
	Set_maxbuild(FromString(out[index++],m_maxbuild) );
	Set_downlevel(FromString(out[index++],m_downlevel) );
	Set_treereturn(FromString(out[index++],m_treereturn) );
	Set_stonereturn(FromString(out[index++],m_stonereturn) );
	Set_ironreturn(FromString(out[index++],m_ironreturn) );
	Set_silkreturn(FromString(out[index++],m_silkreturn) );
	Set_populationreturn(FromString(out[index++],m_populationreturn) );
	Set_hideHero(FromString(out[index++],m_hideHero) );
	Set_resettime(FromString(out[index++],m_resettime) );
	Set_itemnum(FromString(out[index++],m_itemnum) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_T_Barrack g_Sys_T_Barrack;


tcstr Sys_T_Barrack::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_isid(FromString(out[index++],m_isid) );
	Set_client_file(nExcelUtil_StringConverter(out[index++]).getT());
	Set_upgradetime(FromString(out[index++],m_upgradetime) );
	Set_tree_num(FromString(out[index++],m_tree_num) );
	Set_stone_num(FromString(out[index++],m_stone_num) );
	Set_iron_num(FromString(out[index++],m_iron_num) );
	Set_silk_num(FromString(out[index++],m_silk_num) );
	Set_population_num(FromString(out[index++],m_population_num) );
	Set_maxbuild(FromString(out[index++],m_maxbuild) );
	Set_downlevel(FromString(out[index++],m_downlevel) );
	Set_treereturn(FromString(out[index++],m_treereturn) );
	Set_stonereturn(FromString(out[index++],m_stonereturn) );
	Set_ironreturn(FromString(out[index++],m_ironreturn) );
	Set_silkreturn(FromString(out[index++],m_silkreturn) );
	Set_populationreturn(FromString(out[index++],m_populationreturn) );
	Set_s_p_speed(FromString(out[index++],m_s_p_speed) );
	Set_s_p_cost(FromString(out[index++],m_s_p_cost) );
	Set_s_output(FromString(out[index++],m_s_output) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_T_Camp g_Sys_T_Camp;


tcstr Sys_T_Camp::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_isid(FromString(out[index++],m_isid) );
	Set_client_file(nExcelUtil_StringConverter(out[index++]).getT());
	Set_upgradetime(FromString(out[index++],m_upgradetime) );
	Set_tree_num(FromString(out[index++],m_tree_num) );
	Set_stone_num(FromString(out[index++],m_stone_num) );
	Set_iron_num(FromString(out[index++],m_iron_num) );
	Set_silk_num(FromString(out[index++],m_silk_num) );
	Set_population_num(FromString(out[index++],m_population_num) );
	Set_maxbuild(FromString(out[index++],m_maxbuild) );
	Set_downlevel(FromString(out[index++],m_downlevel) );
	Set_treereturn(FromString(out[index++],m_treereturn) );
	Set_stonereturn(FromString(out[index++],m_stonereturn) );
	Set_ironreturn(FromString(out[index++],m_ironreturn) );
	Set_silkreturn(FromString(out[index++],m_silkreturn) );
	Set_populationreturn(FromString(out[index++],m_populationreturn) );
	Set_f_r_spend(FromString(out[index++],m_f_r_spend) );
	Set_f_storage(FromString(out[index++],m_f_storage) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_T_Depot g_Sys_T_Depot;


tcstr Sys_T_Depot::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_isid(FromString(out[index++],m_isid) );
	Set_client_file(nExcelUtil_StringConverter(out[index++]).getT());
	Set_upgradetime(FromString(out[index++],m_upgradetime) );
	Set_tree_num(FromString(out[index++],m_tree_num) );
	Set_stone_num(FromString(out[index++],m_stone_num) );
	Set_iron_num(FromString(out[index++],m_iron_num) );
	Set_silk_num(FromString(out[index++],m_silk_num) );
	Set_population_num(FromString(out[index++],m_population_num) );
	Set_maxbuild(FromString(out[index++],m_maxbuild) );
	Set_downlevel(FromString(out[index++],m_downlevel) );
	Set_treereturn(FromString(out[index++],m_treereturn) );
	Set_stonereturn(FromString(out[index++],m_stonereturn) );
	Set_ironreturn(FromString(out[index++],m_ironreturn) );
	Set_silkreturn(FromString(out[index++],m_silkreturn) );
	Set_populationreturn(FromString(out[index++],m_populationreturn) );
	Set_storage(FromString(out[index++],m_storage) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_T_Farm g_Sys_T_Farm;


tcstr Sys_T_Farm::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_isid(FromString(out[index++],m_isid) );
	Set_client_file(nExcelUtil_StringConverter(out[index++]).getT());
	Set_upgradetime(FromString(out[index++],m_upgradetime) );
	Set_tree_num(FromString(out[index++],m_tree_num) );
	Set_stone_num(FromString(out[index++],m_stone_num) );
	Set_iron_num(FromString(out[index++],m_iron_num) );
	Set_silk_num(FromString(out[index++],m_silk_num) );
	Set_population_num(FromString(out[index++],m_population_num) );
	Set_maxbuild(FromString(out[index++],m_maxbuild) );
	Set_downlevel(FromString(out[index++],m_downlevel) );
	Set_treereturn(FromString(out[index++],m_treereturn) );
	Set_stonereturn(FromString(out[index++],m_stonereturn) );
	Set_ironreturn(FromString(out[index++],m_ironreturn) );
	Set_silkreturn(FromString(out[index++],m_silkreturn) );
	Set_populationreturn(FromString(out[index++],m_populationreturn) );
	Set_foodoutput(FromString(out[index++],m_foodoutput) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_T_House g_Sys_T_House;


tcstr Sys_T_House::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_isid(FromString(out[index++],m_isid) );
	Set_client_file(nExcelUtil_StringConverter(out[index++]).getT());
	Set_upgradetime(FromString(out[index++],m_upgradetime) );
	Set_tree_num(FromString(out[index++],m_tree_num) );
	Set_stone_num(FromString(out[index++],m_stone_num) );
	Set_iron_num(FromString(out[index++],m_iron_num) );
	Set_silk_num(FromString(out[index++],m_silk_num) );
	Set_population_num(FromString(out[index++],m_population_num) );
	Set_maxbuild(FromString(out[index++],m_maxbuild) );
	Set_downlevel(FromString(out[index++],m_downlevel) );
	Set_treereturn(FromString(out[index++],m_treereturn) );
	Set_stonereturn(FromString(out[index++],m_stonereturn) );
	Set_ironreturn(FromString(out[index++],m_ironreturn) );
	Set_silkreturn(FromString(out[index++],m_silkreturn) );
	Set_populationreturn(FromString(out[index++],m_populationreturn) );
	Set_maxpopulation(FromString(out[index++],m_maxpopulation) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_T_HQ g_Sys_T_HQ;


tcstr Sys_T_HQ::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_isid(FromString(out[index++],m_isid) );
	Set_client_file(nExcelUtil_StringConverter(out[index++]).getT());
	Set_upgradetime(FromString(out[index++],m_upgradetime) );
	Set_tree_num(FromString(out[index++],m_tree_num) );
	Set_stone_num(FromString(out[index++],m_stone_num) );
	Set_iron_num(FromString(out[index++],m_iron_num) );
	Set_silk_num(FromString(out[index++],m_silk_num) );
	Set_population_num(FromString(out[index++],m_population_num) );
	Set_maxbuild(FromString(out[index++],m_maxbuild) );
	Set_downlevel(FromString(out[index++],m_downlevel) );
	Set_treereturn(FromString(out[index++],m_treereturn) );
	Set_stonereturn(FromString(out[index++],m_stonereturn) );
	Set_ironreturn(FromString(out[index++],m_ironreturn) );
	Set_silkreturn(FromString(out[index++],m_silkreturn) );
	Set_populationreturn(FromString(out[index++],m_populationreturn) );
	Set_getgold(FromString(out[index++],m_getgold) );
	return szKEY;
}

void Sys__T_BuildObj::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_T_Bar::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_T_Barrack::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_T_Camp::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_T_Depot::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_T_Farm::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_T_House::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_T_HQ::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys__T_BuildObj>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_T_Bar>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_T_Barrack>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_T_Camp>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_T_Depot>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_T_Farm>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_T_House>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_T_HQ>);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_user)
		{
			{
				SquirrelObject enumRoot= nSQ::jSQ_GetEnumTable();
				for_each_nEXCEL_excel_user_ENUM(jEXCEL_SQ_bind_EnumField_BEGIN);
				for_each_nEXCEL_EBuildType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EOutput_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
			}
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys__T_BuildObj>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys__T_BuildObj*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys__T_BuildObj*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys__T_BuildObj*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys__T_BuildObj)
			for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys__T_BuildObj)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys__T_BuildObj>* p = &g_Sys__T_BuildObj;
				jSQ_g_var(p , g_Sys__T_BuildObj);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_T_Bar>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_T_Bar*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_T_Bar*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_T_Bar*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_T_Bar)
			for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_T_Bar)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_T_Bar>* p = &g_Sys_T_Bar;
				jSQ_g_var(p , g_Sys_T_Bar);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_T_Barrack>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_T_Barrack*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_T_Barrack*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_T_Barrack*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_T_Barrack)
			for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_T_Barrack)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_T_Barrack>* p = &g_Sys_T_Barrack;
				jSQ_g_var(p , g_Sys_T_Barrack);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_T_Camp>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_T_Camp*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_T_Camp*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_T_Camp*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_T_Camp)
			for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_T_Camp)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_T_Camp>* p = &g_Sys_T_Camp;
				jSQ_g_var(p , g_Sys_T_Camp);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_T_Depot>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_T_Depot*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_T_Depot*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_T_Depot*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_T_Depot)
			for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_T_Depot)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_T_Depot>* p = &g_Sys_T_Depot;
				jSQ_g_var(p , g_Sys_T_Depot);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_T_Farm>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_T_Farm*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_T_Farm*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_T_Farm*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_T_Farm)
			for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_T_Farm)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_T_Farm>* p = &g_Sys_T_Farm;
				jSQ_g_var(p , g_Sys_T_Farm);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_T_House>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_T_House*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_T_House*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_T_House*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_T_House)
			for_each_nEXCEL_Sys_T_House_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_T_House)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_T_House>* p = &g_Sys_T_House;
				jSQ_g_var(p , g_Sys_T_House);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_T_HQ>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_T_HQ*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_T_HQ*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_T_HQ*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_T_HQ)
			for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_T_HQ)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_T_HQ>* p = &g_Sys_T_HQ;
				jSQ_g_var(p , g_Sys_T_HQ);
			}

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

