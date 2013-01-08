/* file : DBUserManager.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 17:25:24
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "DBUserManager.h"

cstr ToString(TDBCacheUser* pUser,tname_t buf)
{
	jt_sprintf(buf, _T("%s(%I64d:%d) T:%d D:%d")
		,jT(pUser->m_pjDBUserInfo->m_szID)
		,pUser->m_pjDBUserInfo->m_uid.m_id
		,pUser->m_pjDBUserInfo->m_uid.m_dc_sid
		,pUser->m_pToChannel ? 1 :0
		,pUser->m_pToGame ? 1 :0
		);

	return buf;
}
