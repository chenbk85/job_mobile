// TPlayer.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "TPlayer.h"
//서버 dll에서만 사용.
//#include "../TCommonServer/recv_Common.h"


_xmlid_LIST(jxDEFINE);

var_enum_ServerCommon(jCV_DEFINE);
var_enum(jCV_DEFINE);


namespace nMech
{
	StringID g_Current_LogLevel_jStringID = jx(TPlayer);
}



T_NetDLL* g_pjConsoleDLL=0;

extern jNetClient g_jNetClient;

extern "C"
{
	__declspec(dllexport) void* jCreateInterface(jIE* pE)
	{
 		Init_T_SERVER_LIB_API();

		if(g_pjConsoleDLL)return g_pjConsoleDLL;
		if(!pE)	nInterface::g_pjINet_OGS->RunMessageThread();
		g_pjConsoleDLL = new T_NetDLL();
		g_pNetClient= new jNetClient;
		return g_pjConsoleDLL;

	}
	__declspec(dllexport) jINetClient* Get_NetClient_Interface()
	{
		g_pNetClient->m_isDummyMode=false;
		return (jINetClient*)g_pNetClient;
	}

	__declspec(dllexport) void jDeleteInterface()
	{
		SAFE_DELETE(g_pNetClient);
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
