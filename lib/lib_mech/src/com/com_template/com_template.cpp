// com_template.cpp : DLL ���� ���α׷��� ���� ������ �Լ��� �����մϴ�.
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
