// DB_Cache_App.cpp : main source file for DB_Cache_App.exe
//

#include "stdafx.h"

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>

#include ".\resource.h"
#include ".\aboutdlg.h"
#include ".\MainDlg.h"

#include "common/jInit.h"
#include "interface/jIConsoleCmd.h"
#include "header/jBoost.h"
#include "Interface/jIINI_File.h"


#include <conio.h>


struct  _jDLL
{
	jDllLoader_Mech* m_pDLL;
	nCONSOLE::jIConsoleDLL* m_pConsoleDLL;

	void Clear()
	{
		if(m_pConsoleDLL)
		{
			m_pConsoleDLL->End();
			m_pConsoleDLL=0;
		}
		SAFE_DELETE(m_pDLL);

	}
};
tcstr ToString(_jDLL*p , tname1024_t buf)
{
	jt_sprintf(buf, _T("%s") , p->m_pDLL->m_sDLL.c_str());
	return buf;
}

jLIST_TYPEDEF_map(tstring ,_jDLL , g_mapDLL);
jIVar* g_pvNetConfigXml=0;
_jDLL* g_pCurr_jDLL=0;

jIVar* pvNetConfigNode = jCV(exe,NetConfigNode,g_ExeEnv.m_szAppNic,0,"node name of NetConfigXml  default app_nic_name" );

static bool console_parser(cstr sz)
{
	if(g_pCurr_jDLL && g_pCurr_jDLL->m_pConsoleDLL) 
		return g_pCurr_jDLL->m_pConsoleDLL->ParseCmd(sz);
	return false;
}

// static unsigned __stdcall _run_xgame( void* pThreadParam)
// {
// 	nCONSOLE::jIConsoleDLL* pConsoleDLL = (nCONSOLE::jIConsoleDLL*)pThreadParam;
// 	pConsoleDLL->Start(g_pvNetConfigXml->Get_cstr(), pvNetConfigNode->Get_cstr());
// 	_endthread();
// 	return 0;
// }

jCONSOLE_CMD_AUTO(con,set_net_parser,0,"con.list_net로 출력되는 네트웍 모듈DLL로 명령파서를 바꿈","<net.dll>")
{
	g_mapDLL_it it =g_mapDLL.find(arg[0]);
	if(it==g_mapDLL.end())
	{
		jLOG(_T("해당 net.dll을 못찾음 : %s"), arg[0].c_str());
		return false;
	}
	g_pCurr_jDLL = &it->second;
	return true;
}
jCONSOLE_CMD_AUTO(con,list_net,0,"로딩된 네트웍 모듈DLL 리스트","")
{
	g_mapDLL_it it =g_mapDLL.begin() ,ie =g_mapDLL.end();
	tname1024_t buf;
	for(;it!=ie;++it)
	{
		jLOG(ToString(&it->second , buf));
	}
	jLOG(_T("curr net.dll= %s"), g_pCurr_jDLL->m_pDLL->m_sDLL.c_str());
	return true;
}


jCONSOLE_CMD_AUTO(con,load_net,0,"네트웍 모듈DLL 로딩","<net.dll> <netconfig_node_name> [netconfig_xmlfile]")
{
	tstring sDLL = arg[0];
	tstring netconfig_node_name = arg[1];
	if(arg.size()==3)
	{
		g_pvNetConfigXml->Set_cstr(arg[2].c_str());
	}
	tstring netconfig_xmlfile = g_pvNetConfigXml->Get_cstr();

	using namespace nMech::nCONSOLE;
	g_mapDLL_it it = g_mapDLL.find(sDLL);
	if(it !=g_mapDLL.end())
	{
		//Get_jIConsoleCmd()->UnRegist_ConsoleParser(sDLL.c_str());
		it->second.Clear();
		g_mapDLL.erase(it);
	}
	_jDLL& d = g_mapDLL[sDLL];
	
	nFileSystem::jFolder dir;
	dir.Goto(g_ExeEnv.m_szModuleDir);

	d.m_pDLL = new jDllLoader_Mech(sDLL.c_str());
	d.m_pConsoleDLL= (jIConsoleDLL*)d.m_pDLL->jCreateInterface(0);
	if(!d.m_pConsoleDLL)
	{
		jWARN(_T("load_net(%s) : d.m_pConsoleDLL== NULL "), sDLL.c_str());
		g_mapDLL.erase(sDLL);
		return false;
	}
	bool is = d.m_pConsoleDLL->Start(netconfig_xmlfile.c_str(), netconfig_node_name.c_str());
	if(is==false)
		return false;

	if(g_mapDLL.size()==1)
	{
		fname_t szBuf;
		jt_sprintf(szBuf , _T("Start_%s:%s"),netconfig_xmlfile.c_str() , pvNetConfigNode->Get_cstr());
		nCONSOLE::Get_jIConsoleCmd()->Run(jS(con) , jS(set_title) , szBuf, true,0);
		g_pCurr_jDLL = &d;
	}

	return true;
}

CAppModule _Module;

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainDlg dlgMain;

	if(dlgMain.Create(NULL) == NULL)
	{
		ATLTRACE(_T("Main dialog creation failed!\n"));
		return 0;
	}

	dlgMain.ShowWindow(nCmdShow);
	dlgMain.LoadWinPos();

	void load_main_net_dll();load_main_net_dll();

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}


