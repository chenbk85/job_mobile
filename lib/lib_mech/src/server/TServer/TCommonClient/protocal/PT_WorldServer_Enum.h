
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_world.xml)
#pragma once

#ifndef WorldServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_WorldServer(WorldServer);

jxDECL_WorldServer(CH2W_NEW_TOWN);
jxDECL_WorldServer(W_ERROR);
jxDECL_WorldServer(W2DC_NEW_TOWN);
jxDECL_WorldServer(DC2W_NEW_TOWN_ERROR);
jxDECL_WorldServer(DC2W_TOWN_DELETE_OK);
jxDECL_WorldServer(W4_USER_DISCONNECT);
jxDECL_WorldServer(W2DC_USER_DISCONNECT);
jxDECL_WorldServer(W2_USER_LOGIN_DUPLICATE);
jxDECL_WorldServer(W_HELLO);
jxDECL_WorldServer(SS2W_ONLINE);
jxDECL_WorldServer(W_SERVERINFO_ACK);
jxDECL_WorldServer(SS2W_SERVERINFO_ACK);
jxDECL_WorldServer(W_ECHO);
jxDECL_WorldServer(W2DC_USER_LOGIN);
jxDECL_WorldServer(DC2W_USER_LOGIN_RESULT);
jxDECL_WorldServer(W2DC_USER_LOGIN_CHANNEL);
jxDECL_WorldServer(DC2W_USER_LOGIN_CHANNEL_FAIL);
jxDECL_WorldServer(DC2W_USER_LOGIN_DUPLICATE_OK);
jxDECL_WorldServer(W2_USER_DISCONNECT);
jxDECL_WorldServer(CH2W_USER_LOGIN_CHANNEL);
#endif //WorldServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nWorldServer
{
	enum EWorldServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/5000,
		CH2W_NEW_TOWN=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+1,
		/*[[ ������ ���ο� ����Ȯ�� , tpid=0�̸� ������ ���� ]]*/
		/* player_id_t pid;*/
		/* Sys_Castle_id_t csid;*/
		/* Sys_TownPos_id_t tpsid;*/
		/* wname32_t town_name;*/
		
		W_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+2,
		/* jErrorInfo ei;*/
		
		W2DC_NEW_TOWN=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+3,
		/*[[ ���õȼ����� �����ϰ� ��������		
������� �ʴ� Sys_TownPos_id_t�� ���� ]]*/
		/* player_id_t pid;*/
		/* Sys_Castle_id_t csid;*/
		/* Sys_TownPos_id_t tpsid;*/
		/* wname32_t name;*/
		
		DC2W_NEW_TOWN_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+4,
		/*[[ DBŸ���������&#x0A; ]]*/
		/* player_id_t pid;*/
		/* Sys_Castle_id_t csid;*/
		/* Sys_TownPos_id_t tpsid;*/
		/* jError e;*/
		
		DC2W_TOWN_DELETE_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+5,
		/* wname64_t user;*/
		/* Sys_Castle_id_t csid;*/
		/* Sys_TownPos_id_t tp;*/
		
		W4_USER_DISCONNECT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+6,
		/*[[ ��������� �������� �� 6�ʰ�������&#x0A;��Ƽ� ������.		
Town������ Dungeon������ ���� disconnection��		
����� ������ ���� ������.		
���忡���� DC�� �ٽ� ������. ]]*/
		/* wstring id[-1];*/
		
		W2DC_USER_DISCONNECT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+7,
		/* player_id_t pid[-1];*/
		
		W2_USER_LOGIN_DUPLICATE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+8,
		/* wname64_t id;*/
		/* player_id_t pid;*/
		
		W_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+9,
		/* jServerInfo si;*/
		
		SS2W_ONLINE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+10,
		/*[[ W_HELLO�� ���� ����. ]]*/
		/* serverid_t your_sid;*/
		/*[[ Ȯ�ο���Ŷ ]]*/
		/* jServerInfo my;*/
		
		W_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+11,
		/*[[ SS2W_ONLINE�� �޾����� �������� sid=0�϶�		
�ٽ� ��û�Ͽ� ����.		
�ֳĸ� sid=0�̶�¿���� ���� central�̳� command��&#x0A;���� sid�� �߱޹޴����̱⶧���̴�. ]]*/
		/* jServerInfo si;*/
		
		SS2W_SERVERINFO_ACK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+12,
		/* jServerInfo si;*/
		
		W_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+13,
		/* tname256_t msg;*/
		/* int8 type;*/
		
		W2DC_USER_LOGIN=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+14,
		/*[[ �̶� ���밡���� DC�� �����Ͽ� ��û�Ѵ�.		
uid�� wid�� dc_handle�� ������&#x0A; ]]*/
		/* player_id_t pid;*/
		/* wname64_t id;*/
		
		DC2W_USER_LOGIN_RESULT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+15,
		/* jError e;*/
		/* wname64_t id;*/
		/* player_id_t pid;*/
		
		W2DC_USER_LOGIN_CHANNEL=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+16,
		/* player_id_t pid;*/
		/* wname64_t id;*/
		/* serverid_t town;*/
		
		DC2W_USER_LOGIN_CHANNEL_FAIL=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+17,
		/* player_id_t pid;*/
		/* jError e;*/
		
		DC2W_USER_LOGIN_DUPLICATE_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+18,
		/* wname64_t id;*/
		
		W2_USER_DISCONNECT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+19,
		/* wstring id[-1];*/
		
		CH2W_USER_LOGIN_CHANNEL=/*nMech::nNET::EProtocal_jINet_OGS_END+*/5000+20,
		/* player_id_t pid;*/
		/* wname64_t id;*/
		
		PT_WorldServer_END
	};//enum EWorldServer

	void call_sq_CH2W_NEW_TOWN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_W_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_W2DC_NEW_TOWN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2W_NEW_TOWN_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2W_TOWN_DELETE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_W4_USER_DISCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_W2DC_USER_DISCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_W2_USER_LOGIN_DUPLICATE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_W_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2W_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_W_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_SS2W_SERVERINFO_ACK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_W_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_W2DC_USER_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2W_USER_LOGIN_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_W2DC_USER_LOGIN_CHANNEL(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2W_USER_LOGIN_CHANNEL_FAIL(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DC2W_USER_LOGIN_DUPLICATE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_W2_USER_DISCONNECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2W_USER_LOGIN_CHANNEL(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef WorldServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_WorldServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // WorldServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nWorldServer
}/* nNET*/ } //nMech

#ifndef WorldServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "WorldServer/CH2W_NEW_TOWN.hpp"
#include "WorldServer/W_ERROR.hpp"
#include "WorldServer/W2DC_NEW_TOWN.hpp"
#include "WorldServer/DC2W_NEW_TOWN_ERROR.hpp"
#include "WorldServer/DC2W_TOWN_DELETE_OK.hpp"
#include "WorldServer/W4_USER_DISCONNECT.hpp"
#include "WorldServer/W2DC_USER_DISCONNECT.hpp"
#include "WorldServer/W2_USER_LOGIN_DUPLICATE.hpp"
#include "WorldServer/W_HELLO.hpp"
#include "WorldServer/SS2W_ONLINE.hpp"
#include "WorldServer/W_SERVERINFO_ACK.hpp"
#include "WorldServer/SS2W_SERVERINFO_ACK.hpp"
#include "WorldServer/W_ECHO.hpp"
#include "WorldServer/W2DC_USER_LOGIN.hpp"
#include "WorldServer/DC2W_USER_LOGIN_RESULT.hpp"
#include "WorldServer/W2DC_USER_LOGIN_CHANNEL.hpp"
#include "WorldServer/DC2W_USER_LOGIN_CHANNEL_FAIL.hpp"
#include "WorldServer/DC2W_USER_LOGIN_DUPLICATE_OK.hpp"
#include "WorldServer/W2_USER_DISCONNECT.hpp"
#include "WorldServer/CH2W_USER_LOGIN_CHANNEL.hpp"
#endif // WorldServer_jNOTUSE_PACKET_HPP_INCLUDE