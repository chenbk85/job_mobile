/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_item_
#define __namespace_nEXCEL___filename_excel_baseball_table_item_

#include "table_const_excel_baseball_table_item.h"
// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_item_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_ItemEquip,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_ItemStuff,설명없음,nMech,nEXCEL)\
	STRUCT(Sys__ItemBase,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_ItemConsume,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_ItemEquip 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD(FIELD)\
		FIELD(equip_category         ,장비아이템카테고리          ,EItemCategoryEquipment       ,1 , EItemCategoryEquipment , EItemCategoryEquipment , e)\
		FIELD(sex_type               ,아이템남여구분            ,EItemSexType                 ,2 , EItemSexType , EItemSexType , e)\
		FIELD(player_type            ,타자투수구분             ,EPlayerType                  ,3 , EPlayerType , EPlayerType , e)\
		FIELD(item_batter_ability_type,타자 아이템 영향 스텟      ,EItemAbilityType             ,4 , EItemAbilityType , EItemAbilityType , e)\
		FIELD(item_pitcher_ability_type,투수 아이템 영향 스텟     ,EItemAbilityType             ,5 , EItemAbilityType , EItemAbilityType , e)\

	#endif // for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_ItemEquip가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_ItemEquip_InheritedTable
	#define for_each_nEXCEL_Sys_ItemEquip_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_InheritedTable(FUNC)\
		FUNC(Sys__ItemBase)\

	#endif // for_each_nEXCEL_Sys_ItemEquip_InheritedTable


	// ------------------------------------------------------------
	// Sys_ItemEquip가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_ItemEquip가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_ItemStuff 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD(FIELD)\
		FIELD(upgradable_item_type   ,업그레이드시킬수있는아이템종류    ,EItemUpgradeResult           ,1 , EItemUpgradeResult , EItemUpgradeResult , e)\

	#endif // for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_ItemStuff가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_ItemStuff_InheritedTable
	#define for_each_nEXCEL_Sys_ItemStuff_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_InheritedTable(FUNC)\
		FUNC(Sys__ItemBase)\

	#endif // for_each_nEXCEL_Sys_ItemStuff_InheritedTable


	// ------------------------------------------------------------
	// Sys_ItemStuff가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_ItemStuff가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys__ItemBase 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD
	#define for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,고유식별ID             ,Sys__ItemBase_id_t           ,0 , Sys__ItemBase_id_t , uint16 , u16)\
		FIELD(name                   ,이름                 ,aname32_t                    ,1 , acstr , acstr , a32)\
		FIELD(category               ,대분류                ,EItemCategory                ,2 , EItemCategory , EItemCategory , e)\
		FIELD(upgrade_type           ,업그레이드 가능 유뮤        ,bool                         ,3 , bool , bool , b)\
		FIELD(is_visual              ,비쥬얼                ,bool                         ,4 , bool , bool , b)\
		FIELD(help                   ,설명                 ,aname256_t                   ,5 , acstr , acstr , a256)\
		FIELD(grade                  ,등급                 ,EItemGradeType               ,6 , EItemGradeType , EItemGradeType , e)\
		FIELD(subgrade               ,서브 등급              ,EItemSubGradeType            ,7 , EItemSubGradeType , EItemSubGradeType , e)\
		FIELD(player_level_min       ,사용레벨MIN            ,player_level_t               ,8 , int32 , int32 , i32)\
		FIELD(player_level_max       ,사용레벨MAX            ,player_level_t               ,9 , int32 , int32 , i32)\

	#endif // for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys__ItemBase가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys__ItemBase_InheritedTable
	#define for_each_nEXCEL_Sys__ItemBase_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys__ItemBase_InheritedTable


	// ------------------------------------------------------------
	// Sys__ItemBase가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys__ItemBase가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_ItemConsume 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD(FIELD)\
		FIELD(player_type            ,타자투수구분             ,EPlayerType                  ,1 , EPlayerType , EPlayerType , e)\
		FIELD(consume_item_effect    ,컨슘아이템효과            ,EConsumeItemEffect           ,2 , EConsumeItemEffect , EConsumeItemEffect , e)\
		FIELD(Item_Ability_Type      ,아이템영향스텟            ,EItemAbilityType             ,3 , EItemAbilityType , EItemAbilityType , e)\
		FIELD(consume_item_effect_value,컨슘아이템효과값         ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(gameplay_effect_repeat ,게임 플레이시 지속효과 제한(횟수) ,int16                       ,5 , int16 , int16 , i16)\
		FIELD(gameplay_effect_time   ,게임 플레이시 지속효과 제한(시간) ,int16                       ,6 , int16 , int16 , i16)\
		FIELD(consume_item_overlap   ,다른아이템과 중복사용 여부     ,bool                         ,7 , bool , bool , b)\
		FIELD(use_count              ,사용 횟수              ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(is_bonus               ,보너스용아이템            ,bool                         ,9 , bool , bool , b)\

	#endif // for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_ItemConsume가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_ItemConsume_InheritedTable
	#define for_each_nEXCEL_Sys_ItemConsume_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_InheritedTable(FUNC)\
		FUNC(Sys__ItemBase)\

	#endif // for_each_nEXCEL_Sys_ItemConsume_InheritedTable


	// ------------------------------------------------------------
	// Sys_ItemConsume가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_ItemConsume가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{



struct jEXCEL_LIB_API Sys__ItemBase /* 설명없음 */
{
	Sys__ItemBase_id_t m_sid; // 고유식별ID min_max(,)
		typedef Sys__ItemBase_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_sid; }
	void SetPrimaryKey(primary_key_t id) { m_sid = id; }
	/*  영문이름 고유해야함. 이 영문이름으로 스트링테이블에서 한글이름검색 */
	aname32_t m_name; // 이름 min_max(,)
	EItemCategory m_category; // 대분류 min_max(,EItemCategory)
	/*  업그레이드가 가능한지의 여부 */
	bool m_upgrade_type; // 업그레이드 가능 유뮤 min_max(,)
	/*  화면에 보여지느냐 안보여지느냐 여부 */
	bool m_is_visual; // 비쥬얼 min_max(,)
	aname256_t m_help; // 설명 min_max(,)
	/*  아이템 업그레이드 등급 */
	EItemGradeType m_grade; // 등급 min_max(,EItemGradeType)
	/*  아이템 서브 업그레이드 등급 */
	EItemSubGradeType m_subgrade; // 서브 등급 min_max(,EItemSubGradeType)
	/*  현제는 약 110까지 가능 */
	player_level_t m_player_level_min; // 사용레벨MIN min_max(,)
	/*  현제는 약 110까지 가능 */
	player_level_t m_player_level_max; // 사용레벨MAX min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Sys_ItemEquip /* 설명없음 */
	:Sys__ItemBase
{
	Sys__ItemBase* GetBase_Sys__ItemBase(){ return static_cast<Sys__ItemBase*>(this);}
	/*  장비아이템카테고리 */
	EItemCategoryEquipment m_equip_category; // 장비아이템카테고리 min_max(,EItemCategoryEquipment)
	/*  남여구분 */
	EItemSexType m_sex_type; // 아이템남여구분 min_max(,EItemSexType)
	/*  타자투수구분 */
	EPlayerType m_player_type; // 타자투수구분 min_max(,EPlayerType)
	/*  타자 아이템 영향 스텟 */
	EItemAbilityType m_item_batter_ability_type; // 타자 아이템 영향 스텟 min_max(,EItemAbilityType)
	/*  투수 아이템 영향 스텟 */
	EItemAbilityType m_item_pitcher_ability_type; // 투수 아이템 영향 스텟 min_max(,EItemAbilityType)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Sys_ItemStuff /* 설명없음 */
	:Sys__ItemBase
{
	Sys__ItemBase* GetBase_Sys__ItemBase(){ return static_cast<Sys__ItemBase*>(this);}
	/*  업그레이드시킬수있는아이템종류 */
	EItemUpgradeResult m_upgradable_item_type; // 업그레이드시킬수있는아이템종류 min_max(,EItemUpgradeResult)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Sys_ItemConsume /* 설명없음 */
	:Sys__ItemBase
{
	Sys__ItemBase* GetBase_Sys__ItemBase(){ return static_cast<Sys__ItemBase*>(this);}
	/*  타자투수구분 */
	EPlayerType m_player_type; // 타자투수구분 min_max(,EPlayerType)
	/*  컨슘아이템 소비 시 효과 구분 */
	EConsumeItemEffect m_consume_item_effect; // 컨슘아이템효과 min_max(,EConsumeItemEffect)
	/*  컨슘아이템영향스텟 */
	EItemAbilityType m_Item_Ability_Type; // 아이템영향스텟 min_max(,EItemAbilityType)
	/*  각 해당 아이템 효과의 값(아이템의 효과 마다 값이 다름-->) */
	int16 m_consume_item_effect_value; // 컨슘아이템효과값 min_max(,)
	/*  게임 플레이시 지속효과 제한(횟수) */
	int16 m_gameplay_effect_repeat; // 게임 플레이시 지속효과 제한(횟수) min_max(,)
	/*  게임 플레이시 지속효과 제한(시간) */
	int16 m_gameplay_effect_time; // 게임 플레이시 지속효과 제한(시간) min_max(,)
	/*  다른아이템과 중복사용 여부 */
	bool m_consume_item_overlap; // 다른아이템과 중복사용 여부 min_max(,)
	/*  사용 횟수 */
	int16 m_use_count; // 사용 횟수 min_max(,)
	/*  보너스용아이템 */
	bool m_is_bonus; // 보너스용아이템 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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
