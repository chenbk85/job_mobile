// GameInfo.h: interface for the CGameInfo class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __GameUser_H__
#define __GameUser_H__
#if _MSC_VER>1000
#pragma once
#endif // _MSC_VER>1000

#include "../../Protocol Buffers/Poker/AdlGameUser_Poker.h"

using namespace adl;

class CGameUser
{
public:
	RCUserData m_RCUserData;
public:
	CGameUser(void){ InitGameUser(); }
	virtual ~CGameUser(void){ FreeGameUser(); }
	void InitGameUser(void){ }
	void FreeGameUser(void){ m_RCUserData.Clear(); }
public:
	RCUserData& GetRCUT(void){ return m_RCUserData; }
public:
	void AddUser(RCUser& ud){ m_RCUserData.AddUser(ud); }
	void RemoveUser(long lUSN){ m_RCUserData.RemoveUser(lUSN); }
	RCUser* FindUser(long lUSN){ return m_RCUserData.FindUser(lUSN); }
	int	GetIndex(long lUSN){ return m_RCUserData.GetIndex(lUSN); }
	bool ExistUser(){ return m_RCUserData.ExistUser(); }
};


#endif
