/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToBackEnd.h"
#include "PlugIn_ToFrontEnd.h"
#include "network/protocal/PT_CentralServer_Enum.h"
#include "network/protocal/PT_LoginServer_Enum.h"
#include "network/protocal/PT_DBCacheServer_Enum.h"
#include "network/protocal/PT_WorldServer_Enum.h"
#include "network/protocal/PT_UserServer_Enum.h"

using namespace nMech::nNET::nCentralServer;
using namespace nMech::nNET::nLoginServer;
using namespace nMech::nNET::nDBCacheServer;
using namespace nMech::nNET::nWorldServer;
using namespace nMech::nNET::nUserServer;

jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{
	namespace _from_backend_server
	{
#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,DBCacheServer)
		{
			// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
			be_READ_PACKET_P2P_PB(aaa);
		}
#endif
	}//namespace _from_backend_server
}
jNET_EVENT_END(PlugIn_ToBackEnd)


