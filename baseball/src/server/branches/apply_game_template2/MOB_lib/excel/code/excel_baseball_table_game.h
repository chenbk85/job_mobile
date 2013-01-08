/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_game_
#define __namespace_nEXCEL___filename_excel_baseball_table_game_

#include "table_const_excel_baseball_table_game.h"
// -------------------------------------------------
// enum�� �ڵ� ���ø� ����
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nEXCEL_excel_baseball_table_game_ENUM(ENUM_TABLE)\
	ENUM_TABLE(ERunnerStateRound,�������,nMech,nEXCEL)\
	ENUM_TABLE(ERunnerStateType,�������,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// ���� enum������ �տ� e�� �ڵ����� �پ ����� 
	// -------------------------------------------------

	/* ������� */
	#define for_each_nEXCEL_ERunnerStateRound_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ERSR_0			,0,���� ����,nMech,nEXCEL,ERunnerStateRound)\
		ENUM_FIELD(ERSR_1			,1,���� 1��,nMech,nEXCEL,ERunnerStateRound)\
		ENUM_FIELD(ERSR_2			,2,���� 2��,nMech,nEXCEL,ERunnerStateRound)\
		ENUM_FIELD(ERSR_12			,3,���� 1�� 2��,nMech,nEXCEL,ERunnerStateRound)\
		ENUM_FIELD(ERSR_3			,4,���� 3��,nMech,nEXCEL,ERunnerStateRound)\
		ENUM_FIELD(ERSR_13			,5,���� 1�� 3��,nMech,nEXCEL,ERunnerStateRound)\
		ENUM_FIELD(ERSR_23			,6,���� 2�� 3��,nMech,nEXCEL,ERunnerStateRound)\
		ENUM_FIELD(ERSR_123			,7,���� 1�� 2�� 3��,nMech,nEXCEL,ERunnerStateRound)\

	/* ������� */
	#define for_each_nEXCEL_ERunnerStateType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ERST_A			,1,A��,nMech,nEXCEL,ERunnerStateType)\
		ENUM_FIELD(ERST_B			,2,B��,nMech,nEXCEL,ERunnerStateType)\
		ENUM_FIELD(ERST_C			,3,C��,nMech,nEXCEL,ERunnerStateType)\


// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_game_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Runner_State,�������,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Runner_State �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD(FIELD)\
		FIELD(index                  ,index              ,Sys_Runner_State_id_t        ,0 , Sys_Runner_State_id_t , uint16 , u16)\
		FIELD(category               ,���ڹ�ġ Ÿ��            ,ERunnerStateType             ,1 , ERunnerStateType , ERunnerStateType , e)\
		FIELD(state_1r               ,1���� ���� ��Ȳ         ,ERunnerStateRound            ,2 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_2r               ,2���� ���� ��Ȳ         ,ERunnerStateRound            ,3 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_3r               ,3���� ���� ��Ȳ         ,ERunnerStateRound            ,4 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_4r               ,4���� ���� ��Ȳ         ,ERunnerStateRound            ,5 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_5r               ,5���� ���� ��Ȳ         ,ERunnerStateRound            ,6 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_6r               ,6���� ���� ��Ȳ         ,ERunnerStateRound            ,7 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_7r               ,7���� ���� ��Ȳ         ,ERunnerStateRound            ,8 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_8r               ,8���� ���� ��Ȳ         ,ERunnerStateRound            ,9 , ERunnerStateRound , ERunnerStateRound , e)\
		FIELD(state_9r               ,9���� ���� ��Ȳ         ,ERunnerStateRound            ,10 , ERunnerStateRound , ERunnerStateRound , e)\

	#endif // for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Runner_State�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Runner_State_InheritedTable
	#define for_each_nEXCEL_Sys_Runner_State_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Runner_State_InheritedTable


	// ------------------------------------------------------------
	// Sys_Runner_State�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Runner_State�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Runner_State_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum ERunnerStateRound // �������
	{
		eBEGIN_ERunnerStateRound = 0,
		/* ���� ���� */
		eERSR_0 = 0, // ���� ����
		/* ���� 1�� */
		eERSR_1 = 1, // ���� 1��
		/* ���� 2�� */
		eERSR_2 = 2, // ���� 2��
		/* ���� 1�� 2�� */
		eERSR_12 = 3, // ���� 1�� 2��
		/* ���� 3�� */
		eERSR_3 = 4, // ���� 3��
		/* ���� 1�� 3�� */
		eERSR_13 = 5, // ���� 1�� 3��
		/* ���� 2�� 3�� */
		eERSR_23 = 6, // ���� 2�� 3��
		/* ���� 1�� 2�� 3�� */
		eERSR_123 = 7, // ���� 1�� 2�� 3��
		eEND_ERunnerStateRound
	}; // ERunnerStateRound 



	enum ERunnerStateType // �������
	{
		eBEGIN_ERunnerStateType = 0,
		/* 5����� 9���� ���� ��Ȳ */
		eERST_A = 1, // A��
		/* 3����� 6���� 9���� ���� ��Ȳ */
		eERST_B = 2, // B��
		/* 4����� 7���� 9���� ���� ��Ȳ */
		eERST_C = 3, // C��
		eEND_ERunnerStateType
	}; // ERunnerStateType 





struct jEXCEL_LIB_API Sys_Runner_State /* ������� */
{
	/*  �����г��� , �������̺��� ��� */
	Sys_Runner_State_id_t m_index; // index min_max(,)
		typedef Sys_Runner_State_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_index; }
	void SetPrimaryKey(primary_key_t id) { m_index = id; }
	/*  ���ڹ�ġ Ÿ�� */
	ERunnerStateType m_category; // ���ڹ�ġ Ÿ�� min_max(,ERunnerStateType)
	/*  1���� ���� ��Ȳ */
	ERunnerStateRound m_state_1r; // 1���� ���� ��Ȳ min_max(,ERunnerStateRound)
	/*  2���� ���� ��Ȳ */
	ERunnerStateRound m_state_2r; // 2���� ���� ��Ȳ min_max(,ERunnerStateRound)
	/*  3���� ���� ��Ȳ */
	ERunnerStateRound m_state_3r; // 3���� ���� ��Ȳ min_max(,ERunnerStateRound)
	/*  4���� ���� ��Ȳ */
	ERunnerStateRound m_state_4r; // 4���� ���� ��Ȳ min_max(,ERunnerStateRound)
	/*  5���� ���� ��Ȳ */
	ERunnerStateRound m_state_5r; // 5���� ���� ��Ȳ min_max(,ERunnerStateRound)
	/*  6���� ���� ��Ȳ */
	ERunnerStateRound m_state_6r; // 6���� ���� ��Ȳ min_max(,ERunnerStateRound)
	/*  7���� ���� ��Ȳ */
	ERunnerStateRound m_state_7r; // 7���� ���� ��Ȳ min_max(,ERunnerStateRound)
	/*  8���� ���� ��Ȳ */
	ERunnerStateRound m_state_8r; // 8���� ���� ��Ȳ min_max(,ERunnerStateRound)
	/*  9���� ���� ��Ȳ */
	ERunnerStateRound m_state_9r; // 9���� ���� ��Ȳ min_max(,ERunnerStateRound)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
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
