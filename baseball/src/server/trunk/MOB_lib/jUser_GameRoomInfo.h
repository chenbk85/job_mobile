

/* file : jUser_GameRoomInfo.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-06-01 16:24:18
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __jUser_GameRoomInfo_header__
#define __jUser_GameRoomInfo_header__
#pragma once

#include "header/jDefine_enum.h"

#define for_each_EUserGPS(X)\
	X(eUGPS_LOGOUT					,"//- 네트웍접속해제")\
	X(eUGPS_LOGIN					,"// -UserGate서버에접속-)")\
	X(eUGPS_DB_LOAD					,"// -UserGate서버에접속-)")\
	\
	X(eUGPS_x2ug_goto_main	,"메인화면")\
	\
	X(eUGPS_x2ug_goto_charactor_create,"캐릭생성창")\
	X(eUGPS_x2ug_goto_inventory,"인벤토리창")\
	\
	X(eUGPS_x2ug_goto_single,"싱글플레이상태")\
	X(eUGPS_SINGLEPLAY				,"//-싱글프레이중-")\
	\
	X(eUGPS_x2ug_goto_upgrade_pitcher,"강화-투수코치창")\
	X(eUGPS_x2ug_goto_upgrade_tranner,"강화-트레이너창")\
	X(eUGPS_x2ug_goto_upgrade_maestro,"강화-장인창")\
	X(eUGPS_x2ug_goto_etc_ativate,"강화-장외활동창")\
	\
	X(eUGPS_x2ug_goto_shop,"상점창")\
	X(eUGPS_x2ug_goto_team,"팀관리창")\
	X(eUGPS_x2ug_goto_rank,"랭킹창")\
	X(eUGPS_x2ug_goto_quest,"퀘스트창")\
	X(eUGPS_x2ug_goto_option,"옵션창")\
	X(eUGPS_x2ug_goto_tutorial,"튜토리얼모드")\
	\
	X(eUGPS_UserGateServer			,"//여기까지가 유저게이트서버에서의 상태")\
	X(eUGPS_x2ug_goto_match,"매치창(멀티플레이창)")\
	X(eUGPS_GAMEROOM				,"//BaseballServer에접속 대기방상태")\
	X(eUGPS_LABEL_GAME_NOT_QUIT		,"// ")\
	X(eUGPS_GAME_READY2				,"//x2bs_auto_match_ready2 레디 한 상태")\
	X(eUGPS_GAME_READY				,"//게임 레디 한 상태")\
	X(eUGPS_GAME_START				,"//게임시작")\
	X(eUGPS_GAME_ROUND_START		,"//")\
	X(eUGPS_GAME_BATTER_READY		,"//라운드시작후 타자가 칠준비가되었는지")\
	X(eUGPS_PITCHER_THROW			,"//투수가 공을 던졌다")\
	X(eUGPS_BETTER_HIT				,"//타자가 공을 쳤다")\
	X(eUGPS_BETTER_HIT_RESULT		,"//타자는 req_result_better_hit를 보냈고 투수는 ans_result_better_hit를 받았다.")\
	X(eUGPS_ATTACK_USER_CHANGED		,"//팀이 막 바꼈다.")\
	X(eUGPS_GAME_END				,"//게임을 모두 끝내고 게임종료패킷 ans_game_end 을 보냈다")\
	X(eUGPS_GAME_REMATCH			,"//게임을 모두 끝내고 req_rematch보낸상태 또는 rematch허락상태")\
	X(eUGPS_GAMEROOM_PRE_LEAVE		,"//로비로 갈려고 대기중인 상태-")\
	X(eUGPS_BS_USER_IS_ILLEGAL		,"//게임서버에 접속된 상태이지만 유저의 정보가 정상이 아님 강제종료대상")\
	X(eUGPS_BS_ABNORMAL_DISCONNECT	,"//해당 유저는 클라이언트가 비정상적인 TCP DISCONNECT상태이다.")\
	\
	X(eUGPS_x2ug_goto_friend_match,"프랜들리매치상태")\
	X(eUGPS_BaseballServer			,"//여기까지가 게임서버접속상태")\

jDEFINE_ENUM_CODE2(EUserGPS);


#define for_each_menu_window(FUNC)\
	FUNC(x2ug_goto_main)\
	FUNC(x2ug_goto_charactor_create)\
	FUNC(x2ug_goto_inventory)\
	FUNC(x2ug_goto_match)\
	FUNC(x2ug_goto_single)\
	FUNC(x2ug_goto_friend_match)\
	FUNC(x2ug_goto_upgrade_pitcher)\
	FUNC(x2ug_goto_upgrade_tranner)\
	FUNC(x2ug_goto_upgrade_maestro)\
	FUNC(x2ug_goto_etc_ativate)\
	FUNC(x2ug_goto_rank)\
	FUNC(x2ug_goto_quest)\
	FUNC(x2ug_goto_option)\
	FUNC(x2ug_goto_shop)\
	FUNC(x2ug_goto_team)\


namespace nBASE_BALL
{
	struct jUser_GameRoomInfo
	{
		GameRoomInfo	m_GameRoomInfo; // gameLogic.proto첨고 할것.
		void clear()
		{
			m_GameRoomInfo.Clear();
		}
		bool				is_auto_play(){ return m_GameRoomInfo.has_m_is_auto_play() && m_GameRoomInfo.m_is_auto_play();}
		int32				get_round_count(){ return m_GameRoomInfo.m_round_count();}
		Tbl_User_id_t		get_attack_uid(){ return m_GameRoomInfo.m_attack_user();}
		s_game_play_info* get_s_game_play_info_Other(Tbl_User_id_t db_id_me);//자신의 db_id로 상대방 정보를 가져옴.
		s_game_play_info* get_s_game_play_info(Tbl_User_id_t db_id/*,bool isCreate=false*/);
		s_game_play_info* at_s_game_play_info(int array_idx);
		s_tbl_result&		get_s_tbl_result(){ return *m_GameRoomInfo.mutable_m_result_game()->mutable_m_tbl_result();}
		template <class _Predicate> 
		void for_each_s_game_play_info(_Predicate &__pred) // __pred는 s_game_play_info* gpi를 인자로 받는다.
		{
			int iTotal=m_GameRoomInfo.m_game_play_info_size();
			for(int i=0; i< iTotal; ++i){__pred(m_GameRoomInfo.mutable_m_game_play_info(i));}
		}
		template <class _Predicate> 
		s_game_play_info* find_if_s_game_play_info(_Predicate &__pred) // __pred는 s_game_play_info* gpi를 인자로 받는다.
		{
			int iTotal=m_GameRoomInfo.m_game_play_info_size();
			for(int i=0; i< iTotal; ++i)
			{
				if( __pred(m_GameRoomInfo.mutable_m_game_play_info(i)) )
				{
					return m_GameRoomInfo.mutable_m_game_play_info(i);
				}
			}
			return 0;
		}

		bool delete_s_game_play_info(int64 db_id)
		{
			jLOG("PREV <delete_s_game_play_info> db_id = %lld, size=%d"
				,db_id ,m_GameRoomInfo.m_game_play_info_size());
			bool isFind=false;
			GameRoomInfo org;
			for(int i=0; i < m_GameRoomInfo.m_game_play_info_size() ; ++i)
			{
				jLOG("i=%d",i);
				s_game_play_info* p = at_s_game_play_info(i);
				if(p->m_tbl_user().db_id()==db_id) 
				{ 
					isFind=true;
					continue;
				}
				s_game_play_info* pNew = org.add_m_game_play_info();
				pNew->CopyFrom(*p);
			}
			jRETURN_ret(false, isFind);

			jLOG("<AFTER delete_s_game_play_info> db_id = %d",db_id ,m_GameRoomInfo.m_game_play_info_size());
			m_GameRoomInfo.clear_m_game_play_info();
			jvCHECK(org.m_game_play_info_size()<=2,"org.m_game_play_info_size() =%d",org.m_game_play_info_size());
			m_GameRoomInfo.mutable_m_game_play_info()->CopyFrom(org.m_game_play_info());
			
			return true;
		}

		void make_round_result( OUT s_result_round* pRR , IN EBatterHitType eType, IN ERunnerStateRound eRSR);//이번라운드에서 획득한 점수를 리턴.

		typedef score_t score_list_value_t; 
		typedef std::map<Tbl_User_id_t,score_t> 	score_list_t; 
		typedef score_list_t::iterator score_list_it;
		typedef score_list_t::value_type score_list_vt; 
		typedef std::pair<score_list_it, bool>	score_list_pt;

		void get_score(OUT score_list_t& score)const;  //현재 스코어.

		void print_score();
		void reset_user_info();//경기재시작시 플레이데이타 초기화.
	
	};



