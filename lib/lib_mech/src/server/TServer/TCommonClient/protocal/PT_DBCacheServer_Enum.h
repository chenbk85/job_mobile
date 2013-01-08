
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_dbcache.xml)
#pragma once

#ifndef DBCacheServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DBCacheServer(DBCacheServer);

jxDECL_DBCacheServer(DC2CH_NEW_TOWN_OK);
jxDECL_DBCacheServer(CH2DC_TOWN_DELETE);
jxDECL_DBCacheServer(DC2CH_TOWN_DELETE_OK);
jxDECL_DBCacheServer(DC_HELLO);
jxDECL_DBCacheServer(SS2DC_ONLINE);
jxDECL_DBCacheServer(DC_SERVERINFO_ACK);
jxDECL_DBCacheServer(SS2DC_SERVERINFO_ACK);
jxDECL_DBCacheServer(DC_ECHO);
jxDECL_DBCacheServer(DC_ERROR);
jxDECL_DBCacheServer(DC2CH_USER_LOGIN_CHANNEL_OK);
jxDECL_DBCacheServer(DC2CH_USER_LOGIN_CHANNEL_OK2);
#endif //DBCacheServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nDBCacheServer
{
	enum EDBCacheServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/6000,
		DC2CH_NEW_TOWN_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+1,
		/* player_id_t pid;*/
		/* channelid_t index;*/
		/* Use_Town town;*/
		/* bool isCapital;*/
		
		CH2DC_TOWN_DELETE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+2,
		/* player_id_t pid;*/
		/* channelid_t index;*/
		
		DC2CH_TOWN_DELETE_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+3,
		/* player_id_t pid;*/
		/* channelid_t index;*/
		
		DC_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+4,
		/* jServerInfo si;*/
		
		SS2DC_ONLINE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+5,
		/* serverid_t your_sid;*/
		/*[[ 패킷확인용&#x0A; ]]*/
		/* jServerInfo my;*/
		
		DC_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+6,
		/*[[ SS2DC_ONLINE을 받았을때 보낸쪽의 sid=0일때		
다시 요청하여 받음.		
왜냐면 sid=0이라는예기는 아직 central이나 command로&#x0A;부터 sid를 발급받는중이기때문이다. ]]*/
		/* jServerInfo si;*/
		
		SS2DC_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+7,
		/* jServerInfo si;*/
		
		DC_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+8,
		/* tname256_t msg;*/
		/* int8 type;*/
		
		DC_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+9,
		/* jErrorInfo ei;*/
		
		DC2CH_USER_LOGIN_CHANNEL_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+10,
		/*[[ iMAX_USER_TOWN	= 20 ]]*/
		/* player_id_t pid;*/
		/* nAQ::Use_User user;*/
		/* nAQ::Use_Town town[-1];*/
		
		DC2CH_USER_LOGIN_CHANNEL_OK2=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+11,
		/* player_id_t pid;*/
		/* nAQ::Use_Hero hero[-1];*/
		/* nAQ::Use_Force force[-1];*/
		
		PT_DBCacheServer_END
	};//enum EDBCacheServer

	void call_sq_DC2CH_NEW_TOWN_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2DC_TOWN_DELETE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2CH_TOWN_DELETE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2DC_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2DC_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2CH_USER_LOGIN_CHANNEL_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2CH_USER_LOGIN_CHANNEL_OK2(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef DBCacheServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_DBCacheServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // DBCacheServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nDBCacheServer
}/* nNET*/ } //nMech

#ifndef DBCacheServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "DBCacheServer/DC2CH_NEW_TOWN_OK.hpp"
#include "DBCacheServer/CH2DC_TOWN_DELETE.hpp"
#include "DBCacheServer/DC2CH_TOWN_DELETE_OK.hpp"
#include "DBCacheServer/DC_HELLO.hpp"
#include "DBCacheServer/SS2DC_ONLINE.hpp"
#include "DBCacheServer/DC_SERVERINFO_ACK.hpp"
#include "DBCacheServer/SS2DC_SERVERINFO_ACK.hpp"
#include "DBCacheServer/DC_ECHO.hpp"
#include "DBCacheServer/DC_ERROR.hpp"
#include "DBCacheServer/DC2CH_USER_LOGIN_CHANNEL_OK.hpp"
#include "DBCacheServer/DC2CH_USER_LOGIN_CHANNEL_OK2.hpp"
#endif // DBCacheServer_jNOTUSE_PACKET_HPP_INCLUDE