/* file : DBQuery_Proxy.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 16:09:09
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "network/protocal/PT_DBQueryServer_Enum.h"
using namespace nDBQueryServer;


DBQuery_Proxy g_Users_DC;

DBQuery_Proxy::DBQuery_Proxy()
{
}

DBQuery_Proxy::~DBQuery_Proxy()
{
	if(m_hReadQueueThread)
	{
		TerminateThread(m_hReadQueueThread, 0);
	}
}


//--------------------------------------------------------------------------
unsigned __stdcall ReadQueueThread( void* lp)
//--------------------------------------------------------------------------
{
	DBQuery_Proxy::m_mapjDBEventNode_it it;
	DBQuery_Proxy* pQP = (DBQuery_Proxy*)lp;
	nMech::nUtil::nSharedMem::jPacket_Base pk;
	BYTE pReadBuff[nMech::nUtil::nSharedMem::MAX_PKTSIZE];
	pk.buf = pReadBuff;
	
	static jIPacketDispatch* pjIPacketDispatch= jCREATE_INTERFACE(nMech::nNET::jIPacketDispatch);
	jNamedEventTable* pPHT = pjIPacketDispatch->GetNamedEventTable(_T("DBQueryServer") );
	//jNamedEventTable* pPHT = (jNamedEventTable*)nMech::jBase::FindNamedPointer(_T("nNET"),_T("DBQueryServer") );

	while(TRUE)
	{
		if( !pQP->m_RecvQueue.ReadPacket(pk) ) {Sleep(0);continue;}

		it = pQP->m_mapjDBEventNode.find(pk.num);
		if(it==pQP->m_mapjDBEventNode.end())
		{
			jNamedEventNode* pPHN = pPHT->GetByNum(pk.num);
			if(!pPHN)
			{
				GetjILog()->Warning(_T("ERROR : unkown DBQuery ID  , pPHT->GetByNum(%d)==NULL"), pk.num);
			}
			else
			{
				GetjILog()->Warning(_T("ERROR : unkown DBQuery ID : pPHT->GetByNum(%d)==%s"),pk.num,pPHN->m_szName);
			}
			continue;
		}
		it->second->Call(pk.buf, pk.len,0,pQP);
	}
	return 0;
}

static void for_each_func_jPlugInHelpNode(jNamedEventNode* pT , jIE* pE,jIPacketDispatchTable* pTable)
{
	DBQuery_Proxy* p = (DBQuery_Proxy*)pTable;
	p->insertNode(pT);
}

void DBQuery_Proxy::insertNode(jNamedEventNode* pT )
{
	_jDBEventNode* pEN = (_jDBEventNode*)nMech::jBase::FindNamedPointer(_T("jDBEvent"),pT->m_szName);
	if(!pEN) return;
	GetjILog()->Log(_T("regist jDBEvent::%s %d"), pT->m_szName, pT->m_id);
	m_mapjDBEventNode[pT->m_id] = pEN;
}

//--------------------------------------------------------------------------
BOOL DBQuery_Proxy::Begin()
//--------------------------------------------------------------------------
{
	jNamedEventTable* g_pPlugInHelpTableList = (jNamedEventTable*)nMech::jBase::FindNamedPointer(_T("nNET"),_T("DBQueryServer") );
	g_pPlugInHelpTableList->for_each(for_each_func_jPlugInHelpNode,0,(jIPacketDispatchTable*)this);

	if(!m_SendQueue.InitailizeMMF( sizeof(nMech::nUtil::nSharedMem::jSmqPacket_UNIT)
		, pv_SM_QUEUE_MAX_COUNT->Get_int()
		, pv_SM_CACHE2QUERY_NAME->Get_cstr(), FALSE ))
	{
		GetjILog()->Error(_T("Shared Memory Open Fail!!\n"));		
		return FALSE;
	}

	if(!m_RecvQueue.InitailizeMMF( sizeof(nMech::nUtil::nSharedMem::jSmqPacket_UNIT)
		, pv_SM_QUEUE_MAX_COUNT->Get_int()
		, pv_SM_QUERY2CACHE_NAME->Get_cstr(), FALSE))
	{
		GetjILog()->Error(_T("Shared Memory Open Fail!!\n"));	
		return FALSE;
	}

	UINT id;
	m_hReadQueueThread = (HANDLE)_beginthreadex( NULL, 0, ReadQueueThread, (LPVOID)this, 0, &id);
	GetjILog()->Log(_T("Shared Memory Initialize Success\n"));

	//--------------------------------------------------------------------------
	// user shared memory info initialize
	//--------------------------------------------------------------------------
	jAssert0(pv_SM_USER_MAX->Get_int() < 65000); // 2^16½Â

	if( !m_UsersSM.Init(pv_SM_USER_INFO_NAME->Get_cstr(), pv_SM_USER_MAX->Get_int() , sizeof(jUserZoneInfo_DC)) )
	{
		GetjILog()->Error(_T("m_UsersSM.Init(%s , %d,sizeof(jUserZoneInfo_DC)) error")
			,pv_SM_USER_INFO_NAME->Get_cstr() 
			,pv_SM_USER_MAX->Get_int());
		return false;
	}

	m_vecUsersSM.resize(pv_SM_USER_MAX->Get_int());
	//jBE_ret(false);
	for(int id= 0; id< pv_SM_USER_MAX->Get_int(); id++)
	{
		AqDBCacheUser* pAccount = &m_vecUsersSM[id];
		pAccount->m_pjDBUserInfo = m_UsersSM.GetUnit(id);
		//pAccount->m_pjDBUserInfo->m_uid.m_dc_sid = pBE->m_sid;
		pAccount->m_pjDBUserInfo->m_uid.m_dc_handle = id;
	}

	_tprintf(TEXT("Shared Memory Create complete \n\r"));


	nswb1024_t buf;
	WritePacket(WRITE_DC2DQ_CONNECT(buf
		,pv_WORLD_NAME->Get_cstr()
		,pv_SM_QUERY2CACHE_NAME->Get_cstr()
		,pv_SM_CACHE2QUERY_NAME->Get_cstr()
		,pv_SM_USER_INFO_NAME->Get_cstr()
		));


	return TRUE;
}

void DBQuery_Proxy::Set_sid(serverid_t sid)
{
	for(int id= 0; id< m_vecUsersSM.size(); id++)
	{
		AqDBCacheUser* pAccount = &m_vecUsersSM[id];
		pAccount->m_pjDBUserInfo->m_uid.m_dc_sid = sid;
	}
}

//--------------------------------------------------------------------------
void DBQuery_Proxy::WritePacket(nMech::nUtil::nSharedMem::jPacket_Base&pk)
//--------------------------------------------------------------------------
{
	int count = 0;
	while( m_SendQueue.WritePacket(pk) >= nMech::nUtil::nSharedMem::SMQ_FULL )
	{
		GetjILog()->Error(_T("WritePacket fail...\n"));
		Sleep(100);
		count++;
		if(count == 10) 
			break;
	}
}

AqDBCacheUser* DBQuery_Proxy::Going_to_Login(userid_t uid , username_t id)
{
	AqDBCacheUser* pUser =0;
	int i;
	for(i=0; i< m_vecUsersSM.size() ; ++i)
	{
		pUser = &m_vecUsersSM[i];
		if(pUser->m_pjDBUserInfo->m_eUsingState==jUserZoneInfo_DC::eNOT_USE) 
		{
			//GetjILog()->Log(_T("[Insert Client : %d] \n"), i);
			pUser->m_pjDBUserInfo->m_eUsingState=jUserZoneInfo_DC::eGOING_TO_LOGIN;
			pUser->m_pjDBUserInfo->m_uid.m_w_handle = uid.m_w_handle;
			ja_strcpy(pUser->m_pjDBUserInfo->m_szID ,id);
			pUser->m_pjDBUserInfo->m_uid.m_dc_handle = i;

			break;
		}
	}
	return pUser;
}

AqDBCacheUser* DBQuery_Proxy::Going_to_delete(acstr _id)
{
	AqDBCacheUser* pUser = find_by_username(_id);
	if(pUser)
	{
		pUser->m_pjDBUserInfo->m_eUsingState=jUserZoneInfo_DC::eNOW_DELETING;
	}
	else
	{
		GetjILog()->Warning(jFUNC1 _T("user not found : %s"),_id);
	}
	return pUser;
}


AqDBCacheUser*	DBQuery_Proxy::find_by_yhandle(userid_t uid)
{
	if(uid.m_dc_handle >= m_vecUsersSM.size())
	{
		fname_t buf;
		GetjILog()->Warning(jFUNC1 _T("uid.m_dc_handle >= m_vecUsersSM.size() : %s") , ToString(uid,buf));
		return 0;
	}
	return &m_vecUsersSM[uid.m_dc_handle];
}

AqDBCacheUser*	DBQuery_Proxy::find_by_username(acstr _id)
{
	aname64_t id;
	ja_strcpy(id,_id);
	ja_strlwr(id);

	AqDBCacheUser* pUser =0;
	int i;
	for(i=0; i< m_vecUsersSM.size() ; ++i)
	{
		pUser = &m_vecUsersSM[i];
		if(!ja_strcmp(pUser->GetDB()->m_szID, id)) 
		{
			break;
		}
	}
	return pUser;
}

void			DBQuery_Proxy::erase_now(userid_t uid)
{
		AqDBCacheUser* pUser =find_by_yhandle(uid);
		if(!pUser)
		{
			GetjILog()->Warning(jFUNC1 _T("user not found : %d:%d") , uid.m_dc_sid,uid.m_dc_handle);
		}
		pUser->m_pjDBUserInfo->m_eUsingState = jUserZoneInfo_DC::eNOT_USE;
}

AqDBCacheUser* DBQuery_Proxy::erase_now_by_username(acstr id)
{
	AqDBCacheUser* pUser =find_by_username(id);
	if(pUser)
		pUser->m_pjDBUserInfo->m_eUsingState = jUserZoneInfo_DC::eNOT_USE;
	return pUser;
}