/* file : define_code_ToClient.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-11-03 00:02:35
comp.: t3.co.kr
title : 
desc : 


front end server에서 클라이언트 컨넥션 관련 코드.

*/

#ifndef __define_code_ToClient_header__
#define __define_code_ToClient_header__
#pragma once



//jFE_GetUser(Data.pid); //jGridNode_Client* pGNC  , jPlayerObj* pPlayer , 
#define jFE_GetUser(pid)\
	jCI(g_SG.m_Client.find(pid));\
	jPlayerObj* pPlayer = (jPlayerObj*)ci->m_pPlayer;\
	if(!pPlayer )\
	{\
		fname_t szBuf;\
		jWARN1(_T("user not found : %s"), ToString(pid, szBuf));\
		return;\
	}\




// buf, jGridNode_Client* pGNC  , jPlayerObj* pPlayer ,PlugIn_Server* pP 
#define READ_PACKET_FromClient(X) READ_PACKET(X);	nswb1024_t buf;\
	PlugIn_Server* pP = (PlugIn_Server*)pPlugIn;\
	jGridNode_Client* pGNC = (jGridNode_Client*)pS->GetGridNode();\
	if(!pGNC){jWARN("pGNC==NULL");}\
	jPlayerObj* pPlayer= (jPlayerObj*)pGNC->m_pPlayer;\
	if(!pPlayer){jWARN(" pPlayer==NULL");	return;}\


#define jSend_ERROR_TO_CLIENT(fromTAG,TAG)\
	READ_PACKET_PC_B(fromTAG##_ERROR);\
	jIGridNode* pGNC = g_SG.m_Client.find(Data.ei.pid);\
	if(!pGNC) return;\
	if(Data.ei.IsAction(eEAT_DISCON_USER))\
	{\
		pGNC->m_pPlugIn->DoDisconnect(pS);\
		return;\
	}\
	else\
	{\
		jNET_SEND(pGNC ,TAG##_ERROR , Data.ei);\
	}\

// channel, dungeon에서 client로 가벼운 에러메시지 보냄
#define pS_eSEND_jError_ToClient(SERVER_TAG, server_error,client_error)\
	jError e(server_error,client_error); name1024_t szError;e.ToString(szError);\
	pS->WritePacket(& _jJOIN_3(WRITE_,SERVER_TAG,_ERROR)(buf , e,eEAT_NOTIFY_TO_CLIENT,__FUNCTION__,player_id_t()));\


#define jCONSOLE_PARAM_user_list2(X,Y) X(outType,tcstr) Y(file_tag,tcstr,0)
#define jLAMDA_jxGet_User_list(X,Z) Z(vector<tstring>& ,users)
#define jCONSOLE_CMD_AUTO_user_list2()\
	jCONSOLE_CMD_AUTO(jSERVER_NAME,user_list2, 0 ,"print user list" , "<file | con> [file_tag]")\
{\
	jCONSOLE_PARAM_END(user_list2);\
	jLAMDA_for_each(jxGet_User_list , jPlayerBase*)\
	{\
	jPlayerObj* pPO = (jPlayerObj*)it;\
	tname1024_t buf;\
	ToString(pPO,buf);\
	users.push_back(buf);\
	}\
	jLAMDA_end();\
	\
	vector<tstring> users;\
	g_PL.for_each(to_string_vector(users));\
	bool is = g_TCommon.output_string_to_file_or_con(outType, jS(user_list_) jsSERVER_NAME, file_tag, users);\
	jLOG1(_T("tot user= %d"),users.size());\
	return is;\
}\



#define jFE_OnIoConnected_fromClient(PACKET) jFE_OnIoConnected_fromServer(PACKET)

#define jFE_OnIoDisconnected_fromClient()\
	jRETURN(pS)\
	--g_SG.m_MyInfo.m_iTotClient;\
	jCI(pS->GetGridNode());\
	jPlayerObj* pPlayer = (jPlayerObj*)ci->m_pPlayer;\
	jRETURN(pPlayer);\
	jRETURN(pPlayer->m_pid.m_id);\
	g_SG.Set_U4_USER_CONNECTION_NOTIFY_CS(pPlayer->m_pid,pPlayer->m_szID,false);\
	jLOG1(jFUNC1 _T("player = %s"), jT(pPlayer->m_szID));\




#endif // __define_code_ToClient_header__
