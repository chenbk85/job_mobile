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
	// 설명없음
	// -------------------------------------------------

	public class Sys__ItemBase
	{
		public Sys__ItemBase_id_t m_sid; 	// [고유식별ID]  
		public string m_name; 	// [이름] 영문이름 고유해야함. 이 영문이름으로 스트링테이블에서 한글이름검색 
		public EItemCategory m_category; 	// [대분류]  
		public bool m_upgrade_type; 	// [업그레이드 가능 유뮤] 업그레이드가 가능한지의 여부 
		public bool m_is_visual; 	// [비쥬얼] 화면에 보여지느냐 안보여지느냐 여부 
		public string m_help; 	// [설명]  
		public EItemGradeType m_grade; 	// [등급] 아이템 업그레이드 등급 
		public EItemSubGradeType m_subgrade; 	// [서브 등급] 아이템 서브 업그레이드 등급 
		public player_level_t m_player_level_min; 	// [사용레벨MIN] 현제는 약 110까지 가능 
		public player_level_t m_player_level_max; 	// [사용레벨MAX] 현제는 약 110까지 가능 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_UInt16.Parse("Sys__ItemBase::sid",token[idx++], ref m_sid);
				nUtil.jString_string.Parse("Sys__ItemBase::name",token[idx++], ref m_name);
				nUtil.jString_EItemCategory.Parse("Sys__ItemBase::category",token[idx++], ref m_category);
				nUtil.jString_bool.Parse("Sys__ItemBase::upgrade_type",token[idx++], ref m_upgrade_type);
				nUtil.jString_bool.Parse("Sys__ItemBase::is_visual",token[idx++], ref m_is_visual);
				nUtil.jString_string.Parse("Sys__ItemBase::help",token[idx++], ref m_help);
				nUtil.jString_EItemGradeType.Parse("Sys__ItemBase::grade",token[idx++], ref m_grade);
				nUtil.jString_EItemSubGradeType.Parse("Sys__ItemBase::subgrade",token[idx++], ref m_subgrade);
				nUtil.jString_Int32.Parse("Sys__ItemBase::player_level_min",token[idx++], ref m_player_level_min);
				nUtil.jString_Int32.Parse("Sys__ItemBase::player_level_max",token[idx++], ref m_player_level_max);
			}
catch(System.Exception e)
			{
				if (nEXCEL.nUtil.jCSV.m_ErrorLogFunc != null)
				{
					String strError = String.Format("{0} = id={1} {2} [ {3} ]", e.ToString(), token[0], token[idx -1],idx -1);
					nEXCEL.nUtil.jCSV.m_ErrorLogFunc(strError,e);
				}
				else
				{
					Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
					throw e;
				}
			}
		}
		public override string ToString()
		{
			string output = "";
			output += m_sid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_category.ToString() + ",";
			output += m_upgrade_type.ToString() + ",";
			output += m_is_visual.ToString() + ",";
			output += m_help.ToString() + ",";
			output += m_grade.ToString() + ",";
			output += m_subgrade.ToString() + ",";
			output += m_player_level_min.ToString() + ",";
			output += m_player_level_max.ToString() + ",";
			return output;
		}
	}//class Sys__ItemBase

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_ItemEquip
			: Sys__ItemBase
	{
		public EItemCategoryEquipment m_equip_category; 	// [장비아이템카테고리] 장비아이템카테고리 
		public EItemSexType m_sex_type; 	// [아이템남여구분] 남여구분 
		public EPlayerType m_player_type; 	// [타자투수구분] 타자투수구분 
		public EItemAbilityType m_item_batter_ability_type; 	// [타자 아이템 영향 스텟] 타자 아이템 영향 스텟 
		public EItemAbilityType m_item_pitcher_ability_type; 	// [투수 아이템 영향 스텟] 투수 아이템 영향 스텟 
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				base.ReadCSV(token,ref idx,isPostParse);
				nUtil.jString_EItemCategoryEquipment.Parse("Sys_ItemEquip::equip_category",token[idx++], ref m_equip_category);
				nUtil.jString_EItemSexType.Parse("Sys_ItemEquip::sex_type",token[idx++], ref m_sex_type);
				nUtil.jString_EPlayerType.Parse("Sys_ItemEquip::player_type",token[idx++], ref m_player_type);
				nUtil.jString_EItemAbilityType.Parse("Sys_ItemEquip::item_batter_ability_type",token[idx++], ref m_item_batter_ability_type);
				nUtil.jString_EItemAbilityType.Parse("Sys_ItemEquip::item_pitcher_ability_type",token[idx++], ref m_item_pitcher_ability_type);
			}
