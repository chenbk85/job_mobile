/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_shop_
#define __namespace_nEXCEL___filename_excel_baseball_table_shop_

#include "table_const_excel_baseball_table_shop.h"
// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_shop_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_MainItemAbility,�������,nMech,nEXCEL)\
	STRUCT(Sys_Package,�������,nMech,nEXCEL)\
	STRUCT(Sys_Shop,�������,nMech,nEXCEL)\
	STRUCT(Sys_SubItemAbility,�������,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_MainItemAbility �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,������ȣ               ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(equip_category         ,��������ī�װ�          ,EItemCategoryEquipment       ,1 , EItemCategoryEquipment , EItemCategoryEquipment , e)\
		FIELD(grade                  ,���                 ,EItemGradeType               ,2 , EItemGradeType , EItemGradeType , e)\
		FIELD(subgrade               ,���� ���              ,EItemSubGradeType            ,3 , EItemSubGradeType , EItemSubGradeType , e)\
		FIELD(mainitem_first_equip_level,���������� ���� ����     ,float                        ,4 , float , float , f)\
		FIELD(mainitem_possible_upgrade_level,�����۰�ȭ ���� ���� ,float                       ,5 , float , float , f)\
		FIELD(mainitem_need_time     ,�����۰�ȭ �ʿ� �ð�        ,float                        ,6 , float , float , f)\
		FIELD(mainitem_basic_value   ,�����۱⺻�ɷ�ġ           ,float                        ,7 , float , float , f)\
		FIELD(mainitem_equip_level   ,�ش��������������          ,float                        ,8 , float , float , f)\
		FIELD(value_min              ,��ȭ���ּ������ɷ�ġ         ,float                        ,9 , float , float , f)\
		FIELD(value_max              ,��ȭ���ִ������ɷ�ġ         ,float                        ,10 , float , float , f)\
		FIELD(player_type            ,Ÿ����������             ,EPlayerType                  ,11 , EPlayerType , EPlayerType , e)\
		FIELD(mainitem_upgrade_need_money,�ʿ���ӸӴ�         ,int64                        ,12 , int64 , int64 , i64)\

	#endif // for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_MainItemAbility�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_MainItemAbility_InheritedTable
	#define for_each_nEXCEL_Sys_MainItemAbility_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_MainItemAbility_InheritedTable


	// ------------------------------------------------------------
	// Sys_MainItemAbility�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_MainItemAbility�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Package �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Package_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Package_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,sid                ,Sys_Package_id_t             ,0 , Sys_Package_id_t , uint16 , u16)\
		FIELD(name                   ,name               ,aname32_t                    ,1 , acstr , acstr , a32)\
		FIELD(price_type             ,����Ÿ��               ,EItemPriceType               ,2 , EItemPriceType , EItemPriceType , e)\
		FIELD(price_money            ,�ʿ���ӸӴ�             ,int32                        ,3 , int32 , int32 , i32)\
		FIELD(price_cash             ,�ʿ丮��ĳ��             ,int32                        ,4 , int32 , int32 , i32)\
		FIELD(equip_items1           ,�����ۺ��׷��̵����1 Ÿ��     ,Sys_ItemEquip_ptr_vec        , 5 ,Sys_ItemEquip_ptr_vec_ref , Sys_ItemEquip_ptr_vec_ref , ptr_vec)\
		FIELD(consum_items1          ,�����ۺ��׷��̵����2 Ÿ��     ,Sys_ItemConsume_ptr_vec      , 6 ,Sys_ItemConsume_ptr_vec_ref , Sys_ItemConsume_ptr_vec_ref , ptr_vec)\
		FIELD(equip_items2           ,�����ۺ��׷��̵����1 ����     ,Sys_ItemEquip_ptr_vec        , 7 ,Sys_ItemEquip_ptr_vec_ref , Sys_ItemEquip_ptr_vec_ref , ptr_vec)\
		FIELD(consum_items2          ,�����ۺ��׷��̵����2 ����     ,Sys_ItemConsume_ptr_vec      , 8 ,Sys_ItemConsume_ptr_vec_ref , Sys_ItemConsume_ptr_vec_ref , ptr_vec)\
		FIELD(equip_items3           ,�����ۺ��׷��̵����1 ����Ÿ��   ,Sys_ItemEquip_ptr_vec        , 9 ,Sys_ItemEquip_ptr_vec_ref , Sys_ItemEquip_ptr_vec_ref , ptr_vec)\
		FIELD(consum_items3          ,�����ۺ��׷��̵����2 ����Ÿ��   ,Sys_ItemConsume_ptr_vec      , 10 ,Sys_ItemConsume_ptr_vec_ref , Sys_ItemConsume_ptr_vec_ref , ptr_vec)\
		FIELD(equip_items4           ,�����ۺ��׷��̵����1 ��������   ,Sys_ItemEquip_ptr_vec        , 11 ,Sys_ItemEquip_ptr_vec_ref , Sys_ItemEquip_ptr_vec_ref , ptr_vec)\
		FIELD(consum_items4          ,�����ۺ��׷��̵����2 ��������   ,Sys_ItemConsume_ptr_vec      , 12 ,Sys_ItemConsume_ptr_vec_ref , Sys_ItemConsume_ptr_vec_ref , ptr_vec)\
		FIELD(gift_type1             ,��������1              ,EGiftType                    ,13 , EGiftType , EGiftType , e)\
		FIELD(gift_type1_value       ,����1                ,int64                        ,14 , int64 , int64 , i64)\
		FIELD(gift_type2             ,��������2              ,EGiftType                    ,15 , EGiftType , EGiftType , e)\
		FIELD(gift_type2_value       ,����2                ,int64                        ,16 , int64 , int64 , i64)\
		FIELD(gift_type3             ,��������3              ,EGiftType                    ,17 , EGiftType , EGiftType , e)\
		FIELD(gift_type3_value       ,����3                ,int64                        ,18 , int64 , int64 , i64)\
		FIELD(gift_type4             ,��������4              ,EGiftType                    ,19 , EGiftType , EGiftType , e)\
		FIELD(gift_type4_value       ,����4                ,int64                        ,20 , int64 , int64 , i64)\
		FIELD(gift_type5             ,��������5              ,EGiftType                    ,21 , EGiftType , EGiftType , e)\
		FIELD(gift_type5_value       ,����5                ,int64                        ,22 , int64 , int64 , i64)\
		FIELD(gift_type6             ,��������6              ,EGiftType                    ,23 , EGiftType , EGiftType , e)\
		FIELD(gift_type6_value       ,����6                ,int64                        ,24 , int64 , int64 , i64)\
		FIELD(gift_type7             ,��������7              ,EGiftType                    ,25 , EGiftType , EGiftType , e)\
		FIELD(gift_type7_value       ,����7                ,int64                        ,26 , int64 , int64 , i64)\
		FIELD(gift_type8             ,��������8              ,EGiftType                    ,27 , EGiftType , EGiftType , e)\
		FIELD(gift_type8_value       ,����8                ,int64                        ,28 , int64 , int64 , i64)\
		FIELD(gift_type9             ,��������9              ,EGiftType                    ,29 , EGiftType , EGiftType , e)\
		FIELD(gift_type9_value       ,����9                ,int64                        ,30 , int64 , int64 , i64)\
		FIELD(gift_type10            ,��������10             ,EGiftType                    ,31 , EGiftType , EGiftType , e)\
		FIELD(gift_type10_value      ,����10               ,int64                        ,32 , int64 , int64 , i64)\

	#endif // for_each_nEXCEL_Sys_Package_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Package�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Package_InheritedTable
	#define for_each_nEXCEL_Sys_Package_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Package_InheritedTable


	// ------------------------------------------------------------
	// Sys_Package�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Package_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Package_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Package_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Package�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Package_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Package_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Package_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Package_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Package_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Shop �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Shop_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Shop_STRUCT_FIELD(FIELD)\
		FIELD(shop_id                ,shop_id            ,Sys_Shop_id_t                ,0 , Sys_Shop_id_t , uint16 , u16)\
		FIELD(name                   ,name               ,aname32_t                    ,1 , acstr , acstr , a32)\
		FIELD(item_type              ,item_type          ,EShopItemType                ,2 , EShopItemType , EShopItemType , e)\
		FIELD(item_index             ,item_index         ,int32                        ,3 , int32 , int32 , i32)\
		FIELD(is_new                 ,is_new             ,bool                         ,4 , bool , bool , b)\
		FIELD(is_best                ,is_best            ,bool                         ,5 , bool , bool , b)\
		FIELD(is_hot                 ,is_hot             ,bool                         ,6 , bool , bool , b)\
		FIELD(shop_batter_section    ,shop_batter_section ,EShopBatterSection          ,7 , EShopBatterSection , EShopBatterSection , e)\
		FIELD(shop_pitcher_section   ,shop_pitcher_section ,EShopPitcherSection        ,8 , EShopPitcherSection , EShopPitcherSection , e)\
		FIELD(shop_consume_section   ,shop_consume_section ,EShopConsumeSection        ,9 , EShopConsumeSection , EShopConsumeSection , e)\
		FIELD(sell_start_date        ,�Ǹ� ���� �Ͻ�           ,SYSTEMTIME                   ,10 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(sell_end_date          ,�Ǹ� ���� �Ͻ�           ,SYSTEMTIME                   ,11 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(price_money            ,�ʿ���ӸӴ�             ,int32                        ,12 , int32 , int32 , i32)\
		FIELD(price_cash             ,�ʿ丮��ĳ��             ,int32                        ,13 , int32 , int32 , i32)\
		FIELD(price_type             ,����Ÿ��               ,EItemPriceType               ,14 , EItemPriceType , EItemPriceType , e)\
		FIELD(sell_status            ,�ǸŻ���               ,EItemSellStatus              ,15 , EItemSellStatus , EItemSellStatus , e)\

	#endif // for_each_nEXCEL_Sys_Shop_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Shop�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Shop_InheritedTable
	#define for_each_nEXCEL_Sys_Shop_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Shop_InheritedTable


	// ------------------------------------------------------------
	// Sys_Shop�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Shop�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Shop_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_SubItemAbility �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,������ȣ               ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(equip_category         ,��������ī�װ�          ,EItemCategoryEquipment       ,1 , EItemCategoryEquipment , EItemCategoryEquipment , e)\
		FIELD(grade                  ,���                 ,EItemGradeType               ,2 , EItemGradeType , EItemGradeType , e)\
		FIELD(subitem_first_equip_level,���������� ���� ����      ,int8                         ,3 , int8 , int8 , i8)\
		FIELD(subitem_better_ability ,������Ÿ�ڴɷ�ġ           ,int8                         ,4 , int8 , int8 , i8)\
		FIELD(subitem_pitcher_ability,�����������ɷ�ġ           ,float                        ,5 , float , float , f)\

	#endif // for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_SubItemAbility�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_SubItemAbility_InheritedTable
	#define for_each_nEXCEL_Sys_SubItemAbility_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_SubItemAbility_InheritedTable


	// ------------------------------------------------------------
	// Sys_SubItemAbility�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_SubItemAbility�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	struct Sys_ItemEquip;
	typedef Sys_ItemEquip* Sys_ItemEquip_ptr;
	typedef std::vector<Sys_ItemEquip_ptr> Sys_ItemEquip_ptr_vec;
	typedef Sys_ItemEquip_ptr_vec& Sys_ItemEquip_ptr_vec_ref;

	struct Sys_ItemConsume;
	typedef Sys_ItemConsume* Sys_ItemConsume_ptr;
	typedef std::vector<Sys_ItemConsume_ptr> Sys_ItemConsume_ptr_vec;
	typedef Sys_ItemConsume_ptr_vec& Sys_ItemConsume_ptr_vec_ref;



struct jEXCEL_LIB_API Sys_MainItemAbility /* ������� */
{
	/*  ������ȣ */
	int16 m_sid; // ������ȣ min_max(,)
	/*  ��������ī�װ� */
	EItemCategoryEquipment m_equip_category; // ��������ī�װ� min_max(,EItemCategoryEquipment)
	/*  ������ ���׷��̵� ��� */
	EItemGradeType m_grade; // ��� min_max(,EItemGradeType)
	/*  ������ ���� ���׷��̵� ��� */
	EItemSubGradeType m_subgrade; // ���� ��� min_max(,EItemSubGradeType)
	/*  ������ ���� ���� ���� */
	float m_mainitem_first_equip_level; // ���������� ���� ���� min_max(,)
	/*  ������ ��ȭ ���� ���� */
	float m_mainitem_possible_upgrade_level; // �����۰�ȭ ���� ���� min_max(,)
	/*  ������ ��ȭ �ʿ� �ð� */
	float m_mainitem_need_time; // �����۰�ȭ �ʿ� �ð� min_max(,)
	/*  ������ �⺻ �ɷ�ġ */
	float m_mainitem_basic_value; // �����۱⺻�ɷ�ġ min_max(,)
	/*  �ش�������������� */
	float m_mainitem_equip_level; // �ش�������������� min_max(,)
	/*  ��ȭ�� �ּ� ���� �ɷ�ġ(IUR_NORMAL) */
	float m_value_min; // ��ȭ���ּ������ɷ�ġ min_max(,)
	/*  ��ȭ�� �ִ� ���� �ɷ�ġ(IUR_PERFECT) */
	float m_value_max; // ��ȭ���ִ������ɷ�ġ min_max(,)
	/*  Ÿ���������� */
	EPlayerType m_player_type; // Ÿ���������� min_max(,EPlayerType)
	/*  ���׷��̵� �ʿ� ���� �Ӵ� */
	int64 m_mainitem_upgrade_need_money; // �ʿ���ӸӴ� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_MainItemAbility
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  13 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_MainItemAbility
		jEXCEL_TABLE_COMMON_CODE_H_Sys_MainItemAbility();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_MainItemAbility

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_MainItemAbility)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_MainItemAbility
enum { eSTRUCT_SIZE_Sys_MainItemAbility = sizeof(Sys_MainItemAbility) };


struct CSV_Sys_MainItemAbility : public nMech::nUtil::jCSV_File<Sys_MainItemAbility>
{
	virtual ~CSV_Sys_MainItemAbility(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_MainItemAbility>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_MainItemAbility g_Sys_MainItemAbility;

struct jEXCEL_LIB_API Sys_Package /* ������� */
{
	Sys_Package_id_t m_sid; // sid min_max(,)
	aname32_t m_name; // name min_max(,)
	EItemPriceType m_price_type; // ����Ÿ�� min_max(,EItemPriceType)
	int32 m_price_money; // �ʿ���ӸӴ� min_max(,)
	int32 m_price_cash; // �ʿ丮��ĳ�� min_max(,)
	Sys_ItemEquip_ptr_vec m_equip_items1_ptr_vec; // �����ۺ��׷��̵����1 Ÿ�� min_max(,)
	Sys_ItemConsume_ptr_vec m_consum_items1_ptr_vec; // �����ۺ��׷��̵����2 Ÿ�� min_max(,)
	Sys_ItemEquip_ptr_vec m_equip_items2_ptr_vec; // �����ۺ��׷��̵����1 ���� min_max(,)
	Sys_ItemConsume_ptr_vec m_consum_items2_ptr_vec; // �����ۺ��׷��̵����2 ���� min_max(,)
	Sys_ItemEquip_ptr_vec m_equip_items3_ptr_vec; // �����ۺ��׷��̵����1 ����Ÿ�� min_max(,)
	Sys_ItemConsume_ptr_vec m_consum_items3_ptr_vec; // �����ۺ��׷��̵����2 ����Ÿ�� min_max(,)
	Sys_ItemEquip_ptr_vec m_equip_items4_ptr_vec; // �����ۺ��׷��̵����1 �������� min_max(,)
	Sys_ItemConsume_ptr_vec m_consum_items4_ptr_vec; // �����ۺ��׷��̵����2 �������� min_max(,)
	EGiftType m_gift_type1; // ��������1 min_max(,EGiftType)
	/*  value�� �ǹ̴� EGiftType�� ���� �ٸ��� */
	int64 m_gift_type1_value; // ����1 min_max(,)
	EGiftType m_gift_type2; // ��������2 min_max(,EGiftType)
	int64 m_gift_type2_value; // ����2 min_max(,)
	EGiftType m_gift_type3; // ��������3 min_max(,EGiftType)
	int64 m_gift_type3_value; // ����3 min_max(,)
	EGiftType m_gift_type4; // ��������4 min_max(,EGiftType)
	int64 m_gift_type4_value; // ����4 min_max(,)
	EGiftType m_gift_type5; // ��������5 min_max(,EGiftType)
	int64 m_gift_type5_value; // ����5 min_max(,)
	EGiftType m_gift_type6; // ��������6 min_max(,EGiftType)
	int64 m_gift_type6_value; // ����6 min_max(,)
	EGiftType m_gift_type7; // ��������7 min_max(,EGiftType)
	int64 m_gift_type7_value; // ����7 min_max(,)
	EGiftType m_gift_type8; // ��������8 min_max(,EGiftType)
	int64 m_gift_type8_value; // ����8 min_max(,)
	EGiftType m_gift_type9; // ��������9 min_max(,EGiftType)
	int64 m_gift_type9_value; // ����9 min_max(,)
	EGiftType m_gift_type10; // ��������10 min_max(,EGiftType)
	int64 m_gift_type10_value; // ����10 min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_Package
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Package_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  33 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Package
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Package();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Package

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Package_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Package)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Package
enum { eSTRUCT_SIZE_Sys_Package = sizeof(Sys_Package) };


struct CSV_Sys_Package : public nMech::nUtil::jCSV_File<Sys_Package>
{
	virtual ~CSV_Sys_Package(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Package>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Package g_Sys_Package;

struct jEXCEL_LIB_API Sys_Shop /* ������� */
{
	Sys_Shop_id_t m_shop_id; // shop_id min_max(,)
	aname32_t m_name; // name min_max(,)
	/*  ������ type */
	EShopItemType m_item_type; // item_type min_max(,EShopItemType)
	/*  ������ index */
	int32 m_item_index; // item_index min_max(,)
	/*  �Ż�ǰ���� �ƴ��� */
	bool m_is_new; // is_new min_max(,)
	/*  ����Ʈ ��ǰ���� �ƴ��� */
	bool m_is_best; // is_best min_max(,)
	/*  �� ��ǰ���� �ƴ��� */
	bool m_is_hot; // is_hot min_max(,)
	/*  ���� ���� ����(Ÿ�� ������) */
	EShopBatterSection m_shop_batter_section; // shop_batter_section min_max(,EShopBatterSection)
	/*  ���� ���� ����(���� ������) */
	EShopPitcherSection m_shop_pitcher_section; // shop_pitcher_section min_max(,EShopPitcherSection)
	/*  ���� ���� ����(�Һ� ������) */
	EShopConsumeSection m_shop_consume_section; // shop_consume_section min_max(,EShopConsumeSection)
	/*  �Ǹ� ���� �Ͻ� */
	SYSTEMTIME m_sell_start_date; // �Ǹ� ���� �Ͻ� min_max(,)
	/*  �Ǹ� ���� �Ͻ� */
	SYSTEMTIME m_sell_end_date; // �Ǹ� ���� �Ͻ� min_max(,)
	/*  �ʿ���ӸӴ� */
	int32 m_price_money; // �ʿ���ӸӴ� min_max(,)
	/*  �ʿ丮��ĳ�� */
	int32 m_price_cash; // �ʿ丮��ĳ�� min_max(,)
	/*  ����Ÿ�� */
	EItemPriceType m_price_type; // ����Ÿ�� min_max(,EItemPriceType)
	/*  �ǸŻ��� */
	EItemSellStatus m_sell_status; // �ǸŻ��� min_max(,EItemSellStatus)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_Shop
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Shop_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  16 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Shop
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Shop();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Shop

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Shop_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Shop)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Shop
enum { eSTRUCT_SIZE_Sys_Shop = sizeof(Sys_Shop) };


struct CSV_Sys_Shop : public nMech::nUtil::jCSV_File<Sys_Shop>
{
	virtual ~CSV_Sys_Shop(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Shop>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Shop g_Sys_Shop;

struct jEXCEL_LIB_API Sys_SubItemAbility /* ������� */
{
	/*  ������ȣ */
	int16 m_sid; // ������ȣ min_max(,)
	/*  ��������ī�װ� */
	EItemCategoryEquipment m_equip_category; // ��������ī�װ� min_max(,EItemCategoryEquipment)
	/*  ������ ���׷��̵� ��� */
	EItemGradeType m_grade; // ��� min_max(,EItemGradeType)
	/*  ������ ���� ���� ���� */
	int8 m_subitem_first_equip_level; // ���������� ���� ���� min_max(,)
	/*  ������ �⺻ �ɷ�ġ */
	int8 m_subitem_better_ability; // ������Ÿ�ڴɷ�ġ min_max(,)
	/*  ������ �⺻ �ɷ�ġ */
	float m_subitem_pitcher_ability; // �����������ɷ�ġ min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_SubItemAbility
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  6 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_SubItemAbility
		jEXCEL_TABLE_COMMON_CODE_H_Sys_SubItemAbility();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_SubItemAbility

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_SubItemAbility)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_SubItemAbility
enum { eSTRUCT_SIZE_Sys_SubItemAbility = sizeof(Sys_SubItemAbility) };


struct CSV_Sys_SubItemAbility : public nMech::nUtil::jCSV_File<Sys_SubItemAbility>
{
	virtual ~CSV_Sys_SubItemAbility(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_SubItemAbility>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_SubItemAbility g_Sys_SubItemAbility;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_baseball_table_shop_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_baseball_table_shop_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_baseball_table_shop_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_baseball_table_shop_
