/* file : AqServerNode.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-14 15:41:55
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __AqClientUser_header__
#define __AqClientUser_header__
#pragma once



#include "interface/net/jConnectUser.h"

struct AqServerNode : public jConnectUser<jIPacketSocket_IOCP*,user_id_t> , public nDataStruct::yVectorNode<AqServerNode>
{
	jDECLEAR_YVECTOR_MANAGER(AqServerNode);
	aname32_t m_szIP;
	aname32_t m_szID;
	aname32_t m_szPWD;
	uint32	m_playTime;	//2009/03/19 HMC 게임사용 시간[분단위]

	virtual void Create()
	{
		m_pS=0;
		m_uid=0;
		m_sName.clear();
		jCLEAR(m_szIP);
		jCLEAR(m_szID);
		jCLEAR(m_szPWD);
	}
	virtual void Destroy()
	{
		m_pS=0;
		m_uid=0;
	}
	virtual void CopyFrom(const AqServerNode& o)
	{
		jAssert0(0 && "AqServerNode::CopyFrom");
	}


	virtual void Write_Packet(jPacket_Base& pk)
	{
		if(m_pS)m_pS->WritePacket(&pk);
	}

	int StartPlayTime();
	int GetPlayTime();

	AqServerNode();

};



#endif // __AqClientUser_header__
