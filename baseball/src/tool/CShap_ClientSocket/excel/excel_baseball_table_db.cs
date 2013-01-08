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
	// �������
	// -------------------------------------------------

	public class Tbl__PlayerBase
	{
		public Tbl__PlayerBase_id_t m_db_id; 	// [PK index] ���� database table PK 
		public Sys_PlayerCard_id_t m_sid; 	// [Sys_Player���̵�] ������ ����ī���� ��ȣ(Sys_Player�� sid) ���� 0 �̸� ���󼱼� 
		public Tbl_User_id_t m_uid; 	// [������ȣ]  
		public string m_pname; 	// [�г���]  
		public EPlayerNationType m_city; 	// [��ű���] ĳ�־�߱� ���ӱ�ȹ�� 3�� (20111031).docx���� 
		public string m_initial_name; 	// [�̴ϼ�] ������ ����. ������̴ϼȱ���. �ߺ����� 
		public Int16 m_back_number; 	// [��ѹ�] ������ ����. ������������� ���氡�� 
		public Int16 m_age; 	// [����] ������ ����. 
		public EPlayerBodyType m_body_type; 	// [ü��]  
		public bool m_is_left; 	// [�¿�Ÿ��] ĳ������ �¿� ���� 1�̸� �¼��� 0�̸� �켱�� 
		public Int64 m_exp; 	// [����ġ] ������ ����ġ�� �ش��ϴ� Sys_PlayerLevel�� ���� ���� ���� 
		public Sys_Quest_id_t m_questcomplete_count; 	// [����Ʈ�Ϸ�_ī��Ʈ] �Ϸ� ����Ʈ ī��Ʈ 
		public Int16 m_win_continue; 	// [����] �������� �¸��� ���� 
		public Int16 m_lose_continue; 	// [����] ���� ���� ���� 
		public Tbl_Result_id_t m_last_game_result; 	// [���������id] ���������� �÷����� ����� �ĺ��� 
		public Int32 m_win_tot; 	// [������_��] ��Ż �� ī��Ʈ 
		public Int32 m_lose_tot; 	// [������_��] ��Ż �� ī��Ʈ 
		public Int32 m_win_season; 	// [��������_��] ���� �� ī��Ʈ(3����) 
		public Int32 m_lose_season; 	// [��������_��] ���� �� ī��Ʈ(3����) 
		public string m_skill_sticker; 	// [Ư���ɷ��̸�] Sys_PlayeSkillSticker������ name  ";"�� ���еǾ� �������Է� 
		public Int16 m_is_deleted; 	// [is_deleted]  
		public DATETIME m_date_insert; 	// [��Ͻð�] ���ʰ��ӵ���� 
		public DATETIME m_date_update; 	// [�����Ƚð�] �����������ð� 
		public Int32 m_elo_point; 	// [ELO_����Ʈ] ��⸶�� ĳ���Ϳ� ���ŵǴ� ��Ī�� ����Ʈ 
		public Tbl_Team_id_t m_team; 	// [�Ҽ���id] �Ҽӵ� ����ȣ 
		
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
	// �������
	// -------------------------------------------------

	public class Tbl_Friend
	{
		public Tbl_Friend_id_t m_db_id; 	// [id]  
		public Tbl_User_id_t m_uid; 	// [������ȣ]  
		public Tbl_User_id_t m_uid_fiend; 	// [ģ����ȣ]  
		public string m_nic_fiend; 	// [ģ���̸�]  
		public bool m_is_blocked; 	// [is_blocked] ������Ʈ�̳�? 
		public Int16 m_is_deleted; 	// [is_deleted]  
		public Int32 m_win; 	// [ģ��������]  
		public Int32 m_lose; 	// [ģ��������]  
		
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
	// �������
	// -------------------------------------------------

	public class Tbl_Item
	{
		public Tbl_Item_id_t m_db_id; 	// [�����ĺ���] db pk 
		public Sys__ItemBase_id_t m_sid; 	// [������ ����������] Sys__ItemBase_id_t 
		public EItemCategory m_category; 	// [��з�] ��� ���� �Һ� ���� 
		public Tbl_User_id_t m_uid; 	// [������id]  
		public Tbl__PlayerBase_id_t m_used_player_id; 	// [�ͼӵȼ���ID] �ͼӵ� ����id�̸� �Ҹ��������� Ư�����ͼӵ����ʰ���.ĳ���κ� or �����κ� ȯ�ҿ��ΰ� �����ȴ� 
		public string m_upgrade_level; 	// [���׷��̵���] baseball.xml���� ITEM_UPGRADE_LOGIC ���� 
		public DATETIME m_date_end_upgrade; 	// [���׷��̵�����Ϸ�ð�] �����ð����� �̷��� �ð��� ���õǸ� ���׷��̵�����̴�. 
		public string m_etc_info; 	// [��Ÿ����] ���ȣ �������϶��� ���ȣ. ��ŷ �������϶��� ��ŷ���ڸ� ����. 
		public bool m_is_equiped; 	// [��������] �����������ǰ�� ������������ ���� 
		public DATETIME m_date_expire; 	// [�Ⱓ���������ǻ��ð�] �Ⱓ���������ǰ�� ��밡���� �ð� 
		public DATETIME m_date_insert; 	// [�����ѳ�¥] �����ѳ�¥ 
		public DATETIME m_date_update; 	// [�����Ƚð�] �����������ð� 
		public Int16 m_is_deleted; 	// [�����÷���] �������� �����Ȱ�.�Ǵ� ���¡���� �������� 
		public EItemState m_state; 	// [�����ۻ���]  
		public Int16 m_use_count; 	// [��밡���� ���Ƚ��] �Һ�(����)�ǰ�� ��밡���� ������ ��� Ƚ��. ���(����)�ǰ�� ��������(��ø����) 
		
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
	// �������
	// -------------------------------------------------

	public class Tbl_Item_Admin
	{
		public Tbl_Item_id_t m_db_id; 	// [�����ĺ���] db pk 
		public Tbl_Result_id_t m_rid; 	// [���Ӱ���ĺ���] ����������ǰ�� �ش����� �ĺ��� 
		public real_money_t m_bought_real_money; 	// [����ĳ��] ���Ž� ����� ����ĳ�� 
		public real_money_t m_bought_point_money; 	// [��������Ʈ] ���Ž� ����� ����Ʈ 
		public game_money_t m_bought_game_money; 	// [���Ű��ӸӴ�] ���Ž� ����� ���ӸӴ� 
		public EItemBuyType m_item_buy_type; 	// [���Ż���] ������ȹ���� ���� ( ���������  �Ǵ� ��������  or �̺�Ʈ) 
		public Sys_Shop_id_t m_shop_id; 	// [�����ǸŹ�ȣ] �������κ��� �����Ѱ�� �����Ǹ����� 
		
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
	// �������
	// -------------------------------------------------

	public class Tbl_PitcherSkill
	{
		public Tbl_PitcherSkill_id_t m_db_id; 	// [������ȣ]  
		public Tbl_User_id_t m_uid; 	// [������id]  
		public Tbl_PlayerPitcher_id_t m_pid; 	// [��������id] ����Ʈ���� pp_name�̴� 
		public EGestureType m_gesture; 	// [������Ÿ��] ���������� 
		public Int16 m_is_deleted; 	// [�����÷���]  
		public Int32 m_exp; 	// [������ȭ�� ���� �ð�] ������ ��ȭ���� ����� �ð��� ��� 
		public EPlayerBreakingBall m_type; 	// [������ȭ������] ���� ��ȭ������ 
		
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
	// �������
	// -------------------------------------------------

	public class Tbl_PlayerBetter
			: Tbl__PlayerBase
	{
		public Int16 m_batting_average; 	// [Ÿ��] 0.001~0.999 õ������ ǥ�� 
		public Int16 m_continue_homerun_count; 	// [����Ȩ����] ����_Ȩ���� 
		public Int16 m_homeruntotal_count; 	// [��_Ȩ����] ��_Ȩ���� 
		public Int16 m_single_homerun_count; 	// [�̱�Ȩ��ī��Ʈ] �̱�Ȩ�� ī��Ʈ 
		public Int16 m_tworun_homerun_count; 	// [����Ȩ��ī��Ʈ] ����Ȩ�� ī��Ʈ 
		public Int16 m_threerun_homerun_count; 	// [������Ȩ��ī��Ʈ] ������Ȩ�� ī��Ʈ 
		public Int16 m_grandslam_homerun_count; 	// [����Ȩ��ī��Ʈ] ����Ȩ�� ī��Ʈ 
		public Int16 m_one_hit_count; 	// [�Ϸ�Ÿī��Ʈ] �Ϸ�Ÿ ī��Ʈ 
		public Int16 m_double_hit_count; 	// [�̷�Ÿī��Ʈ] �̷�Ÿ ī��Ʈ 
		public Int16 m_triple_hit_count; 	// [���Ÿī��Ʈ] ���Ÿ ī��Ʈ 
		public Int16 m_foul_hit_count; 	// [�Ŀ�ī��Ʈ] �Ŀ� ī��Ʈ 
		public Int16 m_out_hit_count; 	// [�ƿ�ī��Ʈ] �ƿ� ī��Ʈ 
		public Int16 m_score_count; 	// [����ī��Ʈ] ���� ī��Ʈ 
		public EBetterAbility m_betting_type; 	// [Ÿ��Ÿ��] Ÿ�� ������ ��ų 
		public EBetterForm m_betting_form; 	// [Ÿ����] Ÿ�� �� 
		public Int16 m_better_power; 	// [Ÿ�� �Ŀ�]  
		public Int16 m_better_focus; 	// [Ÿ�� ����]  
		public Int16 m_better_power_buff; 	// [Ÿ�� �Ŀ� ����]  
		public Int16 m_better_focus_buff; 	// [Ÿ�� ���� ����]  
		
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
	// �������
	// -------------------------------------------------

	public class Tbl_PlayerPitcher
			: Tbl__PlayerBase
	{
		public Int16 m_pitching_average; 	// [�����] 0.001~0.999 õ������ ǥ�� 
		public Int16 m_hit_count; 	// [�Ǿ�Ÿ��] �Ǿ�Ÿ�� 
		public Int16 m_strikeout_count; 	// [Ż������] Ż������ 
		public Int16 m_homerun_pitching_count; 	// [��Ȩ����] ��Ȩ���� 
		public Int16 m_continue_strikeout_count; 	// [���ӻ�����] ���ӻ����� 
		public Int16 m_continue_homerun_pitching_count; 	// [������Ȩ����] ������Ȩ���� 
		public EPitcherAbility m_pitcher_type; 	// [����Ÿ��] ���� ��Ÿ�� ��ų 
		public EPitcherForm m_pitcher_form; 	// [������] ���� �� 
		public Int16 m_pitcher_control; 	// [���� ����]  
		public Int16 m_pitcher_ballspeed; 	// [���� ����]  
		public Int16 m_pitcher_control_buff; 	// [���� ���� ����]  
		public Int16 m_pitcher_ballspeed_buff; 	// [���� ���� ����]  
		public Int16 m_pitcher_breakingball_value_buff; 	// [���� ��ȭ�� ��ġ ����]  
		
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
	// �������
	// -------------------------------------------------

	public class Tbl_Result
	{
		public Tbl_Result_id_t m_db_id; 	// [game������ȣ]  
		public bool m_is_singlemode; 	// [is_singlemode] 0=��Ƽ�÷��� 1=�̱��÷��� 
		public Tbl_User_id_t m_win_uid; 	// [������ȣ] ���� ������ȣ 
		public Tbl_PlayerBetter_id_t m_win_better; 	// [Ÿ�� pid] ���� 
		public Tbl_PlayerPitcher_id_t m_win_pitcher; 	// [���� pid] ���� 
		public Tbl_Team_id_t m_win_team; 	// [��id]  
		public Int16 m_win_score; 	// [���ڽ��ھ�]  
		public Int32 m_win_reward_exp; 	// [���� �������ġ] �÷��̾�1�� �������ġ 
		public game_money_t m_win_reward_gamemoney; 	// [���� ������ӸӴ�] ������ӸӴ� 
		public Tbl_User_id_t m_lose_uid; 	// [������ȣ] ���� ������ȣ 
		public Tbl_PlayerBetter_id_t m_lose_better; 	// [Ÿ�� pid] ���� 
		public Tbl_PlayerPitcher_id_t m_lose_pitcher; 	// [���� pid] ���� 
		public Tbl_Team_id_t m_lose_team; 	// [������id]  
		public Int16 m_lose_score; 	// [���ڽ��ھ�]  
		public Int32 m_lose_reward_exp; 	// [���� �������ġ] �������ġ 
		public game_money_t m_lose_reward_gamemoney; 	// [���� ������ӸӴ�] ������ӸӴ� 
		public DATETIME m_time_start; 	// [���ӽ��۽ð�] ���� �Ͻ� 
		public DATETIME m_time_end; 	// [��������ð�] �÷��� �ð� 
		
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
	// �������
	// -------------------------------------------------

	public class Tbl_RoundResult
	{
		public Tbl_RoundResult_id_t m_db_id; 	// [������ȣ] �Ϻ� ��Ƽ�� Ű 
		public Tbl_Result_id_t m_grid; 	// [Tbl_Result_M�� ������ȣ]  
		public Int16 m_round_number; 	// [�����ȣ] 1���ͽ���. 1~10�� ���� �Ѱ����� ��Ż����� Tbl_Result�� ���� 
		public Tbl_User_id_t m_uid_attack; 	// [uid_attack] ������ 
		public Int16 m_score; 	// [better������]  
		public Int16 m_base_runner_state; 	// [��������ڼ�] bit flag�� ����� ���ڻ��¸� ǥ���Ѵ�. 1��� 2^0 �ִ�� xml����  i_max_runner_per_game=19�̴� 
		public EBetterHitType m_hit_type; 	// [��Ÿ����] 0=�ƿ� 1�Ϸ�Ÿ 2�̷�Ÿ 3���Ÿ 4�̱�Ȩ�� 5����Ȩ�� 6 
		
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
	// �������
	// -------------------------------------------------

	public class Tbl_Team
	{
		public Tbl_Team_id_t m_db_id; 	// [������ȣ]  
		public string m_name; 	// [���̸�] ����Ʈ���� pp_name�̴� 
		public Tbl_User_id_t m_uid; 	// [����id]  
		public Tbl_PlayerBetter_id_t m_pid_better; 	// [Ÿ��]  
		public Tbl_PlayerPitcher_id_t m_pid_pitcher; 	// [����]  
		public Int16 m_is_deleted; 	// [�����÷���] �������� �����Ȱ�.�Ǵ� ���¡���� �������� 
		public Int16 m_win; 	// [��]  
		public Int16 m_lose; 	// [��]  
		
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
	// �������
	// -------------------------------------------------

	public class Tbl_User
	{
		public Tbl_User_id_t m_db_id; 	// [������ȣ] db pk �Ǹ����� �� id�� �״�� ��� 
		public string m_uname; 	// [�г���] ���̽��������� �����г��� 
		public Int16 m_tot_win; 	// [������_��] ����������_�� 
		public Int16 m_tot_lose; 	// [������_��] ����������_�� 
		public Int16 m_pitcher_tot_strikeout; 	// [Ż������] ������_Ż���� 
		public Int16 m_pitcher_tot_average_level; 	// [���������_����] ���������_���� �ַ� ����� �����ΰ� 
		public Int16 m_better_tot_homerun; 	// [��_Ȩ����] Ÿ����_Ȩ�� 
		public Int16 m_better_tot__average_level; 	// [Ÿ�������_����] Ÿ�������_���� 
		public Int16 m_cash_item_buy_count; 	// [ĳ���۱��Ű���] ĳ���۱��Ű��� 
		public DATETIME m_time_last_login; 	// [�������α�ð�] �������α�ð� 
		public DATETIME m_time_last_logout; 	// [�������α׾ƿ��ð�] ������ �α׾ƿ��ð� 
		public Int16 m_day_continue_attend; 	// [�����⼮�ϼ�] �����⼮�� �ϼ� 
		public DATETIME m_date_insert; 	// [��Ͻð�] ���ʰ��ӵ���� 
		public DATETIME m_date_update; 	// [�����Ƚð�] �����������ð� 
		public Tbl_Team_id_t m_default_tid; 	// [�⺻����ȣ] �⺻�� index 
		public string m_option; 	// [�ɼ�] �ɼ�(Ŭ�󿡼����Ƿ������ҳ���) 
		public Int16 m_is_deleted; 	// [�����÷���] �������� �����Ȱ�.�Ǵ� ���¡���� �������� 
		public Int64 m_game_money; 	// [���ӸӴ�]  
		public Int64 m_playtime_tot; 	// [��_�÷���_Ÿ��] ��_�÷���_Ÿ��(��) 
		
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
