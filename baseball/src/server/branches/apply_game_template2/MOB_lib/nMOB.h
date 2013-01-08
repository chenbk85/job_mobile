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

}//namespace nMOB


#endif // __nMOB_header__
