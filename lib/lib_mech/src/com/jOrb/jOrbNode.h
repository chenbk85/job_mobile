/* file : jOrbNode.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-10-29 19:02:22
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jOrbNode_header__
#define __jOrbNode_header__
#pragma once

#include "interface/jIOrb.h"
#include "interface/net/jConnectUser.h"
using namespace nMech::nORB;
#include "header/jRocker.h"

struct jOrbNode : public jConnectUser<jIPacketSocket_IOCP*,jIP_Address> , public jIOrbNode ,public nDataStruct::yVectorNode<jOrbNode>
{
	jINTERFACE_HEADER(jIOrbNode);
	jDECLEAR_YVECTOR_MANAGER(jOrbNode);

	void CopyFrom(const jOrbNode& ){ assert(0);	}
	void Create()
	{
		m_hWndTarget=0;
		m_pS=0;
		m_sName.clear();

	}
	void Destroy()
	{
		m_hWndTarget=0;
		m_pS =0;
	}


	jOrbNode()
	{
		jOrbNode::Create();
	}
	jLIST_TYPEDEF_map(tstring, Notify_callback_t , m_mapXmlDownEvent);
	void call_XmlEvent(cstr name,jID* pD);

	virtual void Write_Packet(jPacket_Base& pk){if(m_pS)m_pS->WriteToPacket_Direct(&m_uid,&pk);}
	virtual void WritePacket(jPacket_Base* pk){if(m_pS)m_pS->WriteToPacket_Direct(&m_uid,pk);}
	nEVENT::jEvent m_IsAlive;
	HWND m_hWndTarget;
	jIE* m_peOrbService;//<ORB_APP_LIST>에서의 항목
	jID* m_pDocProtocal; // 접속된orb와 통신할 프로토콜 XML
	bool m_isRemoteServerMode;// 접속된 ORB에 대해 내가 서버로 작동하는지

	void Init(jIPacketSocket_IOCP* pS, jIP_Address& ip);
	void jOrbNode::_localCall(tcstr szOrbFunc, jIE* peData);

};



#endif // __jOrbNode_header__
