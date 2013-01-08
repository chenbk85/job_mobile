/* file : SAMPLE_Room.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-10 18:43:21
comp.: www.neowiz.com
title : 
desc : 

*/

#include "room.h"
#include "user.h"

#include "proto.h"
#include "stdafx.h"

#include "game/server.h"




#define jLAMDA_func_send_ans_team_match_ready(X,Z) Z(Room* , pRoom)
jLAMDA_for_each(func_send_ans_team_match_ready,User*)
{
	if(it->get_m_e_user_gps() >= eUGPS_GAME_READY) return;
	pRoom->send_ans_team_match_ready(it->id());
}
jLAMDA_end();

void time_out_req_team_match_ready(Room* pRoom)
{
	//20�ʰ� �����µ��� ���� ���ϹǷ� ������ ans_team_match_ready�� ����.
	boost::function<void(User*)> func = func_send_ans_team_match_ready(pRoom);
	pRoom->for_each_User(func);
}


//#--------------------------------------------------------------------------
// ������ʹ� MSG�� �ʼ� �Լ���.
//#--------------------------------------------------------------------------

/* -------------------------------------------------------------------------- */
Room::Room(int id, int category, int channel):
MSG::Room(id, category, channel)
{
	m_timer_game_start=0;
	jLOG("create room # %d" , id );
	m_GameRoomInfo.set_room_id(id);
	Room::reset_user_info();
}


/* -------------------------------------------------------------------------- */

Room::~Room()
{
	jLOG("destroy room #%d" , id() );
}

/* -------------------------------------------------------------------------- */
namespace 
{
	jLIST_TYPEDEF_map(room_id_t,Room*,g_mapRoom);
}

void 
Room::on_create()
{
	g_mapRoom[id()]=this;
	//�ʱ� �����Ұ�
	jFUNC_LOG2("Room",id());
}

/* -------------------------------------------------------------------------- */

void 
Room::on_destroy()
{
	g_mapRoom.erase(id());
	jFUNC_LOG2("Room",id());

	_Timer_Clear();

}


bool
Room::on_join(MSG::Session* participant) // true : ������ . false�� �����ϸ� UAnsAutoJoin�� UG���� Ŭ��� ������ �ʴ´�. 
// �� Ŭ�����忡���� �ڵ���ġ�� �����Ѱ�ó�� ó���ɼ� �ִ�.
{
	jFUNC_LOG2("Room",id());

	Sessions sessions_;get_sessions(sessions_);
	jLOG("sessions_.size() = %d ", sessions_.size());

	//���� ������ �ִ��ο�(2)���� ������ false�����Ͽ� ���ӽ��к���.
	jRETURN_ret(false,sessions_.size() < ((size_t)nG::i_MAX_PLAYING_USER->Get_int() ));

	User* pUser = dynamic_cast<User*>(participant);
	pUser->set_room(this);

	if (sessions_.size() == 0) 
	{
		// ���� ù��° �����ڰ� ������ ù��° ������ ���� �� ���� ������ ó��
		std::cerr << "first pUser\n";
	}
	else 
	{
		std::cerr << "not first pUser\n";
		//#--------------------------------------------------------------------------
		// ���� ���Ա⶧���� ���� �ٸ�������鿡�� �������� �˸���.
		//#--------------------------------------------------------------------------
		jMAKE_MSG_BS2X(sendMsg,sd,ans_join_room);
		sd->mutable_gri()->CopyFrom(m_GameRoomInfo);
		send_all_except_me(sendMsg, pUser);

		TIMER_CREATE_Room(this,time_out_req_team_match_ready, nG::i_TIME_ALL_PLAYER_NOT_READY->Get_int(), this);
	}
	return true;
}

/* -------------------------------------------------------------------------- */

int
Room::on_leave(MSG::Session* participant, bool /*kick*/)
{
	jFUNC_LOG2("Room",id());

	// ����ڰ� ���ӿ��� ������������ ó��
	// ������ ����� �����̸� �����ΰ�ó��.
	// �°��� ������ ������ �ɾ�� ����� ���� ö.

	//User* pUser = dynamic_cast<User*>(participant);

	// �߹� ���ο� ���� ��ü ���θ� �� ����ؼ� ó���ؾ� ��
	int ret = GAnsGameLeave::EXIT_RESERVATION;

	return ret; // kick_code
}

