/* file : Recv_FromClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:56:07
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TChannel.h"


jNET_EVENT_BEGIN(PlugIn_Server)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(CH_ECHO)
	{
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(CH_ECHO);
		jNET_SEND2(g_SG.m_Client,CH_ECHO, Data.msg, Data.type);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2CH_CHAT)
	{
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(X2CH_CHAT);
		jNET_SEND2(g_SG.m_Client,CH2X_CHAT, Data.msg, Data.type);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2CH_USER_LOGIN_CHANNEL)
	{
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(X2CH_USER_LOGIN_CHANNEL);
		pPlayer->m_pid = Data.pid;
		jw_strcpy( pPlayer->m_szID , Data.id);
		// channel은 속한 도메인의 월드서버 하나에만 접속해있다.
		jNET_SEND2(g_SG.m_World , CH2W_USER_LOGIN_CHANNEL , Data.pid , Data.id);
		g_SG.Set_U4_USER_CONNECTION_NOTIFY_CS(Data.pid,Data.id,true);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2CH_TOWN_SELECT)
	{
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(X2CH_TOWN_SELECT);
		//pUser_Check_channelid(Data.index,T,player_id_t());
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2CH_TOWN_DELETE)
	{
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(X2CH_TOWN_DELETE);

		//pS_DB->WritePacket(&WRITE_CH2DC_TOWN_DELETE(buf, pPlayer->Get_uid() , Data.index));
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2CH_NEW_TOWN)
	{
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(X2CH_NEW_TOWN);
#if 0
		if(pPlayer->m_Channel.size() > (iMAX_USER_Channel-1))
		{
			//허용 아바타 갯수 초가
			pS_eSEND_jError_ToClient(T , SR_t(TOWN_NUM_IS_OVER),CR_t(X2CH_TOWN_CREATE));
			return;
		}

		pUser_Check_make_name(Data.name);

		jPC();
		pPC->m_pToWorld->WritePacket(&WRITE_CH2W_NEW_TOWN(buf,pPlayer->Get_uid(),Data.csid,Data.tpsid,Data.name));
#endif
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2CH_NEW_BUILD)
	{
#if 0
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(X2CH_NEW_BUILD);
		fname_t szBuf1;
		nAQ::EBuildType eType = (nAQ::EBuildType)Data._EBuildType;
		nXML::jE eBList = pPlayer->m_eCurrChannel[jS(BUILD_SLOT_LIST)];
		nXML::jE eSlot = eBList(Data.build_slot);
		jUSER_ERROR_CHECK(eSlot.full(),X2CH_NEW_BUILD,SLOT_IS_USE);
		Use_Hero* pHero = pPlayer->Hero_at(Data.hero_id);
		jUSER_ERROR_CHECK(!pHero,X2CH_NEW_BUILD,HERO_ID_ERROR);
		jUSER_ERROR_CHECK(pHero->Get_work_state()!=nAQ::eHWS_REST,X2CH_NEW_BUILD,HERO_STATE_IS_NOT_REST);
		
		eSlot = eBList[Data.build_slot];
		int32 level =0;
		eSlot.AttrP(jS(LEVEL)).T() = (int32)level;
		eSlot.AttrP(jS(EBuildType)).T() = ToString(eType);
		eSlot.AttrP(jS(EXEC_HERO_UID)).T() = ToString(pHero->Get_huid(),szBuf1);

		jError e;
		std::pair<time_t,int32> upgrade_sec;//업글 시간 < 서버현제시간 , 업글걸리는 초>
		try
		{
			bool isOk=false;
			if(0){}
#define CheckUpgrade_Sys_T_Bar2344(table)\
			else if( eType ==nAQ::eEBT_##table)\
			{\
				std::pair<time_t,int32> CheckUpgrade_##table(Use_User&u,Use_Channel* pT,nXML::jE eSlot,Use_Hero*pH);\
				upgrade_sec = CheckUpgrade_##table(pPlayer->m_User,pPlayer->GetCurrChannel(),eSlot,pHero);\
			}
			for_each_EBuildType_Impl(CheckUpgrade_Sys_T_Bar2344)
			else
			{
				throw jError(SR_t(X2CH_NEW_BUILD),CR_t(_EBuildType_IS_UNKOWN));
			}
		}
		catch (jError e1)
		{
			e = e1;
		}

		if(e.isError())
		{
			eSlot->Erase();
		}
		else
		{
			pHero->Set_work_state(nAQ::eHWS_CONSTRUCTION);

		}
		j_time_t curr_server_time;
		curr_server_time.m_t = upgrade_sec.first;
		//time(&curr_server_time);

		pS->WritePacket(&WRITE_CH2X_BUILD_UPGRADE_RESULT(buf
			,Data.build_slot,Data._EBuildType,level,e,curr_server_time,upgrade_sec.second
			,Data.hero_id));
#endif
	}


	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2CH_GOTO_CASTLE_MAP)
	{
#if 0
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(X2CH_GOTO_CASTLE_MAP);

		switch(pPlayer->m_eGPS)
		{
		case eGPS_CASTLE:
			{
				jWARN1(_T("if(pPlayer->m_eGPS == eGPS_CASTLE) : %s"),jT(pPlayer->m_User.Get_name()));
				return;
			}
			break;
		case eGPS_TOWN:
			{

			}
			break;
		case eGPS_WORLD:
			{
				//pPS->Get_WorldInfo()[jS(Force)]
			}
			break;
		}

		pPlayer->m_eGPS == eGPS_CASTLE;
		Use_Channel* pChannel = pPlayer->GetCurrChannel();
		nXML::jE eCastle = pPS->Get_CastleInfo(pChannel->Get_castle_sid());
		S_CH2X_GOTO_CASTLE_MAP pk;
		pk.channelNo = Data.channelNo;
		pk.castle_map_info = eCastle;
		pPlayer->WritePacket(&WRITE_CH2X_GOTO_CASTLE_MAP(buf,pk) );
#endif
	}



	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2CH_GOTO_WORLD_MAP)
	{
#if 0
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(X2CH_GOTO_WORLD_MAP);

		switch(pPlayer->m_eGPS)
		{
		case eGPS_CASTLE:
			{
			}
			break;
		case eGPS_TOWN:
			{

			}
			break;
		case eGPS_WORLD:
			{
				jWARN1(_T("if(pPlayer->m_eGPS == eGPS_WORLD) : %s"), jT(pPlayer->m_User.Get_name()) );
				return;
			}
			break;
		}

		pPlayer->m_eGPS == eGPS_WORLD;
		nXML::jE eWorld = pPS->Get_WorldInfo();
		S_CH2X_GOTO_WORLD_MAP pk;
		pk.channelNo = Data.channelNo;
		pk.world_map_info = eWorld;
		pPlayer->WritePacket(&WRITE_CH2X_GOTO_WORLD_MAP(buf,pk) );
#endif
	}



	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2CH_GOTO_TOWN_MAP)
	{
#if 0
		// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
		READ_PACKET_FromClient(X2CH_GOTO_TOWN_MAP);

		switch(pPlayer->m_eGPS)
		{
		case eGPS_CASTLE:
			{
			}
			break;
		case eGPS_TOWN:
			{
				jWARN1(_T("if(pPlayer->m_eGPS == eGPS_TOWN) : %s"), jT(pPlayer->m_User.Get_name()) );
				return;
			}
			break;
		case eGPS_WORLD:
			{
			}
			break;
		}

		pPlayer->m_eGPS == eGPS_TOWN;
		pPlayer->WritePacket(&WRITE_CH2X_GOTO_TOWN_MAP(buf,Data.channelNo) );
#endif
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
