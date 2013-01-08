/* file : recv_Common.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-31 15:00:28
comp.: wiki.aqrius.com
title : 
desc : 

*/
using namespace nMech;

#include "Common_code.h"
#include "Common_ConsoleCmd.h"



#include "../TCommonClient/protocal/PT_CentralServer_Enum.h"
using namespace nNET::nCentralServer;
#include "../TCommonClient/protocal/PT_CommandServer_Enum.h"
using namespace nNET::nCommandServer;
#include "../TCommonClient/protocal/PT_UserServer_Enum.h"
using namespace nNET::nUserServer;
#include "../TCommonClient/protocal/PT_MsgServer_Enum.h"
using namespace nNET::nMsgServer;
#include "../TCommonClient/protocal/PT_WorldServer_Enum.h"
using namespace nNET::nWorldServer;
#include "../TCommonClient/protocal/PT_AuctionServer_Enum.h"
using namespace nNET::nAuctionServer;
#include "../TCommonClient/protocal/PT_MailServer_Enum.h"
using namespace nNET::nMailServer;
#include "../TCommonClient/protocal/PT_TradeServer_Enum.h"
using namespace nNET::nTradeServer;
#include "../TCommonClient/protocal/PT_LoginServer_Enum.h"
using namespace nNET::nLoginServer;
#include "../TCommonClient/protocal/PT_ChannelServer_Enum.h"
using namespace nNET::nChannelServer;
#include "../TCommonClient/protocal/PT_GameServer_Enum.h"
using namespace nNET::nGameServer;




jNET_EVENT_BEGIN(PlugIn_Connect) // 내가 접속한 서버로 부터 날라오는 패킷.
{

#include "Recv_Common_ECHO.h"

	namespace _from_common_HELLO_SERVERINFO_ACK 
	{
#define for_each_HELLO(X) \
		X(C		,Central)\
		X(CD	,Command)\
		X(U		,User)\
		X(MG	,Msg)\
		X(W		,World)\
		X(A		,Auction)\
		X(T		,Trade)\
		X(M		,Mail)\
		X(DC	,DBCache)\

#define Recv_HELLO_132(SERVER_TAG,SERVER_NAME)\
		jNET_EVENT_RECEIVER_P2P(SERVER_TAG##_HELLO,SERVER_NAME##Server)			{jRecv_HELLO(SERVER_TAG);	}\
		jNET_EVENT_RECEIVER_P2P(SERVER_TAG##_SERVERINFO_ACK,SERVER_NAME##Server) \
		{\
			READ_PACKET(SERVER_TAG##_SERVERINFO_ACK); nswb1024_t buf;\
			pS->WritePacket(&_jJOIN_3(WRITE_SS2,SERVER_TAG,_SERVERINFO_ACK)(buf,g_SG.m_MyInfo));\
		}\

		for_each_HELLO(Recv_HELLO_132);
	}//namespace _from_common_HELLO_SERVERINFO_ACK 


	namespace _from_nUserServer //UserServer로 부터 날라오는 패킷에 대해 서버 공통적으로 처리하는 코드
	{

#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,UserServer)
		{
			// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
			READ_PACKET(aaa);// 이 서버에 접속할것인지 아니면 무시할것인지 결정.
		}
#endif

	}//namespace _from_nUserServer


	namespace _from_nCommandServer
	{
		jNET_EVENT_RECEIVER_P2P(CD2SS_ONLINE_OK		,CommandServer)	{jRecv_C2SS_ONLINE_OK(CD);}// 서버목록중에서 접속할 서버들에 대해 연결시작.
		jNET_EVENT_RECEIVER_P2P(CD_SERVER_ONLINE	,CommandServer)	{jRecv_C_SERVER_ONLINE(CD);}// 이 서버에 접속할것인지 아니면 무시할것인지 결정.
		jNET_EVENT_RECEIVER_P2P(CD_SERVER_OFFLINE	,CommandServer)	{READ_PACKET(CD_SERVER_OFFLINE);g_SG.ServerInfo_erase(Data.sid);}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(CD2_CENTRAL_RESTART,CommandServer)
		{
			READ_PACKET(CD2_CENTRAL_RESTART);
			jPC();
			jIE* pE = pPC->m_pE->Find(jS(Central));
			if(!pE) return;
			pE->GetAttrVar(jS(ENABLE))->Set_bool(true);
			pPC->m_pClientSession->Start_ClientSocket(pE);
		}
		
#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,CommandServer)
		{
			// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
			//READ_PACKET(aaa);// 이 서버에 접속할것인지 아니면 무시할것인지 결정.
		}
#endif

	}//namespace _from_nCommandServer


	namespace _from_nCentralServer
	{
		jNET_EVENT_RECEIVER_P2P(C2SS_ONLINE_OK,CentralServer)	{jRecv_C2SS_ONLINE_OK(C);}// 서버목록중에서 접속할 서버들에 대해 연결시작.
		jNET_EVENT_RECEIVER_P2P(C_SERVER_ONLINE,CentralServer)	{jRecv_C_SERVER_ONLINE(C);}// 이 서버에 접속할것인지 아니면 무시할것인지 결정.
		jNET_EVENT_RECEIVER_P2P(C_SERVER_OFFLINE,CentralServer)	{READ_PACKET(C_SERVER_OFFLINE);g_SG.ServerInfo_erase(Data.sid);}

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C2_USER_CONNECTION_NOTIFY,CentralServer)
		{
			// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
			READ_PACKET(C2_USER_CONNECTION_NOTIFY);
			g_SG.ServerInfo_update_userCnt(Data.sid,Data.userCnt);

		}
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(C2_SERVER_LOG_LEVEL,CentralServer)
		{
			// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
			READ_PACKET(C2_SERVER_LOG_LEVEL);
			if(!jt_strcmp(Data.type,jS(console)) )
			{
				tname256_t buf;
				js_sprintf(buf, _T("@%s.log_console %s"), jsSERVER_NAME, Data.enable ? jS(true):jS(false) );
				nCONSOLE::Get_jIConsoleCmd()->ParseCmd(buf);
			}
		}
	}//namespace _from_nCentralServer


#ifdef TSERVER_PREPARE
	namespace _from_nTestServer
	{
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(T_ERROR_MSG,DummyServer)
		{
			// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
			READ_PACKET(T_ERROR_MSG);		
			jLOG1(_T("T_ERROR_MSG==%s") , jT(Data.msg));	
		}
	}

	namespace _from_DBCacheServer
	{

	}

	namespace _from_WorldServer
	{

	}

	namespace _from_UserServer
	{

	}
#endif //TSERVER_PREPARE

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(C2_RUN_CONSOLE_CMD,CentralServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		READ_PACKET(C2_RUN_CONSOLE_CMD);
		TCHAR cmd[2048];
		js_sprintf(cmd, "@%s.%s ",Data.category,Data.cmd);
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
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
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
jNET_EVENT_END(PlugIn_Connect)
