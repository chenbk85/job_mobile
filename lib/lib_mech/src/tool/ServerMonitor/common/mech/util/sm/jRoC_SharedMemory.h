/* file : jRoC_SharedMemory.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-05-08 18:49:59
comp.: rocworks.co.kr
title : 
desc : 

*/

#ifndef __jRoC_SharedMemory_header__
#define __jRoC_SharedMemory_header__
#pragma once

#include "mech/header/MemoryMap.h"
#include "SharedMemQueue.h"

#include "mech/util/sm/jRoC_SharedMemory_header.h"

namespace nSM
{
	class jSM_net_agent;
#define _ARG_jDBEventNode		BYTE* pReadBuff, nUtil::nSharedMem::jPacketNum_t dwLen,void* pS

	struct _jDBEventNode{	virtual void Call(_ARG_jDBEventNode)=0;};
	extern void _jRegistNamedPointer(int, _jDBEventNode*);

#ifndef jDBQ_EVENT_RECEIVER
#define jDBQ_EVENT_RECEIVER(PROTOCAL) \
	struct _jJOIN_2(jDBQEvent_,PROTOCAL) : public nSM::_jDBEventNode \
	{	_jJOIN_2(jDBQEvent_,PROTOCAL)(){ _jRegistNamedPointer(nSM::PROTOCAL,this);}\
	virtual void Call(_ARG_jDBEventNode);};	static _jJOIN_2(jDBQEvent_,PROTOCAL) _jJOIN_2(g_jDBEvent_,PROTOCAL);\
	void _jJOIN_2(jDBQEvent_,PROTOCAL)::Call(_ARG_jDBEventNode)
#endif


	struct jServerInfo
	{
		tstring m_eServerState; // z:\bin\client\xml\App_ServerMonitor.xml의 <EServerState_Color>의 노드
		nUtil::nSharedMem::CSharedMemQueue m_SendQueue;

#ifdef DF_NET_AGENT
		nEVENT::jIMessage* m_pM_JOB_check_process_killed;
#endif

		jLIST_TYPEDEF_map(wstring,wstring,m_Data);
		jServerInfo()
		{
			m_eServerState = jS(eSS_Offline);
#ifdef DF_NET_AGENT
			m_pM_JOB_check_process_killed=0;
#endif
		}
		void ToString_Info(wstring & out)
		{
			out=L"";
			m_Data_it it = m_Data.begin(), ie = m_Data.end();
			for(; it!=ie;++it)
			{
				out += it->first;
				out += L"=";
				out += it->second;
				out += L"~";
			}
		}
	};

	struct jMaestiaServerInfo
	{
		int m_iThisSize;
		DWORD m_ProcessID;
		aname256_t m_ServerType;
		aname256_t m_ServerName;
	};

	typedef void jSM_logger_t(wcstr sz);
	extern jSM_logger_t* g_pLogger;
	typedef void make_dump_file_t(acstr szTag);
	extern make_dump_file_t* g_make_dump_file;

	//--------------------------------------------------------------------------
	class jSM_server
	//--------------------------------------------------------------------------
	{
	public:
		jSM_server()
		{
			m_isQuit=0;
			m_hThread_run_dq=0;
		}
		tstring m_eMyServerType;
		jServerInfo m_Agent;
		nUtil::nSharedMem::CSharedMemQueue m_RecvQueue;
		nUtil::jMemoryMap<jMaestiaServerInfo> m_ServerInfoSM;
		int m_isQuit;
		HANDLE m_hThread_run_dq;

		jServerInfo & GetMyServerInfo()
		{
			return m_Agent;
		}
		BOOL WritePacket(nUtil::nSharedMem::jPacketNum_t num,wcstr szFmt, ...);

		void Start(tcstr eServerType);//eLOGIN , eZONE ,ePBRMS eCHAT중의 한개이다.
		void End();

	};

	//--------------------------------------------------------------------------
	class jSM_net_agent
	//--------------------------------------------------------------------------
	{
	public:
		int m_isQuit;
		HANDLE m_hThread_run_dq;

		vector<wstring> m_serverExeList;

		jLIST_TYPEDEF_map(wstring,jServerInfo,m_ServerInfo);

		jSM_net_agent()
		{
			m_isQuit=0;
			m_hThread_run_dq=0;
		}

		nUtil::jMemoryMap<jMaestiaServerInfo> m_ServerInfoSM;
		nUtil::nSharedMem::CSharedMemQueue m_RecvQueue;
	
		BOOL WritePacket(const wstring &sServerType , nUtil::nSharedMem::jPacketNum_t num,wcstr szFmt, ...);
		void Start(const vector<wstring>& serverExeList);
		void End();

	};


#ifdef DF_NET_AGENT

	extern jSM_net_agent *g_jSMA;

#ifdef _DEBUG
#	define jLOG_PACKET_DEBUG jLOG
#else
#	define jLOG_PACKET_DEBUG 
#endif


#define jPARSE_SMA() 	jRETURN(g_jSMA);wcstr sz = (wcstr)pReadBuff;std::vector<wstring> arg;nString::jSplitW(sz,L"#",arg);jLOG_PACKET_DEBUG(jFUNC1 _T("%s"),jT(sz));nswb1024_t buf;
#define jPARSE_SMA2() 	jPARSE_SMA();jBE(); /*jRETURN(pBE->m_pS_MonitorServer);*/

#else //#ifdef DF_NET_AGENT

	jLIST_TYPEDEF_map_header(tstring,jSM_server*,g_jSM);

	jLIST_TYPEDEF_map_header(tstring , wstring , g_szONLINE_String);

	//게임서버 -> 에이젼트 보내기
#define jSendToAgent(eServerType,...) if(nSM::g_jSM.count(jS(eServerType)) )nSM::g_jSM[jS(eServerType)]->WritePacket(__VA_ARGS__);

#define SEND_RoCServerState(eSERVER_TYPE,eSTATE)\
	nSM::g_jSM[jS(eSERVER_TYPE)]->GetMyServerInfo().m_eServerState = jS(eSS_##eSTATE);\
	jSendToAgent(eSERVER_TYPE,nSM::eS2A_SERVER_MENU_CMD_RS , _jW(eSERVER_TYPE) L"#" _jW(eSS_##eSTATE) );\


#define jPARSE_SM() 	wcstr sz = (wcstr)pReadBuff;\
	jSM_server* pSM = (jSM_server*)pS;\
	std::vector<wstring> arg;nString::jSplitW(sz,L"#",arg);jLOG_T(jFUNC1 _T("%s\n"),jT(sz));

	enum EErrorLogDomain
	{
		eELD_GAME,
		eELD_PBRMS,
	};

	void SendDumpCount(EErrorLogDomain logDomain);
	void SendErrorLogToAgent(wcstr pLogBuffer,EErrorLogDomain logDomain);
#endif //#ifdef DF_NET_AGENT



}//nSM



#endif // __jRoC_SharedMemory_header__