/* -------------------------------------------------------------------------- */

void
Room::get_info(std::string& info) // on_joinȣ���� msg���� ȣ���ϴµ� �̶� ���� gameroominfo�� �����Ұ�.
// ���⼭ ���õ� gameroominfo�� UAnsAutoJoin������ Ŭ�� ���޵ȴ�.
{
	jFUNC_LOG2("Room",id());

	m_GameRoomInfo.SerializeToString(&info);// �� ������ ä���� ��Ŷ�� ����� �����Ѵ�
}



//#--------------------------------------------------------------------------
// ������ʹ� Baseball�� ���� �Լ���.
//#--------------------------------------------------------------------------


void Room::reset_user_info() // �����÷������� �ʱ�ȭ�۾�.
{
  memset(m_sid_RunnerState,0,sizeof(m_sid_RunnerState));
  m_sid_RunnerState_index=0;

  jCHECK(nG::i_TOTAL_ROUND);
  if(nG::i_TOTAL_ROUND)
  {
	  m_i_TOTAL_ROUND =nG::i_TOTAL_ROUND->Get_int();
	  jIF(m_i_TOTAL_ROUND<=0)
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
	  jIF(m_i_ATTACK_CHANGE_ROUND <=0 || m_i_ATTACK_CHANGE_ROUND > m_i_TOTAL_ROUND)
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


Tbl_User_id_t Room::reset_user_info_for_gamestart() // ������ & �������
{
	Room::reset_user_info();

	int idx =0;

	if(nG::b_IS_FIRST_ATTACK_USER_IS_RANDOM->Get_bool())
	{
		idx = nMOB::make_random() % nG::i_MAX_PLAYING_USER->Get_int();
	}
	User* pUser = this->get_user(idx);
	jRETURN_ret(0,pUser);
	jLOG("%s > first user is =%d", __FUNCTION__, pUser->id());

	m_GameRoomInfo.set_m_attack_user(pUser->id());

	return pUser->db_id();
}

bool Room::is_full_user()
{
	Sessions sessions_;
	get_sessions(sessions_); 
	if(is_auto_play() && sessions_.size()>=1) return true;
	return sessions_.size()>=DEF_i_MAX_PLAYING_USER;	
}

static Sys_Runner_State_id_t _get_random_Sys_Runner_State_id(vector<Sys_Runner_State*> &vec )
{
	int idx = nMOB::random_my(0,vec.size()-1);
	jRETURN_ret(1, idx>=0 && ((size_t)idx)<vec.size());
	Sys_Runner_State* pSys = vec[idx];
	jRETURN_ret(1, pSys);
	return pSys->Get_index();
}

ERunnerStateRound get_round_state(round_t iRoundCount, Sys_Runner_State_id_t sid)
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

/* -------------------------------------------------------------------------- */
void timer_job_ans_game_round_start(Room* pRoom)
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
	TIMER_CREATE_Room(pRoom, time_out_req_pitcher_throw,GAME_PITCHER_THROW_WAIT_TIME_COUNT,pRoom);
#endif

}


void timer_job_ans_game_start(Room* pRoom)
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
	// ���� ������ġ ���.
	//#--------------------------------------------------------------------------
	ERunnerStateType eType = (ERunnerStateType)nMOB::random_my(eBEGIN_ERunnerStateType+1, eEND_ERunnerStateType-1);
	jCHECK(IsValid(eType));
	vector<Sys_Runner_State*> &vec = jCSV(Sys_Runner_State).m_INDEX_category[eType];
	jvRETURN(vec.size(), "eType = %s , jCSV(Sys_Runner_State).size=%d", ToString(eType), jCSV(Sys_Runner_State).size());
	pRoom->m_sid_RunnerState[0] = _get_random_Sys_Runner_State_id(vec);
	pRoom->m_sid_RunnerState[1] = _get_random_Sys_Runner_State_id(vec);
	jLOG("%s> ERunnerStateType= %s , Sys_Runner_State_id = %d, %d", jFUNC, ToString(eType),pRoom->m_sid_RunnerState[0],pRoom->m_sid_RunnerState[1] );

	TIMER_CREATE_Room(pRoom,  timer_job_ans_game_round_start , nG::i_TIME_ALL_PLAYER_READY->Get_int(),pRoom);
}

