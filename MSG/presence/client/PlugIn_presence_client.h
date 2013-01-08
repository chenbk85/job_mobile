/* file : PlugIn_presence_client.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:11
comp.: wiki.test.com
title : 
desc : 

*/

#ifndef __PlugIn_presence_client_header__
#define __PlugIn_presence_client_header__
#pragma once

#include "common_ug.h"
#include "TestSession.h"


//class PlugIn_presence_client : public jIPlugIn_Net_SQ<PlugIn_presence_client,jIPlugin_jIClientSession_Asio> 
class PlugIn_presence_client : public jIPlugin_jIClientSession_Asio
{
public:
	jDECLARE_RTTIOBJ(PlugIn_presence_client);
	INTERFACE_jIPlugin_jIClientSession_Asio(;);

	nEVENT::jIMsgManager* m_pMM;

  void Send_PReqProtocol(jIE* peSession, PReqProtocol& sendMsg);
  void for_each_Session(boost::function<void(TestSession&)> &func);
	jIE* CreateSession(cstr ip, cstr id);
	tcstr MakeSessionName(cstr id,OUT fname_t buf)	
  {
    jt_sprintf(buf, _T("TCP_PresenceServer_%s") , id); return buf;
  }
	jIE* FindSession(cstr id)                       
  {
    fname_t buf; return m_pE->Find(MakeSessionName(id,buf)); 	
  }

};

jLIST_TYPEDEF_map_header(jIE*,TestSession,g_SessionList);
DECLARE_INSTANCE_TYPE(PlugIn_presence_client);


extern PlugIn_presence_client* g_pPlugIn;
extern jIE* g_peCurrSession;


#endif // __PlugIn_presence_client_header__
