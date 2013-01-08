/* file : PlugIn_BaseballClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:13
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TestClient.h"
#include "PlugIn_BaseballClient.h"

PlugIn_BaseballClient* g_pPlugIn=0;


jIE* g_peCurrSession=0;

jLIST_TYPEDEF_map(jIE*,jUser,g_Users);
nUtil::jCriticalSection g_Users_CS;


jDEFINE_RTTIOBJ_BY_SCOPE(PlugIn_BaseballClient,jNet, 1,1);


jSQ_REGIST_BIND(PLUGIN)
{
	jSQ_Interface(PlugIn_BaseballClient)
		jSQ_end();

	//jSQ_g_var(&g_TestInfo,g_TestInfo);
}


void PlugIn_BaseballClient::OnStartup()
{
	m_pMM=0;
	jLOG(jFUNC);
	g_pPlugIn=this;
	nCONSOLE::Get_jIConsoleCmd()->Run(_T("con"),_T("message"),_T("tcp_mode"),true ,0);
	nCONSOLE::Get_jIConsoleCmd()->Run(_T("con"),_T("message_txt"),_T("\"default : to test server\n\r* chat : to game server\""),true ,0);

}
void PlugIn_BaseballClient::OnStop()
{
	jLOG(jFUNC);
	if(g_pPlugIn==this)
		g_pPlugIn=0;
}


//#--------------------------------------------------------------------------
bool PlugIn_BaseballClient::OnConnect(jIE* peSession)
//#--------------------------------------------------------------------------
{
	if(!g_peCurrSession) g_peCurrSession=peSession;
	jLOG(jFUNC1 _T("%s"), peSession->GetTagName());


	if(!jt_strstr(peSession->GetTagName(), jS(TCP_BaseballServer))) return true;


	jAUTO_LOCK_CS(g_Users_CS);
	jUser* pUser=&g_Users[peSession];
	pUser->m_peSession = peSession;
	pUser->m_id = peSession->GetAttr(jS(id));
	pUser->game_id=jt_atoi64(pUser->m_id.c_str());

	UReqProtocol sendMsg;
	sendMsg.set_type(UReqProtocol::UREQCONNECT);
	UReqConnect* sd = sendMsg.mutable_reqconnect();
	sd->set_svcid(0);
	sd->set_gameid(pUser->game_id);
	sd->set_lastclosetime(0);
	ug::Make(*sd->mutable_version() );
	ug::Make(*sd->mutable_memberinfo() , pUser->game_id ,"avartar_url_test", jA(pUser->m_id), true );
	pUser->m_MemberInfo.CopyFrom(sd->memberinfo());
	pUser->m_eEUserGPS = eUGPS_LOGIN;

	//[AutoPlay] Init
	pUser->Init_AutoReConnectCount(pv_AutoReConnectCount->Get_int());
	jLOG(_T("pUser->Set_AutoReConnectCount = %d"),pUser->Get_AutoReConnectCount());

	this->send_to_ug(peSession, sendMsg);

	return true;
}

//#--------------------------------------------------------------------------
void PlugIn_BaseballClient::OnDisconnect(jIE* peSession)
//#--------------------------------------------------------------------------
{
	if(g_peCurrSession==peSession)
		g_peCurrSession=0;
	jLOG(jFUNC1 _T("%s"),peSession->GetTagName());
	jAUTO_LOCK_CS(g_Users_CS);
	jRETURN(g_Users.count(peSession));	
	jUser* pUser= &g_Users[peSession];
	int iCount = pUser->Get_AutoReConnectCount();
	jLOG(_T("pUser->Get_AutoReConnectCount() = %d"),iCount);

	if(pv_IsAutoPlay->Get_bool())
	{
		if(iCount>0)
		{
			--iCount;
			pUser->Set_AutoReConnectCount(iCount);
			fname_t szCmd;
			jt_sprintf(szCmd,_T("@user.login %s %I64d"),peSession->Get_cstr() , pUser->db_id());
			nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd,pv_AutoReConnectWaitTime->Get_float());
		}
	}
	g_Users.erase(peSession);
}

//#--------------------------------------------------------------------------
bool PlugIn_BaseballClient::OnRead(jIE* peSession,char* pRecvBuff,int iReadLen)
//#--------------------------------------------------------------------------
{
	google::protobuf::io::ArrayInputStream ais(pRecvBuff, iReadLen);
	UAnsProtocol r;
	r.ParseFromZeroCopyStream(&ais);

	jAUTO_LOCK_CS(g_Users_CS);
	jvRETURN_ret(false, g_Users.count(peSession) ,_T("r.type= %s ") , r.GetTypeName().c_str() );	
	jUser& user= g_Users[peSession];


	if(r.type()==UAnsProtocol_Type_UANSGATEWAYPROTOCOL)
	{
		UserGateServer_Client recvMsg;
		recvMsg.ParseFromString(r.ansgatewayprotocol());
		switch(recvMsg.type())
		{

#define parse_UserGateServer_Client(DOMAIN,NAME,ORDER) \
		case UserGateServer_Client_Type_##NAME:\
			{\
			jLOG(_T("recv(%s) : %s"),user.m_id.c_str(),#NAME);\
			bool On_UserGateServer_Client(RECV_PARAM_PlugIn_BaseballClient,const s_##NAME& rd);\
			return On_UserGateServer_Client(this,peSession,&user,recvMsg.m_##NAME() );\
		}\

		for_each_UserGateServer_Client(parse_UserGateServer_Client);

		default:
			{
				jWARN(_T("unkown packet %d"), recvMsg.type());
			}
		}
	}
	else if(r.type()==UAnsProtocol_Type_GLANSGAMEPROTOCOL)
	{
		BaseballServer_Client r2;
		r2.ParseFromString(r.ansgameprotocol());

#		define switch_BaseballServer_Client(DOMAIN,NAME,ORDER)\
		if(r2.type() == BaseballServer_Client_Type_##NAME ) \
		{\
			jLOG(jFUNC1 _T("%s:%s") , user.m_id.c_str(), jS(NAME) );\
			bool On_BaseballServer_Client_##NAME(RECV_PARAM_PlugIn_BaseballClient,const s_##NAME& rd);\
			return On_BaseballServer_Client_##NAME(this,peSession,&user,r2.m_##NAME() );\
		}\

		for_each_BaseballServer_Client(switch_BaseballServer_Client);

		jWARN(_T("r.type()==UAnsProtocol_Type_GLANSGAMEPROTOCOL > r2.type()= %d(%s) : invalied packet")
			,r2.type(), r2.GetTypeName().c_str());
		return true;

	}

#	define switch_UAnsProtocol(ENUM,MSG,VAR)\
	if(r.type() == UAnsProtocol_Type_##ENUM )\
	{\
		if(tstring(jS(AnsDB))!=jS(MSG))\
		{\
			jLOG(jFUNC1 _T("%s : %s") ,user.m_id.c_str(), jS(MSG) );\
		}\
		bool OnRecv_##MSG(RECV_PARAM_PlugIn_BaseballClient,const MSG &r2);\
		return OnRecv_##MSG(this, peSession,&user,r.VAR());\
	}\

	for_each_UAnsProtocol(switch_UAnsProtocol);

	jWARN(_T("r.type()= %d(%s) : invalied packet"),r.type(), r.GetTypeName().c_str());
	return true;
}

bool PlugIn_BaseballClient::ParseCmd(tcstr szCmd)
{
	jRETURN_ret(false,g_peCurrSession);
	jUser& user= g_Users[g_peCurrSession];

	if(szCmd[0]==' ')
	{
		jLOG(_T("%s> send msg : %s" ), user.m_id.c_str() , szCmd);

		//nswb256_t buf;
		jRETURN_ret(false,g_peCurrSession!=NULL);
		tstring sC = szCmd;
		nSTL::replace(sC,_T(" ") , _T("_"));
		szCmd = sC.c_str();

		jLOG(_T("%s> send msg : %s" ), user.m_id.c_str() , szCmd);
		fname_t szCmd;
		tcstr szID = user.m_id.c_str();
		jt_sprintf(szCmd, _T("@%s.ug_echo %s %s"), jsSERVER_NAME, jT(szID), szCmd);
		nCONSOLE::Get_jIConsoleCmd()->ParseCmd(szCmd);
		return false;
	}
	jLOG(_T("%s>%s" ), user.m_id.c_str() , szCmd);
	return false;
}


void PlugIn_BaseballClient::send_to_bs(jIE* peSession, Client_BaseballServer& sendMsgG)
{
	UReqProtocol sendMsgU;
	sendMsgU.set_type(UReqProtocol_Type_GLREQGAMEPROTOCOL);
	sendMsgG.SerializeToString(sendMsgU.mutable_reqgameprotocol());

	char buf[MAX_BODY_LENGTH];
	google::protobuf::io::ArrayOutputStream os(buf, sendMsgU.ByteSize());
	sendMsgU.SerializeToZeroCopyStream(&os);
	m_pCSM->Send( peSession, buf, sendMsgU.ByteSize());
}

jIE* PlugIn_BaseballClient::CreateClient(cstr ip, cstr id)
{
	cstr szSERVICE_NAME = m_pE->GetAttr(jS(SERVICE_NAME));
	jIE* peSession = FindUser(id);
	if(!peSession)//없으면 만든다.
	{
		fname_t szName;
		MakeSessionName(id,szName);
		peSession = m_pE->InsertChildElement(szName);
		jIE* peORIGINAL = m_pE->Find(jS(TCP_BaseballServer));
		peORIGINAL->CopyTo(peSession);
		peSession->ChangeTagName(szName);
	}
	peSession->GetAttrVar(jS(ENABLE))->Set_bool(true);
	peSession->Set_cstr(ip);
	nXML::jE e=peSession;
	e.AttrP(jS(id)).T() = id;

	return m_pCSM->Create(szSERVICE_NAME , g_pPlugIn , peSession);
}

void PlugIn_BaseballClient::send_to_ug(jIE* peSession, UReqProtocol& sendMsg)
{
	char buf[MAX_BODY_LENGTH];
	google::protobuf::io::ArrayOutputStream os(buf, sendMsg.ByteSize());
	sendMsg.SerializeToZeroCopyStream(&os);

	m_pCSM->Send( peSession, buf, sendMsg.ByteSize());
}



void PlugIn_BaseballClient::send_to_ug(jIE* peSession, Client_UserGateServer& msg)// PT_UserGateServer.proto에 정의된 메세지만 보내자.
{
	UReqProtocol sendMsg;
	sendMsg.set_type(UReqProtocol::UREQDB);
	ReqDB* sd = sendMsg.mutable_reqdb();
	sd->set_seq(0);
	sd->set_query("ug_game");
	msg.SerializeToString(sd->mutable_options());
	send_to_ug(peSession, sendMsg);

}


