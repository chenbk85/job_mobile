/* file : SAMPLE_Room.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-10 18:43:19
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __POKER_ROOM_H__
#define __POKER_ROOM_H__
#include <vector>

#include "game/game.h"

#include "proto.h"


#include "user.h"
#include "excel/db_uid_type.h"
#include "excel/code/table_type.h"
#include "excel/code/table_const_excel_enum.h"

typedef boost::asio::deadline_timer MOB_Timer;
typedef boost::function<void()> MOB_Timer_handler_t;

#define jFOR_Room(it) Sessions sessions_;get_sessions(sessions_);for(Sessions::iterator it = sessions_.begin(); it != sessions_.end(); it++)
#define INVALID_TIMER 0xffffffff


class Room: 
    public MSG::Room
	,public jUser_GameRoomInfo
{
public:
	jLIST_TYPEDEF_map(string ,MOB_Timer*,m_mapMOB_Timer);
    Room(int id, int category, int channel);

    virtual ~Room();

public:
    virtual void on_create();

    virtual void on_destroy();

    virtual bool on_join(MSG::Session* session);

    virtual int on_leave(MSG::Session* session, bool kick);

    virtual void get_info(std::string& info);

public: 
	template <class _Predicate> 
	void for_each_User(_Predicate __pred)
	{
		jFOR_Room(it){	__pred(dynamic_cast<User*>(*it));}
	}

	//#--------------------------------------------------------------------------
	// Baseball Server -> Cilent 게임 패킷 송신 루틴
	//#--------------------------------------------------------------------------
#define _make_bs2x_msg(sd,sendMsg)\
	GAnsProtocol sd;\
	sd.set_type(GAnsProtocol::GLANSGAMEPROTOCOL);\
	sendMsg.SerializeToString(sd.mutable_ansgameprotocol());\

	void send_all(const BaseballServer_Client& sendMsg)
	{
		_make_bs2x_msg(sd,sendMsg);
		MSG::Room::send_all(sd);
	}
	void send_all_except_me(const BaseballServer_Client& sendMsg,User* me)
	{
		_make_bs2x_msg(sd,sendMsg);
		MSG::Room::send_all_except_me(sd, (MSG::Session*)me);
	}
	void send(int id, const BaseballServer_Client& sendMsg)
	{
		_make_bs2x_msg(sd,sendMsg);
		MSG::Room::send(id, sd); 
	}

	//#--------------------------------------------------------------------------
	// Baseball Server -> UserGate Server
	//#--------------------------------------------------------------------------
private:
	GAnsProtocol& _make_bs2ug_msg(IN const BaseballServer_UserGateServer& in , OUT GAnsProtocol& out)
	{
		out.set_type(GAnsProtocol::GDBREQ);
		ReqDB* db = out.mutable_reqdb();
		db->set_seq(IS_BS2UG_PACKET);
		db->set_query("BaseballServer_UserGateServer");
		in.SerializeToString(db->mutable_options());
		return out;
	}
public:
	void send_all_to_ug(const BaseballServer_UserGateServer& sendMsg)
	{
		GAnsProtocol sd; MSG::Room::send_all(_make_bs2ug_msg(IN sendMsg,OUT sd));
	}
	void send_all_except_me_to_ug(const BaseballServer_UserGateServer& sendMsg,User* me)
	{
		GAnsProtocol sd; MSG::Room::send_all_except_me(_make_bs2ug_msg(IN sendMsg,OUT sd), (MSG::Session*)me);
	}
	void send_to_ug(int id, const BaseballServer_UserGateServer& sendMsg)
	{
		GAnsProtocol sd; MSG::Room::send(id, _make_bs2ug_msg(IN sendMsg,OUT sd)); 
	}
	
	bool is_all_user_ready();
	bool is_full_user();

	User* find_user(Tbl_User_id_t uid);
	User* get_other_user(Tbl_User_id_t uid);
	User* get_user(int iOrder);
	User* get_current_pitcher();//현제라운드의 투수 유저.
	User* get_current_better(); // 현제 라운드의 타자유저.

	void send_ans_pitcher_throw(const s_req_pitcher_throw& rd,bool is_auto);
	void send_ans_team_match_ready(Tbl_User_id_t uid);

	game_money_t calc_game_money(EBatterHitType e, score_t curr_score,bool isWin);

	void Timer_Create(tcstr szTimer,MOB_Timer_handler_t& func,int iTime);
	void Timer_Delete(tcstr szTimer);
private: 
	void _Timer_Clear();

public:
	//#--------------------------------------------------------------------------
	// Room's memeber variable
	//#--------------------------------------------------------------------------
	s_req_pitcher_throw m_req_pitcher_throw;
	s_req_better_hit	m_req_better_hit;
	
	void calc_game_result();
	void give_exp_to_team(Tbl_User_id_t uid, exp_t exp);//해당 유저의 팀선수들에게 경험치지급.

	int64 m_timer_game_start;//게임시작시간.


	//#--------------------------------------------------------------------------
	// 랜덤 주자배치처리.
	//#--------------------------------------------------------------------------
	Sys_Runner_State_id_t m_sid_RunnerState[2];
	int m_sid_RunnerState_index;
	Sys_Runner_State_id_t Get_Curr_RSR()
	{
		int idx = m_sid_RunnerState_index; 
		if(idx>1 || idx<0) idx = 0; 
		return m_sid_RunnerState[idx];
	}
	//#--------------------------------------------------------------------------
	// 라운드별 공수 체인지.
	//#--------------------------------------------------------------------------
	round_t m_i_TOTAL_ROUND;
	round_t m_i_ATTACK_CHANGE_ROUND;
	round_t m_i_CheckRound;

	void reset_user_info(); // 게임플레이정보 초기화작업.
	Tbl_User_id_t reset_user_info_for_gamestart(); // 경기시작 & 재경기시작전에 초기화작업(공수선택)
};


//--------------------------------------------------------------------------------------------------------------
// 인자 설명:		 TIMER_CREATE_Room(Room* pRoom , 타이머_함수명 , 타이머_시간 , Room* pRoom , param1 ,param2);
//					 param1 ,param2는 필요할때만 기입.
// 타이머 함수원형 : void 타이머_함수명(Room* pRoom , int param1, string param2);
#define TIMER_CREATE_Room(pRoom,FUNC,TIME_SEC,...)\
{\
	/*extern void FUNC(Room*);*/\
	MOB_Timer_handler_t func = boost::bind(FUNC,__VA_ARGS__);\
	pRoom->Timer_Create(jS(FUNC),func,TIME_SEC);\
}\


void timer_job_ans_game_round_start(Room* pRoom);
void timer_job_ans_game_start(Room* pRoom);

#endif //__POKER_ROOM_H__

