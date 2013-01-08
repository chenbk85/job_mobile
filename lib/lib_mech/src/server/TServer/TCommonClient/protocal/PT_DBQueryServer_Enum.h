
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_dbquery.xml)
#pragma once

#ifndef DBQueryServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DBQueryServer(DBQueryServer);

jxDECL_DBQueryServer(DC2DQ_USER_DISCONNECT);
jxDECL_DBQueryServer(DQ_ECHO);
jxDECL_DBQueryServer(DQ_ERROR);
jxDECL_DBQueryServer(DC2DQ_TOWN_CREATE);
jxDECL_DBQueryServer(DQ2DC_TOWN_CREATE_OK);
jxDECL_DBQueryServer(DC2DQ_TOWN_DELETE);
jxDECL_DBQueryServer(DQ2DC_TOWN_DELETE_OK);
jxDECL_DBQueryServer(DC2DQ_INSERT_ITEM_AND_SKILL);
jxDECL_DBQueryServer(DQ2DC_TOWN_CREATE_ERROR);
jxDECL_DBQueryServer(DC2DQ_CONNECT);
jxDECL_DBQueryServer(DQ2DC_CONNECT);
jxDECL_DBQueryServer(DQ2DC_CONNECT_OK);
jxDECL_DBQueryServer(DC2DQ_CONNECT_OK);
jxDECL_DBQueryServer(DC2DQ_USER_LOGIN);
jxDECL_DBQueryServer(DQ2DC_USER_LOGIN_RESULT);
jxDECL_DBQueryServer(DC2DQ_GET_TOWN_LIST);
jxDECL_DBQueryServer(DQ2DC_SEND_TOWN_LIST);
#endif //DBQueryServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nDBQueryServer
{
	enum EDBQueryServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/6500,
		DC2DQ_USER_DISCONNECT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+1,
		/* player_id_t pid[-1];*/
		
		DQ_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+2,
		/* uint8 type;*/
		/* tname256_t msg;*/
		
		DQ_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+3,
		/* jErrorInfo ei;*/
		
		DC2DQ_TOWN_CREATE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+4,
		/* player_id_t pid;*/
		/* Sys_Castle_id_t csid;*/
		/* Sys_TownPos_id_t tpsid;*/
		/* wname32_t name;*/
		
		DQ2DC_TOWN_CREATE_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+5,
		/* player_id_t pid;*/
		/* channelid_t channelNo;*/
		
		DC2DQ_TOWN_DELETE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+6,
		/* player_id_t pid;*/
		/* channelid_t index;*/
		
		DQ2DC_TOWN_DELETE_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+7,
		/* player_id_t pid;*/
		/* uint8 channel_index;*/
		
		DC2DQ_INSERT_ITEM_AND_SKILL=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+8,
		/* player_id_t pid;*/
		/* uint8 channel_index;*/
		
		DQ2DC_TOWN_CREATE_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+9,
		/* player_id_t pid;*/
		/* jError e;*/
		
		DC2DQ_CONNECT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+10,
		/* tname32_t WORLD_NAME;*/
		/* tname32_t SM_QUERY2CACHE_NAME;*/
		/* tname32_t SM_CACHE2QUERY_NAME;*/
		/* tname32_t SM_USER_INFO_NAME;*/
		/* uint32 processid;*/
		
		DQ2DC_CONNECT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+11,
		/* tname32_t WORLD_NAME;*/
		/* tname32_t SM_QUERY2CACHE_NAME;*/
		/* tname32_t SM_CACHE2QUERY_NAME;*/
		/* tname32_t SM_USER_INFO_NAME;*/
		/* tname32_t GAMEDB_NAME;*/
		/* uint32 processid;*/
		
		DQ2DC_CONNECT_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+12,
		/* jError e;*/
		/* uint32 processid;*/
		
		DC2DQ_CONNECT_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+13,
		/* jError e;*/
		/* uint32 processid;*/
		
		DC2DQ_USER_LOGIN=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+14,
		/* player_id_t pid;*/
		
		DQ2DC_USER_LOGIN_RESULT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+15,
		/* player_id_t pid;*/
		/* jError e;*/
		
		DC2DQ_GET_TOWN_LIST=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+16,
		/* player_id_t pid;*/
		
		DQ2DC_SEND_TOWN_LIST=/*nMech::nNET::EProtocal_jINet_OGS_END+*/6500+17,
		/* player_id_t pid;*/
		/* jError e;*/
		
		PT_DBQueryServer_END
	};//enum EDBQueryServer

	void call_sq_DC2DQ_USER_DISCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DQ_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DQ_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2DQ_TOWN_CREATE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DQ2DC_TOWN_CREATE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2DQ_TOWN_DELETE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DQ2DC_TOWN_DELETE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2DQ_INSERT_ITEM_AND_SKILL(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DQ2DC_TOWN_CREATE_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2DQ_CONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DQ2DC_CONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DQ2DC_CONNECT_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2DQ_CONNECT_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2DQ_USER_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DQ2DC_USER_LOGIN_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2DQ_GET_TOWN_LIST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DQ2DC_SEND_TOWN_LIST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef DBQueryServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_DBQueryServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // DBQueryServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nDBQueryServer
}/* nNET*/ } //nMech

#ifndef DBQueryServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "DBQueryServer/DC2DQ_USER_DISCONNECT.hpp"
#include "DBQueryServer/DQ_ECHO.hpp"
#include "DBQueryServer/DQ_ERROR.hpp"
#include "DBQueryServer/DC2DQ_TOWN_CREATE.hpp"
#include "DBQueryServer/DQ2DC_TOWN_CREATE_OK.hpp"
#include "DBQueryServer/DC2DQ_TOWN_DELETE.hpp"
#include "DBQueryServer/DQ2DC_TOWN_DELETE_OK.hpp"
#include "DBQueryServer/DC2DQ_INSERT_ITEM_AND_SKILL.hpp"
#include "DBQueryServer/DQ2DC_TOWN_CREATE_ERROR.hpp"
#include "DBQueryServer/DC2DQ_CONNECT.hpp"
#include "DBQueryServer/DQ2DC_CONNECT.hpp"
#include "DBQueryServer/DQ2DC_CONNECT_OK.hpp"
#include "DBQueryServer/DC2DQ_CONNECT_OK.hpp"
#include "DBQueryServer/DC2DQ_USER_LOGIN.hpp"
#include "DBQueryServer/DQ2DC_USER_LOGIN_RESULT.hpp"
#include "DBQueryServer/DC2DQ_GET_TOWN_LIST.hpp"
#include "DBQueryServer/DQ2DC_SEND_TOWN_LIST.hpp"
#endif // DBQueryServer_jNOTUSE_PACKET_HPP_INCLUDE