void Room::send_ans_team_match_ready(Tbl_User_id_t uid)
{
	s_game_play_info *gpi = get_s_game_play_info(uid);
	jRETURN(gpi);
	gpi->set_m_e_user_gps(eUGPS_GAME_READY);

	jMAKE_MSG_BS2X(sendMsg,sd,ans_team_match_ready);
	sd->set_uid(uid);
	this->send_all(sendMsg);

	if(this->is_full_user() && this->is_all_user_ready())
	{
		TIMER_CREATE_Room(this , timer_job_ans_game_start , nG::i_TIME_ALL_PLAYER_READY->Get_int(),this);
	}
}


bool Room::is_all_user_ready()
{
	jFOR_Room(it)
	{
		User* pUser = dynamic_cast<User*>(*it);
		if(!pUser->is_ready())
			return false;
	}
	return true;
}

User* Room::find_user(Tbl_User_id_t uid)
{
	jFOR_Room(it)
	{
		User* pUser = dynamic_cast<User*>(*it);
		if(pUser->db_id()==uid) return pUser;
	}
	return 0;

}

User* Room::get_other_user(Tbl_User_id_t uid)
{
	jFOR_Room(it)
	{
		User* pUser = dynamic_cast<User*>(*it);
		if(pUser->db_id()!=uid) return pUser;
	}
	return 0;
}

User* Room::get_user(int iOrder)
{
	jvRETURN_ret(0,iOrder < nG::i_MAX_PLAYING_USER->Get_int(),"iOrder = %d",iOrder);
	int i=0;
	jFOR_Room(it)
	{
		if((i++)!=iOrder) continue;
		return dynamic_cast<User*>(*it);
	}
	jWARN(" code is strange!!! : iOrder=%d",iOrder)
	return 0;//���� �̷����� ����� �Ѵ�.
}

User* Room::get_current_better()
{
	jFOR_Room(it)
	{
		User* pUser = dynamic_cast<User*>(*it);
		if(pUser->id() == get_attack_uid())
			return pUser;
	}
	return 0;
}

User* Room::get_current_pitcher()
{
	jFOR_Room(it)
	{
		User* pUser = dynamic_cast<User*>(*it);
		if(pUser->id() != get_attack_uid())
			return pUser;
	}
	return 0;
}


static void timer_handle(room_id_t rid,MOB_Timer_handler_t func,cstr szDebug,const boost::system::error_code& error)
{
	jRETURN(szDebug);
	if (error == boost::asio::error::operation_aborted) 
	{
		jLOG(_T("Timer was canceled : %s"),szDebug);
		return;
	}
	jvRETURN(!(error),"Timer error : %s",szDebug);
	jRETURN(g_mapRoom.count(rid));
	func();
}

//#--------------------------------------------------------------------------
void Room::Timer_Create(tcstr szTimer,MOB_Timer_handler_t& func,int iTime)
//#--------------------------------------------------------------------------
{
	jRETURN(szTimer);
	jRETURN(g_mapRoom.count(id() ) );
	jLOG("%s>%s( sec=%d ) ",jFUNC,szTimer,iTime);
	m_mapMOB_Timer_it it = m_mapMOB_Timer.find(szTimer);
	if(it!=m_mapMOB_Timer.end() && it->second)
	{
		MOB_Timer* pTimer= (MOB_Timer*)it->second;
		it->second=0;
		if(pTimer)
		{
			jLOG("%s > exist timer deleting: %s",jFUNC, szTimer);
			pTimer->cancel();
			SAFE_DELETE(pTimer);
		}
	}
	MOB_Timer* pTimer = new MOB_Timer(MSG::Server::io_service(), boost::posix_time::seconds(iTime));
	m_mapMOB_Timer[szTimer]=pTimer;
	pTimer->async_wait(boost::bind(timer_handle,id(),func,szTimer, boost::asio::placeholders::error));
	jLOG("pTimer->async_wait ok");
}

