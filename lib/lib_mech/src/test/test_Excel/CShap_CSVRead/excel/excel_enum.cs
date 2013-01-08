/*------------------------------------------------------------


command line : 
Excel_Converter.exe D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_test.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_test2.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_enum.txt 

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
	using Use_User_id_t = Int64;
	using Sys_Force_id_t = UInt16;
	using Use_F_Transport_id_t = Int64;
	using Use_Force_id_t = Int64;
	using Use_Town_id_t = Int64;
	using Use_Hero_id_t = Int64;
	using Sys__T_Base_id_t = UInt16;
	using Sys_T_Bar_id_t = UInt16;
	using Sys_T__Bar_id_t = UInt16;
	using Sys_T_Barrack_id_t = UInt16;
	using Sys_T_Camp_id_t = UInt16;
	using Sys_T_Depot_id_t = UInt16;
	using Sys_T_Farm_id_t = UInt16;
	using Sys_T_House_id_t = UInt16;
	using Sys_T_HQ_id_t = UInt16;
	using Use_T_Output_id_t = Int64;
	using cash_money_t = Int32;
	using Sys_Tile_id_t = UInt16;
	using Sys_World_id_t = UInt16;
	using Sys_T_Test_id_t = UInt16;
	using Sys_T_Test2_id_t = UInt16;
	using Sys_T_Test3_id_t = UInt16;
	

	// -------------------------------------------------
	// enum형 코드 템플릿 정의
	// -------------------------------------------------

	public enum EAvatarClass
	{
		eBEGIN_EAvatarClass=0,
		AC_MERCENARY = 1, // [용병] 상위 직업군
		AC_WIZARD = 2, // [마법사] 
		AC_FIGHTER = 3, // [격투가] 
		AC_ALL = 4, // [모든 클래스] 모든 직업(상위, 하위 포함)
		eEND_EAvatarClass,
	}
	namespace nUtil
	{
		class FromString_EAvatarClass
		{
			public static void Parse(string sDebug,string sVal, ref EAvatarClass eVal) 
			{
				eVal = (EAvatarClass)Enum.Parse(typeof(EAvatarClass), sVal);
			}
		}
	}


	public enum EBuildType_test
	{
		eBEGIN_EBuildType_test=0,
		EBTTT_Sys_T_HQ = 1, // [본영] 본영
		EBTTT_Sys_T_Bar = 2, // [주점] 주점
		EBTTT_ACADEMY = 3, // [서원] 서원
		EBTTT_PEACE = 4, // [치안부] 치안부
		EBTTT_SHRINE = 5, // [사당] 사당
		EBTTT_HIDEOUT = 6, // [감찰부] 감찰부
		EBTTT_TRADINGPOST = 7, // [교역소] 교역소
		EBTTT_Sys_T_House = 8, // [민가] 민가
		EBTTT_Sys_T_Farm = 9, // [농지] 농지
		EBTTT_SAWMILL = 10, // [제재소] 제재소
		EBTTT_QUARRY = 11, // [채석장] 채석장
		EBTTT_MINING = 12, // [광업장] 광업장
		EBTTT_COCOONERY = 13, // [양잠소] 양잠소
		EBTTT_Sys_T_Barrack = 14, // [병영] 병영
		EBTTT_SMITHY = 15, // [대장간] 대장간
		EBTTT_FORGE = 16, // [공방] 공방
		EBTTT_STABLE = 17, // [마구간] 마구간
		EBTTT_Sys_T_Camp = 18, // [둔영] 둔영
		EBTTT_Sys_T_Depot = 19, // [창고] 창고
		EBTTT_SECRET = 20, // [비밀창고] 비밀창고
		EBTTT_TOWER = 21, // [망루] 망루
		EBTTT_BARRIER = 22, // [방벽] 방벽
		eEND_EBuildType_test,
	}
	namespace nUtil
	{
		class FromString_EBuildType_test
		{
			public static void Parse(string sDebug,string sVal, ref EBuildType_test eVal) 
			{
				eVal = (EBuildType_test)Enum.Parse(typeof(EBuildType_test), sVal);
			}
		}
	}


	public enum EBuildTypeTest
	{
		eBEGIN_EBuildTypeTest=0,
		ETT_Sys_T_HQ = 1, // [본영] 본영
		ETT_Sys_T_Bar = 2, // [주점] 주점
		ETT_ACADEMY = 3, // [서원] 서원
		ETT_PEACE = 4, // [치안부] 치안부
		ETT_SHRINE = 5, // [사당] 사당
		ETT_HIDEOUT = 6, // [감찰부] 감찰부
		ETT_TRADINGPOST = 7, // [교역소] 교역소
		ETT_Sys_T_House = 8, // [민가] 민가
		ETT_Sys_T_Farm = 9, // [농지] 농지
		ETT_SAWMILL = 10, // [제재소] 제재소
		ETT_QUARRY = 11, // [채석장] 채석장
		ETT_MINING = 12, // [광업장] 광업장
		ETT_COCOONERY = 13, // [양잠소] 양잠소
		ETT_Sys_T_Barrack = 14, // [병영] 병영
		ETT_SMITHY = 15, // [대장간] 대장간
		ETT_FORGE = 16, // [공방] 공방
		ETT_STABLE = 17, // [마구간] 마구간
		ETT_Sys_T_Camp = 18, // [둔영] 둔영
		ETT_Sys_T_Depot = 19, // [창고] 창고
		ETT_SECRET = 20, // [비밀창고] 비밀창고
		ETT_TOWER = 21, // [망루] 망루
		ETT_BARRIER = 22, // [방벽] 방벽
		eEND_EBuildTypeTest,
	}
	namespace nUtil
	{
		class FromString_EBuildTypeTest
		{
			public static void Parse(string sDebug,string sVal, ref EBuildTypeTest eVal) 
			{
				eVal = (EBuildTypeTest)Enum.Parse(typeof(EBuildTypeTest), sVal);
			}
		}
	}


	public enum EOutput_test
	{
		eBEGIN_EOutput_test=0,
		EOTTT_POPULATION = 1, // [인구] 인구
		EOTTT_GOLD = 2, // [금] 금
		EOTTT_FOOD = 3, // [식량] 식량
		EOTTT_TREE = 4, // [목재] 목재
		EOTTT_STONE = 5, // [석재] 석재
		EOTTT_IRON = 6, // [철재] 철재
		EOTTT_SILK = 7, // [비단] 비단
		EOTTT_SOLDIER = 8, // [병사] 병사
		EOTTT_PIKE = 9, // [창 병기] 
		EOTTT_HEAVY = 10, // [중갑 병기] 
		EOTTT_HALBERD = 11, // [언월도 병기] 근위병 (철 소모 위주)
		EOTTT_BOW = 12, // [궁 병기] 
		EOTTT_CROSSBOW = 13, // [노 병기] 
		EOTTT_BOWGUN = 14, // [강노 병기] 
		EOTTT_BALLISTA = 15, // [노포 병기] 
		EOTTT_CHARIOT = 16, // [전차 병기] 군마랑 조합해서만 가능 (개수 늘어나야)
		EOTTT_WAGON = 17, // [마차] 군마랑 조합해서만 가능 (개수 늘어나야)
		EOTTT_HORSE = 18, // [군마] Eunit_ClassItemA 와 조합 가능
		EOTTT_WHEELBARROW = 19, // [수레] 공작, 수송, 보급 용도
		EOTTT_CART = 20, // [목우] 
		EOTTT_SIEGE_LADDER = 21, // [운제] B만 활용 가능
		EOTTT_SIEGE_RAM = 22, // [충차] 
		EOTTT_SIEGE_TOWER = 23, // [정란] 
		EOTTT_SIEGE_TREBUCHET = 24, // [투석기] 
		eEND_EOutput_test,
	}
	namespace nUtil
	{
		class FromString_EOutput_test
		{
			public static void Parse(string sDebug,string sVal, ref EOutput_test eVal) 
			{
				eVal = (EOutput_test)Enum.Parse(typeof(EOutput_test), sVal);
			}
		}
	}


	


}//namespace nEXCEL
