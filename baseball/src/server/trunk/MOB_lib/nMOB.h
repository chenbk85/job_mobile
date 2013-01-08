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
	//# @brief	:item1 item2 item3의 나타날 확률이 15, 25, 10일때 랜덤하게 하나의 item을 선택해주는 함수.
	//# @param  : in은 확률에 대한 배열.
	//# @return : 선택된 배열 index , -1이면 무효.
	int random_by_percent_list(const std::vector<int>& in);



	typedef int32 packet_type_t;
	//jPacketRecvTimeControl 목적 : 유저기준으로 어떠한 패킷이 허용된 짦은시간보다 반복적으로 날나올때 예외처리.
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

