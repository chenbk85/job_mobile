
//from(d:\svn\common\server\tool\umlpad\baseballtestclient\code\pt_baseballserver.xml)
#pragma once

#ifndef BaseballServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_BaseballServer(BaseballServer);

jxDECL_BaseballServer(S_HELLO);
#endif //BaseballServer_jNOTUSE_PACKET_JXDEFINE

#define for_each_BaseballServer_EAddAccount(ENUM)\
	ENUM(AA_SUCCESS)  ENUM(AA_AccountDuple)  ENUM(AA_Auth)  ENUM(AA_Unkown)  
namespace nMech { namespace nNET {

namespace nBaseballServer
{
	// from d:\svn\common\server\tool\umlpad\baseballtestclient\test.usd
	enum EAddAccount
	{
		eBEGIN_EAddAccount,
		eAA_SUCCESS=0, //¼º°ø
		eAA_AccountDuple, // duplication login
		eAA_Auth, // not auth
		eAA_Unkown, // unkown fail
		eEND_EAddAccount
	};

	enum EBaseballServer
	{
		PT_VERSION	= /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000,
		S_HELLO=/*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+1,
		/* int type;*/
		/* astring msg;*/
		
		PT_BaseballServer_END
	};//enum EBaseballServer

	void call_sq_S_HELLO(void* v,jIPacketSocket_IOCP*pS,jPacket_Base* pk,jIP_Address* pIP);

	#ifndef BaseballServer_jNOT_USE_PACKET_PLUGIN_HELP
		extern PT_BaseballServer_LIB_API nMech::nNET::jNamedEventTable *g_pPlugInHelpTableList;
	#endif // BaseballServer_jNOT_USE_PACKET_PLUGIN_HELP


}//nBaseballServer
}/* nNET*/ } //nMech

#ifndef BaseballServer_jNOTUSE_PACKET_HPP_INCLUDE
#include "BaseballServer/S_HELLO.hpp"
#endif // BaseballServer_jNOTUSE_PACKET_HPP_INCLUDE