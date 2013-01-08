/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nTESTSERVER___filename_LocalizingTable_
#define __namespace_nTESTSERVER___filename_LocalizingTable_

#include "table_const_LocalizingTable.h"
// -------------------------------------------------
// enum�� �ڵ� ���ø� ����
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nTESTSERVER_LocalizingTable_ENUM(ENUM_TABLE)\
	ENUM_TABLE(ETextCategory,�������,nMech,nTESTSERVER)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// ���� enum������ �տ� e�� �ڵ����� �پ ����� 
	// -------------------------------------------------

	/* ������� */
	#define for_each_nTESTSERVER_ETextCategory_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ETC_Tutorial			,1,Ʃ�丮�󼳸�,nMech,nTESTSERVER,ETextCategory)\
		ENUM_FIELD(ETC_Quest			,2,����Ʈ����,nMech,nTESTSERVER,ETextCategory)\
		ENUM_FIELD(ETC_Npc			,3,npc��ȭ,nMech,nTESTSERVER,ETextCategory)\
		ENUM_FIELD(ETC_LoadScreen			,4,�ε�ȭ�� ����,nMech,nTESTSERVER,ETextCategory)\
		ENUM_FIELD(ETC_Menu			,5,���� �޴� ����,nMech,nTESTSERVER,ETextCategory)\


// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nTESTSERVER_LocalizingTable_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_LocalizingText,�������,nMech,nTESTSERVER)\
	STRUCT(Sys_LocalizingWord,�������,nMech,nTESTSERVER)\



	// ------------------------------------------------------------
	// Sys_LocalizingText �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD
	#define for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD(FIELD)\
		FIELD(id                     ,���̵�                ,uint16                       ,0 , uint16 , uint16 , i16)\
		FIELD(category               ,ī�װ�               ,ETextCategory                ,1 , ETextCategory , ETextCategory , e)\
		FIELD(name                   ,������                ,tname256_t                   ,2 , tcstr , tcstr , t256)\
		FIELD(name_kor               ,�ѱ۸�                ,wname256_t                   ,3 , wcstr , wcstr , w256)\
		FIELD(name_loc               ,���ö���¡��             ,wname256_t                   ,4 , wcstr , wcstr , w256)\

	#endif // for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_LocalizingText�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nTESTSERVER_Sys_LocalizingText_InheritedTable
	#define for_each_nTESTSERVER_Sys_LocalizingText_InheritedTable(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_LocalizingText_InheritedTable


	// ------------------------------------------------------------
	// Sys_LocalizingText�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD_Inherited
	#define for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_LocalizingText�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD_all_member
	#define for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD_all_member(FUNC)\
		for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_LocalizingWord �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD
	#define for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD(FIELD)\
		FIELD(id                     ,���̵�                ,uint16                       ,0 , uint16 , uint16 , i16)\
		FIELD(name                   ,������                ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(name_kor               ,�ѱ۸�                ,wname32_t                    ,2 , wcstr , wcstr , w32)\
		FIELD(name_loc               ,���ö���¡��             ,wname32_t                    ,3 , wcstr , wcstr , w32)\

	#endif // for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_LocalizingWord�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nTESTSERVER_Sys_LocalizingWord_InheritedTable
	#define for_each_nTESTSERVER_Sys_LocalizingWord_InheritedTable(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_LocalizingWord_InheritedTable


	// ------------------------------------------------------------
	// Sys_LocalizingWord�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD_Inherited
	#define for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_LocalizingWord�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD_all_member
	#define for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD_all_member(FUNC)\
		for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nTESTSERVER 
{

	enum ETextCategory // �������
	{
		eBEGIN_ETextCategory = 0,
		/* Ʃ�丮�󼳸� */
		eETC_Tutorial = 1, // Ʃ�丮�󼳸�
		/* ����Ʈ���� */
		eETC_Quest = 2, // ����Ʈ����
		/* npc��ȭ */
		eETC_Npc = 3, // npc��ȭ
		/* �ε�ȭ�� ���� */
		eETC_LoadScreen = 4, // �ε�ȭ�� ����
		/* ���� �޴� ���� */
		eETC_Menu = 5, // ���� �޴� ����
		eEND_ETextCategory
	}; // ETextCategory 





struct jEXCEL_LIB_API Sys_LocalizingText /* ������� */
{
	/*  id */
	uint16 m_id; // ���̵� min_max(,)
		typedef uint16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_id; }
	void SetPrimaryKey(primary_key_t id) { m_id = id; }
	/*  asfd */
	ETextCategory m_category; // ī�װ� min_max(,ETextCategory)
	/*  ������ */
	tname256_t m_name; // ������ min_max(,)
	/*  �ѱ۸� */
	wname256_t m_name_kor; // �ѱ۸� min_max(,)
	/*  ���ö���¡�� */
	wname256_t m_name_loc; // ���ö���¡�� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_LocalizingText
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  5 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_LocalizingText
		jEXCEL_TABLE_COMMON_CODE_H_Sys_LocalizingText();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_LocalizingText

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nTESTSERVER_Sys_LocalizingText_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_LocalizingText)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_LocalizingText
enum { eSTRUCT_SIZE_Sys_LocalizingText = sizeof(Sys_LocalizingText) };


struct CSV_Sys_LocalizingText : public nMech::nUtil::jCSV_File<Sys_LocalizingText>
{
	virtual ~CSV_Sys_LocalizingText(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_LocalizingText>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_LocalizingText g_Sys_LocalizingText;

struct jEXCEL_LIB_API Sys_LocalizingWord /* ������� */
{
	/*  id */
	uint16 m_id; // ���̵� min_max(,)
		typedef uint16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_id; }
	void SetPrimaryKey(primary_key_t id) { m_id = id; }
	/*  ������ */
	tname32_t m_name; // ������ min_max(,)
	/*  �ѱ۸� */
	wname32_t m_name_kor; // �ѱ۸� min_max(,)
	/*  ���ö���¡�� */
	wname32_t m_name_loc; // ���ö���¡�� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_LocalizingWord
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  4 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_LocalizingWord
		jEXCEL_TABLE_COMMON_CODE_H_Sys_LocalizingWord();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_LocalizingWord

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nTESTSERVER_Sys_LocalizingWord_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_LocalizingWord)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_LocalizingWord
enum { eSTRUCT_SIZE_Sys_LocalizingWord = sizeof(Sys_LocalizingWord) };


struct CSV_Sys_LocalizingWord : public nMech::nUtil::jCSV_File<Sys_LocalizingWord>
{
	virtual ~CSV_Sys_LocalizingWord(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_LocalizingWord>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_LocalizingWord g_Sys_LocalizingWord;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nTESTSERVER_LocalizingTable_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ETextCategory[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nTESTSERVER 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nTESTSERVER;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nTESTSERVER_LocalizingTable_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nTESTSERVER_LocalizingTable_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nTESTSERVER;
	for_each_nTESTSERVER_LocalizingTable_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nTESTSERVER___filename_LocalizingTable_
