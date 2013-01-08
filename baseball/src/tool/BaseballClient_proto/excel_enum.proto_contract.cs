
// THIS CODE IS USED FOR unity3d + google protocal buffer + c# + iphone
// by icandoit@neowiz.com
// command line : Excel_Converter.exe D:\svn\baseball\doc\design\excel\code\excel_enum.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_string_table.txt 



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
	


	public class excel_enum_proto_contract
	{
		public static ArrayList GetTypes()
		{
			ArrayList list = new ArrayList();
			
			list.Add(typeof(EBaseballObjectType));
			list.Add(typeof(EBatterAbility));
			list.Add(typeof(EBatterForm));
			list.Add(typeof(EBatterHitType));
			list.Add(typeof(EBreakingBallPitch));
			list.Add(typeof(EBreakingBallRotation));
			list.Add(typeof(ECategoryString));
			list.Add(typeof(EConsumeItemEffect));
			list.Add(typeof(EEventType));
			list.Add(typeof(EGestureType));
			list.Add(typeof(EGiftCategory));
			list.Add(typeof(EGiftType));
			list.Add(typeof(EGradeAllitemType));
			list.Add(typeof(EHitTimmingType));
			list.Add(typeof(EHitType));
			list.Add(typeof(EItemAbilityType));
			list.Add(typeof(EItemBuyType));
			list.Add(typeof(EItemCategory));
			list.Add(typeof(EItemCategoryEquipment));
			list.Add(typeof(EItemGradeType));
			list.Add(typeof(EItemPriceType));
			list.Add(typeof(EItemReuseType));
			list.Add(typeof(EItemSellStatus));
			list.Add(typeof(EItemSexType));
			list.Add(typeof(EItemState));
			list.Add(typeof(EItemSubGradeType));
			list.Add(typeof(EItemUpgradeResult));
			list.Add(typeof(ELogType));
			list.Add(typeof(ENoticeType));
			list.Add(typeof(ENpcSituationString));
			list.Add(typeof(ENpcString));
			list.Add(typeof(EPitcherAbility));
			list.Add(typeof(EPitcherForm));
			list.Add(typeof(EPlayerBodyType));
			list.Add(typeof(EPlayerBreakingBall));
			list.Add(typeof(EPlayerGradeType));
			list.Add(typeof(EPlayerNationType));
			list.Add(typeof(EPlayerType));
			list.Add(typeof(EPlayer_Onoffline));
			list.Add(typeof(EQuestConditionType));
			list.Add(typeof(EQuestType));
			list.Add(typeof(ERhythmJudge));
			list.Add(typeof(EShopBatterSection));
			list.Add(typeof(EShopConsumeSection));
			list.Add(typeof(EShopItemType));
			list.Add(typeof(EShopPitcherSection));
			list.Add(typeof(ETotalGameType));
			return list;
		}
	}
}// namespace nEXCEL


