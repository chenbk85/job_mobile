/* file : define_code_jFE.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-16 17:34:47
comp.: wiki.aqrius.com
title : 
desc : 



front end server 용 define 
*/

#ifndef __jFE_define_code_header__
#define __jFE_define_code_header__
#pragma once




//jFE_GetUser(Data.uid); //AqClientUser* pUser
#define jFE_GetUser(uid)\
	AqClientUser* pUser = pFE->find_user(uid);\
	if(!pUser)\
	{\
		fname_t szBuf;\
		GetjILog()->Warning(jFUNC1 _T("user not found : %s"), ToString(uid, szBuf));\
		return;\
	}\



#define jCONSOLE_PARAM_lists(X,Y) X(outType,tcstr) Y(file_tag,tcstr,0)
#define jLAMDA_jxGet_User_list(X,Z) Z(vector<tstring>& ,users)

#define jCONSOLE_CMD_AUTO_user_lists()\
jCONSOLE_CMD_AUTO(jSERVER_NAME,user_list, 0 ,"print user list" , "<file | con> [file_tag]")\
{\
	jCONSOLE_PARAM_END(lists);\
	jFE_ret(false);\
\
	jLAMDA_for_each(jxGet_User_list , AqClientUser&)\
	{\
		tname1024_t buf;\
		ToString(&it,buf);\
		users.push_back(buf);\
	}\
	jLAMDA_end();\
\
	vector<tstring> users;\
	pFE->for_each(jxGet_User_list(users));\
	bool is = g_jAqCommon.output_string_to_file_or_con(outType, jS(login_user_list), file_tag, users);\
	GetjILog()->Log(_T("tot user= %d"),users.size());\
	return is;\
}\


#define jFE_OnIoConnected_fromClient(FRONT_SERVER_TAG)\
	nswb256_t buf;\
	AqClientUser_##FRONT_SERVER_TAG* pUser = push_back_if_not_found(pS);\
	fname_t szIP;\
	GetjILog()->Log(_T("OnIoConnected = %s"), pS->GetAddressString(szIP));\
	pS->WritePacket(&_jJOIN_3(WRITE_,FRONT_SERVER_TAG,_HELLO)(buf) );\



#define jFE_OnIoDisconnected_fromClient(FRONT_SERVER_TAG)\
	if(!pS) return;\
	AqClientUser_##FRONT_SERVER_TAG* pUser = get_user(pS);\
	if(!pUser){	GetjILog()->Warning(jFUNC1 _T(" pUser==null"));	return;	}\
	GetjILog()->Log(jFUNC1 _T("user: %s"), jT(pUser->m_szID) );\
	GetjILog()->Log(_T("uid = %I64d"),pUser->m_uid.m_id);\
	if(pUser->m_uid.m_id)\
	{\
		PlugIn_ToBackEnd*pBE = PlugIn_ToBackEnd::Get();\
		if(pBE)\
		{\
			pBE->Set_U4_USER_CONNECTION_NOTIFY_CS(pUser->m_uid,pUser->m_szID,false);\
		}\
		else\
		{\
			GetjILog()->Warning(jFUNC1 _T("PlugIn_ToBackEnd::Get() ==0"));\
		}\
	}\
	else\
	{\
		GetjILog()->Warning(jFUNC1 _T("user uid ==0"));\
	}\



#define READ_PACKET_FromClient(X) READ_PACKET(X);\
	jFE();	nswb1024_t buf;	AqClientUser* pUser= pFE->get_user(pS);\
	if(!pUser){GetjILog()->Warning(_T(#X) _T(" pUser==NULL"));	return;}\


//jBE_GetUserDBCache(uid);//jIPacketSocket_IOCP* pS_DB; 
#define jBE_GetUserDBCache(uid)\
	jIPacketSocket_IOCP* pS_DB= pBE->find_DBCache(uid.m_dc_sid);\
	if(!pS_DB)\
	{\
		fname_t szBuf;\
		GetjILog()->Warning(jFUNC1 _T("user's dbcache is not found : %s") , ToString(uid,szBuf));\
		return;\
	}\



#define jSend_ERROR_TO_CLIENT(fromTAG,TAG)\
	be_READ_PACKET_P2P_PB(fromTAG##_ERROR);\
	jFE();\
	if(Data.type==0){pFE->DisconnectTcpClient(Data.uid);}\
	else\
	{\
	jFE_GetUser(Data.uid);\
	pUser->Write_Packet(_jJOIN_3(WRITE_,TAG,_ERROR)(buf, Data.e, Data.type,Data.msg,userid_t() ));\
	}\


// town, dungeon에서 client로 가벼운 에러메시지 보냄
#define pS_eSEND_jError_ToClient(SERVER_TAG, server_error,client_error)\
	jError e(server_error,client_error); name1024_t szError;e.ToString(szError);\
	pS->WritePacket(& _jJOIN_3(WRITE_,SERVER_TAG,_ERROR)(buf , e,eSEND_jError_ToClient,__FUNCTION__,userid_t()));\


#define jLAMDA_connectToDBCache(X,Z) Z(jPlugIn_BE_Helper*,pBE)
jLAMDA_for_each(connectToDBCache,jIE*)
{
	cstr sz = it->GetAttr(jS(m_eType));
	if(!sz) return;
	if(jt_strcmp(sz, jS(DBCacheServer))) return;
	pBE->ConnectToDBCacheServer(it);
}
jLAMDA_end()


#endif // __jFE_define_code_header__
