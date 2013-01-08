// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include ".\resource.h"

#include ".\aboutdlg.h"
#include ".\maindlg.h"

#include <list>
#include "header/jDefine.h"
#include "header/m_stltag.h"
#include "base/uStringParsor.h"
#include "interface/jIConsoleCmd.h"
using namespace nMech;

#include "base/jMsgManager.h"
#include "base/jxVar.h"
#include "util/jRegistry.h"
#include "Interface/jIConsoleCmd.h"
#include "interface/jIConsoleVar.h"

#define TIMER_CONNECT 1
HWND m_ConsoleHWND=0;


jLIST_TYPEDEF_vector(CString,g_listCmd);
jLIST_TYPEDEF_list(CString,g_cmdHelp);




CMainDlg* CMainDlg::m_pSingleton = NULL;
WNDPROC g_hEditProc;
const int maxLIST = 160;
const int iSTART_MENU_INDEX = 2000000;


jIVar* pvCMD_CACHE_FILE = jCV(exe,CMD_CACHE_FILE,_T("D:\\svn\\common\\Server\\Tool\\bin\\BaseballTestClient1.cmd.txt") , 0, "default cmd list file that will be load and display to ListControl");

static bool ReadLineFromFile(TCHAR* buf, int buf_size, FILE* pF)
{
	if( jt_fgets( buf, buf_size-1, pF ) == NULL)
	{
		buf=NULL; return false;
	}
	size_t len = _tcslen(buf);
	buf[len-1] = NULL; // 여기까지 file로 부터 한라인 읽어서 마지막 의 개행문자를 제거.
	return true;
}

tcstr make_menu_key_name(jIE* it,fname_t szName)
{
	jIVar* pvKEY = it->GetAttrVar(jS(KEY));
	if(pvKEY)
	{
		tname_t szT;
		jt_strcpy(szT,pvKEY->Get_cstr());
		jt_sprintf(szName , _T("&%c : %s") , szT[0],it->GetVar()->IsType(jIVar::ETelement) ? it->GetTagName() : it->Get_cstr());
		return szName;
	}
	jt_strcpy( szName , it->Get_cstr());
	return szName;
}

#define jLAMDA_jxMakeMenu(X,Z) Z(CMenu*,pMenuP)
jLAMDA_for_each(jxMakeMenu,jIE*)
{
	uint32 iHandle = it->GetHandle();
	jASSERT0(iSTART_MENU_INDEX > iHandle);
	fname_t szName;
	if(it->GetVar()->IsType(jIVar::ETelement)) 
	{
		CMenu* pMenu = (CMenu*)it->GetUserData(jS(CMenu));
		if(pMenu) delete pMenu;
		pMenu = new CMenu;
		pMenu->CreatePopupMenu();
		it->SetUserData(jS(CMenu) , pMenu);
		it->for_each_child(jxMakeMenu(pMenu));
		if(pMenuP)
			pMenuP->AppendMenu(MF_POPUP, pMenu->m_hMenu, make_menu_key_name(it, szName));
	}
	else if(it->GetVar()->IsType(jIVar::EDcstr))
	{
		pMenuP->AppendMenu (MF_STRING|MF_ENABLED, (UINT_PTR)it->GetHandle(), make_menu_key_name(it,szName) );
	}
}
jLAMDA_end();


void load_cmd_file()
{
#if 0
	nXML::jE e = nGLOBAL::g_pDocApp->BaseI();
	e = e[jS(ConsoleCmdList)];
	e->for_each_child(jxMakeMenu(0));
#endif

	g_listCmd.clear();
	nFileSystem::jFolder dir;
	fname_t buf;
	jt_sprintf(buf, _T("%s.cmd.txt"),g_ExeEnv.m_szAppNic);
	FILE* fp = jt_fopen(buf, _T("rt"));
	if(fp)
	{
		TCHAR buf[1024];
		while(ReadLineFromFile(buf,sizeof(buf),fp))
		{
			g_listCmd.push_back(buf);
		}
		fclose(fp);
	}

	std::sort(g_listCmd.begin() ,g_listCmd.end());
}

void save_cmd_file()
{
	fname_t buf;
	jt_sprintf(buf, _T("%s.cmd.txt"),g_ExeEnv.m_szAppNic);
	FILE* fp = jt_fopen(buf, _T("wt"));
	if(fp)
	{
		std::sort(g_listCmd.begin(),g_listCmd.end());
		g_listCmd_it it = g_listCmd.begin(), ie = g_listCmd.end();
		for( ; it!=ie ; ++it)
		{
			CString &str = *it;
			jt_fprintf(fp , _T("%s\n"),str);
		}
		fclose(fp);
	}

}

