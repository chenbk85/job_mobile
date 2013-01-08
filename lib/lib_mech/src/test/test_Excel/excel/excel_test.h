/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_test_
#define __namespace_nEXCEL___filename_excel_test_

#include "table_const_excel_test.h"
// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nEXCEL_excel_test_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys__T_Base,����type ���̺��� base ���̺��̴�. ��� ����type ���̺��� �� ���̺��� ��ӹ޴´�,nMech,nEXCEL)\
	STRUCT(Sys_T_Test,�׽�Ʈ��,nMech,nEXCEL)\
	STRUCT(Sys_T_Test2,�׽�Ʈ��2,nMech,nEXCEL)\
	STRUCT(Sys_T_Test3,�׽�Ʈ��2,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys__T_Base �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD
	#define for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD(FIELD)\
		FIELD(level                  ,����                 ,Sys__T_Base_id_t             ,0 , Sys__T_Base_id_t , uint16 , u16)\
		FIELD(base_type              ,�ǹ�Ÿ��               ,EBuildType_test              ,1 , EBuildType_test , EBuildType_test , e)\
		FIELD(name                   ,�ǹ����ҽ���             ,tname32_t                    ,2 , tcstr , tcstr , t32)\
		FIELD(upgradetime            ,���׷��̵� �ð�           ,uint32                       ,3 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,���� ���              ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(stone_num              ,�� ���               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(iron_num               ,ö ���               ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(silk_num               ,��� ���              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(population_num         ,�α� ���              ,int16                        ,8 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys__T_Base�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys__T_Base_InheritedTable
	#define for_each_nEXCEL_Sys__T_Base_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys__T_Base_InheritedTable


	// ------------------------------------------------------------
	// Sys__T_Base�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys__T_Base�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Test �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD(FIELD)\
		FIELD(maxbuild               ,111�ִ� ������          ,int16                        ,1 , int16 , int16 , i16)\
		FIELD(downlevel              ,111�ٿ�׷��̵巹��        ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(populationreturn       ,111�α� ��ȯ���         ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(test                   ,111test            ,EBuildType_test              ,4 , EBuildType_test , EBuildType_test , e)\
		FIELD(getgold                ,111¡��              ,int16                        ,5 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Test�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Test_InheritedTable
	#define for_each_nEXCEL_Sys_T_Test_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys__T_Base_InheritedTable(FUNC)\
		FUNC(Sys__T_Base)\

	#endif // for_each_nEXCEL_Sys_T_Test_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Test�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Test�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Test2 �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD(FIELD)\
		FIELD(maxbuild2              ,222�ִ� ������          ,int16                        ,1 , int16 , int16 , i16)\
		FIELD(downlevel2             ,2�ٿ�׷��̵巹��          ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(treereturn2            ,222���� ��ȯ���         ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stonereturn2           ,222�� ��ȯ���          ,EOutput_test                 ,4 , EOutput_test , EOutput_test , e)\
		FIELD(populationreturn2      ,222�α� ��ȯ���         ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(test2                  ,222test            ,EBuildType_test              ,6 , EBuildType_test , EBuildType_test , e)\
		FIELD(getgold2               ,222¡��              ,int16                        ,7 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Test2�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Test2_InheritedTable
	#define for_each_nEXCEL_Sys_T_Test2_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys_T_Test_InheritedTable(FUNC)\
		FUNC(Sys_T_Test)\

	#endif // for_each_nEXCEL_Sys_T_Test2_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Test2�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Test2�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Test3 �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD(FIELD)\
		FIELD(maxbuild2              ,333�ִ� ������          ,int16                        ,1 , int16 , int16 , i16)\
		FIELD(stonereturn2           ,333�� ��ȯ���          ,EOutput_test                 ,2 , EOutput_test , EOutput_test , e)\
		FIELD(populationreturn2      ,333�α� ��ȯ���         ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(test2                  ,333test            ,EBuildType_test              ,4 , EBuildType_test , EBuildType_test , e)\
		FIELD(getgold2               ,333¡��              ,int16                        ,5 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Test3�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Test3_InheritedTable
	#define for_each_nEXCEL_Sys_T_Test3_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys__T_Base_InheritedTable(FUNC)\
		FUNC(Sys__T_Base)\

	#endif // for_each_nEXCEL_Sys_T_Test3_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Test3�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Test3�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{



struct jEXCEL_LIB_API Sys__T_Base /* ����type ���̺��� base ���̺��̴�. ��� ����type ���̺��� �� ���̺��� ��ӹ޴´� */
{
	/*  �ǹ� ���� ( �ش� ������ �ǹ� sid �ĺ��ڷε� ���δ�) */
	Sys__T_Base_id_t m_level; // ���� min_max(,)
		typedef Sys__T_Base_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_level; }
	void SetPrimaryKey(primary_key_t id) { m_level = id; }
	/*  Sys_T_BaseObj����� �޴� ���̺��� �ǹ� ���� */
	EBuildType_test m_base_type; // �ǹ�Ÿ�� min_max(,EBuildType_test)
	/*  �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� */
	tname32_t m_name; // �ǹ����ҽ��� min_max(,)
	/*  ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� */
	uint32 m_upgradetime; // ���׷��̵� �ð� min_max(,)
	/*  �Ǽ��� �ʿ��� ���� ��� */
	int16 m_tree_num; // ���� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �� ��� */
	int16 m_stone_num; // �� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ö ��� */
	int16 m_iron_num; // ö ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ��� ��� */
	int16 m_silk_num; // ��� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �α� ��� */
	int16 m_population_num; // �α� ��� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys__T_Base
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  9 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys__T_Base
		jEXCEL_TABLE_COMMON_CODE_H_Sys__T_Base();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys__T_Base

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys__T_Base)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys__T_Base
enum { eSTRUCT_SIZE_Sys__T_Base = sizeof(Sys__T_Base) };


struct CSV_Sys__T_Base : public nMech::nUtil::jCSV_File<Sys__T_Base>
{
	virtual ~CSV_Sys__T_Base(){}
	jLIST_TYPEDEF_vector_typedef(Sys__T_Base*,vector_base_type);
	jLIST_TYPEDEF_map(EBuildType_test, vector_base_type_t, m_INDEX_base_type);
	void init_INDEX_base_type()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys__T_Base* p = at(i);
			m_INDEX_base_type[p->Get_base_type()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys__T_Base>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_base_type();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys__T_Base g_Sys__T_Base;

struct jEXCEL_LIB_API Sys_T_Test /* �׽�Ʈ�� */
	:Sys__T_Base
{
	Sys__T_Base* GetBase_Sys__T_Base(){ return static_cast<Sys__T_Base*>(this);}
	/*  �� ������ �ִ� ���� ������ �ǹ� �� */
	int16 m_maxbuild; // 111�ִ� ������ min_max(,)
	/*  �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ */
	int16 m_downlevel; // 111�ٿ�׷��̵巹�� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. */
	int16 m_populationreturn; // 111�α� ��ȯ��� min_max(,)
	EBuildType_test m_test; // 111test min_max(,EBuildType_test)
	/*  ¡�� ��� */
	int16 m_getgold; // 111¡�� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_T_Test
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  5 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Sys__T_Base::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Test)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Test
enum { eSTRUCT_SIZE_Sys_T_Test = sizeof(Sys_T_Test) };


struct CSV_Sys_T_Test : public nMech::nUtil::jCSV_File<Sys_T_Test>
{
	virtual ~CSV_Sys_T_Test(){}
	jLIST_TYPEDEF_vector_typedef(Sys_T_Test*,vector_base_type);
	jLIST_TYPEDEF_map(EBuildType_test, vector_base_type_t, m_INDEX_base_type);
	void init_INDEX_base_type()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_T_Test* p = at(i);
			m_INDEX_base_type[p->Get_base_type()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Test>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_base_type();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Test g_Sys_T_Test;

struct jEXCEL_LIB_API Sys_T_Test2 /* �׽�Ʈ��2 */
	:Sys_T_Test
{
	Sys_T_Test* GetBase_Sys_T_Test(){ return static_cast<Sys_T_Test*>(this);}
	/*  �� ������ �ִ� ���� ������ �ǹ� �� */
	int16 m_maxbuild2; // 222�ִ� ������ min_max(,)
	/*  �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ */
	int16 m_downlevel2; // 2�ٿ�׷��̵巹�� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) */
	int16 m_treereturn2; // 222���� ��ȯ��� min_max(,)
	EOutput_test m_stonereturn2; // 222�� ��ȯ��� min_max(,EOutput_test)
	/*  �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. */
	int16 m_populationreturn2; // 222�α� ��ȯ��� min_max(,)
	EBuildType_test m_test2; // 222test min_max(,EBuildType_test)
	/*  ¡�� ��� */
	int16 m_getgold2; // 222¡�� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_T_Test2
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  7 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Sys_T_Test::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test2
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test2();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test2

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Test2)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Test2
enum { eSTRUCT_SIZE_Sys_T_Test2 = sizeof(Sys_T_Test2) };


struct CSV_Sys_T_Test2 : public nMech::nUtil::jCSV_File<Sys_T_Test2>
{
	virtual ~CSV_Sys_T_Test2(){}
	jLIST_TYPEDEF_vector_typedef(Sys_T_Test2*,vector_base_type);
	jLIST_TYPEDEF_map(EBuildType_test, vector_base_type_t, m_INDEX_base_type);
	void init_INDEX_base_type()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_T_Test2* p = at(i);
			m_INDEX_base_type[p->Get_base_type()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Test2>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_base_type();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Test2 g_Sys_T_Test2;

struct jEXCEL_LIB_API Sys_T_Test3 /* �׽�Ʈ��2 */
	:Sys__T_Base
{
	Sys__T_Base* GetBase_Sys__T_Base(){ return static_cast<Sys__T_Base*>(this);}
	/*  �� ������ �ִ� ���� ������ �ǹ� �� */
	int16 m_maxbuild2; // 333�ִ� ������ min_max(,)
	EOutput_test m_stonereturn2; // 333�� ��ȯ��� min_max(,EOutput_test)
	/*  �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. */
	int16 m_populationreturn2; // 333�α� ��ȯ��� min_max(,)
	EBuildType_test m_test2; // 333test min_max(,EBuildType_test)
	/*  ¡�� ��� */
	int16 m_getgold2; // 333¡�� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_T_Test3
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  5 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Sys__T_Base::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test3
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test3();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test3

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Test3)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Test3
enum { eSTRUCT_SIZE_Sys_T_Test3 = sizeof(Sys_T_Test3) };


struct CSV_Sys_T_Test3 : public nMech::nUtil::jCSV_File<Sys_T_Test3>
{
	virtual ~CSV_Sys_T_Test3(){}
	jLIST_TYPEDEF_vector_typedef(Sys_T_Test3*,vector_base_type);
	jLIST_TYPEDEF_map(EBuildType_test, vector_base_type_t, m_INDEX_base_type);
	void init_INDEX_base_type()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_T_Test3* p = at(i);
			m_INDEX_base_type[p->Get_base_type()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Test3>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_base_type();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Test3 g_Sys_T_Test3;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_test_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_test_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_test_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_test_
