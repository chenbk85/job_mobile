/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_db_
#define __namespace_nEXCEL___filename_excel_baseball_table_db_

#include "table_const_excel_baseball_table_db.h"
// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_db_Tbl_STRUCT_LIST(STRUCT)\
	STRUCT(Tbl__BasicScore,�������,nMech,nEXCEL)\
	STRUCT(Tbl__PlayerBase,�������,nMech,nEXCEL)\
	STRUCT(Tbl_Friend,�������,nMech,nEXCEL)\
	STRUCT(Tbl_Item,�������,nMech,nEXCEL)\
	STRUCT(Tbl_Item_Admin,�������,nMech,nEXCEL)\
	STRUCT(Tbl_Package,������ ��Ű������Ʈ,nMech,nEXCEL)\
	STRUCT(Tbl_PitcherSkill,�������,nMech,nEXCEL)\
	STRUCT(Tbl_PlayerBetter,�������,nMech,nEXCEL)\
	STRUCT(Tbl_PlayerPitcher,�������,nMech,nEXCEL)\
	STRUCT(Tbl_Quest,�������,nMech,nEXCEL)\
	STRUCT(Tbl_Result,�������,nMech,nEXCEL)\
	STRUCT(Tbl_RoundResult,�������,nMech,nEXCEL)\
	STRUCT(Tbl_Team,�������,nMech,nEXCEL)\
	STRUCT(Tbl_Title,�������,nMech,nEXCEL)\
	STRUCT(Tbl_User,�������,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Tbl__BasicScore �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD(FIELD)\
		FIELD(win_tot                ,������_��              ,int32                        ,0 , int32 , int32 , i32)\
		FIELD(lose_tot               ,������_��              ,int32                        ,1 , int32 , int32 , i32)\
		FIELD(win_season             ,��������_��             ,int32                        ,2 , int32 , int32 , i32)\
		FIELD(lose_season            ,��������_��             ,int32                        ,3 , int32 , int32 , i32)\
		FIELD(win_continue           ,����                 ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(win_tot_single         ,�̱�-������_��           ,int32                        ,5 , int32 , int32 , i32)\
		FIELD(lose_tot_single        ,�̱�-������_��           ,int32                        ,6 , int32 , int32 , i32)\
		FIELD(win_season_single      ,�̱�-��������_��          ,int32                        ,7 , int32 , int32 , i32)\
		FIELD(lose_season_single     ,�̱�-��������_��          ,int32                        ,8 , int32 , int32 , i32)\
		FIELD(win_continue_single    ,�̱�-������             ,int16                        ,9 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl__BasicScore�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl__BasicScore_InheritedTable
	#define for_each_nEXCEL_Tbl__BasicScore_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl__BasicScore_InheritedTable


	// ------------------------------------------------------------
	// Tbl__BasicScore�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl__BasicScore�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl__PlayerBase �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,PK index           ,Tbl__PlayerBase_id_t         ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(sid                    ,Sys_Player���̵�      ,Sys_PlayerCard_id_t          ,1 , Sys_PlayerCard_id_t , uint16 , u16)\
		FIELD(uid                    ,������ȣ               ,Tbl_User_id_t                ,2 , int64 , int64 , i)\
		FIELD(pname                  ,�г���                ,aname32_t                    ,3 , acstr , acstr , a32)\
		FIELD(city                   ,��ű���               ,EPlayerNationType            ,4 , EPlayerNationType , EPlayerNationType , e)\
		FIELD(initial_name           ,�̴ϼ�                ,aname32_t                    ,5 , acstr , acstr , a32)\
		FIELD(back_number            ,��ѹ�                ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(age                    ,����                 ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(body_type              ,ü��                 ,EPlayerBodyType              ,8 , EPlayerBodyType , EPlayerBodyType , e)\
		FIELD(is_left                ,�¿�Ÿ��               ,bool                         ,9 , bool , bool , b)\
		FIELD(exp                    ,����ġ                ,int64                        ,10 , int64 , int64 , i64)\
		FIELD(questcomplete_count    ,����Ʈ�Ϸ�_ī��Ʈ          ,Sys_Quest_id_t               ,11 , Sys_Quest_id_t , uint16 , u16)\
		FIELD(last_game_result       ,���������id            ,Tbl_Result_id_t              ,12 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(skill_sticker          ,Ư���ɷ��̸�             ,aname1024_t                  ,14 , acstr , acstr , a1024)\
		FIELD(is_deleted             ,is_deleted         ,int16                        ,15 , int16 , int16 , i16)\
		FIELD(date_insert            ,��Ͻð�               ,SYSTEMTIME                   ,16 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(date_update            ,�����Ƚð�              ,SYSTEMTIME                   ,17 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(elo_point              ,ELO_����Ʈ            ,int32                        ,18 , int32 , int32 , i32)\
		FIELD(team                   ,�Ҽ���id              ,Tbl_Team_id_t                ,19 , db_uid_type_ref , db_uid_type_ref , i64)\

	#endif // for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl__PlayerBase�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl__PlayerBase_InheritedTable
	#define for_each_nEXCEL_Tbl__PlayerBase_InheritedTable(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_InheritedTable(FUNC)\
		FUNC(Tbl__BasicScore)\

	#endif // for_each_nEXCEL_Tbl__PlayerBase_InheritedTable


	// ------------------------------------------------------------
	// Tbl__PlayerBase�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl__PlayerBase�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Friend �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,id                 ,Tbl_Friend_id_t              ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(uid                    ,������ȣ               ,Tbl_User_id_t                ,1 , int64 , int64 , i)\
		FIELD(uid_fiend              ,ģ����ȣ               ,Tbl_User_id_t                ,2 , int64 , int64 , i)\
		FIELD(nic_fiend              ,ģ���̸�               ,aname32_t                    ,3 , acstr , acstr , a32)\
		FIELD(is_blocked             ,is_blocked         ,bool                         ,4 , bool , bool , b)\
		FIELD(is_deleted             ,is_deleted         ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(win_tot                ,ģ��-������_��           ,int32                        ,6 , int32 , int32 , i32)\
		FIELD(lose_tot               ,ģ��-������_��           ,int32                        ,7 , int32 , int32 , i32)\
		FIELD(win_season             ,ģ��-��������_��          ,int32                        ,8 , int32 , int32 , i32)\
		FIELD(lose_season            ,ģ��-��������_��          ,int32                        ,9 , int32 , int32 , i32)\
		FIELD(win_continue           ,ģ��-����              ,int16                        ,10 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Friend�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Friend_InheritedTable
	#define for_each_nEXCEL_Tbl_Friend_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Friend_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Friend�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Friend�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Item �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Item_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Item_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,�����ĺ���              ,Tbl_Item_id_t                ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(sid                    ,������ ����������          ,Sys__ItemBase_id_t           ,1 , Sys__ItemBase_id_t , uint16 , u16)\
		FIELD(category               ,��з�                ,EItemCategory                ,2 , EItemCategory , EItemCategory , e)\
		FIELD(uid                    ,������id              ,Tbl_User_id_t                ,3 , int64 , int64 , i)\
		FIELD(used_player_id         ,�ͼӵȼ���ID            ,Tbl__PlayerBase_id_t         ,4 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(is_better              ,������Ÿ����������          ,bool                         ,5 , bool , bool , b)\
		FIELD(upgrade_level          ,���׷��̵���            ,aname32_t                    ,6 , acstr , acstr , a32)\
		FIELD(date_end_upgrade       ,���׷��̵�����Ϸ�ð�        ,SYSTEMTIME                   ,7 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(etc_info               ,��Ÿ����               ,aname256_t                   ,8 , acstr , acstr , a256)\
		FIELD(is_equiped             ,��������               ,bool                         ,9 , bool , bool , b)\
		FIELD(date_expire            ,�Ⱓ���������ǻ��ð�        ,SYSTEMTIME                   ,10 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(date_insert            ,�����ѳ�¥              ,SYSTEMTIME                   ,11 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(date_update            ,�����Ƚð�              ,SYSTEMTIME                   ,12 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(is_deleted             ,�����÷���              ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(state                  ,�����ۻ���              ,EItemState                   ,14 , EItemState , EItemState , e)\
		FIELD(use_count              ,��밡���� ���Ƚ��         ,int16                        ,15 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Tbl_Item_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Item�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Item_InheritedTable
	#define for_each_nEXCEL_Tbl_Item_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Item_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Item�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Item�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Item_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Item_Admin �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,�����ĺ���              ,Tbl_Item_id_t                ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(rid                    ,���Ӱ���ĺ���            ,Tbl_Result_id_t              ,1 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(bought_real_money      ,����ĳ��               ,real_money_t                 ,2 , int32 , int32 , i32)\
		FIELD(bought_point_money     ,��������Ʈ              ,real_money_t                 ,3 , int32 , int32 , i32)\
		FIELD(bought_game_money      ,���Ű��ӸӴ�             ,game_money_t                 ,4 , int32 , int32 , i32)\
		FIELD(item_buy_type          ,���Ż���               ,EItemBuyType                 ,5 , EItemBuyType , EItemBuyType , e)\
		FIELD(shop_id                ,�����ǸŹ�ȣ             ,Sys_Shop_id_t                ,6 , Sys_Shop_id_t , uint16 , u16)\

	#endif // for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Item_Admin�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Item_Admin_InheritedTable
	#define for_each_nEXCEL_Tbl_Item_Admin_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Item_Admin_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Item_Admin�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Item_Admin�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Package �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Package_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Package_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,�����ĺ���              ,Tbl_Package_id_t             ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(sid_package            ,������ ����������          ,Sys_Package_id_t             ,1 , Sys_Package_id_t , uint16 , u16)\
		FIELD(uid                    ,������id              ,Tbl_User_id_t                ,2 , int64 , int64 , i)\
		FIELD(etc_info               ,��Ÿ����               ,aname256_t                   ,3 , acstr , acstr , a256)\
		FIELD(date_insert            ,�����ѳ�¥              ,SYSTEMTIME                   ,4 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(date_update            ,�����Ƚð�              ,SYSTEMTIME                   ,5 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(is_deleted             ,�����÷���              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(state                  ,�����ۻ���              ,EItemState                   ,7 , EItemState , EItemState , e)\

	#endif // for_each_nEXCEL_Tbl_Package_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Package�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Package_InheritedTable
	#define for_each_nEXCEL_Tbl_Package_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Package_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Package�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Package�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Package_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_PitcherSkill �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,������ȣ               ,Tbl_PitcherSkill_id_t        ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(uid                    ,������id              ,Tbl_User_id_t                ,1 , int64 , int64 , i)\
		FIELD(pid                    ,��������id             ,Tbl_PlayerPitcher_id_t       ,2 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(gesture                ,������Ÿ��              ,EGestureType                 ,3 , EGestureType , EGestureType , e)\
		FIELD(is_deleted             ,�����÷���              ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(exp                    ,������ȭ�� ���� �ð�        ,int32                        ,5 , int32 , int32 , i32)\
		FIELD(type                   ,������ȭ������            ,EPlayerBreakingBall          ,6 , EPlayerBreakingBall , EPlayerBreakingBall , e)\

	#endif // for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_PitcherSkill�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_PitcherSkill_InheritedTable
	#define for_each_nEXCEL_Tbl_PitcherSkill_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_PitcherSkill_InheritedTable


	// ------------------------------------------------------------
	// Tbl_PitcherSkill�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_PitcherSkill�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_PlayerBetter �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD(FIELD)\
		FIELD(batting_average        ,Ÿ��                 ,int16                        ,1 , int16 , int16 , i16)\
		FIELD(continue_homerun_count ,����Ȩ����              ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(homeruntotal_count     ,��_Ȩ����              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(single_homerun_count   ,�̱�Ȩ��ī��Ʈ            ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(tworun_homerun_count   ,����Ȩ��ī��Ʈ            ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(threerun_homerun_count ,������Ȩ��ī��Ʈ           ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(grandslam_homerun_count,����Ȩ��ī��Ʈ            ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(one_hit_count          ,�Ϸ�Ÿī��Ʈ             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(double_hit_count       ,�̷�Ÿī��Ʈ             ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(triple_hit_count       ,���Ÿī��Ʈ             ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(foul_hit_count         ,�Ŀ�ī��Ʈ              ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(out_hit_count          ,�ƿ�ī��Ʈ              ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(score_count            ,����ī��Ʈ              ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(betting_type           ,Ÿ��Ÿ��               ,EBatterAbility               ,14 , EBatterAbility , EBatterAbility , e)\
		FIELD(betting_form           ,Ÿ����                ,EBatterForm                  ,15 , EBatterForm , EBatterForm , e)\
		FIELD(better_power           ,Ÿ�� �Ŀ�              ,int16                        ,16 , int16 , int16 , i16)\
		FIELD(better_focus           ,Ÿ�� ����              ,int16                        ,17 , int16 , int16 , i16)\
		FIELD(better_power_buff      ,Ÿ�� �Ŀ� ����           ,int16                        ,18 , int16 , int16 , i16)\
		FIELD(better_focus_buff      ,Ÿ�� ���� ����           ,int16                        ,19 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_PlayerBetter�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_PlayerBetter_InheritedTable
	#define for_each_nEXCEL_Tbl_PlayerBetter_InheritedTable(FUNC)\
		for_each_nEXCEL_Tbl__PlayerBase_InheritedTable(FUNC)\
		FUNC(Tbl__PlayerBase)\

	#endif // for_each_nEXCEL_Tbl_PlayerBetter_InheritedTable


	// ------------------------------------------------------------
	// Tbl_PlayerBetter�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_PlayerBetter�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_PlayerPitcher �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD(FIELD)\
		FIELD(pitching_average       ,�����                ,int16                        ,1 , int16 , int16 , i16)\
		FIELD(hit_count              ,�Ǿ�Ÿ��               ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(strikeout_count        ,Ż������               ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(homerun_pitching_count ,��Ȩ����               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(continue_strikeout_count,���ӻ�����             ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(continue_homerun_pitching_count,������Ȩ����     ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(pitcher_type           ,����Ÿ��               ,EPitcherAbility              ,7 , EPitcherAbility , EPitcherAbility , e)\
		FIELD(pitcher_form           ,������                ,EPitcherForm                 ,8 , EPitcherForm , EPitcherForm , e)\
		FIELD(pitcher_control        ,���� ����              ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(pitcher_ballspeed      ,���� ����              ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(pitcher_control_buff   ,���� ���� ����           ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(pitcher_ballspeed_buff ,���� ���� ����           ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(pitcher_breakingball_value_buff,���� ��ȭ�� ��ġ ���� ,int16                      ,13 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_PlayerPitcher�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_PlayerPitcher_InheritedTable
	#define for_each_nEXCEL_Tbl_PlayerPitcher_InheritedTable(FUNC)\
		for_each_nEXCEL_Tbl__PlayerBase_InheritedTable(FUNC)\
		FUNC(Tbl__PlayerBase)\

	#endif // for_each_nEXCEL_Tbl_PlayerPitcher_InheritedTable


	// ------------------------------------------------------------
	// Tbl_PlayerPitcher�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_PlayerPitcher�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Quest �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,������ȣ               ,Tbl_Quest_id_t               ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(quest_sid              ,������ ����Ʈ sid        ,Sys_Quest_id_t               ,1 , Sys_Quest_id_t , uint16 , u16)\
		FIELD(uid                    ,����id               ,Tbl_User_id_t                ,2 , int64 , int64 , i)\
		FIELD(date_insert            ,��Ͻð�               ,SYSTEMTIME                   ,3 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(date_done              ,�Ϸ�ð�               ,SYSTEMTIME                   ,4 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(info                   ,���� ����              ,aname256_t                   ,5 , acstr , acstr , a256)\
		FIELD(done_count             ,������ Ƚ��             ,int32                        ,6 , int32 , int32 , i32)\

	#endif // for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Quest�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Quest_InheritedTable
	#define for_each_nEXCEL_Tbl_Quest_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Quest_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Quest�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Quest�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Result �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Result_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Result_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,game������ȣ           ,Tbl_Result_id_t              ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(is_singlemode          ,is_singlemode      ,bool                         ,1 , bool , bool , b)\
		FIELD(win_uid                ,������ȣ               ,Tbl_User_id_t                ,2 , int64 , int64 , i)\
		FIELD(win_better             ,Ÿ�� pid             ,Tbl_PlayerBetter_id_t        ,3 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(win_pitcher            ,���� pid             ,Tbl_PlayerPitcher_id_t       ,4 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(win_team               ,��id                ,Tbl_Team_id_t                ,5 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(win_score              ,���ڽ��ھ�              ,int8                         ,6 , int8 , int8 , i8)\
		FIELD(win_reward_exp         ,���� �������ġ           ,int32                        ,7 , int32 , int32 , i32)\
		FIELD(win_reward_gamemoney   ,���� ������ӸӴ�          ,game_money_t                 ,8 , int32 , int32 , i32)\
		FIELD(lose_uid               ,������ȣ               ,Tbl_User_id_t                ,9 , int64 , int64 , i)\
		FIELD(lose_better            ,Ÿ�� pid             ,Tbl_PlayerBetter_id_t        ,10 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(lose_pitcher           ,���� pid             ,Tbl_PlayerPitcher_id_t       ,11 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(lose_team              ,������id              ,Tbl_Team_id_t                ,12 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(lose_score             ,���ڽ��ھ�              ,int8                         ,13 , int8 , int8 , i8)\
		FIELD(lose_reward_exp        ,���� �������ġ           ,int32                        ,14 , int32 , int32 , i32)\
		FIELD(lose_reward_gamemoney  ,���� ������ӸӴ�          ,game_money_t                 ,15 , int32 , int32 , i32)\
		FIELD(play_time_sec          ,�÷��̽ð�              ,int32                        ,16 , int32 , int32 , i32)\
		FIELD(pp_point               ,�Ǹ��÷�������Ʈ           ,int64                        ,17 , int64 , int64 , i64)\
		FIELD(time_end               ,��������ð�             ,SYSTEMTIME                   ,18 , SYSTEMTIME , SYSTEMTIME , tm)\

	#endif // for_each_nEXCEL_Tbl_Result_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Result�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Result_InheritedTable
	#define for_each_nEXCEL_Tbl_Result_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Result_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Result�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Result�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Result_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_RoundResult �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,������ȣ               ,Tbl_RoundResult_id_t         ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(grid                   ,Tbl_Result_M�� ������ȣ ,Tbl_Result_id_t              ,1 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(round_number           ,�����ȣ              ,int8                         ,2 , int8 , int8 , i8)\
		FIELD(is_left                ,������ �������� ����        ,bool                         ,3 , bool , bool , b)\
		FIELD(used_breakingball      ,������ ��� ����          ,EPlayerBreakingBall          ,4 , EPlayerBreakingBall , EPlayerBreakingBall , e)\
		FIELD(used_breakingball_speed,������ ��� ������ ����      ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(used_pitcherability    ,����ϰ� �ִ� ������ ��ų(��ȭ�� ����) ,EPitcherAbility          ,6 , EPitcherAbility , EPitcherAbility , e)\
		FIELD(pitching_rhythm_judge  ,���� �� ���� Ÿ�̹�        ,ERhythmJudge                 ,7 , ERhythmJudge , ERhythmJudge , e)\
		FIELD(used_pitcher_itemcategoryequipment,������ ����ϰ� �ִ� ������ ,EItemCategoryEquipment ,8 , EItemCategoryEquipment , EItemCategoryEquipment , e)\
		FIELD(used_pitcher_counter   ,������ ī���� ���         ,bool                         ,9 , bool , bool , b)\
		FIELD(used_batterability     ,����ϰ� �ִ� Ÿ���� ��ų     ,EBatterAbility               ,10 , EBatterAbility , EBatterAbility , e)\
		FIELD(used_batting_fullpower ,Ÿ�� ��Ʈ �� Ǯ�Ŀ� ���     ,EHitType                     ,11 , EHitType , EHitType , e)\
		FIELD(batting_timing_judge   ,Ÿ�� �� Ÿ�� Ÿ�̹�        ,EHitTimmingType              ,12 , EHitTimmingType , EHitTimmingType , e)\
		FIELD(used_batter_itemcategoryequipment,Ÿ���� ����ϰ� �ִ� ������ ,EItemCategoryEquipment ,13 , EItemCategoryEquipment , EItemCategoryEquipment , e)\
		FIELD(used_batter_counter    ,Ÿ���� ī���� ���         ,bool                         ,14 , bool , bool , b)\
		FIELD(uid_attack             ,uid_attack         ,Tbl_User_id_t                ,15 , int64 , int64 , i)\
		FIELD(score                  ,better������          ,int8                         ,16 , int8 , int8 , i8)\
		FIELD(base_runner_state      ,��������ڼ�             ,int8                         ,17 , int8 , int8 , i8)\
		FIELD(hit_type               ,��Ÿ����               ,EBatterHitType               ,18 , EBatterHitType , EBatterHitType , e)\

	#endif // for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_RoundResult�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_RoundResult_InheritedTable
	#define for_each_nEXCEL_Tbl_RoundResult_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_RoundResult_InheritedTable


	// ------------------------------------------------------------
	// Tbl_RoundResult�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_RoundResult�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Team �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Team_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Team_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,������ȣ               ,Tbl_Team_id_t                ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(name                   ,���̸�                ,aname32_t                    ,1 , acstr , acstr , a32)\
		FIELD(uid                    ,����id               ,Tbl_User_id_t                ,2 , int64 , int64 , i)\
		FIELD(pid_better             ,Ÿ��                 ,Tbl_PlayerBetter_id_t        ,3 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(pid_pitcher            ,����                 ,Tbl_PlayerPitcher_id_t       ,4 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(is_deleted             ,�����÷���              ,int16                        ,6 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Tbl_Team_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Team�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Team_InheritedTable
	#define for_each_nEXCEL_Tbl_Team_InheritedTable(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_InheritedTable(FUNC)\
		FUNC(Tbl__BasicScore)\

	#endif // for_each_nEXCEL_Tbl_Team_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Team�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Team�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Team_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Title �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Title_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Title_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,������ȣ               ,Tbl_Title_id_t               ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(qid                    ,������ ����Ʈ qid        ,Tbl_Quest_id_t               ,1 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(title_sid              ,Ÿ��Ʋid              ,Sys_Title_id_t               ,2 , Sys_Title_id_t , uint16 , u16)\
		FIELD(group                  ,title_group        ,int32                        ,3 , int32 , int32 , i32)\
		FIELD(object_type            ,������ƮŸ��             ,EBaseballObjectType          ,4 , EBaseballObjectType , EBaseballObjectType , e)\
		FIELD(oid                    ,Ojectid            ,int64                        ,5 , int64 , int64 , i64)\
		FIELD(date_update            ,�����ð�               ,SYSTEMTIME                   ,6 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(date_insert            ,��Ͻð�               ,SYSTEMTIME                   ,7 , SYSTEMTIME , SYSTEMTIME , tm)\

	#endif // for_each_nEXCEL_Tbl_Title_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Title�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Title_InheritedTable
	#define for_each_nEXCEL_Tbl_Title_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Title_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Title�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Title�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Title_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_User �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_User_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_User_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,������ȣ               ,Tbl_User_id_t                ,0 , int64 , int64 , i)\
		FIELD(uname                  ,�г���                ,aname32_t                    ,1 , acstr , acstr , a32)\
		FIELD(discon_tot             ,��Disconnect��       ,int32                        ,2 , int32 , int32 , i32)\
		FIELD(pitcher_tot_strikeout  ,Ż������               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(pitcher_tot_average_level,���������_����         ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(better_tot_homerun     ,��_Ȩ����              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(better_tot__average_level,Ÿ�������_����         ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(cash_item_buy_count    ,ĳ���۱��Ű���            ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(time_last_login        ,�������α�ð�            ,SYSTEMTIME                   ,9 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(time_last_logout       ,�������α׾ƿ��ð�          ,SYSTEMTIME                   ,10 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(day_continue_attend    ,�����⼮�ϼ�             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(date_insert            ,��Ͻð�               ,SYSTEMTIME                   ,12 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(date_update            ,�����Ƚð�              ,SYSTEMTIME                   ,13 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(default_tid            ,�⺻����ȣ              ,Tbl_Team_id_t                ,14 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(option                 ,�ɼ�                 ,aname1024_t                  ,15 , acstr , acstr , a1024)\
		FIELD(singleplay_gift_count  ,�̱��÷��̺���ī��Ʈ         ,int16                        ,16 , int16 , int16 , i16)\
		FIELD(is_deleted             ,�����÷���              ,int16                        ,17 , int16 , int16 , i16)\
		FIELD(game_money             ,���ӸӴ�               ,int64                        ,18 , int64 , int64 , i64)\
		FIELD(client_os              ,client_os          ,aname32_t                    ,19 , acstr , acstr , a32)\
		FIELD(client_networ          ,client_networ      ,aname32_t                    ,20 , acstr , acstr , a32)\
		FIELD(playtime_tot           ,��_�÷���_Ÿ��           ,int64                        ,21 , int64 , int64 , i64)\

	#endif // for_each_nEXCEL_Tbl_User_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_User�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_User_InheritedTable
	#define for_each_nEXCEL_Tbl_User_InheritedTable(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_InheritedTable(FUNC)\
		FUNC(Tbl__BasicScore)\

	#endif // for_each_nEXCEL_Tbl_User_InheritedTable


	// ------------------------------------------------------------
	// Tbl_User�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_User_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_User_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Tbl_User_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_User�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_User_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_User_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_User_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_User_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_User_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{



struct jEXCEL_LIB_API Tbl__BasicScore /* ������� */
{
	/*  ��Ż �� ī��Ʈ */
	int32 m_win_tot; // ������_�� min_max(0,)
	/*  ��Ż �� ī��Ʈ */
	int32 m_lose_tot; // ������_�� min_max(0,)
	/*  ���� �� ī��Ʈ(3����) */
	int32 m_win_season; // ��������_�� min_max(0,)
	/*  ���� �� ī��Ʈ(3����) */
	int32 m_lose_season; // ��������_�� min_max(0,)
	/*  �������� �¸��� ����. ������ ���� */
	int16 m_win_continue; // ���� min_max(,)
	/*  ��Ż �� ī��Ʈ */
	int32 m_win_tot_single; // �̱�-������_�� min_max(0,)
	/*  ��Ż �� ī��Ʈ */
	int32 m_lose_tot_single; // �̱�-������_�� min_max(0,)
	/*  ���� �� ī��Ʈ(3����) */
	int32 m_win_season_single; // �̱�-��������_�� min_max(0,)
	/*  ���� �� ī��Ʈ(3����) */
	int32 m_lose_season_single; // �̱�-��������_�� min_max(0,)
	/*  �������� �¸��� ����. ������ ���� */
	int16 m_win_continue_single; // �̱�-������ min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl__BasicScore
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  10 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl__BasicScore
		jEXCEL_TABLE_COMMON_CODE_H_Tbl__BasicScore();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl__BasicScore

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl__BasicScore)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl__BasicScore
enum { eSTRUCT_SIZE_Tbl__BasicScore = sizeof(Tbl__BasicScore) };

struct jEXCEL_LIB_API Tbl__PlayerBase /* ������� */
	:Tbl__BasicScore
{
	/*  ���� database table PK */
	Tbl__PlayerBase_id_t m_db_id; // PK index min_max(,)
		typedef Tbl__PlayerBase_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  ������ ����ī���� ��ȣ(Sys_Player�� sid) ���� 0 �̸� ���󼱼� */
	Sys_PlayerCard_id_t m_sid; // Sys_Player���̵� min_max(,)
	Tbl_User_id_t m_uid; // ������ȣ min_max(,)
	aname32_t m_pname; // �г��� min_max(,)
	/*  ĳ�־�߱� ���ӱ�ȹ�� 3�� (20111031).docx���� */
	EPlayerNationType m_city; // ��ű��� min_max(,EPlayerNationType)
	/*  ������ ����. ������̴ϼȱ���. �ߺ����� */
	aname32_t m_initial_name; // �̴ϼ� min_max(,)
	/*  ������ ����. ������������� ���氡�� */
	int16 m_back_number; // ��ѹ� min_max(,)
	/*  ������ ����. */
	int16 m_age; // ���� min_max(1,999)
	EPlayerBodyType m_body_type; // ü�� min_max(,EPlayerBodyType)
	/*  ĳ������ �¿� ���� 1�̸� �¼��� 0�̸� �켱�� */
	bool m_is_left; // �¿�Ÿ�� min_max(,)
	/*  ������ ����ġ�� �ش��ϴ� Sys_PlayerLevel�� ���� ���� ���� */
	int64 m_exp; // ����ġ min_max(,)
	/*  �Ϸ� ����Ʈ ī��Ʈ */
	Sys_Quest_id_t m_questcomplete_count; // ����Ʈ�Ϸ�_ī��Ʈ min_max(,)
	/*  ���������� �÷����� ����� �ĺ��� */
	Tbl_Result_id_t m_last_game_result; // ���������id min_max(,)
	Tbl__BasicScore* GetBase_Tbl__BasicScore(){ return static_cast<Tbl__BasicScore*>(this);}
	/*  Sys_PlayeSkillSticker������   semicolon�� ���еǾ� �������Է� */
	aname1024_t m_skill_sticker; // Ư���ɷ��̸� min_max(0,)
	int16 m_is_deleted; // is_deleted min_max(,)
	/*  ���ʰ��ӵ���� */
	SYSTEMTIME m_date_insert; // ��Ͻð� min_max(,)
	/*  �����������ð� */
	SYSTEMTIME m_date_update; // �����Ƚð� min_max(,)
	/*  ��⸶�� ĳ���Ϳ� ���ŵǴ� ��Ī�� ����Ʈ */
	int32 m_elo_point; // ELO_����Ʈ min_max(1,10000)
	/*  �Ҽӵ� ����ȣ */
	Tbl_Team_id_t m_team; // �Ҽ���id min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl__PlayerBase
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  19 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Tbl__BasicScore::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl__PlayerBase
		jEXCEL_TABLE_COMMON_CODE_H_Tbl__PlayerBase();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl__PlayerBase

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl__PlayerBase)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl__PlayerBase
enum { eSTRUCT_SIZE_Tbl__PlayerBase = sizeof(Tbl__PlayerBase) };

struct jEXCEL_LIB_API Tbl_Friend /* ������� */
{
	Tbl_Friend_id_t m_db_id; // id min_max(,)
		typedef Tbl_Friend_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	Tbl_User_id_t m_uid; // ������ȣ min_max(,)
	Tbl_User_id_t m_uid_fiend; // ģ����ȣ min_max(,)
	aname32_t m_nic_fiend; // ģ���̸� min_max(,)
	/*  ������Ʈ�̳�? */
	bool m_is_blocked; // is_blocked min_max(,)
	int16 m_is_deleted; // is_deleted min_max(,)
	/*  ��Ż �� ī��Ʈ */
	int32 m_win_tot; // ģ��-������_�� min_max(0,)
	/*  ��Ż �� ī��Ʈ */
	int32 m_lose_tot; // ģ��-������_�� min_max(0,)
	/*  ���� �� ī��Ʈ(3����) */
	int32 m_win_season; // ģ��-��������_�� min_max(0,)
	/*  ���� �� ī��Ʈ(3����) */
	int32 m_lose_season; // ģ��-��������_�� min_max(0,)
	/*  �������� �¸��� ����. ������ ���� */
	int16 m_win_continue; // ģ��-���� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl_Friend
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  11 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl_Friend
		jEXCEL_TABLE_COMMON_CODE_H_Tbl_Friend();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl_Friend

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl_Friend)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl_Friend
enum { eSTRUCT_SIZE_Tbl_Friend = sizeof(Tbl_Friend) };

struct jEXCEL_LIB_API Tbl_Item /* ������� */
{
	/*  db pk */
	Tbl_Item_id_t m_db_id; // �����ĺ��� min_max(,)
		typedef Tbl_Item_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  Sys__ItemBase_id_t */
	Sys__ItemBase_id_t m_sid; // ������ ���������� min_max(,)
	/*  ��� ���� �Һ� ���� */
	EItemCategory m_category; // ��з� min_max(,EItemCategory)
	Tbl_User_id_t m_uid; // ������id min_max(,)
	/*  �ͼӵ� ����id�̸� �Ҹ��������� Ư�����ͼӵ����ʰ���.ĳ���κ� or �����κ� ȯ�ҿ��ΰ� �����ȴ� */
	Tbl__PlayerBase_id_t m_used_player_id; // �ͼӵȼ���ID min_max(,)
	/*  true=Ÿ�� false=���� */
	bool m_is_better; // ������Ÿ���������� min_max(,)
	/*  baseball.xml���� ITEM_UPGRADE_LOGIC ���� */
	aname32_t m_upgrade_level; // ���׷��̵��� min_max(,)
	/*  �����ð����� �̷��� �ð��� ���õǸ� ���׷��̵�����̴�. */
	SYSTEMTIME m_date_end_upgrade; // ���׷��̵�����Ϸ�ð� min_max(,)
	/*  ���ȣ ������:BACKNUM=���ȣ. ��ŷ������:MARK=NAME. INSERT_TYPE=Q:NAME | BONUS | ADMIN | SHOP */
	aname256_t m_etc_info; // ��Ÿ���� min_max(,)
	/*  �����������ǰ�� ������������ ���� */
	bool m_is_equiped; // �������� min_max(,)
	/*  �Ⱓ���������ǰ�� ��밡���� �ð� */
	SYSTEMTIME m_date_expire; // �Ⱓ���������ǻ��ð� min_max(,)
	/*  �����ѳ�¥ */
	SYSTEMTIME m_date_insert; // �����ѳ�¥ min_max(,)
	/*  �����������ð� */
	SYSTEMTIME m_date_update; // �����Ƚð� min_max(,)
	/*  �������� �����Ȱ�.�Ǵ� ���¡���� �������� */
	int16 m_is_deleted; // �����÷��� min_max(,)
	EItemState m_state; // �����ۻ��� min_max(,)
	/*  �Һ�(����)�ǰ�� ��밡���� ������ ��� Ƚ��. ���(����)�ǰ�� ��������(��ø����) ������������ ���� 0 */
	int16 m_use_count; // ��밡���� ���Ƚ�� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl_Item
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl_Item_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  16 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl_Item
		jEXCEL_TABLE_COMMON_CODE_H_Tbl_Item();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl_Item

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl_Item_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl_Item)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl_Item
enum { eSTRUCT_SIZE_Tbl_Item = sizeof(Tbl_Item) };

struct jEXCEL_LIB_API Tbl_Item_Admin /* ������� */
{
	/*  db pk */
	Tbl_Item_id_t m_db_id; // �����ĺ��� min_max(,)
		typedef Tbl_Item_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  ����������ǰ�� �ش����� �ĺ��� */
	Tbl_Result_id_t m_rid; // ���Ӱ���ĺ��� min_max(,)
	/*  ���Ž� ����� ����ĳ�� */
	real_money_t m_bought_real_money; // ����ĳ�� min_max(,)
	/*  ���Ž� ����� ����Ʈ */
	real_money_t m_bought_point_money; // ��������Ʈ min_max(,)
	/*  ���Ž� ����� ���ӸӴ� */
	game_money_t m_bought_game_money; // ���Ű��ӸӴ� min_max(,)
	/*  ������ȹ���� ���� ( ���������  �Ǵ� ��������  or �̺�Ʈ) */
	EItemBuyType m_item_buy_type; // ���Ż��� min_max(,)
	/*  �������κ��� �����Ѱ�� �����Ǹ����� */
	Sys_Shop_id_t m_shop_id; // �����ǸŹ�ȣ min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl_Item_Admin
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  7 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl_Item_Admin
		jEXCEL_TABLE_COMMON_CODE_H_Tbl_Item_Admin();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl_Item_Admin

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl_Item_Admin)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl_Item_Admin
enum { eSTRUCT_SIZE_Tbl_Item_Admin = sizeof(Tbl_Item_Admin) };

struct jEXCEL_LIB_API Tbl_Package /* ������ ��Ű������Ʈ */
{
	/*  db pk */
	Tbl_Package_id_t m_db_id; // �����ĺ��� min_max(,)
		typedef Tbl_Package_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  Sys_Package_id_t */
	Sys_Package_id_t m_sid_package; // ������ ���������� min_max(,)
	Tbl_User_id_t m_uid; // ������id min_max(,)
	/*  ���ȣ �������϶��� ���ȣ. ��ŷ �������϶��� ��ŷ���ڸ� ����. */
	aname256_t m_etc_info; // ��Ÿ���� min_max(,)
	/*  �����ѳ�¥ */
	SYSTEMTIME m_date_insert; // �����ѳ�¥ min_max(,)
	/*  �����������ð� */
	SYSTEMTIME m_date_update; // �����Ƚð� min_max(,)
	/*  �������� �����Ȱ�.�Ǵ� ���¡���� �������� */
	int16 m_is_deleted; // �����÷��� min_max(,)
	EItemState m_state; // �����ۻ��� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl_Package
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl_Package_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  8 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl_Package
		jEXCEL_TABLE_COMMON_CODE_H_Tbl_Package();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl_Package

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl_Package_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl_Package)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl_Package
enum { eSTRUCT_SIZE_Tbl_Package = sizeof(Tbl_Package) };

struct jEXCEL_LIB_API Tbl_PitcherSkill /* ������� */
{
	Tbl_PitcherSkill_id_t m_db_id; // ������ȣ min_max(,)
		typedef Tbl_PitcherSkill_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	Tbl_User_id_t m_uid; // ������id min_max(,)
	/*  ����Ʈ���� pp_name�̴� */
	Tbl_PlayerPitcher_id_t m_pid; // ��������id min_max(,)
	/*  ���������� */
	EGestureType m_gesture; // ������Ÿ�� min_max(,EGestureType)
	int16 m_is_deleted; // �����÷��� min_max(,)
	/*  ������ ��ȭ���� ����� �ð��� ��� */
	int32 m_exp; // ������ȭ�� ���� �ð� min_max(,)
	/*  ���� ��ȭ������ */
	EPlayerBreakingBall m_type; // ������ȭ������ min_max(,EPlayerBreakingBall)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl_PitcherSkill
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  7 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl_PitcherSkill
		jEXCEL_TABLE_COMMON_CODE_H_Tbl_PitcherSkill();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl_PitcherSkill

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl_PitcherSkill)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl_PitcherSkill
enum { eSTRUCT_SIZE_Tbl_PitcherSkill = sizeof(Tbl_PitcherSkill) };

struct jEXCEL_LIB_API Tbl_PlayerBetter /* ������� */
	:Tbl__PlayerBase
{
	Tbl__PlayerBase* GetBase_Tbl__PlayerBase(){ return static_cast<Tbl__PlayerBase*>(this);}
	/*  0.001 - 0.999 õ������ ǥ�� */
	int16 m_batting_average; // Ÿ�� min_max(0,)
	/*  ����_Ȩ���� */
	int16 m_continue_homerun_count; // ����Ȩ���� min_max(0,)
	/*  ��_Ȩ���� */
	int16 m_homeruntotal_count; // ��_Ȩ���� min_max(0,)
	/*  �̱�Ȩ�� ī��Ʈ */
	int16 m_single_homerun_count; // �̱�Ȩ��ī��Ʈ min_max(0,)
	/*  ����Ȩ�� ī��Ʈ */
	int16 m_tworun_homerun_count; // ����Ȩ��ī��Ʈ min_max(0,)
	/*  ������Ȩ�� ī��Ʈ */
	int16 m_threerun_homerun_count; // ������Ȩ��ī��Ʈ min_max(0,)
	/*  ����Ȩ�� ī��Ʈ */
	int16 m_grandslam_homerun_count; // ����Ȩ��ī��Ʈ min_max(0,)
	/*  �Ϸ�Ÿ ī��Ʈ */
	int16 m_one_hit_count; // �Ϸ�Ÿī��Ʈ min_max(0,)
	/*  �̷�Ÿ ī��Ʈ */
	int16 m_double_hit_count; // �̷�Ÿī��Ʈ min_max(0,)
	/*  ���Ÿ ī��Ʈ */
	int16 m_triple_hit_count; // ���Ÿī��Ʈ min_max(0,)
	/*  �Ŀ� ī��Ʈ */
	int16 m_foul_hit_count; // �Ŀ�ī��Ʈ min_max(0,)
	/*  �ƿ� ī��Ʈ */
	int16 m_out_hit_count; // �ƿ�ī��Ʈ min_max(0,)
	/*  ���� ī��Ʈ */
	int16 m_score_count; // ����ī��Ʈ min_max(0,)
	/*  Ÿ�� ������ ��ų */
	EBatterAbility m_betting_type; // Ÿ��Ÿ�� min_max(,EBatterAbility)
	/*  Ÿ�� �� */
	EBatterForm m_betting_form; // Ÿ���� min_max(,EBatterForm)
	int16 m_better_power; // Ÿ�� �Ŀ� min_max(0,30)
	int16 m_better_focus; // Ÿ�� ���� min_max(0,30)
	int16 m_better_power_buff; // Ÿ�� �Ŀ� ���� min_max(0,30)
	int16 m_better_focus_buff; // Ÿ�� ���� ���� min_max(0,30)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl_PlayerBetter
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  19 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Tbl__PlayerBase::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl_PlayerBetter
		jEXCEL_TABLE_COMMON_CODE_H_Tbl_PlayerBetter();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl_PlayerBetter

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl_PlayerBetter)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl_PlayerBetter
enum { eSTRUCT_SIZE_Tbl_PlayerBetter = sizeof(Tbl_PlayerBetter) };

struct jEXCEL_LIB_API Tbl_PlayerPitcher /* ������� */
	:Tbl__PlayerBase
{
	Tbl__PlayerBase* GetBase_Tbl__PlayerBase(){ return static_cast<Tbl__PlayerBase*>(this);}
	/*  0.001 - 0.999 õ������ ǥ�� */
	int16 m_pitching_average; // ����� min_max(0,)
	/*  �Ǿ�Ÿ�� */
	int16 m_hit_count; // �Ǿ�Ÿ�� min_max(0,)
	/*  Ż������ */
	int16 m_strikeout_count; // Ż������ min_max(0,)
	/*  ��Ȩ���� */
	int16 m_homerun_pitching_count; // ��Ȩ���� min_max(0,)
	/*  ���ӻ����� */
	int16 m_continue_strikeout_count; // ���ӻ����� min_max(0,)
	/*  ������Ȩ���� */
	int16 m_continue_homerun_pitching_count; // ������Ȩ���� min_max(0,)
	/*  ���� ��Ÿ�� ��ų */
	EPitcherAbility m_pitcher_type; // ����Ÿ�� min_max(,EPitcherAbility)
	/*  ���� �� */
	EPitcherForm m_pitcher_form; // ������ min_max(,EPitcherForm)
	int16 m_pitcher_control; // ���� ���� min_max(0,30)
	int16 m_pitcher_ballspeed; // ���� ���� min_max(0,30)
	int16 m_pitcher_control_buff; // ���� ���� ���� min_max(0,30)
	int16 m_pitcher_ballspeed_buff; // ���� ���� ���� min_max(0,30)
	int16 m_pitcher_breakingball_value_buff; // ���� ��ȭ�� ��ġ ���� min_max(0,30)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl_PlayerPitcher
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  13 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Tbl__PlayerBase::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl_PlayerPitcher
		jEXCEL_TABLE_COMMON_CODE_H_Tbl_PlayerPitcher();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl_PlayerPitcher

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl_PlayerPitcher)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl_PlayerPitcher
enum { eSTRUCT_SIZE_Tbl_PlayerPitcher = sizeof(Tbl_PlayerPitcher) };

struct jEXCEL_LIB_API Tbl_Quest /* ������� */
{
	Tbl_Quest_id_t m_db_id; // ������ȣ min_max(,)
		typedef Tbl_Quest_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  ����Ʈ���� pp_name�̴� */
	Sys_Quest_id_t m_quest_sid; // ������ ����Ʈ sid min_max(,)
	Tbl_User_id_t m_uid; // ����id min_max(,)
	/*  ���� ���� ����� */
	SYSTEMTIME m_date_insert; // ��Ͻð� min_max(,)
	/*  �Ϸ�� �ð� */
	SYSTEMTIME m_date_done; // �Ϸ�ð� min_max(,)
	/*  ����Ʈ�� ����� ��ϵ� �Ķ���� */
	aname256_t m_info; // ���� ���� min_max(,)
	int32 m_done_count; // ������ Ƚ�� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl_Quest
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  7 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl_Quest
		jEXCEL_TABLE_COMMON_CODE_H_Tbl_Quest();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl_Quest

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl_Quest)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl_Quest
enum { eSTRUCT_SIZE_Tbl_Quest = sizeof(Tbl_Quest) };

struct jEXCEL_LIB_API Tbl_Result /* ������� */
{
	Tbl_Result_id_t m_db_id; // game������ȣ min_max(,)
		typedef Tbl_Result_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  0=��Ƽ�÷��� 1=�̱��÷��� */
	bool m_is_singlemode; // is_singlemode min_max(,)
	/*  ���� ������ȣ */
	Tbl_User_id_t m_win_uid; // ������ȣ min_max(,)
	/*  ���� */
	Tbl_PlayerBetter_id_t m_win_better; // Ÿ�� pid min_max(,)
	/*  ���� */
	Tbl_PlayerPitcher_id_t m_win_pitcher; // ���� pid min_max(,)
	Tbl_Team_id_t m_win_team; // ��id min_max(,)
	int8 m_win_score; // ���ڽ��ھ� min_max(,)
	/*  �÷��̾�1�� �������ġ( ����Ÿ�ڸ������) */
	int32 m_win_reward_exp; // ���� �������ġ min_max(,)
	/*  ������ӸӴ� */
	game_money_t m_win_reward_gamemoney; // ���� ������ӸӴ� min_max(,)
	/*  ���� ������ȣ */
	Tbl_User_id_t m_lose_uid; // ������ȣ min_max(,)
	/*  ���� */
	Tbl_PlayerBetter_id_t m_lose_better; // Ÿ�� pid min_max(,)
	/*  ���� */
	Tbl_PlayerPitcher_id_t m_lose_pitcher; // ���� pid min_max(,)
	Tbl_Team_id_t m_lose_team; // ������id min_max(,)
	int8 m_lose_score; // ���ڽ��ھ� min_max(,)
	/*  �������ġ */
	int32 m_lose_reward_exp; // ���� �������ġ min_max(,)
	/*  ������ӸӴ� */
	game_money_t m_lose_reward_gamemoney; // ���� ������ӸӴ� min_max(,)
	/*  �÷��� �� �ð�(��) */
	int32 m_play_time_sec; // �÷��̽ð� min_max(,)
	int64 m_pp_point; // �Ǹ��÷�������Ʈ min_max(,)
	/*  �÷��� �ð� (2012-12-15 13:53:15) */
	SYSTEMTIME m_time_end; // ��������ð� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl_Result
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl_Result_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  19 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl_Result
		jEXCEL_TABLE_COMMON_CODE_H_Tbl_Result();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl_Result

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl_Result_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl_Result)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl_Result
enum { eSTRUCT_SIZE_Tbl_Result = sizeof(Tbl_Result) };

struct jEXCEL_LIB_API Tbl_RoundResult /* ������� */
{
	/*  �Ϻ� ��Ƽ�� Ű */
	Tbl_RoundResult_id_t m_db_id; // ������ȣ min_max(,)
		typedef Tbl_RoundResult_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	Tbl_Result_id_t m_grid; // Tbl_Result_M�� ������ȣ min_max(,)
	/*  1���ͽ���. 1~10�� ���� �Ѱ����� ��Ż����� Tbl_Result�� ���� */
	int8 m_round_number; // �����ȣ min_max(,)
	/*  ĳ������ �¿� ���� 1�̸� �¼��� 0�̸� �켱�� */
	bool m_is_left; // ������ �������� ���� min_max(,)
	/*  ����� ������ ���� */
	EPlayerBreakingBall m_used_breakingball; // ������ ��� ���� min_max(,)
	/*  ����� ������ �ӵ� */
	int16 m_used_breakingball_speed; // ������ ��� ������ ���� min_max(,)
	/*  ���ݿ� ������ �� ������ Ư���ɷ� */
	EPitcherAbility m_used_pitcherability; // ����ϰ� �ִ� ������ ��ų(��ȭ�� ����) min_max(,)
	/*  ���� �� ���� Ÿ�̹��� ���� */
	ERhythmJudge m_pitching_rhythm_judge; // ���� �� ���� Ÿ�̹� min_max(,)
	/*  ���ݿ� ������ �� ������ ������ */
	EItemCategoryEquipment m_used_pitcher_itemcategoryequipment; // ������ ����ϰ� �ִ� ������ min_max(,)
	/*  0=������� �ʾ��� 1=��� �Ͽ��� */
	bool m_used_pitcher_counter; // ������ ī���� ��� min_max(,)
	/*  ���ݿ� ������ �� Ÿ���� Ư���ɷ� */
	EBatterAbility m_used_batterability; // ����ϰ� �ִ� Ÿ���� ��ų min_max(,)
	/*  Ÿ�� ��Ʈ�� ����(�Ϲ���Ʈ_��Ʈ����Ʈ_�꽺��_������) */
	EHitType m_used_batting_fullpower; // Ÿ�� ��Ʈ �� Ǯ�Ŀ� ��� min_max(,)
	/*  Ÿ�� �� Ÿ�̹� ����(veryfast_fast_goodfast_perfect_goodslow_slow_veryslow) */
	EHitTimmingType m_batting_timing_judge; // Ÿ�� �� Ÿ�� Ÿ�̹� min_max(,)
	/*  ���ݿ� ������ �� Ÿ���� ������ */
	EItemCategoryEquipment m_used_batter_itemcategoryequipment; // Ÿ���� ����ϰ� �ִ� ������ min_max(,)
	/*  0=������� �ʾ��� 1=��� �Ͽ��� */
	bool m_used_batter_counter; // Ÿ���� ī���� ��� min_max(,)
	/*  ������ */
	Tbl_User_id_t m_uid_attack; // uid_attack min_max(,)
	int8 m_score; // better������ min_max(,)
	/*  bit flag�� ����� ���ڻ��¸� ǥ���Ѵ�. 1��� 2^0 �ִ�� xml����  i_max_runner_per_game=19�̴� */
	int8 m_base_runner_state; // ��������ڼ� min_max(,)
	/*  0=�ƿ� 1�Ϸ�Ÿ 2�̷�Ÿ 3���Ÿ 4�̱�Ȩ�� 5����Ȩ�� 6 */
	EBatterHitType m_hit_type; // ��Ÿ���� min_max(,EBatterHitType)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl_RoundResult
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  19 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl_RoundResult
		jEXCEL_TABLE_COMMON_CODE_H_Tbl_RoundResult();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl_RoundResult

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl_RoundResult)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl_RoundResult
enum { eSTRUCT_SIZE_Tbl_RoundResult = sizeof(Tbl_RoundResult) };

struct jEXCEL_LIB_API Tbl_Team /* ������� */
	:Tbl__BasicScore
{
	Tbl_Team_id_t m_db_id; // ������ȣ min_max(,)
		typedef Tbl_Team_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  ����Ʈ���� pp_name�̴� */
	aname32_t m_name; // ���̸� min_max(,)
	Tbl_User_id_t m_uid; // ����id min_max(,)
	Tbl_PlayerBetter_id_t m_pid_better; // Ÿ�� min_max(,)
	Tbl_PlayerPitcher_id_t m_pid_pitcher; // ���� min_max(,)
	Tbl__BasicScore* GetBase_Tbl__BasicScore(){ return static_cast<Tbl__BasicScore*>(this);}
	/*  �������� �����Ȱ�.�Ǵ� ���¡���� �������� */
	int16 m_is_deleted; // �����÷��� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl_Team
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl_Team_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  6 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Tbl__BasicScore::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl_Team
		jEXCEL_TABLE_COMMON_CODE_H_Tbl_Team();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl_Team

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl_Team_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl_Team)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl_Team
enum { eSTRUCT_SIZE_Tbl_Team = sizeof(Tbl_Team) };

struct jEXCEL_LIB_API Tbl_Title /* ������� */
{
	Tbl_Title_id_t m_db_id; // ������ȣ min_max(,)
		typedef Tbl_Title_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  Īȣ�� ȹ���� ����Ʈ db id */
	Tbl_Quest_id_t m_qid; // ������ ����Ʈ qid min_max(,)
	/*  Ÿ��Ʋ ���� */
	Sys_Title_id_t m_title_sid; // Ÿ��Ʋid min_max(,)
	/*  Ÿ��Ʋ �׷� */
	int32 m_group; // title_group min_max(,)
	/*  ���� Ÿ�� ���� �� ���� */
	EBaseballObjectType m_object_type; // ������ƮŸ�� min_max(,EBaseballObjectType)
	int64 m_oid; // Ojectid min_max(,)
	/*  �ֱپ�����Ʈ�� */
	SYSTEMTIME m_date_update; // �����ð� min_max(,)
	/*  ȹ���� */
	SYSTEMTIME m_date_insert; // ��Ͻð� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl_Title
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl_Title_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  8 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl_Title
		jEXCEL_TABLE_COMMON_CODE_H_Tbl_Title();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl_Title

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl_Title_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl_Title)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl_Title
enum { eSTRUCT_SIZE_Tbl_Title = sizeof(Tbl_Title) };

struct jEXCEL_LIB_API Tbl_User /* ������� */
	:Tbl__BasicScore
{
	/*  db pk �Ǹ����� �� id�� �״�� ��� */
	Tbl_User_id_t m_db_id; // ������ȣ min_max(,)
		typedef Tbl_User_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  ���̽��������� �����г��� */
	aname32_t m_uname; // �г��� min_max(,)
	/*  �����߰��� ������ */
	int32 m_discon_tot; // ��Disconnect�� min_max(,)
	Tbl__BasicScore* GetBase_Tbl__BasicScore(){ return static_cast<Tbl__BasicScore*>(this);}
	/*  ������_Ż���� */
	int16 m_pitcher_tot_strikeout; // Ż������ min_max(,)
	/*  ���������_���� �ַ� ����� �����ΰ� */
	int16 m_pitcher_tot_average_level; // ���������_���� min_max(,)
	/*  Ÿ����_Ȩ�� */
	int16 m_better_tot_homerun; // ��_Ȩ���� min_max(,)
	/*  Ÿ�������_���� */
	int16 m_better_tot__average_level; // Ÿ�������_���� min_max(,)
	/*  ĳ���۱��Ű��� */
	int16 m_cash_item_buy_count; // ĳ���۱��Ű��� min_max(,)
	/*  �������α�ð� */
	SYSTEMTIME m_time_last_login; // �������α�ð� min_max(,)
	/*  ������ �α׾ƿ��ð� */
	SYSTEMTIME m_time_last_logout; // �������α׾ƿ��ð� min_max(,)
	/*  �����⼮�� �ϼ� */
	int16 m_day_continue_attend; // �����⼮�ϼ� min_max(,)
	/*  ���ʰ��ӵ���� */
	SYSTEMTIME m_date_insert; // ��Ͻð� min_max(,)
	/*  �����������ð� */
	SYSTEMTIME m_date_update; // �����Ƚð� min_max(,)
	/*  �⺻�� index */
	Tbl_Team_id_t m_default_tid; // �⺻����ȣ min_max(,)
	/*  �ɼ�(Ŭ�󿡼����Ƿ������ҳ���) */
	aname1024_t m_option; // �ɼ� min_max(,)
	/*  �Ϸ翡 �߱޵� �̱��÷��� �������ġ Ƚ�� */
	int16 m_singleplay_gift_count; // �̱��÷��̺���ī��Ʈ min_max(,)
	/*  �������� �����Ȱ�.�Ǵ� ���¡���� �������� */
	int16 m_is_deleted; // �����÷��� min_max(,)
	int64 m_game_money; // ���ӸӴ� min_max(,)
	/*  Ŭ�� OS ( IOS / ANDROID ) */
	aname32_t m_client_os; // client_os min_max(,)
	/*  Ŭ�� ��Ʈ��(3G, 4G, WIFI) */
	aname32_t m_client_networ; // client_networ min_max(,)
	/*  ��_�÷���_Ÿ��(��) */
	int64 m_playtime_tot; // ��_�÷���_Ÿ�� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumTbl_User
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Tbl_User_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  21 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Tbl__BasicScore::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl_User
		jEXCEL_TABLE_COMMON_CODE_H_Tbl_User();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl_User

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Tbl_User_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Tbl_User)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Tbl_User
enum { eSTRUCT_SIZE_Tbl_User = sizeof(Tbl_User) };


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Tbl
	for_each_nEXCEL_excel_baseball_table_db_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Tbl);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Tbl


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_baseball_table_db_Tbl_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_baseball_table_db_Tbl_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_baseball_table_db_