jCONSOLE_CMD_AUTO(con,reload_cmd,0,"reload cmd file","")
{
	load_cmd_file();
	return true;
}

jCONSOLE_CMD_AUTO(con,open_cmd,0,"open cmd file","[isOpenUsed_CmdFile]")
{
	nFileSystem::jFolder dir(true);
	afname_t szFile,szExeCmd;
	if(arg.size())
	{
		save_cmd_file();
		ja_sprintf(szFile, ("%s.cmd.txt"),jA(g_ExeEnv.m_szAppNic));
	}
	else
	{
		ja_sprintf(szFile, ("xml\\%s.cmd.help.txt"),jA(g_ExeEnv.m_szAppNic));
	}

	if( !dir.Is_Exist(jT(szFile)) )
	{
		nFileSystem::UFile fp(jT(szFile),_T("wt"));
		fp.fclose();
	}
	ja_sprintf(szExeCmd, ("notepad %s"),szFile);
	WinExec(szExeCmd,SW_SHOW);
	return true;
}
jCONSOLE_CMD_AUTO(con,close,0,"close console & dlg","")
{
	if(CMainDlg::m_pSingleton)
	{
		SendMessage(CMainDlg::m_pSingleton->m_hWnd, WM_CLOSE,99, 99);
		//CMainDlg::m_pSingleton->CloseDialog(0);
	}
	return true;
}

jCONSOLE_CMD_AUTO(con,message,0,"set message to CONSOLE display","<message>")
{
	if(CMainDlg::m_pSingleton)
		CMainDlg::m_pSingleton->SetDlgItemText( IDC_STATIC_MESSAGE, arg[0].c_str());
	return false;
}
jCONSOLE_CMD_AUTO(con,message_txt,0,"set text to CONSOLE info display","<message>")
{
	if(CMainDlg::m_pSingleton)
		CMainDlg::m_pSingleton->SetDlgItemText( IDC_SERVERINFO, arg[0].c_str());
	return false;
}

jCONSOLE_CMD_AUTO(con,set_title,0,"콘솔의 제목설정","<제목>")
{
	if(CMainDlg::m_pSingleton)
		CMainDlg::m_pSingleton->SetWindowText(arg[0].c_str());
	return false;
}

jCONSOLE_CMD_AUTO(con,regist_cmd,0,"매크로리스트에 명령을 등록한다. 공백은 #으로 채운다","<명령>")
{
	CString txt = arg[0].c_str();
	txt.Replace('#',' ');
	g_listCmd_it it = find(g_listCmd.begin(),g_listCmd.end(),txt);
	if(it==g_listCmd.end())
	{
		g_listCmd.push_back(txt);
		if(g_listCmd.size()>maxLIST)
			g_listCmd.erase(g_listCmd.begin());
	}
	return false;
}


#define jLAMDA_jxMakeDefaultCmdMenu(X,Z) X(int,index) Z(CMenu*,pMenuP)
jLAMDA_for_each(jxMakeDefaultCmdMenu,jIE*)
{
	uint32 iHandle = it->GetHandle();
	jASSERT0(iSTART_MENU_INDEX > iHandle);
	fname_t szName;
	if(it->size()) 
	{
		CMenu* pMenu = (CMenu*)it->GetUserData(jS(CMenu));
		if(pMenu) delete pMenu;
		pMenu = new CMenu;
		pMenu->CreatePopupMenu();
		it->SetUserData(jS(CMenu) , pMenu);
		it->for_each_child(jxMakeDefaultCmdMenu(1,pMenu));
		if(pMenuP)
		{
			jt_sprintf(szName , _T("&%d %s"), index++,it->GetTagName());
			pMenuP->AppendMenu(MF_POPUP, pMenu->m_hMenu, szName);
		}
	}
	else 
	{
		tcstr szA = it->GetAttr(jS(m_szArgHelp));
		if(!szA)
		{
			it->DebugPrint(true);
		}
		size_t len = jt_strlen(szA);
		if(len)
		{
			jt_sprintf(szName, _T("@%s.%s %s") 
				, it->GetParent()->GetTagName()
				, it->GetTagName()
				, szA
				);
		}
		else
		{
			jt_sprintf(szName, _T("&%d @%s.%s") 
				, index++
				, it->GetParent()->GetTagName()
				, it->GetTagName()
				);
		}
		pMenuP->AppendMenu (MF_STRING|MF_ENABLED, (UINT_PTR)it->GetHandle(), szName );
	}
}
jLAMDA_end();

