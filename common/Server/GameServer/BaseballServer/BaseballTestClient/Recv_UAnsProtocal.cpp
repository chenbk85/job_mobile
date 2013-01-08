/* file : Recv_TestServer.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-28 17:05:50
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TestClient.h"



jRECV_UAnsProtoca(UAnsConnect, PlugIn_BaseballClient* pPlugIn,jIE* peSession,jUser* pUser, UAnsConnect &rd)
{
	pUser->m_UAnsConnect = rd;

	UReqProtocol sendMsg;
	sendMsg.set_type(UReqProtocol::UREQINFO);
	UReqInfo* sd = sendMsg.mutable_reqinfo();
	{

	}
	pPlugIn->send_to_ug(peSession, sendMsg);
	return true; 
}



jRECV_UAnsProtoca(AnsDB		,PlugIn_BaseballClient* pPlugIn,jIE* peSession,jUser* pUser, AnsDB &rd) 
{
	int32 next_index = rd.retcode();
	if(next_index==19999)
	{
		jWARN_T("SERVER ERROR next_index=%d",next_index);
		return true;
	}
	acstr szQuery = rd.query().c_str();
	rd.result();

	if(!ja_strcmp(szQuery,"ug_game"))
	{
		UserGateServer_Client recvMsg;
		recvMsg.ParseFromString(rd.result());
		switch(recvMsg.type())
		{

#define parse_UserGateServer_Client(DOMAIN,NAME,ORDER) \
		case UserGateServer_Client_Type_##NAME:\
			{\
				jLOG_USER_T("recv : %s",#NAME);\
				bool On_UserGateServer_Client(RECV_PARAM_PlugIn_BaseballClient,const s_##NAME& rd);\
				return On_UserGateServer_Client(pPlugIn,peSession,pUser,recvMsg.m_##NAME() );\
			}\

			for_each_UserGateServer_Client(parse_UserGateServer_Client);

		default:
			{
				jWARN_T("unkown packet %d", recvMsg.type());
			}
		}
		return true;
	}

	if(ja_strstr(szQuery,"ug_echo"))
	{

		jLOG(_T("ug_echo : %s"), rd.result().c_str());
		return true;
	}

	if(ja_strstr(szQuery,"GameInfo"))
	{
		if(next_index ==10000)
		{
			return true;// repeatable 변수는 맨마지막일때 9999가 날라옴.를 보냄.
		}

#define parse_GameInfo(TABLE,EXCEL_TABLE,SELECT_FIELD)\
	if(ja_strstr(szQuery ,#TABLE ) )\
		{\
		s_##TABLE* p= pUser->m_GameUserInfo.mutable_game_info()->add_m_##TABLE();\
		p->ParseFromString(rd.result());\
		/*jLOG_USER_T("recv : %s",#TABLE);*/\
		/*nProtoHelper::message_print(*p);*/\
	}\

		for_each_GameInfo_Excel_Table(parse_GameInfo);

		++pUser->m_recv_table_count[szQuery];

		pUser->m_ServerInfoRecvState[szQuery]=next_index;

		if(next_index ==9999)
		{
			//pUser->OnServerInfoRecvEnd(szQuery);
			if(pv_IsAutoPlay->Get_bool()) //pv_IsAutoPlay is defined in stdafx.h ( Search by IsAutoPlay )
			{
				//[AutoPlay] Init
				pUser->m_iAutoReJoinCount = pv_AutoReJoinCount->Get_int();
				pUser->m_iAutoMatchCount = pv_AutoMatchCount->Get_int();

				fname_t szCmd;
				jt_sprintf(szCmd,_T("@game.match_auto_join_team %I64d"),pUser->db_id());
				nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
			}
			else
			{
				jLOG_USER_T("recv end : %s=%d",jT(szQuery) , pUser->m_recv_table_count[szQuery]);
			}
			return true;// repeatable 변수는 맨마지막일때 9999가 날라옴.를 보냄.
		}

		UReqProtocol sendMsg;
		sendMsg.set_type(UReqProtocol::UREQDB);
		ReqDB* sd = sendMsg.mutable_reqdb();
		sd->set_seq(rd.seq()+1);
		sd->set_query(szQuery);
		DBIn* param = sd->add_params();
		param->set_type(DBIn::INT);
		afname_t szIndex;
		sprintf(szIndex,"%d",next_index);
		param->set_val(szIndex);
		pPlugIn->send_to_ug(peSession, sendMsg);

	}

	return true; 
}