//#--------------------------------------------------------------------------
void Room::Timer_Delete(tcstr szTimer)
//#--------------------------------------------------------------------------
{
	jRETURN(szTimer);
	m_mapMOB_Timer_it it = m_mapMOB_Timer.find(szTimer);

	if(it==m_mapMOB_Timer.end() || !it->second)
	{
		jLOG("timer not found : %s",szTimer);
		return;
	}
	

	jLOG("%s> %s",jFUNC,szTimer);

	MOB_Timer* pTimer= (MOB_Timer*)it->second;
	it->second=0;
	pTimer->cancel();
	SAFE_DELETE(pTimer);
}


void Room::_Timer_Clear()
{
	m_mapMOB_Timer_it it;
	jFOR(m_mapMOB_Timer,it)
	{
		MOB_Timer* pTimer = (MOB_Timer*)it->second;
		jCONTINUE(pTimer);
		it->second=0;
		pTimer->cancel();
		SAFE_DELETE(pTimer);
	}
	m_mapMOB_Timer.clear();
}

game_money_t Room::calc_game_money(EBatterHitType e, score_t curr_score,bool isWin)
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


void Room::give_exp_to_team(Tbl_User_id_t uid, exp_t exp)//�ش� ������ �������鿡�� ����ġ����.
{
	s_game_play_info* gpi = this->get_s_game_play_info(uid);
	gpi->mutable_m_tbl_playerbetter()->set_exp(exp + gpi->mutable_m_tbl_playerbetter()->exp());
	gpi->mutable_m_tbl_playerpitcher()->set_exp(exp + gpi->mutable_m_tbl_playerpitcher()->exp());

}

void Room::calc_game_result()
{
		/*
	�߱� ���â
	���â���� : D:\svn\baseball\doc\design\��ȹ������\ĳ�־�߱� ����UI ��ȹ�� (2012_06_21)�����.pptx

		������� ���������� �ٻ���(1���Ǵ� 1�ð������������� ) ���������ܺ�����.
		�������� �����ۿϷ�� ��ȭâ�ٷΰ��� ������.

	4) ������ ����
		�·��� ����.
		Ÿ�ڴ� Ȩ������.
		������ ��Ʈ����ũ�ƿ���.
		EBHT_STANDOUT
		EBHT_SWINGOUT

	5) ����ġ�׷��� �׸���.
	Sys_PlayerLevel

	6) ���ʽ� ���ӸӴ�(xml) 

	*/
	
	s_tbl_result& rg = this->get_s_tbl_result();

	//#--------------------------------------------------------------------------
	// ���� ���� �������.
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

	bool isEqual = win_score.second == lose_score.second;//���º��̸� ����ó�� ����.

	//#--------------------------------------------------------------------------
	// ���ʽ� ����ġ ���.
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
	if(isEqual) win_exp=_lose_exp;//���º��̸� ����ó�� ����.

	//#--------------------------------------------------------------------------
	//��ȹ���� ���ʽ� ���ӸӴ� ���.
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
		if(isEqual) isWin=false;//���º��̸� ����ó�� ����.
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
		if(isEqual) //���º��̸� ����ó�� ����.
		{
			win_game_money = gm_list.rbegin()->second;
		}
		else
			win_game_money = gm_list.begin()->second;

		lose_game_money = gm_list.rbegin()->second;
	}
	else
	{
		if(isEqual)//���º��̸� ����ó�� ����.
		{
			win_game_money = gm_list.begin()->second;
		}
		else
			win_game_money = gm_list.rbegin()->second;

		lose_game_money = gm_list.begin()->second;
	}

	rg.set_is_singlemode(false);//�̱۸��� Ŭ�󿡼� ������


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

