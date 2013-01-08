// MonitorServer.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "net_monitor.h"




Aq_NetDLL* g_pjConsoleDLL=0;
extern "C"
{
	__declspec(dllexport) void* jCreateInterface(jIE* pE)
	{
		init_common_AQ();
		//jCSV_Manager::Get()->Load_CSV();

		if(g_pjConsoleDLL)return g_pjConsoleDLL;
		jRETURN_ret(0,nInterface::g_pjINet_OGS);
		nInterface::g_pjINet_OGS->RunMessageThread();
		//nInterface::g_pjINet_OGS->SetCallback_PacketSize_UsageInfo(_OnPacketSize_UsageInfo);

		g_pjConsoleDLL = new Aq_NetDLL();
		return g_pjConsoleDLL;

	}
	__declspec(dllexport) void jDeleteInterface()
	{
		SAFE_DELETE(g_pjConsoleDLL);
	}
	__declspec(dllexport) acstr jGetModuleOwnerName()
	{
		return "icandoit";
	}

	__declspec(dllexport) nLOG::jIReportEvent* jGetReportEvent()
	{
		if(nInterface::g_pjILog)
		{
			return g_pjILog->GetReportEvent(0);
		}
		return 0;
	}
	

}


bool Aq_NetDLL::ParseCmd(tcstr szCommand) 
{
	if( parent_t::ParseCmd(szCommand) ) return true;
	//여기에 코드를 추가하시오

	if(g_pCurrPlugIn)
		return g_pCurrPlugIn->ParseCmd(szCommand);
	return false;
}
bool Aq_NetDLL::Start(tcstr szNetConfigFile,tcstr szNetConfig_Name) 
{
	if(!parent_t::Start(szNetConfigFile,szNetConfig_Name)) return false;
	return true;

}

void Aq_NetDLL::End() 
{

	parent_t::End();
}
