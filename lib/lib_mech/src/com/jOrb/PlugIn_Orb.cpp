/* file : PlugIn_Orb.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:13
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_Orb.h"

PlugIn_Orb* g_pCurrPlugIn=0;

jSQ_REGIST_BIND(PLUGIN)
{
	jSQ_Interface(PlugIn_Orb)
		jSQ_end();

	//jSQ_g_var(&g_TestInfo,g_TestInfo);
}


PlugIn_Orb::PlugIn_Orb()
{

}

jPLUGIN_cpp_code_Start(PlugIn_Orb)
{
	g_pCurrPlugIn= this;
	g_jOrb.m_jOrbNode.clear();
	m_pMM = nEVENT::jIMsgManager::Get(jS(PlugIn_Orb), true);
}

jPLUGIN_cpp_code_Stop(PlugIn_Orb);
{
	if(g_pCurrPlugIn==this)
		g_pCurrPlugIn=0;
}
jPLUGIN_cpp_code_End(PlugIn_Orb);


bool PlugIn_Orb::ParseCmd(tcstr szCommand)
{
	nswb1024_t buf;
	jOrb::m_jOrbNode_it it = g_jOrb.m_jOrbNode.begin(), ie = g_jOrb.m_jOrbNode.end();
	for( ; it!=ie ; ++it)
	{
		it->WritePacket(&nOrbHost::WRITE_H_ECHO(buf, 0,szCommand));
	}
	return false;
}

VOID PlugIn_Orb::OnIoConnected(jIPacketSocket_IOCP* pS)
{
	jLOG(jFUNC1);
}

VOID PlugIn_Orb::OnIoDisconnected(jIPacketSocket_IOCP* pS)
{
	jLOG(jFUNC1);
}

