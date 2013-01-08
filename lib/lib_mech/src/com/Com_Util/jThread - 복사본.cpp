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

using namespace nMech;

#define SAFE_CLOSE_HANDLE(d) if(d){ CloseHandle(d);d=0;}

#define jThread_LOCK() jAUTO_LOCK_CS(m_CS)
namespace nMech
{
	namespace nThread
	{

		//--------------------------------------------------------------------------
		class jThread : public jIThread
		//--------------------------------------------------------------------------
		{
			jINTERFACE_HEADER(jIThread);

			HANDLE m_hThread;
			unsigned int m_uiThreadID;
			bool m_isQuit;
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
				,m_isQuit(false)
				,m_hThread(0)
				,m_uiThreadID(0)
				,m_hDestroyEvent(0)
				,m_hWakeUpEvent(0)
				,m_pvTime_msec(0)
			{}

			void Run(thread_func_t f,tcstr szThreadGroup,tcstr szThreadName,__jThread_Func_t* pFunc) ;
			void End() ;
			void __close_thread();

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
			jLIST_TYPEDEF_list_typedef(jThread,jThread_vector);
			jLIST_TYPEDEF_map(tstring , jThread_vector_t,m_mapjThread);

			jThread* __find_thread(jThread_vector_t& vec, tcstr szThreadName);

		};


		jThreadManager g_jThreadManager;
		jCTOR_INTERFACE(nMech::nThread::jIThreadManager,jThreadManager)
		{
			return &g_jThreadManager;
		}
		jDTOR_INTERFACE(nMech::nThread::jIThreadManager,jThreadManager)
		{
		}


		struct __kill_thread_info
		{
			tname_t m_sThreadGroup;
			tname_t m_sThreadName;
		};

		//jThreadManager  g_pjIThreadManager ;
		unsigned int __stdcall __kill_thread( void* v)
		{
			__kill_thread_info* t= (__kill_thread_info*)v;
			//Sleep(500);
			g_jThreadManager.End(t->m_sThreadGroup, t->m_sThreadName );
			SAFE_DELETE(t);
			return 0;
		}

		void run_kill_thread(jThread* t1)
		{
			t1->m_isQuit=true;
			g_jThreadManager.End(t1->m_sThreadGroup, t1->m_sThreadName );
			return;
			unsigned int m_uiThreadID=0;
			__kill_thread_info* t = new __kill_thread_info;
			jt_strcpy_s(t->m_sThreadName ,t1->m_sThreadName);
			jt_strcpy_s(t->m_sThreadGroup , t1->m_sThreadGroup);
			HANDLE m_hThread= (HANDLE)_beginthreadex( NULL , 0 , __kill_thread, t, CREATE_SUSPENDED  , &m_uiThreadID );
			jAssert0(m_hThread);
			ResumeThread( m_hThread );
		}

		unsigned int __stdcall __jThread_Func_UserLoop( void* v)
		{
			jIThread* _t = (jIThread*)v;
			jThread* t = (jThread*)_t;
			try
			{
				t->m_func(t);
			}
			catch (...)
			{
				jWARN1(_T("jIThread = %s 알수 없는 예외"), t->m_sThreadGroup);
				t->m_eState = nThread::eTS_ERROR_OCCUR;
			}
			//jt_printf(jFUNC1 _T("END thread group: %s !"),t->m_sThreadName);
			run_kill_thread(t);
			return 0;
		}

		unsigned int __stdcall __jThread_Func( void* v)
		{
			jIThread* _t = (jIThread*)v;
			jThread* t = (jThread*)_t;
			try
			{
				for(;t->IsRun();)
				{
					t->m_func(t);
				}
			}
			catch (...)
			{
				jWARN1(_T("jIThread = %s 알수 없는 예외"), t->m_sThreadGroup);
				t->m_eState = nThread::eTS_ERROR_OCCUR;
			}
			//jt_printf(jFUNC1 _T("END thread group: %s !"),t->m_sThreadName);
			run_kill_thread(t);
			return 0;
		}


		unsigned int __stdcall __jThread_Func_Timer( void* v)
		{
			jIThread* _t = (jIThread*)v;
			jThread* t = (jThread*)_t;
			try
			{
				for(;t->IsRun();)
				{
					DWORD dwResult = WaitForSingleObject(t->m_hDestroyEvent, t->m_pvTime_msec->Get_int() );

					// 종료 이벤트가 발생했을경우 Thread를 종료합니다.
					if (dwResult == WAIT_OBJECT_0) return 0;
					t->m_func(t);
				}
			}
			catch (...)
			{
				jERROR1(_T("jIThread = %s 알수 없는 예외"), t->m_sThreadGroup);
				t->m_eState = nThread::eTS_ERROR_OCCUR;
			}
			//jt_printf(jFUNC1 _T("END thread group: %s !"),t->m_sThreadName);
			run_kill_thread(t);
			return 0;
		}


