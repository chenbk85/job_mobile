/* file : excel_custom_code.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-03-23 17:25:17
comp.: rocworks.co.kr
title : 
desc : 

�� ����� excel csv�ڵ忡�� �ڵ����� ���� �ڵ� �����Ͽ� �����ؼ� ������ �ڵ��̴�.


*/

#include "stdafx.h"
#include "excel_all.h"
#include "excel_custom_code.h"

//z:\src\base\Interface\net\excel_code_util.h���� struct Excel_PostLoader�� ������
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