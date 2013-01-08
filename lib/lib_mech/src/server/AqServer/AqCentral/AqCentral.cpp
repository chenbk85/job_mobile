// AqCentral.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "AqCentral.h"
#include <boost/bind.hpp>
#include "csv_loader.h"
#include "../AqCommon/jXmlSaveManager.h"


Aq_NetDLL* g_pjConsoleDLL=0;


void _OnPacketSize_UsageInfo(tcstr szPlugIn,uint64 packet_size,tname1024_t info)
{
	g_jAqCommon.OnPacketSize_UsageInfo(szPlugIn,packet_size);
}
extern "C"
{
	AQCENTRAL_API void* jCreateInterface(jIE* pE)
	{
		init_common_AQ();
		/*
		tfname_t szDir;
		Load_Common_CSV(szDir);


		//jFOR_EACH(pCM->m_Sys_LocalizingText.m_List , boost::bind(&Sys_LocalizingText::jDebugPrint,_1));
		Sys_LocalizingText* pN = jCSV(Sys_LocalizingText).find(jS(we_are_fiend));
		if(pN)
		{
			pN->jDebugPrint();
		}
		else
		{
			GetjILog()->Warning( _T("Sys_LocalizingText : we_are_fiend : not found") );
		}
*/
		if(g_pjConsoleDLL) return g_pjConsoleDLL;
		g_pjConsoleDLL = new Aq_NetDLL();
		nInterface::g_pjINet_OGS->RunMessageThread();
		nInterface::g_pjINet_OGS->SetCallback_PacketSize_UsageInfo(_OnPacketSize_UsageInfo);
		return g_pjConsoleDLL;

	}
	AQCENTRAL_API void jDeleteInterface()
	{
		SAFE_DELETE(g_pjConsoleDLL);
	}
	AQCENTRAL_API acstr jGetModuleOwnerName()
	{
		return "icandoit";
	}

}

bool Aq_NetDLL::ParseCmd(tcstr szCommand) 
{
	if( parent_t::ParseCmd(szCommand) ) return true;
	//여기에 코드를 추가하시오

	if(!g_pCurrPlugIn) return false;

	return g_pCurrPlugIn->ParseCmd(szCommand);
}

bool Aq_NetDLL::Start(tcstr szNetConfigFile,tcstr szNetConfig_Name) 
{	
	if(!parent_t::Start(szNetConfigFile,szNetConfig_Name)) return false;
	// 여기에 코드를 추가하시오
	return true;
}

void Aq_NetDLL::End() 
{
	//여기에 코드를 추가하시오
	g_jXmlSaveManager.Destory();

	parent_t::End();
}
