/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nTESTSERVER___filename_sam_hero_
#define __namespace_nTESTSERVER___filename_sam_hero_

#include "table_const_sam_hero.h"
// -------------------------------------------------
// enum형 코드 템플릿 정의
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nTESTSERVER_sam_hero_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EDeckYear,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EHeroCategory,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EHeroEngagementtype,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EHeroFacetype,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EHeroPersonality,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EHeroSex,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EHeroWorkState,설명없음,nMech,nTESTSERVER)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// 주의 enum변수는 앞에 e가 자동으로 붙어서 선언됨 
	// -------------------------------------------------

	/* 설명없음 */
	#define for_each_nTESTSERVER_EDeckYear_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(DY_189			,1,189년 카드 덱,nMech,nTESTSERVER,EDeckYear)\
		ENUM_FIELD(DY_192			,2,192년 카드 덱,nMech,nTESTSERVER,EDeckYear)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EHeroCategory_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(HC_HISTORICAL			,1,역사 장수,nMech,nTESTSERVER,EHeroCategory)\
		ENUM_FIELD(HC_VIRTAUL			,2,가상 장수,nMech,nTESTSERVER,EHeroCategory)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EHeroEngagementtype_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(HE_COMMON			,1,일반,nMech,nTESTSERVER,EHeroEngagementtype)\
		ENUM_FIELD(HE_RARE			,2,희귀,nMech,nTESTSERVER,EHeroEngagementtype)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EHeroFacetype_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(HF_ORIGINAL			,1,얼굴이미지사용,nMech,nTESTSERVER,EHeroFacetype)\
		ENUM_FIELD(HF_COMMON			,2,범용이미지사용,nMech,nTESTSERVER,EHeroFacetype)\
		ENUM_FIELD(HF_MONTAGE			,3,조합(몽타쥬) 이미지,nMech,nTESTSERVER,EHeroFacetype)\
		ENUM_FIELD(HF_UPLOAD			,4,유저 등록 이미지,nMech,nTESTSERVER,EHeroFacetype)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EHeroPersonality_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(HP_TOUGH			,1,저돌,nMech,nTESTSERVER,EHeroPersonality)\
		ENUM_FIELD(HP_BRAVE			,2,용맹,nMech,nTESTSERVER,EHeroPersonality)\
		ENUM_FIELD(HP_COOL			,3,냉정,nMech,nTESTSERVER,EHeroPersonality)\
		ENUM_FIELD(HP_WEAK			,4,소심,nMech,nTESTSERVER,EHeroPersonality)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EHeroSex_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(HS_MALE			,1,남성,nMech,nTESTSERVER,EHeroSex)\
		ENUM_FIELD(HS_FEMALE			,2,여성,nMech,nTESTSERVER,EHeroSex)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EHeroWorkState_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(HWS_REST			,1,휴식,nMech,nTESTSERVER,EHeroWorkState)\
		ENUM_FIELD(HWS_CONSTRUCTION			,2,건물 건설,nMech,nTESTSERVER,EHeroWorkState)\
		ENUM_FIELD(HWS_EXPLORATION			,3,탐색 활동,nMech,nTESTSERVER,EHeroWorkState)\
		ENUM_FIELD(HWS_COMBAT			,4,부대 출전,nMech,nTESTSERVER,EHeroWorkState)\


// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nTESTSERVER_sam_hero_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Hero,장수 테이블,nMech,nTESTSERVER)\



	// ------------------------------------------------------------
	// Sys_Hero 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD
	#define for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD(FIELD)\
		FIELD(hsid                   ,sid                ,Sys_Hero_id_t                ,0 , Sys_Hero_id_t , Sys_Hero_id_t , Sys_Hero_id_t)\
		FIELD(category               ,장수 분류              ,EHeroCategory                ,1 , EHeroCategory , EHeroCategory , EHeroCategory)\
		FIELD(deck_year              ,카드 연도              ,EDeckYear                    ,2 , EDeckYear , EDeckYear , EDeckYear)\
		FIELD(name                   ,장수 영문 이름           ,tname32_t                    ,3 , tcstr , tcstr , t32)\
		FIELD(name_kor               ,장수 한글 이름           ,wname32_t                    ,4 , wcstr , wcstr , w32)\
		FIELD(image_file             ,얼굴 이미지             ,tname256_t                   ,5 , tcstr , tcstr , t256)\
		FIELD(grade                  ,장수 등급              ,int32                        ,6 , int32 , int32 , i32)\
		FIELD(age                    ,나이                 ,int32                        ,7 , int32 , int32 , i32)\
		FIELD(leadership             ,통솔                 ,int32                        ,8 , int32 , int32 , i32)\
		FIELD(power                  ,무력                 ,int32                        ,9 , int32 , int32 , i32)\
		FIELD(intelligent            ,지모                 ,int32                        ,10 , int32 , int32 , i32)\
		FIELD(politic                ,정치                 ,int32                        ,11 , int32 , int32 , i32)\
		FIELD(charm                  ,매력                 ,int32                        ,12 , int32 , int32 , i32)\
		FIELD(is_male                ,성별                 ,bool                         ,13 , bool , bool , b)\
		FIELD(personality            ,성격                 ,EHeroPersonality             ,14 , EHeroPersonality , EHeroPersonality , EHeroPersonality)\

	#endif // for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Hero가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nTESTSERVER_Sys_Hero_InheritedTable
	#define for_each_nTESTSERVER_Sys_Hero_InheritedTable(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Hero_InheritedTable


	// ------------------------------------------------------------
	// Sys_Hero가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD_Inherited
	#define for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Hero가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD_all_member
	#define for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD_all_member(FUNC)\
		for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nTESTSERVER 
{

	enum EDeckYear // 설명없음
	{
		eBEGIN_EDeckYear = 0,
		/* 189년 카드 덱 */
		eDY_189 = 1, // 189년 카드 덱
		/* 192년 카드 덱 */
		eDY_192 = 2, // 192년 카드 덱
		eEND_EDeckYear
	}; // EDeckYear 



	enum EHeroCategory // 설명없음
	{
		eBEGIN_EHeroCategory = 0,
		/* 역사 장수 */
		eHC_HISTORICAL = 1, // 역사 장수
		/* 가상 장수 */
		eHC_VIRTAUL = 2, // 가상 장수
		eEND_EHeroCategory
	}; // EHeroCategory 



	enum EHeroEngagementtype // 설명없음
	{
		eBEGIN_EHeroEngagementtype = 0,
		/* 일반 */
		eHE_COMMON = 1, // 일반
		/* 희귀 */
		eHE_RARE = 2, // 희귀
		eEND_EHeroEngagementtype
	}; // EHeroEngagementtype 



	enum EHeroFacetype // 설명없음
	{
		eBEGIN_EHeroFacetype = 0,
		/* 고유 이미지, 유명 장수 */
		eHF_ORIGINAL = 1, // 얼굴이미지사용
		/* 중복 사용가능한 이미지, 일반 장수 */
		eHF_COMMON = 2, // 범용이미지사용
		/* 얼굴 조합기를 이용한 형태 */
		eHF_MONTAGE = 3, // 조합(몽타쥬) 이미지
		/* 유저가 업로드한 이미지 */
		eHF_UPLOAD = 4, // 유저 등록 이미지
		eEND_EHeroFacetype
	}; // EHeroFacetype 



	enum EHeroPersonality // 설명없음
	{
		eBEGIN_EHeroPersonality = 0,
		/* 저돌 */
		eHP_TOUGH = 1, // 저돌
		/* 용맹 */
		eHP_BRAVE = 2, // 용맹
		/* 냉정 */
		eHP_COOL = 3, // 냉정
		/* 소심 */
		eHP_WEAK = 4, // 소심
		eEND_EHeroPersonality
	}; // EHeroPersonality 



	enum EHeroSex // 설명없음
	{
		eBEGIN_EHeroSex = 0,
		/* 남자 장수 */
		eHS_MALE = 1, // 남성
		/* 여자 장수 */
		eHS_FEMALE = 2, // 여성
		eEND_EHeroSex
	}; // EHeroSex 



	enum EHeroWorkState // 설명없음
	{
		eBEGIN_EHeroWorkState = 0,
		/* 아무 일도 하지 않고 있음 */
		eHWS_REST = 1, // 휴식
		/* 건물 건설을 수행 중 */
		eHWS_CONSTRUCTION = 2, // 건물 건설
		/* 탐색 활동을 수행 중 */
		eHWS_EXPLORATION = 3, // 탐색 활동
		/* 부대를 이끌고 필드에 나간 상태 */
		eHWS_COMBAT = 4, // 부대 출전
		eEND_EHeroWorkState
	}; // EHeroWorkState 





struct jEXCEL_LIB_API Sys_Hero /* 장수 테이블 */
{
	/*  장수가 소속한 세력(소유 유저의 소속 세력과 같음) */
	Sys_Hero_id_t m_hsid; // sid min_max(,)
	/*  장수 분류 형태, 역사 장수, 가상 장수 */
	EHeroCategory m_category; // 장수 분류 min_max(,EHeroCategory)
	/*  장수 연도별 카드 덱 이름 */
	EDeckYear m_deck_year; // 카드 연도 min_max(,EDeckYear)
	/*  장수 영문 이름 */
	tname32_t m_name; // 장수 영문 이름 min_max(,)
	/*  장수 한글 이름 */
	wname32_t m_name_kor; // 장수 한글 이름 min_max(,)
	/*  장수 초상화 이미지 */
	tname256_t m_image_file; // 얼굴 이미지 min_max(,)
	/*  장수 등급, 1성 ~ 7성까지 ( 차후 Sys_HeroGrade_id_t) */
	int32 m_grade; // 장수 등급 min_max(,)
	int32 m_age; // 나이 min_max(1,99)
	int32 m_leadership; // 통솔 min_max(1,200)
	int32 m_power; // 무력 min_max(1,200)
	int32 m_intelligent; // 지모 min_max(1,200)
	int32 m_politic; // 정치 min_max(1,200)
	int32 m_charm; // 매력 min_max(1,200)
	/*  성별 */
	bool m_is_male; // 성별 min_max(,)
	/*  장수 성격 */
	EHeroPersonality m_personality; // 성격 min_max(,EHeroPersonality)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Hero
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  15 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Hero
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Hero();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Hero

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Hero)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Hero
enum { eSTRUCT_SIZE_Sys_Hero = sizeof(Sys_Hero) };


struct CSV_Sys_Hero : public nMech::nUtil::jCSV_File<Sys_Hero>
{
	virtual ~CSV_Sys_Hero(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Hero>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Hero g_Sys_Hero;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nTESTSERVER_sam_hero_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EDeckYear[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroCategory[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroEngagementtype[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroFacetype[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroPersonality[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroSex[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroWorkState[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nTESTSERVER 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nTESTSERVER;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nTESTSERVER_sam_hero_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nTESTSERVER_sam_hero_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nTESTSERVER;
	for_each_nTESTSERVER_sam_hero_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nTESTSERVER___filename_sam_hero_
