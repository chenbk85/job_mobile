
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
	public class s_sys_base_playerstat
	{
		[ProtoMember(1, IsRequired = false)]
		public Int16 m_sid {get; set;}	// [] int16 
		[ProtoMember(2, IsRequired = false)]
		public string m_name {get; set;}	// [�����̸� �����ؾ���. �̿����̸����� ��Ʈ�����̺��� �ѱ��̸��˻�] aname32_t 
		[ProtoMember(3, IsRequired = false)]
		public Int16 m_better_power {get; set;}	// [] int16 
		[ProtoMember(4, IsRequired = false)]
		public Int16 m_better_focus {get; set;}	// [] int16 
		[ProtoMember(5, IsRequired = false)]
		public Int16 m_pitcher_control {get; set;}	// [] int16 
		[ProtoMember(6, IsRequired = false)]
		public Int16 m_pitcher_ballspeed {get; set;}	// [������ ���ڴ� ���̳ʽ��� ����] int16 
		[ProtoMember(7, IsRequired = false)]
		public Int16 m_pitcher_breakingball_value {get; set;}	// [] int16 
		[ProtoMember(8, IsRequired = false)]
		public int m_pitcher_breakingball_type {get; set;}	// [���� ��ȭ��] EPlayerBreakingBall 
	}//public class s_sys_base_playerstat

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	[ProtoContract]
	public class s_sys_playercard
	{
			[ProtoMember(1, IsRequired = false)]
			public Int16 m_sid {get; set;}	// [] int16 
			[ProtoMember(2, IsRequired = false)]
			public string m_name {get; set;}	// [�����̸� �����ؾ���. �̿����̸����� ��Ʈ�����̺��� �ѱ��̸��˻�] aname32_t 
			[ProtoMember(3, IsRequired = false)]
			public Int16 m_better_power {get; set;}	// [] int16 
			[ProtoMember(4, IsRequired = false)]
			public Int16 m_better_focus {get; set;}	// [] int16 
			[ProtoMember(5, IsRequired = false)]
			public Int16 m_pitcher_control {get; set;}	// [] int16 
			[ProtoMember(6, IsRequired = false)]
			public Int16 m_pitcher_ballspeed {get; set;}	// [������ ���ڴ� ���̳ʽ��� ����] int16 
			[ProtoMember(7, IsRequired = false)]
			public Int16 m_pitcher_breakingball_value {get; set;}	// [] int16 
			[ProtoMember(8, IsRequired = false)]
			public int m_pitcher_breakingball_type {get; set;}	// [���� ��ȭ��] EPlayerBreakingBall 
		[ProtoMember(9, IsRequired = false)]
		public bool m_player_leftright {get; set;}	// [�÷��̾��� �¿챸��(1=���� 2=������)] bool 
		[ProtoMember(10, IsRequired = false)]
		public int m_better_form {get; set;}	// [Ÿ���� Ÿ����] EBatterForm 
		[ProtoMember(11, IsRequired = false)]
		public int m_pitcher_form {get; set;}	// [������ ������] EPitcherForm 
		[ProtoMember(12, IsRequired = false)]
		public int m_player_nation {get; set;}	// [] EPlayerNationType 
		[ProtoMember(13, IsRequired = false)]
		public Int16 m_player_year {get; set;}	// [�÷��̾� Ȱ������] int16 
		[ProtoMember(14, IsRequired = false)]
		public int m_player_grade {get; set;}	// [���� �� ���׷��̵� ���] EPlayerGradeType 
		[ProtoMember(15, IsRequired = false)]
		public int m_body_type {get; set;}	// [] EPlayerBodyType 
		[ProtoMember(16, IsRequired = false)]
		public Int16 m_player_level {get; set;}	// [���� ����] int16 
		[ProtoMember(17, IsRequired = false)]
		public int m_player_type {get; set;}	// [Ÿ����������] EPlayerType 
		[ProtoMember(18, IsRequired = false)]
		public int m_price_type {get; set;}	// [] EItemPriceType 
		[ProtoMember(19, IsRequired = false)]
		public Int32 m_price_money {get; set;}	// [] int32 
		[ProtoMember(20, IsRequired = false)]
		public Int32 m_price_cash {get; set;}	// [] int32 
		[ProtoMember(21, IsRequired = false)]
		public int m_sell_status {get; set;}	// [] EItemSellStatus 
		[ProtoMember(22, IsRequired = false)]
		public string m_sell_start_date {get; set;}	// [�Ǹ� ���� �Ͻ�] SYSTEMTIME 
		[ProtoMember(23, IsRequired = false)]
		public string m_sell_end_date {get; set;}	// [�Ǹ� ���� �Ͻ�] SYSTEMTIME 
		[ProtoMember(24, IsRequired = false)]
		public Int16 m_player_level_min {get; set;}	// [] int16 
		[ProtoMember(25, IsRequired = false)]
		public Int16 m_player_level_max {get; set;}	// [] int16 
		[ProtoMember(26, IsRequired = false)]
		public Int16 m_sticker_slot_count {get; set;}	// [] int8 
		[ProtoMember(27, IsRequired = false)]
		public List<Sys_PlayerSkillSticker> m_skill_sticker {get; set;}	// [Sys_PlayerSkillSticker������ name] Sys_PlayerSkillSticker_ptr_vec 
		[ProtoMember(28, IsRequired = false)]
		public bool m_player_onoff {get; set;}	// [�÷��̾��� �¿������� ����(1=�¶��� 0=��������)] bool 
	}//public class s_sys_playercard

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	[ProtoContract]
	public class s_sys_playerlevel
	{
		[ProtoMember(1, IsRequired = false)]
		public Int16 m_sid {get; set;}	// [������ȣ] int16 
		[ProtoMember(2, IsRequired = false)]
		public string m_name {get; set;}	// [] aname32_t 
		[ProtoMember(3, IsRequired = false)]
		public Int16 m_level {get; set;}	// [�÷��̾��] int8 
		[ProtoMember(4, IsRequired = false)]
		public Int64 m_max_exp {get; set;}	// [�ش� ������ �ִ� ����ġ] int64 
		[ProtoMember(5, IsRequired = false)]
		public Int64 m_max_cum_exp {get; set;}	// [�ش� ������ �ִ� ���� ����ġ] int64 
		[ProtoMember(6, IsRequired = false)]
		public Int16 m_better_accuracy_sq {get; set;}	// [Ÿ��_square_��Ȯ] int16 
		[ProtoMember(7, IsRequired = false)]
		public Int16 m_better_accuracy_op {get; set;}	// [Ÿ��_open_��Ȯ] int16 
		[ProtoMember(8, IsRequired = false)]
		public Int16 m_better_accuracy_cl {get; set;}	// [Ÿ��_close_��Ȯ] int16 
		[ProtoMember(9, IsRequired = false)]
		public Int16 m_better_power_sq {get; set;}	// [Ÿ��_square_�Ŀ�] int16 
		[ProtoMember(10, IsRequired = false)]
		public Int16 m_better_power_op {get; set;}	// [Ÿ��_open_�Ŀ�] int16 
		[ProtoMember(11, IsRequired = false)]
		public Int16 m_better_power_cl {get; set;}	// [Ÿ��_close_�Ŀ�] int16 
		[ProtoMember(12, IsRequired = false)]
		public float m_pitcher_speed_ov {get; set;}	// [����_over_����] float 
		[ProtoMember(13, IsRequired = false)]
		public float m_pitcher_speed_tq {get; set;}	// [����_threequarter_����] float 
		[ProtoMember(14, IsRequired = false)]
		public float m_pitcher_speed_sa {get; set;}	// [����_sidearm_����] float 
		[ProtoMember(15, IsRequired = false)]
		public float m_pitcher_speed_un {get; set;}	// [����_under_����] float 
		[ProtoMember(16, IsRequired = false)]
		public Int16 m_pitcher_focus_ov {get; set;}	// [����_over_����] int16 
		[ProtoMember(17, IsRequired = false)]
		public Int16 m_pitcher_focus_tq {get; set;}	// [����_threequarter_����] int16 
		[ProtoMember(18, IsRequired = false)]
		public Int16 m_pitcher_focus_sa {get; set;}	// [����_sidearm_����] int16 
		[ProtoMember(19, IsRequired = false)]
		public Int16 m_pitcher_focus_un {get; set;}	// [����_under_����] int16 
		[ProtoMember(20, IsRequired = false)]
		public Int16 m_pitcher_breakingball_ov {get; set;}	// [����_over_��ȭ�� ���� �ټ�] int16 
		[ProtoMember(21, IsRequired = false)]
		public Int16 m_pitcher_breakingball_tq {get; set;}	// [����_threequarter_��ȭ�� ���� �ټ�] int16 
		[ProtoMember(22, IsRequired = false)]
		public Int16 m_pitcher_breakingball_sa {get; set;}	// [����_sidearm_��ȭ�� ���� �ټ�] int16 
		[ProtoMember(23, IsRequired = false)]
		public Int16 m_pitcher_breakingball_un {get; set;}	// [����_under_��ȭ�� ���� �ټ�] int16 
	}//public class s_sys_playerlevel

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	[ProtoContract]
	public class s_sys_playerskillsticker
	{
			[ProtoMember(1, IsRequired = false)]
			public Int16 m_sid {get; set;}	// [] int16 
			[ProtoMember(2, IsRequired = false)]
			public string m_name {get; set;}	// [�����̸� �����ؾ���. �̿����̸����� ��Ʈ�����̺��� �ѱ��̸��˻�] aname32_t 
			[ProtoMember(3, IsRequired = false)]
			public Int16 m_better_power {get; set;}	// [] int16 
			[ProtoMember(4, IsRequired = false)]
			public Int16 m_better_focus {get; set;}	// [] int16 
			[ProtoMember(5, IsRequired = false)]
			public Int16 m_pitcher_control {get; set;}	// [] int16 
			[ProtoMember(6, IsRequired = false)]
			public Int16 m_pitcher_ballspeed {get; set;}	// [������ ���ڴ� ���̳ʽ��� ����] int16 
			[ProtoMember(7, IsRequired = false)]
			public Int16 m_pitcher_breakingball_value {get; set;}	// [] int16 
			[ProtoMember(8, IsRequired = false)]
			public int m_pitcher_breakingball_type {get; set;}	// [���� ��ȭ��] EPlayerBreakingBall 
		[ProtoMember(9, IsRequired = false)]
		public int m_better_skill1_type {get; set;}	// [Ÿ�� ī���� ��ų ����] EBatterAbility 
		[ProtoMember(10, IsRequired = false)]
		public int m_Pitcher_skill1_type {get; set;}	// [���� ī���� ��ų ����] EPitcherAbility 
		[ProtoMember(11, IsRequired = false)]
		public Int16 m_unlock_player_level {get; set;}	// [�ش� ��ų��ƼĿ�� ���ɼ��ִ� �÷��̾��] int8 
	}//public class s_sys_playerskillsticker

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	[ProtoContract]
	public class s_sys_quest
	{
		[ProtoMember(1, IsRequired = false)]
		public Sys_Quest_id_t m_sid {get; set;}	// [] Sys_Quest_id_t 
		[ProtoMember(2, IsRequired = false)]
		public string m_name {get; set;}	// [Ŭ�� ����� ��Ʈ���� name���� Sys_StringTable���� �˻��ؼ� ����Ѵ�.] aname32_t 
		[ProtoMember(3, IsRequired = false)]
		public int m_quest_type {get; set;}	// [����Ʈ�� � ���� Ÿ������ (�̱�_��ġ_�����鸮_������etc)] EQuestType 
		[ProtoMember(4, IsRequired = false)]
		public game_money_t m_reward_money {get; set;}	// [����Ʈ ���� ���ӸӴ�] game_money_t 
		[ProtoMember(5, IsRequired = false)]
		public Int32 m_reward_exp {get; set;}	// [����Ʈ���Ǽ����鿡��exp������] int32 
		[ProtoMember(6, IsRequired = false)]
		public Sys_Title m_title {get; set;}	// [Sys_Title���̺��� name�ʵ尡 �;��Ѵ�.] Sys_Title_ptr 
		[ProtoMember(7, IsRequired = false)]
		public string m_help {get; set;}	// [��¿��̾ƴ϶� ���߽� ������] aname1024_t 
		[ProtoMember(8, IsRequired = false)]
		public int m_condition_type1 {get; set;}	// [] EQuestConditionType 
		[ProtoMember(9, IsRequired = false)]
		public string m_condition1 {get; set;}	// [���� ��� NULL] aname1024_t 
		[ProtoMember(10, IsRequired = false)]
		public Int32 m_condition_value1 {get; set;}	// [] int32 
		[ProtoMember(11, IsRequired = false)]
		public int m_condition_type2 {get; set;}	// [] EQuestConditionType 
		[ProtoMember(12, IsRequired = false)]
		public string m_condition2 {get; set;}	// [] aname1024_t 
		[ProtoMember(13, IsRequired = false)]
		public Int32 m_condition_value2 {get; set;}	// [] int32 
		[ProtoMember(14, IsRequired = false)]
		public int m_quest_reward_item1 {get; set;}	// [���� ������ 1 ����] EItemCategory 
		[ProtoMember(15, IsRequired = false)]
		public int m_quest_reward_item_grade1 {get; set;}	// [���� ������ 1 ���] EItemGradeType 
		[ProtoMember(16, IsRequired = false)]
		public Int16 m_quest_reward_percent1 {get; set;}	// [stuff  �ش� ��� �����۰� ���Ͽ��� ���� �Ӵϸ� �ް� �� Ȯ�� õ�з�] int16 
		[ProtoMember(17, IsRequired = false)]
		public int m_quest_reward_item2 {get; set;}	// [���� ������ 2 ����] EItemCategory 
		[ProtoMember(18, IsRequired = false)]
		public int m_quest_reward_item_grade2 {get; set;}	// [���� ������ 2 ���] EItemGradeType 
		[ProtoMember(19, IsRequired = false)]
		public Int16 m_quest_reward_percent2 {get; set;}	// [stuff  �ش� ��� �����۰� ���Ͽ��� ���� �Ӵϸ� �ް� �� Ȯ�� õ�з�. -1�̸� quest_reward_percent1�� �����ϱ⸸ �ϸ� ������ �ش�.] int16 
	}//public class s_sys_quest

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	[ProtoContract]
	public class s_sys_title
	{
		[ProtoMember(1, IsRequired = false)]
		public Sys_Title_id_t m_sid {get; set;}	// [] Sys_Title_id_t 
		[ProtoMember(2, IsRequired = false)]
		public string m_name {get; set;}	// [] aname32_t 
		[ProtoMember(3, IsRequired = false)]
		public Int32 m_group {get; set;}	// [�׷��̰��� Īȣ�� �ߺ� �����Ҽ�����.] int32 
		[ProtoMember(4, IsRequired = false)]
		public int m_object_type {get; set;}	// [���� ���� ��] EBaseballObjectType 
		[ProtoMember(5, IsRequired = false)]
		public string m_help {get; set;}	// [] aname256_t 
	}//public class s_sys_title

	


	public class excel_baseball_table_proto_contract
	{
		public static ArrayList GetTypes()
		{
			ArrayList list = new ArrayList();
			
			list.Add(typeof(s_sys_base_playerstat));
			list.Add(typeof(s_sys_playercard));
			list.Add(typeof(s_sys_playerlevel));
			list.Add(typeof(s_sys_playerskillsticker));
			list.Add(typeof(s_sys_quest));
			list.Add(typeof(s_sys_title));
			return list;
		}
	}
}// namespace nEXCEL


