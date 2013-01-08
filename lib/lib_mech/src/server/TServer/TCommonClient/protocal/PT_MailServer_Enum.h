
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_mail.xml)
#pragma once

#ifndef MailServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_MailServer(MailServer);

jxDECL_MailServer(M_HELLO);
jxDECL_MailServer(SS2M_ONLINE);
jxDECL_MailServer(M_SERVERINFO_ACK);
jxDECL_MailServer(SS2M_SERVERINFO_ACK);
jxDECL_MailServer(M_ECHO);
jxDECL_MailServer(M_ERROR);
#endif //MailServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nMailServer
{
	enum EMailServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/7000,
		M_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7000+1,
		/* jServerInfo si;*/
		
		SS2M_ONLINE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7000+2,
		/*[[ M_HELLO에 대한 응답. ]]*/
		/* serverid_t your_sid;*/
		/*[[ 확인용패킷 ]]*/
		/* jServerInfo my;*/
		
		M_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7000+3,
		/*[[ SS2M_ONLINE을 받았을때 보낸쪽의 sid=0일때		
다시 요청하여 받음.		
왜냐면 sid=0이라는예기는 아직 central이나 command로&#x0A;부터 sid를 발급받는중이기때문이다. ]]*/
		/* jServerInfo si;*/
		
		SS2M_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7000+4,
		/* jServerInfo si;*/
		
		M_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7000+5,
		/* tname256_t msg;*/
		/* int8 type;*/
		
		M_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7000+6,
		/* jErrorInfo ei;*/
		
		PT_MailServer_END
	};//enum EMailServer

	void call_sq_M_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2M_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_M_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2M_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_M_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_M_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef MailServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_MailServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // MailServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nMailServer
}/* nNET*/ } //nMech

#ifndef MailServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "MailServer/M_HELLO.hpp"
#include "MailServer/SS2M_ONLINE.hpp"
#include "MailServer/M_SERVERINFO_ACK.hpp"
#include "MailServer/SS2M_SERVERINFO_ACK.hpp"
#include "MailServer/M_ECHO.hpp"
#include "MailServer/M_ERROR.hpp"
#endif // MailServer_jNOTUSE_PACKET_HPP_INCLUDE