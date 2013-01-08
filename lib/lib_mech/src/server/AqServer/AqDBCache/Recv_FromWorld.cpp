/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"

#include "network/protocal/PT_WorldServer_Enum.h"
using namespace nMech::nNET::nWorldServer;
#include "network/protocal/PT_DBQueryServer_Enum.h"
using namespace nMech::nNET::nDBQueryServer;


jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(W_HELLO,WorldServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		jSend_SS2server_ONLINE(W);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(W2DC_USER_LOGIN,WorldServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(W2DC_USER_LOGIN);
		AqDBCacheUser* pUser= g_Users_DC.Going_to_Login(Data.uid,Data.id);
		g_Users_DC.WritePacket(WRITE_DC2DQ_USER_LOGIN(buf, pUser->m_pjDBUserInfo->m_uid));
	}

	
	jNET_EVENT_RECEIVER_P2P(W2DC_USER_DISCONNECT,WorldServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(W2DC_USER_DISCONNECT);

		GetjILog()->Log(_T("user disconnect count: %d"),Data.id.size());
		jFE();
		vector<userid_t>uids;

		for(int i=0; i< Data.id.size(); ++i)
		{
			AqDBCacheUser* pUser = g_Users_DC.Going_to_delete(Data.id[i].c_str());
			if(pUser)
				uids.push_back(pUser->m_pjDBUserInfo->m_uid);
		}
#ifdef _DEBUG
		int iTot_eGOING_TO_LOGIN =0;
		int iTot_eLOGIN_OK =0;

		for(int i=0; i < g_Users_DC.m_vecUsersSM.size() ; ++i)
		{
			jUserZoneInfo_DC::EUserNodeUsingState eType = g_Users_DC.m_vecUsersSM[i].m_pjDBUserInfo->m_eUsingState;
			if(eType==jUserZoneInfo_DC::eGOING_TO_LOGIN )
			{
				++iTot_eGOING_TO_LOGIN;
			}
			else if(eType == jUserZoneInfo_DC::eLOGIN_OK)
			{
				++iTot_eLOGIN_OK;
			}
		}
		if(iTot_eLOGIN_OK==0)
		{
			GetjILog()->Log(_T("user count eGOING_TO_LOGIN(%d), eLOGIN_OK(0)"), iTot_eGOING_TO_LOGIN);
		}
#endif
		g_Users_DC.WritePacket(WRITE_DC2DQ_USER_DISCONNECT(buf, uids));

	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(W2DC_USER_LOGIN_CHANNEL,WorldServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(W2DC_USER_LOGIN_CHANNEL);
		jGet_DBUser_byName(Data.id , Data.uid , pS);// AqDBCacheUser* pUser

		jFE();
		pUser->m_pToTown = pFE->find_user(Data.town);
		if(!pUser->m_pToTown)
		{
			GetjILog()->Warning(jFUNC1 _T("유저가 채널접속을 했으나 해당 마을서버를 못찾음."));
			struct print_servers
			{
				void operator()(AqConnectedServerNode& it)
				{
					fname_t buf;
					GetjILog()->Log(ToString(&it,buf));
				}
			};

			pFE->for_each(print_servers());
			// jTODO jError 유저가 채널접속을 했으나 해당 마을서버를 못찾음.
			jSEND_ERROR_USER_DISCONNECT(W,SR_t(MATCH_TOWNSERVER_NOT_FOUND),0 , Data.uid);
			return;
		}
		g_Users_DC.WritePacket(WRITE_DC2DQ_GET_TOWN_LIST(buf, Data.uid));
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(W2DC_USER_LOGIN_DUPLICATE,WorldServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(W2DC_USER_LOGIN_DUPLICATE);
		g_Users_DC.Going_to_delete(Data.id);
		vector<userid_t> uid;
		uid.push_back(Data.uid);
		g_Users_DC.WritePacket(WRITE_DC2DQ_USER_DISCONNECT(buf, uid));
		pS->WritePacket(&WRITE_DC2W_USER_LOGIN_DUPLICATE_OK(buf,Data.id));
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(W2DC_NEW_TOWN,WorldServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(W2DC_NEW_TOWN);
		
		g_Users_DC.WritePacket(WRITE_DC2DQ_TOWN_CREATE(buf,Data.uid,Data.csid,Data.tpsid,Data.name));

	}


#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(aaa,WorldServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(aaa);
	}
#endif
}
jNET_EVENT_END(PlugIn_ToBackEnd)




