
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
	// �������
	// -------------------------------------------------

	[ProtoContract]
	public class s_tbl_quest
	{
		[ProtoMember(1, IsRequired = false)]
		public Tbl_Quest_id_t m_db_id {get; set;}	// [] Tbl_Quest_id_t 
		[ProtoMember(2, IsRequired = false)]
		public Sys_Quest_id_t m_quest_sid {get; set;}	// [����Ʈ���� pp_name�̴�] Sys_Quest_id_t 
		[ProtoMember(3, IsRequired = false)]
		public Tbl_User_id_t m_uid {get; set;}	// [] Tbl_User_id_t 
		[ProtoMember(4, IsRequired = false)]
		public string m_date_insert {get; set;}	// [���� ���� �����] SYSTEMTIME 
		[ProtoMember(5, IsRequired = false)]
		public string m_date_done {get; set;}	// [�Ϸ�� �ð�] SYSTEMTIME 
		[ProtoMember(6, IsRequired = false)]
		public string m_info {get; set;}	// [����Ʈ�� ����� ��ϵ� �Ķ����] aname256_t 
		[ProtoMember(7, IsRequired = false)]
		public Int32 m_done_count {get; set;}	// [] int32 
	}//public class s_tbl_quest

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	[ProtoContract]
	public class s_tbl_result
	{
		[ProtoMember(1, IsRequired = false)]
		public Tbl_Result_id_t m_db_id {get; set;}	// [] Tbl_Result_id_t 
		[ProtoMember(2, IsRequired = false)]
		public Tbl_User_id_t m_win_uid {get; set;}	// [���� ������ȣ] Tbl_User_id_t 
		[ProtoMember(3, IsRequired = false)]
		public Tbl_PlayerBetter_id_t m_win_better {get; set;}	// [����] Tbl_PlayerBetter_id_t 
		[ProtoMember(4, IsRequired = false)]
		public Tbl_PlayerPitcher_id_t m_win_pitcher {get; set;}	// [����] Tbl_PlayerPitcher_id_t 
		[ProtoMember(5, IsRequired = false)]
		public Int16 m_win_score {get; set;}	// [] int8 
		[ProtoMember(6, IsRequired = false)]
		public Int32 m_win_elo_point {get; set;}	// [��⿡�� �� ���� �� ����ڿ��� �÷��� �Ǵ� ��Ī�� ����Ʈ] int32 
		[ProtoMember(7, IsRequired = false)]
		public Tbl_User_id_t m_lose_uid {get; set;}	// [���� ������ȣ] Tbl_User_id_t 
		[ProtoMember(8, IsRequired = false)]
		public Tbl_PlayerBetter_id_t m_lose_better {get; set;}	// [����] Tbl_PlayerBetter_id_t 
		[ProtoMember(9, IsRequired = false)]
		public Tbl_PlayerPitcher_id_t m_lose_pitcher {get; set;}	// [����] Tbl_PlayerPitcher_id_t 
		[ProtoMember(10, IsRequired = false)]
		public Int16 m_lose_score {get; set;}	// [] int8 
		[ProtoMember(11, IsRequired = false)]
		public Int32 m_lose_elo_point {get; set;}	// [��⿡�� �� ���� ��  ����ڿ��� ���̳ʽ� �Ǵ� ��Ī�� ����Ʈ] int32 
		[ProtoMember(12, IsRequired = false)]
		public Int32 m_play_time_sec {get; set;}	// [�÷��� �� �ð�(��)] int32 
		[ProtoMember(13, IsRequired = false)]
		public string m_time_end {get; set;}	// [�÷��� �ð� (2012-12-15 13:53:15)] SYSTEMTIME 
	}//public class s_tbl_result

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	[ProtoContract]
	public class s_tbl_roundresult
	{
		[ProtoMember(1, IsRequired = false)]
		public Tbl_RoundResult_id_t m_db_id {get; set;}	// [�Ϻ� ��Ƽ�� Ű] Tbl_RoundResult_id_t 
		[ProtoMember(2, IsRequired = false)]
		public Tbl_Result_id_t m_grid {get; set;}	// [] Tbl_Result_id_t 
		[ProtoMember(3, IsRequired = false)]
		public Sys_Better_id_t m_used_batter_id {get; set;}	// [���� �� Ÿ�� id (8��)] Sys_Better_id_t 
		[ProtoMember(4, IsRequired = false)]
		public Sys_Pitcher_id_t m_used_pitcher_id {get; set;}	// [���� �� ���� id (8��)] Sys_Pitcher_id_t 
		[ProtoMember(5, IsRequired = false)]
		public Int16 m_round_number {get; set;}	// [1���ͽ���. 1~10�� ���� �Ѱ����� ��Ż����� Tbl_Result�� ����] int8 
		[ProtoMember(6, IsRequired = false)]
		public int m_used_breakingball {get; set;}	// [����� ������ ����] EPlayerBreakingBall 
		[ProtoMember(7, IsRequired = false)]
		public Int16 m_used_breakingball_speed {get; set;}	// [����� ������ �ӵ�] int16 
		[ProtoMember(8, IsRequired = false)]
		public int m_used_pitcherability {get; set;}	// [���ݿ� ������ �� ������ Ư���ɷ�] EPitcherAbility 
		[ProtoMember(9, IsRequired = false)]
		public int m_pitching_rhythm_judge {get; set;}	// [���� �� ���� Ÿ�̹��� ����] ERhythmJudge 
		[ProtoMember(10, IsRequired = false)]
		public int m_used_gesturetype {get; set;}	// [����� ����ó ����] EGestureType 
		[ProtoMember(11, IsRequired = false)]
		public Int16 m_gesturetype_input_error {get; set;}	// [����ó �Է� ���� Ƚ��] int16 
		[ProtoMember(12, IsRequired = false)]
		public int m_used_batting_fullpower {get; set;}	// [Ÿ�� ��Ʈ�� ����(�Ϲ���Ʈ_��Ʈ����Ʈ_�꽺��_������)] EHitType 
		[ProtoMember(13, IsRequired = false)]
		public int m_batting_timing_judge {get; set;}	// [Ÿ�� �� Ÿ�̹� ����(veryfast_fast_goodfast_perfect_goodslow_slow_veryslow)] EHitTimmingType 
		[ProtoMember(14, IsRequired = false)]
		public int m_batting_hittype {get; set;}	// [Ÿ�� �� ��Ʈ Ÿ��] EBatterHitType 
		[ProtoMember(15, IsRequired = false)]
		public Tbl_User_id_t m_uid_attack {get; set;}	// [������] Tbl_User_id_t 
		[ProtoMember(16, IsRequired = false)]
		public Int16 m_score {get; set;}	// [] int8 
		[ProtoMember(17, IsRequired = false)]
		public Int16 m_base_runner_state {get; set;}	// [bit flag�� ����� ���ڻ��¸� ǥ���Ѵ�. 1��� 2^0 �ִ�� xml����  i_max_runner_per_game=19�̴�] int8 
		[ProtoMember(18, IsRequired = false)]
		public int m_hit_type {get; set;}	// [] EBatterHitType 
	}//public class s_tbl_roundresult

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	[ProtoContract]
	public class s_tbl_user
	{
		[ProtoMember(1, IsRequired = false)]
		public Tbl_User_id_t m_db_id {get; set;}	// [] Tbl_User_id_t 
		[ProtoMember(2, IsRequired = false)]
		public Int64 m_pp_id {get; set;}	// [MemberInfo�� (game_id)�Ǹ����� �� id�� �״�� ���] int64 
		[ProtoMember(3, IsRequired = false)]
		public string m_host_type {get; set;}	// [0-pp user 1-facebook 2-ī��] aname32_t 
		[ProtoMember(4, IsRequired = false)]
		public string m_uname {get; set;}	// [���̽��������� �����г���] aname32_t 
		[ProtoMember(5, IsRequired = false)]
		public Int32 m_discon_tot {get; set;}	// [�����߰��� ������] int32 
		[ProtoMember(6, IsRequired = false)]
		public Int32 m_win_tot {get; set;}	// [��Ż �� ī��Ʈ] int32 
		[ProtoMember(7, IsRequired = false)]
		public Int32 m_win_tot_continue {get; set;}	// [�������� �¸��� ����. ������ ����] int32 
		[ProtoMember(8, IsRequired = false)]
		public Int32 m_win_tot_continue_max {get; set;}	// [�ִ뿬��] int32 
		[ProtoMember(9, IsRequired = false)]
		public Int32 m_lose_tot {get; set;}	// [��Ż �� ī��Ʈ] int32 
		[ProtoMember(10, IsRequired = false)]
		public Int32 m_win_season {get; set;}	// [���� �� ī��Ʈ(3����)] int32 
		[ProtoMember(11, IsRequired = false)]
		public Int32 m_lose_season {get; set;}	// [���� �� ī��Ʈ(3����)] int32 
		[ProtoMember(12, IsRequired = false)]
		public Int16 m_batter_tot_homerun {get; set;}	// [Ÿ����_Ȩ��] int16 
		[ProtoMember(13, IsRequired = false)]
		public Int16 m_pitcher_tot_strikeout {get; set;}	// [������_Ż����] int16 
		[ProtoMember(14, IsRequired = false)]
		public Int16 m_batter_tot_homerun_season {get; set;}	// [���� Ÿ����_Ȩ��] int16 
		[ProtoMember(15, IsRequired = false)]
		public Int16 m_pitcher_tot_strikeout_season {get; set;}	// [���� ������_Ż����] int16 
		[ProtoMember(16, IsRequired = false)]
		public Int32 m_elo_point {get; set;}	// [��⸶�� ĳ���Ϳ� ���ŵǴ� ��Ī�� ����Ʈ] int32 
		[ProtoMember(17, IsRequired = false)]
		public Int64 m_cash_item_buy_money_amount {get; set;}	// [ĳ���۱��� ������] int64 
		[ProtoMember(18, IsRequired = false)]
		public string m_time_last_login {get; set;}	// [�������α�ð�] SYSTEMTIME 
		[ProtoMember(19, IsRequired = false)]
		public string m_time_last_logout {get; set;}	// [������ �α׾ƿ��ð�] SYSTEMTIME 
		[ProtoMember(20, IsRequired = false)]
		public Int16 m_day_continue_attend {get; set;}	// [�����⼮�� �ϼ�] int16 
		[ProtoMember(21, IsRequired = false)]
		public string m_client_os {get; set;}	// [Ŭ�� OS ( IOS  ANDROID )] aname32_t 
		[ProtoMember(22, IsRequired = false)]
		public string m_client_networ {get; set;}	// [Ŭ�� ��Ʈ��(3G 4G WIFI)] aname32_t 
		[ProtoMember(23, IsRequired = false)]
		public Int64 m_playtime_tot {get; set;}	// [��_�÷���_Ÿ��(��)] int64 
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


