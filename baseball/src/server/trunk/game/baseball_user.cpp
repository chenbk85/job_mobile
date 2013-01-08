#include "protocol/ug.pb.h"
#include "proto.h"

#include "stdafx.h" 

#include "baseball_user.h" 
#include "baseball_room.h"

namespace baseball 
{

User::User(MSG::GameID game_id, Room* room) : 
#ifdef DEF__USE_req_timer_start
	m_iCount_req_timer_start(0), 
#endif
	game_id_(game_id), room_(room)
{
}

User::~User()
{
}

GameInfo& 
User::game_info()
{
	return game_info_;
}

Tbl_User_id_t 
User::db_id() const
{
	return game_id_;
}

s_game_play_info* 
User::get_s_game_play_info()
{
	return room_->get_s_game_play_info(db_id());
}

bool 
User::is_ready() const
{
	return get_m_e_user_gps() >=eUGPS_GAME_READY
		&& get_m_e_user_gps()<eUGPS_GAME_END; 
}

bool 
User::is_attackable() const
{
	return room_ && db_id() == room_->get_attack_uid();
}

bool 
User::is_illegal() const
{
	jRETURN_ret(true,room_);
	s_game_play_info *gpi = room_->get_s_game_play_info(db_id());
	jRETURN_ret(true,gpi);
	return gpi->m_e_user_gps() == eUGPS_BS_USER_IS_ILLEGAL;
}

EUserGPS 
User::get_m_e_user_gps() const
{
	jRETURN_ret(eUGPS_BS_USER_IS_ILLEGAL,room_);
	s_game_play_info *gpi = room_->get_s_game_play_info(db_id());
	jRETURN_ret(eUGPS_BS_USER_IS_ILLEGAL,gpi);
	return (EUserGPS)gpi->m_e_user_gps();
}

void 
User::set_m_e_user_gps(EUserGPS e)
{
	Room* pRoom = room_;
	jRETURN(room_);
	s_game_play_info *gpi = room_->get_s_game_play_info(db_id());
	jRETURN_ERROR_ROOM(gpi != NULL  ,ERR_SERVER_DATA_ROOM_NULL);
	gpi->set_m_e_user_gps(e);
}

void 
User::reset_user_info()
{
	is_allow_rematch=false;
}

bool 
User::check_breaking_ball_type(int32 breaking_ball_type)
{
	//jTODO 자신이 가지고 있는 변화구 스킬인지 체크.
	return breaking_ball_type > eBEGIN_EPlayerBreakingBall && breaking_ball_type < eEND_EPlayerBreakingBall;
}
	
} /* baseball */

namespace nBASE_BALL
{
	void make_random_better_hit(s_req_better_hit* rd)
	{
		//jTODO
		s_better_hit_info info;
		// s_better_hit_info_verify verify;

		rd->mutable_info()->CopyFrom(info);
		// rd->mutable_verify()->CopyFrom(verify);
	}
	void make_random_pitcher_throw(s_req_pitcher_throw* rd)
	{
		//jTODO
		s_pitcher_throw_info info;
		// s_pitcher_throw_info_verify verify;

		rd->mutable_info()->CopyFrom(info);
		// rd->mutable_verify()->CopyFrom(verify);
	}

}

