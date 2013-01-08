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
	// �������
	// -------------------------------------------------

	public class Tbl_Quest
	{
		public Tbl_Quest_id_t m_db_id; 	// [������ȣ]  
		public Sys_Quest_id_t m_quest_sid; 	// [������ ����Ʈ sid] ����Ʈ���� pp_name�̴� 
		public Tbl_User_id_t m_uid; 	// [����id]  
		public DATETIME m_date_insert; 	// [��Ͻð�] ���� ���� ����� 
		public DATETIME m_date_done; 	// [�Ϸ�ð�] �Ϸ�� �ð� 
		public string m_info; 	// [���� ����] ����Ʈ�� ����� ��ϵ� �Ķ���� 
		public Int32 m_done_count; 	// [������ Ƚ��]  
		
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
	// �������
	// -------------------------------------------------

	public class Tbl_Result
	{
		public Tbl_Result_id_t m_db_id; 	// [game������ȣ]  
		public Tbl_User_id_t m_win_uid; 	// [������ȣ] ���� ������ȣ 
		public Tbl_PlayerBetter_id_t m_win_better; 	// [Ÿ�� pid] ���� 
		public Tbl_PlayerPitcher_id_t m_win_pitcher; 	// [���� pid] ���� 
		public Int16 m_win_score; 	// [���ڽ��ھ�]  
		public Int32 m_win_elo_point; 	// [ELO_����Ʈ] ��⿡�� �� ���� �� ����ڿ��� �÷��� �Ǵ� ��Ī�� ����Ʈ 
		public Tbl_User_id_t m_lose_uid; 	// [������ȣ] ���� ������ȣ 
		public Tbl_PlayerBetter_id_t m_lose_better; 	// [Ÿ�� pid] ���� 
		public Tbl_PlayerPitcher_id_t m_lose_pitcher; 	// [���� pid] ���� 
		public Int16 m_lose_score; 	// [���ڽ��ھ�]  
		public Int32 m_lose_elo_point; 	// [ELO_����Ʈ] ��⿡�� �� ���� ��  ����ڿ��� ���̳ʽ� �Ǵ� ��Ī�� ����Ʈ 
		public Int32 m_play_time_sec; 	// [�÷��̽ð�] �÷��� �� �ð�(��) 
		public DATETIME m_time_end; 	// [��������ð�] �÷��� �ð� (2012-12-15 13:53:15) 
		
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
	// �������
	// -------------------------------------------------

	public class Tbl_RoundResult
	{
		public Tbl_RoundResult_id_t m_db_id; 	// [������ȣ] �Ϻ� ��Ƽ�� Ű 
		public Tbl_Result_id_t m_grid; 	// [Tbl_Result���̺��� ������ȣ]  
		public Sys_Better_id_t m_used_batter_id; 	// [���� �� Ÿ�� id] ���� �� Ÿ�� id (8��) 
		public Sys_Pitcher_id_t m_used_pitcher_id; 	// [���� �� ���� id] ���� �� ���� id (8��) 
		public Int16 m_round_number; 	// [�����ȣ] 1���ͽ���. 1~10�� ���� �Ѱ����� ��Ż����� Tbl_Result�� ���� 
		public EPlayerBreakingBall m_used_breakingball; 	// [������ ��� ����] ����� ������ ���� 
		public Int16 m_used_breakingball_speed; 	// [������ ��� ������ ����] ����� ������ �ӵ� 
		public EPitcherAbility m_used_pitcherability; 	// [����ϰ� �ִ� ������ ��ų(��ȭ�� ����)] ���ݿ� ������ �� ������ Ư���ɷ� 
		public ERhythmJudge m_pitching_rhythm_judge; 	// [���� �� ���� Ÿ�̹�] ���� �� ���� Ÿ�̹��� ���� 
		public EGestureType m_used_gesturetype; 	// [����� ����ó ����] ����� ����ó ���� 
		public Int16 m_gesturetype_input_error; 	// [����ó �Է� ���� Ƚ��] ����ó �Է� ���� Ƚ�� 
		public EHitType m_used_batting_fullpower; 	// [Ÿ�� ��Ʈ �� ���� �� Ǯ�Ŀ� ���] Ÿ�� ��Ʈ�� ����(�Ϲ���Ʈ_��Ʈ����Ʈ_�꽺��_������) 
		public EHitTimmingType m_batting_timing_judge; 	// [Ÿ�� �� ���� �� Ÿ�� Ÿ�̹�] Ÿ�� �� Ÿ�̹� ����(veryfast_fast_goodfast_perfect_goodslow_slow_veryslow) 
		public EBatterHitType m_batting_hittype; 	// [Ÿ�� �� ���� �� ��Ʈ Ÿ��] Ÿ�� �� ��Ʈ Ÿ�� 
		public Tbl_User_id_t m_uid_attack; 	// [uid_attack] ������ 
		public Int16 m_score; 	// [better������]  
		public Int16 m_base_runner_state; 	// [��������ڼ�] bit flag�� ����� ���ڻ��¸� ǥ���Ѵ�. 1��� 2^0 �ִ�� xml����  i_max_runner_per_game=19�̴� 
		public EBatterHitType m_hit_type; 	// [��Ÿ����]  
		
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
	// �������
	// -------------------------------------------------

	public class Tbl_User
	{
		public Tbl_User_id_t m_db_id; 	// [������ȣ]  
		public Int64 m_pp_id; 	// [�Ǹ�ID] MemberInfo�� (game_id)�Ǹ����� �� id�� �״�� ��� 
		public string m_host_type; 	// [HOST_TYPE] 0-pp user 1-facebook 2-ī�� 
		public string m_uname; 	// [�г���] ���̽��������� �����г��� 
		public Int32 m_discon_tot; 	// [��Disconnect��] �����߰��� ������ 
		public Int32 m_win_tot; 	// [������_��] ��Ż �� ī��Ʈ 
		public Int32 m_win_tot_continue; 	// [������] �������� �¸��� ����. ������ ���� 
		public Int32 m_win_tot_continue_max; 	// [�ִ뿬��] �ִ뿬�� 
		public Int32 m_lose_tot; 	// [������_��] ��Ż �� ī��Ʈ 
		public Int32 m_win_season; 	// [��������_��] ���� �� ī��Ʈ(3����) 
		public Int32 m_lose_season; 	// [��������_��] ���� �� ī��Ʈ(3����) 
		public Int16 m_batter_tot_homerun; 	// [��_Ȩ����] Ÿ����_Ȩ�� 
		public Int16 m_pitcher_tot_strikeout; 	// [Ż������] ������_Ż���� 
		public Int16 m_batter_tot_homerun_season; 	// [���� ��_Ȩ����] ���� Ÿ����_Ȩ�� 
		public Int16 m_pitcher_tot_strikeout_season; 	// [���� Ż������] ���� ������_Ż���� 
		public Int32 m_elo_point; 	// [ELO_����Ʈ] ��⸶�� ĳ���Ϳ� ���ŵǴ� ��Ī�� ����Ʈ 
		public Int64 m_cash_item_buy_money_amount; 	// [ĳ���۱��Ŵ�����] ĳ���۱��� ������ 
		public DATETIME m_time_last_login; 	// [�������α�ð�] �������α�ð� 
		public DATETIME m_time_last_logout; 	// [�������α׾ƿ��ð�] ������ �α׾ƿ��ð� 
		public Int16 m_day_continue_attend; 	// [�����⼮�ϼ�] �����⼮�� �ϼ� 
		public string m_client_os; 	// [client_os] Ŭ�� OS ( IOS  ANDROID ) 
		public string m_client_networ; 	// [client_networ] Ŭ�� ��Ʈ��(3G 4G WIFI) 
		public Int64 m_playtime_tot; 	// [��_�÷���_Ÿ��] ��_�÷���_Ÿ��(��) 
		
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
