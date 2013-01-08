
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
	public class s_sys_breakingballupgrade
	{
		[ProtoMember(1, IsRequired = false)]
		public Sys_BreakingBallState_id_t m_id {get; set;}	// [id] Sys_BreakingBallState_id_t 
		[ProtoMember(2, IsRequired = false)]
		public string m_name {get; set;}	// [name] aname32_t 
		[ProtoMember(3, IsRequired = false)]
		public int m_type {get; set;}	// [��ȭ�� �̸�] EPlayerBreakingBall 
		[ProtoMember(4, IsRequired = false)]
		public int m_need_basicskill1 {get; set;}	// [���׷��̵忡 �ʿ��� ������(null�� ��� ��� �������� �͵� ��� ����)] EPitcherForm 
		[ProtoMember(5, IsRequired = false)]
		public int m_need_basicskill2 {get; set;}	// [���׷��̵忡 �ʿ��� ������(null�� ��� ��� �������� �͵� ��� ����)] EPitcherForm 
		[ProtoMember(6, IsRequired = false)]
		public int m_need_upgrade1 {get; set;}	// [���׷��̵忡 �ʿ��� ��ȭ�� (���� �� 1�� ���׷��̵� �Ұ� null�� ��� �⺻ ��ȭ��)] EPlayerBreakingBall 
		[ProtoMember(7, IsRequired = false)]
		public int m_need_upgrade2 {get; set;}	// [���׷��̵忡 �ʿ��� ��ȭ�� (���� �� 1�� ���׷��̵� �Ұ�)] EPlayerBreakingBall 
		[ProtoMember(8, IsRequired = false)]
		public Int16 m_need_player_level {get; set;}	// [���׷��̵� �ʿ� �÷��̾� ����] int16 
		[ProtoMember(9, IsRequired = false)]
		public Int16 m_equip_player_level {get; set;}	// [���׷��̵� �ʿ� �÷��̾� ����] int16 
		[ProtoMember(10, IsRequired = false)]
		public Int16 m_upgrade_need_time1 {get; set;}	// [���׷��̵� �ʿ� �ð�] int16 
		[ProtoMember(11, IsRequired = false)]
		public Int16 m_upgrade_need_time2 {get; set;}	// [���׷��̵忡 ��ȭ���� 2�� �̻� �ʿ� ��쿡�� ��ȭ���� 2�� ��� Ʈ���̴� �Ϸ� �ؾ� ������ �ʿ�] int16 
		[ProtoMember(12, IsRequired = false)]
		public game_money_t m_need_money {get; set;}	// [���׷��̵� �ʿ� ���ӸӴ�] game_money_t 
		[ProtoMember(13, IsRequired = false)]
		public int m_breaking_pitch {get; set;}	// [��ȭ���� ��Ⱦ��ȭ ����] EBreakingBallPitch 
		[ProtoMember(14, IsRequired = false)]
		public int m_ball_rotation {get; set;}	// [��ȭ�� ���� ȸ�� ���� ����] EBreakingBallRotation 
		[ProtoMember(15, IsRequired = false)]
		public string m_open_date {get; set;}	// [��ȭ�� ���� ����] SYSTEMTIME 
		[ProtoMember(16, IsRequired = false)]
		public bool m_first_open_breakingball {get; set;}	// [ĳ���� ���� �� ���� �Ҽ� �ִ� ��ȭ�� ���� �ƴ��� ���� (0=�Ұ��� 1=����)] bool 
	}//public class s_sys_breakingballupgrade

	


	public class excel_baseball_table_etc_proto_contract
	{
		public static ArrayList GetTypes()
		{
			ArrayList list = new ArrayList();
			
			list.Add(typeof(s_sys_breakingballupgrade));
			return list;
		}
	}
}// namespace nEXCEL


