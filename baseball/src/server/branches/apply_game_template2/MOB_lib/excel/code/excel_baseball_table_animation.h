/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_animation_
#define __namespace_nEXCEL___filename_excel_baseball_table_animation_

#include "table_const_excel_baseball_table_animation.h"
// -------------------------------------------------
// enum형 코드 템플릿 정의
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nEXCEL_excel_baseball_table_animation_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EBatterAnimationType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(ECatcherAnimationType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EEumpireAnimationType,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EPitcherAnimationType,설명없음,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// 주의 enum변수는 앞에 e가 자동으로 붙어서 선언됨 
	// -------------------------------------------------

	/* 설명없음 */
	#define for_each_nEXCEL_EBatterAnimationType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EBAT_STARTUP			,1,Startup,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_MAXAFTER			,2,Max After,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_MAX			,3,Max,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_IDLE			,4,Idle,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_READY			,5,Ready,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_SWING_LEFT			,6,왼쪽 스윙,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_SWING_MIDDLE			,7,중간 스윙,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_SWING_RIGHT			,8,오른쪽 스윙,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_MAUVAIS			,9,헛스윙,nMech,nEXCEL,EBatterAnimationType)\

	/* 설명없음 */
	#define for_each_nEXCEL_ECatcherAnimationType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ECAT_STARTUP_IDLE			,1,Startup,nMech,nEXCEL,ECatcherAnimationType)\
		ENUM_FIELD(ECAT_MITCATCH			,2,미트 볼 캐치,nMech,nEXCEL,ECatcherAnimationType)\
		ENUM_FIELD(ECAT_MOVE_MIDDLE			,3,포수 중단 이동,nMech,nEXCEL,ECatcherAnimationType)\
		ENUM_FIELD(ECAT_MOVE_LEFT			,4,포수 왼쪽 이동,nMech,nEXCEL,ECatcherAnimationType)\
		ENUM_FIELD(ECAT_MOVE_RIGHT			,5,포수 오른쪽 이동,nMech,nEXCEL,ECatcherAnimationType)\
		ENUM_FIELD(ECAT_BACK_MIDDLE			,6,포수 중단 이동 후 돌아오기,nMech,nEXCEL,ECatcherAnimationType)\
		ENUM_FIELD(ECAT_BACK_LEFT			,7,포수 왼쪽 이동 후 돌아오기,nMech,nEXCEL,ECatcherAnimationType)\
		ENUM_FIELD(ECAT_BACK_RIGHT			,8,포수 오른쪽 이동 후 돌아오기,nMech,nEXCEL,ECatcherAnimationType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EEumpireAnimationType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EEAT_PLAYBALL			,1,경기 시작,nMech,nEXCEL,EEumpireAnimationType)\
		ENUM_FIELD(EEAT_IDLE			,2,대기 관전 아이들,nMech,nEXCEL,EEumpireAnimationType)\
		ENUM_FIELD(EEAT_DECISION_PERFECT			,3,퍼펙트 판정,nMech,nEXCEL,EEumpireAnimationType)\
		ENUM_FIELD(EEAT_DECISION_GOOD			,4,굳 판정,nMech,nEXCEL,EEumpireAnimationType)\
		ENUM_FIELD(EEAT_DECISION_NORMAL			,5,노멀 판정,nMech,nEXCEL,EEumpireAnimationType)\
		ENUM_FIELD(EEAT_DECISION_BAD			,6,배드 판정,nMech,nEXCEL,EEumpireAnimationType)\

	/* 설명없음 */
	#define for_each_nEXCEL_EPitcherAnimationType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EPAT_STARTUP_IDL			,1,대기 아이들 1,nMech,nEXCEL,EPitcherAnimationType)\
		ENUM_FIELD(EPAT_HIT_AFTER			,2,투수 히트 후 고개 동작(좌 우),nMech,nEXCEL,EPitcherAnimationType)\
		ENUM_FIELD(EPAT_YES			,3,투수 사인 수락,nMech,nEXCEL,EPitcherAnimationType)\
		ENUM_FIELD(EPAT_NO			,4,투수 사인 거부,nMech,nEXCEL,EPitcherAnimationType)\
		ENUM_FIELD(EPAT_STARTUP			,5,Startup,nMech,nEXCEL,EPitcherAnimationType)\
		ENUM_FIELD(EPAT_PITCHING			,6,투구,nMech,nEXCEL,EPitcherAnimationType)\
		ENUM_FIELD(EPAT_BACK			,7,투구 후 되돌아가기,nMech,nEXCEL,EPitcherAnimationType)\
		ENUM_FIELD(EPAT_CEREMONY			,8,세리머니,nMech,nEXCEL,EPitcherAnimationType)\


// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_animation_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Batter_Animation,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_Catcher_Animation,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_Pitcher_Animation,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_Umpire_Animation,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Batter_Animation 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD(FIELD)\
		FIELD(index                  ,index              ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(body_type              ,체형                 ,EPlayerBodyType              ,1 , EPlayerBodyType , EPlayerBodyType , e)\
		FIELD(better_form            ,타격 폼               ,EBatterForm                  ,2 , EBatterForm , EBatterForm , e)\
		FIELD(batter_animation       ,타자애니메이션            ,EBatterAnimationType         ,3 , EBatterAnimationType , EBatterAnimationType , e)\
		FIELD(animation_number       ,해당 애니메이션 넘버        ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(animation_filename     ,해당 애니메이션 파일 이름     ,aname32_t                    ,5 , acstr , acstr , a32)\

	#endif // for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Batter_Animation가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Batter_Animation_InheritedTable
	#define for_each_nEXCEL_Sys_Batter_Animation_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Batter_Animation_InheritedTable


	// ------------------------------------------------------------
	// Sys_Batter_Animation가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Batter_Animation가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Catcher_Animation 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD(FIELD)\
		FIELD(index                  ,index              ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(catcher_animation      ,포수애니메이션            ,ECatcherAnimationType        ,1 , ECatcherAnimationType , ECatcherAnimationType , e)\
		FIELD(animation_number       ,해당 애니메이션 넘버        ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(animation_filename     ,해당 애니메이션 파일 이름     ,aname32_t                    ,3 , acstr , acstr , a32)\

	#endif // for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Catcher_Animation가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Catcher_Animation_InheritedTable
	#define for_each_nEXCEL_Sys_Catcher_Animation_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Catcher_Animation_InheritedTable


	// ------------------------------------------------------------
	// Sys_Catcher_Animation가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Catcher_Animation가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Pitcher_Animation 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD(FIELD)\
		FIELD(index                  ,index              ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(body_type              ,체형                 ,EPlayerBodyType              ,1 , EPlayerBodyType , EPlayerBodyType , e)\
		FIELD(pitcher_form           ,투구폼                ,EPitcherForm                 ,2 , EPitcherForm , EPitcherForm , e)\
		FIELD(pitcher_animation      ,투수애니메이션            ,EPitcherAnimationType        ,3 , EPitcherAnimationType , EPitcherAnimationType , e)\
		FIELD(animation_number       ,해당 애니메이션 넘버        ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(animation_filename     ,해당 애니메이션 파일 이름     ,aname32_t                    ,5 , acstr , acstr , a32)\

	#endif // for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Pitcher_Animation가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Pitcher_Animation_InheritedTable
	#define for_each_nEXCEL_Sys_Pitcher_Animation_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Pitcher_Animation_InheritedTable


	// ------------------------------------------------------------
	// Sys_Pitcher_Animation가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Pitcher_Animation가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Umpire_Animation 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD(FIELD)\
		FIELD(index                  ,index              ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(umpire_animation       ,심판애니메이션            ,EEumpireAnimationType        ,1 , EEumpireAnimationType , EEumpireAnimationType , e)\
		FIELD(animation_number       ,해당 애니메이션 넘버        ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(animation_filename     ,해당 애니메이션 파일 이름     ,aname32_t                    ,3 , acstr , acstr , a32)\

	#endif // for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Umpire_Animation가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Umpire_Animation_InheritedTable
	#define for_each_nEXCEL_Sys_Umpire_Animation_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Umpire_Animation_InheritedTable


	// ------------------------------------------------------------
	// Sys_Umpire_Animation가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Umpire_Animation가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum EBatterAnimationType // 설명없음
	{
		eBEGIN_EBatterAnimationType = 0,
		/* 배터박스에서 한손으로 투수에게 양해를 구하고, 발로 땅을 고르며 타격 자세 잡기 */
		eEBAT_STARTUP = 1, // Startup
		/* 각각의 스탠스에서 배트커서 맥시멈 당겼다가 평타 아이들로 복귀 */
		eEBAT_MAXAFTER = 2, // Max After
		/* 각각의 스탠스에서 배트커서 맥시멈 당겼을 때 아이들 */
		eEBAT_MAX = 3, // Max
		/* 각각의 스탠스에서 방망이를 1자로 세우고 약간 흔드는 자세 */
		eEBAT_IDLE = 4, // Idle
		/* 각각의 스탠스에서 타격준비 */
		eEBAT_READY = 5, // Ready
		/* 각각의 스탠스에서 왼쪽 스윙 (투수를 바라보는 시점에서) (1_하단 2_중하단 3_중단 4_중상단 5_상단) */
		eEBAT_SWING_LEFT = 6, // 왼쪽 스윙
		/* 각각의 스탠스에서 중간 스윙 (투수를 바라보는 시점에서) (1_하단 2_중하단 3_중단 4_중상단 5_상단) */
		eEBAT_SWING_MIDDLE = 7, // 중간 스윙
		/* 각각의 스탠스에서 오른쪽 스윙 (투수를 바라보는 시점에서) (1_하단 2_중하단 3_중단 4_중상단 5_상단) */
		eEBAT_SWING_RIGHT = 8, // 오른쪽 스윙
		/* 각각의 스탠스에서 헛스윙 */
		eEBAT_MAUVAIS = 9, // 헛스윙
		eEND_EBatterAnimationType
	}; // EBatterAnimationType 



	enum ECatcherAnimationType // 설명없음
	{
		eBEGIN_ECatcherAnimationType = 0,
		/* 투수 던지기 전 포수 아이들 */
		eECAT_STARTUP_IDLE = 1, // Startup
		/* 포수와 미트 모두 해당 위치 이동 상태에서 볼 캐치 동작 (1=하하단 2=하중단 3=하상단 4=중하단 5=중중단 6=중상단 7=상하단 8=상중단 9=상상단 10=최상하단 11=최상중단 12=최상상단) */
		eECAT_MITCATCH = 2, // 미트 볼 캐치
		/* 포수 전체 중단 이동 */
		eECAT_MOVE_MIDDLE = 3, // 포수 중단 이동
		/* 포수 전체 왼쪽 이동 */
		eECAT_MOVE_LEFT = 4, // 포수 왼쪽 이동
		/* 포수 전체 오른쪽 이동 */
		eECAT_MOVE_RIGHT = 5, // 포수 오른쪽 이동
		/* 포수 중단 이동 후 돌아오기 */
		eECAT_BACK_MIDDLE = 6, // 포수 중단 이동 후 돌아오기
		/* 포수 왼쪽 이동 후 돌아오기 */
		eECAT_BACK_LEFT = 7, // 포수 왼쪽 이동 후 돌아오기
		/* 포수 오른쪽 이동 후 돌아오기 */
		eECAT_BACK_RIGHT = 8, // 포수 오른쪽 이동 후 돌아오기
		eEND_ECatcherAnimationType
	}; // ECatcherAnimationType 



	enum EEumpireAnimationType // 설명없음
	{
		eBEGIN_EEumpireAnimationType = 0,
		/* 경기 시작 */
		eEEAT_PLAYBALL = 1, // 경기 시작
		/* 대기 관전 아이들 */
		eEEAT_IDLE = 2, // 대기 관전 아이들
		/* 퍼펙트 판정 */
		eEEAT_DECISION_PERFECT = 3, // 퍼펙트 판정
		/* 굳 판정 */
		eEEAT_DECISION_GOOD = 4, // 굳 판정
		/* 노멀 판정 */
		eEEAT_DECISION_NORMAL = 5, // 노멀 판정
		/* 배드 판정 */
		eEEAT_DECISION_BAD = 6, // 배드 판정
		eEND_EEumpireAnimationType
	}; // EEumpireAnimationType 



	enum EPitcherAnimationType // 설명없음
	{
		eBEGIN_EPitcherAnimationType = 0,
		/* 대기 동작중 숨쉬는 아이들 */
		eEPAT_STARTUP_IDL = 1, // 대기 아이들 1
		/* 투수 히트 후 고개 동작(좌=1 우=2) */
		eEPAT_HIT_AFTER = 2, // 투수 히트 후 고개 동작(좌 우)
		/* 대기 동작 마무리 고개 끄덕 */
		eEPAT_YES = 3, // 투수 사인 수락
		/* 대기 동작 중 고개 절래절래 */
		eEPAT_NO = 4, // 투수 사인 거부
		/* 송진을 만진 후 마운드 자리잡기 */
		eEPAT_STARTUP = 5, // Startup
		/* 오버핸드에서 투구 시작, 대기 자세  포함 */
		eEPAT_PITCHING = 6, // 투구
		/* 투구 후 되돌아가기 */
		eEPAT_BACK = 7, // 투구 후 되돌아가기
		/* 타자가 히트하지 못했을 때 주먹을 앞으로 불끈 쥐며 아싸 */
		eEPAT_CEREMONY = 8, // 세리머니
		eEND_EPitcherAnimationType
	}; // EPitcherAnimationType 





struct jEXCEL_LIB_API Sys_Batter_Animation /* 설명없음 */
{
	/*  영문닉네임 , 각종테이블에서 사용 */
	int16 m_index; // index min_max(,)
		typedef int16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_index; }
	void SetPrimaryKey(primary_key_t id) { m_index = id; }
	/*  체형 */
	EPlayerBodyType m_body_type; // 체형 min_max(,EPlayerBodyType)
	/*  타격 폼 */
	EBatterForm m_better_form; // 타격 폼 min_max(,EBatterForm)
	/*  타자 애니메이션 종류 */
	EBatterAnimationType m_batter_animation; // 타자애니메이션 min_max(,EBatterAnimationType)
	/*  해당 애니메이션의 넘버 */
	int16 m_animation_number; // 해당 애니메이션 넘버 min_max(,)
	/*  해당 에니메이션 파일 이름 */
	aname32_t m_animation_filename; // 해당 애니메이션 파일 이름 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Batter_Animation
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  6 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Batter_Animation
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Batter_Animation();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Batter_Animation

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Batter_Animation)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Batter_Animation
enum { eSTRUCT_SIZE_Sys_Batter_Animation = sizeof(Sys_Batter_Animation) };


struct CSV_Sys_Batter_Animation : public nMech::nUtil::jCSV_File<Sys_Batter_Animation>
{
	virtual ~CSV_Sys_Batter_Animation(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Batter_Animation>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Batter_Animation g_Sys_Batter_Animation;

struct jEXCEL_LIB_API Sys_Catcher_Animation /* 설명없음 */
{
	/*  영문닉네임 , 각종테이블에서 사용 */
	int16 m_index; // index min_max(,)
		typedef int16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_index; }
	void SetPrimaryKey(primary_key_t id) { m_index = id; }
	/*  포수 애니메이션 종류 */
	ECatcherAnimationType m_catcher_animation; // 포수애니메이션 min_max(,ECatcherAnimationType)
	/*  해당 애니메이션의 넘버 */
	int16 m_animation_number; // 해당 애니메이션 넘버 min_max(,)
	/*  해당 에니메이션 파일 이름 */
	aname32_t m_animation_filename; // 해당 애니메이션 파일 이름 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Catcher_Animation
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  4 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Catcher_Animation
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Catcher_Animation();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Catcher_Animation

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Catcher_Animation)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Catcher_Animation
enum { eSTRUCT_SIZE_Sys_Catcher_Animation = sizeof(Sys_Catcher_Animation) };


struct CSV_Sys_Catcher_Animation : public nMech::nUtil::jCSV_File<Sys_Catcher_Animation>
{
	virtual ~CSV_Sys_Catcher_Animation(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Catcher_Animation>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Catcher_Animation g_Sys_Catcher_Animation;

struct jEXCEL_LIB_API Sys_Pitcher_Animation /* 설명없음 */
{
	/*  영문닉네임 , 각종테이블에서 사용 */
	int16 m_index; // index min_max(,)
		typedef int16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_index; }
	void SetPrimaryKey(primary_key_t id) { m_index = id; }
	/*  체형 */
	EPlayerBodyType m_body_type; // 체형 min_max(,EPlayerBodyType)
	/*  투구폼 */
	EPitcherForm m_pitcher_form; // 투구폼 min_max(,EPitcherForm)
	/*  투수 애니메이션 종류 */
	EPitcherAnimationType m_pitcher_animation; // 투수애니메이션 min_max(,EPitcherAnimationType)
	/*  해당 애니메이션의 넘버 */
	int16 m_animation_number; // 해당 애니메이션 넘버 min_max(,)
	/*  해당 에니메이션 파일 이름 */
	aname32_t m_animation_filename; // 해당 애니메이션 파일 이름 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Pitcher_Animation
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  6 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Pitcher_Animation
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Pitcher_Animation();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Pitcher_Animation

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Pitcher_Animation)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Pitcher_Animation
enum { eSTRUCT_SIZE_Sys_Pitcher_Animation = sizeof(Sys_Pitcher_Animation) };


struct CSV_Sys_Pitcher_Animation : public nMech::nUtil::jCSV_File<Sys_Pitcher_Animation>
{
	virtual ~CSV_Sys_Pitcher_Animation(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Pitcher_Animation>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Pitcher_Animation g_Sys_Pitcher_Animation;

struct jEXCEL_LIB_API Sys_Umpire_Animation /* 설명없음 */
{
	/*  영문닉네임 , 각종테이블에서 사용 */
	int16 m_index; // index min_max(,)
		typedef int16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_index; }
	void SetPrimaryKey(primary_key_t id) { m_index = id; }
	/*  심판 애니메이션 종류 */
	EEumpireAnimationType m_umpire_animation; // 심판애니메이션 min_max(,EEumpireAnimationType)
	/*  해당 애니메이션의 넘버 */
	int16 m_animation_number; // 해당 애니메이션 넘버 min_max(,)
	/*  해당 에니메이션 파일 이름 */
	aname32_t m_animation_filename; // 해당 애니메이션 파일 이름 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Umpire_Animation
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  4 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Umpire_Animation
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Umpire_Animation();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Umpire_Animation

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Umpire_Animation)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Umpire_Animation
enum { eSTRUCT_SIZE_Sys_Umpire_Animation = sizeof(Sys_Umpire_Animation) };


struct CSV_Sys_Umpire_Animation : public nMech::nUtil::jCSV_File<Sys_Umpire_Animation>
{
	virtual ~CSV_Sys_Umpire_Animation(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Umpire_Animation>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Umpire_Animation g_Sys_Umpire_Animation;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_baseball_table_animation_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBatterAnimationType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ECatcherAnimationType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EEumpireAnimationType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPitcherAnimationType[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nEXCEL_excel_baseball_table_animation_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_baseball_table_animation_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_baseball_table_animation_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_baseball_table_animation_