#define jLAMDA_jxMakeDefaultVarMenu(X,Z) X(int,index) Z(CMenu*,pMenuP)
jLAMDA_for_each(jxMakeDefaultVarMenu,jIE*)
{
	uint32 iHandle = it->GetHandle();
	jASSERT0(iSTART_MENU_INDEX > iHandle);
	fname_t szName;
	if(it->size()) 
	{
		CMenu* pMenu = (CMenu*)it->GetUserData(jS(CMenu));
		if(pMenu) delete pMenu;
		pMenu = new CMenu;
		pMenu->CreatePopupMenu();
		it->SetUserData(jS(CMenu) , pMenu);
		it->for_each_child(jxMakeDefaultVarMenu(1,pMenu));
		if(pMenuP)
		{
			jt_sprintf(szName , _T("&%d %s"), index++,it->GetTagName());
			pMenuP->AppendMenu(MF_POPUP, pMenu->m_hMenu, szName);
		}
	}
	else 
	{
		tname256_t szBuf;
		cstr szHelp = it->GetAttr(jS(HELP));
		if(szHelp && jt_strlen(szHelp))
		{
			jt_sprintf(szName, _T("!%s.%s <%s> //%s") 
				, it->GetParent()->GetTagName()
				, it->GetTagName()
				, it->GetVar()->ToString(szBuf)
				, it->GetAttr(jS(HELP))
				);
		}
		else
		{
			jt_sprintf(szName, _T("!%s.%s <%s>") 
				, it->GetParent()->GetTagName()
				, it->GetTagName()
				, it->GetVar()->ToString(szBuf)
				);
		}
		pMenuP->AppendMenu (MF_STRING|MF_ENABLED, (UINT_PTR)it->GetHandle(), szName );
	}
}
jLAMDA_end();

static bool g_isResetComplete=0;
static bool g_isCompleteBegin=false;

