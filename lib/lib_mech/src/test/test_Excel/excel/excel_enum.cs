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

	public enum EBetterAbility
	{
		eBEGIN_EBetterAbility=0,
		BA_NULL = 1, // [없음] 없음
		BA_LEFT = 2, // [대좌투수] 좌투수상대시 파워 증가
		BA_RIGHT = 3, // [대우투수] 대우투수 상대시 파워 증가
		BA_HOMERUN = 4, // [홈런타자] 히트시 파워 증가
		BA_WIDE = 5, // [광각타법] 광각타법 - 밀어쳤을때 파워 다운없음
		BA_FULLHIT = 6, // [풀히터] 풀히터 - 당겨쳤을때 파워 증가
		BA_LOWHIT = 7, // [로볼히터] 로볼히터 - 타격판정시 하단/중단에서 파워 증가
		BA_HIGHHIT = 8, // [하이볼히터] 하이볼히터 - 중단# 상단에서 파워 증가
		BA_RUNFIRE = 9, // [연발] 연발 - 바로 이전타석에서 홈런시 파워 증가
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
		BF_SQUARE = 1, // [스퀘어] 스쿼어
		BF_OPEN = 2, // [오픈] 오픈
		BF_CLOSE = 3, // [크로즈드] 크로즈드
		BF_NULL = 4, // [없음] 없음
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
		EBHT_STANDOUT = 1, // [스탠드아웃] 스탠드아웃
		EBHT_SWINGOUT = 2, // [스윙아웃] 스윙아웃
		EBHT_FOULOUT = 3, // [파울아웃] 파울아웃
		EBIT_INFIELDOUT = 4, // [내야아웃] 내야아웃
		EBIT_LEFTFIELDOUT = 5, // [좌익수아웃] 좌익수아웃
		EBIT_CENTERFIELDOUT = 6, // [중견수아웃] 중견수아웃
		EBIT_RIGHTFIELDOUT = 7, // [우익수아웃] 우익수아웃
		EBHT_NO_HIT = 8, // [치지못한상태] 아웃상태
		EBHT_ONEHIT = 9, // [일루타] 일루타
		EBHT_DOUBLEHIT = 10, // [이루타] 이루타
		EBHT_TRIPLEHIT = 11, // [삼루타] 삼루타
		EBHT_HOMERUN = 12, // [홈런] 홈런
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
		EBBP_STRAIGHT = 1, // [직구] 직구
		EBBP_WIDE = 2, // [횡변화] 횡변화
		EBBP_HEIGHT = 3, // [종변화] 종변화
		EBBP_HEIGHTWIDE = 4, // [종횡변화] 종횡변화
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
		EBBR_REGULAR = 1, // [정회전] 정회전
		EBBR_REVERSE = 2, // [역회전] 역회전
		EBBR_NOTHING = 3, // [무회전] 무회전
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


	public enum EGestureType
	{
		eBEGIN_EGestureType=0,
		EGTT_STRAGHT = 1, // [직선] 직선
		EGTT_VERTICAL = 2, // [수직선] 수직선
		EGTT_CURVE = 3, // [곡선] 곡선
		EGTT_STAIR_VERTICAL = 4, // [계단형수직선] 계단형수직선
		EGTT_S_CURVE = 5, // [에스형곡선] 에스형곡선
		EGTT_NULL = 6, // [없음] 변화구에 제스처를 설정하지 않은 경우
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
		IBT_BUY_POINT = 2, // [포인트 구매 아이템] 포인트 구매 아이템
		IBT_BUY_USED = 3, // [캐쉬귀속아이템] 캐쉬OR포인트구매아이템인데 귀속된상태
		IBT_EVENT = 4, // [이벤트 지급아이템] 이벤트지급아이템
		IBT_REWARD = 5, // [경기보상으로받음] 트레이닝 or 경기보상 지급아이템
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
		IC_EQUIP = 1, // [착용장비] 착용장비
		IC_CONSUME = 2, // [소모아이템] 소모아이템
		IC_STUFF = 3, // [재료아이템] 재료아이템
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
		ICE_CAP = 3, // [모자] 모자 메인아이템#
		ICE_SHOES = 4, // [신발] 신발 메인아이템#
		ICE_GLOVE = 5, // [투수글러브] 투수글러브 메인아이템#
		ICE_U_SHIRT = 6, // [언더셔츠] 언더셔츠
		ICE_SOCKS = 7, // [양말] 양말
		ICE_ARM_GUARDS = 8, // [팔_보호대] 팔_보호대
		ICE_LEG_GUARDS = 9, // [다리_보호대] 다리_보호대
		ICE_BET = 10, // [배트] 배트 메인아이템
		ICE_BALL = 11, // [볼] 볼 메인아이템#
		ICE_HELMET = 12, // [헬멧] 헬멧 메인아이템#
		ICE_GLOBE = 13, // [타자장갑] 타자용 장갑 메인아이템#
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
		ICE_HAIR_COLOR = 24, // [헤어칼라] 헤어칼라
		ICE_PATCH = 25, // [패치] 패치
		ICE_MASK = 26, // [마스크] 마스크
		ICE_BACKNUMBER = 27, // [등번호 아이템] 등번호 아이템
		ICE_MAKING = 28, // [마킹 아이템] 마킹 아이템
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
		IGT_D = 2, // [D등급] D - DE #  DD로 업글가능
		IGT_C = 3, // [C등급] C - CE # CD# CC로 업글가능
		IGT_B = 4, // [B등급] B- BE# BD# BC# BB로 업글가능
		IGT_A = 5, // [A등급] A- AE# AD# AC# AB# AA로 업글가능
		IGT_S = 6, // [S등급] S-SE# SD# SC# SB# SA# SS로 업글가능
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
		IPT_MONEY = 3, // [포인트] 캐쉬 또는 포인트# 게임머니로 살수 있는 아이템
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


	public enum EItemState
	{
		eBEGIN_EItemState=0,
		IS_NORMAL = 1, // [일반상태] 일반상태
		IS_DELETE = 2, // [삭제된상태] 삭제된상태
		IS_ADMIN_BLOCKED = 3, // [사용불가능.] 사용불가능.
		IS_DELETE_REFUND = 4, // [되팔기되어 삭제됨] 되팔기되어 삭제됨
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


	public enum EPitcherAbility
	{
		eBEGIN_EPitcherAbility=0,
		PA_NULL = 1, // [없음] 없음
		PA_LEFT = 2, // [대좌타자] 좌타자상대시 능력치증가
		PA_RIGHT = 3, // [대우타자] 우타자상대시 능력치증가
		PA_FASTBALL = 4, // [속구파] 구속 증가
		PA_FULLSKILL = 5, // [기교파] 변화구 각 증가
		PA_RUNFIRE = 6, // [연투] 바로 이전 타석에서 스트라익 잡으면  다음 공 제구 증가
		PA_SWORDCON = 7, // [칼제구] 낮은 투구시 제구 다운 없음
		PA_DOCK = 8, // [닥터K] 2개의 스트라익 잡으면 다음 공 제구 증가
		PA_INFIGHT = 9, // [인파이터] 타자의 몸쪽으로 공을 던질시 제구 증가
		PA_OUTFIGHT = 10, // [아웃파이터] 타자의 바깥쪽으로 공을 던질시 제구 증가
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
		PF_OVER = 1, // [오버] 오버
		PF_THREEQUARTER = 2, // [쓰리쿼터] 쓰리쿼터
		PF_SIDEARM = 3, // [사이드암] 사이드암
		PF_UNDER = 4, // [언더] 언더
		PF_NULL = 5, // [없음] 없음
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
		EPO_ONPLAYER = 1, // [온라인플레이어] 온라인플레이어
		EPO_OFFPLAYER = 2, // [오프라인플레이어] 오프라인플레이어
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
		EPBT_SMALL = 1, // [스몰] 스몰
		EPBT_MIDIUM = 2, // [미디엄] 미디엄
		EPBT_LARGE = 3, // [라지] 라지
		EPBT_WOMAN = 4, // [여성] 여성
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
		PBB_NULL = 1, // [없음] 없음
		PBB_FOURSEAM = 2, // [포심] 포심
		PBB_TWOSEAM = 3, // [투심] 투심
		PBB_RISINGFAST = 4, // [라이징패스트볼] 라이징패스트볼
		PBB_UPSHOUT = 5, // [업슛] 업슛
		PBB_SLIDER = 6, // [슬라이더] 슬라이더
		PBB_HSLIDER = 7, // [H슬라이더] H슬라이더
		PBB_CUTFAST = 8, // [컷패스트볼] 컷패스트볼
		PBB_VSLIDER = 9, // [V슬라이더] V슬라이더
		PBB_SLUB = 10, // [슬러브] 슬러브
		PBB_CHANGEUP = 11, // [체인지업] 체인지업
		PBB_CIRCLECHANGEUP = 12, // [서클체인지업] 서클체인지업
		PBB_KNUCKLE = 13, // [너클] 너클
		PBB_CURVE = 14, // [커브] 커브
		PBB_SLOWCURVE = 15, // [슬로우커브] 슬로우커브
		PBB_KNUCKLECURVE = 16, // [너클커브] 너클커브
		PBB_DROPCURVE = 17, // [드랍커브] 드랍커브
		PBB_POWERCURVE = 18, // [파워커브] 파워커브
		PBB_SHOUT = 19, // [슈트] 슈트
		PBB_HSHOUT = 20, // [H슈트] H슈트
		PBB_FORK = 21, // [포크] 포크
		PBB_PALM = 22, // [팜] 팜
		PBB_SFF = 23, // [SFF] SFF
		PBB_SINKER = 24, // [싱커_ 스크류] 싱커#  스크류
		PBB_HSINKER = 25, // [H싱커] H싱커
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
		PGT_E = 1, // [E등급] E등급 선수
		PGT_D = 2, // [D등급] D등급 선수
		PGT_C = 3, // [C등급] C등급 선수
		PGT_B = 4, // [B등급] B등급 선수
		PGT_A = 5, // [A등급] A등급 선수
		PGT_S = 6, // [S등급] S등급 선수
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


	public enum EShopBetterSection
	{
		eBEGIN_EShopBetterSection=0,
		ESBS_NULL = 1, // [없음] 없음
		ESBS_A = 2, // [섹션 A] 샵의 섹션 A(타자=헬멧)
		ESBS_B = 3, // [섹션 B] 샵의 섹션 B(타자=배트)
		ESBS_C = 4, // [섹션 C] 샵의 섹션 C(타자=장갑)
		ESBS_D = 5, // [섹션 D] 샵의 섹션 D(타자=신발)
		ESBS_E = 6, // [섹션 E] 샵의 섹션 E(타자=상의#  하의)
		ESBS_F = 7, // [섹션 F] 샵의 섹션 F(타자=양말#  리스트밴드)
		ESBS_G = 8, // [섹션 G] 샵의 섹션 G(타자=팔보호대#  다리보호대)
		ESBS_H = 9, // [섹션 H] 샵의 섹션 H(타자=목걸이# 반지#  귀걸이)
		ESBS_I = 10, // [섹션 I] 샵의 섹션 I(타자=(문신#  선글라스#  아이패치)
		ESBS_J = 11, // [섹션 J] 샵의 섹션 J(타자=(수염#  헤어#  패치#  마스크#  등번호#  마킹#  헤어컬러)
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
		ESCS_NULL = 1, // [없음] 없음
		ESCS_A = 2, // [섹션 A] 샵의 섹션 A(소비=버프 아이템)
		ESCS_B = 3, // [섹션 B] 샵의 섹션 B(소비=스텟 영구상승 아이템)
		ESCS_C = 4, // [섹션 C] 샵의 섹션 C(소비=업그레이드 관련 아이템)
		ESCS_D = 5, // [섹션 D] 샵의 섹션 D(소비=아이템 레벨 하향#  강화 취소 아이템)
		ESCS_E = 6, // [섹션 E] 샵의 섹션 E(소비=패키지 아이템)
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
		SIT_Sys_Package = 1, // [패키지] 패키지
		SIT_Sys_ItemEquip = 2, // [장착아이템] 장착아이템
		SIT_Sys_ItemStuff = 3, // [재료아이템] 재료아이템
		SIT_Sys_ItemConsume = 4, // [소모아이템] 소모아이템
		SIT_Sys_PlayerSkillSticker = 5, // [변화구아이템] 변화구아이템(변화구 구매 시 변화구에 제한되어있는 레벨 무시하고 착용 가능#  변화구 업그레이드--)다음 변화구 언락을 위한(--는 그대로 적용)
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
		ESPS_NULL = 1, // [없음] 없음
		ESPS_A = 2, // [섹션 A] 샵의 섹션 A(투수=모자)
		ESPS_B = 3, // [섹션 B] 샵의 섹션 B(투수=볼)
		ESPS_C = 4, // [섹션 C] 샵의 섹션 C(투수=글러브)
		ESPS_D = 5, // [섹션 D] 샵의 섹션 D(투수=신발)
		ESPS_E = 6, // [섹션 E] 샵의 섹션 E(투수=상의#  하의)
		ESPS_F = 7, // [섹션 F] 샵의 섹션 E(투수=양말#  리스트밴드)
		ESPS_G = 8, // [섹션 G] 샵의 섹션 F (투수=목걸이# 반지#  귀걸이)
		ESPS_H = 9, // [섹션 H] 샵의 섹션 H(투수=문신#  선글라스#  아이패치)
		ESPS_I = 10, // [섹션 I] 샵의 섹션 I(투수=수염#  헤어#  패치#  마스크#  등번호#  마킹#  헤어컬러)
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
		TGT_Match = 1, // [매치] 매치
		TGT_Single = 2, // [싱글] 싱글
		TGT_Friendly = 3, // [프랜들리] 프랜들리
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
