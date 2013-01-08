/* file : PK_Room.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-10 18:43:21
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PK_Room.h"

void PK_Room::MOB_OnCreate()
{
	//GameMgr생성
	///////////////////////////////////
	//m_CGameMgr = new CGameMgr;

	///////////////////////////////////
}
void PK_Room::MOB_OnDelete()
{

}
void PK_Room::User_Join(PK_Plugin_Connection* pCon, GReqGameEnter* p)
{
	jLOG(jFUNC1 _T("m_gid=%d"),pCon->m_gid);

	if(!this->m_UserList.size())
	{ //유저가 아무도 없으므로 최초 방정보 세팅하자.
		
		string tmpString;
		char tmpChar[256];
		tmpString.append("9|9|9|9|9|9|9|한판|3|0|666|1|5252|0");
		m_CGameMgr.OnCreateRoom(tmpChar, 0);
		m_CGameMgr.CreateObject();

		RCRoomData *pRoomData = &m_CGameMgr.GetData();
		jRETURN(pRoomData);
		pRoomData->m_lRoomIndex = p->roomid();
	}

	/////////////////////
	//add user
	RCUser user;
	user.Clear();
	user.m_pCon = pCon;
	user.m_pCon->m_gid = p->gameuserinfo().memberinfo().gameid();

	user.m_lUSN = p->gameuserinfo().memberinfo().gameid();
	user.m_lJumin=0;
	user.m_lFirstUSN=111111111;
	user.m_lAgeIndex=1;
	user.m_lJobIndex=1;
	user.m_lRegionIndex=1;
	user.m_lGuildIndex=1;
	user.m_lMemberIndex=1;
	user.m_lClientIP=1;
	user.m_lGatewayIP=1;
	user.m_lMacAddress=1;
	user.m_sMobileInfo="android";
	user.m_sAuthKey="123456";

	user.m_nIndex=-1;
	user.m_sNickName=p->gameuserinfo().memberinfo().nickname();//"aaa";
	user.m_sUserID="bbb";
	user.m_lSex=0;
	user.m_llCMoney=99999;
	user.m_llFMoney=99999;
	user.m_llSafeMoney=999;
	user.m_lCLevel=1;
	user.m_llPlastAllinDate=111;
	user.m_llPlastLogonDay=111;
	user.m_lMTodayPlayCount=11;
	user.m_lMTodayPlayTime=1;
	user.m_lPTotalPlayCount=1;
	user.m_cRefill.m_lPLevel=1;
	user.m_llPExtMoney=1111;
	user.m_llPExtendDate=1111;
	user.m_llPBonusDate=111;
	user.m_lMMonthPlayCount=11;
	user.m_lMMonthPlayTime=11;
	user.m_cWinLose.m_lWin=11;
	user.m_cWinLose.m_lLose=11;
	user.m_lGDisCnt=11;
	user.m_llGlastLogonDay=111;
	user.m_llGRegDate=111;
	user.m_llGFirstPlayDate=111;
	user.m_lGTodayPlayCount=111;
	user.m_lGTodayPlayTime=111;
	user.m_lGTotalPlayCount=111;
	user.m_lGTotalPlayTime=111;
	user.m_lGAllinCnt=1111;
	user.m_lGAllinOut=1111;
	user.m_llGLastAllinDate=111;
	user.m_cWinLose_Today.m_lWin=11;
	user.m_cWinLose_Today.m_lLose=11;
	user.m_llGTodayMoney=11;
	user.m_lFourCardCnt=11;
	user.m_lStraightFlushCnt=111;
	user.m_lRoyalStraightFlushCnt=11;
	user.m_nReserve01=111;
	user.m_nReserve02=11;
	user.m_ItemList.Clear();
	user.m_llJoinDate=1111;
	user.m_llPlayDate=1111;

	/////////////////////
	nMOB::room_user_id_t ruid = m_UserList.size();
	jASSERT(ruid+1 <= iMAX_ROOM_USER);
	m_UserList.push_back(pCon);
	m_CGameMgr.OnAddUserInRoom(&user);
	//m_CGameMgr.SetUserPos(&user, ruid, 0);

}

void PK_Room::User_JoinAns(PK_Plugin_Connection* pCon, GAnsGameEnter* p)
{
	jLOG(jFUNC1 _T("m_gid=%d"),pCon->m_gid);


	GameRoomInfo* pgameroominfo =  p->mutable_gameroominfo();

	ug_room_id_t urid = pCon->Get_room_id();
	
	pgameroominfo->set_roomid(urid);

	pgameroominfo->set_pointmoney(1234);

	//두명 이상일때게임 시작 가능상태로 변경
	pgameroominfo->set_enablestart((this->m_UserList.size() >= 2) ? true : false);

	::google::protobuf::RepeatedPtrField< GameUserInfo >::iterator gameuserinfo_iterator_begin = pgameroominfo->mutable_gameuserinfo()->begin();
	::google::protobuf::RepeatedPtrField< GameUserInfo >::iterator gameuserinfo_iterator_end = pgameroominfo->mutable_gameuserinfo()->end();

	for(; gameuserinfo_iterator_begin != gameuserinfo_iterator_end ; ++gameuserinfo_iterator_begin)
	{
		GameInfo* pgameinfo =  gameuserinfo_iterator_begin->mutable_gameinfo();
		MemberInfo* pmemberinfo = gameuserinfo_iterator_begin->mutable_memberinfo();
		
		//임시로 값 채울것
		//UG에서 채워줄 값들이다.
		pgameinfo->set_allincnt(1);
		pgameinfo->set_gameid(123);
		pgameinfo->set_gameindex(0);
		pgameinfo->set_level("1");
		pgameinfo->set_losecnt(1);
		pgameinfo->set_money("1111");
		pgameinfo->set_wincnt(1);

		pmemberinfo->set_gameid(123);
		pmemberinfo->set_nickname("aaa");
		pmemberinfo->set_avatarurl("testurl");
	}
}

void PK_Room::User_Leave(PK_Plugin_Connection* pCon, GReqGameLeave* p)
{
	jLOG(jFUNC1 _T("m_gid=%d"),pCon->m_gid);

	if(this->m_UserList.size())
		return;

	m_CGameMgr.OnRemoveUser(p->gameid());
	m_CGameMgr.UserDisconnect(p->gameid(), false, true, true);
}

//void PK_Room::Game_Start(PK_Plugin_Connection* pCon, pp_game_id_t game_id)
void PK_Room::Game_Start(PK_Plugin_Connection* pCon, s_req_send_start* msg)
{
	//jASSERT(pCon->m_gid==game_id);

	jLOG(jFUNC1 _T("m_gid=%d"),pCon->m_gid);

	msg->set_gameid(pCon->m_gid);

	m_CGameMgr.OnRcvStart(msg);
}


void PK_Room::User_SelectCard(PK_Plugin_Connection* pCon, s_req_send_select_card* msg)
{
	jASSERT(pCon != NULL);
	jLOG(jFUNC1 _T("selected card index : %d"), msg->m_lcardidx());

	//MsgCS_SelectedCardReq msg;

	//msg.m_lCardIdx = cardidx;

	m_CGameMgr.OnRcvSelectedCardReq(pCon->m_gid, msg);
}

void PK_Room::User_Betting(PK_Plugin_Connection* pCon, s_req_betting* msg)
{
	jASSERT(pCon != NULL);
	jLOG(jFUNC1 _T("Betting type : %d"), msg->m_lbettype());

	//MsgCS_BettingReq msg;

	//msg.m_lBetType = bettingtype;

	m_CGameMgr.OnRcvBettingReq(pCon->m_gid, msg);
}

void PK_Room::Pong(PK_Plugin_Connection* pCon)
{	
	jASSERT(pCon != NULL);
	jLOG(jFUNC1 _T("gameid : %d"), pCon->m_gid);

	GAnsProtocol sendMsg;

	sendMsg.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);
	GLAnsGameProtocol* packet = sendMsg.mutable_ansgameprotocol();
	packet->set_type(GLAnsGameProtocol_Type_ans_pong);

	pCon->send_me(sendMsg);
}

void PK_Room::User_Entry(PK_Plugin_Connection* pCon, s_req_entry* entry)
{
	GAnsProtocol sendMsg;

	sendMsg.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);
	GLAnsGameProtocol* packet = sendMsg.mutable_ansgameprotocol();
	packet->set_type(GLAnsGameProtocol_Type_ans_entry);

	/*
	MsgCS_Entry msg;

	msg.m_bWelcomeSound = entry->m_bwelcomesound();
	msg.m_lCLevel = entry->m_lclevel();
	msg.m_lSex = entry->m_lsex();
	msg.m_lSoundType = entry->m_lsoundtype();
	msg.m_nVersion = entry->m_nversion();
	msg.m_sAvt = entry->m_savt();
	msg.m_sNickName = entry->m_snickname();
	*/

	pCon->m_gid = entry->gameid();

	m_CGameMgr.OnRcvEntry(pCon, pCon->m_gid, entry);
}

