/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_force_
#define __namespace_nEXCEL___filename_excel_force_

#include "table_const_excel_force.h"
// -------------------------------------------------
// enum형 코드 템플릿 정의
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nEXCEL_excel_force_ENUM(ENUM_TABLE)\
	ENUM_TABLE(E_ClassItemA,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(E_ClassItemB,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(E_W_Event,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EForceClass,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(EForcePosType,설명없음,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// 주의 enum변수는 앞에 e가 자동으로 붙어서 선언됨 
	// -------------------------------------------------

	/* 설명없음 */
	#define for_each_nEXCEL_E_ClassItemA_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(CIA_NOT			,1,병기 없음,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_PIKE			,2,창 병기,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_HEAVY			,3,중갑 병기,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_HALBERD			,4,언월도 병기,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_BOW			,5,궁 병기,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_CROSSBOW			,6,노 병기,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_BOWGUN			,7,강노 병기,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_BALLISTA			,8,노포 병기,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_CHARIOT			,9,전차 병기,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_WAGON			,10,마차,nMech,nEXCEL,E_ClassItemA)\

	/* 설명없음 */
	#define for_each_nEXCEL_E_ClassItemB_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(CIB_NOT			,1,탈것 없음,nMech,nEXCEL,E_ClassItemB)\
		ENUM_FIELD(CIB_HORSE			,2,군마,nMech,nEXCEL,E_ClassItemB)\
		ENUM_FIELD(CIB_WHEELBARROW			,3,수레,nMech,nEXCEL,E_ClassItemB)\
		ENUM_FIELD(CIB_CART			,4,목우,nMech,nEXCEL,E_ClassItemB)\
		ENUM_FIELD(CIB_SIEGE_LADDER			,5,운제,nMech,nEXCEL,E_ClassItemB)\
		ENUM_FIELD(CIB_SIEGE_RAM			,6,충차,nMech,nEXCEL,E_ClassItemB)\
		ENUM_FIELD(CIB_SIEGE_TOWER			,7,정란,nMech,nEXCEL,E_ClassItemB)\
		ENUM_FIELD(CIB_SIEGE_TREBUCHET			,8,투석기,nMech,nEXCEL,E_ClassItemB)\

	/* 설명없음 */
	#define for_each_nEXCEL_E_W_Event_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ENV_SUNNY			,1,맑음,nMech,nEXCEL,E_W_Event)\
		ENUM_FIELD(ENV_RAIN			,2,비 속성,nMech,nEXCEL,E_W_Event)\
		ENUM_FIELD(ENV_MIST			,3,안개 속성,nMech,nEXCEL,E_W_Event)\
		ENUM_FIELD(ENV_TIME			,4,밤낮 속성,nMech,nEXCEL,E_W_Event)\
		ENUM_FIELD(ENV_CALAMITY			,5,천재 지변,nMech,nEXCEL,E_W_Event)\
		ENUM_FIELD(ENV_LUCK			,6,축복,nMech,nEXCEL,E_W_Event)\

	/* 설명없음 */
	#define for_each_nEXCEL_EForceClass_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(FC_COMMON			,1,공용,nMech,nEXCEL,EForceClass)\
		ENUM_FIELD(FC_INFANTRY			,2,보병,nMech,nEXCEL,EForceClass)\
		ENUM_FIELD(FC_ARCHER			,3,궁병,nMech,nEXCEL,EForceClass)\
		ENUM_FIELD(FC_CABALRY			,4,기병,nMech,nEXCEL,EForceClass)\
		ENUM_FIELD(FC_SIEGE			,5,공성무기,nMech,nEXCEL,EForceClass)\

	/* 설명없음 */
	#define for_each_nEXCEL_EForcePosType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(FPT_TOWN			,1,마을,nMech,nEXCEL,EForcePosType)\
		ENUM_FIELD(FPT_CASTLE			,2,성,nMech,nEXCEL,EForcePosType)\
		ENUM_FIELD(FPT_CASTLEMAP			,3,성지역맵,nMech,nEXCEL,EForcePosType)\
		ENUM_FIELD(FPT_WORLDMAP			,4,월드맵,nMech,nEXCEL,EForcePosType)\


// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_force_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Force,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Force 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Force_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Force_STRUCT_FIELD(FIELD)\
		FIELD(fsid                   ,숫자_ID              ,Sys_Force_id_t               ,0 , Sys_Force_id_t , uint16 , u16)\
		FIELD(name                   ,이름_ID              ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(name_kor               ,병과이름               ,tname32_t                    ,2 , tcstr , tcstr , t32)\
		FIELD(force_class            ,병과분류               ,EForceClass                  ,3 , EForceClass , EForceClass , e)\
		FIELD(forceClassItemA        ,병과슬롯_아이템 A         ,E_ClassItemA                 ,4 , E_ClassItemA , E_ClassItemA , e)\
		FIELD(forceClassItemB        ,병과슬롯_아이템 B         ,E_ClassItemB                 ,5 , E_ClassItemB , E_ClassItemB , e)\
		FIELD(att                    ,공격력                ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(def                    ,방어력                ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(mspeed                 ,이동_속도              ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(aspeed                 ,공격_속도              ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(srange                 ,가시거리               ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(suvival_ratio          ,생존율                ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(kill_ratio             ,살상율                ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(client_id              ,클라이언트ID            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(unit_load              ,적재량                ,int16                        ,14 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_Force_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Force가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Force_InheritedTable
	#define for_each_nEXCEL_Sys_Force_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Force_InheritedTable


	// ------------------------------------------------------------
	// Sys_Force가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Force_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Force_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Force_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Force가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Force_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Force_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Force_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Force_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Force_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum E_ClassItemA // 설명없음
	{
		eBEGIN_E_ClassItemA = 0,
		/* 보병 병과 자동 분류 */
		eCIA_NOT = 1, // 병기 없음
		eCIA_PIKE = 2, // 창 병기
		eCIA_HEAVY = 3, // 중갑 병기
		/* 근위병 (철 소모 위주) */
		eCIA_HALBERD = 4, // 언월도 병기
		eCIA_BOW = 5, // 궁 병기
		eCIA_CROSSBOW = 6, // 노 병기
		eCIA_BOWGUN = 7, // 강노 병기
		eCIA_BALLISTA = 8, // 노포 병기
		/* 군마랑 조합해서만 가능 (개수 늘어나야) */
		eCIA_CHARIOT = 9, // 전차 병기
		/* 군마랑 조합해서만 가능 (개수 늘어나야) */
		eCIA_WAGON = 10, // 마차
		eEND_E_ClassItemA
	}; // E_ClassItemA 



	enum E_ClassItemB // 설명없음
	{
		eBEGIN_E_ClassItemB = 0,
		eCIB_NOT = 1, // 탈것 없음
		/* Eunit_ClassItemA 와 조합 가능 */
		eCIB_HORSE = 2, // 군마
		/* 공작, 수송, 보급 용도 */
		eCIB_WHEELBARROW = 3, // 수레
		eCIB_CART = 4, // 목우
		/* B만 활용 가능 */
		eCIB_SIEGE_LADDER = 5, // 운제
		eCIB_SIEGE_RAM = 6, // 충차
		eCIB_SIEGE_TOWER = 7, // 정란
		eCIB_SIEGE_TREBUCHET = 8, // 투석기
		eEND_E_ClassItemB
	}; // E_ClassItemB 



	enum E_W_Event // 설명없음
	{
		eBEGIN_E_W_Event = 0,
		/* 속성 없는 경우 */
		eENV_SUNNY = 1, // 맑음
		/* 화계 힘듬, 수계 좋음 */
		eENV_RAIN = 2, // 비 속성
		/* 시야 감소  / 사거리 변화 */
		eENV_MIST = 3, // 안개 속성
		/* 시야 감소  / 사거리 변화 */
		eENV_TIME = 4, // 밤낮 속성
		/* 지진/역병/가뭄/폭염/홍수/태풍/흉작/메뚜기떼/한파 */
		eENV_CALAMITY = 5, // 천재 지변
		/* 풍작/다산 */
		eENV_LUCK = 6, // 축복
		eEND_E_W_Event
	}; // E_W_Event 



	enum EForceClass // 설명없음
	{
		eBEGIN_EForceClass = 0,
		eFC_COMMON = 1, // 공용
		eFC_INFANTRY = 2, // 보병
		eFC_ARCHER = 3, // 궁병
		eFC_CABALRY = 4, // 기병
		eFC_SIEGE = 5, // 공성무기
		eEND_EForceClass
	}; // EForceClass 



	enum EForcePosType // 설명없음
	{
		eBEGIN_EForcePosType = 0,
		/* 마을 */
		eFPT_TOWN = 1, // 마을
		/* 성 */
		eFPT_CASTLE = 2, // 성
		/* 성지역맵 */
		eFPT_CASTLEMAP = 3, // 성지역맵
		/* 월드맵 */
		eFPT_WORLDMAP = 4, // 월드맵
		eEND_EForcePosType
	}; // EForcePosType 





struct jEXCEL_LIB_API Sys_Force /* 설명없음 */
{
	/*  병과 ID */
	Sys_Force_id_t m_fsid; // 숫자_ID min_max(,)
		typedef Sys_Force_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_fsid; }
	void SetPrimaryKey(primary_key_t id) { m_fsid = id; }
	/*  이름 ID */
	tname32_t m_name; // 이름_ID min_max(,)
	/*  병과 이름 */
	tname32_t m_name_kor; // 병과이름 min_max(,)
	/*  병과 분류 */
	EForceClass m_force_class; // 병과분류 min_max(,EForceClass)
	/*  병기 슬롯 A */
	E_ClassItemA m_forceClassItemA; // 병과슬롯_아이템 A min_max(,E_ClassItemA)
	/*  병기 슬롯 B */
	E_ClassItemB m_forceClassItemB; // 병과슬롯_아이템 B min_max(,E_ClassItemB)
	/*  공격력 보정 */
	int16 m_att; // 공격력 min_max(0,100)
	/*  방어력 보정 */
	int16 m_def; // 방어력 min_max(0,100)
	/*  이동 속도 보정 */
	int16 m_mspeed; // 이동_속도 min_max(0,1000)
	/*  공격 속도 보정 / msec 보정 */
	int16 m_aspeed; // 공격_속도 min_max(0,10000)
	/*  가시거리 */
	int16 m_srange; // 가시거리 min_max(0,100)
	/*  살아날 확률 / % 랜덤값 (xx.x%) */
	int16 m_suvival_ratio; // 생존율 min_max(0,1000)
	/*  사망시킬 확률 / % 랜덤값 (xx.x%) */
	int16 m_kill_ratio; // 살상율 min_max(0,1000)
	/*  클라이언트에서 나오는 유닛 이미지 id 번호 */
	int16 m_client_id; // 클라이언트ID min_max(0,100)
	/*  물품 적재량 */
	int16 m_unit_load; // 적재량 min_max(0,100000)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Force
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Force_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  15 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Force
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Force();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Force

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Force_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Force)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Force
enum { eSTRUCT_SIZE_Sys_Force = sizeof(Sys_Force) };


struct CSV_Sys_Force : public nMech::nUtil::jCSV_File<Sys_Force>
{
	virtual ~CSV_Sys_Force(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Force>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Force g_Sys_Force;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_force_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_E_ClassItemA[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_E_ClassItemB[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_E_W_Event[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EForceClass[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EForcePosType[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nEXCEL_excel_force_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_force_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_force_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_force_