LRESULT CALLBACK NewProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(!CMainDlg::m_pSingleton) return 0;
	switch(msg)
	{
	case WM_KEYUP:
		{
			if(wParam != VK_DOWN)
			{
				g_isResetComplete =true;
				g_isCompleteBegin=true;
			}

			switch(wParam)
			{
			case VK_RETURN:
				{
					if(GetAsyncKeyState(VK_LCONTROL))
						break;
					CString txt;
					CMainDlg::m_pSingleton->m_edit.GetWindowText(txt);
					if(!txt.GetLength() )	break;
					if(!nCONSOLE::Get_jIConsoleCmd()->ParseCmd(txt)) 
					{
						CMainDlg::m_pSingleton->m_edit.SetWindowText(_T(""));
						break;
					}
					//ParseCmd가 성공하면 명령기록에 남긴다.
					g_listCmd_it it = find(g_listCmd.begin(),g_listCmd.end(),txt);
					if(it==g_listCmd.end())
					{
						g_listCmd.push_back(txt);
						if(g_listCmd.size()>maxLIST)
							g_listCmd.erase(g_listCmd.begin());
					}
					CMainDlg::m_pSingleton->m_edit.SetWindowText(_T(""));

					CMainDlg::m_pSingleton->LogCmd(txt);
					break;
				}
			case VK_DOWN:
				{
					CString txt;
					CMainDlg::m_pSingleton->m_edit.GetWindowText(txt);
					if(txt.GetLength() && (txt[0]=='!' || txt[0]=='@') )
					{
						bool isVar = txt[0]=='!';
						txt.Delete(0,1);
						if(g_isCompleteBegin)
						{
							g_isCompleteBegin=false;
						}
						else
						{
							g_isResetComplete=false;
						}
						if(isVar)
						{
							if(g_isResetComplete)
								nCONSOLE::Get_jIConsoleVar()->ResetAutoCompletion();

							std::tstring sz = std::tstring(_T("!")) + nCONSOLE::Get_jIConsoleVar()->ProcessCompletion(txt);
							CMainDlg::m_pSingleton->m_edit.SetWindowText(sz.c_str());
						}
						else
						{
							if(g_isResetComplete)
								nCONSOLE::Get_jIConsoleCmd()->ResetAutoCompletion();

							std::tstring sz = std::tstring(_T("@")) + nCONSOLE::Get_jIConsoleCmd()->ProcessCompletion(txt);
							CMainDlg::m_pSingleton->m_edit.SetWindowText(sz.c_str());
						}
					}
					break;
				}
			case VK_UP:
				{
					CMenu menuMain;
					menuMain.CreatePopupMenu ();
					CMenu defaultCmdMenu;
					defaultCmdMenu.CreatePopupMenu ();
					CMenu consoleMenu;
					consoleMenu.CreatePopupMenu ();

					//#--------------------------------------------------------------------------
					//자동등록되어 있는 jConsoleCmd 명령 등록.
					//#--------------------------------------------------------------------------
					jID* pD = GetjIXml()->GetObj(jS(jConsoleCmd));
					if(pD)
					{
						pD->BaseI()->for_each_child(jxMakeDefaultCmdMenu(1,&defaultCmdMenu) );
						menuMain.AppendMenu(MF_POPUP, defaultCmdMenu.m_hMenu, _T("&@"));
					}//jID* pD = GetjIXml()->GetObj(jS(jConsoleCmd));

					nXML::jE e = nGLOBAL::g_pDocApp->BaseI();
					e = e[jS(ConsoleCmdList)];
					e->for_each_child(jxMakeMenu(&menuMain));


					//#--------------------------------------------------------------------------
					//자동등록되어 있는 jConsoleVar 변수등록.
					//#--------------------------------------------------------------------------
					jID* pDocCV = nCONSOLE::Get_jIConsoleVar()->GetDoc();
					if(pDocCV)
					{
						jIE* pE = pDocCV->BaseI();
						if(pE)
						{
							pE->for_each_child(jxMakeDefaultVarMenu(1,&consoleMenu) );
							menuMain.AppendMenu(MF_POPUP, consoleMenu.m_hMenu, _T("&!"));
						}
					}

					//#--------------------------------------------------------------------------
					//사용된 명령 리스트에 있는 명령 등록.
					//#--------------------------------------------------------------------------
					g_listCmd_it it = g_listCmd.begin(), ie = g_listCmd.end();
					jLIST_TYPEDEF_map(CString, g_listCmd_t , cmdCategory);
					for(;it!=ie;++it)
					{
						fname_t szCmd;
						jt_strcpy(szCmd,*it);
						if(szCmd[0]=='#')
						{
							cmdCategory[jS(#)].push_back(szCmd);
							continue;
						}
						TCHAR* ch = jt_strchr(szCmd,'.');
						if(!ch)
						{
							cmdCategory[jS(NULL)].push_back(szCmd);
							continue;
						}
						*ch=0;
						cmdCategory[szCmd].push_back(*it);
					}

					cmdCategory_it itC= cmdCategory.begin(), ieC = cmdCategory.end();
					int i=0;
					CString listTemp[3*maxLIST+1];
					for( ; itC!=ieC ; ++itC)
					{
						g_listCmd_it it = itC->second.begin(), ie = itC->second.end();
						CMenu subMain;
						CMenu * pMenu=0;
						if(itC->first==jS(NULL))
						{
							pMenu = &menuMain;
						}
						else
						{
							subMain.CreatePopupMenu();
							pMenu = &subMain;
						}

						for( ; it != ie ; ++it)
						{
							pMenu->AppendMenu (MF_STRING|MF_ENABLED, iSTART_MENU_INDEX + i, *it);
							listTemp[i] = (*it);
							++i;
						}
						if(pMenu!= &menuMain)
						{
							menuMain.AppendMenu(MF_POPUP, pMenu->m_hMenu, itC->first);
						}
					}

					int iTotList = CMainDlg::m_pSingleton->m_lv_log.GetCount();
					for(int idxL =0; idxL < iTotList ; ++idxL)
					{
						fname_t szCmd;
						CMainDlg::m_pSingleton->m_lv_log.GetText(idxL,szCmd);
						menuMain.AppendMenu (MF_STRING|MF_ENABLED, iSTART_MENU_INDEX + i, szCmd);
						listTemp[i] = szCmd;
						++i;
					}


					RECT p;
					CMainDlg::m_pSingleton->m_edit.GetWindowRect(&p);
					int iCmd = menuMain.TrackPopupMenu (TPM_LEFTALIGN | TPM_LEFTBUTTON 
						| TPM_RIGHTBUTTON | TPM_RETURNCMD
						, p.left, p.top, CMainDlg::m_pSingleton->m_edit.m_hWnd);

					if(!iCmd) break;
					if(iCmd >= iSTART_MENU_INDEX && iCmd < (iSTART_MENU_INDEX+i))
					{
						CString sz = listTemp[iCmd-iSTART_MENU_INDEX];
						CMainDlg::m_pSingleton->m_edit.SetWindowText(sz);
					}
					else
					{
						jIE* pE = GetjIXml()->FindElementByHandle(iCmd);
						if(!pE)
						{
							jMB(_T("menu element를 못찾음"), _T("error") );
							break;
						}
						fname_t szBuf;
						pE->GetDoc()->GetURL(szBuf);
						if(!jt_stricmp(szBuf, jS(jConsoleCmd))) // 메모리  doc이면
						{
							tname256_t szCmd;
							jt_sprintf(szCmd, _T("@%s.%s %s") , pE->GetParent()->GetTagName(), pE->GetTagName() , pE->GetAttr(jS(m_szArgHelp)) );
							CMainDlg::m_pSingleton->m_edit.SetWindowText(szCmd);
						}
						else //if(pE->GetType() == jIVar::EDcstr)
						{
							tname256_t szBuf;
							tname256_t buf;
							jt_sprintf(szBuf, _T("!%s.%s %s") 
								, pE->GetParent()->GetTagName()
								, pE->GetTagName()
								, pE->GetVar()->ToString(buf)
								);

							CMainDlg::m_pSingleton->m_edit.SetWindowText(szBuf);
						}
// 						else
// 						{
// 							pE->DebugPrint(true);
// 						}
					}
				}
				break;
			case VK_OEM_2:
				{
					CMenu menuMain;
					menuMain.CreatePopupMenu();

					g_cmdHelp_it it = g_cmdHelp.begin(), ie = g_cmdHelp.end();
					const int iSTART_MENU_INDEX = 1234;
					int i=0;
					CString listTemp[maxLIST+1];
					for( ; it != ie ; ++it)
					{
						menuMain.AppendMenu (MF_STRING|MF_ENABLED, iSTART_MENU_INDEX + i, *it);
						listTemp[i] = (*it);
						++i;
					}

					RECT p;
					CMainDlg::m_pSingleton->m_edit.GetWindowRect(&p);
					int iCmd = menuMain.TrackPopupMenu (TPM_LEFTALIGN | TPM_LEFTBUTTON 
						| TPM_RIGHTBUTTON | TPM_RETURNCMD
						, p.left, p.top, CMainDlg::m_pSingleton->m_edit.m_hWnd);

					if(iCmd >= iSTART_MENU_INDEX && iCmd < (iSTART_MENU_INDEX+i))
					{
						CString sz = listTemp[iCmd-iSTART_MENU_INDEX];
						CMainDlg::m_pSingleton->m_edit.SetWindowText(sz);
					}
				}
			}
		}
		break;
	}

	return ::CallWindowProc(g_hEditProc, hwnd, msg, wParam, lParam); // Correct!!!
}

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
#if 0
	if(pMsg->message==WM_KEYDOWN)
	{
		HWND hWndCtl = ::GetFocus();
		if(hWndCtl==m_edit.m_hWnd)
		{
			switch(pMsg->wParam)
			{
			case VK_TAB:
				{
				}
			}

		}
	}
#endif
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{

	return FALSE;
}

void LogToConsole(tcstr szMsg, bool)
{
	CMainDlg::m_pSingleton->Log(szMsg);
}


LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	load_cmd_file();

	m_pSingleton	= this;
	m_status		= STATUS_NOT_READY;
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
								IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, FALSE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
								IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, TRUE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);

	m_lv_log		= GetDlgItem(IDC_LIST1);
	m_edit = GetDlgItem(IDC_EDIT1);

	if (::GetWindowLongPtr(m_edit.m_hWnd, GWLP_WNDPROC) !=  (LONG_PTR)(g_hEditProc))
	{
		g_hEditProc = (WNDPROC)(::SetWindowLongPtr(m_edit.m_hWnd, GWLP_WNDPROC, (LONG_PTR)NewProc));
	}

	//SetTimer( TIMER_CONNECT, 5000, NULL );


	//GetjILog()->SetPrinter(LogToConsole);

	SetWindowText(pvNetConfigNode->Get_cstr());

	load_default_cmd_cache_file(pvCMD_CACHE_FILE->Get_cstr());
	
	return TRUE;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnOK(WORD asdf /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	if( IDYES == MessageBox( _T("OnOK :Close server... OK?"), _T("close"), MB_YESNO | MB_ICONQUESTION ) )
		CloseDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD asdf/*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if( IDYES == MessageBox( _T("OnCancel: Close server... OK?"), _T("close"), MB_YESNO | MB_ICONQUESTION ) )
		CloseDialog(wID);
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	save_cmd_file();

	SaveWinPos();

	DestroyWindow();
	::PostQuitMessage(nVal);
	m_pSingleton =0;
}

LRESULT CMainDlg::OnBnClickedStart(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
#if 0
	switch( m_status )
	{
	case STATUS_NOT_READY : 
		{
			//if( 0 == CreateServer( OnWtlLog ) )
			{
				m_status = STATUS_CREATED;
				SetDlgItemText( IDC_BTN_START, _T("&Run") );

				TCHAR strServerInfo[256] = { 0, };
				//GetServerInfo(strServerInfo);
				SetDlgItemText( IDC_SERVERINFO, (LPCTSTR)strServerInfo );

				SetTimer( TIMER_CONNECT, 5000, NULL );
			}
			else
			{
				MessageBox( _T("create server failed. check \"DungeoNSERVER_CONFIG.txt\" !!!"), _T("start error"), MB_OK | MB_ICONWARNING );
			}
		} 
		break;
	case STATUS_CREATED   :
		{
			//StartAccept();
			SetDlgItemText( IDC_BTN_START, _T("&Stop") );
			m_status = STATUS_RUNNING;
		} break;
	case STATUS_RUNNING   :
		{
			//StopAccept();
			SetDlgItemText( IDC_BTN_START, _T("&Run") );
			m_status = STATUS_CREATED;
		} break;
	}
	
	// MessageBox( _T("Already created !!!"), _T(""), MB_OK | MB_ICONWARNING );
#endif	
	return 0;
}

LRESULT CMainDlg::OnTimer(UINT /*uMsg*/, WPARAM wTimerID , LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
#if 1
	static bool blinker;
	blinker = ! blinker;

	switch( wTimerID )
	{
	case TIMER_CONNECT :
		{
			jLOG(_T("test"));
			return 0;
#if 0
			char mw[ 100 ];
			char relay[ 100 ];
			char stun[ 100 ];
			if( GetChildServerStatus( mw, relay, stun ) )
			{
				WCHAR  wIp[100];
				MultiByteToWideChar( CP_ACP, 0, mw, strlen( mw )+1, wIp, 100 );
				SetDlgItemText( IDC_STATIC_MESSAGE, wIp );

				MultiByteToWideChar( CP_ACP, 0, relay, strlen( relay )+1, wIp, 100 );
				SetDlgItemText( IDC_ST_RELAY, wIp );

				MultiByteToWideChar( CP_ACP, 0, stun, strlen( stun )+1, wIp, 100 );
				SetDlgItemText( IDC_ST_STUN, wIp );
			}
			else
			{
				SetDlgItemText( IDC_STATIC_MESSAGE, _T("not connected") );
			}
#endif
		} break;
	default :
		break;
	}
#endif

	return 0;
}


