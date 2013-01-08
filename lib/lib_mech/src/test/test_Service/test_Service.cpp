// test_Service.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "../../server/support/tool_Service/jService.h"
#include "interface/jIConsoleDLL.h"
#include "header/jDllLoader.h"

using namespace nMech;

nCONSOLE::jIConsoleDLL *g_pjIConsoleDLL_net=0;
nMech::jDllLoader_Mech * g_pDllLoader=0;
void jLoadNetDll(tcstr szNetDLL , tcstr szNetXmlConfigFile,tcstr szNetXmlConfigNode,bool isCustom_NetMsgLoop=false)
{
	jIVar* pv_Custom_MsgLoop = jCV(jINet_OGS,Custom_MsgLoop,true,1,"if (Custom_MsgLoop== true) then called by client game_update()");
	pv_Custom_MsgLoop->Set_bool(isCustom_NetMsgLoop);

	nFileSystem::jFolder dir;
	dir.Goto(g_ExeEnv.m_szModuleDir);

	//실행 인자  =  NetConfigXml:xml\net\test_Server_NetConfig.xml app_nic_name:$(ProjectName) default_dll:$(ProjectName).dll
	g_pDllLoader = new jDllLoader_Mech(szNetDLL);
	typedef void* NetClient_Interface_t();
	g_pjIConsoleDLL_net = (nCONSOLE::jIConsoleDLL*)g_pDllLoader->jCreateInterface(nGLOBAL::g_pDocApp->BaseI());
	g_pjIConsoleDLL_net->Start(szNetXmlConfigFile, szNetXmlConfigNode);
}


bool g_isQuit=false;
DWORD WINAPI BeepThreadCallback(LPVOID paramter)
{

	Beep(5000,10);
	jLoadNetDll(_T("test_Server.dll") , _T("xml\\net\\test_Server_NetConfig.xml"),jS(test_Server),false);
	while(!g_isQuit)
	{
		Beep(5000,10);Sleep(4000);
	}
	return 0;
}

class CTest: public jService
{
private:
	HANDLE mThreadHandle;
public:
	void Main()
	{
		jService::Begin(_T("TestService"));
		WaitForSingleObject(mThreadHandle,INFINITE);
		jService::End();

	}
protected:
	void OnStarted()
	{
		jt_printf(jS(OnStarted));
		DWORD ThreadID=0;
		mThreadHandle = CreateThread(NULL,0,::BeepThreadCallback,NULL,0,&ThreadID);
	}

	void OnStopped()
	{
		ja_printf("OnStopped");
		g_isQuit=true;
		if(g_pjIConsoleDLL_net) 
			g_pjIConsoleDLL_net->End();
		SAFE_DELETE (g_pDllLoader);

	}
};




int _tmain(int argc, _TCHAR* argv[])
{

	jMech_Init(true);

	CTest test;
	if(argc > 1)
	{
		if( jt_strcmp(argv[1],_T("-uninstall")) ==0)
		{
			test.Uninstall(_T("Test Service"));
		}
		else
		if( jt_strcmp(argv[1],_T("-install")) ==0)
		{
			test.Install(_T("Test Service"));
		}
		return 0;
	}
	test.Main();
	jMech_Close();

	return 0;
}

/*
C:\Documents and Settings\user>sc start "Test Service"

SERVICE_NAME: Test Service
TYPE               : 10  WIN32_OWN_PROCESS
STATE              : 2  START_PENDING
(NOT_STOPPABLE,NOT_PAUSABLE,IGNORES_SHUTDOWN)
WIN32_EXIT_CODE    : 0  (0x0)
SERVICE_EXIT_CODE  : 0  (0x0)
CHECKPOINT         : 0x0
WAIT_HINT          : 0x7d0
PID                : 2524
FLAGS              :

C:\Documents and Settings\user>sc stop "Test Service"

SERVICE_NAME: Test Service
TYPE               : 10  WIN32_OWN_PROCESS
STATE              : 1  STOPPED
(NOT_STOPPABLE,NOT_PAUSABLE,IGNORES_SHUTDOWN)
WIN32_EXIT_CODE    : 0  (0x0)
SERVICE_EXIT_CODE  : 0  (0x0)
CHECKPOINT         : 0x0
WAIT_HINT          : 0x0


*/
