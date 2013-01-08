
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_user.xml)
#pragma once

#ifndef UserServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_UserServer(UserServer);

jxDECL_UserServer(U4_USER_CONNECTION_NOTIFY);
jxDECL_UserServer(U_HELLO);
jxDECL_UserServer(SS2U_ONLINE);
jxDECL_UserServer(W2U_ONLINE_USERS);
jxDECL_UserServer(L2U_ONLINE_USERS);
jxDECL_UserServer(U_SERVERINFO_ACK);
jxDECL_UserServer(SS2U_SERVERINFO_ACK);
jxDECL_UserServer(U2SS_ONLINE_OK);
jxDECL_UserServer(U_ECHO);
jxDECL_UserServer(U_ERROR);
jxDECL_UserServer(L2U_USER_LOGIN);
jxDECL_UserServer(U2L_USER_LOGIN_RESULT);
jxDECL_UserServer(U2W_USER_LOGIN);
jxDECL_UserServer(W2U_USER_LOGIN_RESULT);
jxDECL_UserServer(U2W_USER_LOGIN_DUPLICATE);
jxDECL_UserServer(W2U_USER_LOGIN_DUPLICATE_OK);
jxDECL_UserServer(U2W_USER_DISCONNECT);
jxDECL_UserServer(U2L_DO_USER_DISCONNECT);
#endif //UserServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nUserServer
{
	enum EUserServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/4000,
		U4_USER_CONNECTION_NOTIFY=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+1,
		/*[[ 약3초정도의 딜레이후 보낸다. ]]*/
		/* wstring id_connect[-1];*/
		/* wstring id_disconnect[-1];*/
		
		U_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+2,
		/* jServerInfo si;*/
		
		SS2U_ONLINE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+3,
		/* serverid_t your_sid;*/
		/*[[ 확인용패킷 ]]*/
		/* jServerInfo my;*/
		
		W2U_ONLINE_USERS=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+4,
		/*[[ UserServer가 비정상종료했을때 보냄 ]]*/
		/* player_id_t pid[-1];*/
		/* wstring id[-1];*/
		/* serverid_t town[-1];*/
		/*[[ 접속한 타운서버 ]]*/
		
		L2U_ONLINE_USERS=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+5,
		/*[[ UserServer가 비정상종료했을때		
 LoginServer가 보냄 ]]*/
		/* player_id_t pid[-1];*/
		/* wstring id[-1];*/
		
		U_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+6,
		/*[[ SS2U_ONLINE을 받았을때 보낸쪽의 sid=0일때		
다시 요청하여 받음.		
왜냐면 sid=0이라는예기는 아직 central이나 command로&#x0A;부터 sid를 발급받는중이기때문이다. ]]*/
		/* jServerInfo si;*/
		
		SS2U_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+7,
		/* jServerInfo si;*/
		
		U2SS_ONLINE_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+8,
		/* serverid_t your_sid;*/
		
		U_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+9,
		/* tname256_t msg;*/
		/* int8 type;*/
		
		U_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+10,
		/* jErrorInfo ei;*/
		
		L2U_USER_LOGIN=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+11,
		/* serverid_t world;*/
		/* wname64_t id;*/
		
		U2L_USER_LOGIN_RESULT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+12,
		/*[[ user duplication login check		
or WorldServer error ]]*/
		/* player_id_t pid;*/
		/* wname64_t id;*/
		/* jError e;*/
		
		U2W_USER_LOGIN=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+13,
		/* wname64_t id;*/
		
		W2U_USER_LOGIN_RESULT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+14,
		/* player_id_t pid;*/
		/* jError e;*/
		/* wname64_t id;*/
		
		U2W_USER_LOGIN_DUPLICATE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+15,
		/* wname64_t id;*/
		/* player_id_t pid;*/
		
		W2U_USER_LOGIN_DUPLICATE_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+16,
		/* wname64_t id;*/
		
		U2W_USER_DISCONNECT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+17,
		/*[[ 모든접속이 끊겼을때 약 1초간격으로&#x0A;모아서 보낸다.		
로긴서버에만 접속된 상태일때 보낸다.		
Town서버와 Dungeon서버에 접속된 상태에서는&#x0A;User에서 World로 보낼 필요가 없다. ]]*/
		/* wstring id[-1];*/
		
		U2L_DO_USER_DISCONNECT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/4000+18,
		/* player_id_t uids[-1];*/
		
		PT_UserServer_END
	};//enum EUserServer

	void call_sq_U4_USER_CONNECTION_NOTIFY(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_U_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2U_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_W2U_ONLINE_USERS(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_L2U_ONLINE_USERS(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_U_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2U_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_U2SS_ONLINE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_U_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_U_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_L2U_USER_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_U2L_USER_LOGIN_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_U2W_USER_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_W2U_USER_LOGIN_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_U2W_USER_LOGIN_DUPLICATE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_W2U_USER_LOGIN_DUPLICATE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_U2W_USER_DISCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_U2L_DO_USER_DISCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef UserServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_UserServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // UserServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nUserServer
}/* nNET*/ } //nMech

#ifndef UserServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "UserServer/U4_USER_CONNECTION_NOTIFY.hpp"
#include "UserServer/U_HELLO.hpp"
#include "UserServer/SS2U_ONLINE.hpp"
#include "UserServer/W2U_ONLINE_USERS.hpp"
#include "UserServer/L2U_ONLINE_USERS.hpp"
#include "UserServer/U_SERVERINFO_ACK.hpp"
#include "UserServer/SS2U_SERVERINFO_ACK.hpp"
#include "UserServer/U2SS_ONLINE_OK.hpp"
#include "UserServer/U_ECHO.hpp"
#include "UserServer/U_ERROR.hpp"
#include "UserServer/L2U_USER_LOGIN.hpp"
#include "UserServer/U2L_USER_LOGIN_RESULT.hpp"
#include "UserServer/U2W_USER_LOGIN.hpp"
#include "UserServer/W2U_USER_LOGIN_RESULT.hpp"
#include "UserServer/U2W_USER_LOGIN_DUPLICATE.hpp"
#include "UserServer/W2U_USER_LOGIN_DUPLICATE_OK.hpp"
#include "UserServer/U2W_USER_DISCONNECT.hpp"
#include "UserServer/U2L_DO_USER_DISCONNECT.hpp"
#endif // UserServer_jNOTUSE_PACKET_HPP_INCLUDE