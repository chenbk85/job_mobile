/* file : PlugIn_Server.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TDBCache.h"

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

	if(tstring(jS(DQ)) ==g_SG.GetParserType())
	{
		nswb1024_t buf;
		g_DQ.WritePacket(nDBQueryServer::WRITE_DQ_ECHO(buf,0,szCommand));
		return false;
	}

	jPS_COMMON_ParseCmd(DC);
}


// CIocp의 가상함수들
VOID PlugIn_Server::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoConnected_fromServer(DC_HELLO);// jIGridNode* pGN, szIP,nswb256_t buf
}

VOID PlugIn_Server::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromServer(); //jIGridNode* pServer
}
