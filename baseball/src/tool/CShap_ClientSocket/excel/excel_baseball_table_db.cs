/*------------------------------------------------------------


command line : 
Excel_Converter.exe E:\svn\baseball\doc\design\excel\code\excel_baseball_table_etc.txt E:\svn\baseball\doc\design\excel\code\excel_enum.txt E:\svn\baseball\doc\design\excel\code\excel_baseball_table.txt E:\svn\baseball\doc\design\excel\code\excel_baseball_table_db.txt E:\svn\baseball\doc\design\excel\code\excel_baseball_table_item.txt E:\svn\baseball\doc\design\excel\code\excel_baseball_string_table.txt 

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
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Tbl__PlayerBase
	{
		public Tbl__PlayerBase_id_t m_db_id; 	// [PK index] 선수 database table PK 
		public Sys_PlayerCard_id_t m_sid; 	// [Sys_Player아이디] 구매한 선수카드의 번호(Sys_Player의 sid) 값이 0 이면 가상선수 
		public Tbl_User_id_t m_uid; 	// [유저번호]  
		public string m_pname; 	// [닉네임]  
		public EPlayerNationType m_city; 	// [출신국가] 캐주얼야구 게임기획서 3차 (20111031).docx참조 
		public string m_initial_name; 	// [이니셜] 생성시 세팅. 등뒤의이니셜글자. 중복가능 
		public Int16 m_back_number; 	// [백넘버] 생성시 세팅. 변경아이템으로 변경가능 
		public Int16 m_age; 	// [나이] 생성시 세팅. 
		public EPlayerBodyType m_body_type; 	// [체형]  
		public bool m_is_left; 	// [좌우타입] 캐릭터의 좌우 구분 1이면 좌선수 0이면 우선수 
		public Int64 m_exp; 	// [경험치] 레벨은 경험치에 해당하는 Sys_PlayerLevel의 값에 따라 결정 
		public Sys_Quest_id_t m_questcomplete_count; 	// [퀘스트완료_카운트] 완료 퀘스트 카운트 
		public Int16 m_win_continue; 	// [연승] 연속으로 승리한 개수 
		public Int16 m_lose_continue; 	// [연패] 연속 패한 개수 
		public Tbl_Result_id_t m_last_game_result; 	// [마지막경기id] 마지막으로 플레이한 경기결과 식별자 
		public Int32 m_win_tot; 	// [총전적_승] 토탈 승 카운트 
		public Int32 m_lose_tot; 	// [총전적_패] 토탈 패 카운트 
		public Int32 m_win_season; 	// [시즌전적_승] 시즌 승 카운트(3개월) 
		public Int32 m_lose_season; 	// [시즌전적_패] 시즌 패 카운트(3개월) 
		public string m_skill_sticker; 	// [특수능력이름] Sys_PlayeSkillSticker에서의 name  ";"로 구분되어 여러개입력 
		public Int16 m_is_deleted; 	// [is_deleted]  
		public DATETIME m_date_insert; 	// [등록시간] 최초게임등록일 
		public DATETIME m_date_update; 	// [수정된시간] 마지막수정시간 
		public Int32 m_elo_point; 	// [ELO_포인트] 경기마다 캐릭터에 갱신되는 매칭용 포인트 
		public Tbl_Team_id_t m_team; 	// [소속팀id] 소속된 팀번호 
		
		public  void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output += m_db_id.ToString() + ",";
			output += m_sid.ToString() + ",";
			output += m_uid.ToString() + ",";
			output += m_pname.ToString() + ",";
			output += m_city.ToString() + ",";
			output += m_initial_name.ToString() + ",";
			output += m_back_number.ToString() + ",";
			output += m_age.ToString() + ",";
			output += m_body_type.ToString() + ",";
			output += m_is_left.ToString() + ",";
			output += m_exp.ToString() + ",";
			output += m_questcomplete_count.ToString() + ",";
			output += m_win_continue.ToString() + ",";
			output += m_lose_continue.ToString() + ",";
			output += m_last_game_result.ToString() + ",";
			output += m_win_tot.ToString() + ",";
			output += m_lose_tot.ToString() + ",";
			output += m_win_season.ToString() + ",";
			output += m_lose_season.ToString() + ",";
			output += m_skill_sticker.ToString() + ",";
			output += m_is_deleted.ToString() + ",";
			output += m_date_insert.ToString() + ",";
			output += m_date_update.ToString() + ",";
			output += m_elo_point.ToString() + ",";
			output += m_team.ToString() + ",";
			return output;
		}
	}//class Tbl__PlayerBase

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Tbl_Friend
	{
		public Tbl_Friend_id_t m_db_id; 	// [id]  
		public Tbl_User_id_t m_uid; 	// [유저번호]  
		public Tbl_User_id_t m_uid_fiend; 	// [친구번호]  
		public string m_nic_fiend; 	// [친구이름]  
		public bool m_is_blocked; 	// [is_blocked] 블랙리스트이냐? 
		public Int16 m_is_deleted; 	// [is_deleted]  
		public Int32 m_win; 	// [친구전적승]  
		public Int32 m_lose; 	// [친구전적패]  
		
		public  void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output += m_db_id.ToString() + ",";
			output += m_uid.ToString() + ",";
			output += m_uid_fiend.ToString() + ",";
			output += m_nic_fiend.ToString() + ",";
			output += m_is_blocked.ToString() + ",";
			output += m_is_deleted.ToString() + ",";
			output += m_win.ToString() + ",";
			output += m_lose.ToString() + ",";
			return output;
		}
	}//class Tbl_Friend

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Tbl_Item
	{
		public Tbl_Item_id_t m_db_id; 	// [고유식별자] db pk 
		public Sys__ItemBase_id_t m_sid; 	// [구매한 아이템종류] Sys__ItemBase_id_t 
		public EItemCategory m_category; 	// [대분류] 장비 스텁 소비 구분 
		public Tbl_User_id_t m_uid; 	// [소유자id]  
		public Tbl__PlayerBase_id_t m_used_player_id; 	// [귀속된선수ID] 귀속된 선수id이며 소모용아이템은 특별히귀속되지않고쓴다.캐쉬인벤 or 게임인벤 환불여부가 결정된다 
		public string m_upgrade_level; 	// [업그레이드등급] baseball.xml에서 ITEM_UPGRADE_LOGIC 참조 
		public DATETIME m_date_end_upgrade; 	// [업그레이드진행완료시간] 현제시간보다 미래의 시간이 세팅되면 업그레이드상태이다. 
		public string m_etc_info; 	// [기타정보] 등번호 아이템일때는 등번호. 마킹 아이템일때는 마킹글자를 저장. 
		public bool m_is_equiped; 	// [장착상태] 장착아이템의경우 장착상태인지 여부 
		public DATETIME m_date_expire; 	// [기간제아이템의사용시간] 기간제아이템의경우 사용가능한 시간 
		public DATETIME m_date_insert; 	// [구매한날짜] 구매한날짜 
		public DATETIME m_date_update; 	// [수정된시간] 마지막수정시간 
		public Int16 m_is_deleted; 	// [삭제플레그] 아이템이 삭제된것.또는 어뷰징으로 제제상태 
		public EItemState m_state; 	// [아이템상태]  
		public Int16 m_use_count; 	// [사용가능한 경기횟수] 소비(컨슘)의경우 사용가능한 게임의 경기 횟수. 재료(스텁)의경우 보유갯수(중첩갯수) 
		
		public  void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output += m_db_id.ToString() + ",";
			output += m_sid.ToString() + ",";
			output += m_category.ToString() + ",";
			output += m_uid.ToString() + ",";
			output += m_used_player_id.ToString() + ",";
			output += m_upgrade_level.ToString() + ",";
			output += m_date_end_upgrade.ToString() + ",";
			output += m_etc_info.ToString() + ",";
			output += m_is_equiped.ToString() + ",";
			output += m_date_expire.ToString() + ",";
			output += m_date_insert.ToString() + ",";
			output += m_date_update.ToString() + ",";
			output += m_is_deleted.ToString() + ",";
			output += m_state.ToString() + ",";
			output += m_use_count.ToString() + ",";
			return output;
		}
	}//class Tbl_Item

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Tbl_Item_Admin
	{
		public Tbl_Item_id_t m_db_id; 	// [고유식별자] db pk 
		public Tbl_Result_id_t m_rid; 	// [게임결과식별자] 보상아이템의경우 해당경기결과 식별자 
		public real_money_t m_bought_real_money; 	// [구매캐쉬] 구매시 사용한 리얼캐쉬 
		public real_money_t m_bought_point_money; 	// [구매포인트] 구매시 사용한 포인트 
		public game_money_t m_bought_game_money; 	// [구매게임머니] 구매시 사용한 게임머니 
		public EItemBuyType m_item_buy_type; 	// [구매상태] 아이템획득경로 정보 ( 보상아이템  또는 상점구매  or 이벤트) 
		public Sys_Shop_id_t m_shop_id; 	// [상점판매번호] 상점으로부터 구매한경우 상점판매정보 
		
		public  void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output += m_db_id.ToString() + ",";
			output += m_rid.ToString() + ",";
			output += m_bought_real_money.ToString() + ",";
			output += m_bought_point_money.ToString() + ",";
			output += m_bought_game_money.ToString() + ",";
			output += m_item_buy_type.ToString() + ",";
			output += m_shop_id.ToString() + ",";
			return output;
		}
	}//class Tbl_Item_Admin

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Tbl_PitcherSkill
	{
		public Tbl_PitcherSkill_id_t m_db_id; 	// [고유번호]  
		public Tbl_User_id_t m_uid; 	// [소유자id]  
		public Tbl_PlayerPitcher_id_t m_pid; 	// [소유투수id] 디펄트명은 pp_name이다 
		public EGestureType m_gesture; 	// [제스쳐타입] 제스쳐종류 
		public Int16 m_is_deleted; 	// [삭제플레그]  
		public Int32 m_exp; 	// [투수변화구 진행 시간] 각각의 변화구에 진행된 시간을 기록 
		public EPlayerBreakingBall m_type; 	// [투수변화구종류] 투수 변화구종류 
		
		public  void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output += m_db_id.ToString() + ",";
			output += m_uid.ToString() + ",";
			output += m_pid.ToString() + ",";
			output += m_gesture.ToString() + ",";
			output += m_is_deleted.ToString() + ",";
			output += m_exp.ToString() + ",";
			output += m_type.ToString() + ",";
			return output;
		}
	}//class Tbl_PitcherSkill

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Tbl_PlayerBetter
			: Tbl__PlayerBase
	{
		public Int16 m_batting_average; 	// [타율] 0.001~0.999 천분율로 표시 
		public Int16 m_continue_homerun_count; 	// [연속홈런수] 연속_홈런수 
		public Int16 m_homeruntotal_count; 	// [총_홈런수] 총_홈런수 
		public Int16 m_single_homerun_count; 	// [싱글홈런카운트] 싱글홈런 카운트 
		public Int16 m_tworun_homerun_count; 	// [더블홈런카운트] 더블홈런 카운트 
		public Int16 m_threerun_homerun_count; 	// [쓰리런홈런카운트] 쓰리런홈런 카운트 
		public Int16 m_grandslam_homerun_count; 	// [만루홈런카운트] 만루홈런 카운트 
		public Int16 m_one_hit_count; 	// [일루타카운트] 일루타 카운트 
		public Int16 m_double_hit_count; 	// [이루타카운트] 이루타 카운트 
		public Int16 m_triple_hit_count; 	// [삼루타카운트] 삼루타 카운트 
		public Int16 m_foul_hit_count; 	// [파울카운트] 파울 카운트 
		public Int16 m_out_hit_count; 	// [아웃카운트] 아웃 카운트 
		public Int16 m_score_count; 	// [점수카운트] 점수 카운트 
		public EBetterAbility m_betting_type; 	// [타자타입] 타자 대투수 스킬 
		public EBetterForm m_betting_form; 	// [타격폼] 타자 폼 
		public Int16 m_better_power; 	// [타자 파워]  
		public Int16 m_better_focus; 	// [타자 집중]  
		public Int16 m_better_power_buff; 	// [타자 파워 버프]  
		public Int16 m_better_focus_buff; 	// [타자 집중 버프]  
		
		public new void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_batting_average.ToString() + ",";
			output += m_continue_homerun_count.ToString() + ",";
			output += m_homeruntotal_count.ToString() + ",";
			output += m_single_homerun_count.ToString() + ",";
			output += m_tworun_homerun_count.ToString() + ",";
			output += m_threerun_homerun_count.ToString() + ",";
			output += m_grandslam_homerun_count.ToString() + ",";
			output += m_one_hit_count.ToString() + ",";
			output += m_double_hit_count.ToString() + ",";
			output += m_triple_hit_count.ToString() + ",";
			output += m_foul_hit_count.ToString() + ",";
			output += m_out_hit_count.ToString() + ",";
			output += m_score_count.ToString() + ",";
			output += m_betting_type.ToString() + ",";
			output += m_betting_form.ToString() + ",";
			output += m_better_power.ToString() + ",";
			output += m_better_focus.ToString() + ",";
			output += m_better_power_buff.ToString() + ",";
			output += m_better_focus_buff.ToString() + ",";
			return output;
		}
	}//class Tbl_PlayerBetter

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Tbl_PlayerPitcher
			: Tbl__PlayerBase
	{
		public Int16 m_pitching_average; 	// [방어율] 0.001~0.999 천분율로 표시 
		public Int16 m_hit_count; 	// [피안타율] 피안타율 
		public Int16 m_strikeout_count; 	// [탈삼진수] 탈삼진수 
		public Int16 m_homerun_pitching_count; 	// [피홈런수] 피홈런수 
		public Int16 m_continue_strikeout_count; 	// [연속삼진수] 연속삼진수 
		public Int16 m_continue_homerun_pitching_count; 	// [연속피홈런수] 연속피홈런수 
		public EPitcherAbility m_pitcher_type; 	// [투수타입] 투수 대타자 스킬 
		public EPitcherForm m_pitcher_form; 	// [투구폼] 투수 폼 
		public Int16 m_pitcher_control; 	// [투수 제구]  
		public Int16 m_pitcher_ballspeed; 	// [투수 구속]  
		public Int16 m_pitcher_control_buff; 	// [투수 제구 버프]  
		public Int16 m_pitcher_ballspeed_buff; 	// [투수 구속 버프]  
		public Int16 m_pitcher_breakingball_value_buff; 	// [투수 변화구 수치 버프]  
		
		public new void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_pitching_average.ToString() + ",";
			output += m_hit_count.ToString() + ",";
			output += m_strikeout_count.ToString() + ",";
			output += m_homerun_pitching_count.ToString() + ",";
			output += m_continue_strikeout_count.ToString() + ",";
			output += m_continue_homerun_pitching_count.ToString() + ",";
			output += m_pitcher_type.ToString() + ",";
			output += m_pitcher_form.ToString() + ",";
			output += m_pitcher_control.ToString() + ",";
			output += m_pitcher_ballspeed.ToString() + ",";
			output += m_pitcher_control_buff.ToString() + ",";
			output += m_pitcher_ballspeed_buff.ToString() + ",";
			output += m_pitcher_breakingball_value_buff.ToString() + ",";
			return output;
		}
	}//class Tbl_PlayerPitcher

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Tbl_Result
	{
		public Tbl_Result_id_t m_db_id; 	// [game고유번호]  
		public bool m_is_singlemode; 	// [is_singlemode] 0=멀티플레이 1=싱글플레이 
		public Tbl_User_id_t m_win_uid; 	// [고유번호] 승자 고유번호 
		public Tbl_PlayerBetter_id_t m_win_better; 	// [타자 pid] 승자 
		public Tbl_PlayerPitcher_id_t m_win_pitcher; 	// [투수 pid] 승자 
		public Tbl_Team_id_t m_win_team; 	// [팀id]  
		public Int16 m_win_score; 	// [승자스코어]  
		public Int32 m_win_reward_exp; 	// [승자 보상경험치] 플레이어1의 보상경험치 
		public game_money_t m_win_reward_gamemoney; 	// [승자 보상게임머니] 보상게임머니 
		public Tbl_User_id_t m_lose_uid; 	// [고유번호] 패자 고유번호 
		public Tbl_PlayerBetter_id_t m_lose_better; 	// [타자 pid] 패자 
		public Tbl_PlayerPitcher_id_t m_lose_pitcher; 	// [투수 pid] 패자 
		public Tbl_Team_id_t m_lose_team; 	// [패자팀id]  
		public Int16 m_lose_score; 	// [패자스코어]  
		public Int32 m_lose_reward_exp; 	// [패자 보상경험치] 보상경험치 
		public game_money_t m_lose_reward_gamemoney; 	// [패자 보상게임머니] 보상게임머니 
		public DATETIME m_time_start; 	// [게임시작시간] 시작 일시 
		public DATETIME m_time_end; 	// [게임종료시간] 플레이 시간 
		
		public  void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output += m_db_id.ToString() + ",";
			output += m_is_singlemode.ToString() + ",";
			output += m_win_uid.ToString() + ",";
			output += m_win_better.ToString() + ",";
			output += m_win_pitcher.ToString() + ",";
			output += m_win_team.ToString() + ",";
			output += m_win_score.ToString() + ",";
			output += m_win_reward_exp.ToString() + ",";
			output += m_win_reward_gamemoney.ToString() + ",";
			output += m_lose_uid.ToString() + ",";
			output += m_lose_better.ToString() + ",";
			output += m_lose_pitcher.ToString() + ",";
			output += m_lose_team.ToString() + ",";
			output += m_lose_score.ToString() + ",";
			output += m_lose_reward_exp.ToString() + ",";
			output += m_lose_reward_gamemoney.ToString() + ",";
			output += m_time_start.ToString() + ",";
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
		public Tbl_Result_id_t m_grid; 	// [Tbl_Result_M의 고유번호]  
		public Int16 m_round_number; 	// [라운드번호] 1부터시작. 1~10은 라운드 한게임의 토탈집계는 Tbl_Result에 저장 
		public Tbl_User_id_t m_uid_attack; 	// [uid_attack] 공격자 
		public Int16 m_score; 	// [better의점수]  
		public Int16 m_base_runner_state; 	// [출루한주자수] bit flag로 출루한 주자상태를 표시한다. 1루는 2^0 최대는 xml에서  i_max_runner_per_game=19이다 
		public EBetterHitType m_hit_type; 	// [안타종류] 0=아웃 1일루타 2이루타 3삼루타 4싱글홈런 5더블홈런 6 
		
		public  void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output += m_db_id.ToString() + ",";
			output += m_grid.ToString() + ",";
			output += m_round_number.ToString() + ",";
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

	public class Tbl_Team
	{
		public Tbl_Team_id_t m_db_id; 	// [고유번호]  
		public string m_name; 	// [팀이름] 디펄트명은 pp_name이다 
		public Tbl_User_id_t m_uid; 	// [유저id]  
		public Tbl_PlayerBetter_id_t m_pid_better; 	// [타자]  
		public Tbl_PlayerPitcher_id_t m_pid_pitcher; 	// [투수]  
		public Int16 m_is_deleted; 	// [삭제플레그] 아이템이 삭제된것.또는 어뷰징으로 제제상태 
		public Int16 m_win; 	// [승]  
		public Int16 m_lose; 	// [패]  
		
		public  void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output += m_db_id.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_uid.ToString() + ",";
			output += m_pid_better.ToString() + ",";
			output += m_pid_pitcher.ToString() + ",";
			output += m_is_deleted.ToString() + ",";
			output += m_win.ToString() + ",";
			output += m_lose.ToString() + ",";
			return output;
		}
	}//class Tbl_Team

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Tbl_User
	{
		public Tbl_User_id_t m_db_id; 	// [고유번호] db pk 피망에서 온 id를 그대로 사용 
		public string m_uname; 	// [닉네임] 베이스볼에서의 유저닉네임 
		public Int16 m_tot_win; 	// [총전적_승] 투수총전적_승 
		public Int16 m_tot_lose; 	// [총전적_패] 투수총전적_패 
		public Int16 m_pitcher_tot_strikeout; 	// [탈삼진수] 투수총_탈삼진 
		public Int16 m_pitcher_tot_average_level; 	// [투수총평균_레벨] 투수총평균_레벨 멀로 평균을 낼것인가 
		public Int16 m_better_tot_homerun; 	// [총_홈런수] 타자총_홈런 
		public Int16 m_better_tot__average_level; 	// [타자총평균_레벨] 타자총평균_레벨 
		public Int16 m_cash_item_buy_count; 	// [캐쉬템구매갯수] 캐쉬템구매갯수 
		public DATETIME m_time_last_login; 	// [마지막로긴시간] 마지막로긴시간 
		public DATETIME m_time_last_logout; 	// [마지막로그아웃시간] 마지막 로그아웃시간 
		public Int16 m_day_continue_attend; 	// [연속출석일수] 연속출석한 일수 
		public DATETIME m_date_insert; 	// [등록시간] 최초게임등록일 
		public DATETIME m_date_update; 	// [수정된시간] 마지막수정시간 
		public Tbl_Team_id_t m_default_tid; 	// [기본팀번호] 기본팀 index 
		public string m_option; 	// [옵션] 옵션(클라에서임의로저장할내용) 
		public Int16 m_is_deleted; 	// [삭제플레그] 아이템이 삭제된것.또는 어뷰징으로 제제상태 
		public Int64 m_game_money; 	// [게임머니]  
		public Int64 m_playtime_tot; 	// [총_플레이_타임] 총_플레이_타임(분) 
		
		public  void Print(){Console.WriteLine(ToString());}
		public override string ToString()
		{
			string output = "";
			output += m_db_id.ToString() + ",";
			output += m_uname.ToString() + ",";
			output += m_tot_win.ToString() + ",";
			output += m_tot_lose.ToString() + ",";
			output += m_pitcher_tot_strikeout.ToString() + ",";
			output += m_pitcher_tot_average_level.ToString() + ",";
			output += m_better_tot_homerun.ToString() + ",";
			output += m_better_tot__average_level.ToString() + ",";
			output += m_cash_item_buy_count.ToString() + ",";
			output += m_time_last_login.ToString() + ",";
			output += m_time_last_logout.ToString() + ",";
			output += m_day_continue_attend.ToString() + ",";
			output += m_date_insert.ToString() + ",";
			output += m_date_update.ToString() + ",";
			output += m_default_tid.ToString() + ",";
			output += m_option.ToString() + ",";
			output += m_is_deleted.ToString() + ",";
			output += m_game_money.ToString() + ",";
			output += m_playtime_tot.ToString() + ",";
			return output;
		}
	}//class Tbl_User

	


	


}//namespace nEXCEL
