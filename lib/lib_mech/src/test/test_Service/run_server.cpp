/* file : run_server.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-08-27 23:22:43
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "interface/jIConsoleDLL.h"
#include "header/jDllLoader.h"


void jLoadNetDll(tcstr szNetDLL , tcstr szNetXmlConfigFile,tcstr szNetXmlConfigNode,bool isCustom_NetMsgLoop=false)
{
	nMech::jDllLoader_Mech * g_pDllLoader=0;
	nCONSOLE::jIConsoleDLL *g_pjIConsoleDLL_net=0;
	jIVar* pv_Custom_MsgLoop = jCV(jINet_OGS,Custom_MsgLoop,true,1,"if (Custom_MsgLoop== true) then called by client game_update()");
	pv_Custom_MsgLoop->Set_bool(isCustom_NetMsgLoop);

	//실행 인자  =  NetConfigXml:xml\net\test_Server_NetConfig.xml app_nic_name:$(ProjectName) default_dll:$(ProjectName).dll
	g_pDllLoader = new jDllLoader_Mech(szNetDLL);
	typedef void* NetClient_Interface_t();
	g_pjIConsoleDLL_net = (nCONSOLE::jIConsoleDLL*)g_pDllLoader->jCreateInterface(nGLOBAL::g_pDocApp->BaseI());
	g_pjIConsoleDLL_net->Start(szNetXmlConfigFile, szNetXmlConfigNode);
}

void run_server()
{
	jLoadNetDll(_T("test_Server.dll") , _T("xml\\net\\test_Server_NetConfig.xml"),jS(test_Server),false);
}
