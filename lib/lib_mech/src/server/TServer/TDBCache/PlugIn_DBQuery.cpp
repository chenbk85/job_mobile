/* file : PlugIn_DBQuery.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 16:09:09
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TDBCache.h"
#include <process.h>

PlugIn_DBQuery g_DQ;

PlugIn_DBQuery::PlugIn_DBQuery()
{
	m_ProcessID=0;
}

PlugIn_DBQuery::~PlugIn_DBQuery()
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
	PlugIn_DBQuery::m_mapjDBEventNode_it it;
	PlugIn_DBQuery* pQP = (PlugIn_DBQuery*)lp;
	nUtil::nSharedMem::jPacket_Base pk;
	BYTE pReadBuff[nUtil::nSharedMem::MAX_PKTSIZE];
	pk.buf = pReadBuff;
	
	static jIPacketDispatch* pjIPacketDispatch= jCREATE_INTERFACE(nMech::nNET::jIPacketDispatch);
	jNamedEventTable* pPHT = pjIPacketDispatch->GetNamedEventTable(_T("DBQueryServer") );
	//jNamedEventTable* pPHT = (jNamedEventTable*)nMech::jBase::FindNamedPointer(_T("nNET"),_T("DBQueryServer") );

	while(TRUE)
	{
		if( !pQP->m_RecvQueue.ReadPacket(pk) ) {Sleep(13);continue;}
		if(pk.num>=PT_DBQueryServer_END || pk.num <=nDBQueryServer::PT_VERSION	)
		{
			jWARN("Unkown packet recvied : %d",pk.num );
			continue;
		}

		it = pQP->m_mapjDBEventNode.find(pk.num);
		if(it==pQP->m_mapjDBEventNode.end())
		{
			jNamedEventNode* pPHN = pPHT->GetByNum(pk.num);
			if(!pPHN)
			{
				jWARN1(_T("ERROR : unkown DBQuery ID  , pPHT->GetByNum(%d)==NULL"), pk.num);
			}
			else
			{
				jWARN1(_T("ERROR : unkown DBQuery ID : pPHT->GetByNum(%d)==%s"),pk.num,pPHN->m_szName);
			}
			continue;
		}
		it->second->Call(pk.buf, pk.len,0,pQP);
	}
	return 0;
}

static void for_each_func_jPlugInHelpNode(jNamedEventNode* pT , jIE* pE,jIPacketDispatchTable* pTable)
{
	PlugIn_DBQuery* p = (PlugIn_DBQuery*)pTable;
	p->insertNode(pT);
}

void PlugIn_DBQuery::insertNode(jNamedEventNode* pT )
{
	_jDBEventNode* pEN = (_jDBEventNode*)nMech::jBase::FindNamedPointer(_T("jDBEvent"),pT->m_szName);
	if(!pEN) return;
	jLOG1(_T("regist jDBEvent::%s %d"), pT->m_szName, pT->m_id);
	m_mapjDBEventNode[pT->m_id] = pEN;
}

//--------------------------------------------------------------------------
BOOL PlugIn_DBQuery::Begin()
//--------------------------------------------------------------------------
{
	try
	{
		jNamedEventTable* g_pPlugInHelpTableList = (jNamedEventTable*)nMech::jBase::FindNamedPointer(_T("nNET"),_T("DBQueryServer") );
		g_pPlugInHelpTableList->for_each(for_each_func_jPlugInHelpNode,0,(jIPacketDispatchTable*)this);

		bool isCreate = m_SendQueue.InitailizeMMF( sizeof(nUtil::nSharedMem::jSmqPacket_UNIT)
			, pv_SM_QUEUE_MAX_COUNT->Get_int()
			, pv_SM_CACHE2QUERY_NAME->Get_cstr());

		isCreate = m_RecvQueue.InitailizeMMF( sizeof(nUtil::nSharedMem::jSmqPacket_UNIT)
			, pv_SM_QUEUE_MAX_COUNT->Get_int()
			, pv_SM_QUERY2CACHE_NAME->Get_cstr());

		UINT id;
		m_hReadQueueThread = (HANDLE)_beginthreadex( NULL, 0, ReadQueueThread, (LPVOID)this, 0, &id);
		jLOG1(_T("Shared Memory Initialize Success\n"));

		//--------------------------------------------------------------------------
		// user shared memory info initialize
		//--------------------------------------------------------------------------
		jAssert0(pv_SM_USER_MAX->Get_int() < 65000); // 2^16승

		isCreate = m_PlayersSM.Init(pv_SM_USER_INFO_NAME->Get_cstr(), pv_SM_USER_MAX->Get_int());

		vector<jPlayerObj*> vec;
		jAssert0(jPlayerObj::_size()==0);
		for(size_t id= 0; id< pv_SM_USER_MAX->Get_int(); id++)
		{
			jPlayerObj* pPlayer = jPlayerObj::_push_back();
			jPlayerDBSM* pSM = m_PlayersSM.at(id);
			pPlayer->m_SharedMemory = pSM;
			if(isCreate) //DBQuery서버가 떠져 있는게아니다.
			{
				pSM->m_pid.m_dc_handle = id; // yvector handle
				pSM->m_eUsingState = jPlayerDBSM::eNOT_USE;
			}
			else
			{
				//! DBCache가 리부팅된것이다.
				//jPlayerBase에 jPlayerDBSM정보를 동기홧킨다.
				pPlayer->m_pid = pSM->m_pid;
				pPlayer->m_uid = pSM->Get_uid();
				jw_strcpy_s(pPlayer->m_szID, pSM->m_User.Get_name());
				pPlayer->m_StartTime = pSM->m_StartTime;
			}
			vec.push_back(pPlayer);
		}
		jAssert0(jPlayerObj::_size()==pv_SM_USER_MAX->Get_int());
		for(id= 0; id < vec.size() ; ++id)
		{
			jPlayerObj::_erase(vec[id]);
		}
		jAssert0(jPlayerObj::_size()==0);

		_tprintf(TEXT("Shared Memory Create complete \n\r"));

		nswb1024_t buf;
		jNET_SEND(this, DC2DQ_CONNECT
			,pv_DOMAIN_NAME->Get_cstr()
			,pv_SM_QUERY2CACHE_NAME->Get_cstr()
			,pv_SM_CACHE2QUERY_NAME->Get_cstr()
			,pv_SM_USER_INFO_NAME->Get_cstr()
			,(uint32)GetCurrentProcessId()
			);

		return TRUE;
	}
	catch (tcstr sz)
	{
		jERROR(" -> %s ",sz);		
	}
	return FALSE;
}

void PlugIn_DBQuery::Init_sid(serverid_t sid)
{
	jAssert0(jPlayerObj::_size()==0);
	for(size_t id= 0; id< pv_SM_USER_MAX->Get_int(); id++)
	{
		jPlayerDBSM* pSM = m_PlayersSM.at(id);
		pSM->m_pid.m_dc_sid = sid;
	}
}

//--------------------------------------------------------------------------
void PlugIn_DBQuery::WritePacket(nUtil::nSharedMem::jPacket_Base&pk)
//--------------------------------------------------------------------------
{
	int count = 0;
	while( m_SendQueue.WritePacket(pk) >= nUtil::nSharedMem::SMQ_FULL )
	{
		GetjILog()->Error(_T("WritePacket fail...\n"));
		Sleep(100);
		count++;
		if(count == 10) 
			break;
	}
}

