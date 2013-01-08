/* file : cmd_Tool.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-04-23 03:18:53
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "common/jInit.h"
#include "Interface/jIINI_File.h"
#include <conio.h>
#include "interface/jIConsoleDlg.h"
#include <process.h>

bool g_isShowedCon=false;
bool g_is_show_cmd_dlg = false;

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

static void unload_mapDLL()
{
	g_mapDLL_it it = g_mapDLL.begin(),ie = g_mapDLL.end();
	for(;it!=ie;++it)
	{
		it->second.Clear();
	}
	g_mapDLL.clear();

}
jIVar* pvNetConfigNode = jCV(exe,NetConfigNode,g_ExeEnv.m_szAppNic,0,"node name of NetConfigXml  default app_nic_name" );

static bool console_parser(cstr sz)
{
	if(g_pCurr_jDLL && g_pCurr_jDLL->m_pConsoleDLL) 
		return g_pCurr_jDLL->m_pConsoleDLL->ParseCmd(sz);
	else
	{
		jLOG(sz);
	}
	return false;
}

// static unsigned __stdcall _run_xgame( void* pThreadParam)
// {
// 	nCONSOLE::jIConsoleDLL* pConsoleDLL = (nCONSOLE::jIConsoleDLL*)pThreadParam;
// 	pConsoleDLL->Start(g_pvNetConfigXml->Get_cstr(), pvNetConfigNode->Get_cstr());
// 	_endthread();
// 	return 0;
// }

jCONSOLE_CMD_AUTO(con,set_net_parser,0,"con.list_net�� ��µǴ� ��Ʈ�� ���DLL�� ����ļ��� �ٲ�","<net.dll>")
{
	g_mapDLL_it it =g_mapDLL.find(arg[0]);
	if(it==g_mapDLL.end())
	{
		jLOG(_T("�ش� net.dll�� ��ã�� : %s"), arg[0].c_str());
		return false;
	}
	g_pCurr_jDLL = &it->second;
	return true;
}
jCONSOLE_CMD_AUTO(con,list_net,0,"�ε��� ��Ʈ�� ���DLL ����Ʈ","")
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


jCONSOLE_CMD_AUTO(con,load_net,0,"��Ʈ�� ���DLL �ε�","<net.dll> <netconfig_node_name> [netconfig_xmlfile]")
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
		d.m_pDLL->jDeleteInterface();
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


void load_main_net_dll()
{
	g_pvNetConfigXml = jCV(exe,NetConfigXml,_T("xml\\net\\test_NetConfig.xml"), 0, "(xml\\net\\test_NetConfig.xml)��Ʈ�� ��ü������ ������ xml");

	//--------------------------------------------------------------------------
	// �ε��� jConsoleDLL_net ��� �̸� ���� 
	//--------------------------------------------------------------------------
	jIVar* pvDLL_Name = jCV(exe,default_dll,_T(""),0,"�ε��� ����Ʈ jIConsoleDLL DLL���");
	cstr szDLLName = pvDLL_Name->Get_cstr();

	//--------------------------------------------------------------------------
	// ����° ���� : jConsoleDLL_net �� ����� net config xml���Ͽ����� ��� �̸� ����
	//--------------------------------------------------------------------------

	fname_t szCmd;
	jt_sprintf(szCmd,_T("@con.load_net %s %s"), szDLLName , pvNetConfigNode->Get_cstr() );
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
}


void set_logfile_name()
{
	nScript::jINI_Data_t pv_log_file_path = g_ExeEnv.Get_INI()->GetData(jS(exe) , jS(log_file_path));
	SYSTEMTIME st;
	GetLocalTime(&st);
	fname_t szDATE;
	jt_sprintf(szDATE,_T("[%3d-%2d-%2d]"),st.wYear,st.wMonth,st.wDay);
	fname_t szBufFileTag;
	jt_sprintf(szBufFileTag, _T("%s\\%s\\%s"),pv_log_file_path->Get_cstr() , szDATE , pvNetConfigNode->Get_cstr());
	GetjILog()->SetFileName(szBufFileTag);
}

BOOL WINAPI jConsoleCtrlHandler(DWORD dwCtrlType )
{
	BOOL toRet = FALSE;

	switch( dwCtrlType )
	{
	case CTRL_CLOSE_EVENT:
	case CTRL_SHUTDOWN_EVENT:
	case CTRL_BREAK_EVENT:
		//hide_console_window();

		return FALSE;
		break;
	case CTRL_C_EVENT:
	case CTRL_LOGOFF_EVENT:
	default:
		return FALSE;
		break;
	};

	return FALSE;
}
// 
// typedef LRESULT CALLBACK WndProc_t(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
// WndProc_t* g_WndProc;
// 
// static LRESULT CALLBACK jConsoleWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
// {
// 	switch(uMsg)
// 	{
// 	case WM_NCDESTROY:
// 	case WM_CLOSE:
// 		break;
// 	}
// 	return g_WndProc(hwnd,uMsg,wParam,lParam);
// }

nMech::nCONSOLE::jIConsoleDlg *g_pjIConsoleDlg=0;
int init_Tool()
{
	jIVar* pvShowConsole = jCV(con,ShowConsole , false, 0 , "show console window ");
	if(pvShowConsole->Get_bool())
	{
		show_console_window();
	}

	//<jILog b_ENABLE='0'>jLog.dll</jILog>
	nXML::jE eDLL = nGLOBAL::g_pDocApp->Find(jS(DLL));
	nXML::jE e = eDLL[jS(jIConsoleDlg)];
	e.AttrP(jS(ENABLE)).T() = true;
	e.Var().T() = _T("jConsoleDlg.dll");

	void set_logfile_name();
	set_logfile_name();
	jMech_Init(true);

	jIConsoleDlg_GET(pConDlg);
	jvCHECK(pConDlg,_T("jIConsoleDlg.dll not loaded"));

	GetjILog()->SetPrinter(0);
	nCONSOLE::Get_jIConsoleCmd()->Regist_ConsoleParser(_T("jConsole_ATL") , console_parser );

	//--------------------------------------------------------------------------
	HWND hWnd = 0;
	if(pConDlg)
		hWnd  = pConDlg->console_LoadWinPos(pvNetConfigNode->Get_cstr());
	g_pjIConsoleDlg = pConDlg;

// 	if(hWnd)
// 	{
// 		g_WndProc = (WndProc_t*)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)jConsoleWndProc);
// 	}


	//load_main_net_dll();
	return 0;
}


unsigned int    __stdcall _tool_thread(void* v)
{
	HINSTANCE hInstance= (HINSTANCE)v;
	if(g_pjIConsoleDlg)
		g_pjIConsoleDlg->Run_WTL_Dlg(hInstance, SW_NORMAL,_T("dlg_name"),AfxGetApp()->m_pMainWnd->m_hWnd);
	return 0;
}

void toggle_cmd_dlg()
{
	if(!g_pjIConsoleDlg) return;
	if(g_is_show_cmd_dlg)
	{
		g_is_show_cmd_dlg=false;
		ShowWindow(g_pjIConsoleDlg->GetDlgHWnd()  ,SW_HIDE);
	}
	else
	{
		g_is_show_cmd_dlg=true;
		ShowWindow(g_pjIConsoleDlg->GetDlgHWnd()  ,SW_SHOW);
	}

}
bool cancel_Tool()
{
	toggle_cmd_dlg();
	return true;
}

void show_Tool(HINSTANCE hInstance)
{
	//g_pjIConsoleDlg->Set_Canceler(cancel_Tool);
	g_pjIConsoleDlg->Set_Finalizer(close_Tool);
	//unsigned int m_nID;
	//_beginthreadex(NULL, 0, &_tool_thread, hInstance, 0, &m_nID);
	g_is_show_cmd_dlg=true;
	if(g_pjIConsoleDlg)
		g_pjIConsoleDlg->Run_WTL_Dlg(hInstance, SW_NORMAL,_T("dlg_name"),AfxGetApp()->m_pMainWnd->m_hWnd);

}

bool close_Tool()
{
	if(g_pjIConsoleDlg)g_pjIConsoleDlg->console_SaveWinPos();
	unload_mapDLL();
	jMech_Close();
	return true;
}


void hide_console_window()
{
	if(g_pjIConsoleDlg)g_pjIConsoleDlg->console_SaveWinPos();
	g_isShowedCon=false;
	FreeConsole();
}
void show_console_window()
{
	g_isShowedCon=true;
	AllocConsole();
	freopen("CONOUT$", "wt", stdout);
	freopen("CONIN$", "r", stdin);

	if(g_pjIConsoleDlg )
		g_pjIConsoleDlg ->console_LoadWinPos(pvNetConfigNode->Get_cstr());

	//SetConsoleCtrlHandler(jConsoleCtrlHandler,TRUE );

}


jCONSOLE_CMD_AUTO(con,toggle_console,0,"�ܼ�â ���","")
{
	if(g_isShowedCon)
	{
		hide_console_window();
	}
	else
	{
		show_console_window();
	}
	return true;
}

