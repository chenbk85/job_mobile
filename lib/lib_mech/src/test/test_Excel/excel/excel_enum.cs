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
	// enum�� �ڵ� ���ø� ����
	// -------------------------------------------------

	public enum EBetterAbility
	{
		eBEGIN_EBetterAbility=0,
		BA_NULL = 1, // [����] ����
		BA_LEFT = 2, // [��������] ���������� �Ŀ� ����
		BA_RIGHT = 3, // [�������] ������� ���� �Ŀ� ����
		BA_HOMERUN = 4, // [Ȩ��Ÿ��] ��Ʈ�� �Ŀ� ����
		BA_WIDE = 5, // [����Ÿ��] ����Ÿ�� - �о������� �Ŀ� �ٿ����
		BA_FULLHIT = 6, // [Ǯ����] Ǯ���� - ��������� �Ŀ� ����
		BA_LOWHIT = 7, // [�κ�����] �κ����� - Ÿ�������� �ϴ�/�ߴܿ��� �Ŀ� ����
		BA_HIGHHIT = 8, // [���̺�����] ���̺����� - �ߴ�# ��ܿ��� �Ŀ� ����
		BA_RUNFIRE = 9, // [����] ���� - �ٷ� ����Ÿ������ Ȩ���� �Ŀ� ����
		eEND_EBetterAbility,
	}
	namespace nUtil
	{
		class jString_EBetterAbility
		{
			public static void Parse(string sDebug,string sVal, ref EBetterAbility eVal) 
			{
				eVal = (EBetterAbility)Enum.Parse(typeof(EBetterAbility), sVal);
			}
		}
	}


	public enum EBetterForm
	{
		eBEGIN_EBetterForm=0,
		BF_SQUARE = 1, // [������] ������
		BF_OPEN = 2, // [����] ����
		BF_CLOSE = 3, // [ũ�����] ũ�����
		BF_NULL = 4, // [����] ����
		eEND_EBetterForm,
	}
	namespace nUtil
	{
		class jString_EBetterForm
		{
			public static void Parse(string sDebug,string sVal, ref EBetterForm eVal) 
			{
				eVal = (EBetterForm)Enum.Parse(typeof(EBetterForm), sVal);
			}
		}
	}


	public enum EBetterHitType
	{
		eBEGIN_EBetterHitType=0,
		EBHT_STANDOUT = 1, // [���ĵ�ƿ�] ���ĵ�ƿ�
		EBHT_SWINGOUT = 2, // [�����ƿ�] �����ƿ�
		EBHT_FOULOUT = 3, // [�Ŀ�ƿ�] �Ŀ�ƿ�
		EBIT_INFIELDOUT = 4, // [���߾ƿ�] ���߾ƿ�
		EBIT_LEFTFIELDOUT = 5, // [���ͼ��ƿ�] ���ͼ��ƿ�
		EBIT_CENTERFIELDOUT = 6, // [�߰߼��ƿ�] �߰߼��ƿ�
		EBIT_RIGHTFIELDOUT = 7, // [���ͼ��ƿ�] ���ͼ��ƿ�
		EBHT_NO_HIT = 8, // [ġ�����ѻ���] �ƿ�����
		EBHT_ONEHIT = 9, // [�Ϸ�Ÿ] �Ϸ�Ÿ
		EBHT_DOUBLEHIT = 10, // [�̷�Ÿ] �̷�Ÿ
		EBHT_TRIPLEHIT = 11, // [���Ÿ] ���Ÿ
		EBHT_HOMERUN = 12, // [Ȩ��] Ȩ��
		eEND_EBetterHitType,
	}
	namespace nUtil
	{
		class jString_EBetterHitType
		{
			public static void Parse(string sDebug,string sVal, ref EBetterHitType eVal) 
			{
				eVal = (EBetterHitType)Enum.Parse(typeof(EBetterHitType), sVal);
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


	public enum EConditionCharacterTitle
	{
		eBEGIN_EConditionCharacterTitle=0,
		ECCT_NULL = 1, // [����] ����
		ECCT_ACORNER = 2, // [������] ������
		ECCT_LEGEND = 3, // [������] ������
		ECCT_DESTROYFRIENDSHIP = 4, // [�����ı���] �����ı���
		ECCT_SLUGGER = 5, // [������] ������
		ECCT_DOCTORK = 6, // [����K] ����K
		ECCT_FINALKING = 7, // [���ǿ�] ���ǿ�
		ECCT_SCROOGE = 8, // [��ũ����] ��ũ����
		ECCT_VVIP = 9, // [����] ����
		ECCT_ACE = 10, // [���̽�] ���̽�
		eEND_EConditionCharacterTitle,
	}
	namespace nUtil
	{
		class jString_EConditionCharacterTitle
		{
			public static void Parse(string sDebug,string sVal, ref EConditionCharacterTitle eVal) 
			{
				eVal = (EConditionCharacterTitle)Enum.Parse(typeof(EConditionCharacterTitle), sVal);
			}
		}
	}


	public enum EConsumeItemEffect
	{
		eBEGIN_EConsumeItemEffect=0,
		CIE_MONEYUP = 1, // [���ӸӴϹ����¾�����] ���ӽ� �������� �޴� �Ӵ��� ���� ��� ���(1000����) ���� ���consume_item_effect_value���� 500�̸� 50%�÷���
		CIE_EXPUP = 2, // [����ġ�����¾�����] ���ӽ� �������� �޴� ����ġ�� ���� ��� ���
		CIE_ITEMDROPUP = 3, // [�����۵��Ȯ����¾�����] ���ӽ� �������� �޴� �������� ���� Ȯ�� ���
		CIE_STATUPWHILE = 4, // [�ɷ�ġ�Ͻû�¾�����] ���ӽ� ������ ������ �ִ� ������ �Ͻ������� ���
		CIE_STATUPFOREVER = 5, // [�ɷ�ġ������¾�����] ���ӽ� ������ ������ �ִ� ������ ���������� ���
		CIE_UPGRADELUCKYUP = 6, // [��ȭȮ������������] ���ξ����� ��ȭ�� Ȯ�� ����
		CIE_UPGRADETIMEDOWN = 7, // [��ȭ�ð����Ҿ�����] ���ξ����� ��ȭ�� �ð� ����
		CIE_UPGRADECANCEL = 8, // [��ȭ��Ҿ�����] ��ȭ �Ϸ��� ���ξ������� ��ȭ ���
		CIE_ITEMUSEDOWN = 9, // [�����ۻ�밡�ɷ�������] �������� ��밡�� ������ ����
		CIE_ETC = 10, // [ETC] ��Ÿ. �ش�����ۺ��� �������
		eEND_EConsumeItemEffect,
	}
	namespace nUtil
	{
		class jString_EConsumeItemEffect
		{
			public static void Parse(string sDebug,string sVal, ref EConsumeItemEffect eVal) 
			{
				eVal = (EConsumeItemEffect)Enum.Parse(typeof(EConsumeItemEffect), sVal);
			}
		}
	}


	public enum EEventType
	{
		eBEGIN_EEventType=0,
		ET_MONEY = 1, // [�Ӵ�] �Ӵ�
		ET_ITEM = 2, // [������] ������
		ET_MONEY_ITEM = 3, // [�Ӵ�_������] �Ӵ�_������
		eEND_EEventType,
	}
	namespace nUtil
	{
		class jString_EEventType
		{
			public static void Parse(string sDebug,string sVal, ref EEventType eVal) 
			{
				eVal = (EEventType)Enum.Parse(typeof(EEventType), sVal);
			}
		}
	}


	public enum EGestureType
	{
		eBEGIN_EGestureType=0,
		EGTT_STRAGHT = 1, // [����] ����
		EGTT_VERTICAL = 2, // [������] ������
		EGTT_CURVE = 3, // [�] �
		EGTT_STAIR_VERTICAL = 4, // [�����������] �����������
		EGTT_S_CURVE = 5, // [�������] �������
		EGTT_NULL = 6, // [����] ��ȭ���� ����ó�� �������� ���� ���
		eEND_EGestureType,
	}
	namespace nUtil
	{
		class jString_EGestureType
		{
			public static void Parse(string sDebug,string sVal, ref EGestureType eVal) 
			{
				eVal = (EGestureType)Enum.Parse(typeof(EGestureType), sVal);
			}
		}
	}


	public enum EGiftCategory
	{
		eBEGIN_EGiftCategory=0,
		EGC_SINGLEGAMEWIN = 1, // [�̱۰��ӽ�] �̱۰��ӽ�
		EGC_SINGLEGAMELOSE = 2, // [�̱۰�����] �̱۰�����
		EGC_MATCHGAMEWIN = 3, // [�������ӽ�] �������ӽ�
		EGC_MATCHGAMELOSE = 4, // [����������] ����������
		EGC_FRIENDGAMEWIN = 5, // [ģ�����ӽ�] ģ�����ӽ�
		EGC_FRIENDGAMELOSE = 6, // [ģ��������] ģ��������
		EGC_TRAININGWIN = 7, // [Ʈ���̴׽�] Ʈ���̴׽�
		EGC_TRAININGLOSE = 8, // [Ʈ���̴���] Ʈ���̴���
		eEND_EGiftCategory,
	}
	namespace nUtil
	{
		class jString_EGiftCategory
		{
			public static void Parse(string sDebug,string sVal, ref EGiftCategory eVal) 
			{
				eVal = (EGiftCategory)Enum.Parse(typeof(EGiftCategory), sVal);
			}
		}
	}


	public enum EGiftType
	{
		eBEGIN_EGiftType=0,
		EGT_NULL = 1, // [����] ����
		EGT_EXP = 2, // [����ġ] ����ġ
		EGT_GAMEMONEY = 3, // [���ӸӴ�] ���ӸӴ�
		EGT_PLAYERSKILLSTICKER = 4, // [��ų��ƼĿ] ��ų��ƼĿ
		EGT_PLAYERCARD = 5, // [�÷��̾�ī��] �÷��̾�ī��
		eEND_EGiftType,
	}
	namespace nUtil
	{
		class jString_EGiftType
		{
			public static void Parse(string sDebug,string sVal, ref EGiftType eVal) 
			{
				eVal = (EGiftType)Enum.Parse(typeof(EGiftType), sVal);
			}
		}
	}


	public enum EGradeAllitemType
	{
		eBEGIN_EGradeAllitemType=0,
		EGAT_NULL = 1, // [����] ����
		EGAT_SMAINITEMALL = 2, // [S�� ���ξ����� ���] S�� ���ξ����� ���
		EGAT_AMAINITEMALL = 3, // [A�� ���ξ����� ���] A�� ���ξ����� ���
		EGAT_BMAINITEMALL = 4, // [B�� ���ξ����� ���] B�� ���ξ����� ���
		EGAT_CMAINITEMALL = 5, // [C�� ���ξ����� ���] C�� ���ξ����� ���
		EGAT_DMAINITEMALL = 6, // [D�� ���ξ����� ���] D�� ���ξ����� ���
		EGAT_EMAINITEMALL = 7, // [E�� ���ξ����� ���] E�� ���ξ����� ���
		EGAT_SSUBITEMALL = 8, // [S�� ��������� ���] S�� ��������� ���
		EGAT_ASUBITEMALL = 9, // [A�� ��������� ���] A�� ��������� ���
		EGAT_BSUBITEMALL = 10, // [B�� ��������� ���] B�� ��������� ���
		EGAT_CSUBITEMALL = 11, // [C�� ��������� ���] C�� ��������� ���
		EGAT_DSUBITEMALL = 12, // [D�� ��������� ���] D�� ��������� ���
		EGAT_ESUBITEMALL = 13, // [E�� ��������� ���] E�� ��������� ���
		EGAT_SCONSUMEITEMALL = 14, // [S�� �Һ������ ���] S�� �Һ������ ���
		EGAT_ACONSUMEITEMALL = 15, // [A�� �Һ������ ���] A�� �Һ������ ���
		EGAT_BCONSUMEITEMALL = 16, // [B�� �Һ������ ���] B�� �Һ������ ���
		EGAT_CCONSUMEITEMALL = 17, // [C�� �Һ������ ���] C�� �Һ������ ���
		EGAT_DCONSUMEITEMALL = 18, // [D�� �Һ������ ���] D�� �Һ������ ���
		EGAT_ECONSUMEITEMALL = 19, // [E�� �Һ������ ���] E�� �Һ������ ���
		eEND_EGradeAllitemType,
	}
	namespace nUtil
	{
		class jString_EGradeAllitemType
		{
			public static void Parse(string sDebug,string sVal, ref EGradeAllitemType eVal) 
			{
				eVal = (EGradeAllitemType)Enum.Parse(typeof(EGradeAllitemType), sVal);
			}
		}
	}


	public enum EItemAbilityType
	{
		eBEGIN_EItemAbilityType=0,
		IAT_POWER = 1, // [�Ŀ�] �Ŀ�
		IAT_ACCURACY = 2, // [��Ȯ] ��Ȯ
		IAT_BALLCONTROL = 3, // [����] ����
		IAT_SPEED = 4, // [����] ����
		IAT_BREAKINGBALL = 5, // [��ȭ��] ��ȭ��
		IAT_ALLABILITY = 6, // [��罺��] ��罺��
		IAT_NULL = 7, // [����] ����
		eEND_EItemAbilityType,
	}
	namespace nUtil
	{
		class jString_EItemAbilityType
		{
			public static void Parse(string sDebug,string sVal, ref EItemAbilityType eVal) 
			{
				eVal = (EItemAbilityType)Enum.Parse(typeof(EItemAbilityType), sVal);
			}
		}
	}


	public enum EItemBuyType
	{
		eBEGIN_EItemBuyType=0,
		IBT_BUY_CASH = 1, // [ĳ�� ���� ������] ĳ�� ���� ������
		IBT_BUY_POINT = 2, // [����Ʈ ���� ������] ����Ʈ ���� ������
		IBT_BUY_USED = 3, // [ĳ���ͼӾ�����] ĳ��OR����Ʈ���ž������ε� �ͼӵȻ���
		IBT_EVENT = 4, // [�̺�Ʈ ���޾�����] �̺�Ʈ���޾�����
		IBT_REWARD = 5, // [��⺸�����ι���] Ʈ���̴� or ��⺸�� ���޾�����
		eEND_EItemBuyType,
	}
	namespace nUtil
	{
		class jString_EItemBuyType
		{
			public static void Parse(string sDebug,string sVal, ref EItemBuyType eVal) 
			{
				eVal = (EItemBuyType)Enum.Parse(typeof(EItemBuyType), sVal);
			}
		}
	}


	public enum EItemCategory
	{
		eBEGIN_EItemCategory=0,
		IC_EQUIP = 1, // [�������] �������
		IC_CONSUME = 2, // [�Ҹ������] �Ҹ������
		IC_STUFF = 3, // [��������] ��������
		eEND_EItemCategory,
	}
	namespace nUtil
	{
		class jString_EItemCategory
		{
			public static void Parse(string sDebug,string sVal, ref EItemCategory eVal) 
			{
				eVal = (EItemCategory)Enum.Parse(typeof(EItemCategory), sVal);
			}
		}
	}


	public enum EItemCategoryEquipment
	{
		eBEGIN_EItemCategoryEquipment=0,
		ICE_SHIRT = 1, // [����] ����
		ICE_PANT = 2, // [����] ����
		ICE_CAP = 3, // [����] ���� ���ξ�����#
		ICE_SHOES = 4, // [�Ź�] �Ź� ���ξ�����#
		ICE_GLOVE = 5, // [�����۷���] �����۷��� ���ξ�����#
		ICE_U_SHIRT = 6, // [�������] �������
		ICE_SOCKS = 7, // [�縻] �縻
		ICE_ARM_GUARDS = 8, // [��_��ȣ��] ��_��ȣ��
		ICE_LEG_GUARDS = 9, // [�ٸ�_��ȣ��] �ٸ�_��ȣ��
		ICE_BET = 10, // [��Ʈ] ��Ʈ ���ξ�����
		ICE_BALL = 11, // [��] �� ���ξ�����#
		ICE_HELMET = 12, // [���] ��� ���ξ�����#
		ICE_GLOBE = 13, // [Ÿ���尩] Ÿ�ڿ� �尩 ���ξ�����#
		ICE_WRISTBAND = 14, // [����Ʈ ���] �ո� �ƴ�
		ICE_NECKLACE = 15, // [�����] �����
		ICE_RING = 16, // [����] ����
		ICE_EARRING = 17, // [�Ͱ���] �Ͱ���
		ICE_TATOO = 18, // [����] ����
		ICE_SUNGLASS = 19, // [���۶�] ���۶�
		ICE_EYEPATCH = 20, // [������ġ] �� �� ��ġ
		ICE_BEARD = 21, // [����] ����
		ICE_HAIR_M = 22, // [������Ÿ��] ������Ÿ��
		ICE_HAIR_W = 23, // [������Ÿ��] ������Ÿ��
		ICE_HAIR_COLOR = 24, // [���Į��] ���Į��
		ICE_PATCH = 25, // [��ġ] ��ġ
		ICE_MASK = 26, // [����ũ] ����ũ
		ICE_BACKNUMBER = 27, // [���ȣ ������] ���ȣ ������
		ICE_MAKING = 28, // [��ŷ ������] ��ŷ ������
		eEND_EItemCategoryEquipment,
	}
	namespace nUtil
	{
		class jString_EItemCategoryEquipment
		{
			public static void Parse(string sDebug,string sVal, ref EItemCategoryEquipment eVal) 
			{
				eVal = (EItemCategoryEquipment)Enum.Parse(typeof(EItemCategoryEquipment), sVal);
			}
		}
	}


	public enum EItemGradeType
	{
		eBEGIN_EItemGradeType=0,
		IGT_E = 1, // [E���] E - EE �� ���۰���
		IGT_D = 2, // [D���] D - DE #  DD�� ���۰���
		IGT_C = 3, // [C���] C - CE # CD# CC�� ���۰���
		IGT_B = 4, // [B���] B- BE# BD# BC# BB�� ���۰���
		IGT_A = 5, // [A���] A- AE# AD# AC# AB# AA�� ���۰���
		IGT_S = 6, // [S���] S-SE# SD# SC# SB# SA# SS�� ���۰���
		IGT_NULL = 7, // [�����] ��޾���.  ���ڷ��̼� �����ۡ�
		eEND_EItemGradeType,
	}
	namespace nUtil
	{
		class jString_EItemGradeType
		{
			public static void Parse(string sDebug,string sVal, ref EItemGradeType eVal) 
			{
				eVal = (EItemGradeType)Enum.Parse(typeof(EItemGradeType), sVal);
			}
		}
	}


	public enum EItemPriceType
	{
		eBEGIN_EItemPriceType=0,
		IPT_CASH = 1, // [ĳ��] ĳ�� �θ� ����ִ� ������
		IPT_CASH_POINT = 2, // [ĳ��_����Ʈ] ĳ�� �Ǵ� ����Ʈ �� ��� �ִ� ������
		IPT_MONEY = 3, // [����Ʈ] ĳ�� �Ǵ� ����Ʈ# ���ӸӴϷ� ��� �ִ� ������
		eEND_EItemPriceType,
	}
	namespace nUtil
	{
		class jString_EItemPriceType
		{
			public static void Parse(string sDebug,string sVal, ref EItemPriceType eVal) 
			{
				eVal = (EItemPriceType)Enum.Parse(typeof(EItemPriceType), sVal);
			}
		}
	}


	public enum EItemReuseType
	{
		eBEGIN_EItemReuseType=0,
		IUT_NORMAL = 1, // [����] ����
		IUT_INSTANTLY = 2, // [�Ⱓ��] �Ⱓ�� Ƚ�� ���� �� ������ �� ���
		IUT_FIXED = 3, // [�Ұ�] �Ұ�
		eEND_EItemReuseType,
	}
	namespace nUtil
	{
		class jString_EItemReuseType
		{
			public static void Parse(string sDebug,string sVal, ref EItemReuseType eVal) 
			{
				eVal = (EItemReuseType)Enum.Parse(typeof(EItemReuseType), sVal);
			}
		}
	}


	public enum EItemSellStatus
	{
		eBEGIN_EItemSellStatus=0,
		ISS_SELL_STOP = 1, // [�Ǹ�����] �Ǹ�����( �Ǹ��ϴٰ� ��å�� ���� ������)
		ISS_SELL = 2, // [�Ǹ���] �Ǹ���
		ISS_SELL_PLAN = 3, // [�Ǹſ���] �Ǹſ���
		eEND_EItemSellStatus,
	}
	namespace nUtil
	{
		class jString_EItemSellStatus
		{
			public static void Parse(string sDebug,string sVal, ref EItemSellStatus eVal) 
			{
				eVal = (EItemSellStatus)Enum.Parse(typeof(EItemSellStatus), sVal);
			}
		}
	}


	public enum EItemSexType
	{
		eBEGIN_EItemSexType=0,
		IST_MAN_ONLY = 1, // [��] 
		IST_WOMAN_ONLY = 2, // [��] 
		IST_COMMON = 3, // [����] 
		eEND_EItemSexType,
	}
	namespace nUtil
	{
		class jString_EItemSexType
		{
			public static void Parse(string sDebug,string sVal, ref EItemSexType eVal) 
			{
				eVal = (EItemSexType)Enum.Parse(typeof(EItemSexType), sVal);
			}
		}
	}


	public enum EItemState
	{
		eBEGIN_EItemState=0,
		IS_NORMAL = 1, // [�Ϲݻ���] �Ϲݻ���
		IS_DELETE = 2, // [�����Ȼ���] �����Ȼ���
		IS_ADMIN_BLOCKED = 3, // [���Ұ���.] ���Ұ���.
		IS_DELETE_REFUND = 4, // [���ȱ�Ǿ� ������] ���ȱ�Ǿ� ������
		eEND_EItemState,
	}
	namespace nUtil
	{
		class jString_EItemState
		{
			public static void Parse(string sDebug,string sVal, ref EItemState eVal) 
			{
				eVal = (EItemState)Enum.Parse(typeof(EItemState), sVal);
			}
		}
	}


	public enum EItemUpgradeResult
	{
		eBEGIN_EItemUpgradeResult=0,
		IUR_HELMET = 1, // [���] ���
		IUR_CAP = 2, // [����] ����
		IUR_BET = 3, // [��Ʈ] ��Ʈ
		IUR_BALL = 4, // [��] ��
		IUR_GLOBE = 5, // [Ÿ���尩] Ÿ���尩
		IUR_GLOVE = 6, // [�۷���] �۷���
		IUR_SHOES = 7, // [�Ź�] �Ź�
		eEND_EItemUpgradeResult,
	}
	namespace nUtil
	{
		class jString_EItemUpgradeResult
		{
			public static void Parse(string sDebug,string sVal, ref EItemUpgradeResult eVal) 
			{
				eVal = (EItemUpgradeResult)Enum.Parse(typeof(EItemUpgradeResult), sVal);
			}
		}
	}


	public enum ELogType
	{
		eBEGIN_ELogType=0,
		SCT_KINGROOKIE = 1, // [�α�1] �α�1
		SCT_ROOKIE = 2, // [�α�2] �α�2
		SCT_AMA1 = 3, // [�α�3] �α�3
		SCT_AMA2 = 4, // [�α�4] �α�4
		SCT_PRO = 5, // [�α�5] �α�5
		eEND_ELogType,
	}
	namespace nUtil
	{
		class jString_ELogType
		{
			public static void Parse(string sDebug,string sVal, ref ELogType eVal) 
			{
				eVal = (ELogType)Enum.Parse(typeof(ELogType), sVal);
			}
		}
	}


	public enum ENoticeType
	{
		eBEGIN_ENoticeType=0,
		NT_LED = 1, // [������] ������
		NT_CHECK = 2, // [�ӽ�����] �ӽ�����
		NT_NOTICE = 3, // [��������] ��������
		eEND_ENoticeType,
	}
	namespace nUtil
	{
		class jString_ENoticeType
		{
			public static void Parse(string sDebug,string sVal, ref ENoticeType eVal) 
			{
				eVal = (ENoticeType)Enum.Parse(typeof(ENoticeType), sVal);
			}
		}
	}


	public enum EPitcherAbility
	{
		eBEGIN_EPitcherAbility=0,
		PA_NULL = 1, // [����] ����
		PA_LEFT = 2, // [����Ÿ��] ��Ÿ�ڻ��� �ɷ�ġ����
		PA_RIGHT = 3, // [���Ÿ��] ��Ÿ�ڻ��� �ɷ�ġ����
		PA_FASTBALL = 4, // [�ӱ���] ���� ����
		PA_FULLSKILL = 5, // [�ⱳ��] ��ȭ�� �� ����
		PA_RUNFIRE = 6, // [����] �ٷ� ���� Ÿ������ ��Ʈ���� ������  ���� �� ���� ����
		PA_SWORDCON = 7, // [Į����] ���� ������ ���� �ٿ� ����
		PA_DOCK = 8, // [����K] 2���� ��Ʈ���� ������ ���� �� ���� ����
		PA_INFIGHT = 9, // [��������] Ÿ���� �������� ���� ������ ���� ����
		PA_OUTFIGHT = 10, // [�ƿ�������] Ÿ���� �ٱ������� ���� ������ ���� ����
		eEND_EPitcherAbility,
	}
	namespace nUtil
	{
		class jString_EPitcherAbility
		{
			public static void Parse(string sDebug,string sVal, ref EPitcherAbility eVal) 
			{
				eVal = (EPitcherAbility)Enum.Parse(typeof(EPitcherAbility), sVal);
			}
		}
	}


	public enum EPitcherForm
	{
		eBEGIN_EPitcherForm=0,
		PF_OVER = 1, // [����] ����
		PF_THREEQUARTER = 2, // [��������] ��������
		PF_SIDEARM = 3, // [���̵��] ���̵��
		PF_UNDER = 4, // [���] ���
		PF_NULL = 5, // [����] ����
		eEND_EPitcherForm,
	}
	namespace nUtil
	{
		class jString_EPitcherForm
		{
			public static void Parse(string sDebug,string sVal, ref EPitcherForm eVal) 
			{
				eVal = (EPitcherForm)Enum.Parse(typeof(EPitcherForm), sVal);
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


	public enum EPlayerBodyType
	{
		eBEGIN_EPlayerBodyType=0,
		EPBT_SMALL = 1, // [����] ����
		EPBT_MIDIUM = 2, // [�̵��] �̵��
		EPBT_LARGE = 3, // [����] ����
		EPBT_WOMAN = 4, // [����] ����
		eEND_EPlayerBodyType,
	}
	namespace nUtil
	{
		class jString_EPlayerBodyType
		{
			public static void Parse(string sDebug,string sVal, ref EPlayerBodyType eVal) 
			{
				eVal = (EPlayerBodyType)Enum.Parse(typeof(EPlayerBodyType), sVal);
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
		PBB_SINKER = 24, // [��Ŀ_ ��ũ��] ��Ŀ#  ��ũ��
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


	public enum EPlayerGradeType
	{
		eBEGIN_EPlayerGradeType=0,
		PGT_E = 1, // [E���] E��� ����
		PGT_D = 2, // [D���] D��� ����
		PGT_C = 3, // [C���] C��� ����
		PGT_B = 4, // [B���] B��� ����
		PGT_A = 5, // [A���] A��� ����
		PGT_S = 6, // [S���] S��� ����
		eEND_EPlayerGradeType,
	}
	namespace nUtil
	{
		class jString_EPlayerGradeType
		{
			public static void Parse(string sDebug,string sVal, ref EPlayerGradeType eVal) 
			{
				eVal = (EPlayerGradeType)Enum.Parse(typeof(EPlayerGradeType), sVal);
			}
		}
	}


	public enum EPlayerNationType
	{
		eBEGIN_EPlayerNationType=0,
		PNT_KOREA = 1, // [�ѱ�] �ѱ�
		PNT_USA = 2, // [�̱�] �̱�
		PNT_JAPAN = 3, // [�Ϻ�] �Ϻ�
		PNT_CHINA = 4, // [�߱�] �߱�
		eEND_EPlayerNationType,
	}
	namespace nUtil
	{
		class jString_EPlayerNationType
		{
			public static void Parse(string sDebug,string sVal, ref EPlayerNationType eVal) 
			{
				eVal = (EPlayerNationType)Enum.Parse(typeof(EPlayerNationType), sVal);
			}
		}
	}


	public enum EPlayerType
	{
		eBEGIN_EPlayerType=0,
		PT_BETTER = 1, // [Ÿ��] Ÿ��
		PT_PITCHER = 2, // [����] ����
		PT_COMMON = 3, // [����] Ÿ���������о���
		eEND_EPlayerType,
	}
	namespace nUtil
	{
		class jString_EPlayerType
		{
			public static void Parse(string sDebug,string sVal, ref EPlayerType eVal) 
			{
				eVal = (EPlayerType)Enum.Parse(typeof(EPlayerType), sVal);
			}
		}
	}


	public enum EQuestConditionType
	{
		eBEGIN_EQuestConditionType=0,
		QCT_NULL = 1, // [����] ����
		QCT_SINGLEGAMEWINCOUNT = 2, // [�̱۰��¼�����] Sys_Quest�� condition_value�� �ִ� ����ŭ �̰�ٸ� ����Ʈ ����
		QCT_MATCHGAMEWINCOUNT = 3, // [�������¼�����] ������⿡�� condition_value��ŭ�̰�ٸ� ����
		QCT_FRIENDGAMEWINCOUNT = 4, // [ģ�����¼�����] ��ϵ� ģ���� ����� condition_value��ŭ �̰�ٸ� ����
		QCT_SINGELGAMECOUNT = 5, // [�̱۰��Ƚ������] �̱۰��Ƚ���� value��ŭ �Ǿ����� ����
		QCT_MATCHGAMECOUNT = 6, // [�������Ƚ������] �������Ƚ���� value��ŭ �Ǿ����� ����
		QCT_FRIENDGAMECOUNT = 7, // [ģ�����Ƚ������] ��ϵ� ģ������ ���Ƚ���� value��ŭ �Ǿ����� ����
		QCT_PLAYERLEVELCOUNT = 8, // [�����޼�����] �����޼�����
		QCT_PLAYERCHARACTERCOUNT = 9, // [ĳ���ͻ�������] ĳ���ͻ�������
		QCT_MATCHHOMERUNCOUNT = 10, // [����Ȩ��Ƚ������] ����Ȩ��Ƚ������
		QCT_MATCHSTRIKEOUTCOUNT = 11, // [����Ż����Ƚ������] ����Ż����Ƚ������
		QCT_EQUIPGRADETYPE = 12, // [��ü�����������] ��ü������������� condition1�� �ִ� ���� ����(EItemGradeType)�� �ش��ϸ� ������ �ش�
		QCT_CASHCOUNT = 13, // [ĳ���۱�������] ĳ���۱�������
		QCT_GAMEMONEYCOUNT = 14, // [���ӸӴϴ�������] ���ӸӴϴ�������
		QCT_PLAYERALLSTATCOUNT = 15, // [ĳ���͸��ɷ�ġ�޼�����] ĳ���͸��ɷ�ġ�޼�����
		eEND_EQuestConditionType,
	}
	namespace nUtil
	{
		class jString_EQuestConditionType
		{
			public static void Parse(string sDebug,string sVal, ref EQuestConditionType eVal) 
			{
				eVal = (EQuestConditionType)Enum.Parse(typeof(EQuestConditionType), sVal);
			}
		}
	}


	public enum EShopBetterSection
	{
		eBEGIN_EShopBetterSection=0,
		ESBS_NULL = 1, // [����] ����
		ESBS_A = 2, // [���� A] ���� ���� A(Ÿ��=���)
		ESBS_B = 3, // [���� B] ���� ���� B(Ÿ��=��Ʈ)
		ESBS_C = 4, // [���� C] ���� ���� C(Ÿ��=�尩)
		ESBS_D = 5, // [���� D] ���� ���� D(Ÿ��=�Ź�)
		ESBS_E = 6, // [���� E] ���� ���� E(Ÿ��=����#  ����)
		ESBS_F = 7, // [���� F] ���� ���� F(Ÿ��=�縻#  ����Ʈ���)
		ESBS_G = 8, // [���� G] ���� ���� G(Ÿ��=�Ⱥ�ȣ��#  �ٸ���ȣ��)
		ESBS_H = 9, // [���� H] ���� ���� H(Ÿ��=�����# ����#  �Ͱ���)
		ESBS_I = 10, // [���� I] ���� ���� I(Ÿ��=(����#  ���۶�#  ������ġ)
		ESBS_J = 11, // [���� J] ���� ���� J(Ÿ��=(����#  ���#  ��ġ#  ����ũ#  ���ȣ#  ��ŷ#  ����÷�)
		eEND_EShopBetterSection,
	}
	namespace nUtil
	{
		class jString_EShopBetterSection
		{
			public static void Parse(string sDebug,string sVal, ref EShopBetterSection eVal) 
			{
				eVal = (EShopBetterSection)Enum.Parse(typeof(EShopBetterSection), sVal);
			}
		}
	}


	public enum EShopConsumeSection
	{
		eBEGIN_EShopConsumeSection=0,
		ESCS_NULL = 1, // [����] ����
		ESCS_A = 2, // [���� A] ���� ���� A(�Һ�=���� ������)
		ESCS_B = 3, // [���� B] ���� ���� B(�Һ�=���� ������� ������)
		ESCS_C = 4, // [���� C] ���� ���� C(�Һ�=���׷��̵� ���� ������)
		ESCS_D = 5, // [���� D] ���� ���� D(�Һ�=������ ���� ����#  ��ȭ ��� ������)
		ESCS_E = 6, // [���� E] ���� ���� E(�Һ�=��Ű�� ������)
		eEND_EShopConsumeSection,
	}
	namespace nUtil
	{
		class jString_EShopConsumeSection
		{
			public static void Parse(string sDebug,string sVal, ref EShopConsumeSection eVal) 
			{
				eVal = (EShopConsumeSection)Enum.Parse(typeof(EShopConsumeSection), sVal);
			}
		}
	}


	public enum EShopItemType
	{
		eBEGIN_EShopItemType=0,
		SIT_Sys_Package = 1, // [��Ű��] ��Ű��
		SIT_Sys_ItemEquip = 2, // [����������] ����������
		SIT_Sys_ItemStuff = 3, // [��������] ��������
		SIT_Sys_ItemConsume = 4, // [�Ҹ������] �Ҹ������
		SIT_Sys_PlayerSkillSticker = 5, // [��ȭ��������] ��ȭ��������(��ȭ�� ���� �� ��ȭ���� ���ѵǾ��ִ� ���� �����ϰ� ���� ����#  ��ȭ�� ���׷��̵�--)���� ��ȭ�� ����� ����(--�� �״�� ����)
		eEND_EShopItemType,
	}
	namespace nUtil
	{
		class jString_EShopItemType
		{
			public static void Parse(string sDebug,string sVal, ref EShopItemType eVal) 
			{
				eVal = (EShopItemType)Enum.Parse(typeof(EShopItemType), sVal);
			}
		}
	}


	public enum EShopPitcherSection
	{
		eBEGIN_EShopPitcherSection=0,
		ESPS_NULL = 1, // [����] ����
		ESPS_A = 2, // [���� A] ���� ���� A(����=����)
		ESPS_B = 3, // [���� B] ���� ���� B(����=��)
		ESPS_C = 4, // [���� C] ���� ���� C(����=�۷���)
		ESPS_D = 5, // [���� D] ���� ���� D(����=�Ź�)
		ESPS_E = 6, // [���� E] ���� ���� E(����=����#  ����)
		ESPS_F = 7, // [���� F] ���� ���� E(����=�縻#  ����Ʈ���)
		ESPS_G = 8, // [���� G] ���� ���� F (����=�����# ����#  �Ͱ���)
		ESPS_H = 9, // [���� H] ���� ���� H(����=����#  ���۶�#  ������ġ)
		ESPS_I = 10, // [���� I] ���� ���� I(����=����#  ���#  ��ġ#  ����ũ#  ���ȣ#  ��ŷ#  ����÷�)
		eEND_EShopPitcherSection,
	}
	namespace nUtil
	{
		class jString_EShopPitcherSection
		{
			public static void Parse(string sDebug,string sVal, ref EShopPitcherSection eVal) 
			{
				eVal = (EShopPitcherSection)Enum.Parse(typeof(EShopPitcherSection), sVal);
			}
		}
	}


	public enum ETotalGameType
	{
		eBEGIN_ETotalGameType=0,
		TGT_Match = 1, // [��ġ] ��ġ
		TGT_Single = 2, // [�̱�] �̱�
		TGT_Friendly = 3, // [�����鸮] �����鸮
		eEND_ETotalGameType,
	}
	namespace nUtil
	{
		class jString_ETotalGameType
		{
			public static void Parse(string sDebug,string sVal, ref ETotalGameType eVal) 
			{
				eVal = (ETotalGameType)Enum.Parse(typeof(ETotalGameType), sVal);
			}
		}
	}


	


}//namespace nEXCEL
