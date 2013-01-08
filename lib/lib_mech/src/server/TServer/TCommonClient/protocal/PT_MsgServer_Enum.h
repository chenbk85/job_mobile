
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_msg.xml)
#pragma once

#ifndef MsgServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_MsgServer(MsgServer);

jxDECL_MsgServer(MG_HELLO);
jxDECL_MsgServer(SS2MG_ONLINE);
jxDECL_MsgServer(MG_ECHO);
jxDECL_MsgServer(MG_SERVERINFO_ACK);
jxDECL_MsgServer(SS2MG_SERVERINFO_ACK);
jxDECL_MsgServer(MG_ERROR);
#endif //MsgServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nMsgServer
{
	enum EMsgServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/1900,
		MG_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1900+1,
		/* jServerInfo si;*/
		
		SS2MG_ONLINE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1900+2,
		/* serverid_t your_sid;*/
		/*[[ 패킷확인용&#x0A; ]]*/
		/* jServerInfo my;*/
		
		MG_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1900+3,
		/* tname256_t msg;*/
		/* int8 type;*/
		
		MG_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1900+4,
		/*[[ SS2MG_ONLINE을 받았을때 보낸쪽의 sid=0일때		
다시 요청하여 받음.		
왜냐면 sid=0이라는예기는 아직 central이나 command로&#x0A;부터 sid를 발급받는중이기때문이다. ]]*/
		/* jServerInfo si;*/
		
		SS2MG_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1900+5,
		/* jServerInfo si;*/
		
		MG_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/1900+6,
		/* jErrorInfo ei;*/
		
		PT_MsgServer_END
	};//enum EMsgServer

	void call_sq_MG_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2MG_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_MG_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_MG_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2MG_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_MG_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef MsgServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_MsgServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // MsgServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nMsgServer
}/* nNET*/ } //nMech

#ifndef MsgServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "MsgServer/MG_HELLO.hpp"
#include "MsgServer/SS2MG_ONLINE.hpp"
#include "MsgServer/MG_ECHO.hpp"
#include "MsgServer/MG_SERVERINFO_ACK.hpp"
#include "MsgServer/SS2MG_SERVERINFO_ACK.hpp"
#include "MsgServer/MG_ERROR.hpp"
#endif // MsgServer_jNOTUSE_PACKET_HPP_INCLUDE