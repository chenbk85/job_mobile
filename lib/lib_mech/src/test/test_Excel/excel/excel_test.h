/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_test_
#define __namespace_nEXCEL___filename_excel_test_

#include "table_const_excel_test.h"
// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_test_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys__T_Base,빌딩type 테이블의 base 테이블이다. 모든 빌딩type 테이블은 이 테이블을 상속받는다,nMech,nEXCEL)\
	STRUCT(Sys_T_Test,테스트용,nMech,nEXCEL)\
	STRUCT(Sys_T_Test2,테스트용2,nMech,nEXCEL)\
	STRUCT(Sys_T_Test3,테스트용2,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys__T_Base 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD
	#define for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD(FIELD)\
		FIELD(level                  ,레벨                 ,Sys__T_Base_id_t             ,0 , Sys__T_Base_id_t , uint16 , u16)\
		FIELD(base_type              ,건물타입               ,EBuildType_test              ,1 , EBuildType_test , EBuildType_test , e)\
		FIELD(name                   ,건물리소스명             ,tname32_t                    ,2 , tcstr , tcstr , t32)\
		FIELD(upgradetime            ,업그레이드 시간           ,uint32                       ,3 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,목재 비용              ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(stone_num              ,돌 비용               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(iron_num               ,철 비용               ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(silk_num               ,비단 비용              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(population_num         ,인구 비용              ,int16                        ,8 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys__T_Base가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys__T_Base_InheritedTable
	#define for_each_nEXCEL_Sys__T_Base_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys__T_Base_InheritedTable


	// ------------------------------------------------------------
	// Sys__T_Base가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys__T_Base가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Test 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD(FIELD)\
		FIELD(maxbuild               ,111최대 생성수          ,int16                        ,1 , int16 , int16 , i16)\
		FIELD(downlevel              ,111다운그레이드레벨        ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(populationreturn       ,111인구 반환비용         ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(test                   ,111test            ,EBuildType_test              ,4 , EBuildType_test , EBuildType_test , e)\
		FIELD(getgold                ,111징수              ,int16                        ,5 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Test가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Test_InheritedTable
	#define for_each_nEXCEL_Sys_T_Test_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys__T_Base_InheritedTable(FUNC)\
		FUNC(Sys__T_Base)\

	#endif // for_each_nEXCEL_Sys_T_Test_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Test가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Test가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Test2 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD(FIELD)\
		FIELD(maxbuild2              ,222최대 생성수          ,int16                        ,1 , int16 , int16 , i16)\
		FIELD(downlevel2             ,2다운그레이드레벨          ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(treereturn2            ,222목재 반환비용         ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stonereturn2           ,222돌 반환비용          ,EOutput_test                 ,4 , EOutput_test , EOutput_test , e)\
		FIELD(populationreturn2      ,222인구 반환비용         ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(test2                  ,222test            ,EBuildType_test              ,6 , EBuildType_test , EBuildType_test , e)\
		FIELD(getgold2               ,222징수              ,int16                        ,7 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Test2가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Test2_InheritedTable
	#define for_each_nEXCEL_Sys_T_Test2_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys_T_Test_InheritedTable(FUNC)\
		FUNC(Sys_T_Test)\

	#endif // for_each_nEXCEL_Sys_T_Test2_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Test2가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Test2가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Test3 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD(FIELD)\
		FIELD(maxbuild2              ,333최대 생성수          ,int16                        ,1 , int16 , int16 , i16)\
		FIELD(stonereturn2           ,333돌 반환비용          ,EOutput_test                 ,2 , EOutput_test , EOutput_test , e)\
		FIELD(populationreturn2      ,333인구 반환비용         ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(test2                  ,333test            ,EBuildType_test              ,4 , EBuildType_test , EBuildType_test , e)\
		FIELD(getgold2               ,333징수              ,int16                        ,5 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Test3가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Test3_InheritedTable
	#define for_each_nEXCEL_Sys_T_Test3_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys__T_Base_InheritedTable(FUNC)\
		FUNC(Sys__T_Base)\

	#endif // for_each_nEXCEL_Sys_T_Test3_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Test3가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Test3가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{



struct jEXCEL_LIB_API Sys__T_Base /* 빌딩type 테이블의 base 테이블이다. 모든 빌딩type 테이블은 이 테이블을 상속받는다 */
{
	/*  건물 레벨 ( 해당 종류의 건물 sid 식별자로도 쓰인다) */
	Sys__T_Base_id_t m_level; // 레벨 min_max(,)
		typedef Sys__T_Base_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_level; }
	void SetPrimaryKey(primary_key_t id) { m_level = id; }
	/*  Sys_T_BaseObj를상속 받는 테이블의 건물 종류 */
	EBuildType_test m_base_type; // 건물타입 min_max(,EBuildType_test)
	/*  건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 */
	tname32_t m_name; // 건물리소스명 min_max(,)
	/*  업그레이드를 진행할 때 소비되는 시간 /초단위 */
	uint32 m_upgradetime; // 업그레이드 시간 min_max(,)
	/*  건설에 필요한 목재 비용 */
	int16 m_tree_num; // 목재 비용 min_max(,)
	/*  건설에 필요한 돌 비용 */
	int16 m_stone_num; // 돌 비용 min_max(,)
	/*  건설에 필요한 철 비용 */
	int16 m_iron_num; // 철 비용 min_max(,)
	/*  건설에 필요한 비단 비용 */
	int16 m_silk_num; // 비단 비용 min_max(,)
	/*  건설에 필요한 인구 비용 */
	int16 m_population_num; // 인구 비용 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys__T_Base
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  9 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys__T_Base
		jEXCEL_TABLE_COMMON_CODE_H_Sys__T_Base();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys__T_Base

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys__T_Base)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys__T_Base
enum { eSTRUCT_SIZE_Sys__T_Base = sizeof(Sys__T_Base) };


struct CSV_Sys__T_Base : public nMech::nUtil::jCSV_File<Sys__T_Base>
{
	virtual ~CSV_Sys__T_Base(){}
	jLIST_TYPEDEF_vector_typedef(Sys__T_Base*,vector_base_type);
	jLIST_TYPEDEF_map(EBuildType_test, vector_base_type_t, m_INDEX_base_type);
	void init_INDEX_base_type()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys__T_Base* p = at(i);
			m_INDEX_base_type[p->Get_base_type()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys__T_Base>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_base_type();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys__T_Base g_Sys__T_Base;

struct jEXCEL_LIB_API Sys_T_Test /* 테스트용 */
	:Sys__T_Base
{
	Sys__T_Base* GetBase_Sys__T_Base(){ return static_cast<Sys__T_Base*>(this);}
	/*  한 마을에 최대 생성 가능한 건물 수 */
	int16 m_maxbuild; // 111최대 생성수 min_max(,)
	/*  다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 */
	int16 m_downlevel; // 111다운그레이드레벨 min_max(,)
	/*  건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. */
	int16 m_populationreturn; // 111인구 반환비용 min_max(,)
	EBuildType_test m_test; // 111test min_max(,EBuildType_test)
	/*  징수 명령 */
	int16 m_getgold; // 111징수 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_T_Test
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  5 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Sys__T_Base::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Test_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Test)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Test
enum { eSTRUCT_SIZE_Sys_T_Test = sizeof(Sys_T_Test) };


struct CSV_Sys_T_Test : public nMech::nUtil::jCSV_File<Sys_T_Test>
{
	virtual ~CSV_Sys_T_Test(){}
	jLIST_TYPEDEF_vector_typedef(Sys_T_Test*,vector_base_type);
	jLIST_TYPEDEF_map(EBuildType_test, vector_base_type_t, m_INDEX_base_type);
	void init_INDEX_base_type()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_T_Test* p = at(i);
			m_INDEX_base_type[p->Get_base_type()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Test>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_base_type();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Test g_Sys_T_Test;

struct jEXCEL_LIB_API Sys_T_Test2 /* 테스트용2 */
	:Sys_T_Test
{
	Sys_T_Test* GetBase_Sys_T_Test(){ return static_cast<Sys_T_Test*>(this);}
	/*  한 마을에 최대 생성 가능한 건물 수 */
	int16 m_maxbuild2; // 222최대 생성수 min_max(,)
	/*  다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 */
	int16 m_downlevel2; // 2다운그레이드레벨 min_max(,)
	/*  건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) */
	int16 m_treereturn2; // 222목재 반환비용 min_max(,)
	EOutput_test m_stonereturn2; // 222돌 반환비용 min_max(,EOutput_test)
	/*  건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. */
	int16 m_populationreturn2; // 222인구 반환비용 min_max(,)
	EBuildType_test m_test2; // 222test min_max(,EBuildType_test)
	/*  징수 명령 */
	int16 m_getgold2; // 222징수 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_T_Test2
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  7 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Sys_T_Test::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test2
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test2();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test2

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Test2_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Test2)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Test2
enum { eSTRUCT_SIZE_Sys_T_Test2 = sizeof(Sys_T_Test2) };


struct CSV_Sys_T_Test2 : public nMech::nUtil::jCSV_File<Sys_T_Test2>
{
	virtual ~CSV_Sys_T_Test2(){}
	jLIST_TYPEDEF_vector_typedef(Sys_T_Test2*,vector_base_type);
	jLIST_TYPEDEF_map(EBuildType_test, vector_base_type_t, m_INDEX_base_type);
	void init_INDEX_base_type()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_T_Test2* p = at(i);
			m_INDEX_base_type[p->Get_base_type()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Test2>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_base_type();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Test2 g_Sys_T_Test2;

struct jEXCEL_LIB_API Sys_T_Test3 /* 테스트용2 */
	:Sys__T_Base
{
	Sys__T_Base* GetBase_Sys__T_Base(){ return static_cast<Sys__T_Base*>(this);}
	/*  한 마을에 최대 생성 가능한 건물 수 */
	int16 m_maxbuild2; // 333최대 생성수 min_max(,)
	EOutput_test m_stonereturn2; // 333돌 반환비용 min_max(,EOutput_test)
	/*  건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. */
	int16 m_populationreturn2; // 333인구 반환비용 min_max(,)
	EBuildType_test m_test2; // 333test min_max(,EBuildType_test)
	/*  징수 명령 */
	int16 m_getgold2; // 333징수 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_T_Test3
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  5 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Sys__T_Base::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test3
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test3();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test3

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Test3_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Test3)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Test3
enum { eSTRUCT_SIZE_Sys_T_Test3 = sizeof(Sys_T_Test3) };


struct CSV_Sys_T_Test3 : public nMech::nUtil::jCSV_File<Sys_T_Test3>
{
	virtual ~CSV_Sys_T_Test3(){}
	jLIST_TYPEDEF_vector_typedef(Sys_T_Test3*,vector_base_type);
	jLIST_TYPEDEF_map(EBuildType_test, vector_base_type_t, m_INDEX_base_type);
	void init_INDEX_base_type()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_T_Test3* p = at(i);
			m_INDEX_base_type[p->Get_base_type()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Test3>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_base_type();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Test3 g_Sys_T_Test3;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_test_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_test_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_test_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_test_
