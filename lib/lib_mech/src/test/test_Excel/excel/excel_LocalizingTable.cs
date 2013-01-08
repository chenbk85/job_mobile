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

	public enum ETextCategory
	{
		eBEGIN_ETextCategory=0,
		ETC_Tutorial = 1, // [튜토리얼설명] 튜토리얼설명
		ETC_Quest = 2, // [퀘스트설명] 퀘스트설명
		ETC_Npc = 3, // [npc대화] npc대화
		ETC_LoadScreen = 4, // [로딩화면 설명] 로딩화면 설명
		ETC_Menu = 5, // [게임 메뉴 설명] 게임 메뉴 설명
		eEND_ETextCategory,
	}
	namespace nUtil
	{
		class jString_ETextCategory
		{
			public static void Parse(string sDebug,string sVal, ref ETextCategory eVal) 
			{
				eVal = (ETextCategory)Enum.Parse(typeof(ETextCategory), sVal);
			}
		}
	}

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_LocalizingText
	{
		public UInt16 m_id; 	// [아이디] id 
		public ETextCategory m_category; 	// [카테고리] asfd 
		public string m_name; 	// [영문명] 영문명 
		public string m_name_kor; 	// [한글명] 한글명 
		public string m_name_loc; 	// [로컬라이징명] 로컬라이징명 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_LocalizingText::id",token[idx++], ref m_id);
			nUtil.jString_ETextCategory.Parse("Sys_LocalizingText::category",token[idx++], ref m_category);
			nUtil.jString_string.Parse("Sys_LocalizingText::name",token[idx++], ref m_name);
			nUtil.jString_string.Parse("Sys_LocalizingText::name_kor",token[idx++], ref m_name_kor);
			nUtil.jString_string.Parse("Sys_LocalizingText::name_loc",token[idx++], ref m_name_loc);
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
			output += m_category.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_name_kor.ToString() + ",";
			output += m_name_loc.ToString() + ",";
			return output;
		}
	}//class Sys_LocalizingText

	namespace nUtil
	{
		class jString_Sys_LocalizingText
		{
			public static string ToString(Sys_LocalizingText o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_LocalizingText> sysList)
			{
				string output = "";
				foreach (Sys_LocalizingText o in sysList)
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
				Sys_LocalizingText o = (Sys_LocalizingText)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_LocalizingText o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_LocalizingText.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_LocalizingText.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_LocalizingText> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_LocalizingText> sysList = (List<Sys_LocalizingText>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_LocalizingText o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_LocalizingText.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_LocalizingText.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_LocalizingText
	}//namespace nUtil
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_LocalizingWord
	{
		public UInt16 m_id; 	// [아이디] id 
		public string m_name; 	// [영문명] 영문명 
		public string m_name_kor; 	// [한글명] 한글명 
		public string m_name_loc; 	// [로컬라이징명] 로컬라이징명 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_LocalizingWord::id",token[idx++], ref m_id);
			nUtil.jString_string.Parse("Sys_LocalizingWord::name",token[idx++], ref m_name);
			nUtil.jString_string.Parse("Sys_LocalizingWord::name_kor",token[idx++], ref m_name_kor);
			nUtil.jString_string.Parse("Sys_LocalizingWord::name_loc",token[idx++], ref m_name_loc);
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
			output += m_name_kor.ToString() + ",";
			output += m_name_loc.ToString() + ",";
			return output;
		}
	}//class Sys_LocalizingWord

	namespace nUtil
	{
		class jString_Sys_LocalizingWord
		{
			public static string ToString(Sys_LocalizingWord o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_LocalizingWord> sysList)
			{
				string output = "";
				foreach (Sys_LocalizingWord o in sysList)
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
				Sys_LocalizingWord o = (Sys_LocalizingWord)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_LocalizingWord o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_LocalizingWord.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_LocalizingWord.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_LocalizingWord> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_LocalizingWord> sysList = (List<Sys_LocalizingWord>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_LocalizingWord o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_LocalizingWord.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_LocalizingWord.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_LocalizingWord
	}//namespace nUtil
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_LocalizingText
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_LocalizingText>		m_List = new List<Sys_LocalizingText> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_LocalizingText >>>");
			foreach (Sys_LocalizingText p in CSV_Sys_LocalizingText.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_LocalizingText       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_LocalizingText FindBy_name(string key){return (Sys_LocalizingText)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_LocalizingText p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_LocalizingText info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_LocalizingText();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_LocalizingText


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_LocalizingWord
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_LocalizingWord>		m_List = new List<Sys_LocalizingWord> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_LocalizingWord >>>");
			foreach (Sys_LocalizingWord p in CSV_Sys_LocalizingWord.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_LocalizingWord       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_LocalizingWord FindBy_name(string key){return (Sys_LocalizingWord)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_LocalizingWord p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_LocalizingWord info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_LocalizingWord();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_LocalizingWord



	


}//namespace nEXCEL
