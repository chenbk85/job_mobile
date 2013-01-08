// Com_Util.cpp : DLL 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#ifdef _WIN32
#include <time.h>
#endif

#include "Com_Util.h"
#include "Interface/jIConsoleCmd.h"
using namespace nMech;
jxDEFINE(Com_Util);

namespace nMech
{
	StringID g_Current_LogLevel_jStringID = jx(Com_Util);

	namespace nUtil
	{

		volatile float __f__=10;
		jIE* g_peDLL;
		HMODULE gDLLHandle = NULL;

	}
}

using namespace nMech::nUtil;
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
)
{
	gDLLHandle = (HMODULE)hModule;

	__f__++;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

namespace nMech
{
	namespace nUtil
	{

		extern "C"
		{
			WINDOWS_DLL_TAG void* jCreateInterface(jIE* pE)
			{

				return 0;
			}
			WINDOWS_DLL_TAG void jDeleteInterface()
			{
			}
			WINDOWS_DLL_TAG acstr jGetModuleOwnerName()
			{
				return "icandoit";
			}

		}
	}
}
jCONSOLE_CMD_AUTO(con,cls,0,"clear console window","")
{
	system("cls");
	return true;
}

jCONSOLE_CMD_AUTO(con,open_log,0,"open log file","")
{
	nFileSystem::jFolder dir(true);
	afname_t szExeCmd;
	tcstr szFile=jS(NULL);
	if(nMech::nInterface::g_pjILog)
	{
		nMech::nInterface::g_pjILog->ProcessMessage(jS(flush_WriteCache),0);
		szFile = nMech::nInterface::g_pjILog->GetFileName();
	}
	ja_sprintf(szExeCmd, ("notepad %s"),jA(szFile));
	WinExec(szExeCmd,SW_SHOW);
	return true;
}

#define jSET_CON_FLAG(category,var,value)\
	jIVar* pv_##var= nCONSOLE::Get_jIConsoleVar()->GetVar(jS(category),jS(var));if(pv_##var) pv_##var->Set_bool(value);


jCONSOLE_CMD_AUTO(con,log_off,0,"On/off log excepted waring/error","<bool>")
{
	bool is = arg[0] == tstring(jS(true));

	jSET_CON_FLAG(exe,log_off,is);

	return true;
}

