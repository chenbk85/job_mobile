/* file : Recv_FromCentral.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-05 15:47:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "../AqCommon/define_code_jBE.h"

jNET_EVENT_BEGIN(PlugIn_ToBackEnd)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(W_HELLO,WorldServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		jSend_SS2server_ONLINE(W);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(W_ERROR,WorldServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		jSend_ERROR_TO_CLIENT(W,T);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(W2DC_USER_LOGIN_DUPLICATE,WorldServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(W2DC_USER_LOGIN_DUPLICATE);
		jFE();
		AqClientUser* pUser = pFE->find_user(Data.uid);
		if(pUser)
			pFE->DisconnectTcpClient(pUser);
	}

#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn, jIP_Address* pFromIP
	jNET_EVENT_RECEIVER_P2P(aaa,WorldServer)
	{
		// Data, PlugIn_ToBackEnd*pBE , B YTE buf_[1024]
		be_READ_PACKET_P2P_PB(aaa);
	}
#endif
}
jNET_EVENT_END(PlugIn_ToBackEnd)
