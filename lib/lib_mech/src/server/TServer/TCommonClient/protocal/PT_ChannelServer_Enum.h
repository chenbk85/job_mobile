
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_channel.xml)
#pragma once

#ifndef ChannelServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_ChannelServer(ChannelServer);

jxDECL_ChannelServer(CH_ECHO);
jxDECL_ChannelServer(X2CH_CHAT);
jxDECL_ChannelServer(CH2X_CHAT);
jxDECL_ChannelServer(X2CH_USER_LOGIN_CHANNEL);
jxDECL_ChannelServer(CH2X_NEW_TOWN_OK);
jxDECL_ChannelServer(X2CH_NEW_TOWN);
jxDECL_ChannelServer(CH2X_SELECT_CASTLE);
jxDECL_ChannelServer(X2CH_TOWN_SELECT);
jxDECL_ChannelServer(X2CH_TOWN_DELETE);
jxDECL_ChannelServer(CH2X_TOWN_DELETE_OK);
jxDECL_ChannelServer(CH2X_TOWN_SELECT_RESULT);
jxDECL_ChannelServer(CH2X_CREATE_NEW_TOWN);
jxDECL_ChannelServer(X2CH_USER_EXIT);
jxDECL_ChannelServer(CH2X_USER_EXIT);
jxDECL_ChannelServer(X2CH_GOTO_CASTLE_MAP);
jxDECL_ChannelServer(CH2X_GOTO_CASTLE_MAP);
jxDECL_ChannelServer(X2CH_GOTO_WORLD_MAP);
jxDECL_ChannelServer(CH2X_GOTO_WORLD_MAP);
jxDECL_ChannelServer(CH2X_UPDATE_CASTLE_MAP);
jxDECL_ChannelServer(CH2X_UDPATE_WORLD_MAP);
jxDECL_ChannelServer(X2CH_GOTO_TOWN_MAP);
jxDECL_ChannelServer(CH2X_GOTO_TOWN_MAP);
jxDECL_ChannelServer(X2CH_NEW_BUILD);
jxDECL_ChannelServer(X2CH_BUILD_UPGRADE);
jxDECL_ChannelServer(CH2X_BUILD_UPGRADE_RESULT);
jxDECL_ChannelServer(X2CH_BUILD_UPGRADE_CANCLE);
jxDECL_ChannelServer(X2CH_BUILD_UPGRADE_CANCLE_OK);
jxDECL_ChannelServer(X2CH_BUILD_UPGRADE_CHECK);
jxDECL_ChannelServer(X2CH_BUILD_UPGRADE_CHECK_RESULT);
jxDECL_ChannelServer(CH_ERROR);
jxDECL_ChannelServer(CH_HELLO);
jxDECL_ChannelServer(T2X_NOTICE);
jxDECL_ChannelServer(X2L_NOTICE_TEST);
jxDECL_ChannelServer(CH2X_USER_LOGIN_CHANNEL_OK);
jxDECL_ChannelServer(CH2X_USER_LOGIN_CHANNEL_OK2);
jxDECL_ChannelServer(CH2X_USER_LOGIN_CHANNEL_OK3);
#endif //ChannelServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET {

namespace nChannelServer
{
	enum EChannelServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/2500,
		CH_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+1,
		/* tname256_t msg;*/
		/* uint8 type;*/
		
		X2CH_CHAT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+2,
		/* wname128_t msg;*/
		/* uint8 type;*/
		/* wstring id[-1];*/
		/* player_id_t pid[-1];*/
		
		CH2X_CHAT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+3,
		/* wname128_t msg;*/
		/* uint8 type;*/
		
		X2CH_USER_LOGIN_CHANNEL=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+4,
		/* player_id_t pid;*/
		/* wname64_t id;*/
		
		CH2X_NEW_TOWN_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+5,
		/* channelid_t index;*/
		/* Use_Town town;*/
		
		X2CH_NEW_TOWN=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+6,
		/* Sys_Castle_id_t csid;*/
		/* Sys_TownPos_id_t tpsid;*/
		/* wname32_t name;*/
		
		CH2X_SELECT_CASTLE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+7,
		
		X2CH_TOWN_SELECT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+8,
		/* channelid_t index;*/
		
		X2CH_TOWN_DELETE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+9,
		/* channelid_t index;*/
		
