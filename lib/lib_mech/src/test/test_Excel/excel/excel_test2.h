/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_test2_
#define __namespace_nEXCEL___filename_excel_test2_

#include "table_const_excel_test2.h"
// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nEXCEL_excel_test2_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_T_Test4,�׽�Ʈ��4,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_T_Test4 �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD(FIELD)\
		FIELD(maxbuild2              ,333�ִ� ������          ,int16                        ,1 , int16 , int16 , i16)\
		FIELD(sys_test3_ref          ,�ڽ����̺�����            ,Sys_T_Test4_ptr              , 2 ,Sys_T_Test4_ptr , Sys_T_Test4_ptr , ptr)\
		FIELD(sys_test2_arrary       ,�ڽ����̺������迭          ,Sys_T_Test2_ptr_vec          , 3 ,Sys_T_Test2_ptr_vec_ref , Sys_T_Test2_ptr_vec_ref , ptr_vec)\
		FIELD(enum_val               ,enum_val           ,EBuildTypeTest               ,4 , EBuildTypeTest , EBuildTypeTest , e)\
		FIELD(populationreturn4      ,populationreturn4  ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(test4                  ,test4              ,EBuildTypeTest               ,6 , EBuildTypeTest , EBuildTypeTest , e)\
		FIELD(getgold4               ,getgold4           ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(test3_array_id         ,�ڽ����̺����������迭3       ,Sys_T_Test2_ptr_vec          , 8 ,Sys_T_Test2_ptr_vec_ref , Sys_T_Test2_ptr_vec_ref , ptr_vec)\
		FIELD(field_array            ,int���3            ,int32_vec                    , 9 ,int32_vec_ref , int32_vec_ref , vec)\
		FIELD(field_vector           ,int���             ,int32_vec                    , 10 ,int32_vec_ref , int32_vec_ref , vec)\
		FIELD(itemObj1               ,������ڷ���             ,jItemObj1                    ,11 , jItemObj1_ref , jItemObj1_ref , o)\
		FIELD(val_int                ,int����              ,int32                        ,12 , int32 , int32 , i32)\

	#endif // for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Test4�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Test4_InheritedTable
	#define for_each_nEXCEL_Sys_T_Test4_InheritedTable(FUNC)\
		for_each_nEXCEL_Sys__T_Base_InheritedTable(FUNC)\
		FUNC(Sys__T_Base)\

	#endif // for_each_nEXCEL_Sys_T_Test4_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Test4�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__T_Base_STRUCT_FIELD_all_member(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Test4�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
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



struct jEXCEL_LIB_API Sys_T_Test4 /* �׽�Ʈ��4 */
	:Sys__T_Base
{
	Sys__T_Base* GetBase_Sys__T_Base(){ return static_cast<Sys__T_Base*>(this);}
	/*  �� ������ �ִ� ���� ������ �ǹ� �� */
	int16 m_maxbuild2; // 333�ִ� ������ min_max(,)
	/*  �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ */
	Sys_T_Test4_ptr m_sys_test3_ref_ptr; // �ڽ����̺����� min_max(,Sys_T_Test4)
	/*  �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) */
	Sys_T_Test2_ptr_vec m_sys_test2_arrary_ptr_vec; // �ڽ����̺������迭 min_max(,Sys_T_Test2)
	EBuildTypeTest m_enum_val; // enum_val min_max(,EBuildTypeTest)
	/*  �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. */
	int16 m_populationreturn4; // populationreturn4 min_max(,)
	EBuildTypeTest m_test4; // test4 min_max(,EBuildTypeTest)
	/*  ¡�� ��� */
	int16 m_getgold4; // getgold4 min_max(,)
	Sys_T_Test2_ptr_vec m_test3_array_id_ptr_vec; // �ڽ����̺����������迭3 min_max(,Sys_T_Test2)
	int32_vec m_field_array_vec; // int���3 min_max(,)
	int32_vec m_field_vector_vec; // int��� min_max(,)
	jItemObj1 m_itemObj1; // ������ڷ��� min_max(,)
	int32 m_val_int; // int���� min_max(0,60000)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
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
