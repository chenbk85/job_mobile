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
	// enum형 코드 템플릿 정의
	// -------------------------------------------------

	public enum EBetterHitType
	{
		eBEGIN_EBetterHitType=0,
		EBHT_OUT = 1, // [아웃] 아웃
		EBHT_ONEHIT = 2, // [일루타] 일루타
		EBHT_DOUBLEHIT = 3, // [이루타] 이루타
		EBHT_TRIPLEHIT = 4, // [삼루타] 삼루타
		EBHT_SINGLEHOMERUN = 5, // [싱글홈런] 싱글홈런
		EBHT_TWORUNHOMERUN = 6, // [더블홈런] 더블홈런
		EBHT_THREERUNHOMERUN = 7, // [쓰리런홈런] 쓰리런홈런
		EBHT_GRANDSLAMHOMERUN = 8, // [만루홈런] 만루홈런
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
		ECCT_NULL = 1, // [없음] 없음
		ECCT_ACORNER = 2, // [유망주] 유망주
		ECCT_LEGEND = 3, // [레전드] 레전드
		ECCT_DESTROYFRIENDSHIP = 4, // [우정파괴자] 우정파괴자
		ECCT_SLUGGER = 5, // [슬러거] 슬러거
		ECCT_DOCTORK = 6, // [닥터K] 닥터K
		ECCT_FINALKING = 7, // [끝판왕] 끝판왕
		ECCT_SCROOGE = 8, // [스크루지] 스크루지
		ECCT_VVIP = 9, // [고객님] 고객님
		ECCT_ACE = 10, // [에이스] 에이스
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
		CIE_MONEYUP = 1, // [게임머니배수상승아이템] 게임시 보상으로 받는 머니의 지급 배수 상승(1000분율) 예를 들어consume_item_effect_value값이 500이면 50%올려줌
		CIE_EXPUP = 2, // [경험치배수상승아이템] 게임시 보상으로 받는 경험치의 지급 배수 상승
		CIE_ITEMDROPUP = 3, // [아이템드롭확률상승아이템] 게임시 보상으로 받는 아이템의 지급 확률 상승
		CIE_STATUPWHILE = 4, // [능력치일시상승아이템] 게임시 기존의 가지고 있는 스텟을 일시적으로 상승
		CIE_STATUPFOREVER = 5, // [능력치영구상승아이템] 게임시 기존의 가지고 있는 스텟을 영구적으로 상승
		CIE_UPGRADELUCKYUP = 6, // [강화확률증가아이템] 메인아이템 강화시 확률 증가
		CIE_UPGRADETIMEDOWN = 7, // [강화시간감소아이템] 메인아이템 강화시 시간 감소
		CIE_UPGRADECANCEL = 8, // [강화취소아이템] 강화 완료한 메인아이템의 강화 취소
		CIE_ITEMUSEDOWN = 9, // [아이템사용가능레벨하향] 아이템의 사용가능 레벨을 하향
		CIE_ETC = 10, // [ETC] 기타. 해당아이템별로 기능정의
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
		ET_MONEY = 1, // [머니] 머니
		ET_ITEM = 2, // [아이템] 아이템
		ET_MONEY_ITEM = 3, // [머니_아이템] 머니_아이템
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
		EGC_SINGLEGAMEWIN = 1, // [싱글게임승] 싱글게임승
		EGC_SINGLEGAMELOSE = 2, // [싱글게임패] 싱글게임패
		EGC_MATCHGAMEWIN = 3, // [대전게임승] 대전게임승
		EGC_MATCHGAMELOSE = 4, // [대전게임패] 대전게임패
		EGC_FRIENDGAMEWIN = 5, // [친구게임승] 친구게임승
		EGC_FRIENDGAMELOSE = 6, // [친구게임패] 친구게임패
		EGC_TRAININGWIN = 7, // [트레이닝승] 트레이닝승
		EGC_TRAININGLOSE = 8, // [트레이닝패] 트레이닝패
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
		EGT_NULL = 1, // [없음] 없음
		EGT_EXP = 2, // [경험치] 경험치
		EGT_GAMEMONEY = 3, // [게임머니] 게임머니
		EGT_PLAYERSKILLSTICKER = 4, // [스킬스티커] 스킬스티커
		EGT_PLAYERCARD = 5, // [플레이어카드] 플레이어카드
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
		EGAT_NULL = 1, // [없음] 없음
		EGAT_SMAINITEMALL = 2, // [S급 메인아이템 모두] S급 메인아이템 모두
		EGAT_AMAINITEMALL = 3, // [A급 메인아이템 모두] A급 메인아이템 모두
		EGAT_BMAINITEMALL = 4, // [B급 메인아이템 모두] B급 메인아이템 모두
		EGAT_CMAINITEMALL = 5, // [C급 메인아이템 모두] C급 메인아이템 모두
		EGAT_DMAINITEMALL = 6, // [D급 메인아이템 모두] D급 메인아이템 모두
		EGAT_EMAINITEMALL = 7, // [E급 메인아이템 모두] E급 메인아이템 모두
		EGAT_SSUBITEMALL = 8, // [S급 서브아이템 모두] S급 서브아이템 모두
		EGAT_ASUBITEMALL = 9, // [A급 서브아이템 모두] A급 서브아이템 모두
		EGAT_BSUBITEMALL = 10, // [B급 서브아이템 모두] B급 서브아이템 모두
		EGAT_CSUBITEMALL = 11, // [C급 서브아이템 모두] C급 서브아이템 모두
		EGAT_DSUBITEMALL = 12, // [D급 서브아이템 모두] D급 서브아이템 모두
		EGAT_ESUBITEMALL = 13, // [E급 서브아이템 모두] E급 서브아이템 모두
		EGAT_SCONSUMEITEMALL = 14, // [S급 소비아이템 모두] S급 소비아이템 모두
		EGAT_ACONSUMEITEMALL = 15, // [A급 소비아이템 모두] A급 소비아이템 모두
		EGAT_BCONSUMEITEMALL = 16, // [B급 소비아이템 모두] B급 소비아이템 모두
		EGAT_CCONSUMEITEMALL = 17, // [C급 소비아이템 모두] C급 소비아이템 모두
		EGAT_DCONSUMEITEMALL = 18, // [D급 소비아이템 모두] D급 소비아이템 모두
		EGAT_ECONSUMEITEMALL = 19, // [E급 소비아이템 모두] E급 소비아이템 모두
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
		IAT_POWER = 1, // [파워] 파워
		IAT_ACCURACY = 2, // [정확] 정확
		IAT_BALLCONTROL = 3, // [제구] 제구
		IAT_SPEED = 4, // [구속] 구속
		IAT_BREAKINGBALL = 5, // [변화구] 변화구
		IAT_ALLABILITY = 6, // [모든스텟] 모든스텟
		IAT_NULL = 7, // [없음] 없음
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
		IBT_BUY_CASH = 1, // [캐쉬 구매 아이템] 캐쉬 구매 아이템
		IBT_CHARGE_POINT = 2, // [포인트 충전 아이템] 포인트 충전 아이템
		IBT_BUY_POINT = 3, // [포인트 구매 아이템] 포인트 구매 아이템
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
		IC_NULL = 1, // [없음] 없음
		IC_EQUIPMENT = 2, // [착용장비] 착용장비
		IC_CONSUME = 3, // [소모아이템] 소모아이템
		IC_STUFF = 4, // [재료아이템] 재료아이템
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
		ICE_SHIRT = 1, // [상의] 상의
		ICE_PANT = 2, // [하의] 하의
		ICE_CAP = 3, // [모자] 모자 메인아이템,
		ICE_SHOES = 4, // [신발] 신발 메인아이템,
		ICE_GLOVE = 5, // [투수글러브] 투수글러브 메인아이템,
		ICE_U_SHIRT = 6, // [언더셔츠] 언더셔츠
		ICE_SOCKS = 7, // [양말] 양말
		ICE_ARM_GUARDS = 8, // [팔_보호대] 팔_보호대
		ICE_LEG_GUARDS = 9, // [다리_보호대] 다리_보호대
		ICE_BET = 10, // [배트] 배트 메인아이템
		ICE_BALL = 11, // [볼] 볼 메인아이템,
		ICE_HELMET = 12, // [헬멧] 헬멧 메인아이템,
		ICE_GLOBE = 13, // [타자장갑] 타자용 장갑 메인아이템,
		ICE_WRISTBAND = 14, // [리스트 밴드] 손목 아대
		ICE_NECKLACE = 15, // [목걸이] 목걸이
		ICE_RING = 16, // [반지] 반지
		ICE_EARRING = 17, // [귀걸이] 귀걸이
		ICE_TATOO = 18, // [문신] 문신
		ICE_SUNGLASS = 19, // [선글라스] 선글라스
		ICE_EYEPATCH = 20, // [아이패치] 눈 밑 패치
		ICE_BEARD = 21, // [수염] 수염
		ICE_HAIR_M = 22, // [남성헤어스타일] 남성헤어스타일
		ICE_HAIR_W = 23, // [여성헤어스타일] 여성헤어스타일
		ICE_PATCH = 24, // [패치] 패치
		ICE_MASK = 25, // [마스크] 마스크
		ICE_BACKNUMBER = 26, // [등번호 아이템] 등번호 아이템
		ICE_MAKING = 27, // [마킹 아이템] 마킹 아이템
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
		IGT_E = 1, // [E등급] E - EE 로 업글가능
		IGT_D = 2, // [D등급] D - DE , DD로 업글가능
		IGT_C = 3, // [C등급] C - CE ,CD,CC로 업글가능
		IGT_B = 4, // [B등급] B- BE,BD,BC,BB로 업글가능
		IGT_A = 5, // [A등급] A- AE,AD,AC,AB,AA로 업글가능
		IGT_S = 6, // [S등급] S-SE,SD,SC,SB,SA,SS로 업글가능
		IGT_NULL = 7, // [무등급] 등급없음.  데코레이션 아이템…
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
		IPT_CASH = 1, // [캐쉬] 캐쉬 로만 살수있는 아이템
		IPT_CASH_POINT = 2, // [캐쉬_포인트] 캐쉬 또는 포인트 로 살수 있는 아이템
		IPT_MONEY = 3, // [포인트] 캐쉬 또는 포인트,게임머니로 살수 있는 아이템
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
		IUT_NORMAL = 1, // [가능] 가능
		IUT_INSTANTLY = 2, // [기간제] 기간내 횟수 소진 다 했으면 재 사용
		IUT_FIXED = 3, // [불가] 불가
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
		ISS_SELL_STOP = 1, // [판매중지] 판매중지( 판매하다가 정책상 폐기된 아이템)
		ISS_SELL = 2, // [판매중] 판매중
		ISS_SELL_PLAN = 3, // [판매예정] 판매예정
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
		IST_MAN_ONLY = 1, // [남] 
		IST_WOMAN_ONLY = 2, // [여] 
		IST_COMMON = 3, // [공용] 
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
		IUR_HELMET = 1, // [헬멧] 헬멧
		IUR_CAP = 2, // [모자] 모자
		IUR_BET = 3, // [배트] 배트
		IUR_BALL = 4, // [볼] 볼
		IUR_GLOBE = 5, // [타자장갑] 타자장갑
		IUR_GLOVE = 6, // [글러브] 글러브
		IUR_SHOES = 7, // [신발] 신발
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
		SCT_KINGROOKIE = 1, // [로그1] 로그1
		SCT_ROOKIE = 2, // [로그2] 로그2
		SCT_AMA1 = 3, // [로그3] 로그3
		SCT_AMA2 = 4, // [로그4] 로그4
		SCT_PRO = 5, // [로그5] 로그5
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
		NT_LED = 1, // [전광판] 전광판
		NT_CHECK = 2, // [임시점검] 임시점검
		NT_NOTICE = 3, // [공지사항] 공지사항
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
		EBT_SMALL = 1, // [스몰] 스몰, 성별이 여자일때는 무조건 스몰이다.
		EBT_MIDIUM = 2, // [미디엄] 미디엄
		EBT_LARGE = 3, // [라지] 라지
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
		PBS_NULL = 1, // [없음] 없음
		PBS_LEFT = 2, // [대좌투수] 좌투수상대시 파워 증가
		PBS_RIGHT = 3, // [대우투수] 대우투수 상대시 파워 증가
		PBS_HOMERUN = 4, // [홈런타자] 히트시 파워 증가
		PBS_WIDE = 5, // [광각타법] 광각타법 - 밀어쳤을때 파워 다운없음
		PBS_FULLHIT = 6, // [풀히터] 풀히터 - 당겨쳤을때 파워 증가
		PBS_LOWHIT = 7, // [로볼히터] 로볼히터 - 타격판정시 하단/중단에서 파워 증가
		PBS_HIGHHIT = 8, // [하이볼히터] 하이볼히터 - 중단,상단에서 파워 증가
		PBS_RUNFIRE = 9, // [연발] 연발 - 바로 이전타석에서 홈런시 파워 증가
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
		PGT_E = 1, // [E등급] E등급 플레이어 카드
		PGT_D = 2, // [D등급] D등급 플레이어 카드
		PGT_C = 3, // [C등급] C등급 플레이어 카드
		PGT_B = 4, // [B등급] B등급 플레이어 카드
		PGT_A = 5, // [A등급] A등급 플레이어 카드
		PGT_S = 6, // [S등급] S등급 플레이어 카드
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
		PNT_KOREA = 1, // [한국] 한국
		PNT_USA = 2, // [미국] 미국
		PNT_JAPAN = 3, // [일본] 일본
		PNT_CHINA = 4, // [중국] 중국
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
		PPS_NULL = 1, // [없음] 없음
		PPS_LEFT = 2, // [대좌타자] 좌타자상대시 능력치증가
		PPS_RIGHT = 3, // [대우타자] 우타자상대시 능력치증가
		PPS_FASTBALL = 4, // [속구파] 구속 증가
		PPS_FULLSKILL = 5, // [기교파] 변화구 각 증가
		PPS_RUNFIRE = 6, // [연투] 바로 이전 타석에서 스트라익 잡으면  다음 공 제구 증가
		PPS_SWORDCON = 7, // [칼제구] 낮은 투구시 제구 다운 없음
		PPS_DOCK = 8, // [닥터K] 2개의 스트라익 잡으면 다음 공 제구 증가
		PPS_INFIGHT = 9, // [인파이터] 타자의 몸쪽으로 공을 던질시 제구 증가
		PPS_OUTFIGHT = 10, // [아웃파이터] 타자의 바깥쪽으로 공을 던질시 제구 증가
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
		PT_BETTER = 1, // [타자] 타자
		PT_PITCHER = 2, // [투수] 투수
		PT_COMMON = 3, // [공용] 타자투수구분없음
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
		QCT_NULL = 1, // [없음] 없음
		QCT_SINGLEGAMEWINCOUNT = 2, // [싱글경기승수조건] Sys_Quest의 condition_value에 있는 값만큼 이겼다면 퀘스트 보상
		QCT_MATCHGAMEWINCOUNT = 3, // [대전경기승수조건] 대전경기에서 condition_value만큼이겼다면 보상
		QCT_FRIENDGAMEWINCOUNT = 4, // [친구경기승수조건] 등록된 친구랑 경기후 condition_value만큼 이겼다면 보상
		QCT_SINGELGAMECOUNT = 5, // [싱글경기횟수조건] 싱글경기횟수가 value만큼 되었을때 보상
		QCT_MATCHGAMECOUNT = 6, // [대전경기횟수조건] 대전경기횟수가 value만큼 되었을때 보상
		QCT_FRIENDGAMECOUNT = 7, // [친구경기횟수조건] 등록된 친구와의 경기횟수가 value만큼 되었을때 보상
		QCT_PLAYERLEVELCOUNT = 8, // [레벨달성조건] 레벨달성조건
		QCT_PLAYERCHARACTERCOUNT = 9, // [캐릭터생성갯수] 캐릭터생성갯수
		QCT_MATCHHOMERUNCOUNT = 10, // [대전홈런횟수조건] 대전홈런횟수조건
		QCT_MATCHSTRIKEOUTCOUNT = 11, // [대전탈삼진횟수조건] 대전탈삼진횟수조건
		QCT_EQUIPGRADETYPE = 12, // [전체장비착용조건] 전체장비착용조건이 condition1에 있는 값의 조건(EItemGradeType)에 해당하면 보상을 준다
		QCT_CASHCOUNT = 13, // [캐쉬템구매조건] 캐쉬템구매조건
		QCT_GAMEMONEYCOUNT = 14, // [게임머니누적조건] 게임머니누적조건
		QCT_PLAYERALLSTATCOUNT = 15, // [캐릭터모든능력치달성조건] 캐릭터모든능력치달성조건
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
	// 설명없음
	// -------------------------------------------------

	public class Sys__ItemBase
	{
		public Sys__ItemBase_id_t m_sid; 	// [고유식별ID]  
		public string m_name; 	// [이름] 영문이름 고유해야함. 이 영문이름으로 스트링테이블에서 한글이름검색 
		public EItemCategory m_category; 	// [대분류]  
		public bool m_upgrade_type; 	// [업그레이드 가능 유뮤] 업그레이드가 가능한지의 여부 
		public bool m_is_visual; 	// [비쥬얼] 화면에 보여지느냐 안보여지느냐 여부 
		public string m_help; 	// [설명]  
		public EItemGradeType m_grade; 	// [등급] 아이템 업그레이드 등급 
		public EItemPriceType m_price_type; 	// [구매타입]  
		public Int32 m_price_money; 	// [필요게임머니]  
		public Int32 m_price_cash; 	// [필요리얼캐쉬]  
		public EItemSellStatus m_sell_status; 	// [판매상태]  
		public DATETIME m_sell_start_date; 	// [판매 시작 일시] 판매 시작 일시 
		public DATETIME m_sell_end_date; 	// [판매 종료 일시] 판매 종료 일시 
		public player_level_t m_player_level_min; 	// [사용레벨MIN] 현제는 약 110까지 가능 
		public player_level_t m_player_level_max; 	// [사용레벨MAX] 현제는 약 110까지 가능 
		
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
	// 설명없음
	// -------------------------------------------------

	public class Sys__Base_PlayerStat
	{
		public Int16 m_sid; 	// [고유식별ID]  
		public string m_name; 	// [이름] 영문이름 고유해야함. 이영문이름으로 스트링테이블에서 한글이름검색 
		public Int16 m_better_power; 	// [타자 파워]  
		public Int16 m_better_focus; 	// [타자 집중]  
		public Int16 m_pitcher_control; 	// [투수 제구]  
		public Int16 m_pitcher_ballspeed; 	// [투수 구속] 빨간색 숫자는 마이너스를 뜻함 
		public Int16 m_pitcher_breakingball_value; 	// [투수 변화구 수치]  
		public EPlayerBreakingBall m_pitcher_breakingball_type; 	// [투수 변화구종류] 투수 변화구 
		
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
	// 설명없음
	// -------------------------------------------------

	public class Sys_ItemEquip
			: Sys__ItemBase
	{
		public EItemCategoryEquipment m_equip_category; 	// [장비아이템카테고리] 장비아이템카테고리 
		public EItemSexType m_sex_type; 	// [아이템남여구분] 남여구분 
		public EPlayerType m_player_type; 	// [타자투수구분] 타자투수구분 
		
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
	// 설명없음
	// -------------------------------------------------

	public class Sys_ItemConsume
			: Sys__ItemBase
	{
		public EPlayerType m_player_type; 	// [타자투수구분] 타자투수구분 
		public EConsumeItemEffect m_consume_item_effect; 	// [컨슘아이템효과] 컨슘아이템 소비 시 효과 구분 
		public EItemAbilityType m_Item_Ability_Type; 	// [아이템영향스텟] 컨슘아이템영향스텟 
		public Int16 m_consume_item_effect_value; 	// [컨슘아이템효과값] 각 해당 아이템 효과의 값(아이템의 효과 마다 값이 다름-->) 
		public Int16 m_gameplay_effect_repeat; 	// [게임 플레이시 지속효과 제한(횟수)] 게임 플레이시 지속효과 제한(횟수) 
		public Int16 m_gameplay_effect_time; 	// [게임 플레이시 지속효과 제한(시간)] 게임 플레이시 지속효과 제한(시간) 
		public bool m_consume_item_overlap; 	// [다른아이템과 중복사용 여부] 다른아이템과 중복사용 여부 
		public Int16 m_use_count; 	// [사용 횟수] 사용 횟수 
		
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
	// 설명없음
	// -------------------------------------------------

	public class Sys_ItemStuff
			: Sys__ItemBase
	{
		public EItemUpgradeResult m_item_upgrade_result; 	// [업그레이드 아이템 결과물]  
		
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
	// 설명없음
	// -------------------------------------------------

	public class Sys_MainItemAbility
	{
		public Int16 m_sid; 	// [고유번호] 고유번호 
		public EItemCategoryEquipment m_equip_category; 	// [장비아이템카테고리] 장비아이템카테고리 
		public string m_name; 	// [업그레이드단계] EE SS SA … 
		public Int16 m_mainitem_first_equip_level; 	// [아이템최초 장착 레벨] 아이템 최초 장착 레벨 
		public Int16 m_mainitem_possible_upgrade_level; 	// [아이템강화 가능 레벨] 아이템 강화 가능 레벨 
		public Int16 m_mainitem_need_time; 	// [아이템강화 필요 시간] 아이템 강화 필요 시간 
		public Int16 m_mainitem_basic_ability; 	// [아이템기본능력치] 아이템 기본 능력치 
		public Int16 m_mainitem_equip_level; 	// [해당아이템장착레벨]  
		public Int16 m_ability_min; 	// [일반강화능력치] 강화시 최소 증가 능력치(IUR_NORMAL) 
		public Int16 m_ability_max; 	// [강화시최대증가능력치] 강화시 최대 증가 능력치(IUR_PERFECT) 
		public Int64 m_mainitem_upgrade_need_money; 	// [필요게임머니] 필요 게임 머니 
		
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
	// 설명없음
	// -------------------------------------------------

	public class Sys_Package
	{
		public Int16 m_sid; 	// [sid]  
		public string m_name; 	// [name]  
		public EItemPriceType m_price_type; 	// [구매타입]  
		public Int32 m_price_money; 	// [필요게임머니]  
		public Int32 m_price_cash; 	// [필요리얼캐쉬]  
		public EGradeAllitemType m_grade_allitem_type1; 	// [아이템별그레이드모음1] 아이템별그레이드모음1(EX : 메인아이템S급 모두, 서브아이템s급 모두…) 
		public EGradeAllitemType m_grade_allitem_type2; 	// [아이템별그레이드모음2] 아이템별그레이드모음2 
		public EGradeAllitemType m_grade_allitem_type3; 	// [아이템별그레이드모음3] 아이템별그레이드모음3 
		public EGradeAllitemType m_grade_allitem_type4; 	// [아이템별그레이드모음4] 아이템별그레이드모음4 
		public EGiftType m_gift_type1; 	// [선물종류1]  
		public Int64 m_gift_type1_value; 	// [선물1]  
		public EGiftType m_gift_type2; 	// [선물종류2]  
		public Int64 m_gift_type2_value; 	// [선물2]  
		public EGiftType m_gift_type3; 	// [선물종류3]  
		public Int64 m_gift_type3_value; 	// [선물3]  
		public EGiftType m_gift_type4; 	// [선물종류4]  
		public Int64 m_gift_type4_value; 	// [선물4]  
		public EGiftType m_gift_type5; 	// [선물종류5]  
		public Int64 m_gift_type5_value; 	// [선물5]  
		public EGiftType m_gift_type6; 	// [선물종류6]  
		public Int64 m_gift_type6_value; 	// [선물6]  
		public EGiftType m_gift_type7; 	// [선물종류7]  
		public Int64 m_gift_type7_value; 	// [선물7]  
		public EGiftType m_gift_type8; 	// [선물종류8]  
		public Int64 m_gift_type8_value; 	// [선물8]  
		public EGiftType m_gift_type9; 	// [선물종류9]  
		public Int64 m_gift_type9_value; 	// [선물9]  
		public EGiftType m_gift_type10; 	// [선물종류10]  
		public Int64 m_gift_type10_value; 	// [선물10]  
		
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
	// 설명없음
	// -------------------------------------------------

	public class Sys_PlayerCard
			: Sys__Base_PlayerStat
	{
		public EPlayerNationType m_player_nation; 	// [출신]  
		public Int16 m_player_year; 	// [활동 연도] 플레이어 활동연도 
		public EPlayerGradeType m_player_grade; 	// [등급] 선수 별 업그레이드 등급 
		public EplayerBadyType m_body_type; 	// [체형]  
		public Int16 m_player_level; 	// [플레이어 레벨] 선수 레벨 
		public EPlayerType m_player_type; 	// [타자투수구분] 타자투수구분 
		public EItemPriceType m_price_type; 	// [구매타입]  
		public Int32 m_price_money; 	// [필요게임머니]  
		public Int32 m_price_cash; 	// [필요리얼캐쉬]  
		public EItemSellStatus m_sell_status; 	// [판매상태]  
		public DATETIME m_sell_start_date; 	// [판매 시작 일시] 판매 시작 일시 
		public DATETIME m_sell_end_date; 	// [판매 종료 일시] 판매 종료 일시 
		public Int16 m_player_level_min; 	// [사용레벨MIN]  
		public Int16 m_player_level_max; 	// [사용레벨MAX]  
		public Int16 m_sticker_slot_count; 	// [붙일수있는스티커갯수]  
		public List<Sys_PlayerSkillSticker> m_skill_sticker = new List<Sys_PlayerSkillSticker>{}; 	// [기본적으로보유한 특수능력] Sys_PlayerSkillSticker에서의 name 
		public EPlayer_Onoffline m_player_onoff; 	// [플레이어의 온오프라인 구별] 플레이어의 온오프라인 구별 
		
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
	// 설명없음
	// -------------------------------------------------

	public class Sys_PlayerLevel
	{
		public Int16 m_sid; 	// [고유번호] 고유번호 
		public string m_name; 	// [name]  
		public Int16 m_level; 	// [플레이어레벨] 플레이어레벨 
		public Int64 m_max_exp; 	// [해당 레벨의 최대 경험치] 해당 레벨의 최대 경험치 
		public Int16 m_better_accuracy_s; 	// [타자_small_정확] 타자_small_정확 
		public Int16 m_better_accuracy_m; 	// [타자_Midium_정확] 타자_Midium_정확 
		public Int16 m_better_accuracy_l; 	// [타자_large_정확] 타자_large_정확 
		public Int16 m_better_power_s; 	// [타자_small_파워] 타자_small_파워 
		public Int16 m_better_power_m; 	// [타자_Midium_파워] 타자_Midium_파워 
		public Int16 m_better_power_l; 	// [타자_large_파워] 타자_large_파워 
		public Int16 m_pitcher_speed_s; 	// [투수_small_구속] 투수_small_구속 
		public Int16 m_pitcher_speed_m; 	// [투수_Midium_구속] 투수_Midium_구속 
		public Int16 m_pitcher_speed_l; 	// [투수_large_구속] 투수_large_구속 
		public Int16 m_pitcher_focus_s; 	// [투수_small_제구] 투수_small_제구 
		public Int16 m_pitcher_focus_m; 	// [투수_Midium_제구] 투수_Midium_제구 
		public Int16 m_pitcher_focus_l; 	// [투수_large_제구] 투수_large_제구 
		public Int16 m_pitcher_breakingball_s; 	// [투수_small_변화구] 투수_small_변화구 가능 개수 
		public Int16 m_pitcher_breakingball_m; 	// [투수_Midium_변화구] 투수_Midium_변화구 가능 개수 
		public Int16 m_pitcher_breakingball_l; 	// [투수_large_변화구] 투수_large_변화구 가능 개수 
		
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
	// 설명없음
	// -------------------------------------------------

	public class Sys_PlayerSkillSticker
			: Sys__Base_PlayerStat
	{
		public EPlayerBetterSkill m_better_skill1_type; 	// [타자특수능력종류] 타자 카드의 스킬 종류 
		public EPlayerPitcherSkill m_Pitcher_skill1_type; 	// [투수특수능력종류] 투수 카드의 스킬 종류 
		public Int16 m_unlock_player_level; 	// [봉인해제되는레벨] 해당 스킬스티커가 사용될수있는 플레이어레벨 
		
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
	// 설명없음
	// -------------------------------------------------

	public class Sys_Quest
	{
		public Sys_Quest_id_t m_sid; 	// [고유번호]  
		public string m_name; 	// [퀘스트이름] 클라에 출력할 스트링은 name으로 Sys_StringTable에서 검색해서 출력한다. 
		public game_money_t m_quest_reward_money; 	// [보상머니] 퀘스트 보상 게임머니 
		public pp_point_t m_quest_reward_point; 	// [보상포인트] 퀘스트 보상 pp포인트 
		public EConditionCharacterTitle m_condition_character_title; 	// [보상호칭값] 호칭 부여 시 네이밍 
		public string m_help; 	// [조건설명] 출력용이아니라 개발시 참조용 
		public EQuestConditionType m_condition_type1; 	// [조건1타입]  
		public string m_condition1; 	// [조건1내용] 없을 경우 NULL 
		public Int32 m_condition_value1; 	// [조건1값]  
		public EQuestConditionType m_condition_type2; 	// [조건2타입]  
		public string m_condition2; 	// [조건2내용]  
		public Int32 m_condition_value2; 	// [조건2값]  
		public EQuestConditionType m_condition_type3; 	// [조건3타입]  
		public string m_condition3; 	// [조건3내용]  
		public Int32 m_condition_value3; 	// [조건3값]  
		
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
	// 설명없음
	// -------------------------------------------------

	public class Sys_RandomGift
	{
		public Sys_RandomGift_id_t m_item_sid; 	// [sid]  
		public string m_name; 	// [name]  
		public EGiftCategory m_gift_category; 	// [선물 조건] 이겼을때/졌을때/트레이닝완료시 
		public EGiftType m_gift_type; 	// [선물 타입]  
		public Int32 m_gift1; 	// [선물 값] 확률상 최소 보상값 
		public Int32 m_gift2; 	// [선물 값] 확률상 최고 보상값 
		public string m_gift3; 	// [선물 값] 확률상 아이템 시드값 
		public Int16 m_gift_probability; 	// [EGiftType의 확률] 천분율. 0~1000 
		public string m_help; 	// [EGiftType의 설명]  
		public EItemCategory m_item1_type; 	// [아이템 종류]  
		public Sys_ItemEquip m_item1; 	// [EItemCategory의 SID]  
		public Int16 m_item1_probability; 	// [EItemCategory의 확률] 천분율. 0~1000 
		public EItemCategory m_item2_type; 	// [아이템 종류]  
		public Sys_ItemEquip m_item2; 	// [EItemCategory의 SID]  
		public Int16 m_item2_probability; 	// [EItemCategory의 확률] 천분율. 0~1000 
		public EItemCategory m_item3_type; 	// [아이템 종류]  
		public Sys_ItemEquip m_item3; 	// [EItemCategory의 SID]  
		public Int16 m_item3_probability; 	// [EItemCategory의 확률] 천분율. 0~1000 
		
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
	// 설명없음
	// -------------------------------------------------

	public class Sys_SubItemAbility
	{
		public Int16 m_sid; 	// [고유번호] 고유번호 
		public EItemCategoryEquipment m_equip_category; 	// [장비아이템카테고리] 장비아이템카테고리 
		public EItemGradeType m_grade; 	// [등급] 아이템 업그레이드 등급 
		public Int16 m_subitem_first_equip_level; 	// [아이템최초 장착 레벨] 아이템 최초 장착 레벨 
		public Int16 m_subitem_better_ability; 	// [아이템타자능력치] 아이템 기본 능력치 
		public Int16 m_subitem_pitcher_ability; 	// [아이템투수능력치] 아이템 기본 능력치 
		
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
	// 설명없음
	// -------------------------------------------------

	public class Tbl__PlayerBase
	{
		public Tbl__PlayerBase_id_t m_pid; 	// [PK index] 선수 database table PK 
		public Sys_PlayerCard_id_t m_sid; 	// [Sys_Player아이디] 구매한 선수카드의 번호(Sys_Player의 sid) 값이 0 이면 가상선수 
		public pimang_id_t m_ppid; 	// [PP_ID] 피망아이디번호 
		public string m_pname; 	// [닉네임]  
		public EPlayerNationType m_city; 	// [출신국가] 캐주얼야구 게임기획서 3차 (20111031).docx참조 
		public string m_initial_name; 	// [이니셜] 생성시 세팅. 등뒤의이니셜글자. 중복가능 
		public Int16 m_back_number; 	// [백넘버] 생성시 세팅. 변경아이템으로 변경가능 
		public Int16 m_age; 	// [나이] 생성시 세팅. 
		public EplayerBadyType m_bady_type; 	// [체형]  
		public bool m_leftright_type; 	// [좌우타입] 캐릭터의 좌우 구분 1이면 좌선수 0이면 우선수 
		public Int64 m_exp; 	// [경험치] 레벨은 경험치에 해당하는 Sys_PlayerLevel의 값에 따라 결정 
		public Sys_Quest_id_t m_questcomplete_count; 	// [퀘스트완료_카운트] 완료 퀘스트 카운트 
		public Int16 m_win_continue; 	// [연승] 연속으로 승리한 개수 
		public Int16 m_lose_continue; 	// [연패] 연속 패한 개수 
		public Tbl_Result_id_t m_last_game_result; 	// [마지막경기id] 마지막으로 플레이한 경기결과 식별자 
		public Int32 m_win_tot; 	// [총전적_승] 토탈 승 카운트 
		public Int32 m_lose_tot; 	// [총전적_패] 토탈 패 카운트 
		public Int32 m_win_season; 	// [시즌전적_승] 시즌 승 카운트(3개월) 
		public Int32 m_lose_season; 	// [시즌전적_패] 시즌 패 카운트(3개월) 
		public string m_skill_sticker; 	// [특수능력이름] Sys_PlayeSkillSticker에서의 name  ";"로 구분되어 여러개입력 
		public Int32 m_elo_point; 	// [ELO_포인트] 경기마다 캐릭터에 갱신되는 매칭용 포인트 
		public bool m_onoff_type; 	// [온오프라인구분] 0이면 온라인플레이어 1이면 오프라인플레이어 
		
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
	// 설명없음
	// -------------------------------------------------

	public class Tbl_Item
	{
		public Tbl_Item_id_t m_iid; 	// [고유식별자] db pk 
		public Sys__ItemBase_id_t m_sid; 	// [구매한 아이템종류] Sys__ItemBase_id_t 
		public EItemCategory m_category; 	// [대분류] 장비 스텁 소비 구분 
		public Tbl__PlayerBase_id_t m_pid; 	// [Tbl__PlayerBase pid] Tbl__PlayerBase의 did 
		public string m_upgrade_level; 	// [업그레이드등급] baseball.xml에서 ITEM_UPGRADE_LOGIC 참조 
		public string m_etc_info; 	// [기타정보] 등번호 아이템일때는 등번호. 마킹 아이템일때는 마킹글자를 저장. 
		public string m_grade; 	// [등급] 아이템 업그레이드 등급(최초는 S,A,B,C,D,E중의 한 개) 
		public real_money_t m_bought_real_money; 	// [구매캐쉬] 구매시 사용한 리얼캐쉬 
		public real_money_t m_bought_point_money; 	// [구매포인트] 구매시 사용한 포인트 
		public game_money_t m_bought_game_money; 	// [구매게임머니] 구매시 사용한 게임머니 
		public bool m_is_used; 	// [귀속여부] 한 선수에 사용이되었는지 여부 
		public bool m_is_confirmed; 	// [구매상태] 캐쉬인벤 or 게임인벤 환불여부 
		public Int16 m_usable_hour; 	// [기간제아이템의사용시간] 기간제아이템의경우 사용가능한 시간 
		public Int16 m_used_game_count; 	// [사용한 경기횟수] 사용한 게임의 경기 횟수 
		
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
	// 설명없음
	// -------------------------------------------------

	public class Tbl_PlayerBetter
			: Tbl__PlayerBase
	{
		public Int16 m_batting_average; 	// [타율] 0.001~0.999 천분율로 표시 
		public Int16 m_continue_homerun_count; 	// [연속홈런수] 연속_홈런수 
		public Int16 m_homeruntotal_count; 	// [총_홈런수] 총_홈런수 
		public Int16 m_single_homerun_count; 	// [싱글홈런카운트] 싱글홈런 카운트 
		public Int16 m_tworun_homerun_count; 	// [더블홈런카운트] 더블홈런 카운트 
		public Int16 m_threerun_homerun_count; 	// [쓰리런홈런카운트] 쓰리런홈런 카운트 
		public Int16 m_grandslam_homerun_count; 	// [만루홈런카운트] 만루홈런 카운트 
		public Int16 m_one_hit_count; 	// [일루타카운트] 일루타 카운트 
		public Int16 m_double_hit_count; 	// [이루타카운트] 이루타 카운트 
		public Int16 m_triple_hit_count; 	// [삼루타카운트] 삼루타 카운트 
		public Int16 m_foul_hit_count; 	// [파울카운트] 파울 카운트 
		public Int16 m_out_hit_count; 	// [아웃카운트] 아웃 카운트 
		public Int16 m_score_count; 	// [점수카운트] 점수 카운트 
		public EPlayerBetterSkill m_betting_type; 	// [타자타입]  
		public Int16 m_better_power; 	// [타자 파워]  
		public Int16 m_better_focus; 	// [타자 집중]  
		public Int16 m_better_power_buff; 	// [타자 파워 버프]  
		public Int16 m_better_focus_buff; 	// [타자 집중 버프]  
		
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
	// 설명없음
	// -------------------------------------------------

	public class Tbl_PlayerPitcher
			: Tbl__PlayerBase
	{
		public Int16 m_pitching_average; 	// [방어율] 0.001~0.999 천분율로 표시 
		public Int16 m_hit_count; 	// [피안타율] 피안타율 
		public Int16 m_strikeout_count; 	// [탈삼진수] 탈삼진수 
		public Int16 m_homerun_pitching_count; 	// [피홈런수] 피홈런수 
		public Int16 m_continue_strikeout_count; 	// [연속삼진수] 연속삼진수 
		public Int16 m_continue_homerun_pitching_count; 	// [연속피홈런수] 연속피홈런수 
		public EPlayerPitcherSkill m_pitching_type; 	// [투수타입]  
		public Int16 m_pitcher_control; 	// [투수 제구]  
		public Int16 m_pitcher_ballspeed; 	// [투수 구속]  
		public Int16 m_pitcher_breakingball_value; 	// [투수 변화구 수치]  
		public EPlayerBreakingBall m_pitcher_breakingball_type; 	// [투수 변화구종류] 투수 변화구 
		public Int16 m_pitcher_control_buff; 	// [투수 제구 버프]  
		public Int16 m_pitcher_ballspeed_buff; 	// [투수 구속 버프]  
		public Int16 m_pitcher_breakingball_value_buff; 	// [투수 변화구 수치 버프]  
		
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
	// 설명없음
	// -------------------------------------------------

	public class Tbl_Result
	{
		public Tbl_Result_id_t m_grid; 	// [game고유번호] 일별 파티션 키 
		public bool m_is_singlemode; 	// [is_singlemode] 0=멀티플레이 1=싱글플레이 
		public Int32 m_ppid1; 	// [PP_ID] 플레이어1의 피망아이디번호 
		public Tbl_User_id_t m_uid1; 	// [고유번호] 플레이어1 고유번호 
		public string m_uname1; 	// [유저 닉네임] 플레이어1 베이스볼에서의 유저닉네임 
		public Tbl_PlayerBetter_id_t m_pid_better1; 	// [타자 pid] 플레이어1 
		public Tbl_PlayerPitcher_id_t m_pid_pitcher1; 	// [투수 pid] 플레이어1 
		public Int32 m_ppid2; 	// [PP_ID] 플레이어2 피망아이디번호 
		public Tbl_User_id_t m_uid2; 	// [고유번호] 플레이어2 고유번호 
		public string m_uname2; 	// [유저 닉네임] 플레이어2 베이스볼에서의 유저닉네임 
		public Tbl_PlayerBetter_id_t m_pid_better2; 	// [타자 pid] 플레이어2 
		public Tbl_PlayerPitcher_id_t m_pid_pitcher2; 	// [투수 pid] 플레이어2 
		public DATETIME m_time_start; 	// [게임시작시간] 시작 일시 
		public DATETIME m_time_end; 	// [게임종료시간] 플레이 시간 
		public Tbl_User_id_t m_winner; 	// [승자] 승자 
		public Int32 m_reward_exp1; 	// [플레이어1의 보상경험치] 플레이어1의 보상경험치 
		public Int32 m_reward_exp2; 	// [보상경험치] 보상경험치 
		public Tbl_Item_id_t m_reward_item1; 	// [보상아이템] 보상아이템 
		public Tbl_Item_id_t m_reward_item2; 	// [보상아이템] 보상아이템 
		public game_money_t m_reward_gamemoney1; 	// [보상게임머니] 보상게임머니 
		public game_money_t m_reward_gamemoney2; 	// [보상게임머니] 보상게임머니 
		public Int16 m_score1; 	// [player1스코어]  
		public Int16 m_score2; 	// [player2스코어]  
		
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
	// 설명없음
	// -------------------------------------------------

	public class Tbl_RoundResult
	{
		public Tbl_RoundResult_id_t m_grid2; 	// [고유번호] 일별 파티션 키 
		public Tbl_Result_id_t m_grid; 	// [Tbl_Result_M의 고유번호]  
		public Int16 m_round_number; 	// [라운드번호] 1~10은 라운드 한게임의 토탈집계는 Tbl_Result에 저장 
		public Tbl_PlayerPitcher_id_t m_pid_better; 	// [better]  
		public Int16 m_score; 	// [better의점수]  
		public Int16 m_base_runner_count; 	// [출루한주자수] 최대는 xml에서  i_max_runner_per_game=19이다 
		public EBetterHitType m_hit_type; 	// [안타종류] 0=아웃 1일루타 2이루타 3삼루타 4싱글홈런 5더블홈런 6 
		public Int16 m_strike; 	// [스트라익카운트]  
		public Int16 m_foul; 	// [파울카운트]  
		
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
	// 설명없음
	// -------------------------------------------------

	public class Tbl_User
	{
		public Tbl_User_id_t m_uid; 	// [고유번호] db pk 
		public pimang_id_t m_ppid; 	// [PP_ID] 피망아이디번호 
		public string m_uname; 	// [닉네임] 베이스볼에서의 유저닉네임 
		public Int16 m_pitcher_tot_win; 	// [투수총전적_승] 투수총전적_승 
		public Int16 m_pitcher_tot_lose; 	// [투수총전적_패] 투수총전적_패 
		public Int16 m_pitcher_tot_strikeout; 	// [탈삼진수] 투수총_탈삼진 
		public Int16 m_pitcher_tot_average_level; 	// [투수총평균_레벨] 투수총평균_레벨 
		public Int16 m_better_tot_win; 	// [타자총전적_승] 타자총전적_승 
		public Int16 m_better_tot_lose; 	// [타자총전적_패] 타자총전적_패 
		public Int16 m_better_tot_homerun; 	// [총_홈런수] 타자총_홈런 
		public Int16 m_better_tot__average_level; 	// [타자총평균_레벨] 타자총평균_레벨 
		public Int16 m_cash_item_buy_count; 	// [캐쉬템구매갯수] 캐쉬템구매갯수 
		public DATETIME m_playtime_first; 	// [첫_게임플레이시작_타임] 첫_플레이시작_타임 
		public DATETIME m_playtime_last; 	// [마지막_플레이_타임] 마지막_플레이_타임 
		public Int64 m_playtime_tot; 	// [총_플레이_타임] 총_플레이_타임(분) 
		
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
	// 설명없음
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
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
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
	// 설명없음
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
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
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
	// 설명없음
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
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
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
	// 설명없음
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
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
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
	// 설명없음
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
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
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
	// 설명없음
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
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
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
	// 설명없음
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
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
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
	// 설명없음
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
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
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
	// 설명없음
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
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
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
	// 설명없음
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
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
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
	// 설명없음
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
