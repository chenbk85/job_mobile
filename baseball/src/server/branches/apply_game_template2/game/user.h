/* file : SAMPLE_Room.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-10 18:43:19
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __POKER_USER_H__
#define __POKER_USER_H__

#include "game/game.h"

#include "protocol/ug.pb.h"

#include "proto.h"


#include "stdafx.h"
class Room;
#define DEF__USE_req_timer_start

class User: 
  public MSG::Session
{
public:
    User(int id);

    virtual ~User();

    // 사용자 접속이 되면 강제적으로 설정된다
    virtual void set_info(const std::string& info);

    // 사용자 정보를 얻어가야 할 때 호출된다
    void get_info(GameUserInfo& info);

    const GameInfo& get_game_inf()
    {
        return game_info_;
    }
	template<typename T> 
	void send(const T& msg)
	{
	    GAnsProtocol sendMsg;
		sendMsg.set_type(GAnsProtocol::GLANSGAMEPROTOCOL);
		msg.SerializeToString(sendMsg.mutable_ansgameprotocol());
		MSG::Session::send(sendMsg);
	}

protected:
    virtual void on_connect();
	virtual bool on_database(const AnsDB&);

    virtual void on_disconnect(const char* reason, int code);

    virtual bool on_game_enter(const GReqGameEnter& enter);

    virtual bool on_game_leave(const GReqGameLeave& leave);

    virtual bool on_plug(const GReqPlug& plug);

    virtual bool on_detach(const GReqDetach& detach);
	virtual bool on_joined(const GAnsGameEnter& enter);

    virtual bool on_game_protocol(const std::string& message);

//private:
public:
    // 피망 플러스에서 오는 맴버 정보
    MemberInfo      member_info_;
    // 게임에 필요한 게임 정보
    GameInfo        game_info_;
	Room*           room_;

	s_game_play_info  *m_temp_s_game_play_info;// User::set_info호출시 room_이 NULL이기 때문에 임시로 만듬.
	s_game_play_info* get_s_game_play_info();
	bool is_ready()			{ return get_m_e_user_gps() >=eUGPS_GAME_READY;}
	bool is_attackable();
	Tbl_User_id_t db_id(){ return id();}

public:
	void set_room(Room *p);
	GameInfo* get_game_info()	{   return &game_info_;}

public:
#ifdef DEF__USE_req_timer_start
	s_req_timer_start m_s_req_timer_start;
	int m_iCount_req_timer_start;
#endif

	bool check_breaking_ball_type(int32 breaking_ball_type);//내가 가지고 있는변화구?
	bool check_ball_focus(int32 ball_focus){return true;}//jTODO 멀?

	EUserGPS get_m_e_user_gps();
	void set_m_e_user_gps(EUserGPS e);
	bool is_illegal();// 비정상 유저인지 체크. 강제종료대상 유저이다. 모든 보내오는 패킷 무시.

	void reset_user_info();// 재경기 시작할때 초기화 해야할 데이타들.

	bool is_allow_rematch;



};




namespace nBASE_BALL
{
	void make_random_better_hit(s_req_better_hit* rd);
	void make_random_pitcher_throw(s_req_pitcher_throw* rd);
}

#endif 
