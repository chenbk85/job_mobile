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

	public class Sys__Base_PlayerStat
	{
		public Int16 m_sid; 	// [�����ĺ�ID]  
		public string m_name; 	// [�̸�] �����̸� �����ؾ���. �̿����̸����� ��Ʈ�����̺��� �ѱ��̸��˻� 
		public Int16 m_better_power; 	// [Ÿ�� �Ŀ�]  
		public Int16 m_better_focus; 	// [Ÿ�� ����]  
		public Int16 m_pitcher_control; 	// [���� ����]  
		public Int16 m_pitcher_ballspeed; 	// [���� ����] ������ ���ڴ� ���̳ʽ��� ���� 
		public Int16 m_pitcher_breakingball_value; 	// [���� ��ȭ�� ��Ÿ� ������ġ]  
		public EPlayerBreakingBall m_pitcher_breakingball_type; 	// [���� ��ȭ������] ���� ��ȭ�� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int16.Parse("Sys__Base_PlayerStat::sid",token[idx++], ref m_sid);
			nUtil.jString_string.Parse("Sys__Base_PlayerStat::name",token[idx++], ref m_name);
			nUtil.jString_Int16.Parse("Sys__Base_PlayerStat::better_power",token[idx++], ref m_better_power);
			nUtil.jString_Int16.Parse("Sys__Base_PlayerStat::better_focus",token[idx++], ref m_better_focus);
			nUtil.jString_Int16.Parse("Sys__Base_PlayerStat::pitcher_control",token[idx++], ref m_pitcher_control);
			nUtil.jString_Int16.Parse("Sys__Base_PlayerStat::pitcher_ballspeed",token[idx++], ref m_pitcher_ballspeed);
			nUtil.jString_Int16.Parse("Sys__Base_PlayerStat::pitcher_breakingball_value",token[idx++], ref m_pitcher_breakingball_value);
			nUtil.jString_EPlayerBreakingBall.Parse("Sys__Base_PlayerStat::pitcher_breakingball_type",token[idx++], ref m_pitcher_breakingball_type);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_sid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_better_power.ToString() + ",";
			output += m_better_focus.ToString() + ",";
			output += m_pitcher_control.ToString() + ",";
			output += m_pitcher_ballspeed.ToString() + ",";
			output += m_pitcher_breakingball_value.ToString() + ",";
			output += m_pitcher_breakingball_type.ToString() + ",";
			return output;
		}
	}//class Sys__Base_PlayerStat

	

	// -------------------------------------------------
	// ���� ����Ʈ ���� �������� ���Ͽ��� ��� �� �����ϰ� �ϳ��� ����
	// -------------------------------------------------

	public class Sys_Daily_Quest
	{
		public Sys_Daily_Quest_id_t m_sid; 	// [������ȣ]  
		public string m_name; 	// [����Ʈ�̸�] Ŭ�� ����� ��Ʈ���� name���� Sys_StringTable���� �˻��ؼ� ����Ѵ�. 
		public game_money_t m_quest_reward_money; 	// [����Ӵ�] ����Ʈ ���� ���ӸӴ� 
		public pp_point_t m_quest_reward_point; 	// [��������Ʈ] ����Ʈ ���� pp����Ʈ 
		public EItemCategory m_quest_reward_item; 	// [���� ������ 2] ���� ������ 2 ���� 
		public EItemGradeType m_quest_reward_item_grade; 	// [���� ������ 2 ���] ���� ������ 2 ��� 
		public Int16 m_quest_reward_percent; 	// [���� ������ Ȯ��] stuff  �ش� ��� �����۰� ���Ͽ��� ���� �Ӵϸ� �ް� �� Ȯ�� õ�з� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_Daily_Quest::sid",token[idx++], ref m_sid);
			nUtil.jString_string.Parse("Sys_Daily_Quest::name",token[idx++], ref m_name);
			nUtil.jString_Int32.Parse("Sys_Daily_Quest::quest_reward_money",token[idx++], ref m_quest_reward_money);
			nUtil.jString_Int32.Parse("Sys_Daily_Quest::quest_reward_point",token[idx++], ref m_quest_reward_point);
			nUtil.jString_EItemCategory.Parse("Sys_Daily_Quest::quest_reward_item",token[idx++], ref m_quest_reward_item);
			nUtil.jString_EItemGradeType.Parse("Sys_Daily_Quest::quest_reward_item_grade",token[idx++], ref m_quest_reward_item_grade);
			nUtil.jString_Int16.Parse("Sys_Daily_Quest::quest_reward_percent",token[idx++], ref m_quest_reward_percent);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_sid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_quest_reward_money.ToString() + ",";
			output += m_quest_reward_point.ToString() + ",";
			output += m_quest_reward_item.ToString() + ",";
			output += m_quest_reward_item_grade.ToString() + ",";
			output += m_quest_reward_percent.ToString() + ",";
			return output;
		}
	}//class Sys_Daily_Quest

	namespace nUtil
	{
		class jString_Sys_Daily_Quest
		{
			public static string ToString(Sys_Daily_Quest o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_Daily_Quest> sysList)
			{
				string output = "";
				foreach (Sys_Daily_Quest o in sysList)
				{
					if( o==null )
						output += "NULL;";
					else
						output += (o.m_name + ";");
				}
				return output;
			}
			public static void PostParse(nEXCEL.nUtil.jCSV.PostParseData ppd)
			{
				Sys_Daily_Quest o = (Sys_Daily_Quest)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_Daily_Quest o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_Daily_Quest.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_Daily_Quest.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_Daily_Quest> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_Daily_Quest> sysList = (List<Sys_Daily_Quest>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_Daily_Quest o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_Daily_Quest.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_Daily_Quest.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_Daily_Quest
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_PlayerCard
			: Sys__Base_PlayerStat
	{
		public bool m_player_leftright; 	// [�¿� ����] �÷��̾��� �¿챸��(1=���� 2=������) 
		public EBetterForm m_better_form; 	// [Ÿ�� Ÿ����] Ÿ���� Ÿ���� 
		public EPitcherForm m_pitcher_form; 	// [���� ������] ������ ������ 
		public EPlayerNationType m_player_nation; 	// [���]  
		public Int16 m_player_year; 	// [Ȱ�� ����] �÷��̾� Ȱ������ 
		public EPlayerGradeType m_player_grade; 	// [���] ���� �� ���׷��̵� ��� 
		public EPlayerBodyType m_body_type; 	// [ü��]  
		public Int16 m_player_level; 	// [�÷��̾� ����] ���� ���� 
		public EPlayerType m_player_type; 	// [Ÿ����������] Ÿ���������� 
		public EItemPriceType m_price_type; 	// [����Ÿ��]  
		public Int32 m_price_money; 	// [�ʿ���ӸӴ�]  
		public Int32 m_price_cash; 	// [�ʿ丮��ĳ��]  
		public EItemSellStatus m_sell_status; 	// [�ǸŻ���]  
		public DATETIME m_sell_start_date; 	// [�Ǹ� ���� �Ͻ�] �Ǹ� ���� �Ͻ� 
		public DATETIME m_sell_end_date; 	// [�Ǹ� ���� �Ͻ�] �Ǹ� ���� �Ͻ� 
		public Int16 m_player_level_min; 	// [��뷹��MIN]  
		public Int16 m_player_level_max; 	// [��뷹��MAX]  
		public Int16 m_sticker_slot_count; 	// [���ϼ��ִ½�ƼĿ����]  
		public List<Sys_PlayerSkillSticker> m_skill_sticker = new List<Sys_PlayerSkillSticker>{}; 	// [�⺻�����κ����� Ư���ɷ�] Sys_PlayerSkillSticker������ name 
		public bool m_player_onoff; 	// [�÷��̾��� �¿������� ����] �÷��̾��� �¿������� ����(1=�¶��� 0=��������) 
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_bool.Parse("Sys_PlayerCard::player_leftright",token[idx++], ref m_player_leftright);
			nUtil.jString_EBetterForm.Parse("Sys_PlayerCard::better_form",token[idx++], ref m_better_form);
			nUtil.jString_EPitcherForm.Parse("Sys_PlayerCard::pitcher_form",token[idx++], ref m_pitcher_form);
			nUtil.jString_EPlayerNationType.Parse("Sys_PlayerCard::player_nation",token[idx++], ref m_player_nation);
			nUtil.jString_Int16.Parse("Sys_PlayerCard::player_year",token[idx++], ref m_player_year);
			nUtil.jString_EPlayerGradeType.Parse("Sys_PlayerCard::player_grade",token[idx++], ref m_player_grade);
			nUtil.jString_EPlayerBodyType.Parse("Sys_PlayerCard::body_type",token[idx++], ref m_body_type);
			nUtil.jString_Int16.Parse("Sys_PlayerCard::player_level",token[idx++], ref m_player_level);
			nUtil.jString_EPlayerType.Parse("Sys_PlayerCard::player_type",token[idx++], ref m_player_type);
			nUtil.jString_EItemPriceType.Parse("Sys_PlayerCard::price_type",token[idx++], ref m_price_type);
			nUtil.jString_Int32.Parse("Sys_PlayerCard::price_money",token[idx++], ref m_price_money);
			nUtil.jString_Int32.Parse("Sys_PlayerCard::price_cash",token[idx++], ref m_price_cash);
			nUtil.jString_EItemSellStatus.Parse("Sys_PlayerCard::sell_status",token[idx++], ref m_sell_status);
			nUtil.jString_DATETIME.Parse("Sys_PlayerCard::sell_start_date",token[idx++], ref m_sell_start_date);
			nUtil.jString_DATETIME.Parse("Sys_PlayerCard::sell_end_date",token[idx++], ref m_sell_end_date);
			nUtil.jString_Int16.Parse("Sys_PlayerCard::player_level_min",token[idx++], ref m_player_level_min);
			nUtil.jString_Int16.Parse("Sys_PlayerCard::player_level_max",token[idx++], ref m_player_level_max);
			nUtil.jString_Int16.Parse("Sys_PlayerCard::sticker_slot_count",token[idx++], ref m_sticker_slot_count);
			isFind = nUtil.jString_Sys_PlayerSkillSticker.Parse("Sys_PlayerCard::skill_sticker",token[idx++], ref m_skill_sticker);
			if(!isFind)
			{
				if(!isPostParse)
				{
					if(!nUtil.jCSV.m_PostParseList.ContainsKey(this))
					{
					
						nUtil.jCSV.PostParseData ppd = new nUtil.jCSV.PostParseData();
						ppd.func = new nUtil.jCSV.PostParseFunc(nUtil.jString_Sys_PlayerCard.PostParse);
						ppd.token = token;
						ppd.idx = iStart;
						ppd.o = this;
						ppd.sDebug = " -> Sys_PlayerCard : " ;
						nUtil.jCSV.m_PostParseList[this]=ppd;
					}
				}
				else
				{
					Console.WriteLine("[WARN]" + " -> Sys_PlayerCard : skill_sticker : " + token[idx-1]) ;
				}
			}
			nUtil.jString_bool.Parse("Sys_PlayerCard::player_onoff",token[idx++], ref m_player_onoff);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_player_leftright.ToString() + ",";
			output += m_better_form.ToString() + ",";
			output += m_pitcher_form.ToString() + ",";
			output += m_player_nation.ToString() + ",";
			output += m_player_year.ToString() + ",";
			output += m_player_grade.ToString() + ",";
			output += m_body_type.ToString() + ",";
			output += m_player_level.ToString() + ",";
			output += m_player_type.ToString() + ",";
			output += m_price_type.ToString() + ",";
			output += m_price_money.ToString() + ",";
			output += m_price_cash.ToString() + ",";
			output += m_sell_status.ToString() + ",";
			output += m_sell_start_date.ToString() + ",";
			output += m_sell_end_date.ToString() + ",";
			output += m_player_level_min.ToString() + ",";
			output += m_player_level_max.ToString() + ",";
			output += m_sticker_slot_count.ToString() + ",";
			output += (nUtil.jString_Sys_PlayerSkillSticker.ToString(m_skill_sticker)+ ",");
			output += m_player_onoff.ToString() + ",";
			return output;
		}
	}//class Sys_PlayerCard

	namespace nUtil
	{
		class jString_Sys_PlayerCard
		{
			public static string ToString(Sys_PlayerCard o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_PlayerCard> sysList)
			{
				string output = "";
				foreach (Sys_PlayerCard o in sysList)
				{
					if( o==null )
						output += "NULL;";
					else
						output += (o.m_name + ";");
				}
				return output;
			}
			public static void PostParse(nEXCEL.nUtil.jCSV.PostParseData ppd)
			{
				Sys_PlayerCard o = (Sys_PlayerCard)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_PlayerCard o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_PlayerCard.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_PlayerCard.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_PlayerCard> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_PlayerCard> sysList = (List<Sys_PlayerCard>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_PlayerCard o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_PlayerCard.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_PlayerCard.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_PlayerCard
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_PlayerLevel
	{
		public Int16 m_sid; 	// [������ȣ] ������ȣ 
		public string m_name; 	// [name]  
		public Int16 m_level; 	// [�÷��̾��] �÷��̾�� 
		public Int64 m_max_exp; 	// [�ش� ������ �ִ� ����ġ] �ش� ������ �ִ� ����ġ 
		public Int16 m_better_accuracy_sq; 	// [Ÿ��_square_��Ȯ] Ÿ��_square_��Ȯ 
		public Int16 m_better_accuracy_op; 	// [Ÿ��_open_��Ȯ] Ÿ��_open_��Ȯ 
		public Int16 m_better_accuracy_cl; 	// [Ÿ��_close_��Ȯ] Ÿ��_close_��Ȯ 
		public Int16 m_better_power_sq; 	// [Ÿ��_square_�Ŀ�] Ÿ��_square_�Ŀ� 
		public Int16 m_better_power_op; 	// [Ÿ��_open_�Ŀ�] Ÿ��_open_�Ŀ� 
		public Int16 m_better_power_cl; 	// [Ÿ��_close_�Ŀ�] Ÿ��_close_�Ŀ� 
		public float m_pitcher_speed_ov; 	// [����_over_����] ����_over_���� 
		public float m_pitcher_speed_tq; 	// [����_threequarter_����] ����_threequarter_���� 
		public float m_pitcher_speed_sa; 	// [����_sidearm_����] ����_sidearm_���� 
		public float m_pitcher_speed_un; 	// [����_under_����] ����_under_���� 
		public Int16 m_pitcher_focus_ov; 	// [����_over_����] ����_over_���� 
		public Int16 m_pitcher_focus_tq; 	// [����_threequarter_����] ����_threequarter_���� 
		public Int16 m_pitcher_focus_sa; 	// [����_sidearm_����] ����_sidearm_���� 
		public Int16 m_pitcher_focus_un; 	// [����_under_����] ����_under_���� 
		public Int16 m_pitcher_breakingball_ov; 	// [����_over_��ȭ��] ����_over_��ȭ�� ���� �ټ� 
		public Int16 m_pitcher_breakingball_tq; 	// [����_threequarter_��ȭ��] ����_threequarter_��ȭ�� ���� �ټ� 
		public Int16 m_pitcher_breakingball_sa; 	// [����_sidearm_��ȭ��] ����_sidearm_��ȭ�� ���� �ټ� 
		public Int16 m_pitcher_breakingball_un; 	// [����_under_��ȭ��] ����_under_��ȭ�� ���� �ټ� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::sid",token[idx++], ref m_sid);
			nUtil.jString_string.Parse("Sys_PlayerLevel::name",token[idx++], ref m_name);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::level",token[idx++], ref m_level);
			nUtil.jString_Int64.Parse("Sys_PlayerLevel::max_exp",token[idx++], ref m_max_exp);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::better_accuracy_sq",token[idx++], ref m_better_accuracy_sq);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::better_accuracy_op",token[idx++], ref m_better_accuracy_op);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::better_accuracy_cl",token[idx++], ref m_better_accuracy_cl);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::better_power_sq",token[idx++], ref m_better_power_sq);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::better_power_op",token[idx++], ref m_better_power_op);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::better_power_cl",token[idx++], ref m_better_power_cl);
			nUtil.jString_float.Parse("Sys_PlayerLevel::pitcher_speed_ov",token[idx++], ref m_pitcher_speed_ov);
			nUtil.jString_float.Parse("Sys_PlayerLevel::pitcher_speed_tq",token[idx++], ref m_pitcher_speed_tq);
			nUtil.jString_float.Parse("Sys_PlayerLevel::pitcher_speed_sa",token[idx++], ref m_pitcher_speed_sa);
			nUtil.jString_float.Parse("Sys_PlayerLevel::pitcher_speed_un",token[idx++], ref m_pitcher_speed_un);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_focus_ov",token[idx++], ref m_pitcher_focus_ov);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_focus_tq",token[idx++], ref m_pitcher_focus_tq);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_focus_sa",token[idx++], ref m_pitcher_focus_sa);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_focus_un",token[idx++], ref m_pitcher_focus_un);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_breakingball_ov",token[idx++], ref m_pitcher_breakingball_ov);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_breakingball_tq",token[idx++], ref m_pitcher_breakingball_tq);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_breakingball_sa",token[idx++], ref m_pitcher_breakingball_sa);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_breakingball_un",token[idx++], ref m_pitcher_breakingball_un);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_sid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_level.ToString() + ",";
			output += m_max_exp.ToString() + ",";
			output += m_better_accuracy_sq.ToString() + ",";
			output += m_better_accuracy_op.ToString() + ",";
			output += m_better_accuracy_cl.ToString() + ",";
			output += m_better_power_sq.ToString() + ",";
			output += m_better_power_op.ToString() + ",";
			output += m_better_power_cl.ToString() + ",";
			output += m_pitcher_speed_ov.ToString() + ",";
			output += m_pitcher_speed_tq.ToString() + ",";
			output += m_pitcher_speed_sa.ToString() + ",";
			output += m_pitcher_speed_un.ToString() + ",";
			output += m_pitcher_focus_ov.ToString() + ",";
			output += m_pitcher_focus_tq.ToString() + ",";
			output += m_pitcher_focus_sa.ToString() + ",";
			output += m_pitcher_focus_un.ToString() + ",";
			output += m_pitcher_breakingball_ov.ToString() + ",";
			output += m_pitcher_breakingball_tq.ToString() + ",";
			output += m_pitcher_breakingball_sa.ToString() + ",";
			output += m_pitcher_breakingball_un.ToString() + ",";
			return output;
		}
	}//class Sys_PlayerLevel

	namespace nUtil
	{
		class jString_Sys_PlayerLevel
		{
			public static string ToString(Sys_PlayerLevel o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_PlayerLevel> sysList)
			{
				string output = "";
				foreach (Sys_PlayerLevel o in sysList)
				{
					if( o==null )
						output += "NULL;";
					else
						output += (o.m_name + ";");
				}
				return output;
			}
			public static void PostParse(nEXCEL.nUtil.jCSV.PostParseData ppd)
			{
				Sys_PlayerLevel o = (Sys_PlayerLevel)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_PlayerLevel o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_PlayerLevel.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_PlayerLevel.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_PlayerLevel> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_PlayerLevel> sysList = (List<Sys_PlayerLevel>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_PlayerLevel o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_PlayerLevel.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_PlayerLevel.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_PlayerLevel
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_PlayerSkillSticker
			: Sys__Base_PlayerStat
	{
		public EBetterAbility m_better_skill1_type; 	// [Ÿ��Ư���ɷ�����] Ÿ�� ī���� ��ų ���� 
		public EPitcherAbility m_Pitcher_skill1_type; 	// [����Ư���ɷ�����] ���� ī���� ��ų ���� 
		public Int16 m_unlock_player_level; 	// [���׷��̵� ���� ����] �ش� ��ų��ƼĿ�� ���ɼ��ִ� �÷��̾�� 
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_EBetterAbility.Parse("Sys_PlayerSkillSticker::better_skill1_type",token[idx++], ref m_better_skill1_type);
			nUtil.jString_EPitcherAbility.Parse("Sys_PlayerSkillSticker::Pitcher_skill1_type",token[idx++], ref m_Pitcher_skill1_type);
			nUtil.jString_Int16.Parse("Sys_PlayerSkillSticker::unlock_player_level",token[idx++], ref m_unlock_player_level);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_better_skill1_type.ToString() + ",";
			output += m_Pitcher_skill1_type.ToString() + ",";
			output += m_unlock_player_level.ToString() + ",";
			return output;
		}
	}//class Sys_PlayerSkillSticker

	namespace nUtil
	{
		class jString_Sys_PlayerSkillSticker
		{
			public static string ToString(Sys_PlayerSkillSticker o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_PlayerSkillSticker> sysList)
			{
				string output = "";
				foreach (Sys_PlayerSkillSticker o in sysList)
				{
					if( o==null )
						output += "NULL;";
					else
						output += (o.m_name + ";");
				}
				return output;
			}
			public static void PostParse(nEXCEL.nUtil.jCSV.PostParseData ppd)
			{
				Sys_PlayerSkillSticker o = (Sys_PlayerSkillSticker)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_PlayerSkillSticker o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_PlayerSkillSticker.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_PlayerSkillSticker.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_PlayerSkillSticker> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_PlayerSkillSticker> sysList = (List<Sys_PlayerSkillSticker>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_PlayerSkillSticker o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_PlayerSkillSticker.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_PlayerSkillSticker.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_PlayerSkillSticker
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_Quest
	{
		public Sys_Quest_id_t m_sid; 	// [������ȣ]  
		public string m_name; 	// [����Ʈ�̸�] Ŭ�� ����� ��Ʈ���� name���� Sys_StringTable���� �˻��ؼ� ����Ѵ�. 
		public game_money_t m_quest_reward_money; 	// [����Ӵ�] ����Ʈ ���� ���ӸӴ� 
		public pp_point_t m_quest_reward_point; 	// [��������Ʈ] ����Ʈ ���� pp����Ʈ 
		public EConditionCharacterTitle m_condition_character_title; 	// [����ȣĪ��] ȣĪ �ο� �� ���̹� 
		public string m_help; 	// [���Ǽ���] ��¿��̾ƴ϶� ���߽� ������ 
		public EQuestConditionType m_condition_type1; 	// [����1Ÿ��]  
		public string m_condition1; 	// [����1����] ���� ��� NULL 
		public Int32 m_condition_value1; 	// [����1��]  
		public EQuestConditionType m_condition_type2; 	// [����2Ÿ��]  
		public string m_condition2; 	// [����2����]  
		public Int32 m_condition_value2; 	// [����2��]  
		public EQuestConditionType m_condition_type3; 	// [����3Ÿ��]  
		public string m_condition3; 	// [����3����]  
		public Int32 m_condition_value3; 	// [����3��]  
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_Quest::sid",token[idx++], ref m_sid);
			nUtil.jString_string.Parse("Sys_Quest::name",token[idx++], ref m_name);
			nUtil.jString_Int32.Parse("Sys_Quest::quest_reward_money",token[idx++], ref m_quest_reward_money);
			nUtil.jString_Int32.Parse("Sys_Quest::quest_reward_point",token[idx++], ref m_quest_reward_point);
			nUtil.jString_EConditionCharacterTitle.Parse("Sys_Quest::condition_character_title",token[idx++], ref m_condition_character_title);
			nUtil.jString_string.Parse("Sys_Quest::help",token[idx++], ref m_help);
			nUtil.jString_EQuestConditionType.Parse("Sys_Quest::condition_type1",token[idx++], ref m_condition_type1);
			nUtil.jString_string.Parse("Sys_Quest::condition1",token[idx++], ref m_condition1);
			nUtil.jString_Int32.Parse("Sys_Quest::condition_value1",token[idx++], ref m_condition_value1);
			nUtil.jString_EQuestConditionType.Parse("Sys_Quest::condition_type2",token[idx++], ref m_condition_type2);
			nUtil.jString_string.Parse("Sys_Quest::condition2",token[idx++], ref m_condition2);
			nUtil.jString_Int32.Parse("Sys_Quest::condition_value2",token[idx++], ref m_condition_value2);
			nUtil.jString_EQuestConditionType.Parse("Sys_Quest::condition_type3",token[idx++], ref m_condition_type3);
			nUtil.jString_string.Parse("Sys_Quest::condition3",token[idx++], ref m_condition3);
			nUtil.jString_Int32.Parse("Sys_Quest::condition_value3",token[idx++], ref m_condition_value3);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_sid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_quest_reward_money.ToString() + ",";
			output += m_quest_reward_point.ToString() + ",";
			output += m_condition_character_title.ToString() + ",";
			output += m_help.ToString() + ",";
			output += m_condition_type1.ToString() + ",";
			output += m_condition1.ToString() + ",";
			output += m_condition_value1.ToString() + ",";
			output += m_condition_type2.ToString() + ",";
			output += m_condition2.ToString() + ",";
			output += m_condition_value2.ToString() + ",";
			output += m_condition_type3.ToString() + ",";
			output += m_condition3.ToString() + ",";
			output += m_condition_value3.ToString() + ",";
			return output;
		}
	}//class Sys_Quest

	namespace nUtil
	{
		class jString_Sys_Quest
		{
			public static string ToString(Sys_Quest o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_Quest> sysList)
			{
				string output = "";
				foreach (Sys_Quest o in sysList)
				{
					if( o==null )
						output += "NULL;";
					else
						output += (o.m_name + ";");
				}
				return output;
			}
			public static void PostParse(nEXCEL.nUtil.jCSV.PostParseData ppd)
			{
				Sys_Quest o = (Sys_Quest)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_Quest o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_Quest.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_Quest.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_Quest> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_Quest> sysList = (List<Sys_Quest>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_Quest o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_Quest.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_Quest.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_Quest
	}//namespace nUtil
	

	// -------------------------------------------------
	// ���� ����Ʈ ���� �������� ���Ͽ��� ��� �� �����ϰ� �ϳ��� ����
	// -------------------------------------------------

	public class CSV_Sys_Daily_Quest
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Daily_Quest>		m_List = new List<Sys_Daily_Quest> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Daily_Quest >>>");
			foreach (Sys_Daily_Quest p in CSV_Sys_Daily_Quest.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Daily_Quest       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_Daily_Quest FindBy_name(string key){return (Sys_Daily_Quest)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_Daily_Quest p in m_List){m_Hashtable_name[p.m_name] = p;}
		}
		public static void LoadCSV(string sCsvFileName)
		{
			string sLine = "";
			string[] token;
			
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				Sys_Daily_Quest info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_Daily_Quest();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_Daily_Quest


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_PlayerCard
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_PlayerCard>		m_List = new List<Sys_PlayerCard> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_PlayerCard >>>");
			foreach (Sys_PlayerCard p in CSV_Sys_PlayerCard.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_PlayerCard       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_PlayerCard FindBy_name(string key){return (Sys_PlayerCard)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_PlayerCard p in m_List){m_Hashtable_name[p.m_name] = p;}
		}
		public static void LoadCSV(string sCsvFileName)
		{
			string sLine = "";
			string[] token;
			
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				Sys_PlayerCard info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_PlayerCard();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_PlayerCard


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_PlayerLevel
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_PlayerLevel>		m_List = new List<Sys_PlayerLevel> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_PlayerLevel >>>");
			foreach (Sys_PlayerLevel p in CSV_Sys_PlayerLevel.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_PlayerLevel       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_PlayerLevel FindBy_name(string key){return (Sys_PlayerLevel)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_PlayerLevel p in m_List){m_Hashtable_name[p.m_name] = p;}
		}
		public static void LoadCSV(string sCsvFileName)
		{
			string sLine = "";
			string[] token;
			
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				Sys_PlayerLevel info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_PlayerLevel();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_PlayerLevel


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_PlayerSkillSticker
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_PlayerSkillSticker>		m_List = new List<Sys_PlayerSkillSticker> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_PlayerSkillSticker >>>");
			foreach (Sys_PlayerSkillSticker p in CSV_Sys_PlayerSkillSticker.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_PlayerSkillSticker       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_PlayerSkillSticker FindBy_name(string key){return (Sys_PlayerSkillSticker)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_PlayerSkillSticker p in m_List){m_Hashtable_name[p.m_name] = p;}
		}
		public static void LoadCSV(string sCsvFileName)
		{
			string sLine = "";
			string[] token;
			
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				Sys_PlayerSkillSticker info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_PlayerSkillSticker();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_PlayerSkillSticker


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_Quest
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Quest>		m_List = new List<Sys_Quest> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Quest >>>");
			foreach (Sys_Quest p in CSV_Sys_Quest.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Quest       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_Quest FindBy_name(string key){return (Sys_Quest)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_Quest p in m_List){m_Hashtable_name[p.m_name] = p;}
		}
		public static void LoadCSV(string sCsvFileName)
		{
			string sLine = "";
			string[] token;
			
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				Sys_Quest info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_Quest();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_Quest



	


}//namespace nEXCEL
