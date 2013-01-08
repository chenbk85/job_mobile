
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_central.xml)
#pragma once

#ifndef CentralServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_CentralServer(CentralServer);

jxDECL_CentralServer(C_HELLO);
jxDECL_CentralServer(SS2C_ONLINE);
jxDECL_CentralServer(C_SERVER_ONLINE);
jxDECL_CentralServer(C2SS_ONLINE_OK);
jxDECL_CentralServer(C_SERVERINFO_ACK);
jxDECL_CentralServer(SS2C_SERVERINFO_ACK);
jxDECL_CentralServer(C_SERVER_OFFLINE);
jxDECL_CentralServer(C_ECHO);
jxDECL_CentralServer(C2_LOG_FILE_DAY_CHANGE);
jxDECL_CentralServer(C_ERROR);
jxDECL_CentralServer(CD2C_WELCOME);
jxDECL_CentralServer(C4_USER_CONNECTION_NOTIFY);
jxDECL_CentralServer(C2_USER_CONNECTION_NOTIFY);
jxDECL_CentralServer(C2_NOTICE);
jxDECL_CentralServer(C2_SERVER_LOG_LEVEL);
jxDECL_CentralServer(C2L_DO_USER_DISSCONNECT);
#endif //CentralServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nCentralServer
{
	enum ECentralServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000,
		C_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+1,
		/* jServerInfo si;*/
		
		SS2C_ONLINE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+2,
		/*[[ 주의 : Command서버를 제외한 모든서버는&#x0A;Central restart시에도 보낸다.		
이때 s.m_sid는 0이 아니다. ]]*/
		/* serverid_t your_sid;*/
		/* jServerInfo my;*/
		
		C_SERVER_ONLINE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+3,
		/*[[ 어떤 서버가 CentralServer에 접속했다. ]]*/
		/* jServerInfo s;*/
		
		C2SS_ONLINE_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+4,
		/*[[ 새로운 sid를 발급하고&#x0A;Central에 접속하고 있는 다른서버들정보를 보낸다. ]]*/
		/* jServerInfo you;*/
		/*[[ 새로세팅된정보를다시보냄 ]]*/
		/* jServerInfo s[-1];*/
		
		C_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+5,
		/*[[ Central에서는 C_SERVERINFO_ACK와&#x0A;SS2C_SERVERINFO_ACK는&#x0A;사용하지 않지만 지우지는 말것&#x0A; ]]*/
		/* jServerInfo si;*/
		
		SS2C_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+6,
		/* jServerInfo si;*/
		
		C_SERVER_OFFLINE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+7,
		/* serverid_t sid;*/
		
		C_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+8,
		/* tname256_t msg;*/
		/* int8 type;*/
		
		C2_LOG_FILE_DAY_CHANGE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+9,
		
		C_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+10,
		/* jErrorInfo ei;*/
		
		CD2C_WELCOME=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+11,
		/*[[ 센트랄 서버가 재접속시 보냄 ]]*/
		/* jServerInfo my;*/
		/* jServerInfo s[-1];*/
		
		C4_USER_CONNECTION_NOTIFY=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+12,
		/*[[ 6초정도의 딜레이후 보낸다. ]]*/
		/* uint16 userCnt;*/
		
		C2_USER_CONNECTION_NOTIFY=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+13,
		/*[[ 약 3~6초간 딜레이후 전달&#x0A;던젼서버의 경우 해당 월드의 모든 Town서버에 전달&#x0A;마을서버의 경우 모든 로긴서버에 전달. ]]*/
		/* serverid_t sid[-1];*/
		/* uint16 userCnt[-1];*/
		
		C2_NOTICE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+14,
		/* jNoticeInfo info;*/
		/* wname1024_t msg;*/
		/* aname32_t date;*/
		
		C2_SERVER_LOG_LEVEL=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+15,
		/* tname32_t type;*/
		/* bool enable;*/
		
		C2L_DO_USER_DISSCONNECT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+16,
		/* player_id_t pid[-1];*/
		
		PT_CentralServer_END
	};//enum ECentralServer

	void call_sq_C_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2C_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_C_SERVER_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_C2SS_ONLINE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_C_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2C_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_C_SERVER_OFFLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_C_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_C2_LOG_FILE_DAY_CHANGE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_C_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CD2C_WELCOME(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_C4_USER_CONNECTION_NOTIFY(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_C2_USER_CONNECTION_NOTIFY(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_C2_NOTICE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_C2_SERVER_LOG_LEVEL(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_C2L_DO_USER_DISSCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef CentralServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_CentralServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // CentralServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nCentralServer
}/* nNET*/ } //nMech

#ifndef CentralServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "CentralServer/C_HELLO.hpp"
#include "CentralServer/SS2C_ONLINE.hpp"
#include "CentralServer/C_SERVER_ONLINE.hpp"
#include "CentralServer/C2SS_ONLINE_OK.hpp"
#include "CentralServer/C_SERVERINFO_ACK.hpp"
#include "CentralServer/SS2C_SERVERINFO_ACK.hpp"
#include "CentralServer/C_SERVER_OFFLINE.hpp"
#include "CentralServer/C_ECHO.hpp"
#include "CentralServer/C2_LOG_FILE_DAY_CHANGE.hpp"
#include "CentralServer/C_ERROR.hpp"
#include "CentralServer/CD2C_WELCOME.hpp"
#include "CentralServer/C4_USER_CONNECTION_NOTIFY.hpp"
#include "CentralServer/C2_USER_CONNECTION_NOTIFY.hpp"
#include "CentralServer/C2_NOTICE.hpp"
#include "CentralServer/C2_SERVER_LOG_LEVEL.hpp"
#include "CentralServer/C2L_DO_USER_DISSCONNECT.hpp"
#endif // CentralServer_jNOTUSE_PACKET_HPP_INCLUDE