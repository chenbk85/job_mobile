/* file : excel_custom_code.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-03-23 17:25:17
comp.: rocworks.co.kr
title : 
desc : 

이 모듈은 excel csv코드에서 자동으로 나온 코드 복사하여 선별해서 정의한 코드이다.


*/

#include "stdafx.h"
#include "excel_all.h"
#include "excel_custom_code.h"

//z:\src\base\Interface\net\excel_code_util.h에서 struct Excel_PostLoader의 구현부
namespace nMech{namespace nEXCEL{Excel_PostLoader g_Excel_PostLoader;}}


#ifndef jNOT_USE_SQ_BIND_CODE
DECLARE_INSTANCE_TYPE_COMPLAX_csv(vector<int32>);
#endif //jNOT_USE_SQ_BIND_CODE


namespace nMech
{
	namespace nEXCEL
	{
	}//namespace nEXCEL
}//namespace nMech