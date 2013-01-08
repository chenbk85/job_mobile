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

	public class Sys_BreakingBallUpgrade
	{
		public Sys_BreakingBallState_id_t m_id; 	// [id] id 
		public string m_name; 	// [name] name 
		public EPlayerBreakingBall m_type; 	// [변화구타입] 변화구 이름 
		public EPitcherForm m_need_basicskill1; 	// [업그레이드 필요 투구폼1] 업그레이드에 필요한 투구폼(null일 경우 어떠한 투구폼이 와도 상관 없음) 
		public EPitcherForm m_need_basicskill2; 	// [업그레이드 필요 투구폼2] 업그레이드에 필요한 투구폼(null일 경우 어떠한 투구폼이 와도 상관 없음) 
		public EPlayerBreakingBall m_need_upgrade1; 	// [업그레이드 필요 변화구1] 업그레이드에 필요한 변화구 (레벨 값 1은 업그레이드 불가 null일 경우 기본 변화구) 
		public EPlayerBreakingBall m_need_upgrade2; 	// [업그레이드 필요 변화구2] 업그레이드에 필요한 변화구 (레벨 값 1은 업그레이드 불가) 
		public Int16 m_need_player_level; 	// [업그레이드 가능 플레이어 레벨] 업그레이드 필요 플레이어 레벨 
		public Int16 m_equip_player_level; 	// [장착 가능 플레이어 레벨] 업그레이드 필요 플레이어 레벨 
		public Int16 m_upgrade_need_time1; 	// [변화구1의 업그레이드시간1] 업그레이드 필요 시간 
		public Int16 m_upgrade_need_time2; 	// [변화구2의 업그레이드시간2] 업그레이드에 변화구가 2개 이상 필요 경우에는 변화구를 2개 모두 트레이닝 완료 해야 함으로 필요 
		public game_money_t m_need_money; 	// [업그레이드비용] 업그레이드 필요 게임머니 
		public EBreakingBallPitch m_breaking_pitch; 	// [변화구 구질] 변화구의 종횡변화 구분 
		public EBreakingBallRotation m_ball_rotation; 	// [볼 회전 방향] 변화구 공의 회전 방향 구분 
		public DATETIME m_open_date; 	// [적용 일시] 변화구 적용 일자 
		public bool m_first_open_breakingball; 	// [최초 오픈 선택 변화구] 캐릭터 생성 시 선택 할수 있는 변화구 인지 아닌지 구분 (0=불가능 1=가능) 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_UInt16.Parse("Sys_BreakingBallUpgrade::id",token[idx++], ref m_id);
				nUtil.jString_string.Parse("Sys_BreakingBallUpgrade::name",token[idx++], ref m_name);
				nUtil.jString_EPlayerBreakingBall.Parse("Sys_BreakingBallUpgrade::type",token[idx++], ref m_type);
				nUtil.jString_EPitcherForm.Parse("Sys_BreakingBallUpgrade::need_basicskill1",token[idx++], ref m_need_basicskill1);
				nUtil.jString_EPitcherForm.Parse("Sys_BreakingBallUpgrade::need_basicskill2",token[idx++], ref m_need_basicskill2);
				nUtil.jString_EPlayerBreakingBall.Parse("Sys_BreakingBallUpgrade::need_upgrade1",token[idx++], ref m_need_upgrade1);
				nUtil.jString_EPlayerBreakingBall.Parse("Sys_BreakingBallUpgrade::need_upgrade2",token[idx++], ref m_need_upgrade2);
				nUtil.jString_Int16.Parse("Sys_BreakingBallUpgrade::need_player_level",token[idx++], ref m_need_player_level);
				nUtil.jString_Int16.Parse("Sys_BreakingBallUpgrade::equip_player_level",token[idx++], ref m_equip_player_level);
				nUtil.jString_Int16.Parse("Sys_BreakingBallUpgrade::upgrade_need_time1",token[idx++], ref m_upgrade_need_time1);
				nUtil.jString_Int16.Parse("Sys_BreakingBallUpgrade::upgrade_need_time2",token[idx++], ref m_upgrade_need_time2);
				nUtil.jString_Int32.Parse("Sys_BreakingBallUpgrade::need_money",token[idx++], ref m_need_money);
				nUtil.jString_EBreakingBallPitch.Parse("Sys_BreakingBallUpgrade::breaking_pitch",token[idx++], ref m_breaking_pitch);
				nUtil.jString_EBreakingBallRotation.Parse("Sys_BreakingBallUpgrade::ball_rotation",token[idx++], ref m_ball_rotation);
				nUtil.jString_DATETIME.Parse("Sys_BreakingBallUpgrade::open_date",token[idx++], ref m_open_date);
				nUtil.jString_bool.Parse("Sys_BreakingBallUpgrade::first_open_breakingball",token[idx++], ref m_first_open_breakingball);
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
			output += m_id.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_type.ToString() + ",";
			output += m_need_basicskill1.ToString() + ",";
			output += m_need_basicskill2.ToString() + ",";
			output += m_need_upgrade1.ToString() + ",";
			output += m_need_upgrade2.ToString() + ",";
			output += m_need_player_level.ToString() + ",";
			output += m_equip_player_level.ToString() + ",";
			output += m_upgrade_need_time1.ToString() + ",";
			output += m_upgrade_need_time2.ToString() + ",";
			output += m_need_money.ToString() + ",";
			output += m_breaking_pitch.ToString() + ",";
			output += m_ball_rotation.ToString() + ",";
			output += m_open_date.ToString() + ",";
			output += m_first_open_breakingball.ToString() + ",";
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
				if(sVal=="" || sVal=="0" || sVal=="NULL" || sVal=="null") return true;
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
				if(sVal=="" || sVal=="0" || sVal=="NULL" || sVal=="null") return true;
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
					if(o!=null)
						isFind=true;
					else
						throw new System.Exception(sVal + " -> ((" + s + ")) IS NOT FOUND !! : " + sDebug);
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
		public      static int              Count() { return m_List.Count; }
		public      static Sys_BreakingBallUpgrade       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
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
					Sys_BreakingBallUpgrade info = new Sys_BreakingBallUpgrade();
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
				Sys_BreakingBallUpgrade info = new Sys_BreakingBallUpgrade();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
			_makeIndex();
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_BreakingBallUpgrade



	


}//namespace nEXCEL
