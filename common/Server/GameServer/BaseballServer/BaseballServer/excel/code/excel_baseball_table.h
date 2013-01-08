/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_
#define __namespace_nEXCEL___filename_excel_baseball_table_

#include "table_const_excel_baseball_table.h"
// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Base_PlayerStat,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_PlayerCard,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_PlayerLevel,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_PlayerSkillSticker,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_Quest,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_Title,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Base_PlayerStat 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,고유식별ID             ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(name                   ,이름                 ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(better_power           ,타자 파워              ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(better_focus           ,타자 집중              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(pitcher_control        ,투수 제구              ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(pitcher_ballspeed      ,투수 구속              ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(pitcher_breakingball_value,투수 변화구 비거리 보정수치 ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(pitcher_breakingball_type,투수 변화구종류         ,EPlayerBreakingBall          ,7 , EPlayerBreakingBall , EPlayerBreakingBall , e)\

	#endif // for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Base_PlayerStat가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Base_PlayerStat_InheritedTable
	#define for_each_nEXCEL_Sys_Base_PlayerStat_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Base_PlayerStat_InheritedTable


	// ------------------------------------------------------------
	// Sys_Base_PlayerStat가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Base_PlayerStat가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_PlayerCard 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD(FIELD)\
		FIELD(player_leftright       ,좌우 구분              ,bool                         ,1 , bool , bool , b)\
		FIELD(better_form            ,타자 타격폼             ,EBatterForm                  ,2 , EBatterForm , EBatterForm , e)\
		FIELD(pitcher_form           ,투수 투구폼             ,EPitcherForm                 ,3 , EPitcherForm , EPitcherForm , e)\
		FIELD(player_nation          ,출신                 ,EPlayerNationType            ,4 , EPlayerNationType , EPlayerNationType , e)\
		FIELD(player_year            ,활동 연도              ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(player_grade           ,등급                 ,EPlayerGradeType             ,6 , EPlayerGradeType , EPlayerGradeType , e)\
		FIELD(body_type              ,체형                 ,EPlayerBodyType              ,7 , EPlayerBodyType , EPlayerBodyType , e)\
		FIELD(player_level           ,플레이어 레벨            ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(player_type            ,타자투수구분             ,EPlayerType                  ,9 , EPlayerType , EPlayerType , e)\
		FIELD(price_type             ,구매타입               ,EItemPriceType               ,10 , EItemPriceType , EItemPriceType , e)\
		FIELD(price_money            ,필요게임머니             ,int32                        ,11 , int32 , int32 , i32)\
		FIELD(price_cash             ,필요리얼캐쉬             ,int32                        ,12 , int32 , int32 , i32)\
		FIELD(sell_status            ,판매상태               ,EItemSellStatus              ,13 , EItemSellStatus , EItemSellStatus , e)\
		FIELD(sell_start_date        ,판매 시작 일시           ,SYSTEMTIME                   ,14 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(sell_end_date          ,판매 종료 일시           ,SYSTEMTIME                   ,15 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(player_level_min       ,사용레벨MIN            ,int16                        ,16 , int16 , int16 , i16)\
		FIELD(player_level_max       ,사용레벨MAX            ,int16                        ,17 , int16 , int16 , i16)\
		FIELD(sticker_slot_count     ,붙일수있는스티커갯수         ,int8                         ,18 , int8 , int8 , i8)\
		FIELD(skill_sticker          ,기본적으로보유한 특수능력      ,Sys_PlayerSkillSticker_ptr_vec , 19 ,Sys_PlayerSkillSticker_ptr_vec_ref , Sys_PlayerSkillSticker_ptr_vec_ref , ptr_vec)\
		FIELD(player_onoff           ,플레이어의 온오프라인 구별     ,bool                         ,20 , bool , bool , b)\

	#endif // for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_PlayerCard가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_PlayerCard_InheritedTable
	#define for_each_nEXCEL_Sys_PlayerCard_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys_Base_PlayerStat_InheritedTable(FUNC)\
		FUNC(Sys_Base_PlayerStat)\

	#endif // for_each_nEXCEL_Sys_PlayerCard_InheritedTable


	// ------------------------------------------------------------
	// Sys_PlayerCard가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_PlayerCard가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_PlayerCard_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_PlayerLevel 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,고유번호               ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(name                   ,name               ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(level                  ,플레이어레벨             ,int8                         ,2 , int8 , int8 , i8)\
		FIELD(max_exp                ,해당 레벨의 최대 경험치      ,int64                        ,3 , int64 , int64 , i64)\
		FIELD(max_cum_exp            ,해당 레벨의 최대 누적 경험치   ,int64                        ,4 , int64 , int64 , i64)\
		FIELD(better_accuracy_sq     ,타자_square_정확       ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(better_accuracy_op     ,타자_open_정확         ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(better_accuracy_cl     ,타자_close_정확        ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(better_power_sq        ,타자_square_파워       ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(better_power_op        ,타자_open_파워         ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(better_power_cl        ,타자_close_파워        ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(pitcher_speed_ov       ,투수_over_구속         ,float                        ,11 , float , float , f)\
		FIELD(pitcher_speed_tq       ,투수_threequarter_구속 ,float                        ,12 , float , float , f)\
		FIELD(pitcher_speed_sa       ,투수_sidearm_구속      ,float                        ,13 , float , float , f)\
		FIELD(pitcher_speed_un       ,투수_under_구속        ,float                        ,14 , float , float , f)\
		FIELD(pitcher_focus_ov       ,투수_over_제구         ,int16                        ,15 , int16 , int16 , i16)\
		FIELD(pitcher_focus_tq       ,투수_threequarter_제구 ,int16                        ,16 , int16 , int16 , i16)\
		FIELD(pitcher_focus_sa       ,투수_sidearm_제구      ,int16                        ,17 , int16 , int16 , i16)\
		FIELD(pitcher_focus_un       ,투수_under_제구        ,int16                        ,18 , int16 , int16 , i16)\
		FIELD(pitcher_breakingball_ov,투수_over_변화구        ,int16                        ,19 , int16 , int16 , i16)\
		FIELD(pitcher_breakingball_tq,투수_threequarter_변화구 ,int16                       ,20 , int16 , int16 , i16)\
		FIELD(pitcher_breakingball_sa,투수_sidearm_변화구     ,int16                        ,21 , int16 , int16 , i16)\
		FIELD(pitcher_breakingball_un,투수_under_변화구       ,int16                        ,22 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_PlayerLevel가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_PlayerLevel_InheritedTable
	#define for_each_nEXCEL_Sys_PlayerLevel_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_PlayerLevel_InheritedTable


	// ------------------------------------------------------------
	// Sys_PlayerLevel가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_PlayerLevel가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_PlayerLevel_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_PlayerSkillSticker 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD(FIELD)\
		FIELD(better_skill1_type     ,타자특수능력종류           ,EBatterAbility               ,1 , EBatterAbility , EBatterAbility , e)\
		FIELD(Pitcher_skill1_type    ,투수특수능력종류           ,EPitcherAbility              ,2 , EPitcherAbility , EPitcherAbility , e)\
		FIELD(unlock_player_level    ,업그레이드 가능 레벨        ,int8                         ,3 , int8 , int8 , i8)\

	#endif // for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_PlayerSkillSticker가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_PlayerSkillSticker_InheritedTable
	#define for_each_nEXCEL_Sys_PlayerSkillSticker_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys_Base_PlayerStat_InheritedTable(FUNC)\
		FUNC(Sys_Base_PlayerStat)\

	#endif // for_each_nEXCEL_Sys_PlayerSkillSticker_InheritedTable


	// ------------------------------------------------------------
	// Sys_PlayerSkillSticker가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Base_PlayerStat_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_PlayerSkillSticker가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_PlayerSkillSticker_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Quest 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Quest_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Quest_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,고유번호               ,Sys_Quest_id_t               ,0 , Sys_Quest_id_t , uint16 , u16)\
		FIELD(name                   ,퀘스트이름              ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(quest_type             ,퀘스트타입              ,EQuestType                   ,2 , EQuestType , EQuestType , e)\
		FIELD(reward_money           ,보상머니               ,game_money_t                 ,3 , int32 , int32 , i32)\
		FIELD(reward_exp             ,보상경험치              ,int32                        ,4 , int32 , int32 , i32)\
		FIELD(title                  ,보상호칭               ,Sys_Title_ptr                , 5 ,Sys_Title_ptr , Sys_Title_ptr , ptr)\
		FIELD(help                   ,조건설명               ,tname1024_t                  ,6 , tcstr , tcstr , t1024)\
		FIELD(condition_type1        ,조건1타입              ,EQuestConditionType          ,7 , EQuestConditionType , EQuestConditionType , e)\
		FIELD(condition1             ,조건1내용              ,tname1024_t                  ,8 , tcstr , tcstr , t1024)\
		FIELD(condition_value1       ,조건1값               ,int32                        ,9 , int32 , int32 , i32)\
		FIELD(condition_type2        ,조건2타입              ,EQuestConditionType          ,10 , EQuestConditionType , EQuestConditionType , e)\
		FIELD(condition2             ,조건2내용              ,tname1024_t                  ,11 , tcstr , tcstr , t1024)\
		FIELD(condition_value2       ,조건2값               ,int32                        ,12 , int32 , int32 , i32)\
		FIELD(quest_reward_item1     ,보상 아이템 1           ,EItemCategory                ,13 , EItemCategory , EItemCategory , e)\
		FIELD(quest_reward_item_grade1,보상 아이템 1 등급       ,EItemGradeType               ,14 , EItemGradeType , EItemGradeType , e)\
		FIELD(quest_reward_percent1  ,보상 아이템1 확률         ,int16                        ,15 , int16 , int16 , i16)\
		FIELD(quest_reward_item2     ,보상 아이템 2           ,EItemCategory                ,16 , EItemCategory , EItemCategory , e)\
		FIELD(quest_reward_item_grade2,보상 아이템 2 등급       ,EItemGradeType               ,17 , EItemGradeType , EItemGradeType , e)\
		FIELD(quest_reward_percent2  ,보상 아이템2 확률         ,int16                        ,18 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_Quest_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Quest가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Quest_InheritedTable
	#define for_each_nEXCEL_Sys_Quest_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Quest_InheritedTable


	// ------------------------------------------------------------
	// Sys_Quest가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Quest가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Quest_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Quest_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Title 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Title_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Title_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,고유번호               ,Sys_Title_id_t               ,0 , Sys_Title_id_t , uint16 , u16)\
		FIELD(name                   ,칭호이름               ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(group                  ,칭호그룹               ,int32                        ,2 , int32 , int32 , i32)\
		FIELD(object_type            ,부여할객체종류            ,EBaseballObjectType          ,3 , EBaseballObjectType , EBaseballObjectType , e)\
		FIELD(help                   ,설명                 ,tname256_t                   ,4 , tcstr , tcstr , t256)\

	#endif // for_each_nEXCEL_Sys_Title_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Title가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Title_InheritedTable
	#define for_each_nEXCEL_Sys_Title_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Title_InheritedTable


	// ------------------------------------------------------------
	// Sys_Title가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Title_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Title_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Title_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Title가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Title_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Title_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Title_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Title_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Title_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
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



struct jEXCEL_LIB_API Sys_Base_PlayerStat /* 설명없음 */
{
	int16 m_sid; // 고유식별ID min_max(,)
		typedef int16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_sid; }
	void SetPrimaryKey(primary_key_t id) { m_sid = id; }
	/*  영문이름 고유해야함. 이영문이름으로 스트링테이블에서 한글이름검색 */
	tname32_t m_name; // 이름 min_max(,)
	int16 m_better_power; // 타자 파워 min_max(0,30)
	int16 m_better_focus; // 타자 집중 min_max(0,30)
	int16 m_pitcher_control; // 투수 제구 min_max(0,30)
	/*  빨간색 숫자는 마이너스를 뜻함 */
	int16 m_pitcher_ballspeed; // 투수 구속 min_max(-50,50)
	int16 m_pitcher_breakingball_value; // 투수 변화구 비거리 보정수치 min_max(-50,50)
	/*  투수 변화구 */
	EPlayerBreakingBall m_pitcher_breakingball_type; // 투수 변화구종류 min_max(,EPlayerBreakingBall)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Sys_PlayerCard /* 설명없음 */
	:Sys_Base_PlayerStat
{
	Sys_Base_PlayerStat* GetBase_Sys_Base_PlayerStat(){ return static_cast<Sys_Base_PlayerStat*>(this);}
	/*  플레이어의 좌우구분(1=왼쪽 2=오른쪽) */
	bool m_player_leftright; // 좌우 구분 min_max(,)
	/*  타자의 타격폼 */
	EBatterForm m_better_form; // 타자 타격폼 min_max(,EBatterForm)
	/*  투수의 투구폼 */
	EPitcherForm m_pitcher_form; // 투수 투구폼 min_max(,EPitcherForm)
	EPlayerNationType m_player_nation; // 출신 min_max(,EPlayerNationType)
	/*  플레이어 활동연도 */
	int16 m_player_year; // 활동 연도 min_max(1970,2020)
	/*  선수 별 업그레이드 등급 */
	EPlayerGradeType m_player_grade; // 등급 min_max(,EPlayerGradeType)
	EPlayerBodyType m_body_type; // 체형 min_max(,EPlayerBodyType)
	/*  선수 레벨 */
	int16 m_player_level; // 플레이어 레벨 min_max(1,150)
	/*  타자투수구분 */
	EPlayerType m_player_type; // 타자투수구분 min_max(,EPlayerType)
	EItemPriceType m_price_type; // 구매타입 min_max(,EItemPriceType)
	int32 m_price_money; // 필요게임머니 min_max(,)
	int32 m_price_cash; // 필요리얼캐쉬 min_max(,)
	EItemSellStatus m_sell_status; // 판매상태 min_max(,EItemSellStatus)
	/*  판매 시작 일시 */
	SYSTEMTIME m_sell_start_date; // 판매 시작 일시 min_max(,)
	/*  판매 종료 일시 */
	SYSTEMTIME m_sell_end_date; // 판매 종료 일시 min_max(,)
	int16 m_player_level_min; // 사용레벨MIN min_max(,)
	int16 m_player_level_max; // 사용레벨MAX min_max(,)
	int8 m_sticker_slot_count; // 붙일수있는스티커갯수 min_max(1,12)
	/*  Sys_PlayerSkillSticker에서의 name */
	Sys_PlayerSkillSticker_ptr_vec m_skill_sticker_ptr_vec; // 기본적으로보유한 특수능력 min_max(,Sys_PlayerSkillSticker)
	/*  플레이어의 온오프라인 구별(1=온라인 0=오프라인) */
	bool m_player_onoff; // 플레이어의 온오프라인 구별 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Sys_PlayerLevel /* 설명없음 */
{
	/*  고유번호 */
	int16 m_sid; // 고유번호 min_max(,)
	tname32_t m_name; // name min_max(,)
	/*  플레이어레벨 */
	int8 m_level; // 플레이어레벨 min_max(1,100)
		typedef int8 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_level; }
	void SetPrimaryKey(primary_key_t id) { m_level = id; }
	/*  해당 레벨의 최대 경험치 */
	int64 m_max_exp; // 해당 레벨의 최대 경험치 min_max(,)
	/*  해당 레벨의 최대 누적 경험치 */
	int64 m_max_cum_exp; // 해당 레벨의 최대 누적 경험치 min_max(,)
	/*  타자_square_정확 */
	int16 m_better_accuracy_sq; // 타자_square_정확 min_max(,)
	/*  타자_open_정확 */
	int16 m_better_accuracy_op; // 타자_open_정확 min_max(,)
	/*  타자_close_정확 */
	int16 m_better_accuracy_cl; // 타자_close_정확 min_max(,)
	/*  타자_square_파워 */
	int16 m_better_power_sq; // 타자_square_파워 min_max(,)
	/*  타자_open_파워 */
	int16 m_better_power_op; // 타자_open_파워 min_max(,)
	/*  타자_close_파워 */
	int16 m_better_power_cl; // 타자_close_파워 min_max(,)
	/*  투수_over_구속 */
	float m_pitcher_speed_ov; // 투수_over_구속 min_max(,)
	/*  투수_threequarter_구속 */
	float m_pitcher_speed_tq; // 투수_threequarter_구속 min_max(,)
	/*  투수_sidearm_구속 */
	float m_pitcher_speed_sa; // 투수_sidearm_구속 min_max(,)
	/*  투수_under_구속 */
	float m_pitcher_speed_un; // 투수_under_구속 min_max(,)
	/*  투수_over_제구 */
	int16 m_pitcher_focus_ov; // 투수_over_제구 min_max(,)
	/*  투수_threequarter_제구 */
	int16 m_pitcher_focus_tq; // 투수_threequarter_제구 min_max(,)
	/*  투수_sidearm_제구 */
	int16 m_pitcher_focus_sa; // 투수_sidearm_제구 min_max(,)
	/*  투수_under_제구 */
	int16 m_pitcher_focus_un; // 투수_under_제구 min_max(,)
	/*  투수_over_변화구 보유 겟수 */
	int16 m_pitcher_breakingball_ov; // 투수_over_변화구 min_max(,)
	/*  투수_threequarter_변화구 보유 겟수 */
	int16 m_pitcher_breakingball_tq; // 투수_threequarter_변화구 min_max(,)
	/*  투수_sidearm_변화구 보유 겟수 */
	int16 m_pitcher_breakingball_sa; // 투수_sidearm_변화구 min_max(,)
	/*  투수_under_변화구 보유 겟수 */
	int16 m_pitcher_breakingball_un; // 투수_under_변화구 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Sys_PlayerSkillSticker /* 설명없음 */
	:Sys_Base_PlayerStat
{
	Sys_Base_PlayerStat* GetBase_Sys_Base_PlayerStat(){ return static_cast<Sys_Base_PlayerStat*>(this);}
	/*  타자 카드의 스킬 종류 */
	EBatterAbility m_better_skill1_type; // 타자특수능력종류 min_max(,EBatterAbility)
	/*  투수 카드의 스킬 종류 */
	EPitcherAbility m_Pitcher_skill1_type; // 투수특수능력종류 min_max(,EPitcherAbility)
	/*  해당 스킬스티커가 사용될수있는 플레이어레벨 */
	int8 m_unlock_player_level; // 업그레이드 가능 레벨 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Sys_Quest /* 설명없음 */
{
	Sys_Quest_id_t m_sid; // 고유번호 min_max(,)
	/*  클라에 출력할 스트링은 name으로 Sys_StringTable에서 검색해서 출력한다. */
	tname32_t m_name; // 퀘스트이름 min_max(,)
	/*  퀘스트가 어떤 게임 타입인지 (싱글_매치_프랜들리_아이템etc) */
	EQuestType m_quest_type; // 퀘스트타입 min_max(,EQuestType)
	/*  퀘스트 보상 게임머니 */
	game_money_t m_reward_money; // 보상머니 min_max(,)
	/*  디펄트팀의선수들에게exp를보상 */
	int32 m_reward_exp; // 보상경험치 min_max(,)
	/*  Sys_Title테이블의 name필드가 와야한다. */
	Sys_Title_ptr m_title_ptr; // 보상호칭 min_max(,)
	/*  출력용이아니라 개발시 참조용 */
	tname1024_t m_help; // 조건설명 min_max(,)
	EQuestConditionType m_condition_type1; // 조건1타입 min_max(,EQuestConditionType)
	/*  없을 경우 NULL */
	tname1024_t m_condition1; // 조건1내용 min_max(,)
	int32 m_condition_value1; // 조건1값 min_max(,)
	EQuestConditionType m_condition_type2; // 조건2타입 min_max(,EQuestConditionType)
	tname1024_t m_condition2; // 조건2내용 min_max(,)
	int32 m_condition_value2; // 조건2값 min_max(,)
	/*  보상 아이템 1 종류 */
	EItemCategory m_quest_reward_item1; // 보상 아이템 1 min_max(,EItemCategory)
	/*  보상 아이템 1 등급 */
	EItemGradeType m_quest_reward_item_grade1; // 보상 아이템 1 등급 min_max(,EItemGradeType)
	/*  stuff  해당 등급 아이템과 정하여진 게임 머니를 받게 될 확률 천분률 */
	int16 m_quest_reward_percent1; // 보상 아이템1 확률 min_max(0,1000)
	/*  보상 아이템 2 종류 */
	EItemCategory m_quest_reward_item2; // 보상 아이템 2 min_max(,EItemCategory)
	/*  보상 아이템 2 등급 */
	EItemGradeType m_quest_reward_item_grade2; // 보상 아이템 2 등급 min_max(,EItemGradeType)
	/*  stuff  해당 등급 아이템과 정하여진 게임 머니를 받게 될 확률 천분률. -1이면 quest_reward_percent1가 성공하기만 하면 무조건 준다. */
	int16 m_quest_reward_percent2; // 보상 아이템2 확률 min_max(-1,1000)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Quest
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Quest_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  19 };
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
	jLIST_TYPEDEF_vector_typedef(Sys_Quest*,vector_quest_type);
	jLIST_TYPEDEF_map(EQuestType, vector_quest_type_t, m_INDEX_quest_type);
	void init_INDEX_quest_type()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_Quest* p = at(i);
			m_INDEX_quest_type[p->Get_quest_type()].push_back(p);
		}
	}
	jLIST_TYPEDEF_vector_typedef(Sys_Quest*,vector_condition_type1);
	jLIST_TYPEDEF_map(EQuestConditionType, vector_condition_type1_t, m_INDEX_condition_type1);
	void init_INDEX_condition_type1()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_Quest* p = at(i);
			m_INDEX_condition_type1[p->Get_condition_type1()].push_back(p);
		}
	}
	jLIST_TYPEDEF_vector_typedef(Sys_Quest*,vector_condition_type2);
	jLIST_TYPEDEF_map(EQuestConditionType, vector_condition_type2_t, m_INDEX_condition_type2);
	void init_INDEX_condition_type2()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_Quest* p = at(i);
			m_INDEX_condition_type2[p->Get_condition_type2()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Quest>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_quest_type();
		init_INDEX_condition_type1();
		init_INDEX_condition_type2();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Quest g_Sys_Quest;

struct jEXCEL_LIB_API Sys_Title /* 설명없음 */
{
	Sys_Title_id_t m_sid; // 고유번호 min_max(,)
		typedef Sys_Title_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_sid; }
	void SetPrimaryKey(primary_key_t id) { m_sid = id; }
	tname32_t m_name; // 칭호이름 min_max(,)
	/*  그룹이같은 칭호는 중복 소유할수없다. */
	int32 m_group; // 칭호그룹 min_max(,)
	/*  유저 선수 팀 */
	EBaseballObjectType m_object_type; // 부여할객체종류 min_max(,EBaseballObjectType)
	tname256_t m_help; // 설명 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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
