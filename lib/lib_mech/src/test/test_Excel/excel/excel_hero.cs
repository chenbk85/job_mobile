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

	public enum EDeckYear
	{
		eBEGIN_EDeckYear=0,
		DY_189 = 1, // [189년 카드 덱] 189년 카드 덱
		DY_192 = 2, // [192년 카드 덱] 192년 카드 덱
		eEND_EDeckYear,
	}
	namespace nUtil
	{
		class jString_EDeckYear
		{
			public static void Parse(string sDebug,string sVal, ref EDeckYear eVal) 
			{
				eVal = (EDeckYear)Enum.Parse(typeof(EDeckYear), sVal);
			}
		}
	}


	public enum EHeroCategory
	{
		eBEGIN_EHeroCategory=0,
		HC_HISTORICAL = 1, // [역사 장수] 역사 장수
		HC_VIRTAUL = 2, // [가상 장수] 가상 장수
		eEND_EHeroCategory,
	}
	namespace nUtil
	{
		class jString_EHeroCategory
		{
			public static void Parse(string sDebug,string sVal, ref EHeroCategory eVal) 
			{
				eVal = (EHeroCategory)Enum.Parse(typeof(EHeroCategory), sVal);
			}
		}
	}


	public enum EHeroEngagementtype
	{
		eBEGIN_EHeroEngagementtype=0,
		HE_COMMON = 1, // [일반] 일반
		HE_RARE = 2, // [희귀] 희귀
		eEND_EHeroEngagementtype,
	}
	namespace nUtil
	{
		class jString_EHeroEngagementtype
		{
			public static void Parse(string sDebug,string sVal, ref EHeroEngagementtype eVal) 
			{
				eVal = (EHeroEngagementtype)Enum.Parse(typeof(EHeroEngagementtype), sVal);
			}
		}
	}


	public enum EHeroFacetype
	{
		eBEGIN_EHeroFacetype=0,
		HF_ORIGINAL = 1, // [얼굴이미지사용] 고유 이미지, 유명 장수
		HF_COMMON = 2, // [범용이미지사용] 중복 사용가능한 이미지, 일반 장수
		HF_MONTAGE = 3, // [조합(몽타쥬) 이미지] 얼굴 조합기를 이용한 형태
		HF_UPLOAD = 4, // [유저 등록 이미지] 유저가 업로드한 이미지
		eEND_EHeroFacetype,
	}
	namespace nUtil
	{
		class jString_EHeroFacetype
		{
			public static void Parse(string sDebug,string sVal, ref EHeroFacetype eVal) 
			{
				eVal = (EHeroFacetype)Enum.Parse(typeof(EHeroFacetype), sVal);
			}
		}
	}


	public enum EHeroPersonality
	{
		eBEGIN_EHeroPersonality=0,
		HP_TOUGH = 1, // [저돌] 저돌
		HP_BRAVE = 2, // [용맹] 용맹
		HP_COOL = 3, // [냉정] 냉정
		HP_WEAK = 4, // [소심] 소심
		eEND_EHeroPersonality,
	}
	namespace nUtil
	{
		class jString_EHeroPersonality
		{
			public static void Parse(string sDebug,string sVal, ref EHeroPersonality eVal) 
			{
				eVal = (EHeroPersonality)Enum.Parse(typeof(EHeroPersonality), sVal);
			}
		}
	}


	public enum EHeroSex
	{
		eBEGIN_EHeroSex=0,
		HS_MALE = 1, // [남성] 남자 장수
		HS_FEMALE = 2, // [여성] 여자 장수
		eEND_EHeroSex,
	}
	namespace nUtil
	{
		class jString_EHeroSex
		{
			public static void Parse(string sDebug,string sVal, ref EHeroSex eVal) 
			{
				eVal = (EHeroSex)Enum.Parse(typeof(EHeroSex), sVal);
			}
		}
	}


	public enum EHeroWorkState
	{
		eBEGIN_EHeroWorkState=0,
		HWS_REST = 1, // [휴식] 아무 일도 하지 않고 있음
		HWS_CONSTRUCTION = 2, // [건물 건설] 건물 건설을 수행 중
		HWS_EXPLORATION = 3, // [탐색 활동] 탐색 활동을 수행 중
		HWS_COMBAT = 4, // [부대 출전] 부대를 이끌고 필드에 나간 상태
		eEND_EHeroWorkState,
	}
	namespace nUtil
	{
		class jString_EHeroWorkState
		{
			public static void Parse(string sDebug,string sVal, ref EHeroWorkState eVal) 
			{
				eVal = (EHeroWorkState)Enum.Parse(typeof(EHeroWorkState), sVal);
			}
		}
	}

	// -------------------------------------------------
	// 장수 테이블
	// -------------------------------------------------

	public class Sys_Hero
	{
		public Sys_Hero_id_t m_hsid; 	// [sid] 장수가 소속한 세력(소유 유저의 소속 세력과 같음) 
		public EHeroCategory m_category; 	// [장수 분류] 장수 분류 형태, 역사 장수, 가상 장수 
		public EDeckYear m_deck_year; 	// [카드 연도] 장수 연도별 카드 덱 이름 
		public string m_name; 	// [장수 영문 이름] 장수 영문 이름 
		public string m_name_kor; 	// [장수 한글 이름] 장수 한글 이름 
		public string m_image_file; 	// [얼굴 이미지] 장수 초상화 이미지 
		public Int32 m_grade; 	// [장수 등급] 장수 등급, 1성 ~ 7성까지 ( 차후 Sys_HeroGrade_id_t) 
		public Int32 m_age; 	// [나이]  
		public Int32 m_leadership; 	// [통솔]  
		public Int32 m_power; 	// [무력]  
		public Int32 m_intelligent; 	// [지모]  
		public Int32 m_politic; 	// [정치]  
		public Int32 m_charm; 	// [매력]  
		public bool m_is_male; 	// [성별] 성별 
		public EHeroPersonality m_personality; 	// [성격] 장수 성격 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_Hero::hsid",token[idx++], ref m_hsid);
			nUtil.jString_EHeroCategory.Parse("Sys_Hero::category",token[idx++], ref m_category);
			nUtil.jString_EDeckYear.Parse("Sys_Hero::deck_year",token[idx++], ref m_deck_year);
			nUtil.jString_string.Parse("Sys_Hero::name",token[idx++], ref m_name);
			nUtil.jString_string.Parse("Sys_Hero::name_kor",token[idx++], ref m_name_kor);
			nUtil.jString_string.Parse("Sys_Hero::image_file",token[idx++], ref m_image_file);
			nUtil.jString_Int32.Parse("Sys_Hero::grade",token[idx++], ref m_grade);
			nUtil.jString_Int32.Parse("Sys_Hero::age",token[idx++], ref m_age);
			nUtil.jString_Int32.Parse("Sys_Hero::leadership",token[idx++], ref m_leadership);
			nUtil.jString_Int32.Parse("Sys_Hero::power",token[idx++], ref m_power);
			nUtil.jString_Int32.Parse("Sys_Hero::intelligent",token[idx++], ref m_intelligent);
			nUtil.jString_Int32.Parse("Sys_Hero::politic",token[idx++], ref m_politic);
			nUtil.jString_Int32.Parse("Sys_Hero::charm",token[idx++], ref m_charm);
			nUtil.jString_bool.Parse("Sys_Hero::is_male",token[idx++], ref m_is_male);
			nUtil.jString_EHeroPersonality.Parse("Sys_Hero::personality",token[idx++], ref m_personality);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_hsid.ToString() + ",";
			output += m_category.ToString() + ",";
			output += m_deck_year.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_name_kor.ToString() + ",";
			output += m_image_file.ToString() + ",";
			output += m_grade.ToString() + ",";
			output += m_age.ToString() + ",";
			output += m_leadership.ToString() + ",";
			output += m_power.ToString() + ",";
			output += m_intelligent.ToString() + ",";
			output += m_politic.ToString() + ",";
			output += m_charm.ToString() + ",";
			output += m_is_male.ToString() + ",";
			output += m_personality.ToString() + ",";
			return output;
		}
	}//class Sys_Hero

	namespace nUtil
	{
		class jString_Sys_Hero
		{
			public static string ToString(Sys_Hero o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_Hero> sysList)
			{
				string output = "";
				foreach (Sys_Hero o in sysList)
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
				Sys_Hero o = (Sys_Hero)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_Hero o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_Hero.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_Hero.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_Hero> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_Hero> sysList = (List<Sys_Hero>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_Hero o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_Hero.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_Hero.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_Hero
	}//namespace nUtil
	

	// -------------------------------------------------
	// 장수 테이블
	// -------------------------------------------------

	public class CSV_Sys_Hero
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Hero>		m_List = new List<Sys_Hero> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Hero >>>");
			foreach (Sys_Hero p in CSV_Sys_Hero.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Hero       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_Hero FindBy_name(string key){return (Sys_Hero)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_Hero p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_Hero info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_Hero();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_Hero



	


}//namespace nEXCEL
