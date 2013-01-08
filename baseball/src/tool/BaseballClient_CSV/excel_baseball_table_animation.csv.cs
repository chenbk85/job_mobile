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

	public enum EBatterAnimationType : byte
	{
		eBEGIN_EBatterAnimationType=0,
		EBAT_STARTUP = 1, // [Startup] 배터박스에서 한손으로 투수에게 양해를 구하고, 발로 땅을 고르며 타격 자세 잡기
		EBAT_MAXAFTER = 2, // [Max After] 각각의 스탠스에서 배트커서 맥시멈 당겼다가 평타 아이들로 복귀
		EBAT_MAX = 3, // [Max] 각각의 스탠스에서 배트커서 맥시멈 당겼을 때 아이들
		EBAT_IDLE = 4, // [Idle] 각각의 스탠스에서 방망이를 1자로 세우고 약간 흔드는 자세
		EBAT_READY = 5, // [Ready] 각각의 스탠스에서 타격준비
		EBAT_SWING_LEFT = 6, // [왼쪽 스윙] 각각의 스탠스에서 왼쪽 스윙 (투수를 바라보는 시점에서) (1_하단 2_중하단 3_중단 4_중상단 5_상단)
		EBAT_SWING_MIDDLE = 7, // [중간 스윙] 각각의 스탠스에서 중간 스윙 (투수를 바라보는 시점에서) (1_하단 2_중하단 3_중단 4_중상단 5_상단)
		EBAT_SWING_RIGHT = 8, // [오른쪽 스윙] 각각의 스탠스에서 오른쪽 스윙 (투수를 바라보는 시점에서) (1_하단 2_중하단 3_중단 4_중상단 5_상단)
		EBAT_MAUVAIS = 9, // [헛스윙] 각각의 스탠스에서 헛스윙
		EBAT_WINLOSE = 10, // [게임결과창에서 이기거나 졌을 때] 게임결과창에서 이기거나 졌을 때
		EBAT_MENUUI = 11, // [MENU UI에서 포즈] MENU UI에서 포즈
		eEND_EBatterAnimationType,
	}
	namespace nUtil
	{
		public class jString_EBatterAnimationType
		{
			public static void Parse(string sDebug,string sVal, ref EBatterAnimationType eVal) 
			{
				eVal = (EBatterAnimationType)Enum.Parse(typeof(EBatterAnimationType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EBatterAnimationType i = EBatterAnimationType.eBEGIN_EBatterAnimationType +1;i < EBatterAnimationType.eEND_EBatterAnimationType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EBatterAnimationType> get_enums() 
			{
				List<EBatterAnimationType> list = new List<EBatterAnimationType>();
				for (EBatterAnimationType i = EBatterAnimationType.eBEGIN_EBatterAnimationType +1;i < EBatterAnimationType.eEND_EBatterAnimationType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum ECatcherAnimationType : byte
	{
		eBEGIN_ECatcherAnimationType=0,
		ECAT_STARTUP_IDLE = 1, // [Startup] 투수 던지기 전 포수 아이들
		ECAT_MITCATCH = 2, // [미트 볼 캐치] 포수와 미트 모두 해당 위치 이동 상태에서 볼 캐치 동작 (1=하하단 2=하중단 3=하상단 4=중하단 5=중중단 6=중상단 7=상하단 8=상중단 9=상상단 10=최상하단 11=최상중단 12=최상상단)
		ECAT_MOVE_MIDDLE = 3, // [포수 중단 이동] 포수 전체 중단 이동
		ECAT_MOVE_LEFT = 4, // [포수 왼쪽 이동] 포수 전체 왼쪽 이동
		ECAT_MOVE_RIGHT = 5, // [포수 오른쪽 이동] 포수 전체 오른쪽 이동
		ECAT_BACK_MIDDLE = 6, // [포수 중단 이동 후 돌아오기] 포수 중단 이동 후 돌아오기
		ECAT_BACK_LEFT = 7, // [포수 왼쪽 이동 후 돌아오기] 포수 왼쪽 이동 후 돌아오기
		ECAT_BACK_RIGHT = 8, // [포수 오른쪽 이동 후 돌아오기] 포수 오른쪽 이동 후 돌아오기
		eEND_ECatcherAnimationType,
	}
	namespace nUtil
	{
		public class jString_ECatcherAnimationType
		{
			public static void Parse(string sDebug,string sVal, ref ECatcherAnimationType eVal) 
			{
				eVal = (ECatcherAnimationType)Enum.Parse(typeof(ECatcherAnimationType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (ECatcherAnimationType i = ECatcherAnimationType.eBEGIN_ECatcherAnimationType +1;i < ECatcherAnimationType.eEND_ECatcherAnimationType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<ECatcherAnimationType> get_enums() 
			{
				List<ECatcherAnimationType> list = new List<ECatcherAnimationType>();
				for (ECatcherAnimationType i = ECatcherAnimationType.eBEGIN_ECatcherAnimationType +1;i < ECatcherAnimationType.eEND_ECatcherAnimationType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EEumpireAnimationType : byte
	{
		eBEGIN_EEumpireAnimationType=0,
		EEAT_PLAYBALL = 1, // [경기 시작] 경기 시작
		EEAT_IDLE = 2, // [대기 관전 아이들] 대기 관전 아이들
		EEAT_DECISION_PERFECT = 3, // [퍼펙트 판정] 퍼펙트 판정
		EEAT_DECISION_GOOD = 4, // [굳 판정] 굳 판정
		EEAT_DECISION_NORMAL = 5, // [노멀 판정] 노멀 판정
		EEAT_DECISION_BAD = 6, // [배드 판정] 배드 판정
		eEND_EEumpireAnimationType,
	}
	namespace nUtil
	{
		public class jString_EEumpireAnimationType
		{
			public static void Parse(string sDebug,string sVal, ref EEumpireAnimationType eVal) 
			{
				eVal = (EEumpireAnimationType)Enum.Parse(typeof(EEumpireAnimationType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EEumpireAnimationType i = EEumpireAnimationType.eBEGIN_EEumpireAnimationType +1;i < EEumpireAnimationType.eEND_EEumpireAnimationType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EEumpireAnimationType> get_enums() 
			{
				List<EEumpireAnimationType> list = new List<EEumpireAnimationType>();
				for (EEumpireAnimationType i = EEumpireAnimationType.eBEGIN_EEumpireAnimationType +1;i < EEumpireAnimationType.eEND_EEumpireAnimationType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EPitcherAnimationType : byte
	{
		eBEGIN_EPitcherAnimationType=0,
		EPAT_STARTUP_IDL = 1, // [대기 아이들 1] 대기 동작중 숨쉬는 아이들
		EPAT_HIT_AFTER = 2, // [투수 히트 후 고개 동작(좌 우)] 투수 히트 후 고개 동작(좌=1 우=2)
		EPAT_YES = 3, // [투수 사인 수락] 대기 동작 마무리 고개 끄덕
		EPAT_NO = 4, // [투수 사인 거부] 대기 동작 중 고개 절래절래
		EPAT_STARTUP = 5, // [Startup] 송진을 만진 후 마운드 자리잡기
		EPAT_PITCHING = 6, // [투구] 오버핸드에서 투구 시작, 대기 자세  포함
		EPAT_BACK = 7, // [투구 후 되돌아가기] 투구 후 되돌아가기
		EPAT_CEREMONY = 8, // [세리머니] 타자가 히트하지 못했을 때 주먹을 앞으로 불끈 쥐며 아싸
		EPAT_WINLOSE = 9, // [게임결과창에서 이기거나 졌을 때] 게임결과창에서 이기거나 졌을 때
		EPAT_MENUUI = 10, // [MENU UI에서 포즈] MENU UI에서 포즈
		eEND_EPitcherAnimationType,
	}
	namespace nUtil
	{
		public class jString_EPitcherAnimationType
		{
			public static void Parse(string sDebug,string sVal, ref EPitcherAnimationType eVal) 
			{
				eVal = (EPitcherAnimationType)Enum.Parse(typeof(EPitcherAnimationType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EPitcherAnimationType i = EPitcherAnimationType.eBEGIN_EPitcherAnimationType +1;i < EPitcherAnimationType.eEND_EPitcherAnimationType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EPitcherAnimationType> get_enums() 
			{
				List<EPitcherAnimationType> list = new List<EPitcherAnimationType>();
				for (EPitcherAnimationType i = EPitcherAnimationType.eBEGIN_EPitcherAnimationType +1;i < EPitcherAnimationType.eEND_EPitcherAnimationType; i++){list.Add(i);}
				return list;
			}
		}
	}

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_Batter_Animation
	{
		public Int16 m_index; 	// [index] 영문닉네임 , 각종테이블에서 사용 
		public EPlayerBodyType m_body_type; 	// [체형] 체형 
		public EBatterForm m_better_form; 	// [타격 폼] 타격 폼 
		public EBatterAnimationType m_batter_animation; 	// [타자애니메이션] 타자 애니메이션 종류 
		public Int16 m_animation_number; 	// [해당 애니메이션 넘버] 해당 애니메이션의 넘버 
		public string m_animation_filename; 	// [해당 애니메이션 파일 이름] 해당 에니메이션 파일 이름 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_Int16.Parse("Sys_Batter_Animation::index",token[idx++], ref m_index);
				nUtil.jString_EPlayerBodyType.Parse("Sys_Batter_Animation::body_type",token[idx++], ref m_body_type);
				nUtil.jString_EBatterForm.Parse("Sys_Batter_Animation::better_form",token[idx++], ref m_better_form);
				nUtil.jString_EBatterAnimationType.Parse("Sys_Batter_Animation::batter_animation",token[idx++], ref m_batter_animation);
				nUtil.jString_Int16.Parse("Sys_Batter_Animation::animation_number",token[idx++], ref m_animation_number);
				nUtil.jString_string.Parse("Sys_Batter_Animation::animation_filename",token[idx++], ref m_animation_filename);
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
			output += m_body_type.ToString() + ",";
			output += m_better_form.ToString() + ",";
			output += m_batter_animation.ToString() + ",";
			output += m_animation_number.ToString() + ",";
			output += m_animation_filename.ToString() + ",";
			return output;
		}
	}//class Sys_Batter_Animation

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_Catcher_Animation
	{
		public Int16 m_index; 	// [index] 영문닉네임 , 각종테이블에서 사용 
		public ECatcherAnimationType m_catcher_animation; 	// [포수애니메이션] 포수 애니메이션 종류 
		public Int16 m_animation_number; 	// [해당 애니메이션 넘버] 해당 애니메이션의 넘버 
		public string m_animation_filename; 	// [해당 애니메이션 파일 이름] 해당 에니메이션 파일 이름 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_Int16.Parse("Sys_Catcher_Animation::index",token[idx++], ref m_index);
				nUtil.jString_ECatcherAnimationType.Parse("Sys_Catcher_Animation::catcher_animation",token[idx++], ref m_catcher_animation);
				nUtil.jString_Int16.Parse("Sys_Catcher_Animation::animation_number",token[idx++], ref m_animation_number);
				nUtil.jString_string.Parse("Sys_Catcher_Animation::animation_filename",token[idx++], ref m_animation_filename);
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
			output += m_catcher_animation.ToString() + ",";
			output += m_animation_number.ToString() + ",";
			output += m_animation_filename.ToString() + ",";
			return output;
		}
	}//class Sys_Catcher_Animation

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_Pitcher_Animation
	{
		public Int16 m_index; 	// [index] 영문닉네임 , 각종테이블에서 사용 
		public EPlayerBodyType m_body_type; 	// [체형] 체형 
		public EPitcherForm m_pitcher_form; 	// [투구폼] 투구폼 
		public EPitcherAnimationType m_pitcher_animation; 	// [투수애니메이션] 투수 애니메이션 종류 
		public Int16 m_animation_number; 	// [해당 애니메이션 넘버] 해당 애니메이션의 넘버 
		public string m_animation_filename; 	// [해당 애니메이션 파일 이름] 해당 에니메이션 파일 이름 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_Int16.Parse("Sys_Pitcher_Animation::index",token[idx++], ref m_index);
				nUtil.jString_EPlayerBodyType.Parse("Sys_Pitcher_Animation::body_type",token[idx++], ref m_body_type);
				nUtil.jString_EPitcherForm.Parse("Sys_Pitcher_Animation::pitcher_form",token[idx++], ref m_pitcher_form);
				nUtil.jString_EPitcherAnimationType.Parse("Sys_Pitcher_Animation::pitcher_animation",token[idx++], ref m_pitcher_animation);
				nUtil.jString_Int16.Parse("Sys_Pitcher_Animation::animation_number",token[idx++], ref m_animation_number);
				nUtil.jString_string.Parse("Sys_Pitcher_Animation::animation_filename",token[idx++], ref m_animation_filename);
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
			output += m_body_type.ToString() + ",";
			output += m_pitcher_form.ToString() + ",";
			output += m_pitcher_animation.ToString() + ",";
			output += m_animation_number.ToString() + ",";
			output += m_animation_filename.ToString() + ",";
			return output;
		}
	}//class Sys_Pitcher_Animation

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_Umpire_Animation
	{
		public Int16 m_index; 	// [index] 영문닉네임 , 각종테이블에서 사용 
		public EEumpireAnimationType m_umpire_animation; 	// [심판애니메이션] 심판 애니메이션 종류 
		public Int16 m_animation_number; 	// [해당 애니메이션 넘버] 해당 애니메이션의 넘버 
		public string m_animation_filename; 	// [해당 애니메이션 파일 이름] 해당 에니메이션 파일 이름 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_Int16.Parse("Sys_Umpire_Animation::index",token[idx++], ref m_index);
				nUtil.jString_EEumpireAnimationType.Parse("Sys_Umpire_Animation::umpire_animation",token[idx++], ref m_umpire_animation);
				nUtil.jString_Int16.Parse("Sys_Umpire_Animation::animation_number",token[idx++], ref m_animation_number);
				nUtil.jString_string.Parse("Sys_Umpire_Animation::animation_filename",token[idx++], ref m_animation_filename);
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
			output += m_umpire_animation.ToString() + ",";
			output += m_animation_number.ToString() + ",";
			output += m_animation_filename.ToString() + ",";
			return output;
		}
	}//class Sys_Umpire_Animation

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_Batter_Animation
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Batter_Animation>		m_List = new List<Sys_Batter_Animation> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Batter_Animation >>>");
			foreach (Sys_Batter_Animation p in CSV_Sys_Batter_Animation.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Batter_Animation       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
					Sys_Batter_Animation info = new Sys_Batter_Animation();
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
				Sys_Batter_Animation info = new Sys_Batter_Animation();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_Batter_Animation


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_Catcher_Animation
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Catcher_Animation>		m_List = new List<Sys_Catcher_Animation> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Catcher_Animation >>>");
			foreach (Sys_Catcher_Animation p in CSV_Sys_Catcher_Animation.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Catcher_Animation       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
					Sys_Catcher_Animation info = new Sys_Catcher_Animation();
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
				Sys_Catcher_Animation info = new Sys_Catcher_Animation();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_Catcher_Animation


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_Pitcher_Animation
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Pitcher_Animation>		m_List = new List<Sys_Pitcher_Animation> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Pitcher_Animation >>>");
			foreach (Sys_Pitcher_Animation p in CSV_Sys_Pitcher_Animation.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Pitcher_Animation       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
					Sys_Pitcher_Animation info = new Sys_Pitcher_Animation();
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
				Sys_Pitcher_Animation info = new Sys_Pitcher_Animation();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_Pitcher_Animation


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_Umpire_Animation
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Umpire_Animation>		m_List = new List<Sys_Umpire_Animation> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Umpire_Animation >>>");
			foreach (Sys_Umpire_Animation p in CSV_Sys_Umpire_Animation.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Umpire_Animation       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
					Sys_Umpire_Animation info = new Sys_Umpire_Animation();
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
				Sys_Umpire_Animation info = new Sys_Umpire_Animation();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_Umpire_Animation



	


}//namespace nEXCEL
