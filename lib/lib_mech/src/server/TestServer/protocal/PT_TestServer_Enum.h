
//from(d:\svn\lib\lib_mech\src\server\testserver\sequence\testserver\..\..\protocal\pt_testserver.xml)
#pragma once

#ifndef TestServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_TestServer(TestServer);

jxDECL_TestServer(S_HELLO);
jxDECL_TestServer(X2S_LOGIN);
jxDECL_TestServer(S2X_LOGIN_OK);
jxDECL_TestServer(S_ECHO);
jxDECL_TestServer(S2X_ECHO);
jxDECL_TestServer(X2S_THREAD_TEST1);
jxDECL_TestServer(X2S_THREAD_TEST2);
jxDECL_TestServer(X2S_TEST_PACKET);
#endif //TestServer_jNOTUSE_PACKET_JXDEFINE

#define for_each_TestServer_EAddAccount(ENUM)\
	ENUM(AA_SUCCESS)  ENUM(AA_AccountDuple)  ENUM(AA_Auth)  ENUM(AA_Unkown)  
#define for_each_TestServer_EAddAccount1(ENUM)\
	ENUM(AA1_SUCCESS)  ENUM(AA1_AccountDuple)  ENUM(AA1_Auth)  ENUM(AA1_Unkown)  
namespace nMech { namespace nNET {

namespace nTestServer
{
	// from d:\svn\lib\lib_mech\src\server\testserver\sequence\testserver\s_1.1.1_login.usd
	enum EAddAccount
	{
		eBEGIN_EAddAccount,
		eAA_SUCCESS=0, //성공
		eAA_AccountDuple, // duplication login
		eAA_Auth, // not auth
		eAA_Unkown, // unkown fail
		eEND_EAddAccount
	};

	// from d:\svn\lib\lib_mech\src\server\testserver\sequence\testserver\s_1.1.1_login.usd
	enum EAddAccount1
	{
		eBEGIN_EAddAccount1,
		eAA1_SUCCESS=0, //성공
		eAA1_AccountDuple, // duplication login
		eAA1_Auth, // not auth
		eAA1_Unkown, // unkown fail
		eEND_EAddAccount1
	};

	enum ETestServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000,
		S_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+1,
		
		X2S_LOGIN=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+2,
		/* wname32_t name;*/
		
		S2X_LOGIN_OK=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+3,
		/* wname32_t server_name;*/
		
		S_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+4,
		/* uint8 type;*/
		/* wstring msg;*/
		
		S2X_ECHO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+5,
		/* uint8 type;*/
		/* wstring msg;*/
		
		X2S_THREAD_TEST1=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+6,
		/* uint8 type;*/
		/* wstring msg;*/
		
		X2S_THREAD_TEST2=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+7,
		/* uint8 type;*/
		/* wstring msg;*/
		
		X2S_TEST_PACKET=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+8,
		/* int32 val;*/
		/* string msg;*/
		
		PT_TestServer_END
	};//enum ETestServer

	void call_sq_S_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2S_LOGIN(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_S2X_LOGIN_OK(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_S_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_S2X_ECHO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2S_THREAD_TEST1(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2S_THREAD_TEST2(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);
	void call_sq_X2S_TEST_PACKET(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef TestServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_TestServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // TestServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nTestServer
}/* nNET*/ } //nMech

#ifndef TestServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "TestServer/S_HELLO.hpp"
#include "TestServer/X2S_LOGIN.hpp"
#include "TestServer/S2X_LOGIN_OK.hpp"
#include "TestServer/S_ECHO.hpp"
#include "TestServer/S2X_ECHO.hpp"
#include "TestServer/X2S_THREAD_TEST1.hpp"
#include "TestServer/X2S_THREAD_TEST2.hpp"
#include "TestServer/X2S_TEST_PACKET.hpp"
#endif // TestServer_jNOTUSE_PACKET_HPP_INCLUDE