#	define jLAMDA_set_EUserGPS(X,Z) Z(EUserGPS , eVal)
	jLAMDA_for_each(set_EUserGPS,s_game_play_info*)
	{
		it->set_m_e_user_gps(eVal);
	}
	jLAMDA_end();

	jLAMDA_for_each0(print_EUserGPS,s_game_play_info*)
	{
		jLOG("uid=%d, EUserGPS=%s", it->m_tbl_user().db_id() , ToString((EUserGPS)it->m_e_user_gps()) );
	}
	jLAMDA_end();

#	define jLAMDA_find_EUserGPS(X,Z) Z(EUserGPS , eVal)
	jLAMDA_find_if(find_EUserGPS,s_game_play_info*)
	{
		//jLOG("uid=%d, EUserGPS= %s : %d ,%d ", it->m_tbl_user().db_id() , ToString((EUserGPS)it->m_e_user_gps()),it->m_e_user_gps() , eVal);
		return it->m_e_user_gps()!=eVal;
	}
	jLAMDA_end();

	inline void jUser_GameRoomInfo::reset_user_info()//경기 재시작 시 플레이데이타 초기화.
	{
		m_GameRoomInfo.set_m_attack_user(0);
		m_GameRoomInfo.set_m_round_count(0);
		m_GameRoomInfo.clear_m_round_count();
		m_GameRoomInfo.mutable_m_result_game()->Clear();
		m_GameRoomInfo.set_m_is_auto_play(false);
	
		set_EUserGPS func(eUGPS_GAMEROOM);
		this->for_each_s_game_play_info(func);

	}

	inline s_game_play_info* jUser_GameRoomInfo::at_s_game_play_info(int index)
	{
		if(index<0 || index>=m_GameRoomInfo.m_game_play_info_size()) return 0;
		return m_GameRoomInfo.mutable_m_game_play_info(index);
	}

	inline s_game_play_info* jUser_GameRoomInfo::get_s_game_play_info(Tbl_User_id_t db_id)
	{
		s_game_play_info* gpi=0;
		for(int i=0; i< m_GameRoomInfo.m_game_play_info_size() ; ++i)
		{
			s_game_play_info* p = m_GameRoomInfo.mutable_m_game_play_info(i);
			if(p->m_tbl_user().db_id() != db_id) continue;
			gpi = p;
			break;
		}
		if(!gpi ) 
		{
			gpi = m_GameRoomInfo.add_m_game_play_info();
		}
		return gpi;
	}
	inline void jUser_GameRoomInfo::get_score(OUT jUser_GameRoomInfo::score_list_t& score)const  //현재 스코어.
	{
		int32 iSize = m_GameRoomInfo.m_result_round_size();
		for(int i=0; i<iSize ; ++i)
		{
			const s_tbl_roundresult& rr = m_GameRoomInfo.m_result_round(i).m_tbl_roundresult();
			if(!score.count(rr.uid_attack()))
			{
				score[rr.uid_attack()]=rr.score();
			}
			else
			{
				score[rr.uid_attack()] += rr.score();
			}
			jLOG("%d %d %d",i , rr.uid_attack(), rr.score());
		}
		//jCHECK(score.size()==DEF_i_MAX_PLAYING_USER);
	}

	////이번라운드에서 획득한 점수를 리턴.
	inline void jUser_GameRoomInfo::make_round_result( OUT s_result_round* pRR 
		, IN EBatterHitType eHitType, IN ERunnerStateRound eRSR_current)
	{
		std::pair<score_t,base_runner_state_t> p = calc_base_runner_count(eRSR_current, eHitType);

		s_tbl_roundresult &rr = *pRR->mutable_m_tbl_roundresult();		// 라운드 결과
		nProtoHelper::message_init(rr);
		rr.set_hit_type(eHitType);
		rr.set_score(p.first);						// _SIMPLE_MODIFY	: 현재 라운드에서 획득한 점수
		
		jLOG("[] p.first : %d rr.score() : %d , eHitType=%d , eRSR_current=%d"
			, p.first, rr.score(), eHitType , eRSR_current);

		rr.set_base_runner_state(eRSR_current);	// 치기전의 주자 `상태.
		rr.set_round_number(this->m_GameRoomInfo.m_round_count());
		rr.set_uid_attack(this->m_GameRoomInfo.m_attack_user());


		nBASE_BALL::print_s_result_round(eRSR_current, p, eHitType);
		
		//return p.first;
	}


	inline s_game_play_info* jUser_GameRoomInfo::get_s_game_play_info_Other(Tbl_User_id_t db_id_me)//자신의 db_id로 상대방 정보를 가져옴.
	{
		for (int i = 0; i < m_GameRoomInfo.m_game_play_info_size(); ++i)
		{
			s_game_play_info* p = m_GameRoomInfo.mutable_m_game_play_info(i);
			if (db_id_me == p->m_tbl_user().db_id()) continue;
			return p;
		}
		return NULL;
	}

	inline void jUser_GameRoomInfo::print_score()
	{
		score_list_t score_list;
		get_score(score_list);
		score_list_it it = score_list.begin() , ie= score_list.end();
		for(;it!=ie;++it)
		{
			jLOG("%d = %d",it->first,it->second);
		}

		int32 iSize = m_GameRoomInfo.m_result_round_size();
		string str;
		for(int i=0; i<iSize ; ++i)
		{
			const s_tbl_roundresult& rr = m_GameRoomInfo.m_result_round(i).m_tbl_roundresult();
			std::bitset<3> state_bit(rr.base_runner_state());
			boost::format fmt = boost::format("uid(%1%) score(%3%) : %4% : %2%") 
				% rr.uid_attack() % nExcelUtil::ToString((EBatterHitType)rr.hit_type()) % rr.score() % state_bit.to_string();
			jLOG("%s",boost::str(fmt).c_str());
		}
	}

}//namespace nBASE_BALL



#endif // __jUser_GameRoomInfo_header__
