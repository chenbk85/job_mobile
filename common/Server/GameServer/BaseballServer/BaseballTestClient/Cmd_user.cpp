/* file : Cmd_Dummy.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-27 16:19:23
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "excel/code/excel_enum.h"


void JOB_ConsoleCmd(nEVENT::jIMessage*pMsg)
{
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(pMsg->GetArg(0)->Get_cstr());
}

namespace nCmdUser
{

	jCONSOLE_CMD_AUTO(user,login,0,"로긴테스트","<127.0.0.1:33100> <uid>")
	{
#define jCONSOLE_PARAM_login(X,Y) X(ip,tcstr) X(uid,tcstr) 
		jCONSOLE_PARAM_END(login);

		jRETURN_ret(false,g_pPlugIn);

		g_pPlugIn->CreateClient(ip,uid);
		return true;
	}

	jCONSOLE_CMD_AUTO(user,logout,0,"접속종료","<uid>")
	{
#define jCONSOLE_PARAM_logout(X,Y) X(uid,tcstr) 
		jCONSOLE_PARAM_END(logout);
		jFIND_USER(peSession,pUser,uid);

//		비정상 종료 시뮬레이션 하기위해 막음.
// 		if(pUser->m_eEUserGPS > eUGPS_UserGateServer)
// 		{
// 			pUser->m_eEUserGPS = eUGPS_GAMEROOM_PRE_LEAVE;
// 			fname_t szCmd;
// 			jt_sprintf(szCmd,"@game.UReqLeaveGame %s", uid);
// 			nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
// 
// 			//jWARN_T("게임서버에 붙어 있습니다. @user.game_quit <uid>로 게임서버를 나가세요.");
// 			return true;
// 		}
		g_pPlugIn->m_pCSM->Close(peSession);
		return true;
	}


	jCONSOLE_CMD_AUTO(user,req_GameInfo,0,"send req_GameInfo"
		,"<uid> <tbl_user>")
	{
#define jCONSOLE_PARAM_req_GameInfo(X,Y) X(uid,tcstr) X(szTable,acstr)
		jCONSOLE_PARAM_END(req_GameInfo);
		jFIND_USER(peSession,pUser,uid);

		astring sREQ = astring("GameInfo.") + szTable;

		if(ja_strcmp(szTable,"tbl_user")==0 )
		{
			pUser->m_GameUserInfo.mutable_game_info()->clear_m_tbl_user();
		}

		UReqProtocol sendMsg;
		sendMsg.set_type(UReqProtocol::UREQDB);
		ReqDB* sd = sendMsg.mutable_reqdb();
		static int32 iSeq=0;
		sd->set_seq(++iSeq);
		sd->set_query(sREQ);
		DBIn* param = sd->add_params();
		param->set_type(DBIn::INT);
		param->set_val("0");
		g_pPlugIn->send_to_ug(peSession, sendMsg);
		pUser->m_ServerInfoRecvState[sREQ]=0;


		return true;
	}

	jCONSOLE_CMD_AUTO(user,ug_echo,0,"UserGateServer echo test ","<uid> <msg> [data_repeat_count=1]")
	{
#define jCONSOLE_PARAM_ug_echo(X,Y) X(uid,tcstr) X(msg,tcstr) Y(data_repeat_count,int32,1)
		jCONSOLE_PARAM_END(ug_echo);
		jRETURN_ret(false,g_pPlugIn);
		jIE* peSession = g_pPlugIn->FindUser(uid);
		UReqProtocol sendMsg;
		sendMsg.set_type(UReqProtocol::UREQDB);
		ReqDB* sd = sendMsg.mutable_reqdb();
		static int32 iSeq=0;
		sd->set_seq(++iSeq);
		sd->set_query("ug_echo");
		DBIn* param = sd->add_params();
		param->set_type(DBIn::STR);
		tstring send_data = _T("");
		for(int i=0; i< data_repeat_count; ++i)
		{
			send_data +=msg;
		}
		param->set_val(jA(send_data));
		g_pPlugIn->send_to_ug(peSession, sendMsg);


		return true;
	}


	jCONSOLE_CMD_AUTO(user,x2ug_echo,0,"echo to ug server","<uid> <msg> [data_repeat_count=1]")
	{
#define jCONSOLE_PARAM_x2ug_echo(X,Y) X(uid,tcstr) X(msg,tcstr)  Y(data_repeat_count,int32,1)
		jCONSOLE_PARAM_END(x2ug_echo);
		jFIND_USER(peSession,pUser,uid);

		jMAKE_MESSAGE_X2UG(pUser,sendMsg, sd ,x2ug_echo);
		sd->set_type(333);

		tstring send_data = _T("");
		for(int i=0; i< data_repeat_count; ++i)
		{
			send_data +=msg;
		}
		sd->set_msg(jA(send_data));
		sd->set_client_time_msec(timeGetTime());
		g_pPlugIn->send_to_ug(peSession, sendMsg);
		return true;
	}

	jCONSOLE_CMD_AUTO(user,x2bs_echo,0,"echo to baseball server","<uid> <msg> [data_repeat_count=1]")
	{
#define jCONSOLE_PARAM_x2bs_echo(X,Y) X(uid,tcstr) X(msg,tcstr)  Y(data_repeat_count,int32,1)
		jCONSOLE_PARAM_END(x2bs_echo);
		jFIND_USER(peSession,pUser,uid);

		jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,x2bs_echo);
		tstring send_data = _T("");
		for(int i=0; i< data_repeat_count; ++i)
		{
			send_data +=msg;
		}
		sd->set_msg(jA(send_data));
		// sd->set_type(0);
		sd->set_type(100);
		sd->set_client_time_msec(timeGetTime());
		jLOG_USER(_T("%s x2bs_echo  Echo type = %d"), jFUNC, 100 );

		g_pPlugIn->send_to_bs(peSession,sendMsg);

		return true;
	}


	jCONSOLE_CMD_AUTO(user,print_info,0,"print_user_info","<uid>")
	{
#define jCONSOLE_PARAM_print_info(X,Y) X(uid,tcstr)
		jCONSOLE_PARAM_END(print_info);
		jFIND_USER(peSession,pUser,uid);

		jLOG_USER(_T("%s : game_id=%d, nic_name=%s ,gender=%d")
			, pUser->m_id.c_str() 
			, pUser->m_MemberInfo.game_id() 
			, pUser->m_MemberInfo.nick_name().c_str() 
			, pUser->m_MemberInfo.gender_option() ) ;
		nProtoHelper::message_print( *pUser->get_tbl_user());

		jLOG_USER(_T("%s= %d tbl_user"), pUser->size_tbl_user() );

		return true;
	}

#if 0
	jCONSOLE_CMD_AUTO(user,goto_menu,0,"goto_menu","<uid> <menu_window>")
	{
#define jCONSOLE_PARAM_goto_menu(X,Y) X(uid,tcstr) X(menu_window,tcstr)
		jCONSOLE_PARAM_END(goto_menu);
		jFIND_USER(peSession,pUser,uid);

#define send_goto_menu(MENU)\
		if(string(#MENU) == menu_window)\
		{\
			jMAKE_MESSAGE_X2UG(pUser,sendMsg,sd,MENU);\
			sd->Clear();\
			g_pPlugIn->send_to_ug(peSession,sendMsg);\
			return true;\
		}\

		for_each_menu_window(send_goto_menu);
		return true;
	}
#endif

	jCONSOLE_CMD_AUTO(user,UReqNotice,0,"UReqNotice","<uid>")
	{
#define jCONSOLE_PARAM_UReqNotice(X,Y) X(uid,tcstr)
		jCONSOLE_PARAM_END(UReqNotice);
		jFIND_USER(peSession,pUser,uid);

		UReqProtocol sendMsg;
		sendMsg.set_type(UReqProtocol::UREQNOTICE);

		UReqNotice* notice = sendMsg.mutable_reqnotice();

		g_pPlugIn->send_to_ug(peSession, sendMsg);
		//pUser->m_ServerInfoRecvState[sREQ]=0;

		return true;
	}
	


	jCONSOLE_CMD_AUTO(user,test_send_UReqConnect,0,"test_send_UReqConnect","<uid>")
	{
#define jCONSOLE_PARAM_test_send_UReqConnect(X,Y) X(uid,tcstr)
		jCONSOLE_PARAM_END(test_send_UReqConnect);
		jFIND_USER(peSession,pUser,uid);

		UReqProtocol sendMsg;
		sendMsg.set_type(UReqProtocol::UREQCONNECT);
		UReqConnect* sd = sendMsg.mutable_reqconnect();
		sd->set_svcid(0);
		sd->set_gameid(pUser->game_id);
		sd->set_lastclosetime(0);
		ug::Make(*sd->mutable_version() );
		ug::Make(*sd->mutable_memberinfo() , pUser->game_id ,"avartar_url_test", jA(pUser->m_id), true );
		g_pPlugIn->send_to_ug(peSession, sendMsg);
		return true;
	}


}//namespace nCmdUser

#if 0

jCONSOLE_CMD_AUTO(user,asdf,0,"asdf","<uid>")
{
#define jCONSOLE_PARAM_asdf(X,Y) X(uid,tcstr)
	jCONSOLE_PARAM_END(asdf);
	jFIND_USER(peSession,pUser,uid);

	jMAKE_MESSAGE_X2UG(pUser,sendMsg,sd,asdf);
	g_pPlugIn->send_to_ug(peSession,sendMsg);

	return true;
}

#endif

