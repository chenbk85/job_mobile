/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_force.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_force_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_force_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_force_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE


for_each_nEXCEL_excel_force_ENUM(jEXCEL_SQ_DECLARE_ENUM_TYPE);
namespace nMech {
	namespace nEXCEL {

jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_E_ClassItemA[] = 
{
	{ 10 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_E_ClassItemA_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_E_ClassItemB[] = 
{
	{ 8 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_E_ClassItemB_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_E_W_Event[] = 
{
	{ 6 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_E_W_Event_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EForceClass[] = 
{
	{ 5 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EForceClass_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EForcePosType[] = 
{
	{ 4 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EForcePosType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Force
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Force();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Force


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	Sys_Force_id_t Sys_Force::Get_fsid()	{		return (Sys_Force_id_t)m_fsid;}
	void Sys_Force::Set_fsid(uint16 v)
	{
		m_fsid=v;
	}

	tcstr Sys_Force::Get_name()	{		return (tcstr)m_name;}
	void Sys_Force::Set_name(tcstr v)
	{
		if(!v){ throw _T("Sys_Force::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	tcstr Sys_Force::Get_name_kor()	{		return (tcstr)m_name_kor;}
	void Sys_Force::Set_name_kor(tcstr v)
	{
		if(!v){ throw _T("Sys_Force::Set_name_kor( val = NULL )");}
		nExcelUtil::jSetter(m_name_kor , v, 32);
	}

	EForceClass Sys_Force::Get_force_class()	{		return (EForceClass)m_force_class;}
	void Sys_Force::Set_force_class(EForceClass v)
	{
		if(v<eBEGIN_EForceClass || v>=eEND_EForceClass)
		{
			jERROR(_T("Sys_Force::Set_force_class(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EForceClass,eEND_EForceClass,v);
		}
		m_force_class=v;
	}

	E_ClassItemA Sys_Force::Get_forceClassItemA()	{		return (E_ClassItemA)m_forceClassItemA;}
	void Sys_Force::Set_forceClassItemA(E_ClassItemA v)
	{
		if(v<eBEGIN_E_ClassItemA || v>=eEND_E_ClassItemA)
		{
			jERROR(_T("Sys_Force::Set_forceClassItemA(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_E_ClassItemA,eEND_E_ClassItemA,v);
		}
		m_forceClassItemA=v;
	}

	E_ClassItemB Sys_Force::Get_forceClassItemB()	{		return (E_ClassItemB)m_forceClassItemB;}
	void Sys_Force::Set_forceClassItemB(E_ClassItemB v)
	{
		if(v<eBEGIN_E_ClassItemB || v>=eEND_E_ClassItemB)
		{
			jERROR(_T("Sys_Force::Set_forceClassItemB(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_E_ClassItemB,eEND_E_ClassItemB,v);
		}
		m_forceClassItemB=v;
	}

	int16 Sys_Force::Get_att()	{		return (int16)m_att;}
	void Sys_Force::Set_att(int16 v)
	{
		if(v>100) v = (int16)100;
		if(v<0) v = 0;
		m_att=v;
	}

	int16 Sys_Force::Get_def()	{		return (int16)m_def;}
	void Sys_Force::Set_def(int16 v)
	{
		if(v>100) v = (int16)100;
		if(v<0) v = 0;
		m_def=v;
	}

	int16 Sys_Force::Get_mspeed()	{		return (int16)m_mspeed;}
	void Sys_Force::Set_mspeed(int16 v)
	{
		if(v>1000) v = (int16)1000;
		if(v<0) v = 0;
		m_mspeed=v;
	}

	int16 Sys_Force::Get_aspeed()	{		return (int16)m_aspeed;}
	void Sys_Force::Set_aspeed(int16 v)
	{
		if(v>10000) v = (int16)10000;
		if(v<0) v = 0;
		m_aspeed=v;
	}

	int16 Sys_Force::Get_srange()	{		return (int16)m_srange;}
	void Sys_Force::Set_srange(int16 v)
	{
		if(v>100) v = (int16)100;
		if(v<0) v = 0;
		m_srange=v;
	}

	int16 Sys_Force::Get_suvival_ratio()	{		return (int16)m_suvival_ratio;}
	void Sys_Force::Set_suvival_ratio(int16 v)
	{
		if(v>1000) v = (int16)1000;
		if(v<0) v = 0;
		m_suvival_ratio=v;
	}

	int16 Sys_Force::Get_kill_ratio()	{		return (int16)m_kill_ratio;}
	void Sys_Force::Set_kill_ratio(int16 v)
	{
		if(v>1000) v = (int16)1000;
		if(v<0) v = 0;
		m_kill_ratio=v;
	}

	int16 Sys_Force::Get_client_id()	{		return (int16)m_client_id;}
	void Sys_Force::Set_client_id(int16 v)
	{
		if(v>100) v = (int16)100;
		if(v<0) v = 0;
		m_client_id=v;
	}

	int16 Sys_Force::Get_unit_load()	{		return (int16)m_unit_load;}
	void Sys_Force::Set_unit_load(int16 v)
	{
		if(v>100000) v = (int16)100000;
		if(v<0) v = 0;
		m_unit_load=v;
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_force_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_Force g_Sys_Force;


tcstr Sys_Force::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_fsid(FromString(out[index++],m_fsid) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getT());
	szKEY = Get_name();
	Set_name_kor(nExcelUtil_StringConverter(out[index++]).getT());
	Set_force_class(FromString(out[index++],m_force_class) );
	Set_forceClassItemA(FromString(out[index++],m_forceClassItemA) );
	Set_forceClassItemB(FromString(out[index++],m_forceClassItemB) );
	Set_att(FromString(out[index++],m_att) );
	Set_def(FromString(out[index++],m_def) );
	Set_mspeed(FromString(out[index++],m_mspeed) );
	Set_aspeed(FromString(out[index++],m_aspeed) );
	Set_srange(FromString(out[index++],m_srange) );
	Set_suvival_ratio(FromString(out[index++],m_suvival_ratio) );
	Set_kill_ratio(FromString(out[index++],m_kill_ratio) );
	Set_client_id(FromString(out[index++],m_client_id) );
	Set_unit_load(FromString(out[index++],m_unit_load) );
	return szKEY;
}

void Sys_Force::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Force_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Force>);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_force)
		{
			{
				SquirrelObject enumRoot= nSQ::jSQ_GetEnumTable();
				for_each_nEXCEL_excel_force_ENUM(jEXCEL_SQ_bind_EnumField_BEGIN);
				for_each_nEXCEL_E_ClassItemA_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_E_ClassItemB_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_E_W_Event_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EForceClass_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EForcePosType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
			}
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Force>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Force*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Force*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Force*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Force)
			for_each_nEXCEL_Sys_Force_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Force)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Force>* p = &g_Sys_Force;
				jSQ_g_var(p , g_Sys_Force);
			}

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

