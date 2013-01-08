/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TGame.h"

jNET_EVENT_BEGIN(PlugIn_Connect)
{

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(DC_ERROR,DBCacheServer)
	{
		// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
		jSend_ERROR_TO_CLIENT(DC,G);
	}

	
#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,DBCacheServer)
		{
			// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
			READ_PACKET_PC_B(aaa);
		}
#endif
}
jNET_EVENT_END(PlugIn_Connect)


