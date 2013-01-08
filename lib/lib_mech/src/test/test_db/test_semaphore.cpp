/* file : test_semaphore.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-08-25 11:44:35
comp.: t3.co.kr
title : 
desc : 

*/

// Semaphore.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
//////////////////////////////////////////////////////////////////////////////////////
//
//  이 예제는 뮤텍스를 이용하여 g_nInteger의 증가값을 출력하는 예제이다
//

#include "stdafx.h"
#include <windows.h>
#include <process.h>

#include "base/jMsgManager.h"
#include "base/jxVar.h"
using namespace std;
int g_nInteger = 0;
HANDLE g_hSemaphore;
unsigned int __stdcall ThreadFunc( void* lpVoid )
{
	char* sz = (char*)lpVoid;
	LONG lPre = 0;
	while( true )
	{
		//g_hEvent객체가 신호 받음(Signaled)상태가 
		//될 때까지 대기 상태로 들어간다.
		WaitForSingleObject( g_hSemaphore , INFINITE );
		g_nInteger++;
		cout<<"ThreadID(" <<sz <<"): "<<GetCurrentThreadId()<<" : "
			<<g_nInteger<<endl;
		if( g_nInteger >= 8 )
			break;
		//g_hSemaphore객체의 소유권을 해제 함으로써 
		//객체의 상태를 신호 받음(Signaled)상태로 바꾸어 준다.

		ReleaseSemaphore( g_hSemaphore , 1 , &lPre );
	}
	cout<<sz <<" end.. ThreadID : "
		<<GetCurrentThreadId()<<endl;
	ReleaseSemaphore( g_hSemaphore , 1 , &lPre );
	return 0;
}

int test_semaphore(int argc, _TCHAR* argv[])
{
	unsigned int uiThreadID = 0;
	
	const int MAX_RUN_COUNT=2; // 동시에 임계영역(리소스)에 접근가능한 스레드 갯수를 지정.
	g_hSemaphore = CreateSemaphore( NULL , 0 , MAX_RUN_COUNT, NULL );
	if( NULL == g_hSemaphore )
	{
		cout<<"CreateMutex() 함수 호출 실패 : "<<
			GetLastError()<<endl;
	}

	//쓰레드 생성
	HANDLE hThread1 = (HANDLE)_beginthreadex( NULL , 0 
		,ThreadFunc,"hThread1",CREATE_SUSPENDED,&uiThreadID );
	cout<<"Create Thread1 ID : "<<uiThreadID<<endl;

	HANDLE hThread2 = (HANDLE)_beginthreadex( NULL , 0 
		,ThreadFunc,"hThread2",CREATE_SUSPENDED,&uiThreadID );
	cout<<"Create Thread2 ID : "<<uiThreadID<<endl;

	HANDLE hThread3 = (HANDLE)_beginthreadex( NULL , 0 
		,ThreadFunc,"hThread3",CREATE_SUSPENDED,&uiThreadID );
	cout<<"Create Thread3 ID : "<<uiThreadID<<endl;

	if( NULL == hThread1 || NULL == hThread2 || NULL == hThread3 )
	{
		cout<<"[ERROR] Thread1 or hThread2 is NULL.."<<endl;
		return 0;
	}

	//쓰레드를 실행
	ResumeThread( hThread1 );
	ResumeThread( hThread2 );
	ResumeThread( hThread3 );
	//g_hMutex객체의 소유권을 해제 함으로써 
	//객체의 상태를 신호 받음(Signaled)상태로 바꾸어 준다.
	LONG lPre = 0;
	for(int ii=0; ii < MAX_RUN_COUNT ; ++ii)
	{
		ReleaseSemaphore( g_hSemaphore , 1 , &lPre );
	}

	//쓰레드가 종료될 때까지 기다린다.
	WaitForSingleObject( hThread1 , INFINITE );
	WaitForSingleObject( hThread2 , INFINITE );

	//g_hMutex객체의 핸들을 닫는다.
	CloseHandle( g_hSemaphore );
	//쓰레드 핸들을 닫는다.
	CloseHandle( hThread1 );
	CloseHandle( hThread2 );
	return 0;
}

nMech::nUtil::jCriticalSection m_listUdpClientSocket_CS;

void test_jCriticalSection3()
{
	nUtil::jCriticalSection::Auto a2(&m_listUdpClientSocket_CS);
	int i=3;
	++i;
}
void test_jCriticalSection2()
{
	nUtil::jCriticalSection::Auto a2(&m_listUdpClientSocket_CS);
	test_jCriticalSection3();
}
void test_jCriticalSection()
{
	nUtil::jCriticalSection::Auto a2(&m_listUdpClientSocket_CS);
	test_jCriticalSection2();

}





nEVENT::jIMsgManager* pMM1 =0;
nEVENT::jIMsgManager* pMM2 =0;
nEVENT::jIMsgManager* pMM3 =0;
bool g_isQuit=false;
int g_i3=0;
int g_i1=0;
void job1(nEVENT::jIMessage* pM)
{
	printf("job1(%d)\n",g_i1++);
}
void job2(nEVENT::jIMessage* pM)
{
	printf("<<<job2>>>\n");
}
void job3(nEVENT::jIMessage* pM)
{
	printf("job3(%d) : ",g_i3++);
	static int ii=0;
	++ii;
	if(ii%3)
	{
		pMM1->WakeThread();
	}
	if(ii>10)
	{
		g_isQuit=true;
	}
	Sleep(100);
}
nEVENT::jIMessage* pM=0;
jxVar vTime;

void test_jThread()
{
#if 0
결과 : job1 Wake가 jIThread::WakeThread()호출 갯수보다 작을수 있다.
	---------------------
		job3(0) : job1(0)
		job3(1) : job1(1)
		job3(2) : <<<job2>>>
		job3(3) : job1(2)
		job3(4) : job1(3)
		job3(5) : <<<job2>>>
		job3(6) : job1(4)
		job3(7) : job1(5)
		job3(8) : <<<job2>>>
		job3(9) : job1(6)
		job3(10) : job1(7)
#endif

	pMM1 = nEVENT::jIMsgManager::Get(jS(_test1) ,true);
	pMM1->StartThread(true);
	pM = pMM1->Regist_Loop(0,jFUNC_Msg(job1),0,true);
	pM->DoWakeUp();
	
	vTime.SetType(jIVar::EDint);
	vTime.Set_int(3000);

	pMM2 = nEVENT::jIMsgManager::Get(jS(_test2) ,true);
	pMM2->StartTimerThread(&vTime);
	pM = pMM2->Regist_Loop(0,jFUNC_Msg(job2),0,true);
	pM->DoWakeUp();

	pMM3 = nEVENT::jIMsgManager::Get(jS(_test3) ,true);
	pMM3->StartThread(false);
	pM = pMM3->Regist_Loop(0,jFUNC_Msg(job3),0,true);
	pM->DoWakeUp();

	while(!g_isQuit)
	{

	}

}