// MessageServer.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "MessageServer.h"



#ifdef _MANAGED
#pragma managed(push, off)
#endif

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

#ifdef _MANAGED
#pragma managed(pop)
#endif


MessageServer* g_pTrServerDLL=0;
jIPlugIn_Connection* g_pCurrPlugIn=0;
extern aname32_t g_service_ip;




extern "C"
{
	MESSAGESERVER_API void* jCreateInterface(jIE* pE)
	{
		init_common_TR();
		//TR_CSV_Manager::Get()->Load_CSV();
		if(g_pTrServerDLL)return g_pTrServerDLL;
		g_pTrServerDLL = new MessageServer();
		return g_pTrServerDLL;

	}
	MESSAGESERVER_API void jDeleteInterface()
	{
		SAFE_DELETE(g_pTrServerDLL);
	}
	MESSAGESERVER_API acstr jGetModuleOwnerName()
	{
		return "icandoit";
	}

}


bool MessageServer::ParseCmd(tcstr szCommand) 
{
	if( parent_t::ParseCmd(szCommand) ) return true;
	//여기에 코드를 추가하시오

	if(g_pCurrServerPlugIn)
		return g_pCurrServerPlugIn->ParseCmd(szCommand);
	if(g_pCurrPlugIn)
		return g_pCurrPlugIn->ParseCmd(szCommand);
	return false;
}
void MessageServer::Start(tcstr szNetConfigFile,tcstr szNetConfig_Name) 
{
	parent_t::Start(szNetConfigFile,szNetConfig_Name);
	// 여기에 코드를 추가하시오



}

void MessageServer::End() 
{
	//여기에 코드를 추가하시오

	parent_t::End();
}
