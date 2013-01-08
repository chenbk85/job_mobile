/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_string_table_
#define __namespace_nEXCEL___filename_excel_baseball_string_table_

#include "table_const_excel_baseball_string_table.h"
// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_string_table_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Error,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Error 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Error_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Error_STRUCT_FIELD(FIELD)\
		FIELD(id                     ,id                 ,Sys_Error_id_t               ,0 , Sys_Error_id_t , uint16 , u16)\
		FIELD(name                   ,name               ,aname256_t                   ,1 , acstr , acstr , a256)\
		FIELD(help                   ,help               ,aname256_t                   ,2 , acstr , acstr , a256)\

	#endif // for_each_nEXCEL_Sys_Error_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Error가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Error_InheritedTable
	#define for_each_nEXCEL_Sys_Error_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Error_InheritedTable


	// ------------------------------------------------------------
	// Sys_Error가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Error_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Error_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Error_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Error가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Error_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Error_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Error_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Error_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Error_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{



struct jEXCEL_LIB_API Sys_Error /* 설명없음 */
{
	Sys_Error_id_t m_id; // id min_max(,)
		typedef Sys_Error_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_id; }
	void SetPrimaryKey(primary_key_t id) { m_id = id; }
	aname256_t m_name; // name min_max(,)
	aname256_t m_help; // help min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Error
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Error_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  3 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Error
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Error();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Error

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Error_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Error)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Error
enum { eSTRUCT_SIZE_Sys_Error = sizeof(Sys_Error) };


struct CSV_Sys_Error : public nMech::nUtil::jCSV_File<Sys_Error>
{
	virtual ~CSV_Sys_Error(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Error>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Error g_Sys_Error;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_baseball_string_table_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_baseball_string_table_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_baseball_string_table_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_baseball_string_table_
