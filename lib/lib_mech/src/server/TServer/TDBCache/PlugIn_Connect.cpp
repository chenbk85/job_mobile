/* file : PlugIn_Connect.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:13
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TDBCache.h"

jPLUGIN_CPP_CODE_START_Connect(PlugIn_Connect)
{

}
jPLUGIN_CPP_CODE_STOP(PlugIn_Connect);
{

}
jPLUGIN_CPP_CODE_END_Connect(PlugIn_Connect);



//DECLARE_INSTANCE_TYPE(S_TA_SET_TEST_ENV);
jSQ_REGIST_BIND(PlugIn_Connect)
//jSQ_REGIST_BIND_jINetPlugIn_CLIENT(PlugIn_Connect)
{
	jSQ_Interface(PlugIn_Connect)
		jSQ_end();

	//jSQ_g_var(&g_TestInfo,g_TestInfo);
}

PlugIn_Connect::PlugIn_Connect()
{
}

bool PlugIn_Connect::ParseCmd(tcstr szCommand)
{
	if(tstring(jS(DQ)) ==g_SG.GetParserType())
	{
		nswb1024_t buf;
		g_DQ.WritePacket(nDBQueryServer::WRITE_DQ_ECHO(buf,0,szCommand));
		return false;
	}

	jPS_COMMON_ParseCmd(DC);
	return false;
}

VOID PlugIn_Connect::OnIoConnected(jIPacketSocket_IOCP* pS)
{
	jInit_PlugIn_Connect_OnIoConnected();
}


VOID PlugIn_Connect::OnIoDisconnected(jIPacketSocket_IOCP* pS)
{
	jInit_PlugIn_Connect_OnIoDisconnected();
}
