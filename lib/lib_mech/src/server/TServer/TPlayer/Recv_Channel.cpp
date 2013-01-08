/* file : Recv_Channel.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-28 17:05:54
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TPlayer.h"
#include "base/jTimeHelper.h"

jNET_EVENT_BEGIN(PlugIn_Connect)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CH_HELLO,ChannelServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(CH_HELLO);
		pPlayer->SetState(eGPS_T_HELLO);
		jNET_SEND(pS,X2CH_USER_LOGIN_CHANNEL, pPlayer->Get_uid(), pPlayer->m_szID);
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CH_ECHO,ChannelServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(CH_ECHO);
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CH2X_CHAT,ChannelServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(CH2X_CHAT);
		jNetClient_Call_ret(CH2X_CHAT, Data);

	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CH2X_USER_LOGIN_CHANNEL_OK,ChannelServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(CH2X_USER_LOGIN_CHANNEL_OK);
// 		pPlayer->m_User = Data.user;
// 		pPlayer->m_Channel = Data.channel;
// 		pPlayer->SetState(eGPS_T_USER_INFO_RECV);
// 		jNetClient_Call_ret(CH2X_USER_LOGIN_CHANNEL_OK, Data);
// 		if(!pPlayer->Channel().size())
// 		{
// 			const Sys_Castle_id_t csid = 1;
// 			const Sys_TownPos_id_t tpsid =0;//0 이면 서버가 자동 결정.
// 			pS->WritePacket(&WRITE_X2T_NEW_TOWN(buf,csid,tpsid,jS(channel)));
// 		}
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CH2X_USER_LOGIN_CHANNEL_OK2,ChannelServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(CH2X_USER_LOGIN_CHANNEL_OK2);
// 		pPlayer->m_Force = Data.force;
// 		pPlayer->m_Hero = Data.hero;
// 		pPlayer->SetState(eGPS_T_USER_INFO_RECV);
// 		jNetClient_Call_ret(CH2X_USER_LOGIN_CHANNEL_OK2, Data);
	}

	const int  CAPITAL_TOWN_ID = 1;

// 	unsigned int __stdcall __RUN_CASTLE_SELECT( void* v)
// 	{
// 		jPlayerObj* pPlayer = g_pCurrUser;
// 		while(!pPlayer->Channel().size())
// 		{
// 			int i=0;
// 			++i;
// 
// 		}
// 
// 		Use_Town_id_t tuid = pPlayer->Channel_at(CAPITAL_TOWN_ID)->Get_tuid();
// 
// 		nXML::jE e;
// 		do
// 		{
// 			e=g_TCommonServer.FindChannel_by_TUID(pPlayer->m_eUser_file_db , tuid );
// 		}while(e.empty());
// 
// 		pPlayer->Change_CurrChannel(CAPITAL_TOWN_ID);
// 		_endthread();
// 		return 0;
// 	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CH2X_USER_LOGIN_CHANNEL_OK3,ChannelServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB_xml(CH2X_USER_LOGIN_CHANNEL_OK3,town_xml);
		g_pNetClient->SetServerTime(Data.server_time.m_t);
// 		if(pPlayer->m_eUser_file_db.full())
// 		{
// 			GetjIXml()->DeleteElement(pPlayer->m_eUser_file_db);
// 		}
// 		pPlayer->m_eUser_file_db = Data.town_xml;
// 		jIE* it = pPlayer->m_eUser_file_db(jS(Channel_List))->begin();
// 		jrFOR(it)
// 		{
// 			fname_t buf;
// 			jIVar* pV = it->GetAttrVar(jS(TUID));
// 			pV->ToString(buf);
// 			jLOG1(_T("channel tuid = %s"), buf);
// 		}
// 		pPlayer->SetState(eGPS_T_TOWN_SELECTED);
// 		if(g_pNetClient->m_isDummyMode)
// 		{
// 			pPlayer->Change_CurrChannel(CAPITAL_TOWN_ID);
// 		}
// 		else
// 		{
// 			unsigned int m_uiThreadID=0;
// 			_beginthreadex( NULL , 0 , __RUN_CASTLE_SELECT, 0, 0  , &m_uiThreadID );
// 		}
// 
// 		jNetClient_Call_ret(CH2X_USER_LOGIN_CHANNEL_OK3, Data);

	}


	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CH_ERROR,ChannelServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(CH_ERROR);
		jNetClient_Call_ret(T_ERROR,Data);
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CH2X_NEW_TOWN_OK,ChannelServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(CH2X_NEW_TOWN_OK);
// 		pPlayer->Channel().push_back(Data.channel);
// 		assert(Data.index == pPlayer->Channel().size());
// 		nXML::jE eNewChannel = pPlayer->m_eUser_file_db[jS(Channel_List)]->InsertChildElement(jS(Channel));
// 		fname_t szTUID;
// 		ToString(Data.channel.Get_tuid() , szTUID );
// 		eNewChannel.AttrP(jS(TUID)).T() = szTUID;
// 		Test_UID(eNewChannel.Attr(jS(TUID))->Get_cstr(),Data.channel.Get_tuid());
// 		//eNewChannel->DebugPrint(true);
// 		//pPlayer->m_eUser_file_db->DebugPrint(true);
// 
// 		if(pPlayer->Channel().size()==1)
// 		{
// 			pPlayer->Get_Use_User().Set_capital_tuid(Data.channel.Get_tuid());
// 			assert(pPlayer->Hero().size()==1);
// 			pPlayer->Hero()[0].Set_tuid(Data.channel.Get_tuid() );
// 			pPlayer->Change_CurrChannel(1);
// 		}

		jNetClient_Call_ret(CH2X_NEW_TOWN_OK,Data);
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CH2X_TOWN_DELETE_OK,ChannelServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(CH2X_TOWN_DELETE_OK);
// 		assert(Data.index > 0 && Data.index <= pPlayer->Channel().size());
// 
// 		Use_Town* pChannel = pPlayer->Channel_at(Data.index);
// 		assert(pChannel);
// 		jIE* peChannel = g_TCommonServer.FindChannel_by_TUID(pPlayer->m_eUser_file_db,pChannel->Get_tuid() );
// 		assert(peChannel);
// 		peChannel->Erase();
// 
// 		pPlayer->Channel().erase(pPlayer->Channel().begin() + (Data.index-1 ) );
// 
		jNetClient_Call_ret(CH2X_TOWN_DELETE_OK, Data);
	}


	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CH2X_TOWN_SELECT_RESULT,ChannelServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(CH2X_TOWN_SELECT_RESULT);
		jAssert0(Data.e.isOk());
// 		pPlayer->Change_CurrChannel(Data.channelNo,false);
// 		jNetClient_Call_ret(CH2X_TOWN_SELECT_RESULT, Data);


	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CH2X_BUILD_UPGRADE_RESULT,ChannelServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(CH2X_BUILD_UPGRADE_RESULT);
		if(Data.e.isError())
		{
			S_CH_ERROR pk;
			
			pk.ei.e= Data.e;
			pk.ei.sFunction = "build create error";
			pk.ei.eAction = eEAT_NOTIFY_ALL_CLIENT;
			jNetClient_Call_ret(CH_ERROR, pk);
			return;
		}
// 		Use_Hero* pHero = pPlayer->Hero_at(Data.hero_id);
// 		jAssert0(pHero);
// 		g_pNetClient->SetServerTime(Data.curr_server_time);
// 		nXML::jE eSlot = pPlayer->m_eCurrChannel[jS(BUILD_SLOT_LIST)][Data.build_slot];
// 		eSlot.AttrP(jS(LEVEL)).T() = (int32)Data.level;
// 		EBuildType eType = (EBuildType)Data._EBuildType;
// 		eSlot.AttrP(jS(EBuildType)).T() = ToString(eType);
// 		fname_t szBuf;
// 		eSlot.AttrP(jS(EXEC_HERO_UID)).T() = ToString(pHero->Get_huid(),szBuf);
// 		pHero->Set_work_state(nAQ::eHWS_CONSTRUCTION);
// 		jTimeHelper th;
// 		th.Get_curr_time();
// 		time_t end_day = Data.curr_server_time + Data.upgrade_sec;//종료되는 서버시간.
// 		eSlot.AttrP(jS(UPGRADE_END_DAY)).T() = ToString(end_day,szBuf);
// 		jNetClient_Call_ret(CH2X_BUILD_UPGRADE_RESULT, Data);
// 
// 		{
// 			jTimeHelper th;
// 			th.m_t = g_pNetClient->GetServerTime();
// 			TCHAR szBuf[128];
// 			th.Get_diff_day_string(end_day,szBuf);
// 			eSlot->DebugPrint(true);
// 			jLOG1(_T("build slot left time: %s"),szBuf);
// 
// 		}
	}
	
	
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CH2X_GOTO_CASTLE_MAP,ChannelServer)
	{
#if 0
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB_xml(CH2X_GOTO_CASTLE_MAP,castle_map_info);
		pPlayer->m_eGPS = eGPS_CASTLE;
		if(pPlayer->m_eGPS_Cashe.full())
		{
			GetjIXml()->DeleteElement(pPlayer->m_eGPS_Cashe);
		}
		pPlayer->m_eGPS_Cashe = Data.castle_map_info;
		jNetClient_Call_ret(CH2X_GOTO_CASTLE_MAP, Data);
#endif
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CH2X_GOTO_WORLD_MAP,ChannelServer)
	{
#if 0
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB_xml(CH2X_GOTO_WORLD_MAP,world_map_info);
		pPlayer->m_eGPS = eGPS_WORLD;
		if(pPlayer->m_eGPS_Cashe.full())
		{
			GetjIXml()->DeleteElement(pPlayer->m_eGPS_Cashe);
		}
		pPlayer->m_eGPS_Cashe = Data.world_map_info;
		jNetClient_Call_ret(CH2X_GOTO_WORLD_MAP, Data);
#endif
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(CH2X_GOTO_TOWN_MAP,ChannelServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(CH2X_GOTO_TOWN_MAP);

		pPlayer->m_eGPS = eGPS_TOWN;
		jNetClient_Call_ret(CH2X_GOTO_TOWN_MAP, Data);

	}

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(aaa,ChannelServer)
	{
		// Data, PlugIn_ToServer*pPC , B YTE buf_[1024] jPlayerObj* pPlayer
		aq_READ_PACKET_P2P_PB(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_Connect)
