/* file : AqClientUserBase.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-28 15:59:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __AqClientUserBase_header__
#define __AqClientUserBase_header__
#pragma once

#include "interface/net/jConnectUser.h"

struct _AqClientUserBase : public jConnectUser<jIPacketSocket_IOCP*,userid_t> 
{
	username_t m_szID;
	uint32	m_playTime;	//2009/03/19 HMC 게임사용 시간[분단위]
	EUserGPS m_EUserGPS;
	serverid_t m_sid_world;
	virtual void _Create()
	{
		m_pS=0;
		m_uid.m_id=0;
		m_sName.clear();
		jCLEAR(m_szID);
		m_EUserGPS = eGPS_NULL;
	}
	virtual void _Destroy()
	{
		m_pS=0;
		m_uid.m_id=0;
	}

	virtual void Write_Packet(jPacket_Base& pk){if(m_pS)m_pS->WritePacket(&pk);}
	virtual void WritePacket(jPacket_Base* pk){if(m_pS)m_pS->WritePacket(pk);}

	void _AqClientUserBase::StartPlayTime()
	{
		m_playTime = GetTickCount();
	}

	int _AqClientUserBase::GetPlayTime()
	{
		uint32 rTime = GetTickCount() - m_playTime;		
		return rTime > 0 ? rTime / 60000 : 0; //1000*60 분단위
	}

};

tcstr AQ_SERVER_LIB_API ToString(_AqClientUserBase* pUser, tname1024_t buf);



#endif // __AqClientUserBase_header__
