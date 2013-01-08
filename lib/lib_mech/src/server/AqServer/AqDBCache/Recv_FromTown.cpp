/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"

#include "network/protocal/PT_DBQueryServer_Enum.h"
using namespace nMech::nNET::nDBQueryServer;

jNET_EVENT_BEGIN(PlugIn_ToFrontEnd)
{

	jNET_EVENT_RECEIVER(T2DC_TOWN_DELETE)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqConnectedServerNode* pServer,AqDBCacheUser* pUser
		READ_PACKET_FromServer_UID(T2DC_TOWN_DELETE);
		pUser_Check_townid(Data.index,DC,Data.uid);

		//T2X_TOWN_DELETE_OK를 받으면 삭제하자.
		g_Users_DC.WritePacket(WRITE_DC2DQ_TOWN_DELETE(buf, Data.uid,Data.index));
	}

	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_ToFrontEnd*p , BYTE buf[1024] , AqConnectedServerNode* pServer,AqDBCacheUser* pUser
		READ_PACKET_FromServer_UID(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_ToFrontEnd)



