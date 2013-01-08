/* file : TClientUserBase.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-28 15:59:17
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __AqClientUserBase_header__
#define __AqClientUserBase_header__
#pragma once

#include "interface/net/jINetGrid.h"
#include "../TCommonBase/jPlayerBase.h"



//! jGridNode_ClientBase  => LoginServer, Client, GameServer? ,ChannelServer에서 사용.
struct jGridNode_ClientBase : public nNET::jIGridNode
{
	typedef jGridNode_ClientBase parent_t;
#ifdef JIMPLIMENT_jGridNode_Client1234
	// Login, Game, Channel server에서 사용될 유저 컨넥션 객체
	jDECLARE_RTTIOBJ(jGridNode_ClientBase);
	virtual void Create()
	{
	}
	virtual void Destroy()
	{
	}
	jDEFINE_RTTIOBJ(jGridNode_ClientBase,jINetGrid,10,50);

#endif
	EUserGPS m_EUserGPS;
	uint32	m_playTime;	//2009/03/19 HMC 게임사용 시간[분단위]
	jPlayerBase* m_pPlayer;
	virtual player_id_t GetID(){ return m_pPlayer->m_pid;}
	virtual void _Create()
	{
		m_pPlayer =0;
		m_EUserGPS = eGPS_NULL;
	}
	virtual void _Destroy()
	{
		m_EUserGPS = eGPS_NULL;
	}
	void jGridNode_ClientBase::StartPlayTime()
	{
		m_playTime = GetTickCount();
	}
	int jGridNode_ClientBase::GetPlayTime()
	{
		uint32 rTime = GetTickCount() - m_playTime;		
		return rTime > 0 ? rTime / 60000 : 0; //1000*60 분단위
	}

};



//tcstr T_SERVER_LIB_API ToString(jGridNode_ClientBase* pUser, tname1024_t buf);


inline tcstr ToString(jGridNode_ClientBase* p, tname1024_t buf)
{
	tname1024_t buf1;
	ToString(p->m_pPlayer,buf1);
	jt_sprintf_s(buf,1024, _T("%s : %s"),buf1,ToString(p->m_EUserGPS));
	return buf;
}

// LoginServer, ChannelServer, client에서 사용.
#define jCI(pGN)			jGridNode_Client* ci = (jGridNode_Client*)(jGridNode_ClientBase*)pGN; jRETURN(ci && ci->m_pPlayer);
#define jCI_ret(ret,pGN)	jGridNode_Client* ci = (jGridNode_Client*)(jGridNode_ClientBase*)pGN; jRETURN_ret(ret, ci && ci->m_pPlayer);


#endif // __AqClientUserBase_header__
