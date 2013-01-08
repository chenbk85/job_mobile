/* file : PlugIn_Orb.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:11
comp.: wiki.test.com
title : 
desc : 

*/

#ifndef __PlugIn_Orb_header__
#define __PlugIn_Orb_header__
#pragma once

#include "jOrbNode.h"

#define jPLUGIN_header_code(NAME)\
	jDECLARE_RTTIOBJ(NAME);\
	JNET_PLUGIN_SINGTONE_DECL(NAME);\
	virtual void Start();\
	virtual void Stop();\
	VOID OnIoRead(jNETARG_SOCK_NUM_BUFF_LEN_IP);\
	virtual VOID OnIoWrote(jIPacketSocket_IOCP*pObject);\
	virtual VOID OnIoConnected(jIPacketSocket_IOCP* pPlugIn);\
	virtual VOID OnIoDisconnected(jIPacketSocket_IOCP*);\
	virtual bool ParseCmd(tcstr szCommand);\
	NAME();\
	nEVENT::jIMsgManager* m_pMM;\


#define jPLUGIN_cpp_code_Start(NAME)\
	jDEFINE_RTTIOBJ_BY_SCOPE(NAME,jNet, 1,1);\
	JNET_PLUGIN_SINGTONE_DEFINE(NAME);\
	VOID NAME::OnIoRead(jNETARG_SOCK_NUM_BUFF_LEN_IP)\
{\
	jNamedEventNode* pHN = pHT->GetByNum(pk->num);\
	jWARN(_T("%d:%s"),pk->num,pHN?pHN->m_szName:jS(NULL));\
}\
	VOID NAME::OnIoWrote(jIPacketSocket_IOCP* pSocket){}\
	void NAME::Start()\
{\
	NAME::Set(this);\
	jLOG(jFUNC1 );\



#define jPLUGIN_cpp_code_Stop(NAME)\
}\
	void NAME::Stop()\
{\


#define jPLUGIN_cpp_code_End(NAME)\
NAME::Set(0);\
jLOG(jFUNC1 );\
}\



//--------------------------------------------------------------------------
class PlugIn_Orb : public jIPlugIn_Net_SQ<PlugIn_Orb,jIPlugIn_Connection > 
//--------------------------------------------------------------------------
{
public:
	jPLUGIN_header_code(PlugIn_Orb);

	virtual tcstr GetPlugInNicName(){ return _T("PlugIn_Orb");}

#define for_each_PT_MEMEBER(func)\

	//func(nTestServer,TS_HELLO)\

	for_each_PT_MEMEBER(jPT_MEMBER);

	void Write_Packet(jIP_Address &ip ,jPacket_Base& pk){m_pClientSession->Get_ClientSocket(0)->WriteToPacket_Direct(&ip,&pk);}
	void WritePacket(jIP_Address &ip ,jPacket_Base* pk){m_pClientSession->Get_ClientSocket(0)->WriteToPacket_Direct(&ip,pk);}

};

DECLARE_INSTANCE_TYPE(PlugIn_Orb);

extern PlugIn_Orb* g_pCurrPlugIn;

#endif // __PlugIn_Orb_header__