catch(System.Exception e)
			{
				if (nEXCEL.nUtil.jCSV.m_ErrorLogFunc != null)
				{
					String strError = String.Format("{0} = id={1} {2} [ {3} ]", e.ToString(), token[0], token[idx -1],idx -1);
					nEXCEL.nUtil.jCSV.m_ErrorLogFunc(strError,e);
				}
				else
				{
					Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
					throw e;
				}
			}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_equip_category.ToString() + ",";
			output += m_sex_type.ToString() + ",";
			output += m_player_type.ToString() + ",";
			output += m_item_batter_ability_type.ToString() + ",";
			output += m_item_pitcher_ability_type.ToString() + ",";
			return output;
		}
	}//class Sys_ItemEquip

	namespace nUtil
	{
		class jString_Sys_ItemEquip
		{
			public static string ToString(Sys_ItemEquip o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_ItemEquip> sysList)
			{
				string output = "";
				foreach (Sys_ItemEquip o in sysList)
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
				Sys_ItemEquip o = (Sys_ItemEquip)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_ItemEquip o)
			{
				if(sVal=="" || sVal=="0" || sVal=="NULL" || sVal=="null") return true;
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_ItemEquip.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_ItemEquip.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_ItemEquip> oList)
			{
				oList.Clear();
				if(sVal=="" || sVal=="0" || sVal=="NULL" || sVal=="null") return true;
				bool isFind=false;
				List<Sys_ItemEquip> sysList = (List<Sys_ItemEquip>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_ItemEquip o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_ItemEquip.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_ItemEquip.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null)
						isFind=true;
					else
						throw new System.Exception(sVal + " -> ((" + s + ")) IS NOT FOUND !! : " + sDebug);
				}
				return isFind;
			}
		}//class jString_Sys_ItemEquip
	}//namespace nUtil
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_ItemStuff
			: Sys__ItemBase
	{
		public EItemUpgradeResult m_upgradable_item_type; 	// [업그레이드시킬수있는아이템종류] 업그레이드시킬수있는아이템종류 
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				base.ReadCSV(token,ref idx,isPostParse);
				nUtil.jString_EItemUpgradeResult.Parse("Sys_ItemStuff::upgradable_item_type",token[idx++], ref m_upgradable_item_type);
			}
catch(System.Exception e)
			{
				if (nEXCEL.nUtil.jCSV.m_ErrorLogFunc != null)
				{
					String strError = String.Format("{0} = id={1} {2} [ {3} ]", e.ToString(), token[0], token[idx -1],idx -1);
					nEXCEL.nUtil.jCSV.m_ErrorLogFunc(strError,e);
				}
				else
				{
					Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
					throw e;
				}
			}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_upgradable_item_type.ToString() + ",";
			return output;
		}
	}//class Sys_ItemStuff

	namespace nUtil
	{
		class jString_Sys_ItemStuff
		{
			public static string ToString(Sys_ItemStuff o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_ItemStuff> sysList)
			{
				string output = "";
				foreach (Sys_ItemStuff o in sysList)
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
				Sys_ItemStuff o = (Sys_ItemStuff)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_ItemStuff o)
			{
				if(sVal=="" || sVal=="0" || sVal=="NULL" || sVal=="null") return true;
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_ItemStuff.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_ItemStuff.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_ItemStuff> oList)
			{
				oList.Clear();
				if(sVal=="" || sVal=="0" || sVal=="NULL" || sVal=="null") return true;
				bool isFind=false;
				List<Sys_ItemStuff> sysList = (List<Sys_ItemStuff>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_ItemStuff o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_ItemStuff.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_ItemStuff.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null)
						isFind=true;
					else
						throw new System.Exception(sVal + " -> ((" + s + ")) IS NOT FOUND !! : " + sDebug);
				}
				return isFind;
			}
		}//class jString_Sys_ItemStuff
	}//namespace nUtil
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_ItemConsume
			: Sys__ItemBase
	{
		public EPlayerType m_player_type; 	// [타자투수구분] 타자투수구분 
		public EConsumeItemEffect m_consume_item_effect; 	// [컨슘아이템효과] 컨슘아이템 소비 시 효과 구분 
		public EItemAbilityType m_Item_Ability_Type; 	// [아이템영향스텟] 컨슘아이템영향스텟 
		public Int16 m_consume_item_effect_value; 	// [컨슘아이템효과값] 각 해당 아이템 효과의 값(아이템의 효과 마다 값이 다름-->) 
		public Int16 m_gameplay_effect_repeat; 	// [게임 플레이시 지속효과 제한(횟수)] 게임 플레이시 지속효과 제한(횟수) 
		public Int16 m_gameplay_effect_time; 	// [게임 플레이시 지속효과 제한(시간)] 게임 플레이시 지속효과 제한(시간) 
		public bool m_consume_item_overlap; 	// [다른아이템과 중복사용 여부] 다른아이템과 중복사용 여부 
		public Int16 m_use_count; 	// [사용 횟수] 사용 횟수 
		public bool m_is_bonus; 	// [보너스용아이템] 보너스용아이템 
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				base.ReadCSV(token,ref idx,isPostParse);
				nUtil.jString_EPlayerType.Parse("Sys_ItemConsume::player_type",token[idx++], ref m_player_type);
				nUtil.jString_EConsumeItemEffect.Parse("Sys_ItemConsume::consume_item_effect",token[idx++], ref m_consume_item_effect);
				nUtil.jString_EItemAbilityType.Parse("Sys_ItemConsume::Item_Ability_Type",token[idx++], ref m_Item_Ability_Type);
				nUtil.jString_Int16.Parse("Sys_ItemConsume::consume_item_effect_value",token[idx++], ref m_consume_item_effect_value);
				nUtil.jString_Int16.Parse("Sys_ItemConsume::gameplay_effect_repeat",token[idx++], ref m_gameplay_effect_repeat);
				nUtil.jString_Int16.Parse("Sys_ItemConsume::gameplay_effect_time",token[idx++], ref m_gameplay_effect_time);
				nUtil.jString_bool.Parse("Sys_ItemConsume::consume_item_overlap",token[idx++], ref m_consume_item_overlap);
				nUtil.jString_Int16.Parse("Sys_ItemConsume::use_count",token[idx++], ref m_use_count);
				nUtil.jString_bool.Parse("Sys_ItemConsume::is_bonus",token[idx++], ref m_is_bonus);
			}
