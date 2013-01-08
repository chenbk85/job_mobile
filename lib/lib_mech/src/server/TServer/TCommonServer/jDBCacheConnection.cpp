/* file : jDBCacheConnection.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-02-12 14:17:08
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jDBCacheConnection.h"


jDBCacheInfo* jDBCacheConnection::get_free_server()
{
	if(!m_Servers.size()) return 0;
#if 1
	static int s_index=0;

	if(s_index>=m_Servers.size())
		s_index=0;

	m_Servers_it it = m_Servers.begin(), ie = m_Servers.end() ;
	for(int i=0 ;it!=ie;++it)
	{
		if(i==s_index)
			break;
	}

	if(it==ie)
	{
		it= m_Servers.begin();
		s_index=0;
	}

	jDBCacheInfo* pDB =0;
	for( ; it!=ie ; ++it)
	{
		pDB = &it->second;
		if(pDB->m_isOnline && ( pDB->Base().Get_m_iTotClient() < pDB->Base().Get_m_iMaxClient() ) )
		{
			break;
		}
	}
	if(!pDB)
	{
		pDB =0;
		it = m_Servers.begin();
		s_index=0;
		for( ; it!=ie ; ++it,++s_index)
		{
			pDB = &it->second;
			if(pDB->m_isOnline && ( pDB->Base().Get_m_iTotClient() < pDB->Base().Get_m_iMaxClient() ) )
			{
				break;
			}
		}

	}
	else
		++s_index;

	if(!pDB)
	{
		GetjILog()->Warning(_T("db cache server is full"));
	}
	return pDB;
#else
	return &m_Servers.begin()->second;
#endif
}

bool jDBCacheConnection::erase(jIPacketSocket_IOCP* pS)
{ 
	jDBCacheInfo* pDB= (jDBCacheInfo*)pS->Get_jIE()->GetUserData(jS(jDBCacheInfo));
	if(pDB)
	{
		m_Servers.erase(pDB->Base().Get_m_sid());
		pS->Get_jIE()->SetUserData(jS(jDBCacheInfo),0);
		return true;
	}
	pS->Get_jIE()->DebugPrint(true);
	GetjILog()->Warning(_T("jDBCacheConnection::erase : pS is not db connection"));
	return false;
}

jDBCacheInfo* jDBCacheConnection::insert(jServerInfo &s,jIPlugIn_Connection* pP)
{ 
	nXML::jE eWhere = pP->m_pE;
	jDBCacheInfo& db = m_Servers[s.Get_m_sid()];
	db.Base()= s;
	nXML::jE eDB = eWhere(jS(ToDBCache));
	nXML::jE eNew= eWhere->InsertChildElement(jS(NULL));
	eDB->CopyTo(eNew);
	tname32_t szT ;
	jt_sprintf(szT, _T("ToDBCache_%d"),db .Base().Get_m_sid());
	eDB->ChangeTagName(szT);

	eNew.Attr(jS(ENABLE)).T() = (bool)true;
	fname_t buf;
	jt_sprintf(buf, _T("%s:%d"),s.Get_m_szServiceIP(),s.Get_m_service_port());
	eNew->Set_cstr(buf);
	db.m_pS = pP->m_pClientSession->Start_ClientSocket( eNew );
	if(!db.m_pS)
	{
		eNew->DebugPrint(true);
		GetjILog()->Warning(_T("dbcache 접속실패"));
		return 0;
	}
	db.m_pS->Get_jIE()->SetUserData(jS(jDBCacheInfo), &db);
	return &db;

}

jDBCacheInfo* jDBCacheConnection::insertCentral(jServerInfo &s)
{ 
	jDBCacheInfo& db = m_Servers[s.Get_m_sid()];
	db.Base()= s;
	return &db;
}

