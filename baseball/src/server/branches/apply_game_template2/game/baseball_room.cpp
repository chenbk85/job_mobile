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

#define jLAMDA_func_send_ans_team_match_ready(X,Z) Z(baseball::Room* , pRoom)
jLAMDA_for_each(func_send_ans_team_match_ready,baseball::User*)
{
	if(it->get_m_e_user_gps() >= eUGPS_GAME_READY) return;
	pRoom->send_ans_team_match_ready(it->db_id());
}
jLAMDA_end()

void 
time_out_req_team_match_ready(baseball::Room* pRoom)
{
	//20초가 지났는데도 레디를 안하므로 강제로 ans_team_match_ready를 보냄.
	boost::function<void(baseball::User*)> func = func_send_ans_team_match_ready(pRoom);
	pRoom->for_each_User(func);
}

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
get_round_state(round_t iRoundCount, Sys_Runner_State_id_t sid)
{
	Sys_Runner_State* pSys = jCSV(Sys_Runner_State).Index(sid);
	jRETURN_ret(eERSR_123,pSys);
	const int MAX_ROUND = 9;
	iRoundCount %=MAX_ROUND;
	if(iRoundCount==0) iRoundCount=MAX_ROUND;


	switch(iRoundCount)
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
			jWARN("iRoundCount= %d  -> over then 9", iRoundCount);
			return eERSR_123;
		}
	}
}

void 
timer_job_ans_game_start(baseball::Room* pRoom)
{
	jRETURN(pRoom->is_full_user());
	jRETURN(pRoom->is_all_user_ready());

	Tbl_User_id_t uid = pRoom->reset_user_info_for_gamestart();
	jMAKE_MSG_BS2X(sendMsg,sd,ans_game_start);
	set_EUserGPS func(eUGPS_GAME_START);
	pRoom->for_each_s_game_play_info(func);

	sd->set_attack_user(uid);
	pRoom->send_all(sendMsg);
	pRoom->m_GameRoomInfo.set_m_round_count(0);
	
	pRoom->m_timer_game_start = time(0);

	//#--------------------------------------------------------------------------
	// 주자 랜덤배치 계산.
	//#--------------------------------------------------------------------------
	ERunnerStateType eType = (ERunnerStateType)nMOB::random_my(eBEGIN_ERunnerStateType+1, eEND_ERunnerStateType-1);
	jCHECK(IsValid(eType));
	vector<Sys_Runner_State*> &vec = jCSV(Sys_Runner_State).m_INDEX_category[eType];
	jvRETURN(vec.size(), "eType = %s , jCSV(Sys_Runner_State).size=%d", ToString(eType), jCSV(Sys_Runner_State).size());
	pRoom->m_sid_RunnerState[0] = _get_random_Sys_Runner_State_id(vec);
	pRoom->m_sid_RunnerState[1] = _get_random_Sys_Runner_State_id(vec);
	jLOG("%s> ERunnerStateType= %s , Sys_Runner_State_id = %d, %d", jFUNC, ToString(eType),pRoom->m_sid_RunnerState[0],pRoom->m_sid_RunnerState[1] );

	pRoom->add_timer_wrapper(baseball::Room::E_TIMER_JOB_ANS_GAME_ROUND_START,
			nG::i_TIME_ALL_PLAYER_READY->Get_int(),
			timer_job_ans_game_round_start);
}

void 
timer_job_ans_game_round_start(baseball::Room* pRoom)
{
	jRETURN(pRoom && pRoom->is_full_user());
	jRETURN(pRoom->is_all_user_ready());

	jMAKE_MSG_BS2X(sendMsg,sd,ans_game_round_start);
	sd->set_round(pRoom->get_round_count());

	ERunnerStateRound eRSType = get_round_state(pRoom->get_round_count(), pRoom->Get_Curr_RSR() );
	sd->set_runner_state(eRSType);
	pRoom->send_all(sendMsg);
	jLOG("\n\nsend : ans_game_round_start : runner state= %s\n\n\n", ToString(eRSType));

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
	jLOG("create room # %d" , id() );
	m_GameRoomInfo.set_room_id(id());
	Room::reset_user_info();

	g_mapRoom.insert(id(), this);

	//초기 세팅할것
	jFUNC_LOG2("Room",id());
}

