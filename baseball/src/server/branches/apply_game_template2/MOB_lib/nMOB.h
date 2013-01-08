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

}//namespace nMOB


#endif // __nMOB_header__
