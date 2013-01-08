/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_test2_
#define __namespace_nEXCEL___filename_excel_test2_

#include "table_const_excel_test2.h"
// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_test2_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_T_Test4,테스트용4,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_T_Test4 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD(FIELD)\
		FIELD(maxbuild2              ,333최대 생성수          ,int16                        ,1 , int16 , int16 , i16)\
		FIELD(sys_test3_ref          ,자신테이블참조            ,Sys_T_Test4_ptr              , 2 ,Sys_T_Test4_ptr , Sys_T_Test4_ptr , ptr)\
		FIELD(sys_test2_arrary       ,자신테이블참조배열          ,Sys_T_Test2_ptr_vec          , 3 ,Sys_T_Test2_ptr_vec_ref , Sys_T_Test2_ptr_vec_ref , ptr_vec)\
		FIELD(enum_val               ,enum_val           ,EBuildTypeTest               ,4 , EBuildTypeTest , EBuildTypeTest , e)\
		FIELD(populationreturn4      ,populationreturn4  ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(test4                  ,test4              ,EBuildTypeTest               ,6 , EBuildTypeTest , EBuildTypeTest , e)\
		FIELD(getgold4               ,getgold4           ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(test3_array_id         ,자신테이블참조고정배열3       ,Sys_T_Test2_ptr_vec          , 8 ,Sys_T_Test2_ptr_vec_ref , Sys_T_Test2_ptr_vec_ref , ptr_vec)\
		FIELD(field_array            ,int어레이3            ,int32_vec                    , 9 ,int32_vec_ref , int32_vec_ref , vec)\
		FIELD(field_vector           ,int어레이             ,int32_vec                    , 10 ,int32_vec_ref , int32_vec_ref , vec)\
		FIELD(itemObj1               ,사용자자료형             ,jItemObj1                    ,11 , jItemObj1_ref , jItemObj1_ref , o)\
		FIELD(val_int                ,int변수              ,int32                        ,12 , int32 , int32 , i32)\

	#endif // for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Test4가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Test4_InheritedTable
	#define for_each_nEXCEL_Sys_T_Test4_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys__T_Base_InheritedTable(FUNC)\
		FUNC(Sys__T_Base)\

	#endif // for_each_nEXCEL_Sys_T_Test4_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Test4가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Test4가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	struct Sys_T_Test4;
	typedef Sys_T_Test4* Sys_T_Test4_ptr;
	typedef std::vector<Sys_T_Test4_ptr> Sys_T_Test4_ptr_vec;
	typedef Sys_T_Test4_ptr_vec& Sys_T_Test4_ptr_vec_ref;

	struct Sys_T_Test2;
	typedef Sys_T_Test2* Sys_T_Test2_ptr;
	typedef std::vector<Sys_T_Test2_ptr> Sys_T_Test2_ptr_vec;
	typedef Sys_T_Test2_ptr_vec& Sys_T_Test2_ptr_vec_ref;

	typedef std::vector<int32> int32_vec;
	typedef int32_vec& int32_vec_ref;



struct jEXCEL_LIB_API Sys_T_Test4 /* 테스트용4 */
	:Sys__T_Base
{
	Sys__T_Base* GetBase_Sys__T_Base(){ return static_cast<Sys__T_Base*>(this);}
	/*  한 마을에 최대 생성 가능한 건물 수 */
	int16 m_maxbuild2; // 333최대 생성수 min_max(,)
	/*  다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 */
	Sys_T_Test4_ptr m_sys_test3_ref_ptr; // 자신테이블참조 min_max(,Sys_T_Test4)
	/*  건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) */
	Sys_T_Test2_ptr_vec m_sys_test2_arrary_ptr_vec; // 자신테이블참조배열 min_max(,Sys_T_Test2)
	EBuildTypeTest m_enum_val; // enum_val min_max(,EBuildTypeTest)
	/*  건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. */
	int16 m_populationreturn4; // populationreturn4 min_max(,)
	EBuildTypeTest m_test4; // test4 min_max(,EBuildTypeTest)
	/*  징수 명령 */
	int16 m_getgold4; // getgold4 min_max(,)
	Sys_T_Test2_ptr_vec m_test3_array_id_ptr_vec; // 자신테이블참조고정배열3 min_max(,Sys_T_Test2)
	int32_vec m_field_array_vec; // int어레이3 min_max(,)
	int32_vec m_field_vector_vec; // int어레이 min_max(,)
	jItemObj1 m_itemObj1; // 사용자자료형 min_max(,)
	int32 m_val_int; // int변수 min_max(0,60000)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_T_Test4
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  12 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT
		 + Sys__T_Base::Get_STRUCT_COUNT()
	; };


	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test4
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test4();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Test4

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Test4)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Test4
enum { eSTRUCT_SIZE_Sys_T_Test4 = sizeof(Sys_T_Test4) };


struct CSV_Sys_T_Test4 : public nMech::nUtil::jCSV_File<Sys_T_Test4>
{
	virtual ~CSV_Sys_T_Test4(){}
	jLIST_TYPEDEF_vector_typedef(Sys_T_Test4*,vector_base_type);
	jLIST_TYPEDEF_map(EBuildType_test, vector_base_type_t, m_INDEX_base_type);
	void init_INDEX_base_type()
	{
		for(size_t i=0; i<size() ; ++i)
		{
			Sys_T_Test4* p = at(i);
			m_INDEX_base_type[p->Get_base_type()].push_back(p);
		}
	}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Test4>::Load(_szFile);
		if(!isOk) return false;
		init_INDEX_base_type();
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Test4 g_Sys_T_Test4;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_test2_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_test2_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_test2_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_test2_
