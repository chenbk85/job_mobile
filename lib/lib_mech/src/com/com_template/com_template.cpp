// com_template.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "com_template.h"



namespace nMech
{
	namespace nUtil
	{

		extern "C"
		{
			__declspec(dllexport) void* jCreateInterface(jIE* pE)
			{

				return 0;
			}
			__declspec(dllexport) void jDeleteInterface()
			{
			}
			__declspec(dllexport) acstr jGetModuleOwnerName()
			{
				return "icandoit";
			}

		}
	}
}
