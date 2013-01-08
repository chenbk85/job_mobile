
//from(d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\..\..\..\tcommonclient\protocal\pt_dummy.xml)
#pragma once

#ifndef DummyServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DummyServer(DummyServer);

jxDECL_DummyServer(DT_ECHO);
jxDECL_DummyServer(DT_ERROR);
jxDECL_DummyServer(DT_HELLO);
jxDECL_DummyServer(X2DT_HELLO);
jxDECL_DummyServer(DT_ONLINE);
jxDECL_DummyServer(DT_TEST_LOGIN_START);
jxDECL_DummyServer(DT_TEST_LOG_OUT);
jxDECL_DummyServer(DT_LOGIN_START_OK);
jxDECL_DummyServer(DT2_UPDATE_XPATH_VALUE);
jxDECL_DummyServer(DT4_UPDATE_XPATH_VALUE_OK);
jxDECL_DummyServer(DT_RUN_CONSOLE_CMD);
jxDECL_DummyServer(DT2X_SET_TEST_ENV);
jxDECL_DummyServer(DT_RUN_DUMMY_SCRIPT);
#endif //DummyServer_jNOTUSE_PACKET_JXDEFINE

#define for_each_DummyServer_EEchoType(ENUM)\
	ENUM(ET_nomal)  ENUM(ET_CmdToDummyTest)  ENUM(ET_CmdToClient)  ENUM(ET_CmdToAqMonitor)  
#define for_each_DummyServer_EXpathTarget(ENUM)\
	ENUM(XT_TestCentral)  ENUM(XT_TestDummy)  
namespace nMech { namespace nNET {

namespace nDummyServer
{
	// from d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\dt_01_01_testserver.usd
	enum EEchoType
	{
		eBEGIN_EEchoType,
		eET_nomal, //
		eET_CmdToDummyTest, //
		eET_CmdToClient, //
		eET_CmdToAqMonitor, //
		eEND_EEchoType
	};

	// from d:\svn\common\lib\windows\mech\src\server\tserver\doc\sequece\tserver\dt_1.5.1_cmd.usd
	enum EXpathTarget
	{
		eBEGIN_EXpathTarget,
		eXT_TestCentral, //
		eXT_TestDummy, //
		eEND_EXpathTarget
	};

	enum EDummyServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000,
		DT_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+1,
		/*[[ type - DummyServer:EEchoType ]]*/
		/* TCHAR msg[256];*/
		/* uint8 type;*/
		
		DT_ERROR=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+2,
		/* jErrorInfo ei;*/
		
		DT_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+3,
		/* jServerInfo si;*/
		
		X2DT_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+4,
		/* jServerInfo si;*/
		
		DT_ONLINE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+5,
		/* tname32_t test_id;*/
		/*[[ 테스트용 계정 접두어&#x0A; ]]*/
		/* int TEST_ID_START_NUM;*/
		/* uint16 iDummyCount;*/
		/*[[ 테스트클라이언트당 더미갯수 ]]*/
		/* tname32_t szLoginIP;*/
		/* uint16 iLoginPort;*/
		
		DT_TEST_LOGIN_START=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+6,
		/* int16 per_user;*/
		/* uint32 delay;*/
		/* tname32_t testClientName;*/
		
		DT_TEST_LOG_OUT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+7,
		/* int16 per_user;*/
		/* uint32 delay;*/
		/* tname32_t testClientName;*/
		
		DT_LOGIN_START_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+8,
		/* uint32 process_msec;*/
		/* aname32_t user_id;*/
		/* CHAR lobby_ip[32];*/
		
		DT2_UPDATE_XPATH_VALUE=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+9,
		
		DT4_UPDATE_XPATH_VALUE_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+10,
		/* tname256_t target_name;*/
		/* tname256_t doc;*/
		/* tname256_t xpath;*/
		/* tname256_t value;*/
		
		DT_RUN_CONSOLE_CMD=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+11,
		/*[[ isCentral=false이면 모든더미에대해 		
콘솔명령을 실행.&#x0A; ]]*/
		/* dummy_id_t dummy_id;*/
		/* tname32_t category;*/
		/* tname32_t cmd;*/
		/* tstring arg[-1];*/
		
		DT2X_SET_TEST_ENV=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+12,
		
		DT_RUN_DUMMY_SCRIPT=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+13,
		/* TCHAR code[4096];*/
		
		PT_DummyServer_END
	};//enum EDummyServer

	void call_sq_DT_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DT_ERROR(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DT_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2DT_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DT_ONLINE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DT_TEST_LOGIN_START(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DT_TEST_LOG_OUT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DT_LOGIN_START_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DT2_UPDATE_XPATH_VALUE(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DT4_UPDATE_XPATH_VALUE_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DT_RUN_CONSOLE_CMD(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DT2X_SET_TEST_ENV(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_DT_RUN_DUMMY_SCRIPT(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef DummyServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_DummyServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // DummyServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nDummyServer
}/* nNET*/ } //nMech

#ifndef DummyServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "DummyServer/DT_ECHO.hpp"
#include "DummyServer/DT_ERROR.hpp"
#include "DummyServer/DT_HELLO.hpp"
#include "DummyServer/X2DT_HELLO.hpp"
#include "DummyServer/DT_ONLINE.hpp"
#include "DummyServer/DT_TEST_LOGIN_START.hpp"
#include "DummyServer/DT_TEST_LOG_OUT.hpp"
#include "DummyServer/DT_LOGIN_START_OK.hpp"
#include "DummyServer/DT2_UPDATE_XPATH_VALUE.hpp"
#include "DummyServer/DT4_UPDATE_XPATH_VALUE_OK.hpp"
#include "DummyServer/DT_RUN_CONSOLE_CMD.hpp"
#include "DummyServer/DT2X_SET_TEST_ENV.hpp"
#include "DummyServer/DT_RUN_DUMMY_SCRIPT.hpp"
#endif // DummyServer_jNOTUSE_PACKET_HPP_INCLUDE