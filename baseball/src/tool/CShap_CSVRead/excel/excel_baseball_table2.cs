/*------------------------------------------------------------


command line : 
Excel_Converter.exe D:\svn\baseball\doc\design\excel\code\excel_baseball_table2.txt D:\svn\baseball\doc\design\excel\code\excel_enum.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_string_table.txt 

-------------------------------------------------------------*/


using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
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
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_BreakingBallUpgrade
	{
		public Sys_BreakingBallState_id_t m_id; 	// [id] id 
		public string m_name; 	// [name] name 
		public EPlayerBreakingBall m_breakingball_name; 	// [변화구명] 변화구 이름 
		public EPlayerBreakingBall m_breakingball_result; 	// [업그레이드 필요 변화구] 업그레이드 필요 변화구 
		public Int16 m_breaking_need_level; 	// [업그레이드 필요 레벨] 업그레이드 필요 레벨 
		public EBreakingBallPitch m_breaking_pitch; 	// [변화구 구질]  
		public EBreakingBallRotation m_ball_rotation; 	// [볼 회전 방향]  
		public DATETIME m_breaking_open_date; 	// [적용 일시] 변화구 적용 일자 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_BreakingBallUpgrade::id",token[idx++], ref m_id);
			nUtil.jString_string.Parse("Sys_BreakingBallUpgrade::name",token[idx++], ref m_name);
			nUtil.jString_EPlayerBreakingBall.Parse("Sys_BreakingBallUpgrade::breakingball_name",token[idx++], ref m_breakingball_name);
			nUtil.jString_EPlayerBreakingBall.Parse("Sys_BreakingBallUpgrade::breakingball_result",token[idx++], ref m_breakingball_result);
			nUtil.jString_Int16.Parse("Sys_BreakingBallUpgrade::breaking_need_level",token[idx++], ref m_breaking_need_level);
			nUtil.jString_EBreakingBallPitch.Parse("Sys_BreakingBallUpgrade::breaking_pitch",token[idx++], ref m_breaking_pitch);
			nUtil.jString_EBreakingBallRotation.Parse("Sys_BreakingBallUpgrade::ball_rotation",token[idx++], ref m_ball_rotation);
			nUtil.jString_DATETIME.Parse("Sys_BreakingBallUpgrade::breaking_open_date",token[idx++], ref m_breaking_open_date);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_id.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_breakingball_name.ToString() + ",";
			output += m_breakingball_result.ToString() + ",";
			output += m_breaking_need_level.ToString() + ",";
			output += m_breaking_pitch.ToString() + ",";
			output += m_ball_rotation.ToString() + ",";
			output += m_breaking_open_date.ToString() + ",";
			return output;
		}
	}//class Sys_BreakingBallUpgrade

	namespace nUtil
	{
		class jString_Sys_BreakingBallUpgrade
		{
			public static string ToString(Sys_BreakingBallUpgrade o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_BreakingBallUpgrade> sysList)
			{
				string output = "";
				foreach (Sys_BreakingBallUpgrade o in sysList)
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
				Sys_BreakingBallUpgrade o = (Sys_BreakingBallUpgrade)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_BreakingBallUpgrade o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_BreakingBallUpgrade.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_BreakingBallUpgrade.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_BreakingBallUpgrade> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_BreakingBallUpgrade> sysList = (List<Sys_BreakingBallUpgrade>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_BreakingBallUpgrade o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_BreakingBallUpgrade.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_BreakingBallUpgrade.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_BreakingBallUpgrade
	}//namespace nUtil
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_BreakingBallUpgrade
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_BreakingBallUpgrade>		m_List = new List<Sys_BreakingBallUpgrade> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_BreakingBallUpgrade >>>");
			foreach (Sys_BreakingBallUpgrade p in CSV_Sys_BreakingBallUpgrade.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_BreakingBallUpgrade       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_BreakingBallUpgrade FindBy_name(string key){return (Sys_BreakingBallUpgrade)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_BreakingBallUpgrade p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_BreakingBallUpgrade info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_BreakingBallUpgrade();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_BreakingBallUpgrade



	


}//namespace nEXCEL