		unsigned int __stdcall __jThread_Func_Wake( void* v)
		{
			jIThread* _t = (jIThread*)v;
			jThread* t = (jThread*)_t;
			//nUtil::nWIN::SetThreadName(-1,t->mm_sName);
			try
			{
				HANDLE	hEvents[2] = {t->m_hDestroyEvent, t->m_hWakeUpEvent};
				DWORD	eventID=0;

				for(;t->IsRun();)
				{
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
				}
			}
			catch (...)
			{
				jERROR1(_T("jIThread = [%s] 알수 없는 예외"), t->m_sThreadGroup,t->m_sThreadName);
				t->m_eState = nThread::eTS_ERROR_OCCUR;
			}
			jLOG1(jFUNC1 _T("END thread group: %s !"),t->m_sThreadName);
			run_kill_thread(t);
			return 0;
		}

		cstr		jThread::GetThreadName()				{ return m_sThreadName;}
		cstr		jThread::GetThreadGroup()				{ return m_sThreadGroup;}
		HANDLE &	jThread::GetDestroyEvent()		{return m_hDestroyEvent;}
		bool		jThread::IsRun()				{return !m_isQuit;}
		void		jThread::DoWake()				{SetEvent(m_hWakeUpEvent);}
		void		jThread::Release()				{g_jThreadManager.End(m_sThreadGroup,m_sThreadName);}

