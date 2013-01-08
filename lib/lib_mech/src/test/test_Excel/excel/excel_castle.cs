/*------------------------------------------------------------


command line : 
Excel_Converter.exe D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_baseball_table_db.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_enum.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_LocalizingTable.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_ClientResult.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_ServerResult.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_force.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_test.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_test2.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_user.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_world.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_hero.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_castle.txt 

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
	// enum형 코드 템플릿 정의
	// -------------------------------------------------

	public enum Evillage_Condition
	{
		eBEGIN_Evillage_Condition=0,
		EVC_Normal = 1, // [일반] 보통 상태
		EVC_OCCUPY = 2, // [점령중] 점령중인 상태
		EVC_INACTIVE = 3, // [장기비접속] 장기비적속유저
		EVC_ONLINE = 4, // [온라인] 온라인 유저
		EVC_OFFLINE = 5, // [오프라인] 오프라인 유저
		eEND_Evillage_Condition,
	}
	namespace nUtil
	{
		class jString_Evillage_Condition
		{
			public static void Parse(string sDebug,string sVal, ref Evillage_Condition eVal) 
			{
				eVal = (Evillage_Condition)Enum.Parse(typeof(Evillage_Condition), sVal);
			}
		}
	}

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_Castle
	{
		public UInt16 m_csid; 	// [숫자_ID]  
		public string m_name; 	// [이름_ID] 월드랑 연동 
		public string m_name_kor; 	// [성_이름]  
		public Sys_Hero_id_t m_default_gsid; 	// [기본_태수] 제너럴 sid 입력 
		public string m_force_gen_name; 	// [부대생성규칙이름] bin/server/xml/NpcCastle.xml 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_Castle::csid",token[idx++], ref m_csid);
			nUtil.jString_string.Parse("Sys_Castle::name",token[idx++], ref m_name);
			nUtil.jString_string.Parse("Sys_Castle::name_kor",token[idx++], ref m_name_kor);
			nUtil.jString_UInt16.Parse("Sys_Castle::default_gsid",token[idx++], ref m_default_gsid);
			nUtil.jString_string.Parse("Sys_Castle::force_gen_name",token[idx++], ref m_force_gen_name);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_csid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_name_kor.ToString() + ",";
			output += m_default_gsid.ToString() + ",";
			output += m_force_gen_name.ToString() + ",";
			return output;
		}
	}//class Sys_Castle

	namespace nUtil
	{
		class jString_Sys_Castle
		{
			public static string ToString(Sys_Castle o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_Castle> sysList)
			{
				string output = "";
				foreach (Sys_Castle o in sysList)
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
				Sys_Castle o = (Sys_Castle)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_Castle o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_Castle.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_Castle.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_Castle> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_Castle> sysList = (List<Sys_Castle>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_Castle o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_Castle.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_Castle.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_Castle
	}//namespace nUtil
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_CastlePos
	{
		public Sys_Castle_id_t m_cpsid; 	// [성 sid]  
		public UInt16 m_x; 	// [x]  
		public UInt16 m_y; 	// [y]  
		public string m_castle_map; 	// [castle_map파일] 성지역의 마을 배치정보파일 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_CastlePos::cpsid",token[idx++], ref m_cpsid);
			nUtil.jString_UInt16.Parse("Sys_CastlePos::x",token[idx++], ref m_x);
			nUtil.jString_UInt16.Parse("Sys_CastlePos::y",token[idx++], ref m_y);
			nUtil.jString_string.Parse("Sys_CastlePos::castle_map",token[idx++], ref m_castle_map);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_cpsid.ToString() + ",";
			output += m_x.ToString() + ",";
			output += m_y.ToString() + ",";
			output += m_castle_map.ToString() + ",";
			return output;
		}
	}//class Sys_CastlePos

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_TownPos
	{
		public Sys_TownPos_id_t m_tpsid; 	// [숫자_ID]  
		public UInt16 m_x; 	// [x]  
		public UInt16 m_y; 	// [y]  
		public string m_town_map_type; 	// [타운맵파일명] 건물슬롯배치정보가 포함된 타운맵파일명 
		public UInt16 m_object_id; 	// [오브젝트 ID] 오브젝트 정보 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_TownPos::tpsid",token[idx++], ref m_tpsid);
			nUtil.jString_UInt16.Parse("Sys_TownPos::x",token[idx++], ref m_x);
			nUtil.jString_UInt16.Parse("Sys_TownPos::y",token[idx++], ref m_y);
			nUtil.jString_string.Parse("Sys_TownPos::town_map_type",token[idx++], ref m_town_map_type);
			nUtil.jString_UInt16.Parse("Sys_TownPos::object_id",token[idx++], ref m_object_id);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_tpsid.ToString() + ",";
			output += m_x.ToString() + ",";
			output += m_y.ToString() + ",";
			output += m_town_map_type.ToString() + ",";
			output += m_object_id.ToString() + ",";
			return output;
		}
	}//class Sys_TownPos

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_Castle
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Castle>		m_List = new List<Sys_Castle> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Castle >>>");
			foreach (Sys_Castle p in CSV_Sys_Castle.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Castle       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_Castle FindBy_name(string key){return (Sys_Castle)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_Castle p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_Castle info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_Castle();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_Castle


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_CastlePos
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_CastlePos>		m_List = new List<Sys_CastlePos> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_CastlePos >>>");
			foreach (Sys_CastlePos p in CSV_Sys_CastlePos.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_CastlePos       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
				Sys_CastlePos info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_CastlePos();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_CastlePos


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_TownPos
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_TownPos>		m_List = new List<Sys_TownPos> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_TownPos >>>");
			foreach (Sys_TownPos p in CSV_Sys_TownPos.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_TownPos       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
				Sys_TownPos info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_TownPos();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_TownPos



	


}//namespace nEXCEL
