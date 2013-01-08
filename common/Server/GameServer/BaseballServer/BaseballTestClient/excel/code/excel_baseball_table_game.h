/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_game_
#define __namespace_nEXCEL___filename_excel_baseball_table_game_

#include "table_const_excel_baseball_table_game.h"
// -------------------------------------------------
// enum형 코드 템플릿 정의
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nEXCEL_excel_baseball_table_game_ENUM(ENUM_TABLE)\
	ENUM_TABLE(ERunnerStateRound,설명없음,nMech,nEXCEL)\
	ENUM_TABLE(ERunnerStateType,설명없음,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// 주의 enum변수는 앞에 e가 자동으로 붙어서 선언됨 
	// -------------------------------------------------

	/* 설명없음 */
	#define for_each_nEXCEL_ERunnerStateRound_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ERSR_0			,0,주자 없음,nMech,nEXCEL,ERunnerStateRound)\
		ENUM_FIELD(ERSR_1			,1,주자 1루,nMech,nEXCEL,ERunnerStateRound)\
		ENUM_FIELD(ERSR_2			,2,주자 2루,nMech,nEXCEL,ERunnerStateRound)\
		ENUM_FIELD(ERSR_12			,3,주자 1루 2루,nMech,nEXCEL,ERunnerStateRound)\
		ENUM_FIELD(ERSR_3			,4,주자 3루,nMech,nEXCEL,ERunnerStateRound)\
		ENUM_FIELD(ERSR_13			,5,주자 1루 3루,nMech,nEXCEL,ERunnerStateRound)\
		ENUM_FIELD(ERSR_23			,6,주자 2루 3루,nMech,nEXCEL,ERunnerStateRound)\
		ENUM_FIELD(ERSR_123			,7,주자 1루 2루 3루,nMech,nEXCEL,ERunnerStateRound)\

	/* 설명없음 */
	#define for_each_nEXCEL_ERunnerStateType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ERST_A			,1,A형,nMech,nEXCEL,ERunnerStateType)\
		ENUM_FIELD(ERST_B			,2,B형,nMech,nEXCEL,ERunnerStateType)\
		ENUM_FIELD(ERST_C			,3,C형,nMech,nEXCEL,ERunnerStateType)\


// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_game_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Runner_State,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Runner_State 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD(FIELD)\
		FIELD(index                  ,index              ,Sys_Runner_State_id_t        ,0 , Sys_Runner_State_id_t , uint16 , u16)\
		FIELD(category               ,주자배치 타입            ,ERunnerStateType             ,1 , ERunnerStateType , ERunnerStateType , e)\
		FIELD(state_1r               ,1라운드 주자 상황         ,ERunnerStateRound            ,2 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_2r               ,2라운드 주자 상황         ,ERunnerStateRound            ,3 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_3r               ,3라운드 주자 상황         ,ERunnerStateRound            ,4 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_4r               ,4라운드 주자 상황         ,ERunnerStateRound            ,5 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_5r               ,5라운드 주자 상황         ,ERunnerStateRound            ,6 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_6r               ,6라운드 주자 상황         ,ERunnerStateRound            ,7 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_7r               ,7라운드 주자 상황         ,ERunnerStateRound            ,8 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_8r               ,8라운드 주자 상황         ,ERunnerStateRound            ,9 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_9r               ,9라운드 주자 상황         ,ERunnerStateRound            ,10 , ERunnerStateRound , ERunnerStateRound , e)\

	#endif // for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Runner_State가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Runner_State_InheritedTable
	#define for_each_nEXCEL_Sys_Runner_State_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Runner_State_InheritedTable


	// ------------------------------------------------------------
	// Sys_Runner_State가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Runner_State가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum ERunnerStateRound // 설명없음
	{
		eBEGIN_ERunnerStateRound = 0,
		/* 주자 없음 */
		eERSR_0 = 0, // 주자 없음
		/* 주자 1루 */
		eERSR_1 = 1, // 주자 1루
		/* 주자 2루 */
		eERSR_2 = 2, // 주자 2루
		/* 주자 1루 2루 */
		eERSR_12 = 3, // 주자 1루 2루
		/* 주자 3루 */
		eERSR_3 = 4, // 주자 3루
		/* 주자 1루 3루 */
		eERSR_13 = 5, // 주자 1루 3루
		/* 주자 2루 3루 */
		eERSR_23 = 6, // 주자 2루 3루
		/* 주자 1루 2루 3루 */
		eERSR_123 = 7, // 주자 1루 2루 3루
		eEND_ERunnerStateRound
	}; // ERunnerStateRound 



	enum ERunnerStateType // 설명없음
	{
		eBEGIN_ERunnerStateType = 0,
		/* 5라운드와 9라운드 만루 상황 */
		eERST_A = 1, // A형
		/* 3라운드와 6라운드 9라운드 만루 상황 */
		eERST_B = 2, // B형
		/* 4라운드와 7라운드 9라운드 만루 상황 */
		eERST_C = 3, // C형
		eEND_ERunnerStateType
	}; // ERunnerStateType 





struct jEXCEL_LIB_API Sys_Runner_State /* 설명없음 */
{
	/*  영문닉네임 , 각종테이블에서 사용 */
	Sys_Runner_State_id_t m_index; // index min_max(,)
		typedef Sys_Runner_State_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_index; }
	void SetPrimaryKey(primary_key_t id) { m_index = id; }
	/*  주자배치 타입 */
	ERunnerStateType m_category; // 주자배치 타입 min_max(,ERunnerStateType)
	/*  1라운드 주자 상황 */
	ERunnerStateRound m_state_1r; // 1라운드 주자 상황 min_max(,ERunnerStateRound)
	/*  2라운드 주자 상황 */
	ERunnerStateRound m_state_2r; // 2라운드 주자 상황 min_max(,ERunnerStateRound)
	/*  3라운드 주자 상황 */
	ERunnerStateRound m_state_3r; // 3라운드 주자 상황 min_max(,ERunnerStateRound)
	/*  4라운드 주자 상황 */
	ERunnerStateRound m_state_4r; // 4라운드 주자 상황 min_max(,ERunnerStateRound)
	/*  5라운드 주자 상황 */
	ERunnerStateRound m_state_5r; // 5라운드 주자 상황 min_max(,ERunnerStateRound)
	/*  6라운드 주자 상황 */
	ERunnerStateRound m_state_6r; // 6라운드 주자 상황 min_max(,ERunnerStateRound)
	/*  7라운드 주자 상황 */
	ERunnerStateRound m_state_7r; // 7라운드 주자 상황 min_max(,ERunnerStateRound)
	/*  8라운드 주자 상황 */
	ERunnerStateRound m_state_8r; // 8라운드 주자 상황 min_max(,ERunnerStateRound)
	/*  9라운드 주자 상황 */
	ERunnerStateRound m_state_9r; // 9라운드 주자 상황 min_max(,ERunnerStateRound)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Runner_State
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  11 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Runner_State
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Runner_State();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Runner_State

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Runner_State)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Runner_State
enum { eSTRUCT_SIZE_Sys_Runner_State = sizeof(Sys_Runner_State) };


struct CSV_Sys_Runner_State : public nMech::nUtil::jCSV_File<Sys_Runner_State>
{
	virtual ~CSV_Sys_Runner_State(){}
	jLIST_TYPEDEF_vector_typedef(Sys_Runner_State*,vector_category);
	jLIST_TYPEDEF_map(ERunnerStateType, vector_category_t, m_INDEX_category);
	void init_INDEX_category()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_Runner_State* p = at(i);
			m_INDEX_category[p->Get_category()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Runner_State>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_category();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Runner_State g_Sys_Runner_State;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_baseball_table_game_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ERunnerStateRound[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ERunnerStateType[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nEXCEL_excel_baseball_table_game_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_baseball_table_game_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_baseball_table_game_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_baseball_table_game_
