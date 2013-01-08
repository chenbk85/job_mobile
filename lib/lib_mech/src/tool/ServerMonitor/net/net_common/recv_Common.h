/* file : recv_Common.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-31 15:00:28
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "network/protocal/PT_CentralServer_Enum.h"
using namespace nNET::nCentralServer;

#include "network/protocal/PT_UserServer_Enum.h"
using namespace nNET::nUserServer;

#include "network/protocal/PT_WorldServer_Enum.h"
using namespace nNET::nWorldServer;

#include "network/protocal/PT_TestServer_Enum.h"
using namespace nNET::nTestServer;

#include "network/protocal/PT_DBCacheServer_Enum.h"
using namespace nNET::nDBCacheServer;


jPlugIn_BE_Helper* g_pjPlugIn_BE_Helper=0;

void jMsg_C4_USER_CONNECTION_NOTIFY(nEVENT::jIMessage*)
{
	nswb16000_t buf;
	if(g_pjPlugIn_BE_Helper->m_pToCentral)
	{
		static uint16 oldCnt=0;
		uint16 currCnt = g_pjPlugIn_BE_Helper->Get_CURR_USER();
		if(oldCnt!=currCnt)
		{
			oldCnt=currCnt;
			g_pjPlugIn_BE_Helper->m_pToCentral->WritePacket(&WRITE_C4_USER_CONNECTION_NOTIFY(buf, currCnt));
		}
	}
	if(g_pjPlugIn_BE_Helper->m_pToUser)
	{
		vector<astring> uid_connect,uid_disconnect;
		if( g_pjPlugIn_BE_Helper->Make_U4_USER_CONNECTION_NOTIFY(uid_connect,uid_disconnect) )
		{
			g_pjPlugIn_BE_Helper->m_pToUser->WritePacket(&WRITE_U4_USER_CONNECTION_NOTIFY(buf, uid_connect, uid_disconnect));
			if(g_pjPlugIn_BE_Helper->m_MyInfo.m_eType==jServerInfo::eTown 
				|| g_pjPlugIn_BE_Helper->m_MyInfo.m_eType==jServerInfo::eDungeon)
			{
				if(uid_disconnect.size()&&g_pjPlugIn_BE_Helper->m_pToWorld)
					g_pjPlugIn_BE_Helper->m_pToWorld->WritePacket(&nWorldServer::WRITE_W4_USER_DISCONNECT(buf, uid_disconnect));
			}

		}
	}
}



jCONSOLE_CMD_AUTO(jSERVER_NAME,log_console,0,"On/off console log ","<bool>")
{
	#define jCONSOLE_PARAM_log_console(X,Y) X(is,bool)
	jCONSOLE_PARAM_END(log_console);
	jSET_CON_FLAG(exe,LOG_OFF,is);
	return true;
}

jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{
	namespace _from_nCentralServer
	{
		using namespace nCentralServer;


		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C_ECHO,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			READ_PACKET(C_ECHO);		
			//GetjILog()->Log(_T("C_ECHO==%s") , jT(Data.msg));	
			if(g_pjPlugIn_BE_Helper->Call_C_ECHO(Data.msg)) return;

			if(Data.msg[0]!='$') return;
			wfname_t szTag;
			jw_strcpy(szTag, Data.msg+1);
			WCHAR *ch = jw_strchr(szTag, ' ');
			WCHAR * szCmd= ch+1;
			*ch =0;
			if(jw_strcmp(szTag,L"ALL") 
				&& g_pjPlugIn_BE_Helper->m_MyInfo.GetServerType() != g_pjPlugIn_BE_Helper->m_MyInfo.GetServerTypeByTag(jT(szTag))) return;
			
			tstring strCmd = jT(szCmd);
			nSTL::replace(strCmd,_T("APP_NAME"),jsSERVER_NAME);
			nCONSOLE::Get_jIConsoleCmd()->ParseCmd(jT(strCmd.c_str())); 

		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C_SERVER_OFFLINE,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			READ_PACKET(C_SERVER_OFFLINE);
			int sid = Data.sid;
			nXML::jE e = g_pjPlugIn_BE_Helper->m_eServers->FindByFirstAttr(jS(m_sid),jIVar::EDint , &sid);
			if(e.empty())
			{
				GetjILog()->Warning(jFUNC1 _T("sid(%d) not found") , Data.sid);
				return;
			}
			e->Erase();
		}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C2_USER_CONNECTION_NOTIFY,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			READ_PACKET(C2_USER_CONNECTION_NOTIFY);
			for(int i=0; i< Data.sid.size() ; ++i)
			{
				g_pjPlugIn_BE_Helper->SetServerInfo_UserCount(Data.sid[i], Data.userCnt[i]);
			}
		}
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C2_SERVER_LOG_LEVEL,CentralServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			READ_PACKET(C2_SERVER_LOG_LEVEL);
			if(!jt_strcmp(Data.type,jS(console)) )
			{
				tname256_t buf;
				jt_sprintf(buf, _T("@%s.log_console %s"), jsSERVER_NAME, Data.enable ? jS(true):jS(false) );
				nCONSOLE::Get_jIConsoleCmd()->ParseCmd(buf);
			}

		}

		


	}//namespace _from_nCentralServer

	namespace _from_nTestServer
	{
		using namespace nTestServer;
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(T_ERROR_MSG,TestServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			READ_PACKET(T_ERROR_MSG);		
			GetjILog()->Log(_T("T_ERROR_MSG==%s") , jT(Data.msg));	
		}

	}

	namespace _from_DBCacheServer
	{
		using namespace nDBCacheServer;
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(DC_ECHO,DBCacheServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			READ_PACKET(DC_ECHO);
		}
	}

	namespace _from_WorldServer
	{
		using namespace nWorldServer;
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(W_ECHO,WorldServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			READ_PACKET(W_ECHO);
		}
	}

	namespace _from_UserServer
	{
		using namespace nUserServer;
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(U_ECHO,UserServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			READ_PACKET(U_ECHO);
		}
	}
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(C2_RUN_CONSOLE_CMD,CentralServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		READ_PACKET(C2_RUN_CONSOLE_CMD);
		TCHAR cmd[2048];
		jt_sprintf(cmd, "@%s.%s ",Data.category,Data.cmd);
		for(int i=0; i< Data.arg .size() ; ++i)
		{
			jt_strcat(cmd, Data.arg[0].c_str());
			jt_strcat(cmd, _T(" "));
		}
		nCONSOLE::Get_jIConsoleCmd()->ParseCmd(cmd);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(C2_SERVER_LOG_LEVEL,CentralServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		READ_PACKET(C2_SERVER_LOG_LEVEL);
		if(tstring(_T("console")) == Data.type)
		{
			jIVar* pv_LOG_TO_FILE = nCONSOLE::Get_jIConsoleVar()->GetVar(jS(exe),jS(LOG_TO_FILE));
			if(pv_LOG_TO_FILE)
			{
				pv_LOG_TO_FILE->Set_bool(!Data.enable);
			}
		}
	}
#endif
}
jNET_EVENT_END(PlugIn_ToBackEnd)



