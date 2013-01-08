/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_client_locale_Eng_
#define __namespace_nEXCEL___filename_excel_baseball_table_client_locale_Eng_

#include "table_const_excel_baseball_table_client_locale_Eng.h"
// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_client_locale_Eng_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Dialog_Usa,대화용 스트링테이블,nMech,nEXCEL)\
	STRUCT(Sys_String_Usa,스트링테이블,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Dialog_Usa 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD(FIELD)\
		FIELD(index                  ,index              ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(npc                    ,npc                ,ENpcString                   ,1 , ENpcString , ENpcString , e)\
		FIELD(image_type             ,npc그림종류            ,aname32_t                    ,2 , acstr , acstr , a32)\
		FIELD(situation              ,상황                 ,ENpcSituationString          ,3 , ENpcSituationString , ENpcSituationString , e)\
		FIELD(text                   ,text               ,aname1024_t                  ,4 , acstr , acstr , a1024)\

	#endif // for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Dialog_Usa가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Dialog_Usa_InheritedTable
	#define for_each_nEXCEL_Sys_Dialog_Usa_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Dialog_Usa_InheritedTable


	// ------------------------------------------------------------
	// Sys_Dialog_Usa가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Dialog_Usa가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_String_Usa 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD(FIELD)\
		FIELD(index                  ,index              ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(category               ,category           ,ECategoryString              ,1 , ECategoryString , ECategoryString , e)\
		FIELD(name                   ,name               ,aname32_t                    ,2 , acstr , acstr , a32)\
		FIELD(text1                  ,text1              ,aname1024_t                  ,3 , acstr , acstr , a1024)\
		FIELD(text2                  ,text2              ,aname1024_t                  ,4 , acstr , acstr , a1024)\
		FIELD(text3                  ,text3              ,aname1024_t                  ,5 , acstr , acstr , a1024)\

	#endif // for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_String_Usa가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_String_Usa_InheritedTable
	#define for_each_nEXCEL_Sys_String_Usa_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_String_Usa_InheritedTable


	// ------------------------------------------------------------
	// Sys_String_Usa가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_String_Usa가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{



struct jEXCEL_LIB_API Sys_Dialog_Usa /* 대화용 스트링테이블 */
{
	/*  영문닉네임 , 각종테이블에서 사용 */
	int16 m_index; // index min_max(,)
		typedef int16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_index; }
	void SetPrimaryKey(primary_key_t id) { m_index = id; }
	/*  말하는 npc종류 */
	ENpcString m_npc; // npc min_max(,ENpcString)
	aname32_t m_image_type; // npc그림종류 min_max(,)
	/*  대화 상황 종류 */
	ENpcSituationString m_situation; // 상황 min_max(,ENpcSituationString)
	/*  출력되는 영문 대화 */
	aname1024_t m_text; // text min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Dialog_Usa
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  5 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Dialog_Usa
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Dialog_Usa();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Dialog_Usa

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Dialog_Usa_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Dialog_Usa)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Dialog_Usa
enum { eSTRUCT_SIZE_Sys_Dialog_Usa = sizeof(Sys_Dialog_Usa) };


struct CSV_Sys_Dialog_Usa : public nMech::nUtil::jCSV_File<Sys_Dialog_Usa>
{
	virtual ~CSV_Sys_Dialog_Usa(){}
	jLIST_TYPEDEF_vector_typedef(Sys_Dialog_Usa*,vector_situation);
	jLIST_TYPEDEF_map(ENpcSituationString, vector_situation_t, m_INDEX_situation);
	void init_INDEX_situation()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_Dialog_Usa* p = at(i);
			m_INDEX_situation[p->Get_situation()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Dialog_Usa>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_situation();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Dialog_Usa g_Sys_Dialog_Usa;

struct jEXCEL_LIB_API Sys_String_Usa /* 스트링테이블 */
{
	/*  영문닉네임 , 각종테이블에서 사용 */
	int16 m_index; // index min_max(,)
		typedef int16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_index; }
	void SetPrimaryKey(primary_key_t id) { m_index = id; }
	ECategoryString m_category; // category min_max(,ECategoryString)
	/*  영문닉네임 , 각종테이블에서 사용 */
	aname32_t m_name; // name min_max(,)
	/*  출력되는 영문명 */
	aname1024_t m_text1; // text1 min_max(,)
	/*  출력되는 영문명의 설명 a */
	aname1024_t m_text2; // text2 min_max(,)
	/*  출력되는 영문명의 설명 b */
	aname1024_t m_text3; // text3 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_String_Usa
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  6 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_String_Usa
		jEXCEL_TABLE_COMMON_CODE_H_Sys_String_Usa();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_String_Usa

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_String_Usa_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_String_Usa)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_String_Usa
enum { eSTRUCT_SIZE_Sys_String_Usa = sizeof(Sys_String_Usa) };


struct CSV_Sys_String_Usa : public nMech::nUtil::jCSV_File<Sys_String_Usa>
{
	virtual ~CSV_Sys_String_Usa(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_String_Usa>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_String_Usa g_Sys_String_Usa;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_baseball_table_client_locale_Eng_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_baseball_table_client_locale_Eng_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_baseball_table_client_locale_Eng_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_baseball_table_client_locale_Eng_
