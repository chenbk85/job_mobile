/* file : jAgentNode.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-14 15:41:55
comp.: wiki.test.com
title : 
desc : 

*/

#ifndef __AqClientUser_header__
#define __AqClientUser_header__
#pragma once



#include "interface/net/jConnectUser.h"


struct jAgentNode : public jConnectUser<jIPacketSocket_IOCP*,dummy_id_t> , public nDataStruct::yVectorNode<jAgentNode>
{
	typedef dummy_id_t KEY_TYPE_id_t;
	jDECLEAR_YVECTOR_MANAGER(jAgentNode);
	tname32_t m_szComputerName;

	virtual void Create()
	{
		m_pS=0;
		m_uid=iHandle;
		m_sName.clear();
		jCLEAR(m_szComputerName);
	}
	virtual void Destroy()
	{
		m_pS=0;
		m_uid=0;
	}
	virtual void CopyFrom(const jAgentNode& o){jASSERT0(0 && "jAgentNode::CopyFrom");}


	virtual void Write_Packet(jPacket_Base& pk){if(m_pS)m_pS->WritePacket(&pk);}
	virtual void WritePacket(jPacket_Base* pk){if(m_pS)m_pS->WritePacket(pk);}
};



#endif // __AqClientUser_header__
