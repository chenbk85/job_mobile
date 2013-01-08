
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_trade.xml)
#pragma once

#ifndef TradeServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_TradeServer(TradeServer);

jxDECL_TradeServer(T_HELLO);
jxDECL_TradeServer(SS2T_ONLINE);
jxDECL_TradeServer(T_SERVERINFO_ACK);
jxDECL_TradeServer(SS2T_SERVERINFO_ACK);
jxDECL_TradeServer(T_ECHO);
jxDECL_TradeServer(T_ERROR);
#endif //TradeServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nTradeServer
{
	enum ETradeServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/7200,
		T_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7200+1,
		/* jServerInfo si;*/
		
		SS2T_ONLINE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7200+2,
		/*[[ T_HELLO에 대한 응답. ]]*/
		/* serverid_t your_sid;*/
		/*[[ 확인용패킷 ]]*/
		/* jServerInfo my;*/
		
		T_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7200+3,
		/*[[ SS2T_ONLINE을 받았을때 보낸쪽의 sid=0일때		
다시 요청하여 받음.		
왜냐면 sid=0이라는예기는 아직 central이나 command로&#x0A;부터 sid를 발급받는중이기때문이다. ]]*/
		/* jServerInfo si;*/
		
		SS2T_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7200+4,
		/* jServerInfo si;*/
		
		T_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7200+5,
		/* tname256_t msg;*/
		/* int8 type;*/
		
		T_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7200+6,
		/* jErrorInfo ei;*/
		
		PT_TradeServer_END
	};//enum ETradeServer

	void call_sq_T_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2T_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_T_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2T_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_T_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_T_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef TradeServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_TradeServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // TradeServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nTradeServer
}/* nNET*/ } //nMech

#ifndef TradeServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "TradeServer/T_HELLO.hpp"
#include "TradeServer/SS2T_ONLINE.hpp"
#include "TradeServer/T_SERVERINFO_ACK.hpp"
#include "TradeServer/SS2T_SERVERINFO_ACK.hpp"
#include "TradeServer/T_ECHO.hpp"
#include "TradeServer/T_ERROR.hpp"
#endif // TradeServer_jNOTUSE_PACKET_HPP_INCLUDE