void load_main_net_dll()
{
	g_pvNetConfigXml = jCV(exe,NetConfigXml,_T("xml\\net\\test_NetConfig.xml"), 0, "(xml\\net\\test_NetConfig.xml)네트웍 객체정보를 참조할 xml");

	//--------------------------------------------------------------------------
	// 로딩할 jConsoleDLL_net 모듈 이름 세팅 
	//--------------------------------------------------------------------------
	jIVar* pvDLL_Name = jCV(exe,default_dll,_T(""),0,"로딩할 디펄트 jIConsoleDLL DLL모듈");
	cstr szDLLName = pvDLL_Name->Get_cstr();

	//--------------------------------------------------------------------------
	// 세번째 인자 : jConsoleDLL_net 이 사용할 net config xml파일에서의 노드 이름 세팅
	//--------------------------------------------------------------------------

	fname_t szCmd;
	jt_sprintf(szCmd,_T("@con.load_net %s %s"), szDLLName , pvNetConfigNode->Get_cstr() );
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
}

void _jConsolePrinterFunc( tcstr szString,bool bAdd )
{
	static HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	static CONSOLE_SCREEN_BUFFER_INFO conInfo;
	static int i =0;
	if(i==0)
	{
		i=1;
		GetConsoleScreenBufferInfo(hCon,&conInfo);
	}
	vector<tstring> out;
	nString::jSplit(szString,_T("$"),out);
	DWORD writtenCount;

	for(size_t i=0; i< out.size(); ++i)
	{
		tcstr sz = out[i].c_str();
		
		if(sz[0]>=1 && sz[0]<9)
		{
			const int iden[]={
				FOREGROUND_BLUE // 0
				,FOREGROUND_GREEN // 1 
				,FOREGROUND_RED //2 
				,FOREGROUND_BLUE|FOREGROUND_INTENSITY //3 
				,FOREGROUND_GREEN|FOREGROUND_INTENSITY //4 
				,FOREGROUND_RED|FOREGROUND_INTENSITY //5 
				,FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_BLUE //6 
				,FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_BLUE // 7
				,FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_BLUE}; //8
			int col = sz[0];
			sz = sz+1;
			SetConsoleTextAttribute(hCon, iden[col]);
		}
		else if(sz[0]==0)
		{
			sz = sz+1;
			SetConsoleTextAttribute(hCon, conInfo.wAttributes);
		}
		else
		{
			SetConsoleTextAttribute(hCon, conInfo.wAttributes);
		}
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), sz, jt_strlen(sz), &writtenCount, NULL);
	}
	if(!bAdd)
	{
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), _T("\n"), 1, &writtenCount, NULL);
	}


}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{

	HRESULT hRes = ::CoInitialize(NULL);
	// If you are running on NT 4.0 or higher you can use the following call instead to 
	// make the EXE free threaded. This means that calls come in on a random RPC thread.
	//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

	//lpstrCmdLine에는 실행파일을 제외한 인자 스트링이 온다.
	if(0 && __argc <2)
	{
		jMB("Use : jConsoleShell.exe [app_nic_name:이름] [default_dll:net_module.dll] [NetConfigNode:netconfig_xml_node_name]", "warning");
		return 1;
	}
	GetjILog()->SetPrinter(_jConsolePrinterFunc);
	jIVar* pvShowConsole = jCV(con,ShowConsoel , true, 0 , "show console window ");
	if(pvShowConsole->Get_bool())
	{
		AllocConsole();
		freopen("CONOUT$", "wt", stdout);
		freopen("CONIN$", "r", stdin);
	}
	else
	{
		FreeConsole();
	}
	nScript::jINI_Data_t pv_log_file_path = g_ExeEnv.Get_INI()->GetData(jS(exe) , jS(log_file_path));
	SYSTEMTIME st;
	GetLocalTime(&st);
	fname_t szDATE;
	jt_sprintf(szDATE,_T("[%3d-%2d-%2d]"),st.wYear,st.wMonth,st.wDay);
	fname_t szBufFileTag;
	jt_sprintf(szBufFileTag, _T("%s\\%s\\%s"),pv_log_file_path->Get_cstr() , szDATE , pvNetConfigNode->Get_cstr());
	GetjILog()->SetFileName(szBufFileTag);

	jMech_Init(true);
	GetjILog()->SetPrinter(_jConsolePrinterFunc);
#if 0
	setlocale( LC_ALL,"kor");
	wprintf(L"wsprintf 하핳");
	jt_printf(_T("jt_sprintf 하핳"));
	jLOG(_T("jLOG 하ㅣ핳ㅇ"));
#endif

	nCONSOLE::Get_jIConsoleCmd()->Regist_ConsoleParser(_T("jConsoleShell") , console_parser );


	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	//--------------------------------------------------------------------------
	jIVar* pvShowDlg = jCV(exe,ShowDlg,true,0,"Show Input Dialog when server starting");

	int nRet =0;
	if(pvShowDlg->Get_bool())
	{
		nRet = Run(lpstrCmdLine, nCmdShow);
		_Module.Term();
		::CoUninitialize();
	}
	else
	{
		void jconsole_LoadWinPos();jconsole_LoadWinPos();
		load_main_net_dll();
		char ch;
		do
		{
			ch = _getch();
		} while( ch != 27 );
		void jconsole_SaveWinPos();jconsole_SaveWinPos();
	}
		
	//nInterface::g_pjINet_OGS->ProcessMsg(_T("g_jThreadManager.EndAll()"),0);
	printf("asdf\n");
	g_mapDLL_it it = g_mapDLL.begin(),ie = g_mapDLL.end();
	for(;it!=ie;++it)
	{
		it->second.Clear();
	}
	g_mapDLL.clear();
	jMech_Close();

 	return nRet;
}
