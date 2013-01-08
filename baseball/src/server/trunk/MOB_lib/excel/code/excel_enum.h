/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_enum_
#define __namespace_nEXCEL___filename_excel_enum_

#include "table_const_excel_enum.h"
// -------------------------------------------------
// enum�� �ڵ� ���ø� ����
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nEXCEL_excel_enum_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EBaseballObjectType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EBatterAbility,�������,nMech,nEXCEL)\
	ENUM_TABLE(EBatterForm,�������,nMech,nEXCEL)\
	ENUM_TABLE(EBatterHitType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EBreakingBallPitch,�������,nMech,nEXCEL)\
	ENUM_TABLE(EBreakingBallRotation,�������,nMech,nEXCEL)\
	ENUM_TABLE(ECategoryString,�������,nMech,nEXCEL)\
	ENUM_TABLE(EConsumeItemEffect,�������,nMech,nEXCEL)\
	ENUM_TABLE(EEventType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EGestureType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EGiftCategory,�������,nMech,nEXCEL)\
	ENUM_TABLE(EGiftType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EGradeAllitemType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EHitTimmingType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EHitType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EItemAbilityType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EItemBuyType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EItemCategory,�������,nMech,nEXCEL)\
	ENUM_TABLE(EItemCategoryEquipment,�������,nMech,nEXCEL)\
	ENUM_TABLE(EItemGradeType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EItemPriceType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EItemReuseType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EItemSellStatus,�������,nMech,nEXCEL)\
	ENUM_TABLE(EItemSexType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EItemState,(�������� �Һ� ������ ���� �� ���������� ������ ����),nMech,nEXCEL)\
	ENUM_TABLE(EItemSubGradeType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EItemUpgradeResult,�������,nMech,nEXCEL)\
	ENUM_TABLE(ELogType,�������,nMech,nEXCEL)\
	ENUM_TABLE(ENoticeType,�������,nMech,nEXCEL)\
	ENUM_TABLE(ENpcSituationString,�������,nMech,nEXCEL)\
	ENUM_TABLE(ENpcString,�������,nMech,nEXCEL)\
	ENUM_TABLE(EPitcherAbility,�������,nMech,nEXCEL)\
	ENUM_TABLE(EPitcherForm,�������,nMech,nEXCEL)\
	ENUM_TABLE(EPlayer_Onoffline,�������,nMech,nEXCEL)\
	ENUM_TABLE(EPlayerBodyType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EPlayerBreakingBall,�������,nMech,nEXCEL)\
	ENUM_TABLE(EPlayerGradeType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EPlayerNationType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EPlayerType,(������ ������ Ŭ���̾�Ʈ ��Ŵ��),nMech,nEXCEL)\
	ENUM_TABLE(EQuestConditionType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EQuestType,�������,nMech,nEXCEL)\
	ENUM_TABLE(ERhythmJudge,�������,nMech,nEXCEL)\
	ENUM_TABLE(EShopBatterSection,(�������� ��� ���ÿ��� Ÿ�� �ϰ�� ���������� ������ ����),nMech,nEXCEL)\
	ENUM_TABLE(EShopConsumeSection,(�������� �Һ� ������ ���� �� ���������� ������ ����),nMech,nEXCEL)\
	ENUM_TABLE(EShopItemType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EShopPitcherSection,(�������� ��� ���ÿ��� ���� �ϰ�� ���� �� ���������� ������ ����),nMech,nEXCEL)\
	ENUM_TABLE(ETotalGameType,�������,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// ���� enum������ �տ� e�� �ڵ����� �پ ����� 
	// -------------------------------------------------

	/* ������� */
	#define for_each_nEXCEL_EBaseballObjectType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(BOT_user			,1,����,nMech,nEXCEL,EBaseballObjectType)\
		ENUM_FIELD(BOT_pitcher			,2,����,nMech,nEXCEL,EBaseballObjectType)\
		ENUM_FIELD(BOT_better			,3,Ÿ��,nMech,nEXCEL,EBaseballObjectType)\
		ENUM_FIELD(BOT_team			,4,��,nMech,nEXCEL,EBaseballObjectType)\

	/* ������� */
	#define for_each_nEXCEL_EBatterAbility_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(BA_NULL			,1,����,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_LEFT			,2,��������,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_RIGHT			,3,�������,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_HOMERUN			,4,Ȩ��Ÿ��,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_WIDE			,5,����Ÿ��,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_FULLHIT			,6,Ǯ����,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_LOWHIT			,7,�κ�����,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_HIGHHIT			,8,���̺�����,nMech,nEXCEL,EBatterAbility)\
		ENUM_FIELD(BA_RUNFIRE			,9,����,nMech,nEXCEL,EBatterAbility)\

	/* ������� */
	#define for_each_nEXCEL_EBatterForm_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(BF_SQUARE			,1,������,nMech,nEXCEL,EBatterForm)\
		ENUM_FIELD(BF_OPEN			,2,����,nMech,nEXCEL,EBatterForm)\
		ENUM_FIELD(BF_CLOSE			,3,ũ�����,nMech,nEXCEL,EBatterForm)\
		ENUM_FIELD(BF_NULL			,4,����,nMech,nEXCEL,EBatterForm)\
		ENUM_FIELD(BF_COMMON			,5,����,nMech,nEXCEL,EBatterForm)\

	/* ������� */
	#define for_each_nEXCEL_EBatterHitType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EBHT_STANDOUT			,1,���ĵ�ƿ�,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBHT_SWINGOUT			,2,�����ƿ�,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBHT_FOULOUT			,3,�Ŀ�ƿ�,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBIT_INFIELDOUT			,4,���߾ƿ�,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBIT_LEFTFIELDOUT			,5,���ͼ��ƿ�,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBIT_CENTERFIELDOUT			,6,�߰߼��ƿ�,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBIT_RIGHTFIELDOUT			,7,���ͼ��ƿ�,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBHT_NO_HIT			,8,ġ�����ѻ���,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBHT_ONEHIT			,9,�Ϸ�Ÿ,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBHT_DOUBLEHIT			,10,�̷�Ÿ,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBHT_TRIPLEHIT			,11,���Ÿ,nMech,nEXCEL,EBatterHitType)\
		ENUM_FIELD(EBHT_HOMERUN			,12,Ȩ��,nMech,nEXCEL,EBatterHitType)\

	/* ������� */
	#define for_each_nEXCEL_EBreakingBallPitch_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EBBP_STRAIGHT			,1,����,nMech,nEXCEL,EBreakingBallPitch)\
		ENUM_FIELD(EBBP_WIDE			,2,Ⱦ��ȭ,nMech,nEXCEL,EBreakingBallPitch)\
		ENUM_FIELD(EBBP_HEIGHT			,3,����ȭ,nMech,nEXCEL,EBreakingBallPitch)\
		ENUM_FIELD(EBBP_HEIGHTWIDE			,4,��Ⱦ��ȭ,nMech,nEXCEL,EBreakingBallPitch)\

	/* ������� */
	#define for_each_nEXCEL_EBreakingBallRotation_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EBBR_REGULAR			,1,��ȸ��,nMech,nEXCEL,EBreakingBallRotation)\
		ENUM_FIELD(EBBR_REVERSE			,2,��ȸ��,nMech,nEXCEL,EBreakingBallRotation)\
		ENUM_FIELD(EBBR_NOTHING			,3,��ȸ��,nMech,nEXCEL,EBreakingBallRotation)\

	/* ������� */
	#define for_each_nEXCEL_ECategoryString_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ECS_ITEM			,1,������,nMech,nEXCEL,ECategoryString)\
		ENUM_FIELD(ECS_GUI			,2,GUI,nMech,nEXCEL,ECategoryString)\
		ENUM_FIELD(ECS_SKILL			,3,��ų��,nMech,nEXCEL,ECategoryString)\
		ENUM_FIELD(ECS_ETC			,4,��Ÿ,nMech,nEXCEL,ECategoryString)\

	/* ������� */
	#define for_each_nEXCEL_EConsumeItemEffect_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(CIE_MONEYUP			,1,���ӸӴϹ����¾�����,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_EXPUP			,2,����ġ�����¾�����,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_ITEMDROPUP			,3,�����۵��Ȯ����¾�����,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_STATUPWHILE			,4,�ɷ�ġ�Ͻû�¾�����,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_STATUPFOREVER			,5,�ɷ�ġ������¾�����,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_UPGRADELUCKYUP			,6,��ȭȮ������������,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_UPGRADETIMEDOWN			,7,��ȭ�ð����Ҿ�����,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_UPGRADECANCEL			,8,��ȭ��Ҿ�����,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_ITEMUSEDOWN			,9,�����ۻ�밡�ɷ�������,nMech,nEXCEL,EConsumeItemEffect)\
		ENUM_FIELD(CIE_ETC			,10,ETC,nMech,nEXCEL,EConsumeItemEffect)\

	/* ������� */
	#define for_each_nEXCEL_EEventType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ET_MONEY			,1,�Ӵ�,nMech,nEXCEL,EEventType)\
		ENUM_FIELD(ET_ITEM			,2,������,nMech,nEXCEL,EEventType)\
		ENUM_FIELD(ET_MONEY_ITEM			,3,�Ӵ�_������,nMech,nEXCEL,EEventType)\

	/* ������� */
	#define for_each_nEXCEL_EGestureType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EGTT_STRAGHT			,1,����,nMech,nEXCEL,EGestureType)\
		ENUM_FIELD(EGTT_VERTICAL			,2,������,nMech,nEXCEL,EGestureType)\
		ENUM_FIELD(EGTT_CURVE			,3,�,nMech,nEXCEL,EGestureType)\
		ENUM_FIELD(EGTT_STAIR_VERTICAL			,4,�����������,nMech,nEXCEL,EGestureType)\
		ENUM_FIELD(EGTT_S_CURVE			,5,�������,nMech,nEXCEL,EGestureType)\
		ENUM_FIELD(EGTT_NULL			,6,����,nMech,nEXCEL,EGestureType)\

	/* ������� */
	#define for_each_nEXCEL_EGiftCategory_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EGC_SINGLEGAMEWIN			,1,�̱۰��ӽ�,nMech,nEXCEL,EGiftCategory)\
		ENUM_FIELD(EGC_SINGLEGAMELOSE			,2,�̱۰�����,nMech,nEXCEL,EGiftCategory)\
		ENUM_FIELD(EGC_MATCHGAMEWIN			,3,�������ӽ�,nMech,nEXCEL,EGiftCategory)\
		ENUM_FIELD(EGC_MATCHGAMELOSE			,4,����������,nMech,nEXCEL,EGiftCategory)\
		ENUM_FIELD(EGC_FRIENDGAMEWIN			,5,ģ�����ӽ�,nMech,nEXCEL,EGiftCategory)\
		ENUM_FIELD(EGC_FRIENDGAMELOSE			,6,ģ��������,nMech,nEXCEL,EGiftCategory)\
		ENUM_FIELD(EGC_TRAININGWIN			,7,Ʈ���̴׽�,nMech,nEXCEL,EGiftCategory)\
		ENUM_FIELD(EGC_TRAININGLOSE			,8,Ʈ���̴���,nMech,nEXCEL,EGiftCategory)\

	/* ������� */
	#define for_each_nEXCEL_EGiftType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EGT_NULL			,1,����,nMech,nEXCEL,EGiftType)\
		ENUM_FIELD(EGT_GAMEMONEY			,2,���ӸӴ�,nMech,nEXCEL,EGiftType)\
		ENUM_FIELD(EGT_PLAYERSKILLSTICKER			,3,��ų��ƼĿ,nMech,nEXCEL,EGiftType)\
		ENUM_FIELD(EGT_PLAYERCARD			,4,�÷��̾�ī��,nMech,nEXCEL,EGiftType)\
		ENUM_FIELD(EGT_GAMECASH			,5,���� ĳ��,nMech,nEXCEL,EGiftType)\

	/* ������� */
	#define for_each_nEXCEL_EGradeAllitemType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EGAT_NULL			,1,����,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_SMAINITEMALL			,2,S�� ���ξ����� ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_AMAINITEMALL			,3,A�� ���ξ����� ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_BMAINITEMALL			,4,B�� ���ξ����� ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_CMAINITEMALL			,5,C�� ���ξ����� ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_DMAINITEMALL			,6,D�� ���ξ����� ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_EMAINITEMALL			,7,E�� ���ξ����� ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_SSUBITEMALL			,8,S�� ��������� ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_ASUBITEMALL			,9,A�� ��������� ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_BSUBITEMALL			,10,B�� ��������� ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_CSUBITEMALL			,11,C�� ��������� ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_DSUBITEMALL			,12,D�� ��������� ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_ESUBITEMALL			,13,E�� ��������� ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_SCONSUMEITEMALL			,14,S�� �Һ������ ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_ACONSUMEITEMALL			,15,A�� �Һ������ ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_BCONSUMEITEMALL			,16,B�� �Һ������ ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_CCONSUMEITEMALL			,17,C�� �Һ������ ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_DCONSUMEITEMALL			,18,D�� �Һ������ ���,nMech,nEXCEL,EGradeAllitemType)\
		ENUM_FIELD(EGAT_ECONSUMEITEMALL			,19,E�� �Һ������ ���,nMech,nEXCEL,EGradeAllitemType)\

	/* ������� */
	#define for_each_nEXCEL_EHitTimmingType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EHTT_eHitTime_None			,0,Ŭ���̾�Ʈ��,nMech,nEXCEL,EHitTimmingType)\
		ENUM_FIELD(EHTT_eHitTime_VeryFast			,1,�ſ� ����,nMech,nEXCEL,EHitTimmingType)\
		ENUM_FIELD(EHTT_eHitTime_Fast			,2,����,nMech,nEXCEL,EHitTimmingType)\
		ENUM_FIELD(EHTT_eHitTime_GoodFast			,3,���� ����,nMech,nEXCEL,EHitTimmingType)\
		ENUM_FIELD(EHTT_eHitTime_Perfect			,4,����Ʈ ����,nMech,nEXCEL,EHitTimmingType)\
		ENUM_FIELD(EHTT_eHitTime_GoodSlow			,5,���� ����,nMech,nEXCEL,EHitTimmingType)\
		ENUM_FIELD(EHTT_eHitTime_Slow			,6,����,nMech,nEXCEL,EHitTimmingType)\
		ENUM_FIELD(EHTT_eHitTime_VerySlow			,7,�ſ� ����,nMech,nEXCEL,EHitTimmingType)\

	/* ������� */
	#define for_each_nEXCEL_EHitType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EHT_eNS_NONE			,0,Ŭ���̾�Ʈ��,nMech,nEXCEL,EHitType)\
		ENUM_FIELD(EHT_eNS_BALLHIT			,1,�Ϲ� ��Ʈ,nMech,nEXCEL,EHitType)\
		ENUM_FIELD(EHT_eNS_BALLHITSTRONG			,2,����_��Ʈ�� ��Ʈ,nMech,nEXCEL,EHitType)\
		ENUM_FIELD(EHT_eNS_SWING			,3,�꽺��,nMech,nEXCEL,EHitType)\
		ENUM_FIELD(EHT_eNS_NOTHING			,4,��� ����,nMech,nEXCEL,EHitType)\

	/* ������� */
	#define for_each_nEXCEL_EItemAbilityType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IAT_POWER			,1,�Ŀ�,nMech,nEXCEL,EItemAbilityType)\
		ENUM_FIELD(IAT_ACCURACY			,2,��Ȯ,nMech,nEXCEL,EItemAbilityType)\
		ENUM_FIELD(IAT_FOCUS			,3,����,nMech,nEXCEL,EItemAbilityType)\
		ENUM_FIELD(IAT_SPEED			,4,����,nMech,nEXCEL,EItemAbilityType)\
		ENUM_FIELD(IAT_BREAKINGBALL			,5,��ȭ��,nMech,nEXCEL,EItemAbilityType)\
		ENUM_FIELD(IAT_ALLABILITY			,6,��罺��,nMech,nEXCEL,EItemAbilityType)\
		ENUM_FIELD(IAT_NULL			,7,����,nMech,nEXCEL,EItemAbilityType)\

	/* ������� */
	#define for_each_nEXCEL_EItemBuyType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IBT_BUY_CASH			,1,ĳ�� ���� ������,nMech,nEXCEL,EItemBuyType)\
		ENUM_FIELD(IBT_BUY_POINT			,2,����Ʈ ���� ������,nMech,nEXCEL,EItemBuyType)\
		ENUM_FIELD(IBT_BUY_USED			,3,ĳ���ͼӾ�����,nMech,nEXCEL,EItemBuyType)\
		ENUM_FIELD(IBT_EVENT			,4,�̺�Ʈ ���޾�����,nMech,nEXCEL,EItemBuyType)\
		ENUM_FIELD(IBT_REWARD			,5,��⺸�����ι���,nMech,nEXCEL,EItemBuyType)\

	/* ������� */
	#define for_each_nEXCEL_EItemCategory_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IC_EQUIP			,1,�������,nMech,nEXCEL,EItemCategory)\
		ENUM_FIELD(IC_CONSUME			,2,�Ҹ������,nMech,nEXCEL,EItemCategory)\
		ENUM_FIELD(IC_STUFF			,3,��������,nMech,nEXCEL,EItemCategory)\
		ENUM_FIELD(IC_NULL			,4,����,nMech,nEXCEL,EItemCategory)\

	/* ������� */
	#define for_each_nEXCEL_EItemCategoryEquipment_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ICE_SHIRT			,1,����,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_PANT			,2,����,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_CAP			,3,����,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_SHOES_B			,4,Ÿ�� �Ź�,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_SHOES_P			,5,���� �Ź�,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_GLOVE			,6,�����۷���,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_U_SHIRT			,7,�������,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_SOCKS			,8,�縻,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_ARM_GUARDS			,9,��_��ȣ��,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_LEG_GUARDS			,10,�ٸ�_��ȣ��,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_BAT			,11,��Ʈ,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_BALL			,12,��,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_HELMET			,13,���,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_GLOBE			,14,Ÿ���尩,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_WRISTBAND			,15,����Ʈ ���,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_NECKLACE			,16,�����,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_RING			,17,����,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_EARRING			,18,�Ͱ���,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_TATOO			,19,����,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_SUNGLASS			,20,���۶�,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_EYEPATCH			,21,������ġ,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_BEARD			,22,����,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_HAIR_M			,23,������Ÿ��,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_HAIR_W			,24,������Ÿ��,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_HAIR_COLOR			,25,���Į��,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_PATCH			,26,��ġ,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_MASK			,27,����ũ,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_BACKNUMBER			,28,���ȣ ������,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_MAKING			,29,��ŷ ������,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_FACE			,30,��,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_ARM			,31,��,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_LEG			,32,�ٸ�(����),nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_LEFTHAND			,33,�޼�,nMech,nEXCEL,EItemCategoryEquipment)\
		ENUM_FIELD(ICE_RIGHTHAND			,34,������,nMech,nEXCEL,EItemCategoryEquipment)\

	/* ������� */
	#define for_each_nEXCEL_EItemGradeType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IGT_E			,1,E���,nMech,nEXCEL,EItemGradeType)\
		ENUM_FIELD(IGT_D			,2,D���,nMech,nEXCEL,EItemGradeType)\
		ENUM_FIELD(IGT_C			,3,C���,nMech,nEXCEL,EItemGradeType)\
		ENUM_FIELD(IGT_B			,4,B���,nMech,nEXCEL,EItemGradeType)\
		ENUM_FIELD(IGT_A			,5,A���,nMech,nEXCEL,EItemGradeType)\
		ENUM_FIELD(IGT_S			,6,S���,nMech,nEXCEL,EItemGradeType)\
		ENUM_FIELD(IGT_NULL			,7,�����,nMech,nEXCEL,EItemGradeType)\

	/* ������� */
	#define for_each_nEXCEL_EItemPriceType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IPT_CASH			,1,ĳ��,nMech,nEXCEL,EItemPriceType)\
		ENUM_FIELD(IPT_CASH_POINT			,2,ĳ��_����Ʈ,nMech,nEXCEL,EItemPriceType)\
		ENUM_FIELD(IPT_MONEY			,3,����Ʈ,nMech,nEXCEL,EItemPriceType)\

	/* ������� */
	#define for_each_nEXCEL_EItemReuseType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IUT_NORMAL			,1,����,nMech,nEXCEL,EItemReuseType)\
		ENUM_FIELD(IUT_INSTANTLY			,2,�Ⱓ��,nMech,nEXCEL,EItemReuseType)\
		ENUM_FIELD(IUT_FIXED			,3,�Ұ�,nMech,nEXCEL,EItemReuseType)\

	/* ������� */
	#define for_each_nEXCEL_EItemSellStatus_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ISS_SELL_STOP			,1,�Ǹ�����,nMech,nEXCEL,EItemSellStatus)\
		ENUM_FIELD(ISS_SELL			,2,�Ǹ���,nMech,nEXCEL,EItemSellStatus)\
		ENUM_FIELD(ISS_SELL_PLAN			,3,�Ǹſ���,nMech,nEXCEL,EItemSellStatus)\

	/* ������� */
	#define for_each_nEXCEL_EItemSexType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IST_MAN_ONLY			,1,��,nMech,nEXCEL,EItemSexType)\
		ENUM_FIELD(IST_WOMAN_ONLY			,2,��,nMech,nEXCEL,EItemSexType)\
		ENUM_FIELD(IST_COMMON			,3,����,nMech,nEXCEL,EItemSexType)\

	/* (�������� �Һ� ������ ���� �� ���������� ������ ����) */
	#define for_each_nEXCEL_EItemState_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IS_NORMAL			,1,�Ϲݻ���,nMech,nEXCEL,EItemState)\
		ENUM_FIELD(IS_DELETE			,2,�����Ȼ���,nMech,nEXCEL,EItemState)\
		ENUM_FIELD(IS_ADMIN_BLOCKED			,3,���Ұ���.,nMech,nEXCEL,EItemState)\
		ENUM_FIELD(IS_DELETE_REFUND			,4,���ȱ�Ǿ� ������,nMech,nEXCEL,EItemState)\

	/* ������� */
	#define for_each_nEXCEL_EItemSubGradeType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ISGT_EE			,1,EE���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_DE			,2,DE���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_DD			,3,DD���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_CE			,4,CE���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_CD			,5,CD���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_CC			,6,CC���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_BE			,7,BE���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_BD			,8,BD���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_BC			,9,BC���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_BB			,10,BB���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_AE			,11,AE���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_AD			,12,AD���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_AC			,13,AC���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_AB			,14,AB���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_AA			,15,AA���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_SE			,16,SE���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_SD			,17,SD���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_SC			,18,SC���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_SB			,19,SB���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_SA			,20,SA���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_SS			,21,SS���,nMech,nEXCEL,EItemSubGradeType)\
		ENUM_FIELD(ISGT_NULL			,22,��޾���,nMech,nEXCEL,EItemSubGradeType)\

	/* ������� */
	#define for_each_nEXCEL_EItemUpgradeResult_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IUR_HELMET			,1,���,nMech,nEXCEL,EItemUpgradeResult)\
		ENUM_FIELD(IUR_CAP			,2,����,nMech,nEXCEL,EItemUpgradeResult)\
		ENUM_FIELD(IUR_BET			,3,��Ʈ,nMech,nEXCEL,EItemUpgradeResult)\
		ENUM_FIELD(IUR_BALL			,4,��,nMech,nEXCEL,EItemUpgradeResult)\
		ENUM_FIELD(IUR_GLOBE			,5,Ÿ���尩,nMech,nEXCEL,EItemUpgradeResult)\
		ENUM_FIELD(IUR_GLOVE			,6,�۷���,nMech,nEXCEL,EItemUpgradeResult)\
		ENUM_FIELD(IUR_SHOES			,7,�Ź�,nMech,nEXCEL,EItemUpgradeResult)\

	/* ������� */
	#define for_each_nEXCEL_ELogType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(SCT_KINGROOKIE			,1,�α�1,nMech,nEXCEL,ELogType)\
		ENUM_FIELD(SCT_ROOKIE			,2,�α�2,nMech,nEXCEL,ELogType)\
		ENUM_FIELD(SCT_AMA1			,3,�α�3,nMech,nEXCEL,ELogType)\
		ENUM_FIELD(SCT_AMA2			,4,�α�4,nMech,nEXCEL,ELogType)\
		ENUM_FIELD(SCT_PRO			,5,�α�5,nMech,nEXCEL,ELogType)\

	/* ������� */
	#define for_each_nEXCEL_ENoticeType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(NT_LED			,1,������,nMech,nEXCEL,ENoticeType)\
		ENUM_FIELD(NT_CHECK			,2,�ӽ�����,nMech,nEXCEL,ENoticeType)\
		ENUM_FIELD(NT_NOTICE			,3,��������,nMech,nEXCEL,ENoticeType)\

	/* ������� */
	#define for_each_nEXCEL_ENpcSituationString_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ENSS_STANDING_BY			,1,�����,nMech,nEXCEL,ENpcSituationString)\
		ENUM_FIELD(ENSS_SELECTION			,2,���� ��,nMech,nEXCEL,ENpcSituationString)\
		ENUM_FIELD(ENSS_UPGRADE_WORKING			,3,���׷��̵� ��,nMech,nEXCEL,ENpcSituationString)\
		ENUM_FIELD(ENSS_TRANING_WORKING			,4,Ʈ���̴� ��,nMech,nEXCEL,ENpcSituationString)\
		ENUM_FIELD(ENSS_COMPLETE			,5,�Ϸ�,nMech,nEXCEL,ENpcSituationString)\
		ENUM_FIELD(ENSS_UPGRADE_RESULT			,6,���׷��̵� ���,nMech,nEXCEL,ENpcSituationString)\
		ENUM_FIELD(ENSS_TRANING_RESULT			,7,Ʈ���̴� ���,nMech,nEXCEL,ENpcSituationString)\

	/* ������� */
	#define for_each_nEXCEL_ENpcString_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ENS_MAESTRO			,1,����,nMech,nEXCEL,ENpcString)\
		ENUM_FIELD(ENS_COACH			,2,������ġ,nMech,nEXCEL,ENpcString)\

	/* ������� */
	#define for_each_nEXCEL_EPitcherAbility_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(PA_NULL			,1,����,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_LEFT			,2,����Ÿ��,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_RIGHT			,3,���Ÿ��,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_FASTBALL			,4,�ӱ���,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_FULLSKILL			,5,�ⱳ��,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_RUNFIRE			,6,����,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_SWORDCON			,7,Į����,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_DOCK			,8,����K,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_INFIGHT			,9,��������,nMech,nEXCEL,EPitcherAbility)\
		ENUM_FIELD(PA_OUTFIGHT			,10,�ƿ�������,nMech,nEXCEL,EPitcherAbility)\

	/* ������� */
	#define for_each_nEXCEL_EPitcherForm_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(PF_OVER			,1,����,nMech,nEXCEL,EPitcherForm)\
		ENUM_FIELD(PF_THREEQUARTER			,2,��������,nMech,nEXCEL,EPitcherForm)\
		ENUM_FIELD(PF_SIDEARM			,3,���̵��,nMech,nEXCEL,EPitcherForm)\
		ENUM_FIELD(PF_UNDER			,4,���,nMech,nEXCEL,EPitcherForm)\
		ENUM_FIELD(PF_NULL			,5,����,nMech,nEXCEL,EPitcherForm)\
		ENUM_FIELD(PF_COMMON			,6,����,nMech,nEXCEL,EPitcherForm)\

	/* ������� */
	#define for_each_nEXCEL_EPlayer_Onoffline_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EPO_ONPLAYER			,1,�¶����÷��̾�,nMech,nEXCEL,EPlayer_Onoffline)\
		ENUM_FIELD(EPO_OFFPLAYER			,2,���������÷��̾�,nMech,nEXCEL,EPlayer_Onoffline)\

	/* ������� */
	#define for_each_nEXCEL_EPlayerBodyType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EPBT_SMALL			,1,����,nMech,nEXCEL,EPlayerBodyType)\
		ENUM_FIELD(EPBT_MIDIUM			,2,�̵��,nMech,nEXCEL,EPlayerBodyType)\
		ENUM_FIELD(EPBT_LARGE			,3,����,nMech,nEXCEL,EPlayerBodyType)\
		ENUM_FIELD(EPBT_WOMAN			,4,����,nMech,nEXCEL,EPlayerBodyType)\

	/* ������� */
	#define for_each_nEXCEL_EPlayerBreakingBall_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(PBB_NULL			,1,����,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_FOURSEAM			,2,����,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_TWOSEAM			,3,����,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_RISINGFAST			,4,����¡�н�Ʈ��,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_UPSHOUT			,5,����,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_SLIDER			,6,�����̴�,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_HSLIDER			,7,H�����̴�,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_CUTFAST			,8,���н�Ʈ��,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_VSLIDER			,9,V�����̴�,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_SLUB			,10,������,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_CHANGEUP			,11,ü������,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_CIRCLECHANGEUP			,12,��Ŭü������,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_KNUCKLE			,13,��Ŭ,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_CURVE			,14,Ŀ��,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_SLOWCURVE			,15,���ο�Ŀ��,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_KNUCKLECURVE			,16,��ŬĿ��,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_DROPCURVE			,17,���Ŀ��,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_POWERCURVE			,18,�Ŀ�Ŀ��,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_SHOUT			,19,��Ʈ,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_HSHOUT			,20,H��Ʈ,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_FORK			,21,��ũ,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_PALM			,22,��,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_SFF			,23,SFF,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_SINKER			,24,��Ŀ_ ��ũ��,nMech,nEXCEL,EPlayerBreakingBall)\
		ENUM_FIELD(PBB_HSINKER			,25,H��Ŀ,nMech,nEXCEL,EPlayerBreakingBall)\

	/* ������� */
	#define for_each_nEXCEL_EPlayerGradeType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(PGT_E			,1,E���,nMech,nEXCEL,EPlayerGradeType)\
		ENUM_FIELD(PGT_D			,2,D���,nMech,nEXCEL,EPlayerGradeType)\
		ENUM_FIELD(PGT_C			,3,C���,nMech,nEXCEL,EPlayerGradeType)\
		ENUM_FIELD(PGT_B			,4,B���,nMech,nEXCEL,EPlayerGradeType)\
		ENUM_FIELD(PGT_A			,5,A���,nMech,nEXCEL,EPlayerGradeType)\
		ENUM_FIELD(PGT_S			,6,S���,nMech,nEXCEL,EPlayerGradeType)\

	/* ������� */
	#define for_each_nEXCEL_EPlayerNationType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(PNT_KOREA			,1,�ѱ�,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_USA			,2,�̱�,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_JAPAN			,3,�Ϻ�,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_CHINA			,4,�߱�,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_CANADA			,5,ĳ����,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_ITALY			,6,��Ż����,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_TAIWAN			,7,�븸,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_AUSTRALIA			,8,ȣ��,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_NETHERLANDS			,9,�״�����,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_CUBA			,10,���,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_TRINIDADANDTOBAGO			,11,Ʈ���ϴٵ���ٰ�,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_DOMINICANREPUBLIC			,12,���̴�ī��ȭ��,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_PANAMA			,13,�ĳ���,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_PUERTORICO			,14,Ǫ�����丮��,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_REPUBLICOFSOUTHAFRICA			,15,��������ī��ȭ��,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_VENEZUELA			,16,���׼�����,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_UNITEDKINGDOM			,17,����,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_SPAIN			,18,������,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_FRANCE			,19,������,nMech,nEXCEL,EPlayerNationType)\
		ENUM_FIELD(PNT_GERMANY			,20,����,nMech,nEXCEL,EPlayerNationType)\

	/* (������ ������ Ŭ���̾�Ʈ ��Ŵ��) */
	#define for_each_nEXCEL_EPlayerType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(PT_BATTER			,1,Ÿ��,nMech,nEXCEL,EPlayerType)\
		ENUM_FIELD(PT_PITCHER			,2,����,nMech,nEXCEL,EPlayerType)\
		ENUM_FIELD(PT_COMMON			,3,����,nMech,nEXCEL,EPlayerType)\
		ENUM_FIELD(PT_CATCHER			,4,����,nMech,nEXCEL,EPlayerType)\
		ENUM_FIELD(PT_UMPIRE			,5,����,nMech,nEXCEL,EPlayerType)\

	/* ������� */
	#define for_each_nEXCEL_EQuestConditionType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(QCT_NULL			,1,����,nMech,nEXCEL,EQuestConditionType)\
		ENUM_FIELD(QCT_EQUIPGRADETYPE			,12,��ü�����������,nMech,nEXCEL,EQuestConditionType)\
		ENUM_FIELD(QCT_CASHCOUNT			,13,ĳ���۱�������,nMech,nEXCEL,EQuestConditionType)\
		ENUM_FIELD(QCT_GAMEMONEYCOUNT			,14,���ӸӴϴ�������,nMech,nEXCEL,EQuestConditionType)\
		ENUM_FIELD(QCT_PLAYERALLSTATCOUNT			,15,ĳ���͸��ɷ�ġ�޼�����,nMech,nEXCEL,EQuestConditionType)\
		ENUM_FIELD(QCT_GAME_VALIABLE			,16,���Ӻ���,nMech,nEXCEL,EQuestConditionType)\
		ENUM_FIELD(QCT_MANUAL_FINISH			,17,���ǿϷ�,nMech,nEXCEL,EQuestConditionType)\

	/* ������� */
	#define for_each_nEXCEL_EQuestType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EQT_MATCH			,1,MATCH ����Ʈ,nMech,nEXCEL,EQuestType)\
		ENUM_FIELD(EQT_SINGLE			,2,SINGLE ����Ʈ,nMech,nEXCEL,EQuestType)\
		ENUM_FIELD(EQT_FRIENDLY			,3,FRIENDLY ����Ʈ,nMech,nEXCEL,EQuestType)\
		ENUM_FIELD(EQT_ITEMETC			,4,ITEM_ETC ����Ʈ,nMech,nEXCEL,EQuestType)\
		ENUM_FIELD(EQT_INGAMETUTORIAL			,5,TUTORIAL,nMech,nEXCEL,EQuestType)\
		ENUM_FIELD(EQT_DAILY			,6,DAILY ����Ʈ,nMech,nEXCEL,EQuestType)\

	/* ������� */
	#define for_each_nEXCEL_ERhythmJudge_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ERJ_eJudge_None			,0,Ŭ���̾�Ʈ��,nMech,nEXCEL,ERhythmJudge)\
		ENUM_FIELD(ERJ_eJudge_Bad			,1,���,nMech,nEXCEL,ERhythmJudge)\
		ENUM_FIELD(ERJ_eJudge_Normal			,2,���,nMech,nEXCEL,ERhythmJudge)\
		ENUM_FIELD(ERJ_eJudge_Good			,3,��,nMech,nEXCEL,ERhythmJudge)\
		ENUM_FIELD(ERJ_eJudge_Perfect			,4,����Ʈ,nMech,nEXCEL,ERhythmJudge)\

	/* (�������� ��� ���ÿ��� Ÿ�� �ϰ�� ���������� ������ ����) */
	#define for_each_nEXCEL_EShopBatterSection_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ESBS_NULL			,1,����,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_A			,2,���� A,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_B			,3,���� B,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_C			,4,���� C,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_D			,5,���� D,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_E			,6,���� E,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_F			,7,���� F,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_G			,8,���� G,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_H			,9,���� H,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_I			,10,���� I,nMech,nEXCEL,EShopBatterSection)\
		ENUM_FIELD(ESBS_J			,11,���� J,nMech,nEXCEL,EShopBatterSection)\

	/* (�������� �Һ� ������ ���� �� ���������� ������ ����) */
	#define for_each_nEXCEL_EShopConsumeSection_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ESCS_NULL			,1,����,nMech,nEXCEL,EShopConsumeSection)\
		ENUM_FIELD(ESCS_A			,2,���� A,nMech,nEXCEL,EShopConsumeSection)\
		ENUM_FIELD(ESCS_B			,3,���� B,nMech,nEXCEL,EShopConsumeSection)\
		ENUM_FIELD(ESCS_C			,4,���� C,nMech,nEXCEL,EShopConsumeSection)\
		ENUM_FIELD(ESCS_D			,5,���� D,nMech,nEXCEL,EShopConsumeSection)\
		ENUM_FIELD(ESCS_E			,6,���� E,nMech,nEXCEL,EShopConsumeSection)\

	/* ������� */
	#define for_each_nEXCEL_EShopItemType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ESIT_Sys_Package			,1,��Ű��,nMech,nEXCEL,EShopItemType)\
		ENUM_FIELD(ESIT_Sys_ItemEquip			,2,����������,nMech,nEXCEL,EShopItemType)\
		ENUM_FIELD(ESIT_Sys_ItemStuff			,3,��������,nMech,nEXCEL,EShopItemType)\
		ENUM_FIELD(ESIT_Sys_ItemConsume			,4,�Ҹ������,nMech,nEXCEL,EShopItemType)\
		ENUM_FIELD(ESIT_Sys_PlayerSkillSticker			,5,��ȭ��������,nMech,nEXCEL,EShopItemType)\

	/* (�������� ��� ���ÿ��� ���� �ϰ�� ���� �� ���������� ������ ����) */
	#define for_each_nEXCEL_EShopPitcherSection_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ESPS_NULL			,1,����,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_A			,2,���� A,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_B			,3,���� B,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_C			,4,���� C,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_D			,5,���� D,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_E			,6,���� E,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_F			,7,���� F,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_G			,8,���� G,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_H			,9,���� H,nMech,nEXCEL,EShopPitcherSection)\
		ENUM_FIELD(ESPS_I			,10,���� I,nMech,nEXCEL,EShopPitcherSection)\

	/* ������� */
	#define for_each_nEXCEL_ETotalGameType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(TGT_Match			,1,��ġ,nMech,nEXCEL,ETotalGameType)\
		ENUM_FIELD(TGT_Single			,2,�̱�,nMech,nEXCEL,ETotalGameType)\
		ENUM_FIELD(TGT_Friendly			,3,�����鸮,nMech,nEXCEL,ETotalGameType)\


// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum EBaseballObjectType // �������
	{
		eBEGIN_EBaseballObjectType = 0,
		/* ���� */
		eBOT_user = 1, // ����
		/* ���� */
		eBOT_pitcher = 2, // ����
		/* Ÿ�� */
		eBOT_better = 3, // Ÿ��
		/* �� */
		eBOT_team = 4, // ��
		eEND_EBaseballObjectType
	}; // EBaseballObjectType 



	enum EBatterAbility // �������
	{
		eBEGIN_EBatterAbility = 0,
		/* ���� */
		eBA_NULL = 1, // ����
		/* ���������� �Ŀ� ����. ������ BA_RIGHT��ƼĿ�� ���������� */
		eBA_LEFT = 2, // ��������
		/* ������� ���� �Ŀ� ����. ������ BA_LEFT��ƼĿ�� ���������� */
		eBA_RIGHT = 3, // �������
		/* ��Ʈ�� �Ŀ� ���� */
		eBA_HOMERUN = 4, // Ȩ��Ÿ��
		/* ����Ÿ�� - �о������� �Ŀ� �ٿ���� */
		eBA_WIDE = 5, // ����Ÿ��
		/* Ǯ���� - ��������� �Ŀ� ���� */
		eBA_FULLHIT = 6, // Ǯ����
		/* �κ����� - Ÿ�������� �ϴ�/�ߴܿ��� �Ŀ� ���� */
		eBA_LOWHIT = 7, // �κ�����
		/* ���̺����� - �ߴ�# ��ܿ��� �Ŀ� ���� */
		eBA_HIGHHIT = 8, // ���̺�����
		/* ���� - �ٷ� ����Ÿ������ Ȩ���� �Ŀ� ���� */
		eBA_RUNFIRE = 9, // ����
		eEND_EBatterAbility
	}; // EBatterAbility 



	enum EBatterForm // �������
	{
		eBEGIN_EBatterForm = 0,
		/* ������ */
		eBF_SQUARE = 1, // ������
		/* ���� */
		eBF_OPEN = 2, // ����
		/* ũ����� */
		eBF_CLOSE = 3, // ũ�����
		/* ���� */
		eBF_NULL = 4, // ����
		/* ���� */
		eBF_COMMON = 5, // ����
		eEND_EBatterForm
	}; // EBatterForm 



	enum EBatterHitType // �������
	{
		eBEGIN_EBatterHitType = 0,
		/* ���ĵ�ƿ� */
		eEBHT_STANDOUT = 1, // ���ĵ�ƿ�
		/* �����ƿ� */
		eEBHT_SWINGOUT = 2, // �����ƿ�
		/* �Ŀ�ƿ� */
		eEBHT_FOULOUT = 3, // �Ŀ�ƿ�
		/* ���߾ƿ� */
		eEBIT_INFIELDOUT = 4, // ���߾ƿ�
		/* ���ͼ��ƿ� */
		eEBIT_LEFTFIELDOUT = 5, // ���ͼ��ƿ�
		/* �߰߼��ƿ� */
		eEBIT_CENTERFIELDOUT = 6, // �߰߼��ƿ�
		/* ���ͼ��ƿ� */
		eEBIT_RIGHTFIELDOUT = 7, // ���ͼ��ƿ�
		/* �� �̻��� �ƿ����¸� ��Ÿ�������� �� */
		eEBHT_NO_HIT = 8, // ġ�����ѻ���
		/* �Ϸ�Ÿ */
		eEBHT_ONEHIT = 9, // �Ϸ�Ÿ
		/* �̷�Ÿ */
		eEBHT_DOUBLEHIT = 10, // �̷�Ÿ
		/* ���Ÿ */
		eEBHT_TRIPLEHIT = 11, // ���Ÿ
		/* Ȩ�� */
		eEBHT_HOMERUN = 12, // Ȩ��
		eEND_EBatterHitType
	}; // EBatterHitType 



	enum EBreakingBallPitch // �������
	{
		eBEGIN_EBreakingBallPitch = 0,
		/* ���� */
		eEBBP_STRAIGHT = 1, // ����
		/* Ⱦ��ȭ */
		eEBBP_WIDE = 2, // Ⱦ��ȭ
		/* ����ȭ */
		eEBBP_HEIGHT = 3, // ����ȭ
		/* ��Ⱦ��ȭ */
		eEBBP_HEIGHTWIDE = 4, // ��Ⱦ��ȭ
		eEND_EBreakingBallPitch
	}; // EBreakingBallPitch 



	enum EBreakingBallRotation // �������
	{
		eBEGIN_EBreakingBallRotation = 0,
		/* ��ȸ�� */
		eEBBR_REGULAR = 1, // ��ȸ��
		/* ��ȸ�� */
		eEBBR_REVERSE = 2, // ��ȸ��
		/* ��ȸ�� */
		eEBBR_NOTHING = 3, // ��ȸ��
		eEND_EBreakingBallRotation
	}; // EBreakingBallRotation 



	enum ECategoryString // �������
	{
		eBEGIN_ECategoryString = 0,
		/* �����۰��� ��Ʈ��. Text1=�̸� text2=���� �� ����������϶��� text2=Ÿ�ڿ뼳�� text3=�����뼳�� */
		eECS_ITEM = 1, // ������
		/* ȭ�� GUI�� ��Ʈ�� */
		eECS_GUI = 2, // GUI
		/* ��ų�� ��Ʈ��, text1=�̸� text2=���� */
		eECS_SKILL = 3, // ��ų��
		/* �׿� ��Ʈ�� */
		eECS_ETC = 4, // ��Ÿ
		eEND_ECategoryString
	}; // ECategoryString 



	enum EConsumeItemEffect // �������
	{
		eBEGIN_EConsumeItemEffect = 0,
		/* ���ӽ� �������� �޴� �Ӵ��� ���� ��� ���(1000����) ���� ���consume_item_effect_value���� 500�̸� 50%�÷��� */
		eCIE_MONEYUP = 1, // ���ӸӴϹ����¾�����
		/* ���ӽ� �������� �޴� ����ġ�� ���� ��� ��� */
		eCIE_EXPUP = 2, // ����ġ�����¾�����
		/* ���ӽ� �������� �޴� �������� ���� Ȯ�� ��� */
		eCIE_ITEMDROPUP = 3, // �����۵��Ȯ����¾�����
		/* ���ӽ� ������ ������ �ִ� ������ �Ͻ������� ��� */
		eCIE_STATUPWHILE = 4, // �ɷ�ġ�Ͻû�¾�����
		/* ���ӽ� ������ ������ �ִ� ������ ���������� ��� */
		eCIE_STATUPFOREVER = 5, // �ɷ�ġ������¾�����
		/* ���ξ����� ��ȭ�� Ȯ�� ���� */
		eCIE_UPGRADELUCKYUP = 6, // ��ȭȮ������������
		/* ���ξ����� ��ȭ�� �ð� ���� */
		eCIE_UPGRADETIMEDOWN = 7, // ��ȭ�ð����Ҿ�����
		/* ��ȭ �Ϸ��� ���ξ������� ��ȭ ��� */
		eCIE_UPGRADECANCEL = 8, // ��ȭ��Ҿ�����
		/* �������� ��밡�� ������ ���� */
		eCIE_ITEMUSEDOWN = 9, // �����ۻ�밡�ɷ�������
		/* ��Ÿ. �ش�����ۺ��� ������� */
		eCIE_ETC = 10, // ETC
		eEND_EConsumeItemEffect
	}; // EConsumeItemEffect 



	enum EEventType // �������
	{
		eBEGIN_EEventType = 0,
		/* �Ӵ� */
		eET_MONEY = 1, // �Ӵ�
		/* ������ */
		eET_ITEM = 2, // ������
		/* �Ӵ�_������ */
		eET_MONEY_ITEM = 3, // �Ӵ�_������
		eEND_EEventType
	}; // EEventType 



	enum EGestureType // �������
	{
		eBEGIN_EGestureType = 0,
		/* ���� */
		eEGTT_STRAGHT = 1, // ����
		/* ������ */
		eEGTT_VERTICAL = 2, // ������
		/* � */
		eEGTT_CURVE = 3, // �
		/* ����������� */
		eEGTT_STAIR_VERTICAL = 4, // �����������
		/* ������� */
		eEGTT_S_CURVE = 5, // �������
		/* ��ȭ���� ����ó�� �������� ���� ��� */
		eEGTT_NULL = 6, // ����
		eEND_EGestureType
	}; // EGestureType 



	enum EGiftCategory // �������
	{
		eBEGIN_EGiftCategory = 0,
		/* �̱۰��ӽ� */
		eEGC_SINGLEGAMEWIN = 1, // �̱۰��ӽ�
		/* �̱۰����� */
		eEGC_SINGLEGAMELOSE = 2, // �̱۰�����
		/* �������ӽ� */
		eEGC_MATCHGAMEWIN = 3, // �������ӽ�
		/* ���������� */
		eEGC_MATCHGAMELOSE = 4, // ����������
		/* ģ�����ӽ� */
		eEGC_FRIENDGAMEWIN = 5, // ģ�����ӽ�
		/* ģ�������� */
		eEGC_FRIENDGAMELOSE = 6, // ģ��������
		/* Ʈ���̴׽� */
		eEGC_TRAININGWIN = 7, // Ʈ���̴׽�
		/* Ʈ���̴��� */
		eEGC_TRAININGLOSE = 8, // Ʈ���̴���
		eEND_EGiftCategory
	}; // EGiftCategory 



	enum EGiftType // �������
	{
		eBEGIN_EGiftType = 0,
		/* ���� */
		eEGT_NULL = 1, // ����
		/* ���ӸӴ� */
		eEGT_GAMEMONEY = 2, // ���ӸӴ�
		/* ��ų��ƼĿ */
		eEGT_PLAYERSKILLSTICKER = 3, // ��ų��ƼĿ
		/* �÷��̾�ī�� */
		eEGT_PLAYERCARD = 4, // �÷��̾�ī��
		/* ����ĳ�� */
		eEGT_GAMECASH = 5, // ���� ĳ��
		eEND_EGiftType
	}; // EGiftType 



	enum EGradeAllitemType // �������
	{
		eBEGIN_EGradeAllitemType = 0,
		/* ���� */
		eEGAT_NULL = 1, // ����
		/* S�� ���ξ����� ��� */
		eEGAT_SMAINITEMALL = 2, // S�� ���ξ����� ���
		/* A�� ���ξ����� ��� */
		eEGAT_AMAINITEMALL = 3, // A�� ���ξ����� ���
		/* B�� ���ξ����� ��� */
		eEGAT_BMAINITEMALL = 4, // B�� ���ξ����� ���
		/* C�� ���ξ����� ��� */
		eEGAT_CMAINITEMALL = 5, // C�� ���ξ����� ���
		/* D�� ���ξ����� ��� */
		eEGAT_DMAINITEMALL = 6, // D�� ���ξ����� ���
		/* E�� ���ξ����� ��� */
		eEGAT_EMAINITEMALL = 7, // E�� ���ξ����� ���
		/* S�� ��������� ��� */
		eEGAT_SSUBITEMALL = 8, // S�� ��������� ���
		/* A�� ��������� ��� */
		eEGAT_ASUBITEMALL = 9, // A�� ��������� ���
		/* B�� ��������� ��� */
		eEGAT_BSUBITEMALL = 10, // B�� ��������� ���
		/* C�� ��������� ��� */
		eEGAT_CSUBITEMALL = 11, // C�� ��������� ���
		/* D�� ��������� ��� */
		eEGAT_DSUBITEMALL = 12, // D�� ��������� ���
		/* E�� ��������� ��� */
		eEGAT_ESUBITEMALL = 13, // E�� ��������� ���
		/* S�� �Һ������ ��� */
		eEGAT_SCONSUMEITEMALL = 14, // S�� �Һ������ ���
		/* A�� �Һ������ ��� */
		eEGAT_ACONSUMEITEMALL = 15, // A�� �Һ������ ���
		/* B�� �Һ������ ��� */
		eEGAT_BCONSUMEITEMALL = 16, // B�� �Һ������ ���
		/* C�� �Һ������ ��� */
		eEGAT_CCONSUMEITEMALL = 17, // C�� �Һ������ ���
		/* D�� �Һ������ ��� */
		eEGAT_DCONSUMEITEMALL = 18, // D�� �Һ������ ���
		/* E�� �Һ������ ��� */
		eEGAT_ECONSUMEITEMALL = 19, // E�� �Һ������ ���
		eEND_EGradeAllitemType
	}; // EGradeAllitemType 



	enum EHitTimmingType // �������
	{
		eBEGIN_EHitTimmingType = 0,
		/* Ŭ���̾�Ʈ�� (���� 0_���������� ó������ ����) */
		eEHTT_eHitTime_None = 0, // Ŭ���̾�Ʈ��
		/* �ſ� ���� */
		eEHTT_eHitTime_VeryFast = 1, // �ſ� ����
		/* ���� */
		eEHTT_eHitTime_Fast = 2, // ����
		/* ���� ���� */
		eEHTT_eHitTime_GoodFast = 3, // ���� ����
		/* ����Ʈ ���� */
		eEHTT_eHitTime_Perfect = 4, // ����Ʈ ����
		/* ���� ���� */
		eEHTT_eHitTime_GoodSlow = 5, // ���� ����
		/* ���� */
		eEHTT_eHitTime_Slow = 6, // ����
		/* �ſ� ���� */
		eEHTT_eHitTime_VerySlow = 7, // �ſ� ����
		eEND_EHitTimmingType
	}; // EHitTimmingType 



	enum EHitType // �������
	{
		eBEGIN_EHitType = 0,
		/* Ŭ���̾�Ʈ�� (���� 0_���������� ó������ ����) */
		eEHT_eNS_NONE = 0, // Ŭ���̾�Ʈ��
		/* �Ϲ� ��Ʈ */
		eEHT_eNS_BALLHIT = 1, // �Ϲ� ��Ʈ
		/* ����_��Ʈ�� ��Ʈ */
		eEHT_eNS_BALLHITSTRONG = 2, // ����_��Ʈ�� ��Ʈ
		/* �꽺�� */
		eEHT_eNS_SWING = 3, // �꽺��
		/* ��� ���� */
		eEHT_eNS_NOTHING = 4, // ��� ����
		eEND_EHitType
	}; // EHitType 



	enum EItemAbilityType // �������
	{
		eBEGIN_EItemAbilityType = 0,
		/* �Ŀ� */
		eIAT_POWER = 1, // �Ŀ�
		/* ��Ȯ */
		eIAT_ACCURACY = 2, // ��Ȯ
		/* ���� */
		eIAT_FOCUS = 3, // ����
		/* ���� */
		eIAT_SPEED = 4, // ����
		/* ��ȭ�� */
		eIAT_BREAKINGBALL = 5, // ��ȭ��
		/* ��罺�� */
		eIAT_ALLABILITY = 6, // ��罺��
		/* ���� */
		eIAT_NULL = 7, // ����
		eEND_EItemAbilityType
	}; // EItemAbilityType 



	enum EItemBuyType // �������
	{
		eBEGIN_EItemBuyType = 0,
		/* ĳ�� ���� ������ */
		eIBT_BUY_CASH = 1, // ĳ�� ���� ������
		/* ����Ʈ ���� ������ */
		eIBT_BUY_POINT = 2, // ����Ʈ ���� ������
		/* ĳ��OR����Ʈ���ž������ε� �ͼӵȻ��� */
		eIBT_BUY_USED = 3, // ĳ���ͼӾ�����
		/* �̺�Ʈ���޾����� */
		eIBT_EVENT = 4, // �̺�Ʈ ���޾�����
		/* Ʈ���̴� or ��⺸�� ���޾����� */
		eIBT_REWARD = 5, // ��⺸�����ι���
		eEND_EItemBuyType
	}; // EItemBuyType 



	enum EItemCategory // �������
	{
		eBEGIN_EItemCategory = 0,
		/* ������� */
		eIC_EQUIP = 1, // �������
		/* �Ҹ������ */
		eIC_CONSUME = 2, // �Ҹ������
		/* �������� */
		eIC_STUFF = 3, // ��������
		/* ���� */
		eIC_NULL = 4, // ����
		eEND_EItemCategory
	}; // EItemCategory 



	enum EItemCategoryEquipment // �������
	{
		eBEGIN_EItemCategoryEquipment = 0,
		/* ���� */
		eICE_SHIRT = 1, // ����
		/* ���� */
		eICE_PANT = 2, // ����
		/* ���� ���ξ�����# */
		eICE_CAP = 3, // ����
		/* Ÿ�� �Ź� ���ξ�����# */
		eICE_SHOES_B = 4, // Ÿ�� �Ź�
		/* ���� �Ź� ���ξ�����# */
		eICE_SHOES_P = 5, // ���� �Ź�
		/* �����۷��� ���ξ�����# */
		eICE_GLOVE = 6, // �����۷���
		/* ������� */
		eICE_U_SHIRT = 7, // �������
		/* �縻 */
		eICE_SOCKS = 8, // �縻
		/* ��_��ȣ�� */
		eICE_ARM_GUARDS = 9, // ��_��ȣ��
		/* �ٸ�_��ȣ�� */
		eICE_LEG_GUARDS = 10, // �ٸ�_��ȣ��
		/* ��Ʈ ���ξ����� */
		eICE_BAT = 11, // ��Ʈ
		/* �� ���ξ�����# */
		eICE_BALL = 12, // ��
		/* ��� ���ξ�����# */
		eICE_HELMET = 13, // ���
		/* Ÿ�ڿ� �尩 ���ξ�����# */
		eICE_GLOBE = 14, // Ÿ���尩
		/* �ո� �ƴ� */
		eICE_WRISTBAND = 15, // ����Ʈ ���
		/* ����� */
		eICE_NECKLACE = 16, // �����
		/* ���� */
		eICE_RING = 17, // ����
		/* �Ͱ��� */
		eICE_EARRING = 18, // �Ͱ���
		/* ���� */
		eICE_TATOO = 19, // ����
		/* ���۶� */
		eICE_SUNGLASS = 20, // ���۶�
		/* �� �� ��ġ */
		eICE_EYEPATCH = 21, // ������ġ
		/* ���� */
		eICE_BEARD = 22, // ����
		/* ������Ÿ�� */
		eICE_HAIR_M = 23, // ������Ÿ��
		/* ������Ÿ�� */
		eICE_HAIR_W = 24, // ������Ÿ��
		/* ���Į�� */
		eICE_HAIR_COLOR = 25, // ���Į��
		/* ��ġ */
		eICE_PATCH = 26, // ��ġ
		/* ����ũ */
		eICE_MASK = 27, // ����ũ
		/* ���ȣ ������ */
		eICE_BACKNUMBER = 28, // ���ȣ ������
		/* ��ŷ ������ */
		eICE_MAKING = 29, // ��ŷ ������
		/* �� */
		eICE_FACE = 30, // ��
		/* �� */
		eICE_ARM = 31, // ��
		/* �ٸ�(����) */
		eICE_LEG = 32, // �ٸ�(����)
		/* �޼� */
		eICE_LEFTHAND = 33, // �޼�
		/* ������ */
		eICE_RIGHTHAND = 34, // ������
		eEND_EItemCategoryEquipment
	}; // EItemCategoryEquipment 



	enum EItemGradeType // �������
	{
		eBEGIN_EItemGradeType = 0,
		/* E - EE �� ���۰��� */
		eIGT_E = 1, // E���
		/* D - DE #  DD�� ���۰��� */
		eIGT_D = 2, // D���
		/* C - CE # CD# CC�� ���۰��� */
		eIGT_C = 3, // C���
		/* B- BE# BD# BC# BB�� ���۰��� */
		eIGT_B = 4, // B���
		/* A- AE# AD# AC# AB# AA�� ���۰��� */
		eIGT_A = 5, // A���
		/* S-SE# SD# SC# SB# SA# SS�� ���۰��� */
		eIGT_S = 6, // S���
		/* ��޾���.  ���ڷ��̼� �����ۡ� */
		eIGT_NULL = 7, // �����
		eEND_EItemGradeType
	}; // EItemGradeType 



	enum EItemPriceType // �������
	{
		eBEGIN_EItemPriceType = 0,
		/* ĳ�� �θ� ����ִ� ������ */
		eIPT_CASH = 1, // ĳ��
		/* ĳ�� �Ǵ� ����Ʈ �� ��� �ִ� ������ */
		eIPT_CASH_POINT = 2, // ĳ��_����Ʈ
		/* ĳ�� �Ǵ� ����Ʈ# ���ӸӴϷ� ��� �ִ� ������ */
		eIPT_MONEY = 3, // ����Ʈ
		eEND_EItemPriceType
	}; // EItemPriceType 



	enum EItemReuseType // �������
	{
		eBEGIN_EItemReuseType = 0,
		/* ���� */
		eIUT_NORMAL = 1, // ����
		/* �Ⱓ�� Ƚ�� ���� �� ������ �� ��� */
		eIUT_INSTANTLY = 2, // �Ⱓ��
		/* �Ұ� */
		eIUT_FIXED = 3, // �Ұ�
		eEND_EItemReuseType
	}; // EItemReuseType 



	enum EItemSellStatus // �������
	{
		eBEGIN_EItemSellStatus = 0,
		/* �Ǹ�����( �Ǹ��ϴٰ� ��å�� ���� ������) */
		eISS_SELL_STOP = 1, // �Ǹ�����
		/* �Ǹ��� */
		eISS_SELL = 2, // �Ǹ���
		/* �Ǹſ��� */
		eISS_SELL_PLAN = 3, // �Ǹſ���
		eEND_EItemSellStatus
	}; // EItemSellStatus 



	enum EItemSexType // �������
	{
		eBEGIN_EItemSexType = 0,
		eIST_MAN_ONLY = 1, // ��
		eIST_WOMAN_ONLY = 2, // ��
		eIST_COMMON = 3, // ����
		eEND_EItemSexType
	}; // EItemSexType 



	enum EItemState // (�������� �Һ� ������ ���� �� ���������� ������ ����)
	{
		eBEGIN_EItemState = 0,
		/* �Ϲݻ��� */
		eIS_NORMAL = 1, // �Ϲݻ���
		/* �����Ȼ��� */
		eIS_DELETE = 2, // �����Ȼ���
		/* ���Ұ���. */
		eIS_ADMIN_BLOCKED = 3, // ���Ұ���.
		/* ���ȱ�Ǿ� ������ */
		eIS_DELETE_REFUND = 4, // ���ȱ�Ǿ� ������
		eEND_EItemState
	}; // EItemState 



	enum EItemSubGradeType // �������
	{
		eBEGIN_EItemSubGradeType = 0,
		/* EE��� */
		eISGT_EE = 1, // EE���
		/* DE��� */
		eISGT_DE = 2, // DE���
		/* DD��� */
		eISGT_DD = 3, // DD���
		/* CE��� */
		eISGT_CE = 4, // CE���
		/* CD��� */
		eISGT_CD = 5, // CD���
		/* CC��� */
		eISGT_CC = 6, // CC���
		/* BE��� */
		eISGT_BE = 7, // BE���
		/* BD��� */
		eISGT_BD = 8, // BD���
		/* BC��� */
		eISGT_BC = 9, // BC���
		/* BB��� */
		eISGT_BB = 10, // BB���
		/* AE��� */
		eISGT_AE = 11, // AE���
		/* AD��� */
		eISGT_AD = 12, // AD���
		/* AC��� */
		eISGT_AC = 13, // AC���
		/* AB��� */
		eISGT_AB = 14, // AB���
		/* AA��� */
		eISGT_AA = 15, // AA���
		/* SE��� */
		eISGT_SE = 16, // SE���
		/* SD��� */
		eISGT_SD = 17, // SD���
		/* SC��� */
		eISGT_SC = 18, // SC���
		/* SB��� */
		eISGT_SB = 19, // SB���
		/* SA��� */
		eISGT_SA = 20, // SA���
		/* SS��� */
		eISGT_SS = 21, // SS���
		/* ��޾���(NULL�� ��� �ش� ����� ����) */
		eISGT_NULL = 22, // ��޾���
		eEND_EItemSubGradeType
	}; // EItemSubGradeType 



	enum EItemUpgradeResult // �������
	{
		eBEGIN_EItemUpgradeResult = 0,
		/* ��� */
		eIUR_HELMET = 1, // ���
		/* ���� */
		eIUR_CAP = 2, // ����
		/* ��Ʈ */
		eIUR_BET = 3, // ��Ʈ
		/* �� */
		eIUR_BALL = 4, // ��
		/* Ÿ���尩 */
		eIUR_GLOBE = 5, // Ÿ���尩
		/* �۷��� */
		eIUR_GLOVE = 6, // �۷���
		/* �Ź� */
		eIUR_SHOES = 7, // �Ź�
		eEND_EItemUpgradeResult
	}; // EItemUpgradeResult 



	enum ELogType // �������
	{
		eBEGIN_ELogType = 0,
		/* �α�1 */
		eSCT_KINGROOKIE = 1, // �α�1
		/* �α�2 */
		eSCT_ROOKIE = 2, // �α�2
		/* �α�3 */
		eSCT_AMA1 = 3, // �α�3
		/* �α�4 */
		eSCT_AMA2 = 4, // �α�4
		/* �α�5 */
		eSCT_PRO = 5, // �α�5
		eEND_ELogType
	}; // ELogType 



	enum ENoticeType // �������
	{
		eBEGIN_ENoticeType = 0,
		/* ������ */
		eNT_LED = 1, // ������
		/* �ӽ����� */
		eNT_CHECK = 2, // �ӽ�����
		/* �������� */
		eNT_NOTICE = 3, // ��������
		eEND_ENoticeType
	}; // ENoticeType 



	enum ENpcSituationString // �������
	{
		eBEGIN_ENpcSituationString = 0,
		/* ����� �Ͻ� ��� */
		eENSS_STANDING_BY = 1, // �����
		/* ���ý� ��� */
		eENSS_SELECTION = 2, // ���� ��
		/* ���׷��̵� �� �Ͻ� ��� */
		eENSS_UPGRADE_WORKING = 3, // ���׷��̵� ��
		/* Ʈ���̴� �� �Ͻ� ��� */
		eENSS_TRANING_WORKING = 4, // Ʈ���̴� ��
		/* �Ϸ� �ÿ� ��� */
		eENSS_COMPLETE = 5, // �Ϸ�
		/* ���׷��̵� ���  ��� */
		eENSS_UPGRADE_RESULT = 6, // ���׷��̵� ���
		/* Ʈ���̴� ���  ��� */
		eENSS_TRANING_RESULT = 7, // Ʈ���̴� ���
		eEND_ENpcSituationString
	}; // ENpcSituationString 



	enum ENpcString // �������
	{
		eBEGIN_ENpcString = 0,
		/* ���� */
		eENS_MAESTRO = 1, // ����
		/* ������ġ */
		eENS_COACH = 2, // ������ġ
		eEND_ENpcString
	}; // ENpcString 



	enum EPitcherAbility // �������
	{
		eBEGIN_EPitcherAbility = 0,
		/* ���� */
		ePA_NULL = 1, // ����
		/* ��Ÿ�ڻ��� �ɷ�ġ����. PA_RIGHT�Ӽ��� ��ų ��ƼĿ�� ���������� */
		ePA_LEFT = 2, // ����Ÿ��
		/* ��Ÿ�ڻ��� �ɷ�ġ����. PA_LEFT�Ӽ��� ��ų ��ƼĿ�� ������ ���� */
		ePA_RIGHT = 3, // ���Ÿ��
		/* ���� ���� */
		ePA_FASTBALL = 4, // �ӱ���
		/* ��ȭ�� �� ���� */
		ePA_FULLSKILL = 5, // �ⱳ��
		/* �ٷ� ���� Ÿ������ ��Ʈ���� ������  ���� �� ���� ���� */
		ePA_RUNFIRE = 6, // ����
		/* ���� ������ ���� �ٿ� ���� */
		ePA_SWORDCON = 7, // Į����
		/* 2���� ��Ʈ���� ������ ���� �� ���� ���� */
		ePA_DOCK = 8, // ����K
		/* Ÿ���� �������� ���� ������ ���� ���� */
		ePA_INFIGHT = 9, // ��������
		/* Ÿ���� �ٱ������� ���� ������ ���� ���� */
		ePA_OUTFIGHT = 10, // �ƿ�������
		eEND_EPitcherAbility
	}; // EPitcherAbility 



	enum EPitcherForm // �������
	{
		eBEGIN_EPitcherForm = 0,
		/* ���� */
		ePF_OVER = 1, // ����
		/* �������� */
		ePF_THREEQUARTER = 2, // ��������
		/* ���̵�� */
		ePF_SIDEARM = 3, // ���̵��
		/* ��� */
		ePF_UNDER = 4, // ���
		/* ���� */
		ePF_NULL = 5, // ����
		/* ���� */
		ePF_COMMON = 6, // ����
		eEND_EPitcherForm
	}; // EPitcherForm 



	enum EPlayer_Onoffline // �������
	{
		eBEGIN_EPlayer_Onoffline = 0,
		/* �¶����÷��̾� */
		eEPO_ONPLAYER = 1, // �¶����÷��̾�
		/* ���������÷��̾� */
		eEPO_OFFPLAYER = 2, // ���������÷��̾�
		eEND_EPlayer_Onoffline
	}; // EPlayer_Onoffline 



	enum EPlayerBodyType // �������
	{
		eBEGIN_EPlayerBodyType = 0,
		/* ���� */
		eEPBT_SMALL = 1, // ����
		/* �̵�� */
		eEPBT_MIDIUM = 2, // �̵��
		/* ���� */
		eEPBT_LARGE = 3, // ����
		/* ���� */
		eEPBT_WOMAN = 4, // ����
		eEND_EPlayerBodyType
	}; // EPlayerBodyType 



	enum EPlayerBreakingBall // �������
	{
		eBEGIN_EPlayerBreakingBall = 0,
		/* ���� */
		ePBB_NULL = 1, // ����
		/* ���� */
		ePBB_FOURSEAM = 2, // ����
		/* ���� */
		ePBB_TWOSEAM = 3, // ����
		/* ����¡�н�Ʈ�� */
		ePBB_RISINGFAST = 4, // ����¡�н�Ʈ��
		/* ���� */
		ePBB_UPSHOUT = 5, // ����
		/* �����̴� */
		ePBB_SLIDER = 6, // �����̴�
		/* H�����̴� */
		ePBB_HSLIDER = 7, // H�����̴�
		/* ���н�Ʈ�� */
		ePBB_CUTFAST = 8, // ���н�Ʈ��
		/* V�����̴� */
		ePBB_VSLIDER = 9, // V�����̴�
		/* ������ */
		ePBB_SLUB = 10, // ������
		/* ü������ */
		ePBB_CHANGEUP = 11, // ü������
		/* ��Ŭü������ */
		ePBB_CIRCLECHANGEUP = 12, // ��Ŭü������
		/* ��Ŭ */
		ePBB_KNUCKLE = 13, // ��Ŭ
		/* Ŀ�� */
		ePBB_CURVE = 14, // Ŀ��
		/* ���ο�Ŀ�� */
		ePBB_SLOWCURVE = 15, // ���ο�Ŀ��
		/* ��ŬĿ�� */
		ePBB_KNUCKLECURVE = 16, // ��ŬĿ��
		/* ���Ŀ�� */
		ePBB_DROPCURVE = 17, // ���Ŀ��
		/* �Ŀ�Ŀ�� */
		ePBB_POWERCURVE = 18, // �Ŀ�Ŀ��
		/* ��Ʈ */
		ePBB_SHOUT = 19, // ��Ʈ
		/* H��Ʈ */
		ePBB_HSHOUT = 20, // H��Ʈ
		/* ��ũ */
		ePBB_FORK = 21, // ��ũ
		/* �� */
		ePBB_PALM = 22, // ��
		/* SFF */
		ePBB_SFF = 23, // SFF
		/* ��Ŀ#  ��ũ�� */
		ePBB_SINKER = 24, // ��Ŀ_ ��ũ��
		/* H��Ŀ */
		ePBB_HSINKER = 25, // H��Ŀ
		eEND_EPlayerBreakingBall
	}; // EPlayerBreakingBall 



	enum EPlayerGradeType // �������
	{
		eBEGIN_EPlayerGradeType = 0,
		/* E��� ���� */
		ePGT_E = 1, // E���
		/* D��� ���� */
		ePGT_D = 2, // D���
		/* C��� ���� */
		ePGT_C = 3, // C���
		/* B��� ���� */
		ePGT_B = 4, // B���
		/* A��� ���� */
		ePGT_A = 5, // A���
		/* S��� ���� */
		ePGT_S = 6, // S���
		eEND_EPlayerGradeType
	}; // EPlayerGradeType 



	enum EPlayerNationType // �������
	{
		eBEGIN_EPlayerNationType = 0,
		/* �ѱ� */
		ePNT_KOREA = 1, // �ѱ�
		/* �̱� */
		ePNT_USA = 2, // �̱�
		/* �Ϻ� */
		ePNT_JAPAN = 3, // �Ϻ�
		/* �߱� */
		ePNT_CHINA = 4, // �߱�
		/* ĳ���� */
		ePNT_CANADA = 5, // ĳ����
		/* ��Ż���� */
		ePNT_ITALY = 6, // ��Ż����
		/* �븸 */
		ePNT_TAIWAN = 7, // �븸
		/* ȣ�� */
		ePNT_AUSTRALIA = 8, // ȣ��
		/* �״����� */
		ePNT_NETHERLANDS = 9, // �״�����
		/* ��� */
		ePNT_CUBA = 10, // ���
		/* Ʈ���ϴٵ���ٰ� */
		ePNT_TRINIDADANDTOBAGO = 11, // Ʈ���ϴٵ���ٰ�
		/* ���̴�ī��ȭ�� */
		ePNT_DOMINICANREPUBLIC = 12, // ���̴�ī��ȭ��
		/* �ĳ��� */
		ePNT_PANAMA = 13, // �ĳ���
		/* Ǫ�����丮�� */
		ePNT_PUERTORICO = 14, // Ǫ�����丮��
		/* ��������ī��ȭ�� */
		ePNT_REPUBLICOFSOUTHAFRICA = 15, // ��������ī��ȭ��
		/* ���׼����� */
		ePNT_VENEZUELA = 16, // ���׼�����
		/* ���� */
		ePNT_UNITEDKINGDOM = 17, // ����
		/* ������ */
		ePNT_SPAIN = 18, // ������
		/* ������ */
		ePNT_FRANCE = 19, // ������
		/* ���� */
		ePNT_GERMANY = 20, // ����
		eEND_EPlayerNationType
	}; // EPlayerNationType 



	enum EPlayerType // (������ ������ Ŭ���̾�Ʈ ��Ŵ��)
	{
		eBEGIN_EPlayerType = 0,
		/* Ÿ�� */
		ePT_BATTER = 1, // Ÿ��
		/* ���� */
		ePT_PITCHER = 2, // ����
		/* Ÿ���������о��� */
		ePT_COMMON = 3, // ����
		/* ���� */
		ePT_CATCHER = 4, // ����
		/* ���� */
		ePT_UMPIRE = 5, // ����
		eEND_EPlayerType
	}; // EPlayerType 



	enum EQuestConditionType // �������
	{
		eBEGIN_EQuestConditionType = 0,
		/* ���� */
		eQCT_NULL = 1, // ����
		/* ��ü������������� condition1�� �ִ� ���� ����(EItemGradeType)�� �ش��ϸ� ������ �ش� */
		eQCT_EQUIPGRADETYPE = 12, // ��ü�����������
		/* ĳ���۱������� */
		eQCT_CASHCOUNT = 13, // ĳ���۱�������
		/* ���ӸӴϴ������� */
		eQCT_GAMEMONEYCOUNT = 14, // ���ӸӴϴ�������
		/* ĳ���͸��ɷ�ġ�޼�����. ���Ҽ��� ����Ÿ�ڰ� ���ÿ� �ش� �ɷ�ġ ���޽� �ش�. pitcher_breakingball�� ���ǿ��� ���� */
		eQCT_PLAYERALLSTATCOUNT = 15, // ĳ���͸��ɷ�ġ�޼�����
		/* ������ ���ӳ������� ����. ���Ӻ����� ���������Ͻÿ� */
		eQCT_GAME_VALIABLE = 16, // ���Ӻ���
		/* Ʃ�丮�� or ��������Ʈ�� �Ϸ������� EQuestType������ ������.�Ϸ��뺸 */
		eQCT_MANUAL_FINISH = 17, // ���ǿϷ�
		eEND_EQuestConditionType
	}; // EQuestConditionType 



	enum EQuestType // �������
	{
		eBEGIN_EQuestType = 0,
		/* MATCH ����Ʈ */
		eEQT_MATCH = 1, // MATCH ����Ʈ
		/* SINGLE ����Ʈ */
		eEQT_SINGLE = 2, // SINGLE ����Ʈ
		/* FRIENDLY ����Ʈ */
		eEQT_FRIENDLY = 3, // FRIENDLY ����Ʈ
		/* ITEM_ETC ����Ʈ */
		eEQT_ITEMETC = 4, // ITEM_ETC ����Ʈ
		/* �ΰ��� Ʃ�丮��. �Ϸ������� Ŭ���̾�Ʈ�� üũ�� ������.(x2ug_quest_end) */
		eEQT_INGAMETUTORIAL = 5, // TUTORIAL
		/* DAILIY ����Ʈ. (���� condition_value1�ǰ��� 0~100������ Ȯ�������� �ǹ��Ѵ�.) */
		eEQT_DAILY = 6, // DAILY ����Ʈ
		eEND_EQuestType
	}; // EQuestType 



	enum ERhythmJudge // �������
	{
		eBEGIN_ERhythmJudge = 0,
		/* Ŭ���̾�Ʈ�� (���� 0_���������� ó������ ����) */
		eERJ_eJudge_None = 0, // Ŭ���̾�Ʈ��
		/* ��� */
		eERJ_eJudge_Bad = 1, // ���
		/* ��� */
		eERJ_eJudge_Normal = 2, // ���
		/* �� */
		eERJ_eJudge_Good = 3, // ��
		/* ����Ʈ */
		eERJ_eJudge_Perfect = 4, // ����Ʈ
		eEND_ERhythmJudge
	}; // ERhythmJudge 



	enum EShopBatterSection // (�������� ��� ���ÿ��� Ÿ�� �ϰ�� ���������� ������ ����)
	{
		eBEGIN_EShopBatterSection = 0,
		/* ���� */
		eESBS_NULL = 1, // ����
		/* ���� ���� A(Ÿ��=���) */
		eESBS_A = 2, // ���� A
		/* ���� ���� B(Ÿ��=��Ʈ) */
		eESBS_B = 3, // ���� B
		/* ���� ���� C(Ÿ��=�尩) */
		eESBS_C = 4, // ���� C
		/* ���� ���� D(Ÿ��=�Ź�) */
		eESBS_D = 5, // ���� D
		/* ���� ���� E(Ÿ��=����#  ����) */
		eESBS_E = 6, // ���� E
		/* ���� ���� F(Ÿ��=�縻#  ����Ʈ���) */
		eESBS_F = 7, // ���� F
		/* ���� ���� G(Ÿ��=�Ⱥ�ȣ��#  �ٸ���ȣ��) */
		eESBS_G = 8, // ���� G
		/* ���� ���� H(Ÿ��=�����# ����#  �Ͱ���) */
		eESBS_H = 9, // ���� H
		/* ���� ���� I(Ÿ��=(����#  ���۶�#  ������ġ) */
		eESBS_I = 10, // ���� I
		/* ���� ���� J(Ÿ��=(����#  ���#  ��ġ#  ����ũ#  ���ȣ#  ��ŷ#  ����÷�) */
		eESBS_J = 11, // ���� J
		eEND_EShopBatterSection
	}; // EShopBatterSection 



	enum EShopConsumeSection // (�������� �Һ� ������ ���� �� ���������� ������ ����)
	{
		eBEGIN_EShopConsumeSection = 0,
		/* ���� */
		eESCS_NULL = 1, // ����
		/* ���� ���� A(�Һ�=���� ������) */
		eESCS_A = 2, // ���� A
		/* ���� ���� B(�Һ�=���� ������� ������) */
		eESCS_B = 3, // ���� B
		/* ���� ���� C(�Һ�=���׷��̵� ���� ������) */
		eESCS_C = 4, // ���� C
		/* ���� ���� D(�Һ�=������ ���� ����#  ��ȭ ��� ������) */
		eESCS_D = 5, // ���� D
		/* ���� ���� E(�Һ�=��Ű�� ������) */
		eESCS_E = 6, // ���� E
		eEND_EShopConsumeSection
	}; // EShopConsumeSection 



	enum EShopItemType // �������
	{
		eBEGIN_EShopItemType = 0,
		/* ��Ű�� */
		eESIT_Sys_Package = 1, // ��Ű��
		/* ���������� */
		eESIT_Sys_ItemEquip = 2, // ����������
		/* �������� */
		eESIT_Sys_ItemStuff = 3, // ��������
		/* �Ҹ������ */
		eESIT_Sys_ItemConsume = 4, // �Ҹ������
		/* ��ȭ��������(��ȭ�� ���� �� ��ȭ���� ���ѵǾ��ִ� ���� �����ϰ� ���� ����#  ��ȭ�� ���׷��̵�--)���� ��ȭ�� ����� ����(--�� �״�� ����) */
		eESIT_Sys_PlayerSkillSticker = 5, // ��ȭ��������
		eEND_EShopItemType
	}; // EShopItemType 



	enum EShopPitcherSection // (�������� ��� ���ÿ��� ���� �ϰ�� ���� �� ���������� ������ ����)
	{
		eBEGIN_EShopPitcherSection = 0,
		/* ���� */
		eESPS_NULL = 1, // ����
		/* ���� ���� A(����=����) */
		eESPS_A = 2, // ���� A
		/* ���� ���� B(����=��) */
		eESPS_B = 3, // ���� B
		/* ���� ���� C(����=�۷���) */
		eESPS_C = 4, // ���� C
		/* ���� ���� D(����=�Ź�) */
		eESPS_D = 5, // ���� D
		/* ���� ���� E(����=����#  ����) */
		eESPS_E = 6, // ���� E
		/* ���� ���� E(����=�縻#  ����Ʈ���) */
		eESPS_F = 7, // ���� F
		/* ���� ���� F (����=�����# ����#  �Ͱ���) */
		eESPS_G = 8, // ���� G
		/* ���� ���� H(����=����#  ���۶�#  ������ġ) */
		eESPS_H = 9, // ���� H
		/* ���� ���� I(����=����#  ���#  ��ġ#  ����ũ#  ���ȣ#  ��ŷ#  ����÷�) */
		eESPS_I = 10, // ���� I
		eEND_EShopPitcherSection
	}; // EShopPitcherSection 



	enum ETotalGameType // �������
	{
		eBEGIN_ETotalGameType = 0,
		/* ��ġ */
		eTGT_Match = 1, // ��ġ
		/* �̱� */
		eTGT_Single = 2, // �̱�
		/* �����鸮 */
		eTGT_Friendly = 3, // �����鸮
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
