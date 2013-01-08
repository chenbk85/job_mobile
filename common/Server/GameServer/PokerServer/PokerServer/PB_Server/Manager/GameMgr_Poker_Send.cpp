//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"
#include <ctime>

#include "GameMgr_Poker.h"

#include "../util/util.h"
 
#include "../../Protocol Buffers/Poker/AdlGameCommon.h"

#include "gameLogic.pb.h"

using namespace adl;

#if defined(_Poker)

//----------------------------------------------------------------------------------------------------
void CGameMgr::SendUserJoinAns(long lUSN, int nEnter, int nSet)
{

// 	nMOB::ug_room_id_t rid = 1234;
// 	PK_Room* pRoom = g_PK_Plugin_NetIOModel.Room_Find(rid);
// 	jRETURN(pRoom);

	RCUser* pUser=FindUser(lUSN);
	if(pUser==NULL) return;

	__int64 lCurrentTime=GetCurrentSystemTime();
	MsgSC_UserJoinAns msg;
	msg.m_lState=m_cRCRoomData.m_lState;
	msg.m_nEnter=nEnter;
	msg.m_nSet=nSet;
	msg.m_lChannel_idx=m_cGameInfo.m_lChannel_idx;
	msg.m_lOwnerUSN=m_cGameInfo.m_lOwnerUSN;
	msg.m_lBossUSN=m_cGameInfo.m_lBossUSN;
	msg.m_nRoomPurgeCnt=0;
	msg.m_option=m_cRCRoomData.m_option;
	m_cGameInfo.m_cvtJoin.AddVector(lUSN, nSet);
	//msg.m_RCUserMe=(*pUser);

	//PayloadSC pld(PayloadSC::msgUserJoinAns_Tag, msg);
	//SendToUser(lUSN, pld);
	SendToUser(lUSN, GLAnsGameProtocol_Type_userjoinans, &msg);
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendEntryAns(long lUSN, int nIndex, bool bWelcomeSound)
{
	MsgSC_EntryAns msg;
	msg.m_lUSN=lUSN;
	msg.m_nIndex=nIndex;
	msg.m_lOwnerUSN=m_cGameInfo.m_lOwnerUSN;
	msg.m_tblUI.resize(m_cRCRoomData.m_option.m_lMaxPlayerUserCnt);
	for(int i=0; i<m_cRCRoomData.m_tblUI.size(); i++){
		msg.m_tblUI[i]=m_cRCRoomData.m_tblUI[i];
	}
	msg.m_tblMoney.resize(m_cRCRoomData.m_option.m_lMaxPlayerUserCnt);
	for(int i=0; i<m_cRCRoomData.m_tblMoney.size(); i++){
		msg.m_tblMoney[i]=m_cRCRoomData.m_tblMoney[i];
	}
	msg.m_bWelcomeSound=bWelcomeSound;
	msg.m_lObserveCnt=m_vtObserveUSN.size(); 

//	Store_WinLoseCntVector( msg.m_vWinLoseCnt );

	//PayloadSC pld(PayloadSC::msgEntryAns_Tag, msg);
	//SendToAll(pld);
	SendToAll(GLAnsGameProtocol_Type_ans_entry, &msg);

	long lState=m_cRCRoomData.m_lState;
	switch(lState)
	{
	case GAMESTATE_INVALID: break;
	case GAMESTATE_READY: break;
	case GAMESTATE_START: break;
	case GAMESTATE_SELECT:
	case GAMESTATE_PLAY:
	case GAMESTATE_RESULT:
	case GAMESTATE_SAVE:
		{
			CardTable tblCard;
			CardDataSet(tblCard, lState);
			SendCardData(lUSN, tblCard);
			SendAnteMoney();
		}
		break;
	default: break;
	}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendCardData(long lUSN, CardTable &tblCard)
{
	MsgSC_CardData msg;
	msg.m_nDealCnt=m_cGameInfo.m_lDealtCardCount;
	msg.m_lCardsDealt=m_cGameInfo.m_lCardsDealt;
	msg.m_tblCard.resize(m_cRCRoomData.m_option.m_lMaxPlayerCardCnt);
	for(int i=0; i<m_cRCRoomData.m_tblCard.size(); i++){
	//	msg.m_tblCard[i]=m_cRCRoomData.m_tblCard[i];
		msg.m_tblCard[i]=tblCard[i];
	}
	
	msg.m_tblMoney.resize(m_cRCRoomData.m_option.m_lMaxPlayerUserCnt);
	for(int i=0; i<m_cRCRoomData.m_tblMoney.size(); i++){
		msg.m_tblMoney[i]=m_cRCRoomData.m_tblMoney[i];
	}
	msg.m_llPoolMoney=m_cGameInfo.m_llPoolMoney;
	//PayloadSC pld(PayloadSC::msgCardData_Tag, msg);
	//SendToUser(lUSN, pld, false);
	SendToUser(lUSN, GLAnsGameProtocol_Type_carddata, &msg);
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendStartReq()
{
	long lUSN=m_cGameInfo.m_lBossUSN;
	int nTotal=GetUISize();
	if(IsUI(lUSN)==false)
	{
		for(int i=0; i<nTotal; ++i)
		{
			UserInfo & ui=GetUI(i);
			if(ui.m_lUSN!=EMPTY_USER)
			{
				m_cGameInfo.m_lBossUSN=ui.m_lUSN;
				lUSN=ui.m_lUSN;
				break;
			}
		}
	}
	if(lUSN<0) return;
	int nPlayerCount=GetUICount();
	if(nPlayerCount<GetMinPlayerCount()) return;	//적정 게임 시작 인원이 안될때
	m_cGameInfo.m_bStart=true;
	MsgSC_StartReq msg;
	//PayloadSC pld(PayloadSC::msgStartReq_Tag, msg);
	//SendToUser(lUSN, pld);
	SendToUser(lUSN, GLAnsGameProtocol_Type_startreq, &msg);

	int nSetTime=Get_Velocity(TIMER_START, -1);
	SetTimer(TIMER_START, nSetTime, NULL);
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendNewGame()
{
	RemoveTimer(TIMER_NEWGAME);
	MsgSC_NewGame msg;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; ++i){
		UserInfo& ui=GetUI(i);
		Money& money=GetMoney(i);

		WinLoseInfo winlose;
		winlose.Clear();
		winlose.m_llCMoney=money.m_llCMoney;
		winlose.m_lWin=ui.m_cWinLose_Room.m_lWin;
		winlose.m_lLose=ui.m_cWinLose_Room.m_lLose;
		winlose.m_lReserved=0;
		msg.m_vtWinLoseInfo.push_back(winlose);
	}
	//PayloadSC pld(PayloadSC::msgNewGame_Tag, msg);
	//SendToAll(pld);
	SendToAll(GLAnsGameProtocol_Type_newgame, &msg);
	BanCheck();
	SwitchState(GAMESTATE_READY);
	InitGame();
	SendStartReq();
	m_cGameInfo.m_nOldRuleIdx=m_cGameInfo.m_nRuleIdx;
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendContinueAns(long lUSN)
{
	MsgSC_ContinueAns msg;
	msg.m_lUSN=lUSN;
	//PayloadSC pld(PayloadSC::msgContinueAns_Tag, msg);
	//SendToAll(pld);
	SendToAll(GLAnsGameProtocol_Type_ans_continue, &msg);
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendContinue()
{
	RemoveTimer(TIMER_CONTINUE);
	MsgSC_Continue msg;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; ++i){
		UserInfo& ui=GetUI(i);
		Money& money=GetMoney(i);

		WinLoseInfo winlose;
		winlose.Clear();
		winlose.m_llCMoney=money.m_llCMoney;
		winlose.m_lWin=ui.m_cWinLose_Room.m_lWin;
		winlose.m_lLose=ui.m_cWinLose_Room.m_lLose;
		winlose.m_lReserved=0;
		msg.m_vtWinLoseInfo.push_back(winlose);
	}
	//PayloadSC pld(PayloadSC::msgContinue_Tag, msg);
	//SendToAll(pld);
	SendToAll(GLAnsGameProtocol_Type_continue_msg, &msg);
	BanCheck();
	SwitchState(GAMESTATE_READY);
	InitGame();
	SendStartAns();
//	SendStartReq();
	m_cGameInfo.m_nOldRuleIdx=m_cGameInfo.m_nRuleIdx;
}

//----------------------------------------------------------------------------------------------------
void CGameMgr::SendStartAns()
{
	RemoveTimer(TIMER_START);
	int nTotal=GetUISize();
	// 게임 Play유저 Flag 세팅
	SwitchState(GAMESTATE_START);
	// 모든 게임 Data를 초기화 한다.
	InitGame();
	UserStateSetting();

	bool bTempStart=false;
	if(GetPlayerCount() >= GetMinPlayerCount()){
		m_cGameInfo.m_bStartReq=false;
		bTempStart=true;
	}
	m_cGameInfo.m_bStart=false;
	if(bTempStart){
		m_cGameInfo.m_bStartReq=true;
		//SYSTEMTIME sys;
		//memset(&sys, 0, sizeof(SYSTEMTIME));
		//::GetLocalTime(&sys);
		//m_cGameInfo.m_sGameDate=::format("%d%02d%02d%02d%02d%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
		m_cGameInfo.m_lRoomId=m_cRCRoomData.m_lRoomIndex;
		m_cGameInfo.m_dwStartTimer=time(0);
		m_cGameInfo.m_llGameData=GetCurrentSystemTime();
		m_cGameInfo.m_sGameDate=GetCurrentSystemTime_s(); // 게임 시작 시간을 적어둔다.
		SendSystemMsg(SYSMSG_GAMESTART, _T("GameStart"));//20110118 불필요하여 삭제함
		StartItem();
		for(int k=0; k<nTotal; ++k){
			Money& money=GetMoney(k);
			if(true==IsInRange(k, 0, m_cGameInfo.m_vllStartMoney.size()-1)){
				m_cGameInfo.m_vllStartMoney[k]=money.m_llCMoney;
			}
		}
		if(true==m_cGameInfo.m_bBetUserMoney){
			m_cRCRoomData.m_option.m_llGameAnteMoney=m_cRCRoomData.m_option.m_llAnteMoney;
		}
		else{
			m_cRCRoomData.m_option.m_llGameAnteMoney=__CONST_::Get_Ante_Multi(m_cGameInfo.m_lChannel_idx, m_cRCRoomData.m_option.m_llAnteMoney, GetPlayerCount(), 5);
		}
		MsgSC_StartAns msg;
		msg.m_lState=m_cRCRoomData.m_lState;
		msg.m_llSystemTime=time(0);//timeGetTime();
		for(int i=0; i<nTotal; i++){
			UserInfo & ui=GetUI(i);
			msg.m_vtState.push_back(ui.m_lUserState);
		}
		PayloadSC pld(PayloadSC::msgStartAns_Tag, msg);
		//SendToAll(pld);//20110118 불필요하여 삭제함
		SendToAll(GLAnsGameProtocol_Type_ans_start, &msg);
		if(true==m_cGameInfo.m_bStartPrev){
			m_cGameInfo.m_lDealtCardCount=GetShuffleCount()/2;
		}
		SendDealCards();
	}
	else{
		SwitchState(GAMESTATE_READY);
		UserStateSetting();
		RemoveTimer(TIMER_START);
		SendSystemMsg(SYSMSG_NOSTART, _T("GameStart"));//20110118 불필요하여 삭제함
		return;
		// 다시 준비 상태로 세팅한다.
	}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendNoStart()
{
	RemoveTimer(TIMER_START);
	m_cGameInfo.m_bStart=false;
	MsgSC_NoStart msg;
	PayloadSC pld(PayloadSC::msgNoStart_Tag, msg);
	//SendToAll(pld);
	SendToAll(GLAnsGameProtocol_Type_nostart, &msg);
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendAnteMoney()
{
	s_ans_send_ante msg;
	msg.set_m_llantemoney(m_cRCRoomData.m_option.m_llGameAnteMoney);

	//m_cFileLog.DebugLog("Ante==%I64d", m_cRCRoomData.m_option.m_llGameAnteMoney);
	//m_cFileLog.DebugLog("Pool==%I64d", m_cGameInfo.m_llPoolMoney);
	//PayloadSC pld(PayloadSC::msgAnteMoney_Tag, msg);
	//SendToAll(pld);
	SendToAll(GLAnsGameProtocol_Type_ans_send_ante, &msg);
}
//----------------------------------------------------------------------------------------------------

void CGameMgr::SetCardTbl(s_ans_deal_cards* pMsg, CardTable* pCardTable)
{
	/*

			msg.set_m_lbossusn(m_cGameInfo.m_lBossUSN);
			msg.set_m_lstate(m_cRCRoomData.m_lState);
			msg.m_tblcard.resize(m_cRCRoomData.m_option.m_lMaxPlayerCardCnt);
			for(int i=0; i<tbltempCard.size(); i++){
				msg.m_tblcard[i]=tbltempCard[i];
			}

			msg.m_tblMoney.resize(m_cRCRoomData.m_option.m_lMaxPlayerUserCnt);
			for(int i=0; i<m_cRCRoomData.m_tblMoney.size(); i++){
				msg.m_tblmoney[i]=m_cRCRoomData.m_tblMoney[i];
			}
			msg.set_m_llpoolmoney(m_cGameInfo.m_llPoolMoney);
			m_cFileLog.DebugLog("Pool==%I64d", msg.m_llpoolmoney());
			msg.m_nType=Cards::CARDTYPE_NORMAL;
			if(IsHiddenCard())
				msg.set_m_ntype(msg.m_ntype() | Cards::CARDTYPE_HIDDEN);
				*/


	pMsg->set_m_lbossusn(m_cGameInfo.m_lBossUSN);
	pMsg->set_m_lstate(m_cRCRoomData.m_lState);

	for(int i = 0 ; i < m_cRCRoomData.m_option.m_lMaxPlayerCardCnt ; ++i)
	{
		PKCards* pCard = pMsg->add_m_tblcard();
		pCard->IsInitialized();

		for(int y=0; y < pCardTable->size() ; y++){
			pCard->add_m_vtcards(pCardTable->GetCards(i).m_vtCards[y]);
		}
	}

	for(int i = 0 ; i < m_cRCRoomData.m_option.m_lMaxPlayerUserCnt ; ++i)
	{
		PKMoney* pPKMoney = pMsg->add_m_tblmoney();
		pPKMoney->IsInitialized();

		pPKMoney->set_m_lbetcount(m_cRCRoomData.m_tblMoney[i].m_lBetCount);
		pPKMoney->set_m_lbetreceive(m_cRCRoomData.m_tblMoney[i].m_lBetReceive);
		pPKMoney->set_m_lbetstate(m_cRCRoomData.m_tblMoney[i].m_lBetState);
		pPKMoney->set_m_llcallhabmoney(m_cRCRoomData.m_tblMoney[i].m_llCallHabMoney);
		pPKMoney->set_m_llcallmoney(m_cRCRoomData.m_tblMoney[i].m_llCallMoney);
		pPKMoney->set_m_llcmoney(m_cRCRoomData.m_tblMoney[i].m_llCMoney);
		pPKMoney->set_m_lljackpotmoney(m_cRCRoomData.m_tblMoney[i].m_llJackpotMoney);
		pPKMoney->set_m_llsidemoney(m_cRCRoomData.m_tblMoney[i].m_llSideMoney);
		pPKMoney->set_m_lltakemoney(m_cRCRoomData.m_tblMoney[i].m_llTakeMoney);
		pPKMoney->set_m_lresultidx(m_cRCRoomData.m_tblMoney[i].m_lResultIdx);
		pPKMoney->set_m_smoneymsg(m_cRCRoomData.m_tblMoney[i].m_sMoneyMsg);
	}

	pMsg->set_m_llpoolmoney(m_cGameInfo.m_llPoolMoney);
	pMsg->set_m_ntype(Cards::CARDTYPE_NORMAL);
	if(IsHiddenCard())
		pMsg->set_m_ntype(pMsg->m_ntype() | Cards::CARDTYPE_HIDDEN);

}

void CGameMgr::SendDealCards()
{
	SwitchState(GAMESTATE_SELECT);
#ifdef _DEBUG
	CheckJokbo();
#endif
	m_cGameInfo.m_lWantBetType=BET_TYPE_NONE;
	long lUserState=((true==IsSelect()) ? (USERSTATE_SELECTBEGIN) : (USERSTATE_PLAYING));
	long lPlayerCount=GetPlayerCount();
	SetAnte(lPlayerCount, lUserState);
	long lBossUSN=m_cGameInfo.m_lBossUSN;
	if(!IsUI(lBossUSN))
	{
		m_cGameInfo.m_lBossUSN=GetFindBossUSN();
		SendBoss();
	}

	int nTemp=0;
	adl::VecMoney vtCMoney;
	int nIndex=USNToIdx(m_cGameInfo.m_lBossUSN);
	int nTotal=GetUISize();
	for(int n=0; n<nTotal; n++)
	{
		Money & money=GetMoney(n);
		vtCMoney.push_back(money.m_llCMoney);
	}
	DealCard(GetMaxDealCount(), lUserState);
	CardTable tbltempCard;
	tbltempCard.Init(m_cRCRoomData.m_option.m_lMaxPlayerCardCnt);
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN==-1) continue;
		if(ui.m_lUserState==lUserState)
		{
			tbltempCard.Clear();
			Cards & Card=GetCards(ui.m_nIndex);
			tbltempCard.GetCards(ui.m_nIndex)=Card;
			s_ans_deal_cards  msg;
			
			SetCardTbl(&msg, &tbltempCard);
			/*
			msg.m_tblCard.resize(m_cRCRoomData.m_option.m_lMaxPlayerCardCnt);
			for(int i=0; i<tbltempCard.size(); i++){
				msg.m_tblCard[i]=tbltempCard[i];
			}
			msg.m_tblMoney.resize(m_cRCRoomData.m_option.m_lMaxPlayerUserCnt);
			for(int i=0; i<m_cRCRoomData.m_tblMoney.size(); i++){
				msg.m_tblMoney[i]=m_cRCRoomData.m_tblMoney[i];
			}
			msg.m_llPoolMoney=m_cGameInfo.m_llPoolMoney;
			m_cFileLog.DebugLog("Pool==%I64d", msg.m_llPoolMoney);
			msg.m_nType=Cards::CARDTYPE_NORMAL;
			if(IsHiddenCard())
				msg.m_nType=msg.m_nType | Cards::CARDTYPE_HIDDEN;
				*/

			/*

			msg.set_m_lbossusn(m_cGameInfo.m_lBossUSN);
			msg.set_m_lstate(m_cRCRoomData.m_lState);
			msg.m_tblcard.resize(m_cRCRoomData.m_option.m_lMaxPlayerCardCnt);
			for(int i=0; i<tbltempCard.size(); i++){
				msg.m_tblcard[i]=tbltempCard[i];
			}

			msg.m_tblMoney.resize(m_cRCRoomData.m_option.m_lMaxPlayerUserCnt);
			for(int i=0; i<m_cRCRoomData.m_tblMoney.size(); i++){
				msg.m_tblmoney[i]=m_cRCRoomData.m_tblMoney[i];
			}
			msg.set_m_llpoolmoney(m_cGameInfo.m_llPoolMoney);
			m_cFileLog.DebugLog("Pool==%I64d", msg.m_llpoolmoney());
			msg.m_nType=Cards::CARDTYPE_NORMAL;
			if(IsHiddenCard())
				msg.set_m_ntype(msg.m_ntype() | Cards::CARDTYPE_HIDDEN);
				*/

			SendToUser(ui.m_lUSN, ::GLAnsGameProtocol_Type_ans_deal_cards, &msg);
			nTemp++;
		}
		else
		{
			tbltempCard.Clear();
			s_ans_deal_cards  msg;
			/*
			msg.m_lBossUSN=m_cGameInfo.m_lBossUSN;
			msg.m_lState=m_cRCRoomData.m_lState;
			msg.m_tblCard.resize(m_cRCRoomData.m_option.m_lMaxPlayerCardCnt);
			for(int i=0; i<tbltempCard.size(); i++){
				msg.m_tblCard[i]=tbltempCard[i];
			}
			msg.m_tblMoney.resize(m_cRCRoomData.m_option.m_lMaxPlayerUserCnt);
			for(int i=0; i<m_cRCRoomData.m_tblMoney.size(); i++){
				msg.m_tblMoney[i]=m_cRCRoomData.m_tblMoney[i];
			}
			msg.m_llPoolMoney=m_cGameInfo.m_llPoolMoney;
			m_cFileLog.DebugLog("Pool==%I64d", msg.m_llPoolMoney);
			msg.m_nType=Cards::CARDTYPE_NORMAL;
			if(IsHiddenCard())
				msg.m_nType=msg.m_nType | Cards::CARDTYPE_HIDDEN;
				*/
			//PayloadSC pld(PayloadSC::msgDealCards_Tag, msg);
			//SendToUser(ui.m_lUSN, pld, false);


			SetCardTbl(&msg, &tbltempCard);

			SendToUser(ui.m_lUSN, ::GLAnsGameProtocol_Type_ans_deal_cards, &msg);
			nTemp++;
		}
	}
	tbltempCard.Clear();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN==-1) continue;
		if(ui.m_lUserState==lUserState){
			for(int m=0; m<GetMaxDealCount(); m++){
				tbltempCard.GetCards(ui.m_nIndex).m_vtCards.push_back(-1);
			}
		}
	}

	for(int i=0; i<(int)m_vtObserveUSN.size(); ++i) // send to Obserber
	{
		s_ans_deal_cards msg;

		/*
		msg.m_lBossUSN=m_cGameInfo.m_lBossUSN;
		msg.m_lState=m_cRCRoomData.m_lState;
		msg.m_tblCard.resize(m_cRCRoomData.m_option.m_lMaxPlayerCardCnt);
		for(int i=0; i<tbltempCard.size(); i++){
			msg.m_tblCard[i]=tbltempCard[i];
		}
		msg.m_tblMoney.resize(m_cRCRoomData.m_option.m_lMaxPlayerUserCnt);
		for(int i=0; i<m_cRCRoomData.m_tblMoney.size(); i++){
			msg.m_tblMoney[i]=m_cRCRoomData.m_tblMoney[i];
		}
		msg.m_llPoolMoney=m_cGameInfo.m_llPoolMoney;
		m_cFileLog.DebugLog("Pool==%I64d", msg.m_llPoolMoney);
		msg.m_nType=Cards::CARDTYPE_NORMAL;
		if(IsHiddenCard())
			msg.m_nType=msg.m_nType | Cards::CARDTYPE_HIDDEN;
		//PayloadSC pld(PayloadSC::msgDealCards_Tag, msg);
		//SendToUser(m_vtObserveUSN[i], pld, false);
		*/

		SetCardTbl(&msg, &tbltempCard);

		SendToUser(m_vtObserveUSN[i], ::GLAnsGameProtocol_Type_ans_deal_cards, &msg);
	}
	SendSystemMsg(SYSMSG_CARDSELECT, _T("CardSelect"));
	if(true==m_cRCRoomData.m_option.m_bEcho){
		int nSetTime=Get_Velocity(TIMER_ECHO_DEALS, -1);
		GetUITable().SetAck(TIMER_ECHO_DEALS);
		SetTimer(TIMER_ECHO_DEALS, nSetTime, 0);
	}
	else{
		int nSetTime=Get_Velocity(TIMER_DEALOPEN, -1);
		SetTimer(TIMER_DEALOPEN, nSetTime, 0);
	}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendSelectedCardAns(long lUSN, int nSelect, long lCardIndex, long lChoiceType)
{
	s_ans_select_card msg;
	msg.set_m_lusn(lUSN);
	msg.set_m_nselect(nSelect);
	msg.set_m_lchoicetype(lChoiceType);
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; ++i)
	{
		UserInfo& ui=GetUI(i);
		if(ui.m_lUSN==-1)
			continue;
		if(ui.m_lUSN==lUSN)
			msg.set_m_lcardindex(lCardIndex);
		else
			msg.set_m_lcardindex(-1);
		//PayloadSC pld(PayloadSC::msgSelectedCardAns_Tag, msg);
		//SendToUser(ui.m_lUSN, pld, false);
		SendToUser(ui.m_lUSN, GLAnsGameProtocol_Type_ans_select_card, &msg);
	}
	//관전모드 사용안함
	/////////////////////////////////////
	msg.set_m_lcardindex(-1);
	//PayloadSC pld(PayloadSC::msgSelectedCardAns_Tag, msg);
	int nObserveSize=m_vtObserveUSN.size();
	for(int i=0; i<nObserveSize; ++i) // send to Observer
		SendToUser(m_vtObserveUSN[i], GLAnsGameProtocol_Type_ans_select_card, &msg);
		//SendToUser(m_vtObserveUSN[i], pld, false);
	/////////////////////////////////////
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendDealOpenCard()
{
	RemoveTimer(TIMER_DEALOPEN);
	int nTotal=GetUISize();
	for(int j=0; j<nTotal; j++)
	{
		UserInfo & ui=GetUI(j);
		int nIndex=ui.m_nIndex;
		if(ui.m_lUSN<0) continue;
		Cards & Card=GetCards(nIndex);
		int nSize=GetMaxDealCount();
		if(IsErase()){
			if(Card.m_vtCards.size()==nSize) //user가 선택하지 않았을 때
			{
				long lRemoveCard=Card.m_vtCards[nSize-1];
				Card.m_vtCards.erase(remove(Card.m_vtCards.begin(), Card.m_vtCards.end(), lRemoveCard), Card.m_vtCards.end());
			}
		}
	}
	if(IsErase()){
		m_cGameInfo.m_lCardsDealt--;
	}

	SwitchState(GAMESTATE_PLAY);
	UserStateSetting();
	s_ans_opencard msg;
	int nSize=0;
	CardTable tblCard;
	//msg.m_tblCard.resize(m_cRCRoomData.m_option.m_lMaxPlayerCardCnt);
	msg.mutable_m_tblcard()->Clear();
	tblCard.Init(m_cRCRoomData.m_option.m_lMaxPlayerCardCnt);
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		msg.set_m_lstate(m_cRCRoomData.m_lState);
		if(ui.m_lUSN<0) continue;
		msg.mutable_m_vtstate()->Clear();
		tblCard.Clear();

		for(int j=0; j<nTotal; j++)
		{
			UserInfo & TempUI=GetUI(j);
			//msg.m_vtState.push_back(TempUI.m_lUserState);
			msg.add_m_vtstate(TempUI.m_lUserState);
			if(TempUI.m_lUSN<0) continue;
			Cards & Card=GetCards(TempUI.m_nIndex);
			int nSize=Card.m_vtCards.size();
			if(0==nSize) continue;
			if(ui.m_lUserState==USERSTATE_DIE)
			{
				for(int mm=0; mm<nSize; mm++)
				{
					tblCard.GetCards(TempUI.m_nIndex).m_vtCards.push_back(-1);
				}
			}
			else
			{
				for(int mm=0; mm<nSize; mm++)
				{
					if(ui.m_lUSN==TempUI.m_lUSN)
					{
						tblCard.GetCards(TempUI.m_nIndex).m_vtCards.push_back(Card.m_vtCards[mm]);
					}
					else
					{
						if(mm<2 || mm==6)
							tblCard.GetCards(TempUI.m_nIndex).m_vtCards.push_back(-1);
						else
							tblCard.GetCards(TempUI.m_nIndex).m_vtCards.push_back(Card.m_vtCards[mm]);
					}
				}
			}
		}

		/*
		for(int i=0; i<tblCard.size(); i++){
			msg.m_tblCard[i]=tblCard[i];
		}
		*/

		for(int i=0; i< tblCard.size(); i++){
			PKCards*  card =  msg.add_m_tblcard();

			for(VecCard::iterator it = tblCard.GetCards(i).m_vtCards.begin() ; it < tblCard.GetCards(i).m_vtCards.end() ; ++it)
			{
				card->add_m_vtcards(*it);
			}
		}

		/*
		for(int i = 0 ; i < m_cRCRoomData.m_option.m_lMaxPlayerCardCnt ; ++i)
		{
			PKCards* pCard = msg.add_m_tblcard();
			for(int y = 0 ; y < tblCard.size() ; ++y)
			{
				pCard->add_m_vtcards(tblCard.GetCards(i).m_vtCards[y]);
			}
		}
		*/

		PKCards* pCard = msg.add_m_tblcard();
		//PayloadSC pld(PayloadSC::msgDealOpenCard_Tag, msg);
		//SendToUser(ui.m_lUSN, pld, false);
		SendToUser(ui.m_lUSN, GLAnsGameProtocol_Type_ans_opencard, &msg);
	}
	msg.set_m_lstate(m_cRCRoomData.m_lState);
	msg.mutable_m_vtstate()->Clear();
	tblCard.Clear();
	for (int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		msg.add_m_vtstate(ui.m_lUserState);
		if(ui.m_lUSN<0) continue;
		Cards & Card=GetCards(ui.m_nIndex);
		int nSize=Card.m_vtCards.size();
		if(0==nSize) continue;
		if(ui.m_lUserState==USERSTATE_DIE)
		{
			for(int mm=0; mm<nSize; mm++)
			{
				tblCard.GetCards(ui.m_nIndex).m_vtCards.push_back(-1);
			}
		}
		else
		{
			for(int mm=0; mm<nSize; mm++)
			{
				if(mm<2 || mm==6)
					tblCard.GetCards(ui.m_nIndex).m_vtCards.push_back(-1);
				else
					tblCard.GetCards(ui.m_nIndex).m_vtCards.push_back(Card.m_vtCards[mm]);
			}
		}
	}
	/*
	for(int i=0; i<tblCard.size(); i++){
		msg.m_tblCard[i]=tblCard[i];
	}
	*/
	for(int i=0; i< tblCard.size(); i++){
		PKCards*  card =  msg.add_m_tblcard();

		for(VecCard::iterator it = tblCard.GetCards(i).m_vtCards.begin() ; it < tblCard.GetCards(i).m_vtCards.end() ; ++it)
		{
			card->add_m_vtcards(*it);
		}
	}

	PayloadSC pld(PayloadSC::msgDealOpenCard_Tag, msg);
	for(int i=0; i<(int)m_vtObserveUSN.size(); i++){
		//SendToUser(m_vtObserveUSN[i], pld, false);
		SendToUser(m_vtObserveUSN[i], GLAnsGameProtocol_Type_ans_opencard, &msg);
	}
	m_cGameInfo.m_lBossUSN=IdxToUSN(FindBossIndex());
	SendBoss();
	if( !IsRule_Speed() )	//스피드 게임이 아니라면
		SendDealCard();
	else
		SendSpeedGame_DealCard();	//스피드 게임이라면
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendDealCard()
{
	m_cGameInfo.m_lBossUSN=IdxToUSN(FindBossIndex());
	DealCard(1, USERSTATE_PLAYING, FALSE);
	vector<OneCard> vtOneCard;
	int nTotal=GetUISize();
	if(IsHiddenCard()){
		for(int i=0; i<nTotal; i++)
		{
			UserInfo & ui=GetUI(i);
			if(ui.m_lUSN<0) continue;
			vtOneCard.clear();
			if(ui.m_lUserState!=USERSTATE_PLAYING)
			{
				for(int j=0; j<nTotal; j++)
				{
					UserInfo & TempUI=GetUI(j);
					if(TempUI.m_lUSN<0) continue;
					Cards & Card=GetCards(TempUI.m_nIndex);
					int nSize=Card.m_vtCards.size();
					if(nSize==7)
					{
						OneCard TempCard;
						TempCard.m_nIndex=TempUI.m_nIndex;
						TempCard.m_lCardIndex=-1;
						vtOneCard.push_back(TempCard);
					}
				}
			}
			else if(ui.m_lUserState==USERSTATE_PLAYING)
			{
				for(int j=0; j<nTotal; j++)
				{
					UserInfo & TempUI=GetUI(j);
					if(TempUI.m_lUSN<0) continue;

					Cards & Card=GetCards(TempUI.m_nIndex);

					int nSize=Card.m_vtCards.size();
					if(nSize==7)
					{
						OneCard TempCard;
						TempCard.m_nIndex=TempUI.m_nIndex;
						if(ui.m_nIndex==j)
							TempCard.m_lCardIndex=Card.m_vtCards[nSize-1];
						else
							TempCard.m_lCardIndex=-1;

						vtOneCard.push_back(TempCard);
					}
				}
			}

			MsgSC_DealHiddenCard msg;
			msg.m_lBossUSN=m_cGameInfo.m_lBossUSN;
		msg.m_lCardsDealt=m_cGameInfo.m_lCardsDealt;
			msg.m_vtOneCard.assign(vtOneCard.begin(), vtOneCard.end());
			PayloadSC pld(PayloadSC::msgDealHiddenCard_Tag, msg);
			//SendToUser(ui.m_lUSN, pld, false);
			SendToUser(ui.m_lUSN, GLAnsGameProtocol_Type_ans_deal_hiddencard, &msg);
		}
		vtOneCard.clear();
		for(int j=0; j<nTotal; j++)
		{
			UserInfo & TempUI=GetUI(j);
			if(TempUI.m_lUSN<0) continue;

			Cards & Card=GetCards(TempUI.m_nIndex);
			int nSize=Card.m_vtCards.size();

			if(nSize==7)
			{
				OneCard TempCard;
				TempCard.m_nIndex=TempUI.m_nIndex;
				TempCard.m_lCardIndex=-1;
				vtOneCard.push_back(TempCard);
			}
		}

		for(int i=0; i<(int)m_vtObserveUSN.size(); i++)
		{
			MsgSC_DealHiddenCard msg;
			msg.m_lBossUSN=m_cGameInfo.m_lBossUSN;
			msg.m_lCardsDealt=m_cGameInfo.m_lCardsDealt;
			msg.m_vtOneCard.assign(vtOneCard.begin(), vtOneCard.end());
			//PayloadSC pld(PayloadSC::msgDealHiddenCard_Tag, msg);
			//SendToUser(m_vtObserveUSN[i], pld, false);
			SendToUser(m_vtObserveUSN[i], GLAnsGameProtocol_Type_ans_deal_hiddencard, &msg);

		}

		long lTempBoss=m_cGameInfo.m_lBossUSN;
		if(!IsUI(m_cGameInfo.m_lBossUSN))
			m_cGameInfo.m_lBossUSN=IdxToUSN(FindBossIndex());

		if(lTempBoss!=m_cGameInfo.m_lBossUSN)
		{
			string sMsg=FindUserName(m_cGameInfo.m_lBossUSN);
			SendSystemMsg(SYSMSG_BOSS, sMsg);
		}
		m_cGameInfo.m_lBetUSN=m_cGameInfo.m_lBossUSN;
	}
	else{

		/*
		vector<OneCard> vtOneCard;
		for(int i=0; i<nTotal; i++)
		{
			UserInfo & ui=GetUI(i);
			if(ui.m_lUSN<0) continue;
			if(ui.m_lUserState!=USERSTATE_PLAYING) continue;

			Cards & Card=GetCards(ui.m_nIndex);
			int nSize=Card.m_vtCards.size();
			OneCard TempCard;
			TempCard.m_nIndex=ui.m_nIndex;
			TempCard.m_lCardIndex=Card.m_vtCards[nSize-1];			
			vtOneCard.push_back(TempCard);
		}
		*/

		s_ans_deal_card msg;
		msg.set_m_lbossusn(m_cGameInfo.m_lBossUSN);
		msg.set_m_lcardsdealt(m_cGameInfo.m_lCardsDealt);
		for(int i=0; i<nTotal; i++)
		{
			UserInfo & ui=GetUI(i);
			if(ui.m_lUSN<0) continue;
			if(ui.m_lUserState!=USERSTATE_PLAYING) continue;

			Cards & Card=GetCards(ui.m_nIndex);
			int nSize=Card.m_vtCards.size();

			PKOneCard* pCard = msg.add_m_vtonecard();

			pCard->set_m_lcardindex(Card.m_vtCards[nSize-1]);
			pCard->set_m_nindex(ui.m_nIndex);
		}

		SendToAll(GLAnsGameProtocol_Type_ans_deal_card, &msg);

		long lTempBoss=m_cGameInfo.m_lBossUSN;
		m_cGameInfo.m_lBossUSN=IdxToUSN(FindBossIndex());

		{
			string sMsg=FindUserName(m_cGameInfo.m_lBossUSN);
			SendSystemMsg(SYSMSG_BOSS, sMsg);
		}
		m_cGameInfo.m_lBetUSN=m_cGameInfo.m_lBossUSN;
	}
	InitBetClear();

	//if(true==m_cRCRoomData.m_option.m_bEcho){
	//	int nSetTime=Get_Velocity(TIMER_ECHO_DEAL, -1);
	//	SetTimer(TIMER_ECHO_DEAL, nSetTime, 0);
	//}
	//else{
	SendBoss();
	SendBetting(BET_TYPE_CHECK);
	//}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendSpeedGame_DealCard()
{
	RemoveTimer(TIMER_SPEEDGAME);

	m_cGameInfo.m_lBossUSN=IdxToUSN(FindBossIndex());
	int nTotal=GetUISize();
	DealCard();
	if(IsHiddenCard())
	{
		vector<OneCard> vtOneCard;
		for(int i=0; i<nTotal; i++)
		{
			UserInfo & ui=GetUI(i);
			if(ui.m_lUSN<0) continue;

			vtOneCard.clear();
			if(ui.m_lUserState!=USERSTATE_PLAYING) // Die, Waiting
			{
				for(int j=0; j<nTotal; j++)
				{
					UserInfo & TempUI=GetUI(j);
					if(TempUI.m_lUSN<0) continue;

					Cards & Card=GetCards(TempUI.m_nIndex);

					int nSize=Card.m_vtCards.size();
					if(nSize==7)
					{
						OneCard TempCard;
						TempCard.m_nIndex=TempUI.m_nIndex;
						TempCard.m_lCardIndex=-1;
						vtOneCard.push_back(TempCard);
					}
				}
			}
			else if(ui.m_lUserState==USERSTATE_PLAYING)
			{
				for(int j=0; j<nTotal; j++)
				{
					UserInfo & TempUI=GetUI(j);
					if(TempUI.m_lUSN<0) continue;

					Cards & Card=GetCards(TempUI.m_nIndex);

					int nSize=Card.m_vtCards.size();
					if(nSize==7)
					{
						OneCard TempCard;
						TempCard.m_nIndex=TempUI.m_nIndex;
						if(ui.m_nIndex==j)
							TempCard.m_lCardIndex=Card.m_vtCards[nSize-1];
						else
							TempCard.m_lCardIndex=-1;

						vtOneCard.push_back(TempCard);
					}
				}
			}

			MsgSC_DealHiddenCard msg;
			msg.m_lBossUSN=m_cGameInfo.m_lBossUSN;
			msg.m_lCardsDealt=m_cGameInfo.m_lCardsDealt;
			msg.m_vtOneCard.assign(vtOneCard.begin(), vtOneCard.end());
			//PayloadSC pld(PayloadSC::msgDealHiddenCard_Tag, msg);
			//SendToUser(ui.m_lUSN, pld, false);
			SendToUser(ui.m_lUSN, GLAnsGameProtocol_Type_ans_deal_hiddencard, &msg);
		}

		vtOneCard.clear();
		for(int j=0; j<nTotal; j++)
		{
			UserInfo & TempUI=GetUI(j);
			if(TempUI.m_lUSN<0) continue;

			Cards & Card=GetCards(TempUI.m_nIndex);
			int nSize=Card.m_vtCards.size();

			if(nSize==7)
			{
				OneCard TempCard;
				TempCard.m_nIndex=TempUI.m_nIndex;
				TempCard.m_lCardIndex=-1;
				vtOneCard.push_back(TempCard);
			}
		}

		for(int i=0; i<(int)m_vtObserveUSN.size(); i++)
		{
			MsgSC_DealHiddenCard msg;
			msg.m_lBossUSN=m_cGameInfo.m_lBossUSN;
			msg.m_lCardsDealt=m_cGameInfo.m_lCardsDealt;
			msg.m_vtOneCard.assign(vtOneCard.begin(), vtOneCard.end());
			//PayloadSC pld(PayloadSC::msgDealHiddenCard_Tag, msg);
			//SendToUser(m_vtObserveUSN[i], pld, false);
			SendToUser(m_vtObserveUSN[i], GLAnsGameProtocol_Type_ans_deal_hiddencard, &msg);
		}

		long lTempBoss=m_cGameInfo.m_lBossUSN;
		if(!IsUI(m_cGameInfo.m_lBossUSN)){
			m_cGameInfo.m_lBossUSN=IdxToUSN(FindBossIndex());
		}

		if(lTempBoss!=m_cGameInfo.m_lBossUSN)
		{
			string sMsg=FindUserName(m_cGameInfo.m_lBossUSN);
			SendSystemMsg(SYSMSG_BOSS, sMsg);
		}
		m_cGameInfo.m_lBetUSN=m_cGameInfo.m_lBossUSN;
	}
	else
	{
		/*
		vector<OneCard> vtOneCard;
		for(int i=0; i<nTotal; i++)
		{
			UserInfo & ui=GetUI(i);
			if(ui.m_lUSN<0) continue;
			if(ui.m_lUserState!=USERSTATE_PLAYING) continue;

			Cards & Card=GetCards(ui.m_nIndex);
			int nSize=Card.m_vtCards.size();
			OneCard TempCard;
			TempCard.m_nIndex=ui.m_nIndex;
			TempCard.m_lCardIndex=Card.m_vtCards[nSize-1];			
			vtOneCard.push_back(TempCard);
		}


		MsgSC_DealCard msg;
		msg.m_lBossUSN=m_cGameInfo.m_lBossUSN;
		msg.m_lCardsDealt=m_cGameInfo.m_lCardsDealt;
		msg.m_vtOneCard.assign(vtOneCard.begin(), vtOneCard.end());
		//PayloadSC pld(PayloadSC::msgDealCard_Tag, msg);
		//SendToAll(pld, false);
		SendToAll(GLAnsGameProtocol_Type_ans_deal_card, &msg);
		*/

		s_ans_deal_card msg;
		msg.set_m_lbossusn(m_cGameInfo.m_lBossUSN);
		msg.set_m_lcardsdealt(m_cGameInfo.m_lCardsDealt);
		for(int i=0; i<nTotal; i++)
		{
			UserInfo & ui=GetUI(i);
			if(ui.m_lUSN<0) continue;
			if(ui.m_lUserState!=USERSTATE_PLAYING) continue;

			Cards & Card=GetCards(ui.m_nIndex);
			int nSize=Card.m_vtCards.size();

			PKOneCard* pCard = msg.add_m_vtonecard();

			pCard->set_m_lcardindex(Card.m_vtCards[nSize-1]);
			pCard->set_m_nindex(ui.m_nIndex);
		}

		SendToAll(GLAnsGameProtocol_Type_ans_deal_card, &msg);

		long lTempBoss=0;
		lTempBoss=m_cGameInfo.m_lBossUSN;
		m_cGameInfo.m_lBossUSN=IdxToUSN(FindBossIndex());
		// typhon 2005/05/19
		// 매 카드 나누워줄때마다 보스를 알려준다.
		//if(lTempBoss!=m_cGameInfo.m_lBossUSN || m_cGameInfo.m_lCardsDealt==4)
		{
			string sMsg=FindUserName(m_cGameInfo.m_lBossUSN);
			SendSystemMsg(SYSMSG_BOSS, sMsg);
			SendBoss();
		}
		m_cGameInfo.m_lBetUSN=m_cGameInfo.m_lBossUSN;
	}
	InitBetClear();
	int nIndex=USNToIdx(m_cGameInfo.m_lBossUSN);
	if(nIndex!=-1)
	{
		BOOL bExitPossible=false;
		bExitPossible=IsRuleExit( nIndex );
		if( bExitPossible ){ //패티아니다
			SendBoss();
			SendBetting(BET_TYPE_CHECK);
		}
		else{
			int nSetTime=Get_Velocity(TIMER_SPEEDGAME, -1);
			SetTimer(TIMER_SPEEDGAME, nSetTime, 0);
		}
	}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendBetting(long lBetBtnType)
{
	MsgSC_Betting msg;
	msg.m_lBetUSN=m_cGameInfo.m_lBetUSN;
	msg.m_lBetBtnType=lBetBtnType;
	int nBet = GetRuleBet(m_cGameInfo.m_lBetUSN);
	int nSetTime=Get_Velocity(TIMER_BETTING, -1);
	if(BETSTATE_NONE != nBet){
		if(BETSTATE_DEAL == nBet){
			GameEndProcess();
		}
		else{
			msg.m_lBetBtnType=BET_TYPE_AUTO;
			PayloadSC pld(PayloadSC::msgBetting_Tag, msg);
			//SendToAll(pld);
			SendToAll(GLAnsGameProtocol_Type_ans_betting, &msg);
			nSetTime=Get_Velocity(TIMER_AUTOBET, -1);
			SetTimer(TIMER_AUTOBET, nSetTime, NULL);
		}
	}
	else{
		PayloadSC pld(PayloadSC::msgBetting_Tag, msg);
		//SendToAll(pld);
		SendToAll(GLAnsGameProtocol_Type_ans_betting, &msg);
		if(true==m_cRCRoomData.m_option.m_bEcho){
			nSetTime=Get_Velocity(TIMER_ECHO_BET, -1);
			GetUITable().SetAck(TIMER_ECHO_BET);
			SetTimer(TIMER_ECHO_BET, nSetTime, NULL);
		}
		else{
			SetTimer(TIMER_BETTING, nSetTime, NULL);
		}
	}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendBettingAns(int nIndex, long lBetType) // 사용안함
{
	MsgSC_BettingAns msg;
	msg.m_nIndex=nIndex;
	msg.m_lBetType=lBetType;
	msg.m_money=GetMoney(nIndex);
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		Money & money=GetMoney(i);
		msg.m_vtCallMoney.push_back(money.m_llCallMoney);
	}
	msg.m_lPoolMoney=m_cGameInfo.m_llPoolMoney;
	PayloadSC pld(PayloadSC::msgBettingAns_Tag, msg);
	SendToAll(pld);
}

//----------------------------------------------------------------------------------------------------
void CGameMgr::SendBettingReq()
{
	RemoveTimer(TIMER_BETTING);
	int nTimerDie=BETSTATE_DIE;
	int nTotal=GetUISize();
	int nIndex=USNToIdx(m_cGameInfo.m_lBetUSN);
	if(nIndex<0) return;
	UserInfo& ui=GetUI(nIndex);
	if(ui.m_lUserState!=USERSTATE_PLAYING) return;
	Money& money=GetMoney(nIndex);
	int nRaise=BETSTATE_HALF;
	nTimerDie=BETSTATE_DIE;

	int nBet = GetRuleBet(m_cGameInfo.m_lBetUSN);
	if(nBet != BETSTATE_NONE){
		if(BETSTATE_DEAL == nBet){
			GameEndProcess();
			return;
		}
		nTimerDie=nBet;
	}
	if(nTimerDie==BETSTATE_DIE){
		if(true==IsInRange(nIndex, 0, m_cGameInfo.m_vlTimerDie.size()-1)){
			++m_cGameInfo.m_vlTimerDie[nIndex];
		}
	}
	OnBettingReq(m_cGameInfo.m_lBetUSN, nTimerDie);
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendBettingAnsMsg(MsgSC_BettingAnsMsg& msg, long lBetType)
{
	BettingMsg & betting=GetBettingMsg(msg.m_nIndex);
	betting.m_lUSN=msg.m_lUSN;
	betting.m_nIndex=msg.m_nIndex;
	betting.m_BetType=msg.m_BetType;
	betting.m_bBettingMoney=msg.m_bBettingMoney;
	betting.m_bMoneyLack=msg.m_bMoneyLack;
	betting.m_bCallMoneyZero=msg.m_bCallMoneyZero;
	betting.m_llCallMoney=msg.m_llCallMoney;
	betting.m_llRaiseMoney=msg.m_llRaiseMoney;
	msg.m_lBetType=lBetType;
	msg.m_money=GetMoney(msg.m_nIndex);
	msg.m_lBetTurn=m_cGameInfo.m_lBetTurn;
	int nTotal=GetMoneySize();
	for(int i=0; i<nTotal; ++i){
		Money& money=GetMoney(i);
		msg.m_vtCallMoney.push_back(money.m_llCallMoney);
	}
	msg.m_llPoolMoney=m_cGameInfo.m_llPoolMoney;
	PayloadSC pld(PayloadSC::msgBettingAnsMsg_Tag, msg);
	//SendToAll(pld);
	//SendToAll(GLAnsGameProtocol_Type_ans_betting, &msg);
	SendToAll(GLAnsGameProtocol_Type_betting_msg, &msg);
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendFinished(bool bGiveUp, int nWinIdx)
{
	bool bJackpot=false;
	long long llJackpotMoney=0;
	if(false==bGiveUp){
		bJackpot=JackpotCheck(nWinIdx, llJackpotMoney);
	}
	MsgSC_Finished msg;
	msg.m_lState=m_cRCRoomData.m_lState;
	msg.m_bGiveUp=bGiveUp;
	if(true==IsInRange(nWinIdx, 0, m_cGameInfo.m_vResultOrder.size()-1)){
		msg.m_lRank=m_cGameInfo.m_vResultOrder[nWinIdx];
	}
	msg.m_lBossUSN=m_cGameInfo.m_lBossUSN;
	msg.m_llGiveMoney=m_cGameInfo.GetGiveMoneyHab();
	msg.m_vtWin.assign(m_cGameInfo.m_vtWinIndex.begin(), m_cGameInfo.m_vtWinIndex.end());
	msg.m_vtGiveMoney.assign(m_cGameInfo.m_vllGiveMoney.begin(), m_cGameInfo.m_vllGiveMoney.end());
	Cards& card=GetCards(nWinIdx);
	msg.m_tblCard.resize(m_cRCRoomData.m_option.m_lMaxPlayerCardCnt);
	for(int i=0; i<m_cRCRoomData.m_tblCard.size(); i++){
		msg.m_tblCard[i]=m_cRCRoomData.m_tblCard[i];
	}
	msg.m_tblMoney.resize(m_cRCRoomData.m_option.m_lMaxPlayerUserCnt);
	for(int i=0; i<m_cRCRoomData.m_tblMoney.size(); i++){
		msg.m_tblMoney[i]=m_cRCRoomData.m_tblMoney[i];
	}
	msg.m_lResultIdx=(long)max(0, (int)(card.m_lResultIdx - 1));
	msg.m_llPoolMoney=m_cGameInfo.m_llPoolMoney;
	ForEachElmt(vector<UserMoney>, m_cGameInfo.m_CDivisionMoney.m_vtUser, ia, ib)
	{
		msg.m_vtUserMoney.push_back(*ia);
	}
	msg.m_llJackpot=0;
	if(true==bJackpot){
		msg.m_llJackpot=llJackpotMoney;
	}
	//PayloadSC pld(PayloadSC::msgFinished_Tag, msg);
	//SendToAll(pld);
	SendToAll(GLAnsGameProtocol_Type_finished, &msg);

}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SendJackpotMoney(long lUSN, long long llJackpotMoney)
{
	MsgSC_JackpotMoneyNtf msg;
	msg.m_lUSN=lUSN;
	msg.m_llJackpotMoney=llJackpotMoney;
	PayloadSC pld(PayloadSC::msgJackpotMoneyNtf_Tag, msg);
	SendToUser(lUSN, pld, false);
}
//----------------------------------------------------------------------------------------------------


#endif