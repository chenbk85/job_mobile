/* file : Cmd_Dummy.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-27 16:19:23
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToBackEnd.h"

#define jGET_USER_BE(pUser)\
jBE_ret(false);\
jIE* peUser = pBE->FindUser(jT(uid));\
jRETURN_ret(false,peUser);\
jUser* pUser = pBE->GetUser(peUser);\
jRETURN_ret(false, pUser);\


void JOB_ConsoleCmd(nEVENT::jIMessage*pMsg)
{
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(pMsg->GetArg(0)->Get_cstr());
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,login,0,"로긴테스트","<127.0.0.1:33000> <id> <pwd>")
{
#define jCONSOLE_PARAM_login(X,Y) X(ip,tcstr) X(id,acstr) X(pwd,acstr)
	jCONSOLE_PARAM_END(login);
	jBE_ret(false);
	fname_t szTCP_ID;
	MakeSessionName(jT(id),szTCP_ID);
	nXML::jE eTCP_new = pBE->m_pE->Find(szTCP_ID);
	if(eTCP_new.empty())
	{
		nXML::jE eTCP = pBE->m_pE->Find(jS(TCP_TestServer));
		jRETURN_ret(false , eTCP.full());
		eTCP_new = pBE->m_pE->InsertChildElement(szTCP_ID);
		eTCP->CopyTo(eTCP_new);
		eTCP_new->ChangeTagName(szTCP_ID);
	}
	else
	{
		size_t count = pBE->m_Users.count(eTCP_new);
		jvRETURN_ret(true , count <= 0 , _T("user is exist : %s"), jT(id));
	}


	eTCP_new.AttrP(jS(ENABLE)).T() = true;
	eTCP_new->Set_cstr(ip);
	eTCP_new.AttrP(jS(id)).T() = id;

	jAUTO_LOCK_CS(pBE->m_Users_CS);
	jUser* pUser = &pBE->m_Users[eTCP_new];
	ja_strcpy(pUser->m_szPWD , pwd);
	ja_strcpy(pUser->m_szID , id);
	pUser->m_pE = eTCP_new;
	
	pBE->m_pClientSession->Start_ClientSocket(eTCP_new);
	return true;
}


jCONSOLE_CMD_AUTO(jSERVER_NAME,echo,0,"help : echo","<uid>")
{
#define jCONSOLE_PARAM_echo(X,Y) X(uid,tcstr)
	jCONSOLE_PARAM_END(echo);

	jGET_USER_BE(pUser);

	nswb256_t buf;
	using namespace nNET::nTestServer;
	wfname_t szCommand;
	static int s_ii=0;
	jw_sprintf(szCommand , L"echo test : %d" , s_ii++);
	jNET_SEND(pUser->m_pS,S_ECHO,0,jW(szCommand));

	return true;
}


/*

jCONSOLE_CMD_AUTO(jSERVER_NAME,asdf,0,"help : asdf","<uid>")
{
	#define jCONSOLE_PARAM_asdf(X,Y) X(uid,tcstr)
	jCONSOLE_PARAM_END(asdf);
	jGET_USER_BE(pUser);

	pBE->ConnectToLoginServer_AllDummy(per_user , delay_msec);
	return true;
}

*/

