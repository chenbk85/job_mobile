/* file : define_code_Server.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-16 19:00:02
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __define_code_Server_header__
#define __define_code_Server_header__
#pragma once


// dc , world , user server 에서 서버들 소켓 리딩.
#define READ_PACKET_FromServer(X) READ_PACKET(X);\
	jFE(); nswb1024_t buf; AqConnectedServerNode* pServer= pFE->get_user(pS);\
	if(!pServer){GetjILog()->Warning(_T(#X) _T(" pServer==NULL"));	return;}\


#define jxSocket_Connected33(X) if(pS->Get_jIE()->IsName(jS(To##X))) m_pTo##X=pS; else 
#define jInit_PlugIn_ToBackEnd_OnIoConnected()\
	GetjILog()->Log(jFUNC1 _T("%s"), pS->Get_jIE()->GetTagName() );\
	for_each_ToBackEnd(jxSocket_Connected33);\

#define jxSocket_Disconnected33(X) if(pS->Get_jIE()->IsName(jS(To##X))) m_pTo##X=0; else 
#define jInit_PlugIn_ToBackEnd_OnIoDisconnected()\
	GetjILog()->Log(jFUNC1 _T("%s"), pS->Get_jIE()->GetTagName() );\
	for_each_ToBackEnd(jxSocket_Disconnected33);\
	if(jt_strstr(pS->Get_jIE()->GetTagName() , jS(ToDBCache) ) ) {	erase_DBCache(pS);	}\
	

//if(!m_pToCentral){exit(1);};\


#define jSend_SS2server_ONLINE(X)\
	be_READ_PACKET_P2P_PB(X##_HELLO);\
	nXML::jE e = pBE->GetServerInfo_jIE(pS);jAssert0(e.full() && _T(__FUNCTION__));\
	pS->WritePacket(&_jJOIN_3(WRITE_SS2,X,_ONLINE)(buf,e.Attr(jS(m_sid))->Get_int() ,pBE->m_sid,pBE->m_MyInfo.m_eType));\


#define  jRecv_C_SERVER_ONLINE()\
	be_READ_PACKET_P2P_PB_xml(C_SERVER_ONLINE,server);\
	cstr szWorld = Data.server->GetAttr(jS(m_szWorld));\
	nXML::jE eee;\
	do{eee = pBE->m_eServers(jS(aqconnectedservernode));}while(eee.empty());\
	eee[szWorld]->InsertChild(0,Data.server);\
	pBE->m_eServers->DebugPrint(true);\

#define jRecv_C2SS_ONLINE_OK()\
	be_READ_PACKET_P2P_PB_xml(C2SS_ONLINE_OK,server_list);\
	pBE->m_sid = Data.sid;\
	pBE->m_eServers.AttrP(jS(m_sid)).T() = (int)Data.sid;\
	pBE->m_eServers->InsertChild(0,Data.server_list);\
	pBE->m_eServers->DebugPrint(true);\



#define jSend_SS2C_ONLINE(name,world,eType)\
	jFE();jSOCKADDR_IN* pAddr = pFE->m_pServer->GetTcpListenAddress();\
	tname32_t szIP;	pAddr->GetIP(szIP);\
	while(pBE->m_eServers.empty());\
	\
	nMech::nUtil::CRegistry reg;\
	reg.Open(_T("SOFTWARE\\jGame\\jAqServer"),HKEY_LOCAL_MACHINE);\
	if(!reg[_T("name_number")].Exists()) reg[_T("name_number")] = (int)0;\
	int name_number = reg[_T("name_number")];\
	fname_t szServerName;\
	jt_sprintf(szServerName,_T("%s_%d"),name,name_number);\
	++name_number;\
	reg[_T("name_number")]=name_number;\
	reg.Close();\
	\
	pBE->m_MyInfo.MakeInfo(pBE->m_eServers,szServerName, world, szIP , jServerInfoBase:: eType, pAddr->GetPort() , Get_MAX_USER() );\
	S_SS2C_ONLINE pk= {pBE->m_MyInfo.m_eType ,pBE->m_eServers};\
	pS->WritePacket(&nCentralServer::WRITE_SS2C_ONLINE(buf, pk ));\


#define jSEND_ERROR_USER_DISCONNECT(SERVER_TAG, server_error,client_error , uid)\
	jError e(server_error,client_error); name1024_t szError;e.ToString(szError);\
	GetjILog()->Warning(jFUNC1 _T("WRITE_") _T(#SERVER_TAG) _T("_ERROR(%s);"), szError);\
	pS->WritePacket(& _jJOIN_3(WRITE_,SERVER_TAG,_ERROR)(buf , e,eSEND_Disconn_User,"",uid));\


#define jSEND_ERROR_TO_USER(SERVER_TAG, server_error,client_error , uid)\
	jError e(server_error,client_error); name1024_t szError;e.ToString(szError);\
	GetjILog()->Warning(jFUNC1 _T("WRITE_") _T(#SERVER_TAG) _T("_ERROR(%s);"), szError);\
	pS->WritePacket(& _jJOIN_3(WRITE_,SERVER_TAG,_ERROR)(buf , e,eSEND_jError_ToClient,"",uid));\


//jTODO jError 선택된 아바타 index가 잘못되었습니다. 향후 강제접속.
#define pUser_Check_townid(aid,SERVER_TAG,uid)\
if(pUser->Town_size() < aid || aid<=0)\
{\
	pS->WritePacket(&_jJOIN_3(WRITE_,SERVER_TAG,_ERROR)(buf, jError(SR_t(TOWN_ID_WRONG),0) \
	, eSEND_jError_and_User_Do_Disconn, __FUNCTION__ ,uid) );\
	return;\
}\


#endif // __define_code_Server_header__
