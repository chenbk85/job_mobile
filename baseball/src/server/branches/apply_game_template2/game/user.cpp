/* file : SAMPLE_Room.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-10 18:43:21
comp.: www.neowiz.com
title : 
desc : 

*/

#include "user.h"

#include "proto.h"
#include "stdafx.h"
#include "room.h"

/* -------------------------------------------------------------------------- */

User::User(int id):
  MSG::Session(id)
{
	m_iCount_req_timer_start=0;
	room_=0;
	m_temp_s_game_play_info=0;
	jFUNC_LOG();

}

/* -------------------------------------------------------------------------- */

User::~User()
{
	jFUNC_LOG();

}

void User::reset_user_info()
{
	is_allow_rematch=false;

}

/* -------------------------------------------------------------------------- */

void 
User::set_info(const std::string& info)
{
	jFUNC_LOG();

    // 사용자가 들어오면 자동으로 전달된다. 내용을 복사해서 넣어놓으면 됨
	// gateway에서 Database::get_gameuserinfo()에 의해 세팅된 값을 받는다.
	s_game_play_info* p =0;
	if(!room_ && !m_temp_s_game_play_info)
	{
		m_temp_s_game_play_info = new s_game_play_info;
	}
	p = get_s_game_play_info();

	p->ParseFromString(info);
	nProtoHelper::message_print(p->m_tbl_user());
	nProtoHelper::message_print(p->m_tbl_team(),db_id());
}

/* -------------------------------------------------------------------------- */

void
User::get_info(GameUserInfo& info)
{
	jFUNC_LOG();

    // 맴버 정보 시리얼라이브해서 패킷에 로딩
    member_info_.SerializeToString(info.mutable_member_info());

    // 게임 정보 복사해서 패킷에 로딩
    info.mutable_game_info()->CopyFrom(game_info_);
}

/* -------------------------------------------------------------------------- */

