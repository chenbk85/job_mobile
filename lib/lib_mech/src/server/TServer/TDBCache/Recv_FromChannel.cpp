/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TDBCache.h"


jNET_EVENT_BEGIN(PlugIn_Server)
{
	jNET_EVENT_RECEIVER(CH2DC_TOWN_DELETE)
	{
		// PlugIn_Server*p , BYTE buf[1024] , jIGridNode* pServer,jPlayerObj* pUser
		READ_PACKET_PS_DCUser(CH2DC_TOWN_DELETE);

#ifdef TSERVER_PREPARE
		pUser_Check_channelid(Data.index,DC,Data.pid);

		//jTODO T2X_TOWN_DELETE_OK를 받으면 삭제하자.
		g_DQ.WritePacket(WRITE_DC2DQ_TOWN_DELETE(buf, Data.pid,Data.index));
#endif //TSERVER_PREPARE

	}

	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_Server*p , BYTE buf[1024] , jIGridNode* pServer,jPlayerObj* pUser
		READ_PACKET_PS_DCUser(aaa);
	}
#endif

}
jNET_EVENT_END(PlugIn_Server)



