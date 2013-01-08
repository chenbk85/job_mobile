/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table2_
#define __namespace_nEXCEL___filename_excel_baseball_table2_

#include "table_const_excel_baseball_table2.h"
// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table2_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_BreakingBallUpgrade,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_BreakingBallUpgrade 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD(FIELD)\
		FIELD(id                     ,id                 ,Sys_BreakingBallState_id_t   ,0 , Sys_BreakingBallState_id_t , uint16 , u16)\
		FIELD(name                   ,name               ,aname32_t                    ,1 , acstr , acstr , a32)\
		FIELD(breakingball_name      ,변화구명               ,EPlayerBreakingBall          ,2 , EPlayerBreakingBall , EPlayerBreakingBall , e)\
		FIELD(breakingball_result    ,업그레이드 필요 변화구       ,EPlayerBreakingBall          ,3 , EPlayerBreakingBall , EPlayerBreakingBall , e)\
		FIELD(breaking_need_level    ,업그레이드 필요 레벨        ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(breaking_pitch         ,변화구 구질             ,EBreakingBallPitch           ,5 , EBreakingBallPitch , EBreakingBallPitch , e)\
		FIELD(ball_rotation          ,볼 회전 방향            ,EBreakingBallRotation        ,6 , EBreakingBallRotation , EBreakingBallRotation , e)\
		FIELD(breaking_open_date     ,적용 일시              ,DATETIME                     ,7 , int32 , int32 , i32)\

	#endif // for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_BreakingBallUpgrade가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_BreakingBallUpgrade_InheritedTable
	#define for_each_nEXCEL_Sys_BreakingBallUpgrade_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_BreakingBallUpgrade_InheritedTable


	// ------------------------------------------------------------
	// Sys_BreakingBallUpgrade가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_BreakingBallUpgrade가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{



struct OUT Sys_BreakingBallUpgrade /* 설명없음 */
{
	/*  id */
	Sys_BreakingBallState_id_t m_id_u16; // id min_max(,)
	/*  name */
	aname32_t m_name_a32; // name min_max(,)
	/*  변화구 이름 */
	EPlayerBreakingBall m_breakingball_name_e; // 변화구명 min_max(,EPlayerBreakingBall)
	/*  업그레이드 필요 변화구 */
	EPlayerBreakingBall m_breakingball_result_e; // 업그레이드 필요 변화구 min_max(,EPlayerBreakingBall)
	/*  업그레이드 필요 레벨 */
	int16 m_breaking_need_level_i16; // 업그레이드 필요 레벨 min_max(0,100)
	EBreakingBallPitch m_breaking_pitch_e; // 변화구 구질 min_max(,EBreakingBallPitch)
	EBreakingBallRotation m_ball_rotation_e; // 볼 회전 방향 min_max(,EBreakingBallRotation)
	/*  변화구 적용 일자 */
	DATETIME m_breaking_open_date_i32; // 적용 일시 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_BreakingBallUpgrade
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  8 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_BreakingBallUpgrade
		jEXCEL_TABLE_COMMON_CODE_H_Sys_BreakingBallUpgrade();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_BreakingBallUpgrade

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_BreakingBallUpgrade)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_BreakingBallUpgrade
enum { eSTRUCT_SIZE_Sys_BreakingBallUpgrade = sizeof(Sys_BreakingBallUpgrade) };

extern OUT nMech::nUtil::jCSV_File<Sys_BreakingBallUpgrade> g_Sys_BreakingBallUpgrade;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_baseball_table2_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_baseball_table2_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_baseball_table2_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_baseball_table2_
