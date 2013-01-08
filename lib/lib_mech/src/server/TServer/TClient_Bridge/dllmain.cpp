// dllmain.cpp : DLL 응용 프로그램의 진입점을 정의합니다.
#include "stdafx.h"

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "common/jCommon.h"
#include "common/jInit.h"
#include "interface/jIConsoleDLL.h"
#include "header/jDllLoader.h"
#include "interface/jIConsoleCmd.h"
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
	__declspec(dllexport) void* jCreateInterface(tcstr logFilePath, tcstr dllName,tcstr netConfigXml,tcstr netConfigXmlNode)
	{
		GetjILog()->SetFileName(logFilePath);
		jMech_Init(true);
		jIVar* g_pvNetConfigNode	= jCV(exe,NetConfigNode,jS(TestClient),0,"node name of NetConfigXml: default=app_nic_name" );
		g_pvNetConfigNode->Set_cstr(netConfigXmlNode);

		g_pDllLoader = new jDllLoader_Mech(dllName);
		g_pjIConsoleDLL_net = (nCONSOLE::jIConsoleDLL*)g_pDllLoader->jCreateInterface(0);
		nCONSOLE::Get_jIConsoleCmd()->Regist_ConsoleParser(jS(client), console_parsor);
		g_pjIConsoleDLL_net->Start(netConfigXml, g_pvNetConfigNode->Get_cstr());

		typedef void* NetClient_Interface_t();
		NetClient_Interface_t* v = (NetClient_Interface_t*)g_pDllLoader->GetFunc("Get_NetClient_Interface");
		return v();
	}

	__declspec(dllexport) void jDeleteInterface()
	{
		if(g_pjIConsoleDLL_net) 
			g_pjIConsoleDLL_net->End();

		delete g_pDllLoader;
		jMech_Close();

	}

}
