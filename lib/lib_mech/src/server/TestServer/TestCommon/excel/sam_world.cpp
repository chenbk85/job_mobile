/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "sam_world.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nTESTSERVER_sam_world_Sys_STRUCT_LIST)
		for_each_nTESTSERVER_sam_world_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nTESTSERVER_sam_world_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE


for_each_nTESTSERVER_sam_world_ENUM(jEXCEL_SQ_DECLARE_ENUM_TYPE);
namespace nMech {
	namespace nTESTSERVER {

jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EIssue_Info[] = 
{
	{ 4 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EIssue_Info_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ETile_Sort[] = 
{
	{ 7 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_ETile_Sort_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Tile
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Tile();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Tile


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	Sys_Tile_id_t Sys_Tile::Get_tisid()	{		return (Sys_Tile_id_t)m_tisid;}
	void Sys_Tile::Set_tisid(uint16 v)
	{
		m_tisid=v;
	}

	tcstr Sys_Tile::Get_name()	{		return (tcstr)m_name;}
	void Sys_Tile::Set_name(tcstr v)
	{
		if(!v){ throw _T("Sys_Tile::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	tcstr Sys_Tile::Get_name_kor()	{		return (tcstr)m_name_kor;}
	void Sys_Tile::Set_name_kor(tcstr v)
	{
		if(!v){ throw _T("Sys_Tile::Set_name_kor( val = NULL )");}
		nExcelUtil::jSetter(m_name_kor , v, 32);
	}

	tcstr Sys_Tile::Get_client_file()	{		return (tcstr)m_client_file;}
	void Sys_Tile::Set_client_file(tcstr v)
	{
		if(!v){ throw _T("Sys_Tile::Set_client_file( val = NULL )");}
		nExcelUtil::jSetter(m_client_file , v, 256);
	}

	ETile_Sort Sys_Tile::Get_sort()	{		return (ETile_Sort)m_sort;}
	void Sys_Tile::Set_sort(ETile_Sort v)
	{
		if(v<eBEGIN_ETile_Sort || v>=eEND_ETile_Sort)
		{
			jERROR(_T("Sys_Tile::Set_sort(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ETile_Sort,eEND_ETile_Sort,v);
		}
		m_sort=v;
	}

	int16 Sys_Tile::Get_mspeed()	{		return (int16)m_mspeed;}
	void Sys_Tile::Set_mspeed(int16 v)
	{
		if(v>5000) v = (int16)5000;
		if(v<0) v = 0;
		m_mspeed=v;
	}

	int16 Sys_Tile::Get_visibility()	{		return (int16)m_visibility;}
	void Sys_Tile::Set_visibility(int16 v)
	{
		if(v>100) v = (int16)100;
		if(v<-100) v = -100;
		m_visibility=v;
	}

	bool Sys_Tile::Get_build()	{		return (bool)m_build;}
	void Sys_Tile::Set_build(bool v)
	{
		m_build=v;
	}

	int16 Sys_Tile::Get_fskill()	{		return (int16)m_fskill;}
	void Sys_Tile::Set_fskill(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_fskill=v;
	}

	int16 Sys_Tile::Get_wskill()	{		return (int16)m_wskill;}
	void Sys_Tile::Set_wskill(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_wskill=v;
	}

	int16 Sys_Tile::Get_rskill()	{		return (int16)m_rskill;}
	void Sys_Tile::Set_rskill(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_rskill=v;
	}

	int16 Sys_Tile::Get_hiskill()	{		return (int16)m_hiskill;}
	void Sys_Tile::Set_hiskill(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_hiskill=v;
	}

	Sys_World_id_t Sys_World::Get_wsid()	{		return (Sys_World_id_t)m_wsid;}
	void Sys_World::Set_wsid(uint16 v)
	{
		m_wsid=v;
	}

	tcstr Sys_World::Get_name()	{		return (tcstr)m_name;}
	void Sys_World::Set_name(tcstr v)
	{
		if(!v){ throw _T("Sys_World::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	tcstr Sys_World::Get_name_kor()	{		return (tcstr)m_name_kor;}
	void Sys_World::Set_name_kor(tcstr v)
	{
		if(!v){ throw _T("Sys_World::Set_name_kor( val = NULL )");}
		nExcelUtil::jSetter(m_name_kor , v, 32);
	}

	EIssue_Info Sys_World::Get_issue()	{		return (EIssue_Info)m_issue;}
	void Sys_World::Set_issue(EIssue_Info v)
	{
		if(v<eBEGIN_EIssue_Info || v>=eEND_EIssue_Info)
		{
			jERROR(_T("Sys_World::Set_issue(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EIssue_Info,eEND_EIssue_Info,v);
		}
		m_issue=v;
	}

	tcstr Sys_World::Get_address()	{		return (tcstr)m_address;}
	void Sys_World::Set_address(tcstr v)
	{
		if(!v){ throw _T("Sys_World::Set_address( val = NULL )");}
		nExcelUtil::jSetter(m_address , v, 32);
	}

	tcstr Sys_World::Get_help()	{		return (tcstr)m_help;}
	void Sys_World::Set_help(tcstr v)
	{
		if(!v){ throw _T("Sys_World::Set_help( val = NULL )");}
		nExcelUtil::jSetter(m_help , v, 64);
	}

	int16 Sys_World::Get_goldstart()	{		return (int16)m_goldstart;}
	void Sys_World::Set_goldstart(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<0) v = 0;
		m_goldstart=v;
	}

	int16 Sys_World::Get_ricestart()	{		return (int16)m_ricestart;}
	void Sys_World::Set_ricestart(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<0) v = 0;
		m_ricestart=v;
	}

	int16 Sys_World::Get_treestart()	{		return (int16)m_treestart;}
	void Sys_World::Set_treestart(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<0) v = 0;
		m_treestart=v;
	}

	int16 Sys_World::Get_stonestart()	{		return (int16)m_stonestart;}
	void Sys_World::Set_stonestart(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<0) v = 0;
		m_stonestart=v;
	}

	int16 Sys_World::Get_ironstart()	{		return (int16)m_ironstart;}
	void Sys_World::Set_ironstart(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<0) v = 0;
		m_ironstart=v;
	}

	int16 Sys_World::Get_silkstart()	{		return (int16)m_silkstart;}
	void Sys_World::Set_silkstart(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<0) v = 0;
		m_silkstart=v;
	}

	int16 Sys_World::Get_mspeed()	{		return (int16)m_mspeed;}
	void Sys_World::Set_mspeed(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_mspeed=v;
	}

	int16 Sys_World::Get_re_increase()	{		return (int16)m_re_increase;}
	void Sys_World::Set_re_increase(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_re_increase=v;
	}

	int16 Sys_World::Get_buildtime()	{		return (int16)m_buildtime;}
	void Sys_World::Set_buildtime(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_buildtime=v;
	}

	int16 Sys_World::Get_produtime()	{		return (int16)m_produtime;}
	void Sys_World::Set_produtime(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_produtime=v;
	}

	int16 Sys_World::Get_recrutime()	{		return (int16)m_recrutime;}
	void Sys_World::Set_recrutime(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_recrutime=v;
	}

	int16 Sys_World::Get_researchtime()	{		return (int16)m_researchtime;}
	void Sys_World::Set_researchtime(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_researchtime=v;
	}

	int16 Sys_World::Get_goldamount()	{		return (int16)m_goldamount;}
	void Sys_World::Set_goldamount(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_goldamount=v;
	}

	int16 Sys_World::Get_peo_increase()	{		return (int16)m_peo_increase;}
	void Sys_World::Set_peo_increase(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_peo_increase=v;
	}

	int16 Sys_World::Get_questbenefit()	{		return (int16)m_questbenefit;}
	void Sys_World::Set_questbenefit(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_questbenefit=v;
	}

	int16 Sys_World::Get_huntbenefit()	{		return (int16)m_huntbenefit;}
	void Sys_World::Set_huntbenefit(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_huntbenefit=v;
	}

	int16 Sys_World::Get_appoint_ratio()	{		return (int16)m_appoint_ratio;}
	void Sys_World::Set_appoint_ratio(int16 v)
	{
		if(v>999) v = (int16)999;
		if(v<-999) v = -999;
		m_appoint_ratio=v;
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nTESTSERVER_sam_world_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_Tile g_Sys_Tile;


tcstr Sys_Tile::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_tisid(FromString(out[index++],m_tisid) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getT());
	szKEY = Get_name();
	Set_name_kor(nExcelUtil_StringConverter(out[index++]).getT());
	Set_client_file(nExcelUtil_StringConverter(out[index++]).getT());
	Set_sort(FromString(out[index++],m_sort) );
	Set_mspeed(FromString(out[index++],m_mspeed) );
	Set_visibility(FromString(out[index++],m_visibility) );
	FromString(&m_build,out[index++]);
	Set_fskill(FromString(out[index++],m_fskill) );
	Set_wskill(FromString(out[index++],m_wskill) );
	Set_rskill(FromString(out[index++],m_rskill) );
	Set_hiskill(FromString(out[index++],m_hiskill) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_World g_Sys_World;


tcstr Sys_World::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_wsid(FromString(out[index++],m_wsid) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getT());
	szKEY = Get_name();
	Set_name_kor(nExcelUtil_StringConverter(out[index++]).getT());
	Set_issue(FromString(out[index++],m_issue) );
	Set_address(nExcelUtil_StringConverter(out[index++]).getT());
	Set_help(nExcelUtil_StringConverter(out[index++]).getT());
	Set_goldstart(FromString(out[index++],m_goldstart) );
	Set_ricestart(FromString(out[index++],m_ricestart) );
	Set_treestart(FromString(out[index++],m_treestart) );
	Set_stonestart(FromString(out[index++],m_stonestart) );
	Set_ironstart(FromString(out[index++],m_ironstart) );
	Set_silkstart(FromString(out[index++],m_silkstart) );
	Set_mspeed(FromString(out[index++],m_mspeed) );
	Set_re_increase(FromString(out[index++],m_re_increase) );
	Set_buildtime(FromString(out[index++],m_buildtime) );
	Set_produtime(FromString(out[index++],m_produtime) );
	Set_recrutime(FromString(out[index++],m_recrutime) );
	Set_researchtime(FromString(out[index++],m_researchtime) );
	Set_goldamount(FromString(out[index++],m_goldamount) );
	Set_peo_increase(FromString(out[index++],m_peo_increase) );
	Set_questbenefit(FromString(out[index++],m_questbenefit) );
	Set_huntbenefit(FromString(out[index++],m_huntbenefit) );
	Set_appoint_ratio(FromString(out[index++],m_appoint_ratio) );
	return szKEY;
}

void Sys_Tile::DebugPrint()
{	tname1024_t szBuf;

	for_each_nTESTSERVER_Sys_Tile_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_World::DebugPrint()
{	tname1024_t szBuf;

	for_each_nTESTSERVER_Sys_World_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nTESTSERVER 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nTESTSERVER;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Tile>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_World>);

	namespace nMech { namespace nTESTSERVER
	{
		jSQ_REGIST_BIND(nMech_nTESTSERVER_sam_world)
		{
			{
				SquirrelObject enumRoot= nSQ::jSQ_GetEnumTable();
				for_each_nTESTSERVER_sam_world_ENUM(jEXCEL_SQ_bind_EnumField_BEGIN);
				for_each_nTESTSERVER_EIssue_Info_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_ETile_Sort_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
			}
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Tile>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Tile*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Tile*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Tile*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Tile)
			for_each_nTESTSERVER_Sys_Tile_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Tile)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Tile>* p = &g_Sys_Tile;
				jSQ_g_var(p , g_Sys_Tile);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_World>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_World*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_World*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_World*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_World)
			for_each_nTESTSERVER_Sys_World_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_World)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_World>* p = &g_Sys_World;
				jSQ_g_var(p , g_Sys_World);
			}

		}
	} /*namespace nTESTSERVER */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

