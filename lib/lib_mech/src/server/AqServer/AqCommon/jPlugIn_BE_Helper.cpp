/* file : AqServerUserBase.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-31 15:09:09
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jPlugIn_BE_Helper.h"
#include "AqClientUserBase.h"

#include "network/protocal/PT_UserServer_Enum.h"
using namespace nNET::nUserServer;

#include "network/protocal/PT_WorldServer_Enum.h"
using namespace nNET::nWorldServer;

#include "network/protocal/PT_DBCacheServer_Enum.h"
using namespace nNET::nDBCacheServer;


jIPacketSocket_IOCP* jPlugIn_BE_Helper::Start_ClientSocket(cstr szServer ,nXML::jE e)
{
	if(e.empty()) return 0;
	cstr szIP = e.Attr(jS(m_szServiceIP))->Get_cstr();
	int port = e.Attr(jS(m_service_port))->Get_int();

	fname_t szIPS;
	jt_sprintf(szIPS,_T("%s:%d"),szIP,port);
	jIE* pE = m_pE->Find(szServer);
	assert(pE && "Start_ClientSocket");
	pE->Set_cstr(szIPS);
	pE->GetAttrVar(jS(ENABLE))->Set_bool(true);
	jIPacketSocket_IOCP* pS = m_pClientSession->Start_ClientSocket(pE);
	pS->Get_jIE()->SetUserData(jS(jServerInfo_jIE),e.BaseI());
	return pS;
}


jIPacketSocket_IOCP* jPlugIn_BE_Helper::ConnectToWorldServer(nXML::jE e)
{
	if(e.empty()) return 0;
	jVar v = e.Attr(jS(m_eType));
	if(v.empty() || !v->IsContents(jS(WorldServer) ) )
	{
		e = e->FindByFirstAttr(jS(m_eType),jIVar::EDcstr,jS(WorldServer) );
	}
	return this->Start_ClientSocket(jS(ToWorld),e);
}

jIPacketSocket_IOCP* jPlugIn_BE_Helper::ConnectToDBCacheServer(nXML::jE e)
{
	if(e.empty()) return 0;
	jVar v = e.Attr(jS(m_eType));
	if(v.empty() || !v->IsContents(jS(DBCacheServer) ) )
	{
		e = e->FindByFirstAttr(jS(m_eType),jIVar::EDcstr,jS(DBCacheServer) );
	}
	jIE* pOrg = m_pE->Find(jS(ToDBCache));
	fname_t szName;
	jt_sprintf(szName , _T("ToDBCache_%s") , e.Attr(jS(m_szName))->Get_cstr() );
	nXML::jE eDC = nXML::jE(m_pE)[szName]; // szName으로 기존에 노드가 있을수 있다.(접속되었으나 Dissconnect되었다가 다시 접속되는상황!)
	pOrg->CopyTo(eDC);
	eDC->ChangeTagName(szName);
	return this->Start_ClientSocket(szName,e);
}



tcstr ToString(_AqClientUserBase* p, tname1024_t buf)
{
	jt_sprintf(buf, _T("%s : dc(%d) %s"),jT(p->m_szID), p->m_uid.m_dc_sid, ToString(p->m_EUserGPS));
	return buf;
}


const int iMaxSendUser_U4_USER_CONNECTION_NOTIFY = 100;

void jPlugIn_BE_Helper::Set_U4_USER_CONNECTION_NOTIFY_CS(userid_t uid, acstr id,bool isConnect)
{
	jAUTO_LOCK_CS(m_mapU4_USER_CONNECTION_NOTIFY_CS);
	m_mapU4_USER_CONNECTION_NOTIFY[id]=isConnect;
	if(m_mapU4_USER_CONNECTION_NOTIFY.size() < iMaxSendUser_U4_USER_CONNECTION_NOTIFY) return;

	nswb16000_t buf;
	vector<astring> uid_connect,uid_disconnect;
	Make_U4_USER_CONNECTION_NOTIFY(uid_connect, uid_disconnect);
	if(!m_pToUser)
	{
		GetjILog()->Warning(jFUNC1 _T("m_pToUser == NULL"));
	}
	else
		m_pToUser->WritePacket(&WRITE_U4_USER_CONNECTION_NOTIFY(buf, uid_connect, uid_disconnect));

	if(m_MyInfo.m_eType==jServerInfo::eTown || m_MyInfo.m_eType==jServerInfo::eDungeon)
	{
		if(uid_disconnect.size() && m_pToWorld)
			m_pToWorld->WritePacket(&nWorldServer::WRITE_W4_USER_DISCONNECT(buf, uid_disconnect));
	}
	m_mapU4_USER_CONNECTION_NOTIFY.clear();
}

bool jPlugIn_BE_Helper::Make_U4_USER_CONNECTION_NOTIFY(vector<astring>& uid_connect , vector<astring>& uid_disconnect)
{
	jAUTO_LOCK_CS(m_mapU4_USER_CONNECTION_NOTIFY_CS);
	int is = m_mapU4_USER_CONNECTION_NOTIFY.size();
	if(!is) return false;

	m_mapU4_USER_CONNECTION_NOTIFY_it it = m_mapU4_USER_CONNECTION_NOTIFY.begin(), ie = m_mapU4_USER_CONNECTION_NOTIFY.end();
	int i=0, iCon=0 ,iDis=0;
	for(i=0;it!=ie;++it,++i)
	{
		if(it->second)
		{
			uid_connect.push_back(it->first);
			++iCon;
		}
		else
		{
			uid_disconnect.push_back(it->first);
			++iDis;
		}
	}
#ifdef _DEBUG
	GetjILog()->Log(_T("1Make_U4_USER_CONNECTION_NOTIFY: uid_disconnect.size()=%d uid_connect.size()=%d"), iDis, iCon);
#endif
	m_mapU4_USER_CONNECTION_NOTIFY.clear();
	return is;
}

void jPlugIn_BE_Helper::SetServerInfo_UserCount(serverid_t sid, uint16 userCnt)
{
	nXML::jE e = Find_Server(sid);
	if(!e.empty()) return;
	e.Attr(jS(m_iTotClient))->Set_int(userCnt);
}

jIE* jPlugIn_BE_Helper::Find_Server(serverid_t sid)
{
	int _sid = sid;
	jIE* pE = m_eServers->FindByFirstAttr(jS(m_sid), jIVar::EDint , &_sid);
	if(!pE)
	{
		GetjILog()->Warning(_T("jPlugIn_BE_Helper::Find_Server not found : %d"),sid);
	}
	return pE;
}

jIE* jPlugIn_BE_Helper::Find_WorldServer(cstr szWorld)
{
	jIE* pE = m_eServers->Find(szWorld);
	if(!pE) return 0;
	//pE->DebugPrint(true);
	return pE->FindByFirstAttr(jS(m_eType), jIVar::EDcstr , jS(WorldServer));
}

bool jPlugIn_BE_Helper::Call_C_ECHO(wcstr szMsg)
{
	
	return false;
}

void jPlugIn_BE_Helper::erase_DBCache(jIPacketSocket_IOCP* pS)
{ 
	#define jLAMDA_finddc(X,Z) Z(jIPacketSocket_IOCP*,pS)
	jLAMDA_find_if(finddc,m_listToDBCache_vt&)
	{
		return it.second==pS;
	}
	jLAMDA_end();
	m_listToDBCache_it it = jFIND_IF(m_listToDBCache,finddc(pS));
	if(it!=m_listToDBCache.end())
		m_listToDBCache.erase(it);
}
jIPacketSocket_IOCP* jPlugIn_BE_Helper::find_DBCache(serverid_t sid)
{
	m_listToDBCache_it it = m_listToDBCache.find(sid);
	if(it==m_listToDBCache.end()) return 0;
	return it->second;
}


void jPlugIn_BE_Helper::test_dc_echo()
{
	m_listToDBCache_it it = m_listToDBCache.begin(), ie = m_listToDBCache.end();
	nswb256_t buf;
	for( ; it!=ie ; ++it)
	{
		it->second->WritePacket(&WRITE_DC_ECHO(buf,_T("asdf "),0));
	}
}
