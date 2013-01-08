// TDBCache.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "TDBCache.h"

_xmlid_LIST(jxDEFINE);

var_enum_ServerCommon(jCV_DEFINE);
var_enum(jCV_DEFINE);

namespace nMech
{
	StringID g_Current_LogLevel_jStringID = jx(TDBCache);
}

#include "../TCommonServer/recv_Common.h"


T_NetDLL* g_pjConsoleDLL=0;

extern "C"
{
	__declspec(dllexport) void* jCreateInterface(jIE* pE)
	{
		Init_T_SERVER_LIB_API();
		g_DQ.Begin();

		if(g_pjConsoleDLL)return g_pjConsoleDLL;
		nInterface::g_pjINet_OGS->RunMessageThread();
		nInterface::g_pjINet_OGS->SetCallback_PacketSize_UsageInfo(_OnPacketSize_UsageInfo);

		g_pjConsoleDLL = new T_NetDLL();

#ifdef TSERVER_PREPARE
		#define for_each_struct_size(X)\
		X(jPlayerDBSM)\
		X(nAQ::Use_Channel)\
		X(jHeroItem)\
		X(jHeroSkill)\

		#define print_size43289(X) jLOG1(jS(X) _T(" size=%d") , sizeof(X));
		for_each_struct_size(print_size43289);
#endif//TSERVER_PREPARE

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


bool T_NetDLL::ParseCmd(tcstr szCommand) 
{
	if( parent_t::ParseCmd(szCommand) ) return true;
	//여기에 코드를 추가하시오

	if(g_pCurrPlugIn_CmdParser)
		return g_pCurrPlugIn_CmdParser->ParseCmd(szCommand);
	return false;
}
bool T_NetDLL::Start(tcstr szNetConfigFile,tcstr szNetConfig_Name) 
{
	if(!parent_t::Start(szNetConfigFile,szNetConfig_Name)) return false;
	return true;

}

void T_NetDLL::End() 
{
	g_jXmlSaveManager.Destory();

	parent_t::End();
}
