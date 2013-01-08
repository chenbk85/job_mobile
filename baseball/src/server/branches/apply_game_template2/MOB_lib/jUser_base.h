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
		s_game_play_info* get_s_game_play_info_Other(){ return jUser_GameRoomInfo::get_s_game_play_info_Other(db_id());}
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

//s_tbl_team	size_tbl_team(), get_tbl_team(iOrder ) find_tbl_team(db_id) , delete_tbl_team(db_id) add_tbl_team();
//s_tbl_user	size_tbl_user(), get_tbl_user(iOrder ) find_tbl_user(db_id) , delete_tbl_user(db_id) add_tbl_user();
//s_tbl_item	size_tbl_item(), get_tbl_item(iOrder ) find_tbl_item(db_id) , delete_tbl_item(db_id) add_tbl_item();
//s_tbl_friend	
//s_tbl_playerbetter 
//s_tbl_playerpitcher 
//s_tbl_pitcherskill
//s_tbl_quest
//s_tbl_title
#		define get_tbl_user_234(TABLE,EXCEL_TABLE,SELECT_FIELD)	\
		int	size_##TABLE(){return m_GameUserInfo.mutable_game_info()->_jJOIN_3(m_,TABLE,_size)();}\
		s_##TABLE* get_##TABLE(int idx=0)\
		{\
			if(idx<0 || idx>=size_##TABLE()) return 0;\
			return m_GameUserInfo.mutable_game_info()->mutable_m_##TABLE(idx);\
		}\
		\
		s_##TABLE* find_##TABLE(int64 db_id)\
		{\
			for(int i=0; i< size_##TABLE() ; ++i)\
			if( get_##TABLE(i)->db_id()==db_id)\
			return get_##TABLE(i);\
			return 0;\
		}\
		bool delete_##TABLE(int64 db_id)\
		{\
			bool isFind=false;\
			GameInfo org;\
			for(int i=0; i < size_##TABLE() ; ++i)\
			{\
				s_##TABLE* p = get_##TABLE(i);\
				if(p->db_id()==db_id) { isFind=true;continue;}\
				s_##TABLE * pNew = org.add_m_##TABLE();\
				pNew->CopyFrom(*p);\
			}\
			if(!isFind) return false;\
			m_GameUserInfo.mutable_game_info()->clear_m_##TABLE();\
			m_GameUserInfo.mutable_game_info()->mutable_m_##TABLE()->CopyFrom(org.m_##TABLE());\
			return true;\
		}\
		\
		s_##TABLE* add_##TABLE() {return m_GameUserInfo.mutable_game_info()->add_m_##TABLE();}\
		\
		template <class _Predicate> void for_each_##TABLE(_Predicate &__pred) \
		{for (int i = 0; i < size_##TABLE(); ++i) __pred(get_##TABLE(i));}\
		\
		template <class _Predicate> s_##TABLE* find_if_##TABLE(_Predicate &__pred) \
		{\
			for (int i = 0; i < size_##TABLE(); ++i) if(__pred(get_##TABLE(i))) return get_##TABLE(i);\
			return 0;\
		}\
		void clear_##TABLE(){ m_GameUserInfo.mutable_game_info()->clear_m_##TABLE();};\



		for_each_GameInfo_Excel_Table(get_tbl_user_234);

		/// @brief 해당 유저의 디펄트 팀을 구함.
		/// @param 
		/// @return 만약 디펄트 팀이 세팅안되어 있으면 NULL리턴.
		s_tbl_team* get_default_tbl_team()
		{
			int32 team_order = get_tbl_user()->default_tid();
			if( 0 > team_order || size_tbl_team() <= team_order )
				return 0;
			return get_tbl_team( team_order );
		}

#		define jLAMDA___get_tbl_pitcherskill(X,Z) X(vector<s_tbl_pitcherskill*>&,out) Z(Tbl_PlayerPitcher_id_t,pid)
		jLAMDA_for_each(__get_tbl_pitcherskill,s_tbl_pitcherskill*)
		{
			if (it && it->pid() == pid) 
				out.push_back(it);
		}
		jLAMDA_end();

		/// @brief 투수가 보유한 스킬을 구한다.
		/// @param 투수의 pid
		void get_tbl_pitcherskill(OUT vector<s_tbl_pitcherskill*>& out,IN Tbl_PlayerPitcher_id_t pid)
		{
			__get_tbl_pitcherskill func(out,pid);
			for_each_tbl_pitcherskill( func );
		}

#		define jLAMDA___is_dup_gesture(X,Z) X(EGestureType ,gesture)  X(EPlayerBreakingBall, eType)  Z(Tbl_PlayerPitcher_id_t,pid)
		jLAMDA_find_if(__is_dup_gesture,s_tbl_pitcherskill*)
		{
			if(!it) return false;
			if(it->pid() != pid ) return false;

			if(gesture!=eEND_EGestureType && it->gesture()==gesture)
				return true;
			if(eType!=eEND_EPlayerBreakingBall && it->type()==eType)
				return true;
			return false;

		}
		jLAMDA_end();

		bool is_duplicate_pitcherskill(EGestureType gesture, EPlayerBreakingBall eType,  Tbl_PlayerPitcher_id_t pid) //gesture이 투수의 보유 스킬에서 중복되었는지 체크.
		{
			__is_dup_gesture func(gesture, eType, pid);
			return find_if_tbl_pitcherskill(func)!=NULL;
		}

		// get_default_tbl_playerbetter() ,find_team_by_better(db_id)
		// get_default_tbl_playerpitcher() ,find_team_by_pitcher(db_id)
#	define get_find_code_546456(TABLE)\
	s_tbl_player##TABLE* get_default_tbl_player##TABLE()\
		{\
		s_tbl_team* p = get_default_tbl_team();\
		if(!p) return 0;\
		return find_tbl_player##TABLE(p->pid_##TABLE());\
		}\
		s_tbl_team* find_team_by_##TABLE(int64 db_id)\
		{\
		int iSize = size_tbl_team();\
		for( int i =0; i<iSize; ++i )\
		{\
		s_tbl_team* pTeam = get_tbl_team( i );\
		if(!pTeam) { continue; }\
		if(pTeam->pid_##TABLE() == db_id) { return pTeam; }\
		}\
		return 0;\
		}\

#	define for_each_player234(X) X(pitcher) X(better)
		for_each_player234(get_find_code_546456);


#		define jLAMDA___find_tbl_quest_by_sid(X,Z) Z(Sys_Quest_id_t,sid)
		jLAMDA_find_if(__find_tbl_quest_by_sid,s_tbl_quest*)
		{
			return (it && it->quest_sid() == sid);
		}
		jLAMDA_end();

		s_tbl_quest* find_tbl_quest_by_sid(Sys_Quest_id_t sid)
		{
			__find_tbl_quest_by_sid func(sid);
			return find_if_tbl_quest(func);
		}


	};//struct jUser_base

	inline int64 get_player_db_id(jUser_base* pUser, int player_index, bool is_better)
	{
		if(!pUser) return 0;
		if(is_better)
		{
			s_tbl_playerbetter* p = pUser->get_tbl_playerbetter(player_index);
			if(!p) return 0;
			return p->db_id();
		}
		s_tbl_playerpitcher* p = pUser->get_tbl_playerpitcher(player_index);
		if(!p) return 0;
		return p->db_id();
	}



}//namespace nBASE_BALL
using namespace nBASE_BALL;


#define jGET_BASEBALL_OBJECT(user,better,pitcher,team)\
	s_tbl_user* user=pUser->get_tbl_user();\
	s_tbl_team* team=pUser->get_default_tbl_team();\
	s_tbl_playerbetter* better=pUser->get_default_tbl_playerbetter();\
	s_tbl_playerpitcher* pitcher=pUser->get_default_tbl_playerpitcher();\

/*
jRETURN_ret(true, user);
jRETURN_ret(true, team);
jRETURN_ret(true, pitcher);
jRETURN_ret(true, better);


jRETURN_ans_ug_error( user, ERR_SERVER_DATA);
jRETURN_ans_ug_error( team, ERR_COND_DEFAULT_TEAM);
jRETURN_ans_ug_error( pitcher, ERR_COND_DEFAULT_PITCHER);
jRETURN_ans_ug_error( better, ERR_COND_DEFAULT_BETTER);

*/


#endif // __jUser_base_header__
