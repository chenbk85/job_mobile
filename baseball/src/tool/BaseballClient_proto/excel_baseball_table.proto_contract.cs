
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
	public class s_sys_base_playerstat
	{
		[ProtoMember(1, IsRequired = false)]
		public Int16 m_sid {get; set;}	// [] int16 
		[ProtoMember(2, IsRequired = false)]
		public string m_name {get; set;}	// [영문이름 고유해야함. 이영문이름으로 스트링테이블에서 한글이름검색] aname32_t 
		[ProtoMember(3, IsRequired = false)]
		public Int16 m_better_power {get; set;}	// [] int16 
		[ProtoMember(4, IsRequired = false)]
		public Int16 m_better_focus {get; set;}	// [] int16 
		[ProtoMember(5, IsRequired = false)]
		public Int16 m_pitcher_control {get; set;}	// [] int16 
		[ProtoMember(6, IsRequired = false)]
		public Int16 m_pitcher_ballspeed {get; set;}	// [빨간색 숫자는 마이너스를 뜻함] int16 
		[ProtoMember(7, IsRequired = false)]
		public Int16 m_pitcher_breakingball_value {get; set;}	// [] int16 
		[ProtoMember(8, IsRequired = false)]
		public int m_pitcher_breakingball_type {get; set;}	// [투수 변화구] EPlayerBreakingBall 
	}//public class s_sys_base_playerstat

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	[ProtoContract]
	public class s_sys_playercard
	{
			[ProtoMember(1, IsRequired = false)]
			public Int16 m_sid {get; set;}	// [] int16 
			[ProtoMember(2, IsRequired = false)]
			public string m_name {get; set;}	// [영문이름 고유해야함. 이영문이름으로 스트링테이블에서 한글이름검색] aname32_t 
			[ProtoMember(3, IsRequired = false)]
			public Int16 m_better_power {get; set;}	// [] int16 
			[ProtoMember(4, IsRequired = false)]
			public Int16 m_better_focus {get; set;}	// [] int16 
			[ProtoMember(5, IsRequired = false)]
			public Int16 m_pitcher_control {get; set;}	// [] int16 
			[ProtoMember(6, IsRequired = false)]
			public Int16 m_pitcher_ballspeed {get; set;}	// [빨간색 숫자는 마이너스를 뜻함] int16 
			[ProtoMember(7, IsRequired = false)]
			public Int16 m_pitcher_breakingball_value {get; set;}	// [] int16 
			[ProtoMember(8, IsRequired = false)]
			public int m_pitcher_breakingball_type {get; set;}	// [투수 변화구] EPlayerBreakingBall 
		[ProtoMember(9, IsRequired = false)]
		public bool m_player_leftright {get; set;}	// [플레이어의 좌우구분(1=왼쪽 2=오른쪽)] bool 
		[ProtoMember(10, IsRequired = false)]
		public int m_better_form {get; set;}	// [타자의 타격폼] EBatterForm 
		[ProtoMember(11, IsRequired = false)]
		public int m_pitcher_form {get; set;}	// [투수의 투구폼] EPitcherForm 
		[ProtoMember(12, IsRequired = false)]
		public int m_player_nation {get; set;}	// [] EPlayerNationType 
		[ProtoMember(13, IsRequired = false)]
		public Int16 m_player_year {get; set;}	// [플레이어 활동연도] int16 
		[ProtoMember(14, IsRequired = false)]
		public int m_player_grade {get; set;}	// [선수 별 업그레이드 등급] EPlayerGradeType 
		[ProtoMember(15, IsRequired = false)]
		public int m_body_type {get; set;}	// [] EPlayerBodyType 
		[ProtoMember(16, IsRequired = false)]
		public Int16 m_player_level {get; set;}	// [선수 레벨] int16 
		[ProtoMember(17, IsRequired = false)]
		public int m_player_type {get; set;}	// [타자투수구분] EPlayerType 
		[ProtoMember(18, IsRequired = false)]
		public int m_price_type {get; set;}	// [] EItemPriceType 
		[ProtoMember(19, IsRequired = false)]
		public Int32 m_price_money {get; set;}	// [] int32 
		[ProtoMember(20, IsRequired = false)]
		public Int32 m_price_cash {get; set;}	// [] int32 
		[ProtoMember(21, IsRequired = false)]
		public int m_sell_status {get; set;}	// [] EItemSellStatus 
		[ProtoMember(22, IsRequired = false)]
		public string m_sell_start_date {get; set;}	// [판매 시작 일시] SYSTEMTIME 
		[ProtoMember(23, IsRequired = false)]
		public string m_sell_end_date {get; set;}	// [판매 종료 일시] SYSTEMTIME 
		[ProtoMember(24, IsRequired = false)]
		public Int16 m_player_level_min {get; set;}	// [] int16 
		[ProtoMember(25, IsRequired = false)]
		public Int16 m_player_level_max {get; set;}	// [] int16 
		[ProtoMember(26, IsRequired = false)]
		public Int16 m_sticker_slot_count {get; set;}	// [] int8 
		[ProtoMember(27, IsRequired = false)]
		public List<Sys_PlayerSkillSticker> m_skill_sticker {get; set;}	// [Sys_PlayerSkillSticker에서의 name] Sys_PlayerSkillSticker_ptr_vec 
		[ProtoMember(28, IsRequired = false)]
		public bool m_player_onoff {get; set;}	// [플레이어의 온오프라인 구별(1=온라인 0=오프라인)] bool 
	}//public class s_sys_playercard

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	[ProtoContract]
	public class s_sys_playerlevel
	{
		[ProtoMember(1, IsRequired = false)]
		public Int16 m_sid {get; set;}	// [고유번호] int16 
		[ProtoMember(2, IsRequired = false)]
		public string m_name {get; set;}	// [] aname32_t 
		[ProtoMember(3, IsRequired = false)]
		public Int16 m_level {get; set;}	// [플레이어레벨] int8 
		[ProtoMember(4, IsRequired = false)]
		public Int64 m_max_exp {get; set;}	// [해당 레벨의 최대 경험치] int64 
		[ProtoMember(5, IsRequired = false)]
		public Int64 m_max_cum_exp {get; set;}	// [해당 레벨의 최대 누적 경험치] int64 
		[ProtoMember(6, IsRequired = false)]
		public Int16 m_better_accuracy_sq {get; set;}	// [타자_square_정확] int16 
		[ProtoMember(7, IsRequired = false)]
		public Int16 m_better_accuracy_op {get; set;}	// [타자_open_정확] int16 
		[ProtoMember(8, IsRequired = false)]
		public Int16 m_better_accuracy_cl {get; set;}	// [타자_close_정확] int16 
		[ProtoMember(9, IsRequired = false)]
		public Int16 m_better_power_sq {get; set;}	// [타자_square_파워] int16 
		[ProtoMember(10, IsRequired = false)]
		public Int16 m_better_power_op {get; set;}	// [타자_open_파워] int16 
		[ProtoMember(11, IsRequired = false)]
		public Int16 m_better_power_cl {get; set;}	// [타자_close_파워] int16 
		[ProtoMember(12, IsRequired = false)]
		public float m_pitcher_speed_ov {get; set;}	// [투수_over_구속] float 
		[ProtoMember(13, IsRequired = false)]
		public float m_pitcher_speed_tq {get; set;}	// [투수_threequarter_구속] float 
		[ProtoMember(14, IsRequired = false)]
		public float m_pitcher_speed_sa {get; set;}	// [투수_sidearm_구속] float 
		[ProtoMember(15, IsRequired = false)]
		public float m_pitcher_speed_un {get; set;}	// [투수_under_구속] float 
		[ProtoMember(16, IsRequired = false)]
		public Int16 m_pitcher_focus_ov {get; set;}	// [투수_over_제구] int16 
		[ProtoMember(17, IsRequired = false)]
		public Int16 m_pitcher_focus_tq {get; set;}	// [투수_threequarter_제구] int16 
		[ProtoMember(18, IsRequired = false)]
		public Int16 m_pitcher_focus_sa {get; set;}	// [투수_sidearm_제구] int16 
		[ProtoMember(19, IsRequired = false)]
		public Int16 m_pitcher_focus_un {get; set;}	// [투수_under_제구] int16 
		[ProtoMember(20, IsRequired = false)]
		public Int16 m_pitcher_breakingball_ov {get; set;}	// [투수_over_변화구 보유 겟수] int16 
		[ProtoMember(21, IsRequired = false)]
		public Int16 m_pitcher_breakingball_tq {get; set;}	// [투수_threequarter_변화구 보유 겟수] int16 
		[ProtoMember(22, IsRequired = false)]
		public Int16 m_pitcher_breakingball_sa {get; set;}	// [투수_sidearm_변화구 보유 겟수] int16 
		[ProtoMember(23, IsRequired = false)]
		public Int16 m_pitcher_breakingball_un {get; set;}	// [투수_under_변화구 보유 겟수] int16 
	}//public class s_sys_playerlevel

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	[ProtoContract]
	public class s_sys_playerskillsticker
	{
			[ProtoMember(1, IsRequired = false)]
			public Int16 m_sid {get; set;}	// [] int16 
			[ProtoMember(2, IsRequired = false)]
			public string m_name {get; set;}	// [영문이름 고유해야함. 이영문이름으로 스트링테이블에서 한글이름검색] aname32_t 
			[ProtoMember(3, IsRequired = false)]
			public Int16 m_better_power {get; set;}	// [] int16 
			[ProtoMember(4, IsRequired = false)]
			public Int16 m_better_focus {get; set;}	// [] int16 
			[ProtoMember(5, IsRequired = false)]
			public Int16 m_pitcher_control {get; set;}	// [] int16 
			[ProtoMember(6, IsRequired = false)]
			public Int16 m_pitcher_ballspeed {get; set;}	// [빨간색 숫자는 마이너스를 뜻함] int16 
			[ProtoMember(7, IsRequired = false)]
			public Int16 m_pitcher_breakingball_value {get; set;}	// [] int16 
			[ProtoMember(8, IsRequired = false)]
			public int m_pitcher_breakingball_type {get; set;}	// [투수 변화구] EPlayerBreakingBall 
		[ProtoMember(9, IsRequired = false)]
		public int m_better_skill1_type {get; set;}	// [타자 카드의 스킬 종류] EBatterAbility 
		[ProtoMember(10, IsRequired = false)]
		public int m_Pitcher_skill1_type {get; set;}	// [투수 카드의 스킬 종류] EPitcherAbility 
		[ProtoMember(11, IsRequired = false)]
		public Int16 m_unlock_player_level {get; set;}	// [해당 스킬스티커가 사용될수있는 플레이어레벨] int8 
	}//public class s_sys_playerskillsticker

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	[ProtoContract]
	public class s_sys_quest
	{
		[ProtoMember(1, IsRequired = false)]
		public Sys_Quest_id_t m_sid {get; set;}	// [] Sys_Quest_id_t 
		[ProtoMember(2, IsRequired = false)]
		public string m_name {get; set;}	// [클라에 출력할 스트링은 name으로 Sys_StringTable에서 검색해서 출력한다.] aname32_t 
		[ProtoMember(3, IsRequired = false)]
		public int m_quest_type {get; set;}	// [퀘스트가 어떤 게임 타입인지 (싱글_매치_프랜들리_아이템etc)] EQuestType 
		[ProtoMember(4, IsRequired = false)]
		public game_money_t m_reward_money {get; set;}	// [퀘스트 보상 게임머니] game_money_t 
		[ProtoMember(5, IsRequired = false)]
		public Int32 m_reward_exp {get; set;}	// [디펄트팀의선수들에게exp를보상] int32 
		[ProtoMember(6, IsRequired = false)]
		public Sys_Title m_title {get; set;}	// [Sys_Title테이블의 name필드가 와야한다.] Sys_Title_ptr 
		[ProtoMember(7, IsRequired = false)]
		public string m_help {get; set;}	// [출력용이아니라 개발시 참조용] aname1024_t 
		[ProtoMember(8, IsRequired = false)]
		public int m_condition_type1 {get; set;}	// [] EQuestConditionType 
		[ProtoMember(9, IsRequired = false)]
		public string m_condition1 {get; set;}	// [없을 경우 NULL] aname1024_t 
		[ProtoMember(10, IsRequired = false)]
		public Int32 m_condition_value1 {get; set;}	// [] int32 
		[ProtoMember(11, IsRequired = false)]
		public int m_condition_type2 {get; set;}	// [] EQuestConditionType 
		[ProtoMember(12, IsRequired = false)]
		public string m_condition2 {get; set;}	// [] aname1024_t 
		[ProtoMember(13, IsRequired = false)]
		public Int32 m_condition_value2 {get; set;}	// [] int32 
		[ProtoMember(14, IsRequired = false)]
		public int m_quest_reward_item1 {get; set;}	// [보상 아이템 1 종류] EItemCategory 
		[ProtoMember(15, IsRequired = false)]
		public int m_quest_reward_item_grade1 {get; set;}	// [보상 아이템 1 등급] EItemGradeType 
		[ProtoMember(16, IsRequired = false)]
		public Int16 m_quest_reward_percent1 {get; set;}	// [stuff  해당 등급 아이템과 정하여진 게임 머니를 받게 될 확률 천분률] int16 
		[ProtoMember(17, IsRequired = false)]
		public int m_quest_reward_item2 {get; set;}	// [보상 아이템 2 종류] EItemCategory 
		[ProtoMember(18, IsRequired = false)]
		public int m_quest_reward_item_grade2 {get; set;}	// [보상 아이템 2 등급] EItemGradeType 
		[ProtoMember(19, IsRequired = false)]
		public Int16 m_quest_reward_percent2 {get; set;}	// [stuff  해당 등급 아이템과 정하여진 게임 머니를 받게 될 확률 천분률. -1이면 quest_reward_percent1가 성공하기만 하면 무조건 준다.] int16 
	}//public class s_sys_quest

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	[ProtoContract]
	public class s_sys_title
	{
		[ProtoMember(1, IsRequired = false)]
		public Sys_Title_id_t m_sid {get; set;}	// [] Sys_Title_id_t 
		[ProtoMember(2, IsRequired = false)]
		public string m_name {get; set;}	// [] aname32_t 
		[ProtoMember(3, IsRequired = false)]
		public Int32 m_group {get; set;}	// [그룹이같은 칭호는 중복 소유할수없다.] int32 
		[ProtoMember(4, IsRequired = false)]
		public int m_object_type {get; set;}	// [유저 선수 팀] EBaseballObjectType 
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


