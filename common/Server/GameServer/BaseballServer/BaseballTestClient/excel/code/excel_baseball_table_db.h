/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_db_
#define __namespace_nEXCEL___filename_excel_baseball_table_db_

#include "table_const_excel_baseball_table_db.h"
// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_db_Tbl_STRUCT_LIST(STRUCT)\
	STRUCT(Tbl_Quest,�������,nMech,nEXCEL)\
	STRUCT(Tbl_Result,�������,nMech,nEXCEL)\
	STRUCT(Tbl_RoundResult,�������,nMech,nEXCEL)\
	STRUCT(Tbl_User,�������,nMech,nEXCEL)\



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
		FIELD(win_uid                ,������ȣ               ,Tbl_User_id_t                ,1 , int64 , int64 , i)\
		FIELD(win_better             ,Ÿ�� pid             ,Tbl_PlayerBetter_id_t        ,2 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(win_pitcher            ,���� pid             ,Tbl_PlayerPitcher_id_t       ,3 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(win_score              ,���ڽ��ھ�              ,int8                         ,4 , int8 , int8 , i8)\
		FIELD(win_elo_point          ,ELO_����Ʈ            ,int32                        ,5 , int32 , int32 , i32)\
		FIELD(lose_uid               ,������ȣ               ,Tbl_User_id_t                ,6 , int64 , int64 , i)\
		FIELD(lose_better            ,Ÿ�� pid             ,Tbl_PlayerBetter_id_t        ,7 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(lose_pitcher           ,���� pid             ,Tbl_PlayerPitcher_id_t       ,8 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(lose_score             ,���ڽ��ھ�              ,int8                         ,9 , int8 , int8 , i8)\
		FIELD(lose_elo_point         ,ELO_����Ʈ            ,int32                        ,10 , int32 , int32 , i32)\
		FIELD(play_time_sec          ,�÷��̽ð�              ,int32                        ,11 , int32 , int32 , i32)\
		FIELD(time_end               ,��������ð�             ,SYSTEMTIME                   ,12 , SYSTEMTIME , SYSTEMTIME , tm)\

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
		FIELD(grid                   ,Tbl_Result���̺��� ������ȣ ,Tbl_Result_id_t             ,1 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(used_batter_id         ,���� �� Ÿ�� id         ,Sys_Better_id_t              ,2 , Sys_Better_id_t , uint16 , u16)\
		FIELD(used_pitcher_id        ,���� �� ���� id         ,Sys_Pitcher_id_t             ,3 , Sys_Pitcher_id_t , uint16 , u16)\
		FIELD(round_number           ,�����ȣ              ,int8                         ,4 , int8 , int8 , i8)\
		FIELD(used_breakingball      ,������ ��� ����          ,EPlayerBreakingBall          ,5 , EPlayerBreakingBall , EPlayerBreakingBall , e)\
		FIELD(used_breakingball_speed,������ ��� ������ ����      ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(used_pitcherability    ,����ϰ� �ִ� ������ ��ų(��ȭ�� ����) ,EPitcherAbility          ,7 , EPitcherAbility , EPitcherAbility , e)\
		FIELD(pitching_rhythm_judge  ,���� �� ���� Ÿ�̹�        ,ERhythmJudge                 ,8 , ERhythmJudge , ERhythmJudge , e)\
		FIELD(used_gesturetype       ,����� ����ó ����         ,EGestureType                 ,9 , EGestureType , EGestureType , e)\
		FIELD(gesturetype_input_error,����ó �Է� ���� Ƚ��       ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(used_batting_fullpower ,Ÿ�� ��Ʈ �� ���� �� Ǯ�Ŀ� ��� ,EHitType                   ,11 , EHitType , EHitType , e)\
		FIELD(batting_timing_judge   ,Ÿ�� �� ���� �� Ÿ�� Ÿ�̹�  ,EHitTimmingType              ,12 , EHitTimmingType , EHitTimmingType , e)\
		FIELD(batting_hittype        ,Ÿ�� �� ���� �� ��Ʈ Ÿ��   ,EBatterHitType               ,13 , EBatterHitType , EBatterHitType , e)\
		FIELD(uid_attack             ,uid_attack         ,Tbl_User_id_t                ,14 , int64 , int64 , i)\
		FIELD(score                  ,better������          ,int8                         ,15 , int8 , int8 , i8)\
		FIELD(base_runner_state      ,��������ڼ�             ,int8                         ,16 , int8 , int8 , i8)\
		FIELD(hit_type               ,��Ÿ����               ,EBatterHitType               ,17 , EBatterHitType , EBatterHitType , e)\

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
	// Tbl_User �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_User_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_User_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,������ȣ               ,Tbl_User_id_t                ,0 , int64 , int64 , i)\
		FIELD(pp_id                  ,�Ǹ�ID               ,int64                        ,1 , int64 , int64 , i64)\
		FIELD(host_type              ,HOST_TYPE          ,aname32_t                    ,2 , acstr , acstr , a32)\
		FIELD(uname                  ,�г���                ,aname32_t                    ,3 , acstr , acstr , a32)\
		FIELD(discon_tot             ,��Disconnect��       ,int32                        ,4 , int32 , int32 , i32)\
		FIELD(win_tot                ,������_��              ,int32                        ,5 , int32 , int32 , i32)\
		FIELD(win_tot_continue       ,������                ,int32                        ,6 , int32 , int32 , i32)\
		FIELD(win_tot_continue_max   ,�ִ뿬��               ,int32                        ,7 , int32 , int32 , i32)\
		FIELD(lose_tot               ,������_��              ,int32                        ,8 , int32 , int32 , i32)\
		FIELD(win_season             ,��������_��             ,int32                        ,9 , int32 , int32 , i32)\
		FIELD(lose_season            ,��������_��             ,int32                        ,10 , int32 , int32 , i32)\
		FIELD(batter_tot_homerun     ,��_Ȩ����              ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(pitcher_tot_strikeout  ,Ż������               ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(batter_tot_homerun_season,���� ��_Ȩ����         ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(pitcher_tot_strikeout_season,���� Ż������       ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(elo_point              ,ELO_����Ʈ            ,int32                        ,15 , int32 , int32 , i32)\
		FIELD(cash_item_buy_money_amount,ĳ���۱��Ŵ�����        ,int64                        ,16 , int64 , int64 , i64)\
		FIELD(time_last_login        ,�������α�ð�            ,SYSTEMTIME                   ,17 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(time_last_logout       ,�������α׾ƿ��ð�          ,SYSTEMTIME                   ,18 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(day_continue_attend    ,�����⼮�ϼ�             ,int16                        ,19 , int16 , int16 , i16)\
		FIELD(client_os              ,client_os          ,aname32_t                    ,20 , acstr , acstr , a32)\
		FIELD(client_networ          ,client_networ      ,aname32_t                    ,21 , acstr , acstr , a32)\
		FIELD(playtime_tot           ,��_�÷���_Ÿ��           ,int64                        ,22 , int64 , int64 , i64)\

	#endif // for_each_nEXCEL_Tbl_User_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_User�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_User_InheritedTable
	#define for_each_nEXCEL_Tbl_User_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_User_InheritedTable


	// ------------------------------------------------------------
	// Tbl_User�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_User_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_User_STRUCT_FIELD_Inherited(FUNC)\

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
	/*  ���� ������ȣ */
	Tbl_User_id_t m_win_uid; // ������ȣ min_max(,)
	/*  ���� */
	Tbl_PlayerBetter_id_t m_win_better; // Ÿ�� pid min_max(,)
	/*  ���� */
	Tbl_PlayerPitcher_id_t m_win_pitcher; // ���� pid min_max(,)
	int8 m_win_score; // ���ڽ��ھ� min_max(,)
	/*  ��⿡�� �� ���� �� ����ڿ��� �÷��� �Ǵ� ��Ī�� ����Ʈ */
	int32 m_win_elo_point; // ELO_����Ʈ min_max(1,10000)
	/*  ���� ������ȣ */
	Tbl_User_id_t m_lose_uid; // ������ȣ min_max(,)
	/*  ���� */
	Tbl_PlayerBetter_id_t m_lose_better; // Ÿ�� pid min_max(,)
	/*  ���� */
	Tbl_PlayerPitcher_id_t m_lose_pitcher; // ���� pid min_max(,)
	int8 m_lose_score; // ���ڽ��ھ� min_max(,)
	/*  ��⿡�� �� ���� ��  ����ڿ��� ���̳ʽ� �Ǵ� ��Ī�� ����Ʈ */
	int32 m_lose_elo_point; // ELO_����Ʈ min_max(1,10000)
	/*  �÷��� �� �ð�(��) */
	int32 m_play_time_sec; // �÷��̽ð� min_max(,)
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
	enum { eSTRUCT_COUNT =  13 };
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
	Tbl_Result_id_t m_grid; // Tbl_Result���̺��� ������ȣ min_max(,)
	/*  ���� �� Ÿ�� id (8��) */
	Sys_Better_id_t m_used_batter_id; // ���� �� Ÿ�� id min_max(,)
	/*  ���� �� ���� id (8��) */
	Sys_Pitcher_id_t m_used_pitcher_id; // ���� �� ���� id min_max(,)
	/*  1���ͽ���. 1~10�� ���� �Ѱ����� ��Ż����� Tbl_Result�� ���� */
	int8 m_round_number; // �����ȣ min_max(,)
	/*  ����� ������ ���� */
	EPlayerBreakingBall m_used_breakingball; // ������ ��� ���� min_max(,)
	/*  ����� ������ �ӵ� */
	int16 m_used_breakingball_speed; // ������ ��� ������ ���� min_max(,)
	/*  ���ݿ� ������ �� ������ Ư���ɷ� */
	EPitcherAbility m_used_pitcherability; // ����ϰ� �ִ� ������ ��ų(��ȭ�� ����) min_max(,)
	/*  ���� �� ���� Ÿ�̹��� ���� */
	ERhythmJudge m_pitching_rhythm_judge; // ���� �� ���� Ÿ�̹� min_max(,)
	/*  ����� ����ó ���� */
	EGestureType m_used_gesturetype; // ����� ����ó ���� min_max(,)
	/*  ����ó �Է� ���� Ƚ�� */
	int16 m_gesturetype_input_error; // ����ó �Է� ���� Ƚ�� min_max(,)
	/*  Ÿ�� ��Ʈ�� ����(�Ϲ���Ʈ_��Ʈ����Ʈ_�꽺��_������) */
	EHitType m_used_batting_fullpower; // Ÿ�� ��Ʈ �� ���� �� Ǯ�Ŀ� ��� min_max(,)
	/*  Ÿ�� �� Ÿ�̹� ����(veryfast_fast_goodfast_perfect_goodslow_slow_veryslow) */
	EHitTimmingType m_batting_timing_judge; // Ÿ�� �� ���� �� Ÿ�� Ÿ�̹� min_max(,)
	/*  Ÿ�� �� ��Ʈ Ÿ�� */
	EBatterHitType m_batting_hittype; // Ÿ�� �� ���� �� ��Ʈ Ÿ�� min_max(,)
	/*  ������ */
	Tbl_User_id_t m_uid_attack; // uid_attack min_max(,)
	int8 m_score; // better������ min_max(,)
	/*  bit flag�� ����� ���ڻ��¸� ǥ���Ѵ�. 1��� 2^0 �ִ�� xml����  i_max_runner_per_game=19�̴� */
	int8 m_base_runner_state; // ��������ڼ� min_max(,)
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
	enum { eSTRUCT_COUNT =  18 };
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

struct jEXCEL_LIB_API Tbl_User /* ������� */
{
	Tbl_User_id_t m_db_id; // ������ȣ min_max(,)
		typedef Tbl_User_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  MemberInfo�� (game_id)�Ǹ����� �� id�� �״�� ��� */
	int64 m_pp_id; // �Ǹ�ID min_max(,)
	/*  0-pp user 1-facebook 2-ī�� */
	aname32_t m_host_type; // HOST_TYPE min_max(,)
	/*  ���̽��������� �����г��� */
	aname32_t m_uname; // �г��� min_max(,)
	/*  �����߰��� ������ */
	int32 m_discon_tot; // ��Disconnect�� min_max(,)
	/*  ��Ż �� ī��Ʈ */
	int32 m_win_tot; // ������_�� min_max(0,)
	/*  �������� �¸��� ����. ������ ���� */
	int32 m_win_tot_continue; // ������ min_max(,)
	/*  �ִ뿬�� */
	int32 m_win_tot_continue_max; // �ִ뿬�� min_max(,)
	/*  ��Ż �� ī��Ʈ */
	int32 m_lose_tot; // ������_�� min_max(0,)
	/*  ���� �� ī��Ʈ(3����) */
	int32 m_win_season; // ��������_�� min_max(0,)
	/*  ���� �� ī��Ʈ(3����) */
	int32 m_lose_season; // ��������_�� min_max(0,)
	/*  Ÿ����_Ȩ�� */
	int16 m_batter_tot_homerun; // ��_Ȩ���� min_max(,)
	/*  ������_Ż���� */
	int16 m_pitcher_tot_strikeout; // Ż������ min_max(,)
	/*  ���� Ÿ����_Ȩ�� */
	int16 m_batter_tot_homerun_season; // ���� ��_Ȩ���� min_max(,)
	/*  ���� ������_Ż���� */
	int16 m_pitcher_tot_strikeout_season; // ���� Ż������ min_max(,)
	/*  ��⸶�� ĳ���Ϳ� ���ŵǴ� ��Ī�� ����Ʈ */
	int32 m_elo_point; // ELO_����Ʈ min_max(1,10000)
	/*  ĳ���۱��� ������ */
	int64 m_cash_item_buy_money_amount; // ĳ���۱��Ŵ����� min_max(,)
	/*  �������α�ð� */
	SYSTEMTIME m_time_last_login; // �������α�ð� min_max(,)
	/*  ������ �α׾ƿ��ð� */
	SYSTEMTIME m_time_last_logout; // �������α׾ƿ��ð� min_max(,)
	/*  �����⼮�� �ϼ� */
	int16 m_day_continue_attend; // �����⼮�ϼ� min_max(,)
	/*  Ŭ�� OS ( IOS  ANDROID ) */
	aname32_t m_client_os; // client_os min_max(,)
	/*  Ŭ�� ��Ʈ��(3G 4G WIFI) */
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
	enum { eSTRUCT_COUNT =  23 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

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
