/* file : Recv_Town.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-28 17:05:54
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TestClient.h"
#include "PlugIn_ToBackEnd.h"
#include "base/jTimeHelper.h"

jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(T_HELLO,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(T_HELLO);
		pUser->SetState(eGPS_T_HELLO);
		pS->WritePacket(&WRITE_X2T_USER_LOGIN_CHANNEL(buf, pUser->Get_uid(), pUser->m_szID));
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(T_ECHO,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(T_ECHO);
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(T2X_CHAT,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(T2X_CHAT);
		jNetClient_Call_ret(T2X_CHAT, Data);

	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(T2X_USER_LOGIN_CHANNEL_OK,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(T2X_USER_LOGIN_CHANNEL_OK);
		pUser->m_User = Data.user;
		pUser->m_Town = Data.town;
		pUser->SetState(eGPS_T_USER_INFO_RECV);
		jNetClient_Call_ret(T2X_USER_LOGIN_CHANNEL_OK, Data);
		if(!pUser->Town().size())
		{
			const Sys_Castle_id_t csid = 1;
			const Sys_TownPos_id_t tpsid =0;//0 이면 서버가 자동 결정.
			pS->WritePacket(&WRITE_X2T_NEW_TOWN(buf,csid,tpsid,jS(town)));
		}
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(T2X_USER_LOGIN_CHANNEL_OK2,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(T2X_USER_LOGIN_CHANNEL_OK2);
		pUser->m_Force = Data.force;
		pUser->m_Hero = Data.hero;
		pUser->SetState(eGPS_T_USER_INFO_RECV);
		jNetClient_Call_ret(T2X_USER_LOGIN_CHANNEL_OK2, Data);
	}

	const int  CAPITAL_TOWN_ID = 1;

	unsigned int __stdcall __RUN_CASTLE_SELECT( void* v)
	{
		jDummyPlayer* pUser = g_pCurrUser;
		while(!pUser->Town().size())
		{
			int i=0;
			++i;

		}

		Use_Town_id_t tuid = pUser->Town_at(CAPITAL_TOWN_ID)->Get_tuid();

		nXML::jE e;
		do
		{
			e=g_jAqCommon.FindTownBYTUID(pUser->m_eUser_file_db , tuid );
		}while(e.empty());

		pUser->Change_CurrTown(CAPITAL_TOWN_ID);
		_endthread();
		return 0;
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(T2X_USER_LOGIN_CHANNEL_OK3,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB_xml(T2X_USER_LOGIN_CHANNEL_OK3,town_xml);
		g_pNetClient->SetServerTime(Data.server_time.m_t);
		if(pUser->m_eUser_file_db.full())
		{
			GetjIXml()->DeleteElement(pUser->m_eUser_file_db);
		}
		pUser->m_eUser_file_db = Data.town_xml;
		jIE* it = pUser->m_eUser_file_db(jS(Town_List))->begin();
		jrFOR(it)
		{
			fname_t buf;
			jIVar* pV = it->GetAttrVar(jS(TUID));
			pV->ToString(buf);
			GetjILog()->Log(_T("town tuid = %s"), buf);
		}
		pUser->SetState(eGPS_T_TOWN_SELECTED);
		if(g_pNetClient->m_isDummyMode)
		{
			pUser->Change_CurrTown(CAPITAL_TOWN_ID);
		}
		else
		{
			unsigned int m_uiThreadID=0;
			_beginthreadex( NULL , 0 , __RUN_CASTLE_SELECT, 0, 0  , &m_uiThreadID );
		}

		jNetClient_Call_ret(T2X_USER_LOGIN_CHANNEL_OK3, Data);

	}


	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(T_ERROR,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(T_ERROR);
		jNetClient_Call_ret(T_ERROR,Data);
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(T2X_NEW_TOWN_OK,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(T2X_NEW_TOWN_OK);
		pUser->Town().push_back(Data.town);
		assert(Data.index == pUser->Town().size());
		nXML::jE eNewTown = pUser->m_eUser_file_db[jS(Town_List)]->InsertChildElement(jS(Town));
		fname_t szTUID;
		ToString(Data.town.Get_tuid() , szTUID );
		eNewTown.AttrP(jS(TUID)).T() = szTUID;
		Test_UID(eNewTown.Attr(jS(TUID))->Get_cstr(),Data.town.Get_tuid());
		//eNewTown->DebugPrint(true);
		//pUser->m_eUser_file_db->DebugPrint(true);

		if(pUser->Town().size()==1)
		{
			pUser->Get_Use_User().Set_capital_tuid(Data.town.Get_tuid());
			assert(pUser->Hero().size()==1);
			pUser->Hero()[0].Set_tuid(Data.town.Get_tuid() );
			pUser->Change_CurrTown(1);
		}

		jNetClient_Call_ret(T2X_NEW_TOWN_OK,Data);
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(T2X_TOWN_DELETE_OK,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(T2X_TOWN_DELETE_OK);
		assert(Data.index > 0 && Data.index <= pUser->Town().size());

		Use_Town* pTown = pUser->Town_at(Data.index);
		assert(pTown);
		jIE* peTown = g_jAqCommon.FindTownBYTUID(pUser->m_eUser_file_db,pTown->Get_tuid() );
		assert(peTown);
		peTown->Erase();

		pUser->Town().erase(pUser->Town().begin() + (Data.index-1 ) );

		jNetClient_Call_ret(T2X_TOWN_DELETE_OK, Data);
	}


	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(T2X_TOWN_SELECT_RESULT,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(T2X_TOWN_SELECT_RESULT);
		jAssert0(Data.e.isOk());
		pUser->Change_CurrTown(Data.tid,false);
		jNetClient_Call_ret(T2X_TOWN_SELECT_RESULT, Data);


	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(T2X_BUILD_UPGRADE_RESULT,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(T2X_BUILD_UPGRADE_RESULT);
		if(Data.e.isError())
		{
			S_T_ERROR pk;
			pk.e= Data.e;
			pk.msg = "build create error";
			pk.type=2;
			jNetClient_Call_ret(T_ERROR, pk);
			return;
		}
		Use_Hero* pHero = pUser->Hero_at(Data.hero_id);
		jAssert0(pHero);
		g_pNetClient->SetServerTime(Data.curr_server_time);
		nXML::jE eSlot = pUser->m_eCurrTown[jS(BUILD_SLOT_LIST)][Data.build_slot];
		eSlot.AttrP(jS(LEVEL)).T() = (int32)Data.level;
		EBuildType eType = (EBuildType)Data._EBuildType;
		eSlot.AttrP(jS(EBuildType)).T() = ToString(eType);
		fname_t szBuf;
		eSlot.AttrP(jS(EXEC_HERO_UID)).T() = ToString(pHero->Get_huid(),szBuf);
		pHero->Set_work_state(nAQ::eHWS_CONSTRUCTION);
		jTimeHelper th;
		th.Get_curr_time();
		time_t end_day = Data.curr_server_time + Data.upgrade_sec;//종료되는 서버시간.
		eSlot.AttrP(jS(UPGRADE_END_DAY)).T() = ToString(end_day,szBuf);
		jNetClient_Call_ret(T2X_BUILD_UPGRADE_RESULT, Data);

		{
			jTimeHelper th;
			th.m_t = g_pNetClient->GetServerTime();
			TCHAR szBuf[128];
			th.Get_diff_day_string(end_day,szBuf);
			eSlot->DebugPrint(true);
			GetjILog()->Log(_T("build slot left time: %s"),szBuf);

		}
	}
	
	
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(T2X_GOTO_CASTLE_MAP,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB_xml(T2X_GOTO_CASTLE_MAP,castle_map_info);
		pUser->m_eGPS = eGPS_CASTLE;
		if(pUser->m_eGPS_Cashe.full())
		{
			GetjIXml()->DeleteElement(pUser->m_eGPS_Cashe);
		}
		pUser->m_eGPS_Cashe = Data.castle_map_info;
		jNetClient_Call_ret(T2X_GOTO_CASTLE_MAP, Data);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(T2X_GOTO_WORLD_MAP,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB_xml(T2X_GOTO_WORLD_MAP,world_map_info);
		pUser->m_eGPS = eGPS_WORLD;
		if(pUser->m_eGPS_Cashe.full())
		{
			GetjIXml()->DeleteElement(pUser->m_eGPS_Cashe);
		}
		pUser->m_eGPS_Cashe = Data.world_map_info;
		jNetClient_Call_ret(T2X_GOTO_WORLD_MAP, Data);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(T2X_GOTO_TOWN_MAP,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(T2X_GOTO_TOWN_MAP);

		pUser->m_eGPS = eGPS_TOWN;
		jNetClient_Call_ret(T2X_GOTO_TOWN_MAP, Data);

	}

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(aaa,TownServer)
	{
		// Data, PlugIn_ToServer*pBE , B YTE buf_[1024] jDummyPlayer* pUser
		aq_READ_PACKET_P2P_PB(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToBackEnd)