		CH2X_TOWN_DELETE_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+10,
		/* channelid_t index;*/
		
		CH2X_TOWN_SELECT_RESULT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+11,
		/* channelid_t channelNo;*/
		/* jError e;*/
		
		CH2X_CREATE_NEW_TOWN=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+12,
		
		X2CH_USER_EXIT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+13,
		
		CH2X_USER_EXIT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+14,
		
		X2CH_GOTO_CASTLE_MAP=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+15,
		/* uint8 channelNo;*/
		
		CH2X_GOTO_CASTLE_MAP=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+16,
		/*[[ 반경 이내의 마을정보를미리 보냄 ]]*/
		/* uint8 channelNo;*/
		/* jIE* castle_map_info;*/
		
		X2CH_GOTO_WORLD_MAP=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+17,
		/* uint8 channelNo;*/
		
		CH2X_GOTO_WORLD_MAP=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+18,
		/*[[ 반경이내의 성정보를 보냄 ]]*/
		/* uint8 channelNo;*/
		/* jIE* world_map_info;*/
		
		CH2X_UPDATE_CASTLE_MAP=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+19,
		/*[[ 새로운 유닛등장시 보냄 ]]*/
		/* jIE* castle_map_info;*/
		
		CH2X_UDPATE_WORLD_MAP=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+20,
		/*[[ 새로운유닛등장시&#x0A; ]]*/
		/* jIE* world_map_info;*/
		
		X2CH_GOTO_TOWN_MAP=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+21,
		/* uint8 channelNo;*/
		
		CH2X_GOTO_TOWN_MAP=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+22,
		/* uint8 channelNo;*/
		
		X2CH_NEW_BUILD=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+23,
		/* tname32_t build_slot;*/
		/* uint8 _EBuildType;*/
		/* uint8 hero_id;*/
		
		X2CH_BUILD_UPGRADE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+24,
		/* tname32_t build_slot;*/
		/* uint8 hero_id;*/
		
		CH2X_BUILD_UPGRADE_RESULT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+25,
		/* tname32_t build_slot;*/
		/* uint8 _EBuildType;*/
		/* uint8 level;*/
		/* jError e;*/
		/* j_time_t curr_server_time;*/
		/* int32 upgrade_sec;*/
		/* uint8 hero_id;*/
		
		X2CH_BUILD_UPGRADE_CANCLE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+26,
		/* tname32_t build_slot;*/
		
		X2CH_BUILD_UPGRADE_CANCLE_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+27,
		/* tname32_t build_slot;*/
		
		X2CH_BUILD_UPGRADE_CHECK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+28,
		/*[[ 업글 서버종료시간을 클라가 알기때문에		
업글 종료시간에 맞추어 이패킷을 보내자.		
		
이패킷을 불법적으로 보내면 클라 종료시키자. ]]*/
		/* tname32_t build_slot;*/
		
		X2CH_BUILD_UPGRADE_CHECK_RESULT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+29,
		/* tname32_t build_slot;*/
		/* jError e;*/
		/* int32 left_sec;*/
		/*[[ 남은시간(sec) ]]*/
		
		CH_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+30,
		/* jErrorInfo ei;*/
		
		CH_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+31,
		/* jServerInfo si;*/
		
		T2X_NOTICE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+32,
		/* jNoticeInfo info;*/
		/* wname1024_t msg;*/
		/* aname32_t date;*/
		
		X2L_NOTICE_TEST=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+33,
		
		CH2X_USER_LOGIN_CHANNEL_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+34,
		/*[[ 해당 채널서버 접속완료및 아바타리스트 받기&#x0A; ]]*/
		/* nAQ::Use_User user;*/
		/* nAQ::Use_Town town[-1];*/
		
		CH2X_USER_LOGIN_CHANNEL_OK2=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+35,
		/*[[ iMAX_USER_Hero =? ]]*/
		/* nAQ::Use_Hero hero[-1];*/
		/* nAQ::Use_Force force[-1];*/
		
		CH2X_USER_LOGIN_CHANNEL_OK3=/*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+36,
		/* jIE* town_xml;*/
		/* j_time_t server_time;*/
		
