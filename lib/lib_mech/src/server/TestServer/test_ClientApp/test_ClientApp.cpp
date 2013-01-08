// test_ClientApp.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>
#include "interface/jISystemPlugIn.h"
#include "common/jInit.h"
#include "interface/jIConsoleDLL.h"
#include "header/jDllLoader.h"
#include "Interface/ITimer.h"


nMech::jDllLoader_Mech * g_pDllLoader=0;
nCONSOLE::jIConsoleDLL *g_pjIConsoleDLL_net=0;
jINetClient* g_pjINetClient;

void jLoadNetDll(tcstr szNetDLL , tcstr szNetXmlConfigFile,tcstr szNetXmlConfigNode,bool isCustom_NetMsgLoop=false)
{
	jIVar* pv_Custom_MsgLoop = jCV(jINet_OGS,Custom_MsgLoop,true,1,"if (Custom_MsgLoop== true) then called by client game_update()");
	pv_Custom_MsgLoop->Set_bool(isCustom_NetMsgLoop);

	//실행 인자  =  NetConfigXml:xml\net\test_Server_NetConfig.xml app_nic_name:$(ProjectName) default_dll:$(ProjectName).dll

	nFileSystem::jFolder dir;
	dir.Goto(g_ExeEnv.m_szModuleDir);

	g_pDllLoader = new jDllLoader_Mech(szNetDLL);
	typedef void* NetClient_Interface_t();
	NetClient_Interface_t* pNetClient_Interface= (NetClient_Interface_t*)g_pDllLoader->GetFunc("Get_NetClient_Interface");
	g_pjINetClient = (jINetClient*)pNetClient_Interface();
	g_pjIConsoleDLL_net = (nCONSOLE::jIConsoleDLL*)g_pDllLoader->jCreateInterface(nGLOBAL::g_pDocApp->BaseI());
	g_pjIConsoleDLL_net->Start(szNetXmlConfigFile, szNetXmlConfigNode);
	//g_pjINetClient->NetworkStart();
}


bool game_console_parsor(tcstr sz)
{
	return g_pjIConsoleDLL_net->ParseCmd(sz);
}


void game_update()
{
	nTIME::Get_ITimer()->Update();
}


void game_init()
{
	// *_* by icandoit : 2010-02-11 18:38:48
	//
	nCONSOLE::Get_jIConsoleCmd()->Regist_ConsoleParser(g_ExeEnv.m_szAppNic , game_console_parsor );
	jSystemPlugIn_func fn;
	fn.m_OnFrameMove = game_update;
	Get_jISystemPlugIn()->Regist(0,&fn );

	jMech_Init();
	assert(nGLOBAL::g_pDocApp);

}



void game_close()
{
	if(g_pjIConsoleDLL_net) 
		g_pjIConsoleDLL_net->End();
	SAFE_DELETE (g_pDllLoader);
	jMech_Close();
}

bool g_isQuit=false;
DWORD WINAPI cb(LPVOID paramter)
{
	char ch;
	do
	{
		ch = _getch();
	} while( ch != 27 );
	g_isQuit=true;
	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	game_init();
	jLoadNetDll(_T("test_Client.dll") , _T("xml\\net\\test_Server_NetConfig.xml"),jS(test_Client),true);
	DWORD ThreadID=0;
	CreateThread(NULL,0,::cb,NULL,0,&ThreadID);
	while(!g_isQuit)
	{
		Get_jISystemPlugIn()->OnFrameMove();
	}
	game_close();
	return 0;
}

