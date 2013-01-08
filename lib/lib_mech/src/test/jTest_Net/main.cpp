#include "stdafx.h"
#include "dialog.h"
#include "jInit.h"

extern jNetPortCallback g_ClientCB ;
extern jNetPortCallback g_ServerCB ;
extern jNetPortCallback g_HostServerCB;
extern jNetPortCallback g_HostClientCB;

jINetPort* g_pGameServer=0;
jIConnection* g_pClientCon = NULL;

jINetPort* g_pHostServer=0;
jIConnection* g_pHostServerCon=0;



void ServerUpdate()
{
	g_pjINet->FrameMove();
	jIMsgManager::FrameMove();
}

int main(int argc, _TCHAR* argv[])
{
	if(argc==4)
	{//jTest_NetHostClient
		cstr szArg = argv[1];
		jUtil_Init(szArg, true);

		g_pHostServer= g_pjINet->FindNetPort("jHostServer");
		g_pHostServerCon = g_pHostServer->StartService(g_HostClientCB);
	}
	else if(argc==3)
	{ //jTest_NetHost
		cstr szArg = argv[1];
		jUtil_Init(szArg, true);
		g_pGameServer = g_pjINet->FindNetPort("jGameServer");
		g_pClientCon = g_pGameServer->StartService(g_ClientCB);

		g_pHostServer = g_pjINet->FindNetPort("jHostServer");
		g_pHostServerCon = g_pHostServer->StartService(g_HostServerCB);
	}
	else if(argc==2)
	{// jTest_NetClient
		cstr szArg = argv[1];
		jUtil_Init(szArg, true);
		g_pGameServer = g_pjINet->FindNetPort("jGameServer");
		g_pClientCon = g_pGameServer->StartService(g_ClientCB);
	}
	else 
	{//jTest_Net
		jUtil_Init("jTest_Net");
		g_pGameServer = g_pjINet->FindNetPort("jGameServer");
		g_pClientCon = g_pGameServer->StartService(g_ServerCB);
	}

	InitializeDialog();
	
	// Enter the message loop
	MSG msg; 
	ZeroMemory( &msg, sizeof(msg) );
	while( msg.message!=WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
			ServerUpdate();
	}
/* *_* by icandoit : 2006-02-27 00:22:44

	MSG msg;
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
/* *_* by icandoit : 2006-02-26 20:13:54

	fname_t buf ;
	while(1)
	{
		int iCnt = g_pjINet->ConsoleInput(buf, sizeof(buf)) ;
		if(iCnt )
		{
			if(iCnt>=sizeof(buf))
				iCnt = sizeof(buf)-1;
			buf[iCnt]=0;
		}
	}
*/ //*_* by icandoit : 2006-02-26 20:13:56

	if(g_pGameServer)g_pGameServer->StopService();

	jUtil_Close();
	return 0;
}
