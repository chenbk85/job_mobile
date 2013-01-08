/* file : Recv_FromServers.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:50:59
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToFrontEnd.h"
#include "network/protocal/PT_CentralServer_Enum.h"
using namespace nCentralServer;




jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(C_ECHO)
	{
		// PlugIn_Central*pP , B YTE buf_[1024] , AqConnectedServerNode* pFServer
		READ_PACKET_C(C_ECHO);
		pFE->send_all(WRITE_C_ECHO(buf, Data.msg),0);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(SS2C_ONLINE)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqConnectedServerNode*pFServer
		READ_PACKET_C_XML(SS2C_ONLINE,xml);

		pFServer->m_eType = Data.eType;
		pFServer->m_Timer.restart();
		GetLocalTime(&pFServer->m_StartTime);

		tname32_t szBuf;
		pFServer->m_pS->GetIP(szBuf);
		pFServer->Set_ServerInfo(Data.xml , pFServer->iHandle , szBuf);

		tcstr szWorld = pFServer->Get_m_szWorld();
		nXML::jE eWorldCluster;
		eWorldCluster = pFE->m_eServers[szWorld];
		eWorldCluster->InsertChild(0,Data.xml);
		pFServer->m_E->SetUserData(jS(AqConnectedServerNode),pFServer);
		eWorldCluster->DebugPrint(true);

		//--------------------------------------------------------------------------
		// 1 기존 서버정보를 새로접속한 서버에 알린다.
		//--------------------------------------------------------------------------
		nswb16000_t buf;

		S_C2SS_ONLINE_OK sendData;
		sendData.sid = pFServer->Get_m_sid();
		sendData.server_list = pFE->m_eServers;
		//pFE->m_eServers->DebugPrint(true);
		pFServer->Write_Packet(WRITE_C2SS_ONLINE_OK(buf,sendData) );
		
		//--------------------------------------------------------------------------
		// 2 다른 서버에 알린다.
		//--------------------------------------------------------------------------
		S_C_SERVER_ONLINE sendData2;
		sendData2.eType = pFServer->Get_m_eType();
		sendData2.server = pFServer->m_E;
		jPacket_Base pk = WRITE_C_SERVER_ONLINE(buf,sendData2 );
		// 서버가 기동되면 모든 서버들에게 항상 알린다.
		pFE->send_all(pk,pS);

		pFE->m_eServers->DebugPrint(true);

	}//jNET_EVENT_RECEIVER(SS2C_ONLINE)

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(C4_USER_CONNECTION_NOTIFY)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqConnectedServerNode*pFServer
		READ_PACKET_C(C4_USER_CONNECTION_NOTIFY);
		pFServer->m_iTotClient->Set_int(Data.userCnt);
		switch(pFServer->Get_m_eType() )
		{
		case jServerInfoBase::eTown:// Town서버이면 모든 로긴서버에 통보
			{
				jAUTO_LOCK_CS1(pFE->m_mapC2_USER_CONNECTION_NOTIFY_CS_Town);
				pFE->m_mapC2_USER_CONNECTION_NOTIFY_Town[pFServer->Get_m_sid()] = Data.userCnt;
			}
			break;
		case jServerInfoBase::eDungeon: // Dungeon 서버이면 해당 월드의 모든 Town서버에 통보
			{
				jAUTO_LOCK_CS1(pFE->m_mapC2_USER_CONNECTION_NOTIFY_CS_Dungeon);
				pFE->m_mapC2_USER_CONNECTION_NOTIFY_Dungeon[pFServer->Get_m_szWorld()][pFServer->Get_m_sid()] = Data.userCnt;
			}
			break;
		}
	}

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqConnectedServerNode*pFServer
		READ_PACKET_C(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)


