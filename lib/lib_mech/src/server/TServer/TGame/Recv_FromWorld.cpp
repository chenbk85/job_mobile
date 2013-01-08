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
	namespace _from_backend_server
	{

		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(W_ERROR,WorldServer)
		{
			// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
			jSend_ERROR_TO_CLIENT(W,G);
		}

#if 0
		//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
		jNET_EVENT_RECEIVER_P2P(aaa,WorldServer)
		{
			// Data, PlugIn_Connect*pPC , B YTE buf_[1024]
			READ_PACKET_PC_B(aaa);
		}
#endif
	}//namespace _from_backend_server
}
jNET_EVENT_END(PlugIn_Connect)


