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
		public player_level_t m_player_level_min; 	// [사용레벨MIN] 현제는 약 110까지 가능 
		public player_level_t m_player_level_max; 	// [사용레벨MAX] 현제는 약 110까지 가능 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
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
			nUtil.jString_Int32.Parse("Sys__ItemBase::player_level_min",token[idx++], ref m_player_level_min);
			nUtil.jString_Int32.Parse("Sys__ItemBase::player_level_max",token[idx++], ref m_player_level_max);
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
			output += m_category.ToString() + ",";
			output += m_upgrade_type.ToString() + ",";
			output += m_is_visual.ToString() + ",";
			output += m_help.ToString() + ",";
			output += m_grade.ToString() + ",";
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
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_EItemCategoryEquipment.Parse("Sys_ItemEquip::equip_category",token[idx++], ref m_equip_category);
			nUtil.jString_EItemSexType.Parse("Sys_ItemEquip::sex_type",token[idx++], ref m_sex_type);
			nUtil.jString_EPlayerType.Parse("Sys_ItemEquip::player_type",token[idx++], ref m_player_type);
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
			output += m_equip_category.ToString() + ",";
			output += m_sex_type.ToString() + ",";
			output += m_player_type.ToString() + ",";
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
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_ItemEquip
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
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
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
			output += m_player_type.ToString() + ",";
			output += m_consume_item_effect.ToString() + ",";
			output += m_Item_Ability_Type.ToString() + ",";
			output += m_consume_item_effect_value.ToString() + ",";
			output += m_gameplay_effect_repeat.ToString() + ",";
			output += m_gameplay_effect_time.ToString() + ",";
			output += m_consume_item_overlap.ToString() + ",";
			output += m_use_count.ToString() + ",";
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
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_ItemConsume
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
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_EItemUpgradeResult.Parse("Sys_ItemStuff::upgradable_item_type",token[idx++], ref m_upgradable_item_type);
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
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_ItemStuff
	}//namespace nUtil
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_MainItemAbility
	{
		public Int16 m_sid; 	// [고유번호] 고유번호 
		public EItemCategoryEquipment m_equip_category; 	// [장비아이템카테고리] 장비아이템카테고리 
		public EItemGradeType m_grade; 	// [등급] 아이템 업그레이드 등급 
		public string m_name; 	// [업그레이드단계] EE SS SA … 
		public float m_mainitem_first_equip_level; 	// [아이템최초 장착 레벨] 아이템 최초 장착 레벨 
		public float m_mainitem_possible_upgrade_level; 	// [아이템강화 가능 레벨] 아이템 강화 가능 레벨 
		public float m_mainitem_need_time; 	// [아이템강화 필요 시간] 아이템 강화 필요 시간 
		public float m_mainitem_basic_value; 	// [아이템기본능력치] 아이템 기본 능력치 
		public float m_mainitem_equip_level; 	// [해당아이템장착레벨] 해당아이템장착레벨 
		public float m_value_min; 	// [강화시최소증가능력치] 강화시 최소 증가 능력치(IUR_NORMAL) 
		public float m_value_max; 	// [강화시최대증가능력치] 강화시 최대 증가 능력치(IUR_PERFECT) 
		public EPlayerType m_player_type; 	// [타자투수구분] 타자투수구분 
		public Int64 m_mainitem_upgrade_need_money; 	// [필요게임머니] 업그레이드 필요 게임 머니 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int16.Parse("Sys_MainItemAbility::sid",token[idx++], ref m_sid);
			nUtil.jString_EItemCategoryEquipment.Parse("Sys_MainItemAbility::equip_category",token[idx++], ref m_equip_category);
			nUtil.jString_EItemGradeType.Parse("Sys_MainItemAbility::grade",token[idx++], ref m_grade);
			nUtil.jString_string.Parse("Sys_MainItemAbility::name",token[idx++], ref m_name);
			nUtil.jString_float.Parse("Sys_MainItemAbility::mainitem_first_equip_level",token[idx++], ref m_mainitem_first_equip_level);
			nUtil.jString_float.Parse("Sys_MainItemAbility::mainitem_possible_upgrade_level",token[idx++], ref m_mainitem_possible_upgrade_level);
			nUtil.jString_float.Parse("Sys_MainItemAbility::mainitem_need_time",token[idx++], ref m_mainitem_need_time);
			nUtil.jString_float.Parse("Sys_MainItemAbility::mainitem_basic_value",token[idx++], ref m_mainitem_basic_value);
			nUtil.jString_float.Parse("Sys_MainItemAbility::mainitem_equip_level",token[idx++], ref m_mainitem_equip_level);
			nUtil.jString_float.Parse("Sys_MainItemAbility::value_min",token[idx++], ref m_value_min);
			nUtil.jString_float.Parse("Sys_MainItemAbility::value_max",token[idx++], ref m_value_max);
			nUtil.jString_EPlayerType.Parse("Sys_MainItemAbility::player_type",token[idx++], ref m_player_type);
			nUtil.jString_Int64.Parse("Sys_MainItemAbility::mainitem_upgrade_need_money",token[idx++], ref m_mainitem_upgrade_need_money);
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
			output += m_equip_category.ToString() + ",";
			output += m_grade.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_mainitem_first_equip_level.ToString() + ",";
			output += m_mainitem_possible_upgrade_level.ToString() + ",";
			output += m_mainitem_need_time.ToString() + ",";
			output += m_mainitem_basic_value.ToString() + ",";
			output += m_mainitem_equip_level.ToString() + ",";
			output += m_value_min.ToString() + ",";
			output += m_value_max.ToString() + ",";
			output += m_player_type.ToString() + ",";
			output += m_mainitem_upgrade_need_money.ToString() + ",";
			return output;
		}
	}//class Sys_MainItemAbility

	namespace nUtil
	{
		class jString_Sys_MainItemAbility
		{
			public static string ToString(Sys_MainItemAbility o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_MainItemAbility> sysList)
			{
				string output = "";
				foreach (Sys_MainItemAbility o in sysList)
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
				Sys_MainItemAbility o = (Sys_MainItemAbility)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_MainItemAbility o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_MainItemAbility.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_MainItemAbility.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_MainItemAbility> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_MainItemAbility> sysList = (List<Sys_MainItemAbility>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_MainItemAbility o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_MainItemAbility.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_MainItemAbility.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_MainItemAbility
	}//namespace nUtil
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_Package
	{
		public Int16 m_sid; 	// [sid]  
		public string m_name; 	// [name]  
		public EItemPriceType m_price_type; 	// [구매타입]  
		public Int32 m_price_money; 	// [필요게임머니]  
		public Int32 m_price_cash; 	// [필요리얼캐쉬]  
		public EGradeAllitemType m_grade_allitem_type1; 	// [아이템별그레이드모음1] 아이템별그레이드모음1(EX : 메인아이템S급 모두, 서브아이템s급 모두…) 
		public EGradeAllitemType m_grade_allitem_type2; 	// [아이템별그레이드모음2] 아이템별그레이드모음2 
		public EGradeAllitemType m_grade_allitem_type3; 	// [아이템별그레이드모음3] 아이템별그레이드모음3 
		public EGradeAllitemType m_grade_allitem_type4; 	// [아이템별그레이드모음4] 아이템별그레이드모음4 
		public EGiftType m_gift_type1; 	// [선물종류1]  
		public Int64 m_gift_type1_value; 	// [선물1] value의 의미는 EGiftType에 따라 다르다 
		public EGiftType m_gift_type2; 	// [선물종류2]  
		public Int64 m_gift_type2_value; 	// [선물2]  
		public EGiftType m_gift_type3; 	// [선물종류3]  
		public Int64 m_gift_type3_value; 	// [선물3]  
		public EGiftType m_gift_type4; 	// [선물종류4]  
		public Int64 m_gift_type4_value; 	// [선물4]  
		public EGiftType m_gift_type5; 	// [선물종류5]  
		public Int64 m_gift_type5_value; 	// [선물5]  
		public EGiftType m_gift_type6; 	// [선물종류6]  
		public Int64 m_gift_type6_value; 	// [선물6]  
		public EGiftType m_gift_type7; 	// [선물종류7]  
		public Int64 m_gift_type7_value; 	// [선물7]  
		public EGiftType m_gift_type8; 	// [선물종류8]  
		public Int64 m_gift_type8_value; 	// [선물8]  
		public EGiftType m_gift_type9; 	// [선물종류9]  
		public Int64 m_gift_type9_value; 	// [선물9]  
		public EGiftType m_gift_type10; 	// [선물종류10]  
		public Int64 m_gift_type10_value; 	// [선물10]  
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int16.Parse("Sys_Package::sid",token[idx++], ref m_sid);
			nUtil.jString_string.Parse("Sys_Package::name",token[idx++], ref m_name);
			nUtil.jString_EItemPriceType.Parse("Sys_Package::price_type",token[idx++], ref m_price_type);
			nUtil.jString_Int32.Parse("Sys_Package::price_money",token[idx++], ref m_price_money);
			nUtil.jString_Int32.Parse("Sys_Package::price_cash",token[idx++], ref m_price_cash);
			nUtil.jString_EGradeAllitemType.Parse("Sys_Package::grade_allitem_type1",token[idx++], ref m_grade_allitem_type1);
			nUtil.jString_EGradeAllitemType.Parse("Sys_Package::grade_allitem_type2",token[idx++], ref m_grade_allitem_type2);
			nUtil.jString_EGradeAllitemType.Parse("Sys_Package::grade_allitem_type3",token[idx++], ref m_grade_allitem_type3);
			nUtil.jString_EGradeAllitemType.Parse("Sys_Package::grade_allitem_type4",token[idx++], ref m_grade_allitem_type4);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type1",token[idx++], ref m_gift_type1);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type1_value",token[idx++], ref m_gift_type1_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type2",token[idx++], ref m_gift_type2);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type2_value",token[idx++], ref m_gift_type2_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type3",token[idx++], ref m_gift_type3);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type3_value",token[idx++], ref m_gift_type3_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type4",token[idx++], ref m_gift_type4);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type4_value",token[idx++], ref m_gift_type4_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type5",token[idx++], ref m_gift_type5);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type5_value",token[idx++], ref m_gift_type5_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type6",token[idx++], ref m_gift_type6);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type6_value",token[idx++], ref m_gift_type6_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type7",token[idx++], ref m_gift_type7);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type7_value",token[idx++], ref m_gift_type7_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type8",token[idx++], ref m_gift_type8);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type8_value",token[idx++], ref m_gift_type8_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type9",token[idx++], ref m_gift_type9);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type9_value",token[idx++], ref m_gift_type9_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type10",token[idx++], ref m_gift_type10);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type10_value",token[idx++], ref m_gift_type10_value);
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
			output += m_price_type.ToString() + ",";
			output += m_price_money.ToString() + ",";
			output += m_price_cash.ToString() + ",";
			output += m_grade_allitem_type1.ToString() + ",";
			output += m_grade_allitem_type2.ToString() + ",";
			output += m_grade_allitem_type3.ToString() + ",";
			output += m_grade_allitem_type4.ToString() + ",";
			output += m_gift_type1.ToString() + ",";
			output += m_gift_type1_value.ToString() + ",";
			output += m_gift_type2.ToString() + ",";
			output += m_gift_type2_value.ToString() + ",";
			output += m_gift_type3.ToString() + ",";
			output += m_gift_type3_value.ToString() + ",";
			output += m_gift_type4.ToString() + ",";
			output += m_gift_type4_value.ToString() + ",";
			output += m_gift_type5.ToString() + ",";
			output += m_gift_type5_value.ToString() + ",";
			output += m_gift_type6.ToString() + ",";
			output += m_gift_type6_value.ToString() + ",";
			output += m_gift_type7.ToString() + ",";
			output += m_gift_type7_value.ToString() + ",";
			output += m_gift_type8.ToString() + ",";
			output += m_gift_type8_value.ToString() + ",";
			output += m_gift_type9.ToString() + ",";
			output += m_gift_type9_value.ToString() + ",";
			output += m_gift_type10.ToString() + ",";
			output += m_gift_type10_value.ToString() + ",";
			return output;
		}
	}//class Sys_Package

	namespace nUtil
	{
		class jString_Sys_Package
		{
			public static string ToString(Sys_Package o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_Package> sysList)
			{
				string output = "";
				foreach (Sys_Package o in sysList)
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
				Sys_Package o = (Sys_Package)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_Package o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_Package.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_Package.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_Package> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_Package> sysList = (List<Sys_Package>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_Package o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_Package.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_Package.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_Package
	}//namespace nUtil
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_Shop
	{
		public Sys_Shop_id_t m_shop_id; 	// [shop_id]  
		public string m_name; 	// [name]  
		public EShopItemType m_item_type; 	// [item_type] 아이템 type 
		public Int32 m_item_index; 	// [item_index] 아이템 index 
		public bool m_is_new; 	// [is_new] 신상품인지 아닌지 
		public bool m_is_best; 	// [is_best] 베스트 상품인지 아닌지 
		public bool m_is_hot; 	// [is_hot] 핫 상품인지 아닌지 
		public EShopBetterSection m_shop_better_section; 	// [shop_better_section] 샵의 섹션 구분(타자 아이템) 
		public EShopPitcherSection m_shop_pitcher_section; 	// [shop_pitcher_section] 샵의 섹션 구분(투수 아이템) 
		public EShopConsumeSection m_shop_consume_section; 	// [shop_consume_section] 샵의 섹션 구분(소비 아이템) 
		public DATETIME m_sell_start_date; 	// [판매 시작 일시] 판매 시작 일시 
		public DATETIME m_sell_end_date; 	// [판매 종료 일시] 판매 종료 일시 
		public Int32 m_price_money; 	// [필요게임머니] 필요게임머니 
		public Int32 m_price_cash; 	// [필요리얼캐쉬] 필요리얼캐쉬 
		public EItemPriceType m_price_type; 	// [구매타입] 구매타입 
		public EItemSellStatus m_sell_status; 	// [판매상태] 판매상태 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_Shop::shop_id",token[idx++], ref m_shop_id);
			nUtil.jString_string.Parse("Sys_Shop::name",token[idx++], ref m_name);
			nUtil.jString_EShopItemType.Parse("Sys_Shop::item_type",token[idx++], ref m_item_type);
			nUtil.jString_Int32.Parse("Sys_Shop::item_index",token[idx++], ref m_item_index);
			nUtil.jString_bool.Parse("Sys_Shop::is_new",token[idx++], ref m_is_new);
			nUtil.jString_bool.Parse("Sys_Shop::is_best",token[idx++], ref m_is_best);
			nUtil.jString_bool.Parse("Sys_Shop::is_hot",token[idx++], ref m_is_hot);
			nUtil.jString_EShopBetterSection.Parse("Sys_Shop::shop_better_section",token[idx++], ref m_shop_better_section);
			nUtil.jString_EShopPitcherSection.Parse("Sys_Shop::shop_pitcher_section",token[idx++], ref m_shop_pitcher_section);
			nUtil.jString_EShopConsumeSection.Parse("Sys_Shop::shop_consume_section",token[idx++], ref m_shop_consume_section);
			nUtil.jString_DATETIME.Parse("Sys_Shop::sell_start_date",token[idx++], ref m_sell_start_date);
			nUtil.jString_DATETIME.Parse("Sys_Shop::sell_end_date",token[idx++], ref m_sell_end_date);
			nUtil.jString_Int32.Parse("Sys_Shop::price_money",token[idx++], ref m_price_money);
			nUtil.jString_Int32.Parse("Sys_Shop::price_cash",token[idx++], ref m_price_cash);
			nUtil.jString_EItemPriceType.Parse("Sys_Shop::price_type",token[idx++], ref m_price_type);
			nUtil.jString_EItemSellStatus.Parse("Sys_Shop::sell_status",token[idx++], ref m_sell_status);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_shop_id.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_item_type.ToString() + ",";
			output += m_item_index.ToString() + ",";
			output += m_is_new.ToString() + ",";
			output += m_is_best.ToString() + ",";
			output += m_is_hot.ToString() + ",";
			output += m_shop_better_section.ToString() + ",";
			output += m_shop_pitcher_section.ToString() + ",";
			output += m_shop_consume_section.ToString() + ",";
			output += m_sell_start_date.ToString() + ",";
			output += m_sell_end_date.ToString() + ",";
			output += m_price_money.ToString() + ",";
			output += m_price_cash.ToString() + ",";
			output += m_price_type.ToString() + ",";
			output += m_sell_status.ToString() + ",";
			return output;
		}
	}//class Sys_Shop

	namespace nUtil
	{
		class jString_Sys_Shop
		{
			public static string ToString(Sys_Shop o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_Shop> sysList)
			{
				string output = "";
				foreach (Sys_Shop o in sysList)
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
				Sys_Shop o = (Sys_Shop)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_Shop o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_Shop.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_Shop.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_Shop> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_Shop> sysList = (List<Sys_Shop>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_Shop o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_Shop.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_Shop.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_Shop
	}//namespace nUtil
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_SubItemAbility
	{
		public Int16 m_sid; 	// [고유번호] 고유번호 
		public EItemCategoryEquipment m_equip_category; 	// [장비아이템카테고리] 장비아이템카테고리 
		public EItemGradeType m_grade; 	// [등급] 아이템 업그레이드 등급 
		public Int16 m_subitem_first_equip_level; 	// [아이템최초 장착 레벨] 아이템 최초 장착 레벨 
		public Int16 m_subitem_better_ability; 	// [아이템타자능력치] 아이템 기본 능력치 
		public float m_subitem_pitcher_ability; 	// [아이템투수능력치] 아이템 기본 능력치 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int16.Parse("Sys_SubItemAbility::sid",token[idx++], ref m_sid);
			nUtil.jString_EItemCategoryEquipment.Parse("Sys_SubItemAbility::equip_category",token[idx++], ref m_equip_category);
			nUtil.jString_EItemGradeType.Parse("Sys_SubItemAbility::grade",token[idx++], ref m_grade);
			nUtil.jString_Int16.Parse("Sys_SubItemAbility::subitem_first_equip_level",token[idx++], ref m_subitem_first_equip_level);
			nUtil.jString_Int16.Parse("Sys_SubItemAbility::subitem_better_ability",token[idx++], ref m_subitem_better_ability);
			nUtil.jString_float.Parse("Sys_SubItemAbility::subitem_pitcher_ability",token[idx++], ref m_subitem_pitcher_ability);
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
			output += m_equip_category.ToString() + ",";
			output += m_grade.ToString() + ",";
			output += m_subitem_first_equip_level.ToString() + ",";
			output += m_subitem_better_ability.ToString() + ",";
			output += m_subitem_pitcher_ability.ToString() + ",";
			return output;
		}
	}//class Sys_SubItemAbility

	

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

		private static void _makeIndex()
		{
			foreach(Sys_ItemEquip p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_ItemEquip info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_ItemEquip();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_ItemEquip


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

		private static void _makeIndex()
		{
			foreach(Sys_ItemConsume p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_ItemConsume info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_ItemConsume();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_ItemConsume


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

		private static void _makeIndex()
		{
			foreach(Sys_ItemStuff p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_ItemStuff info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_ItemStuff();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_ItemStuff


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_MainItemAbility
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_MainItemAbility>		m_List = new List<Sys_MainItemAbility> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_MainItemAbility >>>");
			foreach (Sys_MainItemAbility p in CSV_Sys_MainItemAbility.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_MainItemAbility       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_MainItemAbility FindBy_name(string key){return (Sys_MainItemAbility)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_MainItemAbility p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_MainItemAbility info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_MainItemAbility();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_MainItemAbility


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_Package
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Package>		m_List = new List<Sys_Package> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Package >>>");
			foreach (Sys_Package p in CSV_Sys_Package.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Package       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_Package FindBy_name(string key){return (Sys_Package)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_Package p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_Package info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_Package();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_Package


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_Shop
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Shop>		m_List = new List<Sys_Shop> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Shop >>>");
			foreach (Sys_Shop p in CSV_Sys_Shop.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Shop       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_Shop FindBy_name(string key){return (Sys_Shop)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_Shop p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_Shop info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_Shop();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_Shop


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_SubItemAbility
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_SubItemAbility>		m_List = new List<Sys_SubItemAbility> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_SubItemAbility >>>");
			foreach (Sys_SubItemAbility p in CSV_Sys_SubItemAbility.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_SubItemAbility       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static void _makeIndex()
		{
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
				Sys_SubItemAbility info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_SubItemAbility();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_SubItemAbility



	


}//namespace nEXCEL
