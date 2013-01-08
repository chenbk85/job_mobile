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


	int	random_my(int nMin, int nMax)
	{
		if(nMin>nMax)
		{
			int temp = nMin; nMin=nMax; nMax=temp;
		}
		int ret =make_random() % (nMax-nMin) + nMin;
// 		printf("\n");
// 		printf("\n");
// 		printf("%s ret=%d  , nMin=%d , nMax=%d",jFUNC,ret,nMin,nMax);
// 		printf("\n");
// 		printf("\n");
		return ret;
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

	jLIST_TYPEDEF_map(packet_type_t,allowed_repeat_time_t,g_allowed_repeat_time);
	bool jPacketRecvTimeControl::is_repeated(packet_type_t packet)
	{
		return false;// jTODO ��� ��ɲ�.

		int32 allowed_repeat_time=0;

		jPacketInfo& info = m_jPacketInfoList[packet];
		int64 curr_time = nOS::get_curr_time_msec();

		g_allowed_repeat_time_it it = g_allowed_repeat_time.find(packet);
		if(it!=g_allowed_repeat_time.end())
		{
			allowed_repeat_time=it->second;
		}
		if(allowed_repeat_time<0) // �����̸� üũ����.
			return false;

		if(allowed_repeat_time==0)// 0�̸� �⺻������ üũ.
		{
			allowed_repeat_time = nG::i_TIME_CLIENT_REPEAT_SEND_PACKET->Get_int();
		}
		int64 prev_time = info.m_prev_time;
		info.m_prev_time = curr_time;
		int64 diff = curr_time - prev_time;
		jvRETURN_ret( true, diff >= allowed_repeat_time ,"packet = %d, allowed_repeat_time= %d , time diff=%lld"
			,packet,allowed_repeat_time , diff);
		return false;
	}


}//namespace nMOB

