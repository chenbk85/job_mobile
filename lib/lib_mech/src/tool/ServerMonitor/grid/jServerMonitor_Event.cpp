/* file : jServerMonitor_Event.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-04-29 00:46:56
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "grid/jServerMonitor.h"
#include "../../tool_Grid/grid/jGridCtrl.h"
#include "./net/protocal/PT_MonitorServer_Enum.h"
using namespace nMech::nNET::nMonitorServer;

#define jCHEKC_m_isRocked_Monitor() if(g_pjServerMonitor && g_pjServerMonitor->m_isRocked_Monitor)\
{\
	MessageBox(AfxGetApp()->GetMainWnd()->m_hWnd , _T("Monitor is Lock Mode"),_T("ERROR"),MB_OK);\
	return TRUE;\
}\


#ifdef _DEBUG
#define jMB_CHECK(X)
#else
#define jMB_CHECK(X)\
	int ret = MessageBox(AfxGetApp()->GetMainWnd()->m_hWnd, _T("OK ") jS(X) _T(" ?"), _T("Warning") , MB_YESNO);\
	if(ret!=IDYES) return TRUE;\

#endif


wcstr make_server_menu_string(OUT wfname_t szBuf, cstr sServerType, tcstr szServerState)
{
	//@net_agent.SendMenuCmd <eLOGIN | eZONE | all> <StartUp | Accept | SOS | DisAccept | DisUser | ShutDown >
	cstr szServerEnum = nSM::GetServerType(sServerType);
	jw_sprintf(szBuf, L"@net_agent.SendMenuCmd %s %s" , jW(szServerEnum),jW(szServerState));
	return szBuf;
}


//jGridCtrl* pGrid,jIE* pE,long ID,int col,long row,long msg,LONG_PTR param
jGRIDCRTL_EVENT(grid_ServerMonitor,Start_Local_Agent)
{
	nFileSystem::jFolder dir;
	dir.Goto(g_ExeEnv.m_szModuleDir);
	jRETURN_ret(TRUE, nFileSystem::jFolder::Is_Exist(_T("_net_Agent.bat")) );
	WinExec("_net_Agent.bat",SW_NORMAL);
	return TRUE;
}




//jGridCtrl* pGrid,jIE* pE,long ID,int col,long row,long msg,LONG_PTR param
jGRIDCRTL_EVENT(jServerMonitor,DYNAMIC_DROP) //DropList
{
	jCHEKC_m_isRocked_Monitor()

	if(pE->IsName(jS(DropList)))
	{
		switch(msg)
		{
		case UGCT_DROPLISTSTART:
			{
				break;
			}
		case UGCT_DROPLISTSELECTEX:
			{
				jIE* it = pE->FindByOrder(param);
				jLOG(jFUNC1 _T("%s , msg=%d, select=%s") , pE->GetParent()->GetAttr(jS(Name)) , msg, it->Get_cstr());
				break;
			}
		}
	}
	else if(pE->IsName(jS(Menu)))
	{
		jLOG(jFUNC1 _T("%s , msg=%d, item=%s") , pE->GetParent()->GetAttr(jS(Name)) , msg, pE->FindByOrder(param)->Get_cstr());
	}
	return TRUE;
}

// jIE* peSERVER_ZONE , jIPacketSocket_IOCP* pS , nswb1024_t buf ,jIE* peServer , tstring sServerType
#define jGRIDCRTL_EVENT_ARG_PARSE(pE,pS)\
	jCHEKC_m_isRocked_Monitor()\
	jLOG(jFUNC);\
	nswb1024_t buf;\
	jIPacketSocket_IOCP* pS;\
	jIE* peSERVER_ZONE = parent_SERVER_ZONE(pE,&pS);\
	jRETURN_ret(TRUE,peSERVER_ZONE);\
	tstring sServerType;\
	jIE* peServer = parent_SERVER_MENU_NODE(pE,sServerType);\


//jGridCtrl* pGrid,jIE* pE,long ID,int col,long row,long msg,LONG_PTR param
jGRIDCRTL_EVENT(grid_ServerMonitor,Restart_Agent)
{	jLOG(jFUNC);
	jCHEKC_m_isRocked_Monitor();
	//if(ID==jUGCT_CONTEXT_MENU_EVENT)
	{
		jGRIDCRTL_EVENT_ARG_PARSE(pE,pS);
		jNET_SEND(pS,M2A_CALL_CMD_RQ,jS(eST_AGENT),(L"@net_agent.restart"));//EServerType_MAX는 Agent자체를 의미.

	}
	return TRUE;
}

//jGridCtrl* pGrid,jIE* pE,long ID,int col,long row,long msg,LONG_PTR param
jGRIDCRTL_EVENT(grid_ServerMonitor,Kill_All_Server)
{	jLOG(jFUNC);
jCHEKC_m_isRocked_Monitor();

	//if(ID==jUGCT_CONTEXT_MENU_EVENT)
	{
		jMB_CHECK(Kill_All_Server);
		jGRIDCRTL_EVENT_ARG_PARSE(pE,pS);
		jNET_SEND(pS,M2A_CALL_CMD_RQ,jS(eST_AGENT),(L"@net_agent.server_kill all"));//EServerType_MAX는 Agent자체를 의미.

	}
	return TRUE;
}

//jGridCtrl* pGrid,jIE* pE,long ID,int col,long row,long msg,LONG_PTR param
jGRIDCRTL_EVENT(grid_ServerMonitor,Start_All_Server)
{	jLOG(jFUNC);
	//if(ID==jUGCT_CONTEXT_MENU_EVENT)
	jGRIDCRTL_EVENT_ARG_PARSE(pE,pS);//peSERVER_ZONE , pS , nswb1024_t buf ,peServer , sServerType
	jNET_SEND(pS,M2A_CALL_CMD_RQ,jS(eST_AGENT),(L"@net_agent.server_start all"));//EServerType_MAX는 Agent자체를 의미.
	return TRUE;
}

//jGridCtrl* pGrid,jIE* pE,long ID,int col,long row,long msg,LONG_PTR param
jGRIDCRTL_EVENT(grid_ServerMonitor,Restart_Agent_all)
{
	jCHEKC_m_isRocked_Monitor();

	jMB_CHECK(Restart_Agent_all);
	//모든 에이젼트 리부팅
	jLAMDA_for_each0(Restart_Agent_all,jIE*)
	{
		nswb1024_t buf;
		jIPacketSocket_IOCP* pS;
		jIE* peSERVER_ZONE = parent_SERVER_ZONE(it,&pS);
		if(!peSERVER_ZONE) 
			return;
		jNET_SEND(pS,M2A_CALL_CMD_RQ,jS(eST_AGENT),(L"@net_agent.restart"));
	}
	jLAMDA_end();

	Get_jServerMonitor()->for_each_SERVER_ZONE(Restart_Agent_all());

	return TRUE;
}
//jGridCtrl* pGrid,jIE* pE,long ID,int col,long row,long msg,LONG_PTR param
jGRIDCRTL_EVENT(grid_ServerMonitor,Kill_All_Server_all)
{
	jCHEKC_m_isRocked_Monitor();

	//모든 서버들 죽임
	jMB_CHECK(Kill_All_Server_all);
	jLAMDA_for_each0(Kill_All_Server_all,jIE*)
	{
		nswb1024_t buf;
		jIPacketSocket_IOCP* pS;
		jIE* peSERVER_ZONE = parent_SERVER_ZONE(it,&pS);
		if(!peSERVER_ZONE) 
			return;
		jNET_SEND(pS,M2A_CALL_CMD_RQ,jS(eST_AGENT),(L"@net_agent.server_kill all"));
	}
	jLAMDA_end();

	Get_jServerMonitor()->for_each_SERVER_ZONE(Kill_All_Server_all());

	return TRUE;
}
//jGridCtrl* pGrid,jIE* pE,long ID,int col,long row,long msg,LONG_PTR param
jGRIDCRTL_EVENT(grid_ServerMonitor,Start_All_Server_all)
{
	jCHEKC_m_isRocked_Monitor();

	//모든 서버들 시작
	jMB_CHECK(Start_All_Server_all);
	jLAMDA_for_each0(Start_All_Server_all,jIE*)
	{
		nswb1024_t buf;
		jIPacketSocket_IOCP* pS;
		jIE* peSERVER_ZONE = parent_SERVER_ZONE(it,&pS);
		if(!peSERVER_ZONE) 
			return;
		jNET_SEND(pS,M2A_CALL_CMD_RQ,jS(eST_AGENT),(L"@net_agent.server_start all"));
	}
	jLAMDA_end();

	Get_jServerMonitor()->for_each_SERVER_ZONE(Start_All_Server_all());

	return TRUE;
}

wcstr get_kill_start_string(jIE* pE)
{
	bool isKill = jt_strstr(pE->GetAttr(jS(Value)) , jS(kill));
	return isKill ? L"kill" : L"start" ;
}

//jGridCtrl* pGrid,jIE* pE,long ID,int col,long row,long msg,LONG_PTR param
jGRIDCRTL_EVENT(grid_ServerMonitor,BTN_SERVER_START_OR_KILL)
{
	jCHEKC_m_isRocked_Monitor();

	jGRIDCRTL_EVENT_ARG_PARSE(pE,pS);//peSERVER_ZONE , pS , nswb1024_t buf ,peServer , sServerType

	cstr szServerType = pE->GetAttr(jS(NAME));
	jRETURN_ret(TRUE,szServerType);
	wfname_t szBuf;
	jw_sprintf(szBuf,L"@net_agent.server_%s %s", get_kill_start_string(pE) ,jW(szServerType));
	jNET_SEND(pS,M2A_CALL_CMD_RQ,jS(eST_AGENT),szBuf);//EServerType_MAX는 Agent자체를 의미.

	return TRUE;
}


//===============================================================
// 서버 메뉴 명령.
//===============================================================

struct send_server_menu_string
{
	tcstr eState;
	send_server_menu_string(tcstr e):eState(e){}
	void operator()(jIE* pE /*peSERVER_MENU_NODE*/, jIPacketSocket_IOCP* pS)
	{
		nswb1024_t buf;
		tstring sServerType;
		jIE* peServer = parent_SERVER_MENU_NODE(pE,sServerType);
		if(sServerType.size()==0)
		{
			pE->DebugPrint(true);
		}
		wfname_t szBuf;
		jNET_SEND(pS,M2A_CALL_CMD_RQ,jS(eST_AGENT),make_server_menu_string(szBuf,sServerType.c_str(),eState));
	}
};

