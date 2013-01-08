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

	public enum EIssue_Info
	{
		eBEGIN_EIssue_Info=0,
		EII_NORMAL = 1, // [일반] 일반 서버
		EII_NEW = 2, // [신규] 신규 서버
		EII_RECOMMEND = 3, // [추천] 추천 서버
		EII_TEST = 4, // [테스트용] 테스트용 서버
		eEND_EIssue_Info,
	}
	namespace nUtil
	{
		class jString_EIssue_Info
		{
			public static void Parse(string sDebug,string sVal, ref EIssue_Info eVal) 
			{
				eVal = (EIssue_Info)Enum.Parse(typeof(EIssue_Info), sVal);
			}
		}
	}


	public enum ETile_Sort
	{
		eBEGIN_ETile_Sort=0,
		ETS_ROAD = 1, // [도로] 성과 성 사이의 길
		ETS_MEADOW = 2, // [초원] 숲
		ETS_LAND = 3, // [평지] 평지
		ETS_MOUNT = 4, // [산악] 산악
		ETS_RIVER = 5, // [강] 강물
		ETS_SEA = 6, // [바다] 바다
		ETS_SWAMP = 7, // [늪] 늪
		eEND_ETile_Sort,
	}
	namespace nUtil
	{
		class jString_ETile_Sort
		{
			public static void Parse(string sDebug,string sVal, ref ETile_Sort eVal) 
			{
				eVal = (ETile_Sort)Enum.Parse(typeof(ETile_Sort), sVal);
			}
		}
	}

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_Tile
	{
		public Sys_Tile_id_t m_tisid; 	// [숫자ID]  
		public string m_name; 	// [이름ID]  
		public string m_name_kor; 	// [타일_이름]  
		public string m_client_file; 	// [타일 이미지]  
		public ETile_Sort m_sort; 	// [분류] 세부 텍스쳐 종류 
		public Int16 m_mspeed; 	// [이동속도보정] 유저 이동속도 보정 (%보정값으로 500.0% 가능) 
		public Int16 m_visibility; 	// [가시거리] 유닛의 시야 보정 
		public bool m_build; 	// [건설여부] 건설 개념이 안들어갈 때는 삭제 
		public Int16 m_fskill; 	// [화계_스킬_보정] 불 속성 스킬 보정값 
		public Int16 m_wskill; 	// [수계_스킬_보정] 물 속성 스킬 보정값 
		public Int16 m_rskill; 	// [낙석_스킬_보정] 돌 속성 스킬 보정값 
		public Int16 m_hiskill; 	// [은신_스킬_보정] 은신 스킬 보정값 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_Tile::tisid",token[idx++], ref m_tisid);
			nUtil.jString_string.Parse("Sys_Tile::name",token[idx++], ref m_name);
			nUtil.jString_string.Parse("Sys_Tile::name_kor",token[idx++], ref m_name_kor);
			nUtil.jString_string.Parse("Sys_Tile::client_file",token[idx++], ref m_client_file);
			nUtil.jString_ETile_Sort.Parse("Sys_Tile::sort",token[idx++], ref m_sort);
			nUtil.jString_Int16.Parse("Sys_Tile::mspeed",token[idx++], ref m_mspeed);
			nUtil.jString_Int16.Parse("Sys_Tile::visibility",token[idx++], ref m_visibility);
			nUtil.jString_bool.Parse("Sys_Tile::build",token[idx++], ref m_build);
			nUtil.jString_Int16.Parse("Sys_Tile::fskill",token[idx++], ref m_fskill);
			nUtil.jString_Int16.Parse("Sys_Tile::wskill",token[idx++], ref m_wskill);
			nUtil.jString_Int16.Parse("Sys_Tile::rskill",token[idx++], ref m_rskill);
			nUtil.jString_Int16.Parse("Sys_Tile::hiskill",token[idx++], ref m_hiskill);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_tisid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_name_kor.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_sort.ToString() + ",";
			output += m_mspeed.ToString() + ",";
			output += m_visibility.ToString() + ",";
			output += m_build.ToString() + ",";
			output += m_fskill.ToString() + ",";
			output += m_wskill.ToString() + ",";
			output += m_rskill.ToString() + ",";
			output += m_hiskill.ToString() + ",";
			return output;
		}
	}//class Sys_Tile

	namespace nUtil
	{
		class jString_Sys_Tile
		{
			public static string ToString(Sys_Tile o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_Tile> sysList)
			{
				string output = "";
				foreach (Sys_Tile o in sysList)
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
				Sys_Tile o = (Sys_Tile)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_Tile o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_Tile.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_Tile.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_Tile> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_Tile> sysList = (List<Sys_Tile>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_Tile o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_Tile.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_Tile.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_Tile
	}//namespace nUtil
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_World
	{
		public Sys_World_id_t m_wsid; 	// [숫자 ID] 서버 오픈 순서별로 번호 지정 
		public string m_name; 	// [이름 ID] 서버이름 ID 
		public string m_name_kor; 	// [서버 이름] 서버 선택 리스트에 표시되는 서버 이름 
		public EIssue_Info m_issue; 	// [이슈 상항] 유저에게 알리는 서버 상황. 아이콘 이미지로 표현 
		public string m_address; 	// [접속IP] 접속 주소 
		public string m_help; 	// [서버설명] 기타설명 
		public Int16 m_goldstart; 	// [금 시작자원] 처음 시작시의 금자원량 
		public Int16 m_ricestart; 	// [식량 시작자원] 처음 시작시의 나무자원량 
		public Int16 m_treestart; 	// [나무 시작자원] 처음 시작시의 금자원량 
		public Int16 m_stonestart; 	// [돌 시작자원] 처음 시작시의 금자원량 
		public Int16 m_ironstart; 	// [철 시작자원] 처음 시작시의 금자원량 
		public Int16 m_silkstart; 	// [비단 시작자원] 처음 시작시의 금자원량 
		public Int16 m_mspeed; 	// [부대이동속도보정] 전략맵에서의 부대 이동 속도 (기본 100으로 지정) 1000초에 100타일 이동 
		public Int16 m_re_increase; 	// [자원 증가량] 각 자원채취용 건물에서의 시간당 자원 채취량 보정값. (기본 100으로 지정) 
		public Int16 m_buildtime; 	// [건축 시간] 건물의 건축, 업그레이드 소요 시간 보정값. (기본 100으로 지정) 
		public Int16 m_produtime; 	// [생산 시간] 건물에서의 무기, 기타 생산품들의 생산 시간 보정값. (기본 100으로 지정) 
		public Int16 m_recrutime; 	// [모집 시간] 건물에서의 병사 모집 시간 보정값. (기본 100으로 지정) 
		public Int16 m_researchtime; 	// [연구 시간] 연구 진행 시간 보정값. (기본 100으로 지정) 
		public Int16 m_goldamount; 	// [금 획득량] 건물에서의 세금 징수등의 금 획득량 보정값. (기본 100으로 지정) 
		public Int16 m_peo_increase; 	// [인구 증가] 건물에서의 인구 증가량 보정값. (기본 100으로 지정) 
		public Int16 m_questbenefit; 	// [퀘스트 보상] 퀘스트 수행 후의 보상내용 보정값. (기본 100으로 지정) 
		public Int16 m_huntbenefit; 	// [사냥 보상] 사냥(PVE)에서 승리 후의 보상내용 보정값. (기본 100으로 지정) 
		public Int16 m_appoint_ratio; 	// [장수 등용 확률] 장수 등용 시도시 성공할 확률 보정값. (기본 100으로 지정) 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_World::wsid",token[idx++], ref m_wsid);
			nUtil.jString_string.Parse("Sys_World::name",token[idx++], ref m_name);
			nUtil.jString_string.Parse("Sys_World::name_kor",token[idx++], ref m_name_kor);
			nUtil.jString_EIssue_Info.Parse("Sys_World::issue",token[idx++], ref m_issue);
			nUtil.jString_string.Parse("Sys_World::address",token[idx++], ref m_address);
			nUtil.jString_string.Parse("Sys_World::help",token[idx++], ref m_help);
			nUtil.jString_Int16.Parse("Sys_World::goldstart",token[idx++], ref m_goldstart);
			nUtil.jString_Int16.Parse("Sys_World::ricestart",token[idx++], ref m_ricestart);
			nUtil.jString_Int16.Parse("Sys_World::treestart",token[idx++], ref m_treestart);
			nUtil.jString_Int16.Parse("Sys_World::stonestart",token[idx++], ref m_stonestart);
			nUtil.jString_Int16.Parse("Sys_World::ironstart",token[idx++], ref m_ironstart);
			nUtil.jString_Int16.Parse("Sys_World::silkstart",token[idx++], ref m_silkstart);
			nUtil.jString_Int16.Parse("Sys_World::mspeed",token[idx++], ref m_mspeed);
			nUtil.jString_Int16.Parse("Sys_World::re_increase",token[idx++], ref m_re_increase);
			nUtil.jString_Int16.Parse("Sys_World::buildtime",token[idx++], ref m_buildtime);
			nUtil.jString_Int16.Parse("Sys_World::produtime",token[idx++], ref m_produtime);
			nUtil.jString_Int16.Parse("Sys_World::recrutime",token[idx++], ref m_recrutime);
			nUtil.jString_Int16.Parse("Sys_World::researchtime",token[idx++], ref m_researchtime);
			nUtil.jString_Int16.Parse("Sys_World::goldamount",token[idx++], ref m_goldamount);
			nUtil.jString_Int16.Parse("Sys_World::peo_increase",token[idx++], ref m_peo_increase);
			nUtil.jString_Int16.Parse("Sys_World::questbenefit",token[idx++], ref m_questbenefit);
			nUtil.jString_Int16.Parse("Sys_World::huntbenefit",token[idx++], ref m_huntbenefit);
			nUtil.jString_Int16.Parse("Sys_World::appoint_ratio",token[idx++], ref m_appoint_ratio);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_wsid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_name_kor.ToString() + ",";
			output += m_issue.ToString() + ",";
			output += m_address.ToString() + ",";
			output += m_help.ToString() + ",";
			output += m_goldstart.ToString() + ",";
			output += m_ricestart.ToString() + ",";
			output += m_treestart.ToString() + ",";
			output += m_stonestart.ToString() + ",";
			output += m_ironstart.ToString() + ",";
			output += m_silkstart.ToString() + ",";
			output += m_mspeed.ToString() + ",";
			output += m_re_increase.ToString() + ",";
			output += m_buildtime.ToString() + ",";
			output += m_produtime.ToString() + ",";
			output += m_recrutime.ToString() + ",";
			output += m_researchtime.ToString() + ",";
			output += m_goldamount.ToString() + ",";
			output += m_peo_increase.ToString() + ",";
			output += m_questbenefit.ToString() + ",";
			output += m_huntbenefit.ToString() + ",";
			output += m_appoint_ratio.ToString() + ",";
			return output;
		}
	}//class Sys_World

	namespace nUtil
	{
		class jString_Sys_World
		{
			public static string ToString(Sys_World o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_World> sysList)
			{
				string output = "";
				foreach (Sys_World o in sysList)
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
				Sys_World o = (Sys_World)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_World o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_World.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_World.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_World> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_World> sysList = (List<Sys_World>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_World o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_World.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_World.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_World
	}//namespace nUtil
	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_Tile
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Tile>		m_List = new List<Sys_Tile> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Tile >>>");
			foreach (Sys_Tile p in CSV_Sys_Tile.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Tile       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_Tile FindBy_name(string key){return (Sys_Tile)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_Tile p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_Tile info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_Tile();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_Tile


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_World
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_World>		m_List = new List<Sys_World> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_World >>>");
			foreach (Sys_World p in CSV_Sys_World.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_World       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_World FindBy_name(string key){return (Sys_World)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_World p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_World info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_World();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_World



	


}//namespace nEXCEL
