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

	//X2LG_USER_EKEY를 클라이언트로부터 받았을때.
	jNET_EVENT_RECEIVER(L_ECHO)
	{
		READ_PACKET_FromClient(L_ECHO);
		pFE->send_all(WRITE_L_ECHO(buf,0,Data.msg),0);
	}
	
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2L_USER_LOGIN)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser_L* pUser
		READ_PACKET_FromClient(X2L_USER_LOGIN);
		ja_strcpy(pUser->m_szID , Data.id);
		pUser->m_sName = jT(Data.id);
		jBE();
		jIE* pE = pBE->Find_WorldServer(jT(Data.world));
		if(!pE)
		{
			pBE->m_eServers->DebugPrint(true);
			GetjILog()->Warning(jFUNC1 _T("world sid not found : %s"),jT(Data.world));
			return;
		}
		serverid_t sid = pE->GetAttrVar(jS(m_sid))->Get_int();
		pUser->m_sid_world = sid;
		if(pBE && pBE->m_pToUser)
			pBE->m_pToUser->WritePacket(&WRITE_L2U_USER_LOGIN(buf, sid, Data.id ) );
		else
		{
			pS_eSEND_jError_ToClient(L,SR_t(UserServer_is_hult),CR_t(X2L_USER_LOGIN));
		}
	}
	
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2L_GET_WORLD_LIST)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser_L* pUser
		READ_PACKET_FromClient(X2L_GET_WORLD_LIST);
		vector<jWorldServerInfo> out;
		jBE();
		/* *_* by icandoit : 2009-09-03 00:30:00
		//pBE->m_eServers->DebugPrint(true);
		<aqconnectedservernode  m_szName='ICANDOIT_83'  m_szWorld='LoginServer'  m_szSer
			viceIP='192.168.212.111'  m_service_port='33100'  m_iMaxClient='3000'  m_eType='
			LoginServer'  m_sid='2' >
			<aqconnectedservernode >
				<UserServer >
					<aqconnectedservernode  m_szName='ICANDOIT_78'  m_szWorld='UserServer'
					m_szServiceIP='192.168.212.111'  m_service_port='33003'  m_iMaxClient='50'  m_e
					Type='UserServer'  m_szIP='192.168.212.111'  m_sid='0'  m_iTotClient='0' >
					</aqconnectedservernode>
				</UserServer>
				<Fuzhou >
					<aqconnectedservernode  m_szName='ICANDOIT_82'  m_szWorld='Fuzhou'  m_s
					zServiceIP='192.168.212.111'  m_service_port='33001'  m_iMaxClient='50'  m_eType
					='DBCacheServer'  m_szIP='192.168.212.111'  m_sid='4'  m_iTotClient='0' >
					</aqconnectedservernode>
					<aqconnectedservernode  m_szName='ICANDOIT_81'  m_szWorld='Fuzhou'  m_s
					zServiceIP='192.168.212.111'  m_service_port='41246'  m_iMaxClient='3000'  m_eTy
					pe='TownServer'  m_szIP='192.168.212.111'  m_sid='3'  m_iTotClient='0' >
					</aqconnectedservernode>
					<aqconnectedservernode  m_szName='ICANDOIT_79'  m_szWorld='Fuzhou'  m_s
					zServiceIP='192.168.212.111'  m_service_port='33002'  m_iMaxClient='50'  m_eType
					='WorldServer'  m_szIP='192.168.212.111'  m_sid='1'  m_iTotClient='0' >
					</aqconnectedservernode>
				</Fuzhou>
				<LoginServer >
					<aqconnectedservernode  m_szName='ICANDOIT_83'  m_szWorld='LoginServer'
					m_szServiceIP='192.168.212.111'  m_service_port='33100'  m_iMaxClient='3000'
					m_eType='LoginServer'  m_szIP='192.168.212.111'  m_sid='2'  m_iTotClient='0' >
					</aqconnectedservernode>
				</LoginServer>
			</aqconnectedservernode>
		</aqconnectedservernode>
*/ //*_* by icandoit : 2009-09-03 00:29:54


		#define jLAMDA_jxGet_world_list(X,Z) \
			Z(vector<jWorldServerInfo>&,out)
		jLAMDA_for_each(jxGet_world_list, jIE*)
		{
			if(it->size()) return;
			cstr szType = it->GetAttr(jS(m_eType));
			if(!szType || jt_strcmp(szType,jS(WorldServer))) return;

			jWorldServerInfo w;
			ja_strcpy(w.szName,jA(it->GetAttr(jS(m_szWorld)) ) );
			w.iBusy = 0;
			out.push_back( w );
		}
		jLAMDA_end();

		pBE->m_eServers->for_each(jxGet_world_list(out));
		pUser->Write_Packet(WRITE_L2X_WORLD_LIST(buf, out));
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2L_GET_CHANNEL_LIST)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser_L* pUser
		READ_PACKET_FromClient(X2L_GET_CHANNEL_LIST);
		jBE();
		S_L2X_CHANNEL_LIST pk;
		jIE* pE = pBE->m_eServers->Find(jT(Data.world));
		if(!pE)
		{
			tname1024_t szBuf;
			GetjILog()->Warning(jFUNC1 _T("world(%s) not found")  , jT(Data.world) , ToString(pUser,szBuf) );
			pFE->DisconnectTcpClient(pUser);
			return;
		}

		pE->for_each_child(jxGet_channel_list(pk.channel,pk.channel_name,pk.buzy_level));
		pUser->Write_Packet(WRITE_L2X_CHANNEL_LIST(buf, pk));
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2L_CHANNEL_SELECT)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser_L* pUser
		READ_PACKET_FromClient(X2L_CHANNEL_SELECT);
		jBE();
		jIE *pE = pBE->Find_Server(Data.sid);
		if(!pE)
		{
			tname_t szIP;
			GetjILog()->Warning(jFUNC1 _T("Channel server is not found : %d , user=(%s,%s)"),Data.sid, jT(pUser->m_szID), pS->GetIP(szIP));
			pFE->DisconnectTcpClient(pUser);
			return;
		}

		uint16 port = pE->GetAttrVar(jS(m_service_port))->Get_int();
		pS->WritePacket(&WRITE_L2X_CHANNEL_SELECT_RESULT(buf, jError(),jA(pE->GetAttr(jS(m_szServiceIP))),port,pUser->Get_uid()));
	}

	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqClientUser_L* pUser
		READ_PACKET_FromClient(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)