void CMainDlg::Log(CString str)
{
	TCHAR wTime[ 1024 ];

	SYSTEMTIME st;
	GetLocalTime(&st);
	if(m_lv_log.GetCount()>100)
	{
		m_lv_log.ResetContent();
	}

	jt_sprintf( wTime, _T("[%02d/%02d %02d:%02d] %s"), st.wMonth, st.wDay, st.wHour, st.wMinute, str );

	m_lv_log.SetCurSel( m_lv_log.InsertString(-1, wTime) );


}
void CMainDlg::LogCmd(CString str)
{
	if(m_lv_log.FindString(0,str)>=0) return;
	if(m_lv_log.GetCount()>100)
	{
		m_lv_log.ResetContent();
	}
	m_lv_log.SetCurSel( m_lv_log.InsertString(-1, str) );
}

LRESULT CMainDlg::OnActvateApp(UINT /*uMsg*/a, WPARAM /*wParam*/b, LPARAM /*lParam*/c, BOOL& /*bHandled*/d)
{
#if 0
	static int i=0;
	i++;
	jLOG(_T(" i = %d a= %d, b=%d, c=%d, d=%d"),i,a,b,c,d);
#endif
	if(b)
	{
		SetForegroundWindow(m_ConsoleHWND);
		SetForegroundWindow(m_hWnd);
	}
	return 0;
}



