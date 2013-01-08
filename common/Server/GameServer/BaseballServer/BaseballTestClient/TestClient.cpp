// TestClient.cpp : DLL ���� ���α׷��� ���� ������ �Լ��� �����մϴ�.
//

#include "stdafx.h"
#include "TestClient.h"

Aq_NetDLL* g_pjConsoleDLL=0;


jIPlugIn_Connection* g_pCurrPlugInBE=0;

void Load_Common_CSV();

extern "C"
{
	__declspec(dllexport) void* jCreateInterface(jIE* pE)
	{
		//init_common_AQ();
		nFileSystem::jFolder dir;
// 		pv_CSV_PATH->Set_cstr(_T("server_data\\csv\\"));
// 		tfname_t szDir;
 		Load_Common_CSV();


		if(g_pjConsoleDLL)return g_pjConsoleDLL;
		if(!pE)	nInterface::g_pjINet_OGS->RunMessageThread();
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

	if(g_pPlugIn)
		return g_pPlugIn->ParseCmd(szCommand);
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
	g_pPlugIn->m_pCSM->ReleaseAll();
	parent_t::End();
}
