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
	// enum형 코드 템플릿 정의
	// -------------------------------------------------

	public enum EBaseballObjectType : byte
	{
		eBEGIN_EBaseballObjectType=0,
		BOT_user = 1, // [유저] 유저
		BOT_pitcher = 2, // [투수] 투수
		BOT_better = 3, // [타자] 타자
		BOT_team = 4, // [팀] 팀
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
		BA_NULL = 1, // [없음] 없음
		BA_LEFT = 2, // [대좌투수] 좌투수상대시 파워 증가. 소유시 BA_RIGHT스티커는 가질수없슴
		BA_RIGHT = 3, // [대우투수] 대우투수 상대시 파워 증가. 소유시 BA_LEFT스티커는 가질수없슴
		BA_HOMERUN = 4, // [홈런타자] 히트시 파워 증가
		BA_WIDE = 5, // [광각타법] 광각타법 - 밀어쳤을때 파워 다운없음
		BA_FULLHIT = 6, // [풀히터] 풀히터 - 당겨쳤을때 파워 증가
		BA_LOWHIT = 7, // [로볼히터] 로볼히터 - 타격판정시 하단/중단에서 파워 증가
		BA_HIGHHIT = 8, // [하이볼히터] 하이볼히터 - 중단# 상단에서 파워 증가
		BA_RUNFIRE = 9, // [연발] 연발 - 바로 이전타석에서 홈런시 파워 증가
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
		BF_SQUARE = 1, // [스퀘어] 스쿼어
		BF_OPEN = 2, // [오픈] 오픈
		BF_CLOSE = 3, // [크로즈드] 크로즈드
		BF_NULL = 4, // [없음] 없음
		BF_COMMON = 5, // [공통] 공통
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
		EBHT_STANDOUT = 1, // [스탠드아웃] 스탠드아웃
		EBHT_SWINGOUT = 2, // [스윙아웃] 스윙아웃
		EBHT_FOULOUT = 3, // [파울아웃] 파울아웃
		EBIT_INFIELDOUT = 4, // [내야아웃] 내야아웃
		EBIT_LEFTFIELDOUT = 5, // [좌익수아웃] 좌익수아웃
		EBIT_CENTERFIELDOUT = 6, // [중견수아웃] 중견수아웃
		EBIT_RIGHTFIELDOUT = 7, // [우익수아웃] 우익수아웃
		EBHT_NO_HIT = 8, // [치지못한상태] 이 이상은 아웃상태를 나타내기위한 값
		EBHT_ONEHIT = 9, // [일루타] 일루타
		EBHT_DOUBLEHIT = 10, // [이루타] 이루타
		EBHT_TRIPLEHIT = 11, // [삼루타] 삼루타
		EBHT_HOMERUN = 12, // [홈런] 홈런
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
		EBBP_STRAIGHT = 1, // [직구] 직구
		EBBP_WIDE = 2, // [횡변화] 횡변화
		EBBP_HEIGHT = 3, // [종변화] 종변화
		EBBP_HEIGHTWIDE = 4, // [종횡변화] 종횡변화
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
		EBBR_REGULAR = 1, // [정회전] 정회전
		EBBR_REVERSE = 2, // [역회전] 역회전
		EBBR_NOTHING = 3, // [무회전] 무회전
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
		ECS_ITEM = 1, // [아이템] 아이템관련 스트링. Text1=이름 text2=설명 단 공용아이템일때는 text2=타자용설명 text3=투수용설명
		ECS_GUI = 2, // [GUI] 화면 GUI용 스트링
		ECS_SKILL = 3, // [스킬용] 스킬용 스트링, text1=이름 text2=설명
		ECS_ETC = 4, // [기타] 그외 스트링
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
		ET_MONEY = 1, // [머니] 머니
		ET_ITEM = 2, // [아이템] 아이템
		ET_MONEY_ITEM = 3, // [머니_아이템] 머니_아이템
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
		EGT_NULL = 1, // [없음] 없음
		EGT_GAMEMONEY = 2, // [게임머니] 게임머니
		EGT_PLAYERSKILLSTICKER = 3, // [스킬스티커] 스킬스티커
		EGT_PLAYERCARD = 4, // [플레이어카드] 플레이어카드
		EGT_GAMECASH = 5, // [게임 캐쉬] 게임캐쉬
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
		EHTT_eHitTime_None = 0, // [클라이언트용] 클라이언트용 (값은 0_서버에서는 처리하지 않음)
		EHTT_eHitTime_VeryFast = 1, // [매우 빠름] 매우 빠름
		EHTT_eHitTime_Fast = 2, // [빠름] 빠름
		EHTT_eHitTime_GoodFast = 3, // [적정 빠름] 적정 빠름
		EHTT_eHitTime_Perfect = 4, // [퍼펙트 빠름] 퍼펙트 빠름
		EHTT_eHitTime_GoodSlow = 5, // [적정 느림] 적정 느림
		EHTT_eHitTime_Slow = 6, // [느림] 느림
		EHTT_eHitTime_VerySlow = 7, // [매우 느림] 매우 느림
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
		EHT_eNS_NONE = 0, // [클라이언트용] 클라이언트용 (값은 0_서버에서는 처리하지 않음)
		EHT_eNS_BALLHIT = 1, // [일반 히트] 일반 히트
		EHT_eNS_BALLHITSTRONG = 2, // [강진_스트롱 히트] 강진_스트롱 히트
		EHT_eNS_SWING = 3, // [헛스윙] 헛스윙
		EHT_eNS_NOTHING = 4, // [대기 상태] 대기 상태
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
		IAT_POWER = 1, // [파워] 파워
		IAT_ACCURACY = 2, // [정확] 정확
		IAT_FOCUS = 3, // [제구] 제구
		IAT_SPEED = 4, // [구속] 구속
		IAT_BREAKINGBALL = 5, // [변화구] 변화구
		IAT_ALLABILITY = 6, // [모든스텟] 모든스텟
		IAT_NULL = 7, // [없음] 없음
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
		IBT_BUY_CASH = 1, // [캐쉬 구매 아이템] 캐쉬 구매 아이템
		IBT_BUY_POINT = 2, // [포인트 구매 아이템] 포인트 구매 아이템
		IBT_BUY_USED = 3, // [캐쉬귀속아이템] 캐쉬OR포인트구매아이템인데 귀속된상태
		IBT_EVENT = 4, // [이벤트 지급아이템] 이벤트지급아이템
		IBT_REWARD = 5, // [경기보상으로받음] 트레이닝 or 경기보상 지급아이템
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
		IC_EQUIP = 1, // [착용장비] 착용장비
		IC_CONSUME = 2, // [소모아이템] 소모아이템
		IC_STUFF = 3, // [재료아이템] 재료아이템
		IC_NULL = 4, // [없음] 없음
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
		ICE_SHIRT = 1, // [상의] 상의
		ICE_PANT = 2, // [하의] 하의
		ICE_CAP = 3, // [모자] 모자 메인아이템#
		ICE_SHOES_B = 4, // [타자 신발] 타자 신발 메인아이템#
		ICE_SHOES_P = 5, // [투수 신발] 투수 신발 메인아이템#
		ICE_GLOVE = 6, // [투수글러브] 투수글러브 메인아이템#
		ICE_U_SHIRT = 7, // [언더셔츠] 언더셔츠
		ICE_SOCKS = 8, // [양말] 양말
		ICE_ARM_GUARDS = 9, // [팔_보호대] 팔_보호대
		ICE_LEG_GUARDS = 10, // [다리_보호대] 다리_보호대
		ICE_BAT = 11, // [배트] 배트 메인아이템
		ICE_BALL = 12, // [볼] 볼 메인아이템#
		ICE_HELMET = 13, // [헬멧] 헬멧 메인아이템#
		ICE_GLOBE = 14, // [타자장갑] 타자용 장갑 메인아이템#
		ICE_WRISTBAND = 15, // [리스트 밴드] 손목 아대
		ICE_NECKLACE = 16, // [목걸이] 목걸이
		ICE_RING = 17, // [반지] 반지
		ICE_EARRING = 18, // [귀걸이] 귀걸이
		ICE_TATOO = 19, // [문신] 문신
		ICE_SUNGLASS = 20, // [선글라스] 선글라스
		ICE_EYEPATCH = 21, // [아이패치] 눈 밑 패치
		ICE_BEARD = 22, // [수염] 수염
		ICE_HAIR_M = 23, // [남성헤어스타일] 남성헤어스타일
		ICE_HAIR_W = 24, // [여성헤어스타일] 여성헤어스타일
		ICE_HAIR_COLOR = 25, // [헤어칼라] 헤어칼라
		ICE_PATCH = 26, // [패치] 패치
		ICE_MASK = 27, // [마스크] 마스크
		ICE_BACKNUMBER = 28, // [등번호 아이템] 등번호 아이템
		ICE_MAKING = 29, // [마킹 아이템] 마킹 아이템
		ICE_FACE = 30, // [얼굴] 얼굴
		ICE_ARM = 31, // [팔] 팔
		ICE_LEG = 32, // [다리(여자)] 다리(여자)
		ICE_LEFTHAND = 33, // [왼손] 왼손
		ICE_RIGHTHAND = 34, // [오른손] 오른손
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
		IPT_CASH = 1, // [캐쉬] 캐쉬 로만 살수있는 아이템
		IPT_CASH_POINT = 2, // [캐쉬_포인트] 캐쉬 또는 포인트 로 살수 있는 아이템
		IPT_MONEY = 3, // [포인트] 캐쉬 또는 포인트# 게임머니로 살수 있는 아이템
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
		IUT_NORMAL = 1, // [가능] 가능
		IUT_INSTANTLY = 2, // [기간제] 기간내 횟수 소진 다 했으면 재 사용
		IUT_FIXED = 3, // [불가] 불가
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
		ISS_SELL_STOP = 1, // [판매중지] 판매중지( 판매하다가 정책상 폐기된 아이템)
		ISS_SELL = 2, // [판매중] 판매중
		ISS_SELL_PLAN = 3, // [판매예정] 판매예정
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
		IST_MAN_ONLY = 1, // [남] 
		IST_WOMAN_ONLY = 2, // [여] 
		IST_COMMON = 3, // [공용] 
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
		IS_NORMAL = 1, // [일반상태] 일반상태
		IS_DELETE = 2, // [삭제된상태] 삭제된상태
		IS_ADMIN_BLOCKED = 3, // [사용불가능.] 사용불가능.
		IS_DELETE_REFUND = 4, // [되팔기되어 삭제됨] 되팔기되어 삭제됨
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
		ISGT_EE = 1, // [EE등급] EE등급
		ISGT_DE = 2, // [DE등급] DE등급
		ISGT_DD = 3, // [DD등급] DD등급
		ISGT_CE = 4, // [CE등급] CE등급
		ISGT_CD = 5, // [CD등급] CD등급
		ISGT_CC = 6, // [CC등급] CC등급
		ISGT_BE = 7, // [BE등급] BE등급
		ISGT_BD = 8, // [BD등급] BD등급
		ISGT_BC = 9, // [BC등급] BC등급
		ISGT_BB = 10, // [BB등급] BB등급
		ISGT_AE = 11, // [AE등급] AE등급
		ISGT_AD = 12, // [AD등급] AD등급
		ISGT_AC = 13, // [AC등급] AC등급
		ISGT_AB = 14, // [AB등급] AB등급
		ISGT_AA = 15, // [AA등급] AA등급
		ISGT_SE = 16, // [SE등급] SE등급
		ISGT_SD = 17, // [SD등급] SD등급
		ISGT_SC = 18, // [SC등급] SC등급
		ISGT_SB = 19, // [SB등급] SB등급
		ISGT_SA = 20, // [SA등급] SA등급
		ISGT_SS = 21, // [SS등급] SS등급
		ISGT_NULL = 22, // [등급없음] 등급없음(NULL일 경우 해당 등급의 무급)
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
		SCT_KINGROOKIE = 1, // [로그1] 로그1
		SCT_ROOKIE = 2, // [로그2] 로그2
		SCT_AMA1 = 3, // [로그3] 로그3
		SCT_AMA2 = 4, // [로그4] 로그4
		SCT_PRO = 5, // [로그5] 로그5
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
		NT_LED = 1, // [전광판] 전광판
		NT_CHECK = 2, // [임시점검] 임시점검
		NT_NOTICE = 3, // [공지사항] 공지사항
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
		ENSS_STANDING_BY = 1, // [대기중] 대기중 일시 출력
		ENSS_SELECTION = 2, // [선택 시] 선택시 출력
		ENSS_UPGRADE_WORKING = 3, // [업그레이드 중] 업그레이드 중 일시 출력
		ENSS_TRANING_WORKING = 4, // [트레이닝 중] 트레이닝 중 일시 출력
		ENSS_COMPLETE = 5, // [완료] 완료 시에 출력
		ENSS_UPGRADE_RESULT = 6, // [업그레이드 결과] 업그레이드 결과  출력
		ENSS_TRANING_RESULT = 7, // [트레이닝 결과] 트레이닝 결과  출력
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
		ENS_MAESTRO = 1, // [장인] 장인
		ENS_COACH = 2, // [투수코치] 투수코치
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
		PA_NULL = 1, // [없음] 없음
		PA_LEFT = 2, // [대좌타자] 좌타자상대시 능력치증가. PA_RIGHT속성의 스킬 스티커는 가질수없슴
		PA_RIGHT = 3, // [대우타자] 우타자상대시 능력치증가. PA_LEFT속성의 스킬 스티커는 가질수 없슴
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
		PF_OVER = 1, // [오버] 오버
		PF_THREEQUARTER = 2, // [쓰리쿼터] 쓰리쿼터
		PF_SIDEARM = 3, // [사이드암] 사이드암
		PF_UNDER = 4, // [언더] 언더
		PF_NULL = 5, // [없음] 없음
		PF_COMMON = 6, // [공통] 공통
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
		EPO_ONPLAYER = 1, // [온라인플레이어] 온라인플레이어
		EPO_OFFPLAYER = 2, // [오프라인플레이어] 오프라인플레이어
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
		EPBT_SMALL = 1, // [스몰] 스몰
		EPBT_MIDIUM = 2, // [미디엄] 미디엄
		EPBT_LARGE = 3, // [라지] 라지
		EPBT_WOMAN = 4, // [여성] 여성
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
		PNT_KOREA = 1, // [한국] 한국
		PNT_USA = 2, // [미국] 미국
		PNT_JAPAN = 3, // [일본] 일본
		PNT_CHINA = 4, // [중국] 중국
		PNT_CANADA = 5, // [캐나다] 캐나다
		PNT_ITALY = 6, // [이탈리아] 이탈리아
		PNT_TAIWAN = 7, // [대만] 대만
		PNT_AUSTRALIA = 8, // [호주] 호주
		PNT_NETHERLANDS = 9, // [네덜란드] 네덜란드
		PNT_CUBA = 10, // [쿠바] 쿠바
		PNT_TRINIDADANDTOBAGO = 11, // [트리니다드토바고] 트리니다드토바고
		PNT_DOMINICANREPUBLIC = 12, // [도미니카공화국] 도미니카공화국
		PNT_PANAMA = 13, // [파나마] 파나마
		PNT_PUERTORICO = 14, // [푸에르토리코] 푸에르토리코
		PNT_REPUBLICOFSOUTHAFRICA = 15, // [남아프리카공화국] 남아프리카공화국
		PNT_VENEZUELA = 16, // [베네수엘라] 베네수엘라
		PNT_UNITEDKINGDOM = 17, // [영국] 영국
		PNT_SPAIN = 18, // [스페인] 스페인
		PNT_FRANCE = 19, // [프랑스] 프랑스
		PNT_GERMANY = 20, // [독일] 독일
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
		PT_BATTER = 1, // [타자] 타자
		PT_PITCHER = 2, // [투수] 투수
		PT_COMMON = 3, // [공용] 타자투수구분없음
		PT_CATCHER = 4, // [포수] 포수
		PT_UMPIRE = 5, // [심판] 심판
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
		QCT_NULL = 1, // [없음] 없음
		QCT_EQUIPGRADETYPE = 12, // [전체장비착용조건] 전체장비착용조건이 condition1에 있는 값의 조건(EItemGradeType)에 해당하면 보상을 준다
		QCT_CASHCOUNT = 13, // [캐쉬템구매조건] 캐쉬템구매조건
		QCT_GAMEMONEYCOUNT = 14, // [게임머니누적조건] 게임머니누적조건
		QCT_PLAYERALLSTATCOUNT = 15, // [캐릭터모든능력치달성조건] 캐릭터모든능력치달성조건. 팀소속의 투수타자가 동시에 해당 능력치 도달시 준다. pitcher_breakingball는 조건에서 제외
		QCT_GAME_VALIABLE = 16, // [게임변수] 정해진 게임내변수의 조건. 게임변수의 종류참고하시오
		QCT_MANUAL_FINISH = 17, // [임의완료] 튜토리얼 or 일일퀘스트등 완료조건이 EQuestType에의해 결정됨.완료통보
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
		EQT_MATCH = 1, // [MATCH 퀘스트] MATCH 퀘스트
		EQT_SINGLE = 2, // [SINGLE 퀘스트] SINGLE 퀘스트
		EQT_FRIENDLY = 3, // [FRIENDLY 퀘스트] FRIENDLY 퀘스트
		EQT_ITEMETC = 4, // [ITEM_ETC 퀘스트] ITEM_ETC 퀘스트
		EQT_INGAMETUTORIAL = 5, // [TUTORIAL] 인게임 튜토리얼. 완료조건을 클라이언트가 체크후 보낸다.(x2ug_quest_end)
		EQT_DAILY = 6, // [DAILY 퀘스트] DAILIY 퀘스트. (주의 condition_value1의값은 0~100까지의 확률분포를 의미한다.)
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
		ERJ_eJudge_None = 0, // [클라이언트용] 클라이언트용 (값은 0_서버에서는 처리하지 않음)
		ERJ_eJudge_Bad = 1, // [배드] 배드
		ERJ_eJudge_Normal = 2, // [노멀] 노멀
		ERJ_eJudge_Good = 3, // [굳] 굳
		ERJ_eJudge_Perfect = 4, // [퍼팩트] 퍼팩트
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
		ESIT_Sys_Package = 1, // [패키지] 패키지
		ESIT_Sys_ItemEquip = 2, // [장착아이템] 장착아이템
		ESIT_Sys_ItemStuff = 3, // [재료아이템] 재료아이템
		ESIT_Sys_ItemConsume = 4, // [소모아이템] 소모아이템
		ESIT_Sys_PlayerSkillSticker = 5, // [변화구아이템] 변화구아이템(변화구 구매 시 변화구에 제한되어있는 레벨 무시하고 착용 가능#  변화구 업그레이드--)다음 변화구 언락을 위한(--는 그대로 적용)
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
		TGT_Match = 1, // [매치] 매치
		TGT_Single = 2, // [싱글] 싱글
		TGT_Friendly = 3, // [프랜들리] 프랜들리
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