void CMainDlg::load_default_cmd_cache_file(tcstr szFile)
{
	pvCMD_CACHE_FILE->Set_cstr(szFile);
	std::tstring sBuf;
	nFileSystem::read_file(pvCMD_CACHE_FILE->Get_cstr(), sBuf);
	if(!sBuf.size()) return;
	vector<std::tstring> out;
	nString::jSplit(sBuf, _T("\n\r") , out);
	if(!out.size()) return ;
	m_lv_log.ResetContent();
	for(size_t i = 0; i< out.size(); ++i)
	{
		LogCmd(out[i].c_str());
	}
	CString str = _T("load default cmd file : ");
	str+=szFile;
	SetDlgItemText( IDC_STATIC_MESSAGE, str);

}

LRESULT CMainDlg::On_ID_COMMAND_LOADCMDFILE(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

	CFileDialog fileDlg ( true, _T("txt"), pvCMD_CACHE_FILE->Get_cstr(),
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		_T("cmd txt file\0*.txt\0All Files\0*.*\0") );

	if ( IDOK != fileDlg.DoModal() )
		return 0;

	load_default_cmd_cache_file(fileDlg.m_szFileName);
	return 0;
}

LRESULT CMainDlg::OnBnClickedRefreshMiddleware(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

	return 0;
}

