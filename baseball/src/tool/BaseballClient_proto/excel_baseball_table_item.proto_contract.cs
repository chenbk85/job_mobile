
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
	public class s_sys__itembase
	{
		[ProtoMember(1, IsRequired = false)]
		public Sys__ItemBase_id_t m_sid {get; set;}	// [] Sys__ItemBase_id_t 
		[ProtoMember(2, IsRequired = false)]
		public string m_name {get; set;}	// [�����̸� �����ؾ���. �� �����̸����� ��Ʈ�����̺��� �ѱ��̸��˻�] aname32_t 
		[ProtoMember(3, IsRequired = false)]
		public int m_category {get; set;}	// [] EItemCategory 
		[ProtoMember(4, IsRequired = false)]
		public bool m_upgrade_type {get; set;}	// [���׷��̵尡 ���������� ����] bool 
		[ProtoMember(5, IsRequired = false)]
		public bool m_is_visual {get; set;}	// [ȭ�鿡 ���������� �Ⱥ��������� ����] bool 
		[ProtoMember(6, IsRequired = false)]
		public string m_help {get; set;}	// [] aname256_t 
		[ProtoMember(7, IsRequired = false)]
		public int m_grade {get; set;}	// [������ ���׷��̵� ���] EItemGradeType 
		[ProtoMember(8, IsRequired = false)]
		public int m_subgrade {get; set;}	// [������ ���� ���׷��̵� ���] EItemSubGradeType 
		[ProtoMember(9, IsRequired = false)]
		public player_level_t m_player_level_min {get; set;}	// [������ �� 110���� ����] player_level_t 
		[ProtoMember(10, IsRequired = false)]
		public player_level_t m_player_level_max {get; set;}	// [������ �� 110���� ����] player_level_t 
	}//public class s_sys__itembase

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	[ProtoContract]
	public class s_sys_itemequip
	{
			[ProtoMember(1, IsRequired = false)]
			public Sys__ItemBase_id_t m_sid {get; set;}	// [] Sys__ItemBase_id_t 
			[ProtoMember(2, IsRequired = false)]
			public string m_name {get; set;}	// [�����̸� �����ؾ���. �� �����̸����� ��Ʈ�����̺��� �ѱ��̸��˻�] aname32_t 
			[ProtoMember(3, IsRequired = false)]
			public int m_category {get; set;}	// [] EItemCategory 
			[ProtoMember(4, IsRequired = false)]
			public bool m_upgrade_type {get; set;}	// [���׷��̵尡 ���������� ����] bool 
			[ProtoMember(5, IsRequired = false)]
			public bool m_is_visual {get; set;}	// [ȭ�鿡 ���������� �Ⱥ��������� ����] bool 
			[ProtoMember(6, IsRequired = false)]
			public string m_help {get; set;}	// [] aname256_t 
			[ProtoMember(7, IsRequired = false)]
			public int m_grade {get; set;}	// [������ ���׷��̵� ���] EItemGradeType 
			[ProtoMember(8, IsRequired = false)]
			public int m_subgrade {get; set;}	// [������ ���� ���׷��̵� ���] EItemSubGradeType 
			[ProtoMember(9, IsRequired = false)]
			public player_level_t m_player_level_min {get; set;}	// [������ �� 110���� ����] player_level_t 
			[ProtoMember(10, IsRequired = false)]
			public player_level_t m_player_level_max {get; set;}	// [������ �� 110���� ����] player_level_t 
		[ProtoMember(11, IsRequired = false)]
		public int m_equip_category {get; set;}	// [��������ī�װ�] EItemCategoryEquipment 
		[ProtoMember(12, IsRequired = false)]
		public int m_sex_type {get; set;}	// [��������] EItemSexType 
		[ProtoMember(13, IsRequired = false)]
		public int m_player_type {get; set;}	// [Ÿ����������] EPlayerType 
		[ProtoMember(14, IsRequired = false)]
		public int m_item_batter_ability_type {get; set;}	// [Ÿ�� ������ ���� ����] EItemAbilityType 
		[ProtoMember(15, IsRequired = false)]
		public int m_item_pitcher_ability_type {get; set;}	// [���� ������ ���� ����] EItemAbilityType 
	}//public class s_sys_itemequip

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	[ProtoContract]
	public class s_sys_itemstuff
	{
			[ProtoMember(1, IsRequired = false)]
			public Sys__ItemBase_id_t m_sid {get; set;}	// [] Sys__ItemBase_id_t 
			[ProtoMember(2, IsRequired = false)]
			public string m_name {get; set;}	// [�����̸� �����ؾ���. �� �����̸����� ��Ʈ�����̺��� �ѱ��̸��˻�] aname32_t 
			[ProtoMember(3, IsRequired = false)]
			public int m_category {get; set;}	// [] EItemCategory 
			[ProtoMember(4, IsRequired = false)]
			public bool m_upgrade_type {get; set;}	// [���׷��̵尡 ���������� ����] bool 
			[ProtoMember(5, IsRequired = false)]
			public bool m_is_visual {get; set;}	// [ȭ�鿡 ���������� �Ⱥ��������� ����] bool 
			[ProtoMember(6, IsRequired = false)]
			public string m_help {get; set;}	// [] aname256_t 
			[ProtoMember(7, IsRequired = false)]
			public int m_grade {get; set;}	// [������ ���׷��̵� ���] EItemGradeType 
			[ProtoMember(8, IsRequired = false)]
			public int m_subgrade {get; set;}	// [������ ���� ���׷��̵� ���] EItemSubGradeType 
			[ProtoMember(9, IsRequired = false)]
			public player_level_t m_player_level_min {get; set;}	// [������ �� 110���� ����] player_level_t 
			[ProtoMember(10, IsRequired = false)]
			public player_level_t m_player_level_max {get; set;}	// [������ �� 110���� ����] player_level_t 
		[ProtoMember(11, IsRequired = false)]
		public int m_upgradable_item_type {get; set;}	// [���׷��̵��ų���ִ¾���������] EItemUpgradeResult 
	}//public class s_sys_itemstuff

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	[ProtoContract]
	public class s_sys_itemconsume
	{
			[ProtoMember(1, IsRequired = false)]
			public Sys__ItemBase_id_t m_sid {get; set;}	// [] Sys__ItemBase_id_t 
			[ProtoMember(2, IsRequired = false)]
			public string m_name {get; set;}	// [�����̸� �����ؾ���. �� �����̸����� ��Ʈ�����̺��� �ѱ��̸��˻�] aname32_t 
			[ProtoMember(3, IsRequired = false)]
			public int m_category {get; set;}	// [] EItemCategory 
			[ProtoMember(4, IsRequired = false)]
			public bool m_upgrade_type {get; set;}	// [���׷��̵尡 ���������� ����] bool 
			[ProtoMember(5, IsRequired = false)]
			public bool m_is_visual {get; set;}	// [ȭ�鿡 ���������� �Ⱥ��������� ����] bool 
			[ProtoMember(6, IsRequired = false)]
			public string m_help {get; set;}	// [] aname256_t 
			[ProtoMember(7, IsRequired = false)]
			public int m_grade {get; set;}	// [������ ���׷��̵� ���] EItemGradeType 
			[ProtoMember(8, IsRequired = false)]
			public int m_subgrade {get; set;}	// [������ ���� ���׷��̵� ���] EItemSubGradeType 
			[ProtoMember(9, IsRequired = false)]
			public player_level_t m_player_level_min {get; set;}	// [������ �� 110���� ����] player_level_t 
			[ProtoMember(10, IsRequired = false)]
			public player_level_t m_player_level_max {get; set;}	// [������ �� 110���� ����] player_level_t 
		[ProtoMember(11, IsRequired = false)]
		public int m_player_type {get; set;}	// [Ÿ����������] EPlayerType 
		[ProtoMember(12, IsRequired = false)]
		public int m_consume_item_effect {get; set;}	// [���������� �Һ� �� ȿ�� ����] EConsumeItemEffect 
		[ProtoMember(13, IsRequired = false)]
		public int m_Item_Ability_Type {get; set;}	// [���������ۿ��⽺��] EItemAbilityType 
		[ProtoMember(14, IsRequired = false)]
		public Int16 m_consume_item_effect_value {get; set;}	// [�� �ش� ������ ȿ���� ��(�������� ȿ�� ���� ���� �ٸ�-->)] int16 
		[ProtoMember(15, IsRequired = false)]
		public Int16 m_gameplay_effect_repeat {get; set;}	// [���� �÷��̽� ����ȿ�� ����(Ƚ��)] int16 
		[ProtoMember(16, IsRequired = false)]
		public Int16 m_gameplay_effect_time {get; set;}	// [���� �÷��̽� ����ȿ�� ����(�ð�)] int16 
		[ProtoMember(17, IsRequired = false)]
		public bool m_consume_item_overlap {get; set;}	// [�ٸ������۰� �ߺ���� ����] bool 
		[ProtoMember(18, IsRequired = false)]
		public Int16 m_use_count {get; set;}	// [��� Ƚ��] int16 
		[ProtoMember(19, IsRequired = false)]
		public bool m_is_bonus {get; set;}	// [���ʽ��������] bool 
	}//public class s_sys_itemconsume

	


	public class excel_baseball_table_item_proto_contract
	{
		public static ArrayList GetTypes()
		{
			ArrayList list = new ArrayList();
			
			list.Add(typeof(s_sys__itembase));
			list.Add(typeof(s_sys_itemconsume));
			list.Add(typeof(s_sys_itemequip));
			list.Add(typeof(s_sys_itemstuff));
			return list;
		}
	}
}// namespace nEXCEL


