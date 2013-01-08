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



#define  jRecv_C_SERVER_ONLINE(SERVER_TAG)\
	READ_PACKET_PC_B(SERVER_TAG##_SERVER_ONLINE);\
	g_SG.ServerInfo_insert(Data.s);\
	g_SG.Do_SERVER_ONLINE_ACTION(Data.s);\
	jDebugPrint(jS(SERVER_TAG##_SERVER_ONLINE),Data.s);\


#define jRecv_C2SS_ONLINE_OK(SERVER_TAG)\
	READ_PACKET_PC_B(SERVER_TAG##2SS_ONLINE_OK);\
	g_SG.m_MyInfo = Data.you;\
	jSI(pS->GetGridNode());\
	g_SG.ServerInfo_insert_from_vector(Data.s);\
	for(size_t ii=0;ii<Data.s.size();++ii) g_SG.Do_SERVER_ONLINE_ACTION(Data.s[ii]);\

// central이 아니고 또한 central접속이 된상태에서는 
// central에서 sid를 부여받기전(C2SS_ONLINE_OK)까지 무한루프돈다!.
// 이때 SERVER_TAG##_HELLO에 대한 thread_name이 반드시 세팅되어 있어야한다.
#define jRecv_HELLO(SERVER_TAG)\
	READ_PACKET_PC_BS(SERVER_TAG##_HELLO);\
	*si = Data.si;\
	if(g_SG.m_MyInfo.m_szName[0]==0)\
	{\
		jPS();jSOCKADDR_IN* pAddr = pPS->m_pServer->GetTcpListenAddress();\
		tname32_t szIP;			pAddr->GetIP(szIP);\
		fname_t szServerName;	g_SG.generate_server_name(g_ExeEnv.m_szComputerName,szServerName);\
		g_SG.m_MyInfo.MakeInfo(szServerName, szIP , pAddr->GetPort() , Get_MAX_USER() );\
		jt_strcpy_s(g_SG.m_MyInfo.m_szDomain , (pv_DOMAIN_NAME->Get_cstr()) );\
	}\
	pS->WritePacket(&_jJOIN_3(WRITE_SS2,SERVER_TAG,_ONLINE)(buf,si->m_sid,g_SG.m_MyInfo) );\




#define jSEND_ERROR_USER_DISCONNECT(SERVER_TAG, server_error,client_error , pid)\
	jError e(server_error,client_error); name1024_t szError;e.ToString(szError);\
	jWARN(" jSEND_ERROR_USER_DISCONNECT(%s);", szError);\
	jNET_SEND(pS,SERVER_TAG##_ERROR,jErrorInfo(e,eEAT_DISCON_USER,__FUNCTION__,pid));\


#define jSEND_ERROR_TO_USER(SERVER_TAG, server_error,client_error , pid)\
	jError e(server_error,client_error); name1024_t szError;e.ToString(szError);\
	jWARN("jSEND_ERROR_TO_USER(%s);", szError);\
	jNET_SEND(pS,SERVER_TAG##_ERROR, jErrorInfo(e,eEAT_NOTIFY_TO_CLIENT,__FUNCTION__,pid));\


//jTODO jError 선택된 아바타 index가 잘못되었습니다. 향후 강제접속.
#define pUser_Check_channelid(aid,SERVER_TAG,uid)\

#ifdef TSERVER_PREPARE
if(pUser->Channel_size() < aid || aid<=0)\
{\
	jNET_SEND(pS,SERVER_TAG##_ERROR, jErrorInfo(jError(SR_t(TOWN_ID_WRONG),0) , eEAT_NOTIFY_AND_DISCON_USER, __FUNCTION__ ,uid) );\
	return;\
}
#endif //TSERVER_PREPARE


#endif // __define_code_Server_header__
