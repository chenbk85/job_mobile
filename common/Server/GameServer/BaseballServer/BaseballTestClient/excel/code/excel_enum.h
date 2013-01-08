/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_enum_
#define __namespace_nEXCEL___filename_excel_enum_

#include "table_const_excel_enum.h"
// -------------------------------------------------
// enum형 코드 템플릿 정의
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nEXCEL_excel_enum_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EBaseballObjectType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EBatterAbility,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EBatterForm,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EBatterHitType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EBreakingBallPitch,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EBreakingBallRotation,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(ECategoryString,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EConsumeItemEffect,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EEventType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EGestureType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EGiftCategory,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EGiftType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EGradeAllitemType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EHitTimmingType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EHitType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EItemAbilityType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EItemBuyType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EItemCategory,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EItemCategoryEquipment,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EItemGradeType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EItemPriceType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EItemReuseType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EItemSellStatus,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EItemSexType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EItemState,(상점에서 소비 아이템 선택 시 나뉘어지는 섹션의 구분),nMech,nEXCEL)\
	ENUM_TABLE(EItemSubGradeType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EItemUpgradeResult,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(ELogType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(ENoticeType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(ENpcSituationString,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(ENpcString,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EPitcherAbility,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EPitcherForm,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EPlayer_Onoffline,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EPlayerBodyType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EPlayerBreakingBall,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EPlayerGradeType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EPlayerNationType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EPlayerType,(포수와 심판은 클라이언트 스킴용),nMech,nEXCEL)\
	ENUM_TABLE(EQuestConditionType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EQuestType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(ERhythmJudge,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EShopBatterSection,(상점에서 장비 선택에서 타자 일경우 나뉘어지는 섹션의 구분),nMech,nEXCEL)\
	ENUM_TABLE(EShopConsumeSection,(상점에서 소비 아이템 선택 시 나뉘어지는 섹션의 구분),nMech,nEXCEL)\
	ENUM_TABLE(EShopItemType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EShopPitcherSection,(상점에서 장비 선택에서 투수 일경우 선택 시 나뉘어지는 섹션의 구분),nMech,nEXCEL)\
	ENUM_TABLE(ETotalGameType,설명없음,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// 주의 enum변수는 앞에 e가 자동으로 붙어서 선언됨 
	// -------------------------------------------------

	/* 설명없음 */
	#define for_each_nEXCEL_EBaseballObjectType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(BOT_user			,1,유저,nMech,nEXCEL,EBaseballObjectType)\
		ENUM_FIELD(BOT_pitcher			,2,투수,nMech,nEXCEL,EBaseballObjectType)\
		ENUM_FIELD(BOT_better			,3,타자,nMech,nEXCEL,EBaseballObjectType)\
		ENUM_FIELD(BOT_team			,4,팀,nMech,nEXCEL,EBaseballObjectType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EBatterAbility_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(BA_NULL			,1,없음,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_LEFT			,2,대좌투수,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_RIGHT			,3,대우투수,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_HOMERUN			,4,홈런타자,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_WIDE			,5,광각타법,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_FULLHIT			,6,풀히터,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_LOWHIT			,7,로볼히터,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_HIGHHIT			,8,하이볼히터,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_RUNFIRE			,9,연발,nMech,nEXCEL,EBatterAbility)\

	/* 설명없음 */
	#define for_each_nEXCEL_EBatterForm_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(BF_SQUARE			,1,스퀘어,nMech,nEXCEL,EBatterForm)\
		ENUM_FIELD(BF_OPEN			,2,오픈,nMech,nEXCEL,EBatterForm)\
		ENUM_FIELD(BF_CLOSE			,3,크로즈드,nMech,nEXCEL,EBatterForm)\
		ENUM_FIELD(BF_NULL			,4,없음,nMech,nEXCEL,EBatterForm)\
		ENUM_FIELD(BF_COMMON			,5,공통,nMech,nEXCEL,EBatterForm)\

	/* 설명없음 */
	#define for_each_nEXCEL_EBatterHitType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EBHT_STANDOUT			,1,스탠드아웃,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBHT_SWINGOUT			,2,스윙아웃,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBHT_FOULOUT			,3,파울아웃,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBIT_INFIELDOUT			,4,내야아웃,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBIT_LEFTFIELDOUT			,5,좌익수아웃,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBIT_CENTERFIELDOUT			,6,중견수아웃,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBIT_RIGHTFIELDOUT			,7,우익수아웃,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBHT_NO_HIT			,8,치지못한상태,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBHT_ONEHIT			,9,일루타,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBHT_DOUBLEHIT			,10,이루타,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBHT_TRIPLEHIT			,11,삼루타,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBHT_HOMERUN			,12,홈런,nMech,nEXCEL,EBatterHitType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EBreakingBallPitch_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EBBP_STRAIGHT			,1,직구,nMech,nEXCEL,EBreakingBallPitch)\
		ENUM_FIELD(EBBP_WIDE			,2,횡변화,nMech,nEXCEL,EBreakingBallPitch)\
		ENUM_FIELD(EBBP_HEIGHT			,3,종변화,nMech,nEXCEL,EBreakingBallPitch)\
		ENUM_FIELD(EBBP_HEIGHTWIDE			,4,종횡변화,nMech,nEXCEL,EBreakingBallPitch)\

	/* 설명없음 */
	#define for_each_nEXCEL_EBreakingBallRotation_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EBBR_REGULAR			,1,정회전,nMech,nEXCEL,EBreakingBallRotation)\
		ENUM_FIELD(EBBR_REVERSE			,2,역회전,nMech,nEXCEL,EBreakingBallRotation)\
		ENUM_FIELD(EBBR_NOTHING			,3,무회전,nMech,nEXCEL,EBreakingBallRotation)\

	/* 설명없음 */
	#define for_each_nEXCEL_ECategoryString_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ECS_ITEM			,1,아이템,nMech,nEXCEL,ECategoryString)\
		ENUM_FIELD(ECS_GUI			,2,GUI,nMech,nEXCEL,ECategoryString)\
		ENUM_FIELD(ECS_SKILL			,3,스킬용,nMech,nEXCEL,ECategoryString)\
		ENUM_FIELD(ECS_ETC			,4,기타,nMech,nEXCEL,ECategoryString)\

	/* 설명없음 */
	#define for_each_nEXCEL_EConsumeItemEffect_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(CIE_MONEYUP			,1,게임머니배수상승아이템,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_EXPUP			,2,경험치배수상승아이템,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_ITEMDROPUP			,3,아이템드롭확률상승아이템,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_STATUPWHILE			,4,능력치일시상승아이템,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_STATUPFOREVER			,5,능력치영구상승아이템,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_UPGRADELUCKYUP			,6,강화확률증가아이템,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_UPGRADETIMEDOWN			,7,강화시간감소아이템,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_UPGRADECANCEL			,8,강화취소아이템,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_ITEMUSEDOWN			,9,아이템사용가능레벨하향,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_ETC			,10,ETC,nMech,nEXCEL,EConsumeItemEffect)\

	/* 설명없음 */
	#define for_each_nEXCEL_EEventType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ET_MONEY			,1,머니,nMech,nEXCEL,EEventType)\
		ENUM_FIELD(ET_ITEM			,2,아이템,nMech,nEXCEL,EEventType)\
		ENUM_FIELD(ET_MONEY_ITEM			,3,머니_아이템,nMech,nEXCEL,EEventType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EGestureType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EGTT_STRAGHT			,1,직선,nMech,nEXCEL,EGestureType)\
		ENUM_FIELD(EGTT_VERTICAL			,2,수직선,nMech,nEXCEL,EGestureType)\
		ENUM_FIELD(EGTT_CURVE			,3,곡선,nMech,nEXCEL,EGestureType)\
		ENUM_FIELD(EGTT_STAIR_VERTICAL			,4,계단형수직선,nMech,nEXCEL,EGestureType)\
		ENUM_FIELD(EGTT_S_CURVE			,5,에스형곡선,nMech,nEXCEL,EGestureType)\
		ENUM_FIELD(EGTT_NULL			,6,없음,nMech,nEXCEL,EGestureType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EGiftCategory_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EGC_SINGLEGAMEWIN			,1,싱글게임승,nMech,nEXCEL,EGiftCategory)\
		ENUM_FIELD(EGC_SINGLEGAMELOSE			,2,싱글게임패,nMech,nEXCEL,EGiftCategory)\
		ENUM_FIELD(EGC_MATCHGAMEWIN			,3,대전게임승,nMech,nEXCEL,EGiftCategory)\
		ENUM_FIELD(EGC_MATCHGAMELOSE			,4,대전게임패,nMech,nEXCEL,EGiftCategory)\
		ENUM_FIELD(EGC_FRIENDGAMEWIN			,5,친구게임승,nMech,nEXCEL,EGiftCategory)\
		ENUM_FIELD(EGC_FRIENDGAMELOSE			,6,친구게임패,nMech,nEXCEL,EGiftCategory)\
		ENUM_FIELD(EGC_TRAININGWIN			,7,트레이닝승,nMech,nEXCEL,EGiftCategory)\
		ENUM_FIELD(EGC_TRAININGLOSE			,8,트레이닝패,nMech,nEXCEL,EGiftCategory)\

	/* 설명없음 */
	#define for_each_nEXCEL_EGiftType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EGT_NULL			,1,없음,nMech,nEXCEL,EGiftType)\
		ENUM_FIELD(EGT_GAMEMONEY			,2,게임머니,nMech,nEXCEL,EGiftType)\
		ENUM_FIELD(EGT_PLAYERSKILLSTICKER			,3,스킬스티커,nMech,nEXCEL,EGiftType)\
		ENUM_FIELD(EGT_PLAYERCARD			,4,플레이어카드,nMech,nEXCEL,EGiftType)\
		ENUM_FIELD(EGT_GAMECASH			,5,게임 캐쉬,nMech,nEXCEL,EGiftType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EGradeAllitemType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EGAT_NULL			,1,없음,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_SMAINITEMALL			,2,S급 메인아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_AMAINITEMALL			,3,A급 메인아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_BMAINITEMALL			,4,B급 메인아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_CMAINITEMALL			,5,C급 메인아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_DMAINITEMALL			,6,D급 메인아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_EMAINITEMALL			,7,E급 메인아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_SSUBITEMALL			,8,S급 서브아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_ASUBITEMALL			,9,A급 서브아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_BSUBITEMALL			,10,B급 서브아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_CSUBITEMALL			,11,C급 서브아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_DSUBITEMALL			,12,D급 서브아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_ESUBITEMALL			,13,E급 서브아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_SCONSUMEITEMALL			,14,S급 소비아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_ACONSUMEITEMALL			,15,A급 소비아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_BCONSUMEITEMALL			,16,B급 소비아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_CCONSUMEITEMALL			,17,C급 소비아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_DCONSUMEITEMALL			,18,D급 소비아이템 모두,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_ECONSUMEITEMALL			,19,E급 소비아이템 모두,nMech,nEXCEL,EGradeAllitemType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EHitTimmingType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EHTT_eHitTime_None			,0,클라이언트용,nMech,nEXCEL,EHitTimmingType)\
		ENUM_FIELD(EHTT_eHitTime_VeryFast			,1,매우 빠름,nMech,nEXCEL,EHitTimmingType)\
		ENUM_FIELD(EHTT_eHitTime_Fast			,2,빠름,nMech,nEXCEL,EHitTimmingType)\
		ENUM_FIELD(EHTT_eHitTime_GoodFast			,3,적정 빠름,nMech,nEXCEL,EHitTimmingType)\
		ENUM_FIELD(EHTT_eHitTime_Perfect			,4,퍼펙트 빠름,nMech,nEXCEL,EHitTimmingType)\
		ENUM_FIELD(EHTT_eHitTime_GoodSlow			,5,적정 느림,nMech,nEXCEL,EHitTimmingType)\
		ENUM_FIELD(EHTT_eHitTime_Slow			,6,느림,nMech,nEXCEL,EHitTimmingType)\
		ENUM_FIELD(EHTT_eHitTime_VerySlow			,7,매우 느림,nMech,nEXCEL,EHitTimmingType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EHitType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EHT_eNS_NONE			,0,클라이언트용,nMech,nEXCEL,EHitType)\
		ENUM_FIELD(EHT_eNS_BALLHIT			,1,일반 히트,nMech,nEXCEL,EHitType)\
		ENUM_FIELD(EHT_eNS_BALLHITSTRONG			,2,강진_스트롱 히트,nMech,nEXCEL,EHitType)\
		ENUM_FIELD(EHT_eNS_SWING			,3,헛스윙,nMech,nEXCEL,EHitType)\
		ENUM_FIELD(EHT_eNS_NOTHING			,4,대기 상태,nMech,nEXCEL,EHitType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EItemAbilityType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IAT_POWER			,1,파워,nMech,nEXCEL,EItemAbilityType)\
		ENUM_FIELD(IAT_ACCURACY			,2,정확,nMech,nEXCEL,EItemAbilityType)\
		ENUM_FIELD(IAT_FOCUS			,3,제구,nMech,nEXCEL,EItemAbilityType)\
		ENUM_FIELD(IAT_SPEED			,4,구속,nMech,nEXCEL,EItemAbilityType)\
		ENUM_FIELD(IAT_BREAKINGBALL			,5,변화구,nMech,nEXCEL,EItemAbilityType)\
		ENUM_FIELD(IAT_ALLABILITY			,6,모든스텟,nMech,nEXCEL,EItemAbilityType)\
		ENUM_FIELD(IAT_NULL			,7,없음,nMech,nEXCEL,EItemAbilityType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EItemBuyType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IBT_BUY_CASH			,1,캐쉬 구매 아이템,nMech,nEXCEL,EItemBuyType)\
		ENUM_FIELD(IBT_BUY_POINT			,2,포인트 구매 아이템,nMech,nEXCEL,EItemBuyType)\
		ENUM_FIELD(IBT_BUY_USED			,3,캐쉬귀속아이템,nMech,nEXCEL,EItemBuyType)\
		ENUM_FIELD(IBT_EVENT			,4,이벤트 지급아이템,nMech,nEXCEL,EItemBuyType)\
		ENUM_FIELD(IBT_REWARD			,5,경기보상으로받음,nMech,nEXCEL,EItemBuyType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EItemCategory_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IC_EQUIP			,1,착용장비,nMech,nEXCEL,EItemCategory)\
		ENUM_FIELD(IC_CONSUME			,2,소모아이템,nMech,nEXCEL,EItemCategory)\
		ENUM_FIELD(IC_STUFF			,3,재료아이템,nMech,nEXCEL,EItemCategory)\
		ENUM_FIELD(IC_NULL			,4,없음,nMech,nEXCEL,EItemCategory)\

	/* 설명없음 */
	#define for_each_nEXCEL_EItemCategoryEquipment_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ICE_SHIRT			,1,상의,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_PANT			,2,하의,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_CAP			,3,모자,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_SHOES_B			,4,타자 신발,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_SHOES_P			,5,투수 신발,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_GLOVE			,6,투수글러브,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_U_SHIRT			,7,언더셔츠,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_SOCKS			,8,양말,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_ARM_GUARDS			,9,팔_보호대,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_LEG_GUARDS			,10,다리_보호대,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_BAT			,11,배트,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_BALL			,12,볼,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_HELMET			,13,헬멧,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_GLOBE			,14,타자장갑,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_WRISTBAND			,15,리스트 밴드,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_NECKLACE			,16,목걸이,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_RING			,17,반지,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_EARRING			,18,귀걸이,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_TATOO			,19,문신,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_SUNGLASS			,20,선글라스,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_EYEPATCH			,21,아이패치,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_BEARD			,22,수염,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_HAIR_M			,23,남성헤어스타일,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_HAIR_W			,24,여성헤어스타일,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_HAIR_COLOR			,25,헤어칼라,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_PATCH			,26,패치,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_MASK			,27,마스크,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_BACKNUMBER			,28,등번호 아이템,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_MAKING			,29,마킹 아이템,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_FACE			,30,얼굴,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_ARM			,31,팔,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_LEG			,32,다리(여자),nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_LEFTHAND			,33,왼손,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_RIGHTHAND			,34,오른손,nMech,nEXCEL,EItemCategoryEquipment)\

	/* 설명없음 */
	#define for_each_nEXCEL_EItemGradeType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IGT_E			,1,E등급,nMech,nEXCEL,EItemGradeType)\
		ENUM_FIELD(IGT_D			,2,D등급,nMech,nEXCEL,EItemGradeType)\
		ENUM_FIELD(IGT_C			,3,C등급,nMech,nEXCEL,EItemGradeType)\
		ENUM_FIELD(IGT_B			,4,B등급,nMech,nEXCEL,EItemGradeType)\
		ENUM_FIELD(IGT_A			,5,A등급,nMech,nEXCEL,EItemGradeType)\
		ENUM_FIELD(IGT_S			,6,S등급,nMech,nEXCEL,EItemGradeType)\
		ENUM_FIELD(IGT_NULL			,7,무등급,nMech,nEXCEL,EItemGradeType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EItemPriceType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IPT_CASH			,1,캐쉬,nMech,nEXCEL,EItemPriceType)\
		ENUM_FIELD(IPT_CASH_POINT			,2,캐쉬_포인트,nMech,nEXCEL,EItemPriceType)\
		ENUM_FIELD(IPT_MONEY			,3,포인트,nMech,nEXCEL,EItemPriceType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EItemReuseType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IUT_NORMAL			,1,가능,nMech,nEXCEL,EItemReuseType)\
		ENUM_FIELD(IUT_INSTANTLY			,2,기간제,nMech,nEXCEL,EItemReuseType)\
		ENUM_FIELD(IUT_FIXED			,3,불가,nMech,nEXCEL,EItemReuseType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EItemSellStatus_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ISS_SELL_STOP			,1,판매중지,nMech,nEXCEL,EItemSellStatus)\
		ENUM_FIELD(ISS_SELL			,2,판매중,nMech,nEXCEL,EItemSellStatus)\
		ENUM_FIELD(ISS_SELL_PLAN			,3,판매예정,nMech,nEXCEL,EItemSellStatus)\

	/* 설명없음 */
	#define for_each_nEXCEL_EItemSexType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IST_MAN_ONLY			,1,남,nMech,nEXCEL,EItemSexType)\
		ENUM_FIELD(IST_WOMAN_ONLY			,2,여,nMech,nEXCEL,EItemSexType)\
		ENUM_FIELD(IST_COMMON			,3,공용,nMech,nEXCEL,EItemSexType)\

	/* (상점에서 소비 아이템 선택 시 나뉘어지는 섹션의 구분) */
	#define for_each_nEXCEL_EItemState_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IS_NORMAL			,1,일반상태,nMech,nEXCEL,EItemState)\
		ENUM_FIELD(IS_DELETE			,2,삭제된상태,nMech,nEXCEL,EItemState)\
		ENUM_FIELD(IS_ADMIN_BLOCKED			,3,사용불가능.,nMech,nEXCEL,EItemState)\
		ENUM_FIELD(IS_DELETE_REFUND			,4,되팔기되어 삭제됨,nMech,nEXCEL,EItemState)\

	/* 설명없음 */
	#define for_each_nEXCEL_EItemSubGradeType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ISGT_EE			,1,EE등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_DE			,2,DE등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_DD			,3,DD등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_CE			,4,CE등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_CD			,5,CD등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_CC			,6,CC등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_BE			,7,BE등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_BD			,8,BD등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_BC			,9,BC등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_BB			,10,BB등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_AE			,11,AE등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_AD			,12,AD등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_AC			,13,AC등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_AB			,14,AB등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_AA			,15,AA등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_SE			,16,SE등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_SD			,17,SD등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_SC			,18,SC등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_SB			,19,SB등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_SA			,20,SA등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_SS			,21,SS등급,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_NULL			,22,등급없음,nMech,nEXCEL,EItemSubGradeType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EItemUpgradeResult_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IUR_HELMET			,1,헬멧,nMech,nEXCEL,EItemUpgradeResult)\
		ENUM_FIELD(IUR_CAP			,2,모자,nMech,nEXCEL,EItemUpgradeResult)\
		ENUM_FIELD(IUR_BET			,3,배트,nMech,nEXCEL,EItemUpgradeResult)\
		ENUM_FIELD(IUR_BALL			,4,볼,nMech,nEXCEL,EItemUpgradeResult)\
		ENUM_FIELD(IUR_GLOBE			,5,타자장갑,nMech,nEXCEL,EItemUpgradeResult)\
		ENUM_FIELD(IUR_GLOVE			,6,글러브,nMech,nEXCEL,EItemUpgradeResult)\
		ENUM_FIELD(IUR_SHOES			,7,신발,nMech,nEXCEL,EItemUpgradeResult)\

	/* 설명없음 */
	#define for_each_nEXCEL_ELogType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(SCT_KINGROOKIE			,1,로그1,nMech,nEXCEL,ELogType)\
		ENUM_FIELD(SCT_ROOKIE			,2,로그2,nMech,nEXCEL,ELogType)\
		ENUM_FIELD(SCT_AMA1			,3,로그3,nMech,nEXCEL,ELogType)\
		ENUM_FIELD(SCT_AMA2			,4,로그4,nMech,nEXCEL,ELogType)\
		ENUM_FIELD(SCT_PRO			,5,로그5,nMech,nEXCEL,ELogType)\

	/* 설명없음 */
	#define for_each_nEXCEL_ENoticeType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(NT_LED			,1,전광판,nMech,nEXCEL,ENoticeType)\
		ENUM_FIELD(NT_CHECK			,2,임시점검,nMech,nEXCEL,ENoticeType)\
		ENUM_FIELD(NT_NOTICE			,3,공지사항,nMech,nEXCEL,ENoticeType)\

	/* 설명없음 */
	#define for_each_nEXCEL_ENpcSituationString_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ENSS_STANDING_BY			,1,대기중,nMech,nEXCEL,ENpcSituationString)\
		ENUM_FIELD(ENSS_SELECTION			,2,선택 시,nMech,nEXCEL,ENpcSituationString)\
		ENUM_FIELD(ENSS_UPGRADE_WORKING			,3,업그레이드 중,nMech,nEXCEL,ENpcSituationString)\
		ENUM_FIELD(ENSS_TRANING_WORKING			,4,트레이닝 중,nMech,nEXCEL,ENpcSituationString)\
		ENUM_FIELD(ENSS_COMPLETE			,5,완료,nMech,nEXCEL,ENpcSituationString)\
		ENUM_FIELD(ENSS_UPGRADE_RESULT			,6,업그레이드 결과,nMech,nEXCEL,ENpcSituationString)\
		ENUM_FIELD(ENSS_TRANING_RESULT			,7,트레이닝 결과,nMech,nEXCEL,ENpcSituationString)\

	/* 설명없음 */
	#define for_each_nEXCEL_ENpcString_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ENS_MAESTRO			,1,장인,nMech,nEXCEL,ENpcString)\
		ENUM_FIELD(ENS_COACH			,2,투수코치,nMech,nEXCEL,ENpcString)\

	/* 설명없음 */
	#define for_each_nEXCEL_EPitcherAbility_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(PA_NULL			,1,없음,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_LEFT			,2,대좌타자,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_RIGHT			,3,대우타자,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_FASTBALL			,4,속구파,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_FULLSKILL			,5,기교파,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_RUNFIRE			,6,연투,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_SWORDCON			,7,칼제구,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_DOCK			,8,닥터K,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_INFIGHT			,9,인파이터,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_OUTFIGHT			,10,아웃파이터,nMech,nEXCEL,EPitcherAbility)\

	/* 설명없음 */
	#define for_each_nEXCEL_EPitcherForm_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(PF_OVER			,1,오버,nMech,nEXCEL,EPitcherForm)\
		ENUM_FIELD(PF_THREEQUARTER			,2,쓰리쿼터,nMech,nEXCEL,EPitcherForm)\
		ENUM_FIELD(PF_SIDEARM			,3,사이드암,nMech,nEXCEL,EPitcherForm)\
		ENUM_FIELD(PF_UNDER			,4,언더,nMech,nEXCEL,EPitcherForm)\
		ENUM_FIELD(PF_NULL			,5,없음,nMech,nEXCEL,EPitcherForm)\
		ENUM_FIELD(PF_COMMON			,6,공통,nMech,nEXCEL,EPitcherForm)\

	/* 설명없음 */
	#define for_each_nEXCEL_EPlayer_Onoffline_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EPO_ONPLAYER			,1,온라인플레이어,nMech,nEXCEL,EPlayer_Onoffline)\
		ENUM_FIELD(EPO_OFFPLAYER			,2,오프라인플레이어,nMech,nEXCEL,EPlayer_Onoffline)\

	/* 설명없음 */
	#define for_each_nEXCEL_EPlayerBodyType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EPBT_SMALL			,1,스몰,nMech,nEXCEL,EPlayerBodyType)\
		ENUM_FIELD(EPBT_MIDIUM			,2,미디엄,nMech,nEXCEL,EPlayerBodyType)\
		ENUM_FIELD(EPBT_LARGE			,3,라지,nMech,nEXCEL,EPlayerBodyType)\
		ENUM_FIELD(EPBT_WOMAN			,4,여성,nMech,nEXCEL,EPlayerBodyType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EPlayerBreakingBall_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(PBB_NULL			,1,없음,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_FOURSEAM			,2,포심,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_TWOSEAM			,3,투심,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_RISINGFAST			,4,라이징패스트볼,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_UPSHOUT			,5,업슛,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_SLIDER			,6,슬라이더,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_HSLIDER			,7,H슬라이더,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_CUTFAST			,8,컷패스트볼,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_VSLIDER			,9,V슬라이더,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_SLUB			,10,슬러브,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_CHANGEUP			,11,체인지업,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_CIRCLECHANGEUP			,12,서클체인지업,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_KNUCKLE			,13,너클,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_CURVE			,14,커브,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_SLOWCURVE			,15,슬로우커브,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_KNUCKLECURVE			,16,너클커브,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_DROPCURVE			,17,드랍커브,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_POWERCURVE			,18,파워커브,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_SHOUT			,19,슈트,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_HSHOUT			,20,H슈트,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_FORK			,21,포크,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_PALM			,22,팜,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_SFF			,23,SFF,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_SINKER			,24,싱커_ 스크류,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_HSINKER			,25,H싱커,nMech,nEXCEL,EPlayerBreakingBall)\

	/* 설명없음 */
	#define for_each_nEXCEL_EPlayerGradeType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(PGT_E			,1,E등급,nMech,nEXCEL,EPlayerGradeType)\
		ENUM_FIELD(PGT_D			,2,D등급,nMech,nEXCEL,EPlayerGradeType)\
		ENUM_FIELD(PGT_C			,3,C등급,nMech,nEXCEL,EPlayerGradeType)\
		ENUM_FIELD(PGT_B			,4,B등급,nMech,nEXCEL,EPlayerGradeType)\
		ENUM_FIELD(PGT_A			,5,A등급,nMech,nEXCEL,EPlayerGradeType)\
		ENUM_FIELD(PGT_S			,6,S등급,nMech,nEXCEL,EPlayerGradeType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EPlayerNationType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(PNT_KOREA			,1,한국,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_USA			,2,미국,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_JAPAN			,3,일본,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_CHINA			,4,중국,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_CANADA			,5,캐나다,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_ITALY			,6,이탈리아,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_TAIWAN			,7,대만,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_AUSTRALIA			,8,호주,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_NETHERLANDS			,9,네덜란드,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_CUBA			,10,쿠바,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_TRINIDADANDTOBAGO			,11,트리니다드토바고,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_DOMINICANREPUBLIC			,12,도미니카공화국,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_PANAMA			,13,파나마,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_PUERTORICO			,14,푸에르토리코,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_REPUBLICOFSOUTHAFRICA			,15,남아프리카공화국,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_VENEZUELA			,16,베네수엘라,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_UNITEDKINGDOM			,17,영국,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_SPAIN			,18,스페인,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_FRANCE			,19,프랑스,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_GERMANY			,20,독일,nMech,nEXCEL,EPlayerNationType)\

	/* (포수와 심판은 클라이언트 스킴용) */
	#define for_each_nEXCEL_EPlayerType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(PT_BATTER			,1,타자,nMech,nEXCEL,EPlayerType)\
		ENUM_FIELD(PT_PITCHER			,2,투수,nMech,nEXCEL,EPlayerType)\
		ENUM_FIELD(PT_COMMON			,3,공용,nMech,nEXCEL,EPlayerType)\
		ENUM_FIELD(PT_CATCHER			,4,포수,nMech,nEXCEL,EPlayerType)\
		ENUM_FIELD(PT_UMPIRE			,5,심판,nMech,nEXCEL,EPlayerType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EQuestConditionType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(QCT_NULL			,1,없음,nMech,nEXCEL,EQuestConditionType)\
		ENUM_FIELD(QCT_EQUIPGRADETYPE			,12,전체장비착용조건,nMech,nEXCEL,EQuestConditionType)\
		ENUM_FIELD(QCT_CASHCOUNT			,13,캐쉬템구매조건,nMech,nEXCEL,EQuestConditionType)\
		ENUM_FIELD(QCT_GAMEMONEYCOUNT			,14,게임머니누적조건,nMech,nEXCEL,EQuestConditionType)\
		ENUM_FIELD(QCT_PLAYERALLSTATCOUNT			,15,캐릭터모든능력치달성조건,nMech,nEXCEL,EQuestConditionType)\
		ENUM_FIELD(QCT_GAME_VALIABLE			,16,게임변수,nMech,nEXCEL,EQuestConditionType)\
		ENUM_FIELD(QCT_MANUAL_FINISH			,17,임의완료,nMech,nEXCEL,EQuestConditionType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EQuestType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EQT_MATCH			,1,MATCH 퀘스트,nMech,nEXCEL,EQuestType)\
		ENUM_FIELD(EQT_SINGLE			,2,SINGLE 퀘스트,nMech,nEXCEL,EQuestType)\
		ENUM_FIELD(EQT_FRIENDLY			,3,FRIENDLY 퀘스트,nMech,nEXCEL,EQuestType)\
		ENUM_FIELD(EQT_ITEMETC			,4,ITEM_ETC 퀘스트,nMech,nEXCEL,EQuestType)\
		ENUM_FIELD(EQT_INGAMETUTORIAL			,5,TUTORIAL,nMech,nEXCEL,EQuestType)\
		ENUM_FIELD(EQT_DAILY			,6,DAILY 퀘스트,nMech,nEXCEL,EQuestType)\

	/* 설명없음 */
	#define for_each_nEXCEL_ERhythmJudge_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ERJ_eJudge_None			,0,클라이언트용,nMech,nEXCEL,ERhythmJudge)\
		ENUM_FIELD(ERJ_eJudge_Bad			,1,배드,nMech,nEXCEL,ERhythmJudge)\
		ENUM_FIELD(ERJ_eJudge_Normal			,2,노멀,nMech,nEXCEL,ERhythmJudge)\
		ENUM_FIELD(ERJ_eJudge_Good			,3,굳,nMech,nEXCEL,ERhythmJudge)\
		ENUM_FIELD(ERJ_eJudge_Perfect			,4,퍼팩트,nMech,nEXCEL,ERhythmJudge)\

	/* (상점에서 장비 선택에서 타자 일경우 나뉘어지는 섹션의 구분) */
	#define for_each_nEXCEL_EShopBatterSection_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ESBS_NULL			,1,없음,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_A			,2,섹션 A,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_B			,3,섹션 B,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_C			,4,섹션 C,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_D			,5,섹션 D,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_E			,6,섹션 E,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_F			,7,섹션 F,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_G			,8,섹션 G,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_H			,9,섹션 H,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_I			,10,섹션 I,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_J			,11,섹션 J,nMech,nEXCEL,EShopBatterSection)\

	/* (상점에서 소비 아이템 선택 시 나뉘어지는 섹션의 구분) */
	#define for_each_nEXCEL_EShopConsumeSection_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ESCS_NULL			,1,없음,nMech,nEXCEL,EShopConsumeSection)\
		ENUM_FIELD(ESCS_A			,2,섹션 A,nMech,nEXCEL,EShopConsumeSection)\
		ENUM_FIELD(ESCS_B			,3,섹션 B,nMech,nEXCEL,EShopConsumeSection)\
		ENUM_FIELD(ESCS_C			,4,섹션 C,nMech,nEXCEL,EShopConsumeSection)\
		ENUM_FIELD(ESCS_D			,5,섹션 D,nMech,nEXCEL,EShopConsumeSection)\
		ENUM_FIELD(ESCS_E			,6,섹션 E,nMech,nEXCEL,EShopConsumeSection)\

	/* 설명없음 */
	#define for_each_nEXCEL_EShopItemType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ESIT_Sys_Package			,1,패키지,nMech,nEXCEL,EShopItemType)\
		ENUM_FIELD(ESIT_Sys_ItemEquip			,2,장착아이템,nMech,nEXCEL,EShopItemType)\
		ENUM_FIELD(ESIT_Sys_ItemStuff			,3,재료아이템,nMech,nEXCEL,EShopItemType)\
		ENUM_FIELD(ESIT_Sys_ItemConsume			,4,소모아이템,nMech,nEXCEL,EShopItemType)\
		ENUM_FIELD(ESIT_Sys_PlayerSkillSticker			,5,변화구아이템,nMech,nEXCEL,EShopItemType)\

	/* (상점에서 장비 선택에서 투수 일경우 선택 시 나뉘어지는 섹션의 구분) */
	#define for_each_nEXCEL_EShopPitcherSection_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ESPS_NULL			,1,없음,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_A			,2,섹션 A,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_B			,3,섹션 B,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_C			,4,섹션 C,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_D			,5,섹션 D,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_E			,6,섹션 E,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_F			,7,섹션 F,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_G			,8,섹션 G,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_H			,9,섹션 H,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_I			,10,섹션 I,nMech,nEXCEL,EShopPitcherSection)\

	/* 설명없음 */
	#define for_each_nEXCEL_ETotalGameType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(TGT_Match			,1,매치,nMech,nEXCEL,ETotalGameType)\
		ENUM_FIELD(TGT_Single			,2,싱글,nMech,nEXCEL,ETotalGameType)\
		ENUM_FIELD(TGT_Friendly			,3,프랜들리,nMech,nEXCEL,ETotalGameType)\


// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum EBaseballObjectType // 설명없음
	{
		eBEGIN_EBaseballObjectType = 0,
		/* 유저 */
		eBOT_user = 1, // 유저
		/* 투수 */
		eBOT_pitcher = 2, // 투수
		/* 타자 */
		eBOT_better = 3, // 타자
		/* 팀 */
		eBOT_team = 4, // 팀
		eEND_EBaseballObjectType
	}; // EBaseballObjectType 



	enum EBatterAbility // 설명없음
	{
		eBEGIN_EBatterAbility = 0,
		/* 없음 */
		eBA_NULL = 1, // 없음
		/* 좌투수상대시 파워 증가. 소유시 BA_RIGHT스티커는 가질수없슴 */
		eBA_LEFT = 2, // 대좌투수
		/* 대우투수 상대시 파워 증가. 소유시 BA_LEFT스티커는 가질수없슴 */
		eBA_RIGHT = 3, // 대우투수
		/* 히트시 파워 증가 */
		eBA_HOMERUN = 4, // 홈런타자
		/* 광각타법 - 밀어쳤을때 파워 다운없음 */
		eBA_WIDE = 5, // 광각타법
		/* 풀히터 - 당겨쳤을때 파워 증가 */
		eBA_FULLHIT = 6, // 풀히터
		/* 로볼히터 - 타격판정시 하단/중단에서 파워 증가 */
		eBA_LOWHIT = 7, // 로볼히터
		/* 하이볼히터 - 중단# 상단에서 파워 증가 */
		eBA_HIGHHIT = 8, // 하이볼히터
		/* 연발 - 바로 이전타석에서 홈런시 파워 증가 */
		eBA_RUNFIRE = 9, // 연발
		eEND_EBatterAbility
	}; // EBatterAbility 



	enum EBatterForm // 설명없음
	{
		eBEGIN_EBatterForm = 0,
		/* 스쿼어 */
		eBF_SQUARE = 1, // 스퀘어
		/* 오픈 */
		eBF_OPEN = 2, // 오픈
		/* 크로즈드 */
		eBF_CLOSE = 3, // 크로즈드
		/* 없음 */
		eBF_NULL = 4, // 없음
		/* 공통 */
		eBF_COMMON = 5, // 공통
		eEND_EBatterForm
	}; // EBatterForm 



	enum EBatterHitType // 설명없음
	{
		eBEGIN_EBatterHitType = 0,
		/* 스탠드아웃 */
		eEBHT_STANDOUT = 1, // 스탠드아웃
		/* 스윙아웃 */
		eEBHT_SWINGOUT = 2, // 스윙아웃
		/* 파울아웃 */
		eEBHT_FOULOUT = 3, // 파울아웃
		/* 내야아웃 */
		eEBIT_INFIELDOUT = 4, // 내야아웃
		/* 좌익수아웃 */
		eEBIT_LEFTFIELDOUT = 5, // 좌익수아웃
		/* 중견수아웃 */
		eEBIT_CENTERFIELDOUT = 6, // 중견수아웃
		/* 우익수아웃 */
		eEBIT_RIGHTFIELDOUT = 7, // 우익수아웃
		/* 이 이상은 아웃상태를 나타내기위한 값 */
		eEBHT_NO_HIT = 8, // 치지못한상태
		/* 일루타 */
		eEBHT_ONEHIT = 9, // 일루타
		/* 이루타 */
		eEBHT_DOUBLEHIT = 10, // 이루타
		/* 삼루타 */
		eEBHT_TRIPLEHIT = 11, // 삼루타
		/* 홈런 */
		eEBHT_HOMERUN = 12, // 홈런
		eEND_EBatterHitType
	}; // EBatterHitType 



	enum EBreakingBallPitch // 설명없음
	{
		eBEGIN_EBreakingBallPitch = 0,
		/* 직구 */
		eEBBP_STRAIGHT = 1, // 직구
		/* 횡변화 */
		eEBBP_WIDE = 2, // 횡변화
		/* 종변화 */
		eEBBP_HEIGHT = 3, // 종변화
		/* 종횡변화 */
		eEBBP_HEIGHTWIDE = 4, // 종횡변화
		eEND_EBreakingBallPitch
	}; // EBreakingBallPitch 



	enum EBreakingBallRotation // 설명없음
	{
		eBEGIN_EBreakingBallRotation = 0,
		/* 정회전 */
		eEBBR_REGULAR = 1, // 정회전
		/* 역회전 */
		eEBBR_REVERSE = 2, // 역회전
		/* 무회전 */
		eEBBR_NOTHING = 3, // 무회전
		eEND_EBreakingBallRotation
	}; // EBreakingBallRotation 



	enum ECategoryString // 설명없음
	{
		eBEGIN_ECategoryString = 0,
		/* 아이템관련 스트링. Text1=이름 text2=설명 단 공용아이템일때는 text2=타자용설명 text3=투수용설명 */
		eECS_ITEM = 1, // 아이템
		/* 화면 GUI용 스트링 */
		eECS_GUI = 2, // GUI
		/* 스킬용 스트링, text1=이름 text2=설명 */
		eECS_SKILL = 3, // 스킬용
		/* 그외 스트링 */
		eECS_ETC = 4, // 기타
		eEND_ECategoryString
	}; // ECategoryString 



	enum EConsumeItemEffect // 설명없음
	{
		eBEGIN_EConsumeItemEffect = 0,
		/* 게임시 보상으로 받는 머니의 지급 배수 상승(1000분율) 예를 들어consume_item_effect_value값이 500이면 50%올려줌 */
		eCIE_MONEYUP = 1, // 게임머니배수상승아이템
		/* 게임시 보상으로 받는 경험치의 지급 배수 상승 */
		eCIE_EXPUP = 2, // 경험치배수상승아이템
		/* 게임시 보상으로 받는 아이템의 지급 확률 상승 */
		eCIE_ITEMDROPUP = 3, // 아이템드롭확률상승아이템
		/* 게임시 기존의 가지고 있는 스텟을 일시적으로 상승 */
		eCIE_STATUPWHILE = 4, // 능력치일시상승아이템
		/* 게임시 기존의 가지고 있는 스텟을 영구적으로 상승 */
		eCIE_STATUPFOREVER = 5, // 능력치영구상승아이템
		/* 메인아이템 강화시 확률 증가 */
		eCIE_UPGRADELUCKYUP = 6, // 강화확률증가아이템
		/* 메인아이템 강화시 시간 감소 */
		eCIE_UPGRADETIMEDOWN = 7, // 강화시간감소아이템
		/* 강화 완료한 메인아이템의 강화 취소 */
		eCIE_UPGRADECANCEL = 8, // 강화취소아이템
		/* 아이템의 사용가능 레벨을 하향 */
		eCIE_ITEMUSEDOWN = 9, // 아이템사용가능레벨하향
		/* 기타. 해당아이템별로 기능정의 */
		eCIE_ETC = 10, // ETC
		eEND_EConsumeItemEffect
	}; // EConsumeItemEffect 



	enum EEventType // 설명없음
	{
		eBEGIN_EEventType = 0,
		/* 머니 */
		eET_MONEY = 1, // 머니
		/* 아이템 */
		eET_ITEM = 2, // 아이템
		/* 머니_아이템 */
		eET_MONEY_ITEM = 3, // 머니_아이템
		eEND_EEventType
	}; // EEventType 



	enum EGestureType // 설명없음
	{
		eBEGIN_EGestureType = 0,
		/* 직선 */
		eEGTT_STRAGHT = 1, // 직선
		/* 수직선 */
		eEGTT_VERTICAL = 2, // 수직선
		/* 곡선 */
		eEGTT_CURVE = 3, // 곡선
		/* 계단형수직선 */
		eEGTT_STAIR_VERTICAL = 4, // 계단형수직선
		/* 에스형곡선 */
		eEGTT_S_CURVE = 5, // 에스형곡선
		/* 변화구에 제스처를 설정하지 않은 경우 */
		eEGTT_NULL = 6, // 없음
		eEND_EGestureType
	}; // EGestureType 



	enum EGiftCategory // 설명없음
	{
		eBEGIN_EGiftCategory = 0,
		/* 싱글게임승 */
		eEGC_SINGLEGAMEWIN = 1, // 싱글게임승
		/* 싱글게임패 */
		eEGC_SINGLEGAMELOSE = 2, // 싱글게임패
		/* 대전게임승 */
		eEGC_MATCHGAMEWIN = 3, // 대전게임승
		/* 대전게임패 */
		eEGC_MATCHGAMELOSE = 4, // 대전게임패
		/* 친구게임승 */
		eEGC_FRIENDGAMEWIN = 5, // 친구게임승
		/* 친구게임패 */
		eEGC_FRIENDGAMELOSE = 6, // 친구게임패
		/* 트레이닝승 */
		eEGC_TRAININGWIN = 7, // 트레이닝승
		/* 트레이닝패 */
		eEGC_TRAININGLOSE = 8, // 트레이닝패
		eEND_EGiftCategory
	}; // EGiftCategory 



	enum EGiftType // 설명없음
	{
		eBEGIN_EGiftType = 0,
		/* 없음 */
		eEGT_NULL = 1, // 없음
		/* 게임머니 */
		eEGT_GAMEMONEY = 2, // 게임머니
		/* 스킬스티커 */
		eEGT_PLAYERSKILLSTICKER = 3, // 스킬스티커
		/* 플레이어카드 */
		eEGT_PLAYERCARD = 4, // 플레이어카드
		/* 게임캐쉬 */
		eEGT_GAMECASH = 5, // 게임 캐쉬
		eEND_EGiftType
	}; // EGiftType 



	enum EGradeAllitemType // 설명없음
	{
		eBEGIN_EGradeAllitemType = 0,
		/* 없음 */
		eEGAT_NULL = 1, // 없음
		/* S급 메인아이템 모두 */
		eEGAT_SMAINITEMALL = 2, // S급 메인아이템 모두
		/* A급 메인아이템 모두 */
		eEGAT_AMAINITEMALL = 3, // A급 메인아이템 모두
		/* B급 메인아이템 모두 */
		eEGAT_BMAINITEMALL = 4, // B급 메인아이템 모두
		/* C급 메인아이템 모두 */
		eEGAT_CMAINITEMALL = 5, // C급 메인아이템 모두
		/* D급 메인아이템 모두 */
		eEGAT_DMAINITEMALL = 6, // D급 메인아이템 모두
		/* E급 메인아이템 모두 */
		eEGAT_EMAINITEMALL = 7, // E급 메인아이템 모두
		/* S급 서브아이템 모두 */
		eEGAT_SSUBITEMALL = 8, // S급 서브아이템 모두
		/* A급 서브아이템 모두 */
		eEGAT_ASUBITEMALL = 9, // A급 서브아이템 모두
		/* B급 서브아이템 모두 */
		eEGAT_BSUBITEMALL = 10, // B급 서브아이템 모두
		/* C급 서브아이템 모두 */
		eEGAT_CSUBITEMALL = 11, // C급 서브아이템 모두
		/* D급 서브아이템 모두 */
		eEGAT_DSUBITEMALL = 12, // D급 서브아이템 모두
		/* E급 서브아이템 모두 */
		eEGAT_ESUBITEMALL = 13, // E급 서브아이템 모두
		/* S급 소비아이템 모두 */
		eEGAT_SCONSUMEITEMALL = 14, // S급 소비아이템 모두
		/* A급 소비아이템 모두 */
		eEGAT_ACONSUMEITEMALL = 15, // A급 소비아이템 모두
		/* B급 소비아이템 모두 */
		eEGAT_BCONSUMEITEMALL = 16, // B급 소비아이템 모두
		/* C급 소비아이템 모두 */
		eEGAT_CCONSUMEITEMALL = 17, // C급 소비아이템 모두
		/* D급 소비아이템 모두 */
		eEGAT_DCONSUMEITEMALL = 18, // D급 소비아이템 모두
		/* E급 소비아이템 모두 */
		eEGAT_ECONSUMEITEMALL = 19, // E급 소비아이템 모두
		eEND_EGradeAllitemType
	}; // EGradeAllitemType 



	enum EHitTimmingType // 설명없음
	{
		eBEGIN_EHitTimmingType = 0,
		/* 클라이언트용 (값은 0_서버에서는 처리하지 않음) */
		eEHTT_eHitTime_None = 0, // 클라이언트용
		/* 매우 빠름 */
		eEHTT_eHitTime_VeryFast = 1, // 매우 빠름
		/* 빠름 */
		eEHTT_eHitTime_Fast = 2, // 빠름
		/* 적정 빠름 */
		eEHTT_eHitTime_GoodFast = 3, // 적정 빠름
		/* 퍼펙트 빠름 */
		eEHTT_eHitTime_Perfect = 4, // 퍼펙트 빠름
		/* 적정 느림 */
		eEHTT_eHitTime_GoodSlow = 5, // 적정 느림
		/* 느림 */
		eEHTT_eHitTime_Slow = 6, // 느림
		/* 매우 느림 */
		eEHTT_eHitTime_VerySlow = 7, // 매우 느림
		eEND_EHitTimmingType
	}; // EHitTimmingType 



	enum EHitType // 설명없음
	{
		eBEGIN_EHitType = 0,
		/* 클라이언트용 (값은 0_서버에서는 처리하지 않음) */
		eEHT_eNS_NONE = 0, // 클라이언트용
		/* 일반 히트 */
		eEHT_eNS_BALLHIT = 1, // 일반 히트
		/* 강진_스트롱 히트 */
		eEHT_eNS_BALLHITSTRONG = 2, // 강진_스트롱 히트
		/* 헛스윙 */
		eEHT_eNS_SWING = 3, // 헛스윙
		/* 대기 상태 */
		eEHT_eNS_NOTHING = 4, // 대기 상태
		eEND_EHitType
	}; // EHitType 



	enum EItemAbilityType // 설명없음
	{
		eBEGIN_EItemAbilityType = 0,
		/* 파워 */
		eIAT_POWER = 1, // 파워
		/* 정확 */
		eIAT_ACCURACY = 2, // 정확
		/* 제구 */
		eIAT_FOCUS = 3, // 제구
		/* 구속 */
		eIAT_SPEED = 4, // 구속
		/* 변화구 */
		eIAT_BREAKINGBALL = 5, // 변화구
		/* 모든스텟 */
		eIAT_ALLABILITY = 6, // 모든스텟
		/* 없음 */
		eIAT_NULL = 7, // 없음
		eEND_EItemAbilityType
	}; // EItemAbilityType 



	enum EItemBuyType // 설명없음
	{
		eBEGIN_EItemBuyType = 0,
		/* 캐쉬 구매 아이템 */
		eIBT_BUY_CASH = 1, // 캐쉬 구매 아이템
		/* 포인트 구매 아이템 */
		eIBT_BUY_POINT = 2, // 포인트 구매 아이템
		/* 캐쉬OR포인트구매아이템인데 귀속된상태 */
		eIBT_BUY_USED = 3, // 캐쉬귀속아이템
		/* 이벤트지급아이템 */
		eIBT_EVENT = 4, // 이벤트 지급아이템
		/* 트레이닝 or 경기보상 지급아이템 */
		eIBT_REWARD = 5, // 경기보상으로받음
		eEND_EItemBuyType
	}; // EItemBuyType 



	enum EItemCategory // 설명없음
	{
		eBEGIN_EItemCategory = 0,
		/* 착용장비 */
		eIC_EQUIP = 1, // 착용장비
		/* 소모아이템 */
		eIC_CONSUME = 2, // 소모아이템
		/* 재료아이템 */
		eIC_STUFF = 3, // 재료아이템
		/* 없음 */
		eIC_NULL = 4, // 없음
		eEND_EItemCategory
	}; // EItemCategory 



	enum EItemCategoryEquipment // 설명없음
	{
		eBEGIN_EItemCategoryEquipment = 0,
		/* 상의 */
		eICE_SHIRT = 1, // 상의
		/* 하의 */
		eICE_PANT = 2, // 하의
		/* 모자 메인아이템# */
		eICE_CAP = 3, // 모자
		/* 타자 신발 메인아이템# */
		eICE_SHOES_B = 4, // 타자 신발
		/* 투수 신발 메인아이템# */
		eICE_SHOES_P = 5, // 투수 신발
		/* 투수글러브 메인아이템# */
		eICE_GLOVE = 6, // 투수글러브
		/* 언더셔츠 */
		eICE_U_SHIRT = 7, // 언더셔츠
		/* 양말 */
		eICE_SOCKS = 8, // 양말
		/* 팔_보호대 */
		eICE_ARM_GUARDS = 9, // 팔_보호대
		/* 다리_보호대 */
		eICE_LEG_GUARDS = 10, // 다리_보호대
		/* 배트 메인아이템 */
		eICE_BAT = 11, // 배트
		/* 볼 메인아이템# */
		eICE_BALL = 12, // 볼
		/* 헬멧 메인아이템# */
		eICE_HELMET = 13, // 헬멧
		/* 타자용 장갑 메인아이템# */
		eICE_GLOBE = 14, // 타자장갑
		/* 손목 아대 */
		eICE_WRISTBAND = 15, // 리스트 밴드
		/* 목걸이 */
		eICE_NECKLACE = 16, // 목걸이
		/* 반지 */
		eICE_RING = 17, // 반지
		/* 귀걸이 */
		eICE_EARRING = 18, // 귀걸이
		/* 문신 */
		eICE_TATOO = 19, // 문신
		/* 선글라스 */
		eICE_SUNGLASS = 20, // 선글라스
		/* 눈 밑 패치 */
		eICE_EYEPATCH = 21, // 아이패치
		/* 수염 */
		eICE_BEARD = 22, // 수염
		/* 남성헤어스타일 */
		eICE_HAIR_M = 23, // 남성헤어스타일
		/* 여성헤어스타일 */
		eICE_HAIR_W = 24, // 여성헤어스타일
		/* 헤어칼라 */
		eICE_HAIR_COLOR = 25, // 헤어칼라
		/* 패치 */
		eICE_PATCH = 26, // 패치
		/* 마스크 */
		eICE_MASK = 27, // 마스크
		/* 등번호 아이템 */
		eICE_BACKNUMBER = 28, // 등번호 아이템
		/* 마킹 아이템 */
		eICE_MAKING = 29, // 마킹 아이템
		/* 얼굴 */
		eICE_FACE = 30, // 얼굴
		/* 팔 */
		eICE_ARM = 31, // 팔
		/* 다리(여자) */
		eICE_LEG = 32, // 다리(여자)
		/* 왼손 */
		eICE_LEFTHAND = 33, // 왼손
		/* 오른손 */
		eICE_RIGHTHAND = 34, // 오른손
		eEND_EItemCategoryEquipment
	}; // EItemCategoryEquipment 



	enum EItemGradeType // 설명없음
	{
		eBEGIN_EItemGradeType = 0,
		/* E - EE 로 업글가능 */
		eIGT_E = 1, // E등급
		/* D - DE #  DD로 업글가능 */
		eIGT_D = 2, // D등급
		/* C - CE # CD# CC로 업글가능 */
		eIGT_C = 3, // C등급
		/* B- BE# BD# BC# BB로 업글가능 */
		eIGT_B = 4, // B등급
		/* A- AE# AD# AC# AB# AA로 업글가능 */
		eIGT_A = 5, // A등급
		/* S-SE# SD# SC# SB# SA# SS로 업글가능 */
		eIGT_S = 6, // S등급
		/* 등급없음.  데코레이션 아이템… */
		eIGT_NULL = 7, // 무등급
		eEND_EItemGradeType
	}; // EItemGradeType 



	enum EItemPriceType // 설명없음
	{
		eBEGIN_EItemPriceType = 0,
		/* 캐쉬 로만 살수있는 아이템 */
		eIPT_CASH = 1, // 캐쉬
		/* 캐쉬 또는 포인트 로 살수 있는 아이템 */
		eIPT_CASH_POINT = 2, // 캐쉬_포인트
		/* 캐쉬 또는 포인트# 게임머니로 살수 있는 아이템 */
		eIPT_MONEY = 3, // 포인트
		eEND_EItemPriceType
	}; // EItemPriceType 



	enum EItemReuseType // 설명없음
	{
		eBEGIN_EItemReuseType = 0,
		/* 가능 */
		eIUT_NORMAL = 1, // 가능
		/* 기간내 횟수 소진 다 했으면 재 사용 */
		eIUT_INSTANTLY = 2, // 기간제
		/* 불가 */
		eIUT_FIXED = 3, // 불가
		eEND_EItemReuseType
	}; // EItemReuseType 



	enum EItemSellStatus // 설명없음
	{
		eBEGIN_EItemSellStatus = 0,
		/* 판매중지( 판매하다가 정책상 폐기된 아이템) */
		eISS_SELL_STOP = 1, // 판매중지
		/* 판매중 */
		eISS_SELL = 2, // 판매중
		/* 판매예정 */
		eISS_SELL_PLAN = 3, // 판매예정
		eEND_EItemSellStatus
	}; // EItemSellStatus 



	enum EItemSexType // 설명없음
	{
		eBEGIN_EItemSexType = 0,
		eIST_MAN_ONLY = 1, // 남
		eIST_WOMAN_ONLY = 2, // 여
		eIST_COMMON = 3, // 공용
		eEND_EItemSexType
	}; // EItemSexType 



	enum EItemState // (상점에서 소비 아이템 선택 시 나뉘어지는 섹션의 구분)
	{
		eBEGIN_EItemState = 0,
		/* 일반상태 */
		eIS_NORMAL = 1, // 일반상태
		/* 삭제된상태 */
		eIS_DELETE = 2, // 삭제된상태
		/* 사용불가능. */
		eIS_ADMIN_BLOCKED = 3, // 사용불가능.
		/* 되팔기되어 삭제됨 */
		eIS_DELETE_REFUND = 4, // 되팔기되어 삭제됨
		eEND_EItemState
	}; // EItemState 



	enum EItemSubGradeType // 설명없음
	{
		eBEGIN_EItemSubGradeType = 0,
		/* EE등급 */
		eISGT_EE = 1, // EE등급
		/* DE등급 */
		eISGT_DE = 2, // DE등급
		/* DD등급 */
		eISGT_DD = 3, // DD등급
		/* CE등급 */
		eISGT_CE = 4, // CE등급
		/* CD등급 */
		eISGT_CD = 5, // CD등급
		/* CC등급 */
		eISGT_CC = 6, // CC등급
		/* BE등급 */
		eISGT_BE = 7, // BE등급
		/* BD등급 */
		eISGT_BD = 8, // BD등급
		/* BC등급 */
		eISGT_BC = 9, // BC등급
		/* BB등급 */
		eISGT_BB = 10, // BB등급
		/* AE등급 */
		eISGT_AE = 11, // AE등급
		/* AD등급 */
		eISGT_AD = 12, // AD등급
		/* AC등급 */
		eISGT_AC = 13, // AC등급
		/* AB등급 */
		eISGT_AB = 14, // AB등급
		/* AA등급 */
		eISGT_AA = 15, // AA등급
		/* SE등급 */
		eISGT_SE = 16, // SE등급
		/* SD등급 */
		eISGT_SD = 17, // SD등급
		/* SC등급 */
		eISGT_SC = 18, // SC등급
		/* SB등급 */
		eISGT_SB = 19, // SB등급
		/* SA등급 */
		eISGT_SA = 20, // SA등급
		/* SS등급 */
		eISGT_SS = 21, // SS등급
		/* 등급없음(NULL일 경우 해당 등급의 무급) */
		eISGT_NULL = 22, // 등급없음
		eEND_EItemSubGradeType
	}; // EItemSubGradeType 



	enum EItemUpgradeResult // 설명없음
	{
		eBEGIN_EItemUpgradeResult = 0,
		/* 헬멧 */
		eIUR_HELMET = 1, // 헬멧
		/* 모자 */
		eIUR_CAP = 2, // 모자
		/* 배트 */
		eIUR_BET = 3, // 배트
		/* 볼 */
		eIUR_BALL = 4, // 볼
		/* 타자장갑 */
		eIUR_GLOBE = 5, // 타자장갑
		/* 글러브 */
		eIUR_GLOVE = 6, // 글러브
		/* 신발 */
		eIUR_SHOES = 7, // 신발
		eEND_EItemUpgradeResult
	}; // EItemUpgradeResult 



	enum ELogType // 설명없음
	{
		eBEGIN_ELogType = 0,
		/* 로그1 */
		eSCT_KINGROOKIE = 1, // 로그1
		/* 로그2 */
		eSCT_ROOKIE = 2, // 로그2
		/* 로그3 */
		eSCT_AMA1 = 3, // 로그3
		/* 로그4 */
		eSCT_AMA2 = 4, // 로그4
		/* 로그5 */
		eSCT_PRO = 5, // 로그5
		eEND_ELogType
	}; // ELogType 



	enum ENoticeType // 설명없음
	{
		eBEGIN_ENoticeType = 0,
		/* 전광판 */
		eNT_LED = 1, // 전광판
		/* 임시점검 */
		eNT_CHECK = 2, // 임시점검
		/* 공지사항 */
		eNT_NOTICE = 3, // 공지사항
		eEND_ENoticeType
	}; // ENoticeType 



	enum ENpcSituationString // 설명없음
	{
		eBEGIN_ENpcSituationString = 0,
		/* 대기중 일시 출력 */
		eENSS_STANDING_BY = 1, // 대기중
		/* 선택시 출력 */
		eENSS_SELECTION = 2, // 선택 시
		/* 업그레이드 중 일시 출력 */
		eENSS_UPGRADE_WORKING = 3, // 업그레이드 중
		/* 트레이닝 중 일시 출력 */
		eENSS_TRANING_WORKING = 4, // 트레이닝 중
		/* 완료 시에 출력 */
		eENSS_COMPLETE = 5, // 완료
		/* 업그레이드 결과  출력 */
		eENSS_UPGRADE_RESULT = 6, // 업그레이드 결과
		/* 트레이닝 결과  출력 */
		eENSS_TRANING_RESULT = 7, // 트레이닝 결과
		eEND_ENpcSituationString
	}; // ENpcSituationString 



	enum ENpcString // 설명없음
	{
		eBEGIN_ENpcString = 0,
		/* 장인 */
		eENS_MAESTRO = 1, // 장인
		/* 투수코치 */
		eENS_COACH = 2, // 투수코치
		eEND_ENpcString
	}; // ENpcString 



	enum EPitcherAbility // 설명없음
	{
		eBEGIN_EPitcherAbility = 0,
		/* 없음 */
		ePA_NULL = 1, // 없음
		/* 좌타자상대시 능력치증가. PA_RIGHT속성의 스킬 스티커는 가질수없슴 */
		ePA_LEFT = 2, // 대좌타자
		/* 우타자상대시 능력치증가. PA_LEFT속성의 스킬 스티커는 가질수 없슴 */
		ePA_RIGHT = 3, // 대우타자
		/* 구속 증가 */
		ePA_FASTBALL = 4, // 속구파
		/* 변화구 각 증가 */
		ePA_FULLSKILL = 5, // 기교파
		/* 바로 이전 타석에서 스트라익 잡으면  다음 공 제구 증가 */
		ePA_RUNFIRE = 6, // 연투
		/* 낮은 투구시 제구 다운 없음 */
		ePA_SWORDCON = 7, // 칼제구
		/* 2개의 스트라익 잡으면 다음 공 제구 증가 */
		ePA_DOCK = 8, // 닥터K
		/* 타자의 몸쪽으로 공을 던질시 제구 증가 */
		ePA_INFIGHT = 9, // 인파이터
		/* 타자의 바깥쪽으로 공을 던질시 제구 증가 */
		ePA_OUTFIGHT = 10, // 아웃파이터
		eEND_EPitcherAbility
	}; // EPitcherAbility 



	enum EPitcherForm // 설명없음
	{
		eBEGIN_EPitcherForm = 0,
		/* 오버 */
		ePF_OVER = 1, // 오버
		/* 쓰리쿼터 */
		ePF_THREEQUARTER = 2, // 쓰리쿼터
		/* 사이드암 */
		ePF_SIDEARM = 3, // 사이드암
		/* 언더 */
		ePF_UNDER = 4, // 언더
		/* 없음 */
		ePF_NULL = 5, // 없음
		/* 공통 */
		ePF_COMMON = 6, // 공통
		eEND_EPitcherForm
	}; // EPitcherForm 



	enum EPlayer_Onoffline // 설명없음
	{
		eBEGIN_EPlayer_Onoffline = 0,
		/* 온라인플레이어 */
		eEPO_ONPLAYER = 1, // 온라인플레이어
		/* 오프라인플레이어 */
		eEPO_OFFPLAYER = 2, // 오프라인플레이어
		eEND_EPlayer_Onoffline
	}; // EPlayer_Onoffline 



	enum EPlayerBodyType // 설명없음
	{
		eBEGIN_EPlayerBodyType = 0,
		/* 스몰 */
		eEPBT_SMALL = 1, // 스몰
		/* 미디엄 */
		eEPBT_MIDIUM = 2, // 미디엄
		/* 라지 */
		eEPBT_LARGE = 3, // 라지
		/* 여성 */
		eEPBT_WOMAN = 4, // 여성
		eEND_EPlayerBodyType
	}; // EPlayerBodyType 



	enum EPlayerBreakingBall // 설명없음
	{
		eBEGIN_EPlayerBreakingBall = 0,
		/* 없음 */
		ePBB_NULL = 1, // 없음
		/* 포심 */
		ePBB_FOURSEAM = 2, // 포심
		/* 투심 */
		ePBB_TWOSEAM = 3, // 투심
		/* 라이징패스트볼 */
		ePBB_RISINGFAST = 4, // 라이징패스트볼
		/* 업슛 */
		ePBB_UPSHOUT = 5, // 업슛
		/* 슬라이더 */
		ePBB_SLIDER = 6, // 슬라이더
		/* H슬라이더 */
		ePBB_HSLIDER = 7, // H슬라이더
		/* 컷패스트볼 */
		ePBB_CUTFAST = 8, // 컷패스트볼
		/* V슬라이더 */
		ePBB_VSLIDER = 9, // V슬라이더
		/* 슬러브 */
		ePBB_SLUB = 10, // 슬러브
		/* 체인지업 */
		ePBB_CHANGEUP = 11, // 체인지업
		/* 서클체인지업 */
		ePBB_CIRCLECHANGEUP = 12, // 서클체인지업
		/* 너클 */
		ePBB_KNUCKLE = 13, // 너클
		/* 커브 */
		ePBB_CURVE = 14, // 커브
		/* 슬로우커브 */
		ePBB_SLOWCURVE = 15, // 슬로우커브
		/* 너클커브 */
		ePBB_KNUCKLECURVE = 16, // 너클커브
		/* 드랍커브 */
		ePBB_DROPCURVE = 17, // 드랍커브
		/* 파워커브 */
		ePBB_POWERCURVE = 18, // 파워커브
		/* 슈트 */
		ePBB_SHOUT = 19, // 슈트
		/* H슈트 */
		ePBB_HSHOUT = 20, // H슈트
		/* 포크 */
		ePBB_FORK = 21, // 포크
		/* 팜 */
		ePBB_PALM = 22, // 팜
		/* SFF */
		ePBB_SFF = 23, // SFF
		/* 싱커#  스크류 */
		ePBB_SINKER = 24, // 싱커_ 스크류
		/* H싱커 */
		ePBB_HSINKER = 25, // H싱커
		eEND_EPlayerBreakingBall
	}; // EPlayerBreakingBall 



	enum EPlayerGradeType // 설명없음
	{
		eBEGIN_EPlayerGradeType = 0,
		/* E등급 선수 */
		ePGT_E = 1, // E등급
		/* D등급 선수 */
		ePGT_D = 2, // D등급
		/* C등급 선수 */
		ePGT_C = 3, // C등급
		/* B등급 선수 */
		ePGT_B = 4, // B등급
		/* A등급 선수 */
		ePGT_A = 5, // A등급
		/* S등급 선수 */
		ePGT_S = 6, // S등급
		eEND_EPlayerGradeType
	}; // EPlayerGradeType 



	enum EPlayerNationType // 설명없음
	{
		eBEGIN_EPlayerNationType = 0,
		/* 한국 */
		ePNT_KOREA = 1, // 한국
		/* 미국 */
		ePNT_USA = 2, // 미국
		/* 일본 */
		ePNT_JAPAN = 3, // 일본
		/* 중국 */
		ePNT_CHINA = 4, // 중국
		/* 캐나다 */
		ePNT_CANADA = 5, // 캐나다
		/* 이탈리아 */
		ePNT_ITALY = 6, // 이탈리아
		/* 대만 */
		ePNT_TAIWAN = 7, // 대만
		/* 호주 */
		ePNT_AUSTRALIA = 8, // 호주
		/* 네덜란드 */
		ePNT_NETHERLANDS = 9, // 네덜란드
		/* 쿠바 */
		ePNT_CUBA = 10, // 쿠바
		/* 트리니다드토바고 */
		ePNT_TRINIDADANDTOBAGO = 11, // 트리니다드토바고
		/* 도미니카공화국 */
		ePNT_DOMINICANREPUBLIC = 12, // 도미니카공화국
		/* 파나마 */
		ePNT_PANAMA = 13, // 파나마
		/* 푸에르토리코 */
		ePNT_PUERTORICO = 14, // 푸에르토리코
		/* 남아프리카공화국 */
		ePNT_REPUBLICOFSOUTHAFRICA = 15, // 남아프리카공화국
		/* 베네수엘라 */
		ePNT_VENEZUELA = 16, // 베네수엘라
		/* 영국 */
		ePNT_UNITEDKINGDOM = 17, // 영국
		/* 스페인 */
		ePNT_SPAIN = 18, // 스페인
		/* 프랑스 */
		ePNT_FRANCE = 19, // 프랑스
		/* 독일 */
		ePNT_GERMANY = 20, // 독일
		eEND_EPlayerNationType
	}; // EPlayerNationType 



	enum EPlayerType // (포수와 심판은 클라이언트 스킴용)
	{
		eBEGIN_EPlayerType = 0,
		/* 타자 */
		ePT_BATTER = 1, // 타자
		/* 투수 */
		ePT_PITCHER = 2, // 투수
		/* 타자투수구분없음 */
		ePT_COMMON = 3, // 공용
		/* 포수 */
		ePT_CATCHER = 4, // 포수
		/* 심판 */
		ePT_UMPIRE = 5, // 심판
		eEND_EPlayerType
	}; // EPlayerType 



	enum EQuestConditionType // 설명없음
	{
		eBEGIN_EQuestConditionType = 0,
		/* 없음 */
		eQCT_NULL = 1, // 없음
		/* 전체장비착용조건이 condition1에 있는 값의 조건(EItemGradeType)에 해당하면 보상을 준다 */
		eQCT_EQUIPGRADETYPE = 12, // 전체장비착용조건
		/* 캐쉬템구매조건 */
		eQCT_CASHCOUNT = 13, // 캐쉬템구매조건
		/* 게임머니누적조건 */
		eQCT_GAMEMONEYCOUNT = 14, // 게임머니누적조건
		/* 캐릭터모든능력치달성조건. 팀소속의 투수타자가 동시에 해당 능력치 도달시 준다. pitcher_breakingball는 조건에서 제외 */
		eQCT_PLAYERALLSTATCOUNT = 15, // 캐릭터모든능력치달성조건
		/* 정해진 게임내변수의 조건. 게임변수의 종류참고하시오 */
		eQCT_GAME_VALIABLE = 16, // 게임변수
		/* 튜토리얼 or 일일퀘스트등 완료조건이 EQuestType에의해 결정됨.완료통보 */
		eQCT_MANUAL_FINISH = 17, // 임의완료
		eEND_EQuestConditionType
	}; // EQuestConditionType 



	enum EQuestType // 설명없음
	{
		eBEGIN_EQuestType = 0,
		/* MATCH 퀘스트 */
		eEQT_MATCH = 1, // MATCH 퀘스트
		/* SINGLE 퀘스트 */
		eEQT_SINGLE = 2, // SINGLE 퀘스트
		/* FRIENDLY 퀘스트 */
		eEQT_FRIENDLY = 3, // FRIENDLY 퀘스트
		/* ITEM_ETC 퀘스트 */
		eEQT_ITEMETC = 4, // ITEM_ETC 퀘스트
		/* 인게임 튜토리얼. 완료조건을 클라이언트가 체크후 보낸다.(x2ug_quest_end) */
		eEQT_INGAMETUTORIAL = 5, // TUTORIAL
		/* DAILIY 퀘스트. (주의 condition_value1의값은 0~100까지의 확률분포를 의미한다.) */
		eEQT_DAILY = 6, // DAILY 퀘스트
		eEND_EQuestType
	}; // EQuestType 



	enum ERhythmJudge // 설명없음
	{
		eBEGIN_ERhythmJudge = 0,
		/* 클라이언트용 (값은 0_서버에서는 처리하지 않음) */
		eERJ_eJudge_None = 0, // 클라이언트용
		/* 배드 */
		eERJ_eJudge_Bad = 1, // 배드
		/* 노멀 */
		eERJ_eJudge_Normal = 2, // 노멀
		/* 굳 */
		eERJ_eJudge_Good = 3, // 굳
		/* 퍼팩트 */
		eERJ_eJudge_Perfect = 4, // 퍼팩트
		eEND_ERhythmJudge
	}; // ERhythmJudge 



	enum EShopBatterSection // (상점에서 장비 선택에서 타자 일경우 나뉘어지는 섹션의 구분)
	{
		eBEGIN_EShopBatterSection = 0,
		/* 없음 */
		eESBS_NULL = 1, // 없음
		/* 샵의 섹션 A(타자=헬멧) */
		eESBS_A = 2, // 섹션 A
		/* 샵의 섹션 B(타자=배트) */
		eESBS_B = 3, // 섹션 B
		/* 샵의 섹션 C(타자=장갑) */
		eESBS_C = 4, // 섹션 C
		/* 샵의 섹션 D(타자=신발) */
		eESBS_D = 5, // 섹션 D
		/* 샵의 섹션 E(타자=상의#  하의) */
		eESBS_E = 6, // 섹션 E
		/* 샵의 섹션 F(타자=양말#  리스트밴드) */
		eESBS_F = 7, // 섹션 F
		/* 샵의 섹션 G(타자=팔보호대#  다리보호대) */
		eESBS_G = 8, // 섹션 G
		/* 샵의 섹션 H(타자=목걸이# 반지#  귀걸이) */
		eESBS_H = 9, // 섹션 H
		/* 샵의 섹션 I(타자=(문신#  선글라스#  아이패치) */
		eESBS_I = 10, // 섹션 I
		/* 샵의 섹션 J(타자=(수염#  헤어#  패치#  마스크#  등번호#  마킹#  헤어컬러) */
		eESBS_J = 11, // 섹션 J
		eEND_EShopBatterSection
	}; // EShopBatterSection 



	enum EShopConsumeSection // (상점에서 소비 아이템 선택 시 나뉘어지는 섹션의 구분)
	{
		eBEGIN_EShopConsumeSection = 0,
		/* 없음 */
		eESCS_NULL = 1, // 없음
		/* 샵의 섹션 A(소비=버프 아이템) */
		eESCS_A = 2, // 섹션 A
		/* 샵의 섹션 B(소비=스텟 영구상승 아이템) */
		eESCS_B = 3, // 섹션 B
		/* 샵의 섹션 C(소비=업그레이드 관련 아이템) */
		eESCS_C = 4, // 섹션 C
		/* 샵의 섹션 D(소비=아이템 레벨 하향#  강화 취소 아이템) */
		eESCS_D = 5, // 섹션 D
		/* 샵의 섹션 E(소비=패키지 아이템) */
		eESCS_E = 6, // 섹션 E
		eEND_EShopConsumeSection
	}; // EShopConsumeSection 



	enum EShopItemType // 설명없음
	{
		eBEGIN_EShopItemType = 0,
		/* 패키지 */
		eESIT_Sys_Package = 1, // 패키지
		/* 장착아이템 */
		eESIT_Sys_ItemEquip = 2, // 장착아이템
		/* 재료아이템 */
		eESIT_Sys_ItemStuff = 3, // 재료아이템
		/* 소모아이템 */
		eESIT_Sys_ItemConsume = 4, // 소모아이템
		/* 변화구아이템(변화구 구매 시 변화구에 제한되어있는 레벨 무시하고 착용 가능#  변화구 업그레이드--)다음 변화구 언락을 위한(--는 그대로 적용) */
		eESIT_Sys_PlayerSkillSticker = 5, // 변화구아이템
		eEND_EShopItemType
	}; // EShopItemType 



	enum EShopPitcherSection // (상점에서 장비 선택에서 투수 일경우 선택 시 나뉘어지는 섹션의 구분)
	{
		eBEGIN_EShopPitcherSection = 0,
		/* 없음 */
		eESPS_NULL = 1, // 없음
		/* 샵의 섹션 A(투수=모자) */
		eESPS_A = 2, // 섹션 A
		/* 샵의 섹션 B(투수=볼) */
		eESPS_B = 3, // 섹션 B
		/* 샵의 섹션 C(투수=글러브) */
		eESPS_C = 4, // 섹션 C
		/* 샵의 섹션 D(투수=신발) */
		eESPS_D = 5, // 섹션 D
		/* 샵의 섹션 E(투수=상의#  하의) */
		eESPS_E = 6, // 섹션 E
		/* 샵의 섹션 E(투수=양말#  리스트밴드) */
		eESPS_F = 7, // 섹션 F
		/* 샵의 섹션 F (투수=목걸이# 반지#  귀걸이) */
		eESPS_G = 8, // 섹션 G
		/* 샵의 섹션 H(투수=문신#  선글라스#  아이패치) */
		eESPS_H = 9, // 섹션 H
		/* 샵의 섹션 I(투수=수염#  헤어#  패치#  마스크#  등번호#  마킹#  헤어컬러) */
		eESPS_I = 10, // 섹션 I
		eEND_EShopPitcherSection
	}; // EShopPitcherSection 



	enum ETotalGameType // 설명없음
	{
		eBEGIN_ETotalGameType = 0,
		/* 매치 */
		eTGT_Match = 1, // 매치
		/* 싱글 */
		eTGT_Single = 2, // 싱글
		/* 프랜들리 */
		eTGT_Friendly = 3, // 프랜들리
		eEND_ETotalGameType
	}; // ETotalGameType 






#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBaseballObjectType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBatterAbility[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBatterForm[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBatterHitType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBreakingBallPitch[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBreakingBallRotation[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ECategoryString[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EConsumeItemEffect[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EEventType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EGestureType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EGiftCategory[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EGiftType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EGradeAllitemType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHitTimmingType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHitType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemAbilityType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemBuyType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemCategory[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemCategoryEquipment[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemGradeType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemPriceType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemReuseType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemSellStatus[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemSexType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemState[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemSubGradeType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemUpgradeResult[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ELogType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ENoticeType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ENpcSituationString[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ENpcString[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPitcherAbility[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPitcherForm[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPlayer_Onoffline[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPlayerBodyType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPlayerBreakingBall[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPlayerGradeType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPlayerNationType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPlayerType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EQuestConditionType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EQuestType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ERhythmJudge[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EShopBatterSection[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EShopConsumeSection[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EShopItemType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EShopPitcherSection[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ETotalGameType[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nEXCEL_excel_enum_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_enum_
