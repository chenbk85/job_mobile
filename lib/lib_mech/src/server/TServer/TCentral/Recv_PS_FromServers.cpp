/* file : Recv_FromServers.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:50:59
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TCentral.h"


jNET_EVENT_BEGIN(PlugIn_Server)
{

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(C_ECHO)
	{
		// PlugIn_Central*pP , B YTE buf_[1024] , jIGridNode* pFServer
		READ_PACKET_PS_BS(C_ECHO);
		g_SG.WritePacket(WRITE_C_ECHO(buf, Data.msg,0),0);
	}


	static serverid_t generate_serverid(jServerInfo* si)//SS2C_ONLINE를 받았을때 만듬.
	{
		if(si->m_eType==eCentral) return iSTART_SERVERID_Central;
		#define make_server_id_432(name,idStart,TAG) if(si->m_eType==e##name)\
		{ serverid_t sid = iSTART_SERVERID_##name; for(;;++sid)if(!g_SG.m_##name.find(sid)) break; return sid;}
		for_each_SERVER_TYPE(make_server_id_432);
		jERROR( "" );
		return 0;
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(SS2C_ONLINE)
	{
		// PlugIn_Server*pPS , BYTE buf[1024] , jServerInfo*si
		READ_PACKET_PS_BS(SS2C_ONLINE);
		*si = Data.my;
#ifdef DEBUG
		{
			jSI(pS->GetGridNode());
			jAssert0( memcmp(si, &Data.my, sizeof(jServerInfo) ) ==0 );
		}
#endif
		GetLocalTime(&si->m_StartTime);
		tname32_t szBuf;
		jt_strcpy_s(si->m_szIP , pS->GetIP(szBuf));

		//--------------------------------------------------------------------------
		// 0. 센트럴서버가 restart된게 아닐때 server id 새로 발급.
		//--------------------------------------------------------------------------
		if(!si->m_sid)
		{
			si->m_sid = generate_serverid(si);
		}
		//--------------------------------------------------------------------------
		// 1 기존 서버정보를 새로접속한 서버에 알린다.
		//--------------------------------------------------------------------------
		nswb16000_t buf1;
		jServerInfoList_t servers;
		#define jLAMDA_map2vector(X,Z) Z(vector<jServerInfo>&,servers)
		jLAMDA_for_each(map2vector,jServerInfo*)
		{
			servers.push_back(*it);
		}
		jLAMDA_end();

		tr1::function<void (jServerInfo*)> func = map2vector(servers);
		g_SG.ServerInfo_for_each( func );
		jNET_SEND(pS,C2SS_ONLINE_OK, *si,servers);
		g_SG.ServerInfo_insert(*si);
		//--------------------------------------------------------------------------
		// 2 다른 서버에 알린다.
		//--------------------------------------------------------------------------
		g_SG.WritePacket(WRITE_C_SERVER_ONLINE(buf1,*si),pS);

	}//jNET_EVENT_RECEIVER(SS2C_ONLINE)

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(C4_USER_CONNECTION_NOTIFY)
	{
#ifdef TSERVER_PREPARE
		// PlugIn_Server*pPS , BYTE buf[1024] , jServerInfo*si
		READ_PACKET_PS_BS(C4_USER_CONNECTION_NOTIFY);
		pFServer->m_iTotClient->Set_int(Data.userCnt);
		switch(pFServer->Get_m_eType() )
		{
		case eChannel:// Channel서버이면 모든 로긴서버에 통보
			{
				jAUTO_LOCK_CS1(pPS->m_mapC2_USER_CONNECTION_NOTIFY_CS_Channel);
				pPS->m_mapC2_USER_CONNECTION_NOTIFY_Channel[pFServer->Get_m_sid()] = Data.userCnt;
			}
			break;
		case eGame: // Game 서버이면 해당 월드의 모든 Channel서버에 통보
			{
				jAUTO_LOCK_CS1(pPS->m_mapC2_USER_CONNECTION_NOTIFY_CS_Game);
				pPS->m_mapC2_USER_CONNECTION_NOTIFY_Game[pFServer->Get_m_szWorld()][pFServer->Get_m_sid()] = Data.userCnt;
			}
			break;
		}
#endif
	}

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_Server*pPS , BYTE buf[1024] , jServerInfo*si
		READ_PACKET_PS_BS(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_Server)


