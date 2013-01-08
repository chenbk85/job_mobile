/* file : PlugIn_Server.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TCommand.h"
#include "PlugIn_Server.h"

jPLUGIN_CPP_CODE_START_Server(PlugIn_Server)
{

}
jPLUGIN_CPP_CODE_STOP(PlugIn_Server)
{

}
jPLUGIN_CPP_CODE_END_Server(PlugIn_Server);


PlugIn_Server::PlugIn_Server()
{

}

bool PlugIn_Server::ParseCmd(tcstr szCommand)
{
	jPS_COMMON_ParseCmd(CD);
}


// CIocp의 가상함수들
VOID PlugIn_Server::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	jSI(pS->GetGridNode());
	if(si->m_eType == eCentral)
	{
		if(g_SG.m_Central.size()<2)
		{
			jLOG("CentralServer Restart!!!");
			// Central에서 연결한 것이다.
			nswb256_t buf;
			fname_t szIP;
			jLOG1(jFUNC1 _T(" %s"), pS->GetAddressString(szIP), nNET::GridName(pS->GetGridNode()) );
			g_SG.WritePacket(WRITE_CD2_CENTRAL_RESTART(buf),pS);

			jPC();
			jIE* pE = pPC->m_pE->Find(jS(Central));
			jAssert0(pE);
			pE->GetAttrVar(jS(ENABLE))->Set_bool(true);
			pPC->m_pClientSession->Start_ClientSocket(pE);
		}

		DoDisconnect(pS);
		return;
	}
	else
	{

	}
	jFE_OnIoConnected_fromServer(CD_HELLO);// jIGridNode* pGN, szIP,nswb256_t buf
}


VOID PlugIn_Server::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromServer(); //jIGridNode* pGN ,jServerInfo* si 
	if(!g_SG.m_Central.size())
	{
		nswb256_t buf;
		g_SG.WritePacket(WRITE_CD_SERVER_OFFLINE(buf,si->m_sid));
	}
}


