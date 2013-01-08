/* file : jAqServerNode1.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 13:57:28
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __jAqServerNode1_header__
#define __jAqServerNode1_header__
#pragma once

#include <boost/timer.hpp>
#include "interface/net/jConnectUser.h"


struct AqConnectedServerNode 
	: public jServerInfo
	, public jConnectUser<jIPacketSocket_IOCP*,serverid_t> 
	, public nDataStruct::yVectorNode<AqConnectedServerNode> 
{
	typedef serverid_t KEY_TYPE_id_t;
	jDECLEAR_YVECTOR_MANAGER(AqConnectedServerNode);

	jServerInfo& Base(){ return *this;}
	boost::timer m_Timer;//서버시작시간

	serverid_t Get_sid(){ return Base().Get_m_sid();}
	tcstr Get_ServerName(){ return m_sName.c_str();}

	AqConnectedServerNode::AqConnectedServerNode()
	{
		m_pS=0;
	}

	//--------------------------------------------------------------------------
	// jConnectUser Virtual func
	//--------------------------------------------------------------------------
	virtual serverid_t GetUID(){ return Base().Get_m_sid(); }
	virtual tcstr GetUserName(){return m_sName.c_str(); }
	virtual void Write_Packet(jPacket_Base& pk)
	{
		if(m_pS) m_pS->WritePacket(&pk);
	}
	//--------------------------------------------------------------------------
	// jVectorNode virtual func
	//--------------------------------------------------------------------------
	virtual void Create()
	{
		m_pS=0;
		jCLEAR(Base());
	}
	virtual void Destroy()
	{

	}
	virtual void CopyFrom(const AqConnectedServerNode& o)
	{
		jAssert0(0 && "AqConnectedServerNode::CopyFrom");
	}

};
tcstr ToString(AqConnectedServerNode* pServer, tname1024_t buf);




#endif // __jAqServerNode1_header__
