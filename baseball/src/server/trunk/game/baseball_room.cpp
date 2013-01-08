#include <boost/function.hpp> 

#include "baseball_user.h"
#include "proto.h"
#include "stdafx.h"
#include "baseball_room.h" 
#include "baseball_room_list.h" 

namespace 
{

baseball::RoomList g_mapRoom;

}



#define jPARSE_PROTO_MESSAGE_UG2BS_DECLARE(DOMAIN,NAME,ORDER)\
	void CB_##DOMAIN(baseball::User* ,const s_##NAME&);\

for_each_UserGateServer_BaseballServer(jPARSE_PROTO_MESSAGE_UG2BS_DECLARE);

void timer_job_req_timer_start(baseball::User* pUser);

namespace baseball 
{

void time_out_req_pitcher_throw(baseball::Room* pRoom); 
void time_out_req_better_hit(baseball::Room* pRoom);
void timer_user_goto_lobby(baseball::Room* pRoom,Tbl_User_id_t uid);
void timer_TIME_GAME_ROUND_TEAMCHANGE(baseball::Room* pRoom);



Sys_Runner_State_id_t 
_get_random_Sys_Runner_State_id(vector<Sys_Runner_State*> &vec )
{
	int idx = nMOB::random_my(0,vec.size()-1);
	jRETURN_ret(1, idx>=0 && ((size_t)idx)<vec.size());
	Sys_Runner_State* pSys = vec[idx];
	jRETURN_ret(1, pSys);
	return pSys->Get_index();
}

ERunnerStateRound 
get_round_state(round_t iTeamRoundCount, Sys_Runner_State_id_t sid)
{
	Sys_Runner_State* pSys = jCSV(Sys_Runner_State).Index(sid);
	jRETURN_ret(eERSR_2,pSys);
	const int MAX_ROUND = 9;
	iTeamRoundCount %=MAX_ROUND;
	jCHECK(iTeamRoundCount>=0 && iTeamRoundCount<MAX_ROUND);

	if(iTeamRoundCount<0)
	{
		iTeamRoundCount=0;
		LOG_WARNING("iTeamRoundCount<0");
	}

	switch(iTeamRoundCount+1)
	{
	case 1: return pSys->Get_state_1r();
	case 2: return pSys->Get_state_2r();
	case 3: return pSys->Get_state_3r();
	case 4: return pSys->Get_state_4r();
	case 5: return pSys->Get_state_5r();
	case 6: return pSys->Get_state_6r();
	case 7: return pSys->Get_state_7r();
	case 8: return pSys->Get_state_8r();
	case 9: return pSys->Get_state_9r();
	default:
		{
			LOG_WARNING("iTeamRoundCount= " << iTeamRoundCount+1 << "  -> over then 9");
			return eERSR_2;
		}
	}
}


void print_Sys_Runner_State(Sys_Runner_State_id_t sid)
{
	Sys_Runner_State* pSys = jCSV(Sys_Runner_State).Index(sid);

#define _print_SRS(NUMBER)	\
	LOG_DEBUG( NUMBER << " = " << pSys->_jJOIN_3(Get_state_,NUMBER,r)() << ", " << ToString(pSys->_jJOIN_3(Get_state_,NUMBER,r)()) );

	for_each_123456789(_print_SRS);

	LOG_DEBUG("------");
}


void 
timer_job_ans_game_start(baseball::Room* pRoom)
{
	jRETURN_ERROR_ROOM(pRoom!=NULL,ERR_SERVER_DATA_ROOM_NULL);
	jRETURN_ERROR_ROOM(pRoom->is_full_user(),ERR_SERVER_DATA_ROOM_NULL);
	jRETURN_ERROR_ROOM(pRoom->is_all_user_ready(),ERR_SERVER_DATA_ROOM_NULL);

	pRoom->reset_user_info();
	Tbl_User_id_t uid_attack = pRoom->get_attack_user();

	// _AUTO_FUNC : 리매치 신청만 와도 자동 로비 입장 diable !
	LOG_DEBUG("[auto_goto_lobby] TIMER OFF!");
	pRoom->remove_timer_wrapper(baseball::Room::E_TIMER_AUTO_GOTO_LOBBY);

	jMAKE_MSG_BS2X(sendMsg,sd,ans_game_start);

	pRoom->SetGameEndType(GAME_PLAYING);

	set_EUserGPS func(eUGPS_GAME_START);
	pRoom->for_each_s_game_play_info(func);

	sd->set_attack_user(uid_attack);
	pRoom->send_all(sendMsg);

	// pRoom->m_isNotJoin_ = true;
	pRoom->SetisNotJoin( true );	// 입장 불가 flag 초기화 
	pRoom->SetGame_End_DB( false );	// 게임 DB 게임 종료 초기화
	pRoom->m_GameRoomInfo.set_m_round_count(0);
	pRoom->m_timer_game_start = time(0);

	//#--------------------------------------------------------------------------
	// 주자 랜덤배치 계산.
	//#--------------------------------------------------------------------------
	// ERunnerStateType eType = (ERunnerStateType)nMOB::random_my(eBEGIN_ERunnerStateType+1, eEND_ERunnerStateType-1);
	ERunnerStateType eType = (ERunnerStateType)nMOB::random_my(eBEGIN_ERunnerStateType+1, eEND_ERunnerStateType);
	if(eType>=eEND_ERunnerStateType)
	{
		eType = eERST_C;
	}

	jCHECK(IsValid(eType));

	vector<Sys_Runner_State*> &vec = jCSV(Sys_Runner_State).m_INDEX_category[eType];
	jvRETURN(vec.size(), "eType = %s , jCSV(Sys_Runner_State).size=%d", ToString(eType), jCSV(Sys_Runner_State).size());

	pRoom->m_sid_RunnerState[uid_attack] = _get_random_Sys_Runner_State_id(vec);
	s_game_play_info* gpi_other = pRoom->get_s_game_play_info_Other(uid_attack);
	jRETURN_ERROR_ROOM(gpi_other!=NULL , ERR_SERVER_DATA_ROOM_NULL);

	Tbl_User_id_t uid_other = gpi_other->m_tbl_user().db_id();
	jCHECK(uid_other != uid_attack );

	pRoom->m_sid_RunnerState[uid_other] = _get_random_Sys_Runner_State_id(vec);

	LOG_DEBUG("ERunnerStateType= " << ToString(eType) << 
			", Sys_Runner_State_id uid_attack(" << uid_attack << ")= " << pRoom->m_sid_RunnerState[uid_attack] <<
		   	", uid_other(" << uid_other << ")=" << pRoom->m_sid_RunnerState[uid_other]);

	print_Sys_Runner_State(pRoom->m_sid_RunnerState[uid_attack]);
	print_Sys_Runner_State(pRoom->m_sid_RunnerState[uid_other]);

	// 비정상 종료에 대비한 elp_point 계산
	s_game_play_info* gpi_me = pRoom->get_s_game_play_info(uid_attack);

	if( gpi_other != NULL && gpi_me != NULL )
	{
		LOG_DEBUG("abnormalEnd save");
		pRoom->calc_abnormal_elo(gpi_me->mutable_m_tbl_user(), gpi_other->mutable_m_tbl_user());
	}
	else
		LOG_WARNING("abnormalEnd can not save");
	
	pRoom->add_timer_wrapper(baseball::Room::E_TIMER_JOB_ANS_GAME_ROUND_START,
			nG::i_TIME_ALL_PLAYER_READY->Get_int(),
			timer_job_ans_game_round_start);
}


void 
timer_job_ans_game_round_start(baseball::Room* pRoom)
{
	jRETURN_ERROR_ROOM(pRoom!=NULL,ERR_SERVER_DATA_ROOM_NULL);
	jRETURN_ERROR_ROOM(pRoom->is_full_user(),ERR_SERVER_DATA_ROOM_NULL);
	jRETURN_ERROR_ROOM(pRoom->is_all_user_ready(),ERR_SERVER_DATA_ROOM_NULL);

	jMAKE_MSG_BS2X(sendMsg,sd,ans_game_round_start);
	sd->set_round(pRoom->get_round_count());

	//test_RSR();

	jCHECK(nG::i_ATTACK_CHANGE_ROUND->Get_int()==3);

	round_t iTeamRoundCount = nBASE_BALL::curr_team_round(pRoom->get_round_count()\
						,nG::i_ATTACK_CHANGE_ROUND->Get_int());

	jCHECK( iTeamRoundCount >= 0 && iTeamRoundCount < nG::i_TOTAL_ROUND->Get_int() );

	ERunnerStateRound eRSType = get_round_state(iTeamRoundCount, pRoom->Get_Curr_RSR() );

	sd->set_runner_state(eRSType);
	pRoom->send_all(sendMsg);
	
	// LOG_DEBUG("[iTeamRoundCount]	: iTeamRoundCount = " << iTeamRoundCount );
	// LOG_DEBUG("[Curr_RSR]	: Curr_RSR = " << pRoom->Get_Curr_RSR() );
	LOG_DEBUG("nsend			: ans_game_round_start : runner state= " << ToString(eRSType));
	
	set_EUserGPS func(eUGPS_GAME_ROUND_START);
	pRoom->for_each_s_game_play_info(func);

#ifdef SERVER_AUTO_PLAY
	pRoom->add_timer_wrapper(baseball::Room::E_TIME_OUT_REQ_PITCHER_THROW,
			nG::i_TIME_ALL_PLAYER_READY->Get_int(),
			time_out_req_pitcher_throw);
#endif

}

Room::Room() :
	m_timer_game_start(0)
{ 
}

Room::~Room()
{
}

void        
Room::on_create() 
{
	LOG_DEBUG("create room # " << id() );
	m_GameRoomInfo.Clear();
	m_GameRoomInfo.set_room_id(id());
	Room::reset_user_info();

	g_mapRoom.insert(id(), this);

	//초기 세팅할것
	jFUNC_LOG2("Room",id());

	// 방입장 제한 요소
	SetisNotJoin( false );
}

void        
Room::on_destroy()
{
	g_mapRoom.erase(id());
	jFUNC_LOG2("Room",id());
	LOG_DEBUG("destroy room #" << id() );
	m_GameRoomInfo.Clear();
}

bool		
Room::on_join(MSG::GameID game_id, const std::string& room_user_info, std::string& room_info, MSG::KICK_TYPE& kick_type, std::string& leave_info) 
{ 
	LOG_DEBUG("user_.size() = " << user_count());

	//들어온 유저가 최대인원(2)보다 많으면 false리턴하여 접속실패보냄.
	kick_type = MSG::PURGE;	
	jRETURN_ret(false,user_count() <= ((size_t)DEF_i_MAX_PLAYING_USER) );
	jRETURN_ret(false,m_GameRoomInfo.m_game_play_info_size() <= (DEF_i_MAX_PLAYING_USER) );

	insert_user_(game_id);
	s_game_play_info* p = get_s_game_play_info(game_id);

	if (p)
	{
		p->ParseFromString(room_user_info);
		// 타자/투수 인덱스 초기화
		p->set_m_batter_sid(-1);
		p->set_m_pitcher_sid(-1);

		LOG_DEBUG("join uid  = " << game_id );
		LOG_DEBUG("m_batter_sid  = " << p->m_batter_sid());
		LOG_DEBUG("m_pitcher_sid  = " << p->m_pitcher_sid());
	}

	if (1 == user_count()) 
	{
		m_first_attack_user = game_id;
		LOG_DEBUG(" on_join   First User  = " << game_id );
		m_GameRoomInfo.set_m_attack_user(game_id);
		m_GameRoomInfo.set_m_baseball_park(nMOB::make_random());
		SetGameEndType(GAME_PLAYING);			// 게임 종료 타입 초기화
	}	
	else// if(0 == user_count() )
	{
		if ( GetisNotJoin() == true )
		{
			LOG_WARNING("on_join room stat is game_start :  uid= " << game_id );
			return false;
		}

		if (nG::b_IS_FIRST_ATTACK_USER_IS_RANDOM->Get_bool())
		{
			int idx = nMOB::make_random() % DEF_i_MAX_PLAYING_USER;
			if(idx==1)//랜덤이 두번째유저면.
			{
				m_first_attack_user = game_id;
				m_GameRoomInfo.set_m_attack_user(game_id);
			}
		}

		//#--------------------------------------------------------------------------
		// 내가 들어왔기때문에 방의 다른모든사람들에게 내정보를 알리자.
		//#--------------------------------------------------------------------------
		jMAKE_MSG_BS2X(sendMsg,sd,ans_join_room);
		sd->mutable_gri()->CopyFrom(m_GameRoomInfo);
		send_all_except_me(sendMsg, game_id);
		LOG_DEBUG("on_join   Second User  = " << game_id );

	}

	jCHECK(m_GameRoomInfo.m_game_play_info_size()<=2);

	nProtoHelper::message_print(m_GameRoomInfo);

	m_GameRoomInfo.SerializeToString(&room_info);// 룸 정보를 채워서 패킷을 만들어 전달한다

	return true; 
}

void        
Room::on_leave(MSG::GameID game_id, MSG::KICK_TYPE reason, const std::string& leave_info)
{
	jFUNC_LOG2("Room",id());

	// 사용자가 게임에서 빠저나갈때의 처리
	reason = MSG::EXIT_RESERVATION;

	/// user.cpp의 on_disconnect 로직을 옮겨옴
	LOG_DEBUG("uid = " << game_id);
	LOG_DEBUG("reason = " << reason);

	// game_id : loser 처리( 게임 중 일때만 )
	User* pOtherUser = get_other_user(game_id);

	if(pOtherUser)//방에 누군가 남은 사람이 있다면.
	{
		// pOtherUser : winner 처리( 게임 중  일때만 )
		LOG_DEBUG("other uid = " << pOtherUser->db_id() );

		EUserGPS e = (EUserGPS)pOtherUser->get_m_e_user_gps() ;
		LOG_DEBUG("OtherUser state = " << ::ToString(e));
		
		if (pOtherUser->get_m_e_user_gps() >= eUGPS_GAME_BATTER_READY && 
		pOtherUser->get_m_e_user_gps() < eUGPS_GAME_END)
		{
			LOG_DEBUG("remain user id = " << pOtherUser->db_id() );
			abnormalGameEnd(this, pOtherUser->db_id());
		}
		kick_out(pOtherUser->db_id(), MSG::EXIT_RESERVATION, "OTHER_USER_EIXT");	// 일단 로비로 보냄
	}
	delete_user_(game_id);

	jCHECK(delete_s_game_play_info(game_id));//game_id == db_id , pp_id
	jCHECK(m_GameRoomInfo.m_game_play_info_size()<=2);

	nProtoHelper::message_print(m_GameRoomInfo);

	/// on_disconnect 로직 완료
}

// 비정상 게임 종료 처리
void 
Room::abnormalGameEnd(baseball::Room* pRoom, int64 winner)
{
	User* pWinner = get_other_user(winner);

	if(pWinner == NULL)
	{
		LOG_WARNING("there is no win_uid = " << winner);
		return ;
	}

	pRoom->abnormal_calc_game_result(winner);

	s_result_game* rg = pRoom->m_GameRoomInfo.mutable_m_result_game();
	{
		//jMAKE_MSG_BS2UG(sendMsg,sd,bs2ug_game_end);
		BaseballServer_UserGateServer sendMsg;
		sendMsg.set_type(::BaseballServer_UserGateServer_Type_bs2ug_game_end);
		s_bs2ug_game_end* sd = sendMsg.mutable_m_bs2ug_game_end();

		LOG_DEBUG("abnormal game end -> bs2ug_game_end" );

		sd->mutable_rg()->CopyFrom(*rg);
		*sd->mutable_rr() = pRoom->m_GameRoomInfo.m_result_round();
		sd->set_is_better(true);
		sd->set_end_type(GIVE_UP);
		pRoom->send_to_ug(winner, sendMsg);
		
		sd->set_is_better(false);
		pRoom->send_all_except_me_to_ug(sendMsg, winner);

		LOG_DEBUG("end_type = " << sd->has_end_type());
	}
}

void
Room::on_detach(MSG::GameID game_id)
{
	LOG_INFO("uid = " << game_id);
	std::cerr << "on_detach game_id = "<<  game_id << std::endl;

    // 사용자 회선이 잠시 떨어져 나감
	kick_out(game_id, MSG::EXIT_RESERVATION, "");
}

void
Room::on_plug(MSG::GameID game_id)
{
	LOG_INFO(" uid = " << game_id);

    // 사용자 회선이 다시 돌아옴
	kick_out(game_id, MSG::EXIT_RESERVATION, "");
}

void
Room::on_game_protocol(MSG::GameID game_id, const std::string& message)
{
	Room* pRoom = this;
	User* pUser = find_user(game_id);

	jRETURN_ERROR_ROOM(NULL != pUser,ERR_SERVER_DATA_ROOM_NULL);

    // 클라이언트에서 전송되는 게임에 관련된 메시지가 들어있다
    Client_BaseballServer request;

    request.ParseFromString(message);

	//std::cout << endl << __FUNCTION__ << " : type = "  << request.type() << endl;

	bool isRepeat = pUser->m_jPacketRecvTimeControl.is_repeated(request.type()) ;
	if(isRepeat)
	{
		LOG_WARNING("request.type() = " << request.type());
	}
	jRETURN_ERROR(!isRepeat , ERR_jPacketRecvTimeControl);

    switch (request.type())
    {
#	define jPARSE_PROTO_MESSAGE_X2BS(DOMAIN,NAME,ORDER)\
	case _jJOIN_3(DOMAIN,_Type_,NAME):\
	{\
		LOG_DEBUG("\n\nRECV>"  #DOMAIN  "::" #NAME " : " << game_id << "\n\n");\
		void CB_Client_BaseballServer(baseball::User* pUser, const s_##NAME&);\
		CB_Client_BaseballServer(pUser,request.m_##NAME());\
		break;\
	}\

	for_each_Client_BaseballServer(jPARSE_PROTO_MESSAGE_X2BS);

    default:
		LOG_WARNING("[error] unkown packet");		// 프로토콜 틀릴 때 발생!
		kick_out(game_id, MSG::KILL, "");
        break;
    }
}

void        
Room::on_database(MSG::GameID game_id, 
	int32_t seq, 
	const std::string& query,
	int32_t	ret_code,
	const std::string& result)
{
	User* pUser = find_user(game_id);
	Room* pRoom = this;
	jRETURN_ERROR_ROOM(NULL != pUser,ERR_SERVER_DATA_ROOM_NULL);
	jRETURN_ERROR_ROOM(seq==IS_BS2UG_PACKET,ERR_SERVER_DATA_ROOM_NULL);
	UserGateServer_BaseballServer rd;
	rd.ParseFromString(result);

	switch (rd.type())
	{
#define jPARSE_PROTO_MESSAGE_UG2BS(DOMAIN,NAME,ORDER)\
	case _jJOIN_3(DOMAIN,_Type_,NAME):\
	{\
		LOG_DEBUG("\n\nRecv : " #DOMAIN "(" #NAME ") :uid = " << game_id);\
		CB_##DOMAIN(pUser,rd.m_##NAME());\
		return;\
	}\

	for_each_UserGateServer_BaseballServer(jPARSE_PROTO_MESSAGE_UG2BS);

	default:
		{
			LOG_ERROR("unkown packet : type=" << rd.type());
			kick_out(game_id, MSG::KILL, "");
		}
	}
}

void
Room::on_timer(MSG::RoomTimerID timer_id, int32_t token, void* param)
{
	ETimerKey timer_key = static_cast<ETimerKey>(token);
	timer_ids__it itr_id = timer_ids_.find(timer_key);

	Room* pRoom = this;
	jRETURN_ERROR_ROOM(timer_ids_.end() != itr_id ,ERR_SERVER_DATA_ROOM_NULL);

	timer_callbacks__it itr_cb = timer_callbacks_.find(timer_key);
	jRETURN_ERROR_ROOM(timer_callbacks_.end() != itr_cb,ERR_SERVER_DATA_ROOM_NULL);
	timer_callback_t callback = itr_cb->second;
	
	timer_ids_.erase(itr_id);
	timer_callbacks_.erase(itr_cb);

	jRETURN_ERROR_ROOM(callback != NULL  ,ERR_SERVER_DATA_ROOM_NULL);
	callback(this);
	LOG_DEBUG("called " << ToString(timer_key));
}

bool 
Room::is_all_user_ready()
{
	BOOST_FOREACH (UserMapType::value_type& kv, user_map_)
	{
		if (!kv.second->is_ready())
			return false;
	}
	return true;
}

bool 
Room::is_full_user()
{
	if (is_auto_play() && user_count() >= 1) return true;
	return user_count() >= DEF_i_MAX_PLAYING_USER;	
}

void 
Room::reset_user_info()		// 한 게임 끝났을 때 초기화
{
	m_sid_RunnerState.clear();
	m_sid_RunnerState_index = 0;
	
	jCHECK(nG::i_TOTAL_ROUND);
	if (nG::i_TOTAL_ROUND)
	{
	    m_i_TOTAL_ROUND =nG::i_TOTAL_ROUND->Get_int();
	    jIF (m_i_TOTAL_ROUND<=0)
	    {
	  	  m_i_TOTAL_ROUND = 9;
	    }
	}
	else
	{
	    m_i_TOTAL_ROUND = 9;
	}
	
	jCHECK(nG::i_ATTACK_CHANGE_ROUND);
	if(nG::i_ATTACK_CHANGE_ROUND)
	{
	    m_i_ATTACK_CHANGE_ROUND = nG::i_ATTACK_CHANGE_ROUND->Get_int();
	    jIF (m_i_ATTACK_CHANGE_ROUND <=0 || m_i_ATTACK_CHANGE_ROUND > m_i_TOTAL_ROUND)
	    {
	  	  m_i_ATTACK_CHANGE_ROUND = 3;
	    }
	}
	else
	{
	    m_i_ATTACK_CHANGE_ROUND = 3;
	}
	
	m_i_CheckRound = (m_i_TOTAL_ROUND % m_i_ATTACK_CHANGE_ROUND);
	m_i_CheckRound = (m_i_TOTAL_ROUND - m_i_CheckRound)*2 + 1;
	
	jUser_GameRoomInfo::reset_user_info();

	m_GameRoomInfo.set_m_attack_user(m_first_attack_user);
}

Tbl_User_id_t 
Room::select_first_attack_user() // 경기시작 & 재경기시작
{
	int idx =0;

	if (nG::b_IS_FIRST_ATTACK_USER_IS_RANDOM->Get_bool())
	{
		idx = nMOB::make_random() % DEF_i_MAX_PLAYING_USER;
	}

	User* pUser = get_user_(idx);
	jRETURN_ret(0,pUser);
	LOG_DEBUG("first user is =" << pUser->db_id());

	m_first_attack_user = pUser->db_id();
	m_GameRoomInfo.set_m_attack_user(pUser->db_id());

	return pUser->db_id();
}

void 
Room::send_ans_pitcher_throw(const s_req_pitcher_throw& rd,bool is_auto)
{
	jMAKE_MSG_BS2X(sendMsg,sd,ans_pitcher_throw);
	sd->mutable_info()->CopyFrom(rd.info());	// 투수/타자에 투구 정보 전송
	sd->set_is_auto(is_auto);
	send_all(sendMsg);

#ifdef  SERVER_AUTO_PLAY
	add_timer_wrapper(E_TIME_OUT_REQ_BETTER_HIT, 
			GAME_BATTER_HIT_WAIT_TIME_COUNT+g_TIME_OUT_OFFSET,
			time_out_req_better_hit);
#endif
}

void 
Room::send_bs2x_auto_match_ready2(Tbl_User_id_t uid)
{
	s_game_play_info *gpi		= get_s_game_play_info(uid);		// 내 정보
	s_game_play_info *gpi_other = get_s_game_play_info_Other(uid);	// 상대방 정보

	Room* pRoom = this;
	
	jRETURN_ERROR_ROOM(gpi != NULL  ,ERR_SERVER_DATA_ROOM_NULL);
	jMAKE_MSG_BS2X(sendMsg,sd,bs2x_auto_match_ready2);

	sd->set_uid(uid);
	sd->set_batter(gpi->m_batter_sid());
	sd->set_pitcher(gpi->m_pitcher_sid());

	if (gpi_other)	// 상대방이 방안에 있으면 sendall
	{
		sd->set_other_batter(gpi_other->m_batter_sid());
		sd->set_other_pitcher(gpi_other->m_pitcher_sid());
		this->send_all(sendMsg);
	}
	else			// 상대방이 없으면 to me
	{
		sd->set_other_batter(-1);	
		sd->set_other_pitcher(-1);	
		this->send(uid, sendMsg);	// 에코 되면 안되는 데이터!
	}
	LOG_DEBUG("automatchready2   batter		=" << sd->batter() );
	LOG_DEBUG("automatchready2   pitcher	=" << sd->pitcher());
	LOG_DEBUG("automatchready2   uid		=" << sd->uid() );
	LOG_DEBUG("automatchready2  other batter	=" << sd->other_batter() );
	LOG_DEBUG("automatchready2  other pitcher	=" << sd->other_pitcher() );
	// this->send_all(sendMsg);		// 버그로 위치 이동
}

game_money_t 
Room::calc_game_money(EBatterHitType e, score_t curr_score,bool isWin)
{
	game_money_t gm=0;
	jTE* peGAME_RESULT;
	if(isWin)
	{
		static jTE* peWIN = nXML::find(nG::g_DocApp , "baseball.play_data.GAME_RESULT.PVP.WIN");
		jCHECK(peWIN);
		peGAME_RESULT  = peWIN;
	}
	else
	{
		static jTE* peLOSE= nXML::find(nG::g_DocApp , "baseball.play_data.GAME_RESULT.PVP.LOSE");
		jCHECK(peLOSE);
		peGAME_RESULT = peLOSE;
	}
	jRETURN_ret(0,peGAME_RESULT);

	//<WIN i_EXP='30' EBHT_ONEHIT="5" EBHT_DOUBLEHIT="10" EBHT_TRIPLEHIT="15" EBHT_HOMERUN_1="40" EBHT_HOMERUN_2="60" EBHT_HOMERUN_3="80" EBHT_HOMERUN_4="100" />
	switch(e)
	{
	case eEBHT_ONEHIT:
	case eEBHT_DOUBLEHIT:
	case eEBHT_TRIPLEHIT:
		{
			cstr sz = nExcelUtil::ToString(e);
			cstr szVal = peGAME_RESULT->Attribute(sz);
			jvRETURN_ret(0 , szVal , "%s is not found",sz);
			gm = atoi(szVal);
		}
		break;
	case eEBHT_HOMERUN:
		{
			fname_t sz;
			sprintf(sz, "%s_%d", nExcelUtil::ToString(e), curr_score);
			cstr szVal = peGAME_RESULT->Attribute(sz);
			jvRETURN_ret(0 , szVal , "%s is not found",sz);
			gm = atoi(szVal);
		}
		break;
	default:
		{
			break;
		}
	}
	//LOG_DEBUG(nExcelUtil::ToString(e) << ": curr_score=" << curr_score << " : money=" << gm);
	return gm;
}


// userA가 승자이다. userB는 패자( 변화된 elp_point 를 save 한다 )
static void calc_elo_point( INOUT  s_tbl_user* userA, INOUT  s_tbl_user* userB,IN bool is_tie)
{
	//jTODO ELO 보상 처리
	/// ELO계산은 다음 문서 참조. :http://nwmsvn.nwinet.co.kr/svn/baseball/doc/server/ELO.docx
	elo_point_t curr_Ra = userA->elo_point();
	elo_point_t curr_Rb = userB->elo_point();

	LOG_INFO("old : userA = (" << userA->db_id() << "," << (int32)curr_Ra << ")");
	LOG_INFO("old : userA = (" << userA->db_id() << "," << (int32)curr_Rb << ")");

	elo_point_t Ka		= nBASE_BALL::calc_elo_K(curr_Ra);
	elo_point_t Kb		= nBASE_BALL::calc_elo_K(curr_Rb);

	elo_point_t curr_Sa = 1;			
	elo_point_t curr_Sb = 0;

	if ( is_tie )			// 무승부
	{
		// curr_Sa = 0.5;
		// curr_Sb = 0.5;
		// 무승부일때는 양쪽 모두 0 처리( 2012.10.04 : 기획팀 요청 처리 )-> 기존 elo_point 그대로!
		userA->set_elo_point((int32)userA->elo_point());
		userB->set_elo_point((int32)userB->elo_point());

		std::cout << "calc_elo_point : GAME TIE! : " << std::endl;

		return ;
	}
	
	elo_point_t curr_Qa = pow(10, curr_Ra / 400);
	elo_point_t curr_Qb = pow(10, curr_Rb / 400);

	if (curr_Qa+curr_Qb == 0)
	{
		LOG_WARNING("elo basic data error = (" << curr_Qa << "," << curr_Qb << ")");
		return;
	}

	elo_point_t curr_Ea = curr_Qa / (curr_Qa+curr_Qb);
	elo_point_t curr_Eb = curr_Qb / (curr_Qa+curr_Qb);

	elo_point_t new_Ra = curr_Ra + Ka*(curr_Sa-curr_Ea);	// A 유저의 add elo_point
	elo_point_t new_Rb = curr_Rb + Kb*(curr_Sb-curr_Eb);	// B 유저의 add elo_point

	userA->set_elo_point((int32)new_Ra);
	userB->set_elo_point((int32)new_Rb);
	LOG_INFO("cur : userA = (" << userA->db_id() << "," << (int32)new_Ra << ")");
	LOG_INFO("cur : userB = (" << userB->db_id() << "," << (int32)new_Rb << ")");

}

// 비정상 종료에 대비한 elo_point 계산( 변화된 값을 구한다 )
int 
Room::calc_abnormal_elo( INOUT  s_tbl_user* userA, INOUT  s_tbl_user* userB )
{
	elo_point_t curr_Ra = userA->elo_point();
	elo_point_t curr_Rb = userB->elo_point();

	std::cout << "curr_Ra : Ka : " << curr_Ra << std::endl;
	std::cout << "curr_Rb : Kb : " << curr_Rb << std::endl;

	LOG_INFO("old : userA = (" << userA->db_id() << "," << (int32)curr_Ra << ")");
	LOG_INFO("old : userA = (" << userA->db_id() << "," << (int32)curr_Rb << ")");

	elo_point_t Ka		= nBASE_BALL::calc_elo_K(curr_Ra);
	elo_point_t Kb		= nBASE_BALL::calc_elo_K(curr_Rb);

	std::cout << "calc_elo_point : Ka : " << Ka << std::endl;
	std::cout << "calc_elo_point : Kb : " << Kb << std::endl;

	elo_point_t curr_Qa = pow(10, curr_Ra / 400);
	elo_point_t curr_Qb = pow(10, curr_Rb / 400);

	std::cout << "calc_elo_point : curr_Qa : " << curr_Qa << std::endl;
	std::cout << "calc_elo_point : curr_Qb : " << curr_Qb << std::endl;

	if (curr_Qa+curr_Qb == 0)
	{
		LOG_WARNING("elo basic data error = (" << curr_Qa << "," << curr_Qb << ")");
		return 0;
	}

	elo_point_t curr_Ea = curr_Qa / (curr_Qa+curr_Qb);
	elo_point_t curr_Eb = curr_Qb / (curr_Qa+curr_Qb);

	std::cout << "calc_elo_point : curr_Ea : " << curr_Ea << std::endl;
	std::cout << "calc_elo_point : curr_Eb : " << curr_Eb << std::endl;

	// A win case
	elo_point_t curr_Sa = 1;			
	elo_point_t curr_Sb = 0;

	std::cout << "calc_elo_point : curr_Sa : " << curr_Sa << std::endl;
	std::cout << "calc_elo_point : curr_Sb : " << curr_Sb << std::endl;

	elo_point_t new_Ra = curr_Ra + Ka*(curr_Sa-curr_Ea);	// A 유저의 add elo_point
	elo_point_t new_Rb = curr_Rb + Kb*(curr_Sb-curr_Eb);	// B 유저의 add elo_point

	std::cout << "A win : new_Ra : " << new_Ra << std::endl;
	std::cout << "B lose : new_Rb : " << new_Rb << std::endl;

	memset( &abnormalEnd, 0, sizeof(abnormalEnd));

	abnormalEnd.db_id_A		= userA->db_id();
	abnormalEnd.db_id_B		= userB->db_id();
	abnormalEnd.Win_elo_A	= (new_Ra - curr_Ra)/2;
	abnormalEnd.Lose_elo_B	= (new_Rb - curr_Rb)/2;

	//------------------------------------------//
	// b win case
	curr_Sa = 0;			
	curr_Sb = 1;

	std::cout << "calc_elo_point : curr_Sa : " << curr_Sa << std::endl;
	std::cout << "calc_elo_point : curr_Sb : " << curr_Sb << std::endl;

	new_Ra = curr_Ra + Ka*(curr_Sa-curr_Ea);	// A 유저의 add elo_point
	new_Rb = curr_Rb + Kb*(curr_Sb-curr_Eb);	// B 유저의 add elo_point

	std::cout << "A lose : new_Ra : " << new_Ra << std::endl;
	std::cout << "B win : new_Rb : " << new_Rb << std::endl;

	abnormalEnd.Lose_elo_A	= (new_Ra - curr_Ra)/2;
	abnormalEnd.Win_elo_B	= (new_Rb - curr_Rb)/2;

	LOG_INFO("winner userA = (" << userA->db_id() << "," << abnormalEnd.Win_elo_A << ")");
	LOG_INFO("loser userB = (" << userB->db_id() << "," << abnormalEnd.Lose_elo_B << ")");
	LOG_INFO("Loser userA = (" << userA->db_id() << "," << abnormalEnd.Lose_elo_A << ")");
	LOG_INFO("Winner userB = (" << userB->db_id() << "," << abnormalEnd.Win_elo_B << ")");

	return true;
}

void 
Room::calc_game_result()
{
	s_tbl_result& rg = this->get_s_tbl_result();

	//#--------------------------------------------------------------------------
	// 승자 패자 점수계산.
	//#--------------------------------------------------------------------------
	jUser_GameRoomInfo::score_list_t score_list;
	this->get_score(score_list);
	if(!(score_list.size()==2))
	{
		GetjILog()->Warning(0,jDEBUG_LINE_INFO "%s>",jFUNC);
		GetjILog()->Warning(0, "jCHECK(score_list.size()==2)");
		GetjILog()->Warning(0,"\n");
	}

	std::pair<Tbl_User_id_t,score_t> win_score, lose_score;

	if(score_list.begin()->second >= score_list.rbegin()->second)
	{
		win_score = std::make_pair(score_list.begin()->first , score_list.begin()->second);
		lose_score = std::make_pair(score_list.rbegin()->first, score_list.rbegin()->second);
	}
	else if(score_list.begin()->second < score_list.rbegin()->second)
	{
		win_score = std::make_pair(score_list.rbegin()->first , score_list.rbegin()->second);
		lose_score = std::make_pair(score_list.begin()->first, score_list.begin()->second);
	}
 	LOG_DEBUG("win_score = (" << win_score.first << "," << win_score.second << ")");
 	LOG_DEBUG("lose_score = (" << lose_score.first << "," << lose_score.second << ")");

	bool isEqual = win_score.second == lose_score.second;//무승부이면 진것처럼 보상.

	rg.set_win_uid(win_score.first);
	s_game_play_info *gpi_win = this->get_s_game_play_info(win_score.first);
	rg.set_win_better(gpi_win->m_batter_sid());
	rg.set_win_pitcher(gpi_win->m_pitcher_sid());
	rg.set_win_score(win_score.second);

	rg.set_lose_uid(lose_score.first);
	s_game_play_info *gpi_lose = this->get_s_game_play_info(lose_score.first);
	rg.set_lose_better(gpi_lose->m_batter_sid());
	rg.set_lose_pitcher(gpi_lose->m_pitcher_sid());
	rg.set_lose_score(lose_score.second);

	// jTODO ELO 계산.
	int old_win_elo_point	= gpi_win->m_tbl_user().elo_point();	
	int old_lose_elo_point	= gpi_lose->m_tbl_user().elo_point();
	
	std::cout << "old_win_elo_point : " << gpi_win->m_tbl_user().elo_point() << std::endl;
	std::cout << "old_lose_elo_point: " << gpi_lose->m_tbl_user().elo_point() << std::endl;

	calc_elo_point(INOUT gpi_win->mutable_m_tbl_user(),INOUT gpi_lose->mutable_m_tbl_user(),IN isEqual);

	std::cout << "calc_game_result : win_elo_point : " << gpi_win->m_tbl_user().elo_point() << std::endl;
	std::cout << "calc_game_result : lose_elo_point : " << gpi_lose->m_tbl_user().elo_point() << std::endl;
	// _ORACLE
	rg.set_win_elo_point(gpi_win->m_tbl_user().elo_point() - old_win_elo_point);	// 통 데이터를 -> 가감 값으로 수정
	rg.set_lose_elo_point(gpi_lose->m_tbl_user().elo_point() - old_lose_elo_point);	// 통 데이터를 -> 가감 값으로 수정	

	std::cout << "calc_game_result : rg.win_elo_point : " << rg.win_elo_point() << std::endl;
	std::cout << "calc_game_result : rg.lose_elo_point : " << rg.lose_elo_point() << std::endl;

	fname_t buf;
	
	time_t sec = time(0) - m_timer_game_start;
	rg.set_play_time_sec((int32)sec);
	LOG_DEBUG("play_time_sec = " << rg.play_time_sec());
	rg.set_time_end(nOS::current_SYSTEMTIME(buf));
	
}
// 비정상 종료 시 게임 결과
bool 
Room::abnormal_calc_game_result(int64 winner)
{
	s_tbl_result& rg = this->get_s_tbl_result();

	if (winner == abnormalEnd.db_id_A)
	{
		s_game_play_info *gpi_win = this->get_s_game_play_info(winner);
		if( gpi_win )
		{
			rg.set_win_uid(winner);
			rg.set_win_better(gpi_win->m_batter_sid());
			rg.set_win_pitcher(gpi_win->m_pitcher_sid());
			rg.set_win_score(1);
			rg.set_win_elo_point(abnormalEnd.Win_elo_A);		// 가감 데이터
		}

		s_game_play_info *gpi_lose = this->get_s_game_play_info(abnormalEnd.db_id_B);
		if ( gpi_lose )
		{
			rg.set_lose_uid(abnormalEnd.db_id_B);
			rg.set_lose_better(gpi_lose->m_batter_sid());
			rg.set_lose_pitcher(gpi_lose->m_pitcher_sid());
			rg.set_lose_score(0);
			rg.set_lose_elo_point(abnormalEnd.Lose_elo_B);		// 가감 데이터
		}
	}
	else
	{
		// check abnormalEnd.db_id_B == winner
		if (winner != abnormalEnd.db_id_B)
		{
			LOG_WARNING("winner = " << winner);
			LOG_WARNING("abnormalEnd.db_id_B = " << abnormalEnd.db_id_B);
			return false;
		}

		s_game_play_info *gpi_win = this->get_s_game_play_info(abnormalEnd.db_id_B);
		if( gpi_win )
		{
			rg.set_win_uid(abnormalEnd.db_id_B);
			rg.set_win_better(gpi_win->m_batter_sid());
			rg.set_win_pitcher(gpi_win->m_pitcher_sid());
			rg.set_win_score(1);
			rg.set_win_elo_point(abnormalEnd.Win_elo_B);		// 가감 데이터
		}

		s_game_play_info *gpi_lose = this->get_s_game_play_info(abnormalEnd.db_id_A);
		if ( gpi_lose )
		{
			rg.set_lose_uid(abnormalEnd.db_id_A);
			rg.set_lose_better(gpi_lose->m_batter_sid());
			rg.set_lose_pitcher(gpi_lose->m_pitcher_sid());
			rg.set_lose_score(0);
			rg.set_lose_elo_point(abnormalEnd.Lose_elo_A);		// 가감 데이터
		}
	}

	std::cout << "rg.win_elo_point : " << rg.win_elo_point() << std::endl;
	std::cout << "rg.lose_elo_point : " << rg.lose_elo_point() << std::endl;

	fname_t buf;

	time_t sec = time(0) - m_timer_game_start;
	rg.set_play_time_sec((int32)sec);
	rg.set_time_end(nOS::current_SYSTEMTIME(buf));

	LOG_DEBUG("win_uid = " << rg.win_uid());
	LOG_DEBUG("win_elo_point = " << rg.win_elo_point());
	LOG_DEBUG("lose_uid = " << rg.lose_uid());
	LOG_DEBUG("lose_elo_point = " << rg.lose_elo_point());

	return true;
}


// 콜드 게임 종료 조건 체크 용
int 
Room::calc_game_score()
{
	jUser_GameRoomInfo::score_list_t score_list;

	this->get_score(score_list);

	if(!(score_list.size()==2))
	{
		LOG_DEBUG("score_list.size() = << score_list.size()");
		return 0;
	}

	std::pair<Tbl_User_id_t,score_t> win_score, lose_score;

	if(score_list.begin()->second >= score_list.rbegin()->second)
	{
		win_score = std::make_pair(score_list.begin()->first , score_list.begin()->second);
		lose_score = std::make_pair(score_list.rbegin()->first, score_list.rbegin()->second);
	}
	else if(score_list.begin()->second < score_list.rbegin()->second)
	{
		win_score = std::make_pair(score_list.rbegin()->first , score_list.rbegin()->second);
		lose_score = std::make_pair(score_list.begin()->first, score_list.begin()->second);
	}

	LOG_DEBUG("win_score = (" << win_score.first << "," << win_score.second << ")");
	LOG_DEBUG("lose_score = (" << lose_score.first << "," << lose_score.second << ")");

	int score_gab = win_score.second - lose_score.second;	// 콜드 게임 조건 체크
	LOG_DEBUG("score_gab = " << score_gab );
	std::cout << "\n score_gab : " << score_gab << std::endl;

	if ( score_gab >= CALLED_GAME_SCORE )
	{
		LOG_DEBUG("score_gab = " << score_gab );
		LOG_DEBUG("win_uid = " << win_score.first);
		LOG_DEBUG("win_score = " << win_score.second);
		LOG_DEBUG("lose_uid = " << lose_score.first);
	}

	return score_gab;
}

// 14 라운드에서 승부 확정 상황 검사
int 
Room::check_withoutattack_loser()
{
	jUser_GameRoomInfo::score_list_t score_list;

	this->get_score(score_list);

	if(!(score_list.size()==2))
	{
		LOG_DEBUG("score_list.size() = << score_list.size()");
		return GAME_PLAYING;
	}

	std::pair<Tbl_User_id_t,score_t> win_score, lose_score;

	if(score_list.begin()->second >= score_list.rbegin()->second)
	{
		win_score = std::make_pair(score_list.begin()->first , score_list.begin()->second);
		lose_score = std::make_pair(score_list.rbegin()->first, score_list.rbegin()->second);
	}
	else if(score_list.begin()->second < score_list.rbegin()->second)
	{
		win_score = std::make_pair(score_list.rbegin()->first , score_list.rbegin()->second);
		lose_score = std::make_pair(score_list.begin()->first, score_list.begin()->second);
	}

	LOG_DEBUG("check_attack_uid = " << get_attack_user());
	LOG_DEBUG("win_score = (" << win_score.first << "," << win_score.second << ")");
	LOG_DEBUG("lose_score = (" << lose_score.first << "," << lose_score.second << ")");

	int score_gab = win_score.second - lose_score.second;	// 콜드 게임 조건 체크
	LOG_DEBUG("score_gab = " << score_gab );
	std::cout << "score_gab : " << score_gab << std::endl;

	LOG_DEBUG("attack_uid = " << get_attack_user());
	std::cout << "attack_user : " << get_attack_user() << std::endl;
	
	// 동점이 아님 && 지고 있는 유저의 마지막 공격 일때
	if (score_gab != 0 && lose_score.first == get_attack_user())	
	{
		LOG_DEBUG("attack_uid = " << get_attack_user());
		LOG_DEBUG("win_uid = " << win_score.first);
		LOG_DEBUG("win_score = " << win_score.second);
		LOG_DEBUG("lose_uid = " << lose_score.first);
		LOG_DEBUG("WITHOUT_ATTACK : lose_score = " << lose_score.second);
		return WITHOUT_ATTACK;
	}

	return GAME_PLAYING;
}

// 15 라운드 이후 에서 승부 확정 검사
int 
Room::check_withoutattack_winner()
{
	jUser_GameRoomInfo::score_list_t score_list;

	this->get_score(score_list);

	if(!(score_list.size()==2))
	{
		LOG_DEBUG("score_list.size() = << score_list.size()");
		return GAME_PLAYING;
	}

	std::pair<Tbl_User_id_t,score_t> win_score, lose_score;

	if(score_list.begin()->second >= score_list.rbegin()->second)
	{
		win_score = std::make_pair(score_list.begin()->first , score_list.begin()->second);
		lose_score = std::make_pair(score_list.rbegin()->first, score_list.rbegin()->second);
	}
	else if(score_list.begin()->second < score_list.rbegin()->second)
	{
		win_score = std::make_pair(score_list.rbegin()->first , score_list.rbegin()->second);
		lose_score = std::make_pair(score_list.begin()->first, score_list.begin()->second);
	}

	LOG_DEBUG("check_attack_uid = " << get_attack_user());
	LOG_DEBUG("win_score = (" << win_score.first << "," << win_score.second << ")");
	LOG_DEBUG("lose_score = (" << lose_score.first << "," << lose_score.second << ")");

	int score_gab = win_score.second - lose_score.second;	// 콜드 게임 조건 체크

	LOG_DEBUG("score_gab = " << score_gab );
	LOG_DEBUG("attack_uid = " << get_attack_user());

	// 승부 확정 : 동점이 아니고 이기고 있는 유저가 공격자 일 때
	if ( score_gab != 0 && get_curr_winner() == get_attack_user() )
	{
		LOG_DEBUG("current_round_count = " << get_round_count() );
		LOG_DEBUG("checkGameEnd : WITHOUT_ATTACK");
		LOG_DEBUG("attack_user = " << get_attack_user() );
		return WITHOUT_ATTACK;		
	}

	return GAME_PLAYING;
}

// 현재 승자 ( 역전 승 체크 ) : 에러,동점,승자가 있는 3가지 상황
Tbl_User_id_t 
Room::get_curr_winner()
{
	jUser_GameRoomInfo::score_list_t score_list;

	this->get_score(score_list);

	if(!(score_list.size()==2))
	{
		LOG_DEBUG("Error : there are no winner yet!");
		return -1;
	}

	std::pair<Tbl_User_id_t,score_t> win_score, lose_score;

	if(score_list.begin()->second >= score_list.rbegin()->second)
	{
		win_score = std::make_pair(score_list.begin()->first , score_list.begin()->second);
		lose_score = std::make_pair(score_list.rbegin()->first, score_list.rbegin()->second);
	}
	else if(score_list.begin()->second < score_list.rbegin()->second)
	{
		win_score = std::make_pair(score_list.rbegin()->first , score_list.rbegin()->second);
		lose_score = std::make_pair(score_list.begin()->first, score_list.begin()->second);
	}

	int score_gab = win_score.second - lose_score.second;	// 동점 상황 체크

	if ( score_gab == 0 )
	{
		LOG_DEBUG("game is tie : no winner");
		return 0;
	}

	LOG_DEBUG("current win_uid = " << win_score.first);

	return win_score.first;
}

// 주자 상태와 홈런을 쳤을 때의 점수 계산
int
Room::calc_RSTypeWhenHomerun(ERunnerStateRound eRSType)
{
	int score = 0;

	LOG_DEBUG("eRSType = " << eRSType);

	switch(eRSType)
	{
	case eERSR_0:	 score = 1;		break;
	case eERSR_1:	 score = 2;		break;
	case eERSR_2:	 score = 2;		break;
	case eERSR_12:	 score = 3;		break;
	case eERSR_3:	 score = 2;		break;
	case eERSR_13:	 score = 3;		break;
	case eERSR_23:	 score = 3;		break;
	case eERSR_123:	 score = 4;		break;
	default:		 score = 1;		break;
	}

	LOG_DEBUG("if all homerun score = " << score );
	return score;
}

int 
Room::calc_max_remain_score()
{
	int TotalScore = 0;

	// 현재 이닝
	round_t iTeamRoundCount = nBASE_BALL::curr_team_round((get_round_count()+1)\
		,nG::i_ATTACK_CHANGE_ROUND->Get_int());

	LOG_DEBUG("iTeamRoundCount = "<< iTeamRoundCount);
	LOG_DEBUG("i_TOTAL_ROUND = " << nG::i_TOTAL_ROUND->Get_int());

	jCHECK( iTeamRoundCount >= 0 && iTeamRoundCount < nG::i_TOTAL_ROUND->Get_int() );

	ERunnerStateRound eRSType;

	for( int i = iTeamRoundCount; i <= nG::i_TOTAL_ROUND->Get_int(); i++)
	{
		eRSType = get_round_state(i, this->Get_Curr_RSR());	// 남은 주자 배치
		LOG_DEBUG("eRSType = "<< eRSType);
		int Score = calc_RSTypeWhenHomerun(eRSType);		// 홈런을 쳤을 때 점수
		LOG_DEBUG("Score = " << Score);
		// TotalScore += calc_RSTypeWhenHomerun(eRSType);	// 홈런을 쳤을 때 점수
		TotalScore += Score;		// 홈런을 쳤을 때 점수
		LOG_DEBUG("temp TotalScore = " << TotalScore);

	}
	LOG_DEBUG("return : TotalScore = "<< TotalScore);

	return TotalScore;
}

User* 
Room::get_current_pitcher()
{
	BOOST_FOREACH (UserMapType::value_type& kv, user_map_)
	{
		User* pUser = kv.second;
		if (pUser->db_id() != get_attack_uid())
			return pUser;
	}
	return NULL;
}

User* 
Room::get_current_better()
{
	BOOST_FOREACH (UserMapType::value_type& kv, user_map_)
	{
		User* pUser = kv.second;
		if (pUser->db_id() == get_attack_uid())
			return pUser;
	}
	return NULL;
}

User* 
Room::get_other_user(MSG::GameID game_id)
{
	BOOST_FOREACH (UserMapType::value_type& kv, user_map_)
	{
		User* pUser = kv.second;
		if (pUser->db_id() != game_id) return pUser;
	}
	return NULL;
}

User* 
Room::find_user(MSG::GameID game_id)
{
	UserMapType::iterator itr = user_map_.find(game_id);
	if (user_map_.end() == itr)
		return NULL;
	return itr->second;
}

User* 
Room::insert_user_(MSG::GameID game_id)
{
	if (user_map_.end() != user_map_.find(game_id))
		return NULL;
	User* user = new User(game_id, this);
	user_map_.insert(std::make_pair(game_id, user));
	return user;
}

User* 
Room::get_user_(int iOrder)
{
	jvRETURN_ret(0,iOrder < nG::i_MAX_PLAYING_USER->Get_int(),"iOrder = %d",iOrder);
	int i=0;
	BOOST_FOREACH (UserMapType::value_type& kv, user_map_)
	{
		if ((i++) != iOrder) continue;
		return kv.second;
	}
	LOG_WARNING(" code is strange!!! : iOrder=" << iOrder);
	return NULL;//절대 이런일은 없어야 한다.
}

void 
Room::delete_user_(MSG::GameID game_id)
{
	UserMapType::iterator itr = user_map_.find(game_id);
	if (user_map_.end() == itr)
		return ;
	delete itr->second;
	user_map_.erase(itr);
}
	
} /* baseball */