//jGridCtrl* pGrid,jIE* pE,long ID,int col,long row,long msg,LONG_PTR param
jGRIDCRTL_EVENT(grid_ServerMonitor,SERVER_MENU)
{	jCHEKC_m_isRocked_Monitor();

	jGRIDCRTL_EVENT_ARG_PARSE(pE,pS);
	wfname_t szBuf;
	jNET_SEND(pS,M2A_CALL_CMD_RQ,jS(eST_AGENT),make_server_menu_string(szBuf,sServerType.c_str(),pE->GetAttr(jS(NAME)) ) );
	return TRUE;
}


//jGridCtrl* pGrid,jIE* pE,long ID,int col,long row,long msg,LONG_PTR param
jGRIDCRTL_EVENT(grid_ServerMonitor,SERVER_MENU_ALL)
{	jCHEKC_m_isRocked_Monitor();

	tfname_t szServerState;
	jt_strcpy(szServerState, pE->GetAttr(jS(NAME) ) ) ;
	TCHAR* ch = jt_strstr(szServerState,jS(_All));
	if(ch) *ch = 0;
	Get_jServerMonitor()->for_each_SERVER_MENU(send_server_menu_string(szServerState));
	return TRUE;
}

//jGridCtrl* pGrid,jIE* pE,long ID,int col,long row,long msg,LONG_PTR param
jGRIDCRTL_EVENT(grid_ServerMonitor,ProcessInfoUpdate)
{	jCHEKC_m_isRocked_Monitor();

	// jIE* peSERVER_ZONE , jIPacketSocket_IOCP* pS , nswb1024_t buf ,jIE* peServer , tstring sServerType
	jGRIDCRTL_EVENT_ARG_PARSE(pE,pS);
	jRETURN_ret(TRUE,param==jGRIDCTRL_CELLTYPE_IS_EDITABLE);
	tstring serverHelpName;
	jRETURN_ret(TRUE,parent_SERVER_MENU_NODE(pE,serverHelpName));

	cstr szLabel= pE->GetAttr(jS(Label));
	jRETURN_ret(TRUE,szLabel);
	tname256_t szValue;
	jIVar* pV = pE->GetAttrVar(jS(Value));
	jRETURN_ret(TRUE, pV);
	pV->ToString(szValue);
	jNET_SEND(pS,M2A_PROCESS_INFO_UPDATE , nSM::GetServerType(serverHelpName.c_str()) , jW(szLabel), jW(szValue));

	return TRUE;
}

