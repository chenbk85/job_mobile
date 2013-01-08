/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "../AqCommon/define_code_jBE.h"
#include "base/jtimehelper.h"

jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(DC_HELLO,DBCacheServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		jSend_SS2server_ONLINE(DC);
		pBE->insert_DBCache(Data.sid,pS);
		pS->WritePacket(&WRITE_DC_ECHO(buf, (jS(asdf)),0));
		pBE->m_pDBSocket = pS;
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(DC_ERROR,DBCacheServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		jSend_ERROR_TO_CLIENT(DC,T);
	}

	Use_Town& find_town_by_tuid(vector<Use_Town>& towns,Use_Town_id_t tuid)
	{
		for(int i=0; i< towns.size() ; ++i)
		{
			if( tuid == towns[i].Get_tuid())
				return towns[i];
		}
		return towns.front();
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(DC2T_USER_LOGIN_CHANNEL_OK,DBCacheServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(DC2T_USER_LOGIN_CHANNEL_OK);
		jFE();
		jFE_GetUser(Data.uid); //AqClientUser* pUser
		S_T2X_USER_LOGIN_CHANNEL_OK pk;
		pk.user = pUser->m_User = Data.user;
		pk.town = pUser->m_Town = Data.town;
		nswb8000_t buf2;
		pUser->Write_Packet(WRITE_T2X_USER_LOGIN_CHANNEL_OK(buf2,pk));
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(DC2T_USER_LOGIN_CHANNEL_OK2,DBCacheServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(DC2T_USER_LOGIN_CHANNEL_OK2);
		jFE();
		jFE_GetUser(Data.uid); //AqClientUser* pUser
		S_T2X_USER_LOGIN_CHANNEL_OK2 pk;
		pk.hero = pUser->m_Hero = Data.hero;
		pk.force = pUser->m_Force = Data.force;
		nswb8000_t buf2;
		pUser->Write_Packet(WRITE_T2X_USER_LOGIN_CHANNEL_OK2(buf2,pk));

		assert(pUser->m_eUser_file_db.empty());
		{
			fname_t szDoc;
			bool isCreate = g_jAqCommon.Make_FileDBPath_By_Town_DBID(jT(pUser->m_szID), pUser->m_User.Get_uid(), szDoc);
			jID* pD = GetjIXml()->Load(szDoc);
			pUser->m_eUser_file_db = pD;
			if(isCreate)
			{
				pUser->m_eUser_file_db.AttrP(jS(USER)).T()= jT(pUser->m_User.Get_name());
				fname_t szUID;
				jt_sprintf(szUID , _T("%I64d") , pUser->m_User.Get_uid().m_db_id);
				pUser->m_eUser_file_db.AttrP(jS(UID)).T()= szUID;
				pUser->m_eUser_file_db[jS(Town_List)]->EraseChild();
				pD->Save();
			}
			else
			{
				pUser->m_eUser_file_db.Attr(jS(USER))->IsContents(jT(pUser->m_User.Get_name()));

			}
			S_T2X_USER_LOGIN_CHANNEL_OK3 pk;
			pk.town_xml = pD->BaseI();
			jTimeHelper th;
			j_time_t server_time;
			server_time.m_t = th.Get_curr_time();
			pk.server_time = server_time;
			pUser->Write_Packet(WRITE_T2X_USER_LOGIN_CHANNEL_OK3(buf,pk) );
		}
	}


	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(DC2T_NEW_TOWN_OK,DBCacheServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(DC2T_NEW_TOWN_OK);
		jFE();
		jFE_GetUser(Data.uid); //AqClientUser* pUser
		pUser->m_Town.push_back(Data.town);
		assert(pUser->m_Town.size() == Data.index);
		if(pUser->m_Town.size()==1)
		{// 弥檬 付阑 积己矫 固府 积己等 康旷狼 鸥款家加技泼.
			pUser->m_User.Set_capital_tuid(Data.town.Get_tuid());
			assert(pUser->m_Hero.size()==1);
			pUser->m_Hero[0].Set_tuid(Data.town.Get_tuid());
		}

		nXML::jE eNewTown = pUser->m_eUser_file_db(jS(Town_List))->InsertChildElement(jS(Town));
		fname_t szTUID;
		eNewTown.AttrP(jS(TUID)).T() = ToString(Data.town.Get_tuid() , szTUID );
		Test_UID(eNewTown.Attr(jS(TUID))->Get_cstr(), Data.town.Get_tuid());
		g_jXmlSaveManager.SaveDoc(pUser->m_eUser_file_db->GetDoc());

		pUser->Write_Packet(WRITE_T2X_NEW_TOWN_OK(buf, Data.index, Data.town) );
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(DC2T_TOWN_DELETE_OK,DBCacheServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(DC2T_TOWN_DELETE_OK);
		jFE();
		jFE_GetUser(Data.uid); //AqClientUser* pUser

		Use_Town* pTown = pUser->Town_at(Data.index);
		jIE* peTown = g_jAqCommon.FindTownBYTUID(pUser->m_eUser_file_db,pTown->Get_tuid() );
		if(!peTown)
		{
			tname1024_t szBuf;
			pUser->m_eUser_file_db->DebugPrint(true);
			GetjILog()->Warning(jFUNC1 _T("pUser->m_eUser_file_db : tuid not found : %s"),ToString(pTown->Get_tuid(),szBuf));
			GetjILog()->Warning(jFUNC1 _T("townname:%s"),pTown->Get_name());
		}
		else
			peTown->Erase();

		assert(Data.index >0 && Data.index <= pUser->m_Town.size() );
		pUser->m_Town.erase(pUser->m_Town.begin() + (Data.index - 1));
		
		pUser->Write_Packet(WRITE_T2X_TOWN_DELETE_OK(buf, Data.index));
		g_jXmlSaveManager.SaveDoc(pUser->m_eUser_file_db->GetDoc());
	}


#if 0


	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(aaa,DBCacheServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(aaa);
	}
#endif
}
jNET_EVENT_END(PlugIn_ToBackEnd)


