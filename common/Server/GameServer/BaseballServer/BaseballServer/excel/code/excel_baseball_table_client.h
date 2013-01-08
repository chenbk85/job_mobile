/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_client_
#define __namespace_nEXCEL___filename_excel_baseball_table_client_

#include "table_const_excel_baseball_table_client.h"
// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_client_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Client_Graphic_File_Name,설명없음,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Client_Graphic_File_Name 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD(FIELD)\
		FIELD(sid                    ,고유번호               ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(equip_PlayerBodyType   ,아이템 착용 캐릭터 타입      ,EPlayerBodyType              ,1 , EPlayerBodyType , EPlayerBodyType , e)\
		FIELD(Sys_ItemEquip_Sid      ,장비아이템카테고리의 sid     ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(file_name_texture      ,텍스처 파일 이름          ,aname32_t                    ,3 , acstr , acstr , a32)\
		FIELD(file_name_object       ,오브젝트 파일 이름         ,aname32_t                    ,4 , acstr , acstr , a32)\
		FIELD(file_name_icon         ,아이콘 파일 이름          ,aname32_t                    ,5 , acstr , acstr , a32)\
		FIELD(equip_animation_item   ,애니메이션 아이템          ,aname32_t                    ,6 , acstr , acstr , a32)\

	#endif // for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Client_Graphic_File_Name가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Client_Graphic_File_Name_InheritedTable
	#define for_each_nEXCEL_Sys_Client_Graphic_File_Name_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Client_Graphic_File_Name_InheritedTable


	// ------------------------------------------------------------
	// Sys_Client_Graphic_File_Name가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Client_Graphic_File_Name가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{



struct jEXCEL_LIB_API Sys_Client_Graphic_File_Name /* 설명없음 */
{
	/*  고유번호 */
	int16 m_sid; // 고유번호 min_max(,)
	/*  아이템 착용 캐릭터 타입 */
	EPlayerBodyType m_equip_PlayerBodyType; // 아이템 착용 캐릭터 타입 min_max(,EPlayerBodyType)
	/*  Sys_ItemEquip의 sid */
	int16 m_Sys_ItemEquip_Sid; // 장비아이템카테고리의 sid min_max(,)
	/*  텍스처 파일 네임 */
	aname32_t m_file_name_texture; // 텍스처 파일 이름 min_max(,)
	/*  오브젝트 파일네임 */
	aname32_t m_file_name_object; // 오브젝트 파일 이름 min_max(,)
	/*  아이콘 파일 네임 */
	aname32_t m_file_name_icon; // 아이콘 파일 이름 min_max(,)
	/*  애니메이션 아이템 */
	aname32_t m_equip_animation_item; // 애니메이션 아이템 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Client_Graphic_File_Name
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  7 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Client_Graphic_File_Name
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Client_Graphic_File_Name();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Client_Graphic_File_Name

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Client_Graphic_File_Name_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Client_Graphic_File_Name)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Client_Graphic_File_Name
enum { eSTRUCT_SIZE_Sys_Client_Graphic_File_Name = sizeof(Sys_Client_Graphic_File_Name) };


struct CSV_Sys_Client_Graphic_File_Name : public nMech::nUtil::jCSV_File<Sys_Client_Graphic_File_Name>
{
	virtual ~CSV_Sys_Client_Graphic_File_Name(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Client_Graphic_File_Name>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Client_Graphic_File_Name g_Sys_Client_Graphic_File_Name;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_baseball_table_client_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_baseball_table_client_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_baseball_table_client_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_baseball_table_client_
