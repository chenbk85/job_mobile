/* file : Recv_TestClient.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-28 17:09:22
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToFrontEnd.h"

#include "../protocal/PT_MonitorServer_Enum.h"
using namespace nMech::nNET::nMonitorServer;



jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{
	jCONSOLE_CMD_AUTO(monitor,send_file,0,"send file to all agent","<szPath> [szRemoteJobThread] [szRemotePath] [agent_ip]")
	{
		#define jCONSOLE_PARAM_send_file(X,Y) X(szPath,tcstr) Y(szRemoteJobThread,tcstr,_T("NULL")) Y(szRemotePath,tcstr,_T("NULL")) Y(agent_ip,tcstr,_T("NULL"))
		jCONSOLE_PARAM_END(send_file);

		jFE_ret(false);


#define jLAMDA_send_file_to_agent(X,Z) X(tcstr,szPath) X(tcstr ,szRemoteJobThread) Z(tcstr ,szRemotePath)
		jLAMDA_for_each(send_file_to_agent,jAgentNode*)
		{
			nswb1024_t buf;
			it->m_pS->SendFile(szPath,szRemoteJobThread,szRemotePath,&WRITE_M2A_SEND_FILE(buf,0,_T("asdf1234") ) );
			
		}
		jLAMDA_end();
		pFE->for_each(send_file_to_agent(szPath,szRemoteJobThread,szRemotePath));
		return true;
	}

	jNET_EVENT_RECEIVER(X2S_LOGIN)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , jAgentNode* pDummy
		READ_PACKET_net_monitor(X2S_LOGIN);
		jt_strcpy(pUser->m_szComputerName, jT(Data.name));
		Get_jIServerMonitor()->On_X2S_LOGIN(Data,pUser->m_uid,pS);
		jNET_SEND(pS,S2X_LOGIN_OK,pUser->m_uid);

	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(S_ECHO)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , jAgentNode* pDummy
		READ_PACKET_net_monitor(S_ECHO);
		pFE->send_all(WRITE_S_ECHO(buf,Data),0);
	}
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2S_THREAD_TEST1)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , jAgentNode* pDummy
		READ_PACKET_net_monitor(X2S_THREAD_TEST1);
		wfname_t szMsg;
		jw_sprintf(szMsg,L"X2S_THREAD_TEST1 thread=%d",GetCurrentThreadId());
		pFE->send_all(WRITE_S_ECHO(buf,Data.type, szMsg),0);

	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(X2S_THREAD_TEST2)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , jAgentNode* pDummy
		READ_PACKET_net_monitor(X2S_THREAD_TEST2);
		wfname_t szMsg;
		jw_sprintf(szMsg,L"X2S_THREAD_TEST2 thread=%d",GetCurrentThreadId());
		pFE->send_all(WRITE_S_ECHO(buf,Data.type, szMsg),0);
	}
#endif
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(A2M_SEND_ERROR_LOG)
	{
		// BYTE buf[1024]  ,jServerMonitor* pSM = g_pjServerMonitor
		READ_PACKET_net_monitor(A2M_SEND_ERROR_LOG);
		fname_t szIP;
		pS->GetAddressString(szIP);
		TCHAR* ch = jt_strchr(szIP,':');
		if(ch)*ch =0;
		GetjILog()->Log(0,_T("\006[%s]%s"),szIP,jT(Data.log));
	}

	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , jAgentNode* pDummy
		READ_PACKET_net_monitor(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)

