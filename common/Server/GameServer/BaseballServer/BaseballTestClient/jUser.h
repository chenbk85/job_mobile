/* file : jUser.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-20 15:34:01
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __jUser_header__
#define __jUser_header__
#pragma once

/*
#define for_each_EUserGPS(X)\
X(eGPS_LOGOUT			," 네트웍접속해제")\
X(eGPS_LOGIN			,"UserGate서버에접속")\
X(eGPS_SHOP				,"상점입장")\
X(eGPS_UserGateServer	,"여기까지가 유저게이트서버에서의 상태")\
\
X(eGPS_GAMEROOM			,"BaseballServer에접속 대기방상태")\
X(eGPS_GAME_START		,"게임시작")\
X(eGPS_GAME_ROUND_START	,"게임시작")\
X(eGPS_PITCHER_THROW	,"투수가 공을 던졌다")\
X(eGPS_BETTER_HIT		,"타자가 공을 쳤다")\
X(eGPS_GAMEROOM_PRE_LEAVE,"로비로 갈려고 대기중인 상태")\
X(eGPS_BaseballServer	,"여기까지가 게임서버접속상태")\

jDEFINE_ENUM_CODE2(EUserGPS);
*/


struct jUser : public jUser_base
{
	jUser();

	jIE* m_peSession;// 소켓 session 연결 객체
	tstring m_id;
	Tbl_User_id_t game_id;
	Tbl_User_id_t db_id(){ return game_id;}


	s_ans_pitcher_throw		m_ans_pitcher_throw;
	s_ans_better_hit		m_ans_better_hit;

#	define UAnsProtocol_member(ENUM,STRUCT,VAR) STRUCT m_##STRUCT;
	for_each_UAnsProtocol(UAnsProtocol_member);


	void do_play_client_production(){}
	void calc_better_hit(const s_req_better_hit & rbh);
	void send_req_result_better_hit(const s_ans_better_hit& abh);

	bool is_allow_rematch;
	bool is_allow_rematch_other;
	int32 m_single_play_id;//싱글매치 시작할때 서버에서 승패를 저장관련하여 검증하기위한 서버id
	void reset_user_info()
	{
		jUser_base::reset_user_info();
		is_allow_rematch=false;
		is_allow_rematch_other=false;
		m_single_play_id=0;
	}

	ERunnerStateRound m_ERunnerStateRound;
	EBatterHitType m_EBatterHitType;

	//#--------------------------------------------------------------------------
	//  퀘스트 관련.
	//#--------------------------------------------------------------------------
	Sys_Quest_id_t m_quest_sid;
	int64			m_quest_id;

	//#--------------------------------------------------------------------------
	//디버깅용.
	//#--------------------------------------------------------------------------
	jLIST_TYPEDEF_map(astring,int,m_recv_table_count);
	jLIST_TYPEDEF_map(astring,int,m_ServerInfoRecvState);

	//#--------------------------------------------------------------------------
	//[AutoPlay]
	//#--------------------------------------------------------------------------
	int m_iAutoMatchCount; // pv_IsAutoPlay가 true일때 AnsDB에서 pv_AutoMatchCount값이 세팅된다. 만약 서버에러가 발생하면 -1이 세팅됨.
	bool IsAutoPlay(){ return m_iAutoMatchCount>0;}
	bool IsAutoPlayError(){ return m_iAutoMatchCount<0;}

	int m_iAutoReJoinCount; // pv_IsAutoPlay가 true일때 AnsDB에서 pv_AutoReJoinCount값이 세팅된다.
	void Init_AutoReConnectCount(int iCount);
	int Get_AutoReConnectCount();
	void Set_AutoReConnectCount(int iCount);

};



#endif // __jUser_header__
