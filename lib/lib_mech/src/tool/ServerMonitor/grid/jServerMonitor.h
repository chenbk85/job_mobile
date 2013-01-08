/* file : jServerMonitor.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-04-14 13:40:41
comp.: rocworks.co.kr
title : 
desc : 

*/

#ifndef __jServerMonitor_header__
#define __jServerMonitor_header__
#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../tool_Grid/grid/jGridCtrl.h"
#include "./net/net_common/jDLL_Bridge.h"
#include "mech/util/sm/jRoC_SharedMemory_header.h"

class jServerMonitor : public jGridCtrl , public jIServerMonitor
{
public:
	jINTERFACE_HEADER(jIServerMonitor);

	jServerMonitor::jServerMonitor(jIE* pE);
	virtual jServerMonitor::~jServerMonitor();

	virtual void OnSetup();

	afx_msg virtual LRESULT On_jWM_USER_UPDATE_CELL(WPARAM w, LPARAM l);
	DECLARE_MESSAGE_MAP()

public:
	jIE* m_peServerList_FromApp;
	bool m_isRocked_Monitor;

	void Reload_xml(jIE* pE);

	void server_state_cell_change(tcstr szServerState,jIE* it);
	void updateCellMessage(jIE* peCell)				{		PostMessage(jWM_USER_UPDATE_CELL, (WPARAM)peCell, 0);	}
	jIE* find_peSERVER_ZONE_by_socket(jIPacketSocket_IOCP*pS);
	void SetProcessInfo(jIE* peSERVER_ZONE ,tcstr szServerType,  wcstr szInfo,wcstr szValue);

	template <class _Predicate>
	jIE* find_if_SERVER_ZONE(_Predicate &__pred )  
	{
		jIE * pE = m_peGrid->FindByFirstAttr(jS(HELP), jIVar::EDcstr, jS(AGENT_LIST));
		jRETURN_ret(0,pE);
		return pE->find_if_child(__pred);
	}

	template <class _Predicate>
	void for_each_SERVER_ZONE(_Predicate &__pred )  
	{
		jIE * pE = m_peGrid->FindByFirstAttr(jS(HELP), jIVar::EDcstr, jS(AGENT_LIST));
		jRETURN(pE);
		pE->for_each_child(__pred);
	}
	template <class _Predicate>
	void for_each_SERVER_MENU(_Predicate &__pred ,jIE* peSERVER_ZONE=0)  // SERVER_MENU아래의 peServer(Login, Zone , PbRms)에 대해..
	{
		bool isOnce=true;
		if(!peSERVER_ZONE)
		{
			isOnce=false;
			jIE * peAGENT_LIST = m_peGrid->FindByFirstAttr(jS(HELP), jIVar::EDcstr, jS(AGENT_LIST));
			jRETURN(peAGENT_LIST);
			peSERVER_ZONE = peAGENT_LIST->begin();
		}
		jIVar* pV;
		jrFOR(peSERVER_ZONE)
		{
			pV = peSERVER_ZONE->GetAttrVar(jS(HELP));
			if(!pV || !pV->IsContents(jS(SERVER_ZONE))) continue;
			jIPacketSocket_IOCP* pS = (jIPacketSocket_IOCP*)peSERVER_ZONE->GetUserData(jS(jIPacketSocket_IOCP));
			jIE* peSERVER_MENU= peSERVER_ZONE->FindByFirstAttr(jS(HELP),jIVar::EDcstr, jS(SERVER_MENU));
			if(!peSERVER_MENU) continue;
			jIE* peServer = peSERVER_MENU->begin();
			jrFOR(peServer)
			{
				pV = peServer->GetAttrVar(jS(HELP2));
				if(!pV || !pV->IsContents(jS(SERVER_MENU_NODE))) continue;
				__pred(peServer,pS);
			}
			if(isOnce) break;
		}
	}
};

extern jServerMonitor * g_pjServerMonitor ;
#define Get_jServerMonitor() if(g_pjServerMonitor)g_pjServerMonitor

jIE* find_server_info_label(jIE* peSERVER_INFO_CELL , cstr szLabel);
jIE* find_SERVER_MENU_NODE(jIE* peSERVER_ZONE, tcstr szServerType); // HELP=" Login, Zone , PbRms"를 리턴.
jIE* parent_SERVER_ZONE(jIE* pE, jIPacketSocket_IOCP** ppS=0); //it의 부모에서 SERVER_ZONE노드를 찾는다.
jIE* parent_SERVER_MENU(jIE* it);// it의 부모에서 SERVER_MENU노드를찾는다.
jIE* parent_SERVER_MENU_NODE(jIE* it,OUT tstring &serverName);//it의 부모에서 SERVER_MENU 하위 서버노드(Login, Zone, PbRms ) 를 리턴 

namespace nSM
{
	// SERVER_MENU 하위 서버노드에서 해당 이름(HELP속성)으로된 컨트롤을 찾는다.
	inline jIE* find_Control(jIE* peSERVER_MENU,cstr szHELP,cstr szATTR=jS(HELP))
	{
		jRETURN_ret(0,peSERVER_MENU);
		jRETURN_ret(0,szHELP);
		return peSERVER_MENU->FindByFirstAttr(szATTR,jIVar::EDcstr , const_cast<TCHAR*>(szHELP) );	
	}

	cstr GetServerType(cstr szServerTypeHelp);
	cstr GetServerTypeHelp(cstr szServerType);
}

#define var_enum(func)\
	func(ServerMonitor,GridView_RTTI_NAME,_T("grid_ServerMonitor"),0,"grid_default.xml rtti name")\

var_enum(jCV_DECLARE);


#endif // __jServerMonitor_header__
