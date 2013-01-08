/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_user_
#define __namespace_nEXCEL___filename_excel_user_

#include "table_const_excel_user.h"
// -------------------------------------------------
// enum형 코드 템플릿 정의
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nEXCEL_excel_user_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EBuildType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EOutput,설명없음,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// 주의 enum변수는 앞에 e가 자동으로 붙어서 선언됨 
	// -------------------------------------------------

	/* 설명없음 */
	#define for_each_nEXCEL_EBuildType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EBT_Sys_T_HQ			,1,본영,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_Sys_T_Bar			,2,주점,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_ACADEMY			,3,서원,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_PEACE			,4,치안부,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_SHRINE			,5,사당,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_HIDEOUT			,6,감찰부,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_TRADINGPOST			,7,교역소,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_Sys_T_House			,8,민가,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_Sys_T_Farm			,9,농지,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_SAWMILL			,10,제재소,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_QUARRY			,11,채석장,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_MINING			,12,광업장,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_COCOONERY			,13,양잠소,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_Sys_T_Barrack			,14,병영,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_SMITHY			,15,대장간,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_FORGE			,16,공방,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_STABLE			,17,마구간,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_Sys_T_Camp			,18,둔영,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_Sys_T_Depot			,19,창고,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_SECRET			,20,비밀창고,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_TOWER			,21,망루,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_BARRIER			,22,방벽,nMech,nEXCEL,EBuildType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EOutput_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EOT_POPULATION			,1,인구,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_GOLD			,2,금,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_FOOD			,3,식량,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_TREE			,4,목재,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_STONE			,5,석재,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_IRON			,6,철재,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_SILK			,7,비단,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_SOLDIER			,8,병사,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_PIKE			,9,창 병기,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_HEAVY			,10,중갑 병기,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_HALBERD			,11,언월도 병기,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_BOW			,12,궁 병기,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_CROSSBOW			,13,노 병기,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_BOWGUN			,14,강노 병기,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_BALLISTA			,15,노포 병기,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_CHARIOT			,16,전차 병기,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_WAGON			,17,마차,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_HORSE			,18,군마,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_WHEELBARROW			,19,수레,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_CART			,20,목우,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_SIEGE_LADDER			,21,운제,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_SIEGE_RAM			,22,충차,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_SIEGE_TOWER			,23,정란,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_SIEGE_TREBUCHET			,24,투석기,nMech,nEXCEL,EOutput)\


// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_user_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys__T_BuildObj,빌딩type 테이블의 base 테이블이다. 모든 빌딩type 테이블은 이 테이블을 상속받는다,nMech,nEXCEL)\
	STRUCT(Sys_T_Bar,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_T_Barrack,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_T_Camp,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_T_Depot,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_T_Farm,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_T_House,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_T_HQ,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys__T_BuildObj 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD
	#define for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD(FIELD)\
		FIELD(base_type              ,건물타입               ,EBuildType                   ,0 , EBuildType , EBuildType , e)\
		FIELD(name                   ,건물리소스명             ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(upgradetime            ,업그레이드 시간           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,목재 비용              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,돌 비용               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,철 비용               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,비단 비용              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,인구 비용              ,int16                        ,7 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys__T_BuildObj가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys__T_BuildObj_InheritedTable
	#define for_each_nEXCEL_Sys__T_BuildObj_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys__T_BuildObj_InheritedTable


	// ------------------------------------------------------------
	// Sys__T_BuildObj가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys__T_BuildObj가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Bar 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,레벨                 ,Sys_T_Bar_id_t               ,0 , Sys_T_Bar_id_t , uint16 , u16)\
		FIELD(client_file            ,건물 이미지 파일          ,tname256_t                   ,1 , tcstr , tcstr , t256)\
		FIELD(upgradetime            ,업그레이드 시간           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,목재 비용              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,돌 비용               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,철 비용               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,비단 비용              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,인구 비용              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(maxbuild               ,최대 생성수             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(downlevel              ,다운그레이드레벨           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(treereturn             ,목재 반환비용            ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(stonereturn            ,돌 반환비용             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(ironreturn             ,철 반환비용             ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(silkreturn             ,비단 반환비용            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(populationreturn       ,인구 반환비용            ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(hideHero               ,재야 장수              ,int16                        ,15 , int16 , int16 , i16)\
		FIELD(resettime              ,리셋시간               ,uint32                       ,16 , uint32 , uint32 , i32)\
		FIELD(itemnum                ,아이템수               ,int16                        ,17 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Bar가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Bar_InheritedTable
	#define for_each_nEXCEL_Sys_T_Bar_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Bar_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Bar가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Bar가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Barrack 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,레벨                 ,Sys_T_Barrack_id_t           ,0 , Sys_T_Barrack_id_t , uint16 , u16)\
		FIELD(client_file            ,건물 이미지 파일          ,tname256_t                   ,1 , tcstr , tcstr , t256)\
		FIELD(upgradetime            ,업그레이드 시간           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,목재 비용              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,돌 비용               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,철 비용               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,비단 비용              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,인구 비용              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(maxbuild               ,최대 생성수             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(downlevel              ,다운그레이드레벨           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(treereturn             ,목재 반환비용            ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(stonereturn            ,돌 반환비용             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(ironreturn             ,철 반환비용             ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(silkreturn             ,비단 반환비용            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(populationreturn       ,인구 반환비용            ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(s_p_speed              ,병사_생산_속도           ,int16                        ,15 , int16 , int16 , i16)\
		FIELD(s_p_cost               ,병사_생산_비용           ,int16                        ,16 , int16 , int16 , i16)\
		FIELD(s_output               ,병사_ 생산량            ,int16                        ,17 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Barrack가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Barrack_InheritedTable
	#define for_each_nEXCEL_Sys_T_Barrack_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Barrack_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Barrack가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Barrack가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Camp 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,레벨                 ,Sys_T_Camp_id_t              ,0 , Sys_T_Camp_id_t , uint16 , u16)\
		FIELD(client_file            ,건물 이미지 파일          ,tname256_t                   ,1 , tcstr , tcstr , t256)\
		FIELD(upgradetime            ,업그레이드 시간           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,목재 비용              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,돌 비용               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,철 비용               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,비단 비용              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,인구 비용              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(maxbuild               ,최대 생성수             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(downlevel              ,다운그레이드레벨           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(treereturn             ,목재 반환비용            ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(stonereturn            ,돌 반환비용             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(ironreturn             ,철 반환비용             ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(silkreturn             ,비단 반환비용            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(populationreturn       ,인구 반환비용            ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(f_r_spend              ,병사_ 식량_소비량         ,int16                        ,15 , int16 , int16 , i16)\
		FIELD(f_storage              ,병사_보관량             ,int32                        ,16 , int32 , int32 , i32)\

	#endif // for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Camp가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Camp_InheritedTable
	#define for_each_nEXCEL_Sys_T_Camp_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Camp_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Camp가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Camp가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Depot 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,레벨                 ,Sys_T_Depot_id_t             ,0 , Sys_T_Depot_id_t , uint16 , u16)\
		FIELD(client_file            ,건물 이미지 파일          ,tname256_t                   ,1 , tcstr , tcstr , t256)\
		FIELD(upgradetime            ,업그레이드 시간           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,목재 비용              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,돌 비용               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,철 비용               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,비단 비용              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,인구 비용              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(maxbuild               ,최대 생성수             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(downlevel              ,다운그레이드레벨           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(treereturn             ,목재 반환비용            ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(stonereturn            ,돌 반환비용             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(ironreturn             ,철 반환비용             ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(silkreturn             ,비단 반환비용            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(populationreturn       ,인구 반환비용            ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(storage                ,최대보관량              ,int32                        ,15 , int32 , int32 , i32)\

	#endif // for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Depot가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Depot_InheritedTable
	#define for_each_nEXCEL_Sys_T_Depot_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Depot_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Depot가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Depot가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Farm 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,레벨                 ,Sys_T_Farm_id_t              ,0 , Sys_T_Farm_id_t , uint16 , u16)\
		FIELD(client_file            ,건물 이미지 파일          ,tname256_t                   ,1 , tcstr , tcstr , t256)\
		FIELD(upgradetime            ,업그레이드 시간           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,목재 비용              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,돌 비용               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,철 비용               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,비단 비용              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,인구 비용              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(maxbuild               ,최대 생성수             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(downlevel              ,다운그레이드레벨           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(treereturn             ,목재 반환비용            ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(stonereturn            ,돌 반환비용             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(ironreturn             ,철 반환비용             ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(silkreturn             ,비단 반환비용            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(populationreturn       ,인구 반환비용            ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(foodoutput             ,식량생산량              ,int16                        ,15 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Farm가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Farm_InheritedTable
	#define for_each_nEXCEL_Sys_T_Farm_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Farm_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Farm가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Farm가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_House 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_House_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_House_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,레벨                 ,Sys_T_House_id_t             ,0 , Sys_T_House_id_t , uint16 , u16)\
		FIELD(client_file            ,건물 이미지 파일          ,tname256_t                   ,1 , tcstr , tcstr , t256)\
		FIELD(upgradetime            ,업그레이드 시간           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,목재 비용              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,돌 비용               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,철 비용               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,비단 비용              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,인구 비용              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(maxbuild               ,최대 생성수             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(downlevel              ,다운그레이드레벨           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(treereturn             ,목재 반환비용            ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(stonereturn            ,돌 반환비용             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(ironreturn             ,철 반환비용             ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(silkreturn             ,비단 반환비용            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(populationreturn       ,인구 반환비용            ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(maxpopulation          ,민가최대인구             ,int16                        ,15 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_House_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_House가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_House_InheritedTable
	#define for_each_nEXCEL_Sys_T_House_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_House_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_House가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_House가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_House_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_HQ 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,레벨                 ,Sys_T_HQ_id_t                ,0 , Sys_T_HQ_id_t , uint16 , u16)\
		FIELD(client_file            ,건물 이미지 파일          ,tname256_t                   ,1 , tcstr , tcstr , t256)\
		FIELD(upgradetime            ,업그레이드 시간           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,목재 비용              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,돌 비용               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,철 비용               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,비단 비용              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,인구 비용              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(maxbuild               ,최대 생성수             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(downlevel              ,다운그레이드레벨           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(treereturn             ,목재 반환비용            ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(stonereturn            ,돌 반환비용             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(ironreturn             ,철 반환비용             ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(silkreturn             ,비단 반환비용            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(populationreturn       ,인구 반환비용            ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(getgold                ,징수                 ,int16                        ,15 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_HQ가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_HQ_InheritedTable
	#define for_each_nEXCEL_Sys_T_HQ_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_HQ_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_HQ가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_HQ가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum EBuildType // 설명없음
	{
		eBEGIN_EBuildType = 0,
		/* 본영 */
		eEBT_Sys_T_HQ = 1, // 본영
		/* 주점 */
		eEBT_Sys_T_Bar = 2, // 주점
		/* 서원 */
		eEBT_ACADEMY = 3, // 서원
		/* 치안부 */
		eEBT_PEACE = 4, // 치안부
		/* 사당 */
		eEBT_SHRINE = 5, // 사당
		/* 감찰부 */
		eEBT_HIDEOUT = 6, // 감찰부
		/* 교역소 */
		eEBT_TRADINGPOST = 7, // 교역소
		/* 민가 */
		eEBT_Sys_T_House = 8, // 민가
		/* 농지 */
		eEBT_Sys_T_Farm = 9, // 농지
		/* 제재소 */
		eEBT_SAWMILL = 10, // 제재소
		/* 채석장 */
		eEBT_QUARRY = 11, // 채석장
		/* 광업장 */
		eEBT_MINING = 12, // 광업장
		/* 양잠소 */
		eEBT_COCOONERY = 13, // 양잠소
		/* 병영 */
		eEBT_Sys_T_Barrack = 14, // 병영
		/* 대장간 */
		eEBT_SMITHY = 15, // 대장간
		/* 공방 */
		eEBT_FORGE = 16, // 공방
		/* 마구간 */
		eEBT_STABLE = 17, // 마구간
		/* 둔영 */
		eEBT_Sys_T_Camp = 18, // 둔영
		/* 창고 */
		eEBT_Sys_T_Depot = 19, // 창고
		/* 비밀창고 */
		eEBT_SECRET = 20, // 비밀창고
		/* 망루 */
		eEBT_TOWER = 21, // 망루
		/* 방벽 */
		eEBT_BARRIER = 22, // 방벽
		eEND_EBuildType
	}; // EBuildType 



	enum EOutput // 설명없음
	{
		eBEGIN_EOutput = 0,
		/* 인구 */
		eEOT_POPULATION = 1, // 인구
		/* 금 */
		eEOT_GOLD = 2, // 금
		/* 식량 */
		eEOT_FOOD = 3, // 식량
		/* 목재 */
		eEOT_TREE = 4, // 목재
		/* 석재 */
		eEOT_STONE = 5, // 석재
		/* 철재 */
		eEOT_IRON = 6, // 철재
		/* 비단 */
		eEOT_SILK = 7, // 비단
		/* 병사 */
		eEOT_SOLDIER = 8, // 병사
		eEOT_PIKE = 9, // 창 병기
		eEOT_HEAVY = 10, // 중갑 병기
		/* 근위병 (철 소모 위주) */
		eEOT_HALBERD = 11, // 언월도 병기
		eEOT_BOW = 12, // 궁 병기
		eEOT_CROSSBOW = 13, // 노 병기
		eEOT_BOWGUN = 14, // 강노 병기
		eEOT_BALLISTA = 15, // 노포 병기
		/* 군마랑 조합해서만 가능 (개수 늘어나야) */
		eEOT_CHARIOT = 16, // 전차 병기
		/* 군마랑 조합해서만 가능 (개수 늘어나야) */
		eEOT_WAGON = 17, // 마차
		/* Eunit_ClassItemA 와 조합 가능 */
		eEOT_HORSE = 18, // 군마
		/* 공작, 수송, 보급 용도 */
		eEOT_WHEELBARROW = 19, // 수레
		eEOT_CART = 20, // 목우
		/* B만 활용 가능 */
		eEOT_SIEGE_LADDER = 21, // 운제
		eEOT_SIEGE_RAM = 22, // 충차
		eEOT_SIEGE_TOWER = 23, // 정란
		eEOT_SIEGE_TREBUCHET = 24, // 투석기
		eEND_EOutput
	}; // EOutput 





struct jEXCEL_LIB_API Sys__T_BuildObj /* 빌딩type 테이블의 base 테이블이다. 모든 빌딩type 테이블은 이 테이블을 상속받는다 */
{
	/*  Sys_T_BaseObj를상속 받는 테이블의 건물 종류 */
	EBuildType m_base_type; // 건물타입 min_max(,EBuildType)
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
	enum enumSys__T_BuildObj
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  8 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys__T_BuildObj
		jEXCEL_TABLE_COMMON_CODE_H_Sys__T_BuildObj();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys__T_BuildObj

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys__T_BuildObj)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys__T_BuildObj
enum { eSTRUCT_SIZE_Sys__T_BuildObj = sizeof(Sys__T_BuildObj) };


struct CSV_Sys__T_BuildObj : public nMech::nUtil::jCSV_File<Sys__T_BuildObj>
{
	virtual ~CSV_Sys__T_BuildObj(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys__T_BuildObj>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys__T_BuildObj g_Sys__T_BuildObj;

struct jEXCEL_LIB_API Sys_T_Bar /* 설명없음 */
{
	/*  건물 아이디 */
	Sys_T_Bar_id_t m_isid; // 레벨 min_max(,)
		typedef Sys_T_Bar_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 */
	tname256_t m_client_file; // 건물 이미지 파일 min_max(,)
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
	/*  한 마을에 최대 생성 가능한 건물 수 */
	int16 m_maxbuild; // 최대 생성수 min_max(,)
	/*  다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 */
	int16 m_downlevel; // 다운그레이드레벨 min_max(,)
	/*  건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) */
	int16 m_treereturn; // 목재 반환비용 min_max(,)
	int16 m_stonereturn; // 돌 반환비용 min_max(,)
	int16 m_ironreturn; // 철 반환비용 min_max(,)
	int16 m_silkreturn; // 비단 반환비용 min_max(,)
	/*  건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. */
	int16 m_populationreturn; // 인구 반환비용 min_max(,)
	/*  주점에 들어오는 재야장수 수 */
	int16 m_hideHero; // 재야 장수 min_max(,)
	/*  주점에서 자동으로 재야장수와 아이템이 리셋되는 시간 (초로계산) */
	uint32 m_resettime; // 리셋시간 min_max(,)
	/*  주점에서 행상인이 1회에 가져오는 아이템 수 */
	int16 m_itemnum; // 아이템수 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_T_Bar
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  18 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Bar
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Bar();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Bar

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Bar)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Bar
enum { eSTRUCT_SIZE_Sys_T_Bar = sizeof(Sys_T_Bar) };


struct CSV_Sys_T_Bar : public nMech::nUtil::jCSV_File<Sys_T_Bar>
{
	virtual ~CSV_Sys_T_Bar(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Bar>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Bar g_Sys_T_Bar;

struct jEXCEL_LIB_API Sys_T_Barrack /* 설명없음 */
{
	/*  건물 아이디 */
	Sys_T_Barrack_id_t m_isid; // 레벨 min_max(,)
		typedef Sys_T_Barrack_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 */
	tname256_t m_client_file; // 건물 이미지 파일 min_max(,)
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
	/*  한 마을에 최대 생성 가능한 건물 수 */
	int16 m_maxbuild; // 최대 생성수 min_max(,)
	/*  다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 */
	int16 m_downlevel; // 다운그레이드레벨 min_max(,)
	/*  건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) */
	int16 m_treereturn; // 목재 반환비용 min_max(,)
	int16 m_stonereturn; // 돌 반환비용 min_max(,)
	int16 m_ironreturn; // 철 반환비용 min_max(,)
	int16 m_silkreturn; // 비단 반환비용 min_max(,)
	/*  건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. */
	int16 m_populationreturn; // 인구 반환비용 min_max(,)
	/*  병영 레벨업당 생산속도 향상 */
	int16 m_s_p_speed; // 병사_생산_속도 min_max(,)
	/*  병영병사 1인 생산 비용 */
	int16 m_s_p_cost; // 병사_생산_비용 min_max(,)
	/*  병영병사 최대 생산량 */
	int16 m_s_output; // 병사_ 생산량 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_T_Barrack
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  18 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Barrack
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Barrack();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Barrack

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Barrack)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Barrack
enum { eSTRUCT_SIZE_Sys_T_Barrack = sizeof(Sys_T_Barrack) };


struct CSV_Sys_T_Barrack : public nMech::nUtil::jCSV_File<Sys_T_Barrack>
{
	virtual ~CSV_Sys_T_Barrack(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Barrack>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Barrack g_Sys_T_Barrack;

struct jEXCEL_LIB_API Sys_T_Camp /* 설명없음 */
{
	/*  건물 아이디 */
	Sys_T_Camp_id_t m_isid; // 레벨 min_max(,)
		typedef Sys_T_Camp_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 */
	tname256_t m_client_file; // 건물 이미지 파일 min_max(,)
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
	/*  한 마을에 최대 생성 가능한 건물 수 */
	int16 m_maxbuild; // 최대 생성수 min_max(,)
	/*  다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 */
	int16 m_downlevel; // 다운그레이드레벨 min_max(,)
	/*  건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) */
	int16 m_treereturn; // 목재 반환비용 min_max(,)
	int16 m_stonereturn; // 돌 반환비용 min_max(,)
	int16 m_ironreturn; // 철 반환비용 min_max(,)
	int16 m_silkreturn; // 비단 반환비용 min_max(,)
	/*  건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. */
	int16 m_populationreturn; // 인구 반환비용 min_max(,)
	/*  병사 1인이 시간당 소비하는 식량의 양 */
	int16 m_f_r_spend; // 병사_ 식량_소비량 min_max(,)
	/*  둔영에서 병사 최대 보관량 */
	int32 m_f_storage; // 병사_보관량 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_T_Camp
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  17 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Camp
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Camp();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Camp

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Camp)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Camp
enum { eSTRUCT_SIZE_Sys_T_Camp = sizeof(Sys_T_Camp) };


struct CSV_Sys_T_Camp : public nMech::nUtil::jCSV_File<Sys_T_Camp>
{
	virtual ~CSV_Sys_T_Camp(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Camp>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Camp g_Sys_T_Camp;

struct jEXCEL_LIB_API Sys_T_Depot /* 설명없음 */
{
	/*  건물 아이디 */
	Sys_T_Depot_id_t m_isid; // 레벨 min_max(,)
		typedef Sys_T_Depot_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 */
	tname256_t m_client_file; // 건물 이미지 파일 min_max(,)
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
	/*  한 마을에 최대 생성 가능한 건물 수 */
	int16 m_maxbuild; // 최대 생성수 min_max(,)
	/*  다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 */
	int16 m_downlevel; // 다운그레이드레벨 min_max(,)
	/*  건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) */
	int16 m_treereturn; // 목재 반환비용 min_max(,)
	int16 m_stonereturn; // 돌 반환비용 min_max(,)
	int16 m_ironreturn; // 철 반환비용 min_max(,)
	int16 m_silkreturn; // 비단 반환비용 min_max(,)
	/*  건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. */
	int16 m_populationreturn; // 인구 반환비용 min_max(,)
	/*  창고에서 자원 최대 보관량 */
	int32 m_storage; // 최대보관량 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_T_Depot
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  16 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Depot
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Depot();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Depot

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Depot)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Depot
enum { eSTRUCT_SIZE_Sys_T_Depot = sizeof(Sys_T_Depot) };


struct CSV_Sys_T_Depot : public nMech::nUtil::jCSV_File<Sys_T_Depot>
{
	virtual ~CSV_Sys_T_Depot(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Depot>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Depot g_Sys_T_Depot;

struct jEXCEL_LIB_API Sys_T_Farm /* 설명없음 */
{
	/*  건물 아이디 */
	Sys_T_Farm_id_t m_isid; // 레벨 min_max(,)
		typedef Sys_T_Farm_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 */
	tname256_t m_client_file; // 건물 이미지 파일 min_max(,)
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
	/*  한 마을에 최대 생성 가능한 건물 수 */
	int16 m_maxbuild; // 최대 생성수 min_max(,)
	/*  다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 */
	int16 m_downlevel; // 다운그레이드레벨 min_max(,)
	/*  건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) */
	int16 m_treereturn; // 목재 반환비용 min_max(,)
	int16 m_stonereturn; // 돌 반환비용 min_max(,)
	int16 m_ironreturn; // 철 반환비용 min_max(,)
	int16 m_silkreturn; // 비단 반환비용 min_max(,)
	/*  건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. */
	int16 m_populationreturn; // 인구 반환비용 min_max(,)
	/*  농가 레벨업당 농지 생산량 */
	int16 m_foodoutput; // 식량생산량 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_T_Farm
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  16 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Farm
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Farm();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Farm

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Farm)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Farm
enum { eSTRUCT_SIZE_Sys_T_Farm = sizeof(Sys_T_Farm) };


struct CSV_Sys_T_Farm : public nMech::nUtil::jCSV_File<Sys_T_Farm>
{
	virtual ~CSV_Sys_T_Farm(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Farm>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Farm g_Sys_T_Farm;

struct jEXCEL_LIB_API Sys_T_House /* 설명없음 */
{
	/*  건물 아이디 */
	Sys_T_House_id_t m_isid; // 레벨 min_max(,)
		typedef Sys_T_House_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 */
	tname256_t m_client_file; // 건물 이미지 파일 min_max(,)
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
	/*  한 마을에 최대 생성 가능한 건물 수 */
	int16 m_maxbuild; // 최대 생성수 min_max(,)
	/*  다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 */
	int16 m_downlevel; // 다운그레이드레벨 min_max(,)
	/*  건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) */
	int16 m_treereturn; // 목재 반환비용 min_max(,)
	int16 m_stonereturn; // 돌 반환비용 min_max(,)
	int16 m_ironreturn; // 철 반환비용 min_max(,)
	int16 m_silkreturn; // 비단 반환비용 min_max(,)
	/*  건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. */
	int16 m_populationreturn; // 인구 반환비용 min_max(,)
	/*  민가 레벨당 상승되는 최대 인구수 */
	int16 m_maxpopulation; // 민가최대인구 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_T_House
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_House_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  16 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_House
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_House();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_House

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_House_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_House)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_House
enum { eSTRUCT_SIZE_Sys_T_House = sizeof(Sys_T_House) };


struct CSV_Sys_T_House : public nMech::nUtil::jCSV_File<Sys_T_House>
{
	virtual ~CSV_Sys_T_House(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_House>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_House g_Sys_T_House;

struct jEXCEL_LIB_API Sys_T_HQ /* 설명없음 */
{
	/*  건물 아이디 */
	Sys_T_HQ_id_t m_isid; // 레벨 min_max(,)
		typedef Sys_T_HQ_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  건물 이미지: 레벨에 따라 이미지 변경 -맵툴에 있는 리소스 이름 */
	tname256_t m_client_file; // 건물 이미지 파일 min_max(,)
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
	/*  한 마을에 최대 생성 가능한 건물 수 */
	int16 m_maxbuild; // 최대 생성수 min_max(,)
	/*  다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 */
	int16 m_downlevel; // 다운그레이드레벨 min_max(,)
	/*  건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) */
	int16 m_treereturn; // 목재 반환비용 min_max(,)
	int16 m_stonereturn; // 돌 반환비용 min_max(,)
	int16 m_ironreturn; // 철 반환비용 min_max(,)
	int16 m_silkreturn; // 비단 반환비용 min_max(,)
	/*  건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. */
	int16 m_populationreturn; // 인구 반환비용 min_max(,)
	/*  징수 명령 */
	int16 m_getgold; // 징수 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_T_HQ
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  16 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_HQ
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_HQ();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_HQ

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_HQ)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_HQ
enum { eSTRUCT_SIZE_Sys_T_HQ = sizeof(Sys_T_HQ) };


struct CSV_Sys_T_HQ : public nMech::nUtil::jCSV_File<Sys_T_HQ>
{
	virtual ~CSV_Sys_T_HQ(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_HQ>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_HQ g_Sys_T_HQ;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_user_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBuildType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EOutput[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nEXCEL_excel_user_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_user_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_user_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_user_
