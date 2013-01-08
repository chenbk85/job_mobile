/* file : define_code_jBE.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-16 14:25:27
comp.: wiki.aqrius.com
title : 
desc : 


back end server¿ë define 

*/

#ifndef __jNET_define_code_header__
#define __jNET_define_code_header__
#pragma once


serverid_t jSERVER_sid();
#define jFE_OnIoConnected_fromServer(PACKET)\
	nswb256_t buf;\
	AqConnectedServerNode* pServer = push_back_if_not_found(pS);\
	fname_t szIP;\
	GetjILog()->Log(jFUNC1 _T("OnIoConnected = %s"), pS->GetAddressString(szIP));\
	pS->WritePacket(&WRITE_##PACKET(buf,jSERVER_sid()) );\
	pS->SetDebugger(jSocketDebugger);\


#define jFE_OnIoDisconnected_fromServer()\
	if(!pS) return;\
	AqConnectedServerNode* pServer = get_user(pS);\
	if(!pServer){	GetjILog()->Warning(jFUNC1 _T(" pServer==null"));return;}\
	GetjILog()->Log(jFUNC1 _T(" server : %s"), jT(pServer->Get_ServerName()) );\


#define jRecv_SS2server_ONLINE()\
	jBE();\
	if( Data.your_sid != pBE->m_sid)\
	{\
	GetjILog()->Warning(_T("Data.userserver(%d) != pBE->m_sid(%d)"),Data.your_sid, pBE->m_sid);\
	pFE->m_pServer->DisconnectTcpClient(pS);\
	return;\
	}\
	int sid = Data.my_sid;\
	nXML::jE e = pBE->m_eServers->FindByFirstAttr(jS(m_sid), jIVar::EDint , &sid);\
	if(e.empty())\
	{\
	GetjILog()->Warning(jFUNC1 _T("pBE->m_eServers->FindByFirstAttr(%d) not found"),sid);\
	pFE->m_pServer->DisconnectTcpClient(pS);\
	return;\
	}\
	pServer->m_E = e;\
	pServer->Set_sid(Data.my_sid);\
	pServer->m_eType = Data.my_eType\



#endif // __jNET_define_code_header__
