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

	public enum EBetterHitType
	{
		eBEGIN_EBetterHitType=0,
		EBHT_OUT = 1, // [�ƿ�] �ƿ�
		EBHT_ONEHIT = 2, // [�Ϸ�Ÿ] �Ϸ�Ÿ
		EBHT_DOUBLEHIT = 3, // [�̷�Ÿ] �̷�Ÿ
		EBHT_TRIPLEHIT = 4, // [���Ÿ] ���Ÿ
		EBHT_SINGLEHOMERUN = 5, // [�̱�Ȩ��] �̱�Ȩ��
		EBHT_TWORUNHOMERUN = 6, // [����Ȩ��] ����Ȩ��
		EBHT_THREERUNHOMERUN = 7, // [������Ȩ��] ������Ȩ��
		EBHT_GRANDSLAMHOMERUN = 8, // [����Ȩ��] ����Ȩ��
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
		IBT_CHARGE_POINT = 2, // [����Ʈ ���� ������] ����Ʈ ���� ������
		IBT_BUY_POINT = 3, // [����Ʈ ���� ������] ����Ʈ ���� ������
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
		IC_NULL = 1, // [����] ����
		IC_EQUIPMENT = 2, // [�������] �������
		IC_CONSUME = 3, // [�Ҹ������] �Ҹ������
		IC_STUFF = 4, // [��������] ��������
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
		ICE_CAP = 3, // [����] ���� ���ξ�����,
		ICE_SHOES = 4, // [�Ź�] �Ź� ���ξ�����,
		ICE_GLOVE = 5, // [�����۷���] �����۷��� ���ξ�����,
		ICE_U_SHIRT = 6, // [�������] �������
		ICE_SOCKS = 7, // [�縻] �縻
		ICE_ARM_GUARDS = 8, // [��_��ȣ��] ��_��ȣ��
		ICE_LEG_GUARDS = 9, // [�ٸ�_��ȣ��] �ٸ�_��ȣ��
		ICE_BET = 10, // [��Ʈ] ��Ʈ ���ξ�����
		ICE_BALL = 11, // [��] �� ���ξ�����,
		ICE_HELMET = 12, // [���] ��� ���ξ�����,
		ICE_GLOBE = 13, // [Ÿ���尩] Ÿ�ڿ� �尩 ���ξ�����,
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
		ICE_PATCH = 24, // [��ġ] ��ġ
		ICE_MASK = 25, // [����ũ] ����ũ
		ICE_BACKNUMBER = 26, // [���ȣ ������] ���ȣ ������
		ICE_MAKING = 27, // [��ŷ ������] ��ŷ ������
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
		IGT_D = 2, // [D���] D - DE , DD�� ���۰���
		IGT_C = 3, // [C���] C - CE ,CD,CC�� ���۰���
		IGT_B = 4, // [B���] B- BE,BD,BC,BB�� ���۰���
		IGT_A = 5, // [A���] A- AE,AD,AC,AB,AA�� ���۰���
		IGT_S = 6, // [S���] S-SE,SD,SC,SB,SA,SS�� ���۰���
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
		IPT_MONEY = 3, // [����Ʈ] ĳ�� �Ǵ� ����Ʈ,���ӸӴϷ� ��� �ִ� ������
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


	public enum EplayerBadyType
	{
		eBEGIN_EplayerBadyType=0,
		EBT_SMALL = 1, // [����] ����, ������ �����϶��� ������ �����̴�.
		EBT_MIDIUM = 2, // [�̵��] �̵��
		EBT_LARGE = 3, // [����] ����
		eEND_EplayerBadyType,
	}
	namespace nUtil
	{
		class jString_EplayerBadyType
		{
			public static void Parse(string sDebug,string sVal, ref EplayerBadyType eVal) 
			{
				eVal = (EplayerBadyType)Enum.Parse(typeof(EplayerBadyType), sVal);
			}
		}
	}


	public enum EPlayerBetterSkill
	{
		eBEGIN_EPlayerBetterSkill=0,
		PBS_NULL = 1, // [����] ����
		PBS_LEFT = 2, // [��������] ���������� �Ŀ� ����
		PBS_RIGHT = 3, // [�������] ������� ���� �Ŀ� ����
		PBS_HOMERUN = 4, // [Ȩ��Ÿ��] ��Ʈ�� �Ŀ� ����
		PBS_WIDE = 5, // [����Ÿ��] ����Ÿ�� - �о������� �Ŀ� �ٿ����
		PBS_FULLHIT = 6, // [Ǯ����] Ǯ���� - ��������� �Ŀ� ����
		PBS_LOWHIT = 7, // [�κ�����] �κ����� - Ÿ�������� �ϴ�/�ߴܿ��� �Ŀ� ����
		PBS_HIGHHIT = 8, // [���̺�����] ���̺����� - �ߴ�,��ܿ��� �Ŀ� ����
		PBS_RUNFIRE = 9, // [����] ���� - �ٷ� ����Ÿ������ Ȩ���� �Ŀ� ����
		eEND_EPlayerBetterSkill,
	}
	namespace nUtil
	{
		class jString_EPlayerBetterSkill
		{
			public static void Parse(string sDebug,string sVal, ref EPlayerBetterSkill eVal) 
			{
				eVal = (EPlayerBetterSkill)Enum.Parse(typeof(EPlayerBetterSkill), sVal);
			}
		}
	}


	public enum EPlayerGradeType
	{
		eBEGIN_EPlayerGradeType=0,
		PGT_E = 1, // [E���] E��� �÷��̾� ī��
		PGT_D = 2, // [D���] D��� �÷��̾� ī��
		PGT_C = 3, // [C���] C��� �÷��̾� ī��
		PGT_B = 4, // [B���] B��� �÷��̾� ī��
		PGT_A = 5, // [A���] A��� �÷��̾� ī��
		PGT_S = 6, // [S���] S��� �÷��̾� ī��
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


	public enum EPlayerPitcherSkill
	{
		eBEGIN_EPlayerPitcherSkill=0,
		PPS_NULL = 1, // [����] ����
		PPS_LEFT = 2, // [����Ÿ��] ��Ÿ�ڻ��� �ɷ�ġ����
		PPS_RIGHT = 3, // [���Ÿ��] ��Ÿ�ڻ��� �ɷ�ġ����
		PPS_FASTBALL = 4, // [�ӱ���] ���� ����
		PPS_FULLSKILL = 5, // [�ⱳ��] ��ȭ�� �� ����
		PPS_RUNFIRE = 6, // [����] �ٷ� ���� Ÿ������ ��Ʈ���� ������  ���� �� ���� ����
		PPS_SWORDCON = 7, // [Į����] ���� ������ ���� �ٿ� ����
		PPS_DOCK = 8, // [����K] 2���� ��Ʈ���� ������ ���� �� ���� ����
		PPS_INFIGHT = 9, // [��������] Ÿ���� �������� ���� ������ ���� ����
		PPS_OUTFIGHT = 10, // [�ƿ�������] Ÿ���� �ٱ������� ���� ������ ���� ����
		eEND_EPlayerPitcherSkill,
	}
	namespace nUtil
	{
		class jString_EPlayerPitcherSkill
		{
			public static void Parse(string sDebug,string sVal, ref EPlayerPitcherSkill eVal) 
			{
				eVal = (EPlayerPitcherSkill)Enum.Parse(typeof(EPlayerPitcherSkill), sVal);
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

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys__ItemBase
	{
		public Sys__ItemBase_id_t m_sid; 	// [�����ĺ�ID]  
		public string m_name; 	// [�̸�] �����̸� �����ؾ���. �� �����̸����� ��Ʈ�����̺��� �ѱ��̸��˻� 
		public EItemCategory m_category; 	// [��з�]  
		public bool m_upgrade_type; 	// [���׷��̵� ���� ����] ���׷��̵尡 ���������� ���� 
		public bool m_is_visual; 	// [�����] ȭ�鿡 ���������� �Ⱥ��������� ���� 
		public string m_help; 	// [����]  
		public EItemGradeType m_grade; 	// [���] ������ ���׷��̵� ��� 
		public EItemPriceType m_price_type; 	// [����Ÿ��]  
		public Int32 m_price_money; 	// [�ʿ���ӸӴ�]  
		public Int32 m_price_cash; 	// [�ʿ丮��ĳ��]  
		public EItemSellStatus m_sell_status; 	// [�ǸŻ���]  
		public DATETIME m_sell_start_date; 	// [�Ǹ� ���� �Ͻ�] �Ǹ� ���� �Ͻ� 
		public DATETIME m_sell_end_date; 	// [�Ǹ� ���� �Ͻ�] �Ǹ� ���� �Ͻ� 
		public player_level_t m_player_level_min; 	// [��뷹��MIN] ������ �� 110���� ���� 
		public player_level_t m_player_level_max; 	// [��뷹��MAX] ������ �� 110���� ���� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys__ItemBase::sid",token[idx++], ref m_sid);
			nUtil.jString_string.Parse("Sys__ItemBase::name",token[idx++], ref m_name);
			nUtil.jString_EItemCategory.Parse("Sys__ItemBase::category",token[idx++], ref m_category);
			nUtil.jString_bool.Parse("Sys__ItemBase::upgrade_type",token[idx++], ref m_upgrade_type);
			nUtil.jString_bool.Parse("Sys__ItemBase::is_visual",token[idx++], ref m_is_visual);
			nUtil.jString_string.Parse("Sys__ItemBase::help",token[idx++], ref m_help);
			nUtil.jString_EItemGradeType.Parse("Sys__ItemBase::grade",token[idx++], ref m_grade);
			nUtil.jString_EItemPriceType.Parse("Sys__ItemBase::price_type",token[idx++], ref m_price_type);
			nUtil.jString_Int32.Parse("Sys__ItemBase::price_money",token[idx++], ref m_price_money);
			nUtil.jString_Int32.Parse("Sys__ItemBase::price_cash",token[idx++], ref m_price_cash);
			nUtil.jString_EItemSellStatus.Parse("Sys__ItemBase::sell_status",token[idx++], ref m_sell_status);
			nUtil.jString_DATETIME.Parse("Sys__ItemBase::sell_start_date",token[idx++], ref m_sell_start_date);
			nUtil.jString_DATETIME.Parse("Sys__ItemBase::sell_end_date",token[idx++], ref m_sell_end_date);
			nUtil.jString_Int32.Parse("Sys__ItemBase::player_level_min",token[idx++], ref m_player_level_min);
			nUtil.jString_Int32.Parse("Sys__ItemBase::player_level_max",token[idx++], ref m_player_level_max);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_sid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_category.ToString() + ",";
			output += m_upgrade_type.ToString() + ",";
			output += m_is_visual.ToString() + ",";
			output += m_help.ToString() + ",";
			output += m_grade.ToString() + ",";
			output += m_price_type.ToString() + ",";
			output += m_price_money.ToString() + ",";
			output += m_price_cash.ToString() + ",";
			output += m_sell_status.ToString() + ",";
			output += m_sell_start_date.ToString() + ",";
			output += m_sell_end_date.ToString() + ",";
			output += m_player_level_min.ToString() + ",";
			output += m_player_level_max.ToString() + ",";
			return output;
		}
	}//class Sys__ItemBase

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys__Base_PlayerStat
	{
		public Int16 m_sid; 	// [�����ĺ�ID]  
		public string m_name; 	// [�̸�] �����̸� �����ؾ���. �̿����̸����� ��Ʈ�����̺��� �ѱ��̸��˻� 
		public Int16 m_better_power; 	// [Ÿ�� �Ŀ�]  
		public Int16 m_better_focus; 	// [Ÿ�� ����]  
		public Int16 m_pitcher_control; 	// [���� ����]  
		public Int16 m_pitcher_ballspeed; 	// [���� ����] ������ ���ڴ� ���̳ʽ��� ���� 
		public Int16 m_pitcher_breakingball_value; 	// [���� ��ȭ�� ��ġ]  
		public EPlayerBreakingBall m_pitcher_breakingball_type; 	// [���� ��ȭ������] ���� ��ȭ�� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int16.Parse("Sys__Base_PlayerStat::sid",token[idx++], ref m_sid);
			nUtil.jString_string.Parse("Sys__Base_PlayerStat::name",token[idx++], ref m_name);
			nUtil.jString_Int16.Parse("Sys__Base_PlayerStat::better_power",token[idx++], ref m_better_power);
			nUtil.jString_Int16.Parse("Sys__Base_PlayerStat::better_focus",token[idx++], ref m_better_focus);
			nUtil.jString_Int16.Parse("Sys__Base_PlayerStat::pitcher_control",token[idx++], ref m_pitcher_control);
			nUtil.jString_Int16.Parse("Sys__Base_PlayerStat::pitcher_ballspeed",token[idx++], ref m_pitcher_ballspeed);
			nUtil.jString_Int16.Parse("Sys__Base_PlayerStat::pitcher_breakingball_value",token[idx++], ref m_pitcher_breakingball_value);
			nUtil.jString_EPlayerBreakingBall.Parse("Sys__Base_PlayerStat::pitcher_breakingball_type",token[idx++], ref m_pitcher_breakingball_type);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_sid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_better_power.ToString() + ",";
			output += m_better_focus.ToString() + ",";
			output += m_pitcher_control.ToString() + ",";
			output += m_pitcher_ballspeed.ToString() + ",";
			output += m_pitcher_breakingball_value.ToString() + ",";
			output += m_pitcher_breakingball_type.ToString() + ",";
			return output;
		}
	}//class Sys__Base_PlayerStat

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_ItemEquip
			: Sys__ItemBase
	{
		public EItemCategoryEquipment m_equip_category; 	// [��������ī�װ�] ��������ī�װ� 
		public EItemSexType m_sex_type; 	// [�����۳�������] �������� 
		public EPlayerType m_player_type; 	// [Ÿ����������] Ÿ���������� 
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_EItemCategoryEquipment.Parse("Sys_ItemEquip::equip_category",token[idx++], ref m_equip_category);
			nUtil.jString_EItemSexType.Parse("Sys_ItemEquip::sex_type",token[idx++], ref m_sex_type);
			nUtil.jString_EPlayerType.Parse("Sys_ItemEquip::player_type",token[idx++], ref m_player_type);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_equip_category.ToString() + ",";
			output += m_sex_type.ToString() + ",";
			output += m_player_type.ToString() + ",";
			return output;
		}
	}//class Sys_ItemEquip

	namespace nUtil
	{
		class jString_Sys_ItemEquip
		{
			public static string ToString(Sys_ItemEquip o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_ItemEquip> sysList)
			{
				string output = "";
				foreach (Sys_ItemEquip o in sysList)
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
				Sys_ItemEquip o = (Sys_ItemEquip)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_ItemEquip o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_ItemEquip.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_ItemEquip.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_ItemEquip> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_ItemEquip> sysList = (List<Sys_ItemEquip>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_ItemEquip o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_ItemEquip.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_ItemEquip.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_ItemEquip
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_ItemConsume
			: Sys__ItemBase
	{
		public EPlayerType m_player_type; 	// [Ÿ����������] Ÿ���������� 
		public EConsumeItemEffect m_consume_item_effect; 	// [����������ȿ��] ���������� �Һ� �� ȿ�� ���� 
		public EItemAbilityType m_Item_Ability_Type; 	// [�����ۿ��⽺��] ���������ۿ��⽺�� 
		public Int16 m_consume_item_effect_value; 	// [����������ȿ����] �� �ش� ������ ȿ���� ��(�������� ȿ�� ���� ���� �ٸ�-->) 
		public Int16 m_gameplay_effect_repeat; 	// [���� �÷��̽� ����ȿ�� ����(Ƚ��)] ���� �÷��̽� ����ȿ�� ����(Ƚ��) 
		public Int16 m_gameplay_effect_time; 	// [���� �÷��̽� ����ȿ�� ����(�ð�)] ���� �÷��̽� ����ȿ�� ����(�ð�) 
		public bool m_consume_item_overlap; 	// [�ٸ������۰� �ߺ���� ����] �ٸ������۰� �ߺ���� ���� 
		public Int16 m_use_count; 	// [��� Ƚ��] ��� Ƚ�� 
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_EPlayerType.Parse("Sys_ItemConsume::player_type",token[idx++], ref m_player_type);
			nUtil.jString_EConsumeItemEffect.Parse("Sys_ItemConsume::consume_item_effect",token[idx++], ref m_consume_item_effect);
			nUtil.jString_EItemAbilityType.Parse("Sys_ItemConsume::Item_Ability_Type",token[idx++], ref m_Item_Ability_Type);
			nUtil.jString_Int16.Parse("Sys_ItemConsume::consume_item_effect_value",token[idx++], ref m_consume_item_effect_value);
			nUtil.jString_Int16.Parse("Sys_ItemConsume::gameplay_effect_repeat",token[idx++], ref m_gameplay_effect_repeat);
			nUtil.jString_Int16.Parse("Sys_ItemConsume::gameplay_effect_time",token[idx++], ref m_gameplay_effect_time);
			nUtil.jString_bool.Parse("Sys_ItemConsume::consume_item_overlap",token[idx++], ref m_consume_item_overlap);
			nUtil.jString_Int16.Parse("Sys_ItemConsume::use_count",token[idx++], ref m_use_count);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_player_type.ToString() + ",";
			output += m_consume_item_effect.ToString() + ",";
			output += m_Item_Ability_Type.ToString() + ",";
			output += m_consume_item_effect_value.ToString() + ",";
			output += m_gameplay_effect_repeat.ToString() + ",";
			output += m_gameplay_effect_time.ToString() + ",";
			output += m_consume_item_overlap.ToString() + ",";
			output += m_use_count.ToString() + ",";
			return output;
		}
	}//class Sys_ItemConsume

	namespace nUtil
	{
		class jString_Sys_ItemConsume
		{
			public static string ToString(Sys_ItemConsume o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_ItemConsume> sysList)
			{
				string output = "";
				foreach (Sys_ItemConsume o in sysList)
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
				Sys_ItemConsume o = (Sys_ItemConsume)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_ItemConsume o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_ItemConsume.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_ItemConsume.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_ItemConsume> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_ItemConsume> sysList = (List<Sys_ItemConsume>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_ItemConsume o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_ItemConsume.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_ItemConsume.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_ItemConsume
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_ItemStuff
			: Sys__ItemBase
	{
		public EItemUpgradeResult m_item_upgrade_result; 	// [���׷��̵� ������ �����]  
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_EItemUpgradeResult.Parse("Sys_ItemStuff::item_upgrade_result",token[idx++], ref m_item_upgrade_result);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_item_upgrade_result.ToString() + ",";
			return output;
		}
	}//class Sys_ItemStuff

	namespace nUtil
	{
		class jString_Sys_ItemStuff
		{
			public static string ToString(Sys_ItemStuff o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_ItemStuff> sysList)
			{
				string output = "";
				foreach (Sys_ItemStuff o in sysList)
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
				Sys_ItemStuff o = (Sys_ItemStuff)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_ItemStuff o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_ItemStuff.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_ItemStuff.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_ItemStuff> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_ItemStuff> sysList = (List<Sys_ItemStuff>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_ItemStuff o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_ItemStuff.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_ItemStuff.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_ItemStuff
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_MainItemAbility
	{
		public Int16 m_sid; 	// [������ȣ] ������ȣ 
		public EItemCategoryEquipment m_equip_category; 	// [��������ī�װ�] ��������ī�װ� 
		public string m_name; 	// [���׷��̵�ܰ�] EE SS SA �� 
		public Int16 m_mainitem_first_equip_level; 	// [���������� ���� ����] ������ ���� ���� ���� 
		public Int16 m_mainitem_possible_upgrade_level; 	// [�����۰�ȭ ���� ����] ������ ��ȭ ���� ���� 
		public Int16 m_mainitem_need_time; 	// [�����۰�ȭ �ʿ� �ð�] ������ ��ȭ �ʿ� �ð� 
		public Int16 m_mainitem_basic_ability; 	// [�����۱⺻�ɷ�ġ] ������ �⺻ �ɷ�ġ 
		public Int16 m_mainitem_equip_level; 	// [�ش��������������]  
		public Int16 m_ability_min; 	// [�Ϲݰ�ȭ�ɷ�ġ] ��ȭ�� �ּ� ���� �ɷ�ġ(IUR_NORMAL) 
		public Int16 m_ability_max; 	// [��ȭ���ִ������ɷ�ġ] ��ȭ�� �ִ� ���� �ɷ�ġ(IUR_PERFECT) 
		public Int64 m_mainitem_upgrade_need_money; 	// [�ʿ���ӸӴ�] �ʿ� ���� �Ӵ� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int16.Parse("Sys_MainItemAbility::sid",token[idx++], ref m_sid);
			nUtil.jString_EItemCategoryEquipment.Parse("Sys_MainItemAbility::equip_category",token[idx++], ref m_equip_category);
			nUtil.jString_string.Parse("Sys_MainItemAbility::name",token[idx++], ref m_name);
			nUtil.jString_Int16.Parse("Sys_MainItemAbility::mainitem_first_equip_level",token[idx++], ref m_mainitem_first_equip_level);
			nUtil.jString_Int16.Parse("Sys_MainItemAbility::mainitem_possible_upgrade_level",token[idx++], ref m_mainitem_possible_upgrade_level);
			nUtil.jString_Int16.Parse("Sys_MainItemAbility::mainitem_need_time",token[idx++], ref m_mainitem_need_time);
			nUtil.jString_Int16.Parse("Sys_MainItemAbility::mainitem_basic_ability",token[idx++], ref m_mainitem_basic_ability);
			nUtil.jString_Int16.Parse("Sys_MainItemAbility::mainitem_equip_level",token[idx++], ref m_mainitem_equip_level);
			nUtil.jString_Int16.Parse("Sys_MainItemAbility::ability_min",token[idx++], ref m_ability_min);
			nUtil.jString_Int16.Parse("Sys_MainItemAbility::ability_max",token[idx++], ref m_ability_max);
			nUtil.jString_Int64.Parse("Sys_MainItemAbility::mainitem_upgrade_need_money",token[idx++], ref m_mainitem_upgrade_need_money);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_sid.ToString() + ",";
			output += m_equip_category.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_mainitem_first_equip_level.ToString() + ",";
			output += m_mainitem_possible_upgrade_level.ToString() + ",";
			output += m_mainitem_need_time.ToString() + ",";
			output += m_mainitem_basic_ability.ToString() + ",";
			output += m_mainitem_equip_level.ToString() + ",";
			output += m_ability_min.ToString() + ",";
			output += m_ability_max.ToString() + ",";
			output += m_mainitem_upgrade_need_money.ToString() + ",";
			return output;
		}
	}//class Sys_MainItemAbility

	namespace nUtil
	{
		class jString_Sys_MainItemAbility
		{
			public static string ToString(Sys_MainItemAbility o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_MainItemAbility> sysList)
			{
				string output = "";
				foreach (Sys_MainItemAbility o in sysList)
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
				Sys_MainItemAbility o = (Sys_MainItemAbility)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_MainItemAbility o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_MainItemAbility.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_MainItemAbility.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_MainItemAbility> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_MainItemAbility> sysList = (List<Sys_MainItemAbility>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_MainItemAbility o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_MainItemAbility.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_MainItemAbility.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_MainItemAbility
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_Package
	{
		public Int16 m_sid; 	// [sid]  
		public string m_name; 	// [name]  
		public EItemPriceType m_price_type; 	// [����Ÿ��]  
		public Int32 m_price_money; 	// [�ʿ���ӸӴ�]  
		public Int32 m_price_cash; 	// [�ʿ丮��ĳ��]  
		public EGradeAllitemType m_grade_allitem_type1; 	// [�����ۺ��׷��̵����1] �����ۺ��׷��̵����1(EX : ���ξ�����S�� ���, ���������s�� ��Ρ�) 
		public EGradeAllitemType m_grade_allitem_type2; 	// [�����ۺ��׷��̵����2] �����ۺ��׷��̵����2 
		public EGradeAllitemType m_grade_allitem_type3; 	// [�����ۺ��׷��̵����3] �����ۺ��׷��̵����3 
		public EGradeAllitemType m_grade_allitem_type4; 	// [�����ۺ��׷��̵����4] �����ۺ��׷��̵����4 
		public EGiftType m_gift_type1; 	// [��������1]  
		public Int64 m_gift_type1_value; 	// [����1]  
		public EGiftType m_gift_type2; 	// [��������2]  
		public Int64 m_gift_type2_value; 	// [����2]  
		public EGiftType m_gift_type3; 	// [��������3]  
		public Int64 m_gift_type3_value; 	// [����3]  
		public EGiftType m_gift_type4; 	// [��������4]  
		public Int64 m_gift_type4_value; 	// [����4]  
		public EGiftType m_gift_type5; 	// [��������5]  
		public Int64 m_gift_type5_value; 	// [����5]  
		public EGiftType m_gift_type6; 	// [��������6]  
		public Int64 m_gift_type6_value; 	// [����6]  
		public EGiftType m_gift_type7; 	// [��������7]  
		public Int64 m_gift_type7_value; 	// [����7]  
		public EGiftType m_gift_type8; 	// [��������8]  
		public Int64 m_gift_type8_value; 	// [����8]  
		public EGiftType m_gift_type9; 	// [��������9]  
		public Int64 m_gift_type9_value; 	// [����9]  
		public EGiftType m_gift_type10; 	// [��������10]  
		public Int64 m_gift_type10_value; 	// [����10]  
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int16.Parse("Sys_Package::sid",token[idx++], ref m_sid);
			nUtil.jString_string.Parse("Sys_Package::name",token[idx++], ref m_name);
			nUtil.jString_EItemPriceType.Parse("Sys_Package::price_type",token[idx++], ref m_price_type);
			nUtil.jString_Int32.Parse("Sys_Package::price_money",token[idx++], ref m_price_money);
			nUtil.jString_Int32.Parse("Sys_Package::price_cash",token[idx++], ref m_price_cash);
			nUtil.jString_EGradeAllitemType.Parse("Sys_Package::grade_allitem_type1",token[idx++], ref m_grade_allitem_type1);
			nUtil.jString_EGradeAllitemType.Parse("Sys_Package::grade_allitem_type2",token[idx++], ref m_grade_allitem_type2);
			nUtil.jString_EGradeAllitemType.Parse("Sys_Package::grade_allitem_type3",token[idx++], ref m_grade_allitem_type3);
			nUtil.jString_EGradeAllitemType.Parse("Sys_Package::grade_allitem_type4",token[idx++], ref m_grade_allitem_type4);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type1",token[idx++], ref m_gift_type1);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type1_value",token[idx++], ref m_gift_type1_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type2",token[idx++], ref m_gift_type2);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type2_value",token[idx++], ref m_gift_type2_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type3",token[idx++], ref m_gift_type3);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type3_value",token[idx++], ref m_gift_type3_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type4",token[idx++], ref m_gift_type4);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type4_value",token[idx++], ref m_gift_type4_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type5",token[idx++], ref m_gift_type5);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type5_value",token[idx++], ref m_gift_type5_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type6",token[idx++], ref m_gift_type6);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type6_value",token[idx++], ref m_gift_type6_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type7",token[idx++], ref m_gift_type7);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type7_value",token[idx++], ref m_gift_type7_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type8",token[idx++], ref m_gift_type8);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type8_value",token[idx++], ref m_gift_type8_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type9",token[idx++], ref m_gift_type9);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type9_value",token[idx++], ref m_gift_type9_value);
			nUtil.jString_EGiftType.Parse("Sys_Package::gift_type10",token[idx++], ref m_gift_type10);
			nUtil.jString_Int64.Parse("Sys_Package::gift_type10_value",token[idx++], ref m_gift_type10_value);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_sid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_price_type.ToString() + ",";
			output += m_price_money.ToString() + ",";
			output += m_price_cash.ToString() + ",";
			output += m_grade_allitem_type1.ToString() + ",";
			output += m_grade_allitem_type2.ToString() + ",";
			output += m_grade_allitem_type3.ToString() + ",";
			output += m_grade_allitem_type4.ToString() + ",";
			output += m_gift_type1.ToString() + ",";
			output += m_gift_type1_value.ToString() + ",";
			output += m_gift_type2.ToString() + ",";
			output += m_gift_type2_value.ToString() + ",";
			output += m_gift_type3.ToString() + ",";
			output += m_gift_type3_value.ToString() + ",";
			output += m_gift_type4.ToString() + ",";
			output += m_gift_type4_value.ToString() + ",";
			output += m_gift_type5.ToString() + ",";
			output += m_gift_type5_value.ToString() + ",";
			output += m_gift_type6.ToString() + ",";
			output += m_gift_type6_value.ToString() + ",";
			output += m_gift_type7.ToString() + ",";
			output += m_gift_type7_value.ToString() + ",";
			output += m_gift_type8.ToString() + ",";
			output += m_gift_type8_value.ToString() + ",";
			output += m_gift_type9.ToString() + ",";
			output += m_gift_type9_value.ToString() + ",";
			output += m_gift_type10.ToString() + ",";
			output += m_gift_type10_value.ToString() + ",";
			return output;
		}
	}//class Sys_Package

	namespace nUtil
	{
		class jString_Sys_Package
		{
			public static string ToString(Sys_Package o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_Package> sysList)
			{
				string output = "";
				foreach (Sys_Package o in sysList)
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
				Sys_Package o = (Sys_Package)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_Package o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_Package.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_Package.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_Package> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_Package> sysList = (List<Sys_Package>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_Package o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_Package.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_Package.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_Package
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_PlayerCard
			: Sys__Base_PlayerStat
	{
		public EPlayerNationType m_player_nation; 	// [���]  
		public Int16 m_player_year; 	// [Ȱ�� ����] �÷��̾� Ȱ������ 
		public EPlayerGradeType m_player_grade; 	// [���] ���� �� ���׷��̵� ��� 
		public EplayerBadyType m_body_type; 	// [ü��]  
		public Int16 m_player_level; 	// [�÷��̾� ����] ���� ���� 
		public EPlayerType m_player_type; 	// [Ÿ����������] Ÿ���������� 
		public EItemPriceType m_price_type; 	// [����Ÿ��]  
		public Int32 m_price_money; 	// [�ʿ���ӸӴ�]  
		public Int32 m_price_cash; 	// [�ʿ丮��ĳ��]  
		public EItemSellStatus m_sell_status; 	// [�ǸŻ���]  
		public DATETIME m_sell_start_date; 	// [�Ǹ� ���� �Ͻ�] �Ǹ� ���� �Ͻ� 
		public DATETIME m_sell_end_date; 	// [�Ǹ� ���� �Ͻ�] �Ǹ� ���� �Ͻ� 
		public Int16 m_player_level_min; 	// [��뷹��MIN]  
		public Int16 m_player_level_max; 	// [��뷹��MAX]  
		public Int16 m_sticker_slot_count; 	// [���ϼ��ִ½�ƼĿ����]  
		public List<Sys_PlayerSkillSticker> m_skill_sticker = new List<Sys_PlayerSkillSticker>{}; 	// [�⺻�����κ����� Ư���ɷ�] Sys_PlayerSkillSticker������ name 
		public EPlayer_Onoffline m_player_onoff; 	// [�÷��̾��� �¿������� ����] �÷��̾��� �¿������� ���� 
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_EPlayerNationType.Parse("Sys_PlayerCard::player_nation",token[idx++], ref m_player_nation);
			nUtil.jString_Int16.Parse("Sys_PlayerCard::player_year",token[idx++], ref m_player_year);
			nUtil.jString_EPlayerGradeType.Parse("Sys_PlayerCard::player_grade",token[idx++], ref m_player_grade);
			nUtil.jString_EplayerBadyType.Parse("Sys_PlayerCard::body_type",token[idx++], ref m_body_type);
			nUtil.jString_Int16.Parse("Sys_PlayerCard::player_level",token[idx++], ref m_player_level);
			nUtil.jString_EPlayerType.Parse("Sys_PlayerCard::player_type",token[idx++], ref m_player_type);
			nUtil.jString_EItemPriceType.Parse("Sys_PlayerCard::price_type",token[idx++], ref m_price_type);
			nUtil.jString_Int32.Parse("Sys_PlayerCard::price_money",token[idx++], ref m_price_money);
			nUtil.jString_Int32.Parse("Sys_PlayerCard::price_cash",token[idx++], ref m_price_cash);
			nUtil.jString_EItemSellStatus.Parse("Sys_PlayerCard::sell_status",token[idx++], ref m_sell_status);
			nUtil.jString_DATETIME.Parse("Sys_PlayerCard::sell_start_date",token[idx++], ref m_sell_start_date);
			nUtil.jString_DATETIME.Parse("Sys_PlayerCard::sell_end_date",token[idx++], ref m_sell_end_date);
			nUtil.jString_Int16.Parse("Sys_PlayerCard::player_level_min",token[idx++], ref m_player_level_min);
			nUtil.jString_Int16.Parse("Sys_PlayerCard::player_level_max",token[idx++], ref m_player_level_max);
			nUtil.jString_Int16.Parse("Sys_PlayerCard::sticker_slot_count",token[idx++], ref m_sticker_slot_count);
			isFind = nUtil.jString_Sys_PlayerSkillSticker.Parse("Sys_PlayerCard::skill_sticker",token[idx++], ref m_skill_sticker);
			if(!isFind)
			{
				if(!isPostParse)
				{
					if(!nUtil.jCSV.m_PostParseList.ContainsKey(this))
					{
					
						nUtil.jCSV.PostParseData ppd = new nUtil.jCSV.PostParseData();
						ppd.func = new nUtil.jCSV.PostParseFunc(nUtil.jString_Sys_PlayerCard.PostParse);
						ppd.token = token;
						ppd.idx = iStart;
						ppd.o = this;
						ppd.sDebug = " -> Sys_PlayerCard : " ;
						nUtil.jCSV.m_PostParseList[this]=ppd;
					}
				}
				else
				{
					Console.WriteLine("[WARN]" + " -> Sys_PlayerCard : skill_sticker : " + token[idx-1]) ;
				}
			}
			nUtil.jString_EPlayer_Onoffline.Parse("Sys_PlayerCard::player_onoff",token[idx++], ref m_player_onoff);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_player_nation.ToString() + ",";
			output += m_player_year.ToString() + ",";
			output += m_player_grade.ToString() + ",";
			output += m_body_type.ToString() + ",";
			output += m_player_level.ToString() + ",";
			output += m_player_type.ToString() + ",";
			output += m_price_type.ToString() + ",";
			output += m_price_money.ToString() + ",";
			output += m_price_cash.ToString() + ",";
			output += m_sell_status.ToString() + ",";
			output += m_sell_start_date.ToString() + ",";
			output += m_sell_end_date.ToString() + ",";
			output += m_player_level_min.ToString() + ",";
			output += m_player_level_max.ToString() + ",";
			output += m_sticker_slot_count.ToString() + ",";
			output += (nUtil.jString_Sys_PlayerSkillSticker.ToString(m_skill_sticker)+ ",");
			output += m_player_onoff.ToString() + ",";
			return output;
		}
	}//class Sys_PlayerCard

	namespace nUtil
	{
		class jString_Sys_PlayerCard
		{
			public static string ToString(Sys_PlayerCard o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_PlayerCard> sysList)
			{
				string output = "";
				foreach (Sys_PlayerCard o in sysList)
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
				Sys_PlayerCard o = (Sys_PlayerCard)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_PlayerCard o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_PlayerCard.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_PlayerCard.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_PlayerCard> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_PlayerCard> sysList = (List<Sys_PlayerCard>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_PlayerCard o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_PlayerCard.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_PlayerCard.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_PlayerCard
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_PlayerLevel
	{
		public Int16 m_sid; 	// [������ȣ] ������ȣ 
		public string m_name; 	// [name]  
		public Int16 m_level; 	// [�÷��̾��] �÷��̾�� 
		public Int64 m_max_exp; 	// [�ش� ������ �ִ� ����ġ] �ش� ������ �ִ� ����ġ 
		public Int16 m_better_accuracy_s; 	// [Ÿ��_small_��Ȯ] Ÿ��_small_��Ȯ 
		public Int16 m_better_accuracy_m; 	// [Ÿ��_Midium_��Ȯ] Ÿ��_Midium_��Ȯ 
		public Int16 m_better_accuracy_l; 	// [Ÿ��_large_��Ȯ] Ÿ��_large_��Ȯ 
		public Int16 m_better_power_s; 	// [Ÿ��_small_�Ŀ�] Ÿ��_small_�Ŀ� 
		public Int16 m_better_power_m; 	// [Ÿ��_Midium_�Ŀ�] Ÿ��_Midium_�Ŀ� 
		public Int16 m_better_power_l; 	// [Ÿ��_large_�Ŀ�] Ÿ��_large_�Ŀ� 
		public Int16 m_pitcher_speed_s; 	// [����_small_����] ����_small_���� 
		public Int16 m_pitcher_speed_m; 	// [����_Midium_����] ����_Midium_���� 
		public Int16 m_pitcher_speed_l; 	// [����_large_����] ����_large_���� 
		public Int16 m_pitcher_focus_s; 	// [����_small_����] ����_small_���� 
		public Int16 m_pitcher_focus_m; 	// [����_Midium_����] ����_Midium_���� 
		public Int16 m_pitcher_focus_l; 	// [����_large_����] ����_large_���� 
		public Int16 m_pitcher_breakingball_s; 	// [����_small_��ȭ��] ����_small_��ȭ�� ���� ���� 
		public Int16 m_pitcher_breakingball_m; 	// [����_Midium_��ȭ��] ����_Midium_��ȭ�� ���� ���� 
		public Int16 m_pitcher_breakingball_l; 	// [����_large_��ȭ��] ����_large_��ȭ�� ���� ���� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::sid",token[idx++], ref m_sid);
			nUtil.jString_string.Parse("Sys_PlayerLevel::name",token[idx++], ref m_name);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::level",token[idx++], ref m_level);
			nUtil.jString_Int64.Parse("Sys_PlayerLevel::max_exp",token[idx++], ref m_max_exp);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::better_accuracy_s",token[idx++], ref m_better_accuracy_s);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::better_accuracy_m",token[idx++], ref m_better_accuracy_m);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::better_accuracy_l",token[idx++], ref m_better_accuracy_l);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::better_power_s",token[idx++], ref m_better_power_s);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::better_power_m",token[idx++], ref m_better_power_m);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::better_power_l",token[idx++], ref m_better_power_l);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_speed_s",token[idx++], ref m_pitcher_speed_s);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_speed_m",token[idx++], ref m_pitcher_speed_m);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_speed_l",token[idx++], ref m_pitcher_speed_l);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_focus_s",token[idx++], ref m_pitcher_focus_s);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_focus_m",token[idx++], ref m_pitcher_focus_m);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_focus_l",token[idx++], ref m_pitcher_focus_l);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_breakingball_s",token[idx++], ref m_pitcher_breakingball_s);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_breakingball_m",token[idx++], ref m_pitcher_breakingball_m);
			nUtil.jString_Int16.Parse("Sys_PlayerLevel::pitcher_breakingball_l",token[idx++], ref m_pitcher_breakingball_l);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_sid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_level.ToString() + ",";
			output += m_max_exp.ToString() + ",";
			output += m_better_accuracy_s.ToString() + ",";
			output += m_better_accuracy_m.ToString() + ",";
			output += m_better_accuracy_l.ToString() + ",";
			output += m_better_power_s.ToString() + ",";
			output += m_better_power_m.ToString() + ",";
			output += m_better_power_l.ToString() + ",";
			output += m_pitcher_speed_s.ToString() + ",";
			output += m_pitcher_speed_m.ToString() + ",";
			output += m_pitcher_speed_l.ToString() + ",";
			output += m_pitcher_focus_s.ToString() + ",";
			output += m_pitcher_focus_m.ToString() + ",";
			output += m_pitcher_focus_l.ToString() + ",";
			output += m_pitcher_breakingball_s.ToString() + ",";
			output += m_pitcher_breakingball_m.ToString() + ",";
			output += m_pitcher_breakingball_l.ToString() + ",";
			return output;
		}
	}//class Sys_PlayerLevel

	namespace nUtil
	{
		class jString_Sys_PlayerLevel
		{
			public static string ToString(Sys_PlayerLevel o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_PlayerLevel> sysList)
			{
				string output = "";
				foreach (Sys_PlayerLevel o in sysList)
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
				Sys_PlayerLevel o = (Sys_PlayerLevel)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_PlayerLevel o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_PlayerLevel.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_PlayerLevel.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_PlayerLevel> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_PlayerLevel> sysList = (List<Sys_PlayerLevel>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_PlayerLevel o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_PlayerLevel.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_PlayerLevel.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_PlayerLevel
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_PlayerSkillSticker
			: Sys__Base_PlayerStat
	{
		public EPlayerBetterSkill m_better_skill1_type; 	// [Ÿ��Ư���ɷ�����] Ÿ�� ī���� ��ų ���� 
		public EPlayerPitcherSkill m_Pitcher_skill1_type; 	// [����Ư���ɷ�����] ���� ī���� ��ų ���� 
		public Int16 m_unlock_player_level; 	// [���������Ǵ·���] �ش� ��ų��ƼĿ�� ���ɼ��ִ� �÷��̾�� 
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_EPlayerBetterSkill.Parse("Sys_PlayerSkillSticker::better_skill1_type",token[idx++], ref m_better_skill1_type);
			nUtil.jString_EPlayerPitcherSkill.Parse("Sys_PlayerSkillSticker::Pitcher_skill1_type",token[idx++], ref m_Pitcher_skill1_type);
			nUtil.jString_Int16.Parse("Sys_PlayerSkillSticker::unlock_player_level",token[idx++], ref m_unlock_player_level);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_better_skill1_type.ToString() + ",";
			output += m_Pitcher_skill1_type.ToString() + ",";
			output += m_unlock_player_level.ToString() + ",";
			return output;
		}
	}//class Sys_PlayerSkillSticker

	namespace nUtil
	{
		class jString_Sys_PlayerSkillSticker
		{
			public static string ToString(Sys_PlayerSkillSticker o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_PlayerSkillSticker> sysList)
			{
				string output = "";
				foreach (Sys_PlayerSkillSticker o in sysList)
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
				Sys_PlayerSkillSticker o = (Sys_PlayerSkillSticker)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_PlayerSkillSticker o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_PlayerSkillSticker.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_PlayerSkillSticker.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_PlayerSkillSticker> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_PlayerSkillSticker> sysList = (List<Sys_PlayerSkillSticker>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_PlayerSkillSticker o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_PlayerSkillSticker.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_PlayerSkillSticker.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_PlayerSkillSticker
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_Quest
	{
		public Sys_Quest_id_t m_sid; 	// [������ȣ]  
		public string m_name; 	// [����Ʈ�̸�] Ŭ�� ����� ��Ʈ���� name���� Sys_StringTable���� �˻��ؼ� ����Ѵ�. 
		public game_money_t m_quest_reward_money; 	// [����Ӵ�] ����Ʈ ���� ���ӸӴ� 
		public pp_point_t m_quest_reward_point; 	// [��������Ʈ] ����Ʈ ���� pp����Ʈ 
		public EConditionCharacterTitle m_condition_character_title; 	// [����ȣĪ��] ȣĪ �ο� �� ���̹� 
		public string m_help; 	// [���Ǽ���] ��¿��̾ƴ϶� ���߽� ������ 
		public EQuestConditionType m_condition_type1; 	// [����1Ÿ��]  
		public string m_condition1; 	// [����1����] ���� ��� NULL 
		public Int32 m_condition_value1; 	// [����1��]  
		public EQuestConditionType m_condition_type2; 	// [����2Ÿ��]  
		public string m_condition2; 	// [����2����]  
		public Int32 m_condition_value2; 	// [����2��]  
		public EQuestConditionType m_condition_type3; 	// [����3Ÿ��]  
		public string m_condition3; 	// [����3����]  
		public Int32 m_condition_value3; 	// [����3��]  
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_Quest::sid",token[idx++], ref m_sid);
			nUtil.jString_string.Parse("Sys_Quest::name",token[idx++], ref m_name);
			nUtil.jString_Int32.Parse("Sys_Quest::quest_reward_money",token[idx++], ref m_quest_reward_money);
			nUtil.jString_Int32.Parse("Sys_Quest::quest_reward_point",token[idx++], ref m_quest_reward_point);
			nUtil.jString_EConditionCharacterTitle.Parse("Sys_Quest::condition_character_title",token[idx++], ref m_condition_character_title);
			nUtil.jString_string.Parse("Sys_Quest::help",token[idx++], ref m_help);
			nUtil.jString_EQuestConditionType.Parse("Sys_Quest::condition_type1",token[idx++], ref m_condition_type1);
			nUtil.jString_string.Parse("Sys_Quest::condition1",token[idx++], ref m_condition1);
			nUtil.jString_Int32.Parse("Sys_Quest::condition_value1",token[idx++], ref m_condition_value1);
			nUtil.jString_EQuestConditionType.Parse("Sys_Quest::condition_type2",token[idx++], ref m_condition_type2);
			nUtil.jString_string.Parse("Sys_Quest::condition2",token[idx++], ref m_condition2);
			nUtil.jString_Int32.Parse("Sys_Quest::condition_value2",token[idx++], ref m_condition_value2);
			nUtil.jString_EQuestConditionType.Parse("Sys_Quest::condition_type3",token[idx++], ref m_condition_type3);
			nUtil.jString_string.Parse("Sys_Quest::condition3",token[idx++], ref m_condition3);
			nUtil.jString_Int32.Parse("Sys_Quest::condition_value3",token[idx++], ref m_condition_value3);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_sid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_quest_reward_money.ToString() + ",";
			output += m_quest_reward_point.ToString() + ",";
			output += m_condition_character_title.ToString() + ",";
			output += m_help.ToString() + ",";
			output += m_condition_type1.ToString() + ",";
			output += m_condition1.ToString() + ",";
			output += m_condition_value1.ToString() + ",";
			output += m_condition_type2.ToString() + ",";
			output += m_condition2.ToString() + ",";
			output += m_condition_value2.ToString() + ",";
			output += m_condition_type3.ToString() + ",";
			output += m_condition3.ToString() + ",";
			output += m_condition_value3.ToString() + ",";
			return output;
		}
	}//class Sys_Quest

	namespace nUtil
	{
		class jString_Sys_Quest
		{
			public static string ToString(Sys_Quest o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_Quest> sysList)
			{
				string output = "";
				foreach (Sys_Quest o in sysList)
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
				Sys_Quest o = (Sys_Quest)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_Quest o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_Quest.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_Quest.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_Quest> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_Quest> sysList = (List<Sys_Quest>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_Quest o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_Quest.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_Quest.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_Quest
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_RandomGift
	{
		public Sys_RandomGift_id_t m_item_sid; 	// [sid]  
		public string m_name; 	// [name]  
		public EGiftCategory m_gift_category; 	// [���� ����] �̰�����/������/Ʈ���̴׿Ϸ�� 
		public EGiftType m_gift_type; 	// [���� Ÿ��]  
		public Int32 m_gift1; 	// [���� ��] Ȯ���� �ּ� ���� 
		public Int32 m_gift2; 	// [���� ��] Ȯ���� �ְ� ���� 
		public string m_gift3; 	// [���� ��] Ȯ���� ������ �õ尪 
		public Int16 m_gift_probability; 	// [EGiftType�� Ȯ��] õ����. 0~1000 
		public string m_help; 	// [EGiftType�� ����]  
		public EItemCategory m_item1_type; 	// [������ ����]  
		public Sys_ItemEquip m_item1; 	// [EItemCategory�� SID]  
		public Int16 m_item1_probability; 	// [EItemCategory�� Ȯ��] õ����. 0~1000 
		public EItemCategory m_item2_type; 	// [������ ����]  
		public Sys_ItemEquip m_item2; 	// [EItemCategory�� SID]  
		public Int16 m_item2_probability; 	// [EItemCategory�� Ȯ��] õ����. 0~1000 
		public EItemCategory m_item3_type; 	// [������ ����]  
		public Sys_ItemEquip m_item3; 	// [EItemCategory�� SID]  
		public Int16 m_item3_probability; 	// [EItemCategory�� Ȯ��] õ����. 0~1000 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_RandomGift::item_sid",token[idx++], ref m_item_sid);
			nUtil.jString_string.Parse("Sys_RandomGift::name",token[idx++], ref m_name);
			nUtil.jString_EGiftCategory.Parse("Sys_RandomGift::gift_category",token[idx++], ref m_gift_category);
			nUtil.jString_EGiftType.Parse("Sys_RandomGift::gift_type",token[idx++], ref m_gift_type);
			nUtil.jString_Int32.Parse("Sys_RandomGift::gift1",token[idx++], ref m_gift1);
			nUtil.jString_Int32.Parse("Sys_RandomGift::gift2",token[idx++], ref m_gift2);
			nUtil.jString_string.Parse("Sys_RandomGift::gift3",token[idx++], ref m_gift3);
			nUtil.jString_Int16.Parse("Sys_RandomGift::gift_probability",token[idx++], ref m_gift_probability);
			nUtil.jString_string.Parse("Sys_RandomGift::help",token[idx++], ref m_help);
			nUtil.jString_EItemCategory.Parse("Sys_RandomGift::item1_type",token[idx++], ref m_item1_type);
			isFind = nUtil.jString_Sys_ItemEquip.Parse("Sys_RandomGift::item1",token[idx++], ref m_item1);
			if(!isFind)
			{
				if(!isPostParse)
				{
					if(!nUtil.jCSV.m_PostParseList.ContainsKey(this))
					{
					
						nUtil.jCSV.PostParseData ppd = new nUtil.jCSV.PostParseData();
						ppd.func = new nUtil.jCSV.PostParseFunc(nUtil.jString_Sys_RandomGift.PostParse);
						ppd.token = token;
						ppd.idx = iStart;
						ppd.o = this;
						ppd.sDebug = " -> Sys_RandomGift : " ;
						nUtil.jCSV.m_PostParseList[this]=ppd;
					}
				}
				else
				{
					Console.WriteLine("[WARN]" + " -> Sys_RandomGift : item1 : " + token[idx-1]) ;
				}
			}
			nUtil.jString_Int16.Parse("Sys_RandomGift::item1_probability",token[idx++], ref m_item1_probability);
			nUtil.jString_EItemCategory.Parse("Sys_RandomGift::item2_type",token[idx++], ref m_item2_type);
			isFind = nUtil.jString_Sys_ItemEquip.Parse("Sys_RandomGift::item2",token[idx++], ref m_item2);
			if(!isFind)
			{
				if(!isPostParse)
				{
					if(!nUtil.jCSV.m_PostParseList.ContainsKey(this))
					{
					
						nUtil.jCSV.PostParseData ppd = new nUtil.jCSV.PostParseData();
						ppd.func = new nUtil.jCSV.PostParseFunc(nUtil.jString_Sys_RandomGift.PostParse);
						ppd.token = token;
						ppd.idx = iStart;
						ppd.o = this;
						ppd.sDebug = " -> Sys_RandomGift : " ;
						nUtil.jCSV.m_PostParseList[this]=ppd;
					}
				}
				else
				{
					Console.WriteLine("[WARN]" + " -> Sys_RandomGift : item2 : " + token[idx-1]) ;
				}
			}
			nUtil.jString_Int16.Parse("Sys_RandomGift::item2_probability",token[idx++], ref m_item2_probability);
			nUtil.jString_EItemCategory.Parse("Sys_RandomGift::item3_type",token[idx++], ref m_item3_type);
			isFind = nUtil.jString_Sys_ItemEquip.Parse("Sys_RandomGift::item3",token[idx++], ref m_item3);
			if(!isFind)
			{
				if(!isPostParse)
				{
					if(!nUtil.jCSV.m_PostParseList.ContainsKey(this))
					{
					
						nUtil.jCSV.PostParseData ppd = new nUtil.jCSV.PostParseData();
						ppd.func = new nUtil.jCSV.PostParseFunc(nUtil.jString_Sys_RandomGift.PostParse);
						ppd.token = token;
						ppd.idx = iStart;
						ppd.o = this;
						ppd.sDebug = " -> Sys_RandomGift : " ;
						nUtil.jCSV.m_PostParseList[this]=ppd;
					}
				}
				else
				{
					Console.WriteLine("[WARN]" + " -> Sys_RandomGift : item3 : " + token[idx-1]) ;
				}
			}
			nUtil.jString_Int16.Parse("Sys_RandomGift::item3_probability",token[idx++], ref m_item3_probability);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_item_sid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_gift_category.ToString() + ",";
			output += m_gift_type.ToString() + ",";
			output += m_gift1.ToString() + ",";
			output += m_gift2.ToString() + ",";
			output += m_gift3.ToString() + ",";
			output += m_gift_probability.ToString() + ",";
			output += m_help.ToString() + ",";
			output += m_item1_type.ToString() + ",";
			output += (nUtil.jString_Sys_ItemEquip.ToString(m_item1)+ ",");
			output += m_item1_probability.ToString() + ",";
			output += m_item2_type.ToString() + ",";
			output += (nUtil.jString_Sys_ItemEquip.ToString(m_item2)+ ",");
			output += m_item2_probability.ToString() + ",";
			output += m_item3_type.ToString() + ",";
			output += (nUtil.jString_Sys_ItemEquip.ToString(m_item3)+ ",");
			output += m_item3_probability.ToString() + ",";
			return output;
		}
	}//class Sys_RandomGift

	namespace nUtil
	{
		class jString_Sys_RandomGift
		{
			public static string ToString(Sys_RandomGift o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_RandomGift> sysList)
			{
				string output = "";
				foreach (Sys_RandomGift o in sysList)
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
				Sys_RandomGift o = (Sys_RandomGift)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_RandomGift o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_RandomGift.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_RandomGift.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_RandomGift> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_RandomGift> sysList = (List<Sys_RandomGift>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_RandomGift o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_RandomGift.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_RandomGift.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_RandomGift
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_SubItemAbility
	{
		public Int16 m_sid; 	// [������ȣ] ������ȣ 
		public EItemCategoryEquipment m_equip_category; 	// [��������ī�װ�] ��������ī�װ� 
		public EItemGradeType m_grade; 	// [���] ������ ���׷��̵� ��� 
		public Int16 m_subitem_first_equip_level; 	// [���������� ���� ����] ������ ���� ���� ���� 
		public Int16 m_subitem_better_ability; 	// [������Ÿ�ڴɷ�ġ] ������ �⺻ �ɷ�ġ 
		public Int16 m_subitem_pitcher_ability; 	// [�����������ɷ�ġ] ������ �⺻ �ɷ�ġ 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int16.Parse("Sys_SubItemAbility::sid",token[idx++], ref m_sid);
			nUtil.jString_EItemCategoryEquipment.Parse("Sys_SubItemAbility::equip_category",token[idx++], ref m_equip_category);
			nUtil.jString_EItemGradeType.Parse("Sys_SubItemAbility::grade",token[idx++], ref m_grade);
			nUtil.jString_Int16.Parse("Sys_SubItemAbility::subitem_first_equip_level",token[idx++], ref m_subitem_first_equip_level);
			nUtil.jString_Int16.Parse("Sys_SubItemAbility::subitem_better_ability",token[idx++], ref m_subitem_better_ability);
			nUtil.jString_Int16.Parse("Sys_SubItemAbility::subitem_pitcher_ability",token[idx++], ref m_subitem_pitcher_ability);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_sid.ToString() + ",";
			output += m_equip_category.ToString() + ",";
			output += m_grade.ToString() + ",";
			output += m_subitem_first_equip_level.ToString() + ",";
			output += m_subitem_better_ability.ToString() + ",";
			output += m_subitem_pitcher_ability.ToString() + ",";
			return output;
		}
	}//class Sys_SubItemAbility

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Tbl__PlayerBase
	{
		public Tbl__PlayerBase_id_t m_pid; 	// [PK index] ���� database table PK 
		public Sys_PlayerCard_id_t m_sid; 	// [Sys_Player���̵�] ������ ����ī���� ��ȣ(Sys_Player�� sid) ���� 0 �̸� ���󼱼� 
		public pimang_id_t m_ppid; 	// [PP_ID] �Ǹ����̵��ȣ 
		public string m_pname; 	// [�г���]  
		public EPlayerNationType m_city; 	// [��ű���] ĳ�־�߱� ���ӱ�ȹ�� 3�� (20111031).docx���� 
		public string m_initial_name; 	// [�̴ϼ�] ������ ����. ������̴ϼȱ���. �ߺ����� 
		public Int16 m_back_number; 	// [��ѹ�] ������ ����. ������������� ���氡�� 
		public Int16 m_age; 	// [����] ������ ����. 
		public EplayerBadyType m_bady_type; 	// [ü��]  
		public bool m_leftright_type; 	// [�¿�Ÿ��] ĳ������ �¿� ���� 1�̸� �¼��� 0�̸� �켱�� 
		public Int64 m_exp; 	// [����ġ] ������ ����ġ�� �ش��ϴ� Sys_PlayerLevel�� ���� ���� ���� 
		public Sys_Quest_id_t m_questcomplete_count; 	// [����Ʈ�Ϸ�_ī��Ʈ] �Ϸ� ����Ʈ ī��Ʈ 
		public Int16 m_win_continue; 	// [����] �������� �¸��� ���� 
		public Int16 m_lose_continue; 	// [����] ���� ���� ���� 
		public Tbl_Result_id_t m_last_game_result; 	// [���������id] ���������� �÷����� ����� �ĺ��� 
		public Int32 m_win_tot; 	// [������_��] ��Ż �� ī��Ʈ 
		public Int32 m_lose_tot; 	// [������_��] ��Ż �� ī��Ʈ 
		public Int32 m_win_season; 	// [��������_��] ���� �� ī��Ʈ(3����) 
		public Int32 m_lose_season; 	// [��������_��] ���� �� ī��Ʈ(3����) 
		public string m_skill_sticker; 	// [Ư���ɷ��̸�] Sys_PlayeSkillSticker������ name  ";"�� ���еǾ� �������Է� 
		public Int32 m_elo_point; 	// [ELO_����Ʈ] ��⸶�� ĳ���Ϳ� ���ŵǴ� ��Ī�� ����Ʈ 
		public bool m_onoff_type; 	// [�¿������α���] 0�̸� �¶����÷��̾� 1�̸� ���������÷��̾� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int64.Parse("Tbl__PlayerBase::pid",token[idx++], ref m_pid);
			nUtil.jString_UInt16.Parse("Tbl__PlayerBase::sid",token[idx++], ref m_sid);
			nUtil.jString_Int32.Parse("Tbl__PlayerBase::ppid",token[idx++], ref m_ppid);
			nUtil.jString_string.Parse("Tbl__PlayerBase::pname",token[idx++], ref m_pname);
			nUtil.jString_EPlayerNationType.Parse("Tbl__PlayerBase::city",token[idx++], ref m_city);
			nUtil.jString_string.Parse("Tbl__PlayerBase::initial_name",token[idx++], ref m_initial_name);
			nUtil.jString_Int16.Parse("Tbl__PlayerBase::back_number",token[idx++], ref m_back_number);
			nUtil.jString_Int16.Parse("Tbl__PlayerBase::age",token[idx++], ref m_age);
			nUtil.jString_EplayerBadyType.Parse("Tbl__PlayerBase::bady_type",token[idx++], ref m_bady_type);
			nUtil.jString_bool.Parse("Tbl__PlayerBase::leftright_type",token[idx++], ref m_leftright_type);
			nUtil.jString_Int64.Parse("Tbl__PlayerBase::exp",token[idx++], ref m_exp);
			nUtil.jString_UInt16.Parse("Tbl__PlayerBase::questcomplete_count",token[idx++], ref m_questcomplete_count);
			nUtil.jString_Int16.Parse("Tbl__PlayerBase::win_continue",token[idx++], ref m_win_continue);
			nUtil.jString_Int16.Parse("Tbl__PlayerBase::lose_continue",token[idx++], ref m_lose_continue);
			nUtil.jString_Int64.Parse("Tbl__PlayerBase::last_game_result",token[idx++], ref m_last_game_result);
			nUtil.jString_Int32.Parse("Tbl__PlayerBase::win_tot",token[idx++], ref m_win_tot);
			nUtil.jString_Int32.Parse("Tbl__PlayerBase::lose_tot",token[idx++], ref m_lose_tot);
			nUtil.jString_Int32.Parse("Tbl__PlayerBase::win_season",token[idx++], ref m_win_season);
			nUtil.jString_Int32.Parse("Tbl__PlayerBase::lose_season",token[idx++], ref m_lose_season);
			nUtil.jString_string.Parse("Tbl__PlayerBase::skill_sticker",token[idx++], ref m_skill_sticker);
			nUtil.jString_Int32.Parse("Tbl__PlayerBase::elo_point",token[idx++], ref m_elo_point);
			nUtil.jString_bool.Parse("Tbl__PlayerBase::onoff_type",token[idx++], ref m_onoff_type);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_pid.ToString() + ",";
			output += m_sid.ToString() + ",";
			output += m_ppid.ToString() + ",";
			output += m_pname.ToString() + ",";
			output += m_city.ToString() + ",";
			output += m_initial_name.ToString() + ",";
			output += m_back_number.ToString() + ",";
			output += m_age.ToString() + ",";
			output += m_bady_type.ToString() + ",";
			output += m_leftright_type.ToString() + ",";
			output += m_exp.ToString() + ",";
			output += m_questcomplete_count.ToString() + ",";
			output += m_win_continue.ToString() + ",";
			output += m_lose_continue.ToString() + ",";
			output += m_last_game_result.ToString() + ",";
			output += m_win_tot.ToString() + ",";
			output += m_lose_tot.ToString() + ",";
			output += m_win_season.ToString() + ",";
			output += m_lose_season.ToString() + ",";
			output += m_skill_sticker.ToString() + ",";
			output += m_elo_point.ToString() + ",";
			output += m_onoff_type.ToString() + ",";
			return output;
		}
	}//class Tbl__PlayerBase

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Tbl_Item
	{
		public Tbl_Item_id_t m_iid; 	// [�����ĺ���] db pk 
		public Sys__ItemBase_id_t m_sid; 	// [������ ����������] Sys__ItemBase_id_t 
		public EItemCategory m_category; 	// [��з�] ��� ���� �Һ� ���� 
		public Tbl__PlayerBase_id_t m_pid; 	// [Tbl__PlayerBase pid] Tbl__PlayerBase�� did 
		public string m_upgrade_level; 	// [���׷��̵���] baseball.xml���� ITEM_UPGRADE_LOGIC ���� 
		public string m_etc_info; 	// [��Ÿ����] ���ȣ �������϶��� ���ȣ. ��ŷ �������϶��� ��ŷ���ڸ� ����. 
		public string m_grade; 	// [���] ������ ���׷��̵� ���(���ʴ� S,A,B,C,D,E���� �� ��) 
		public real_money_t m_bought_real_money; 	// [����ĳ��] ���Ž� ����� ����ĳ�� 
		public real_money_t m_bought_point_money; 	// [��������Ʈ] ���Ž� ����� ����Ʈ 
		public game_money_t m_bought_game_money; 	// [���Ű��ӸӴ�] ���Ž� ����� ���ӸӴ� 
		public bool m_is_used; 	// [�ͼӿ���] �� ������ ����̵Ǿ����� ���� 
		public bool m_is_confirmed; 	// [���Ż���] ĳ���κ� or �����κ� ȯ�ҿ��� 
		public Int16 m_usable_hour; 	// [�Ⱓ���������ǻ��ð�] �Ⱓ���������ǰ�� ��밡���� �ð� 
		public Int16 m_used_game_count; 	// [����� ���Ƚ��] ����� ������ ��� Ƚ�� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int64.Parse("Tbl_Item::iid",token[idx++], ref m_iid);
			nUtil.jString_UInt16.Parse("Tbl_Item::sid",token[idx++], ref m_sid);
			nUtil.jString_EItemCategory.Parse("Tbl_Item::category",token[idx++], ref m_category);
			nUtil.jString_Int64.Parse("Tbl_Item::pid",token[idx++], ref m_pid);
			nUtil.jString_string.Parse("Tbl_Item::upgrade_level",token[idx++], ref m_upgrade_level);
			nUtil.jString_string.Parse("Tbl_Item::etc_info",token[idx++], ref m_etc_info);
			nUtil.jString_string.Parse("Tbl_Item::grade",token[idx++], ref m_grade);
			nUtil.jString_Int32.Parse("Tbl_Item::bought_real_money",token[idx++], ref m_bought_real_money);
			nUtil.jString_Int32.Parse("Tbl_Item::bought_point_money",token[idx++], ref m_bought_point_money);
			nUtil.jString_Int32.Parse("Tbl_Item::bought_game_money",token[idx++], ref m_bought_game_money);
			nUtil.jString_bool.Parse("Tbl_Item::is_used",token[idx++], ref m_is_used);
			nUtil.jString_bool.Parse("Tbl_Item::is_confirmed",token[idx++], ref m_is_confirmed);
			nUtil.jString_Int16.Parse("Tbl_Item::usable_hour",token[idx++], ref m_usable_hour);
			nUtil.jString_Int16.Parse("Tbl_Item::used_game_count",token[idx++], ref m_used_game_count);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_iid.ToString() + ",";
			output += m_sid.ToString() + ",";
			output += m_category.ToString() + ",";
			output += m_pid.ToString() + ",";
			output += m_upgrade_level.ToString() + ",";
			output += m_etc_info.ToString() + ",";
			output += m_grade.ToString() + ",";
			output += m_bought_real_money.ToString() + ",";
			output += m_bought_point_money.ToString() + ",";
			output += m_bought_game_money.ToString() + ",";
			output += m_is_used.ToString() + ",";
			output += m_is_confirmed.ToString() + ",";
			output += m_usable_hour.ToString() + ",";
			output += m_used_game_count.ToString() + ",";
			return output;
		}
	}//class Tbl_Item

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Tbl_PlayerBetter
			: Tbl__PlayerBase
	{
		public Int16 m_batting_average; 	// [Ÿ��] 0.001~0.999 õ������ ǥ�� 
		public Int16 m_continue_homerun_count; 	// [����Ȩ����] ����_Ȩ���� 
		public Int16 m_homeruntotal_count; 	// [��_Ȩ����] ��_Ȩ���� 
		public Int16 m_single_homerun_count; 	// [�̱�Ȩ��ī��Ʈ] �̱�Ȩ�� ī��Ʈ 
		public Int16 m_tworun_homerun_count; 	// [����Ȩ��ī��Ʈ] ����Ȩ�� ī��Ʈ 
		public Int16 m_threerun_homerun_count; 	// [������Ȩ��ī��Ʈ] ������Ȩ�� ī��Ʈ 
		public Int16 m_grandslam_homerun_count; 	// [����Ȩ��ī��Ʈ] ����Ȩ�� ī��Ʈ 
		public Int16 m_one_hit_count; 	// [�Ϸ�Ÿī��Ʈ] �Ϸ�Ÿ ī��Ʈ 
		public Int16 m_double_hit_count; 	// [�̷�Ÿī��Ʈ] �̷�Ÿ ī��Ʈ 
		public Int16 m_triple_hit_count; 	// [���Ÿī��Ʈ] ���Ÿ ī��Ʈ 
		public Int16 m_foul_hit_count; 	// [�Ŀ�ī��Ʈ] �Ŀ� ī��Ʈ 
		public Int16 m_out_hit_count; 	// [�ƿ�ī��Ʈ] �ƿ� ī��Ʈ 
		public Int16 m_score_count; 	// [����ī��Ʈ] ���� ī��Ʈ 
		public EPlayerBetterSkill m_betting_type; 	// [Ÿ��Ÿ��]  
		public Int16 m_better_power; 	// [Ÿ�� �Ŀ�]  
		public Int16 m_better_focus; 	// [Ÿ�� ����]  
		public Int16 m_better_power_buff; 	// [Ÿ�� �Ŀ� ����]  
		public Int16 m_better_focus_buff; 	// [Ÿ�� ���� ����]  
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::batting_average",token[idx++], ref m_batting_average);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::continue_homerun_count",token[idx++], ref m_continue_homerun_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::homeruntotal_count",token[idx++], ref m_homeruntotal_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::single_homerun_count",token[idx++], ref m_single_homerun_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::tworun_homerun_count",token[idx++], ref m_tworun_homerun_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::threerun_homerun_count",token[idx++], ref m_threerun_homerun_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::grandslam_homerun_count",token[idx++], ref m_grandslam_homerun_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::one_hit_count",token[idx++], ref m_one_hit_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::double_hit_count",token[idx++], ref m_double_hit_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::triple_hit_count",token[idx++], ref m_triple_hit_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::foul_hit_count",token[idx++], ref m_foul_hit_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::out_hit_count",token[idx++], ref m_out_hit_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::score_count",token[idx++], ref m_score_count);
			nUtil.jString_EPlayerBetterSkill.Parse("Tbl_PlayerBetter::betting_type",token[idx++], ref m_betting_type);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::better_power",token[idx++], ref m_better_power);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::better_focus",token[idx++], ref m_better_focus);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::better_power_buff",token[idx++], ref m_better_power_buff);
			nUtil.jString_Int16.Parse("Tbl_PlayerBetter::better_focus_buff",token[idx++], ref m_better_focus_buff);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_batting_average.ToString() + ",";
			output += m_continue_homerun_count.ToString() + ",";
			output += m_homeruntotal_count.ToString() + ",";
			output += m_single_homerun_count.ToString() + ",";
			output += m_tworun_homerun_count.ToString() + ",";
			output += m_threerun_homerun_count.ToString() + ",";
			output += m_grandslam_homerun_count.ToString() + ",";
			output += m_one_hit_count.ToString() + ",";
			output += m_double_hit_count.ToString() + ",";
			output += m_triple_hit_count.ToString() + ",";
			output += m_foul_hit_count.ToString() + ",";
			output += m_out_hit_count.ToString() + ",";
			output += m_score_count.ToString() + ",";
			output += m_betting_type.ToString() + ",";
			output += m_better_power.ToString() + ",";
			output += m_better_focus.ToString() + ",";
			output += m_better_power_buff.ToString() + ",";
			output += m_better_focus_buff.ToString() + ",";
			return output;
		}
	}//class Tbl_PlayerBetter

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Tbl_PlayerPitcher
			: Tbl__PlayerBase
	{
		public Int16 m_pitching_average; 	// [�����] 0.001~0.999 õ������ ǥ�� 
		public Int16 m_hit_count; 	// [�Ǿ�Ÿ��] �Ǿ�Ÿ�� 
		public Int16 m_strikeout_count; 	// [Ż������] Ż������ 
		public Int16 m_homerun_pitching_count; 	// [��Ȩ����] ��Ȩ���� 
		public Int16 m_continue_strikeout_count; 	// [���ӻ�����] ���ӻ����� 
		public Int16 m_continue_homerun_pitching_count; 	// [������Ȩ����] ������Ȩ���� 
		public EPlayerPitcherSkill m_pitching_type; 	// [����Ÿ��]  
		public Int16 m_pitcher_control; 	// [���� ����]  
		public Int16 m_pitcher_ballspeed; 	// [���� ����]  
		public Int16 m_pitcher_breakingball_value; 	// [���� ��ȭ�� ��ġ]  
		public EPlayerBreakingBall m_pitcher_breakingball_type; 	// [���� ��ȭ������] ���� ��ȭ�� 
		public Int16 m_pitcher_control_buff; 	// [���� ���� ����]  
		public Int16 m_pitcher_ballspeed_buff; 	// [���� ���� ����]  
		public Int16 m_pitcher_breakingball_value_buff; 	// [���� ��ȭ�� ��ġ ����]  
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_Int16.Parse("Tbl_PlayerPitcher::pitching_average",token[idx++], ref m_pitching_average);
			nUtil.jString_Int16.Parse("Tbl_PlayerPitcher::hit_count",token[idx++], ref m_hit_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerPitcher::strikeout_count",token[idx++], ref m_strikeout_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerPitcher::homerun_pitching_count",token[idx++], ref m_homerun_pitching_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerPitcher::continue_strikeout_count",token[idx++], ref m_continue_strikeout_count);
			nUtil.jString_Int16.Parse("Tbl_PlayerPitcher::continue_homerun_pitching_count",token[idx++], ref m_continue_homerun_pitching_count);
			nUtil.jString_EPlayerPitcherSkill.Parse("Tbl_PlayerPitcher::pitching_type",token[idx++], ref m_pitching_type);
			nUtil.jString_Int16.Parse("Tbl_PlayerPitcher::pitcher_control",token[idx++], ref m_pitcher_control);
			nUtil.jString_Int16.Parse("Tbl_PlayerPitcher::pitcher_ballspeed",token[idx++], ref m_pitcher_ballspeed);
			nUtil.jString_Int16.Parse("Tbl_PlayerPitcher::pitcher_breakingball_value",token[idx++], ref m_pitcher_breakingball_value);
			nUtil.jString_EPlayerBreakingBall.Parse("Tbl_PlayerPitcher::pitcher_breakingball_type",token[idx++], ref m_pitcher_breakingball_type);
			nUtil.jString_Int16.Parse("Tbl_PlayerPitcher::pitcher_control_buff",token[idx++], ref m_pitcher_control_buff);
			nUtil.jString_Int16.Parse("Tbl_PlayerPitcher::pitcher_ballspeed_buff",token[idx++], ref m_pitcher_ballspeed_buff);
			nUtil.jString_Int16.Parse("Tbl_PlayerPitcher::pitcher_breakingball_value_buff",token[idx++], ref m_pitcher_breakingball_value_buff);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_pitching_average.ToString() + ",";
			output += m_hit_count.ToString() + ",";
			output += m_strikeout_count.ToString() + ",";
			output += m_homerun_pitching_count.ToString() + ",";
			output += m_continue_strikeout_count.ToString() + ",";
			output += m_continue_homerun_pitching_count.ToString() + ",";
			output += m_pitching_type.ToString() + ",";
			output += m_pitcher_control.ToString() + ",";
			output += m_pitcher_ballspeed.ToString() + ",";
			output += m_pitcher_breakingball_value.ToString() + ",";
			output += m_pitcher_breakingball_type.ToString() + ",";
			output += m_pitcher_control_buff.ToString() + ",";
			output += m_pitcher_ballspeed_buff.ToString() + ",";
			output += m_pitcher_breakingball_value_buff.ToString() + ",";
			return output;
		}
	}//class Tbl_PlayerPitcher

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Tbl_Result
	{
		public Tbl_Result_id_t m_grid; 	// [game������ȣ] �Ϻ� ��Ƽ�� Ű 
		public bool m_is_singlemode; 	// [is_singlemode] 0=��Ƽ�÷��� 1=�̱��÷��� 
		public Int32 m_ppid1; 	// [PP_ID] �÷��̾�1�� �Ǹ����̵��ȣ 
		public Tbl_User_id_t m_uid1; 	// [������ȣ] �÷��̾�1 ������ȣ 
		public string m_uname1; 	// [���� �г���] �÷��̾�1 ���̽��������� �����г��� 
		public Tbl_PlayerBetter_id_t m_pid_better1; 	// [Ÿ�� pid] �÷��̾�1 
		public Tbl_PlayerPitcher_id_t m_pid_pitcher1; 	// [���� pid] �÷��̾�1 
		public Int32 m_ppid2; 	// [PP_ID] �÷��̾�2 �Ǹ����̵��ȣ 
		public Tbl_User_id_t m_uid2; 	// [������ȣ] �÷��̾�2 ������ȣ 
		public string m_uname2; 	// [���� �г���] �÷��̾�2 ���̽��������� �����г��� 
		public Tbl_PlayerBetter_id_t m_pid_better2; 	// [Ÿ�� pid] �÷��̾�2 
		public Tbl_PlayerPitcher_id_t m_pid_pitcher2; 	// [���� pid] �÷��̾�2 
		public DATETIME m_time_start; 	// [���ӽ��۽ð�] ���� �Ͻ� 
		public DATETIME m_time_end; 	// [��������ð�] �÷��� �ð� 
		public Tbl_User_id_t m_winner; 	// [����] ���� 
		public Int32 m_reward_exp1; 	// [�÷��̾�1�� �������ġ] �÷��̾�1�� �������ġ 
		public Int32 m_reward_exp2; 	// [�������ġ] �������ġ 
		public Tbl_Item_id_t m_reward_item1; 	// [���������] ��������� 
		public Tbl_Item_id_t m_reward_item2; 	// [���������] ��������� 
		public game_money_t m_reward_gamemoney1; 	// [������ӸӴ�] ������ӸӴ� 
		public game_money_t m_reward_gamemoney2; 	// [������ӸӴ�] ������ӸӴ� 
		public Int16 m_score1; 	// [player1���ھ�]  
		public Int16 m_score2; 	// [player2���ھ�]  
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int64.Parse("Tbl_Result::grid",token[idx++], ref m_grid);
			nUtil.jString_bool.Parse("Tbl_Result::is_singlemode",token[idx++], ref m_is_singlemode);
			nUtil.jString_Int32.Parse("Tbl_Result::ppid1",token[idx++], ref m_ppid1);
			nUtil.jString_Int64.Parse("Tbl_Result::uid1",token[idx++], ref m_uid1);
			nUtil.jString_string.Parse("Tbl_Result::uname1",token[idx++], ref m_uname1);
			nUtil.jString_Int64.Parse("Tbl_Result::pid_better1",token[idx++], ref m_pid_better1);
			nUtil.jString_Int64.Parse("Tbl_Result::pid_pitcher1",token[idx++], ref m_pid_pitcher1);
			nUtil.jString_Int32.Parse("Tbl_Result::ppid2",token[idx++], ref m_ppid2);
			nUtil.jString_Int64.Parse("Tbl_Result::uid2",token[idx++], ref m_uid2);
			nUtil.jString_string.Parse("Tbl_Result::uname2",token[idx++], ref m_uname2);
			nUtil.jString_Int64.Parse("Tbl_Result::pid_better2",token[idx++], ref m_pid_better2);
			nUtil.jString_Int64.Parse("Tbl_Result::pid_pitcher2",token[idx++], ref m_pid_pitcher2);
			nUtil.jString_DATETIME.Parse("Tbl_Result::time_start",token[idx++], ref m_time_start);
			nUtil.jString_DATETIME.Parse("Tbl_Result::time_end",token[idx++], ref m_time_end);
			nUtil.jString_Int64.Parse("Tbl_Result::winner",token[idx++], ref m_winner);
			nUtil.jString_Int32.Parse("Tbl_Result::reward_exp1",token[idx++], ref m_reward_exp1);
			nUtil.jString_Int32.Parse("Tbl_Result::reward_exp2",token[idx++], ref m_reward_exp2);
			nUtil.jString_Int64.Parse("Tbl_Result::reward_item1",token[idx++], ref m_reward_item1);
			nUtil.jString_Int64.Parse("Tbl_Result::reward_item2",token[idx++], ref m_reward_item2);
			nUtil.jString_Int32.Parse("Tbl_Result::reward_gamemoney1",token[idx++], ref m_reward_gamemoney1);
			nUtil.jString_Int32.Parse("Tbl_Result::reward_gamemoney2",token[idx++], ref m_reward_gamemoney2);
			nUtil.jString_Int16.Parse("Tbl_Result::score1",token[idx++], ref m_score1);
			nUtil.jString_Int16.Parse("Tbl_Result::score2",token[idx++], ref m_score2);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_grid.ToString() + ",";
			output += m_is_singlemode.ToString() + ",";
			output += m_ppid1.ToString() + ",";
			output += m_uid1.ToString() + ",";
			output += m_uname1.ToString() + ",";
			output += m_pid_better1.ToString() + ",";
			output += m_pid_pitcher1.ToString() + ",";
			output += m_ppid2.ToString() + ",";
			output += m_uid2.ToString() + ",";
			output += m_uname2.ToString() + ",";
			output += m_pid_better2.ToString() + ",";
			output += m_pid_pitcher2.ToString() + ",";
			output += m_time_start.ToString() + ",";
			output += m_time_end.ToString() + ",";
			output += m_winner.ToString() + ",";
			output += m_reward_exp1.ToString() + ",";
			output += m_reward_exp2.ToString() + ",";
			output += m_reward_item1.ToString() + ",";
			output += m_reward_item2.ToString() + ",";
			output += m_reward_gamemoney1.ToString() + ",";
			output += m_reward_gamemoney2.ToString() + ",";
			output += m_score1.ToString() + ",";
			output += m_score2.ToString() + ",";
			return output;
		}
	}//class Tbl_Result

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Tbl_RoundResult
	{
		public Tbl_RoundResult_id_t m_grid2; 	// [������ȣ] �Ϻ� ��Ƽ�� Ű 
		public Tbl_Result_id_t m_grid; 	// [Tbl_Result_M�� ������ȣ]  
		public Int16 m_round_number; 	// [�����ȣ] 1~10�� ���� �Ѱ����� ��Ż����� Tbl_Result�� ���� 
		public Tbl_PlayerPitcher_id_t m_pid_better; 	// [better]  
		public Int16 m_score; 	// [better������]  
		public Int16 m_base_runner_count; 	// [��������ڼ�] �ִ�� xml����  i_max_runner_per_game=19�̴� 
		public EBetterHitType m_hit_type; 	// [��Ÿ����] 0=�ƿ� 1�Ϸ�Ÿ 2�̷�Ÿ 3���Ÿ 4�̱�Ȩ�� 5����Ȩ�� 6 
		public Int16 m_strike; 	// [��Ʈ����ī��Ʈ]  
		public Int16 m_foul; 	// [�Ŀ�ī��Ʈ]  
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int64.Parse("Tbl_RoundResult::grid2",token[idx++], ref m_grid2);
			nUtil.jString_Int64.Parse("Tbl_RoundResult::grid",token[idx++], ref m_grid);
			nUtil.jString_Int16.Parse("Tbl_RoundResult::round_number",token[idx++], ref m_round_number);
			nUtil.jString_Int64.Parse("Tbl_RoundResult::pid_better",token[idx++], ref m_pid_better);
			nUtil.jString_Int16.Parse("Tbl_RoundResult::score",token[idx++], ref m_score);
			nUtil.jString_Int16.Parse("Tbl_RoundResult::base_runner_count",token[idx++], ref m_base_runner_count);
			nUtil.jString_EBetterHitType.Parse("Tbl_RoundResult::hit_type",token[idx++], ref m_hit_type);
			nUtil.jString_Int16.Parse("Tbl_RoundResult::strike",token[idx++], ref m_strike);
			nUtil.jString_Int16.Parse("Tbl_RoundResult::foul",token[idx++], ref m_foul);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_grid2.ToString() + ",";
			output += m_grid.ToString() + ",";
			output += m_round_number.ToString() + ",";
			output += m_pid_better.ToString() + ",";
			output += m_score.ToString() + ",";
			output += m_base_runner_count.ToString() + ",";
			output += m_hit_type.ToString() + ",";
			output += m_strike.ToString() + ",";
			output += m_foul.ToString() + ",";
			return output;
		}
	}//class Tbl_RoundResult

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Tbl_User
	{
		public Tbl_User_id_t m_uid; 	// [������ȣ] db pk 
		public pimang_id_t m_ppid; 	// [PP_ID] �Ǹ����̵��ȣ 
		public string m_uname; 	// [�г���] ���̽��������� �����г��� 
		public Int16 m_pitcher_tot_win; 	// [����������_��] ����������_�� 
		public Int16 m_pitcher_tot_lose; 	// [����������_��] ����������_�� 
		public Int16 m_pitcher_tot_strikeout; 	// [Ż������] ������_Ż���� 
		public Int16 m_pitcher_tot_average_level; 	// [���������_����] ���������_���� 
		public Int16 m_better_tot_win; 	// [Ÿ��������_��] Ÿ��������_�� 
		public Int16 m_better_tot_lose; 	// [Ÿ��������_��] Ÿ��������_�� 
		public Int16 m_better_tot_homerun; 	// [��_Ȩ����] Ÿ����_Ȩ�� 
		public Int16 m_better_tot__average_level; 	// [Ÿ�������_����] Ÿ�������_���� 
		public Int16 m_cash_item_buy_count; 	// [ĳ���۱��Ű���] ĳ���۱��Ű��� 
		public DATETIME m_playtime_first; 	// [ù_�����÷��̽���_Ÿ��] ù_�÷��̽���_Ÿ�� 
		public DATETIME m_playtime_last; 	// [������_�÷���_Ÿ��] ������_�÷���_Ÿ�� 
		public Int64 m_playtime_tot; 	// [��_�÷���_Ÿ��] ��_�÷���_Ÿ��(��) 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_Int64.Parse("Tbl_User::uid",token[idx++], ref m_uid);
			nUtil.jString_Int32.Parse("Tbl_User::ppid",token[idx++], ref m_ppid);
			nUtil.jString_string.Parse("Tbl_User::uname",token[idx++], ref m_uname);
			nUtil.jString_Int16.Parse("Tbl_User::pitcher_tot_win",token[idx++], ref m_pitcher_tot_win);
			nUtil.jString_Int16.Parse("Tbl_User::pitcher_tot_lose",token[idx++], ref m_pitcher_tot_lose);
			nUtil.jString_Int16.Parse("Tbl_User::pitcher_tot_strikeout",token[idx++], ref m_pitcher_tot_strikeout);
			nUtil.jString_Int16.Parse("Tbl_User::pitcher_tot_average_level",token[idx++], ref m_pitcher_tot_average_level);
			nUtil.jString_Int16.Parse("Tbl_User::better_tot_win",token[idx++], ref m_better_tot_win);
			nUtil.jString_Int16.Parse("Tbl_User::better_tot_lose",token[idx++], ref m_better_tot_lose);
			nUtil.jString_Int16.Parse("Tbl_User::better_tot_homerun",token[idx++], ref m_better_tot_homerun);
			nUtil.jString_Int16.Parse("Tbl_User::better_tot__average_level",token[idx++], ref m_better_tot__average_level);
			nUtil.jString_Int16.Parse("Tbl_User::cash_item_buy_count",token[idx++], ref m_cash_item_buy_count);
			nUtil.jString_DATETIME.Parse("Tbl_User::playtime_first",token[idx++], ref m_playtime_first);
			nUtil.jString_DATETIME.Parse("Tbl_User::playtime_last",token[idx++], ref m_playtime_last);
			nUtil.jString_Int64.Parse("Tbl_User::playtime_tot",token[idx++], ref m_playtime_tot);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_uid.ToString() + ",";
			output += m_ppid.ToString() + ",";
			output += m_uname.ToString() + ",";
			output += m_pitcher_tot_win.ToString() + ",";
			output += m_pitcher_tot_lose.ToString() + ",";
			output += m_pitcher_tot_strikeout.ToString() + ",";
			output += m_pitcher_tot_average_level.ToString() + ",";
			output += m_better_tot_win.ToString() + ",";
			output += m_better_tot_lose.ToString() + ",";
			output += m_better_tot_homerun.ToString() + ",";
			output += m_better_tot__average_level.ToString() + ",";
			output += m_cash_item_buy_count.ToString() + ",";
			output += m_playtime_first.ToString() + ",";
			output += m_playtime_last.ToString() + ",";
			output += m_playtime_tot.ToString() + ",";
			return output;
		}
	}//class Tbl_User

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_ItemEquip
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_ItemEquip>		m_List = new List<Sys_ItemEquip> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_ItemEquip >>>");
			foreach (Sys_ItemEquip p in CSV_Sys_ItemEquip.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_ItemEquip       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_ItemEquip FindBy_name(string key){return (Sys_ItemEquip)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_ItemEquip p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_ItemEquip info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_ItemEquip();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_ItemEquip


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_ItemConsume
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_ItemConsume>		m_List = new List<Sys_ItemConsume> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_ItemConsume >>>");
			foreach (Sys_ItemConsume p in CSV_Sys_ItemConsume.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_ItemConsume       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_ItemConsume FindBy_name(string key){return (Sys_ItemConsume)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_ItemConsume p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_ItemConsume info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_ItemConsume();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_ItemConsume


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_ItemStuff
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_ItemStuff>		m_List = new List<Sys_ItemStuff> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_ItemStuff >>>");
			foreach (Sys_ItemStuff p in CSV_Sys_ItemStuff.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_ItemStuff       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_ItemStuff FindBy_name(string key){return (Sys_ItemStuff)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_ItemStuff p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_ItemStuff info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_ItemStuff();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_ItemStuff


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_MainItemAbility
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_MainItemAbility>		m_List = new List<Sys_MainItemAbility> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_MainItemAbility >>>");
			foreach (Sys_MainItemAbility p in CSV_Sys_MainItemAbility.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_MainItemAbility       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_MainItemAbility FindBy_name(string key){return (Sys_MainItemAbility)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_MainItemAbility p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_MainItemAbility info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_MainItemAbility();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_MainItemAbility


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_Package
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Package>		m_List = new List<Sys_Package> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Package >>>");
			foreach (Sys_Package p in CSV_Sys_Package.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_Package       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_Package FindBy_name(string key){return (Sys_Package)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_Package p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_Package info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_Package();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_Package


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_PlayerCard
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_PlayerCard>		m_List = new List<Sys_PlayerCard> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_PlayerCard >>>");
			foreach (Sys_PlayerCard p in CSV_Sys_PlayerCard.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_PlayerCard       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_PlayerCard FindBy_name(string key){return (Sys_PlayerCard)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_PlayerCard p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_PlayerCard info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_PlayerCard();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_PlayerCard


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_PlayerLevel
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_PlayerLevel>		m_List = new List<Sys_PlayerLevel> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_PlayerLevel >>>");
			foreach (Sys_PlayerLevel p in CSV_Sys_PlayerLevel.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_PlayerLevel       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_PlayerLevel FindBy_name(string key){return (Sys_PlayerLevel)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_PlayerLevel p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_PlayerLevel info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_PlayerLevel();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_PlayerLevel


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_PlayerSkillSticker
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_PlayerSkillSticker>		m_List = new List<Sys_PlayerSkillSticker> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_PlayerSkillSticker >>>");
			foreach (Sys_PlayerSkillSticker p in CSV_Sys_PlayerSkillSticker.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_PlayerSkillSticker       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_PlayerSkillSticker FindBy_name(string key){return (Sys_PlayerSkillSticker)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_PlayerSkillSticker p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_PlayerSkillSticker info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_PlayerSkillSticker();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_PlayerSkillSticker


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_Quest
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Quest>		m_List = new List<Sys_Quest> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Quest >>>");
			foreach (Sys_Quest p in CSV_Sys_Quest.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_Quest       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_Quest FindBy_name(string key){return (Sys_Quest)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_Quest p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_Quest info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_Quest();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_Quest


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_RandomGift
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_RandomGift>		m_List = new List<Sys_RandomGift> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_RandomGift >>>");
			foreach (Sys_RandomGift p in CSV_Sys_RandomGift.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_RandomGift       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_RandomGift FindBy_name(string key){return (Sys_RandomGift)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_RandomGift p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_RandomGift info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_RandomGift();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_RandomGift


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_SubItemAbility
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_SubItemAbility>		m_List = new List<Sys_SubItemAbility> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_SubItemAbility >>>");
			foreach (Sys_SubItemAbility p in CSV_Sys_SubItemAbility.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_SubItemAbility       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
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
				Sys_SubItemAbility info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_SubItemAbility();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_SubItemAbility



	


}//namespace nEXCEL
