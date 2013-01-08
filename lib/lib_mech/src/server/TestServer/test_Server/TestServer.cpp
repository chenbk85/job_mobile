// TestServer.cpp : DLL ���� ���α׷��� ���� ������ �Լ��� �����մϴ�.
//

#include "stdafx.h"
#include "TestServer.h"




Aq_NetDLL* g_pjConsoleDLL=0;
extern "C"
{
	__declspec(dllexport) void* jCreateInterface(jIE* pE)
	{
		init_common_AQ();
		//jCSV_Manager::Get()->Load_CSV();
		
//		_wsetlocale(LC_ALL, L"korean");
// 		wchar_t *as = L"�ѱ��Դϴ�.";
// 		wprintf_s(L"HanGle = %s\n\n\n\n", as);
// 		jLOG_T("�ѱ�");

		if(g_pjConsoleDLL)return g_pjConsoleDLL;
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
	//���⿡ �ڵ带 �߰��Ͻÿ�

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
