/* file : PK_Room.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-10 18:43:19
comp.: www.neowiz.com
title : 
desc : 

*/
#ifndef __PK_Room_header__
#define __PK_Room_header__
#pragma once

#include "PB_Server/Manager/GameMgr_Poker.h"

//#--------------------------------------------------------------------------
struct PK_Room
//#--------------------------------------------------------------------------
{
	MOB_HEADER_ROOM(PK_Plugin_Connection);
public:
	void User_Join(PK_Plugin_Connection*, GReqGameEnter*);
	void User_JoinAns(PK_Plugin_Connection* , GAnsGameEnter*);
	void User_Leave(PK_Plugin_Connection* pCon, GReqGameLeave* p);
	
	//void Game_Start(PK_Plugin_Connection* pCon, pp_game_id_t game_id);
	void Game_Start(PK_Plugin_Connection* pCon, s_req_send_start* msg);
	//void User_SelectCard(PK_Plugin_Connection*, int32 cardidx);//유저 카드 선택했을때 인텍스와 함께 전달
	void User_SelectCard(PK_Plugin_Connection* pCon, s_req_send_select_card* msg);
	//void User_Betting(PK_Plugin_Connection* pCon, int32 bettingtype);//베팅 타입 설정
	void User_Betting(PK_Plugin_Connection* pCon, s_req_betting* msg);

	void Pong(PK_Plugin_Connection* pCon);

	void User_Entry(PK_Plugin_Connection* pCon, s_req_entry* entry);//유저 엔트리 전달
	void Continue(PK_Plugin_Connection* pCon, s_req_continue* pContinue); //게임 계속할지 결정
	void RuleSet(PK_Plugin_Connection* pCon, s_req_ruleset* ruleset); // 게임룰 세팅
	void JoboSet(PK_Plugin_Connection* pCon, s_req_jokboset* jokbo); // 족보세팅 (치트!!!!)
	void ACK(PK_Plugin_Connection* pCon, s_req_ack* ack); // 상태별 알림
	void User_ChoiceRemoveCard(PK_Plugin_Connection* pCon, s_req_choiceremovecard* choiceremovecard); //초이스룰 일때 버릴카드 선택
	void User_Purge(PK_Plugin_Connection* pCon, s_req_purge* purge); //강제퇴장 요청
	void User_ExitQueue(PK_Plugin_Connection* pCon, s_req_exitque* exitque);
	void User_SoundType(PK_Plugin_Connection* pCon, s_req_soundtype* soundtype);

	void User_Abuse(PK_Plugin_Connection* pCon, s_req_abuse* abuse);
	void User_Observe(PK_Plugin_Connection* pCon, s_req_observe* observe);

	void UserDisconnect(int32 gameid); // 유저 접속끊겼을때

	//게임매니저 (각종데이터, 룰 포함)
	CGameMgr m_CGameMgr;
};


#endif // __PK_Room_header__
