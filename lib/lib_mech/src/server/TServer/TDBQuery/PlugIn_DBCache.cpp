/* file : PlugIn_DBCache.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TDBQuery.h"
#include "PlugIn_DBCache.h"
#include <process.h>


PlugIn_DBCache g_PS;

_jDBEventNode* g_func[PT_DBQueryServer_END];
void _jRegistNamedPointer(int num, _jDBEventNode* v){g_func[num] = v;}
nMech::nDB::jIDB*	g_pDB=0;


//--------------------------------------------------------------------------
static unsigned __stdcall _run_dq( void* pThreadParam)
//--------------------------------------------------------------------------
{
	PlugIn_DBCache* pDC= (PlugIn_DBCache*)pThreadParam;

	jNamedEventTable* pPHT = (jNamedEventTable*)nMech::jBase::FindNamedPointer(_T("nNET"),_T("DBQueryServer") );

	nswb1024_t buf;
	jNET_SEND2(g_PS,DQ2DC_CONNECT
		,pv_DOMAIN_NAME->Get_cstr()
		,pv_SM_QUERY2CACHE_NAME->Get_cstr()
		,pv_SM_CACHE2QUERY_NAME->Get_cstr()
		,pv_SM_USER_INFO_NAME->Get_cstr()
		,pv_GAMEDB_NAME->Get_cstr()
		,(uint32)GetCurrentProcessId()
		);

	nUtil::nSharedMem::jPacket_Base pk;
	BYTE readBuf[nUtil::nSharedMem::MAX_PKTSIZE];
	pk.buf = readBuf;

	g_PS.m_isQuit=1;
	while(g_PS.m_isQuit==1 ) 
	{
		if( !g_PS.m_RecvQueue.ReadPacket( pk ) ){Sleep(13);continue;}
		if(pk.num>=PT_DBQueryServer_END || pk.num <=PT_VERSION	)
		{
			jWARN("Unkown packet recvied : %d",pk.num );
			continue;
		}
		if(g_func[pk.num])
		{
			g_func[pk.num]->Call(pDC, readBuf, pk.len,0);
		}
		else
		{
			jNamedEventNode* pPHN = pPHT->GetByNum(pk.num);
			jWARN("recv : %s callback is not found",pPHN->m_szName);
		}
		memset( &readBuf, 0, sizeof(readBuf) );
	}
	g_PS.m_isQuit=3;

	_endthread();
	return 0;
}

//--------------------------------------------------------------------------
void PlugIn_DBCache::StartServer()
//--------------------------------------------------------------------------
{
	m_ProcessID=0;
	m_isQuit=0;
	try
	{
		bool isCreate = m_SendQueue.InitailizeMMF( sizeof(nUtil::nSharedMem::jSmqPacket_UNIT)
			, pv_SM_QUEUE_MAX_COUNT->Get_int(), pv_SM_QUERY2CACHE_NAME->Get_cstr());

		m_RecvQueue.InitailizeMMF( sizeof(nUtil::nSharedMem::jSmqPacket_UNIT)
			, pv_SM_QUEUE_MAX_COUNT->Get_int(), pv_SM_CACHE2QUERY_NAME->Get_cstr());

		m_PlayersSM.Init(pv_SM_USER_INFO_NAME->Get_cstr(), pv_SM_USER_MAX->Get_int());

		bool isOk = g_pDB->OpenDirect(pv_GAMEDB_STRING->Get_cstr());

		if(!isOk)
		{
			jERROR("g_pDB->OpenDirect(%s,%s:%s) error",pv_GAMEDB_NAME->Get_cstr(), pv_GAMEDB_ID->Get_cstr(), pv_GAMEDB_PWD->Get_cstr());
			return;
		}
		else
		{
			jLOG1(_T("g_pDB->Open(%s,%s) OK"),pv_GAMEDB_NAME->Get_cstr(), pv_GAMEDB_ID->Get_cstr());
		}

		m_hThread_run_dq = (HANDLE)_beginthreadex(NULL, 0, _run_dq, this, 0, 0);
	}
	catch (cstr szError)
	{
		jERROR("%s", szError);
	}

}

//--------------------------------------------------------------------------
void PlugIn_DBCache::EndServer()
//--------------------------------------------------------------------------
{
	if(m_isQuit==0) 
		return;
	m_isQuit=2;
	while(m_isQuit!=3)
	{
		printf(".");
	}
	CloseHandle(m_hThread_run_dq);

}

