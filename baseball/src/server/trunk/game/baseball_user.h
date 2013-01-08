#ifndef __BASEBALL_USER_H_E5A8U957__
#define __BASEBALL_USER_H_E5A8U957__

#include "game2/room_common.h" 

#include "protocol/ug.pb.h"
#include "proto.h"

#include "stdafx.h"

enum GAME_END_TYPE
{
	GAME_PLAYING = 0,	// 게임 진행 중
	NORMAL_END,			// 정상 게임 종료
	WITHOUT_ATTACK,		// 공격 없이 승리 확정!
	WINNING_HIT,		// 끝내기 안타로 승
	CALLED_GAME,		// 10점차 이상 차이( 마지막 라운드 )
	GIVE_UP				// 게임 중간에 한쪽이  close 한 경우( 네트워크 끊김 포함 )
};



namespace baseball 
{

class Room;

class User 
{
public:
	User (MSG::GameID game_id, Room* room);

	virtual ~User ();

	/// @brief 
	GameInfo& game_info();

	/// @brief DB ID. game_id와 동일
	Tbl_User_id_t db_id() const;

	s_game_play_info* get_s_game_play_info();

	/// @brief 레디 상태 반환
	bool is_ready() const;

	/// @brief 공격 가능 여부 반환
	bool is_attackable() const;

	// @brief 비정상 유저인지 체크. 강제종료대상 유저이다. 모든 보내오는 패킷 무시.
	bool is_illegal() const;

	/// @brief 유저 상태 정보 반환
	EUserGPS get_m_e_user_gps() const;

	/// @brief 유저 상태 정보 설정
	void set_m_e_user_gps(EUserGPS e);

	Room* room() const { return room_; }

	void reset_user_info();

	bool is_allow_rematch;

	bool check_breaking_ball_type(int32 breaking_ball_type);//내가 가지고 있는변화구?

	bool check_ball_focus(int32 ball_focus){return true;}//jTODO 멀?

#ifdef DEF__USE_req_timer_start
	s_req_timer_start m_s_req_timer_start;
	int m_iCount_req_timer_start;
#endif

	GameInfo* get_game_info()	{   return &game_info_;}
	nMOB::jPacketRecvTimeControl m_jPacketRecvTimeControl;

private:
	/// @brief 피망 플러스 게임 아이디
	MSG::GameID		game_id_;

	/// @brief 유저가 속한 방
	mutable Room*	room_;

	/// @brief 피망 플러스에서 오는 멤버 정보
    MemberInfo      member_info_;

	/// @brief 게임 정보
    GameInfo        game_info_;
};
	
} /* baseball */

namespace nBASE_BALL
{
	void make_random_better_hit(s_req_better_hit* rd);
	void make_random_pitcher_throw(s_req_pitcher_throw* rd);
}


#endif /* end of include guard: __BASEBALL_USER_H_E5A8U957__ */
