/* file : AqDBCacheUser.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 17:25:16
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __2323AqDBCacheUser_432
#define __2323AqDBCacheUser_432

#pragma once

#include "../AqDBQuery/MemoryMap.h"
#include "../AqCommon/jUserZoneInfo_DC.h"


struct AqConnectedServerNode;

class AqDBCacheUser
{
	int m_iFlag;
public:
	jUserZoneInfo_DC*		m_pjDBUserInfo;
	jUserZoneInfo_DC* GetDB(){return m_pjDBUserInfo;}

	nAQ::Use_Town* TownUse(townid_t aid)
	{
		if(aid>Town_size() || aid<=0) 
		{
			GetjILog()->Log(jFUNC1 _T("townid_t id가 잘못되었습니다. : %d"),aid);
			return 0;
		}
		return GetDB()->m_Town+aid-1;
	}

	userid_t Get_uid(){ return GetDB()->m_uid;}
	acstr Get_name(){ return GetDB()->m_szID;}

	uint8&				Town_size(){ return GetDB()->Town_size();}
	nAQ::Use_Town*	Town_at(townid_t aid){ return GetDB()->Town_at(aid);}
	void				Town_erase(townid_t aid);

	AqConnectedServerNode*	m_pToTown;
	AqConnectedServerNode*	m_pToDungeon;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// AqDBCacheUser
	AqDBCacheUser::AqDBCacheUser()
	{
		_Destroy();
	}

	AqDBCacheUser::~AqDBCacheUser()
	{
		_Destroy();
	}
	void _Create()
	{
		m_pToTown =0;
		m_pToDungeon=0;
	}

	void AqDBCacheUser::_Destroy()
	{
		m_pjDBUserInfo=0;
	}

	void Setup_DBData(){}//db data 로딩후 첫 초기화
};

cstr ToString(AqDBCacheUser* pUser,fname_t buf);


#endif // __2323AqDBCacheUser_432