		void jThread::Run(thread_func_t f,tcstr szThreadGroup,tcstr szThreadName,__jThread_Func_t* pFunc)
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
				//jt_printf(jFUNC1 _T("create error : [%s]%s"),szThreadGroup,SAFE_STR(szThreadName));
				return ;
			}
			ResumeThread( m_hThread );
			m_eState= eTS_START;
		}

		void jThread::__close_thread()
		{
			if(m_hThread)
			{
				//jt_printf(_T("__close_thread() start : %s\n"),this->m_sThreadName);
				//apiCHECK(WaitForSingleObject( m_hThread,INFINITE )!=WAIT_FAILED);
				DWORD ret = WaitForSingleObject( m_hThread,5000 );
				if(ret==WAIT_TIMEOUT)
				{
					apiCHECK(TerminateThread(m_hThread, 0));
					apiCHECK(WaitForSingleObject( m_hThread,INFINITE )==WAIT_OBJECT_0);
				}
				CloseHandle(m_hThread);m_hThread=0;
				//jt_printf(_T("__close_thread() end : %s\n"),this->m_sThreadName);
			}
		}

		void jThread::End()
		{
			//jt_printf(jFUNC1 _T(" %s\n"),this->m_sThreadName);
			m_isQuit=true;
#if 0
			if(m_hDestroyEvent)
			{
				SetEvent(m_hDestroyEvent);
			}

			//if(m_eRunType==eNORMAL_USER_LOOP)
			{
				if(m_hThread)
				{
					apiCHECK(TerminateThread(m_hThread, 0));
				}
			}
#else
			if(m_hThread)
			{
				apiCHECK(TerminateThread(m_hThread, 0));
			}
#endif

			__close_thread();

			SAFE_CLOSE_HANDLE(m_hDestroyEvent);
			SAFE_CLOSE_HANDLE(m_hWakeUpEvent);
			m_eState= eTS_END;

		}


		jIThread* jThreadManager::Run_Timer(thread_func_t f,tcstr szThreadGroup,tcstr szThreadName,jIVar* pvTime_msec)
		{
			jThread_LOCK();

			m_mapjThread[szThreadGroup].push_back(jThread());
			jThread& t = m_mapjThread[szThreadGroup].back();
			t.m_pvTime_msec = pvTime_msec;
			t.m_eRunType = nThread::eTIMER;
			t.m_hDestroyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			if(!t.m_hDestroyEvent)
			{
				jERROR1(_T("t.m_hDestroyEvent==NULL : [%s]%s"),szThreadGroup,SAFE_STR(szThreadName));
				throw jFUNC1;
			}
			t.Run(f,szThreadGroup,szThreadName,__jThread_Func_Timer);
			return &t;
		}

		jIThread* jThreadManager::Run_Wake(thread_func_t f,tcstr szThreadGroup,tcstr szThreadName)
		{
			jThread_LOCK();
			m_mapjThread[szThreadGroup].push_back(jThread());
			jThread& t = m_mapjThread[szThreadGroup].back();
			t.m_eRunType = nThread::eWAKE;
			t.m_hDestroyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			if(!t.m_hDestroyEvent)
			{
				jERROR("t.m_hDestroyEvent==NULL : [%s]%s",szThreadGroup,SAFE_STR(szThreadName));
				throw jFUNC1;
			}
			t.m_hWakeUpEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			if(!t.m_hWakeUpEvent)
			{
				jERROR("t.m_hWakeUpEvent==NULL : [%s]%s",szThreadGroup,SAFE_STR(szThreadName));
				throw jFUNC1;
			}

			t.Run(f,szThreadGroup,szThreadName,__jThread_Func_Wake);
			return &t;
		}

		jIThread* jThreadManager::Run(thread_func_t f,tcstr szThreadGroup,tcstr szThreadName,bool isUserLoop)
		{
			jThread_LOCK();

			m_mapjThread_value_t& v = m_mapjThread[szThreadGroup];
			v.push_back(jThread());
			jThread& t = v.back();
			if(isUserLoop)
			{
				t.m_eRunType = nThread::eNORMAL_USER_LOOP;
				t.Run(f,szThreadGroup,szThreadName,__jThread_Func_UserLoop);
			}
			else
			{
				t.m_eRunType = nThread::eNORMAL_INNER_LOOP;
				t.Run(f,szThreadGroup,szThreadName,__jThread_Func);
			}
			return &t;

		}
		void jThreadManager::End(tcstr szThreadGroup1,tcstr szThreadName1)
		{
			if(!m_mapjThread.size()) return;

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
			m_mapjThread_it it = m_mapjThread.find(szThreadGroup);
			if(it==m_mapjThread.end()) 
			{
				//jWARN1(_T("thread group not found : %s"),szThreadGroup);
				return;
			}
			if(!szThreadName)
			{
				for_each(it->second.begin(), it->second.end() , tr1::bind(&jThread::End,tr1::placeholders::_1));
				it->second.clear();
				//m_mapjThread.erase(it);
				//jt_printf(jFUNC1 _T("DELETED thread group: %s !"),szThreadGroup);

			}
			else
			{
				jThread_vector_it it2 = it->second.begin(), ie2 = it->second.end();
				for(;it2!=ie2;++it2)
				{
					if( jt_strcmp(it2->m_sThreadName , szThreadName)==0)
					{
						it2->End();
						it->second.erase(it2);
						//jt_printf(jFUNC1 _T("DELETED thread : %s End()"),szThreadName);
						break;
					}
				}
			}
		}
	
		void jThreadManager::EndAll()
		{
			jThread_LOCK();
			m_mapjThread_it it = m_mapjThread.begin(), ie = m_mapjThread.end();
			for(;it!=ie; ++it)
			{
				//jt_printf(jFUNC1 _T("DELETE Start thread group : %s "),it->first.c_str());
				for_each(it->second.begin(), it->second.end() , tr1::bind(&jThread::End,tr1::placeholders::_1));
				//jt_printf(jFUNC1 _T("DELETE End thread group : %s "),it->first.c_str());
			}
			m_mapjThread.clear();

		}
		jThread* jThreadManager::__find_thread(jThread_vector_t& vec, tcstr szThreadName)
		{
			jThread_vector_it it2 = vec.begin(), ie2 = vec.end();
			for(;it2!=ie2;++it2)
			{
				if( jt_strcmp(it2->m_sThreadName , szThreadName)==0)
				{
					return &(*it2);
				}
			}
			return 0;
		}
		EThreadState jThreadManager::IsRun(tcstr szThreadGroup,tcstr szThreadName)
		{
			jThread_LOCK();
			m_mapjThread_it it = m_mapjThread.find(szThreadGroup);
			if(!szThreadName)
			{
				if(it==m_mapjThread.end()) return nThread::eTS_NOT_EXIST;
				jAssert0(it->second.size());
				return it->second.front().m_eState;
			}
			jThread* pT = __find_thread(it->second, szThreadName);
			if(!pT) return eTS_NOT_EXIST;
			return pT->m_eState;
		}


	}// nThread

} // namespace nMech;
