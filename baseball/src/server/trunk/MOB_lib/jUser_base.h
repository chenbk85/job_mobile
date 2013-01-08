/* file : jUser_base.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-20 15:30:48
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __jUser_base_header__
#define __jUser_base_header__
#pragma once

#include <algorithm> 
#include <boost/bind.hpp> 
#include <boost/format.hpp>


#include "common_typedef.h"
#include "common_define_const.h"
#include "common_util.h"
#include "jUser_GameRoomInfo.h"

namespace nBASE_BALL
{

	struct jUser_base :public jUser_GameRoomInfo // client 와 서버가 공유하는 클래스.
	{
		int32 m_single_play_id;
		void reset_user_info()//경기재시작시 플레이데이타 초기화.
		{
			m_single_play_id=0;
			jUser_GameRoomInfo::reset_user_info();
		}


		EUserGPS		m_eEUserGPS;//UserGate와 Client에서만 사용.
		EUserGPS		m_eEUserGPS_prev;//UserGate와 Client에서만 사용.

		GameUserInfo    m_GameUserInfo;////GameInfo + MemberInfo . gameLogic.proto참고할것. UserGateServer와 Client에서 사용한다.
		MemberInfo		m_MemberInfo; // ug.proto참고할것

		//ug.proto game_id . 
		Tbl_User_id_t db_id(){ if(!get_tbl_user() ) return 0; return get_tbl_user()->db_id();}
		s_game_play_info* get_s_game_play_info_Other()
		{ 
			return jUser_GameRoomInfo::get_s_game_play_info_Other(db_id());
		}
		bool is_attackable()////선공유저.
		{ 
			if(is_auto_play()) return true;//자동플레이일때는 자신이 선공 다한다.
			return jUser_GameRoomInfo::get_attack_uid() == db_id(); 
		} 
		bool is_throwable()////투수로서 공을 던질수 있는 유저인지.
		{ 
			if(is_auto_play()) return true;//자동플레이일때는 자신이 선공 다한다.
			return jUser_GameRoomInfo::get_attack_uid() !=db_id() ; 
		} 
		void clear()
		{
			m_eEUserGPS=eUGPS_LOGOUT;
			m_eEUserGPS_prev=eUGPS_LOGOUT;
			m_GameUserInfo.Clear();
			m_MemberInfo.Clear();
			jUser_GameRoomInfo::clear();
		}

	public:

		int	size_tbl_user()
		{
			return m_GameUserInfo.mutable_game_info()->m_tbl_user_size();
		}
		s_tbl_user* get_tbl_user(int index=0)
		{
			if(index<0 || index>=size_tbl_user()) return 0;
			return m_GameUserInfo.mutable_game_info()->mutable_m_tbl_user(index);
		}
		
		s_tbl_user* find_tbl_user(int64 db_id)
		{
			for(int i=0; i< size_tbl_user() ; ++i)
			if( get_tbl_user(i)->db_id()==db_id)
			return get_tbl_user(i);
			return 0;
		}
		bool delete_tbl_user(int64 db_id)
		{
			bool isFind=false;
			GameInfo org;
			for(int i=0; i < size_tbl_user() ; ++i)
			{
				s_tbl_user* p = get_tbl_user(i);
				if(p->db_id()==db_id) { isFind=true;continue;}
				s_tbl_user * pNew = org.add_m_tbl_user();
				pNew->CopyFrom(*p);
			}
			if(!isFind) return false;
			m_GameUserInfo.mutable_game_info()->clear_m_tbl_user();
			m_GameUserInfo.mutable_game_info()->mutable_m_tbl_user()->CopyFrom(org.m_tbl_user());
			return true;
		}
		
		s_tbl_user* add_tbl_user() 
		{
			return m_GameUserInfo.mutable_game_info()->add_m_tbl_user();
		}
		
		template <class _Predicate> void for_each_tbl_user(_Predicate &__pred) 
		{
			for (int i = 0; i < size_tbl_user(); ++i) __pred(get_tbl_user(i));
		}
		
		template <class _Predicate> s_tbl_user* find_if_tbl_user(_Predicate &__pred) 
		{
			for (int i = 0; i < size_tbl_user(); ++i) if(__pred(get_tbl_user(i))) return get_tbl_user(i);
			return 0;
		}
		void clear_tbl_user()
		{ 
			m_GameUserInfo.mutable_game_info()->clear_m_tbl_user();
		}
		void print_tbl_user(int index)
		{
			s_tbl_user* p = get_tbl_user(index);
			if(p)
			{
				jLOG( "tbl_user index=%d",index);
				nProtoHelper::message_print(*p);
			}
		}
		void print_all_tbl_user()
		{
			jLOG("<  s_tbl_user > size = %d", size_tbl_user());
			for(int i=0; i< size_tbl_user() ; ++i)
			{
				print_tbl_user(i);
			}
		}


#	define for_each_player234(X) X(pitcher) X(better)


	};//struct jUser_base


	// 0 ~ 17 round system To 0 ~ 8 round system trans : 라운드 시스템 변경
	inline round_t curr_team_round(round_t round, const int i_ATTACK_CHANGE_ROUND=3)
	{
		int temp_round = i_ATTACK_CHANGE_ROUND * 2;
		// round					// 0 ~17 라운드			
		round_t curr_round = 0;		// 0 ~ 9 라운드 리턴 

		if (round < temp_round)
		{
			if(0 == round)
				return (curr_round = 0);
			else
				return (curr_round = round%3);
		}
		else if (round < temp_round*2)
			return (curr_round = round%3 + i_ATTACK_CHANGE_ROUND);
		else
			return (curr_round = round%3 + i_ATTACK_CHANGE_ROUND*2);

		jWARN("return Error : curr_team_round : curr_round = %d\n", curr_round );
		return curr_round;
	}


}//namespace nBASE_BALL
using namespace nBASE_BALL;

#define jGET_BASEBALL_OBJECT_NO_CHECK(pUser,user,better,pitcher,team)\
	s_tbl_user* user=pUser->get_tbl_user();\



#define jGET_BASEBALL_OBJECT(user,better,pitcher,team)\
	jGET_BASEBALL_OBJECT_NO_CHECK(pUser,user,better,pitcher,team);\
	jRETURN_ans_ug_error( user, ERR_SERVER_DATA);\

 


#endif // __jUser_base_header__
