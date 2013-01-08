/* file : jRoC_MaestiaLogPage.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-06-13 16:02:59
comp.: rocworks.co.kr
title : 
desc : 

*/

#ifndef __jRoC_MaestiaLogPage_header__
#define __jRoC_MaestiaLogPage_header__
#pragma once


namespace nSMLog
{
	typedef uint16 thread_index_t;
	typedef uint16 func_index_t;

	extern	__declspec( thread ) thread_index_t	g_tls_ThreadID;

	struct jCallStackTracer
	{
#define rocFUNCNAMESIZE 5000
#define rocTHREAD_COUNT  100
#define rocSTACK_DEPTH 50
		//--------------------------------------------------------------------------
		// 콜스택 트레이서
		//--------------------------------------------------------------------------
	//private:
		thread_index_t	m_threadNameMapFreeIndex;
		DWORD			m_threadMap[rocTHREAD_COUNT];

		uint16			m_funcNameMapFreeIndex;
		aname64_t		m_funcNameMap			[rocFUNCNAMESIZE];

		func_index_t	m_funcStack				[rocTHREAD_COUNT][rocSTACK_DEPTH];
		uint16			m_funcStack_FreeIndex	[rocTHREAD_COUNT];
	public:
		jCallStackTracer() :m_funcNameMapFreeIndex(0)
		{
			// SHARED MEMORY 초기화시 0으로 리셋된다.
		}
		void Init()
		{
			ja_strcpy(m_funcNameMap[0] , "Unkown");
			m_funcNameMapFreeIndex=1;
		}
		thread_index_t	RegistThreadID(DWORD threadID);
		func_index_t	RegistFuncName(acstr szFunc);
		void push_back(thread_index_t t , func_index_t f);
		void pop_back(thread_index_t t , func_index_t f);
		void DebugPrint(tcstr);

		struct ONCE
		{
			func_index_t f;
			ONCE(jCallStackTracer* pST,acstr func)
			{
				if(pST) f = pST->RegistFuncName(func);
			}
		};

		struct AUTO
		{
			thread_index_t t;
			ONCE& o;
			jCallStackTracer* pST;
			AUTO(jCallStackTracer* pST_,ONCE& o_,thread_index_t t_) : o(o_),pST(pST_),t(t_)
			{
				if(pST)pST->push_back(t,o.f);
			}
			~AUTO()
			{
				if(pST)pST->pop_back(t,o.f);
			}
		};


		template <class _Predicate>
		void for_each(_Predicate &__pred )  
		{
			for(thread_index_t iT = 0; iT < this->m_threadNameMapFreeIndex ; ++iT)
			{
				if(this->m_threadMap[iT]==0)
					continue;

				__pred(this,iT,this->m_threadMap[iT],0,0,0);

				uint16 callstackDepth = this->m_funcStack_FreeIndex[iT];
				if(callstackDepth < 0  || callstackDepth >= rocSTACK_DEPTH)
					continue;

				func_index_t* pFuncStack = this->m_funcStack[iT];
				if(!pFuncStack) 
					continue;

				for(int iF = 0 ; iF < callstackDepth ; ++iF)
				{
					acstr szFunc="unkown";
					uint16 iFuncIndex = pFuncStack[iF];
					if(iFuncIndex >= 0  && iFuncIndex < this->m_funcNameMapFreeIndex) 
					{
						acstr sz = this->m_funcNameMap[iFuncIndex];
						if(sz) szFunc = sz;
					}
					__pred(this,iT,this->m_threadMap[iT],pFuncStack,iF,szFunc);
				}
			}

		}

	};
	extern jCallStackTracer* g_pjCallStackTracer;

#ifdef DF_CLIENT_TEAM

#	ifdef ENABLE_CLIENT_SM_LOG
	#define rocSTACK_TRACER() static nSMLog::jCallStackTracer::ONCE s_ONCE_jCallStackTracer(nSMLog::g_pjCallStackTracer, __FUNCTION__);\
							if(!nSMLog::g_tls_ThreadID) nSMLog::g_tls_ThreadID = nSMLog::g_pjCallStackTracer->RegistThreadID(GetCurrentThreadId() );\
							nSMLog::jCallStackTracer::AUTO s_AUTO_jCallStackTracer(nSMLog::g_pjCallStackTracer,s_ONCE_jCallStackTracer,nSMLog::g_tls_ThreadID);
	#define rocSTACK_TRACER__try() \
		nSMLog::thread_index_t t = nSMLog::g_pjCallStackTracer->RegistThreadID(GetCurrentThreadId());\
		nSMLog::func_index_t f= nSMLog::g_pjCallStackTracer->RegistFuncName(__FUNCTION__);\
		nSMLog::g_pjCallStackTracer->push_back(t,f);
#	else //#	ifdef ENABLE_CLIENT_SM_LOG

	#define rocSTACK_TRACER() 
	#define rocSTACK_TRACER__try()

#	endif //#	ifdef ENABLE_CLIENT_SM_LOG

#else //#ifdef DF_CLIENT_TEAM
#define rocSTACK_TRACER() 
#define rocSTACK_TRACER__try()
#endif //#ifdef DF_CLIENT_TEAM


//#define BUFFER_SIZE_jMaestiaLogPage 1024*512
	#define BUFFER_SIZE_jMaestiaLogPage 1024*8
	struct jMaestiaLogPage
	{
		DWORD maestia_pid;
		DWORD watchdog_pid;
		int	  m_iCurrLogBuffIndex;
		int	  m_iCurrBuffLen;
		WCHAR m_szLogBuff[2][BUFFER_SIZE_jMaestiaLogPage];
		tname256_t m_strBuildString; 
		tname256_t m_szFTP_DUMP_IP_ADDRESS;
		tname256_t m_szFTPID; 
		tname256_t m_szFTPPWD; 
		int		m_iFTP_DUMP_PORT;
		bool	m_isFlushed;
		jCallStackTracer m_jCallStackTracer;

		jMaestiaLogPage() : m_iCurrLogBuffIndex(0) ,m_iCurrBuffLen(0),m_isFlushed(0)
		{
			// SHARED MEMORY 초기화시 0으로 리셋된다.
		}
	};

}//namespace nSMLog


#endif // __jRoC_MaestiaLogPage_header__
