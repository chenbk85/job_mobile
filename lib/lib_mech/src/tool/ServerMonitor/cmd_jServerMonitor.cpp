/* file : cmd_jServerMonitor.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-05-13 14:48:43
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "grid/jServerMonitor.h"



jCONSOLE_CMD_AUTO(grid,reload,0,"grid xml reload","")
{
	jIE* peSERVER_ZONE = g_pjServerMonitor->m_peGrid->FindByFirstAttr(jS(HELP) , jIVar::EDcstr, jS(SERVER_ZONE));
	jrFOR(peSERVER_ZONE)
	{
		jIPacketSocket_IOCP* pS = (jIPacketSocket_IOCP*)peSERVER_ZONE->GetUserData(jS(jIPacketSocket_IOCP));
		if(!pS) continue;
		nswb1024_t buf;
		jNET_SEND(pS,A2M_CALL_CMD_RS,jS(eST_AGENT),(L"@net_agent.restart"));//EServerType_MAX는 Agent자체를 의미.
	}

	GetjIXml()->UnLoad(g_pjServerMonitor->m_peGrid->GetDoc());
	jID* pDoc = GetjIXml()->Load(_T("xml\\gridview\\grid_ServerMonitor.xml"));
	cstr szGrid = pv_GridView_RTTI_NAME->Get_cstr();
	jIE* pE = pDoc->BaseI()->FindByFirstAttr(jS(RTTI_NAME), jIVar::EDcstr,(void*)szGrid);
	jRETURN_ret(false,pE);
	g_pjServerMonitor->Reload_xml(pE);


	return true;
}

