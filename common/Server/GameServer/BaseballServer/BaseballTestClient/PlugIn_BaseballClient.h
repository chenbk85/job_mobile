/* file : PlugIn_BaseballClient.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:11
comp.: wiki.test.com
title : 
desc : 

*/

#ifndef __PlugIn_BaseballClient_header__
#define __PlugIn_BaseballClient_header__
#pragma once

#include "common_ug.h"
#include "jUser.h"


#define SERVERDATA_RECIEVED 9999

extern jIE* g_peCurrSession;

//class PlugIn_BaseballClient : public jIPlugIn_Net_SQ<PlugIn_BaseballClient,jIPlugin_jIClientSession_Asio> 
class PlugIn_BaseballClient : public jIPlugin_jIClientSession_Asio
{
public:
	jDECLARE_RTTIOBJ(PlugIn_BaseballClient);
	INTERFACE_jIPlugin_jIClientSession_Asio(;);

	nEVENT::jIMsgManager* m_pMM;

	void send_to_ug(jIE* peSession, UReqProtocol& sendMsg);
	void send_to_ug(jIE* peSession, Client_UserGateServer& msg);// PT_UserGateServer.proto에 정의된 메세지만 보내자.
	void send_to_bs(jIE* peSession, Client_BaseballServer& sendMsg);
	jIE* CreateClient(cstr ip, cstr id);
	void jUser_for_each(boost::function<void(jUser&)> &func);

	tcstr MakeSessionName(cstr id,OUT fname_t buf)
	{
		jt_sprintf(buf, _T("TCP_BaseballServer_%s") , id);
		return buf;
	}
	jIE* FindUser(cstr id)
	{
		fname_t buf;
		return m_pE->Find(MakeSessionName(id,buf));
	}

};
jLIST_TYPEDEF_map_header(jIE*,jUser,g_Users);
DECLARE_INSTANCE_TYPE(PlugIn_BaseballClient);

extern PlugIn_BaseballClient* g_pPlugIn;

//#define jASIO_SEND(SOCK,PACKET,...) if(SOCK){SOCK->Send(&WRITE_##PACKET(buf,__VA_ARGS__ ) ); _jNET_SEND_DEBUG(PACKET);}
#define RECV_PARAM_PlugIn_BaseballClient PlugIn_BaseballClient* pPlugIn,jIE* peSession,jUser* pUser


// client -> game server로 패킷 전송
#define jMAKE_MESSAGE_X2BS(pUser,sendMsg, sd ,NAME)\
	Client_BaseballServer sendMsg;\
	sendMsg.set_type(::Client_BaseballServer_Type_##NAME);\
	s_##NAME* sd = sendMsg.mutable_m_##NAME();\
	jLOG_USER( _T("%s>send X2BS:") jS(NAME) ,jFUNC);\


// client -> user gate로 패킷전송.
#define jMAKE_MESSAGE_X2UG(pUser,sendMsg, sd ,NAME)\
	Client_UserGateServer sendMsg;\
	sendMsg.set_type(::Client_UserGateServer_Type_##NAME);\
	s_##NAME* sd = sendMsg.mutable_m_##NAME();\
	jLOG_USER(_T("%s>send X2UG:") jS(NAME),jFUNC);\


#define jRECV_UAnsProtoca(MSG,...) bool OnRecv_##MSG(RECV_PARAM_PlugIn_BaseballClient,const MSG &rd)



#endif // __PlugIn_BaseballClient_header__
