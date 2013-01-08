/* file : jRoC_SharedMemory.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-05-08 18:50:02
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jRoC_SharedMemory.h"
#include <process.h>

namespace nSM
{

	jSM_logger_t* g_pLogger=0;
	make_dump_file_t* g_make_dump_file=0;

	const int iMAX_EXCEPTIONCOUNT=100;
	int filter_nSM(unsigned int code, struct _EXCEPTION_POINTERS *ep) 
	{
		if(g_make_dump_file)
		{
			g_make_dump_file("nSM_thread");
		}
		return EXCEPTION_EXECUTE_HANDLER;
	}

	//jLIST_TYPEDEF_map(nUtil::nSharedMem::jPacketNum_t,nSM::_jDBEventNode* ,g_func);
	std::map<nUtil::nSharedMem::jPacketNum_t,nSM::_jDBEventNode*> *g_func=0; 

	using namespace nMech::nUtil::nSharedMem;

	void _jRegistNamedPointer(int num, _jDBEventNode* v)
	{
		if(!g_func)
		{
			g_func = new std::map<nUtil::nSharedMem::jPacketNum_t,nSM::_jDBEventNode*>;
		}
		(*g_func)[num] = v;
	}

	static void call_func(nUtil::nSharedMem::jPacket_Base &pk,BYTE* readBuf,void*v)
	{
		if(pk.num>=Enum_jSM_net_agent_MAX)
		{
			jWARN_T("Unkown packet recvied : %d",pk.num );
			return;
		}
		else
		{
			if((*g_func).count(pk.num))
				(*g_func)[pk.num]->Call(readBuf, pk.len,v);
			else
				jWARN_T("recv : %d callback is not found",pk.num);
		}
	}
#ifdef DF_NET_AGENT
	//--------------------------------------------------------------------------
	static unsigned __stdcall _run_net_agent( void* pThreadParam)
		//--------------------------------------------------------------------------
	{
		jSM_net_agent* pDC= (jSM_net_agent*)pThreadParam;
		if(!pDC) return 0;

		uint32 pid = (uint32)GetCurrentProcessId();
		for(size_t i=0; i< pDC->m_serverExeList.size(); ++i)
		{
			pDC->WritePacket(pDC->m_serverExeList[i].c_str() , eA2S_ONLINE_RQ ,L"%d" , pid);
		}

		nUtil::nSharedMem::jPacket_Base pk;
		BYTE readBuf[nUtil::nSharedMem::MAX_PKTSIZE];
		pk.buf = readBuf;
		static int s_ExceptionCount=0;

		pDC->m_isQuit=1;
		while(pDC->m_isQuit==1 ) 
		{
#	ifdef _DEBUG1234 //EXCEPTION FILTER
			__try
			{
#	endif
				if(!g_jSMA) break;
				if( pDC->m_RecvQueue.ReadPacket( pk ) )
					call_func(pk,readBuf,pDC);

				memset( &readBuf, 0, sizeof(readBuf) );
				Sleep(13);
#	ifdef _DEBUG1234 //EXCEPTION FILTER
			}
			__except(filter_nSM(GetExceptionCode(), GetExceptionInformation()))
			{
				++s_ExceptionCount;
				if(g_pLogger)
				{
					g_pLogger(__FUNCTIONW__ L"[ERROR] Exception Error \n");
				}
				if(s_ExceptionCount>iMAX_EXCEPTIONCOUNT)
				{
					break;
				}
			}
#	endif			

		}
		if(g_jSMA)g_jSMA->m_isQuit=3;
		_endthread();
		return 0;
	}
#endif //#ifdef DF_NET_AGENT
	//--------------------------------------------------------------------------
	void jSM_net_agent::Start(const vector<wstring>& serverExeList)
		//--------------------------------------------------------------------------
	{
#ifdef DF_NET_AGENT
		m_serverExeList = serverExeList;
		m_isQuit=0;
		try
		{
			for( int i=0; i< serverExeList.size(); ++i)
			{
				fname_t szBuf;
				jt_sprintf(szBuf, _T("A2_CONNECT_%s"),serverExeList[i].c_str());
				m_ServerInfo[jW(serverExeList[i])].m_SendQueue.InitailizeMMF( sizeof(nUtil::nSharedMem::jSmqPacket_UNIT), SM_QUEUE_MAX_COUNT, szBuf);
			}

			m_RecvQueue.InitailizeMMF( sizeof(nUtil::nSharedMem::jSmqPacket_UNIT)
				, SM_QUEUE_MAX_COUNT, jS(TO_AGENT_CONNECT));

			m_ServerInfoSM.Init(jS(SM_SERVER_INFO_NAME), 1);
			m_hThread_run_dq = (HANDLE)_beginthreadex(NULL, 0, _run_net_agent, this, 0, 0);
		}
		catch (cstr szError)
		{
			jERROR_T("%s", szError);
		}
#endif

	}

	//--------------------------------------------------------------------------
	void jSM_net_agent::End()
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

	BOOL jSM_net_agent::WritePacket(const wstring &sServerType , nUtil::nSharedMem::jPacketNum_t num,wcstr szFmt, ...)
	{
		va_list vl;
		_crt_va_start(vl, szFmt);
		WCHAR szBuf[2048];
		jw_vsprintf(szBuf, szFmt, vl);
		va_end(vl);

		nUtil::nSharedMem::jPacket_Base pk;
		pk.num=num;
		pk.buf = (BYTE*)szBuf;
		pk.len = (nUtil::nSharedMem::jPacketLen_t)(jw_strlen(szBuf) +1)*2;
		jRETURN_ret(FALSE, m_ServerInfo.count(sServerType));
		jServerInfo& si = m_ServerInfo[sServerType];
		si.m_SendQueue.WritePacket(pk);
		return TRUE;
	}

	//--------------------------------------------------------------------------
	static unsigned __stdcall _run_game_server( void* pThreadParam)
		//--------------------------------------------------------------------------
	{
		jSM_server* pDC= (jSM_server*)pThreadParam;
		if(!pDC) return 0;
		nUtil::nSharedMem::jPacket_Base pk;
		BYTE readBuf[nUtil::nSharedMem::MAX_PKTSIZE];
		pk.buf = readBuf;
		pDC->m_isQuit=1;
		static int s_ExceptionCount=0;
		while(pDC->m_isQuit==1 ) 
		{
#ifdef _DEBUG1234 //EXCEPTION FILTER
			__try
			{
#endif
				if( pDC && pDC->m_RecvQueue.ReadPacket( pk ) )
					call_func(pk,readBuf,pDC);
				memset( &readBuf, 0, sizeof(readBuf) );
				Sleep(13);

#ifdef _DEBUG1234 //EXCEPTION FILTER
			}
			__except(filter_nSM(GetExceptionCode(), GetExceptionInformation()))
			{
				++s_ExceptionCount;
				if(g_pLogger)
				{
					g_pLogger(__FUNCTIONW__ L"[ERROR] Exception Error \n");
				}
				if(s_ExceptionCount>iMAX_EXCEPTIONCOUNT)
				{
					break;
				}
			}
#endif			
		}//while(pDC->m_isQuit==1 ) 
		pDC->m_isQuit=3;
		_endthread();
		return 0;
	}

	//--------------------------------------------------------------------------
	void jSM_server::Start(tcstr eServerType)
		//--------------------------------------------------------------------------
	{
		m_eMyServerType = eServerType;
		m_isQuit=0;
		try
		{
			bool isCreateL = m_Agent.m_SendQueue.InitailizeMMF( sizeof(nUtil::nSharedMem::jSmqPacket_UNIT)
				, SM_QUEUE_MAX_COUNT, jS(TO_AGENT_CONNECT));

			fname_t szName;
			jt_sprintf(szName , _T("A2_CONNECT_%s"), eServerType );
			m_RecvQueue.InitailizeMMF( sizeof(nUtil::nSharedMem::jSmqPacket_UNIT)
				, SM_QUEUE_MAX_COUNT, szName);

			m_ServerInfoSM.Init(jS(SM_SERVER_INFO_NAME), 1);
			m_hThread_run_dq = (HANDLE)_beginthreadex(NULL, 0, _run_game_server, this, 0, 0);
		}
		catch (cstr szError)
		{
			jERROR_T("%s", szError);
		}

	}

	//--------------------------------------------------------------------------
	void jSM_server::End()
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

	BOOL jSM_server::WritePacket(nUtil::nSharedMem::jPacketNum_t num,wcstr szFmt, ...)
	{
		va_list vl;
		_crt_va_start(vl, szFmt);
		WCHAR szBuf[2048];
		jw_vsprintf(szBuf, szFmt, vl);
		va_end(vl);

		nUtil::nSharedMem::jPacket_Base pk;
		pk.num=num;
		pk.buf = (BYTE*)szBuf;
		pk.len = (nUtil::nSharedMem::jPacketLen_t)(jw_strlen(szBuf) +1)*2;
		m_Agent.m_SendQueue.WritePacket(pk);
		return TRUE;
	}


#ifdef DF_NET_AGENT
	jSM_net_agent *g_jSMA;

#else //#ifdef DF_NET_AGENT

	inline wcstr find_log_type(wcstr pLogBuffer,EErrorLogDomain logDomain)
	{

		#define _find_log_tag5432(ERROR_PATTERN,ERROR_LABEL)\
			if(jw_strstr(pLogBuffer,ERROR_PATTERN))\
				return _jW(ERROR_LABEL);

		if(logDomain==eELD_GAME)
		{
			for_each_ERROR_LOG_GAME(_find_log_tag5432);
		}
		else 
		{
			for_each_ERROR_LOG_PBRMS(_find_log_tag5432);
			//if(jw_strstr(pLogBuffer,L"[ERROR]"))return _jW(ErrorLog);

		}
		return 0;
	}

	jSM_server* get_current_jSM_server(EErrorLogDomain logDomain)
	{
		using namespace nSM;
		static jSM_server* pjSM_server=0;
		if(!pjSM_server)
		{
			g_jSM_it it;
			if(logDomain==eELD_GAME)
			{
				it = g_jSM.find(jS(eLOGIN));
				if(it==g_jSM.end())
				{
					it = g_jSM.find(jS(eZONE));
				}
			}
			else //eELD_PBRMS
			{
				it = g_jSM.find(jS(ePBRMS));
			}

			if(it!=g_jSM.end())
			{
				pjSM_server = it->second;
			}
		}
		return pjSM_server;
	}
	void SendErrorLogToAgent(wcstr pLogBuffer,EErrorLogDomain logDomain)
	{
		jSM_server* pjSM_server=get_current_jSM_server(logDomain);
		if(!pjSM_server)
		{
			g_jSM_it it;
			if(logDomain==eELD_GAME)
			{
				it = g_jSM.find(jS(eLOGIN));
				if(it==g_jSM.end())
				{
					it = g_jSM.find(jS(eZONE));
				}
			}
			else //eELD_PBRMS
			{
				it = g_jSM.find(jS(ePBRMS));
			}

			if(it!=g_jSM.end())
			{
				pjSM_server = it->second;
			}
		}
		if(pjSM_server)
		{
			wcstr szLogType = find_log_type(pLogBuffer,logDomain);
			if(szLogType)
				pjSM_server->WritePacket(nSM::eS2A_SEND_ERROR_LOG, L"%s#%s#%s",jW(pjSM_server->m_eMyServerType),szLogType,pLogBuffer);
		}
	}
	void SendDumpCount(EErrorLogDomain logDomain)
	{
		nSM::jSM_server* pSM = nSM::get_current_jSM_server(logDomain);
		if(pSM)
		{
			wstring &sDump = pSM->GetMyServerInfo().m_Data[_jW(Dump)];
			int iDump = jw_atoi(sDump.c_str());
			++iDump;
			wfname_t szBuf;
			jw_sprintf(szBuf,L"%d",iDump);
			sDump = szBuf;
			pSM->WritePacket(nSM::eS2A_PROCESS_INFO_UPDATE, L"%s#Dump#%d",jW(pSM->m_eMyServerType), iDump);
		}
	}

	jLIST_TYPEDEF_map(tstring,jSM_server*,g_jSM);

	jLIST_TYPEDEF_map(tstring , wstring , g_szONLINE_String);

	jDBQ_EVENT_RECEIVER(eA2S_ONLINE_RQ) // Server's 모듈.
	{
		jPARSE_SM();

		pSM->m_Agent.m_Data[L"pid"] = arg[0];
		pSM->WritePacket(nSM::eS2A_ONLINE_RQ, L"%s#%s" ,jW(pSM->m_eMyServerType) ,nSM::g_szONLINE_String[pSM->m_eMyServerType].c_str());
		pSM->WritePacket(nSM::eS2A_SERVER_MENU_CMD_RS,L"%s#%s",jW(pSM->m_eMyServerType) ,jW(pSM->GetMyServerInfo().m_eServerState));
	}

	jDBQ_EVENT_RECEIVER(eAGENT_OFFLINE)// Server's 모듈.
	{
		jPARSE_SM();
		pSM->m_Agent.m_eServerState = jS(eSS_Offline);
	}

	jDBQ_EVENT_RECEIVER(eA2S_PROCESS_INFO_UPDATE)
	{
		jPARSE_SM(); //jSM_server* pSM ,wcstr sz , vector<wstring> arg
		enum{eName,eValue,eMAX};
		jRETURN(arg.size()==eMAX);
		pSM->GetMyServerInfo().m_Data[arg[eName]] = arg[eValue];
		//jMB(jT(sz),jS(eA2S_PROCESS_INFO_UPDATE));
	}
	jDBQ_EVENT_RECEIVER(eA2S_RUN_EXE)
	{
		jPARSE_SM(); //jSM_server* pSM ,wcstr sz , vector<wstring> arg
		enum {eOPTION,eEXE,eMAX};
		jRETURN(arg.size()==eMAX);
		WinExec(jA(arg[eEXE].c_str()) , SW_NORMAL);
	}
	


#endif //#ifdef DF_NET_AGENT

}//namespace nSM

