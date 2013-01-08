/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_etc_
#define __namespace_nEXCEL___filename_excel_baseball_table_etc_

#include "table_const_excel_baseball_table_etc.h"
// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_etc_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_BreakingBallUpgrade,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_BreakingBallUpgrade 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD(FIELD)\
		FIELD(id                     ,id                 ,Sys_BreakingBallState_id_t   ,0 , Sys_BreakingBallState_id_t , uint16 , u16)\
		FIELD(name                   ,name               ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(type                   ,변화구타입              ,EPlayerBreakingBall          ,2 , EPlayerBreakingBall , EPlayerBreakingBall , e)\
		FIELD(need_basicskill1       ,업그레이드 필요 투구폼1      ,EPitcherForm                 ,3 , EPitcherForm , EPitcherForm , e)\
		FIELD(need_basicskill2       ,업그레이드 필요 투구폼2      ,EPitcherForm                 ,4 , EPitcherForm , EPitcherForm , e)\
		FIELD(need_upgrade1          ,업그레이드 필요 변화구1      ,EPlayerBreakingBall          ,5 , EPlayerBreakingBall , EPlayerBreakingBall , e)\
		FIELD(need_upgrade2          ,업그레이드 필요 변화구2      ,EPlayerBreakingBall          ,6 , EPlayerBreakingBall , EPlayerBreakingBall , e)\
		FIELD(need_player_level      ,업그레이드 가능 플레이어 레벨   ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(equip_player_level     ,장착 가능 플레이어 레벨      ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(upgrade_need_time1     ,변화구1의 업그레이드시간1     ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(upgrade_need_time2     ,변화구2의 업그레이드시간2     ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(need_money             ,업그레이드비용            ,game_money_t                 ,11 , int32 , int32 , i32)\
		FIELD(breaking_pitch         ,변화구 구질             ,EBreakingBallPitch           ,12 , EBreakingBallPitch , EBreakingBallPitch , e)\
		FIELD(ball_rotation          ,볼 회전 방향            ,EBreakingBallRotation        ,13 , EBreakingBallRotation , EBreakingBallRotation , e)\
		FIELD(open_date              ,적용 일시              ,SYSTEMTIME                   ,14 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(first_open_breakingball,최초 오픈 선택 변화구       ,bool                         ,15 , bool , bool , b)\

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



struct jEXCEL_LIB_API Sys_BreakingBallUpgrade /* 설명없음 */
{
	/*  id */
	Sys_BreakingBallState_id_t m_id; // id min_max(,)
	/*  name */
	tname32_t m_name; // name min_max(,)
	/*  변화구 이름 */
	EPlayerBreakingBall m_type; // 변화구타입 min_max(,EPlayerBreakingBall)
	/*  업그레이드에 필요한 투구폼(null일 경우 어떠한 투구폼이 와도 상관 없음) */
	EPitcherForm m_need_basicskill1; // 업그레이드 필요 투구폼1 min_max(,EPitcherForm)
	/*  업그레이드에 필요한 투구폼(null일 경우 어떠한 투구폼이 와도 상관 없음) */
	EPitcherForm m_need_basicskill2; // 업그레이드 필요 투구폼2 min_max(,EPitcherForm)
	/*  업그레이드에 필요한 변화구 (레벨 값 1은 업그레이드 불가 null일 경우 기본 변화구) */
	EPlayerBreakingBall m_need_upgrade1; // 업그레이드 필요 변화구1 min_max(,EPlayerBreakingBall)
	/*  업그레이드에 필요한 변화구 (레벨 값 1은 업그레이드 불가) */
	EPlayerBreakingBall m_need_upgrade2; // 업그레이드 필요 변화구2 min_max(,EPlayerBreakingBall)
	/*  업그레이드 필요 플레이어 레벨 */
	int16 m_need_player_level; // 업그레이드 가능 플레이어 레벨 min_max(1,100)
	/*  업그레이드 필요 플레이어 레벨 */
	int16 m_equip_player_level; // 장착 가능 플레이어 레벨 min_max(1,100)
	/*  업그레이드 필요 시간 */
	int16 m_upgrade_need_time1; // 변화구1의 업그레이드시간1 min_max(0,100)
	/*  업그레이드에 변화구가 2개 이상 필요 경우에는 변화구를 2개 모두 트레이닝 완료 해야 함으로 필요 */
	int16 m_upgrade_need_time2; // 변화구2의 업그레이드시간2 min_max(0,100)
	/*  업그레이드 필요 게임머니 */
	game_money_t m_need_money; // 업그레이드비용 min_max(,)
	/*  변화구의 종횡변화 구분 */
	EBreakingBallPitch m_breaking_pitch; // 변화구 구질 min_max(,EBreakingBallPitch)
	/*  변화구 공의 회전 방향 구분 */
	EBreakingBallRotation m_ball_rotation; // 볼 회전 방향 min_max(,EBreakingBallRotation)
	/*  변화구 적용 일자 */
	SYSTEMTIME m_open_date; // 적용 일시 min_max(,)
	/*  캐릭터 생성 시 선택 할수 있는 변화구 인지 아닌지 구분 (0=불가능 1=가능) */
	bool m_first_open_breakingball; // 최초 오픈 선택 변화구 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_BreakingBallUpgrade
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  16 };
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


struct CSV_Sys_BreakingBallUpgrade : public nMech::nUtil::jCSV_File<Sys_BreakingBallUpgrade>
{
	virtual ~CSV_Sys_BreakingBallUpgrade(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_BreakingBallUpgrade>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_BreakingBallUpgrade g_Sys_BreakingBallUpgrade;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_baseball_table_etc_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_baseball_table_etc_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_baseball_table_etc_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_baseball_table_etc_
