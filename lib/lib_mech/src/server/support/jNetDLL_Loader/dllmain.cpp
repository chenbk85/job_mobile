// dllmain.cpp : DLL 응용 프로그램의 진입점을 정의합니다.
#include "stdafx.h"

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "common/jCommon.h"
#include "common/jInit.h"
#include "interface/jIConsoleDLL.h"
#include "header/jDllLoader.h"
#include "interface/jIConsoleCmd.h"
#include "Interface/jIReportEvent.h"
using namespace nMech;


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
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

nMech::jDllLoader_Mech * g_pDllLoader=0;
nCONSOLE::jIConsoleDLL *g_pjIConsoleDLL_net=0;
bool console_parsor(tcstr sz)
{
	return g_pjIConsoleDLL_net->ParseCmd(sz);
}

extern "C"
{
	WINDOWS_DLL_TAG void* jCreateInterface(
		tcstr logFilePath // 로그파일 패스
		,tcstr dllName // 로딩할 net dll
		,tcstr netConfigXml // netDLL 용 config xml
		,tcstr netConfigXmlNode // config xml에서의 노드
		,acstr szGetUserInterface // dllName안에 정의된 유저객체를 가져오는 함수 포인터.
		,bool isService
		)
	{
		if(isService)
		{
			jIVar* pv_LOG_TO_FILE= jCV(jILog,LOG_TO_FILE,true,0,"Log(), LogPlus() -> print only file ");
			jIVar* pv_ERROR_CHECK_TYPE = jCV(jILog,ERROR_CHECK_TYPE,_T("NULL"), 0, "error action : NULL, EXIT, MSGBOX, MAIL ");
			pv_ERROR_CHECK_TYPE->Set_cstr(jS(NULL));
			pv_LOG_TO_FILE->Set_bool(true); // 파일로만 로깅. 	
		}

		if(logFilePath)
			GetjILog()->SetFileName(logFilePath);
		jMech_Init(true);

		nLOG::jIReportEvent* pjIRE =0;
		if(isService)
		{
#ifdef DEF_WINDOWS
			pjIRE = jCREATE_INTERFACE(nMech::nLOG::jIReportEvent);
			if(pjIRE)
			{
				pjIRE->Init(g_ExeEnv.m_szAppNic, netConfigXmlNode, 1);
				GetjILog()->SetReportEvent(0, pjIRE);
			}
#endif
		}

		nFileSystem::jFolder dir;
		dir.Goto(g_ExeEnv.m_szModuleDir);

		g_pDllLoader = new jDllLoader_Mech(dllName);
		g_pjIConsoleDLL_net = (nCONSOLE::jIConsoleDLL*)g_pDllLoader->jCreateInterface(0);
		nCONSOLE::Get_jIConsoleCmd()->Regist_ConsoleParser(dllName, console_parsor);
		g_pjIConsoleDLL_net->Start(netConfigXml, netConfigXmlNode);
		if(pjIRE)pjIRE->Write(nLOG::eEL_AUDIT_SUCCESS, 1, _T("Start : %s , %s") , netConfigXml, netConfigXmlNode);
		if(szGetUserInterface)
		{
			typedef void* NetClient_Interface_t();
			NetClient_Interface_t* v = (NetClient_Interface_t*)g_pDllLoader->GetFunc(szGetUserInterface /*"Get_NetClient_Interface"*/);
			return v;
		}
		return 0;
	}

	WINDOWS_DLL_TAG void jDeleteInterface()
	{
		if(g_pjIConsoleDLL_net) 
			g_pjIConsoleDLL_net->End();

		delete g_pDllLoader;
		jMech_Close();

	}

}
