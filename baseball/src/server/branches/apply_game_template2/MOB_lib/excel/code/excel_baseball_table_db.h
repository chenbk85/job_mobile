/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_db_
#define __namespace_nEXCEL___filename_excel_baseball_table_db_

#include "table_const_excel_baseball_table_db.h"
// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_db_Tbl_STRUCT_LIST(STRUCT)\
	STRUCT(Tbl__BasicScore,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl__PlayerBase,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_Friend,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_Item,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_Item_Admin,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_Package,구매한 패키지리스트,nMech,nEXCEL)\
	STRUCT(Tbl_PitcherSkill,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_PlayerBetter,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_PlayerPitcher,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_Quest,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_Result,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_RoundResult,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_Team,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_Title,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_User,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Tbl__BasicScore 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD(FIELD)\
		FIELD(win_tot                ,총전적_승              ,int32                        ,0 , int32 , int32 , i32)\
		FIELD(lose_tot               ,총전적_패              ,int32                        ,1 , int32 , int32 , i32)\
		FIELD(win_season             ,시즌전적_승             ,int32                        ,2 , int32 , int32 , i32)\
		FIELD(lose_season            ,시즌전적_패             ,int32                        ,3 , int32 , int32 , i32)\
		FIELD(win_continue           ,연승                 ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(win_tot_single         ,싱글-총전적_승           ,int32                        ,5 , int32 , int32 , i32)\
		FIELD(lose_tot_single        ,싱글-총전적_패           ,int32                        ,6 , int32 , int32 , i32)\
		FIELD(win_season_single      ,싱글-시즌전적_승          ,int32                        ,7 , int32 , int32 , i32)\
		FIELD(lose_season_single     ,싱글-시즌전적_패          ,int32                        ,8 , int32 , int32 , i32)\
		FIELD(win_continue_single    ,싱글-연승패             ,int16                        ,9 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl__BasicScore가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl__BasicScore_InheritedTable
	#define for_each_nEXCEL_Tbl__BasicScore_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl__BasicScore_InheritedTable


	// ------------------------------------------------------------
	// Tbl__BasicScore가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl__BasicScore가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl__PlayerBase 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,PK index           ,Tbl__PlayerBase_id_t         ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(sid                    ,Sys_Player아이디      ,Sys_PlayerCard_id_t          ,1 , Sys_PlayerCard_id_t , uint16 , u16)\
		FIELD(uid                    ,유저번호               ,Tbl_User_id_t                ,2 , int64 , int64 , i)\
		FIELD(pname                  ,닉네임                ,aname32_t                    ,3 , acstr , acstr , a32)\
		FIELD(city                   ,출신국가               ,EPlayerNationType            ,4 , EPlayerNationType , EPlayerNationType , e)\
		FIELD(initial_name           ,이니셜                ,aname32_t                    ,5 , acstr , acstr , a32)\
		FIELD(back_number            ,백넘버                ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(age                    ,나이                 ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(body_type              ,체형                 ,EPlayerBodyType              ,8 , EPlayerBodyType , EPlayerBodyType , e)\
		FIELD(is_left                ,좌우타입               ,bool                         ,9 , bool , bool , b)\
		FIELD(exp                    ,경험치                ,int64                        ,10 , int64 , int64 , i64)\
		FIELD(questcomplete_count    ,퀘스트완료_카운트          ,Sys_Quest_id_t               ,11 , Sys_Quest_id_t , uint16 , u16)\
		FIELD(last_game_result       ,마지막경기id            ,Tbl_Result_id_t              ,12 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(skill_sticker          ,특수능력이름             ,aname1024_t                  ,14 , acstr , acstr , a1024)\
		FIELD(is_deleted             ,is_deleted         ,int16                        ,15 , int16 , int16 , i16)\
		FIELD(date_insert            ,등록시간               ,SYSTEMTIME                   ,16 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(date_update            ,수정된시간              ,SYSTEMTIME                   ,17 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(elo_point              ,ELO_포인트            ,int32                        ,18 , int32 , int32 , i32)\
		FIELD(team                   ,소속팀id              ,Tbl_Team_id_t                ,19 , db_uid_type_ref , db_uid_type_ref , i64)\

	#endif // for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl__PlayerBase가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl__PlayerBase_InheritedTable
	#define for_each_nEXCEL_Tbl__PlayerBase_InheritedTable(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_InheritedTable(FUNC)\
		FUNC(Tbl__BasicScore)\

	#endif // for_each_nEXCEL_Tbl__PlayerBase_InheritedTable


	// ------------------------------------------------------------
	// Tbl__PlayerBase가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl__PlayerBase가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Friend 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,id                 ,Tbl_Friend_id_t              ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(uid                    ,유저번호               ,Tbl_User_id_t                ,1 , int64 , int64 , i)\
		FIELD(uid_fiend              ,친구번호               ,Tbl_User_id_t                ,2 , int64 , int64 , i)\
		FIELD(nic_fiend              ,친구이름               ,aname32_t                    ,3 , acstr , acstr , a32)\
		FIELD(is_blocked             ,is_blocked         ,bool                         ,4 , bool , bool , b)\
		FIELD(is_deleted             ,is_deleted         ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(win_tot                ,친구-총전적_승           ,int32                        ,6 , int32 , int32 , i32)\
		FIELD(lose_tot               ,친구-총전적_패           ,int32                        ,7 , int32 , int32 , i32)\
		FIELD(win_season             ,친구-시즌전적_승          ,int32                        ,8 , int32 , int32 , i32)\
		FIELD(lose_season            ,친구-시즌전적_패          ,int32                        ,9 , int32 , int32 , i32)\
		FIELD(win_continue           ,친구-연승              ,int16                        ,10 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Friend가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Friend_InheritedTable
	#define for_each_nEXCEL_Tbl_Friend_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Friend_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Friend가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Friend가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Friend_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Item 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Item_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Item_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,고유식별자              ,Tbl_Item_id_t                ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(sid                    ,구매한 아이템종류          ,Sys__ItemBase_id_t           ,1 , Sys__ItemBase_id_t , uint16 , u16)\
		FIELD(category               ,대분류                ,EItemCategory                ,2 , EItemCategory , EItemCategory , e)\
		FIELD(uid                    ,소유자id              ,Tbl_User_id_t                ,3 , int64 , int64 , i)\
		FIELD(used_player_id         ,귀속된선수ID            ,Tbl__PlayerBase_id_t         ,4 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(is_better              ,소유한타자투수구분          ,bool                         ,5 , bool , bool , b)\
		FIELD(upgrade_level          ,업그레이드등급            ,aname32_t                    ,6 , acstr , acstr , a32)\
		FIELD(date_end_upgrade       ,업그레이드진행완료시간        ,SYSTEMTIME                   ,7 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(etc_info               ,기타정보               ,aname256_t                   ,8 , acstr , acstr , a256)\
		FIELD(is_equiped             ,장착상태               ,bool                         ,9 , bool , bool , b)\
		FIELD(date_expire            ,기간제아이템의사용시간        ,SYSTEMTIME                   ,10 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(date_insert            ,구매한날짜              ,SYSTEMTIME                   ,11 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(date_update            ,수정된시간              ,SYSTEMTIME                   ,12 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(is_deleted             ,삭제플레그              ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(state                  ,아이템상태              ,EItemState                   ,14 , EItemState , EItemState , e)\
		FIELD(use_count              ,사용가능한 경기횟수         ,int16                        ,15 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Tbl_Item_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Item가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Item_InheritedTable
	#define for_each_nEXCEL_Tbl_Item_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Item_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Item가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Item가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Item_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Item_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Item_Admin 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,고유식별자              ,Tbl_Item_id_t                ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(rid                    ,게임결과식별자            ,Tbl_Result_id_t              ,1 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(bought_real_money      ,구매캐쉬               ,real_money_t                 ,2 , int32 , int32 , i32)\
		FIELD(bought_point_money     ,구매포인트              ,real_money_t                 ,3 , int32 , int32 , i32)\
		FIELD(bought_game_money      ,구매게임머니             ,game_money_t                 ,4 , int32 , int32 , i32)\
		FIELD(item_buy_type          ,구매상태               ,EItemBuyType                 ,5 , EItemBuyType , EItemBuyType , e)\
		FIELD(shop_id                ,상점판매번호             ,Sys_Shop_id_t                ,6 , Sys_Shop_id_t , uint16 , u16)\

	#endif // for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Item_Admin가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Item_Admin_InheritedTable
	#define for_each_nEXCEL_Tbl_Item_Admin_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Item_Admin_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Item_Admin가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Item_Admin가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Item_Admin_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Package 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Package_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Package_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,고유식별자              ,Tbl_Package_id_t             ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(sid_package            ,구매한 아이템종류          ,Sys_Package_id_t             ,1 , Sys_Package_id_t , uint16 , u16)\
		FIELD(uid                    ,소유자id              ,Tbl_User_id_t                ,2 , int64 , int64 , i)\
		FIELD(etc_info               ,기타정보               ,aname256_t                   ,3 , acstr , acstr , a256)\
		FIELD(date_insert            ,구매한날짜              ,SYSTEMTIME                   ,4 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(date_update            ,수정된시간              ,SYSTEMTIME                   ,5 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(is_deleted             ,삭제플레그              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(state                  ,아이템상태              ,EItemState                   ,7 , EItemState , EItemState , e)\

	#endif // for_each_nEXCEL_Tbl_Package_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Package가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Package_InheritedTable
	#define for_each_nEXCEL_Tbl_Package_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Package_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Package가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Package가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Package_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Package_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_PitcherSkill 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,고유번호               ,Tbl_PitcherSkill_id_t        ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(uid                    ,소유자id              ,Tbl_User_id_t                ,1 , int64 , int64 , i)\
		FIELD(pid                    ,소유투수id             ,Tbl_PlayerPitcher_id_t       ,2 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(gesture                ,제스쳐타입              ,EGestureType                 ,3 , EGestureType , EGestureType , e)\
		FIELD(is_deleted             ,삭제플레그              ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(exp                    ,투수변화구 진행 시간        ,int32                        ,5 , int32 , int32 , i32)\
		FIELD(type                   ,투수변화구종류            ,EPlayerBreakingBall          ,6 , EPlayerBreakingBall , EPlayerBreakingBall , e)\

	#endif // for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_PitcherSkill가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_PitcherSkill_InheritedTable
	#define for_each_nEXCEL_Tbl_PitcherSkill_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_PitcherSkill_InheritedTable


	// ------------------------------------------------------------
	// Tbl_PitcherSkill가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_PitcherSkill가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_PitcherSkill_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_PlayerBetter 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD(FIELD)\
		FIELD(batting_average        ,타율                 ,int16                        ,1 , int16 , int16 , i16)\
		FIELD(continue_homerun_count ,연속홈런수              ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(homeruntotal_count     ,총_홈런수              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(single_homerun_count   ,싱글홈런카운트            ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(tworun_homerun_count   ,더블홈런카운트            ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(threerun_homerun_count ,쓰리런홈런카운트           ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(grandslam_homerun_count,만루홈런카운트            ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(one_hit_count          ,일루타카운트             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(double_hit_count       ,이루타카운트             ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(triple_hit_count       ,삼루타카운트             ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(foul_hit_count         ,파울카운트              ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(out_hit_count          ,아웃카운트              ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(score_count            ,점수카운트              ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(betting_type           ,타자타입               ,EBatterAbility               ,14 , EBatterAbility , EBatterAbility , e)\
		FIELD(betting_form           ,타격폼                ,EBatterForm                  ,15 , EBatterForm , EBatterForm , e)\
		FIELD(better_power           ,타자 파워              ,int16                        ,16 , int16 , int16 , i16)\
		FIELD(better_focus           ,타자 집중              ,int16                        ,17 , int16 , int16 , i16)\
		FIELD(better_power_buff      ,타자 파워 버프           ,int16                        ,18 , int16 , int16 , i16)\
		FIELD(better_focus_buff      ,타자 집중 버프           ,int16                        ,19 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_PlayerBetter가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_PlayerBetter_InheritedTable
	#define for_each_nEXCEL_Tbl_PlayerBetter_InheritedTable(FUNC)\
		for_each_nEXCEL_Tbl__PlayerBase_InheritedTable(FUNC)\
		FUNC(Tbl__PlayerBase)\

	#endif // for_each_nEXCEL_Tbl_PlayerBetter_InheritedTable


	// ------------------------------------------------------------
	// Tbl_PlayerBetter가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_PlayerBetter가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_PlayerBetter_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_PlayerPitcher 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD(FIELD)\
		FIELD(pitching_average       ,방어율                ,int16                        ,1 , int16 , int16 , i16)\
		FIELD(hit_count              ,피안타율               ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(strikeout_count        ,탈삼진수               ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(homerun_pitching_count ,피홈런수               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(continue_strikeout_count,연속삼진수             ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(continue_homerun_pitching_count,연속피홈런수     ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(pitcher_type           ,투수타입               ,EPitcherAbility              ,7 , EPitcherAbility , EPitcherAbility , e)\
		FIELD(pitcher_form           ,투구폼                ,EPitcherForm                 ,8 , EPitcherForm , EPitcherForm , e)\
		FIELD(pitcher_control        ,투수 제구              ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(pitcher_ballspeed      ,투수 구속              ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(pitcher_control_buff   ,투수 제구 버프           ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(pitcher_ballspeed_buff ,투수 구속 버프           ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(pitcher_breakingball_value_buff,투수 변화구 수치 버프 ,int16                      ,13 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_PlayerPitcher가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_PlayerPitcher_InheritedTable
	#define for_each_nEXCEL_Tbl_PlayerPitcher_InheritedTable(FUNC)\
		for_each_nEXCEL_Tbl__PlayerBase_InheritedTable(FUNC)\
		FUNC(Tbl__PlayerBase)\

	#endif // for_each_nEXCEL_Tbl_PlayerPitcher_InheritedTable


	// ------------------------------------------------------------
	// Tbl_PlayerPitcher가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl__PlayerBase_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_PlayerPitcher가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_PlayerPitcher_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Quest 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,고유번호               ,Tbl_Quest_id_t               ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(quest_sid              ,수행한 퀘스트 sid        ,Sys_Quest_id_t               ,1 , Sys_Quest_id_t , uint16 , u16)\
		FIELD(uid                    ,유저id               ,Tbl_User_id_t                ,2 , int64 , int64 , i)\
		FIELD(date_insert            ,등록시간               ,SYSTEMTIME                   ,3 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(date_done              ,완료시간               ,SYSTEMTIME                   ,4 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(info                   ,수행 정보              ,aname256_t                   ,5 , acstr , acstr , a256)\
		FIELD(done_count             ,수행한 횟수             ,int32                        ,6 , int32 , int32 , i32)\

	#endif // for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Quest가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Quest_InheritedTable
	#define for_each_nEXCEL_Tbl_Quest_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Quest_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Quest가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Quest가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Quest_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Result 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Result_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Result_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,game고유번호           ,Tbl_Result_id_t              ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(is_singlemode          ,is_singlemode      ,bool                         ,1 , bool , bool , b)\
		FIELD(win_uid                ,고유번호               ,Tbl_User_id_t                ,2 , int64 , int64 , i)\
		FIELD(win_better             ,타자 pid             ,Tbl_PlayerBetter_id_t        ,3 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(win_pitcher            ,투수 pid             ,Tbl_PlayerPitcher_id_t       ,4 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(win_team               ,팀id                ,Tbl_Team_id_t                ,5 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(win_score              ,승자스코어              ,int8                         ,6 , int8 , int8 , i8)\
		FIELD(win_reward_exp         ,승자 보상경험치           ,int32                        ,7 , int32 , int32 , i32)\
		FIELD(win_reward_gamemoney   ,승자 보상게임머니          ,game_money_t                 ,8 , int32 , int32 , i32)\
		FIELD(lose_uid               ,고유번호               ,Tbl_User_id_t                ,9 , int64 , int64 , i)\
		FIELD(lose_better            ,타자 pid             ,Tbl_PlayerBetter_id_t        ,10 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(lose_pitcher           ,투수 pid             ,Tbl_PlayerPitcher_id_t       ,11 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(lose_team              ,패자팀id              ,Tbl_Team_id_t                ,12 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(lose_score             ,패자스코어              ,int8                         ,13 , int8 , int8 , i8)\
		FIELD(lose_reward_exp        ,패자 보상경험치           ,int32                        ,14 , int32 , int32 , i32)\
		FIELD(lose_reward_gamemoney  ,패자 보상게임머니          ,game_money_t                 ,15 , int32 , int32 , i32)\
		FIELD(play_time_sec          ,플레이시간              ,int32                        ,16 , int32 , int32 , i32)\
		FIELD(pp_point               ,피망플러스포인트           ,int64                        ,17 , int64 , int64 , i64)\
		FIELD(time_end               ,게임종료시간             ,SYSTEMTIME                   ,18 , SYSTEMTIME , SYSTEMTIME , tm)\

	#endif // for_each_nEXCEL_Tbl_Result_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Result가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Result_InheritedTable
	#define for_each_nEXCEL_Tbl_Result_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Result_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Result가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Result가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Result_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Result_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_RoundResult 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,고유번호               ,Tbl_RoundResult_id_t         ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(grid                   ,Tbl_Result_M의 고유번호 ,Tbl_Result_id_t              ,1 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(round_number           ,라운드번호              ,int8                         ,2 , int8 , int8 , i8)\
		FIELD(is_left                ,투수의 좌투우투 구분        ,bool                         ,3 , bool , bool , b)\
		FIELD(used_breakingball      ,투수의 사용 구종          ,EPlayerBreakingBall          ,4 , EPlayerBreakingBall , EPlayerBreakingBall , e)\
		FIELD(used_breakingball_speed,투수의 사용 구종의 구속      ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(used_pitcherability    ,사용하고 있는 투수의 스킬(변화구 제외) ,EPitcherAbility          ,6 , EPitcherAbility , EPitcherAbility , e)\
		FIELD(pitching_rhythm_judge  ,투구 시 제구 타이밍        ,ERhythmJudge                 ,7 , ERhythmJudge , ERhythmJudge , e)\
		FIELD(used_pitcher_itemcategoryequipment,투수의 사용하고 있는 아이템 ,EItemCategoryEquipment ,8 , EItemCategoryEquipment , EItemCategoryEquipment , e)\
		FIELD(used_pitcher_counter   ,투수의 카운터 사용         ,bool                         ,9 , bool , bool , b)\
		FIELD(used_batterability     ,사용하고 있는 타자의 스킬     ,EBatterAbility               ,10 , EBatterAbility , EBatterAbility , e)\
		FIELD(used_batting_fullpower ,타자 히트 시 풀파워 사용     ,EHitType                     ,11 , EHitType , EHitType , e)\
		FIELD(batting_timing_judge   ,타격 시 타격 타이밍        ,EHitTimmingType              ,12 , EHitTimmingType , EHitTimmingType , e)\
		FIELD(used_batter_itemcategoryequipment,타자의 사용하고 있는 아이템 ,EItemCategoryEquipment ,13 , EItemCategoryEquipment , EItemCategoryEquipment , e)\
		FIELD(used_batter_counter    ,타자의 카운터 사용         ,bool                         ,14 , bool , bool , b)\
		FIELD(uid_attack             ,uid_attack         ,Tbl_User_id_t                ,15 , int64 , int64 , i)\
		FIELD(score                  ,better의점수          ,int8                         ,16 , int8 , int8 , i8)\
		FIELD(base_runner_state      ,출루한주자수             ,int8                         ,17 , int8 , int8 , i8)\
		FIELD(hit_type               ,안타종류               ,EBatterHitType               ,18 , EBatterHitType , EBatterHitType , e)\

	#endif // for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_RoundResult가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_RoundResult_InheritedTable
	#define for_each_nEXCEL_Tbl_RoundResult_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_RoundResult_InheritedTable


	// ------------------------------------------------------------
	// Tbl_RoundResult가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_RoundResult가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_RoundResult_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Team 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Team_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Team_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,고유번호               ,Tbl_Team_id_t                ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(name                   ,팀이름                ,aname32_t                    ,1 , acstr , acstr , a32)\
		FIELD(uid                    ,유저id               ,Tbl_User_id_t                ,2 , int64 , int64 , i)\
		FIELD(pid_better             ,타자                 ,Tbl_PlayerBetter_id_t        ,3 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(pid_pitcher            ,투수                 ,Tbl_PlayerPitcher_id_t       ,4 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(is_deleted             ,삭제플레그              ,int16                        ,6 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Tbl_Team_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Team가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Team_InheritedTable
	#define for_each_nEXCEL_Tbl_Team_InheritedTable(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_InheritedTable(FUNC)\
		FUNC(Tbl__BasicScore)\

	#endif // for_each_nEXCEL_Tbl_Team_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Team가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Team가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Team_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Team_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_Title 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Title_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_Title_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,고유번호               ,Tbl_Title_id_t               ,0 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(qid                    ,수행한 퀘스트 qid        ,Tbl_Quest_id_t               ,1 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(title_sid              ,타이틀id              ,Sys_Title_id_t               ,2 , Sys_Title_id_t , uint16 , u16)\
		FIELD(group                  ,title_group        ,int32                        ,3 , int32 , int32 , i32)\
		FIELD(object_type            ,오브젝트타입             ,EBaseballObjectType          ,4 , EBaseballObjectType , EBaseballObjectType , e)\
		FIELD(oid                    ,Ojectid            ,int64                        ,5 , int64 , int64 , i64)\
		FIELD(date_update            ,수정시간               ,SYSTEMTIME                   ,6 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(date_insert            ,등록시간               ,SYSTEMTIME                   ,7 , SYSTEMTIME , SYSTEMTIME , tm)\

	#endif // for_each_nEXCEL_Tbl_Title_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_Title가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_Title_InheritedTable
	#define for_each_nEXCEL_Tbl_Title_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Title_InheritedTable


	// ------------------------------------------------------------
	// Tbl_Title가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_Title가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_Title_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_Title_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Tbl_User 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_User_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_User_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,고유번호               ,Tbl_User_id_t                ,0 , int64 , int64 , i)\
		FIELD(uname                  ,닉네임                ,aname32_t                    ,1 , acstr , acstr , a32)\
		FIELD(discon_tot             ,총Disconnect수       ,int32                        ,2 , int32 , int32 , i32)\
		FIELD(pitcher_tot_strikeout  ,탈삼진수               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(pitcher_tot_average_level,투수총평균_레벨         ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(better_tot_homerun     ,총_홈런수              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(better_tot__average_level,타자총평균_레벨         ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(cash_item_buy_count    ,캐쉬템구매갯수            ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(time_last_login        ,마지막로긴시간            ,SYSTEMTIME                   ,9 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(time_last_logout       ,마지막로그아웃시간          ,SYSTEMTIME                   ,10 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(day_continue_attend    ,연속출석일수             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(date_insert            ,등록시간               ,SYSTEMTIME                   ,12 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(date_update            ,수정된시간              ,SYSTEMTIME                   ,13 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(default_tid            ,기본팀번호              ,Tbl_Team_id_t                ,14 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(option                 ,옵션                 ,aname1024_t                  ,15 , acstr , acstr , a1024)\
		FIELD(singleplay_gift_count  ,싱글플레이보상카운트         ,int16                        ,16 , int16 , int16 , i16)\
		FIELD(is_deleted             ,삭제플레그              ,int16                        ,17 , int16 , int16 , i16)\
		FIELD(game_money             ,게임머니               ,int64                        ,18 , int64 , int64 , i64)\
		FIELD(client_os              ,client_os          ,aname32_t                    ,19 , acstr , acstr , a32)\
		FIELD(client_networ          ,client_networ      ,aname32_t                    ,20 , acstr , acstr , a32)\
		FIELD(playtime_tot           ,총_플레이_타임           ,int64                        ,21 , int64 , int64 , i64)\

	#endif // for_each_nEXCEL_Tbl_User_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_User가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_User_InheritedTable
	#define for_each_nEXCEL_Tbl_User_InheritedTable(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_InheritedTable(FUNC)\
		FUNC(Tbl__BasicScore)\

	#endif // for_each_nEXCEL_Tbl_User_InheritedTable


	// ------------------------------------------------------------
	// Tbl_User가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_User_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_User_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl__BasicScore_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Tbl_User_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Tbl_User가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_User_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Tbl_User_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Tbl_User_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Tbl_User_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Tbl_User_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{



struct jEXCEL_LIB_API Tbl__BasicScore /* 설명없음 */
{
	/*  토탈 승 카운트 */
	int32 m_win_tot; // 총전적_승 min_max(0,)
	/*  토탈 패 카운트 */
	int32 m_lose_tot; // 총전적_패 min_max(0,)
	/*  시즌 승 카운트(3개월) */
	int32 m_win_season; // 시즌전적_승 min_max(0,)
	/*  시즌 패 카운트(3개월) */
	int32 m_lose_season; // 시즌전적_패 min_max(0,)
	/*  연속으로 승리한 개수. 음수면 연패 */
	int16 m_win_continue; // 연승 min_max(,)
	/*  토탈 승 카운트 */
	int32 m_win_tot_single; // 싱글-총전적_승 min_max(0,)
	/*  토탈 패 카운트 */
	int32 m_lose_tot_single; // 싱글-총전적_패 min_max(0,)
	/*  시즌 승 카운트(3개월) */
	int32 m_win_season_single; // 싱글-시즌전적_승 min_max(0,)
	/*  시즌 패 카운트(3개월) */
	int32 m_lose_season_single; // 싱글-시즌전적_패 min_max(0,)
	/*  연속으로 승리한 개수. 음수면 연패 */
	int16 m_win_continue_single; // 싱글-연승패 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Tbl__PlayerBase /* 설명없음 */
	:Tbl__BasicScore
{
	/*  선수 database table PK */
	Tbl__PlayerBase_id_t m_db_id; // PK index min_max(,)
		typedef Tbl__PlayerBase_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  구매한 선수카드의 번호(Sys_Player의 sid) 값이 0 이면 가상선수 */
	Sys_PlayerCard_id_t m_sid; // Sys_Player아이디 min_max(,)
	Tbl_User_id_t m_uid; // 유저번호 min_max(,)
	aname32_t m_pname; // 닉네임 min_max(,)
	/*  캐주얼야구 게임기획서 3차 (20111031).docx참조 */
	EPlayerNationType m_city; // 출신국가 min_max(,EPlayerNationType)
	/*  생성시 세팅. 등뒤의이니셜글자. 중복가능 */
	aname32_t m_initial_name; // 이니셜 min_max(,)
	/*  생성시 세팅. 변경아이템으로 변경가능 */
	int16 m_back_number; // 백넘버 min_max(,)
	/*  생성시 세팅. */
	int16 m_age; // 나이 min_max(1,999)
	EPlayerBodyType m_body_type; // 체형 min_max(,EPlayerBodyType)
	/*  캐릭터의 좌우 구분 1이면 좌선수 0이면 우선수 */
	bool m_is_left; // 좌우타입 min_max(,)
	/*  레벨은 경험치에 해당하는 Sys_PlayerLevel의 값에 따라 결정 */
	int64 m_exp; // 경험치 min_max(,)
	/*  완료 퀘스트 카운트 */
	Sys_Quest_id_t m_questcomplete_count; // 퀘스트완료_카운트 min_max(,)
	/*  마지막으로 플레이한 경기결과 식별자 */
	Tbl_Result_id_t m_last_game_result; // 마지막경기id min_max(,)
	Tbl__BasicScore* GetBase_Tbl__BasicScore(){ return static_cast<Tbl__BasicScore*>(this);}
	/*  Sys_PlayeSkillSticker에서의   semicolon로 구분되어 여러개입력 */
	aname1024_t m_skill_sticker; // 특수능력이름 min_max(0,)
	int16 m_is_deleted; // is_deleted min_max(,)
	/*  최초게임등록일 */
	SYSTEMTIME m_date_insert; // 등록시간 min_max(,)
	/*  마지막수정시간 */
	SYSTEMTIME m_date_update; // 수정된시간 min_max(,)
	/*  경기마다 캐릭터에 갱신되는 매칭용 포인트 */
	int32 m_elo_point; // ELO_포인트 min_max(1,10000)
	/*  소속된 팀번호 */
	Tbl_Team_id_t m_team; // 소속팀id min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Tbl_Friend /* 설명없음 */
{
	Tbl_Friend_id_t m_db_id; // id min_max(,)
		typedef Tbl_Friend_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	Tbl_User_id_t m_uid; // 유저번호 min_max(,)
	Tbl_User_id_t m_uid_fiend; // 친구번호 min_max(,)
	aname32_t m_nic_fiend; // 친구이름 min_max(,)
	/*  블랙리스트이냐? */
	bool m_is_blocked; // is_blocked min_max(,)
	int16 m_is_deleted; // is_deleted min_max(,)
	/*  토탈 승 카운트 */
	int32 m_win_tot; // 친구-총전적_승 min_max(0,)
	/*  토탈 패 카운트 */
	int32 m_lose_tot; // 친구-총전적_패 min_max(0,)
	/*  시즌 승 카운트(3개월) */
	int32 m_win_season; // 친구-시즌전적_승 min_max(0,)
	/*  시즌 패 카운트(3개월) */
	int32 m_lose_season; // 친구-시즌전적_패 min_max(0,)
	/*  연속으로 승리한 개수. 음수면 연패 */
	int16 m_win_continue; // 친구-연승 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Tbl_Item /* 설명없음 */
{
	/*  db pk */
	Tbl_Item_id_t m_db_id; // 고유식별자 min_max(,)
		typedef Tbl_Item_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  Sys__ItemBase_id_t */
	Sys__ItemBase_id_t m_sid; // 구매한 아이템종류 min_max(,)
	/*  장비 스텁 소비 구분 */
	EItemCategory m_category; // 대분류 min_max(,EItemCategory)
	Tbl_User_id_t m_uid; // 소유자id min_max(,)
	/*  귀속된 선수id이며 소모용아이템은 특별히귀속되지않고쓴다.캐쉬인벤 or 게임인벤 환불여부가 결정된다 */
	Tbl__PlayerBase_id_t m_used_player_id; // 귀속된선수ID min_max(,)
	/*  true=타자 false=투수 */
	bool m_is_better; // 소유한타자투수구분 min_max(,)
	/*  baseball.xml에서 ITEM_UPGRADE_LOGIC 참조 */
	aname32_t m_upgrade_level; // 업그레이드등급 min_max(,)
	/*  현제시간보다 미래의 시간이 세팅되면 업그레이드상태이다. */
	SYSTEMTIME m_date_end_upgrade; // 업그레이드진행완료시간 min_max(,)
	/*  등번호 아이템:BACKNUM=등번호. 마킹아이템:MARK=NAME. INSERT_TYPE=Q:NAME | BONUS | ADMIN | SHOP */
	aname256_t m_etc_info; // 기타정보 min_max(,)
	/*  장착아이템의경우 장착상태인지 여부 */
	bool m_is_equiped; // 장착상태 min_max(,)
	/*  기간제아이템의경우 사용가능한 시간 */
	SYSTEMTIME m_date_expire; // 기간제아이템의사용시간 min_max(,)
	/*  구매한날짜 */
	SYSTEMTIME m_date_insert; // 구매한날짜 min_max(,)
	/*  마지막수정시간 */
	SYSTEMTIME m_date_update; // 수정된시간 min_max(,)
	/*  아이템이 삭제된것.또는 어뷰징으로 제제상태 */
	int16 m_is_deleted; // 삭제플레그 min_max(,)
	EItemState m_state; // 아이템상태 min_max(,)
	/*  소비(컨슘)의경우 사용가능한 게임의 경기 횟수. 재료(스텁)의경우 보유갯수(중첩갯수) 장착아이템은 값이 0 */
	int16 m_use_count; // 사용가능한 경기횟수 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Tbl_Item_Admin /* 설명없음 */
{
	/*  db pk */
	Tbl_Item_id_t m_db_id; // 고유식별자 min_max(,)
		typedef Tbl_Item_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  보상아이템의경우 해당경기결과 식별자 */
	Tbl_Result_id_t m_rid; // 게임결과식별자 min_max(,)
	/*  구매시 사용한 리얼캐쉬 */
	real_money_t m_bought_real_money; // 구매캐쉬 min_max(,)
	/*  구매시 사용한 포인트 */
	real_money_t m_bought_point_money; // 구매포인트 min_max(,)
	/*  구매시 사용한 게임머니 */
	game_money_t m_bought_game_money; // 구매게임머니 min_max(,)
	/*  아이템획득경로 정보 ( 보상아이템  또는 상점구매  or 이벤트) */
	EItemBuyType m_item_buy_type; // 구매상태 min_max(,)
	/*  상점으로부터 구매한경우 상점판매정보 */
	Sys_Shop_id_t m_shop_id; // 상점판매번호 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Tbl_Package /* 구매한 패키지리스트 */
{
	/*  db pk */
	Tbl_Package_id_t m_db_id; // 고유식별자 min_max(,)
		typedef Tbl_Package_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  Sys_Package_id_t */
	Sys_Package_id_t m_sid_package; // 구매한 아이템종류 min_max(,)
	Tbl_User_id_t m_uid; // 소유자id min_max(,)
	/*  등번호 아이템일때는 등번호. 마킹 아이템일때는 마킹글자를 저장. */
	aname256_t m_etc_info; // 기타정보 min_max(,)
	/*  구매한날짜 */
	SYSTEMTIME m_date_insert; // 구매한날짜 min_max(,)
	/*  마지막수정시간 */
	SYSTEMTIME m_date_update; // 수정된시간 min_max(,)
	/*  아이템이 삭제된것.또는 어뷰징으로 제제상태 */
	int16 m_is_deleted; // 삭제플레그 min_max(,)
	EItemState m_state; // 아이템상태 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Tbl_PitcherSkill /* 설명없음 */
{
	Tbl_PitcherSkill_id_t m_db_id; // 고유번호 min_max(,)
		typedef Tbl_PitcherSkill_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	Tbl_User_id_t m_uid; // 소유자id min_max(,)
	/*  디펄트명은 pp_name이다 */
	Tbl_PlayerPitcher_id_t m_pid; // 소유투수id min_max(,)
	/*  제스쳐종류 */
	EGestureType m_gesture; // 제스쳐타입 min_max(,EGestureType)
	int16 m_is_deleted; // 삭제플레그 min_max(,)
	/*  각각의 변화구에 진행된 시간을 기록 */
	int32 m_exp; // 투수변화구 진행 시간 min_max(,)
	/*  투수 변화구종류 */
	EPlayerBreakingBall m_type; // 투수변화구종류 min_max(,EPlayerBreakingBall)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Tbl_PlayerBetter /* 설명없음 */
	:Tbl__PlayerBase
{
	Tbl__PlayerBase* GetBase_Tbl__PlayerBase(){ return static_cast<Tbl__PlayerBase*>(this);}
	/*  0.001 - 0.999 천분율로 표시 */
	int16 m_batting_average; // 타율 min_max(0,)
	/*  연속_홈런수 */
	int16 m_continue_homerun_count; // 연속홈런수 min_max(0,)
	/*  총_홈런수 */
	int16 m_homeruntotal_count; // 총_홈런수 min_max(0,)
	/*  싱글홈런 카운트 */
	int16 m_single_homerun_count; // 싱글홈런카운트 min_max(0,)
	/*  더블홈런 카운트 */
	int16 m_tworun_homerun_count; // 더블홈런카운트 min_max(0,)
	/*  쓰리런홈런 카운트 */
	int16 m_threerun_homerun_count; // 쓰리런홈런카운트 min_max(0,)
	/*  만루홈런 카운트 */
	int16 m_grandslam_homerun_count; // 만루홈런카운트 min_max(0,)
	/*  일루타 카운트 */
	int16 m_one_hit_count; // 일루타카운트 min_max(0,)
	/*  이루타 카운트 */
	int16 m_double_hit_count; // 이루타카운트 min_max(0,)
	/*  삼루타 카운트 */
	int16 m_triple_hit_count; // 삼루타카운트 min_max(0,)
	/*  파울 카운트 */
	int16 m_foul_hit_count; // 파울카운트 min_max(0,)
	/*  아웃 카운트 */
	int16 m_out_hit_count; // 아웃카운트 min_max(0,)
	/*  점수 카운트 */
	int16 m_score_count; // 점수카운트 min_max(0,)
	/*  타자 대투수 스킬 */
	EBatterAbility m_betting_type; // 타자타입 min_max(,EBatterAbility)
	/*  타자 폼 */
	EBatterForm m_betting_form; // 타격폼 min_max(,EBatterForm)
	int16 m_better_power; // 타자 파워 min_max(0,30)
	int16 m_better_focus; // 타자 집중 min_max(0,30)
	int16 m_better_power_buff; // 타자 파워 버프 min_max(0,30)
	int16 m_better_focus_buff; // 타자 집중 버프 min_max(0,30)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Tbl_PlayerPitcher /* 설명없음 */
	:Tbl__PlayerBase
{
	Tbl__PlayerBase* GetBase_Tbl__PlayerBase(){ return static_cast<Tbl__PlayerBase*>(this);}
	/*  0.001 - 0.999 천분율로 표시 */
	int16 m_pitching_average; // 방어율 min_max(0,)
	/*  피안타율 */
	int16 m_hit_count; // 피안타율 min_max(0,)
	/*  탈삼진수 */
	int16 m_strikeout_count; // 탈삼진수 min_max(0,)
	/*  피홈런수 */
	int16 m_homerun_pitching_count; // 피홈런수 min_max(0,)
	/*  연속삼진수 */
	int16 m_continue_strikeout_count; // 연속삼진수 min_max(0,)
	/*  연속피홈런수 */
	int16 m_continue_homerun_pitching_count; // 연속피홈런수 min_max(0,)
	/*  투수 대타자 스킬 */
	EPitcherAbility m_pitcher_type; // 투수타입 min_max(,EPitcherAbility)
	/*  투수 폼 */
	EPitcherForm m_pitcher_form; // 투구폼 min_max(,EPitcherForm)
	int16 m_pitcher_control; // 투수 제구 min_max(0,30)
	int16 m_pitcher_ballspeed; // 투수 구속 min_max(0,30)
	int16 m_pitcher_control_buff; // 투수 제구 버프 min_max(0,30)
	int16 m_pitcher_ballspeed_buff; // 투수 구속 버프 min_max(0,30)
	int16 m_pitcher_breakingball_value_buff; // 투수 변화구 수치 버프 min_max(0,30)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Tbl_Quest /* 설명없음 */
{
	Tbl_Quest_id_t m_db_id; // 고유번호 min_max(,)
		typedef Tbl_Quest_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  디펄트명은 pp_name이다 */
	Sys_Quest_id_t m_quest_sid; // 수행한 퀘스트 sid min_max(,)
	Tbl_User_id_t m_uid; // 유저id min_max(,)
	/*  최초 수행 등록일 */
	SYSTEMTIME m_date_insert; // 등록시간 min_max(,)
	/*  완료시 시간 */
	SYSTEMTIME m_date_done; // 완료시간 min_max(,)
	/*  퀘스트별 수행시 기록될 파라미터 */
	aname256_t m_info; // 수행 정보 min_max(,)
	int32 m_done_count; // 수행한 횟수 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Tbl_Result /* 설명없음 */
{
	Tbl_Result_id_t m_db_id; // game고유번호 min_max(,)
		typedef Tbl_Result_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  0=멀티플레이 1=싱글플레이 */
	bool m_is_singlemode; // is_singlemode min_max(,)
	/*  승자 고유번호 */
	Tbl_User_id_t m_win_uid; // 고유번호 min_max(,)
	/*  승자 */
	Tbl_PlayerBetter_id_t m_win_better; // 타자 pid min_max(,)
	/*  승자 */
	Tbl_PlayerPitcher_id_t m_win_pitcher; // 투수 pid min_max(,)
	Tbl_Team_id_t m_win_team; // 팀id min_max(,)
	int8 m_win_score; // 승자스코어 min_max(,)
	/*  플레이어1의 보상경험치( 투수타자모두지급) */
	int32 m_win_reward_exp; // 승자 보상경험치 min_max(,)
	/*  보상게임머니 */
	game_money_t m_win_reward_gamemoney; // 승자 보상게임머니 min_max(,)
	/*  패자 고유번호 */
	Tbl_User_id_t m_lose_uid; // 고유번호 min_max(,)
	/*  패자 */
	Tbl_PlayerBetter_id_t m_lose_better; // 타자 pid min_max(,)
	/*  패자 */
	Tbl_PlayerPitcher_id_t m_lose_pitcher; // 투수 pid min_max(,)
	Tbl_Team_id_t m_lose_team; // 패자팀id min_max(,)
	int8 m_lose_score; // 패자스코어 min_max(,)
	/*  보상경험치 */
	int32 m_lose_reward_exp; // 패자 보상경험치 min_max(,)
	/*  보상게임머니 */
	game_money_t m_lose_reward_gamemoney; // 패자 보상게임머니 min_max(,)
	/*  플레이 한 시간(초) */
	int32 m_play_time_sec; // 플레이시간 min_max(,)
	int64 m_pp_point; // 피망플러스포인트 min_max(,)
	/*  플레이 시간 (2012-12-15 13:53:15) */
	SYSTEMTIME m_time_end; // 게임종료시간 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Tbl_RoundResult /* 설명없음 */
{
	/*  일별 파티션 키 */
	Tbl_RoundResult_id_t m_db_id; // 고유번호 min_max(,)
		typedef Tbl_RoundResult_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	Tbl_Result_id_t m_grid; // Tbl_Result_M의 고유번호 min_max(,)
	/*  1부터시작. 1~10은 라운드 한게임의 토탈집계는 Tbl_Result에 저장 */
	int8 m_round_number; // 라운드번호 min_max(,)
	/*  캐릭터의 좌우 구분 1이면 좌선수 0이면 우선수 */
	bool m_is_left; // 투수의 좌투우투 구분 min_max(,)
	/*  사용한 구종의 종류 */
	EPlayerBreakingBall m_used_breakingball; // 투수의 사용 구종 min_max(,)
	/*  사용한 구종의 속도 */
	int16 m_used_breakingball_speed; // 투수의 사용 구종의 구속 min_max(,)
	/*  스텟에 영향을 준 투수의 특수능력 */
	EPitcherAbility m_used_pitcherability; // 사용하고 있는 투수의 스킬(변화구 제외) min_max(,)
	/*  투구 시 제구 타이밍의 종류 */
	ERhythmJudge m_pitching_rhythm_judge; // 투구 시 제구 타이밍 min_max(,)
	/*  스텟에 영향을 준 투수의 아이템 */
	EItemCategoryEquipment m_used_pitcher_itemcategoryequipment; // 투수의 사용하고 있는 아이템 min_max(,)
	/*  0=사용하지 않앗음 1=사용 하였음 */
	bool m_used_pitcher_counter; // 투수의 카운터 사용 min_max(,)
	/*  스텟에 영향을 준 타자의 특수능력 */
	EBatterAbility m_used_batterability; // 사용하고 있는 타자의 스킬 min_max(,)
	/*  타자 히트의 종류(일반히트_스트롱히트_헛스윙_대기상태) */
	EHitType m_used_batting_fullpower; // 타자 히트 시 풀파워 사용 min_max(,)
	/*  타격 시 타이밍 종류(veryfast_fast_goodfast_perfect_goodslow_slow_veryslow) */
	EHitTimmingType m_batting_timing_judge; // 타격 시 타격 타이밍 min_max(,)
	/*  스텟에 영향을 준 타자의 아이템 */
	EItemCategoryEquipment m_used_batter_itemcategoryequipment; // 타자의 사용하고 있는 아이템 min_max(,)
	/*  0=사용하지 않앗음 1=사용 하였음 */
	bool m_used_batter_counter; // 타자의 카운터 사용 min_max(,)
	/*  공격자 */
	Tbl_User_id_t m_uid_attack; // uid_attack min_max(,)
	int8 m_score; // better의점수 min_max(,)
	/*  bit flag로 출루한 주자상태를 표시한다. 1루는 2^0 최대는 xml에서  i_max_runner_per_game=19이다 */
	int8 m_base_runner_state; // 출루한주자수 min_max(,)
	/*  0=아웃 1일루타 2이루타 3삼루타 4싱글홈런 5더블홈런 6 */
	EBatterHitType m_hit_type; // 안타종류 min_max(,EBatterHitType)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Tbl_Team /* 설명없음 */
	:Tbl__BasicScore
{
	Tbl_Team_id_t m_db_id; // 고유번호 min_max(,)
		typedef Tbl_Team_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  디펄트명은 pp_name이다 */
	aname32_t m_name; // 팀이름 min_max(,)
	Tbl_User_id_t m_uid; // 유저id min_max(,)
	Tbl_PlayerBetter_id_t m_pid_better; // 타자 min_max(,)
	Tbl_PlayerPitcher_id_t m_pid_pitcher; // 투수 min_max(,)
	Tbl__BasicScore* GetBase_Tbl__BasicScore(){ return static_cast<Tbl__BasicScore*>(this);}
	/*  아이템이 삭제된것.또는 어뷰징으로 제제상태 */
	int16 m_is_deleted; // 삭제플레그 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Tbl_Title /* 설명없음 */
{
	Tbl_Title_id_t m_db_id; // 고유번호 min_max(,)
		typedef Tbl_Title_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  칭호를 획득한 퀘스트 db id */
	Tbl_Quest_id_t m_qid; // 수행한 퀘스트 qid min_max(,)
	/*  타이틀 정보 */
	Sys_Title_id_t m_title_sid; // 타이틀id min_max(,)
	/*  타이틀 그룹 */
	int32 m_group; // title_group min_max(,)
	/*  유저 타자 투수 팀 구분 */
	EBaseballObjectType m_object_type; // 오브젝트타입 min_max(,EBaseballObjectType)
	int64 m_oid; // Ojectid min_max(,)
	/*  최근업데이트일 */
	SYSTEMTIME m_date_update; // 수정시간 min_max(,)
	/*  획득일 */
	SYSTEMTIME m_date_insert; // 등록시간 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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

struct jEXCEL_LIB_API Tbl_User /* 설명없음 */
	:Tbl__BasicScore
{
	/*  db pk 피망에서 온 id를 그대로 사용 */
	Tbl_User_id_t m_db_id; // 고유번호 min_max(,)
		typedef Tbl_User_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  베이스볼에서의 유저닉네임 */
	aname32_t m_uname; // 닉네임 min_max(,)
	/*  게임중간에 나간수 */
	int32 m_discon_tot; // 총Disconnect수 min_max(,)
	Tbl__BasicScore* GetBase_Tbl__BasicScore(){ return static_cast<Tbl__BasicScore*>(this);}
	/*  투수총_탈삼진 */
	int16 m_pitcher_tot_strikeout; // 탈삼진수 min_max(,)
	/*  투수총평균_레벨 멀로 평균을 낼것인가 */
	int16 m_pitcher_tot_average_level; // 투수총평균_레벨 min_max(,)
	/*  타자총_홈런 */
	int16 m_better_tot_homerun; // 총_홈런수 min_max(,)
	/*  타자총평균_레벨 */
	int16 m_better_tot__average_level; // 타자총평균_레벨 min_max(,)
	/*  캐쉬템구매갯수 */
	int16 m_cash_item_buy_count; // 캐쉬템구매갯수 min_max(,)
	/*  마지막로긴시간 */
	SYSTEMTIME m_time_last_login; // 마지막로긴시간 min_max(,)
	/*  마지막 로그아웃시간 */
	SYSTEMTIME m_time_last_logout; // 마지막로그아웃시간 min_max(,)
	/*  연속출석한 일수 */
	int16 m_day_continue_attend; // 연속출석일수 min_max(,)
	/*  최초게임등록일 */
	SYSTEMTIME m_date_insert; // 등록시간 min_max(,)
	/*  마지막수정시간 */
	SYSTEMTIME m_date_update; // 수정된시간 min_max(,)
	/*  기본팀 index */
	Tbl_Team_id_t m_default_tid; // 기본팀번호 min_max(,)
	/*  옵션(클라에서임의로저장할내용) */
	aname1024_t m_option; // 옵션 min_max(,)
	/*  하루에 발급된 싱글플레이 보상경험치 횟수 */
	int16 m_singleplay_gift_count; // 싱글플레이보상카운트 min_max(,)
	/*  아이템이 삭제된것.또는 어뷰징으로 제제상태 */
	int16 m_is_deleted; // 삭제플레그 min_max(,)
	int64 m_game_money; // 게임머니 min_max(,)
	/*  클라 OS ( IOS / ANDROID ) */
	aname32_t m_client_os; // client_os min_max(,)
	/*  클라 네트웍(3G, 4G, WIFI) */
	aname32_t m_client_networ; // client_networ min_max(,)
	/*  총_플레이_타임(분) */
	int64 m_playtime_tot; // 총_플레이_타임 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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