jGRIDCRTL_EVENT(grid_ServerMonitor,RESET_ERROR_LOG_COUNT_ALL)
{	jCHEKC_m_isRocked_Monitor();

	struct send_M2A_RESET_ERROR_LOG_COUNT
	{
		void operator()(jIE* pE /*peSERVER_MENU_NODE*/, jIPacketSocket_IOCP* pS)
		{
			nswb1024_t buf;
			jNET_SEND(pS, M2A_RESET_ERROR_LOG_COUNT);
		}
	};

	Get_jServerMonitor()->for_each_SERVER_MENU(send_M2A_RESET_ERROR_LOG_COUNT());

	return TRUE;
}

jGRIDCRTL_EVENT(grid_ServerMonitor,RESET_ERROR_LOG_COUNT)
{	jCHEKC_m_isRocked_Monitor();

	// jIE* peSERVER_ZONE , jIPacketSocket_IOCP* pS , nswb1024_t buf ,jIE* peServer , tstring sServerType
	jGRIDCRTL_EVENT_ARG_PARSE(pE,pS);
	jNET_SEND(pS, M2A_RESET_ERROR_LOG_COUNT);
	return TRUE;
}


/*
//jGridCtrl* pGrid,jIE* pE,long ID,int col,long row,long msg,LONG_PTR param
jGRIDCRTL_EVENT(grid_ServerMonitor,ProcessInfoUpdate)
{	jCHEKC_m_isRocked_Monitor();

	// jIE* peSERVER_ZONE , jIPacketSocket_IOCP* pS , nswb1024_t buf ,jIE* peServer , tstring sServerType
	jGRIDCRTL_EVENT_ARG_PARSE(pE,pS);

	return TRUE;
}

*/