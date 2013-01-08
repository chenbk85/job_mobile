/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_client_
#define __namespace_nEXCEL___filename_excel_baseball_table_client_

#include "table_const_excel_baseball_table_client.h"
// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_client_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Client_Graphic_File_Name,�������,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Client_Graphic_File_Name �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,������ȣ               ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(equip_PlayerBodyType   ,������ ���� ĳ���� Ÿ��      ,EPlayerBodyType              ,1 , EPlayerBodyType , EPlayerBodyType , e)\
		FIELD(Sys_ItemEquip_Sid      ,��������ī�װ��� sid     ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(file_name_texture      ,�ؽ�ó ���� �̸�          ,aname32_t                    ,3 , acstr , acstr , a32)\
		FIELD(file_name_object       ,������Ʈ ���� �̸�         ,aname32_t                    ,4 , acstr , acstr , a32)\
		FIELD(file_name_icon         ,������ ���� �̸�          ,aname32_t                    ,5 , acstr , acstr , a32)\
		FIELD(equip_animation_item   ,�ִϸ��̼� ������          ,aname32_t                    ,6 , acstr , acstr , a32)\

	#endif // for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Client_Graphic_File_Name�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Client_Graphic_File_Name_InheritedTable
	#define for_each_nEXCEL_Sys_Client_Graphic_File_Name_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Client_Graphic_File_Name_InheritedTable


	// ------------------------------------------------------------
	// Sys_Client_Graphic_File_Name�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Client_Graphic_File_Name�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{



struct jEXCEL_LIB_API Sys_Client_Graphic_File_Name /* ������� */
{
	/*  ������ȣ */
	int16 m_sid; // ������ȣ min_max(,)
	/*  ������ ���� ĳ���� Ÿ�� */
	EPlayerBodyType m_equip_PlayerBodyType; // ������ ���� ĳ���� Ÿ�� min_max(,EPlayerBodyType)
	/*  Sys_ItemEquip�� sid */
	int16 m_Sys_ItemEquip_Sid; // ��������ī�װ��� sid min_max(,)
	/*  �ؽ�ó ���� ���� */
	aname32_t m_file_name_texture; // �ؽ�ó ���� �̸� min_max(,)
	/*  ������Ʈ ���ϳ��� */
	aname32_t m_file_name_object; // ������Ʈ ���� �̸� min_max(,)
	/*  ������ ���� ���� */
	aname32_t m_file_name_icon; // ������ ���� �̸� min_max(,)
	/*  �ִϸ��̼� ������ */
	aname32_t m_equip_animation_item; // �ִϸ��̼� ������ min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_Client_Graphic_File_Name
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  7 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Client_Graphic_File_Name
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Client_Graphic_File_Name();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Client_Graphic_File_Name

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Client_Graphic_File_Name)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Client_Graphic_File_Name
enum { eSTRUCT_SIZE_Sys_Client_Graphic_File_Name = sizeof(Sys_Client_Graphic_File_Name) };


struct CSV_Sys_Client_Graphic_File_Name : public nMech::nUtil::jCSV_File<Sys_Client_Graphic_File_Name>
{
	virtual ~CSV_Sys_Client_Graphic_File_Name(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Client_Graphic_File_Name>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Client_Graphic_File_Name g_Sys_Client_Graphic_File_Name;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_baseball_table_client_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_baseball_table_client_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_baseball_table_client_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_baseball_table_client_
