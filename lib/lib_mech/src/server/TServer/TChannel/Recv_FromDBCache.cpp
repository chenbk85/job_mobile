/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TChannel.h"

#include "base/jtimehelper.h"

jNET_EVENT_BEGIN(PlugIn_Connect)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(DC_ERROR,DBCacheServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		jSend_ERROR_TO_CLIENT(DC,CH);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(DC2CH_USER_LOGIN_CHANNEL_OK,DBCacheServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(DC2CH_USER_LOGIN_CHANNEL_OK);
		jFE_GetUser(Data.pid); //TClientUser* pUser
#if 0
		S_CH2X_USER_LOGIN_CHANNEL_OK pk;
		pk.user = pUser->m_User = Data.user;
		pk.channel = pUser->m_Channel = Data.channel;
		nswb8000_t buf2;
		pUser->Write_Packet(WRITE_CH2X_USER_LOGIN_CHANNEL_OK(buf2,pk));
#endif
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(DC2CH_USER_LOGIN_CHANNEL_OK2,DBCacheServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(DC2CH_USER_LOGIN_CHANNEL_OK2);
		jFE_GetUser(Data.pid); //TClientUser* pUser
#if 0
		S_CH2X_USER_LOGIN_CHANNEL_OK2 pk;
		pk.hero = pUser->m_Hero = Data.hero;
		pk.force = pUser->m_Force = Data.force;
		nswb8000_t buf2;
		pUser->Write_Packet(WRITE_CH2X_USER_LOGIN_CHANNEL_OK2(buf2,pk));

		assert(pUser->m_eUser_file_db.empty());
		{
			fname_t szDoc;
			bool isCreate = g_TCommonServer.Make_FileDBPath_By_Channel_DBID(jT(pUser->m_szID), pUser->m_User.Get_uid(), szDoc);
			jID* pD = GetjIXml()->Load(szDoc);
			pUser->m_eUser_file_db = pD;
			if(isCreate)
			{
				pUser->m_eUser_file_db.AttrP(jS(USER)).T()= jT(pUser->m_User.Get_name());
				fname_t szUID;
				jt_sprintf(szUID , _T("%I64d") , pUser->m_User.Get_uid().m_db_id);
				pUser->m_eUser_file_db.AttrP(jS(UID)).T()= szUID;
				pUser->m_eUser_file_db[jS(Channel_List)]->EraseChild();
				pD->Save();
			}
			else
			{
				pUser->m_eUser_file_db.Attr(jS(USER))->IsContents(jT(pUser->m_User.Get_name()));

			}
			S_CH2X_USER_LOGIN_CHANNEL_OK3 pk;
			pk.channel_xml = pD->BaseI();
			jTimeHelper th;
			j_time_t server_time;
			server_time.m_t = th.Get_curr_time();
			pk.server_time = server_time;
			pUser->Write_Packet(WRITE_CH2X_USER_LOGIN_CHANNEL_OK3(buf,pk) );
		}
#endif
	}


	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(DC2CH_NEW_TOWN_OK,DBCacheServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(DC2CH_NEW_TOWN_OK);
		jFE_GetUser(Data.pid); //TClientUser* pUser
#if 0
		pUser->m_Channel.push_back(Data.channel);
		assert(pUser->m_Channel.size() == Data.index);
		if(pUser->m_Channel.size()==1)
		{// 弥檬 付阑 积己矫 固府 积己等 康旷狼 鸥款家加技泼.
			pUser->m_User.Set_capital_tuid(Data.channel.Get_tuid());
			assert(pUser->m_Hero.size()==1);
			pUser->m_Hero[0].Set_tuid(Data.channel.Get_tuid());
		}

		nXML::jE eNewChannel = pUser->m_eUser_file_db(jS(Channel_List))->InsertChildElement(jS(Channel));
		fname_t szTUID;
		eNewChannel.AttrP(jS(TUID)).T() = ToString(Data.channel.Get_tuid() , szTUID );
		Test_UID(eNewChannel.Attr(jS(TUID))->Get_cstr(), Data.channel.Get_tuid());
		g_jXmlSaveManager.SaveDoc(pUser->m_eUser_file_db->GetDoc());

		pUser->Write_Packet(WRITE_CH2X_NEW_TOWN_OK(buf, Data.index, Data.channel) );
#endif
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(DC2CH_TOWN_DELETE_OK,DBCacheServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(DC2CH_TOWN_DELETE_OK);
		jFE_GetUser(Data.pid); //TClientUser* pUser
#if 0
		Use_Channel* pChannel = pUser->Channel_at(Data.index);
		jIE* peChannel = g_TCommonServer.FindChannel_by_TUID(pUser->m_eUser_file_db,pChannel->Get_tuid() );
		if(!peChannel)
		{
			tname1024_t szBuf;
			pUser->m_eUser_file_db->DebugPrint(true);
			jWARN1(_T("pUser->m_eUser_file_db : tuid not found : %s"),ToString(pChannel->Get_tuid(),szBuf));
			jWARN1(_T("channelname:%s"),pChannel->Get_name());
		}
		else
			peChannel->Erase();

		assert(Data.index >0 && Data.index <= pUser->m_Channel.size() );
		pUser->m_Channel.erase(pUser->m_Channel.begin() + (Data.index - 1));
		
		pUser->Write_Packet(WRITE_CH2X_TOWN_DELETE_OK(buf, Data.index));
		g_jXmlSaveManager.SaveDoc(pUser->m_eUser_file_db->GetDoc());
#endif
	}


#if 0


	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(aaa,DBCacheServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET_PC_B(aaa);
	}
#endif
}
jNET_EVENT_END(PlugIn_Connect)


