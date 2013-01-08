/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_item_
#define __namespace_nEXCEL___filename_excel_baseball_table_item_

#include "table_const_excel_baseball_table_item.h"
// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_item_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_ItemEquip,�������,nMech,nEXCEL)\
	STRUCT(Sys_ItemStuff,�������,nMech,nEXCEL)\
	STRUCT(Sys__ItemBase,�������,nMech,nEXCEL)\
	STRUCT(Sys_ItemConsume,�������,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_ItemEquip �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD(FIELD)\
		FIELD(equip_category         ,��������ī�װ�          ,EItemCategoryEquipment       ,1 , EItemCategoryEquipment , EItemCategoryEquipment , e)\
		FIELD(sex_type               ,�����۳�������            ,EItemSexType                 ,2 , EItemSexType , EItemSexType , e)\
		FIELD(player_type            ,Ÿ����������             ,EPlayerType                  ,3 , EPlayerType , EPlayerType , e)\
		FIELD(item_batter_ability_type,Ÿ�� ������ ���� ����      ,EItemAbilityType             ,4 , EItemAbilityType , EItemAbilityType , e)\
		FIELD(item_pitcher_ability_type,���� ������ ���� ����     ,EItemAbilityType             ,5 , EItemAbilityType , EItemAbilityType , e)\

	#endif // for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_ItemEquip�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_ItemEquip_InheritedTable
	#define for_each_nEXCEL_Sys_ItemEquip_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_InheritedTable(FUNC)\
		FUNC(Sys__ItemBase)\

	#endif // for_each_nEXCEL_Sys_ItemEquip_InheritedTable


	// ------------------------------------------------------------
	// Sys_ItemEquip�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_ItemEquip�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_ItemStuff �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD(FIELD)\
		FIELD(upgradable_item_type   ,���׷��̵��ų���ִ¾���������    ,EItemUpgradeResult           ,1 , EItemUpgradeResult , EItemUpgradeResult , e)\

	#endif // for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_ItemStuff�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_ItemStuff_InheritedTable
	#define for_each_nEXCEL_Sys_ItemStuff_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_InheritedTable(FUNC)\
		FUNC(Sys__ItemBase)\

	#endif // for_each_nEXCEL_Sys_ItemStuff_InheritedTable


	// ------------------------------------------------------------
	// Sys_ItemStuff�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_ItemStuff�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys__ItemBase �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD
	#define for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,�����ĺ�ID             ,Sys__ItemBase_id_t           ,0 , Sys__ItemBase_id_t , uint16 , u16)\
		FIELD(name                   ,�̸�                 ,aname32_t                    ,1 , acstr , acstr , a32)\
		FIELD(category               ,��з�                ,EItemCategory                ,2 , EItemCategory , EItemCategory , e)\
		FIELD(upgrade_type           ,���׷��̵� ���� ����        ,bool                         ,3 , bool , bool , b)\
		FIELD(is_visual              ,�����                ,bool                         ,4 , bool , bool , b)\
		FIELD(help                   ,����                 ,aname256_t                   ,5 , acstr , acstr , a256)\
		FIELD(grade                  ,���                 ,EItemGradeType               ,6 , EItemGradeType , EItemGradeType , e)\
		FIELD(subgrade               ,���� ���              ,EItemSubGradeType            ,7 , EItemSubGradeType , EItemSubGradeType , e)\
		FIELD(player_level_min       ,��뷹��MIN            ,player_level_t               ,8 , int32 , int32 , i32)\
		FIELD(player_level_max       ,��뷹��MAX            ,player_level_t               ,9 , int32 , int32 , i32)\

	#endif // for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys__ItemBase�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys__ItemBase_InheritedTable
	#define for_each_nEXCEL_Sys__ItemBase_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys__ItemBase_InheritedTable


	// ------------------------------------------------------------
	// Sys__ItemBase�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys__ItemBase�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_ItemConsume �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD(FIELD)\
		FIELD(player_type            ,Ÿ����������             ,EPlayerType                  ,1 , EPlayerType , EPlayerType , e)\
		FIELD(consume_item_effect    ,����������ȿ��            ,EConsumeItemEffect           ,2 , EConsumeItemEffect , EConsumeItemEffect , e)\
		FIELD(Item_Ability_Type      ,�����ۿ��⽺��            ,EItemAbilityType             ,3 , EItemAbilityType , EItemAbilityType , e)\
		FIELD(consume_item_effect_value,����������ȿ����         ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(gameplay_effect_repeat ,���� �÷��̽� ����ȿ�� ����(Ƚ��) ,int16                       ,5 , int16 , int16 , i16)\
		FIELD(gameplay_effect_time   ,���� �÷��̽� ����ȿ�� ����(�ð�) ,int16                       ,6 , int16 , int16 , i16)\
		FIELD(consume_item_overlap   ,�ٸ������۰� �ߺ���� ����     ,bool                         ,7 , bool , bool , b)\
		FIELD(use_count              ,��� Ƚ��              ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(is_bonus               ,���ʽ��������            ,bool                         ,9 , bool , bool , b)\

	#endif // for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_ItemConsume�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_ItemConsume_InheritedTable
	#define for_each_nEXCEL_Sys_ItemConsume_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_InheritedTable(FUNC)\
		FUNC(Sys__ItemBase)\

	#endif // for_each_nEXCEL_Sys_ItemConsume_InheritedTable


	// ------------------------------------------------------------
	// Sys_ItemConsume�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_ItemConsume�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{



struct jEXCEL_LIB_API Sys__ItemBase /* ������� */
{
	Sys__ItemBase_id_t m_sid; // �����ĺ�ID min_max(,)
		typedef Sys__ItemBase_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_sid; }
	void SetPrimaryKey(primary_key_t id) { m_sid = id; }
	/*  �����̸� �����ؾ���. �� �����̸����� ��Ʈ�����̺��� �ѱ��̸��˻� */
	aname32_t m_name; // �̸� min_max(,)
	EItemCategory m_category; // ��з� min_max(,EItemCategory)
	/*  ���׷��̵尡 ���������� ���� */
	bool m_upgrade_type; // ���׷��̵� ���� ���� min_max(,)
	/*  ȭ�鿡 ���������� �Ⱥ��������� ���� */
	bool m_is_visual; // ����� min_max(,)
	aname256_t m_help; // ���� min_max(,)
	/*  ������ ���׷��̵� ��� */
	EItemGradeType m_grade; // ��� min_max(,EItemGradeType)
	/*  ������ ���� ���׷��̵� ��� */
	EItemSubGradeType m_subgrade; // ���� ��� min_max(,EItemSubGradeType)
	/*  ������ �� 110���� ���� */
	player_level_t m_player_level_min; // ��뷹��MIN min_max(,)
	/*  ������ �� 110���� ���� */
	player_level_t m_player_level_max; // ��뷹��MAX min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys__ItemBase
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  10 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys__ItemBase
		jEXCEL_TABLE_COMMON_CODE_H_Sys__ItemBase();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys__ItemBase

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys__ItemBase)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys__ItemBase
enum { eSTRUCT_SIZE_Sys__ItemBase = sizeof(Sys__ItemBase) };


struct CSV_Sys__ItemBase : public nMech::nUtil::jCSV_File<Sys__ItemBase>
{
	virtual ~CSV_Sys__ItemBase(){}
	jLIST_TYPEDEF_vector_typedef(Sys__ItemBase*,vector_grade);
	jLIST_TYPEDEF_map(EItemGradeType, vector_grade_t, m_INDEX_grade);
	void init_INDEX_grade()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys__ItemBase* p = at(i);
			m_INDEX_grade[p->Get_grade()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys__ItemBase>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_grade();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys__ItemBase g_Sys__ItemBase;

struct jEXCEL_LIB_API Sys_ItemEquip /* ������� */
	:Sys__ItemBase
{
	Sys__ItemBase* GetBase_Sys__ItemBase(){ return static_cast<Sys__ItemBase*>(this);}
	/*  ��������ī�װ� */
	EItemCategoryEquipment m_equip_category; // ��������ī�װ� min_max(,EItemCategoryEquipment)
	/*  �������� */
	EItemSexType m_sex_type; // �����۳������� min_max(,EItemSexType)
	/*  Ÿ���������� */
	EPlayerType m_player_type; // Ÿ���������� min_max(,EPlayerType)
	/*  Ÿ�� ������ ���� ���� */
	EItemAbilityType m_item_batter_ability_type; // Ÿ�� ������ ���� ���� min_max(,EItemAbilityType)
	/*  ���� ������ ���� ���� */
	EItemAbilityType m_item_pitcher_ability_type; // ���� ������ ���� ���� min_max(,EItemAbilityType)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_ItemEquip
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  5 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Sys__ItemBase::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_ItemEquip
		jEXCEL_TABLE_COMMON_CODE_H_Sys_ItemEquip();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_ItemEquip

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_ItemEquip)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_ItemEquip
enum { eSTRUCT_SIZE_Sys_ItemEquip = sizeof(Sys_ItemEquip) };


struct CSV_Sys_ItemEquip : public nMech::nUtil::jCSV_File<Sys_ItemEquip>
{
	virtual ~CSV_Sys_ItemEquip(){}
	jLIST_TYPEDEF_vector_typedef(Sys_ItemEquip*,vector_grade);
	jLIST_TYPEDEF_map(EItemGradeType, vector_grade_t, m_INDEX_grade);
	void init_INDEX_grade()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_ItemEquip* p = at(i);
			m_INDEX_grade[p->Get_grade()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_ItemEquip>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_grade();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_ItemEquip g_Sys_ItemEquip;

struct jEXCEL_LIB_API Sys_ItemStuff /* ������� */
	:Sys__ItemBase
{
	Sys__ItemBase* GetBase_Sys__ItemBase(){ return static_cast<Sys__ItemBase*>(this);}
	/*  ���׷��̵��ų���ִ¾��������� */
	EItemUpgradeResult m_upgradable_item_type; // ���׷��̵��ų���ִ¾��������� min_max(,EItemUpgradeResult)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_ItemStuff
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  1 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Sys__ItemBase::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_ItemStuff
		jEXCEL_TABLE_COMMON_CODE_H_Sys_ItemStuff();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_ItemStuff

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_ItemStuff)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_ItemStuff
enum { eSTRUCT_SIZE_Sys_ItemStuff = sizeof(Sys_ItemStuff) };


struct CSV_Sys_ItemStuff : public nMech::nUtil::jCSV_File<Sys_ItemStuff>
{
	virtual ~CSV_Sys_ItemStuff(){}
	jLIST_TYPEDEF_vector_typedef(Sys_ItemStuff*,vector_grade);
	jLIST_TYPEDEF_map(EItemGradeType, vector_grade_t, m_INDEX_grade);
	void init_INDEX_grade()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_ItemStuff* p = at(i);
			m_INDEX_grade[p->Get_grade()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_ItemStuff>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_grade();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_ItemStuff g_Sys_ItemStuff;

struct jEXCEL_LIB_API Sys_ItemConsume /* ������� */
	:Sys__ItemBase
{
	Sys__ItemBase* GetBase_Sys__ItemBase(){ return static_cast<Sys__ItemBase*>(this);}
	/*  Ÿ���������� */
	EPlayerType m_player_type; // Ÿ���������� min_max(,EPlayerType)
	/*  ���������� �Һ� �� ȿ�� ���� */
	EConsumeItemEffect m_consume_item_effect; // ����������ȿ�� min_max(,EConsumeItemEffect)
	/*  ���������ۿ��⽺�� */
	EItemAbilityType m_Item_Ability_Type; // �����ۿ��⽺�� min_max(,EItemAbilityType)
	/*  �� �ش� ������ ȿ���� ��(�������� ȿ�� ���� ���� �ٸ�-->) */
	int16 m_consume_item_effect_value; // ����������ȿ���� min_max(,)
	/*  ���� �÷��̽� ����ȿ�� ����(Ƚ��) */
	int16 m_gameplay_effect_repeat; // ���� �÷��̽� ����ȿ�� ����(Ƚ��) min_max(,)
	/*  ���� �÷��̽� ����ȿ�� ����(�ð�) */
	int16 m_gameplay_effect_time; // ���� �÷��̽� ����ȿ�� ����(�ð�) min_max(,)
	/*  �ٸ������۰� �ߺ���� ���� */
	bool m_consume_item_overlap; // �ٸ������۰� �ߺ���� ���� min_max(,)
	/*  ��� Ƚ�� */
	int16 m_use_count; // ��� Ƚ�� min_max(,)
	/*  ���ʽ�������� */
	bool m_is_bonus; // ���ʽ�������� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_ItemConsume
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  9 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Sys__ItemBase::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_ItemConsume
		jEXCEL_TABLE_COMMON_CODE_H_Sys_ItemConsume();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_ItemConsume

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_ItemConsume)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_ItemConsume
enum { eSTRUCT_SIZE_Sys_ItemConsume = sizeof(Sys_ItemConsume) };


struct CSV_Sys_ItemConsume : public nMech::nUtil::jCSV_File<Sys_ItemConsume>
{
	virtual ~CSV_Sys_ItemConsume(){}
	jLIST_TYPEDEF_vector_typedef(Sys_ItemConsume*,vector_grade);
	jLIST_TYPEDEF_map(EItemGradeType, vector_grade_t, m_INDEX_grade);
	void init_INDEX_grade()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_ItemConsume* p = at(i);
			m_INDEX_grade[p->Get_grade()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_ItemConsume>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_grade();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_ItemConsume g_Sys_ItemConsume;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_baseball_table_item_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_baseball_table_item_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_baseball_table_item_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_baseball_table_item_
