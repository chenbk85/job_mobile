/* file : test_RDTSC.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-22 14:44:39
comp.: www.actoz.com
title : 
desc : 


RDTSC용법.

결론 nTIME::getMisteryCount()는 RDTSC보다도 신비하고도 엄청빠른 타이머이다.

*/

#include "stdafx.h"
#include "header/jRDTSC.h"
#include "jTestUnit.h"

using namespace nMech;

namespace 
{
	void f(int ii)
	{
		++ii;
		int i=0;
		++i;
		//cout << "asdf ";
		
	}

	jTEST_SUITE_BEGIN(nTIME_)
	jTEST(RTSC_)
	{
		{
			const int TOT = 1000;
			int i =0;
			uint32 s=0,e=0,t=0;
			RDTSC(s);
			f(i);
			RDTSC(e);
			t = e-s;

			uint64 s1,e1,t1=0;
			s1 = nTIME::getMisteryCount();
			f(i);
			e1 = nTIME::getMisteryCount();
			t1 = e1-s1;
			int ii =0;
			++ii;

		}
#ifdef _DEBUG
		const int TOT = 1000;
#else
		const int TOT = 1;
#endif
		int i =0;
		int j;
		uint32 s=0,e=0,t=0;
		for(j=0; j < TOT; ++j)
		{
			RDTSC(s);
			f(i);
			RDTSC(e);
			t += (e-s);
		}
		t/=TOT;

		uint64 s1,e1,t1=0;
		for(j=0; j < TOT; ++j)
		{
			s1 = nTIME::getMisteryCount();
			f(i);
			e1 = nTIME::getMisteryCount();
			t1 += (e1-s1);
		}
		t1/=TOT;
		int iii=0;
		++iii;

	}
	jTEST_SUITE_END(nTIME_)

}
