/* file : Recv_FromClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:56:07
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TCommand.h"



jNET_EVENT_BEGIN(PlugIn_Server)
{

	serverid_t generate_serverid_CD(jServerInfo* si)//SS2CD_ONLINE를 받았을때 만듬. 번호는 맨뒤 큰숫자부터 발급.
	{
		if(si->m_eType==eCentral) return iSTART_SERVERID_Central;

#define make_server_id_432(name,idStart,TAG) if(si->m_eType==e##name)\
		{ serverid_t sid = jServerInfo::get_max_sid(e##name); for(;;--sid)if(!g_SG.m_##name.find(sid)) break; jAssert0(sid>0);return sid;}
		for_each_SERVER_TYPE(make_server_id_432);
		jERROR( "" );
		return 0;
	}

	jNET_EVENT_RECEIVER(SS2CD_ONLINE)
	{
		// PlugIn_Server*p , BYTE buf[1024] , TClientUser* pDummy
		READ_PACKET_PS_BS(SS2CD_ONLINE);
		if(g_SG.m_Central.size())// central이 살아 있을때는 아무일 안함.
		{
			if(si->m_sid==0)
			{
				jNET_SEND(pS,CD_SERVERINFO_ACK,g_SG.m_MyInfo);
			}
			return;
		}
		
		*si = Data.my;
		GetLocalTime(&si->m_StartTime);
		tname32_t szBuf;
		jt_strcpy_s(si->m_szIP , pS->GetIP(szBuf));

		//--------------------------------------------------------------------------
		// 0. 센트럴서버가 restart된게 아닐때 server id 새로 발급.
		//--------------------------------------------------------------------------
		if(!si->m_sid)
		{
			si->m_sid = generate_serverid_CD(si);
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
		jNET_SEND(pS,CD2SS_ONLINE_OK, *si,servers);
		g_SG.ServerInfo_insert(*si);
		//--------------------------------------------------------------------------
		// 2 다른 서버에 알린다.
		//--------------------------------------------------------------------------
		g_SG.WritePacket(WRITE_CD_SERVER_ONLINE(buf1,*si),pS);


	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(SS2CD_SERVERINFO_ACK)
	{
		// PlugIn_Server*p , BYTE buf[1024] , TClientUser* pDummy
		READ_PACKET_PS_BS(SS2CD_SERVERINFO_ACK);
		if(!Data.si.m_sid)
		{
			jNET_SEND(pS, CD_SERVERINFO_ACK, g_SG.m_MyInfo);
			return;
		}
		*si = Data.si;

#ifdef DEBUG
		{
			jSI(pS->GetGridNode());
			jAssert0(Data.si.m_sid == si->m_sid);
		}
#endif
	}

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_Server*p , BYTE buf[1024] , TClientUser* pDummy
		READ_PACKET_PS_BS(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_Server)

