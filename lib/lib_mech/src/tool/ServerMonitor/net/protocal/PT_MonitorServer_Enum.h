
//from(z:\src\tool\servermonitor\net\sequence\monitorprotocal\..\..\protocal\pt_monitorserver.xml)
#pragma once

#ifndef MonitorServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_MonitorServer(MonitorServer);

jxDECL_MonitorServer(M2A_SEND_FILE);
jxDECL_MonitorServer(S_HELLO);
jxDECL_MonitorServer(X2S_LOGIN);
jxDECL_MonitorServer(S2X_LOGIN_OK);
jxDECL_MonitorServer(S_ECHO);
jxDECL_MonitorServer(X2S_THREAD_TEST1);
jxDECL_MonitorServer(X2S_THREAD_TEST2);
jxDECL_MonitorServer(M2A_CALL_CMD_RQ);
jxDECL_MonitorServer(A2M_CALL_CMD_RS);
jxDECL_MonitorServer(A2M_NOTIFY_SERVER_INFO);
jxDECL_MonitorServer(A2M_SERVER_CONNECTED);
jxDECL_MonitorServer(M2A_MYTHOLOGY_MENU_RQ);
jxDECL_MonitorServer(A2M_MYTHOLOGY_MENU_RS);
jxDECL_MonitorServer(A2M_PROCESS_STATUS_NOTIFY);
jxDECL_MonitorServer(A2M_PROCESS_INFO_NOTIFY);
jxDECL_MonitorServer(M2A_PROCESS_INFO_UPDATE);
jxDECL_MonitorServer(A2M_SEND_ERROR_LOG);
jxDECL_MonitorServer(M2A_RESET_ERROR_LOG_COUNT);
jxDECL_MonitorServer(M2A_RUN_EXE);
#endif //MonitorServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nMonitorServer
{
	enum EMonitorServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000,
		M2A_SEND_FILE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+1,
		/* int type;*/
		/* tstring target_dir;*/
		
		S_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+2,
		
		X2S_LOGIN=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+3,
		/*[[ 콤마로 구분된 스트링 : eLOGIN콤마EXE_NAME ]]*/
		/* wname32_t name;*/
		/* aname32_t ip;*/
		/* astring servers[-1];*/
		/* tstring states[-1];*/
		
		S2X_LOGIN_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+4,
		/* int32 did;*/
		
		S_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+5,
		/* uint8 type;*/
		/* wstring msg;*/
		
		X2S_THREAD_TEST1=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+6,
		/* uint8 type;*/
		/* wstring msg;*/
		
		X2S_THREAD_TEST2=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+7,
		/* uint8 type;*/
		/* wstring msg;*/
		
		M2A_CALL_CMD_RQ=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+8,
		/*[[ type이 eSS_AGENT이면 AGENT에 대한 콘솔명령실행&#x0A; ]]*/
		/* tstring eServerType;*/
		/* wstring cmd;*/
		
		A2M_CALL_CMD_RS=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+9,
		/* tstring eServerType;*/
		/* wstring cmd;*/
		
		A2M_NOTIFY_SERVER_INFO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+10,
		/* tstring eServerType;*/
		/* wstring info;*/
		/* tstring eState;*/
		
		A2M_SERVER_CONNECTED=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+11,
		/* tstring eServerType;*/
		/* tstring eServerState;*/
		
		M2A_MYTHOLOGY_MENU_RQ=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+12,
		/* tstring eServerType;*/
		/* astring cmd;*/
		
		A2M_MYTHOLOGY_MENU_RS=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+13,
		/* tstring eServerType;*/
		/* astring cmd;*/
		
		A2M_PROCESS_STATUS_NOTIFY=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+14,
		/* astring eServerType;*/
		/* astring eState;*/
		
		A2M_PROCESS_INFO_NOTIFY=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+15,
		/* aname32_t eServerType;*/
		/* wstring name;*/
		/* wstring value;*/
		
		M2A_PROCESS_INFO_UPDATE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+16,
		/* tstring eServerType;*/
		/* wstring name;*/
		/* wstring value;*/
		
		A2M_SEND_ERROR_LOG=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+17,
		/* aname32_t eServerType;*/
		/* wstring log;*/
		
		M2A_RESET_ERROR_LOG_COUNT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+18,
		
		M2A_RUN_EXE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+19,
		/* int type;*/
		/* wstring option;*/
		/* wstring cmd;*/
		
		PT_MonitorServer_END
	};//enum EMonitorServer

	void call_sq_M2A_SEND_FILE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_S_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2S_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_S2X_LOGIN_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_S_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2S_THREAD_TEST1(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2S_THREAD_TEST2(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_M2A_CALL_CMD_RQ(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_A2M_CALL_CMD_RS(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_A2M_NOTIFY_SERVER_INFO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_A2M_SERVER_CONNECTED(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_M2A_MYTHOLOGY_MENU_RQ(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_A2M_MYTHOLOGY_MENU_RS(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_A2M_PROCESS_STATUS_NOTIFY(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_A2M_PROCESS_INFO_NOTIFY(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_M2A_PROCESS_INFO_UPDATE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_A2M_SEND_ERROR_LOG(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_M2A_RESET_ERROR_LOG_COUNT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_M2A_RUN_EXE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef MonitorServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_MonitorServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // MonitorServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nMonitorServer
}/* nNET*/ } //nMech

#ifndef MonitorServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "MonitorServer/M2A_SEND_FILE.hpp"
#include "MonitorServer/S_HELLO.hpp"
#include "MonitorServer/X2S_LOGIN.hpp"
#include "MonitorServer/S2X_LOGIN_OK.hpp"
#include "MonitorServer/S_ECHO.hpp"
#include "MonitorServer/X2S_THREAD_TEST1.hpp"
#include "MonitorServer/X2S_THREAD_TEST2.hpp"
#include "MonitorServer/M2A_CALL_CMD_RQ.hpp"
#include "MonitorServer/A2M_CALL_CMD_RS.hpp"
#include "MonitorServer/A2M_NOTIFY_SERVER_INFO.hpp"
#include "MonitorServer/A2M_SERVER_CONNECTED.hpp"
#include "MonitorServer/M2A_MYTHOLOGY_MENU_RQ.hpp"
#include "MonitorServer/A2M_MYTHOLOGY_MENU_RS.hpp"
#include "MonitorServer/A2M_PROCESS_STATUS_NOTIFY.hpp"
#include "MonitorServer/A2M_PROCESS_INFO_NOTIFY.hpp"
#include "MonitorServer/M2A_PROCESS_INFO_UPDATE.hpp"
#include "MonitorServer/A2M_SEND_ERROR_LOG.hpp"
#include "MonitorServer/M2A_RESET_ERROR_LOG_COUNT.hpp"
#include "MonitorServer/M2A_RUN_EXE.hpp"
#endif // MonitorServer_jNOTUSE_PACKET_HPP_INCLUDE