// AqTrade.cpp : DLL ���� ���α׷��� ���� ������ �Լ��� �����մϴ�.
//

#include "stdafx.h"
#include "AqTrade.h"



Aq_NetDLL* g_pjConsoleDLL=0;
inline bool Aq_NetDLL::IsCreateStartThread(){return false;}

jIPlugIn_Connection* g_pCurrPlugInBE=0;

extern "C"
{
	__declspec(dllexport) void* jCreateInterface(jIE* pE)
	{
		init_common_AQ();
		//jCSV_Manager::Get()->Load_CSV();

		if(g_pjConsoleDLL)return g_pjConsoleDLL;
		nInterface::g_pjINet_OGS->RunMessageThread();
		nInterface::g_pjINet_OGS->SetCallback_PacketSize_UsageInfo(_OnPacketSize_UsageInfo);

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

}


bool Aq_NetDLL::ParseCmd(tcstr szCommand) 
{
	if( parent_t::ParseCmd(szCommand) ) return true;
	//���⿡ �ڵ带 �߰��Ͻÿ�

	if(g_pCurrPlugIn)
		return g_pCurrPlugIn->ParseCmd(szCommand);
	if(g_pCurrPlugInBE)
		return g_pCurrPlugInBE->ParseCmd(szCommand);
	return false;
}
void Aq_NetDLL::Start(tcstr szNetConfigFile,tcstr szNetConfig_Name) 
{
	parent_t::Start(szNetConfigFile,szNetConfig_Name);

}

void Aq_NetDLL::End() 
{

	parent_t::End();
}
