/* file : Recv_FromDQ.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-25 14:15:04
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"

#include "network/protocal/PT_WorldServer_Enum.h"
using namespace nMech::nNET::nWorldServer;
#include "network/protocal/PT_DBQueryServer_Enum.h"
using namespace nMech::nNET::nDBQueryServer;

#include "AqDBCacheUser.h"

#define READ_PACKET_DC(X) READ_PACKET(X);nswb1024_t buf;

#define READ_PACKET_DC_User(X) READ_PACKET(X);nswb1024_t buf;\
	AqDBCacheUser* pUser = g_Users_DC.find_by_yhandle(Data.uid);\
	jFE();\
	if(!pUser)\
	{\
		fname_t szBuf;\
		GetjILog()->Warning(jFUNC1 _T("user not found : %s"),ToString(Data.uid, szBuf));\
		return;\
	}\
	jBE();\




jDB_EVENT_RECEIVER(DQ2DC_CONNECT_OK) //BYTE* pReadBuff,dwLen
{
	READ_PACKET_DC(DQ2DC_CONNECT_OK);//Data ,buf
}


jDB_EVENT_RECEIVER(DQ_ECHO)//BYTE* pReadBuff,dwLen
{
	READ_PACKET_DC(DQ_ECHO);//Data ,buf
}

jDB_EVENT_RECEIVER(DQ_ERROR)//BYTE* pReadBuff,dwLen
{
	READ_PACKET_DC(DQ_ERROR);//Data ,buf
	//jTODO Front server로 바로 에러 메세지 보내던지 world로 에러보내서 일괄처리하던지 해야함.
	jGet_DBUser(Data.uid,pS); //AqDBCacheUser* pUser

	jBE();
	pBE->m_pToWorld->WritePacket(&WRITE_W_ERROR(buf, Data.e,Data.type,Data.msg ,Data.uid) );
}

jDB_EVENT_RECEIVER(DQ2DC_USER_LOGIN_RESULT)//BYTE* pReadBuff,dwLen
{
	READ_PACKET_DC_User(DQ2DC_USER_LOGIN_RESULT);//Data ,buf , AqDBCacheUser* pUser ,pFE
	if(Data.e.isError())
	{
		GetjILog()->Warning(jFUNC1 _T("error = %s"), Data.e.ToStringS());
		g_Users_DC.erase_now(Data.uid);
	}
	else
	{
		pUser->Setup_DBData();
		pUser->m_pjDBUserInfo->m_eUsingState = jUserZoneInfo_DC::eLOGIN_OK;
	}
	pBE->m_pToWorld->WritePacket(&WRITE_DC2W_USER_LOGIN_RESULT(buf, Data.e , pUser->Get_name(), Data.uid));
}

jDB_EVENT_RECEIVER(DQ2DC_SEND_TOWN_LIST)//BYTE* pReadBuff,dwLen
{
	READ_PACKET_DC_User(DQ2DC_SEND_TOWN_LIST);//Data ,buf , AqDBCacheUser* pUser ,pFE
	if(Data.e.isError())
	{
		pBE->m_pToWorld->WritePacket(&WRITE_DC2W_USER_LOGIN_CHANNEL_FAIL(buf, Data.uid,Data.e));
		return;
	}

#define user_table_packing654(table) vector<nAQ::Use_##table> _##table;	\
	for(int i= 0;i < pUser->GetDB()->m_iTot##table;++i){_##table.push_back(pUser->GetDB()->m_##table[i]);}\

	for_each_User_table(user_table_packing654);

	nswb16000_t buf2;
	pUser->m_pToTown->Write_Packet(WRITE_DC2T_USER_LOGIN_CHANNEL_OK(buf2,pUser->Get_uid(), pUser->GetDB()->m_User, _Town));
	pUser->m_pToTown->Write_Packet(WRITE_DC2T_USER_LOGIN_CHANNEL_OK2(buf2,pUser->Get_uid(), _Hero,_Force));

}



jDB_EVENT_RECEIVER(DQ2DC_TOWN_CREATE_OK)//BYTE* pReadBuff,dwLen
{
	READ_PACKET_DC_User(DQ2DC_TOWN_CREATE_OK);//Data ,buf , AqDBCacheUser* pUser ,pFE
	Use_Town* pTown= pUser->Town_at(Data.tid);
	bool isCapital= pUser->m_pjDBUserInfo->m_User.Get_capital_tuid()==0;
	if(isCapital)
	{
		// 최초 생성이다.
		pUser->m_pjDBUserInfo->m_User.Set_capital_tuid(pTown->Get_tuid());
	}
	pUser->m_pToTown->Write_Packet(WRITE_DC2T_NEW_TOWN_OK(buf
		, Data.uid
		, Data.tid
		, *pTown
		,isCapital
	));

}

jDB_EVENT_RECEIVER(DQ2DC_TOWN_DELETE_OK)//BYTE* pReadBuff,dwLen
{
	READ_PACKET_DC_User(DQ2DC_TOWN_DELETE_OK);//Data ,buf , AqDBCacheUser* pUser ,pFE
	nAQ::Use_Town* pTown = pUser->Town_at(Data.town_index);
	Sys_Castle_id_t csid = pTown->Get_castle_sid();
	Sys_TownPos_id_t tpsid = pTown->Get_townpos_sid();
	pUser->Town_erase(Data.town_index);
	pUser->m_pToTown->Write_Packet(WRITE_DC2T_TOWN_DELETE_OK(buf,Data.uid,Data.town_index));
	pBE->m_pToWorld->WritePacket(&WRITE_DC2W_TOWN_DELETE_OK(buf,pUser->m_pjDBUserInfo->m_User.Get_name() , csid, tpsid));
}





/* *_* by icandoit : 2009-08-25 22:05:10

jDB_EVENT_RECEIVER(aaa)//BYTE* pReadBuff,dwLen
{
	READ_PACKET_DC_User(aaa);//Data ,buf , AqDBCacheUser* pUser ,pFE
}

*/ //*_* by icandoit : 2009-08-25 22:05:11
