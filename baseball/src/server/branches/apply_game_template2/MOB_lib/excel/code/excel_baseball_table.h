/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_
#define __namespace_nEXCEL___filename_excel_baseball_table_

#include "table_const_excel_baseball_table.h"
// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Base_PlayerStat,�������,nMech,nEXCEL)\
	STRUCT(Sys_PlayerCard,�������,nMech,nEXCEL)\
	STRUCT(Sys_PlayerLevel,�������,nMech,nEXCEL)\
	STRUCT(Sys_PlayerSkillSticker,�������,nMech,nEXCEL)\
	STRUCT(Sys_Quest,�������,nMech,nEXCEL)\
	STRUCT(Sys_Title,�������,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Base_PlayerStat �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,�����ĺ�ID             ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(name                   ,�̸�                 ,aname32_t                    ,1 , acstr , acstr , a32)\
		FIELD(better_power           ,Ÿ�� �Ŀ�              ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(better_focus           ,Ÿ�� ����              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(pitcher_control        ,���� ����              ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(pitcher_ballspeed      ,���� ����              ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(pitcher_breakingball_value,���� ��ȭ�� ��Ÿ� ������ġ ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(pitcher_breakingball_type,���� ��ȭ������         ,EPlayerBreakingBall          ,7 , EPlayerBreakingBall , EPlayerBreakingBall , e)\

	#endif // for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Base_PlayerStat�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Base_PlayerStat_InheritedTable
	#define for_each_nEXCEL_Sys_Base_PlayerStat_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Base_PlayerStat_InheritedTable


	// ------------------------------------------------------------
	// Sys_Base_PlayerStat�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Base_PlayerStat�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_PlayerCard �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD(FIELD)\
		FIELD(player_leftright       ,�¿� ����              ,bool                         ,1 , bool , bool , b)\
		FIELD(better_form            ,Ÿ�� Ÿ����             ,EBatterForm                  ,2 , EBatterForm , EBatterForm , e)\
		FIELD(pitcher_form           ,���� ������             ,EPitcherForm                 ,3 , EPitcherForm , EPitcherForm , e)\
		FIELD(player_nation          ,���                 ,EPlayerNationType            ,4 , EPlayerNationType , EPlayerNationType , e)\
		FIELD(player_year            ,Ȱ�� ����              ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(player_grade           ,���                 ,EPlayerGradeType             ,6 , EPlayerGradeType , EPlayerGradeType , e)\
		FIELD(body_type              ,ü��                 ,EPlayerBodyType              ,7 , EPlayerBodyType , EPlayerBodyType , e)\
		FIELD(player_level           ,�÷��̾� ����            ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(player_type            ,Ÿ����������             ,EPlayerType                  ,9 , EPlayerType , EPlayerType , e)\
		FIELD(price_type             ,����Ÿ��               ,EItemPriceType               ,10 , EItemPriceType , EItemPriceType , e)\
		FIELD(price_money            ,�ʿ���ӸӴ�             ,int32                        ,11 , int32 , int32 , i32)\
		FIELD(price_cash             ,�ʿ丮��ĳ��             ,int32                        ,12 , int32 , int32 , i32)\
		FIELD(sell_status            ,�ǸŻ���               ,EItemSellStatus              ,13 , EItemSellStatus , EItemSellStatus , e)\
		FIELD(sell_start_date        ,�Ǹ� ���� �Ͻ�           ,SYSTEMTIME                   ,14 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(sell_end_date          ,�Ǹ� ���� �Ͻ�           ,SYSTEMTIME                   ,15 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(player_level_min       ,��뷹��MIN            ,int16                        ,16 , int16 , int16 , i16)\
		FIELD(player_level_max       ,��뷹��MAX            ,int16                        ,17 , int16 , int16 , i16)\
		FIELD(sticker_slot_count     ,���ϼ��ִ½�ƼĿ����         ,int8                         ,18 , int8 , int8 , i8)\
		FIELD(skill_sticker          ,�⺻�����κ����� Ư���ɷ�      ,Sys_PlayerSkillSticker_ptr_vec , 19 ,Sys_PlayerSkillSticker_ptr_vec_ref , Sys_PlayerSkillSticker_ptr_vec_ref , ptr_vec)\
		FIELD(player_onoff           ,�÷��̾��� �¿������� ����     ,bool                         ,20 , bool , bool , b)\

	#endif // for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_PlayerCard�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_PlayerCard_InheritedTable
	#define for_each_nEXCEL_Sys_PlayerCard_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys_Base_PlayerStat_InheritedTable(FUNC)\
		FUNC(Sys_Base_PlayerStat)\

	#endif // for_each_nEXCEL_Sys_PlayerCard_InheritedTable


	// ------------------------------------------------------------
	// Sys_PlayerCard�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_PlayerCard�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_PlayerLevel �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,������ȣ               ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(name                   ,name               ,aname32_t                    ,1 , acstr , acstr , a32)\
		FIELD(level                  ,�÷��̾��             ,int8                         ,2 , int8 , int8 , i8)\
		FIELD(max_exp                ,�ش� ������ �ִ� ����ġ      ,int64                        ,3 , int64 , int64 , i64)\
		FIELD(max_cum_exp            ,�ش� ������ �ִ� ���� ����ġ   ,int64                        ,4 , int64 , int64 , i64)\
		FIELD(better_accuracy_sq     ,Ÿ��_square_��Ȯ       ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(better_accuracy_op     ,Ÿ��_open_��Ȯ         ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(better_accuracy_cl     ,Ÿ��_close_��Ȯ        ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(better_power_sq        ,Ÿ��_square_�Ŀ�       ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(better_power_op        ,Ÿ��_open_�Ŀ�         ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(better_power_cl        ,Ÿ��_close_�Ŀ�        ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(pitcher_speed_ov       ,����_over_����         ,float                        ,11 , float , float , f)\
		FIELD(pitcher_speed_tq       ,����_threequarter_���� ,float                        ,12 , float , float , f)\
		FIELD(pitcher_speed_sa       ,����_sidearm_����      ,float                        ,13 , float , float , f)\
		FIELD(pitcher_speed_un       ,����_under_����        ,float                        ,14 , float , float , f)\
		FIELD(pitcher_focus_ov       ,����_over_����         ,int16                        ,15 , int16 , int16 , i16)\
		FIELD(pitcher_focus_tq       ,����_threequarter_���� ,int16                        ,16 , int16 , int16 , i16)\
		FIELD(pitcher_focus_sa       ,����_sidearm_����      ,int16                        ,17 , int16 , int16 , i16)\
		FIELD(pitcher_focus_un       ,����_under_����        ,int16                        ,18 , int16 , int16 , i16)\
		FIELD(pitcher_breakingball_ov,����_over_��ȭ��        ,int16                        ,19 , int16 , int16 , i16)\
		FIELD(pitcher_breakingball_tq,����_threequarter_��ȭ�� ,int16                       ,20 , int16 , int16 , i16)\
		FIELD(pitcher_breakingball_sa,����_sidearm_��ȭ��     ,int16                        ,21 , int16 , int16 , i16)\
		FIELD(pitcher_breakingball_un,����_under_��ȭ��       ,int16                        ,22 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_PlayerLevel�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_PlayerLevel_InheritedTable
	#define for_each_nEXCEL_Sys_PlayerLevel_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_PlayerLevel_InheritedTable


	// ------------------------------------------------------------
	// Sys_PlayerLevel�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_PlayerLevel�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_PlayerSkillSticker �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD(FIELD)\
		FIELD(better_skill1_type     ,Ÿ��Ư���ɷ�����           ,EBatterAbility               ,1 , EBatterAbility , EBatterAbility , e)\
		FIELD(Pitcher_skill1_type    ,����Ư���ɷ�����           ,EPitcherAbility              ,2 , EPitcherAbility , EPitcherAbility , e)\
		FIELD(unlock_player_level    ,���׷��̵� ���� ����        ,int8                         ,3 , int8 , int8 , i8)\

	#endif // for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_PlayerSkillSticker�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_PlayerSkillSticker_InheritedTable
	#define for_each_nEXCEL_Sys_PlayerSkillSticker_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys_Base_PlayerStat_InheritedTable(FUNC)\
		FUNC(Sys_Base_PlayerStat)\

	#endif // for_each_nEXCEL_Sys_PlayerSkillSticker_InheritedTable


	// ------------------------------------------------------------
	// Sys_PlayerSkillSticker�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_PlayerSkillSticker�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Quest �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Quest_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Quest_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,������ȣ               ,Sys_Quest_id_t               ,0 , Sys_Quest_id_t , uint16 , u16)\
		FIELD(name                   ,����Ʈ�̸�              ,aname32_t                    ,1 , acstr , acstr , a32)\
		FIELD(quest_type             ,����ƮŸ��              ,EQuestType                   ,2 , EQuestType , EQuestType , e)\
		FIELD(reward_money           ,����Ӵ�               ,game_money_t                 ,3 , int32 , int32 , i32)\
		FIELD(reward_exp             ,�������ġ              ,int32                        ,4 , int32 , int32 , i32)\
		FIELD(title                  ,����ȣĪ               ,Sys_Title_ptr                , 5 ,Sys_Title_ptr , Sys_Title_ptr , ptr)\
		FIELD(help                   ,���Ǽ���               ,aname1024_t                  ,6 , acstr , acstr , a1024)\
		FIELD(condition_type1        ,����1Ÿ��              ,EQuestConditionType          ,7 , EQuestConditionType , EQuestConditionType , e)\
		FIELD(condition1             ,����1����              ,aname1024_t                  ,8 , acstr , acstr , a1024)\
		FIELD(condition_value1       ,����1��               ,int32                        ,9 , int32 , int32 , i32)\
		FIELD(condition_type2        ,����2Ÿ��              ,EQuestConditionType          ,10 , EQuestConditionType , EQuestConditionType , e)\
		FIELD(condition2             ,����2����              ,aname1024_t                  ,11 , acstr , acstr , a1024)\
		FIELD(condition_value2       ,����2��               ,int32                        ,12 , int32 , int32 , i32)\
		FIELD(condition_type3        ,����3Ÿ��              ,EQuestConditionType          ,13 , EQuestConditionType , EQuestConditionType , e)\
		FIELD(condition3             ,����3����              ,aname1024_t                  ,14 , acstr , acstr , a1024)\
		FIELD(condition_value3       ,����3��               ,int32                        ,15 , int32 , int32 , i32)\
		FIELD(quest_reward_item1     ,���� ������ 1           ,EItemCategory                ,16 , EItemCategory , EItemCategory , e)\
		FIELD(quest_reward_item_grade1,���� ������ 1 ���       ,EItemGradeType               ,17 , EItemGradeType , EItemGradeType , e)\
		FIELD(quest_reward_percent1  ,���� ������1 Ȯ��         ,int16                        ,18 , int16 , int16 , i16)\
		FIELD(quest_reward_item2     ,���� ������ 2           ,EItemCategory                ,19 , EItemCategory , EItemCategory , e)\
		FIELD(quest_reward_item_grade2,���� ������ 2 ���       ,EItemGradeType               ,20 , EItemGradeType , EItemGradeType , e)\
		FIELD(quest_reward_percent2  ,���� ������2 Ȯ��         ,int16                        ,21 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_Quest_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Quest�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Quest_InheritedTable
	#define for_each_nEXCEL_Sys_Quest_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Quest_InheritedTable


	// ------------------------------------------------------------
	// Sys_Quest�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Quest�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Quest_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Title �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Title_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Title_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,������ȣ               ,Sys_Title_id_t               ,0 , Sys_Title_id_t , uint16 , u16)\
		FIELD(name                   ,Īȣ�̸�               ,aname32_t                    ,1 , acstr , acstr , a32)\
		FIELD(group                  ,Īȣ�׷�               ,int32                        ,2 , int32 , int32 , i32)\
		FIELD(object_type            ,�ο��Ұ�ü����            ,EBaseballObjectType          ,3 , EBaseballObjectType , EBaseballObjectType , e)\
		FIELD(help                   ,����                 ,aname256_t                   ,4 , acstr , acstr , a256)\

	#endif // for_each_nEXCEL_Sys_Title_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Title�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Title_InheritedTable
	#define for_each_nEXCEL_Sys_Title_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Title_InheritedTable


	// ------------------------------------------------------------
	// Sys_Title�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Title_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Title_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Title_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Title�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Title_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Title_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Title_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Title_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Title_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	struct Sys_PlayerSkillSticker;
	typedef Sys_PlayerSkillSticker* Sys_PlayerSkillSticker_ptr;
	typedef std::vector<Sys_PlayerSkillSticker_ptr> Sys_PlayerSkillSticker_ptr_vec;
	typedef Sys_PlayerSkillSticker_ptr_vec& Sys_PlayerSkillSticker_ptr_vec_ref;

	struct Sys_Title;
	typedef Sys_Title* Sys_Title_ptr;
	typedef std::vector<Sys_Title_ptr> Sys_Title_ptr_vec;
	typedef Sys_Title_ptr_vec& Sys_Title_ptr_vec_ref;



struct jEXCEL_LIB_API Sys_Base_PlayerStat /* ������� */
{
	int16 m_sid; // �����ĺ�ID min_max(,)
		typedef int16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_sid; }
	void SetPrimaryKey(primary_key_t id) { m_sid = id; }
	/*  �����̸� �����ؾ���. �̿����̸����� ��Ʈ�����̺��� �ѱ��̸��˻� */
	aname32_t m_name; // �̸� min_max(,)
	int16 m_better_power; // Ÿ�� �Ŀ� min_max(0,30)
	int16 m_better_focus; // Ÿ�� ���� min_max(0,30)
	int16 m_pitcher_control; // ���� ���� min_max(0,30)
	/*  ������ ���ڴ� ���̳ʽ��� ���� */
	int16 m_pitcher_ballspeed; // ���� ���� min_max(-50,50)
	int16 m_pitcher_breakingball_value; // ���� ��ȭ�� ��Ÿ� ������ġ min_max(-50,50)
	/*  ���� ��ȭ�� */
	EPlayerBreakingBall m_pitcher_breakingball_type; // ���� ��ȭ������ min_max(,EPlayerBreakingBall)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_Base_PlayerStat
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  8 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Base_PlayerStat
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Base_PlayerStat();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Base_PlayerStat

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Base_PlayerStat)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Base_PlayerStat
enum { eSTRUCT_SIZE_Sys_Base_PlayerStat = sizeof(Sys_Base_PlayerStat) };


struct CSV_Sys_Base_PlayerStat : public nMech::nUtil::jCSV_File<Sys_Base_PlayerStat>
{
	virtual ~CSV_Sys_Base_PlayerStat(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Base_PlayerStat>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Base_PlayerStat g_Sys_Base_PlayerStat;

struct jEXCEL_LIB_API Sys_PlayerCard /* ������� */
	:Sys_Base_PlayerStat
{
	Sys_Base_PlayerStat* GetBase_Sys_Base_PlayerStat(){ return static_cast<Sys_Base_PlayerStat*>(this);}
	/*  �÷��̾��� �¿챸��(1=���� 2=������) */
	bool m_player_leftright; // �¿� ���� min_max(,)
	/*  Ÿ���� Ÿ���� */
	EBatterForm m_better_form; // Ÿ�� Ÿ���� min_max(,EBatterForm)
	/*  ������ ������ */
	EPitcherForm m_pitcher_form; // ���� ������ min_max(,EPitcherForm)
	EPlayerNationType m_player_nation; // ��� min_max(,EPlayerNationType)
	/*  �÷��̾� Ȱ������ */
	int16 m_player_year; // Ȱ�� ���� min_max(1970,2020)
	/*  ���� �� ���׷��̵� ��� */
	EPlayerGradeType m_player_grade; // ��� min_max(,EPlayerGradeType)
	EPlayerBodyType m_body_type; // ü�� min_max(,EPlayerBodyType)
	/*  ���� ���� */
	int16 m_player_level; // �÷��̾� ���� min_max(1,150)
	/*  Ÿ���������� */
	EPlayerType m_player_type; // Ÿ���������� min_max(,EPlayerType)
	EItemPriceType m_price_type; // ����Ÿ�� min_max(,EItemPriceType)
	int32 m_price_money; // �ʿ���ӸӴ� min_max(,)
	int32 m_price_cash; // �ʿ丮��ĳ�� min_max(,)
	EItemSellStatus m_sell_status; // �ǸŻ��� min_max(,EItemSellStatus)
	/*  �Ǹ� ���� �Ͻ� */
	SYSTEMTIME m_sell_start_date; // �Ǹ� ���� �Ͻ� min_max(,)
	/*  �Ǹ� ���� �Ͻ� */
	SYSTEMTIME m_sell_end_date; // �Ǹ� ���� �Ͻ� min_max(,)
	int16 m_player_level_min; // ��뷹��MIN min_max(,)
	int16 m_player_level_max; // ��뷹��MAX min_max(,)
	int8 m_sticker_slot_count; // ���ϼ��ִ½�ƼĿ���� min_max(1,12)
	/*  Sys_PlayerSkillSticker������ name */
	Sys_PlayerSkillSticker_ptr_vec m_skill_sticker_ptr_vec; // �⺻�����κ����� Ư���ɷ� min_max(,Sys_PlayerSkillSticker)
	/*  �÷��̾��� �¿������� ����(1=�¶��� 0=��������) */
	bool m_player_onoff; // �÷��̾��� �¿������� ���� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_PlayerCard
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  20 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Sys_Base_PlayerStat::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_PlayerCard
		jEXCEL_TABLE_COMMON_CODE_H_Sys_PlayerCard();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_PlayerCard

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_PlayerCard)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_PlayerCard
enum { eSTRUCT_SIZE_Sys_PlayerCard = sizeof(Sys_PlayerCard) };


struct CSV_Sys_PlayerCard : public nMech::nUtil::jCSV_File<Sys_PlayerCard>
{
	virtual ~CSV_Sys_PlayerCard(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_PlayerCard>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_PlayerCard g_Sys_PlayerCard;

struct jEXCEL_LIB_API Sys_PlayerLevel /* ������� */
{
	/*  ������ȣ */
	int16 m_sid; // ������ȣ min_max(,)
	aname32_t m_name; // name min_max(,)
	/*  �÷��̾�� */
	int8 m_level; // �÷��̾�� min_max(1,100)
		typedef int8 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_level; }
	void SetPrimaryKey(primary_key_t id) { m_level = id; }
	/*  �ش� ������ �ִ� ����ġ */
	int64 m_max_exp; // �ش� ������ �ִ� ����ġ min_max(,)
	/*  �ش� ������ �ִ� ���� ����ġ */
	int64 m_max_cum_exp; // �ش� ������ �ִ� ���� ����ġ min_max(,)
	/*  Ÿ��_square_��Ȯ */
	int16 m_better_accuracy_sq; // Ÿ��_square_��Ȯ min_max(,)
	/*  Ÿ��_open_��Ȯ */
	int16 m_better_accuracy_op; // Ÿ��_open_��Ȯ min_max(,)
	/*  Ÿ��_close_��Ȯ */
	int16 m_better_accuracy_cl; // Ÿ��_close_��Ȯ min_max(,)
	/*  Ÿ��_square_�Ŀ� */
	int16 m_better_power_sq; // Ÿ��_square_�Ŀ� min_max(,)
	/*  Ÿ��_open_�Ŀ� */
	int16 m_better_power_op; // Ÿ��_open_�Ŀ� min_max(,)
	/*  Ÿ��_close_�Ŀ� */
	int16 m_better_power_cl; // Ÿ��_close_�Ŀ� min_max(,)
	/*  ����_over_���� */
	float m_pitcher_speed_ov; // ����_over_���� min_max(,)
	/*  ����_threequarter_���� */
	float m_pitcher_speed_tq; // ����_threequarter_���� min_max(,)
	/*  ����_sidearm_���� */
	float m_pitcher_speed_sa; // ����_sidearm_���� min_max(,)
	/*  ����_under_���� */
	float m_pitcher_speed_un; // ����_under_���� min_max(,)
	/*  ����_over_���� */
	int16 m_pitcher_focus_ov; // ����_over_���� min_max(,)
	/*  ����_threequarter_���� */
	int16 m_pitcher_focus_tq; // ����_threequarter_���� min_max(,)
	/*  ����_sidearm_���� */
	int16 m_pitcher_focus_sa; // ����_sidearm_���� min_max(,)
	/*  ����_under_���� */
	int16 m_pitcher_focus_un; // ����_under_���� min_max(,)
	/*  ����_over_��ȭ�� ���� �ټ� */
	int16 m_pitcher_breakingball_ov; // ����_over_��ȭ�� min_max(,)
	/*  ����_threequarter_��ȭ�� ���� �ټ� */
	int16 m_pitcher_breakingball_tq; // ����_threequarter_��ȭ�� min_max(,)
	/*  ����_sidearm_��ȭ�� ���� �ټ� */
	int16 m_pitcher_breakingball_sa; // ����_sidearm_��ȭ�� min_max(,)
	/*  ����_under_��ȭ�� ���� �ټ� */
	int16 m_pitcher_breakingball_un; // ����_under_��ȭ�� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_PlayerLevel
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  23 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_PlayerLevel
		jEXCEL_TABLE_COMMON_CODE_H_Sys_PlayerLevel();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_PlayerLevel

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_PlayerLevel)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_PlayerLevel
enum { eSTRUCT_SIZE_Sys_PlayerLevel = sizeof(Sys_PlayerLevel) };


struct CSV_Sys_PlayerLevel : public nMech::nUtil::jCSV_File<Sys_PlayerLevel>
{
	virtual ~CSV_Sys_PlayerLevel(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_PlayerLevel>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_PlayerLevel g_Sys_PlayerLevel;

struct jEXCEL_LIB_API Sys_PlayerSkillSticker /* ������� */
	:Sys_Base_PlayerStat
{
	Sys_Base_PlayerStat* GetBase_Sys_Base_PlayerStat(){ return static_cast<Sys_Base_PlayerStat*>(this);}
	/*  Ÿ�� ī���� ��ų ���� */
	EBatterAbility m_better_skill1_type; // Ÿ��Ư���ɷ����� min_max(,EBatterAbility)
	/*  ���� ī���� ��ų ���� */
	EPitcherAbility m_Pitcher_skill1_type; // ����Ư���ɷ����� min_max(,EPitcherAbility)
	/*  �ش� ��ų��ƼĿ�� ���ɼ��ִ� �÷��̾�� */
	int8 m_unlock_player_level; // ���׷��̵� ���� ���� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_PlayerSkillSticker
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  3 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Sys_Base_PlayerStat::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_PlayerSkillSticker
		jEXCEL_TABLE_COMMON_CODE_H_Sys_PlayerSkillSticker();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_PlayerSkillSticker

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_PlayerSkillSticker)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_PlayerSkillSticker
enum { eSTRUCT_SIZE_Sys_PlayerSkillSticker = sizeof(Sys_PlayerSkillSticker) };


struct CSV_Sys_PlayerSkillSticker : public nMech::nUtil::jCSV_File<Sys_PlayerSkillSticker>
{
	virtual ~CSV_Sys_PlayerSkillSticker(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_PlayerSkillSticker>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_PlayerSkillSticker g_Sys_PlayerSkillSticker;

struct jEXCEL_LIB_API Sys_Quest /* ������� */
{
	Sys_Quest_id_t m_sid; // ������ȣ min_max(,)
	/*  Ŭ�� ����� ��Ʈ���� name���� Sys_StringTable���� �˻��ؼ� ����Ѵ�. */
	aname32_t m_name; // ����Ʈ�̸� min_max(,)
	/*  ����Ʈ�� � ���� Ÿ������ (�̱�_��ġ_�����鸮_������etc) */
	EQuestType m_quest_type; // ����ƮŸ�� min_max(,EQuestType)
	/*  ����Ʈ ���� ���ӸӴ� */
	game_money_t m_reward_money; // ����Ӵ� min_max(,)
	/*  ����Ʈ���Ǽ����鿡��exp������ */
	int32 m_reward_exp; // �������ġ min_max(,)
	/*  Sys_Title���̺��� name�ʵ尡 �;��Ѵ�. */
	Sys_Title_ptr m_title_ptr; // ����ȣĪ min_max(,)
	/*  ��¿��̾ƴ϶� ���߽� ������ */
	aname1024_t m_help; // ���Ǽ��� min_max(,)
	EQuestConditionType m_condition_type1; // ����1Ÿ�� min_max(,EQuestConditionType)
	/*  ���� ��� NULL */
	aname1024_t m_condition1; // ����1���� min_max(,)
	int32 m_condition_value1; // ����1�� min_max(,)
	EQuestConditionType m_condition_type2; // ����2Ÿ�� min_max(,EQuestConditionType)
	aname1024_t m_condition2; // ����2���� min_max(,)
	int32 m_condition_value2; // ����2�� min_max(,)
	EQuestConditionType m_condition_type3; // ����3Ÿ�� min_max(,EQuestConditionType)
	aname1024_t m_condition3; // ����3���� min_max(,)
	int32 m_condition_value3; // ����3�� min_max(,)
	/*  ���� ������ 1 ���� */
	EItemCategory m_quest_reward_item1; // ���� ������ 1 min_max(,EItemCategory)
	/*  ���� ������ 1 ��� */
	EItemGradeType m_quest_reward_item_grade1; // ���� ������ 1 ��� min_max(,EItemGradeType)
	/*  stuff  �ش� ��� �����۰� ���Ͽ��� ���� �Ӵϸ� �ް� �� Ȯ�� õ�з� */
	int16 m_quest_reward_percent1; // ���� ������1 Ȯ�� min_max(0,1000)
	/*  ���� ������ 2 ���� */
	EItemCategory m_quest_reward_item2; // ���� ������ 2 min_max(,EItemCategory)
	/*  ���� ������ 2 ��� */
	EItemGradeType m_quest_reward_item_grade2; // ���� ������ 2 ��� min_max(,EItemGradeType)
	/*  stuff  �ش� ��� �����۰� ���Ͽ��� ���� �Ӵϸ� �ް� �� Ȯ�� õ�з�. -1�̸� quest_reward_percent1�� �����ϱ⸸ �ϸ� ������ �ش�. */
	int16 m_quest_reward_percent2; // ���� ������2 Ȯ�� min_max(-1,1000)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_Quest
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Quest_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  22 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Quest
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Quest();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Quest

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Quest_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Quest)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Quest
enum { eSTRUCT_SIZE_Sys_Quest = sizeof(Sys_Quest) };


struct CSV_Sys_Quest : public nMech::nUtil::jCSV_File<Sys_Quest>
{
	virtual ~CSV_Sys_Quest(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Quest>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Quest g_Sys_Quest;

struct jEXCEL_LIB_API Sys_Title /* ������� */
{
	Sys_Title_id_t m_sid; // ������ȣ min_max(,)
		typedef Sys_Title_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_sid; }
	void SetPrimaryKey(primary_key_t id) { m_sid = id; }
	aname32_t m_name; // Īȣ�̸� min_max(,)
	/*  �׷��̰��� Īȣ�� �ߺ� �����Ҽ�����. */
	int32 m_group; // Īȣ�׷� min_max(,)
	/*  ���� ���� �� */
	EBaseballObjectType m_object_type; // �ο��Ұ�ü���� min_max(,EBaseballObjectType)
	aname256_t m_help; // ���� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_Title
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Title_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  5 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Title
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Title();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Title

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Title_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Title)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Title
enum { eSTRUCT_SIZE_Sys_Title = sizeof(Sys_Title) };


struct CSV_Sys_Title : public nMech::nUtil::jCSV_File<Sys_Title>
{
	virtual ~CSV_Sys_Title(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Title>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Title g_Sys_Title;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_baseball_table_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_baseball_table_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_baseball_table_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_baseball_table_
