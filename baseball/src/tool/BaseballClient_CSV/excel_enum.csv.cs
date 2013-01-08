/*------------------------------------------------------------


command line : 
Excel_Converter.exe D:\svn\baseball\doc\design\excel\code\excel_enum.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_string_table.txt 

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
	// enum�� �ڵ� ���ø� ����
	// -------------------------------------------------

	public enum EBaseballObjectType : byte
	{
		eBEGIN_EBaseballObjectType=0,
		BOT_user = 1, // [����] ����
		BOT_pitcher = 2, // [����] ����
		BOT_better = 3, // [Ÿ��] Ÿ��
		BOT_team = 4, // [��] ��
		eEND_EBaseballObjectType,
	}
	namespace nUtil
	{
		public class jString_EBaseballObjectType
		{
			public static void Parse(string sDebug,string sVal, ref EBaseballObjectType eVal) 
			{
				eVal = (EBaseballObjectType)Enum.Parse(typeof(EBaseballObjectType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EBaseballObjectType i = EBaseballObjectType.eBEGIN_EBaseballObjectType +1;i < EBaseballObjectType.eEND_EBaseballObjectType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EBaseballObjectType> get_enums() 
			{
				List<EBaseballObjectType> list = new List<EBaseballObjectType>();
				for (EBaseballObjectType i = EBaseballObjectType.eBEGIN_EBaseballObjectType +1;i < EBaseballObjectType.eEND_EBaseballObjectType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EBatterAbility : byte
	{
		eBEGIN_EBatterAbility=0,
		BA_NULL = 1, // [����] ����
		BA_LEFT = 2, // [��������] ���������� �Ŀ� ����. ������ BA_RIGHT��ƼĿ�� ����������
		BA_RIGHT = 3, // [�������] ������� ���� �Ŀ� ����. ������ BA_LEFT��ƼĿ�� ����������
		BA_HOMERUN = 4, // [Ȩ��Ÿ��] ��Ʈ�� �Ŀ� ����
		BA_WIDE = 5, // [����Ÿ��] ����Ÿ�� - �о������� �Ŀ� �ٿ����
		BA_FULLHIT = 6, // [Ǯ����] Ǯ���� - ��������� �Ŀ� ����
		BA_LOWHIT = 7, // [�κ�����] �κ����� - Ÿ�������� �ϴ�/�ߴܿ��� �Ŀ� ����
		BA_HIGHHIT = 8, // [���̺�����] ���̺����� - �ߴ�# ��ܿ��� �Ŀ� ����
		BA_RUNFIRE = 9, // [����] ���� - �ٷ� ����Ÿ������ Ȩ���� �Ŀ� ����
		eEND_EBatterAbility,
	}
	namespace nUtil
	{
		public class jString_EBatterAbility
		{
			public static void Parse(string sDebug,string sVal, ref EBatterAbility eVal) 
			{
				eVal = (EBatterAbility)Enum.Parse(typeof(EBatterAbility), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EBatterAbility i = EBatterAbility.eBEGIN_EBatterAbility +1;i < EBatterAbility.eEND_EBatterAbility; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EBatterAbility> get_enums() 
			{
				List<EBatterAbility> list = new List<EBatterAbility>();
				for (EBatterAbility i = EBatterAbility.eBEGIN_EBatterAbility +1;i < EBatterAbility.eEND_EBatterAbility; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EBatterForm : byte
	{
		eBEGIN_EBatterForm=0,
		BF_SQUARE = 1, // [������] ������
		BF_OPEN = 2, // [����] ����
		BF_CLOSE = 3, // [ũ�����] ũ�����
		BF_NULL = 4, // [����] ����
		BF_COMMON = 5, // [����] ����
		eEND_EBatterForm,
	}
	namespace nUtil
	{
		public class jString_EBatterForm
		{
			public static void Parse(string sDebug,string sVal, ref EBatterForm eVal) 
			{
				eVal = (EBatterForm)Enum.Parse(typeof(EBatterForm), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EBatterForm i = EBatterForm.eBEGIN_EBatterForm +1;i < EBatterForm.eEND_EBatterForm; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EBatterForm> get_enums() 
			{
				List<EBatterForm> list = new List<EBatterForm>();
				for (EBatterForm i = EBatterForm.eBEGIN_EBatterForm +1;i < EBatterForm.eEND_EBatterForm; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EBatterHitType : byte
	{
		eBEGIN_EBatterHitType=0,
		EBHT_STANDOUT = 1, // [���ĵ�ƿ�] ���ĵ�ƿ�
		EBHT_SWINGOUT = 2, // [�����ƿ�] �����ƿ�
		EBHT_FOULOUT = 3, // [�Ŀ�ƿ�] �Ŀ�ƿ�
		EBIT_INFIELDOUT = 4, // [���߾ƿ�] ���߾ƿ�
		EBIT_LEFTFIELDOUT = 5, // [���ͼ��ƿ�] ���ͼ��ƿ�
		EBIT_CENTERFIELDOUT = 6, // [�߰߼��ƿ�] �߰߼��ƿ�
		EBIT_RIGHTFIELDOUT = 7, // [���ͼ��ƿ�] ���ͼ��ƿ�
		EBHT_NO_HIT = 8, // [ġ�����ѻ���] �� �̻��� �ƿ����¸� ��Ÿ�������� ��
		EBHT_ONEHIT = 9, // [�Ϸ�Ÿ] �Ϸ�Ÿ
		EBHT_DOUBLEHIT = 10, // [�̷�Ÿ] �̷�Ÿ
		EBHT_TRIPLEHIT = 11, // [���Ÿ] ���Ÿ
		EBHT_HOMERUN = 12, // [Ȩ��] Ȩ��
		eEND_EBatterHitType,
	}
	namespace nUtil
	{
		public class jString_EBatterHitType
		{
			public static void Parse(string sDebug,string sVal, ref EBatterHitType eVal) 
			{
				eVal = (EBatterHitType)Enum.Parse(typeof(EBatterHitType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EBatterHitType i = EBatterHitType.eBEGIN_EBatterHitType +1;i < EBatterHitType.eEND_EBatterHitType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EBatterHitType> get_enums() 
			{
				List<EBatterHitType> list = new List<EBatterHitType>();
				for (EBatterHitType i = EBatterHitType.eBEGIN_EBatterHitType +1;i < EBatterHitType.eEND_EBatterHitType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EBreakingBallPitch : byte
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
		public class jString_EBreakingBallPitch
		{
			public static void Parse(string sDebug,string sVal, ref EBreakingBallPitch eVal) 
			{
				eVal = (EBreakingBallPitch)Enum.Parse(typeof(EBreakingBallPitch), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EBreakingBallPitch i = EBreakingBallPitch.eBEGIN_EBreakingBallPitch +1;i < EBreakingBallPitch.eEND_EBreakingBallPitch; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EBreakingBallPitch> get_enums() 
			{
				List<EBreakingBallPitch> list = new List<EBreakingBallPitch>();
				for (EBreakingBallPitch i = EBreakingBallPitch.eBEGIN_EBreakingBallPitch +1;i < EBreakingBallPitch.eEND_EBreakingBallPitch; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EBreakingBallRotation : byte
	{
		eBEGIN_EBreakingBallRotation=0,
		EBBR_REGULAR = 1, // [��ȸ��] ��ȸ��
		EBBR_REVERSE = 2, // [��ȸ��] ��ȸ��
		EBBR_NOTHING = 3, // [��ȸ��] ��ȸ��
		eEND_EBreakingBallRotation,
	}
	namespace nUtil
	{
		public class jString_EBreakingBallRotation
		{
			public static void Parse(string sDebug,string sVal, ref EBreakingBallRotation eVal) 
			{
				eVal = (EBreakingBallRotation)Enum.Parse(typeof(EBreakingBallRotation), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EBreakingBallRotation i = EBreakingBallRotation.eBEGIN_EBreakingBallRotation +1;i < EBreakingBallRotation.eEND_EBreakingBallRotation; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EBreakingBallRotation> get_enums() 
			{
				List<EBreakingBallRotation> list = new List<EBreakingBallRotation>();
				for (EBreakingBallRotation i = EBreakingBallRotation.eBEGIN_EBreakingBallRotation +1;i < EBreakingBallRotation.eEND_EBreakingBallRotation; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum ECategoryString : byte
	{
		eBEGIN_ECategoryString=0,
		ECS_ITEM = 1, // [������] �����۰��� ��Ʈ��. Text1=�̸� text2=���� �� ����������϶��� text2=Ÿ�ڿ뼳�� text3=�����뼳��
		ECS_GUI = 2, // [GUI] ȭ�� GUI�� ��Ʈ��
		ECS_SKILL = 3, // [��ų��] ��ų�� ��Ʈ��, text1=�̸� text2=����
		ECS_ETC = 4, // [��Ÿ] �׿� ��Ʈ��
		eEND_ECategoryString,
	}
	namespace nUtil
	{
		public class jString_ECategoryString
		{
			public static void Parse(string sDebug,string sVal, ref ECategoryString eVal) 
			{
				eVal = (ECategoryString)Enum.Parse(typeof(ECategoryString), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (ECategoryString i = ECategoryString.eBEGIN_ECategoryString +1;i < ECategoryString.eEND_ECategoryString; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<ECategoryString> get_enums() 
			{
				List<ECategoryString> list = new List<ECategoryString>();
				for (ECategoryString i = ECategoryString.eBEGIN_ECategoryString +1;i < ECategoryString.eEND_ECategoryString; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EConsumeItemEffect : byte
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
		public class jString_EConsumeItemEffect
		{
			public static void Parse(string sDebug,string sVal, ref EConsumeItemEffect eVal) 
			{
				eVal = (EConsumeItemEffect)Enum.Parse(typeof(EConsumeItemEffect), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EConsumeItemEffect i = EConsumeItemEffect.eBEGIN_EConsumeItemEffect +1;i < EConsumeItemEffect.eEND_EConsumeItemEffect; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EConsumeItemEffect> get_enums() 
			{
				List<EConsumeItemEffect> list = new List<EConsumeItemEffect>();
				for (EConsumeItemEffect i = EConsumeItemEffect.eBEGIN_EConsumeItemEffect +1;i < EConsumeItemEffect.eEND_EConsumeItemEffect; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EEventType : byte
	{
		eBEGIN_EEventType=0,
		ET_MONEY = 1, // [�Ӵ�] �Ӵ�
		ET_ITEM = 2, // [������] ������
		ET_MONEY_ITEM = 3, // [�Ӵ�_������] �Ӵ�_������
		eEND_EEventType,
	}
	namespace nUtil
	{
		public class jString_EEventType
		{
			public static void Parse(string sDebug,string sVal, ref EEventType eVal) 
			{
				eVal = (EEventType)Enum.Parse(typeof(EEventType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EEventType i = EEventType.eBEGIN_EEventType +1;i < EEventType.eEND_EEventType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EEventType> get_enums() 
			{
				List<EEventType> list = new List<EEventType>();
				for (EEventType i = EEventType.eBEGIN_EEventType +1;i < EEventType.eEND_EEventType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EGestureType : byte
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
		public class jString_EGestureType
		{
			public static void Parse(string sDebug,string sVal, ref EGestureType eVal) 
			{
				eVal = (EGestureType)Enum.Parse(typeof(EGestureType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EGestureType i = EGestureType.eBEGIN_EGestureType +1;i < EGestureType.eEND_EGestureType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EGestureType> get_enums() 
			{
				List<EGestureType> list = new List<EGestureType>();
				for (EGestureType i = EGestureType.eBEGIN_EGestureType +1;i < EGestureType.eEND_EGestureType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EGiftCategory : byte
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
		public class jString_EGiftCategory
		{
			public static void Parse(string sDebug,string sVal, ref EGiftCategory eVal) 
			{
				eVal = (EGiftCategory)Enum.Parse(typeof(EGiftCategory), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EGiftCategory i = EGiftCategory.eBEGIN_EGiftCategory +1;i < EGiftCategory.eEND_EGiftCategory; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EGiftCategory> get_enums() 
			{
				List<EGiftCategory> list = new List<EGiftCategory>();
				for (EGiftCategory i = EGiftCategory.eBEGIN_EGiftCategory +1;i < EGiftCategory.eEND_EGiftCategory; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EGiftType : byte
	{
		eBEGIN_EGiftType=0,
		EGT_NULL = 1, // [����] ����
		EGT_GAMEMONEY = 2, // [���ӸӴ�] ���ӸӴ�
		EGT_PLAYERSKILLSTICKER = 3, // [��ų��ƼĿ] ��ų��ƼĿ
		EGT_PLAYERCARD = 4, // [�÷��̾�ī��] �÷��̾�ī��
		EGT_GAMECASH = 5, // [���� ĳ��] ����ĳ��
		eEND_EGiftType,
	}
	namespace nUtil
	{
		public class jString_EGiftType
		{
			public static void Parse(string sDebug,string sVal, ref EGiftType eVal) 
			{
				eVal = (EGiftType)Enum.Parse(typeof(EGiftType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EGiftType i = EGiftType.eBEGIN_EGiftType +1;i < EGiftType.eEND_EGiftType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EGiftType> get_enums() 
			{
				List<EGiftType> list = new List<EGiftType>();
				for (EGiftType i = EGiftType.eBEGIN_EGiftType +1;i < EGiftType.eEND_EGiftType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EGradeAllitemType : byte
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
		public class jString_EGradeAllitemType
		{
			public static void Parse(string sDebug,string sVal, ref EGradeAllitemType eVal) 
			{
				eVal = (EGradeAllitemType)Enum.Parse(typeof(EGradeAllitemType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EGradeAllitemType i = EGradeAllitemType.eBEGIN_EGradeAllitemType +1;i < EGradeAllitemType.eEND_EGradeAllitemType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EGradeAllitemType> get_enums() 
			{
				List<EGradeAllitemType> list = new List<EGradeAllitemType>();
				for (EGradeAllitemType i = EGradeAllitemType.eBEGIN_EGradeAllitemType +1;i < EGradeAllitemType.eEND_EGradeAllitemType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EHitTimmingType : byte
	{
		eBEGIN_EHitTimmingType=0,
		EHTT_eHitTime_None = 0, // [Ŭ���̾�Ʈ��] Ŭ���̾�Ʈ�� (���� 0_���������� ó������ ����)
		EHTT_eHitTime_VeryFast = 1, // [�ſ� ����] �ſ� ����
		EHTT_eHitTime_Fast = 2, // [����] ����
		EHTT_eHitTime_GoodFast = 3, // [���� ����] ���� ����
		EHTT_eHitTime_Perfect = 4, // [����Ʈ ����] ����Ʈ ����
		EHTT_eHitTime_GoodSlow = 5, // [���� ����] ���� ����
		EHTT_eHitTime_Slow = 6, // [����] ����
		EHTT_eHitTime_VerySlow = 7, // [�ſ� ����] �ſ� ����
		eEND_EHitTimmingType,
	}
	namespace nUtil
	{
		public class jString_EHitTimmingType
		{
			public static void Parse(string sDebug,string sVal, ref EHitTimmingType eVal) 
			{
				eVal = (EHitTimmingType)Enum.Parse(typeof(EHitTimmingType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EHitTimmingType i = EHitTimmingType.eBEGIN_EHitTimmingType +1;i < EHitTimmingType.eEND_EHitTimmingType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EHitTimmingType> get_enums() 
			{
				List<EHitTimmingType> list = new List<EHitTimmingType>();
				for (EHitTimmingType i = EHitTimmingType.eBEGIN_EHitTimmingType +1;i < EHitTimmingType.eEND_EHitTimmingType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EHitType : byte
	{
		eBEGIN_EHitType=0,
		EHT_eNS_NONE = 0, // [Ŭ���̾�Ʈ��] Ŭ���̾�Ʈ�� (���� 0_���������� ó������ ����)
		EHT_eNS_BALLHIT = 1, // [�Ϲ� ��Ʈ] �Ϲ� ��Ʈ
		EHT_eNS_BALLHITSTRONG = 2, // [����_��Ʈ�� ��Ʈ] ����_��Ʈ�� ��Ʈ
		EHT_eNS_SWING = 3, // [�꽺��] �꽺��
		EHT_eNS_NOTHING = 4, // [��� ����] ��� ����
		eEND_EHitType,
	}
	namespace nUtil
	{
		public class jString_EHitType
		{
			public static void Parse(string sDebug,string sVal, ref EHitType eVal) 
			{
				eVal = (EHitType)Enum.Parse(typeof(EHitType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EHitType i = EHitType.eBEGIN_EHitType +1;i < EHitType.eEND_EHitType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EHitType> get_enums() 
			{
				List<EHitType> list = new List<EHitType>();
				for (EHitType i = EHitType.eBEGIN_EHitType +1;i < EHitType.eEND_EHitType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EItemAbilityType : byte
	{
		eBEGIN_EItemAbilityType=0,
		IAT_POWER = 1, // [�Ŀ�] �Ŀ�
		IAT_ACCURACY = 2, // [��Ȯ] ��Ȯ
		IAT_FOCUS = 3, // [����] ����
		IAT_SPEED = 4, // [����] ����
		IAT_BREAKINGBALL = 5, // [��ȭ��] ��ȭ��
		IAT_ALLABILITY = 6, // [��罺��] ��罺��
		IAT_NULL = 7, // [����] ����
		eEND_EItemAbilityType,
	}
	namespace nUtil
	{
		public class jString_EItemAbilityType
		{
			public static void Parse(string sDebug,string sVal, ref EItemAbilityType eVal) 
			{
				eVal = (EItemAbilityType)Enum.Parse(typeof(EItemAbilityType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EItemAbilityType i = EItemAbilityType.eBEGIN_EItemAbilityType +1;i < EItemAbilityType.eEND_EItemAbilityType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EItemAbilityType> get_enums() 
			{
				List<EItemAbilityType> list = new List<EItemAbilityType>();
				for (EItemAbilityType i = EItemAbilityType.eBEGIN_EItemAbilityType +1;i < EItemAbilityType.eEND_EItemAbilityType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EItemBuyType : byte
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
		public class jString_EItemBuyType
		{
			public static void Parse(string sDebug,string sVal, ref EItemBuyType eVal) 
			{
				eVal = (EItemBuyType)Enum.Parse(typeof(EItemBuyType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EItemBuyType i = EItemBuyType.eBEGIN_EItemBuyType +1;i < EItemBuyType.eEND_EItemBuyType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EItemBuyType> get_enums() 
			{
				List<EItemBuyType> list = new List<EItemBuyType>();
				for (EItemBuyType i = EItemBuyType.eBEGIN_EItemBuyType +1;i < EItemBuyType.eEND_EItemBuyType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EItemCategory : byte
	{
		eBEGIN_EItemCategory=0,
		IC_EQUIP = 1, // [�������] �������
		IC_CONSUME = 2, // [�Ҹ������] �Ҹ������
		IC_STUFF = 3, // [��������] ��������
		IC_NULL = 4, // [����] ����
		eEND_EItemCategory,
	}
	namespace nUtil
	{
		public class jString_EItemCategory
		{
			public static void Parse(string sDebug,string sVal, ref EItemCategory eVal) 
			{
				eVal = (EItemCategory)Enum.Parse(typeof(EItemCategory), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EItemCategory i = EItemCategory.eBEGIN_EItemCategory +1;i < EItemCategory.eEND_EItemCategory; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EItemCategory> get_enums() 
			{
				List<EItemCategory> list = new List<EItemCategory>();
				for (EItemCategory i = EItemCategory.eBEGIN_EItemCategory +1;i < EItemCategory.eEND_EItemCategory; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EItemCategoryEquipment : byte
	{
		eBEGIN_EItemCategoryEquipment=0,
		ICE_SHIRT = 1, // [����] ����
		ICE_PANT = 2, // [����] ����
		ICE_CAP = 3, // [����] ���� ���ξ�����#
		ICE_SHOES_B = 4, // [Ÿ�� �Ź�] Ÿ�� �Ź� ���ξ�����#
		ICE_SHOES_P = 5, // [���� �Ź�] ���� �Ź� ���ξ�����#
		ICE_GLOVE = 6, // [�����۷���] �����۷��� ���ξ�����#
		ICE_U_SHIRT = 7, // [�������] �������
		ICE_SOCKS = 8, // [�縻] �縻
		ICE_ARM_GUARDS = 9, // [��_��ȣ��] ��_��ȣ��
		ICE_LEG_GUARDS = 10, // [�ٸ�_��ȣ��] �ٸ�_��ȣ��
		ICE_BAT = 11, // [��Ʈ] ��Ʈ ���ξ�����
		ICE_BALL = 12, // [��] �� ���ξ�����#
		ICE_HELMET = 13, // [���] ��� ���ξ�����#
		ICE_GLOBE = 14, // [Ÿ���尩] Ÿ�ڿ� �尩 ���ξ�����#
		ICE_WRISTBAND = 15, // [����Ʈ ���] �ո� �ƴ�
		ICE_NECKLACE = 16, // [�����] �����
		ICE_RING = 17, // [����] ����
		ICE_EARRING = 18, // [�Ͱ���] �Ͱ���
		ICE_TATOO = 19, // [����] ����
		ICE_SUNGLASS = 20, // [���۶�] ���۶�
		ICE_EYEPATCH = 21, // [������ġ] �� �� ��ġ
		ICE_BEARD = 22, // [����] ����
		ICE_HAIR_M = 23, // [������Ÿ��] ������Ÿ��
		ICE_HAIR_W = 24, // [������Ÿ��] ������Ÿ��
		ICE_HAIR_COLOR = 25, // [���Į��] ���Į��
		ICE_PATCH = 26, // [��ġ] ��ġ
		ICE_MASK = 27, // [����ũ] ����ũ
		ICE_BACKNUMBER = 28, // [���ȣ ������] ���ȣ ������
		ICE_MAKING = 29, // [��ŷ ������] ��ŷ ������
		ICE_FACE = 30, // [��] ��
		ICE_ARM = 31, // [��] ��
		ICE_LEG = 32, // [�ٸ�(����)] �ٸ�(����)
		ICE_LEFTHAND = 33, // [�޼�] �޼�
		ICE_RIGHTHAND = 34, // [������] ������
		eEND_EItemCategoryEquipment,
	}
	namespace nUtil
	{
		public class jString_EItemCategoryEquipment
		{
			public static void Parse(string sDebug,string sVal, ref EItemCategoryEquipment eVal) 
			{
				eVal = (EItemCategoryEquipment)Enum.Parse(typeof(EItemCategoryEquipment), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EItemCategoryEquipment i = EItemCategoryEquipment.eBEGIN_EItemCategoryEquipment +1;i < EItemCategoryEquipment.eEND_EItemCategoryEquipment; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EItemCategoryEquipment> get_enums() 
			{
				List<EItemCategoryEquipment> list = new List<EItemCategoryEquipment>();
				for (EItemCategoryEquipment i = EItemCategoryEquipment.eBEGIN_EItemCategoryEquipment +1;i < EItemCategoryEquipment.eEND_EItemCategoryEquipment; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EItemGradeType : byte
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
		public class jString_EItemGradeType
		{
			public static void Parse(string sDebug,string sVal, ref EItemGradeType eVal) 
			{
				eVal = (EItemGradeType)Enum.Parse(typeof(EItemGradeType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EItemGradeType i = EItemGradeType.eBEGIN_EItemGradeType +1;i < EItemGradeType.eEND_EItemGradeType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EItemGradeType> get_enums() 
			{
				List<EItemGradeType> list = new List<EItemGradeType>();
				for (EItemGradeType i = EItemGradeType.eBEGIN_EItemGradeType +1;i < EItemGradeType.eEND_EItemGradeType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EItemPriceType : byte
	{
		eBEGIN_EItemPriceType=0,
		IPT_CASH = 1, // [ĳ��] ĳ�� �θ� ����ִ� ������
		IPT_CASH_POINT = 2, // [ĳ��_����Ʈ] ĳ�� �Ǵ� ����Ʈ �� ��� �ִ� ������
		IPT_MONEY = 3, // [����Ʈ] ĳ�� �Ǵ� ����Ʈ# ���ӸӴϷ� ��� �ִ� ������
		eEND_EItemPriceType,
	}
	namespace nUtil
	{
		public class jString_EItemPriceType
		{
			public static void Parse(string sDebug,string sVal, ref EItemPriceType eVal) 
			{
				eVal = (EItemPriceType)Enum.Parse(typeof(EItemPriceType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EItemPriceType i = EItemPriceType.eBEGIN_EItemPriceType +1;i < EItemPriceType.eEND_EItemPriceType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EItemPriceType> get_enums() 
			{
				List<EItemPriceType> list = new List<EItemPriceType>();
				for (EItemPriceType i = EItemPriceType.eBEGIN_EItemPriceType +1;i < EItemPriceType.eEND_EItemPriceType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EItemReuseType : byte
	{
		eBEGIN_EItemReuseType=0,
		IUT_NORMAL = 1, // [����] ����
		IUT_INSTANTLY = 2, // [�Ⱓ��] �Ⱓ�� Ƚ�� ���� �� ������ �� ���
		IUT_FIXED = 3, // [�Ұ�] �Ұ�
		eEND_EItemReuseType,
	}
	namespace nUtil
	{
		public class jString_EItemReuseType
		{
			public static void Parse(string sDebug,string sVal, ref EItemReuseType eVal) 
			{
				eVal = (EItemReuseType)Enum.Parse(typeof(EItemReuseType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EItemReuseType i = EItemReuseType.eBEGIN_EItemReuseType +1;i < EItemReuseType.eEND_EItemReuseType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EItemReuseType> get_enums() 
			{
				List<EItemReuseType> list = new List<EItemReuseType>();
				for (EItemReuseType i = EItemReuseType.eBEGIN_EItemReuseType +1;i < EItemReuseType.eEND_EItemReuseType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EItemSellStatus : byte
	{
		eBEGIN_EItemSellStatus=0,
		ISS_SELL_STOP = 1, // [�Ǹ�����] �Ǹ�����( �Ǹ��ϴٰ� ��å�� ���� ������)
		ISS_SELL = 2, // [�Ǹ���] �Ǹ���
		ISS_SELL_PLAN = 3, // [�Ǹſ���] �Ǹſ���
		eEND_EItemSellStatus,
	}
	namespace nUtil
	{
		public class jString_EItemSellStatus
		{
			public static void Parse(string sDebug,string sVal, ref EItemSellStatus eVal) 
			{
				eVal = (EItemSellStatus)Enum.Parse(typeof(EItemSellStatus), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EItemSellStatus i = EItemSellStatus.eBEGIN_EItemSellStatus +1;i < EItemSellStatus.eEND_EItemSellStatus; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EItemSellStatus> get_enums() 
			{
				List<EItemSellStatus> list = new List<EItemSellStatus>();
				for (EItemSellStatus i = EItemSellStatus.eBEGIN_EItemSellStatus +1;i < EItemSellStatus.eEND_EItemSellStatus; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EItemSexType : byte
	{
		eBEGIN_EItemSexType=0,
		IST_MAN_ONLY = 1, // [��] 
		IST_WOMAN_ONLY = 2, // [��] 
		IST_COMMON = 3, // [����] 
		eEND_EItemSexType,
	}
	namespace nUtil
	{
		public class jString_EItemSexType
		{
			public static void Parse(string sDebug,string sVal, ref EItemSexType eVal) 
			{
				eVal = (EItemSexType)Enum.Parse(typeof(EItemSexType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EItemSexType i = EItemSexType.eBEGIN_EItemSexType +1;i < EItemSexType.eEND_EItemSexType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EItemSexType> get_enums() 
			{
				List<EItemSexType> list = new List<EItemSexType>();
				for (EItemSexType i = EItemSexType.eBEGIN_EItemSexType +1;i < EItemSexType.eEND_EItemSexType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EItemState : byte
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
		public class jString_EItemState
		{
			public static void Parse(string sDebug,string sVal, ref EItemState eVal) 
			{
				eVal = (EItemState)Enum.Parse(typeof(EItemState), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EItemState i = EItemState.eBEGIN_EItemState +1;i < EItemState.eEND_EItemState; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EItemState> get_enums() 
			{
				List<EItemState> list = new List<EItemState>();
				for (EItemState i = EItemState.eBEGIN_EItemState +1;i < EItemState.eEND_EItemState; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EItemSubGradeType : byte
	{
		eBEGIN_EItemSubGradeType=0,
		ISGT_EE = 1, // [EE���] EE���
		ISGT_DE = 2, // [DE���] DE���
		ISGT_DD = 3, // [DD���] DD���
		ISGT_CE = 4, // [CE���] CE���
		ISGT_CD = 5, // [CD���] CD���
		ISGT_CC = 6, // [CC���] CC���
		ISGT_BE = 7, // [BE���] BE���
		ISGT_BD = 8, // [BD���] BD���
		ISGT_BC = 9, // [BC���] BC���
		ISGT_BB = 10, // [BB���] BB���
		ISGT_AE = 11, // [AE���] AE���
		ISGT_AD = 12, // [AD���] AD���
		ISGT_AC = 13, // [AC���] AC���
		ISGT_AB = 14, // [AB���] AB���
		ISGT_AA = 15, // [AA���] AA���
		ISGT_SE = 16, // [SE���] SE���
		ISGT_SD = 17, // [SD���] SD���
		ISGT_SC = 18, // [SC���] SC���
		ISGT_SB = 19, // [SB���] SB���
		ISGT_SA = 20, // [SA���] SA���
		ISGT_SS = 21, // [SS���] SS���
		ISGT_NULL = 22, // [��޾���] ��޾���(NULL�� ��� �ش� ����� ����)
		eEND_EItemSubGradeType,
	}
	namespace nUtil
	{
		public class jString_EItemSubGradeType
		{
			public static void Parse(string sDebug,string sVal, ref EItemSubGradeType eVal) 
			{
				eVal = (EItemSubGradeType)Enum.Parse(typeof(EItemSubGradeType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EItemSubGradeType i = EItemSubGradeType.eBEGIN_EItemSubGradeType +1;i < EItemSubGradeType.eEND_EItemSubGradeType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EItemSubGradeType> get_enums() 
			{
				List<EItemSubGradeType> list = new List<EItemSubGradeType>();
				for (EItemSubGradeType i = EItemSubGradeType.eBEGIN_EItemSubGradeType +1;i < EItemSubGradeType.eEND_EItemSubGradeType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EItemUpgradeResult : byte
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
		public class jString_EItemUpgradeResult
		{
			public static void Parse(string sDebug,string sVal, ref EItemUpgradeResult eVal) 
			{
				eVal = (EItemUpgradeResult)Enum.Parse(typeof(EItemUpgradeResult), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EItemUpgradeResult i = EItemUpgradeResult.eBEGIN_EItemUpgradeResult +1;i < EItemUpgradeResult.eEND_EItemUpgradeResult; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EItemUpgradeResult> get_enums() 
			{
				List<EItemUpgradeResult> list = new List<EItemUpgradeResult>();
				for (EItemUpgradeResult i = EItemUpgradeResult.eBEGIN_EItemUpgradeResult +1;i < EItemUpgradeResult.eEND_EItemUpgradeResult; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum ELogType : byte
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
		public class jString_ELogType
		{
			public static void Parse(string sDebug,string sVal, ref ELogType eVal) 
			{
				eVal = (ELogType)Enum.Parse(typeof(ELogType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (ELogType i = ELogType.eBEGIN_ELogType +1;i < ELogType.eEND_ELogType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<ELogType> get_enums() 
			{
				List<ELogType> list = new List<ELogType>();
				for (ELogType i = ELogType.eBEGIN_ELogType +1;i < ELogType.eEND_ELogType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum ENoticeType : byte
	{
		eBEGIN_ENoticeType=0,
		NT_LED = 1, // [������] ������
		NT_CHECK = 2, // [�ӽ�����] �ӽ�����
		NT_NOTICE = 3, // [��������] ��������
		eEND_ENoticeType,
	}
	namespace nUtil
	{
		public class jString_ENoticeType
		{
			public static void Parse(string sDebug,string sVal, ref ENoticeType eVal) 
			{
				eVal = (ENoticeType)Enum.Parse(typeof(ENoticeType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (ENoticeType i = ENoticeType.eBEGIN_ENoticeType +1;i < ENoticeType.eEND_ENoticeType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<ENoticeType> get_enums() 
			{
				List<ENoticeType> list = new List<ENoticeType>();
				for (ENoticeType i = ENoticeType.eBEGIN_ENoticeType +1;i < ENoticeType.eEND_ENoticeType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum ENpcSituationString : byte
	{
		eBEGIN_ENpcSituationString=0,
		ENSS_STANDING_BY = 1, // [�����] ����� �Ͻ� ���
		ENSS_SELECTION = 2, // [���� ��] ���ý� ���
		ENSS_UPGRADE_WORKING = 3, // [���׷��̵� ��] ���׷��̵� �� �Ͻ� ���
		ENSS_TRANING_WORKING = 4, // [Ʈ���̴� ��] Ʈ���̴� �� �Ͻ� ���
		ENSS_COMPLETE = 5, // [�Ϸ�] �Ϸ� �ÿ� ���
		ENSS_UPGRADE_RESULT = 6, // [���׷��̵� ���] ���׷��̵� ���  ���
		ENSS_TRANING_RESULT = 7, // [Ʈ���̴� ���] Ʈ���̴� ���  ���
		eEND_ENpcSituationString,
	}
	namespace nUtil
	{
		public class jString_ENpcSituationString
		{
			public static void Parse(string sDebug,string sVal, ref ENpcSituationString eVal) 
			{
				eVal = (ENpcSituationString)Enum.Parse(typeof(ENpcSituationString), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (ENpcSituationString i = ENpcSituationString.eBEGIN_ENpcSituationString +1;i < ENpcSituationString.eEND_ENpcSituationString; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<ENpcSituationString> get_enums() 
			{
				List<ENpcSituationString> list = new List<ENpcSituationString>();
				for (ENpcSituationString i = ENpcSituationString.eBEGIN_ENpcSituationString +1;i < ENpcSituationString.eEND_ENpcSituationString; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum ENpcString : byte
	{
		eBEGIN_ENpcString=0,
		ENS_MAESTRO = 1, // [����] ����
		ENS_COACH = 2, // [������ġ] ������ġ
		eEND_ENpcString,
	}
	namespace nUtil
	{
		public class jString_ENpcString
		{
			public static void Parse(string sDebug,string sVal, ref ENpcString eVal) 
			{
				eVal = (ENpcString)Enum.Parse(typeof(ENpcString), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (ENpcString i = ENpcString.eBEGIN_ENpcString +1;i < ENpcString.eEND_ENpcString; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<ENpcString> get_enums() 
			{
				List<ENpcString> list = new List<ENpcString>();
				for (ENpcString i = ENpcString.eBEGIN_ENpcString +1;i < ENpcString.eEND_ENpcString; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EPitcherAbility : byte
	{
		eBEGIN_EPitcherAbility=0,
		PA_NULL = 1, // [����] ����
		PA_LEFT = 2, // [����Ÿ��] ��Ÿ�ڻ��� �ɷ�ġ����. PA_RIGHT�Ӽ��� ��ų ��ƼĿ�� ����������
		PA_RIGHT = 3, // [���Ÿ��] ��Ÿ�ڻ��� �ɷ�ġ����. PA_LEFT�Ӽ��� ��ų ��ƼĿ�� ������ ����
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
		public class jString_EPitcherAbility
		{
			public static void Parse(string sDebug,string sVal, ref EPitcherAbility eVal) 
			{
				eVal = (EPitcherAbility)Enum.Parse(typeof(EPitcherAbility), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EPitcherAbility i = EPitcherAbility.eBEGIN_EPitcherAbility +1;i < EPitcherAbility.eEND_EPitcherAbility; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EPitcherAbility> get_enums() 
			{
				List<EPitcherAbility> list = new List<EPitcherAbility>();
				for (EPitcherAbility i = EPitcherAbility.eBEGIN_EPitcherAbility +1;i < EPitcherAbility.eEND_EPitcherAbility; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EPitcherForm : byte
	{
		eBEGIN_EPitcherForm=0,
		PF_OVER = 1, // [����] ����
		PF_THREEQUARTER = 2, // [��������] ��������
		PF_SIDEARM = 3, // [���̵��] ���̵��
		PF_UNDER = 4, // [���] ���
		PF_NULL = 5, // [����] ����
		PF_COMMON = 6, // [����] ����
		eEND_EPitcherForm,
	}
	namespace nUtil
	{
		public class jString_EPitcherForm
		{
			public static void Parse(string sDebug,string sVal, ref EPitcherForm eVal) 
			{
				eVal = (EPitcherForm)Enum.Parse(typeof(EPitcherForm), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EPitcherForm i = EPitcherForm.eBEGIN_EPitcherForm +1;i < EPitcherForm.eEND_EPitcherForm; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EPitcherForm> get_enums() 
			{
				List<EPitcherForm> list = new List<EPitcherForm>();
				for (EPitcherForm i = EPitcherForm.eBEGIN_EPitcherForm +1;i < EPitcherForm.eEND_EPitcherForm; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EPlayer_Onoffline : byte
	{
		eBEGIN_EPlayer_Onoffline=0,
		EPO_ONPLAYER = 1, // [�¶����÷��̾�] �¶����÷��̾�
		EPO_OFFPLAYER = 2, // [���������÷��̾�] ���������÷��̾�
		eEND_EPlayer_Onoffline,
	}
	namespace nUtil
	{
		public class jString_EPlayer_Onoffline
		{
			public static void Parse(string sDebug,string sVal, ref EPlayer_Onoffline eVal) 
			{
				eVal = (EPlayer_Onoffline)Enum.Parse(typeof(EPlayer_Onoffline), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EPlayer_Onoffline i = EPlayer_Onoffline.eBEGIN_EPlayer_Onoffline +1;i < EPlayer_Onoffline.eEND_EPlayer_Onoffline; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EPlayer_Onoffline> get_enums() 
			{
				List<EPlayer_Onoffline> list = new List<EPlayer_Onoffline>();
				for (EPlayer_Onoffline i = EPlayer_Onoffline.eBEGIN_EPlayer_Onoffline +1;i < EPlayer_Onoffline.eEND_EPlayer_Onoffline; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EPlayerBodyType : byte
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
		public class jString_EPlayerBodyType
		{
			public static void Parse(string sDebug,string sVal, ref EPlayerBodyType eVal) 
			{
				eVal = (EPlayerBodyType)Enum.Parse(typeof(EPlayerBodyType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EPlayerBodyType i = EPlayerBodyType.eBEGIN_EPlayerBodyType +1;i < EPlayerBodyType.eEND_EPlayerBodyType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EPlayerBodyType> get_enums() 
			{
				List<EPlayerBodyType> list = new List<EPlayerBodyType>();
				for (EPlayerBodyType i = EPlayerBodyType.eBEGIN_EPlayerBodyType +1;i < EPlayerBodyType.eEND_EPlayerBodyType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EPlayerBreakingBall : byte
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
		public class jString_EPlayerBreakingBall
		{
			public static void Parse(string sDebug,string sVal, ref EPlayerBreakingBall eVal) 
			{
				eVal = (EPlayerBreakingBall)Enum.Parse(typeof(EPlayerBreakingBall), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EPlayerBreakingBall i = EPlayerBreakingBall.eBEGIN_EPlayerBreakingBall +1;i < EPlayerBreakingBall.eEND_EPlayerBreakingBall; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EPlayerBreakingBall> get_enums() 
			{
				List<EPlayerBreakingBall> list = new List<EPlayerBreakingBall>();
				for (EPlayerBreakingBall i = EPlayerBreakingBall.eBEGIN_EPlayerBreakingBall +1;i < EPlayerBreakingBall.eEND_EPlayerBreakingBall; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EPlayerGradeType : byte
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
		public class jString_EPlayerGradeType
		{
			public static void Parse(string sDebug,string sVal, ref EPlayerGradeType eVal) 
			{
				eVal = (EPlayerGradeType)Enum.Parse(typeof(EPlayerGradeType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EPlayerGradeType i = EPlayerGradeType.eBEGIN_EPlayerGradeType +1;i < EPlayerGradeType.eEND_EPlayerGradeType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EPlayerGradeType> get_enums() 
			{
				List<EPlayerGradeType> list = new List<EPlayerGradeType>();
				for (EPlayerGradeType i = EPlayerGradeType.eBEGIN_EPlayerGradeType +1;i < EPlayerGradeType.eEND_EPlayerGradeType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EPlayerNationType : byte
	{
		eBEGIN_EPlayerNationType=0,
		PNT_KOREA = 1, // [�ѱ�] �ѱ�
		PNT_USA = 2, // [�̱�] �̱�
		PNT_JAPAN = 3, // [�Ϻ�] �Ϻ�
		PNT_CHINA = 4, // [�߱�] �߱�
		PNT_CANADA = 5, // [ĳ����] ĳ����
		PNT_ITALY = 6, // [��Ż����] ��Ż����
		PNT_TAIWAN = 7, // [�븸] �븸
		PNT_AUSTRALIA = 8, // [ȣ��] ȣ��
		PNT_NETHERLANDS = 9, // [�״�����] �״�����
		PNT_CUBA = 10, // [���] ���
		PNT_TRINIDADANDTOBAGO = 11, // [Ʈ���ϴٵ���ٰ�] Ʈ���ϴٵ���ٰ�
		PNT_DOMINICANREPUBLIC = 12, // [���̴�ī��ȭ��] ���̴�ī��ȭ��
		PNT_PANAMA = 13, // [�ĳ���] �ĳ���
		PNT_PUERTORICO = 14, // [Ǫ�����丮��] Ǫ�����丮��
		PNT_REPUBLICOFSOUTHAFRICA = 15, // [��������ī��ȭ��] ��������ī��ȭ��
		PNT_VENEZUELA = 16, // [���׼�����] ���׼�����
		PNT_UNITEDKINGDOM = 17, // [����] ����
		PNT_SPAIN = 18, // [������] ������
		PNT_FRANCE = 19, // [������] ������
		PNT_GERMANY = 20, // [����] ����
		eEND_EPlayerNationType,
	}
	namespace nUtil
	{
		public class jString_EPlayerNationType
		{
			public static void Parse(string sDebug,string sVal, ref EPlayerNationType eVal) 
			{
				eVal = (EPlayerNationType)Enum.Parse(typeof(EPlayerNationType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EPlayerNationType i = EPlayerNationType.eBEGIN_EPlayerNationType +1;i < EPlayerNationType.eEND_EPlayerNationType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EPlayerNationType> get_enums() 
			{
				List<EPlayerNationType> list = new List<EPlayerNationType>();
				for (EPlayerNationType i = EPlayerNationType.eBEGIN_EPlayerNationType +1;i < EPlayerNationType.eEND_EPlayerNationType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EPlayerType : byte
	{
		eBEGIN_EPlayerType=0,
		PT_BATTER = 1, // [Ÿ��] Ÿ��
		PT_PITCHER = 2, // [����] ����
		PT_COMMON = 3, // [����] Ÿ���������о���
		PT_CATCHER = 4, // [����] ����
		PT_UMPIRE = 5, // [����] ����
		eEND_EPlayerType,
	}
	namespace nUtil
	{
		public class jString_EPlayerType
		{
			public static void Parse(string sDebug,string sVal, ref EPlayerType eVal) 
			{
				eVal = (EPlayerType)Enum.Parse(typeof(EPlayerType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EPlayerType i = EPlayerType.eBEGIN_EPlayerType +1;i < EPlayerType.eEND_EPlayerType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EPlayerType> get_enums() 
			{
				List<EPlayerType> list = new List<EPlayerType>();
				for (EPlayerType i = EPlayerType.eBEGIN_EPlayerType +1;i < EPlayerType.eEND_EPlayerType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EQuestConditionType : byte
	{
		eBEGIN_EQuestConditionType=0,
		QCT_NULL = 1, // [����] ����
		QCT_EQUIPGRADETYPE = 12, // [��ü�����������] ��ü������������� condition1�� �ִ� ���� ����(EItemGradeType)�� �ش��ϸ� ������ �ش�
		QCT_CASHCOUNT = 13, // [ĳ���۱�������] ĳ���۱�������
		QCT_GAMEMONEYCOUNT = 14, // [���ӸӴϴ�������] ���ӸӴϴ�������
		QCT_PLAYERALLSTATCOUNT = 15, // [ĳ���͸��ɷ�ġ�޼�����] ĳ���͸��ɷ�ġ�޼�����. ���Ҽ��� ����Ÿ�ڰ� ���ÿ� �ش� �ɷ�ġ ���޽� �ش�. pitcher_breakingball�� ���ǿ��� ����
		QCT_GAME_VALIABLE = 16, // [���Ӻ���] ������ ���ӳ������� ����. ���Ӻ����� ���������Ͻÿ�
		QCT_MANUAL_FINISH = 17, // [���ǿϷ�] Ʃ�丮�� or ��������Ʈ�� �Ϸ������� EQuestType������ ������.�Ϸ��뺸
		eEND_EQuestConditionType,
	}
	namespace nUtil
	{
		public class jString_EQuestConditionType
		{
			public static void Parse(string sDebug,string sVal, ref EQuestConditionType eVal) 
			{
				eVal = (EQuestConditionType)Enum.Parse(typeof(EQuestConditionType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EQuestConditionType i = EQuestConditionType.eBEGIN_EQuestConditionType +1;i < EQuestConditionType.eEND_EQuestConditionType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EQuestConditionType> get_enums() 
			{
				List<EQuestConditionType> list = new List<EQuestConditionType>();
				for (EQuestConditionType i = EQuestConditionType.eBEGIN_EQuestConditionType +1;i < EQuestConditionType.eEND_EQuestConditionType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EQuestType : byte
	{
		eBEGIN_EQuestType=0,
		EQT_MATCH = 1, // [MATCH ����Ʈ] MATCH ����Ʈ
		EQT_SINGLE = 2, // [SINGLE ����Ʈ] SINGLE ����Ʈ
		EQT_FRIENDLY = 3, // [FRIENDLY ����Ʈ] FRIENDLY ����Ʈ
		EQT_ITEMETC = 4, // [ITEM_ETC ����Ʈ] ITEM_ETC ����Ʈ
		EQT_INGAMETUTORIAL = 5, // [TUTORIAL] �ΰ��� Ʃ�丮��. �Ϸ������� Ŭ���̾�Ʈ�� üũ�� ������.(x2ug_quest_end)
		EQT_DAILY = 6, // [DAILY ����Ʈ] DAILIY ����Ʈ. (���� condition_value1�ǰ��� 0~100������ Ȯ�������� �ǹ��Ѵ�.)
		eEND_EQuestType,
	}
	namespace nUtil
	{
		public class jString_EQuestType
		{
			public static void Parse(string sDebug,string sVal, ref EQuestType eVal) 
			{
				eVal = (EQuestType)Enum.Parse(typeof(EQuestType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EQuestType i = EQuestType.eBEGIN_EQuestType +1;i < EQuestType.eEND_EQuestType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EQuestType> get_enums() 
			{
				List<EQuestType> list = new List<EQuestType>();
				for (EQuestType i = EQuestType.eBEGIN_EQuestType +1;i < EQuestType.eEND_EQuestType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum ERhythmJudge : byte
	{
		eBEGIN_ERhythmJudge=0,
		ERJ_eJudge_None = 0, // [Ŭ���̾�Ʈ��] Ŭ���̾�Ʈ�� (���� 0_���������� ó������ ����)
		ERJ_eJudge_Bad = 1, // [���] ���
		ERJ_eJudge_Normal = 2, // [���] ���
		ERJ_eJudge_Good = 3, // [��] ��
		ERJ_eJudge_Perfect = 4, // [����Ʈ] ����Ʈ
		eEND_ERhythmJudge,
	}
	namespace nUtil
	{
		public class jString_ERhythmJudge
		{
			public static void Parse(string sDebug,string sVal, ref ERhythmJudge eVal) 
			{
				eVal = (ERhythmJudge)Enum.Parse(typeof(ERhythmJudge), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (ERhythmJudge i = ERhythmJudge.eBEGIN_ERhythmJudge +1;i < ERhythmJudge.eEND_ERhythmJudge; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<ERhythmJudge> get_enums() 
			{
				List<ERhythmJudge> list = new List<ERhythmJudge>();
				for (ERhythmJudge i = ERhythmJudge.eBEGIN_ERhythmJudge +1;i < ERhythmJudge.eEND_ERhythmJudge; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EShopBatterSection : byte
	{
		eBEGIN_EShopBatterSection=0,
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
		eEND_EShopBatterSection,
	}
	namespace nUtil
	{
		public class jString_EShopBatterSection
		{
			public static void Parse(string sDebug,string sVal, ref EShopBatterSection eVal) 
			{
				eVal = (EShopBatterSection)Enum.Parse(typeof(EShopBatterSection), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EShopBatterSection i = EShopBatterSection.eBEGIN_EShopBatterSection +1;i < EShopBatterSection.eEND_EShopBatterSection; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EShopBatterSection> get_enums() 
			{
				List<EShopBatterSection> list = new List<EShopBatterSection>();
				for (EShopBatterSection i = EShopBatterSection.eBEGIN_EShopBatterSection +1;i < EShopBatterSection.eEND_EShopBatterSection; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EShopConsumeSection : byte
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
		public class jString_EShopConsumeSection
		{
			public static void Parse(string sDebug,string sVal, ref EShopConsumeSection eVal) 
			{
				eVal = (EShopConsumeSection)Enum.Parse(typeof(EShopConsumeSection), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EShopConsumeSection i = EShopConsumeSection.eBEGIN_EShopConsumeSection +1;i < EShopConsumeSection.eEND_EShopConsumeSection; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EShopConsumeSection> get_enums() 
			{
				List<EShopConsumeSection> list = new List<EShopConsumeSection>();
				for (EShopConsumeSection i = EShopConsumeSection.eBEGIN_EShopConsumeSection +1;i < EShopConsumeSection.eEND_EShopConsumeSection; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EShopItemType : byte
	{
		eBEGIN_EShopItemType=0,
		ESIT_Sys_Package = 1, // [��Ű��] ��Ű��
		ESIT_Sys_ItemEquip = 2, // [����������] ����������
		ESIT_Sys_ItemStuff = 3, // [��������] ��������
		ESIT_Sys_ItemConsume = 4, // [�Ҹ������] �Ҹ������
		ESIT_Sys_PlayerSkillSticker = 5, // [��ȭ��������] ��ȭ��������(��ȭ�� ���� �� ��ȭ���� ���ѵǾ��ִ� ���� �����ϰ� ���� ����#  ��ȭ�� ���׷��̵�--)���� ��ȭ�� ����� ����(--�� �״�� ����)
		eEND_EShopItemType,
	}
	namespace nUtil
	{
		public class jString_EShopItemType
		{
			public static void Parse(string sDebug,string sVal, ref EShopItemType eVal) 
			{
				eVal = (EShopItemType)Enum.Parse(typeof(EShopItemType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EShopItemType i = EShopItemType.eBEGIN_EShopItemType +1;i < EShopItemType.eEND_EShopItemType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EShopItemType> get_enums() 
			{
				List<EShopItemType> list = new List<EShopItemType>();
				for (EShopItemType i = EShopItemType.eBEGIN_EShopItemType +1;i < EShopItemType.eEND_EShopItemType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EShopPitcherSection : byte
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
		public class jString_EShopPitcherSection
		{
			public static void Parse(string sDebug,string sVal, ref EShopPitcherSection eVal) 
			{
				eVal = (EShopPitcherSection)Enum.Parse(typeof(EShopPitcherSection), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EShopPitcherSection i = EShopPitcherSection.eBEGIN_EShopPitcherSection +1;i < EShopPitcherSection.eEND_EShopPitcherSection; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EShopPitcherSection> get_enums() 
			{
				List<EShopPitcherSection> list = new List<EShopPitcherSection>();
				for (EShopPitcherSection i = EShopPitcherSection.eBEGIN_EShopPitcherSection +1;i < EShopPitcherSection.eEND_EShopPitcherSection; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum ETotalGameType : byte
	{
		eBEGIN_ETotalGameType=0,
		TGT_Match = 1, // [��ġ] ��ġ
		TGT_Single = 2, // [�̱�] �̱�
		TGT_Friendly = 3, // [�����鸮] �����鸮
		eEND_ETotalGameType,
	}
	namespace nUtil
	{
		public class jString_ETotalGameType
		{
			public static void Parse(string sDebug,string sVal, ref ETotalGameType eVal) 
			{
				eVal = (ETotalGameType)Enum.Parse(typeof(ETotalGameType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (ETotalGameType i = ETotalGameType.eBEGIN_ETotalGameType +1;i < ETotalGameType.eEND_ETotalGameType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<ETotalGameType> get_enums() 
			{
				List<ETotalGameType> list = new List<ETotalGameType>();
				for (ETotalGameType i = ETotalGameType.eBEGIN_ETotalGameType +1;i < ETotalGameType.eEND_ETotalGameType; i++){list.Add(i);}
				return list;
			}
		}
	}


	


}//namespace nEXCEL
