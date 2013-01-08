/* file : nMOB.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-24 18:36:34
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "nMOB.h"
#include <boost/random.hpp>

namespace nMOB
{
	int make_random()
	{
		using namespace std;
		using namespace boost;

		// -3�̻�4������ ������ �����ϰ� �����ϴ� �ǻ糭���迭 �ۼ�
		static mt19937 gen;
		static bool is_seed = false;
		static uniform_int<> dst( 1, INT_MAX-1 );
		static variate_generator< mt19937, uniform_int<>  > rand( gen, dst );

		if (false == is_seed)
		{
			gen.seed(::time(NULL));
			is_seed = true;
		}

		return rand();
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

	template <class T> void SWAP( T& a, T& b )
	{
		T c=a;
		a = b; b = c;
	}
	struct jRandom
	{
		uint32 m_u32Seed;
		void Init(uint32 seed)
		{
			m_u32Seed = seed;
		}
		int32 Rand()			{ return( ((m_u32Seed = m_u32Seed * 214013L + 2531011L) >> 16) & 0x7FFF );}
		int32 SimpleRandom()	{ return( ((m_u32Seed = m_u32Seed + 2531011L) >> 3) & 0x7FFF );}
		int32 ComplexRandom()
		{
			uint32 next = m_u32Seed;
			int32  result;

			next *= 1103515245;
			next += 12345;
			result = (uint32) (next / 65536) % 2048;

			next *= 1103515245;
			next += 12345;
			result <<= 10;
			result ^= (uint32) (next / 65536) % 1024;

			next *= 1103515245;
			next += 12345;
			result <<= 10;
			result ^= (uint32) (next / 65536) % 1024;

			m_u32Seed = next;
			return result;
		}
	};
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
		static int iTimeCurr = nLinux::timeGetTime();
		iTimeCurr = arrayData[iTimeCurr%ARRAY_SIZE(arrayData)];
		r.Init((unsigned)nLinux::timeGetTime()*ival*iTimeCurr);
		r.Rand();
		int val = r.ComplexRandom() %(nMax-nMin);
		iTimeCurr = val* (val*val*iTimeCurr);
		return nMin+val;
	}

	int random_by_percent_list(const std::vector<int>& in)
	{
	/*
	(1000���� 100���� �ݺ��� ��� ���� ��)

		14.7465			        25.372			        9.8815 

	������ �Է� ���ġ��
		15,						25,						10

	���õ� ���ġ�� 99% ��Ȯ��.
	�׽�Ʈ ������ _tmain()�Լ��� �����ϼ���.

		*/
		if(in.size()==0) 
		{
			return -1;
		}

		int totPercent=0;
		for(size_t i=0; i < in.size(); ++i)
		{
			totPercent+=in[i];
		}
		if(totPercent<=0)
		{
			return 0;
		}
		
		const int iMAX_PERCENT=1000;
		int prevPercent=0;
		int iSelect = (int )random_my(1,iMAX_PERCENT);
		size_t iCurr=0;
		for(; iCurr < in.size()-1; ++iCurr)
		{
			int iTempPercent = (in[iCurr]*iMAX_PERCENT)/(totPercent) + prevPercent;
			//printf("iTempPercent =%d ,",iTempPercent);
			if(iTempPercent>=iSelect)
				return iCurr;

			prevPercent += iTempPercent;
		}
		return iCurr;
	}



}//namespace nMOB

