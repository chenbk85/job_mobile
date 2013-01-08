/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_ClientResult_
#define __namespace_nEXCEL___filename_excel_ClientResult_

#include "table_const_excel_ClientResult.h"
// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_ClientResult_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_ClientResult,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_ClientResult 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ClientResult_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_ClientResult_STRUCT_FIELD(FIELD)\
		FIELD(id                     ,에러번호               ,uint16                       ,0 , uint16 , uint16 , i16)\
		FIELD(eng_name               ,에러이름               ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(description            ,에러내용               ,tstring                      ,2 , tcstr , tcstr , ts)\

	#endif // for_each_nEXCEL_Sys_ClientResult_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_ClientResult가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_ClientResult_InheritedTable
	#define for_each_nEXCEL_Sys_ClientResult_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_ClientResult_InheritedTable


	// ------------------------------------------------------------
	// Sys_ClientResult가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ClientResult_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_ClientResult_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_ClientResult_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_ClientResult가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_ClientResult_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_ClientResult_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_ClientResult_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_ClientResult_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_ClientResult_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{



struct jEXCEL_LIB_API Sys_ClientResult /* 설명없음 */
{
	uint16 m_id; // 에러번호 min_max(,)
		typedef uint16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_id; }
	void SetPrimaryKey(primary_key_t id) { m_id = id; }
	tname32_t m_eng_name; // 에러이름 min_max(,)
	tstring m_description; // 에러내용 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_ClientResult
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_ClientResult_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  3 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_ClientResult
		jEXCEL_TABLE_COMMON_CODE_H_Sys_ClientResult();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_ClientResult

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_ClientResult_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_ClientResult)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_ClientResult
enum { eSTRUCT_SIZE_Sys_ClientResult = sizeof(Sys_ClientResult) };


struct CSV_Sys_ClientResult : public nMech::nUtil::jCSV_File<Sys_ClientResult>
{
	virtual ~CSV_Sys_ClientResult(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_ClientResult>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_ClientResult g_Sys_ClientResult;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_ClientResult_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_ClientResult_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_ClientResult_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_ClientResult_
