/* file : nMOB.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-24 18:36:31
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __nMOB_header__
#define __nMOB_header__
#pragma once


namespace nMOB
{
	int make_random();

	int	random_my(int nMin, int nMax);
	int random_boost(int min,int max);

	//# --------------------------------------------------------
	//# @brief	:item1 item2 item3�� ��Ÿ�� Ȯ���� 15, 25, 10�϶� �����ϰ� �ϳ��� item�� �������ִ� �Լ�.
	//# @param  : in�� Ȯ���� ���� �迭.
	//# @return : ���õ� �迭 index , -1�̸� ��ȿ.
	int random_by_percent_list(const std::vector<int>& in);



	typedef int32 packet_type_t;
	//jPacketRecvTimeControl ���� : ������������ ��� ��Ŷ�� ���� �F���ð����� �ݺ������� �����ö� ����ó��.
	struct jPacketRecvTimeControl
	{
		struct jPacketInfo
		{
			int64 m_prev_time;
			jPacketInfo()
			{
				m_prev_time=0;
			}
		};

		jLIST_TYPEDEF_map(packet_type_t,jPacketInfo,m_jPacketInfoList);

		bool is_repeated(packet_type_t packet);
		static void Init();

	};

	typedef int32 allowed_repeat_time_t;
	jLIST_TYPEDEF_map_header(packet_type_t,allowed_repeat_time_t,g_allowed_repeat_time);
}//namespace nMOB


#endif // __nMOB_header__

