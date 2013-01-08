/* file : common_util.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-05-31 14:34:23
comp.: www.neowiz.com
title : 
desc : 



�׽�Ʈ Ŭ�� �� ������ �����ϴ� ��ƿ�� �Լ���.

*/

#ifndef __common_util_header__
#define __common_util_header__
#pragma once

namespace nBASE_BALL
{

	inline bool is_stackable_item_type(EItemCategory e) { return e!=eIC_EQUIP; }
	
	inline int32 get_base_runner_count(base_runner_state_t brs)
	{
		int iCount= (brs & jBIT_0);
		iCount+= (brs & jBIT_1);
		iCount+= (brs & jBIT_2);
		return iCount;
	}
	
#define for_each_EBaseCount(X)\
	X(eBC_BASE1			,1	,"1��")\
	X(eBC_BASE2			,2	,"2��")\
	X(eBC_BASE3			,3	,"3��")\

	jDEFINE_ENUM_CODE(EBaseCount);

	// �ʿ� ���� ���� ����.
// 	inline bool is_base_runner(base_runner_state_t brs, EBaseCount eCount)// 1, 2, 3�翡 ���ڰ� �ֳ�?
// 	{
// 		jRETURN_ret(false , eCount>=eBC_BASE1 && eCount <=eBC_BASE3);
// 		brs >> (eCount-1);
// 		return brs & jBIT_0;
// 	}

	template<typename T>
	inline T get_bit_count(T bit_array)
	{
		T iCount = bit_array & jBIT_0;
		bit_array = bit_array >> 1;
		size_t iTot = sizeof(T)*8;
		for(size_t i=1; i< iTot; ++i)
		{
			iCount +=(bit_array & jBIT_0);
			bit_array = bit_array >> 1;
		}
		return iCount;
	}
	inline void print_s_result_round( base_runner_state_t prev_state
		, std::pair<score_t,base_runner_state_t> &new_result, EBatterHitType eType )
	{
		std::bitset<3> old_bit(prev_state);
		std::bitset<3> new_bit(new_result.second);
		jLOG("prev_state=%s, eHitType=%s  => ��� score=%d ,state=%s"
			, old_bit.to_string().c_str(), nMech::ToString(eType),new_result.first, new_bit.to_string().c_str());
	}


	//# --------------------------------------------------------
	//# @brief :���� ���� ���¿� Ÿ���� ��Ʈ���·� ���ο� ���ڻ��¿� �߰��� ������ ����.
	inline std::pair<score_t,base_runner_state_t> calc_base_runner_count(base_runner_state_t curr_brc , EBatterHitType eHitType)
	{
		std::pair<score_t,base_runner_state_t>  ret = std::make_pair(0 , curr_brc);
		jRETURN_ret(ret , (eHitType>eBEGIN_EBatterHitType && eHitType<eEND_EBatterHitType) );

		if(eHitType <= eEBHT_NO_HIT)
		{
			return ret;
		}

		switch(eHitType)
		{
		case eEBHT_ONEHIT:
		case eEBHT_DOUBLEHIT:
		case eEBHT_TRIPLEHIT:
		case eEBHT_HOMERUN:
			{
				const int32 BASE_STATE_MASK= 7; //7 = 2^2 + 2^1 + 2^0
				curr_brc &= BASE_STATE_MASK;// �Ʒ�3 bit�� ���� ��� �ʱ�ȭ. 

				//������
				curr_brc <<= 1;
				curr_brc |=jBIT_0; // ���� �Ѹ� �ϴ� Ȩ���� ����Ѵٰ� �����ϰ�.
				jCHECK(eEBHT_ONEHIT == (eEBHT_NO_HIT+1) );//������.
				int32 shift_count = eHitType - eEBHT_NO_HIT;
				curr_brc = curr_brc << shift_count; //
				curr_brc >>= 1;

				int32 score_bit = curr_brc;
				score_bit &= (~BASE_STATE_MASK);
				curr_brc &= BASE_STATE_MASK;

				ret.first = get_bit_count(score_bit);
				ret.second = curr_brc;
				break;
			}
		default:
			{
				jWARN("eHitType is invalid : %d",eHitType);
				break;
			}
		}
		return ret;
	}

}//namespace nBASE_BALL


#endif // __common_util_header__
