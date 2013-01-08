// tool_Service.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "jService.h"
#include <conio.h>
using namespace nMech;

fname_t g_szModuleDir;
fname_t g_szNetDLLDir;
fname_t g_szExe;
fname_t g_szINI;
fname_t g_szService;
bool g_isServiceThreadQuit=false;

fname_t g_szNetDLL;
fname_t g_szNetXmlConfigFile;
fname_t g_szNetXmlConfigNode;
int g_isAutoRun = 0;

HMODULE g_hDLL_Net =0;
typedef void jDeleteInterface_t();
jDeleteInterface_t* m_pjDeleteInterface=0;
void unloadNetDll()
{
	g_isServiceThreadQuit=true;
	g_pjIReportEvent = 0;
	if(m_pjDeleteInterface)
	{
		m_pjDeleteInterface();
		m_pjDeleteInterface=0;
	}
	FreeLibrary(g_hDLL_Net);
	g_hDLL_Net=0;

}

void loadNetDll(tcstr szNetDLL , tcstr szNetXmlConfigFile,tcstr szNetXmlConfigNode)
{
	jt_chdir(g_szModuleDir);
	{
		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		TCHAR fname[_MAX_FNAME];
		TCHAR ext[_MAX_EXT];
		_tsplitpath( szNetDLL, drive, dir, fname, ext );
		//주의 : GetPath()의 경우 맨마지막에 "\\"가 붙는다.
		_stprintf(g_szNetDLLDir, TEXT("%s%s"),drive,dir);
		if(jt_strlen(g_szNetDLLDir))
			jt_chdir(g_szNetDLLDir);
	}

	g_hDLL_Net = ::LoadLibrary( _T("jNetDLL_Loader.dll"));
	if(!g_hDLL_Net) return;
	typedef void* jCreateInterface_t(
		tcstr logFilePath // 로그파일 패스
		,tcstr dllName // 로딩할 net dll
		,tcstr netConfigXml // netDLL 용 config xml
		,tcstr netConfigXmlNode // config xml에서의 노드
		,acstr szGetUserInterface // dllName안에 정의된 유저객체를 가져오는 함수 포인터.
		,bool  isService
		);
	jCreateInterface_t* m_pjCreateInterface=0;
	m_pjCreateInterface= (jCreateInterface_t*)::GetProcAddress(g_hDLL_Net, "jCreateInterface");
	m_pjDeleteInterface= (jDeleteInterface_t*)::GetProcAddress(g_hDLL_Net, "jDeleteInterface");
	if(!m_pjCreateInterface) return ;

	typedef nLOG::jIReportEvent* jGetReportEvent_t();
	jGetReportEvent_t* pREfunc = (jGetReportEvent_t*)m_pjCreateInterface(0, szNetDLL 
					, szNetXmlConfigFile , szNetXmlConfigNode ,"jGetReportEvent",true);
	if(pREfunc)
	{
		g_pjIReportEvent = pREfunc();
	}
}

DWORD WINAPI BeepThreadCallback(LPVOID paramter)
{
	Beep(5000,10);

	loadNetDll(g_szNetDLL,g_szNetXmlConfigFile,g_szNetXmlConfigNode);
	while(!g_isServiceThreadQuit)
	{
		//Beep(5000,10);Sleep(4000);
	}
	return 0;
}

class tool_Service: public jService
{
private:
	HANDLE mThreadHandle;
public:
	void Main()
	{
		jService::Begin(g_szService);
		WaitForSingleObject(mThreadHandle,INFINITE);
		jService::End();

	}
protected:
	void OnStarted()
	{
		ja_printf("OnStarted");
		DWORD ThreadID=0;
		mThreadHandle = CreateThread(NULL,0,::BeepThreadCallback,NULL,0,&ThreadID);
	}