jRECV_UAnsProtoca(UAnsChannel, PlugIn_BaseballClient* pPlugIn,jIE* peSession,jUser* pUser, UAnsChannel &rd)
{
	
	return true; 
}
jRECV_UAnsProtoca(UAnsStore	,PlugIn_BaseballClient* pPlugIn,jIE* peSession,jUser* pUser, UAnsStore &rd)
{
	
	return true; 
}
jRECV_UAnsProtoca(UAnsInfo	,PlugIn_BaseballClient* pPlugIn,jIE* peSession,jUser* pUser, UAnsInfo &rd) 
{
	pUser->m_UAnsInfo = rd;

	fname_t szCmd;

	pUser->m_recv_table_count.clear();
#	define clear_count_GameInfo_3432(TABLE,EXCEL_TABLE,SELECT_FIELD) pUser->m_recv_table_count[#TABLE]=0;
	for_each_GameInfo_Excel_Table(clear_count_GameInfo_3432);

#	define req_gameinfo_3432(TABLE,EXCEL_TABLE,SELECT_FIELD)\
	jt_sprintf(szCmd,_T("@user.req_GameInfo %s %s"),pUser->m_id.c_str() , jS(TABLE));\
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);\

	for_each_GameInfo_Excel_Table(req_gameinfo_3432);

	return true; 
}

jRECV_UAnsProtoca(UAnsAutoJoin ,PlugIn_BaseballClient* pPlugIn,jIE* peSession,jUser* pUser, UAnsAutoJoin &rd) 
{
	// 매치 성공했다. 이제부터는 pPlugIn->send_to_bs()를 사용해 게임서버와 통신가능.
	pUser->m_eEUserGPS = eUGPS_GAMEROOM;
	pUser->m_GameRoomInfo.ParseFromString(rd.gameroominfo());
	if(pUser->IsAutoPlay())
	{
		fname_t szCmd;
		jt_sprintf(szCmd,_T("@game.x2bs_auto_match_ready2 %I64d"),pUser->db_id());
		nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
	}
	else
		nProtoHelper::message_print(pUser->m_GameRoomInfo);
	return true; 
}
jRECV_UAnsProtoca(UAnsLeaveGame,PlugIn_BaseballClient* pPlugIn,jIE* peSession,jUser* pUser, UAnsLeaveGame &rd) 
{
	pUser->m_eEUserGPS = eUGPS_x2ug_goto_main;
	jLOG_USER_T("UAnsLeaveGame KICK_TYPE=%d" ,rd.ntype() );
	if(pv_IsAutoPlay->Get_bool() && !pUser->IsAutoPlayError())//자동플레이상태에서 정상적으로 게임방을 나왔다면.
	{
		if(pUser->m_iAutoReJoinCount>0)
		{
			--pUser->m_iAutoReJoinCount;
			pUser->m_iAutoMatchCount = pv_AutoMatchCount->Get_int();
			fname_t szCmd;
			jt_sprintf(szCmd,_T("@game.match_auto_join_team %I64d"),pUser->db_id());
			nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
		}
		else
		{
			fname_t szCmd;
			jt_sprintf(szCmd,_T("@user.logout %I64d"),pUser->db_id());
			nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
		}
	}


	return true; 
}
jRECV_UAnsProtoca(UAnsClose	,PlugIn_BaseballClient* pPlugIn,jIE* peSession,jUser* pUser, UAnsClose &rd) 
{
	
	return true; 
}
jRECV_UAnsProtoca(UAnsPing	,PlugIn_BaseballClient* pPlugIn,jIE* peSession,jUser* pUser, UAnsPing &rd) 
{
	UReqProtocol sendMsg;
	sendMsg.set_type(UReqProtocol::UREQPONG);
	UReqPong* sd = sendMsg.mutable_reqpong();
	sd->set_seq(rd.seq());
	pPlugIn->send_to_ug(peSession, sendMsg);
	return true; 
}
jRECV_UAnsProtoca(UAnsPlug	,PlugIn_BaseballClient* pPlugIn,jIE* peSession,jUser* pUser, UAnsPlug &rd) 
{
	
	return true; 
}

jRECV_UAnsProtoca(UAnsNotice,PlugIn_BaseballClient* pPlugIn,jIE* peSession,jUser* pUser, UAnsNotice &rd) 
{

	for( int i=0; i < rd.notices_size(); ++i )
	{
		jLOG( _T("popup : %d,  srl : %d, notice : %s"), rd.notices(i).popup(), rd.notices(i).srl(), rd.notices(i).notice().c_str() );
	}
	
	return true; 
}
jRECV_UAnsProtoca(UError	,PlugIn_BaseballClient* pPlugIn,jIE* peSession,jUser* pUser, UError &rd) 
{
	jWARN_T("error = (%d ,%s, %s)", rd.error().errorcode() ,rd.error().errorinfo().c_str(), rd.error().reqmode());
	return true; 
}



/*

템플릿 코드 

jRECV_UAnsProtoca(asdf ,PlugIn_BaseballClient* pPlugIn,jIE* peSession,jUser* pUser, s_asdf rd) 
{
	
	return true; 
}

*/

