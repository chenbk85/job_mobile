/* file : AqTestClientNode.h
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

#define for_each_TEST_CLIENT_TYPE(func)\
	func(TestClient)\
	func(AqMonitor)\



struct AqTestClientNode : public jConnectUser<jIPacketSocket_IOCP*,dummy_id_t> , public nDataStruct::yVectorNode<AqTestClientNode>
{
	typedef dummy_id_t KEY_TYPE_id_t;
	jDECLEAR_YVECTOR_MANAGER(AqTestClientNode);
	tname32_t m_szID;

	enum ETestClientType
	{
		ETestClientType_BEGIN,
		#define enum_DEFINE234(name) e##name,
		for_each_TEST_CLIENT_TYPE(enum_DEFINE234)
		ETestClientType_END,
	};
	ETestClientType m_eType;
	
	#define IsName234(name) bool Is##name(){return m_eType == e##name;}
	for_each_TEST_CLIENT_TYPE(IsName234);

	tcstr GetTypeName()
	{
		#define GetTypeName234(name) if(m_eType==e##name) return _T(#name);
		for_each_TEST_CLIENT_TYPE(GetTypeName234);
		return jS(NULL);
	};

	virtual void Create()
	{
		m_eType=ETestClientType_BEGIN;
		m_pS=0;
		m_uid=iHandle;
		m_sName.clear();
		jCLEAR(m_szID);
	}
	virtual void Destroy()
	{
		m_pS=0;
		m_uid=0;
	}
	virtual void CopyFrom(const AqTestClientNode& o){jASSERT0(0 && "AqTestClientNode::CopyFrom");}


	virtual void Write_Packet(jPacket_Base& pk){if(m_pS)m_pS->WritePacket(&pk);}
	virtual void WritePacket(jPacket_Base* pk){if(m_pS)m_pS->WritePacket(pk);}
};



#endif // __AqClientUser_header__