void PK_Room::Continue(PK_Plugin_Connection* pCon, s_req_continue* pContinue)
{
	jRETURN(pContinue);
	jASSERT(pCon != NULL);
	jLOG(jFUNC1 _T("%d"),pContinue->m_lexit());

	m_CGameMgr.OnRcvContinue(pCon->m_gid, NULL);//구조체 필요없음
}

void PK_Room::RuleSet(PK_Plugin_Connection* pCon, s_req_ruleset* rule)
{
	jRETURN(rule);
	jASSERT(pCon != NULL);
	jLOG(jFUNC1 _T("%d"),rule->m_nruleidx());

	//MsgCS_RuleSet msg;
	//msg.m_nRuleIdx = rule->m_nruleidx();

	m_CGameMgr.OnRcvRuleSet(pCon->m_gid, rule);
}	

void PK_Room::JoboSet(PK_Plugin_Connection* pCon, s_req_jokboset* jokbo)
{	
	jRETURN(jokbo);
	jASSERT(pCon != NULL);
	jLOG(jFUNC1 _T("jokbo setting : %d, %d, %d, %d, %d"),
		jokbo->m_lkey1(),
		jokbo->m_lkey2(),
		jokbo->m_lkey3(),
		jokbo->m_lkey4(),
		jokbo->m_lkey5());

	/*
	MsgCS_JokboSet msg;
	msg.m_lKey1 = jokbo->m_lkey1();
	msg.m_lKey2 = jokbo->m_lkey2();
	msg.m_lKey3 = jokbo->m_lkey3();
	msg.m_lKey4 = jokbo->m_lkey4();
	msg.m_lKey5 = jokbo->m_lkey5();
	*/

	m_CGameMgr.OnRcvJokboSet(pCon->m_gid, jokbo);
}

