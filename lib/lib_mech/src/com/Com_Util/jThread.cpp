/* file : jIThread.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2009-12-18 11:22:54
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "interface/jIThread.h"
#include <process.h>
#include "base/jWindow_Util.h"
#include <Windows.h>
#include <interface/xml/jIVar.h>
#include "interface/jIDebugCallStack.h"

using namespace nMech;
#define jThread_vector_t_MAX 100

#define SAFE_CLOSE_HANDLE(d) if(d){ CloseHandle(d);d=0;}

#define jThread_LOCK() //jAUTO_LOCK_CS(m_CS)
namespace nMech
{
	jIVar* pv_MAX_EXCPTIONCOUNTER = jCV(DEBUG,MAX_EXCPTIONCOUNTER,50,0,"if exception count is over then exit process");
	namespace nThread
	{
		int filter_jThread(unsigned int code, struct _EXCEPTION_POINTERS *ep) 
		{
			jCREATE_INTERFACE_AUTO(pDebugger, nMech::nUtil::nDebug::jIDebugCallStack);
			jRETURN_ret(code ,pDebugger);

			pDebugger->handleException( ep );
			return EXCEPTION_EXECUTE_HANDLER;

// 			aname1024_t szFile;
// 			pDebugger->SaveDumpFile(szFile, ep);
// 			return EXCEPTION_EXECUTE_HANDLER;
;
		}

		//--------------------------------------------------------------------------
		class jThread : public jIThread
		//--------------------------------------------------------------------------
		{
			jINTERFACE_HEADER(jIThread);
			int		m_iExceptionCounter;
			HANDLE m_hThread;
			unsigned int m_uiThreadID;
			bool m_isQuit;
			bool m_isUse;
			tname_t m_sThreadGroup;
			tname_t m_sThreadName;

			EThreadState m_eState;
			ERunType m_eRunType;

			/// timer용
			jIVar* m_pvTime_msec;
			HANDLE m_hDestroyEvent;

			// Wake용
			HANDLE m_hWakeUpEvent;


			jThread()
				:m_eState(eTS_PREV_INIT)
				,m_iExceptionCounter(0)
				,m_isUse(false)
				,m_isQuit(false)
				,m_hThread(0)
				,m_uiThreadID(0)
				,m_hDestroyEvent(0)
				,m_hWakeUpEvent(0)
				,m_pvTime_msec(0)
			{}

			void Run(thread_func_t& f,tcstr szThreadGroup,tcstr szThreadName,__jThread_Func_t* pFunc) ;
			void End() ;

			friend class jThreadManager ;
		public:
			thread_func_t m_func;
		};

		//--------------------------------------------------------------------------
		class jThreadManager : public jIThreadManager
		//--------------------------------------------------------------------------
		{
		public:
			jINTERFACE_HEADER(jIInterface);
			jINTERFACE_HEADER(jIThreadManager);

			nUtil::jCriticalSection m_CS;
			//jLIST_TYPEDEF_list_typedef(jThread,jThread_vector);
			jThread m_mapjThread[jThread_vector_t_MAX];
			jThread* push_back_thread(cstr szGroup)
			{
				jThread*p = m_mapjThread;
				for(int i=0;i<jThread_vector_t_MAX ; ++i)
				{
					if(p[i].m_isUse) continue;
					p[i].m_isUse=true;
					return p+i;
				}
				jERROR_T("not enough thread resource!");
				return 0;
			}
		};


		jThreadManager g_jThreadManager;
		jCTOR_INTERFACE(nMech::nThread::jIThreadManager,jThreadManager)
		{
			return &g_jThreadManager;
		}
		jDTOR_INTERFACE(nMech::nThread::jIThreadManager,jThreadManager)
		{
		}

		void run_kill_thread(jThread* t1)
		{
			t1->m_isQuit=true;
			g_jThreadManager.End(t1->m_sThreadGroup, t1->m_sThreadName );
		}

		unsigned int __stdcall __jThread_Func_UserLoop( void* v)
		{
			jIThread* _t = (jIThread*)v;
			jThread* t = (jThread*)_t;
__retry_userfunc:
#ifndef _DEBUG //EXCEPTION FILTER
			__try
			{
#endif
				t->m_func(t);
#ifndef _DEBUG //EXCEPTION FILTER
			}
			__except(filter_jThread(GetExceptionCode(), GetExceptionInformation()))
			{
				++t->m_iExceptionCounter;
				jERROR(_T("jIThread = [%s:%s] 알수 없는 예외 ( %d)"), t->m_sThreadGroup,t->m_sThreadName,t->m_iExceptionCounter);
				if(t->m_iExceptionCounter<pv_MAX_EXCPTIONCOUNTER->Get_int())
				{
					goto __retry_userfunc;
				}
				t->m_eState = nThread::eTS_ERROR_OCCUR;

			}
#endif			
			jt_printf(jFUNC1 _T("END thread group: %s !"),t->m_sThreadName);
			run_kill_thread(t);
			return 0;
		}

		unsigned int __stdcall __jThread_Func( void* v)
		{
			jIThread* _t = (jIThread*)v;
			jThread* t = (jThread*)_t;
			for(;t->IsRun();)
			{
#ifndef _DEBUG //EXCEPTION FILTER
				__try
				{
#endif
					t->m_func(t);
#ifndef _DEBUG //EXCEPTION FILTER
				}
				__except(filter_jThread(GetExceptionCode(), GetExceptionInformation()))
				{
					++t->m_iExceptionCounter;
					jERROR(_T("jIThread = [%s:%s] 알수 없는 예외 : m_iExceptionCounter=%d"), t->m_sThreadGroup,t->m_sThreadName,t->m_iExceptionCounter);
					if(t->m_iExceptionCounter>pv_MAX_EXCPTIONCOUNTER->Get_int())
					{
						t->m_eState = nThread::eTS_ERROR_OCCUR;
						break;
					}
				}
#endif
			}
			jt_printf(jFUNC1 _T("END thread group: %s !"),t->m_sThreadName);
			run_kill_thread(t);
			return 0;
		}


		unsigned int __stdcall __jThread_Func_Timer( void* v)
		{
			jIThread* _t = (jIThread*)v;
			jThread* t = (jThread*)_t;
				for(;t->IsRun();)
				{
#ifndef _DEBUG //EXCEPTION FILTER
					__try
					{
#endif
						DWORD dwResult = WaitForSingleObject(t->m_hDestroyEvent, t->m_pvTime_msec->Get_int() );

						// 종료 이벤트가 발생했을경우 Thread를 종료합니다.
						if (dwResult == WAIT_OBJECT_0) return 0;
						t->m_func(t);
#ifndef _DEBUG //EXCEPTION FILTER
					}
					__except(filter_jThread(GetExceptionCode(), GetExceptionInformation()))
					{
						++t->m_iExceptionCounter;
						jERROR(_T("jIThread = [%s:%s] 알수 없는 예외 m_iExceptionCounter=%d"), t->m_sThreadGroup,t->m_sThreadName,t->m_iExceptionCounter);
						if(t->m_iExceptionCounter>pv_MAX_EXCPTIONCOUNTER->Get_int())
						{
							t->m_eState = nThread::eTS_ERROR_OCCUR;
							break;
						}
					}
#endif
				}
			jt_printf(jFUNC1 _T("END thread group: %s !"),t->m_sThreadName);
			run_kill_thread(t);
			return 0;
		}



		unsigned int __stdcall __jThread_Func_Wake( void* v)
		{
			jIThread* _t = (jIThread*)v;
			jThread* t = (jThread*)_t;
			//nUtil::nWIN::SetThreadName(-1,t->mm_sName);
			HANDLE	hEvents[2] = {t->m_hDestroyEvent, t->m_hWakeUpEvent};
			DWORD	eventID=0;

			for(;t->IsRun();)
			{
#ifndef _DEBUG //EXCEPTION FILTER
				__try
				{
#endif
					eventID = WaitForMultipleObjects(2, hEvents, FALSE, INFINITE);
					switch(eventID)
					{
					case WAIT_OBJECT_0:
						return 0;
					case WAIT_OBJECT_0 + 1:
						{
							t->m_func(t);
						}
						break;
					}
#ifndef _DEBUG //EXCEPTION FILTER
				}
				__except(filter_jThread(GetExceptionCode(), GetExceptionInformation()))
				{
					++t->m_iExceptionCounter;
					jERROR_T("jIThread = [%s:%s] 알수 없는 예외 m_iExceptionCounter=%d", t->m_sThreadGroup,t->m_sThreadName,t->m_iExceptionCounter);
					if(t->m_iExceptionCounter>pv_MAX_EXCPTIONCOUNTER->Get_int())
					{
						t->m_eState = nThread::eTS_ERROR_OCCUR;
						break;
					}
				}
#endif
			}
			jLOG(jFUNC1 _T("END thread group: %s !"),t->m_sThreadName);
			run_kill_thread(t);
			return 0;
		}

		cstr		jThread::GetThreadName()		{ return m_sThreadName;}
		cstr		jThread::GetThreadGroup()		{ return m_sThreadGroup;}
		HANDLE &	jThread::GetDestroyEvent()		{return m_hDestroyEvent;}
		HANDLE &	jThread::GetWakeEvent()			{return m_hWakeUpEvent;}
		bool		jThread::IsRun()				{return !m_isQuit;}
		void		jThread::DoWake()				{SetEvent(m_hWakeUpEvent);}
		void		jThread::Release()				{g_jThreadManager.End(m_sThreadGroup,m_sThreadName);}

		void jThread::Run(thread_func_t& f,tcstr szThreadGroup,tcstr szThreadName,__jThread_Func_t* pFunc)
		{
			m_eState= eTS_PREV_INIT;

			m_func = f;
			m_isQuit=false;
			m_uiThreadID=0;
			jt_strcpy_s(m_sThreadGroup ,szThreadGroup);
			jt_strcpy_s(m_sThreadName , SAFE_STR(szThreadName));
			m_hThread= (HANDLE)_beginthreadex( NULL , 0 , pFunc, this , CREATE_SUSPENDED  , &m_uiThreadID );
			SetThreadPriorityBoost( m_hThread, TRUE );		 // 스레드 부스트 업을 막음
			fname_t buf;
			static int iii=0;
			if(szThreadName)
				jt_sprintf_s(buf,_T("%s>%s"),szThreadGroup,szThreadName);
			else
				jt_sprintf_s(buf,_T("%s>%d"),szThreadGroup,iii++);

			nUtil::nWIN::SetThreadName(m_uiThreadID, jA(buf) );

			if(m_hThread==NULL)
			{
				jt_printf(jFUNC1 _T("create error : [%s]%s"),szThreadGroup,SAFE_STR(szThreadName));
				return ;
			}
			ResumeThread( m_hThread );
			m_eState= eTS_START;
		}

		void jThread::End()
		{
			jt_printf(jFUNC1 _T(" %s\n"),this->m_sThreadName);
			m_isQuit=true;
			if(m_hThread)
			{
				//apiCHECK(TerminateThread(m_hThread, 0));

				jt_printf(_T("__close_thread() start : %s\n"),this->m_sThreadName);
				//apiCHECK(WaitForSingleObject( m_hThread,INFINITE )!=WAIT_FAILED);
				DWORD ret = WaitForSingleObject( m_hThread,3000 );
				if(ret==WAIT_TIMEOUT)
				{
					jt_printf(_T("__close_thread() WAIT_TIMEOUT end : %s\n"),this->m_sThreadName);

					apiCHECK(TerminateThread(m_hThread, 0));
					apiCHECK(WaitForSingleObject( m_hThread,INFINITE )==WAIT_OBJECT_0);
				}
				CloseHandle(m_hThread);m_hThread=0;
				jt_printf(_T("__close_thread() end : %s\n"),this->m_sThreadName);
			}

			SAFE_CLOSE_HANDLE(m_hDestroyEvent);
			SAFE_CLOSE_HANDLE(m_hWakeUpEvent);
			m_eState= eTS_END;
			m_isUse=false;
			m_func = thread_func_t();

		}


		jIThread* jThreadManager::Run_Timer(thread_func_t& f,tcstr szThreadGroup,tcstr szThreadName,jIVar* pvTime_msec)
		{
			jThread_LOCK();

			
			jThread* t = push_back_thread(szThreadGroup);
			jvRETURN_ret(0,t,_T("%s : %s"),szThreadGroup,szThreadName);

			t->m_pvTime_msec = pvTime_msec;
			t->m_eRunType = nThread::eTIMER;
			t->m_hDestroyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

			if(!t->m_hDestroyEvent)
			{
				jERROR(_T("t->m_hDestroyEvent==NULL : [%s]%s"),szThreadGroup,SAFE_STR(szThreadName));
				throw jFUNC1;
			}
			t->Run(f,szThreadGroup,szThreadName,__jThread_Func_Timer);
			return t;
		}

		jIThread* jThreadManager::Run_Wake(thread_func_t& f,tcstr szThreadGroup,tcstr szThreadName)
		{
			jThread_LOCK();

			jThread* t = push_back_thread(szThreadGroup);
			jvRETURN_ret(0,t,_T("%s : %s"),szThreadGroup,szThreadName);

			t->m_eRunType = nThread::eWAKE;
			t->m_hDestroyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			if(!t->m_hDestroyEvent)
			{
				jERROR_T("t->m_hDestroyEvent==NULL : [%s]%s",szThreadGroup,SAFE_STR(szThreadName));
				throw jFUNC1;
			}
			t->m_hWakeUpEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			if(!t->m_hWakeUpEvent)
			{
				jERROR_T("t->m_hWakeUpEvent==NULL : [%s]%s",szThreadGroup,SAFE_STR(szThreadName));
				throw jFUNC1;
			}

			t->Run(f,szThreadGroup,szThreadName,__jThread_Func_Wake);
			return t;
		}

		jIThread* jThreadManager::Run(thread_func_t& f,tcstr szThreadGroup,tcstr szThreadName,bool isUserLoop)
		{
			jThread_LOCK();

			jThread* t = push_back_thread(szThreadGroup);
			jvRETURN_ret(0,t,_T("%s : %s"),szThreadGroup,szThreadName);
			if(isUserLoop)
			{
				t->m_eRunType = nThread::eNORMAL_USER_LOOP;
				t->Run(f,szThreadGroup,szThreadName,__jThread_Func_UserLoop);
			}
			else
			{
				t->m_eRunType = nThread::eNORMAL_INNER_LOOP;
				t->Run(f,szThreadGroup,szThreadName,__jThread_Func);
			}
			return t;

		}
		void jThreadManager::End(tcstr szThreadGroup1,tcstr szThreadName1)
		{
			fname_t szThreadGroup2;
			fname_t szThreadName2;
			tcstr szThreadGroup=0;
			tcstr szThreadName=0;
			if(szThreadGroup1)
			{
				jt_strcpy_s(szThreadGroup2,szThreadGroup1);
				szThreadGroup = szThreadGroup2;
			}
			if(szThreadName1)
			{
				jt_strcpy_s(szThreadName2,szThreadName1);
				szThreadName = szThreadName2;
			}


			jThread_LOCK();

			if(!szThreadName)
			{
				jThread*p = m_mapjThread;

				for(int i=0;i<jThread_vector_t_MAX ; ++i)
				{
					if(!p[i].m_isUse)continue;
					p[i].End();
				}
			}
			else
			{
				jThread*p = m_mapjThread;
				for(int i=0;i<jThread_vector_t_MAX ; ++i)
				{
					if(!p[i].m_isUse) continue;
					if( jt_strcmp(p[i].m_sThreadName , szThreadName)) continue;
					p[i].End();
					break;
				}
			}
		}
	
		void jThreadManager::EndAll()
		{
			jThread_LOCK();
			jThread*p = m_mapjThread;
			for(int i=0;i<jThread_vector_t_MAX ; ++i)
			{
				if(!p[i].m_isUse) continue;
				jt_printf(jFUNC1 _T("DELETE Start thread : %s.%s "),p[i].m_sThreadGroup,p[i].m_sThreadName);
				p[i].End();
				jt_printf(jFUNC1 _T("DELETE End thread : %s.%s "),p[i].m_sThreadGroup,p[i].m_sThreadName);
			}
		}
		EThreadState jThreadManager::IsRun(tcstr szThreadGroup,tcstr szThreadName)
		{
			jThread_LOCK();

			jThread*p = m_mapjThread;
			for(int i=0;i<jThread_vector_t_MAX ; ++i)
			{
				if(!p[i].m_isUse) continue;
				if(jt_strcmp(p[i].m_sThreadGroup, szThreadGroup)) continue;
				if(!szThreadName) return p[i].m_eState;
				if(jt_strcmp(p[i].m_sThreadName, szThreadName)) continue;
				return p[i].m_eState;
			}
			return eTS_NOT_EXIST;
		}
	}// nThread

} // namespace nMech;