catch(System.Exception e)
			{
				if (nEXCEL.nUtil.jCSV.m_ErrorLogFunc != null)
				{
					String strError = String.Format("{0} = id={1} {2} [ {3} ]", e.ToString(), token[0], token[idx -1],idx -1);
					nEXCEL.nUtil.jCSV.m_ErrorLogFunc(strError,e);
				}
				else
				{
					Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
					throw e;
				}
			}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_player_type.ToString() + ",";
			output += m_consume_item_effect.ToString() + ",";
			output += m_Item_Ability_Type.ToString() + ",";
			output += m_consume_item_effect_value.ToString() + ",";
			output += m_gameplay_effect_repeat.ToString() + ",";
			output += m_gameplay_effect_time.ToString() + ",";
			output += m_consume_item_overlap.ToString() + ",";
			output += m_use_count.ToString() + ",";
			output += m_is_bonus.ToString() + ",";
			return output;
		}
	}//class Sys_ItemConsume

	namespace nUtil
	{
		class jString_Sys_ItemConsume
		{
			public static string ToString(Sys_ItemConsume o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_ItemConsume> sysList)
			{
				string output = "";
				foreach (Sys_ItemConsume o in sysList)
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
				Sys_ItemConsume o = (Sys_ItemConsume)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_ItemConsume o)
			{
				if(sVal=="" || sVal=="0" || sVal=="NULL" || sVal=="null") return true;
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_ItemConsume.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_ItemConsume.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_ItemConsume> oList)
			{
				oList.Clear();
				if(sVal=="" || sVal=="0" || sVal=="NULL" || sVal=="null") return true;
				bool isFind=false;
				List<Sys_ItemConsume> sysList = (List<Sys_ItemConsume>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_ItemConsume o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_ItemConsume.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_ItemConsume.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null)
						isFind=true;
					else
						throw new System.Exception(sVal + " -> ((" + s + ")) IS NOT FOUND !! : " + sDebug);
				}
				return isFind;
			}
		}//class jString_Sys_ItemConsume
	}//namespace nUtil
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_ItemEquip
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_ItemEquip>		m_List = new List<Sys_ItemEquip> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_ItemEquip >>>");
			foreach (Sys_ItemEquip p in CSV_Sys_ItemEquip.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_ItemEquip       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_ItemEquip FindBy_name(string key){return (Sys_ItemEquip)m_Hashtable_name[key];}

		private static Dictionary<EItemGradeType,List<Sys_ItemEquip>> m_Dictionary_grade = new Dictionary<EItemGradeType,List<Sys_ItemEquip>>{};
		public static List<Sys_ItemEquip> FindBy_grade(EItemGradeType key){return m_Dictionary_grade[key];}

		private static void _makeIndex()
		{
			foreach(Sys_ItemEquip p in m_List){m_Hashtable_name[p.m_name] = p;}
			foreach(Sys_ItemEquip p in m_List)
			{
				if (!m_Dictionary_grade.ContainsKey(p.m_grade))
				{
					m_Dictionary_grade[p.m_grade] = new List<Sys_ItemEquip> { };
				}
				m_Dictionary_grade[p.m_grade].Add(p);
			}
		}
		public static void LoadCSV(string sCsvFileName)
		{
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				string sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					string[] token = sLine.Split(',');
					Sys_ItemEquip info = new Sys_ItemEquip();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

		public static void LoadCSV_FromString(string sData)
		{
			string test = "\n\r";
			string[] all_line = sData.Split(test.ToCharArray());
			int i=0;
			foreach(String sLine in all_line)
			{
				if(i==0){ ++i;continue;}
				if (sLine.Length == 0) continue;
				string[] token = sLine.Split(',');
				Sys_ItemEquip info = new Sys_ItemEquip();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
			_makeIndex();
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_ItemEquip


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_ItemStuff
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_ItemStuff>		m_List = new List<Sys_ItemStuff> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_ItemStuff >>>");
			foreach (Sys_ItemStuff p in CSV_Sys_ItemStuff.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_ItemStuff       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_ItemStuff FindBy_name(string key){return (Sys_ItemStuff)m_Hashtable_name[key];}

		private static Dictionary<EItemGradeType,List<Sys_ItemStuff>> m_Dictionary_grade = new Dictionary<EItemGradeType,List<Sys_ItemStuff>>{};
		public static List<Sys_ItemStuff> FindBy_grade(EItemGradeType key){return m_Dictionary_grade[key];}

		private static void _makeIndex()
		{
			foreach(Sys_ItemStuff p in m_List){m_Hashtable_name[p.m_name] = p;}
			foreach(Sys_ItemStuff p in m_List)
			{
				if (!m_Dictionary_grade.ContainsKey(p.m_grade))
				{
					m_Dictionary_grade[p.m_grade] = new List<Sys_ItemStuff> { };
				}
				m_Dictionary_grade[p.m_grade].Add(p);
			}
		}
		public static void LoadCSV(string sCsvFileName)
		{
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				string sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					string[] token = sLine.Split(',');
					Sys_ItemStuff info = new Sys_ItemStuff();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

		public static void LoadCSV_FromString(string sData)
		{
			string test = "\n\r";
			string[] all_line = sData.Split(test.ToCharArray());
			int i=0;
			foreach(String sLine in all_line)
			{
				if(i==0){ ++i;continue;}
				if (sLine.Length == 0) continue;
				string[] token = sLine.Split(',');
				Sys_ItemStuff info = new Sys_ItemStuff();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
			_makeIndex();
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_ItemStuff


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_ItemConsume
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_ItemConsume>		m_List = new List<Sys_ItemConsume> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_ItemConsume >>>");
			foreach (Sys_ItemConsume p in CSV_Sys_ItemConsume.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_ItemConsume       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_ItemConsume FindBy_name(string key){return (Sys_ItemConsume)m_Hashtable_name[key];}

		private static Dictionary<EItemGradeType,List<Sys_ItemConsume>> m_Dictionary_grade = new Dictionary<EItemGradeType,List<Sys_ItemConsume>>{};
		public static List<Sys_ItemConsume> FindBy_grade(EItemGradeType key){return m_Dictionary_grade[key];}

		private static void _makeIndex()
		{
			foreach(Sys_ItemConsume p in m_List){m_Hashtable_name[p.m_name] = p;}
			foreach(Sys_ItemConsume p in m_List)
			{
				if (!m_Dictionary_grade.ContainsKey(p.m_grade))
				{
					m_Dictionary_grade[p.m_grade] = new List<Sys_ItemConsume> { };
				}
				m_Dictionary_grade[p.m_grade].Add(p);
			}
		}
		public static void LoadCSV(string sCsvFileName)
		{
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				string sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					string[] token = sLine.Split(',');
					Sys_ItemConsume info = new Sys_ItemConsume();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

		public static void LoadCSV_FromString(string sData)
		{
			string test = "\n\r";
			string[] all_line = sData.Split(test.ToCharArray());
			int i=0;
			foreach(String sLine in all_line)
			{
				if(i==0){ ++i;continue;}
				if (sLine.Length == 0) continue;
				string[] token = sLine.Split(',');
				Sys_ItemConsume info = new Sys_ItemConsume();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
			_makeIndex();
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_ItemConsume



	


}//namespace nEXCEL