LRESULT CMainDlg::OnEnChangeEdit1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO:  RICHEDIT 컨트롤인 경우 이 컨트롤은
	// __super::마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여
	// CRichEditCtrl().SetEventMask()를 호출하도록 OnInitDialog() 함수를 재지정하지 않으면
	// 이 알림을 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	return 0;
}

jIVar* pv_WINPOS		= jCV(exe,pv_WINPOS,_T("10;10;450;450"),0,"DLG POS");
jIVar* pv_CONSOLEPOS	= jCV(exe,pv_CONSOLEPOS,_T("10;10;450;450"),0,"CON POS");

inline RECT  get_rect(jIVar* pV)
{
	std::tstring s= pV->Get_cstr();
	vector<std::tstring> out;
	nString::jSplit(s, _T(";"), out);
	RECT r;
	r.left= jt_atoi(out[0].c_str());
	r.top= jt_atoi(out[1].c_str());
	r.right= jt_atoi(out[2].c_str());
	r.bottom= jt_atoi(out[3].c_str());
	return r;
}
inline void set_rect(jIVar* pV, RECT r)
{
	fname_t buf;
	jt_sprintf(buf, _T("%d;%d;%d;%d"),r.left,r.top,r.right,r.bottom);
	pV->Set_cstr(buf);
}

//--------------------------------------------------------------------------
void CMainDlg::LoadWinPos()
//--------------------------------------------------------------------------
{
	RECT rect;
	RECT orgR;
	GetWindowRect(&orgR);

	std::tstring strConTitle = std::tstring(pvNetConfigNode->Get_cstr()) + _T("_CON");
	SetConsoleTitle( strConTitle.c_str() );
	Sleep(1000);
	m_ConsoleHWND=FindWindow( NULL, strConTitle.c_str() );
#if 0
	nMech::nUtil::CRegistry reg;
	fname_t buf;
	jt_sprintf(buf, _T("SOFTWARE\\jGame\\%s\\Ver01_param"), g_ExeEnv.m_szAppNic);
	reg.Open(buf,HKEY_LOCAL_MACHINE);
	if(m_ConsoleHWND)
	{
		RECT r = { 10, 10, 450, 450};
		if(!reg[_T("console_win")].Exists()) reg[_T("console_win")] = r;
		r = reg[_T("console_win")];
		::SetWindowPos( m_ConsoleHWND, HWND_TOP, r.left,r.top,r.left,r.bottom, SWP_NOSIZE | SWP_SHOWWINDOW );
	}

	RECT r = { 10, 10, 450, 350};
	if(!reg[_T("dlg_win")].Exists()) reg[_T("dlg_win")] = r;
	r = reg[_T("dlg_win")];
	rect.right = (orgR.right-orgR.left );
	rect.bottom = (orgR.bottom- orgR.top);
	::SetWindowPos( m_hWnd, HWND_TOP, r.left,r.top,r.left,r.bottom, SWP_NOSIZE | SWP_SHOWWINDOW );
#else
	if(m_ConsoleHWND)
	{
		RECT r = get_rect(pv_CONSOLEPOS);
		::SetWindowPos( m_ConsoleHWND, HWND_TOP, r.left,r.top,r.left,r.bottom, SWP_NOSIZE | SWP_SHOWWINDOW );
	}
	RECT r = get_rect(pv_WINPOS);
	rect.right = (orgR.right-orgR.left );
	rect.bottom = (orgR.bottom- orgR.top);
	::SetWindowPos( m_hWnd, HWND_TOP, r.left,r.top,r.left,r.bottom, SWP_NOSIZE | SWP_SHOWWINDOW );

#endif


}

