/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_baseball_table_client.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_baseball_table_client_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_baseball_table_client_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_baseball_table_client_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE

namespace nMech {
	namespace nEXCEL {


#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Client_Graphic_File_Name
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Client_Graphic_File_Name();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Client_Graphic_File_Name


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	int16 Sys_Client_Graphic_File_Name::Get_sid()	{		return (int16)m_sid;}
	void Sys_Client_Graphic_File_Name::Set_sid(int16 v)
	{
		m_sid=v;
	}

	EPlayerBodyType Sys_Client_Graphic_File_Name::Get_equip_PlayerBodyType()	{		return (EPlayerBodyType)m_equip_PlayerBodyType;}
	void Sys_Client_Graphic_File_Name::Set_equip_PlayerBodyType(EPlayerBodyType v)
	{
		if(v<eBEGIN_EPlayerBodyType || v>=eEND_EPlayerBodyType)
		{
			jERROR(_T("Sys_Client_Graphic_File_Name::Set_equip_PlayerBodyType(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerBodyType,eEND_EPlayerBodyType,v);
		}
		m_equip_PlayerBodyType=v;
	}

	int16 Sys_Client_Graphic_File_Name::Get_Sys_ItemEquip_Sid()	{		return (int16)m_Sys_ItemEquip_Sid;}
	void Sys_Client_Graphic_File_Name::Set_Sys_ItemEquip_Sid(int16 v)
	{
		m_Sys_ItemEquip_Sid=v;
	}

	acstr Sys_Client_Graphic_File_Name::Get_file_name_texture()	{		return (acstr)m_file_name_texture;}
	void Sys_Client_Graphic_File_Name::Set_file_name_texture(acstr v)
	{
		if(!v){ throw _T("Sys_Client_Graphic_File_Name::Set_file_name_texture( val = NULL )");}
		nExcelUtil::jSetter(m_file_name_texture , v, 32);
	}

	acstr Sys_Client_Graphic_File_Name::Get_file_name_object()	{		return (acstr)m_file_name_object;}
	void Sys_Client_Graphic_File_Name::Set_file_name_object(acstr v)
	{
		if(!v){ throw _T("Sys_Client_Graphic_File_Name::Set_file_name_object( val = NULL )");}
		nExcelUtil::jSetter(m_file_name_object , v, 32);
	}

	acstr Sys_Client_Graphic_File_Name::Get_file_name_icon()	{		return (acstr)m_file_name_icon;}
	void Sys_Client_Graphic_File_Name::Set_file_name_icon(acstr v)
	{
		if(!v){ throw _T("Sys_Client_Graphic_File_Name::Set_file_name_icon( val = NULL )");}
		nExcelUtil::jSetter(m_file_name_icon , v, 32);
	}

	acstr Sys_Client_Graphic_File_Name::Get_equip_animation_item()	{		return (acstr)m_equip_animation_item;}
	void Sys_Client_Graphic_File_Name::Set_equip_animation_item(acstr v)
	{
		if(!v){ throw _T("Sys_Client_Graphic_File_Name::Set_equip_animation_item( val = NULL )");}
		nExcelUtil::jSetter(m_equip_animation_item , v, 32);
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_baseball_table_client_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_Client_Graphic_File_Name g_Sys_Client_Graphic_File_Name;


tcstr Sys_Client_Graphic_File_Name::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_sid(FromString(out[index++],m_sid) );
	Set_equip_PlayerBodyType(FromString(out[index++],m_equip_PlayerBodyType) );
	Set_Sys_ItemEquip_Sid(FromString(out[index++],m_Sys_ItemEquip_Sid) );
	Set_file_name_texture(nExcelUtil_StringConverter(out[index++]).getA());
	Set_file_name_object(nExcelUtil_StringConverter(out[index++]).getA());
	Set_file_name_icon(nExcelUtil_StringConverter(out[index++]).getA());
	Set_equip_animation_item(nExcelUtil_StringConverter(out[index++]).getA());
	return szKEY;
}

void Sys_Client_Graphic_File_Name::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Client_Graphic_File_Name>);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_baseball_table_client)
		{
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Client_Graphic_File_Name>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Client_Graphic_File_Name*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Client_Graphic_File_Name*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Client_Graphic_File_Name*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Client_Graphic_File_Name)
			for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Client_Graphic_File_Name)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Client_Graphic_File_Name>* p = &g_Sys_Client_Graphic_File_Name;
				jSQ_g_var(p , g_Sys_Client_Graphic_File_Name);
			}

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

