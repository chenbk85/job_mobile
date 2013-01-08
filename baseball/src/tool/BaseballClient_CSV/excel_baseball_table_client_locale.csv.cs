/*------------------------------------------------------------


command line : 
Excel_Converter.exe D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client_locale.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client_locale.txt D:\svn\baseball\doc\design\excel\code\excel_enum.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_db.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_item.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_string_table.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_etc.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_animation.txt 

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
	

	// -------------------------------------------------
	// 대화용 스트링테이블
	// -------------------------------------------------

	public class Sys_Dialog_Usa
	{
		public Int16 m_index; 	// [index] 영문닉네임 , 각종테이블에서 사용 
		public ENpcString m_npc; 	// [npc] 말하는 npc종류 
		public string m_image_type; 	// [npc그림종류]  
		public ENpcSituationString m_situation; 	// [상황] 대화 상황 종류 
		public string m_text; 	// [text] 출력되는 영문 대화 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_Int16.Parse("Sys_Dialog_Usa::index",token[idx++], ref m_index);
				nUtil.jString_ENpcString.Parse("Sys_Dialog_Usa::npc",token[idx++], ref m_npc);
				nUtil.jString_string.Parse("Sys_Dialog_Usa::image_type",token[idx++], ref m_image_type);
				nUtil.jString_ENpcSituationString.Parse("Sys_Dialog_Usa::situation",token[idx++], ref m_situation);
				nUtil.jString_string.Parse("Sys_Dialog_Usa::text",token[idx++], ref m_text);
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
			output += m_index.ToString() + ",";
			output += m_npc.ToString() + ",";
			output += m_image_type.ToString() + ",";
			output += m_situation.ToString() + ",";
			output += m_text.ToString() + ",";
			return output;
		}
	}//class Sys_Dialog_Usa

	

	// -------------------------------------------------
	// 스트링테이블
	// -------------------------------------------------

	public class Sys_String_Usa
	{
		public Int16 m_index; 	// [index] 영문닉네임 , 각종테이블에서 사용 
		public ECategoryString m_category; 	// [category]  
		public string m_name; 	// [name] 영문닉네임 , 각종테이블에서 사용 
		public string m_text1; 	// [text1] 출력되는 영문명 
		public string m_text2; 	// [text2] 출력되는 영문명의 설명 a 
		public string m_text3; 	// [text3] 출력되는 영문명의 설명 b 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_Int16.Parse("Sys_String_Usa::index",token[idx++], ref m_index);
				nUtil.jString_ECategoryString.Parse("Sys_String_Usa::category",token[idx++], ref m_category);
				nUtil.jString_string.Parse("Sys_String_Usa::name",token[idx++], ref m_name);
				nUtil.jString_string.Parse("Sys_String_Usa::text1",token[idx++], ref m_text1);
				nUtil.jString_string.Parse("Sys_String_Usa::text2",token[idx++], ref m_text2);
				nUtil.jString_string.Parse("Sys_String_Usa::text3",token[idx++], ref m_text3);
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
			output += m_index.ToString() + ",";
			output += m_category.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_text1.ToString() + ",";
			output += m_text2.ToString() + ",";
			output += m_text3.ToString() + ",";
			return output;
		}
	}//class Sys_String_Usa

	namespace nUtil
	{
		class jString_Sys_String_Usa
		{
			public static string ToString(Sys_String_Usa o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_String_Usa> sysList)
			{
				string output = "";
				foreach (Sys_String_Usa o in sysList)
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
				Sys_String_Usa o = (Sys_String_Usa)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_String_Usa o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_String_Usa.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_String_Usa.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_String_Usa> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_String_Usa> sysList = (List<Sys_String_Usa>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_String_Usa o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_String_Usa.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_String_Usa.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_String_Usa
	}//namespace nUtil
	

	// -------------------------------------------------
	// 대화용 스트링테이블 한글
	// -------------------------------------------------

	public class Sys_Dialog_Kor
	{
		public Int16 m_index; 	// [index] 영문닉네임 , 각종테이블에서 사용 
		public ENpcString m_npc; 	// [npc] 말하는 npc종류 
		public string m_image_type; 	// [npc그림종류]  
		public ENpcSituationString m_situation; 	// [상황] 대화 상황 종류 
		public string m_text; 	// [text] 출력되는 한글명 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_Int16.Parse("Sys_Dialog_Kor::index",token[idx++], ref m_index);
				nUtil.jString_ENpcString.Parse("Sys_Dialog_Kor::npc",token[idx++], ref m_npc);
				nUtil.jString_string.Parse("Sys_Dialog_Kor::image_type",token[idx++], ref m_image_type);
				nUtil.jString_ENpcSituationString.Parse("Sys_Dialog_Kor::situation",token[idx++], ref m_situation);
				nUtil.jString_string.Parse("Sys_Dialog_Kor::text",token[idx++], ref m_text);
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
			output += m_index.ToString() + ",";
			output += m_npc.ToString() + ",";
			output += m_image_type.ToString() + ",";
			output += m_situation.ToString() + ",";
			output += m_text.ToString() + ",";
			return output;
		}
	}//class Sys_Dialog_Kor

	

	// -------------------------------------------------
	// 스트링테이블 한글
	// -------------------------------------------------

	public class Sys_String_Kor
	{
		public Int16 m_index; 	// [index] 영문닉네임 , 각종테이블에서 사용 
		public ECategoryString m_category; 	// [category]  
		public string m_name; 	// [name] 영문닉네임 , 각종테이블에서 사용 
		public string m_text1; 	// [text1] 출력되는 한글명 
		public string m_text2; 	// [text2] 출력되는 한글명의 설명 a 
		public string m_text3; 	// [text3] 출력되는 한글명의 설명 b 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_Int16.Parse("Sys_String_Kor::index",token[idx++], ref m_index);
				nUtil.jString_ECategoryString.Parse("Sys_String_Kor::category",token[idx++], ref m_category);
				nUtil.jString_string.Parse("Sys_String_Kor::name",token[idx++], ref m_name);
				nUtil.jString_string.Parse("Sys_String_Kor::text1",token[idx++], ref m_text1);
				nUtil.jString_string.Parse("Sys_String_Kor::text2",token[idx++], ref m_text2);
				nUtil.jString_string.Parse("Sys_String_Kor::text3",token[idx++], ref m_text3);
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
			output += m_index.ToString() + ",";
			output += m_category.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_text1.ToString() + ",";
			output += m_text2.ToString() + ",";
			output += m_text3.ToString() + ",";
			return output;
		}
	}//class Sys_String_Kor

	namespace nUtil
	{
		class jString_Sys_String_Kor
		{
			public static string ToString(Sys_String_Kor o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_String_Kor> sysList)
			{
				string output = "";
				foreach (Sys_String_Kor o in sysList)
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
				Sys_String_Kor o = (Sys_String_Kor)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_String_Kor o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_String_Kor.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_String_Kor.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_String_Kor> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_String_Kor> sysList = (List<Sys_String_Kor>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_String_Kor o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_String_Kor.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_String_Kor.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_String_Kor
	}//namespace nUtil
	

	// -------------------------------------------------
	// 대화용 스트링테이블
	// -------------------------------------------------

	public class CSV_Sys_Dialog_Usa
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Dialog_Usa>		m_List = new List<Sys_Dialog_Usa> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Dialog_Usa >>>");
			foreach (Sys_Dialog_Usa p in CSV_Sys_Dialog_Usa.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Dialog_Usa       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Dictionary<ENpcSituationString,List<Sys_Dialog_Usa>> m_Dictionary_situation = new Dictionary<ENpcSituationString,List<Sys_Dialog_Usa>>{};
		public static List<Sys_Dialog_Usa> FindBy_situation(ENpcSituationString key){return m_Dictionary_situation[key];}

		private static void _makeIndex()
		{
			foreach(Sys_Dialog_Usa p in m_List)
			{
				if (!m_Dictionary_situation.ContainsKey(p.m_situation))
				{
					m_Dictionary_situation[p.m_situation] = new List<Sys_Dialog_Usa> { };
				}
				m_Dictionary_situation[p.m_situation].Add(p);
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
					Sys_Dialog_Usa info = new Sys_Dialog_Usa();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
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
				Sys_Dialog_Usa info = new Sys_Dialog_Usa();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_Dialog_Usa


	// -------------------------------------------------
	// 스트링테이블
	// -------------------------------------------------

	public class CSV_Sys_String_Usa
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_String_Usa>		m_List = new List<Sys_String_Usa> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_String_Usa >>>");
			foreach (Sys_String_Usa p in CSV_Sys_String_Usa.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_String_Usa       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_String_Usa FindBy_name(string key){return (Sys_String_Usa)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_String_Usa p in m_List){m_Hashtable_name[p.m_name] = p;}
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
					Sys_String_Usa info = new Sys_String_Usa();
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
				Sys_String_Usa info = new Sys_String_Usa();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
			_makeIndex();
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_String_Usa


	// -------------------------------------------------
	// 대화용 스트링테이블 한글
	// -------------------------------------------------

	public class CSV_Sys_Dialog_Kor
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Dialog_Kor>		m_List = new List<Sys_Dialog_Kor> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Dialog_Kor >>>");
			foreach (Sys_Dialog_Kor p in CSV_Sys_Dialog_Kor.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Dialog_Kor       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Dictionary<ENpcSituationString,List<Sys_Dialog_Kor>> m_Dictionary_situation = new Dictionary<ENpcSituationString,List<Sys_Dialog_Kor>>{};
		public static List<Sys_Dialog_Kor> FindBy_situation(ENpcSituationString key){return m_Dictionary_situation[key];}

		private static void _makeIndex()
		{
			foreach(Sys_Dialog_Kor p in m_List)
			{
				if (!m_Dictionary_situation.ContainsKey(p.m_situation))
				{
					m_Dictionary_situation[p.m_situation] = new List<Sys_Dialog_Kor> { };
				}
				m_Dictionary_situation[p.m_situation].Add(p);
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
					Sys_Dialog_Kor info = new Sys_Dialog_Kor();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
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
				Sys_Dialog_Kor info = new Sys_Dialog_Kor();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_Dialog_Kor


	// -------------------------------------------------
	// 스트링테이블 한글
	// -------------------------------------------------

	public class CSV_Sys_String_Kor
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_String_Kor>		m_List = new List<Sys_String_Kor> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_String_Kor >>>");
			foreach (Sys_String_Kor p in CSV_Sys_String_Kor.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_String_Kor       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_String_Kor FindBy_name(string key){return (Sys_String_Kor)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_String_Kor p in m_List){m_Hashtable_name[p.m_name] = p;}
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
					Sys_String_Kor info = new Sys_String_Kor();
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
				Sys_String_Kor info = new Sys_String_Kor();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
			_makeIndex();
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_String_Kor



	


}//namespace nEXCEL
