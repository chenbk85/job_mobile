
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_game.xml)
#pragma once

#ifndef GameServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_GameServer(GameServer);

jxDECL_GameServer(G_ECHO);
jxDECL_GameServer(G_ERROR);
jxDECL_GameServer(G_HELLO);
jxDECL_GameServer(D2X_NOTICE);
jxDECL_GameServer(X2D_NOTICE_TEST);
jxDECL_GameServer(D_ECHO);
jxDECL_GameServer(X2G_CHAT);
jxDECL_GameServer(G2X_CHAT);
jxDECL_GameServer(X2G_USER_EXIT);
jxDECL_GameServer(G2X_USER_EXIT);
#endif //GameServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nGameServer
{
	enum EGameServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/3000,
		G_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/3000+1,
		/* tname256_t msg;*/
		/* uint8 type;*/
		
		G_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/3000+2,
		/* jErrorInfo ei;*/
		
		G_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/3000+3,
		/* jServerInfo si;*/
		
		D2X_NOTICE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/3000+4,
		/* jNoticeInfo info;*/
		/* wname1024_t msg;*/
		/* aname32_t date;*/
		
		X2D_NOTICE_TEST=/*nMech::nNET::EProtocal_jINet_OGS_END+*/3000+5,
		/* jNoticeInfo info;*/
		/* wname1024_t msg;*/
		/* aname32_t date;*/
		
		D_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/3000+6,
		
		X2G_CHAT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/3000+7,
		/* wname64_t msg;*/
		/* uint8 type;*/
		/* wstring id[-1];*/
		/* player_id_t pid[-1];*/
		
		G2X_CHAT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/3000+8,
		/* wname64_t msg;*/
		/* uint8 type;*/
		
		X2G_USER_EXIT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/3000+9,
		
		G2X_USER_EXIT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/3000+10,
		
		PT_GameServer_END
	};//enum EGameServer

	void call_sq_G_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_G_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_G_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_D2X_NOTICE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2D_NOTICE_TEST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_D_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2G_CHAT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_G2X_CHAT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2G_USER_EXIT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_G2X_USER_EXIT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef GameServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_GameServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // GameServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nGameServer
}/* nNET*/ } //nMech

#ifndef GameServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "GameServer/G_ECHO.hpp"
#include "GameServer/G_ERROR.hpp"
#include "GameServer/G_HELLO.hpp"
#include "GameServer/D2X_NOTICE.hpp"
#include "GameServer/X2D_NOTICE_TEST.hpp"
#include "GameServer/D_ECHO.hpp"
#include "GameServer/X2G_CHAT.hpp"
#include "GameServer/G2X_CHAT.hpp"
#include "GameServer/X2G_USER_EXIT.hpp"
#include "GameServer/G2X_USER_EXIT.hpp"
#endif // GameServer_jNOTUSE_PACKET_HPP_INCLUDE