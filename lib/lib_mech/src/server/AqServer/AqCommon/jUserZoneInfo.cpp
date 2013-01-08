/* file : jPlayerBase.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-04 14:43:59
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jPlayerBase.h"

jDEFINE_YVECTOR_MANAGER(jPlayerBase, 1024,256);

AQ_SERVER_LIB_API tcstr ToString(jPlayerBase* pUser , tname1024_t buf)
{
	jt_sprintf(buf, _T("%s[%I64d:%d] LG=%u L=%u, R=%u (%d:%d:%d)") 
		, jT(pUser->m_szID)
		,pUser->m_uid.m_id , pUser->m_uid.m_dc_sid
		,pUser->Get_ConnectedServer(jServerInfo::eLogin)
		,pUser->Get_ConnectedServer(jServerInfo::eTown)
		,pUser->Get_ConnectedServer(jServerInfo::eDungeon)
		,pUser->m_LoginTime.wHour
		,pUser->m_LoginTime.wMinute
		,pUser->m_LoginTime.wSecond
		);
	return buf;
}

//--------------------------------------------------------------------------
jPlayerBase* jUserZoneInfoList::_find_by_username(acstr _id)
//--------------------------------------------------------------------------
{
	aname64_t id;
	ja_strcpy(id,_id);
	ja_strlwr(id);
	m_mapUser_by_idname_it it = m_mapUser_by_idname.find(id);
	if(it==m_mapUser_by_idname.end())
		return 0;
	return it->second;
}

//--------------------------------------------------------------------------
jPlayerBase* jUserZoneInfoList::_find_by_uid(userid_t uid)
//--------------------------------------------------------------------------
{
	m_mapUser_by_uid_it it = m_mapUser_by_uid.find(uid);
	if(it==m_mapUser_by_uid.end())
		return 0;
	return it->second;
}


//--------------------------------------------------------------------------
jPlayerBase* jUserZoneInfoList::_find_in_yvector(username_t id)
//--------------------------------------------------------------------------
{
	m_UserZoneList_it it = m_UserZoneList.begin(), ie = m_UserZoneList.end();
	for( ; it!=ie ; ++it)
	{
		if(!ja_stricmp(it->m_szID, id))
		{
			return it;
		}
	}
	return 0;
}
//--------------------------------------------------------------------------
jPlayerBase* jUserZoneInfoList::_find_in_yvector(userid_t uid)
//--------------------------------------------------------------------------
{
	m_UserZoneList_it it = m_UserZoneList.begin(), ie = m_UserZoneList.end();
	for( ; it!=ie ; ++it)
	{
		if(it->m_uid==uid)
		{
			return it;
		}
	}
	return 0;
}


/*
//--------------------------------------------------------------------------
jPlayerBase* jUserZoneInfoList::find_by_yhandle_World(userid_t uid)//월드서버에서 사용
//--------------------------------------------------------------------------
{
	jPlayerBase* pUser = m_UserZoneList.GetNode(uid.m_w_handle);
#ifdef _DEBUG
	if(pUser)
	{
		jAssert0(this->_find_by_username(pUser->m_szID));
	}
#endif
	return pUser;
}
*/




void jUserZoneInfoList::erase_by_name(acstr _id)
{
	jPlayerBase* pUser =0;
	aname64_t id;
	ja_strcpy(id,_id);
	ja_strlwr(id);
	m_mapUser_by_idname_it it = m_mapUser_by_idname.find(id);
	if(it!=m_mapUser_by_idname.end())	
	{
		pUser = it->second;
		m_mapUser_by_idname.erase(it);
	}
	else
	{
		pUser = _find_in_yvector(id);
		if(pUser)
		{
			GetjILog()->Warning(jFUNC1 _T("user finded at yvector : %s"),jT(pUser->m_szID) );
		}
	}

	if(pUser)
	{
		m_mapUser_by_uid.erase(pUser->m_uid);
		m_UserZoneList.erase(pUser);
	}
}

void jUserZoneInfoList::erase_by_uid(userid_t uid)
{
	jPlayerBase* pUser =0;
	m_mapUser_by_uid_it it = m_mapUser_by_uid.find(uid);
	if(it!=m_mapUser_by_uid.end())	
	{
		pUser = it->second;
		m_mapUser_by_uid.erase(it);
	}
	else
	{
		pUser = _find_in_yvector(uid);
		if(pUser)
		{
			GetjILog()->Warning(jFUNC1 _T("user finded at yvector : %s"),jT(pUser->m_szID) );
		}
	}

	if(pUser)
	{
		m_mapUser_by_idname.erase(pUser->m_szID);
		m_UserZoneList.erase(pUser);
	}

}
void jUserZoneInfoList::Regist_by_uid(jPlayerBase* pUser,userid_t uid)
{
#ifdef _DEBUG
	jAssert0(!pUser->m_uid.m_id);
	m_mapUser_by_uid_it it = m_mapUser_by_uid.find(uid);
	if(it!=m_mapUser_by_uid.end())
	{
		GetjILog()->Warning(jFUNC1 _T("uid(%I64d ,%s) 가 m_mapUser_by_uid에 등록되어 있슴"), uid.m_id, jT(it->second->m_szID));
	}
	jAssert0(this->_find_by_username(pUser->m_szID));
#endif
	pUser->m_uid = uid;
	pUser->SetFlag_GoingTo_Login(false);// uid가 등록되면 정식으로 접속성공한것이다.
	m_mapUser_by_uid[uid] = pUser;
}


//--------------------------------------------------------------------------
jPlayerBase* jUserZoneInfoList::push_back_with_world_sid(username_t szID,serverid_t world_sid)
//--------------------------------------------------------------------------
{
	jPlayerBase* pUser = _push_back(szID);
	if(!pUser) return 0;
	pUser->m_sid_world = world_sid;
	pUser->SetFlag_GoingTo_Login(true);//Regist_by_uid()에 의해  false로 만든다.

	return pUser;
}

//--------------------------------------------------------------------------
jPlayerBase* jUserZoneInfoList::_push_back(IN username_t id)
//--------------------------------------------------------------------------
{
	ja_strlwr(id);
	m_mapUser_by_idname_it it = m_mapUser_by_idname.find(id);
	if(it!=m_mapUser_by_idname.end())
	{
		GetjILog()->Error(jFUNC1 _T("user is founded : m_mapUser_by_idname%s"),jT(id));
#ifdef _DEBUG
		jPlayerBase* pUser = this->_find_in_yvector(id);
		jAssert0(pUser && "jUserZoneInfoList::_push_back");
#endif
		return it->second;
	}
#ifdef _DEBUG
	if(_find_in_yvector(id))
	{
		GetjILog()->Error(jFUNC1 _T("user is founded :_find_in_yvector ; %s"), id);
	}
#endif
	jPlayerBase* pUser = m_UserZoneList.push_back();
	ja_strcpy(pUser->m_szID , id);
	m_mapUser_by_idname[id] = pUser;
	GetLocalTime(&pUser->m_LoginTime);

	return pUser;
}