void PK_Room::ACK(PK_Plugin_Connection* pCon, s_req_ack* ack)
{
	jRETURN(ack);
	jASSERT(pCon != NULL);
	jLOG(jFUNC1 _T("ack : %d"), ack->m_ntagid());

	//MsgCS_Ack msg;
	//msg.m_nTagID = ack->m_ntagid();

	m_CGameMgr.OnRcvAck(pCon->m_gid, ack);
}

void PK_Room::User_ChoiceRemoveCard(PK_Plugin_Connection* pCon, s_req_choiceremovecard* choiceremovecard)
{
	jRETURN(choiceremovecard);
	jASSERT(pCon != NULL);
	jLOG(jFUNC1 _T("choiceremovecard : %d"),choiceremovecard->m_nremovecardindex());

	/*
	MsgCS_ChoiceRemoveCard msg;
	msg.m_lUSN = choiceremovecard->m_lusn();
	msg.m_nRemoveCardIndex =choiceremovecard->m_nremovecardindex();
	*/

	m_CGameMgr.OnRcvChoiceRemoveCard(pCon->m_gid, choiceremovecard);
}

void PK_Room::UserDisconnect(int32 gameid)
{
	//m_CGameMgr.OnUserDisconnectInRoomNotify(gameid);

	jLOG(jFUNC1 _T("m_gid=%d"),gameid);

	if(!this->m_UserList.size())
		return;

	m_CGameMgr.OnRemoveUser(gameid);
	m_CGameMgr.UserDisconnect(gameid, false, true, true);
}

void PK_Room::User_Purge(PK_Plugin_Connection* pCon, s_req_purge* purge)
{	
	jRETURN(purge);
	jASSERT(pCon != NULL);
	jLOG(jFUNC1 _T("gameid : %d, type : %d"),purge->m_lpurgeusn(), purge->m_ltype());

	/*
	MsgCS_Purge msg;

	msg.m_lPurgeUSN = purge->m_lpurgeusn();
	msg.m_lType = purge->m_ltype();
	*/

	m_CGameMgr.OnRcvPurge(pCon->m_gid, purge);
}

void PK_Room::User_Abuse(PK_Plugin_Connection* pCon, s_req_abuse* abuse)
{
	jRETURN(abuse);
	jASSERT(pCon != NULL);
	jLOG(jFUNC1 _T("type : %d, day : %d"),abuse->m_ltype(), abuse->m_sday());

	/*
	MsgCS_Abuse msg;

	msg.m_lType = abuse->m_ltype();
	msg.m_sDay = abuse->m_sday();
	*/

	m_CGameMgr.OnRcvAbuse(pCon->m_gid, abuse);
}

void PK_Room::User_Observe(PK_Plugin_Connection* pCon, s_req_observe* observe)
{
	jRETURN(observe);
	jASSERT(pCon != NULL);
	jLOG(jFUNC1 _T(""));

	//MsgCS_Observe msg;

	m_CGameMgr.OnRcvObserve(pCon->m_gid, observe);
}

void PK_Room::User_ExitQueue(PK_Plugin_Connection* pCon, s_req_exitque* exitque)
{
	jRETURN(exitque);
	jASSERT(pCon != NULL);
	jLOG(jFUNC1 _T("exit : %d, action : %d"),exitque->m_lexit(), exitque->m_baction());

	/*
	MsgCS_ExitQue msg;

	msg.m_bAction = exitque->m_baction();
	msg.m_lExit = exitque->m_lexit();
	*/

	m_CGameMgr.OnRcvExitQue(pCon->m_gid, exitque);
}

void PK_Room::User_SoundType(PK_Plugin_Connection* pCon, s_req_soundtype* soundtype)
{
	jRETURN(soundtype);
	jASSERT(pCon != NULL);
	jLOG(jFUNC1 _T("soundtype : %d"),soundtype->m_lsoundtype());

	/*
	MsgCS_SoundType msg;

	msg.m_lSoundType = soundtype->m_lsoundtype();
	*/

	m_CGameMgr.OnRcvSoundType(pCon->m_gid, soundtype);
}