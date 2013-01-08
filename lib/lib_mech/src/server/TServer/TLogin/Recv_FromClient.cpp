/* file : Recv_FromClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:56:07
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TLogin.h"
#include "../TCommonServer/jServerGrid_functor.h"

jNET_EVENT_BEGIN(PlugIn_Server)
{

	//X2LG_USER_EKEY를 클라이언트로부터 받았을때.
	jNET_EVENT_RECEIVER(L_ECHO)
	{
		READ_PACKET_FromClient(L_ECHO);
		jNET_SEND2(g_SG.m_Client,L_ECHO,Data.msg,0);
	}
	
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2L_USER_LOGIN)
	{
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(X2L_USER_LOGIN);
		jw_strcpy_s(pGNC->m_szID,Data.id);
		jw_strcpy_s(pPlayer->m_szID , Data.id);
		jIGridNode* pGN = g_SG.find_if(eWorld,find_by_name(jT(Data.world)) );
		if(!pGN) 
		{ 
			jWARN("world server not found : %s", jT(Data.world)); 
			return;
		}
		jSI(pGN);
		pPlayer->Set_Server(eWorld,si->m_sid);
		jNET_SEND2(g_SG.m_User,L2U_USER_LOGIN, si->m_sid, Data.id);
	}
	
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2L_GET_WORLD_LIST)
	{
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(X2L_GET_WORLD_LIST);
		vector<jWorldServerInfo> out;
		jPC();

		#define jLAMDA_jxGet_world_list(X,Z) \
			Z(vector<jWorldServerInfo>&,out)
		jLAMDA_for_each(jxGet_world_list, jServerInfo*)
		{
			jWorldServerInfo w;
			ja_strcpy_s(w.szName,jA(it->m_szDomain));
			w.iBusy = it->Get_buzy_level();
			out.push_back( w );
		}
		jLAMDA_end();

		g_SG.ServerInfo_for_each(jxGet_world_list(out));
		jNET_SEND(pGNC,L2X_WORLD_LIST, out);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2L_GET_CHANNEL_LIST)
	{
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(X2L_GET_CHANNEL_LIST);
		jPC();

		jIGridNode* pGN = g_SG.m_World.find_if(find_by_name(jT(Data.world)));
		if(!pGN)
		{
			jSEND_ERROR_USER_DISCONNECT(L,SR_t(X2L_GET_CHANNEL_LIST),CR_t(WRONG_WORLD_NAME),pPlayer->m_pid);
			return;
		}

		#define jLAMDA_channel_list_from_ServerInfoList(X,Z) X(tcstr ,szDomain) Z(S_L2X_CHANNEL_LIST&,pk)
		jLAMDA_for_each(channel_list_from_ServerInfoList, jServerInfo*)
		{
			if(jt_strcmp(it->m_szDomain,szDomain)) return;
			pk.channel.push_back(it->m_sid);
			pk.channel_name.push_back(jA(it->m_szName));
			pk.buzy_level.push_back(it->Get_buzy_level());
		}
		jLAMDA_end();

		S_L2X_CHANNEL_LIST pk;
		g_SG.ServerInfo_for_each(channel_list_from_ServerInfoList(jT(Data.world),pk));
		jNET_SEND(pS,L2X_CHANNEL_LIST,pk);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2L_CHANNEL_SELECT)
	{
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(X2L_CHANNEL_SELECT);
		jIGridNode* pGN = g_SG.find(Data.sid);
		if(!pGN)
		{
			tname_t szIP;
			jWARN("Channel server is not found : %d , user=(%s,%s)", Data.sid , jT(pPlayer->m_szID), pS->GetIP(szIP));
			pP->DoDisconnect(pS);
			return;
		}
		jSI(pGN);
		jNET_SEND(pS,L2X_CHANNEL_SELECT_RESULT,jError(),jA(si->m_szServiceIP),si->m_service_port,pPlayer->m_pid);
	}
	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_Server)




