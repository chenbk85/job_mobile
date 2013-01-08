
// THIS CODE IS USED FOR unity3d + google protocal buffer + c# + iphone
// by icandoit@neowiz.com
// command line : Excel_Converter.exe D:\svn\baseball\doc\design\excel\code\excel_baseball_table.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_db.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_game.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_item.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_shop.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_string_table.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_etc.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_animation.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client_locale_Eng.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client_locale_kor.txt 



using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using ProtoBuf;
using nEXCEL;
using nPROTO;
// above code is created by app_xml <PROTO_CONTRACT_NAMESPACE>


namespace nEXCEL
{
	

	//TYPE_INFO_NS
	using Sys_Hero_id_t = UInt16;
	using Sys_Castle_id_t = UInt16;
	using Sys_TownPos_id_t = UInt16;
	using Sys_Force_id_t = UInt16;
	using Sys__T_Base_id_t = UInt16;
	using Sys_T_Bar_id_t = UInt16;
	using Sys_T__Bar_id_t = UInt16;
	using Sys_T_Barrack_id_t = UInt16;
	using Sys_T_Camp_id_t = UInt16;
	using Sys_T_Depot_id_t = UInt16;
	using Sys_T_Farm_id_t = UInt16;
	using Sys_T_House_id_t = UInt16;
	using Sys_T_HQ_id_t = UInt16;
	using cash_money_t = Int32;
	using Sys_Tile_id_t = UInt16;
	using Sys_World_id_t = UInt16;
	using Sys_T_Test_id_t = UInt16;
	using Sys_T_Test2_id_t = UInt16;
	using Sys_T_Test3_id_t = UInt16;
	using Sys_ItemBase_id_t = UInt16;
	using player_level_t = Int32;
	using Sys_Quest_id_t = UInt16;
	using game_money_t = Int32;
	using pp_point_t = Int32;
	using Sys_ItemEquip_id_t = UInt16;
	using Sys__ItemBase_id_t = UInt16;
	using Sys_RandomGift_id_t = UInt16;
	using g234ame_money_t = Int32;
	using Sys_BreakingBallState_id_t = UInt16;
	using Tbl__PlayerBase_id_t = Int64;
	using Sys_PlayerCard_id_t = UInt16;
	using pimang_id_t = Int32;
	using Tbl_Result_id_t = Int64;
	using Tbl_Item_id_t = Int64;
	using real_money_t = Int32;
	using Tbl_User_id_t = Int64;
	using Tbl_PlayerBetter_id_t = Int64;
	using Tbl_PlayerPitcher_id_t = Int64;
	using Tbl_RoundResult_id_t = Int64;
	using Tbl_Team_id_t = Int64;
	using Sys_Shop_id_t = UInt16;
	using Tbl_BreakingBall_id_t = Int64;
	using Tbl_Friend_id_t = Int64;
	using Sys_Daily_Quest_id_t = UInt16;
	using Sys_Error_id_t = UInt16;
	using Tbl_PitcherSkill_id_t = Int64;
	using Tbl_Package_id_t = Int64;
	using Sys_Package_id_t = UInt16;
	using Sys_Runner_State_id_t = UInt16;
	using Tbl_Quest_id_t = Int64;
	using Sys_Title_id_t = UInt16;
	using Tbl_Title_id_t = Int64;
	using Tbl_PlayerSkillSticker_id_t = Int64;
	using Sys_PlayerSkillSticker_id_t = UInt16;
	using Sys_Batter_id_t = UInt16;
	using Sys_Pitcher_id_t = UInt16;
	using Sys_Better_id_t = UInt16;
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	[ProtoContract]
	public class s_tbl_quest
	{
		[ProtoMember(1, IsRequired = false)]
		public Tbl_Quest_id_t m_db_id {get; set;}	// [] Tbl_Quest_id_t 
		[ProtoMember(2, IsRequired = false)]
		public Sys_Quest_id_t m_quest_sid {get; set;}	// [디펄트명은 pp_name이다] Sys_Quest_id_t 
		[ProtoMember(3, IsRequired = false)]
		public Tbl_User_id_t m_uid {get; set;}	// [] Tbl_User_id_t 
		[ProtoMember(4, IsRequired = false)]
		public string m_date_insert {get; set;}	// [최초 수행 등록일] SYSTEMTIME 
		[ProtoMember(5, IsRequired = false)]
		public string m_date_done {get; set;}	// [완료시 시간] SYSTEMTIME 
		[ProtoMember(6, IsRequired = false)]
		public string m_info {get; set;}	// [퀘스트별 수행시 기록될 파라미터] aname256_t 
		[ProtoMember(7, IsRequired = false)]
		public Int32 m_done_count {get; set;}	// [] int32 
	}//public class s_tbl_quest

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	[ProtoContract]
	public class s_tbl_result
	{
		[ProtoMember(1, IsRequired = false)]
		public Tbl_Result_id_t m_db_id {get; set;}	// [] Tbl_Result_id_t 
		[ProtoMember(2, IsRequired = false)]
		public Tbl_User_id_t m_win_uid {get; set;}	// [승자 고유번호] Tbl_User_id_t 
		[ProtoMember(3, IsRequired = false)]
		public Tbl_PlayerBetter_id_t m_win_better {get; set;}	// [승자] Tbl_PlayerBetter_id_t 
		[ProtoMember(4, IsRequired = false)]
		public Tbl_PlayerPitcher_id_t m_win_pitcher {get; set;}	// [승자] Tbl_PlayerPitcher_id_t 
		[ProtoMember(5, IsRequired = false)]
		public Int16 m_win_score {get; set;}	// [] int8 
		[ProtoMember(6, IsRequired = false)]
		public Int32 m_win_elo_point {get; set;}	// [경기에서 승 했을 시 사용자에게 플러스 되는 매칭용 포인트] int32 
		[ProtoMember(7, IsRequired = false)]
		public Tbl_User_id_t m_lose_uid {get; set;}	// [패자 고유번호] Tbl_User_id_t 
		[ProtoMember(8, IsRequired = false)]
		public Tbl_PlayerBetter_id_t m_lose_better {get; set;}	// [패자] Tbl_PlayerBetter_id_t 
		[ProtoMember(9, IsRequired = false)]
		public Tbl_PlayerPitcher_id_t m_lose_pitcher {get; set;}	// [패자] Tbl_PlayerPitcher_id_t 
		[ProtoMember(10, IsRequired = false)]
		public Int16 m_lose_score {get; set;}	// [] int8 
		[ProtoMember(11, IsRequired = false)]
		public Int32 m_lose_elo_point {get; set;}	// [경기에서 패 했을 시  사용자에게 마이너스 되는 매칭용 포인트] int32 
		[ProtoMember(12, IsRequired = false)]
		public Int32 m_play_time_sec {get; set;}	// [플레이 한 시간(초)] int32 
		[ProtoMember(13, IsRequired = false)]
		public string m_time_end {get; set;}	// [플레이 시간 (2012-12-15 13:53:15)] SYSTEMTIME 
	}//public class s_tbl_result

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	[ProtoContract]
	public class s_tbl_roundresult
	{
		[ProtoMember(1, IsRequired = false)]
		public Tbl_RoundResult_id_t m_db_id {get; set;}	// [일별 파티션 키] Tbl_RoundResult_id_t 
		[ProtoMember(2, IsRequired = false)]
		public Tbl_Result_id_t m_grid {get; set;}	// [] Tbl_Result_id_t 
		[ProtoMember(3, IsRequired = false)]
		public Sys_Better_id_t m_used_batter_id {get; set;}	// [선택 된 타자 id (8개)] Sys_Better_id_t 
		[ProtoMember(4, IsRequired = false)]
		public Sys_Pitcher_id_t m_used_pitcher_id {get; set;}	// [선택 된 투수 id (8개)] Sys_Pitcher_id_t 
		[ProtoMember(5, IsRequired = false)]
		public Int16 m_round_number {get; set;}	// [1부터시작. 1~10은 라운드 한게임의 토탈집계는 Tbl_Result에 저장] int8 
		[ProtoMember(6, IsRequired = false)]
		public int m_used_breakingball {get; set;}	// [사용한 구종의 종류] EPlayerBreakingBall 
		[ProtoMember(7, IsRequired = false)]
		public Int16 m_used_breakingball_speed {get; set;}	// [사용한 구종의 속도] int16 
		[ProtoMember(8, IsRequired = false)]
		public int m_used_pitcherability {get; set;}	// [스텟에 영향을 준 투수의 특수능력] EPitcherAbility 
		[ProtoMember(9, IsRequired = false)]
		public int m_pitching_rhythm_judge {get; set;}	// [투구 시 제구 타이밍의 종류] ERhythmJudge 
		[ProtoMember(10, IsRequired = false)]
		public int m_used_gesturetype {get; set;}	// [사용한 제스처 종류] EGestureType 
		[ProtoMember(11, IsRequired = false)]
		public Int16 m_gesturetype_input_error {get; set;}	// [제스처 입력 오류 횟수] int16 
		[ProtoMember(12, IsRequired = false)]
		public int m_used_batting_fullpower {get; set;}	// [타자 히트의 종류(일반히트_스트롱히트_헛스윙_대기상태)] EHitType 
		[ProtoMember(13, IsRequired = false)]
		public int m_batting_timing_judge {get; set;}	// [타격 시 타이밍 종류(veryfast_fast_goodfast_perfect_goodslow_slow_veryslow)] EHitTimmingType 
		[ProtoMember(14, IsRequired = false)]
		public int m_batting_hittype {get; set;}	// [타격 시 히트 타입] EBatterHitType 
		[ProtoMember(15, IsRequired = false)]
		public Tbl_User_id_t m_uid_attack {get; set;}	// [공격자] Tbl_User_id_t 
		[ProtoMember(16, IsRequired = false)]
		public Int16 m_score {get; set;}	// [] int8 
		[ProtoMember(17, IsRequired = false)]
		public Int16 m_base_runner_state {get; set;}	// [bit flag로 출루한 주자상태를 표시한다. 1루는 2^0 최대는 xml에서  i_max_runner_per_game=19이다] int8 
		[ProtoMember(18, IsRequired = false)]
		public int m_hit_type {get; set;}	// [] EBatterHitType 
	}//public class s_tbl_roundresult

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	[ProtoContract]
	public class s_tbl_user
	{
		[ProtoMember(1, IsRequired = false)]
		public Tbl_User_id_t m_db_id {get; set;}	// [] Tbl_User_id_t 
		[ProtoMember(2, IsRequired = false)]
		public Int64 m_pp_id {get; set;}	// [MemberInfo의 (game_id)피망에서 온 id를 그대로 사용] int64 
		[ProtoMember(3, IsRequired = false)]
		public string m_host_type {get; set;}	// [0-pp user 1-facebook 2-카톡] aname32_t 
		[ProtoMember(4, IsRequired = false)]
		public string m_uname {get; set;}	// [베이스볼에서의 유저닉네임] aname32_t 
		[ProtoMember(5, IsRequired = false)]
		public Int32 m_discon_tot {get; set;}	// [게임중간에 나간수] int32 
		[ProtoMember(6, IsRequired = false)]
		public Int32 m_win_tot {get; set;}	// [토탈 승 카운트] int32 
		[ProtoMember(7, IsRequired = false)]
		public Int32 m_win_tot_continue {get; set;}	// [연속으로 승리한 개수. 음수면 연패] int32 
		[ProtoMember(8, IsRequired = false)]
		public Int32 m_win_tot_continue_max {get; set;}	// [최대연승] int32 
		[ProtoMember(9, IsRequired = false)]
		public Int32 m_lose_tot {get; set;}	// [토탈 패 카운트] int32 
		[ProtoMember(10, IsRequired = false)]
		public Int32 m_win_season {get; set;}	// [시즌 승 카운트(3개월)] int32 
		[ProtoMember(11, IsRequired = false)]
		public Int32 m_lose_season {get; set;}	// [시즌 패 카운트(3개월)] int32 
		[ProtoMember(12, IsRequired = false)]
		public Int16 m_batter_tot_homerun {get; set;}	// [타자총_홈런] int16 
		[ProtoMember(13, IsRequired = false)]
		public Int16 m_pitcher_tot_strikeout {get; set;}	// [투수총_탈삼진] int16 
		[ProtoMember(14, IsRequired = false)]
		public Int16 m_batter_tot_homerun_season {get; set;}	// [시즌 타자총_홈런] int16 
		[ProtoMember(15, IsRequired = false)]
		public Int16 m_pitcher_tot_strikeout_season {get; set;}	// [시즌 투수총_탈삼진] int16 
		[ProtoMember(16, IsRequired = false)]
		public Int32 m_elo_point {get; set;}	// [경기마다 캐릭터에 갱신되는 매칭용 포인트] int32 
		[ProtoMember(17, IsRequired = false)]
		public Int64 m_cash_item_buy_money_amount {get; set;}	// [캐쉬템구매 누적액] int64 
		[ProtoMember(18, IsRequired = false)]
		public string m_time_last_login {get; set;}	// [마지막로긴시간] SYSTEMTIME 
		[ProtoMember(19, IsRequired = false)]
		public string m_time_last_logout {get; set;}	// [마지막 로그아웃시간] SYSTEMTIME 
		[ProtoMember(20, IsRequired = false)]
		public Int16 m_day_continue_attend {get; set;}	// [연속출석한 일수] int16 
		[ProtoMember(21, IsRequired = false)]
		public string m_client_os {get; set;}	// [클라 OS ( IOS  ANDROID )] aname32_t 
		[ProtoMember(22, IsRequired = false)]
		public string m_client_networ {get; set;}	// [클라 네트웍(3G 4G WIFI)] aname32_t 
		[ProtoMember(23, IsRequired = false)]
		public Int64 m_playtime_tot {get; set;}	// [총_플레이_타임(분)] int64 
	}//public class s_tbl_user

	


	public class excel_baseball_table_db_proto_contract
	{
		public static ArrayList GetTypes()
		{
			ArrayList list = new ArrayList();
			
			list.Add(typeof(s_tbl_quest));
			list.Add(typeof(s_tbl_result));
			list.Add(typeof(s_tbl_roundresult));
			list.Add(typeof(s_tbl_user));
			return list;
		}
	}
}// namespace nEXCEL