		PT_ChannelServer_END
	};//enum EChannelServer

	void call_sq_CH_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_CHAT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_CHAT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_USER_LOGIN_CHANNEL(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_NEW_TOWN_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_NEW_TOWN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_SELECT_CASTLE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_TOWN_SELECT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_TOWN_DELETE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_TOWN_DELETE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_TOWN_SELECT_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_CREATE_NEW_TOWN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_USER_EXIT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_USER_EXIT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_GOTO_CASTLE_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_GOTO_CASTLE_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_GOTO_WORLD_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_GOTO_WORLD_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_UPDATE_CASTLE_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_UDPATE_WORLD_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_GOTO_TOWN_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_GOTO_TOWN_MAP(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_NEW_BUILD(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_BUILD_UPGRADE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_BUILD_UPGRADE_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_BUILD_UPGRADE_CANCLE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_BUILD_UPGRADE_CANCLE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_BUILD_UPGRADE_CHECK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2CH_BUILD_UPGRADE_CHECK_RESULT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_T2X_NOTICE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2L_NOTICE_TEST(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_USER_LOGIN_CHANNEL_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_USER_LOGIN_CHANNEL_OK2(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_CH2X_USER_LOGIN_CHANNEL_OK3(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef ChannelServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_ChannelServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // ChannelServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nChannelServer
}/* nNET*/ } //nMech

#ifndef ChannelServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "ChannelServer/CH_ECHO.hpp"
#include "ChannelServer/X2CH_CHAT.hpp"
#include "ChannelServer/CH2X_CHAT.hpp"
#include "ChannelServer/X2CH_USER_LOGIN_CHANNEL.hpp"
#include "ChannelServer/CH2X_NEW_TOWN_OK.hpp"
#include "ChannelServer/X2CH_NEW_TOWN.hpp"
#include "ChannelServer/CH2X_SELECT_CASTLE.hpp"
#include "ChannelServer/X2CH_TOWN_SELECT.hpp"
#include "ChannelServer/X2CH_TOWN_DELETE.hpp"
#include "ChannelServer/CH2X_TOWN_DELETE_OK.hpp"
#include "ChannelServer/CH2X_TOWN_SELECT_RESULT.hpp"
#include "ChannelServer/CH2X_CREATE_NEW_TOWN.hpp"
#include "ChannelServer/X2CH_USER_EXIT.hpp"
#include "ChannelServer/CH2X_USER_EXIT.hpp"
#include "ChannelServer/X2CH_GOTO_CASTLE_MAP.hpp"
#include "ChannelServer/CH2X_GOTO_CASTLE_MAP.hpp"
#include "ChannelServer/X2CH_GOTO_WORLD_MAP.hpp"
#include "ChannelServer/CH2X_GOTO_WORLD_MAP.hpp"
#include "ChannelServer/CH2X_UPDATE_CASTLE_MAP.hpp"
#include "ChannelServer/CH2X_UDPATE_WORLD_MAP.hpp"
#include "ChannelServer/X2CH_GOTO_TOWN_MAP.hpp"
#include "ChannelServer/CH2X_GOTO_TOWN_MAP.hpp"
#include "ChannelServer/X2CH_NEW_BUILD.hpp"
#include "ChannelServer/X2CH_BUILD_UPGRADE.hpp"
#include "ChannelServer/CH2X_BUILD_UPGRADE_RESULT.hpp"
#include "ChannelServer/X2CH_BUILD_UPGRADE_CANCLE.hpp"
#include "ChannelServer/X2CH_BUILD_UPGRADE_CANCLE_OK.hpp"
#include "ChannelServer/X2CH_BUILD_UPGRADE_CHECK.hpp"
#include "ChannelServer/X2CH_BUILD_UPGRADE_CHECK_RESULT.hpp"
#include "ChannelServer/CH_ERROR.hpp"
#include "ChannelServer/CH_HELLO.hpp"
#include "ChannelServer/T2X_NOTICE.hpp"
#include "ChannelServer/X2L_NOTICE_TEST.hpp"
#include "ChannelServer/CH2X_USER_LOGIN_CHANNEL_OK.hpp"
#include "ChannelServer/CH2X_USER_LOGIN_CHANNEL_OK2.hpp"
#include "ChannelServer/CH2X_USER_LOGIN_CHANNEL_OK3.hpp"
#endif // ChannelServer_jNOTUSE_PACKET_HPP_INCLUDE