	void OnStopped()
	{
		unloadNetDll();
		ja_printf("OnStopped");
		g_isServiceThreadQuit=true;
	}
public:
#if 0
	virtual void CtrlHandlerCallback(DWORD opCode)
	{
		switch (opCode)
		{
		case SERVICE_CONTROL_PAUSE:
			if(mServiceStatus.dwCurrentState!=SERVICE_RUNNING) return;
			unloadNetDll();
			mServiceStatus.dwCurrentState = SERVICE_PAUSED;
			GetRE()->Write(nLOG::eEL_INFORMATION,1,_T("%s contorl message = [SERVICE_CONTROL_PAUSE]"),g_szNetXmlConfigNode);
			break;
		case SERVICE_CONTROL_CONTINUE:
			{
				if(mServiceStatus.dwCurrentState!=SERVICE_PAUSED) return;
				mServiceStatus.dwCurrentState = SERVICE_RUNNING;
				//loadNetDll(g_szNetDLL,g_szNetXmlConfigFile,g_szNetXmlConfigNode);

				DWORD ThreadID=0;
				mThreadHandle = CreateThread(NULL,0,::BeepThreadCallback,NULL,0,&ThreadID);

			}
			GetRE()->Write(nLOG::eEL_INFORMATION,1,_T("%s contorl message = [SERVICE_CONTROL_CONTINUE]"),g_szNetXmlConfigNode);
			break;
		case SERVICE_CONTROL_STOP:
			mServiceStatus.dwWin32ExitCode	= 0;
			mServiceStatus.dwCurrentState	= SERVICE_STOPPED;
			mServiceStatus.dwCheckPoint		= 0;
			mServiceStatus.dwWaitHint		= 0;
			GetRE()->Write(nLOG::eEL_INFORMATION,1,_T("%s contorl message = [SERVICE_CONTROL_STOP]"),g_szNetXmlConfigNode);
			break;
		case SERVICE_CONTROL_INTERROGATE:
			GetRE()->Write(nLOG::eEL_INFORMATION,1,_T("%s contorl message = [SERVICE_CONTROL_INTERROGATE]"),g_szNetXmlConfigNode);

			break;
		default:
			GetRE()->Write(nLOG::eEL_INFORMATION,1,_T("%s contorl message = %d"),g_szNetXmlConfigNode,opCode);

			break;
		}

		if (!SetServiceStatus(mServiceStatusHandle, &mServiceStatus))
			return;
	}
#endif
};


int _tmain(int argc, _TCHAR* argv[])
{
	GetModuleFileName(NULL, g_szExe , sizeof(g_szExe) );
	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	_tsplitpath( g_szExe, drive, dir, fname, ext );

	//주의 : GetPath()의 경우 맨마지막에 "\\"가 붙는다.
	_stprintf(g_szModuleDir, TEXT("%s%s"),drive,dir);
	jt_chdir(g_szModuleDir);
	_stprintf(g_szINI, TEXT("%s%s_config.ini"),g_szModuleDir,fname);
	tool_Service svc;

	FILE* fp = jt_fopen(g_szINI,_T("r") );
	if(!fp)
		goto _ERROR_LABLE;
	fclose(fp);

	GetPrivateProfileString(jS(Service),jS(g_szService),jS(tool_Service), g_szService , sizeof(g_szService)/2 , g_szINI);
	GetPrivateProfileString(jS(Service),jS(g_szNetDLL),jS(NULL), g_szNetDLL , sizeof(g_szNetDLL)/2 , g_szINI);
	GetPrivateProfileString(jS(Service),jS(g_szNetXmlConfigFile),jS(NULL), g_szNetXmlConfigFile , sizeof(g_szNetXmlConfigFile)/2 , g_szINI);
	GetPrivateProfileString(jS(Service),jS(g_szNetXmlConfigNode),jS(NULL), g_szNetXmlConfigNode , sizeof(g_szNetXmlConfigNode)/2 , g_szINI);
	g_isAutoRun = GetPrivateProfileInt(jS(Service),jS(g_isAutoRun),0, g_szINI);

	if(argc > 1)
	{
		if( jt_strcmp(argv[1],_T("-uninstall")) ==0)
		{
			svc.Uninstall(g_szService);
			jt_printf(_T("%s uninstalled"),g_szService);
		}
		else if( jt_strcmp(argv[1],_T("-install")) ==0)
		{
			svc.Install(g_szService,g_isAutoRun);
			jt_printf(_T("%s installed"),g_szService);
		}
		else
		{
			goto _ERROR_LABLE;
		}
		return 0;
	}
	svc.Main();

_ERROR_LABLE:
	printf("using : tool_Service.exe [ -install | -uninstall | -help ]\n");
	printf("<<< tool_Service_config.ini >>>\n");
	
	printf("[Service]\n");
	
	printf("; windows service name \n");
	printf("g_szService=test_Server\n");
	
	printf(";target dll for start server\n");
	printf("g_szNetDLL=test_Server.dll\n");
	
	printf(";target dll config xml file\n");
	printf("g_szNetXmlConfigFile=xml\\net\\test_Server_NetConfig.xml\n");
	
	printf(";config xml node name\n");
	printf("g_szNetXmlConfigNode=test_Server\n");

	printf(";is auto run 	\n");
	printf("g_isAutoRun=0	\n");

	printf("any key to exit\n");
	_getch();

	return 0;
}