bool
User::on_game_protocol(const std::string& message)
{
	//jFUNC_LOG();

    // 클라이언트에서 전송되는 게임에 관련된 메시지가 들어있다
    Client_BaseballServer request;

    request.ParseFromString(message);

	//std::cout << endl << __FUNCTION__ << " : type = "  << request.type() << endl;
    switch(request.type())
    {
#define jPARSE_PROTO_MESSAGE_X2BS(DOMAIN,NAME,ORDER)\
case _jJOIN_3(DOMAIN,_Type_,NAME):\
		{\
		jLOG("\n\nRECV>"  #DOMAIN  "::" #NAME " : %lld \n\n",db_id());\
		bool CB_Client_BaseballServer(User* pUser,const s_##NAME&);\
		return CB_Client_BaseballServer(this,request.m_##NAME());\
	}\

		for_each_Client_BaseballServer(jPARSE_PROTO_MESSAGE_X2BS);
    default:
		jWARN("[error] unkown packet");
        break;
    }

    return false;
}


/* -------------------------------------------------------------------------- */

void
User::on_connect()
{
	jLOG("%s : uid = %d", jFUNC1 , db_id());

}

/* -------------------------------------------------------------------------- */
	
void
User::on_disconnect(const char* reason, int code)
{
	jLOG("%s : uid = %d", jFUNC1 , db_id());

	User* pOtherUser = room_->get_other_user( this->db_id() );
	jRETURN(pOtherUser);

	EUserGPS e = (EUserGPS)pOtherUser->get_m_e_user_gps() ;
	jLOG("OtherUser state = %s", ToString(e));
	if(pOtherUser->get_m_e_user_gps() <eUGPS_GAME_START || pOtherUser->get_m_e_user_gps() >= eUGPS_GAME_END)
	{
		// 게임을 안하는 상태이면 다른유저도 로비로 보내자.
		pOtherUser->quit(GAnsGameLeave::EXIT_RESERVATION);
	}
	else // 게임플레이중 비정상 종료.
	{
		//jTODO : DB에 비정상 접속해제 카운트를 증가시켜야함.
		jLOG("비정상 종료: uid=%lld",db_id());
		jMAKE_MSG_BS2UG(sendMsg, sd, bs2ug_add_discon_tot);
		sd->set_discon_uid(this->db_id());
		pOtherUser->room_->send_to_ug(pOtherUser->db_id(), sendMsg);
		pOtherUser->room_->m_GameRoomInfo.set_m_is_auto_play(true);
	}

}

/* -------------------------------------------------------------------------- */

bool 
User::on_game_enter(const GReqGameEnter& enter)
{
	jLOG("%s : uid = %d", jFUNC1 , db_id());


    // 사용자가 들어올때의 패킷 처리
    // MSG 내부에서 이미 룸 생성 과정이나 기타 과정을 처리해 놓은 상태임
    return false;
}

/* -------------------------------------------------------------------------- */

bool 
User::on_game_leave(const GReqGameLeave& leave)
{
	jLOG("%s : uid = %d", jFUNC1 , db_id());

    // 무조건 나가로록 설정. jTODO어뷰징에대해서만 고려하자.
// 	EUserGPS gps = get_m_e_user_gps() ;
// 	jvRETURN_ret(false, gps <= eUGPS_LABEL_GAME_NOT_QUIT || gps >= eUGPS_GAME_END , "error client is not quit this state")

    return true;// true이면 게임중에 나갈수 있는상태이고 false이면 게임중에 못나가는 상태다.
	// true를 리턴하면 그때사 room::on_leave()호출됨.
}

/* -------------------------------------------------------------------------- */


bool
User::on_plug(const GReqPlug& plug)
{
	jWARN("%s : uid = %d", jFUNC1 , db_id());


    // 사용자 회선이 다시 돌아옴
	this->quit(GAnsGameLeave::EXIT_RESERVATION);

    return false;
}

/* -------------------------------------------------------------------------- */

bool
User::on_detach(const GReqDetach& detach)
{
	jWARN("%s : uid = %d", jFUNC1 , db_id());
	this->quit(GAnsGameLeave::EXIT_RESERVATION);

    // 사용자 회선이 잠시 떨어져 나감

    return false;
}


// 방에 유저들어온후  user::on_entergame() -> room::on_join() -> user::on_jjoined();
bool User::on_joined(const GAnsGameEnter& enter)
{
	jLOG("%s : uid = %d", jFUNC1 , db_id());

	return true; 
}


bool User::on_database(const AnsDB& recvData)
{
	//jFUNC_LOG();
	jRETURN_ret(false, recvData.seq()==IS_BS2UG_PACKET);
	UserGateServer_BaseballServer rd;
	rd.ParseFromString(recvData.result());

	switch(rd.type())
	{
#define jPARSE_PROTO_MESSAGE_UG2BS(DOMAIN,NAME,ORDER)\
	case _jJOIN_3(DOMAIN,_Type_,NAME):\
	{\
		jLOG("\n\nRecv : %s(%s) :uid = %d", #DOMAIN , #NAME, db_id());\
		bool CB_##DOMAIN(User* ,const s_##NAME&);\
		return CB_##DOMAIN(this,rd.m_##NAME());\
	}\

	for_each_UserGateServer_BaseballServer(jPARSE_PROTO_MESSAGE_UG2BS);

	default:
		{
			jERROR("\n%s unkown packet : type=%d",jFUNC1 , rd.type());
		}
	}
	return false;
}

bool User::is_attackable()
{ 
	return room_ && id() == room_->get_attack_uid();
}

s_game_play_info* User::get_s_game_play_info()
{ 
	if(!room_) return m_temp_s_game_play_info;
	return room_->get_s_game_play_info(id());
}

void User::set_room(Room *pRoom)		
{   
	jFUNC_LOG();
	room_ = pRoom;

	jCHECK(m_temp_s_game_play_info);
	s_game_play_info* gpi = room_->get_s_game_play_info(id());
	gpi->CopyFrom(*m_temp_s_game_play_info);
	gpi->set_m_e_user_gps(eUGPS_GAMEROOM);
	SAFE_DELETE(m_temp_s_game_play_info);

}


EUserGPS User::get_m_e_user_gps()
{
	jRETURN_ret(eUGPS_BS_USER_IS_ILLEGAL,room_);
	s_game_play_info *gpi = room_->get_s_game_play_info(id());
	jRETURN_ret(eUGPS_BS_USER_IS_ILLEGAL,gpi);
	return (EUserGPS)gpi->m_e_user_gps();
}

void User::set_m_e_user_gps(EUserGPS e)
{
	jRETURN(room_);
	s_game_play_info *gpi = room_->get_s_game_play_info(id());
	jRETURN(gpi);
	gpi->set_m_e_user_gps(e);
}
bool User::is_illegal()// 비정상 유저인지 체크. 강제종료대상 유저이다. 모든 보내오는 패킷 무시.
{
	jRETURN_ret(true,room_);
	s_game_play_info *gpi = room_->get_s_game_play_info(id());
	jRETURN_ret(true,gpi);
	return gpi->m_e_user_gps() == eUGPS_BS_USER_IS_ILLEGAL;
}

bool User::check_breaking_ball_type(int32 breaking_ball_type)
{
	//jTODO 자신이 가지고 있는 변화구 스킬인지 체크.
	return breaking_ball_type > eBEGIN_EPlayerBreakingBall && breaking_ball_type < eEND_EPlayerBreakingBall;
}


namespace nBASE_BALL
{
	void make_random_better_hit(s_req_better_hit* rd)
	{
		//jTODO
		s_better_hit_info info;
		s_better_hit_info_verify verify;

		rd->mutable_info()->CopyFrom(info);
		rd->mutable_verify()->CopyFrom(verify);
	}
	void make_random_pitcher_throw(s_req_pitcher_throw* rd)
	{
		//jTODO
		s_pitcher_throw_info info;
		s_pitcher_throw_info_verify verify;

		rd->mutable_info()->CopyFrom(info);
		rd->mutable_verify()->CopyFrom(verify);
	}

}
