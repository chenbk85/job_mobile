/* file : PlugIn_Server.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:37
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __PlugIn_Server_header__
#define __PlugIn_Server_header__
#pragma once



//jGet_DCUser(Data.pid,pS); //jPlayerObj* pUser
#define jGet_DCUser(pid,pS)\
	jPlayerObj* pUser= (jPlayerObj*)g_PL.find(pid);\
	if(!pUser)\
{\
	tname1024_t szBuf;\
	jWARN ("pid is wrong : %s", ToString(pid,szBuf) );\
	jError e(SR_t(DC_USER_NOT_FOUND),0);\
	jNET_SEND(pS,DC_ERROR,jErrorInfo(e,eEAT_NOTIFY_TO_CLIENT,__FUNCTION__,pid) );\
	jNET_SEND2(g_SG.m_World,W_ERROR,jErrorInfo(e,eEAT_DISCON_USER,__FUNCTION__,pid));\
	return;\
}\


#define jGet_DCUser_byName(id,pid,pS)\
	jPlayerObj* pUser= (jPlayerObj*)g_PL.find(id);\
	if(!pUser)\
{\
	jWARN("pid is wrong : %s", id);\
	jError e(SR_t(SQL_INV_SFKIND_QUERY_ERR),0);\
	jNET_SEND(pS,DC_ERROR,jErrorInfo(e,eEAT_NOTIFY_TO_CLIENT,__FUNCTION__,pid) );\
	jNET_SEND2(g_SG.m_World,W_ERROR,jErrorInfo(e,eEAT_DISCON_USER,__FUNCTION__,pid) );\
	return;\
}\






//! PlugIn_Server*p , BYTE buf[1024] , jPlayerObj* pUser
#define READ_PACKET_PS_DCUser(X) READ_PACKET_PS_BS(X);jGet_DCUser(Data.pid,pS);


class PlugIn_Server: public jIPlugIn_Server_IOCP
{
public:
	jPLUGIN_HEADER_CODE(PlugIn_Server);

};

#endif // __PlugIn_Server_header__
