/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_shop_
#define __namespace_nEXCEL___filename_excel_baseball_table_shop_

#include "table_const_excel_baseball_table_shop.h"
// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_shop_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_MainItemAbility,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_Package,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_Shop,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_SubItemAbility,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_MainItemAbility 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,고유번호               ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(equip_category         ,장비아이템카테고리          ,EItemCategoryEquipment       ,1 , EItemCategoryEquipment , EItemCategoryEquipment , e)\
		FIELD(grade                  ,등급                 ,EItemGradeType               ,2 , EItemGradeType , EItemGradeType , e)\
		FIELD(subgrade               ,서브 등급              ,EItemSubGradeType            ,3 , EItemSubGradeType , EItemSubGradeType , e)\
		FIELD(mainitem_first_equip_level,아이템최초 장착 레벨     ,float                        ,4 , float , float , f)\
		FIELD(mainitem_possible_upgrade_level,아이템강화 가능 레벨 ,float                       ,5 , float , float , f)\
		FIELD(mainitem_need_time     ,아이템강화 필요 시간        ,float                        ,6 , float , float , f)\
		FIELD(mainitem_basic_value   ,아이템기본능력치           ,float                        ,7 , float , float , f)\
		FIELD(mainitem_equip_level   ,해당아이템장착레벨          ,float                        ,8 , float , float , f)\
		FIELD(value_min              ,강화시최소증가능력치         ,float                        ,9 , float , float , f)\
		FIELD(value_max              ,강화시최대증가능력치         ,float                        ,10 , float , float , f)\
		FIELD(player_type            ,타자투수구분             ,EPlayerType                  ,11 , EPlayerType , EPlayerType , e)\
		FIELD(mainitem_upgrade_need_money,필요게임머니         ,int64                        ,12 , int64 , int64 , i64)\

	#endif // for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_MainItemAbility가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_MainItemAbility_InheritedTable
	#define for_each_nEXCEL_Sys_MainItemAbility_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_MainItemAbility_InheritedTable


	// ------------------------------------------------------------
	// Sys_MainItemAbility가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_MainItemAbility가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Package 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Package_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Package_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,sid                ,Sys_Package_id_t             ,0 , Sys_Package_id_t , uint16 , u16)\
		FIELD(name                   ,name               ,aname32_t                    ,1 , acstr , acstr , a32)\
		FIELD(price_type             ,구매타입               ,EItemPriceType               ,2 , EItemPriceType , EItemPriceType , e)\
		FIELD(price_money            ,필요게임머니             ,int32                        ,3 , int32 , int32 , i32)\
		FIELD(price_cash             ,필요리얼캐쉬             ,int32                        ,4 , int32 , int32 , i32)\
		FIELD(equip_items1           ,아이템별그레이드모음1 타자     ,Sys_ItemEquip_ptr_vec        , 5 ,Sys_ItemEquip_ptr_vec_ref , Sys_ItemEquip_ptr_vec_ref , ptr_vec)\
		FIELD(consum_items1          ,아이템별그레이드모음2 타자     ,Sys_ItemConsume_ptr_vec      , 6 ,Sys_ItemConsume_ptr_vec_ref , Sys_ItemConsume_ptr_vec_ref , ptr_vec)\
		FIELD(equip_items2           ,아이템별그레이드모음1 투수     ,Sys_ItemEquip_ptr_vec        , 7 ,Sys_ItemEquip_ptr_vec_ref , Sys_ItemEquip_ptr_vec_ref , ptr_vec)\
		FIELD(consum_items2          ,아이템별그레이드모음2 투수     ,Sys_ItemConsume_ptr_vec      , 8 ,Sys_ItemConsume_ptr_vec_ref , Sys_ItemConsume_ptr_vec_ref , ptr_vec)\
		FIELD(equip_items3           ,아이템별그레이드모음1 여자타자   ,Sys_ItemEquip_ptr_vec        , 9 ,Sys_ItemEquip_ptr_vec_ref , Sys_ItemEquip_ptr_vec_ref , ptr_vec)\
		FIELD(consum_items3          ,아이템별그레이드모음2 여자타자   ,Sys_ItemConsume_ptr_vec      , 10 ,Sys_ItemConsume_ptr_vec_ref , Sys_ItemConsume_ptr_vec_ref , ptr_vec)\
		FIELD(equip_items4           ,아이템별그레이드모음1 여자투수   ,Sys_ItemEquip_ptr_vec        , 11 ,Sys_ItemEquip_ptr_vec_ref , Sys_ItemEquip_ptr_vec_ref , ptr_vec)\
		FIELD(consum_items4          ,아이템별그레이드모음2 여자투수   ,Sys_ItemConsume_ptr_vec      , 12 ,Sys_ItemConsume_ptr_vec_ref , Sys_ItemConsume_ptr_vec_ref , ptr_vec)\
		FIELD(gift_type1             ,선물종류1              ,EGiftType                    ,13 , EGiftType , EGiftType , e)\
		FIELD(gift_type1_value       ,선물1                ,int64                        ,14 , int64 , int64 , i64)\
		FIELD(gift_type2             ,선물종류2              ,EGiftType                    ,15 , EGiftType , EGiftType , e)\
		FIELD(gift_type2_value       ,선물2                ,int64                        ,16 , int64 , int64 , i64)\
		FIELD(gift_type3             ,선물종류3              ,EGiftType                    ,17 , EGiftType , EGiftType , e)\
		FIELD(gift_type3_value       ,선물3                ,int64                        ,18 , int64 , int64 , i64)\
		FIELD(gift_type4             ,선물종류4              ,EGiftType                    ,19 , EGiftType , EGiftType , e)\
		FIELD(gift_type4_value       ,선물4                ,int64                        ,20 , int64 , int64 , i64)\
		FIELD(gift_type5             ,선물종류5              ,EGiftType                    ,21 , EGiftType , EGiftType , e)\
		FIELD(gift_type5_value       ,선물5                ,int64                        ,22 , int64 , int64 , i64)\
		FIELD(gift_type6             ,선물종류6              ,EGiftType                    ,23 , EGiftType , EGiftType , e)\
		FIELD(gift_type6_value       ,선물6                ,int64                        ,24 , int64 , int64 , i64)\
		FIELD(gift_type7             ,선물종류7              ,EGiftType                    ,25 , EGiftType , EGiftType , e)\
		FIELD(gift_type7_value       ,선물7                ,int64                        ,26 , int64 , int64 , i64)\
		FIELD(gift_type8             ,선물종류8              ,EGiftType                    ,27 , EGiftType , EGiftType , e)\
		FIELD(gift_type8_value       ,선물8                ,int64                        ,28 , int64 , int64 , i64)\
		FIELD(gift_type9             ,선물종류9              ,EGiftType                    ,29 , EGiftType , EGiftType , e)\
		FIELD(gift_type9_value       ,선물9                ,int64                        ,30 , int64 , int64 , i64)\
		FIELD(gift_type10            ,선물종류10             ,EGiftType                    ,31 , EGiftType , EGiftType , e)\
		FIELD(gift_type10_value      ,선물10               ,int64                        ,32 , int64 , int64 , i64)\

	#endif // for_each_nEXCEL_Sys_Package_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Package가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Package_InheritedTable
	#define for_each_nEXCEL_Sys_Package_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Package_InheritedTable


	// ------------------------------------------------------------
	// Sys_Package가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Package_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Package_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Package_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Package가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Package_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Package_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Package_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Package_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Package_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Shop 자신의 필드만 나열한 매크로.
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
		FIELD(sell_start_date        ,판매 시작 일시           ,SYSTEMTIME                   ,10 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(sell_end_date          ,판매 종료 일시           ,SYSTEMTIME                   ,11 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(price_money            ,필요게임머니             ,int32                        ,12 , int32 , int32 , i32)\
		FIELD(price_cash             ,필요리얼캐쉬             ,int32                        ,13 , int32 , int32 , i32)\
		FIELD(price_type             ,구매타입               ,EItemPriceType               ,14 , EItemPriceType , EItemPriceType , e)\
		FIELD(sell_status            ,판매상태               ,EItemSellStatus              ,15 , EItemSellStatus , EItemSellStatus , e)\

	#endif // for_each_nEXCEL_Sys_Shop_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Shop가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Shop_InheritedTable
	#define for_each_nEXCEL_Sys_Shop_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Shop_InheritedTable


	// ------------------------------------------------------------
	// Sys_Shop가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Shop가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Shop_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_SubItemAbility 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,고유번호               ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(equip_category         ,장비아이템카테고리          ,EItemCategoryEquipment       ,1 , EItemCategoryEquipment , EItemCategoryEquipment , e)\
		FIELD(grade                  ,등급                 ,EItemGradeType               ,2 , EItemGradeType , EItemGradeType , e)\
		FIELD(subitem_first_equip_level,아이템최초 장착 레벨      ,int8                         ,3 , int8 , int8 , i8)\
		FIELD(subitem_better_ability ,아이템타자능력치           ,int8                         ,4 , int8 , int8 , i8)\
		FIELD(subitem_pitcher_ability,아이템투수능력치           ,float                        ,5 , float , float , f)\

	#endif // for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_SubItemAbility가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_SubItemAbility_InheritedTable
	#define for_each_nEXCEL_Sys_SubItemAbility_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_SubItemAbility_InheritedTable


	// ------------------------------------------------------------
	// Sys_SubItemAbility가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_SubItemAbility가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
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



struct jEXCEL_LIB_API Sys_MainItemAbility /* 설명없음 */
{
	/*  고유번호 */
	int16 m_sid; // 고유번호 min_max(,)
	/*  장비아이템카테고리 */
	EItemCategoryEquipment m_equip_category; // 장비아이템카테고리 min_max(,EItemCategoryEquipment)
	/*  아이템 업그레이드 등급 */
	EItemGradeType m_grade; // 등급 min_max(,EItemGradeType)
	/*  아이템 서브 업그레이드 등급 */
	EItemSubGradeType m_subgrade; // 서브 등급 min_max(,EItemSubGradeType)
	/*  아이템 최초 장착 레벨 */
	float m_mainitem_first_equip_level; // 아이템최초 장착 레벨 min_max(,)
	/*  아이템 강화 가능 레벨 */
	float m_mainitem_possible_upgrade_level; // 아이템강화 가능 레벨 min_max(,)
	/*  아이템 강화 필요 시간 */
	float m_mainitem_need_time; // 아이템강화 필요 시간 min_max(,)
	/*  아이템 기본 능력치 */
	float m_mainitem_basic_value; // 아이템기본능력치 min_max(,)
	/*  해당아이템장착레벨 */
	float m_mainitem_equip_level; // 해당아이템장착레벨 min_max(,)
	/*  강화시 최소 증가 능력치(IUR_NORMAL) */
	float m_value_min; // 강화시최소증가능력치 min_max(,)
	/*  강화시 최대 증가 능력치(IUR_PERFECT) */
	float m_value_max; // 강화시최대증가능력치 min_max(,)
	/*  타자투수구분 */
	EPlayerType m_player_type; // 타자투수구분 min_max(,EPlayerType)
	/*  업그레이드 필요 게임 머니 */
	int64 m_mainitem_upgrade_need_money; // 필요게임머니 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Sys_Package /* 설명없음 */
{
	Sys_Package_id_t m_sid; // sid min_max(,)
	aname32_t m_name; // name min_max(,)
	EItemPriceType m_price_type; // 구매타입 min_max(,EItemPriceType)
	int32 m_price_money; // 필요게임머니 min_max(,)
	int32 m_price_cash; // 필요리얼캐쉬 min_max(,)
	Sys_ItemEquip_ptr_vec m_equip_items1_ptr_vec; // 아이템별그레이드모음1 타자 min_max(,)
	Sys_ItemConsume_ptr_vec m_consum_items1_ptr_vec; // 아이템별그레이드모음2 타자 min_max(,)
	Sys_ItemEquip_ptr_vec m_equip_items2_ptr_vec; // 아이템별그레이드모음1 투수 min_max(,)
	Sys_ItemConsume_ptr_vec m_consum_items2_ptr_vec; // 아이템별그레이드모음2 투수 min_max(,)
	Sys_ItemEquip_ptr_vec m_equip_items3_ptr_vec; // 아이템별그레이드모음1 여자타자 min_max(,)
	Sys_ItemConsume_ptr_vec m_consum_items3_ptr_vec; // 아이템별그레이드모음2 여자타자 min_max(,)
	Sys_ItemEquip_ptr_vec m_equip_items4_ptr_vec; // 아이템별그레이드모음1 여자투수 min_max(,)
	Sys_ItemConsume_ptr_vec m_consum_items4_ptr_vec; // 아이템별그레이드모음2 여자투수 min_max(,)
	EGiftType m_gift_type1; // 선물종류1 min_max(,EGiftType)
	/*  value의 의미는 EGiftType에 따라 다르다 */
	int64 m_gift_type1_value; // 선물1 min_max(,)
	EGiftType m_gift_type2; // 선물종류2 min_max(,EGiftType)
	int64 m_gift_type2_value; // 선물2 min_max(,)
	EGiftType m_gift_type3; // 선물종류3 min_max(,EGiftType)
	int64 m_gift_type3_value; // 선물3 min_max(,)
	EGiftType m_gift_type4; // 선물종류4 min_max(,EGiftType)
	int64 m_gift_type4_value; // 선물4 min_max(,)
	EGiftType m_gift_type5; // 선물종류5 min_max(,EGiftType)
	int64 m_gift_type5_value; // 선물5 min_max(,)
	EGiftType m_gift_type6; // 선물종류6 min_max(,EGiftType)
	int64 m_gift_type6_value; // 선물6 min_max(,)
	EGiftType m_gift_type7; // 선물종류7 min_max(,EGiftType)
	int64 m_gift_type7_value; // 선물7 min_max(,)
	EGiftType m_gift_type8; // 선물종류8 min_max(,EGiftType)
	int64 m_gift_type8_value; // 선물8 min_max(,)
	EGiftType m_gift_type9; // 선물종류9 min_max(,EGiftType)
	int64 m_gift_type9_value; // 선물9 min_max(,)
	EGiftType m_gift_type10; // 선물종류10 min_max(,EGiftType)
	int64 m_gift_type10_value; // 선물10 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Sys_Shop /* 설명없음 */
{
	Sys_Shop_id_t m_shop_id; // shop_id min_max(,)
	aname32_t m_name; // name min_max(,)
	/*  아이템 type */
	EShopItemType m_item_type; // item_type min_max(,EShopItemType)
	/*  아이템 index */
	int32 m_item_index; // item_index min_max(,)
	/*  신상품인지 아닌지 */
	bool m_is_new; // is_new min_max(,)
	/*  베스트 상품인지 아닌지 */
	bool m_is_best; // is_best min_max(,)
	/*  핫 상품인지 아닌지 */
	bool m_is_hot; // is_hot min_max(,)
	/*  샵의 섹션 구분(타자 아이템) */
	EShopBatterSection m_shop_batter_section; // shop_batter_section min_max(,EShopBatterSection)
	/*  샵의 섹션 구분(투수 아이템) */
	EShopPitcherSection m_shop_pitcher_section; // shop_pitcher_section min_max(,EShopPitcherSection)
	/*  샵의 섹션 구분(소비 아이템) */
	EShopConsumeSection m_shop_consume_section; // shop_consume_section min_max(,EShopConsumeSection)
	/*  판매 시작 일시 */
	SYSTEMTIME m_sell_start_date; // 판매 시작 일시 min_max(,)
	/*  판매 종료 일시 */
	SYSTEMTIME m_sell_end_date; // 판매 종료 일시 min_max(,)
	/*  필요게임머니 */
	int32 m_price_money; // 필요게임머니 min_max(,)
	/*  필요리얼캐쉬 */
	int32 m_price_cash; // 필요리얼캐쉬 min_max(,)
	/*  구매타입 */
	EItemPriceType m_price_type; // 구매타입 min_max(,EItemPriceType)
	/*  판매상태 */
	EItemSellStatus m_sell_status; // 판매상태 min_max(,EItemSellStatus)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Sys_SubItemAbility /* 설명없음 */
{
	/*  고유번호 */
	int16 m_sid; // 고유번호 min_max(,)
	/*  장비아이템카테고리 */
	EItemCategoryEquipment m_equip_category; // 장비아이템카테고리 min_max(,EItemCategoryEquipment)
	/*  아이템 업그레이드 등급 */
	EItemGradeType m_grade; // 등급 min_max(,EItemGradeType)
	/*  아이템 최초 장착 레벨 */
	int8 m_subitem_first_equip_level; // 아이템최초 장착 레벨 min_max(,)
	/*  아이템 기본 능력치 */
	int8 m_subitem_better_ability; // 아이템타자능력치 min_max(,)
	/*  아이템 기본 능력치 */
	float m_subitem_pitcher_ability; // 아이템투수능력치 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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
