/* file : jIThread.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2009-12-18 11:22:49
comp.: t3.co.kr
title : 
desc : 


void jThreadManger::Run(thread_func_t f,tcstr szThreadName); 용 함수 템플릿

static void _MsgThread_jIMsgManager( jIThread* pT)
{
for(;pT->IsRun();)
{
nMech::nEVENT::jIMsgManager::FrameMove();
Sleep(1);
}
}



*/

#ifndef __jThread_header__
#define __jThread_header__
#pragma once

namespace nMech
{
	namespace nThread
	{
		typedef unsigned int __stdcall __jThread_Func_t( void* v);
		typedef boost::function<void (struct jIThread*)> thread_func_t;

		enum EThreadState 
		{	
			eTS_PREV_INIT,
			eTS_START,
			eTS_END,
			eTS_NOT_EXIST,
			eTS_ERROR_OCCUR,
			//해당 스레드는 존재하지않는다.
		};
		enum ERunType
		{
			eNORMAL_USER_LOOP, // user 함수에서 루프를 돈다.
			eNORMAL_INNER_LOOP,// jIThread내부적으로 루프를 돈다.
			eTIMER,
			eWAKE,//이벤트발생시 작동됨.
		};


		#define jINTERFACE_jIThread(X) public:	\
			virtual cstr GetThreadGroup() ##X \
			virtual cstr GetThreadName() ##X \
			virtual void Release() ##X \
			virtual bool IsRun() ##X \
			virtual void DoWake() ##X \
			virtual HANDLE &GetDestroyEvent() ##X\
			virtual HANDLE &GetWakeEvent() ##X\

		jINTERFACE_END(jIThread);


#define jINTERFACE_jIThreadManager(X) public:	\
		virtual jIThread* Run(thread_func_t& f,tcstr szThreadGroup,tcstr szThreadName,bool isUserLoop=true)##X \
		virtual jIThread* Run_Timer(thread_func_t& f,tcstr szThreadGroup,tcstr szThreadName,jIVar* pvTime_msec)##X \
		virtual jIThread* Run_Wake(thread_func_t& f,tcstr szThreadGroup,tcstr szThreadName)##X \
		virtual void End(tcstr szThreadGroup,tcstr szThreadName)##X \
		virtual void EndAll()##X \
		virtual EThreadState  IsRun(tcstr szThreadGroup,tcstr szThreadName) ##X\

		jINTERFACE_END_BASE1(jIThreadManager, nInterface::jIInterface);

		// 사용법.
		//
		// jIThreadManager* pjIThreadManager= jCREATE_INTERFACE(nMech::nThread::jIThreadManager); 
		// pjIThreadManager는 싱글톤이라서 Release할 필요 없다.

	}//namespace nThread

}
#endif // __jThread_header__