//--------------------------------------------------------------------------
void CMainDlg::SaveWinPos()
//--------------------------------------------------------------------------
{
	RECT rect;
#if 0
	nMech::nUtil::CRegistry reg;
	fname_t buf;
	jt_sprintf(buf, _T("SOFTWARE\\jGame\\%s\\Ver01_param"), g_ExeEnv.m_szAppNic);

	reg.Open(buf,HKEY_LOCAL_MACHINE);
	if(m_ConsoleHWND)
	{
		::GetWindowRect( m_ConsoleHWND, &rect);
		reg[_T("console_win")] = rect;
	}

	::GetWindowRect( m_hWnd, &rect);
	reg[_T("dlg_win")] = rect;
	reg.Close();
#else
	if(m_ConsoleHWND)
	{
		::GetWindowRect( m_ConsoleHWND, &rect);
		set_rect(pv_CONSOLEPOS , rect);
	}

	::GetWindowRect( m_hWnd, &rect);
	set_rect(pv_WINPOS, rect);

#endif

}


//--------------------------------------------------------------------------
void jconsole_LoadWinPos()
//--------------------------------------------------------------------------
{
	std::tstring strConTitle = std::tstring(pvNetConfigNode->Get_cstr()) + _T("_CON");
	SetConsoleTitle( strConTitle.c_str() );
	Sleep(1000);
	m_ConsoleHWND=FindWindow( NULL, strConTitle.c_str() );
#if 0
	nMech::nUtil::CRegistry reg;
	fname_t buf;
	jt_sprintf(buf, _T("SOFTWARE\\jGame\\%s\\Ver01_param"), g_ExeEnv.m_szAppNic);
	reg.Open(buf,HKEY_LOCAL_MACHINE);
	if(m_ConsoleHWND)
	{
		RECT r = { 10, 10, 450, 450};
		if(!reg[_T("console_win")].Exists()) reg[_T("console_win")] = r;
		r = reg[_T("console_win")];
		::SetWindowPos( m_ConsoleHWND, HWND_TOP, r.left,r.top,r.left,r.bottom, SWP_NOSIZE | SWP_SHOWWINDOW );
	}
#else
	if(m_ConsoleHWND)
	{
		RECT r = get_rect(pv_CONSOLEPOS);
		::SetWindowPos( m_ConsoleHWND, HWND_TOP, r.left,r.top,r.left,r.bottom, SWP_NOSIZE | SWP_SHOWWINDOW );
	}
#endif

}

//--------------------------------------------------------------------------
void jconsole_SaveWinPos()
//--------------------------------------------------------------------------
{
	RECT rect;
#if 0
	nMech::nUtil::CRegistry reg;
	fname_t buf;
	jt_sprintf(buf, _T("SOFTWARE\\jGame\\%s\\Ver01_param"), g_ExeEnv.m_szAppNic);

	reg.Open(buf,HKEY_LOCAL_MACHINE);
	if(m_ConsoleHWND)
	{
		::GetWindowRect( m_ConsoleHWND, &rect);
		reg[_T("console_win")] = rect;
	}
	reg.Close();
#else
	if(m_ConsoleHWND)
	{
		::GetWindowRect( m_ConsoleHWND, &rect);
		set_rect(pv_CONSOLEPOS , rect);
	}
#endif

}

LRESULT CMainDlg::OnListDblClick(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

	// 현재 선택되고 있는 아이템을 취득해 표시
	int nIndex = m_lv_log.GetCurSel();
	if(nIndex != LB_ERR)
	{
		CString strText;
		fname_t buf;
		m_lv_log.GetText(nIndex, buf);
		strText = buf;
		if(nCONSOLE::Get_jIConsoleCmd()->ParseCmd(buf))
		{
			//ParseCmd가 성공하면 명령기록에 남긴다.
			g_listCmd_it it = find(g_listCmd.begin(),g_listCmd.end(),strText);
			if(it==g_listCmd.end())
			{
				g_listCmd.push_back(strText);
				if(g_listCmd.size()>maxLIST)
					g_listCmd.erase(g_listCmd.begin());
			}
		}
	}
	return 0;
}