void        
Room::on_destroy()
{
	g_mapRoom.erase(id());
	jFUNC_LOG2("Room",id());
	jLOG("destroy room #%d" , id() );
}

bool		
Room::on_join(MSG::GameID game_id, const std::string& room_user_info, std::string& room_info, MSG::KICK_TYPE& kick_type, std::string& leave_info) 
{ 
	jFUNC_LOG2("Room",id());

	jLOG("user_.size() = %u ", user_count());

	//들어온 유저가 최대인원(2)보다 많으면 false리턴하여 접속실패보냄.
	kick_type = MSG::PURGE;	
	jRETURN_ret(false,user_count() <= ((size_t)nG::i_MAX_PLAYING_USER->Get_int() ));

	insert_user_(game_id);
	s_game_play_info* p = get_s_game_play_info(game_id);

	p->ParseFromString(room_user_info);
	nProtoHelper::message_print(p->m_tbl_user());
	nProtoHelper::message_print(p->m_tbl_team(),game_id);

	if (1 == user_count()) 
	{
		// 게임 첫번째 참가자가 들어왔음 첫번째 참가자 권한 줄 일이 있으면 처리
		std::cerr << "first pUser\n";
	}
	else 
	{
		std::cerr << "not first pUser\n";
		//#--------------------------------------------------------------------------
		// 내가 들어왔기때문에 방의 다른모든사람들에게 내정보를 알리자.
		//#--------------------------------------------------------------------------
		jMAKE_MSG_BS2X(sendMsg,sd,ans_join_room);
		sd->mutable_gri()->CopyFrom(m_GameRoomInfo);
		send_all_except_me(sendMsg, game_id);

		//MSG::TimerID timer_id = 
			add_timer_wrapper(E_TIME_OUT_REQ_TEAM_MATCH_READY,
					nG::i_TIME_ALL_PLAYER_READY->Get_int(),
					time_out_req_team_match_ready);
	}

	m_GameRoomInfo.SerializeToString(&room_info);// 룸 정보를 채워서 패킷을 만들어 전달한다

	return true; 
}

void        
Room::on_leave(MSG::GameID game_id, MSG::KICK_TYPE reason, const std::string& leave_info)
{

	jFUNC_LOG2("Room",id());

	// 사용자가 게임에서 빠저나갈때의 처리
	// 나가는 사람이 방장이면 방장인계처리.
	// 맞고의 나가기 예약을 걸어둔 유저등에 대한 철.

	//User* pUser = dynamic_cast<User*>(participant);

	// 추방 여부와 방장 교체 여부를 잘 고려해서 처리해야 함
	reason = MSG::EXIT_RESERVATION;

	/// user.cpp의 on_disconnect 로직을 옮겨옴
	jLOG("%s : uid = %d", jFUNC1, game_id);

	User* pOtherUser = get_other_user(game_id);
	jRETURN(pOtherUser);

	EUserGPS e = (EUserGPS)pOtherUser->get_m_e_user_gps() ;
	jLOG("OtherUser state = %s", ToString(e));
	if (pOtherUser->get_m_e_user_gps() < eUGPS_GAME_START || 
		pOtherUser->get_m_e_user_gps() >= eUGPS_GAME_END)
	{
		// 게임을 안하는 상태이면 다른유저도 로비로 보내자.
		kick_out(pOtherUser->db_id(), MSG::EXIT_RESERVATION, "");
	}
	else // 게임플레이중 비정상 종료.
	{
		//jTODO : DB에 비정상 접속해제 카운트를 증가시켜야함.
		jLOG("비정상 종료: uid=%lld",game_id);
		jMAKE_MSG_BS2UG(sendMsg, sd, bs2ug_add_discon_tot);
		sd->set_discon_uid(game_id);
		send_to_ug(pOtherUser->db_id(), sendMsg);
		m_GameRoomInfo.set_m_is_auto_play(true);
	}

	delete_user_(game_id);
	/// on_disconnect 로직 완료
}

