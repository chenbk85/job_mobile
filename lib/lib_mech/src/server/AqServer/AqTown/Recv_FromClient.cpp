/* file : Recv_FromClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:56:07
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"


jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(T_ECHO)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser* pUser
		READ_PACKET_FromClient(T_ECHO);
		pFE->send_all(WRITE_T_ECHO(buf, Data.msg, Data.type),0);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2T_CHAT)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser* pUser
		READ_PACKET_FromClient(X2T_CHAT);
		pFE->send_all(WRITE_T2X_CHAT(buf, Data.msg, Data.type),0);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2T_USER_LOGIN_CHANNEL)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser* pUser
		READ_PACKET_FromClient(X2T_USER_LOGIN_CHANNEL);
		pUser->m_uid = Data.uid;
		ja_strcpy( pUser->m_szID , Data.id);
		jBE();
		pBE->m_pToWorld->WritePacket(&WRITE_T2W_USER_LOGIN_CHANNEL(buf, Data.uid , Data.id));
		pBE->Set_U4_USER_CONNECTION_NOTIFY_CS(Data.uid,Data.id,true);
		//pBE->test_dc_echo();
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2T_TOWN_SELECT)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser* pUser
		READ_PACKET_FromClient(X2T_TOWN_SELECT);
		pUser_Check_townid(Data.index,T,userid_t());

		jBE();
		jBE_GetUserDBCache(pUser->Get_uid()); //jIPacketSocket_IOCP* pS_DB; 

		pUser->Change_CurrTown(Data.index);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2T_TOWN_DELETE)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser* pUser
		READ_PACKET_FromClient(X2T_TOWN_DELETE);
		pUser_Check_townid(Data.index,T,userid_t());
		if(pUser->m_Town.size()<=1)
		{
			pS_eSEND_jError_ToClient(T , SR_t(CANT_DEL_ALL_TOWN),CR_t(X2T_TOWN_DELETE));
			return;
		}
		jBE();
		jBE_GetUserDBCache(pUser->Get_uid()); //jIPacketSocket_IOCP* pS_DB;
		pS_DB->WritePacket(&WRITE_T2DC_TOWN_DELETE(buf, pUser->Get_uid() , Data.index));
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2T_NEW_TOWN)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser* pUser
		READ_PACKET_FromClient(X2T_NEW_TOWN);

		if(pUser->m_Town.size() > (iMAX_USER_Town-1))
		{
			//허용 아바타 갯수 초가
			pS_eSEND_jError_ToClient(T , SR_t(TOWN_NUM_IS_OVER),CR_t(X2T_TOWN_CREATE));
			return;
		}

		pUser_Check_make_name(Data.name);

		jBE();
		pBE->m_pToWorld->WritePacket(&WRITE_T2W_NEW_TOWN(buf,pUser->Get_uid(),Data.csid,Data.tpsid,Data.name));
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2T_NEW_BUILD)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser* pUser
		READ_PACKET_FromClient(X2T_NEW_BUILD);
		fname_t szBuf1;
		nAQ::EBuildType eType = (nAQ::EBuildType)Data._EBuildType;
		nXML::jE eBList = pUser->m_eCurrTown[jS(BUILD_SLOT_LIST)];
		nXML::jE eSlot = eBList(Data.build_slot);
		jUSER_ERROR_CHECK(eSlot.full(),X2T_NEW_BUILD,SLOT_IS_USE);
		Use_Hero* pHero = pUser->Hero_at(Data.hero_id);
		jUSER_ERROR_CHECK(!pHero,X2T_NEW_BUILD,HERO_ID_ERROR);
		jUSER_ERROR_CHECK(pHero->Get_work_state()!=nAQ::eHWS_REST,X2T_NEW_BUILD,HERO_STATE_IS_NOT_REST);
		
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
				std::pair<time_t,int32> CheckUpgrade_##table(Use_User&u,Use_Town* pT,nXML::jE eSlot,Use_Hero*pH);\
				upgrade_sec = CheckUpgrade_##table(pUser->m_User,pUser->GetCurrTown(),eSlot,pHero);\
			}
			for_each_EBuildType_Impl(CheckUpgrade_Sys_T_Bar2344)
			else
			{
				throw jError(SR_t(X2T_NEW_BUILD),CR_t(_EBuildType_IS_UNKOWN));
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

		pS->WritePacket(&WRITE_T2X_BUILD_UPGRADE_RESULT(buf
			,Data.build_slot,Data._EBuildType,level,e,curr_server_time,upgrade_sec.second
			,Data.hero_id));
	}


	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2T_GOTO_CASTLE_MAP)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser* pUser
		READ_PACKET_FromClient(X2T_GOTO_CASTLE_MAP);

		jAssert0(pUser->m_iCurrTown==Data.tid);
		switch(pUser->m_eGPS)
		{
		case eGPS_CASTLE:
			{
				GetjILog()->Warning(jFUNC1 _T("if(pUser->m_eGPS == eGPS_CASTLE) : %s"),jT(pUser->m_User.Get_name()));
				return;
			}
			break;
		case eGPS_TOWN:
			{

			}
			break;
		case eGPS_WORLD:
			{
				//pFE->Get_WorldInfo()[jS(Force)]
			}
			break;
		}

		pUser->m_eGPS == eGPS_CASTLE;
		Use_Town* pTown = pUser->GetCurrTown();
		nXML::jE eCastle = pFE->Get_CastleInfo(pTown->Get_castle_sid());
		S_T2X_GOTO_CASTLE_MAP pk;
		pk.tid = Data.tid;
		pk.castle_map_info = eCastle;
		pUser->WritePacket(&WRITE_T2X_GOTO_CASTLE_MAP(buf,pk) );
	}



	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2T_GOTO_WORLD_MAP)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser* pUser
		READ_PACKET_FromClient(X2T_GOTO_WORLD_MAP);

		jAssert0(pUser->m_iCurrTown==Data.tid);
		switch(pUser->m_eGPS)
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
				GetjILog()->Warning(jFUNC1 _T("if(pUser->m_eGPS == eGPS_WORLD) : %s"), jT(pUser->m_User.Get_name()) );
				return;
			}
			break;
		}

		pUser->m_eGPS == eGPS_WORLD;
		nXML::jE eWorld = pFE->Get_WorldInfo();
		S_T2X_GOTO_WORLD_MAP pk;
		pk.tid = Data.tid;
		pk.world_map_info = eWorld;
		pUser->WritePacket(&WRITE_T2X_GOTO_WORLD_MAP(buf,pk) );
	}



	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2T_GOTO_TOWN_MAP)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser* pUser
		READ_PACKET_FromClient(X2T_GOTO_TOWN_MAP);

		jAssert0(pUser->m_iCurrTown==Data.tid);
		switch(pUser->m_eGPS)
		{
		case eGPS_CASTLE:
			{
			}
			break;
		case eGPS_TOWN:
			{
				GetjILog()->Warning(jFUNC1 _T("if(pUser->m_eGPS == eGPS_TOWN) : %s"), jT(pUser->m_User.Get_name()) );
				return;
			}
			break;
		case eGPS_WORLD:
			{
			}
			break;
		}

		pUser->m_eGPS == eGPS_TOWN;
		pUser->WritePacket(&WRITE_T2X_GOTO_TOWN_MAP(buf,Data.tid) );
	}



	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser* pUser
		READ_PACKET_FromClient(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)
