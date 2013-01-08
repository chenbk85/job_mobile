// Aq_NetDLL.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "AqLogin.h"
#include "../AqCommon/recv_Common.h"
#include "../AqCommon/jXmlSaveManager.h"


Aq_NetDLL* g_pjConsoleDLL=0;


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
	//여기에 코드를 추가하시오

	if(g_pCurrPlugIn)
		return g_pCurrPlugIn->ParseCmd(szCommand);
	if(g_pCurrPlugInBE)
		return g_pCurrPlugInBE->ParseCmd(szCommand);
	return false;
}
bool Aq_NetDLL::Start(tcstr szNetConfigFile,tcstr szNetConfig_Name) 
{
	if(!parent_t::Start(szNetConfigFile,szNetConfig_Name)) return false;
	return true;

}

void Aq_NetDLL::End() 
{
	g_jXmlSaveManager.Destory();

	parent_t::End();
}