void
Room::on_detach(MSG::GameID game_id)
{
	jWARN("%s : uid = %d", jFUNC1, game_id);

    // 사용자 회선이 잠시 떨어져 나감
	kick_out(game_id, MSG::EXIT_RESERVATION, "");
}

void
Room::on_plug(MSG::GameID game_id)
{
	jWARN("%s : uid = %d", jFUNC1, game_id);

    // 사용자 회선이 다시 돌아옴
	kick_out(game_id, MSG::EXIT_RESERVATION, "");
}

void
Room::on_game_protocol(MSG::GameID game_id, const std::string& message)
{
	User* user = find_user(game_id);
	jRETURN(NULL != user);
	//jFUNC_LOG();

    // 클라이언트에서 전송되는 게임에 관련된 메시지가 들어있다
    Client_BaseballServer request;

    request.ParseFromString(message);

	//std::cout << endl << __FUNCTION__ << " : type = "  << request.type() << endl;
    switch (request.type())
    {
#define jPARSE_PROTO_MESSAGE_X2BS(DOMAIN,NAME,ORDER)\
case _jJOIN_3(DOMAIN,_Type_,NAME):\
		{\
		jLOG("\n\nRECV>"  #DOMAIN  "::" #NAME " : %lld \n\n",game_id);\
		void CB_Client_BaseballServer(baseball::User* pUser, const s_##NAME&);\
		CB_Client_BaseballServer(user,request.m_##NAME());\
		break;\
	}\

		for_each_Client_BaseballServer(jPARSE_PROTO_MESSAGE_X2BS);
    default:
		jWARN("[error] unkown packet");
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
	User* user = find_user(game_id);
	jRETURN(NULL != user);
	//jFUNC_LOG();
	jRETURN(seq==IS_BS2UG_PACKET);
	UserGateServer_BaseballServer rd;
	rd.ParseFromString(result);

	switch (rd.type())
	{
#define jPARSE_PROTO_MESSAGE_UG2BS(DOMAIN,NAME,ORDER)\
	case _jJOIN_3(DOMAIN,_Type_,NAME):\
	{\
		jLOG("\n\nRecv : %s(%s) :uid = %d", #DOMAIN , #NAME, game_id);\
		CB_##DOMAIN(user,rd.m_##NAME());\
		return;\
	}\

	for_each_UserGateServer_BaseballServer(jPARSE_PROTO_MESSAGE_UG2BS);

	default:
		{
			jERROR("\n%s unkown packet : type=%d",jFUNC1 , rd.type());
			kick_out(game_id, MSG::KILL, "");
		}
	}
}

void
Room::on_timer(MSG::RoomTimerID timer_id, int32_t token, void* param)
{
	TIMER_KEY timer_key = static_cast<TIMER_KEY>(token);
	std::map<TIMER_KEY, MSG::RoomTimerID>::iterator itr_id = timer_ids_.find(timer_key);
	if (timer_ids_.end() == itr_id)
		return;

	std::map<TIMER_KEY, boost::function<void (Room*)> >::iterator itr_cb = timer_callbacks_.find(timer_key);
	boost::function<void (Room*)> callback = itr_cb->second;
	
	timer_ids_.erase(itr_id);
	timer_callbacks_.erase(itr_cb);

	callback(this);
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
Room::reset_user_info()
{
	memset(m_sid_RunnerState,0,sizeof(m_sid_RunnerState));
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
}

Tbl_User_id_t 
Room::reset_user_info_for_gamestart() // 경기시작 & 재경기시작
{
	Room::reset_user_info();

	int idx =0;

	if (nG::b_IS_FIRST_ATTACK_USER_IS_RANDOM->Get_bool())
	{
		idx = nMOB::make_random() % nG::i_MAX_PLAYING_USER->Get_int();
	}

	User* pUser = get_user_(idx);
	jRETURN_ret(0,pUser);
	jLOG("%s > first user is =%d", __FUNCTION__, pUser->db_id());

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
Room::send_ans_team_match_ready(Tbl_User_id_t uid)
{
	s_game_play_info *gpi = get_s_game_play_info(uid);
	jRETURN(gpi);
	gpi->set_m_e_user_gps(eUGPS_GAME_READY);

	jMAKE_MSG_BS2X(sendMsg,sd,ans_team_match_ready);
	sd->set_uid(uid);
	this->send_all(sendMsg);

	if (this->is_full_user() && this->is_all_user_ready())
	{
		add_timer_wrapper(E_TIMER_JOB_ANS_GAME_START,
				nG::i_TIME_ALL_PLAYER_READY->Get_int(),
				timer_job_ans_game_start);
	}
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
			cstr sz = ToString(e);
			cstr szVal = peGAME_RESULT->Attribute(sz);
			jvRETURN_ret(0 , szVal , "%s is not found",sz);
			gm = atoi(szVal);
		}
		break;
	case eEBHT_HOMERUN:
		{
			fname_t sz;
			sprintf(sz, "%s_%d", ToString(e), curr_score);
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
	jLOG("%s> %s: curr_score=%d : money=%d",__FUNCTION__, ToString(e), curr_score,gm);
	return gm;
}


void 
Room::give_exp_to_team(Tbl_User_id_t uid, exp_t exp)//해당 유저의 팀선수들에게 경험치지급.
{
	s_game_play_info* gpi = this->get_s_game_play_info(uid);
	gpi->mutable_m_tbl_playerbetter()->set_exp(exp + gpi->mutable_m_tbl_playerbetter()->exp());
	gpi->mutable_m_tbl_playerpitcher()->set_exp(exp + gpi->mutable_m_tbl_playerpitcher()->exp());

}

void 
Room::calc_game_result()
{
		/*
	야구 결과창
	결과창참고 : D:\svn\baseball\doc\design\기획데이터\캐주얼야구 게임UI 기획서 (2012_06_21)김기준.pptx

		사용중인 컨슘아이템 다사용시(1개또는 1시간남았을때부터 ) 상점아이콘보여줌.
		업글중인 아이템완료시 강화창바로가기 보여줌.

	4) 선수들 정보
		승률은 시즌만.
		타자는 홈런수만.
		투수는 스트라이크아웃만.
		EBHT_STANDOUT
		EBHT_SWINGOUT

	5) 경험치그래프 그리기.
	Sys_PlayerLevel

	6) 보너스 게임머니(xml) 

	*/
	
	s_tbl_result& rg = this->get_s_tbl_result();

	//#--------------------------------------------------------------------------
	// 승자 패자 점수계산.
	//#--------------------------------------------------------------------------
	jUser_GameRoomInfo::score_list_t score_list;
	this->get_score(score_list);
	jCHECK(score_list.size()==2);
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
// 	jLOG("win_score = (%d,%d)", win_score.first, win_score.second);
// 	jLOG("lose_score = (%d,%d)", lose_score.first, lose_score.second);

	bool isEqual = win_score.second == lose_score.second;//무승부이면 진것처럼 보상.

	//#--------------------------------------------------------------------------
	// 보너스 경험치 계산.
	//#--------------------------------------------------------------------------
	static exp_t _win_exp = 0 , _lose_exp = 0;
	if(!_win_exp)
	{
		jTE* peEXP_WIN = nXML::find(nG::g_DocApp , "baseball.play_data.GAME_RESULT.PVP.WIN");
		jTE* peEXP_LOSE = nXML::find(nG::g_DocApp , "baseball.play_data.GAME_RESULT.PVP.LOSE");
		jRETURN(peEXP_WIN && peEXP_LOSE);
		cstr szExpWIN = peEXP_WIN->Attribute("i_EXP");
		cstr szExpLOSE = peEXP_LOSE->Attribute("i_EXP");
		jRETURN(szExpWIN&& szExpLOSE );
		_win_exp = ja_atoi(szExpWIN);
		_lose_exp = ja_atoi(szExpLOSE);
	}
	exp_t win_exp = _win_exp , lose_exp = _lose_exp;
	if(isEqual) win_exp=_lose_exp;//무승부이면 진것처럼 보상.

	//#--------------------------------------------------------------------------
	//총획득한 보너스 게임머니 계산.
	//#--------------------------------------------------------------------------
	jLIST_TYPEDEF_map(Tbl_User_id_t,game_money_t,gm_list);
	int32 iSize = this->m_GameRoomInfo.m_result_round_size();
	score_t prev_score=0;
	Tbl_User_id_t prev_uid= this->m_GameRoomInfo.m_result_round(0).m_tbl_roundresult().uid_attack();
	for(int i=0; i<iSize ; ++i)
	{
		const s_tbl_roundresult& rr = this->m_GameRoomInfo.m_result_round(i).m_tbl_roundresult();
		if(rr.uid_attack()!=prev_uid)
		{
			prev_score=0;
		}
		bool isWin = (rr.uid_attack() == win_score.first);
		if(isEqual) isWin=false;//무승부이면 진것처럼 보상.
		game_money_t gm = this->calc_game_money((EBatterHitType)rr.hit_type(), rr.score()-prev_score , isWin);

		if(gm_list.count(rr.uid_attack()))
		{
			gm_list[rr.uid_attack()] += gm;
		}
		else
		{
			gm_list[rr.uid_attack()] = gm;
		}
		prev_score = rr.score();
	}
	jCHECK(gm_list.size()==DEF_i_MAX_PLAYING_USER);
	game_money_t win_game_money,lose_game_money;
	if(gm_list.begin()->first == win_score.first)
	{
		if(isEqual) //무승부이면 진것처럼 보상.
		{
			win_game_money = gm_list.rbegin()->second;
		}
		else
			win_game_money = gm_list.begin()->second;

		lose_game_money = gm_list.rbegin()->second;
	}
	else
	{
		if(isEqual)//무승부이면 진것처럼 보상.
		{
			win_game_money = gm_list.begin()->second;
		}
		else
			win_game_money = gm_list.rbegin()->second;

		lose_game_money = gm_list.begin()->second;
	}

	rg.set_is_singlemode(false);//싱글모드는 클라에서 구현됨


#define set_result_game(win)\
	rg._jJOIN_3(set_,win,_uid)(win##_score.first);\
	s_game_play_info *gpi_##win = this->get_s_game_play_info(win##_score.first);\
	rg._jJOIN_3(set_,win,_better)(gpi_##win->m_tbl_team().pid_better());\
	rg._jJOIN_3(set_,win,_pitcher)(gpi_##win->m_tbl_team().pid_pitcher());\
	rg._jJOIN_3(set_,win,_team)(gpi_##win->m_tbl_team().db_id());\
	rg._jJOIN_3(set_,win,_score)(win##_score.second);\
	rg._jJOIN_3(set_,win,_reward_exp)(win##_exp);\
	rg._jJOIN_3(set_,win,_reward_gamemoney)(win##_game_money);\
	this->give_exp_to_team(win##_score.first,win##_exp);\

	for_each_WIN_LOSE(set_result_game);

	fname_t buf;
	
	double sec = time(0) - m_timer_game_start;
	rg.set_play_time_sec((int32)sec);
	jLOG("%s > play_time_sec = %d",jFUNC,rg.play_time_sec());
	rg.set_time_end(nOS::current_SYSTEMTIME(buf));

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
	jWARN(" code is strange!!! : iOrder=%d",iOrder)
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
