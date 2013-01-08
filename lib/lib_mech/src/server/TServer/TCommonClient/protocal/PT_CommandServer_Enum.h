
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_command.xml)
#pragma once

#ifndef CommandServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_CommandServer(CommandServer);

jxDECL_CommandServer(CD_HELLO);
jxDECL_CommandServer(SS2CD_ONLINE);
jxDECL_CommandServer(CD2SS_ONLINE_OK);
jxDECL_CommandServer(CD_ECHO);
jxDECL_CommandServer(CD_SERVER_ONLINE);
jxDECL_CommandServer(CD_SERVER_OFFLINE);
jxDECL_CommandServer(CD_SERVERINFO_ACK);
jxDECL_CommandServer(SS2CD_SERVERINFO_ACK);
jxDECL_CommandServer(CD_ERROR);
jxDECL_CommandServer(CD2_CENTRAL_RESTART);
#endif //CommandServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nCommandServer
{
	enum ECommandServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/1500,
		CD_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1500+1,
		/* jServerInfo si;*/
		
		SS2CD_ONLINE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1500+2,
		/*[[ 어떤 서버가 CommandServer에 접속했다.		
만약 CentralServer가 죽었고 si.m_sid==0이면 &#x0A;Command가 sid를 발급해준다. ]]*/
		/* serverid_t your_sid;*/
		/* jServerInfo my;*/
		
		CD2SS_ONLINE_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1500+3,
		/*[[ Central서버가 죽었을때만 대신 해서 보냄.		
Command에 접속하고 있는 다른서버들정보를 보낸다. ]]*/
		/* jServerInfo you;*/
		/* jServerInfo s[-1];*/
		
		CD_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1500+4,
		/* tname256_t msg;*/
		/* int8 type;*/
		
		CD_SERVER_ONLINE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1500+5,
		/* jServerInfo s;*/
		
		CD_SERVER_OFFLINE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1500+6,
		/* serverid_t sid;*/
		
		CD_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1500+7,
		/*[[ SS2CD_ONLINE을 받았을때 보낸쪽의 sid=0일때		
다시 요청하여 받음. ]]*/
		/* jServerInfo si;*/
		
		SS2CD_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1500+8,
		/* jServerInfo si;*/
		
		CD_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1500+9,
		/* jErrorInfo ei;*/
		
		CD2_CENTRAL_RESTART=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1500+10,
		/*[[ CentralServer 재시작을 모든서버에 통보 ]]*/
		
		PT_CommandServer_END
	};//enum ECommandServer

	void call_sq_CD_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2CD_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CD2SS_ONLINE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CD_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CD_SERVER_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CD_SERVER_OFFLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CD_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2CD_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CD_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CD2_CENTRAL_RESTART(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef CommandServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_CommandServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // CommandServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nCommandServer
}/* nNET*/ } //nMech

#ifndef CommandServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "CommandServer/CD_HELLO.hpp"
#include "CommandServer/SS2CD_ONLINE.hpp"
#include "CommandServer/CD2SS_ONLINE_OK.hpp"
#include "CommandServer/CD_ECHO.hpp"
#include "CommandServer/CD_SERVER_ONLINE.hpp"
#include "CommandServer/CD_SERVER_OFFLINE.hpp"
#include "CommandServer/CD_SERVERINFO_ACK.hpp"
#include "CommandServer/SS2CD_SERVERINFO_ACK.hpp"
#include "CommandServer/CD_ERROR.hpp"
#include "CommandServer/CD2_CENTRAL_RESTART.hpp"
#endif // CommandServer_jNOTUSE_PACKET_HPP_INCLUDE