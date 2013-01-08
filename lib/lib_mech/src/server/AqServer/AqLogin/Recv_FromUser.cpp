/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"


jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(U_HELLO,UserServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		jSend_SS2server_ONLINE(U);

	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(U2L_USER_LOGIN_RESULT,UserServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(U2L_USER_LOGIN_RESULT);
		jFE();

		AqClientUser_L* pUser = pFE->find_if(jxFind_ByIDName(Data.id));
		if(!pUser)
		{
			GetjILog()->Warning(jFUNC1 _T("user not found : %s"), jT(Data.id));
			return;
		}

		pUser->m_uid = Data.uid;
		if(Data.e.isError())
		{
			pUser->Write_Packet(WRITE_L_ERROR(buf, Data.e,0,__FUNCTION__,userid_t()));
			return;
		}
		int sid = pUser->m_sid_world;
		jIE* pE = pBE->m_eServers->FindByFirstAttr(jS(m_sid) , jIVar::EDint , &sid);
		if(!pE)
		{
			GetjILog()->Warning(jFUNC1 _T("world server not found : sid(%d) id=(%s)"),sid,pUser->m_sName.c_str());
			pUser->Write_Packet(WRITE_L_ERROR(buf, jError(SR_t(WorldServer_is_not_found),CR_t(U2L_USER_LOGIN_RESULT)),0,__FUNCDNAME__,userid_t()));
			return;
		}
		cstr szWorld = pE->GetAttr(jS(m_szWorld));
		pE = pBE->m_eServers->Find(szWorld);
		if(!pE)
		{
			GetjILog()->Warning(jFUNC1 _T("world server root node not found : name =(%s)"),sid,szWorld);
			pUser->Write_Packet(WRITE_L_ERROR(buf, jError(SR_t(WorldServer_rootNode_not_found),CR_t(U2L_USER_LOGIN_RESULT))
				,0,__FUNCTION__, userid_t()) );
			return;
		}
#if 0 // 채널 서버 지원시
		//pE->DebugPrint(true);
		S_L2X_USER_LOGIN_OK pk;
		pk.uid= Data.uid;
		pE->for_each_child(jxGet_channel_list(pk.channel,pk.channel_name,pk.buzy_level));
		pUser->Write_Packet(WRITE_L2X_USER_LOGIN_OK(buf, pk));
#else

		#define jLAMDA_jxGet_free_townServer(X,Z) \
			X(int,totUser)\
			Z(serverid_t&,sid)
		jLAMDA_for_each(jxGet_free_townServer, jIE*)
		{
			nXML::jE e = it;
			int currTot = e.Attr(jS(m_iTotClient))->Get_int();
			if(totUser > currTot)
			{
				totUser = currTot;
				sid = e.Attr(jS(m_sid))->Get_int();
			}
		}
		jLAMDA_end();

		int free_totUser=INT_MAX;
		serverid_t free_sid=0;
		pE->for_each_child(jxGet_free_townServer(free_totUser,free_sid));

		if(sid==0)
		{
			jAssert0(0 && "에러처리 : jTODO : 가용 Town서버가 없음.");
		}

		jIE *peFreeServer = pBE->Find_Server(free_sid);
		uint16 port = peFreeServer->GetAttrVar(jS(m_service_port))->Get_int();
		pUser->Write_Packet(WRITE_L2X_CHANNEL_SELECT_RESULT(buf, jError(),jA(peFreeServer->GetAttr(jS(m_szServiceIP))),port,pUser->Get_uid()));

#endif
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(U2L_DO_USER_DISCONNECT,UserServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(U2L_DO_USER_DISCONNECT);
		jFE();
		for(int i=0; i< Data.uids.size() ; ++i)
		{
			pFE->DisconnectTcpClient(Data.uids[i]);
		}
	}


	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(aaa,UserServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(aaa);
	}
#endif
}
jNET_EVENT_END(PlugIn_ToBackEnd)


