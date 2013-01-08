/* file : define_code_PlugIn.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-05 11:28:12
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __define_code_PlugIn_header__
#define __define_code_PlugIn_header__
#pragma once

#include "define_code_BackEndServer.h"

#define jPLUGIN_HEADER_CODE(NAME)\
	jDECLARE_RTTIOBJ(NAME);\
	JNET_PLUGIN_SINGTONE_DECL(NAME);\
	virtual void Start();\
	virtual void Stop();\
	VOID OnIoRead(jNETARG_SOCK_NUM_BUFF_LEN_IP);\
	virtual VOID OnIoWrote(jIPacketSocket_IOCP*pObject);\
	virtual VOID OnIoConnected(jIPacketSocket_IOCP* pPlugIn);\
	virtual VOID OnIoDisconnected(jIPacketSocket_IOCP*);\
	virtual bool ParseCmd(tcstr szCommand);\
	NAME();\
	nEVENT::jIMsgManager* m_pMM;\
	size_t	m_iTotConnection;\


#define jPLUGIN_HEADER_CODE_Connect(NAME)\
	jPLUGIN_HEADER_CODE(NAME)\
	virtual int Get_CURR_USER(){return ::Get_CURR_USER();};\


#define jPLUGIN_CPP_CODE_START(NAME)\
	\
	jDEFINE_RTTIOBJ_BY_SCOPE(NAME,jNet, 1,1);\
	JNET_PLUGIN_SINGTONE_DEFINE(NAME);\
	VOID NAME::OnIoRead(jNETARG_SOCK_NUM_BUFF_LEN_IP)\
	{\
		jNamedEventNode* pHN = pHT->GetByNum(pk->num);\
		jWARN1(_T("%d:%s"),pk->num,pHN?pHN->m_szName:jS(NULL));\
	}\
	VOID NAME::OnIoWrote(jIPacketSocket_IOCP* pSocket){}\
	void NAME::Start()\
	{\
		NAME::Set(this);\
		jLOG1(jFUNC1 );\


#define jPLUGIN_CPP_CODE_START_Connect(NAME)\
	\
	jServerGrid g_SG;\
	jPLUGIN_CPP_CODE_START(NAME);\
	g_SG.Init(this);\
	g_SG.m_MyInfo.m_eType = ToServerType(jSERVER_TYPE);\
	jt_strcpy_s(g_SG.m_MyInfo.m_szDomain , (pv_DOMAIN_NAME->Get_cstr()) );\


#define jPLUGIN_CPP_CODE_START_Server(NAME)\
	\
	jPlayerList_IMPLEMENT g_PL;\
	int Get_CURR_USER()	{jPS_ret(0);return pPS->m_iTotConnection;}\
	int Get_MAX_USER()	{jPS_ret(0);return pPS->m_pE->GetAttrVar(jS(MaxTcpUser))->Get_int();}\
	jPLUGIN_CPP_CODE_START(NAME);\
	m_pMM = nEVENT::jIMsgManager::Get(jS(NAME), true);\
	m_iTotConnection=0;\
	if(!g_pCurrPlugIn_CmdParser) g_pCurrPlugIn_CmdParser= this;\



#define jPLUGIN_CPP_CODE_STOP(NAME)\
}\
void NAME::Stop()\
{\


#define jPLUGIN_CPP_CODE_END_Connect(NAME)\
	NAME::Set(0);\
	jLOG1(jFUNC1 );\
	g_SG.m_pPlugIn = 0;\
}\


#define jPLUGIN_CPP_CODE_END_Server(NAME)\
	if(m_pMM){m_pMM->clear();m_pMM=0;}\
	NAME::Set(0);\
	jLOG1(jFUNC1 );\
}\




#define jInit_PlugIn_Connect_OnIoConnected()\
	jLOG1(jFUNC1 _T("%s"), pS->Get_jIE()->GetTagName() );\

#define jInit_PlugIn_Connect_OnIoDisconnected()\
	jLOG1(jFUNC1 _T("%s"), pS->Get_jIE()->GetTagName() );\




/* 사용 코드 예.


jPLUGIN_CPP_CODE_START_Server(PlugIn_Server)
{//PlugIn_Server::Start
}
jPLUGIN_CPP_CODE_STOP(PlugIn_Server)
{//PlugIn_Server::Stop
}
jPLUGIN_CPP_CODE_END_Server(PlugIn_Server);



jPLUGIN_CPP_CODE_START_Connect(PlugIn_Connect)
{
}
jPLUGIN_CPP_CODE_STOP(PlugIn_Connect)
{
}
jPLUGIN_CPP_CODE_END_Connect(PlugIn_Connect);

*/


#endif // __define_code_PlugIn_header__
