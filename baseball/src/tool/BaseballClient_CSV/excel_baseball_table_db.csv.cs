/*------------------------------------------------------------


command line : 
Excel_Converter.exe D:\svn\baseball\doc\design\excel\code\excel_baseball_table.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_db.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_game.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_item.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_shop.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_string_table.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_etc.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_animation.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client_locale_Eng.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client_locale_kor.txt 

-------------------------------------------------------------*/


using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;


namespace nEXCEL
{
	//TYPE_INFO
	

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

	public class Tbl_Quest
	{
		public Tbl_Quest_id_t m_db_id; 	// [고유번호]  
		public Sys_Quest_id_t m_quest_sid; 	// [수행한 퀘스트 sid] 디펄트명은 pp_name이다 
		public Tbl_User_id_t m_uid; 	// [유저id]  
		public DATETIME m_date_insert; 	// [등록시간] 최초 수행 등록일 
		public DATETIME m_date_done; 	// [완료시간] 완료시 시간 
		public string m_info; 	// [수행 정보] 퀘스트별 수행시 기록될 파라미터 
		public Int32 m_done_count; 	// [수행한 횟수]  
		
		public  void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output += m_db_id.ToString() + ",";
			output += m_quest_sid.ToString() + ",";
			output += m_uid.ToString() + ",";
			output += m_date_insert.ToString() + ",";
			output += m_date_done.ToString() + ",";
			output += m_info.ToString() + ",";
			output += m_done_count.ToString() + ",";
			return output;
		}
	}//class Tbl_Quest

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Tbl_Result
	{
		public Tbl_Result_id_t m_db_id; 	// [game고유번호]  
		public Tbl_User_id_t m_win_uid; 	// [고유번호] 승자 고유번호 
		public Tbl_PlayerBetter_id_t m_win_better; 	// [타자 pid] 승자 
		public Tbl_PlayerPitcher_id_t m_win_pitcher; 	// [투수 pid] 승자 
		public Int16 m_win_score; 	// [승자스코어]  
		public Int32 m_win_elo_point; 	// [ELO_포인트] 경기에서 승 했을 시 사용자에게 플러스 되는 매칭용 포인트 
		public Tbl_User_id_t m_lose_uid; 	// [고유번호] 패자 고유번호 
		public Tbl_PlayerBetter_id_t m_lose_better; 	// [타자 pid] 패자 
		public Tbl_PlayerPitcher_id_t m_lose_pitcher; 	// [투수 pid] 패자 
		public Int16 m_lose_score; 	// [패자스코어]  
		public Int32 m_lose_elo_point; 	// [ELO_포인트] 경기에서 패 했을 시  사용자에게 마이너스 되는 매칭용 포인트 
		public Int32 m_play_time_sec; 	// [플레이시간] 플레이 한 시간(초) 
		public DATETIME m_time_end; 	// [게임종료시간] 플레이 시간 (2012-12-15 13:53:15) 
		
		public  void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output += m_db_id.ToString() + ",";
			output += m_win_uid.ToString() + ",";
			output += m_win_better.ToString() + ",";
			output += m_win_pitcher.ToString() + ",";
			output += m_win_score.ToString() + ",";
			output += m_win_elo_point.ToString() + ",";
			output += m_lose_uid.ToString() + ",";
			output += m_lose_better.ToString() + ",";
			output += m_lose_pitcher.ToString() + ",";
			output += m_lose_score.ToString() + ",";
			output += m_lose_elo_point.ToString() + ",";
			output += m_play_time_sec.ToString() + ",";
			output += m_time_end.ToString() + ",";
			return output;
		}
	}//class Tbl_Result

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Tbl_RoundResult
	{
		public Tbl_RoundResult_id_t m_db_id; 	// [고유번호] 일별 파티션 키 
		public Tbl_Result_id_t m_grid; 	// [Tbl_Result테이블의 고유번호]  
		public Sys_Better_id_t m_used_batter_id; 	// [선택 된 타자 id] 선택 된 타자 id (8개) 
		public Sys_Pitcher_id_t m_used_pitcher_id; 	// [선택 된 투수 id] 선택 된 투수 id (8개) 
		public Int16 m_round_number; 	// [라운드번호] 1부터시작. 1~10은 라운드 한게임의 토탈집계는 Tbl_Result에 저장 
		public EPlayerBreakingBall m_used_breakingball; 	// [투수의 사용 구종] 사용한 구종의 종류 
		public Int16 m_used_breakingball_speed; 	// [투수의 사용 구종의 구속] 사용한 구종의 속도 
		public EPitcherAbility m_used_pitcherability; 	// [사용하고 있는 투수의 스킬(변화구 제외)] 스텟에 영향을 준 투수의 특수능력 
		public ERhythmJudge m_pitching_rhythm_judge; 	// [투구 시 제구 타이밍] 투구 시 제구 타이밍의 종류 
		public EGestureType m_used_gesturetype; 	// [사용한 제스처 종류] 사용한 제스처 종류 
		public Int16 m_gesturetype_input_error; 	// [제스처 입력 오류 횟수] 제스처 입력 오류 횟수 
		public EHitType m_used_batting_fullpower; 	// [타자 히트 시 라운드 별 풀파워 사용] 타자 히트의 종류(일반히트_스트롱히트_헛스윙_대기상태) 
		public EHitTimmingType m_batting_timing_judge; 	// [타격 시 라운드 별 타격 타이밍] 타격 시 타이밍 종류(veryfast_fast_goodfast_perfect_goodslow_slow_veryslow) 
		public EBatterHitType m_batting_hittype; 	// [타격 시 라운드 별 히트 타입] 타격 시 히트 타입 
		public Tbl_User_id_t m_uid_attack; 	// [uid_attack] 공격자 
		public Int16 m_score; 	// [better의점수]  
		public Int16 m_base_runner_state; 	// [출루한주자수] bit flag로 출루한 주자상태를 표시한다. 1루는 2^0 최대는 xml에서  i_max_runner_per_game=19이다 
		public EBatterHitType m_hit_type; 	// [안타종류]  
		
		public  void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output += m_db_id.ToString() + ",";
			output += m_grid.ToString() + ",";
			output += m_used_batter_id.ToString() + ",";
			output += m_used_pitcher_id.ToString() + ",";
			output += m_round_number.ToString() + ",";
			output += m_used_breakingball.ToString() + ",";
			output += m_used_breakingball_speed.ToString() + ",";
			output += m_used_pitcherability.ToString() + ",";
			output += m_pitching_rhythm_judge.ToString() + ",";
			output += m_used_gesturetype.ToString() + ",";
			output += m_gesturetype_input_error.ToString() + ",";
			output += m_used_batting_fullpower.ToString() + ",";
			output += m_batting_timing_judge.ToString() + ",";
			output += m_batting_hittype.ToString() + ",";
			output += m_uid_attack.ToString() + ",";
			output += m_score.ToString() + ",";
			output += m_base_runner_state.ToString() + ",";
			output += m_hit_type.ToString() + ",";
			return output;
		}
	}//class Tbl_RoundResult

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Tbl_User
	{
		public Tbl_User_id_t m_db_id; 	// [고유번호]  
		public Int64 m_pp_id; 	// [피망ID] MemberInfo의 (game_id)피망에서 온 id를 그대로 사용 
		public string m_host_type; 	// [HOST_TYPE] 0-pp user 1-facebook 2-카톡 
		public string m_uname; 	// [닉네임] 베이스볼에서의 유저닉네임 
		public Int32 m_discon_tot; 	// [총Disconnect수] 게임중간에 나간수 
		public Int32 m_win_tot; 	// [총전적_승] 토탈 승 카운트 
		public Int32 m_win_tot_continue; 	// [연승패] 연속으로 승리한 개수. 음수면 연패 
		public Int32 m_win_tot_continue_max; 	// [최대연승] 최대연승 
		public Int32 m_lose_tot; 	// [총전적_패] 토탈 패 카운트 
		public Int32 m_win_season; 	// [시즌전적_승] 시즌 승 카운트(3개월) 
		public Int32 m_lose_season; 	// [시즌전적_패] 시즌 패 카운트(3개월) 
		public Int16 m_batter_tot_homerun; 	// [총_홈런수] 타자총_홈런 
		public Int16 m_pitcher_tot_strikeout; 	// [탈삼진수] 투수총_탈삼진 
		public Int16 m_batter_tot_homerun_season; 	// [시즌 총_홈런수] 시즌 타자총_홈런 
		public Int16 m_pitcher_tot_strikeout_season; 	// [시즌 탈삼진수] 시즌 투수총_탈삼진 
		public Int32 m_elo_point; 	// [ELO_포인트] 경기마다 캐릭터에 갱신되는 매칭용 포인트 
		public Int64 m_cash_item_buy_money_amount; 	// [캐쉬템구매누적액] 캐쉬템구매 누적액 
		public DATETIME m_time_last_login; 	// [마지막로긴시간] 마지막로긴시간 
		public DATETIME m_time_last_logout; 	// [마지막로그아웃시간] 마지막 로그아웃시간 
		public Int16 m_day_continue_attend; 	// [연속출석일수] 연속출석한 일수 
		public string m_client_os; 	// [client_os] 클라 OS ( IOS  ANDROID ) 
		public string m_client_networ; 	// [client_networ] 클라 네트웍(3G 4G WIFI) 
		public Int64 m_playtime_tot; 	// [총_플레이_타임] 총_플레이_타임(분) 
		
		public  void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output += m_db_id.ToString() + ",";
			output += m_pp_id.ToString() + ",";
			output += m_host_type.ToString() + ",";
			output += m_uname.ToString() + ",";
			output += m_discon_tot.ToString() + ",";
			output += m_win_tot.ToString() + ",";
			output += m_win_tot_continue.ToString() + ",";
			output += m_win_tot_continue_max.ToString() + ",";
			output += m_lose_tot.ToString() + ",";
			output += m_win_season.ToString() + ",";
			output += m_lose_season.ToString() + ",";
			output += m_batter_tot_homerun.ToString() + ",";
			output += m_pitcher_tot_strikeout.ToString() + ",";
			output += m_batter_tot_homerun_season.ToString() + ",";
			output += m_pitcher_tot_strikeout_season.ToString() + ",";
			output += m_elo_point.ToString() + ",";
			output += m_cash_item_buy_money_amount.ToString() + ",";
			output += m_time_last_login.ToString() + ",";
			output += m_time_last_logout.ToString() + ",";
			output += m_day_continue_attend.ToString() + ",";
			output += m_client_os.ToString() + ",";
			output += m_client_networ.ToString() + ",";
			output += m_playtime_tot.ToString() + ",";
			return output;
		}
	}//class Tbl_User

	


	


}//namespace nEXCEL
