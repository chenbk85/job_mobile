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
	// enum형 코드 템플릿 정의
	// -------------------------------------------------

	public enum ERunnerStateRound : byte
	{
		eBEGIN_ERunnerStateRound=0,
		ERSR_0 = 0, // [주자 없음] 주자 없음
		ERSR_1 = 1, // [주자 1루] 주자 1루
		ERSR_2 = 2, // [주자 2루] 주자 2루
		ERSR_12 = 3, // [주자 1루 2루] 주자 1루 2루
		ERSR_3 = 4, // [주자 3루] 주자 3루
		ERSR_13 = 5, // [주자 1루 3루] 주자 1루 3루
		ERSR_23 = 6, // [주자 2루 3루] 주자 2루 3루
		ERSR_123 = 7, // [주자 1루 2루 3루] 주자 1루 2루 3루
		eEND_ERunnerStateRound,
	}
	namespace nUtil
	{
		public class jString_ERunnerStateRound
		{
			public static void Parse(string sDebug,string sVal, ref ERunnerStateRound eVal) 
			{
				eVal = (ERunnerStateRound)Enum.Parse(typeof(ERunnerStateRound), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (ERunnerStateRound i = ERunnerStateRound.eBEGIN_ERunnerStateRound +1;i < ERunnerStateRound.eEND_ERunnerStateRound; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<ERunnerStateRound> get_enums() 
			{
				List<ERunnerStateRound> list = new List<ERunnerStateRound>();
				for (ERunnerStateRound i = ERunnerStateRound.eBEGIN_ERunnerStateRound +1;i < ERunnerStateRound.eEND_ERunnerStateRound; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum ERunnerStateType : byte
	{
		eBEGIN_ERunnerStateType=0,
		ERST_A = 1, // [A형] 5라운드와 9라운드 만루 상황
		ERST_B = 2, // [B형] 3라운드와 6라운드 9라운드 만루 상황
		ERST_C = 3, // [C형] 4라운드와 7라운드 9라운드 만루 상황
		eEND_ERunnerStateType,
	}
	namespace nUtil
	{
		public class jString_ERunnerStateType
		{
			public static void Parse(string sDebug,string sVal, ref ERunnerStateType eVal) 
			{
				eVal = (ERunnerStateType)Enum.Parse(typeof(ERunnerStateType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (ERunnerStateType i = ERunnerStateType.eBEGIN_ERunnerStateType +1;i < ERunnerStateType.eEND_ERunnerStateType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<ERunnerStateType> get_enums() 
			{
				List<ERunnerStateType> list = new List<ERunnerStateType>();
				for (ERunnerStateType i = ERunnerStateType.eBEGIN_ERunnerStateType +1;i < ERunnerStateType.eEND_ERunnerStateType; i++){list.Add(i);}
				return list;
			}
		}
	}

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_Runner_State
	{
		public Sys_Runner_State_id_t m_index; 	// [index] 영문닉네임 , 각종테이블에서 사용 
		public ERunnerStateType m_category; 	// [주자배치 타입] 주자배치 타입 
		public ERunnerStateRound m_state_1r; 	// [1라운드 주자 상황] 1라운드 주자 상황 
		public ERunnerStateRound m_state_2r; 	// [2라운드 주자 상황] 2라운드 주자 상황 
		public ERunnerStateRound m_state_3r; 	// [3라운드 주자 상황] 3라운드 주자 상황 
		public ERunnerStateRound m_state_4r; 	// [4라운드 주자 상황] 4라운드 주자 상황 
		public ERunnerStateRound m_state_5r; 	// [5라운드 주자 상황] 5라운드 주자 상황 
		public ERunnerStateRound m_state_6r; 	// [6라운드 주자 상황] 6라운드 주자 상황 
		public ERunnerStateRound m_state_7r; 	// [7라운드 주자 상황] 7라운드 주자 상황 
		public ERunnerStateRound m_state_8r; 	// [8라운드 주자 상황] 8라운드 주자 상황 
		public ERunnerStateRound m_state_9r; 	// [9라운드 주자 상황] 9라운드 주자 상황 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_UInt16.Parse("Sys_Runner_State::index",token[idx++], ref m_index);
				nUtil.jString_ERunnerStateType.Parse("Sys_Runner_State::category",token[idx++], ref m_category);
				nUtil.jString_ERunnerStateRound.Parse("Sys_Runner_State::state_1r",token[idx++], ref m_state_1r);
				nUtil.jString_ERunnerStateRound.Parse("Sys_Runner_State::state_2r",token[idx++], ref m_state_2r);
				nUtil.jString_ERunnerStateRound.Parse("Sys_Runner_State::state_3r",token[idx++], ref m_state_3r);
				nUtil.jString_ERunnerStateRound.Parse("Sys_Runner_State::state_4r",token[idx++], ref m_state_4r);
				nUtil.jString_ERunnerStateRound.Parse("Sys_Runner_State::state_5r",token[idx++], ref m_state_5r);
				nUtil.jString_ERunnerStateRound.Parse("Sys_Runner_State::state_6r",token[idx++], ref m_state_6r);
				nUtil.jString_ERunnerStateRound.Parse("Sys_Runner_State::state_7r",token[idx++], ref m_state_7r);
				nUtil.jString_ERunnerStateRound.Parse("Sys_Runner_State::state_8r",token[idx++], ref m_state_8r);
				nUtil.jString_ERunnerStateRound.Parse("Sys_Runner_State::state_9r",token[idx++], ref m_state_9r);
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
			output += m_state_1r.ToString() + ",";
			output += m_state_2r.ToString() + ",";
			output += m_state_3r.ToString() + ",";
			output += m_state_4r.ToString() + ",";
			output += m_state_5r.ToString() + ",";
			output += m_state_6r.ToString() + ",";
			output += m_state_7r.ToString() + ",";
			output += m_state_8r.ToString() + ",";
			output += m_state_9r.ToString() + ",";
			return output;
		}
	}//class Sys_Runner_State

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_Runner_State
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Runner_State>		m_List = new List<Sys_Runner_State> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Runner_State >>>");
			foreach (Sys_Runner_State p in CSV_Sys_Runner_State.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Runner_State       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Dictionary<ERunnerStateType,List<Sys_Runner_State>> m_Dictionary_category = new Dictionary<ERunnerStateType,List<Sys_Runner_State>>{};
		public static List<Sys_Runner_State> FindBy_category(ERunnerStateType key){return m_Dictionary_category[key];}

		private static void _makeIndex()
		{
			foreach(Sys_Runner_State p in m_List)
			{
				if (!m_Dictionary_category.ContainsKey(p.m_category))
				{
					m_Dictionary_category[p.m_category] = new List<Sys_Runner_State> { };
				}
				m_Dictionary_category[p.m_category].Add(p);
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
					Sys_Runner_State info = new Sys_Runner_State();
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
				Sys_Runner_State info = new Sys_Runner_State();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_Runner_State



	


}//namespace nEXCEL
