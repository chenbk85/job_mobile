/* file : jRandom.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-06-23 23:42:28

title : 
desc : 

*/

#include "stdafx.h"
#include "test.h"
#include "jRandom.h"

#pragma comment(lib, "winmm.lib")


namespace nMech
{
	int	random_my(int nMin, int nMax)
	{
		/*
		�ߺ�= 973 Sleep=0,cpu=2618, �����ȷ�����=27, random_my(1,1000);
		�ߺ�= 356 Sleep=3,cpu=239034, �����ȷ�����=644, random_my(1,1000);
		�ߺ�= 363 Sleep=11,cpu=287753, �����ȷ�����=637, random_my(1,1000);
		*/
		using namespace nMech;
		if(nMin > nMax)
		{
			SWAP(nMin,nMax);
		}
		if(nMin==nMax)return nMin;
		int ival = nMin;
		jRandom r;
		int arrayData[]={233,745,89,2389,3983,398,2,3,1234,3,231,554,4567,67,6237,657,123,382,64,275,275,254,2546,345};
		static int iTimeCurr = timeGetTime();
		iTimeCurr = arrayData[iTimeCurr%ARRAY_SIZE(arrayData)];
		r.Init((unsigned)::timeGetTime()*ival*iTimeCurr);
		r.Rand();
		int val = r.ComplexRandom() %(nMax-nMin);
		iTimeCurr = val* (val*val*iTimeCurr);
		return nMin+val;
	}

	int random_api(int min,int max)
	{/*

	 �ߺ�= 999 Sleep=0,cpu=758, �����ȷ�����=1, random_api(1,1000);
	 �ߺ�= 995 Sleep=3,cpu=238997, �����ȷ�����=5, random_api(1,1000);
	 �ߺ�= 987 Sleep=11,cpu=287641, �����ȷ�����=13, random_api(1,1000);
	 */

		if(min > max)
		{
			SWAP(min,max);
		}
		if(min==max)return min;
		int ival = min;
		srand( (unsigned)time( NULL )+ival );
		int val = rand() % (max-min);
		return min+val;
	}
	int random_boost(int min,int max)
	{
		/*
		�ߺ�= 369 Sleep=0,cpu=4272, �����ȷ�����=631, random_boost(1,1000);
		�ߺ�= 376 Sleep=3,cpu=239214, �����ȷ�����=624, random_boost(1,1000);
		�ߺ�= 370 Sleep=11,cpu=287597, �����ȷ�����=630, random_boost(1,1000);

		*/
		using namespace std;
		using namespace boost;

		mt19937 rng(time(NULL));
		uniform_int<> uni_dist(min, max);
		static variate_generator<mt19937, uniform_int<> > die(rng, uni_dist);
		return die();
	}

	void test_random_try1000(RandomFunction_t* pRandom, const char* tag, int SleepTime)
	{
		for(int j=0; j< 1 ; ++j)
		{ // test int	GetRandomValue(int nMin, int nMax)
			const int iMAX = 1000;
			jLIST_TYPEDEF_set(int,int_set);
			int �ߺ�=0;

			u32 b,e;
			RDTSC(b);
			for(int i=0; i< iMAX ; ++i)
			{
				if(SleepTime) Sleep(SleepTime);
				int val = pRandom(1,iMAX);
				int_set_it it = int_set.find(val);
				if(it==int_set.end())
				{
					int_set.insert(val);
				}
				else
				{
					++�ߺ�;
				}
			}
			RDTSC(e);
			printf("�ߺ�= %d Sleep=%d,cpu=%u, �����ȷ�����=%d, %s(%d,%d);\n",�ߺ�,SleepTime,(e-b)/10000,int_set.size(),tag,1,iMAX);

		}
		printf("\n\n");
	}
}
