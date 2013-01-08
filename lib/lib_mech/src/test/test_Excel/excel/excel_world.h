/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_world_
#define __namespace_nEXCEL___filename_excel_world_

#include "table_const_excel_world.h"
// -------------------------------------------------
// enum형 코드 템플릿 정의
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nEXCEL_excel_world_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EIssue_Info,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(ETile_Sort,설명없음,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// 주의 enum변수는 앞에 e가 자동으로 붙어서 선언됨 
	// -------------------------------------------------

	/* 설명없음 */
	#define for_each_nEXCEL_EIssue_Info_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EII_NORMAL			,1,일반,nMech,nEXCEL,EIssue_Info)\
		ENUM_FIELD(EII_NEW			,2,신규,nMech,nEXCEL,EIssue_Info)\
		ENUM_FIELD(EII_RECOMMEND			,3,추천,nMech,nEXCEL,EIssue_Info)\
		ENUM_FIELD(EII_TEST			,4,테스트용,nMech,nEXCEL,EIssue_Info)\

	/* 설명없음 */
	#define for_each_nEXCEL_ETile_Sort_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ETS_ROAD			,1,도로,nMech,nEXCEL,ETile_Sort)\
		ENUM_FIELD(ETS_MEADOW			,2,초원,nMech,nEXCEL,ETile_Sort)\
		ENUM_FIELD(ETS_LAND			,3,평지,nMech,nEXCEL,ETile_Sort)\
		ENUM_FIELD(ETS_MOUNT			,4,산악,nMech,nEXCEL,ETile_Sort)\
		ENUM_FIELD(ETS_RIVER			,5,강,nMech,nEXCEL,ETile_Sort)\
		ENUM_FIELD(ETS_SEA			,6,바다,nMech,nEXCEL,ETile_Sort)\
		ENUM_FIELD(ETS_SWAMP			,7,늪,nMech,nEXCEL,ETile_Sort)\


// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_world_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Tile,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_World,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Tile 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Tile_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Tile_STRUCT_FIELD(FIELD)\
		FIELD(tisid                  ,숫자ID               ,Sys_Tile_id_t                ,0 , Sys_Tile_id_t , uint16 , u16)\
		FIELD(name                   ,이름ID               ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(name_kor               ,타일_이름              ,tname32_t                    ,2 , tcstr , tcstr , t32)\
		FIELD(client_file            ,타일 이미지             ,tname256_t                   ,3 , tcstr , tcstr , t256)\
		FIELD(sort                   ,분류                 ,ETile_Sort                   ,4 , ETile_Sort , ETile_Sort , e)\
		FIELD(mspeed                 ,이동속도보정             ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(visibility             ,가시거리               ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(build                  ,건설여부               ,bool                         ,7 , bool , bool , b)\
		FIELD(fskill                 ,화계_스킬_보정           ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(wskill                 ,수계_스킬_보정           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(rskill                 ,낙석_스킬_보정           ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(hiskill                ,은신_스킬_보정           ,int16                        ,11 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_Tile_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Tile가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Tile_InheritedTable
	#define for_each_nEXCEL_Sys_Tile_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Tile_InheritedTable


	// ------------------------------------------------------------
	// Sys_Tile가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Tile_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Tile_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Tile_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Tile가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Tile_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Tile_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Tile_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Tile_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Tile_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_World 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_World_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_World_STRUCT_FIELD(FIELD)\
		FIELD(wsid                   ,숫자 ID              ,Sys_World_id_t               ,0 , Sys_World_id_t , uint16 , u16)\
		FIELD(name                   ,이름 ID              ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(name_kor               ,서버 이름              ,tname32_t                    ,2 , tcstr , tcstr , t32)\
		FIELD(issue                  ,이슈 상항              ,EIssue_Info                  ,3 , EIssue_Info , EIssue_Info , e)\
		FIELD(address                ,접속IP               ,tname32_t                    ,4 , tcstr , tcstr , t32)\
		FIELD(help                   ,서버설명               ,tname64_t                    ,5 , tcstr , tcstr , t64)\
		FIELD(goldstart              ,금 시작자원             ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(ricestart              ,식량 시작자원            ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(treestart              ,나무 시작자원            ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(stonestart             ,돌 시작자원             ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(ironstart              ,철 시작자원             ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(silkstart              ,비단 시작자원            ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(mspeed                 ,부대이동속도보정           ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(re_increase            ,자원 증가량             ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(buildtime              ,건축 시간              ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(produtime              ,생산 시간              ,int16                        ,15 , int16 , int16 , i16)\
		FIELD(recrutime              ,모집 시간              ,int16                        ,16 , int16 , int16 , i16)\
		FIELD(researchtime           ,연구 시간              ,int16                        ,17 , int16 , int16 , i16)\
		FIELD(goldamount             ,금 획득량              ,int16                        ,18 , int16 , int16 , i16)\
		FIELD(peo_increase           ,인구 증가              ,int16                        ,19 , int16 , int16 , i16)\
		FIELD(questbenefit           ,퀘스트 보상             ,int16                        ,20 , int16 , int16 , i16)\
		FIELD(huntbenefit            ,사냥 보상              ,int16                        ,21 , int16 , int16 , i16)\
		FIELD(appoint_ratio          ,장수 등용 확률           ,int16                        ,22 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_World_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_World가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_World_InheritedTable
	#define for_each_nEXCEL_Sys_World_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_World_InheritedTable


	// ------------------------------------------------------------
	// Sys_World가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_World_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_World_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_World_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_World가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_World_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_World_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_World_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_World_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_World_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum EIssue_Info // 설명없음
	{
		eBEGIN_EIssue_Info = 0,
		/* 일반 서버 */
		eEII_NORMAL = 1, // 일반
		/* 신규 서버 */
		eEII_NEW = 2, // 신규
		/* 추천 서버 */
		eEII_RECOMMEND = 3, // 추천
		/* 테스트용 서버 */
		eEII_TEST = 4, // 테스트용
		eEND_EIssue_Info
	}; // EIssue_Info 



	enum ETile_Sort // 설명없음
	{
		eBEGIN_ETile_Sort = 0,
		/* 성과 성 사이의 길 */
		eETS_ROAD = 1, // 도로
		/* 숲 */
		eETS_MEADOW = 2, // 초원
		/* 평지 */
		eETS_LAND = 3, // 평지
		/* 산악 */
		eETS_MOUNT = 4, // 산악
		/* 강물 */
		eETS_RIVER = 5, // 강
		/* 바다 */
		eETS_SEA = 6, // 바다
		/* 늪 */
		eETS_SWAMP = 7, // 늪
		eEND_ETile_Sort
	}; // ETile_Sort 





struct jEXCEL_LIB_API Sys_Tile /* 설명없음 */
{
	Sys_Tile_id_t m_tisid; // 숫자ID min_max(,)
	tname32_t m_name; // 이름ID min_max(,)
	tname32_t m_name_kor; // 타일_이름 min_max(,)
	tname256_t m_client_file; // 타일 이미지 min_max(,)
	/*  세부 텍스쳐 종류 */
	ETile_Sort m_sort; // 분류 min_max(,ETile_Sort)
	/*  유저 이동속도 보정 (%보정값으로 500.0% 가능) */
	int16 m_mspeed; // 이동속도보정 min_max(0,5000)
	/*  유닛의 시야 보정 */
	int16 m_visibility; // 가시거리 min_max(-100,100)
	/*  건설 개념이 안들어갈 때는 삭제 */
	bool m_build; // 건설여부 min_max(0,1)
	/*  불 속성 스킬 보정값 */
	int16 m_fskill; // 화계_스킬_보정 min_max(-999,999)
	/*  물 속성 스킬 보정값 */
	int16 m_wskill; // 수계_스킬_보정 min_max(-999,999)
	/*  돌 속성 스킬 보정값 */
	int16 m_rskill; // 낙석_스킬_보정 min_max(-999,999)
	/*  은신 스킬 보정값 */
	int16 m_hiskill; // 은신_스킬_보정 min_max(-999,999)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Tile
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Tile_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  12 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Tile
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Tile();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Tile

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Tile_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Tile)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Tile
enum { eSTRUCT_SIZE_Sys_Tile = sizeof(Sys_Tile) };


struct CSV_Sys_Tile : public nMech::nUtil::jCSV_File<Sys_Tile>
{
	virtual ~CSV_Sys_Tile(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Tile>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Tile g_Sys_Tile;

struct jEXCEL_LIB_API Sys_World /* 설명없음 */
{
	/*  서버 오픈 순서별로 번호 지정 */
	Sys_World_id_t m_wsid; // 숫자 ID min_max(,)
	/*  서버이름 ID */
	tname32_t m_name; // 이름 ID min_max(,)
	/*  서버 선택 리스트에 표시되는 서버 이름 */
	tname32_t m_name_kor; // 서버 이름 min_max(,)
	/*  유저에게 알리는 서버 상황. 아이콘 이미지로 표현 */
	EIssue_Info m_issue; // 이슈 상항 min_max(,EIssue_Info)
	/*  접속 주소 */
	tname32_t m_address; // 접속IP min_max(,)
	/*  기타설명 */
	tname64_t m_help; // 서버설명 min_max(,)
	/*  처음 시작시의 금자원량 */
	int16 m_goldstart; // 금 시작자원 min_max(0,999)
	/*  처음 시작시의 나무자원량 */
	int16 m_ricestart; // 식량 시작자원 min_max(0,999)
	/*  처음 시작시의 금자원량 */
	int16 m_treestart; // 나무 시작자원 min_max(0,999)
	/*  처음 시작시의 금자원량 */
	int16 m_stonestart; // 돌 시작자원 min_max(0,999)
	/*  처음 시작시의 금자원량 */
	int16 m_ironstart; // 철 시작자원 min_max(0,999)
	/*  처음 시작시의 금자원량 */
	int16 m_silkstart; // 비단 시작자원 min_max(0,999)
	/*  전략맵에서의 부대 이동 속도 (기본 100으로 지정) 1000초에 100타일 이동 */
	int16 m_mspeed; // 부대이동속도보정 min_max(-999,999)
	/*  각 자원채취용 건물에서의 시간당 자원 채취량 보정값. (기본 100으로 지정) */
	int16 m_re_increase; // 자원 증가량 min_max(-999,999)
	/*  건물의 건축, 업그레이드 소요 시간 보정값. (기본 100으로 지정) */
	int16 m_buildtime; // 건축 시간 min_max(-999,999)
	/*  건물에서의 무기, 기타 생산품들의 생산 시간 보정값. (기본 100으로 지정) */
	int16 m_produtime; // 생산 시간 min_max(-999,999)
	/*  건물에서의 병사 모집 시간 보정값. (기본 100으로 지정) */
	int16 m_recrutime; // 모집 시간 min_max(-999,999)
	/*  연구 진행 시간 보정값. (기본 100으로 지정) */
	int16 m_researchtime; // 연구 시간 min_max(-999,999)
	/*  건물에서의 세금 징수등의 금 획득량 보정값. (기본 100으로 지정) */
	int16 m_goldamount; // 금 획득량 min_max(-999,999)
	/*  건물에서의 인구 증가량 보정값. (기본 100으로 지정) */
	int16 m_peo_increase; // 인구 증가 min_max(-999,999)
	/*  퀘스트 수행 후의 보상내용 보정값. (기본 100으로 지정) */
	int16 m_questbenefit; // 퀘스트 보상 min_max(-999,999)
	/*  사냥(PVE)에서 승리 후의 보상내용 보정값. (기본 100으로 지정) */
	int16 m_huntbenefit; // 사냥 보상 min_max(-999,999)
	/*  장수 등용 시도시 성공할 확률 보정값. (기본 100으로 지정) */
	int16 m_appoint_ratio; // 장수 등용 확률 min_max(-999,999)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_World
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_World_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  23 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_World
		jEXCEL_TABLE_COMMON_CODE_H_Sys_World();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_World

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_World_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_World)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_World
enum { eSTRUCT_SIZE_Sys_World = sizeof(Sys_World) };


struct CSV_Sys_World : public nMech::nUtil::jCSV_File<Sys_World>
{
	virtual ~CSV_Sys_World(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_World>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_World g_Sys_World;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_world_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EIssue_Info[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ETile_Sort[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nEXCEL_excel_world_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_world_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_world_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_world_
