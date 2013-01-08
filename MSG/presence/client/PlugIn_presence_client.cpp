/* file : PlugIn_presence_client.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:13
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TestClient.h"
#include "PlugIn_presence_client.h"

PlugIn_presence_client* g_pPlugIn=0;


jIE* g_peCurrSession=0;

jLIST_TYPEDEF_map(jIE*,TestSession,g_SessionList);
nUtil::jCriticalSection g_SessionList_CS;


jDEFINE_RTTIOBJ_BY_SCOPE(PlugIn_presence_client,jNet, 1,1);


jSQ_REGIST_BIND(PLUGIN)
{
	jSQ_Interface(PlugIn_presence_client)
		jSQ_end();

	//jSQ_g_var(&g_TestInfo,g_TestInfo);
}


void PlugIn_presence_client::OnStartup()
{
	m_pMM=0;
	jLOG(jFUNC);
	g_pPlugIn=this;
	nCONSOLE::Get_jIConsoleCmd()->Run(_T("con"),_T("message"),_T("tcp_mode"),true ,0);
	nCONSOLE::Get_jIConsoleCmd()->Run(_T("con"),_T("message_txt"),_T("\"default : to test server\n\r* chat : to game server\""),true ,0);

}
void PlugIn_presence_client::OnStop()
{
	jLOG(jFUNC);
	if(g_pPlugIn==this)
		g_pPlugIn=0;
}


//#--------------------------------------------------------------------------
bool PlugIn_presence_client::OnConnect(jIE* peSession)
//#--------------------------------------------------------------------------
{
	if(!g_peCurrSession) g_peCurrSession=peSession;
	jLOG(jFUNC1 _T("%s"), peSession->GetTagName());

	if(!jt_strstr(peSession->GetTagName(), jS(TCP_PresenceServer))) return true;

	jAUTO_LOCK_CS(g_SessionList_CS);
	TestSession* pSession=&g_SessionList[peSession];
	pSession->m_peSession = peSession;
	pSession->m_id = peSession->GetAttr(jS(id));
	pSession->game_id=jt_atoi64(pSession->m_id.c_str());

// 	PReqProtocol sendMsg;
// 	sendMsg.set_type(PReqProtocol::UREQCONNECT);
// 	UReqConnect* sd = sendMsg.mutable_reqconnect();
// 	sd->set_svcid(0);
// 	sd->set_gameid(pSession->game_id);
// 	sd->set_lastclosetime(0);
// 	ug::Make(*sd->mutable_version() );
// 	ug::Make(*sd->mutable_memberinfo() , pSession->game_id ,"avartar_url_test", jA(pSession->m_id), true );

	this->Send_PReqProtocol(peSession, sendMsg);

	return true;
}

//#--------------------------------------------------------------------------
void PlugIn_presence_client::OnDisconnect(jIE* peSession)
//#--------------------------------------------------------------------------
{
	if(g_peCurrSession==peSession)
		g_peCurrSession=0;
	jLOG(jFUNC1 _T("%s"),peSession->GetTagName());
  jRETURN(g_SessionList.count(peSession));	
  
	g_SessionList.erase(peSession);
}

//#--------------------------------------------------------------------------
bool PlugIn_presence_client::OnRead(jIE* peSession,char* pRecvBuff,int iReadLen)
//#--------------------------------------------------------------------------
{
	google::protobuf::io::ArrayInputStream ais(pRecvBuff, iReadLen);
	PAnsProtocol r;
	r.ParseFromZeroCopyStream(&ais);

	jAUTO_LOCK_CS(g_SessionList_CS);
	jvRETURN_ret(false, g_SessionList.count(peSession) ,_T("r.type= %s ") , r.GetTypeName().c_str() );	
	TestSession& user= g_SessionList[peSession];

#	define switch_PAnsProtocol(ENUM,MSG,VAR)\
	if(r.type() == PAnsProtocol_Type_##ENUM )\
	{\
		if(tstring(jS(AnsDB))!=jS(MSG))\
		{\
			jLOG(jFUNC1 _T("%s : %s") ,user.m_id.c_str(), jS(MSG) );\
		}\
		bool OnRecv_##MSG(RECV_PARAM_PlugIn_presence_client,const MSG &r2);\
		return OnRecv_##MSG(this, peSession,&user,r.VAR());\
	}\

	//for_each_PAnsProtocol(switch_PAnsProtocol);

	jWARN(_T("r.type()= %d(%s) : invalied packet"),r.type(), r.GetTypeName().c_str());
	return true;
}

bool PlugIn_presence_client::ParseCmd(tcstr szCmd)
{
	jRETURN_ret(false,g_peCurrSession);
	TestSession& user= g_SessionList[g_peCurrSession];

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


jIE* PlugIn_presence_client::CreateSession(cstr ip, cstr id)
{
	cstr szSERVICE_NAME = m_pE->GetAttr(jS(SERVICE_NAME));
	jIE* peSession = FindSession(id);
	if(!peSession)//없으면 만든다.
	{
		fname_t szName;
		MakeSessionName(id,szName);
		peSession = m_pE->InsertChildElement(szName);
		jIE* peORIGINAL = m_pE->Find(jS(TCP_PresenceServer));
		peORIGINAL->CopyTo(peSession);
		peSession->ChangeTagName(szName);
	}
	peSession->GetAttrVar(jS(ENABLE))->Set_bool(true);
	peSession->Set_cstr(ip);
	nXML::jE e=peSession;
	e.AttrP(jS(id)).T() = id;

	return m_pCSM->Create(szSERVICE_NAME , g_pPlugIn , peSession);
}

void PlugIn_presence_client::Send_PReqProtocol(jIE* peSession, PReqProtocol& sendMsg)
{
	char buf[MAX_BODY_LENGTH];
	google::protobuf::io::ArrayOutputStream os(buf, sendMsg.ByteSize());
	sendMsg.SerializeToZeroCopyStream(&os);

	m_pCSM->Send( peSession, buf, sendMsg.ByteSize());
}

