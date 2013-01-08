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
	ENUM_TABLE(EAvatarClass,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EBuildType_test,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EBuildTypeTest,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EOutput_test,설명없음,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// 주의 enum변수는 앞에 e가 자동으로 붙어서 선언됨 
	// -------------------------------------------------

	/* 설명없음 */
	#define for_each_nEXCEL_EAvatarClass_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(AC_MERCENARY			,1,용병,nMech,nEXCEL,EAvatarClass)\
		ENUM_FIELD(AC_WIZARD			,2,마법사,nMech,nEXCEL,EAvatarClass)\
		ENUM_FIELD(AC_FIGHTER			,3,격투가,nMech,nEXCEL,EAvatarClass)\
		ENUM_FIELD(AC_ALL			,4,모든 클래스,nMech,nEXCEL,EAvatarClass)\

	/* 설명없음 */
	#define for_each_nEXCEL_EBuildType_test_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EBTTT_Sys_T_HQ			,1,본영,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_Sys_T_Bar			,2,주점,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_ACADEMY			,3,서원,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_PEACE			,4,치안부,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_SHRINE			,5,사당,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_HIDEOUT			,6,감찰부,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_TRADINGPOST			,7,교역소,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_Sys_T_House			,8,민가,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_Sys_T_Farm			,9,농지,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_SAWMILL			,10,제재소,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_QUARRY			,11,채석장,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_MINING			,12,광업장,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_COCOONERY			,13,양잠소,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_Sys_T_Barrack			,14,병영,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_SMITHY			,15,대장간,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_FORGE			,16,공방,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_STABLE			,17,마구간,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_Sys_T_Camp			,18,둔영,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_Sys_T_Depot			,19,창고,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_SECRET			,20,비밀창고,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_TOWER			,21,망루,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_BARRIER			,22,방벽,nMech,nEXCEL,EBuildType_test)\

	/* 설명없음 */
	#define for_each_nEXCEL_EBuildTypeTest_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ETT_Sys_T_HQ			,1,본영,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_Sys_T_Bar			,2,주점,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_ACADEMY			,3,서원,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_PEACE			,4,치안부,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_SHRINE			,5,사당,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_HIDEOUT			,6,감찰부,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_TRADINGPOST			,7,교역소,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_Sys_T_House			,8,민가,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_Sys_T_Farm			,9,농지,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_SAWMILL			,10,제재소,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_QUARRY			,11,채석장,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_MINING			,12,광업장,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_COCOONERY			,13,양잠소,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_Sys_T_Barrack			,14,병영,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_SMITHY			,15,대장간,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_FORGE			,16,공방,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_STABLE			,17,마구간,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_Sys_T_Camp			,18,둔영,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_Sys_T_Depot			,19,창고,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_SECRET			,20,비밀창고,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_TOWER			,21,망루,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_BARRIER			,22,방벽,nMech,nEXCEL,EBuildTypeTest)\

	/* 설명없음 */
	#define for_each_nEXCEL_EOutput_test_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EOTTT_POPULATION			,1,인구,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_GOLD			,2,금,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_FOOD			,3,식량,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_TREE			,4,목재,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_STONE			,5,석재,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_IRON			,6,철재,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_SILK			,7,비단,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_SOLDIER			,8,병사,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_PIKE			,9,창 병기,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_HEAVY			,10,중갑 병기,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_HALBERD			,11,언월도 병기,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_BOW			,12,궁 병기,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_CROSSBOW			,13,노 병기,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_BOWGUN			,14,강노 병기,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_BALLISTA			,15,노포 병기,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_CHARIOT			,16,전차 병기,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_WAGON			,17,마차,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_HORSE			,18,군마,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_WHEELBARROW			,19,수레,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_CART			,20,목우,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_SIEGE_LADDER			,21,운제,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_SIEGE_RAM			,22,충차,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_SIEGE_TOWER			,23,정란,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_SIEGE_TREBUCHET			,24,투석기,nMech,nEXCEL,EOutput_test)\


// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum EAvatarClass // 설명없음
	{
		eBEGIN_EAvatarClass = 0,
		/* 상위 직업군 */
		eAC_MERCENARY = 1, // 용병
		eAC_WIZARD = 2, // 마법사
		eAC_FIGHTER = 3, // 격투가
		/* 모든 직업(상위, 하위 포함) */
		eAC_ALL = 4, // 모든 클래스
		eEND_EAvatarClass
	}; // EAvatarClass 



	enum EBuildType_test // 설명없음
	{
		eBEGIN_EBuildType_test = 0,
		/* 본영 */
		eEBTTT_Sys_T_HQ = 1, // 본영
		/* 주점 */
		eEBTTT_Sys_T_Bar = 2, // 주점
		/* 서원 */
		eEBTTT_ACADEMY = 3, // 서원
		/* 치안부 */
		eEBTTT_PEACE = 4, // 치안부
		/* 사당 */
		eEBTTT_SHRINE = 5, // 사당
		/* 감찰부 */
		eEBTTT_HIDEOUT = 6, // 감찰부
		/* 교역소 */
		eEBTTT_TRADINGPOST = 7, // 교역소
		/* 민가 */
		eEBTTT_Sys_T_House = 8, // 민가
		/* 농지 */
		eEBTTT_Sys_T_Farm = 9, // 농지
		/* 제재소 */
		eEBTTT_SAWMILL = 10, // 제재소
		/* 채석장 */
		eEBTTT_QUARRY = 11, // 채석장
		/* 광업장 */
		eEBTTT_MINING = 12, // 광업장
		/* 양잠소 */
		eEBTTT_COCOONERY = 13, // 양잠소
		/* 병영 */
		eEBTTT_Sys_T_Barrack = 14, // 병영
		/* 대장간 */
		eEBTTT_SMITHY = 15, // 대장간
		/* 공방 */
		eEBTTT_FORGE = 16, // 공방
		/* 마구간 */
		eEBTTT_STABLE = 17, // 마구간
		/* 둔영 */
		eEBTTT_Sys_T_Camp = 18, // 둔영
		/* 창고 */
		eEBTTT_Sys_T_Depot = 19, // 창고
		/* 비밀창고 */
		eEBTTT_SECRET = 20, // 비밀창고
		/* 망루 */
		eEBTTT_TOWER = 21, // 망루
		/* 방벽 */
		eEBTTT_BARRIER = 22, // 방벽
		eEND_EBuildType_test
	}; // EBuildType_test 



	enum EBuildTypeTest // 설명없음
	{
		eBEGIN_EBuildTypeTest = 0,
		/* 본영 */
		eETT_Sys_T_HQ = 1, // 본영
		/* 주점 */
		eETT_Sys_T_Bar = 2, // 주점
		/* 서원 */
		eETT_ACADEMY = 3, // 서원
		/* 치안부 */
		eETT_PEACE = 4, // 치안부
		/* 사당 */
		eETT_SHRINE = 5, // 사당
		/* 감찰부 */
		eETT_HIDEOUT = 6, // 감찰부
		/* 교역소 */
		eETT_TRADINGPOST = 7, // 교역소
		/* 민가 */
		eETT_Sys_T_House = 8, // 민가
		/* 농지 */
		eETT_Sys_T_Farm = 9, // 농지
		/* 제재소 */
		eETT_SAWMILL = 10, // 제재소
		/* 채석장 */
		eETT_QUARRY = 11, // 채석장
		/* 광업장 */
		eETT_MINING = 12, // 광업장
		/* 양잠소 */
		eETT_COCOONERY = 13, // 양잠소
		/* 병영 */
		eETT_Sys_T_Barrack = 14, // 병영
		/* 대장간 */
		eETT_SMITHY = 15, // 대장간
		/* 공방 */
		eETT_FORGE = 16, // 공방
		/* 마구간 */
		eETT_STABLE = 17, // 마구간
		/* 둔영 */
		eETT_Sys_T_Camp = 18, // 둔영
		/* 창고 */
		eETT_Sys_T_Depot = 19, // 창고
		/* 비밀창고 */
		eETT_SECRET = 20, // 비밀창고
		/* 망루 */
		eETT_TOWER = 21, // 망루
		/* 방벽 */
		eETT_BARRIER = 22, // 방벽
		eEND_EBuildTypeTest
	}; // EBuildTypeTest 



	enum EOutput_test // 설명없음
	{
		eBEGIN_EOutput_test = 0,
		/* 인구 */
		eEOTTT_POPULATION = 1, // 인구
		/* 금 */
		eEOTTT_GOLD = 2, // 금
		/* 식량 */
		eEOTTT_FOOD = 3, // 식량
		/* 목재 */
		eEOTTT_TREE = 4, // 목재
		/* 석재 */
		eEOTTT_STONE = 5, // 석재
		/* 철재 */
		eEOTTT_IRON = 6, // 철재
		/* 비단 */
		eEOTTT_SILK = 7, // 비단
		/* 병사 */
		eEOTTT_SOLDIER = 8, // 병사
		eEOTTT_PIKE = 9, // 창 병기
		eEOTTT_HEAVY = 10, // 중갑 병기
		/* 근위병 (철 소모 위주) */
		eEOTTT_HALBERD = 11, // 언월도 병기
		eEOTTT_BOW = 12, // 궁 병기
		eEOTTT_CROSSBOW = 13, // 노 병기
		eEOTTT_BOWGUN = 14, // 강노 병기
		eEOTTT_BALLISTA = 15, // 노포 병기
		/* 군마랑 조합해서만 가능 (개수 늘어나야) */
		eEOTTT_CHARIOT = 16, // 전차 병기
		/* 군마랑 조합해서만 가능 (개수 늘어나야) */
		eEOTTT_WAGON = 17, // 마차
		/* Eunit_ClassItemA 와 조합 가능 */
		eEOTTT_HORSE = 18, // 군마
		/* 공작, 수송, 보급 용도 */
		eEOTTT_WHEELBARROW = 19, // 수레
		eEOTTT_CART = 20, // 목우
		/* B만 활용 가능 */
		eEOTTT_SIEGE_LADDER = 21, // 운제
		eEOTTT_SIEGE_RAM = 22, // 충차
		eEOTTT_SIEGE_TOWER = 23, // 정란
		eEOTTT_SIEGE_TREBUCHET = 24, // 투석기
		eEND_EOutput_test
	}; // EOutput_test 






#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EAvatarClass[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBuildType_test[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBuildTypeTest[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EOutput_test[];
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
