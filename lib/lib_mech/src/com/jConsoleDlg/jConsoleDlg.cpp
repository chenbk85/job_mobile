// jConsoleDlg.cpp : DLL ���� ���α׷��� ���� ������ �Լ��� �����մϴ�.
//

#include "stdafx.h"
#include "jConsoleDlg.h"



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

