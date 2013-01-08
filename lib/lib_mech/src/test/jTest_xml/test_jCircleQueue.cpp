/* file : test_jCircleQueue.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-07-04 20:44:20
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "header/jQueue.h"
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

void test_jCircleQueue_Liminit()
{
	jCircleQueue_Liminit<_aaa> test;
	test.Init(5);
	_aaa* pA = 0;
	printf("\n 0~7  push_back start");
	for( int i=0 ; i< 8; ++i)
	{
		pA = test.push_back();
		if(!pA) 
		{
			printf("\n%d : push_back skiped", i);
			continue;
		}
		pA->id = i;
		jt_sprintf(pA->buf ,_T(" id =%d"),pA->id);
		jt_printf(_T("\npush_back ok %d : %d => %s \n"), i,pA->id, pA->buf);

	}

	printf("\n 0~2  pop_front start");
	for( int i =0; i< 3; ++i)
	{
		pA = test.pop_front();
		if(!pA) 
		{
			printf("\n%d : pop_front skiped", i);
			continue;
		}
		jt_printf(_T("\n%d : %d => %s \n"), i,pA->id, pA->buf);
	}

	printf("\n 10~20  push_back start");
	for( int i=5 ; i< 21; ++i)
	{
		pA = test.push_back();
		if(!pA) 
		{
			printf("\n%d : push_back skiped", i);
			continue;
		}
		pA->id = i;
		jt_sprintf(pA->buf ,_T(" id =%d"),pA->id);
		jt_printf(_T("\npush_back ok %d : %d => %s \n"), i,pA->id, pA->buf);
	}

	printf("\n 0~10  pop_front start");
	for( int i =0; i< 11; ++i)
	{
		pA = test.pop_front();
		if(!pA) 
		{
			printf("\n%d : pop_front skiped", i);
			continue;
		}
		jt_printf(_T("\n%d : %d => %s \n"), i,pA->id, pA->buf);
	}

	for( int i=8 ; i< 33; ++i)
	{
		pA = test.push_back();
		if(!pA) 
		{
			printf("\n%d : push_back skiped", i);
			continue;
		}
		pA->id = i;
		jt_sprintf(pA->buf ,_T(" id =%d"),pA->id);
	}
	for( int i =0; i< 4; ++i)
	{
		pA = test.pop_front();
		if(!pA) 
		{
			printf("\n%d : pop_front skiped", i);
			continue;
		}
		jt_printf(_T("\n%d : %d => %s \n"), i,pA->id, pA->buf);
	}

	for( int i=13 ; i< 33; ++i)
	{
		pA = test.push_back();
		if(!pA) 
		{
			printf("\n%d : push_back skiped", i);
			continue;
		}
		pA->id = i;
		jt_sprintf(pA->buf ,_T(" id =%d"),pA->id);
	}
	for( int i =0; i< 4; ++i)
	{
		pA = test.pop_front();
		if(!pA) 
		{
			printf("\n%d : pop_front skiped", i);
			continue;
		}
		jt_printf(_T("\n%d : %d => %s \n"), i,pA->id, pA->buf);
	}
	for( int i=17 ; i< 33; ++i)
	{
		pA = test.push_back();
		if(!pA) 
		{
			printf("\n%d : push_back skiped", i);
			continue;
		}
		pA->id = i;
		jt_sprintf(pA->buf ,_T(" id =%d"),pA->id);
	}
	for( int i =0; i< 2; ++i)
	{
		pA = test.pop_front();
		if(!pA) 
		{
			printf("\n%d : pop_front skiped", i);
			continue;
		}
		jt_printf(_T("\n%d : %d => %s \n"), i,pA->id, pA->buf);
	}
}

void test_jCircleQueue_UnLiminit1()
{

	jCircleQueue_UnLiminit<_aaa> test(5);

	for( int i=begin1; i< end1 ; ++i)
	{
		_aaa* a = test.push_back();
		a->id = i;
		jt_sprintf(a->buf ,_T(" id =%d"),a->id);
	}

	_aaa* pA = test.GotoBegin();
	for( ; pA ; pA = test.GotoBeginNext() )
	{
		jt_printf(_T(" %d => %s \n"), pA->id, pA->buf);
	}

	printf("asdf ----------\n");
	for( int i=begin2; i< end2 ; ++i)
	{
		_aaa* a = test.push_back();
		a->id = i;
		jt_sprintf(a->buf ,_T(" id =%d"),a->id);
	}

	pA = test.GotoBegin();
	for( ; pA ; pA = test.GotoBeginNext() )
	{
		jt_printf(_T(" %d => %s \n"), pA->id, pA->buf);
	}
	printf("asdf ----------\n");
	for( int i=begin3; i< end3 ; ++i)
	{
		_aaa* a = test.push_back();
		a->id = i;
		jt_sprintf(a->buf ,_T(" id =%d"),a->id);
	}

	pA = test.GotoBegin();
	for( ; pA ; pA = test.GotoBeginNext() )
	{
		jt_printf(_T(" %d => %s \n"), pA->id, pA->buf);
	}

}


