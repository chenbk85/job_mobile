/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TLogin.h"


jNET_EVENT_BEGIN(PlugIn_Connect)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(U2L_USER_LOGIN_RESULT,UserServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(U2L_USER_LOGIN_RESULT);

		#define jLAMDA_find_player_by_name(X,Z) X(wcstr,szName) Z(S_U2L_USER_LOGIN_RESULT&,Data)
		jLAMDA_find_if(find_player_by_name,jIGridNode*)
		{
			jCI_ret(it,false);
			if(jw_strcmp(ci->m_szID,szName)) return false;
			ci->m_pPlayer = g_PL.create(Data.id, Data.pid);
			jAssert0(ci->m_pPlayer);
			return true;
		}
		jLAMDA_end();

		jGridNode_ClientBase* pClient = g_SG.m_Client.find_if(find_player_by_name(Data.id,Data));
		if(!pClient)
		{
			jERROR("user not found : %s", jT(Data.id));
			return;
		}
		if(Data.e.isError())
		{
			jAssert0(0);
			//  U_ERROR 메세지로 일괄처리할것임.
			//jNET_SEND(pClient,L_ERROR,Data.e, eEAT_DISCON_USER,__FUNCTION__,Data.pid);
			return;
		}

#ifdef TSERVER_PREPARE
		jIGridNode* pWorld = g_SG.m_World.find(pClient->world);
		if(!pWorld)
		{
			jGridNode_ClientBase *pS = pClient;
			jSEND_ERROR_TO_USER(L,SR_t(WorldServer_is_not_found),CR_t(U2L_USER_LOGIN_RESULT),Data.pid);
			return;
		}
		cstr szWorld = pE->GetAttr(jS(m_szWorld));
		pE = pPC->m_eServers->Find(szWorld);
		if(!pE)
		{
			jWARN1(_T("world server root node not found : name =(%s)"),sid,szWorld);
			pClient->Write_Packet(WRITE_L_ERROR(buf, jError(SR_t(WorldServer_rootNode_not_found),CR_t(U2L_USER_LOGIN_RESULT))
				,0,__FUNCTION__, player_id_t()) );
			return;
		}
		#define jLAMDA_jxGet_free_channelServer(X,Z) \
			X(int,totUser)\
			Z(serverid_t&,sid)
		jLAMDA_for_each(jxGet_free_channelServer, jIE*)
		{
			nXML::jE e = it;
			int currTot = e.Attr(jS(m_iTotClient))->Get_int();
			if(totUser > currTot)
			{
				totUser = currTot;
				sid = e.Attr(jS(m_sid))->Get_int();
			}
		}
		jLAMDA_end();

		int free_totUser=INT_MAX;
		serverid_t free_sid=0;
		pE->for_each_child(jxGet_free_channelServer(free_totUser,free_sid));

		if(sid==0)
		{
			jAssert0(0 && "에러처리 : jTODO : 가용 Channel서버가 없음.");
		}

		jIE *peFreeServer = pPC->Find_Server(free_sid);
		uint16 port = peFreeServer->GetAttrVar(jS(m_service_port))->Get_int();
		pClient->Write_Packet(WRITE_L2X_CHANNEL_SELECT_RESULT(buf
			, jError(),jA(peFreeServer->GetAttr(jS(m_szServiceIP))),port,pClient->Get_uid()));
#endif
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(U2L_DO_USER_DISCONNECT,UserServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(U2L_DO_USER_DISCONNECT);
		for(int i=0; i< Data.uids.size() ; ++i)
		{
			g_SG.m_Client.DoDisconnect(Data.uids[i]);
		}
	}

	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(aaa,UserServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(aaa);
	}
#endif
}
jNET_EVENT_END(PlugIn_Connect)


