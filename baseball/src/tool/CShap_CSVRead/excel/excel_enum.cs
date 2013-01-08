/*------------------------------------------------------------


command line : 
Excel_Converter.exe D:\svn\baseball\doc\design\excel\code\excel_baseball_table.txt D:\svn\baseball\doc\design\excel\code\excel_enum.txt 

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
	

	// -------------------------------------------------
	// enum�� �ڵ� ���ø� ����
	// -------------------------------------------------

	public enum EAvatarClass
	{
		eBEGIN_EAvatarClass=0,
		AC_MERCENARY = 1, // [�뺴] ���� ������
		AC_WIZARD = 2, // [������] 
		AC_FIGHTER = 3, // [������] 
		AC_ALL = 4, // [��� Ŭ����] ��� ����(����, ���� ����)
		eEND_EAvatarClass,
	}
	namespace nUtil
	{
		class jString_EAvatarClass
		{
			public static void Parse(string sDebug,string sVal, ref EAvatarClass eVal) 
			{
				eVal = (EAvatarClass)Enum.Parse(typeof(EAvatarClass), sVal);
			}
		}
	}


	public enum EBreakingBallPitch
	{
		eBEGIN_EBreakingBallPitch=0,
		EBBP_STRAIGHT = 1, // [����] ����
		EBBP_WIDE = 2, // [Ⱦ��ȭ] Ⱦ��ȭ
		EBBP_HEIGHT = 3, // [����ȭ] ����ȭ
		EBBP_HEIGHTWIDE = 4, // [��Ⱦ��ȭ] ��Ⱦ��ȭ
		eEND_EBreakingBallPitch,
	}
	namespace nUtil
	{
		class jString_EBreakingBallPitch
		{
			public static void Parse(string sDebug,string sVal, ref EBreakingBallPitch eVal) 
			{
				eVal = (EBreakingBallPitch)Enum.Parse(typeof(EBreakingBallPitch), sVal);
			}
		}
	}


	public enum EBreakingBallRotation
	{
		eBEGIN_EBreakingBallRotation=0,
		EBBR_REGULAR = 1, // [��ȸ��] ��ȸ��
		EBBR_REVERSE = 2, // [��ȸ��] ��ȸ��
		EBBR_NOTHING = 3, // [��ȸ��] ��ȸ��
		eEND_EBreakingBallRotation,
	}
	namespace nUtil
	{
		class jString_EBreakingBallRotation
		{
			public static void Parse(string sDebug,string sVal, ref EBreakingBallRotation eVal) 
			{
				eVal = (EBreakingBallRotation)Enum.Parse(typeof(EBreakingBallRotation), sVal);
			}
		}
	}


	public enum EBuildType_test
	{
		eBEGIN_EBuildType_test=0,
		EBTTT_Sys_T_HQ = 1, // [����] ����
		EBTTT_Sys_T_Bar = 2, // [����] ����
		EBTTT_ACADEMY = 3, // [����] ����
		EBTTT_PEACE = 4, // [ġ�Ⱥ�] ġ�Ⱥ�
		EBTTT_SHRINE = 5, // [���] ���
		EBTTT_HIDEOUT = 6, // [������] ������
		EBTTT_TRADINGPOST = 7, // [������] ������
		EBTTT_Sys_T_House = 8, // [�ΰ�] �ΰ�
		EBTTT_Sys_T_Farm = 9, // [����] ����
		EBTTT_SAWMILL = 10, // [�����] �����
		EBTTT_QUARRY = 11, // [ä����] ä����
		EBTTT_MINING = 12, // [������] ������
		EBTTT_COCOONERY = 13, // [�����] �����
		EBTTT_Sys_T_Barrack = 14, // [����] ����
		EBTTT_SMITHY = 15, // [���尣] ���尣
		EBTTT_FORGE = 16, // [����] ����
		EBTTT_STABLE = 17, // [������] ������
		EBTTT_Sys_T_Camp = 18, // [�п�] �п�
		EBTTT_Sys_T_Depot = 19, // [â��] â��
		EBTTT_SECRET = 20, // [���â��] ���â��
		EBTTT_TOWER = 21, // [����] ����
		EBTTT_BARRIER = 22, // [�溮] �溮
		eEND_EBuildType_test,
	}
	namespace nUtil
	{
		class jString_EBuildType_test
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
		ETT_Sys_T_HQ = 1, // [����] ����
		ETT_Sys_T_Bar = 2, // [����] ����
		ETT_ACADEMY = 3, // [����] ����
		ETT_PEACE = 4, // [ġ�Ⱥ�] ġ�Ⱥ�
		ETT_SHRINE = 5, // [���] ���
		ETT_HIDEOUT = 6, // [������] ������
		ETT_TRADINGPOST = 7, // [������] ������
		ETT_Sys_T_House = 8, // [�ΰ�] �ΰ�
		ETT_Sys_T_Farm = 9, // [����] ����
		ETT_SAWMILL = 10, // [�����] �����
		ETT_QUARRY = 11, // [ä����] ä����
		ETT_MINING = 12, // [������] ������
		ETT_COCOONERY = 13, // [�����] �����
		ETT_Sys_T_Barrack = 14, // [����] ����
		ETT_SMITHY = 15, // [���尣] ���尣
		ETT_FORGE = 16, // [����] ����
		ETT_STABLE = 17, // [������] ������
		ETT_Sys_T_Camp = 18, // [�п�] �п�
		ETT_Sys_T_Depot = 19, // [â��] â��
		ETT_SECRET = 20, // [���â��] ���â��
		ETT_TOWER = 21, // [����] ����
		ETT_BARRIER = 22, // [�溮] �溮
		eEND_EBuildTypeTest,
	}
	namespace nUtil
	{
		class jString_EBuildTypeTest
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
		EOTTT_POPULATION = 1, // [�α�] �α�
		EOTTT_GOLD = 2, // [��] ��
		EOTTT_FOOD = 3, // [�ķ�] �ķ�
		EOTTT_TREE = 4, // [����] ����
		EOTTT_STONE = 5, // [����] ����
		EOTTT_IRON = 6, // [ö��] ö��
		EOTTT_SILK = 7, // [���] ���
		EOTTT_SOLDIER = 8, // [����] ����
		EOTTT_PIKE = 9, // [â ����] 
		EOTTT_HEAVY = 10, // [�߰� ����] 
		EOTTT_HALBERD = 11, // [����� ����] ������ (ö �Ҹ� ����)
		EOTTT_BOW = 12, // [�� ����] 
		EOTTT_CROSSBOW = 13, // [�� ����] 
		EOTTT_BOWGUN = 14, // [���� ����] 
		EOTTT_BALLISTA = 15, // [���� ����] 
		EOTTT_CHARIOT = 16, // [���� ����] ������ �����ؼ��� ���� (���� �þ��)
		EOTTT_WAGON = 17, // [����] ������ �����ؼ��� ���� (���� �þ��)
		EOTTT_HORSE = 18, // [����] Eunit_ClassItemA �� ���� ����
		EOTTT_WHEELBARROW = 19, // [����] ����, ����, ���� �뵵
		EOTTT_CART = 20, // [���] 
		EOTTT_SIEGE_LADDER = 21, // [����] B�� Ȱ�� ����
		EOTTT_SIEGE_RAM = 22, // [����] 
		EOTTT_SIEGE_TOWER = 23, // [����] 
		EOTTT_SIEGE_TREBUCHET = 24, // [������] 
		eEND_EOutput_test,
	}
	namespace nUtil
	{
		class jString_EOutput_test
		{
			public static void Parse(string sDebug,string sVal, ref EOutput_test eVal) 
			{
				eVal = (EOutput_test)Enum.Parse(typeof(EOutput_test), sVal);
			}
		}
	}


	public enum EPlayer_Onoffline
	{
		eBEGIN_EPlayer_Onoffline=0,
		EPO_ONPLAYER = 1, // [�¶����÷��̾�] �¶����÷��̾�
		EPO_OFFPLAYER = 2, // [���������÷��̾�] ���������÷��̾�
		eEND_EPlayer_Onoffline,
	}
	namespace nUtil
	{
		class jString_EPlayer_Onoffline
		{
			public static void Parse(string sDebug,string sVal, ref EPlayer_Onoffline eVal) 
			{
				eVal = (EPlayer_Onoffline)Enum.Parse(typeof(EPlayer_Onoffline), sVal);
			}
		}
	}


	public enum EPlayerBreakingBall
	{
		eBEGIN_EPlayerBreakingBall=0,
		PBB_NULL = 1, // [����] ����
		PBB_FOURSEAM = 2, // [����] ����
		PBB_TWOSEAM = 3, // [����] ����
		PBB_RISINGFAST = 4, // [����¡�н�Ʈ��] ����¡�н�Ʈ��
		PBB_UPSHOUT = 5, // [����] ����
		PBB_SLIDER = 6, // [�����̴�] �����̴�
		PBB_HSLIDER = 7, // [H�����̴�] H�����̴�
		PBB_CUTFAST = 8, // [���н�Ʈ��] ���н�Ʈ��
		PBB_VSLIDER = 9, // [V�����̴�] V�����̴�
		PBB_SLUB = 10, // [������] ������
		PBB_CHANGEUP = 11, // [ü������] ü������
		PBB_CIRCLECHANGEUP = 12, // [��Ŭü������] ��Ŭü������
		PBB_KNUCKLE = 13, // [��Ŭ] ��Ŭ
		PBB_CURVE = 14, // [Ŀ��] Ŀ��
		PBB_SLOWCURVE = 15, // [���ο�Ŀ��] ���ο�Ŀ��
		PBB_KNUCKLECURVE = 16, // [��ŬĿ��] ��ŬĿ��
		PBB_DROPCURVE = 17, // [���Ŀ��] ���Ŀ��
		PBB_POWERCURVE = 18, // [�Ŀ�Ŀ��] �Ŀ�Ŀ��
		PBB_SHOUT = 19, // [��Ʈ] ��Ʈ
		PBB_HSHOUT = 20, // [H��Ʈ] H��Ʈ
		PBB_FORK = 21, // [��ũ] ��ũ
		PBB_PALM = 22, // [��] ��
		PBB_SFF = 23, // [SFF] SFF
		PBB_SINKER = 24, // [��Ŀ_ ��ũ��] ��Ŀ, ��ũ��
		PBB_HSINKER = 25, // [H��Ŀ] H��Ŀ
		eEND_EPlayerBreakingBall,
	}
	namespace nUtil
	{
		class jString_EPlayerBreakingBall
		{
			public static void Parse(string sDebug,string sVal, ref EPlayerBreakingBall eVal) 
			{
				eVal = (EPlayerBreakingBall)Enum.Parse(typeof(EPlayerBreakingBall), sVal);
			}
		}
	}


	


}//namespace nEXCEL
