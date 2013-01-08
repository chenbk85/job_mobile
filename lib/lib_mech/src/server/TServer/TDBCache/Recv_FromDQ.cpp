/* file : Recv_FromDQ.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-25 14:15:04
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TDBCache.h"
#include "jPlayerObj.h"

#define READ_PACKET_fromDQ(X) READ_PACKET(X);nswb1024_t buf;

#define READ_PACKET_fromDQ_User(X) READ_PACKET(X);nswb1024_t buf;\
	jPlayerObj* pUser = (jPlayerObj*)g_PL.find(Data.pid);\
	if(!pUser){tname1024_t szBuf;jERROR("user not found : %s",ToString(Data.pid, szBuf); return;}\


jDB_EVENT_RECEIVER(DQ2DC_CONNECT) //BYTE* pReadBuff,dwLen
{
	READ_PACKET_fromDQ(DQ2DC_CONNECT);//Data ,buf
	pDQ->m_ProcessID = Data.processid;
	jNET_SEND(pDQ,DC2DQ_CONNECT_OK,jError(0,0),(uint32)GetCurrentProcessId());
}


jDB_EVENT_RECEIVER(DQ2DC_CONNECT_OK) //BYTE* pReadBuff,dwLen
{
	READ_PACKET_fromDQ(DQ2DC_CONNECT_OK);//Data ,buf
	pDQ->m_ProcessID = Data.processid;
}


jDB_EVENT_RECEIVER(DQ_ECHO)//BYTE* pReadBuff,dwLen
{
	READ_PACKET_fromDQ(DQ_ECHO);//Data ,buf
}

jDB_EVENT_RECEIVER(DQ_ERROR)//BYTE* pReadBuff,dwLen
{
	READ_PACKET_fromDQ(DQ_ERROR);//Data ,buf
	jPlayerObj* pUser = (jPlayerObj*)g_PL.find(Data.ei.pid);
	if(!pUser){tname1024_t szBuf;jERROR("user not found : %s",ToString(Data.ei.pid, szBuf)); return;}

	switch(Data.ei.eAction)
	{
	case eEAT_SKIP:
		return ;
	case eEAT_NOTIFY_TO_CLIENT:
	case eEAT_NOTIFY_ALL_CLIENT:
		{
			g_SG.SEND_PACKET_SID(pUser->Get_Server(eChannel), DC_ERROR,Data.ei);
			g_SG.SEND_PACKET_SID(pUser->Get_Server(eGame), DC_ERROR,Data.ei);
			g_SG.SEND_PACKET_SID(pUser->Get_Server(eWorld), W_ERROR,Data.ei);
			break;
		}
	case eEAT_NOTIFY_AND_DISCON_USER:
	case eEAT_DISCON_USER :
		{
			g_SG.SEND_PACKET_SID(pUser->Get_Server(eChannel), DC_ERROR,Data.ei);
			g_SG.SEND_PACKET_SID(pUser->Get_Server(eGame), DC_ERROR,Data.ei);
			g_SG.SEND_PACKET_SID(pUser->Get_Server(eWorld), W_ERROR,Data.ei);
			// jTODO DQ에서 메모리상의 값들 db에 save후 종료되어있는지 확인할것.
			g_PL.erase(Data.ei.pid);
			return;
		}
	}
}

jDB_EVENT_RECEIVER(DQ2DC_USER_LOGIN_RESULT)//BYTE* pReadBuff,dwLen
{
	READ_PACKET_fromDQ(DQ2DC_USER_LOGIN_RESULT);//Data ,buf , pPS
	jPlayerObj* pUser = (jPlayerObj*)g_PL.find(Data.pid);
	if(!pUser){tname1024_t szBuf;jERROR("user not found : %s",ToString(Data.pid,szBuf)); return;}

	if(Data.e.isError())
	{
		jWARN("error = %s", Data.e.ToStringS());
		g_PL.erase(Data.pid);
	}
	else
	{
		pUser->GetDB()->m_eUsingState = jPlayerDBSM::eLOGIN_OK;
	}
	jNET_SEND2(g_SG.m_World,DC2W_USER_LOGIN_RESULT, Data.e , pUser->m_szID, Data.pid );
}


#ifdef TSREVER_PREPARE
jDB_EVENT_RECEIVER(DQ2DC_SEND_TOWN_LIST)//BYTE* pReadBuff,dwLen
{
	READ_PACKET_fromDQ_User(DQ2DC_SEND_TOWN_LIST);//Data ,buf , jPlayerObj* pUser ,pPS
	if(Data.e.isError())
	{
		pPC->m_pToWorld->WritePacket(&WRITE_DC2W_USER_LOGIN_CHANNEL_FAIL(buf, Data.pid,Data.e));
		return;
	}

#define user_table_packing654(table) vector<nAQ::Use_##table> _##table;	\
	for(int i= 0;i < pUser->GetDB()->m_iTot##table;++i){_##table.push_back(pUser->GetDB()->m_##table[i]);}\

	for_each_User_table(user_table_packing654);

	nswb16000_t buf2;
	pUser->m_pToChannel->Write_Packet(WRITE_DC2T_USER_LOGIN_CHANNEL_OK(buf2,pUser->Get_uid(), pUser->GetDB()->m_User, _Channel));
	pUser->m_pToChannel->Write_Packet(WRITE_DC2T_USER_LOGIN_CHANNEL_OK2(buf2,pUser->Get_uid(), _Hero,_Force));

}




jDB_EVENT_RECEIVER(DQ2DC_TOWN_CREATE_OK)//BYTE* pReadBuff,dwLen
{
	READ_PACKET_fromDQ_User(DQ2DC_TOWN_CREATE_OK);//Data ,buf , jPlayerObj* pUser ,pPS
	Use_Channel* pChannel= pUser->Channel_at(Data.channelNo);
	bool isCapital= pUser->m_SharedMemory->m_User.Get_capital_tuid()==0;
	if(isCapital)
	{
		// 최초 생성이다.
		pUser->m_SharedMemory->m_User.Set_capital_tuid(pChannel->Get_tuid());
	}
	pUser->m_pToChannel->Write_Packet(WRITE_DC2T_NEW_TOWN_OK(buf
		, Data.pid
		, Data.channelNo
		, *pChannel
		,isCapital
	));

}

jDB_EVENT_RECEIVER(DQ2DC_TOWN_DELETE_OK)//BYTE* pReadBuff,dwLen
{
	READ_PACKET_fromDQ_User(DQ2DC_TOWN_DELETE_OK);//Data ,buf , jPlayerObj* pUser ,pPS
	nAQ::Use_Channel* pChannel = pUser->Channel_at(Data.channel_index);
	Sys_Castle_id_t csid = pChannel->Get_castle_sid();
	Sys_TownPos_id_t tpsid = pChannel->Get_channelpos_sid();
	pUser->Channel_erase(Data.channel_index);
	pUser->m_pToChannel->Write_Packet(WRITE_DC2T_TOWN_DELETE_OK(buf,Data.pid,Data.channel_index));
	pPC->m_pToWorld->WritePacket(&WRITE_DC2W_TOWN_DELETE_OK(buf,pUser->m_SharedMemory->m_User.Get_name() , csid, tpsid));
}

#endif //TSREVER_PREPARE


/* *_* by icandoit : 2009-08-25 22:05:10

jDB_EVENT_RECEIVER(aaa)//BYTE* pReadBuff,dwLen
{
	READ_PACKET_fromDQ_User(aaa);//Data ,buf , jPlayerObj* pUser ,pPS
}

*/ //*_* by icandoit : 2009-08-25 22:05:11
