
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_auction.xml)
#pragma once

#ifndef AuctionServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_AuctionServer(AuctionServer);

jxDECL_AuctionServer(A_HELLO);
jxDECL_AuctionServer(SS2A_ONLINE);
jxDECL_AuctionServer(A_SERVERINFO_ACK);
jxDECL_AuctionServer(SS2A_SERVERINFO_ACK);
jxDECL_AuctionServer(A_ECHO);
jxDECL_AuctionServer(A_ERROR);
#endif //AuctionServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nAuctionServer
{
	enum EAuctionServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/7300,
		A_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7300+1,
		/* jServerInfo si;*/
		
		SS2A_ONLINE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7300+2,
		/*[[ A_HELLO�� ���� ����. ]]*/
		/* serverid_t your_sid;*/
		/*[[ Ȯ�ο� &#x0A; ]]*/
		/* jServerInfo my;*/
		
		A_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7300+3,
		/*[[ SS2A_ONLINE�� �޾����� �������� sid=0�϶�		
�ٽ� ��û�Ͽ� ����.		
�ֳĸ� sid=0�̶�¿���� ���� central�̳� command��&#x0A;���� sid�� �߱޹޴����̱⶧���̴�. ]]*/
		/* jServerInfo si;*/
		
		SS2A_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7300+4,
		/* jServerInfo si;*/
		
		A_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7300+5,
		/* tname256_t msg;*/
		/* int8 type;*/
		
		A_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/7300+6,
		/* jErrorInfo ei;*/
		
		PT_AuctionServer_END
	};//enum EAuctionServer

	void call_sq_A_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2A_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_A_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2A_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_A_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_A_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef AuctionServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_AuctionServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // AuctionServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nAuctionServer
}/* nNET*/ } //nMech

#ifndef AuctionServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "AuctionServer/A_HELLO.hpp"
#include "AuctionServer/SS2A_ONLINE.hpp"
#include "AuctionServer/A_SERVERINFO_ACK.hpp"
#include "AuctionServer/SS2A_SERVERINFO_ACK.hpp"
#include "AuctionServer/A_ECHO.hpp"
#include "AuctionServer/A_ERROR.hpp"
#endif // AuctionServer_jNOTUSE_PACKET_HPP_INCLUDE