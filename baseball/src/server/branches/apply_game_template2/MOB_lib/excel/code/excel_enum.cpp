/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_enum.h"



//현제 모듈의 Sys테이블에 대해 배열형 필드를 사용할때는 아래 코드를 구현해야 한다.
#if 0

#ifndef jNOT_USE_SQ_BIND_CODE
#endif //jNOT_USE_SQ_BIND_CODE


namespace nMech
{
	namespace nEXCEL
	{
	}//namespace nEXCEL
}//namespace nMech
#endif //구현되어야 하는 코드 끝.

#ifndef jNOT_USE_SQ_BIND_CODE

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_enum_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_enum_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_enum_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE


for_each_nEXCEL_excel_enum_ENUM(jEXCEL_SQ_DECLARE_ENUM_TYPE);
namespace nMech {
	namespace nEXCEL {

jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBaseballObjectType[] = 
{
	{ 4 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EBaseballObjectType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBatterAbility[] = 
{
	{ 9 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EBatterAbility_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBatterForm[] = 
{
	{ 5 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EBatterForm_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBatterHitType[] = 
{
	{ 12 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EBatterHitType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBreakingBallPitch[] = 
{
	{ 4 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EBreakingBallPitch_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBreakingBallRotation[] = 
{
	{ 3 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EBreakingBallRotation_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ECategoryString[] = 
{
	{ 4 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_ECategoryString_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EConsumeItemEffect[] = 
{
	{ 10 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EConsumeItemEffect_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EEventType[] = 
{
	{ 3 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EEventType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EGestureType[] = 
{
	{ 6 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EGestureType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EGiftCategory[] = 
{
	{ 8 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EGiftCategory_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EGiftType[] = 
{
	{ 5 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EGiftType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EGradeAllitemType[] = 
{
	{ 19 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EGradeAllitemType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHitTimmingType[] = 
{
	{ 8 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EHitTimmingType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHitType[] = 
{
	{ 5 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EHitType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemAbilityType[] = 
{
	{ 7 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EItemAbilityType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemBuyType[] = 
{
	{ 5 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EItemBuyType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemCategory[] = 
{
	{ 4 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EItemCategory_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemCategoryEquipment[] = 
{
	{ 34 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EItemCategoryEquipment_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemGradeType[] = 
{
	{ 7 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EItemGradeType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemPriceType[] = 
{
	{ 3 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EItemPriceType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemReuseType[] = 
{
	{ 3 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EItemReuseType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemSellStatus[] = 
{
	{ 3 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EItemSellStatus_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemSexType[] = 
{
	{ 3 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EItemSexType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemState[] = 
{
	{ 4 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EItemState_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemSubGradeType[] = 
{
	{ 22 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EItemSubGradeType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemUpgradeResult[] = 
{
	{ 7 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EItemUpgradeResult_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ELogType[] = 
{
	{ 5 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_ELogType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ENoticeType[] = 
{
	{ 3 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_ENoticeType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ENpcSituationString[] = 
{
	{ 7 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_ENpcSituationString_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ENpcString[] = 
{
	{ 2 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_ENpcString_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPitcherAbility[] = 
{
	{ 10 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EPitcherAbility_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPitcherForm[] = 
{
	{ 6 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EPitcherForm_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPlayer_Onoffline[] = 
{
	{ 2 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EPlayer_Onoffline_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPlayerBodyType[] = 
{
	{ 4 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EPlayerBodyType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPlayerBreakingBall[] = 
{
	{ 25 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EPlayerBreakingBall_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPlayerGradeType[] = 
{
	{ 6 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EPlayerGradeType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPlayerNationType[] = 
{
	{ 20 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EPlayerNationType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPlayerType[] = 
{
	{ 5 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EPlayerType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EQuestConditionType[] = 
{
	{ 16 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EQuestConditionType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EQuestType[] = 
{
	{ 6 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EQuestType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ERhythmJudge[] = 
{
	{ 5 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_ERhythmJudge_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EShopBatterSection[] = 
{
	{ 11 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EShopBatterSection_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EShopConsumeSection[] = 
{
	{ 6 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EShopConsumeSection_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EShopItemType[] = 
{
	{ 5 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EShopItemType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EShopPitcherSection[] = 
{
	{ 10 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_EShopPitcherSection_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ETotalGameType[] = 
{
	{ 3 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nEXCEL_ETotalGameType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};

} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_enum)
		{
			{
				SquirrelObject enumRoot= nSQ::jSQ_GetEnumTable();
				for_each_nEXCEL_excel_enum_ENUM(jEXCEL_SQ_bind_EnumField_BEGIN);
				for_each_nEXCEL_EBaseballObjectType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EBatterAbility_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EBatterForm_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EBatterHitType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EBreakingBallPitch_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EBreakingBallRotation_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_ECategoryString_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EConsumeItemEffect_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EEventType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EGestureType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EGiftCategory_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EGiftType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EGradeAllitemType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EHitTimmingType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EHitType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EItemAbilityType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EItemBuyType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EItemCategory_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EItemCategoryEquipment_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EItemGradeType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EItemPriceType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EItemReuseType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EItemSellStatus_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EItemSexType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EItemState_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EItemSubGradeType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EItemUpgradeResult_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_ELogType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_ENoticeType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_ENpcSituationString_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_ENpcString_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EPitcherAbility_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EPitcherForm_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EPlayer_Onoffline_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EPlayerBodyType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EPlayerBreakingBall_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EPlayerGradeType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EPlayerNationType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EPlayerType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EQuestConditionType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EQuestType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_ERhythmJudge_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EShopBatterSection_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EShopConsumeSection_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EShopItemType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_EShopPitcherSection_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nEXCEL_ETotalGameType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
			}
		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

