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

	public enum EBuildType
	{
		eBEGIN_EBuildType=0,
		EBT_Sys_T_HQ = 1, // [본영] 본영
		EBT_Sys_T_Bar = 2, // [주점] 주점
		EBT_ACADEMY = 3, // [서원] 서원
		EBT_PEACE = 4, // [치안부] 치안부
		EBT_SHRINE = 5, // [사당] 사당
		EBT_HIDEOUT = 6, // [감찰부] 감찰부
		EBT_TRADINGPOST = 7, // [교역소] 교역소
		EBT_Sys_T_House = 8, // [민가] 민가
		EBT_Sys_T_Farm = 9, // [농지] 농지
		EBT_SAWMILL = 10, // [제재소] 제재소
		EBT_QUARRY = 11, // [채석장] 채석장
		EBT_MINING = 12, // [광업장] 광업장
		EBT_COCOONERY = 13, // [양잠소] 양잠소
		EBT_Sys_T_Barrack = 14, // [병영] 병영
		EBT_SMITHY = 15, // [대장간] 대장간
		EBT_FORGE = 16, // [공방] 공방
		EBT_STABLE = 17, // [마구간] 마구간
		EBT_Sys_T_Camp = 18, // [둔영] 둔영
		EBT_Sys_T_Depot = 19, // [창고] 창고
		EBT_SECRET = 20, // [비밀창고] 비밀창고
		EBT_TOWER = 21, // [망루] 망루
		EBT_BARRIER = 22, // [방벽] 방벽
		eEND_EBuildType,
	}
	namespace nUtil
	{
		class jString_EBuildType
		{
			public static void Parse(string sDebug,string sVal, ref EBuildType eVal) 
			{
				eVal = (EBuildType)Enum.Parse(typeof(EBuildType), sVal);
			}
		}
	}


	public enum EOutput
	{
		eBEGIN_EOutput=0,
		EOT_POPULATION = 1, // [인구] 인구
		EOT_GOLD = 2, // [금] 금
		EOT_FOOD = 3, // [식량] 식량
		EOT_TREE = 4, // [목재] 목재
		EOT_STONE = 5, // [석재] 석재
		EOT_IRON = 6, // [철재] 철재
		EOT_SILK = 7, // [비단] 비단
		EOT_SOLDIER = 8, // [병사] 병사
		EOT_PIKE = 9, // [창 병기] 
		EOT_HEAVY = 10, // [중갑 병기] 
		EOT_HALBERD = 11, // [언월도 병기] 근위병 (철 소모 위주)
		EOT_BOW = 12, // [궁 병기] 
		EOT_CROSSBOW = 13, // [노 병기] 
		EOT_BOWGUN = 14, // [강노 병기] 
		EOT_BALLISTA = 15, // [노포 병기] 
		EOT_CHARIOT = 16, // [전차 병기] 군마랑 조합해서만 가능 (개수 늘어나야)
		EOT_WAGON = 17, // [마차] 군마랑 조합해서만 가능 (개수 늘어나야)
		EOT_HORSE = 18, // [군마] Eunit_ClassItemA 와 조합 가능
		EOT_WHEELBARROW = 19, // [수레] 공작, 수송, 보급 용도
		EOT_CART = 20, // [목우] 
		EOT_SIEGE_LADDER = 21, // [운제] B만 활용 가능
		EOT_SIEGE_RAM = 22, // [충차] 
		EOT_SIEGE_TOWER = 23, // [정란] 
		EOT_SIEGE_TREBUCHET = 24, // [투석기] 
		eEND_EOutput,
	}
	namespace nUtil
	{
		class jString_EOutput
		{
			public static void Parse(string sDebug,string sVal, ref EOutput eVal) 
			{
				eVal = (EOutput)Enum.Parse(typeof(EOutput), sVal);
			}
		}
	}

	// -------------------------------------------------
	// 빌딩type 테이블의 base 테이블이다. 모든 빌딩type 테이블은 이 테이블을 상속받는다
	// -------------------------------------------------

	public class Sys__T_BuildObj
	{
		public EBuildType m_base_type; 	// [건물타입] Sys_T_BaseObj를상속 받는 테이블의 건물 종류 
		public string m_name; 	// [건물리소스명] 건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 
		public UInt32 m_upgradetime; 	// [업그레이드 시간] 업그레이드를 진행할 때 소비되는 시간 /초단위 
		public Int16 m_tree_num; 	// [목재 비용] 건설에 필요한 목재 비용 
		public Int16 m_stone_num; 	// [돌 비용] 건설에 필요한 돌 비용 
		public Int16 m_iron_num; 	// [철 비용] 건설에 필요한 철 비용 
		public Int16 m_silk_num; 	// [비단 비용] 건설에 필요한 비단 비용 
		public Int16 m_population_num; 	// [인구 비용] 건설에 필요한 인구 비용 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_EBuildType.Parse("Sys__T_BuildObj::base_type",token[idx++], ref m_base_type);
			nUtil.jString_string.Parse("Sys__T_BuildObj::name",token[idx++], ref m_name);
			nUtil.jString_UInt32.Parse("Sys__T_BuildObj::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys__T_BuildObj::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys__T_BuildObj::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys__T_BuildObj::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys__T_BuildObj::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys__T_BuildObj::population_num",token[idx++], ref m_population_num);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_base_type.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			return output;
		}
	}//class Sys__T_BuildObj

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_T_Bar
	{
		public Sys_T_Bar_id_t m_isid; 	// [레벨] 건물 아이디 
		public string m_client_file; 	// [건물 이미지 파일] 건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 
		public UInt32 m_upgradetime; 	// [업그레이드 시간] 업그레이드를 진행할 때 소비되는 시간 /초단위 
		public Int16 m_tree_num; 	// [목재 비용] 건설에 필요한 목재 비용 
		public Int16 m_stone_num; 	// [돌 비용] 건설에 필요한 돌 비용 
		public Int16 m_iron_num; 	// [철 비용] 건설에 필요한 철 비용 
		public Int16 m_silk_num; 	// [비단 비용] 건설에 필요한 비단 비용 
		public Int16 m_population_num; 	// [인구 비용] 건설에 필요한 인구 비용 
		public Int16 m_maxbuild; 	// [최대 생성수] 한 마을에 최대 생성 가능한 건물 수 
		public Int16 m_downlevel; 	// [다운그레이드레벨] 다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 
		public Int16 m_treereturn; 	// [목재 반환비용] 건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) 
		public Int16 m_stonereturn; 	// [돌 반환비용]  
		public Int16 m_ironreturn; 	// [철 반환비용]  
		public Int16 m_silkreturn; 	// [비단 반환비용]  
		public Int16 m_populationreturn; 	// [인구 반환비용] 건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. 
		public Int16 m_hideHero; 	// [재야 장수] 주점에 들어오는 재야장수 수 
		public UInt32 m_resettime; 	// [리셋시간] 주점에서 자동으로 재야장수와 아이템이 리셋되는 시간 (초로계산) 
		public Int16 m_itemnum; 	// [아이템수] 주점에서 행상인이 1회에 가져오는 아이템 수 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_T_Bar::isid",token[idx++], ref m_isid);
			nUtil.jString_string.Parse("Sys_T_Bar::client_file",token[idx++], ref m_client_file);
			nUtil.jString_UInt32.Parse("Sys_T_Bar::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys_T_Bar::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys_T_Bar::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys_T_Bar::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys_T_Bar::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys_T_Bar::population_num",token[idx++], ref m_population_num);
			nUtil.jString_Int16.Parse("Sys_T_Bar::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_Bar::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_Bar::treereturn",token[idx++], ref m_treereturn);
			nUtil.jString_Int16.Parse("Sys_T_Bar::stonereturn",token[idx++], ref m_stonereturn);
			nUtil.jString_Int16.Parse("Sys_T_Bar::ironreturn",token[idx++], ref m_ironreturn);
			nUtil.jString_Int16.Parse("Sys_T_Bar::silkreturn",token[idx++], ref m_silkreturn);
			nUtil.jString_Int16.Parse("Sys_T_Bar::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_Int16.Parse("Sys_T_Bar::hideHero",token[idx++], ref m_hideHero);
			nUtil.jString_UInt32.Parse("Sys_T_Bar::resettime",token[idx++], ref m_resettime);
			nUtil.jString_Int16.Parse("Sys_T_Bar::itemnum",token[idx++], ref m_itemnum);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_isid.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_treereturn.ToString() + ",";
			output += m_stonereturn.ToString() + ",";
			output += m_ironreturn.ToString() + ",";
			output += m_silkreturn.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_hideHero.ToString() + ",";
			output += m_resettime.ToString() + ",";
			output += m_itemnum.ToString() + ",";
			return output;
		}
	}//class Sys_T_Bar

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_T_Barrack
	{
		public Sys_T_Barrack_id_t m_isid; 	// [레벨] 건물 아이디 
		public string m_client_file; 	// [건물 이미지 파일] 건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 
		public UInt32 m_upgradetime; 	// [업그레이드 시간] 업그레이드를 진행할 때 소비되는 시간 /초단위 
		public Int16 m_tree_num; 	// [목재 비용] 건설에 필요한 목재 비용 
		public Int16 m_stone_num; 	// [돌 비용] 건설에 필요한 돌 비용 
		public Int16 m_iron_num; 	// [철 비용] 건설에 필요한 철 비용 
		public Int16 m_silk_num; 	// [비단 비용] 건설에 필요한 비단 비용 
		public Int16 m_population_num; 	// [인구 비용] 건설에 필요한 인구 비용 
		public Int16 m_maxbuild; 	// [최대 생성수] 한 마을에 최대 생성 가능한 건물 수 
		public Int16 m_downlevel; 	// [다운그레이드레벨] 다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 
		public Int16 m_treereturn; 	// [목재 반환비용] 건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) 
		public Int16 m_stonereturn; 	// [돌 반환비용]  
		public Int16 m_ironreturn; 	// [철 반환비용]  
		public Int16 m_silkreturn; 	// [비단 반환비용]  
		public Int16 m_populationreturn; 	// [인구 반환비용] 건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. 
		public Int16 m_s_p_speed; 	// [병사_생산_속도] 병영 레벨업당 생산속도 향상 
		public Int16 m_s_p_cost; 	// [병사_생산_비용] 병영병사 1인 생산 비용 
		public Int16 m_s_output; 	// [병사_ 생산량] 병영병사 최대 생산량 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_T_Barrack::isid",token[idx++], ref m_isid);
			nUtil.jString_string.Parse("Sys_T_Barrack::client_file",token[idx++], ref m_client_file);
			nUtil.jString_UInt32.Parse("Sys_T_Barrack::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::population_num",token[idx++], ref m_population_num);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::treereturn",token[idx++], ref m_treereturn);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::stonereturn",token[idx++], ref m_stonereturn);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::ironreturn",token[idx++], ref m_ironreturn);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::silkreturn",token[idx++], ref m_silkreturn);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::s_p_speed",token[idx++], ref m_s_p_speed);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::s_p_cost",token[idx++], ref m_s_p_cost);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::s_output",token[idx++], ref m_s_output);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_isid.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_treereturn.ToString() + ",";
			output += m_stonereturn.ToString() + ",";
			output += m_ironreturn.ToString() + ",";
			output += m_silkreturn.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_s_p_speed.ToString() + ",";
			output += m_s_p_cost.ToString() + ",";
			output += m_s_output.ToString() + ",";
			return output;
		}
	}//class Sys_T_Barrack

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_T_Camp
	{
		public Sys_T_Camp_id_t m_isid; 	// [레벨] 건물 아이디 
		public string m_client_file; 	// [건물 이미지 파일] 건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 
		public UInt32 m_upgradetime; 	// [업그레이드 시간] 업그레이드를 진행할 때 소비되는 시간 /초단위 
		public Int16 m_tree_num; 	// [목재 비용] 건설에 필요한 목재 비용 
		public Int16 m_stone_num; 	// [돌 비용] 건설에 필요한 돌 비용 
		public Int16 m_iron_num; 	// [철 비용] 건설에 필요한 철 비용 
		public Int16 m_silk_num; 	// [비단 비용] 건설에 필요한 비단 비용 
		public Int16 m_population_num; 	// [인구 비용] 건설에 필요한 인구 비용 
		public Int16 m_maxbuild; 	// [최대 생성수] 한 마을에 최대 생성 가능한 건물 수 
		public Int16 m_downlevel; 	// [다운그레이드레벨] 다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 
		public Int16 m_treereturn; 	// [목재 반환비용] 건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) 
		public Int16 m_stonereturn; 	// [돌 반환비용]  
		public Int16 m_ironreturn; 	// [철 반환비용]  
		public Int16 m_silkreturn; 	// [비단 반환비용]  
		public Int16 m_populationreturn; 	// [인구 반환비용] 건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. 
		public Int16 m_f_r_spend; 	// [병사_ 식량_소비량] 병사 1인이 시간당 소비하는 식량의 양 
		public Int32 m_f_storage; 	// [병사_보관량] 둔영에서 병사 최대 보관량 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_T_Camp::isid",token[idx++], ref m_isid);
			nUtil.jString_string.Parse("Sys_T_Camp::client_file",token[idx++], ref m_client_file);
			nUtil.jString_UInt32.Parse("Sys_T_Camp::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys_T_Camp::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys_T_Camp::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys_T_Camp::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys_T_Camp::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys_T_Camp::population_num",token[idx++], ref m_population_num);
			nUtil.jString_Int16.Parse("Sys_T_Camp::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_Camp::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_Camp::treereturn",token[idx++], ref m_treereturn);
			nUtil.jString_Int16.Parse("Sys_T_Camp::stonereturn",token[idx++], ref m_stonereturn);
			nUtil.jString_Int16.Parse("Sys_T_Camp::ironreturn",token[idx++], ref m_ironreturn);
			nUtil.jString_Int16.Parse("Sys_T_Camp::silkreturn",token[idx++], ref m_silkreturn);
			nUtil.jString_Int16.Parse("Sys_T_Camp::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_Int16.Parse("Sys_T_Camp::f_r_spend",token[idx++], ref m_f_r_spend);
			nUtil.jString_Int32.Parse("Sys_T_Camp::f_storage",token[idx++], ref m_f_storage);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_isid.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_treereturn.ToString() + ",";
			output += m_stonereturn.ToString() + ",";
			output += m_ironreturn.ToString() + ",";
			output += m_silkreturn.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_f_r_spend.ToString() + ",";
			output += m_f_storage.ToString() + ",";
			return output;
		}
	}//class Sys_T_Camp

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_T_Depot
	{
		public Sys_T_Depot_id_t m_isid; 	// [레벨] 건물 아이디 
		public string m_client_file; 	// [건물 이미지 파일] 건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 
		public UInt32 m_upgradetime; 	// [업그레이드 시간] 업그레이드를 진행할 때 소비되는 시간 /초단위 
		public Int16 m_tree_num; 	// [목재 비용] 건설에 필요한 목재 비용 
		public Int16 m_stone_num; 	// [돌 비용] 건설에 필요한 돌 비용 
		public Int16 m_iron_num; 	// [철 비용] 건설에 필요한 철 비용 
		public Int16 m_silk_num; 	// [비단 비용] 건설에 필요한 비단 비용 
		public Int16 m_population_num; 	// [인구 비용] 건설에 필요한 인구 비용 
		public Int16 m_maxbuild; 	// [최대 생성수] 한 마을에 최대 생성 가능한 건물 수 
		public Int16 m_downlevel; 	// [다운그레이드레벨] 다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 
		public Int16 m_treereturn; 	// [목재 반환비용] 건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) 
		public Int16 m_stonereturn; 	// [돌 반환비용]  
		public Int16 m_ironreturn; 	// [철 반환비용]  
		public Int16 m_silkreturn; 	// [비단 반환비용]  
		public Int16 m_populationreturn; 	// [인구 반환비용] 건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. 
		public Int32 m_storage; 	// [최대보관량] 창고에서 자원 최대 보관량 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_T_Depot::isid",token[idx++], ref m_isid);
			nUtil.jString_string.Parse("Sys_T_Depot::client_file",token[idx++], ref m_client_file);
			nUtil.jString_UInt32.Parse("Sys_T_Depot::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys_T_Depot::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys_T_Depot::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys_T_Depot::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys_T_Depot::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys_T_Depot::population_num",token[idx++], ref m_population_num);
			nUtil.jString_Int16.Parse("Sys_T_Depot::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_Depot::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_Depot::treereturn",token[idx++], ref m_treereturn);
			nUtil.jString_Int16.Parse("Sys_T_Depot::stonereturn",token[idx++], ref m_stonereturn);
			nUtil.jString_Int16.Parse("Sys_T_Depot::ironreturn",token[idx++], ref m_ironreturn);
			nUtil.jString_Int16.Parse("Sys_T_Depot::silkreturn",token[idx++], ref m_silkreturn);
			nUtil.jString_Int16.Parse("Sys_T_Depot::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_Int32.Parse("Sys_T_Depot::storage",token[idx++], ref m_storage);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_isid.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_treereturn.ToString() + ",";
			output += m_stonereturn.ToString() + ",";
			output += m_ironreturn.ToString() + ",";
			output += m_silkreturn.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_storage.ToString() + ",";
			return output;
		}
	}//class Sys_T_Depot

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_T_Farm
	{
		public Sys_T_Farm_id_t m_isid; 	// [레벨] 건물 아이디 
		public string m_client_file; 	// [건물 이미지 파일] 건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 
		public UInt32 m_upgradetime; 	// [업그레이드 시간] 업그레이드를 진행할 때 소비되는 시간 /초단위 
		public Int16 m_tree_num; 	// [목재 비용] 건설에 필요한 목재 비용 
		public Int16 m_stone_num; 	// [돌 비용] 건설에 필요한 돌 비용 
		public Int16 m_iron_num; 	// [철 비용] 건설에 필요한 철 비용 
		public Int16 m_silk_num; 	// [비단 비용] 건설에 필요한 비단 비용 
		public Int16 m_population_num; 	// [인구 비용] 건설에 필요한 인구 비용 
		public Int16 m_maxbuild; 	// [최대 생성수] 한 마을에 최대 생성 가능한 건물 수 
		public Int16 m_downlevel; 	// [다운그레이드레벨] 다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 
		public Int16 m_treereturn; 	// [목재 반환비용] 건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) 
		public Int16 m_stonereturn; 	// [돌 반환비용]  
		public Int16 m_ironreturn; 	// [철 반환비용]  
		public Int16 m_silkreturn; 	// [비단 반환비용]  
		public Int16 m_populationreturn; 	// [인구 반환비용] 건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. 
		public Int16 m_foodoutput; 	// [식량생산량] 농가 레벨업당 농지 생산량 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_T_Farm::isid",token[idx++], ref m_isid);
			nUtil.jString_string.Parse("Sys_T_Farm::client_file",token[idx++], ref m_client_file);
			nUtil.jString_UInt32.Parse("Sys_T_Farm::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys_T_Farm::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys_T_Farm::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys_T_Farm::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys_T_Farm::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys_T_Farm::population_num",token[idx++], ref m_population_num);
			nUtil.jString_Int16.Parse("Sys_T_Farm::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_Farm::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_Farm::treereturn",token[idx++], ref m_treereturn);
			nUtil.jString_Int16.Parse("Sys_T_Farm::stonereturn",token[idx++], ref m_stonereturn);
			nUtil.jString_Int16.Parse("Sys_T_Farm::ironreturn",token[idx++], ref m_ironreturn);
			nUtil.jString_Int16.Parse("Sys_T_Farm::silkreturn",token[idx++], ref m_silkreturn);
			nUtil.jString_Int16.Parse("Sys_T_Farm::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_Int16.Parse("Sys_T_Farm::foodoutput",token[idx++], ref m_foodoutput);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_isid.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_treereturn.ToString() + ",";
			output += m_stonereturn.ToString() + ",";
			output += m_ironreturn.ToString() + ",";
			output += m_silkreturn.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_foodoutput.ToString() + ",";
			return output;
		}
	}//class Sys_T_Farm

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_T_House
	{
		public Sys_T_House_id_t m_isid; 	// [레벨] 건물 아이디 
		public string m_client_file; 	// [건물 이미지 파일] 건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 
		public UInt32 m_upgradetime; 	// [업그레이드 시간] 업그레이드를 진행할 때 소비되는 시간 /초단위 
		public Int16 m_tree_num; 	// [목재 비용] 건설에 필요한 목재 비용 
		public Int16 m_stone_num; 	// [돌 비용] 건설에 필요한 돌 비용 
		public Int16 m_iron_num; 	// [철 비용] 건설에 필요한 철 비용 
		public Int16 m_silk_num; 	// [비단 비용] 건설에 필요한 비단 비용 
		public Int16 m_population_num; 	// [인구 비용] 건설에 필요한 인구 비용 
		public Int16 m_maxbuild; 	// [최대 생성수] 한 마을에 최대 생성 가능한 건물 수 
		public Int16 m_downlevel; 	// [다운그레이드레벨] 다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 
		public Int16 m_treereturn; 	// [목재 반환비용] 건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) 
		public Int16 m_stonereturn; 	// [돌 반환비용]  
		public Int16 m_ironreturn; 	// [철 반환비용]  
		public Int16 m_silkreturn; 	// [비단 반환비용]  
		public Int16 m_populationreturn; 	// [인구 반환비용] 건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. 
		public Int16 m_maxpopulation; 	// [민가최대인구] 민가 레벨당 상승되는 최대 인구수 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_T_House::isid",token[idx++], ref m_isid);
			nUtil.jString_string.Parse("Sys_T_House::client_file",token[idx++], ref m_client_file);
			nUtil.jString_UInt32.Parse("Sys_T_House::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys_T_House::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys_T_House::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys_T_House::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys_T_House::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys_T_House::population_num",token[idx++], ref m_population_num);
			nUtil.jString_Int16.Parse("Sys_T_House::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_House::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_House::treereturn",token[idx++], ref m_treereturn);
			nUtil.jString_Int16.Parse("Sys_T_House::stonereturn",token[idx++], ref m_stonereturn);
			nUtil.jString_Int16.Parse("Sys_T_House::ironreturn",token[idx++], ref m_ironreturn);
			nUtil.jString_Int16.Parse("Sys_T_House::silkreturn",token[idx++], ref m_silkreturn);
			nUtil.jString_Int16.Parse("Sys_T_House::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_Int16.Parse("Sys_T_House::maxpopulation",token[idx++], ref m_maxpopulation);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_isid.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_treereturn.ToString() + ",";
			output += m_stonereturn.ToString() + ",";
			output += m_ironreturn.ToString() + ",";
			output += m_silkreturn.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_maxpopulation.ToString() + ",";
			return output;
		}
	}//class Sys_T_House

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class Sys_T_HQ
	{
		public Sys_T_HQ_id_t m_isid; 	// [레벨] 건물 아이디 
		public string m_client_file; 	// [건물 이미지 파일] 건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 
		public UInt32 m_upgradetime; 	// [업그레이드 시간] 업그레이드를 진행할 때 소비되는 시간 /초단위 
		public Int16 m_tree_num; 	// [목재 비용] 건설에 필요한 목재 비용 
		public Int16 m_stone_num; 	// [돌 비용] 건설에 필요한 돌 비용 
		public Int16 m_iron_num; 	// [철 비용] 건설에 필요한 철 비용 
		public Int16 m_silk_num; 	// [비단 비용] 건설에 필요한 비단 비용 
		public Int16 m_population_num; 	// [인구 비용] 건설에 필요한 인구 비용 
		public Int16 m_maxbuild; 	// [최대 생성수] 한 마을에 최대 생성 가능한 건물 수 
		public Int16 m_downlevel; 	// [다운그레이드레벨] 다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 
		public Int16 m_treereturn; 	// [목재 반환비용] 건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) 
		public Int16 m_stonereturn; 	// [돌 반환비용]  
		public Int16 m_ironreturn; 	// [철 반환비용]  
		public Int16 m_silkreturn; 	// [비단 반환비용]  
		public Int16 m_populationreturn; 	// [인구 반환비용] 건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. 
		public Int16 m_getgold; 	// [징수] 징수 명령 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_T_HQ::isid",token[idx++], ref m_isid);
			nUtil.jString_string.Parse("Sys_T_HQ::client_file",token[idx++], ref m_client_file);
			nUtil.jString_UInt32.Parse("Sys_T_HQ::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys_T_HQ::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys_T_HQ::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys_T_HQ::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys_T_HQ::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys_T_HQ::population_num",token[idx++], ref m_population_num);
			nUtil.jString_Int16.Parse("Sys_T_HQ::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_HQ::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_HQ::treereturn",token[idx++], ref m_treereturn);
			nUtil.jString_Int16.Parse("Sys_T_HQ::stonereturn",token[idx++], ref m_stonereturn);
			nUtil.jString_Int16.Parse("Sys_T_HQ::ironreturn",token[idx++], ref m_ironreturn);
			nUtil.jString_Int16.Parse("Sys_T_HQ::silkreturn",token[idx++], ref m_silkreturn);
			nUtil.jString_Int16.Parse("Sys_T_HQ::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_Int16.Parse("Sys_T_HQ::getgold",token[idx++], ref m_getgold);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_isid.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_treereturn.ToString() + ",";
			output += m_stonereturn.ToString() + ",";
			output += m_ironreturn.ToString() + ",";
			output += m_silkreturn.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_getgold.ToString() + ",";
			return output;
		}
	}//class Sys_T_HQ

	

	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_T_Bar
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_T_Bar>		m_List = new List<Sys_T_Bar> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_Bar >>>");
			foreach (Sys_T_Bar p in CSV_Sys_T_Bar.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_T_Bar       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
				Sys_T_Bar info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_Bar();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_T_Bar


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_T_Barrack
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_T_Barrack>		m_List = new List<Sys_T_Barrack> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_Barrack >>>");
			foreach (Sys_T_Barrack p in CSV_Sys_T_Barrack.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_T_Barrack       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
				Sys_T_Barrack info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_Barrack();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_T_Barrack


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_T_Camp
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_T_Camp>		m_List = new List<Sys_T_Camp> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_Camp >>>");
			foreach (Sys_T_Camp p in CSV_Sys_T_Camp.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_T_Camp       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
				Sys_T_Camp info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_Camp();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_T_Camp


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_T_Depot
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_T_Depot>		m_List = new List<Sys_T_Depot> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_Depot >>>");
			foreach (Sys_T_Depot p in CSV_Sys_T_Depot.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_T_Depot       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
				Sys_T_Depot info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_Depot();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_T_Depot


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_T_Farm
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_T_Farm>		m_List = new List<Sys_T_Farm> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_Farm >>>");
			foreach (Sys_T_Farm p in CSV_Sys_T_Farm.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_T_Farm       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
				Sys_T_Farm info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_Farm();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_T_Farm


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_T_House
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_T_House>		m_List = new List<Sys_T_House> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_House >>>");
			foreach (Sys_T_House p in CSV_Sys_T_House.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_T_House       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
				Sys_T_House info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_House();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_T_House


	// -------------------------------------------------
	// 설명없음
	// -------------------------------------------------

	public class CSV_Sys_T_HQ
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_T_HQ>		m_List = new List<Sys_T_HQ> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_HQ >>>");
			foreach (Sys_T_HQ p in CSV_Sys_T_HQ.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_T_HQ       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
				Sys_T_HQ info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_HQ();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_T_HQ



	


}//namespace nEXCEL
