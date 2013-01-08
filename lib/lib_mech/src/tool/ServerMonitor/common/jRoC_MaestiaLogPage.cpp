/* file : jRoC_MaestiaLogPage.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-06-13 23:56:21
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jRoC_MaestiaLogPage.h"
#include "CBSyncObject.h"

namespace nSMLog
{
	__declspec( thread ) thread_index_t	g_tls_ThreadID=0;

	//s_jMaestiaLogPage->m_jCallStackTracer.for_each(print_stackTracer());

	jCallStackTracer* g_pjCallStackTracer=0;

	void jCallStackTracer::DebugPrint(tcstr szTag)
	{
		return;
		struct print_stackTracer
		{
			print_stackTracer(){}
			void operator()(jCallStackTracer* pST,thread_index_t iT, DWORD threadID,func_index_t* pFuncStack,func_index_t iF,acstr szFunc)
			{
				fname_t szBuf;
				if(!pFuncStack)
				{
					jt_sprintf(szBuf,_T("thread(%d): %d\n"),iT,threadID);
					OutputDebugString(szBuf);
					return;
				}
				jt_sprintf(szBuf,_T("thread(%d:%d) : func(%5d): %s\n"),iT,threadID,iF, jT(szFunc));
				OutputDebugString(szBuf);
			}
		};

		fname_t szBuf;
		jt_sprintf(szBuf, _T("\n\n%s : stack tracer thread(%d) func(%d)\n"),szTag,m_threadNameMapFreeIndex, m_funcNameMapFreeIndex);
		OutputDebugString(szBuf);
		this->for_each(print_stackTracer());
	}


	thread_index_t jCallStackTracer::RegistThreadID(DWORD threadID)
	{
		static CBCriticalSection s_pjCallStackTracer_CS;
		AVAAUTOLOCK(s_pjCallStackTracer_CS);

		for(thread_index_t i=0; i< rocTHREAD_COUNT; ++i)
		{
			DWORD &currID = m_threadMap[i];
			if(currID == 0 )
			{
				++m_threadNameMapFreeIndex;
				currID=threadID;
				
// 				fname_t szBuf;
// 				jt_sprintf(szBuf, jFUNC1 _T("new threadID = %u ,index =%d, m_threadNameMapFreeIndex=%d\n"),threadID, i,m_threadNameMapFreeIndex );
// 				OutputDebugString(szBuf);

				return i;
			}
			if(currID == threadID)
			{
// 				fname_t szBuf;
// 				jt_sprintf(szBuf, jFUNC1 _T("기존 threadID = %u ,index =%d, m_threadNameMapFreeIndex=%d\n"),threadID, i,m_threadNameMapFreeIndex );
// 				OutputDebugString(szBuf);
				return i;
			}
		}
// 		fname_t szBuf;
// 		jt_sprintf(szBuf, jFUNC1 _T("에러 threadID = %u ,index =%d, m_threadNameMapFreeIndex=%d\n"),threadID, 0,m_threadNameMapFreeIndex );
// 		OutputDebugString(szBuf);
		return 0;
	}

	func_index_t jCallStackTracer::RegistFuncName(acstr szFunc)
	{
		static CBCriticalSection s_pjCallStackTracer_CS;
		AVAAUTOLOCK(s_pjCallStackTracer_CS);
		if(m_funcNameMapFreeIndex >= rocFUNCNAMESIZE) 
			return 0;

		for(uint16 i =0; i< m_funcNameMapFreeIndex ; ++i)
		{
			if(ja_strcmp(m_funcNameMap[i] , szFunc)==0)
			{
// 				fname_t szBuf;
// 				jt_sprintf(szBuf, jFUNC1 _T("등록  func name : %s : %d\n"),jT(szFunc) ,i );
// 				OutputDebugString(szBuf);
				return i;
			}
		}

		ja_strncpy(m_funcNameMap[m_funcNameMapFreeIndex], szFunc,62);
		m_funcNameMap[m_funcNameMapFreeIndex][62]=0;
		return m_funcNameMapFreeIndex++;
	}

	void jCallStackTracer::push_back(thread_index_t t , func_index_t f)
	{
// 		fname_t szBuf;
// 		jt_sprintf(szBuf,jFUNC1 _T("thread(%d:%d), func(%d:%s)\n"),t,this->m_threadMap[t],f ,jT(m_funcNameMap[f]));
// 		OutputDebugString(szBuf);

		uint16& iF = m_funcStack_FreeIndex[t];
		if(iF>=rocSTACK_DEPTH)
		{
// #if 1//ndef SHIPPING
// 			//jMB("jCallStackTracer::push_back","asdf1");
// 			DebugPrint(jFUNC _T("if(iF>=rocSTACK_DEPTH)"));
// #endif
			return;
		}
// 		if(iF-1 >=0)
// 		{
// 			if( m_funcStack[t][iF-1]  == f)
// 			{
// #if 1//ndef SHIPPING
// 				printf("asfd");
// #endif
// 			}
// 
// 		}
		m_funcStack[t][iF++] = f;
		//DebugPrint(jFUNC);

	}
	void jCallStackTracer::pop_back(thread_index_t t,func_index_t f)
	{
// 		fname_t szBuf;
// 		jt_sprintf(szBuf,jFUNC1 _T("thread(%d:%d), func(%d:%s)\n"),t,m_threadMap[t],f ,jT(m_funcNameMap[f]));
// 		OutputDebugString(szBuf);

		uint16& iF = m_funcStack_FreeIndex[t];
		if((iF-1)<0) 
		{
// #if 1//ndef SHIPPING
// 			//jMB("jCallStackTracer::pop_back","asdf");
// 			DebugPrint(jFUNC _T("if((iF-1)<0)"));
// #endif
			return;
		}
// 		if(m_funcStack[t][iF]!=0)
// 		{
// 			printf("asdf");
// 		}
		m_funcStack[t][iF-1] = 0;
		--iF;

// 		DebugPrint(jFUNC);

	}


}//namespace nSMLog
