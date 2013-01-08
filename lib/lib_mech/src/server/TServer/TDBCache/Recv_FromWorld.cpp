/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TDBCache.h"

#include "../TCommonClient/protocal/PT_WorldServer_Enum.h"
using namespace nMech::nNET::nWorldServer;
#include "../TCommonClient/protocal/PT_DBQueryServer_Enum.h"
using namespace nMech::nNET::nDBQueryServer;


jNET_EVENT_BEGIN(PlugIn_Connect)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(W2DC_USER_LOGIN,WorldServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(W2DC_USER_LOGIN);
#ifdef TSERVER_PREPARE
		jPlayerObj* pUser= g_DQ.Going_to_Login(Data.pid,Data.id);
		g_DQ.WritePacket(WRITE_DC2DQ_USER_LOGIN(buf, pUser->m_SharedMemory->m_uid));
#endif
	}

	
	jNET_EVENT_RECEIVER_P2P(W2DC_USER_DISCONNECT,WorldServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(W2DC_USER_DISCONNECT);
#ifdef TSERVER_PREPARE
		jLOG1(_T("user disconnect count: %d"),Data.pid.size());
		jPS();
		vector<player_id_t>uids;

		for(size_t i=0; i< Data.pid.size(); ++i)
		{
			jPlayerObj* pUser = g_DQ.Going_to_delete(Data.pid[i].c_str());
			if(pUser)
				uids.push_back(pUser->m_SharedMemory->m_uid);
		}
#ifdef _DEBUG
		int iTot_eGOING_TO_LOGIN =0;
		int iTot_eLOGIN_OK =0;

		for(int i=0; i < g_DQ.m_vecUsersSM.size() ; ++i)
		{
			jPlayerDBSM::EUserNodeUsingState eType = g_DQ.m_vecUsersSM[i].m_SharedMemory->m_eUsingState;
			if(eType==jPlayerDBSM::eGOING_TO_LOGIN )
			{
				++iTot_eGOING_TO_LOGIN;
			}
			else if(eType == jPlayerDBSM::eLOGIN_OK)
			{
				++iTot_eLOGIN_OK;
			}
		}
		if(iTot_eLOGIN_OK==0)
		{
			jLOG1(_T("user count eGOING_TO_LOGIN(%d), eLOGIN_OK(0)"), iTot_eGOING_TO_LOGIN);
		}
#endif
		g_DQ.WritePacket(WRITE_DC2DQ_USER_DISCONNECT(buf, uids));
#endif //TSERVER_PREPARE

	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(W2DC_USER_LOGIN_CHANNEL,WorldServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(W2DC_USER_LOGIN_CHANNEL);
		
		jGet_DCUser_byName(Data.id , Data.pid , pS);// jPlayerObj* pUser

		jPS();
		jIGridNode* pGN = g_SG.m_Channel.find(Data.town);
		if(!pGN)
		{
			jWARN("유저가 채널접속을 했으나 해당 마을서버를 못찾음.");

			jLAMDA_for_each0(print_servers,jIGridNode*)
			{
				tname1024_t buf;
				jSI(it);
				jLOG1(ToString(si,buf));
			}
			jLAMDA_end();

			g_SG.m_Channel.for_each(print_servers());
			// jTODO jError 유저가 채널접속을 했으나 해당 마을서버를 못찾음.
			jSEND_ERROR_USER_DISCONNECT(W,SR_t(MATCH_TOWNSERVER_NOT_FOUND),0 , Data.pid);
			return;
		}
		pUser->Set_Server(eChannel,Data.town);
		g_DQ.WritePacket(WRITE_DC2DQ_GET_TOWN_LIST(buf, Data.pid));
	}
#ifdef TSERVER_PREPARE
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(W2DC_USER_LOGIN_DUPLICATE,WorldServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(W2DC_USER_LOGIN_DUPLICATE);
		g_DQ.Going_to_delete(Data.id);
		vector<player_id_t> uid;
		uid.push_back(Data.pid);
		g_DQ.WritePacket(WRITE_DC2DQ_USER_DISCONNECT(buf, uid));
		pS->WritePacket(&WRITE_DC2W_USER_LOGIN_DUPLICATE_OK(buf,Data.id));
	}
#endif //TSERVER_PREPARE

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(W2DC_NEW_TOWN,WorldServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(W2DC_NEW_TOWN);
		
		g_DQ.WritePacket(WRITE_DC2DQ_TOWN_CREATE(buf,Data.pid,Data.csid,Data.tpsid,Data.name));

	}


#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(aaa,WorldServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(aaa);
	}
#endif
}
jNET_EVENT_END(PlugIn_Connect)




