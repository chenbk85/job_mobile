// jTest_xml.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "header/jQueue.h"
#ifndef _WIN64
#include "Interface/jIInput.h"
#include "Interface/jIInputActionMap.h"
#endif


cstr g_szApp = _TEXT("jTest_xml");

void _jConsolePrinterFunc( tcstr szString,bool bAdd )
{
#if 0
	nFileSystem::UFile fp("x:\\xml\\test.txt","a+");
	if(bAdd)
		fprintf(fp,"%s", szString);
	else
		fprintf(fp,"%s\n", szString);
#else
	DWORD writtenCount;

	if(bAdd)
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), szString, jt_strlen(szString), &writtenCount, NULL);
	else
	{
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), _T("\n"), 1, &writtenCount, NULL);
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), szString, jt_strlen(szString), &writtenCount, NULL);
	}

#endif
}

#define TUNE

#if defined( WIN32 ) && defined( TUNE )
#include <crtdbg.h>
_CrtMemState startMemState;
_CrtMemState endMemState;
#endif

void test_jxml()
{
#if defined( WIN32 ) && defined( TUNE )
	_CrtMemCheckpoint( &startMemState );
#endif	

	GetjILog()->SetPrinter(_jConsolePrinterFunc);

#if 1
	nFileSystem::jFileName fn(_T("xml\\jConsoleVar_default.xml"));
	jID* pD = GetjIXml()->Load(fn.buffer);
	pD->DebugPrint(nInterface::g_pjILog);
	pD->SaveAsXML(_T("temp\\test_save.xml"));
	pD->SaveAsJXML(_T("temp\\testasdf.xml"));
	fn.Init(_T("temp\\testasdf.jxml"));
	jID* pD1 = GetjIXml()->Load(fn.buffer);
	printf("\n\n--------------\n");
	pD1->DebugPrint(nInterface::g_pjILog);
	int i=0;
	++i;
	GetjIXml()->UnLoad(pD);
#else
	{
		nFileSystem::jFileName fn("xml\\net\\schema\\player_imp.xml");
		jID* pD = GetjIXml()->Load(fn.buffer);
		pD->DebugPrint(nInterface::g_pjILog);
		int i=0;
		++i;
	}

#endif

#if defined( WIN32 ) && defined( TUNE )
	_CrtMemCheckpoint( &endMemState );
	//_CrtMemDumpStatistics( &endMemState );

	_CrtMemState diffMemState;
	_CrtMemDifference( &diffMemState, &startMemState, &endMemState );
	_CrtMemDumpStatistics( &diffMemState );
#endif


}

int _tmain1()
{
	nFileSystem::jFileName fn(_T("xml\\App_Default.xml"));
	jID* pD = GetjIXml()->Load(fn.buffer);
	pD->SaveAsJXML(_T("temp\\testdb.jxml"));
	fn.Init(_T("temp\\testdb.jxml"));
	jID* pD1 = GetjIXml()->Load(fn.buffer);


	//jIE* pE = pD->Find(TEXT("DLL"));
	//pE->DebugPrint(nInterface::g_pjILog);
	//jIE* pE1 = pE->Find(TEXT("NOTFOUND"));
	//pE1->DebugPrint(nInterface::g_pjILog);


	return 0;
}


void test_sxpath()
{
	return ;
	GetjILog()->SetPrinter(_jConsolePrinterFunc);
	nFileSystem::jFileName fn(_T("jTest\\test.xml"));
	jID* pD = GetjIXml()->Load(fn.buffer);
	jIE* pE  = pD->Find(TEXT("EMOTION_SOUND1"))->FindByOrder(3)->FindByOrder(3);
	TCHAR sz[1024];
	pE->SXPathToString(sz, 0);
	pE->DebugPrint(nInterface::g_pjILog);
	jLOG(TEXT("sxpath = %s"), sz);
	jIA* pA;
	jIE* peFind = pD->GetSXPathNode(sz, &pA);
	peFind->GetParent()->DebugPrint(nInterface::g_pjILog);
	peFind->DebugPrint(nInterface::g_pjILog);

}
/* *_* by icandoit : 2006-05-22 19:47:55

jINPUT_ACTION_RECEIVER(asdf,asdf1)
{
	int i=0;
}
*/ //*_* by icandoit : 2006-05-22 19:47:56
#ifndef _WIN64
jINPUT_ACTION_RECEIVER(asdf,asdf)
{
	int i=0;
	++i;

}
#endif

int _tmain1123(int argc, _TCHAR* argv[])
{
	test_jxml();
	//test_sxpath();
	int _tmain_make(int argc, _TCHAR* argv[]);
	//_tmain_make(argc, argv);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//g_ExeEnv.Get_DLL()->ReadDB("release");
	jMech_Init(g_szApp);

	void test_jCircleQueue_Liminit();test_jCircleQueue_Liminit();
	void test_jCircleQueue_UnLiminit1();test_jCircleQueue_UnLiminit1();
	test_jxml();
	_tmain1();
	test_sxpath();

	printf("-------------------------\n");
	printf("-------------------------\n");
	struct _aaa
	{
		fname_t buf;
		int id;
	};

	int begin1 = 0;
	int end1 = 8;
	int begin2 = 8;
	int end2 = 11;
	int begin3 = 11;
	int end3 = 21;
	std::deque<_aaa> test2;
	std::deque<_aaa>::iterator it, ie;


	for( int i=begin1; i < end1; ++i)
	{
		_aaa a;
		a.id = i;
		jt_sprintf(a.buf, _T("id = %d"),i);
		test2.push_back(a);
		if(test2.size() > 5)
			test2.pop_front();

	}
	it = test2.begin();
	ie = test2.end();
	for( ; it!= ie ; ++it)
	{
		jt_printf(_T("deque  %d => %s \n"), it->id, it->buf);
	}
	for( size_t ii = 0; ii < test2.size() ; ++ii)
	{
		_aaa& a = test2[ii];
		jt_printf(_T("deque  %d,  %d => %s \n"),ii, a.id, a.buf);

	}
	printf("-------------------------\n");

	for( int i=begin2; i < end2; ++i)
	{
		_aaa a;
		a.id = i;
		jt_sprintf(a.buf, _T("id = %d"),i);
		test2.push_back(a);
		if(test2.size() > 5)
			test2.pop_front();
	}
	it = test2.begin();
	ie = test2.end();
	for( ; it!= ie ; ++it)
	{
		jt_printf(_T("deque  %d => %s \n"), it->id, it->buf);
	}
	{
		size_t ii;
		for(  ii = 0; ii < test2.size() ; ++ii)
		{
			_aaa& a = test2[ii];
			jt_printf(_T("deque  %d,  %d => %s \n"),ii, a.id, a.buf);

		}
	}
	jMech_Close();

	return 0;
}
