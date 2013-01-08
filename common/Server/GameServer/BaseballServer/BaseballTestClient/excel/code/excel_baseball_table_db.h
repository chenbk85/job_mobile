/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_db_
#define __namespace_nEXCEL___filename_excel_baseball_table_db_

#include "table_const_excel_baseball_table_db.h"
// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_db_Tbl_STRUCT_LIST(STRUCT)\
	STRUCT(Tbl_Quest,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_Result,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_RoundResult,설명없음,nMech,nEXCEL)\
	STRUCT(Tbl_User,설명없음,nMech,nEXCEL)\



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
		FIELD(win_uid                ,고유번호               ,Tbl_User_id_t                ,1 , int64 , int64 , i)\
		FIELD(win_better             ,타자 pid             ,Tbl_PlayerBetter_id_t        ,2 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(win_pitcher            ,투수 pid             ,Tbl_PlayerPitcher_id_t       ,3 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(win_score              ,승자스코어              ,int8                         ,4 , int8 , int8 , i8)\
		FIELD(win_elo_point          ,ELO_포인트            ,int32                        ,5 , int32 , int32 , i32)\
		FIELD(lose_uid               ,고유번호               ,Tbl_User_id_t                ,6 , int64 , int64 , i)\
		FIELD(lose_better            ,타자 pid             ,Tbl_PlayerBetter_id_t        ,7 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(lose_pitcher           ,투수 pid             ,Tbl_PlayerPitcher_id_t       ,8 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(lose_score             ,패자스코어              ,int8                         ,9 , int8 , int8 , i8)\
		FIELD(lose_elo_point         ,ELO_포인트            ,int32                        ,10 , int32 , int32 , i32)\
		FIELD(play_time_sec          ,플레이시간              ,int32                        ,11 , int32 , int32 , i32)\
		FIELD(time_end               ,게임종료시간             ,SYSTEMTIME                   ,12 , SYSTEMTIME , SYSTEMTIME , tm)\

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
		FIELD(grid                   ,Tbl_Result테이블의 고유번호 ,Tbl_Result_id_t             ,1 , db_uid_type_ref , db_uid_type_ref , i64)\
		FIELD(used_batter_id         ,선택 된 타자 id         ,Sys_Better_id_t              ,2 , Sys_Better_id_t , uint16 , u16)\
		FIELD(used_pitcher_id        ,선택 된 투수 id         ,Sys_Pitcher_id_t             ,3 , Sys_Pitcher_id_t , uint16 , u16)\
		FIELD(round_number           ,라운드번호              ,int8                         ,4 , int8 , int8 , i8)\
		FIELD(used_breakingball      ,투수의 사용 구종          ,EPlayerBreakingBall          ,5 , EPlayerBreakingBall , EPlayerBreakingBall , e)\
		FIELD(used_breakingball_speed,투수의 사용 구종의 구속      ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(used_pitcherability    ,사용하고 있는 투수의 스킬(변화구 제외) ,EPitcherAbility          ,7 , EPitcherAbility , EPitcherAbility , e)\
		FIELD(pitching_rhythm_judge  ,투구 시 제구 타이밍        ,ERhythmJudge                 ,8 , ERhythmJudge , ERhythmJudge , e)\
		FIELD(used_gesturetype       ,사용한 제스처 종류         ,EGestureType                 ,9 , EGestureType , EGestureType , e)\
		FIELD(gesturetype_input_error,제스처 입력 오류 횟수       ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(used_batting_fullpower ,타자 히트 시 라운드 별 풀파워 사용 ,EHitType                   ,11 , EHitType , EHitType , e)\
		FIELD(batting_timing_judge   ,타격 시 라운드 별 타격 타이밍  ,EHitTimmingType              ,12 , EHitTimmingType , EHitTimmingType , e)\
		FIELD(batting_hittype        ,타격 시 라운드 별 히트 타입   ,EBatterHitType               ,13 , EBatterHitType , EBatterHitType , e)\
		FIELD(uid_attack             ,uid_attack         ,Tbl_User_id_t                ,14 , int64 , int64 , i)\
		FIELD(score                  ,better의점수          ,int8                         ,15 , int8 , int8 , i8)\
		FIELD(base_runner_state      ,출루한주자수             ,int8                         ,16 , int8 , int8 , i8)\
		FIELD(hit_type               ,안타종류               ,EBatterHitType               ,17 , EBatterHitType , EBatterHitType , e)\

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
	// Tbl_User 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_User_STRUCT_FIELD
	#define for_each_nEXCEL_Tbl_User_STRUCT_FIELD(FIELD)\
		FIELD(db_id                  ,고유번호               ,Tbl_User_id_t                ,0 , int64 , int64 , i)\
		FIELD(pp_id                  ,피망ID               ,int64                        ,1 , int64 , int64 , i64)\
		FIELD(host_type              ,HOST_TYPE          ,aname32_t                    ,2 , acstr , acstr , a32)\
		FIELD(uname                  ,닉네임                ,aname32_t                    ,3 , acstr , acstr , a32)\
		FIELD(discon_tot             ,총Disconnect수       ,int32                        ,4 , int32 , int32 , i32)\
		FIELD(win_tot                ,총전적_승              ,int32                        ,5 , int32 , int32 , i32)\
		FIELD(win_tot_continue       ,연승패                ,int32                        ,6 , int32 , int32 , i32)\
		FIELD(win_tot_continue_max   ,최대연승               ,int32                        ,7 , int32 , int32 , i32)\
		FIELD(lose_tot               ,총전적_패              ,int32                        ,8 , int32 , int32 , i32)\
		FIELD(win_season             ,시즌전적_승             ,int32                        ,9 , int32 , int32 , i32)\
		FIELD(lose_season            ,시즌전적_패             ,int32                        ,10 , int32 , int32 , i32)\
		FIELD(batter_tot_homerun     ,총_홈런수              ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(pitcher_tot_strikeout  ,탈삼진수               ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(batter_tot_homerun_season,시즌 총_홈런수         ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(pitcher_tot_strikeout_season,시즌 탈삼진수       ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(elo_point              ,ELO_포인트            ,int32                        ,15 , int32 , int32 , i32)\
		FIELD(cash_item_buy_money_amount,캐쉬템구매누적액        ,int64                        ,16 , int64 , int64 , i64)\
		FIELD(time_last_login        ,마지막로긴시간            ,SYSTEMTIME                   ,17 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(time_last_logout       ,마지막로그아웃시간          ,SYSTEMTIME                   ,18 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(day_continue_attend    ,연속출석일수             ,int16                        ,19 , int16 , int16 , i16)\
		FIELD(client_os              ,client_os          ,aname32_t                    ,20 , acstr , acstr , a32)\
		FIELD(client_networ          ,client_networ      ,aname32_t                    ,21 , acstr , acstr , a32)\
		FIELD(playtime_tot           ,총_플레이_타임           ,int64                        ,22 , int64 , int64 , i64)\

	#endif // for_each_nEXCEL_Tbl_User_STRUCT_FIELD


	// ------------------------------------------------------------
	// Tbl_User가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Tbl_User_InheritedTable
	#define for_each_nEXCEL_Tbl_User_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Tbl_User_InheritedTable


	// ------------------------------------------------------------
	// Tbl_User가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Tbl_User_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Tbl_User_STRUCT_FIELD_Inherited(FUNC)\

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
	/*  승자 고유번호 */
	Tbl_User_id_t m_win_uid; // 고유번호 min_max(,)
	/*  승자 */
	Tbl_PlayerBetter_id_t m_win_better; // 타자 pid min_max(,)
	/*  승자 */
	Tbl_PlayerPitcher_id_t m_win_pitcher; // 투수 pid min_max(,)
	int8 m_win_score; // 승자스코어 min_max(,)
	/*  경기에서 승 했을 시 사용자에게 플러스 되는 매칭용 포인트 */
	int32 m_win_elo_point; // ELO_포인트 min_max(1,10000)
	/*  패자 고유번호 */
	Tbl_User_id_t m_lose_uid; // 고유번호 min_max(,)
	/*  패자 */
	Tbl_PlayerBetter_id_t m_lose_better; // 타자 pid min_max(,)
	/*  패자 */
	Tbl_PlayerPitcher_id_t m_lose_pitcher; // 투수 pid min_max(,)
	int8 m_lose_score; // 패자스코어 min_max(,)
	/*  경기에서 패 했을 시  사용자에게 마이너스 되는 매칭용 포인트 */
	int32 m_lose_elo_point; // ELO_포인트 min_max(1,10000)
	/*  플레이 한 시간(초) */
	int32 m_play_time_sec; // 플레이시간 min_max(,)
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

struct jEXCEL_LIB_API Tbl_RoundResult /* 설명없음 */
{
	/*  일별 파티션 키 */
	Tbl_RoundResult_id_t m_db_id; // 고유번호 min_max(,)
		typedef Tbl_RoundResult_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	Tbl_Result_id_t m_grid; // Tbl_Result테이블의 고유번호 min_max(,)
	/*  선택 된 타자 id (8개) */
	Sys_Better_id_t m_used_batter_id; // 선택 된 타자 id min_max(,)
	/*  선택 된 투수 id (8개) */
	Sys_Pitcher_id_t m_used_pitcher_id; // 선택 된 투수 id min_max(,)
	/*  1부터시작. 1~10은 라운드 한게임의 토탈집계는 Tbl_Result에 저장 */
	int8 m_round_number; // 라운드번호 min_max(,)
	/*  사용한 구종의 종류 */
	EPlayerBreakingBall m_used_breakingball; // 투수의 사용 구종 min_max(,)
	/*  사용한 구종의 속도 */
	int16 m_used_breakingball_speed; // 투수의 사용 구종의 구속 min_max(,)
	/*  스텟에 영향을 준 투수의 특수능력 */
	EPitcherAbility m_used_pitcherability; // 사용하고 있는 투수의 스킬(변화구 제외) min_max(,)
	/*  투구 시 제구 타이밍의 종류 */
	ERhythmJudge m_pitching_rhythm_judge; // 투구 시 제구 타이밍 min_max(,)
	/*  사용한 제스처 종류 */
	EGestureType m_used_gesturetype; // 사용한 제스처 종류 min_max(,)
	/*  제스처 입력 오류 횟수 */
	int16 m_gesturetype_input_error; // 제스처 입력 오류 횟수 min_max(,)
	/*  타자 히트의 종류(일반히트_스트롱히트_헛스윙_대기상태) */
	EHitType m_used_batting_fullpower; // 타자 히트 시 라운드 별 풀파워 사용 min_max(,)
	/*  타격 시 타이밍 종류(veryfast_fast_goodfast_perfect_goodslow_slow_veryslow) */
	EHitTimmingType m_batting_timing_judge; // 타격 시 라운드 별 타격 타이밍 min_max(,)
	/*  타격 시 히트 타입 */
	EBatterHitType m_batting_hittype; // 타격 시 라운드 별 히트 타입 min_max(,)
	/*  공격자 */
	Tbl_User_id_t m_uid_attack; // uid_attack min_max(,)
	int8 m_score; // better의점수 min_max(,)
	/*  bit flag로 출루한 주자상태를 표시한다. 1루는 2^0 최대는 xml에서  i_max_runner_per_game=19이다 */
	int8 m_base_runner_state; // 출루한주자수 min_max(,)
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

struct jEXCEL_LIB_API Tbl_User /* 설명없음 */
{
	Tbl_User_id_t m_db_id; // 고유번호 min_max(,)
		typedef Tbl_User_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_db_id; }
	void SetPrimaryKey(primary_key_t id) { m_db_id = id; }
	/*  MemberInfo의 (game_id)피망에서 온 id를 그대로 사용 */
	int64 m_pp_id; // 피망ID min_max(,)
	/*  0-pp user 1-facebook 2-카톡 */
	aname32_t m_host_type; // HOST_TYPE min_max(,)
	/*  베이스볼에서의 유저닉네임 */
	aname32_t m_uname; // 닉네임 min_max(,)
	/*  게임중간에 나간수 */
	int32 m_discon_tot; // 총Disconnect수 min_max(,)
	/*  토탈 승 카운트 */
	int32 m_win_tot; // 총전적_승 min_max(0,)
	/*  연속으로 승리한 개수. 음수면 연패 */
	int32 m_win_tot_continue; // 연승패 min_max(,)
	/*  최대연승 */
	int32 m_win_tot_continue_max; // 최대연승 min_max(,)
	/*  토탈 패 카운트 */
	int32 m_lose_tot; // 총전적_패 min_max(0,)
	/*  시즌 승 카운트(3개월) */
	int32 m_win_season; // 시즌전적_승 min_max(0,)
	/*  시즌 패 카운트(3개월) */
	int32 m_lose_season; // 시즌전적_패 min_max(0,)
	/*  타자총_홈런 */
	int16 m_batter_tot_homerun; // 총_홈런수 min_max(,)
	/*  투수총_탈삼진 */
	int16 m_pitcher_tot_strikeout; // 탈삼진수 min_max(,)
	/*  시즌 타자총_홈런 */
	int16 m_batter_tot_homerun_season; // 시즌 총_홈런수 min_max(,)
	/*  시즌 투수총_탈삼진 */
	int16 m_pitcher_tot_strikeout_season; // 시즌 탈삼진수 min_max(,)
	/*  경기마다 캐릭터에 갱신되는 매칭용 포인트 */
	int32 m_elo_point; // ELO_포인트 min_max(1,10000)
	/*  캐쉬템구매 누적액 */
	int64 m_cash_item_buy_money_amount; // 캐쉬템구매누적액 min_max(,)
	/*  마지막로긴시간 */
	SYSTEMTIME m_time_last_login; // 마지막로긴시간 min_max(,)
	/*  마지막 로그아웃시간 */
	SYSTEMTIME m_time_last_logout; // 마지막로그아웃시간 min_max(,)
	/*  연속출석한 일수 */
	int16 m_day_continue_attend; // 연속출석일수 min_max(,)
	/*  클라 OS ( IOS  ANDROID ) */
	aname32_t m_client_os; // client_os min_max(,)
	/*  클라 네트웍(3G 4G WIFI) */
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
