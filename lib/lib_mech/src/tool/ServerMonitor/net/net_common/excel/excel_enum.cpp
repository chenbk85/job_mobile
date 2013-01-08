/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_enum.h"



//현제 모듈의 Sys테이블에 대해 배열형 필드를 사용할때는 아래 코드를 구현해야 한다.
#if 0

#ifndef jNOT_USE_SQ_BIND_CODE
#endif //jNOT_USE_SQ_BIND_CODE


namespace nMech
{
	namespace nTESTSERVER
	{
	}//namespace nTESTSERVER
}//namespace nMech
#endif //구현되어야 하는 코드 끝.

#ifndef jNOT_USE_SQ_BIND_CODE

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nTESTSERVER_excel_enum_Sys_STRUCT_LIST)
		for_each_nTESTSERVER_excel_enum_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nTESTSERVER_excel_enum_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE


for_each_nTESTSERVER_excel_enum_ENUM(jEXCEL_SQ_DECLARE_ENUM_TYPE);
namespace nMech {
	namespace nTESTSERVER {

jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EAvatarClass[] = 
{
	{ 4 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EAvatarClass_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBuildType_test[] = 
{
	{ 22 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EBuildType_test_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBuildTypeTest[] = 
{
	{ 22 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EBuildTypeTest_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EOutput_test[] = 
{
	{ 24 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EOutput_test_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};

} //namespace nTESTSERVER 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nTESTSERVER;

	namespace nMech { namespace nTESTSERVER
	{
		jSQ_REGIST_BIND(nMech_nTESTSERVER_excel_enum)
		{
			{
				SquirrelObject enumRoot= nSQ::jSQ_GetEnumTable();
				for_each_nTESTSERVER_excel_enum_ENUM(jEXCEL_SQ_bind_EnumField_BEGIN);
				for_each_nTESTSERVER_EAvatarClass_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_EBuildType_test_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_EBuildTypeTest_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_EOutput_test_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
			}
		}
	} /*namespace nTESTSERVER */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

