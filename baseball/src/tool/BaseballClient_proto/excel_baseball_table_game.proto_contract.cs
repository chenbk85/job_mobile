
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
	public class s_sys_runner_state
	{
		[ProtoMember(1, IsRequired = false)]
		public Sys_Runner_State_id_t m_index {get; set;}	// [영문닉네임 , 각종테이블에서 사용] Sys_Runner_State_id_t 
		[ProtoMember(2, IsRequired = false)]
		public int m_category {get; set;}	// [주자배치 타입] ERunnerStateType 
		[ProtoMember(3, IsRequired = false)]
		public int m_state_1r {get; set;}	// [1라운드 주자 상황] ERunnerStateRound 
		[ProtoMember(4, IsRequired = false)]
		public int m_state_2r {get; set;}	// [2라운드 주자 상황] ERunnerStateRound 
		[ProtoMember(5, IsRequired = false)]
		public int m_state_3r {get; set;}	// [3라운드 주자 상황] ERunnerStateRound 
		[ProtoMember(6, IsRequired = false)]
		public int m_state_4r {get; set;}	// [4라운드 주자 상황] ERunnerStateRound 
		[ProtoMember(7, IsRequired = false)]
		public int m_state_5r {get; set;}	// [5라운드 주자 상황] ERunnerStateRound 
		[ProtoMember(8, IsRequired = false)]
		public int m_state_6r {get; set;}	// [6라운드 주자 상황] ERunnerStateRound 
		[ProtoMember(9, IsRequired = false)]
		public int m_state_7r {get; set;}	// [7라운드 주자 상황] ERunnerStateRound 
		[ProtoMember(10, IsRequired = false)]
		public int m_state_8r {get; set;}	// [8라운드 주자 상황] ERunnerStateRound 
		[ProtoMember(11, IsRequired = false)]
		public int m_state_9r {get; set;}	// [9라운드 주자 상황] ERunnerStateRound 
	}//public class s_sys_runner_state

	


	public class excel_baseball_table_game_proto_contract
	{
		public static ArrayList GetTypes()
		{
			ArrayList list = new ArrayList();
			
			list.Add(typeof(ERunnerStateRound));
			list.Add(typeof(ERunnerStateType));
			list.Add(typeof(s_sys_runner_state));
			return list;
		}
	}
}// namespace nEXCEL


