/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nTESTSERVER___filename_ClientText_
#define __namespace_nTESTSERVER___filename_ClientText_

#include "table_const_ClientText.h"
// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nTESTSERVER_ClientText_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_ClientText,�������,nMech,nTESTSERVER)\



	// ------------------------------------------------------------
	// Sys_ClientText �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_ClientText_STRUCT_FIELD
	#define for_each_nTESTSERVER_Sys_ClientText_STRUCT_FIELD(FIELD)\
		FIELD(id                     ,��ȣ                 ,uint16                       ,0 , uint16 , uint16 , i16)\
		FIELD(eng_name               ,�̸�                 ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(description            ,����                 ,tname128_t                   ,2 , tcstr , tcstr , t128)\

	#endif // for_each_nTESTSERVER_Sys_ClientText_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_ClientText�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nTESTSERVER_Sys_ClientText_InheritedTable
	#define for_each_nTESTSERVER_Sys_ClientText_InheritedTable(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_ClientText_InheritedTable


	// ------------------------------------------------------------
	// Sys_ClientText�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_ClientText_STRUCT_FIELD_Inherited
	#define for_each_nTESTSERVER_Sys_ClientText_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_ClientText_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_ClientText�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_ClientText_STRUCT_FIELD_all_member
	#define for_each_nTESTSERVER_Sys_ClientText_STRUCT_FIELD_all_member(FUNC)\
		for_each_nTESTSERVER_Sys_ClientText_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nTESTSERVER_Sys_ClientText_STRUCT_FIELD(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_ClientText_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nTESTSERVER 
{



struct jEXCEL_LIB_API Sys_ClientText /* ������� */
{
	uint16 m_id; // ��ȣ min_max(,)
		typedef uint16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_id; }
	void SetPrimaryKey(primary_key_t id) { m_id = id; }
	tname32_t m_eng_name; // �̸� min_max(,)
	tname128_t m_description; // ���� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_ClientText
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nTESTSERVER_Sys_ClientText_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  3 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_ClientText
		jEXCEL_TABLE_COMMON_CODE_H_Sys_ClientText();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_ClientText

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nTESTSERVER_Sys_ClientText_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_ClientText)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_ClientText
enum { eSTRUCT_SIZE_Sys_ClientText = sizeof(Sys_ClientText) };


struct CSV_Sys_ClientText : public nMech::nUtil::jCSV_File<Sys_ClientText>
{
	virtual ~CSV_Sys_ClientText(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_ClientText>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_ClientText g_Sys_ClientText;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nTESTSERVER_ClientText_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nTESTSERVER 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nTESTSERVER;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nTESTSERVER_ClientText_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nTESTSERVER;
	for_each_nTESTSERVER_ClientText_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nTESTSERVER___filename_ClientText_
