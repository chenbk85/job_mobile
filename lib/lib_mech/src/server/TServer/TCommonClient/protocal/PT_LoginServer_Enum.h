
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_login.xml)
#pragma once

#ifndef LoginServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_LoginServer(LoginServer);

jxDECL_LoginServer(L_ERROR);
jxDECL_LoginServer(L_ECHO);
jxDECL_LoginServer(L_HELLO);
jxDECL_LoginServer(L2X_NOTICE);
jxDECL_LoginServer(X2L_LOGIN);
jxDECL_LoginServer(L2X_USER_LOGIN_OK);
jxDECL_LoginServer(X2L_GET_CHANNEL_LIST);
jxDECL_LoginServer(L2X_CHANNEL_LIST);
jxDECL_LoginServer(X2L_GET_WORLD_LIST);
jxDECL_LoginServer(L2X_WORLD_LIST);
jxDECL_LoginServer(X2L_USER_LOGIN);
jxDECL_LoginServer(X2L_USER_EXIT);
jxDECL_LoginServer(L2X_USER_EXIT);
jxDECL_LoginServer(X2L_CHANNEL_SELECT);
jxDECL_LoginServer(L2X_CHANNEL_SELECT_RESULT);
#endif //LoginServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nLoginServer
{
	enum ELoginServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/2000,
		L_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+1,
		/* jErrorInfo ei;*/
		
		L_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+2,
		/* tname256_t msg;*/
		/* int8 type;*/
		
		L_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+3,
		/* jServerInfo si;*/
		
		L2X_NOTICE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+4,
		/* jNoticeInfo info;*/
		/* wname1024_t msg;*/
		/* aname32_t date;*/
		
		X2L_LOGIN=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+5,
		
		L2X_USER_LOGIN_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+6,
		/* player_id_t pid;*/
		/* serverid_t channel[-1];*/
		/* astring channel_name[-1];*/
		/* uint8 buzy_level[-1];*/
		
		X2L_GET_CHANNEL_LIST=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+7,
		/* aname32_t world;*/
		
		L2X_CHANNEL_LIST=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+8,
		/*[[ 각 인터넷업체별(또한 성별) 개설된 월드리스트받기&#x0A;		
world이름은 xml로 존재한다. data/xml/world_servers.xml		
해당 월드서버리스트를 보냄( 클라이언트에서는 캐슁하세요)&#x0A;약 5분이 경과했을때 다시 요청하는게 좋음. ]]*/
		/* serverid_t channel[-1];*/
		/* astring channel_name[-1];*/
		/* uint8 buzy_level[-1];*/
		
		X2L_GET_WORLD_LIST=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+9,
		
		L2X_WORLD_LIST=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+10,
		/* jWorldServerInfo worlds[-1];*/
		
		X2L_USER_LOGIN=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+11,
		/*[[ 클라이언트 로긴접속&#x0A; ]]*/
		/* aname32_t world;*/
		/* wname64_t id;*/
		/* uint8 pwd[-1];*/
		/* aname32_t ver;*/
		/* aname32_t cpp_ver;*/
		
		X2L_USER_EXIT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+12,
		
		L2X_USER_EXIT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+13,
		
		X2L_CHANNEL_SELECT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+14,
		/* serverid_t sid;*/
		
		L2X_CHANNEL_SELECT_RESULT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+15,
		/* jError e;*/
		/* aname32_t ip;*/
		/* uint16 port;*/
		/* player_id_t pid;*/
		
		PT_LoginServer_END
	};//enum ELoginServer

	void call_sq_L_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_L_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_L_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_L2X_NOTICE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2L_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_L2X_USER_LOGIN_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2L_GET_CHANNEL_LIST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_L2X_CHANNEL_LIST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2L_GET_WORLD_LIST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_L2X_WORLD_LIST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2L_USER_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2L_USER_EXIT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_L2X_USER_EXIT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2L_CHANNEL_SELECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_L2X_CHANNEL_SELECT_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef LoginServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_LoginServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // LoginServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nLoginServer
}/* nNET*/ } //nMech

#ifndef LoginServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "LoginServer/L_ERROR.hpp"
#include "LoginServer/L_ECHO.hpp"
#include "LoginServer/L_HELLO.hpp"
#include "LoginServer/L2X_NOTICE.hpp"
#include "LoginServer/X2L_LOGIN.hpp"
#include "LoginServer/L2X_USER_LOGIN_OK.hpp"
#include "LoginServer/X2L_GET_CHANNEL_LIST.hpp"
#include "LoginServer/L2X_CHANNEL_LIST.hpp"
#include "LoginServer/X2L_GET_WORLD_LIST.hpp"
#include "LoginServer/L2X_WORLD_LIST.hpp"
#include "LoginServer/X2L_USER_LOGIN.hpp"
#include "LoginServer/X2L_USER_EXIT.hpp"
#include "LoginServer/L2X_USER_EXIT.hpp"
#include "LoginServer/X2L_CHANNEL_SELECT.hpp"
#include "LoginServer/L2X_CHANNEL_SELECT_RESULT.hpp"
#endif // LoginServer_jNOTUSE_PACKET_HPP_INCLUDE