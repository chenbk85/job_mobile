/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_castle_
#define __namespace_nEXCEL___filename_excel_castle_

#include "table_const_excel_castle.h"
// -------------------------------------------------
// enum형 코드 템플릿 정의
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nEXCEL_excel_castle_ENUM(ENUM_TABLE)\
	ENUM_TABLE(Evillage_Condition,설명없음,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// 주의 enum변수는 앞에 e가 자동으로 붙어서 선언됨 
	// -------------------------------------------------

	/* 설명없음 */
	#define for_each_nEXCEL_Evillage_Condition_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EVC_Normal			,1,일반,nMech,nEXCEL,Evillage_Condition)\
		ENUM_FIELD(EVC_OCCUPY			,2,점령중,nMech,nEXCEL,Evillage_Condition)\
		ENUM_FIELD(EVC_INACTIVE			,3,장기비접속,nMech,nEXCEL,Evillage_Condition)\
		ENUM_FIELD(EVC_ONLINE			,4,온라인,nMech,nEXCEL,Evillage_Condition)\
		ENUM_FIELD(EVC_OFFLINE			,5,오프라인,nMech,nEXCEL,Evillage_Condition)\


// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_castle_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Castle,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_CastlePos,설명없음,nMech,nEXCEL)\
	STRUCT(Sys_TownPos,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Castle 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Castle_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Castle_STRUCT_FIELD(FIELD)\
		FIELD(csid                   ,숫자_ID              ,uint16                       ,0 , uint16 , uint16 , i16)\
		FIELD(name                   ,이름_ID              ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(name_kor               ,성_이름               ,tname32_t                    ,2 , tcstr , tcstr , t32)\
		FIELD(default_gsid           ,기본_태수              ,Sys_Hero_id_t                ,3 , Sys_Hero_id_t , uint16 , u16)\
		FIELD(force_gen_name         ,부대생성규칙이름           ,tname32_t                    ,4 , tcstr , tcstr , t32)\

	#endif // for_each_nEXCEL_Sys_Castle_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Castle가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Castle_InheritedTable
	#define for_each_nEXCEL_Sys_Castle_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Castle_InheritedTable


	// ------------------------------------------------------------
	// Sys_Castle가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Castle_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Castle_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Castle_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Castle가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Castle_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Castle_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Castle_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Castle_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Castle_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_CastlePos 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD(FIELD)\
		FIELD(cpsid                  ,성 sid              ,Sys_Castle_id_t              ,0 , Sys_Castle_id_t , uint16 , u16)\
		FIELD(x                      ,x                  ,uint16                       ,1 , uint16 , uint16 , i16)\
		FIELD(y                      ,y                  ,uint16                       ,2 , uint16 , uint16 , i16)\
		FIELD(castle_map             ,castle_map파일       ,tname32_t                    ,3 , tcstr , tcstr , t32)\

	#endif // for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_CastlePos가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_CastlePos_InheritedTable
	#define for_each_nEXCEL_Sys_CastlePos_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_CastlePos_InheritedTable


	// ------------------------------------------------------------
	// Sys_CastlePos가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_CastlePos가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_TownPos 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD(FIELD)\
		FIELD(tpsid                  ,숫자_ID              ,Sys_TownPos_id_t             ,0 , Sys_TownPos_id_t , uint16 , u16)\
		FIELD(x                      ,x                  ,uint16                       ,1 , uint16 , uint16 , i16)\
		FIELD(y                      ,y                  ,uint16                       ,2 , uint16 , uint16 , i16)\
		FIELD(town_map_type          ,타운맵파일명             ,tname32_t                    ,3 , tcstr , tcstr , t32)\
		FIELD(object_id              ,오브젝트 ID            ,uint16                       ,4 , uint16 , uint16 , i16)\

	#endif // for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_TownPos가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_TownPos_InheritedTable
	#define for_each_nEXCEL_Sys_TownPos_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_TownPos_InheritedTable


	// ------------------------------------------------------------
	// Sys_TownPos가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_TownPos가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum Evillage_Condition // 설명없음
	{
		eBEGIN_Evillage_Condition = 0,
		/* 보통 상태 */
		eEVC_Normal = 1, // 일반
		/* 점령중인 상태 */
		eEVC_OCCUPY = 2, // 점령중
		/* 장기비적속유저 */
		eEVC_INACTIVE = 3, // 장기비접속
		/* 온라인 유저 */
		eEVC_ONLINE = 4, // 온라인
		/* 오프라인 유저 */
		eEVC_OFFLINE = 5, // 오프라인
		eEND_Evillage_Condition
	}; // Evillage_Condition 





struct jEXCEL_LIB_API Sys_Castle /* 설명없음 */
{
	uint16 m_csid; // 숫자_ID min_max(,)
		typedef uint16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_csid; }
	void SetPrimaryKey(primary_key_t id) { m_csid = id; }
	/*  월드랑 연동 */
	tname32_t m_name; // 이름_ID min_max(,)
	tname32_t m_name_kor; // 성_이름 min_max(,)
	/*  제너럴 sid 입력 */
	Sys_Hero_id_t m_default_gsid; // 기본_태수 min_max(,)
	/*  bin/server/xml/NpcCastle.xml */
	tname32_t m_force_gen_name; // 부대생성규칙이름 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Castle
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Castle_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  5 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Castle
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Castle();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Castle

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Castle_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Castle)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Castle
enum { eSTRUCT_SIZE_Sys_Castle = sizeof(Sys_Castle) };


struct CSV_Sys_Castle : public nMech::nUtil::jCSV_File<Sys_Castle>
{
	virtual ~CSV_Sys_Castle(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Castle>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Castle g_Sys_Castle;

struct jEXCEL_LIB_API Sys_CastlePos /* 설명없음 */
{
	Sys_Castle_id_t m_cpsid; // 성 sid min_max(,)
		typedef Sys_Castle_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_cpsid; }
	void SetPrimaryKey(primary_key_t id) { m_cpsid = id; }
	uint16 m_x; // x min_max(,)
	uint16 m_y; // y min_max(,)
	/*  성지역의 마을 배치정보파일 */
	tname32_t m_castle_map; // castle_map파일 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_CastlePos
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  4 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_CastlePos
		jEXCEL_TABLE_COMMON_CODE_H_Sys_CastlePos();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_CastlePos

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_CastlePos_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_CastlePos)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_CastlePos
enum { eSTRUCT_SIZE_Sys_CastlePos = sizeof(Sys_CastlePos) };


struct CSV_Sys_CastlePos : public nMech::nUtil::jCSV_File<Sys_CastlePos>
{
	virtual ~CSV_Sys_CastlePos(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_CastlePos>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_CastlePos g_Sys_CastlePos;

struct jEXCEL_LIB_API Sys_TownPos /* 설명없음 */
{
	Sys_TownPos_id_t m_tpsid; // 숫자_ID min_max(,)
		typedef Sys_TownPos_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_tpsid; }
	void SetPrimaryKey(primary_key_t id) { m_tpsid = id; }
	uint16 m_x; // x min_max(,)
	uint16 m_y; // y min_max(,)
	/*  건물슬롯배치정보가 포함된 타운맵파일명 */
	tname32_t m_town_map_type; // 타운맵파일명 min_max(,)
	/*  오브젝트 정보 */
	uint16 m_object_id; // 오브젝트 ID min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_TownPos
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  5 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_TownPos
		jEXCEL_TABLE_COMMON_CODE_H_Sys_TownPos();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_TownPos

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_TownPos_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_TownPos)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_TownPos
enum { eSTRUCT_SIZE_Sys_TownPos = sizeof(Sys_TownPos) };


struct CSV_Sys_TownPos : public nMech::nUtil::jCSV_File<Sys_TownPos>
{
	virtual ~CSV_Sys_TownPos(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_TownPos>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_TownPos g_Sys_TownPos;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_castle_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_Evillage_Condition[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nEXCEL_excel_castle_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_castle_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_castle_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_castle_
