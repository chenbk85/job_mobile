//------------------------------------------------------------------------------------
// Module Name			: ObjectBase(.h)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObjectBase
//------------------------------------------------------------------------------------
#ifndef __GameMgr_H__
#define __GameMgr_H__

#pragma once

#include "ObjectMgr.h"
#include "../../Protocol Buffers/Poker/adl.h"
#include "../Library/SGRCContainerBase.h"
#if defined(_Poker)

struct TempRCUser
{
	int nIndex;
	int nTodayCnt;
	int nGetWitch;
	int nReserve01;
	int nReserve02;
};

class CGameMgr : public CObjectMgr
{
public:
	long m_Cards[TOTAL_CARDS];
#ifdef _DEBUG
	CTVector<long> m_ctCard[5];
	CTVector<long> m_ctAllCard;
	bool m_bJokbo;
	void CheckJokbo();
#endif
public:

	/*
	CGameMgr(ISGRCContainer* pGRCContainer, char* szRoomID, long lRoomIDSize):CObjectMgr(pGRCContainer, szRoomID, lRoomIDSize){
		InitGameMgr();
	}
	*/

	CGameMgr():CObjectMgr()
	{
		InitGameMgr();
	}

public:
	virtual ~CGameMgr(void){ FreeGameMgr(); }
	void InitGameMgr(void){}
	void FreeGameMgr(void){ DestroyObject(); }
public:
	virtual bool CreateObject(void);
	virtual void DestroyObject(void);
	virtual void SetUserPos(RCUser* pUser, room_user_id_t nIndex, long lSoundType);
	virtual long OnUserMsg(long lUSN, PayloadCS &pld);
	virtual long OnTimer(long lTimerIndex);
public:
	void UserStateSetting();
	void InitGame();
	void InitBetClear();
	string GetCardString(int nIndex);
	void ShuffleCards(int nCardTotalNum);
	int	OpenCard(int nIndex, int nSelect);
	int	SwapCard(int nIndex, int nSwap1, int nSwap2);
	int	SwapOpenCard(int nIndex, int nSelect);
	long CardCompNumber(long card1, long card2);
	long CardCompPattern(long card1, long card2);
	bool SortCardTop(int nIndex, long* const result, bool bNumber, int nType);
	void CardDataSet(CardTable & tblCard, long lState);
	void DealCard(int nSize=1, long lUserState=USERSTATE_PLAYING, bool bSameCard=false);
	string GetIP(long lIP);

	void SetAnte(long lPlayerCount, long lUserState);
	void SetAnteMoney(long lLevel, long lOption, long lMaxUserCnt=0);
	int GetRuleBet( const long lUSN );
	BOOL IsRuleFree();
	int GetRule591( const long lUSN );
	BOOL IsRuleExit( const int nIndex );
	BOOL IsRuleFree_Free();
	BOOL IsRule_Speed();
	BOOL IsRule491();
	BOOL IsRule591();
	BOOL IsRule592();
	BOOL IsRule_Free();
	BOOL IsRule_NoDie();
	BOOL IsNow491(int nIndex);
	BOOL IsNow492(int nIndex);
	BOOL IsNow591(int nIndex);
	BOOL IsNow592(int nIndex);
	BOOL IsNow593(int nIndex);

	bool IsErase();
	bool IsSelect();
	bool IsDealCard();
	bool IsHiddenCard();
	long GetBettingType();
	long GetBettingTurn();
	bool IsOpenCard(int nCardsDealt, bool bIsDeal);
	int	GetShuffleCount();
	int	GetMaxDealCount();
	int	GetMaxCardCount();
	int	GetHiddenCardCount();
	int	GetMaxDeckCount();
	int	GetMaxPlayerUserCount();
	int	GetMaxPlayerCardCount();
	int	GetRaiseCount();
	int	Get_Velocity(long lTimerType, long lPlayCnt);
	int	FindBossIndex();
	bool DetermineResult(bool bGiveUp);

	long IsWin(int nIndex);
	long IsLose(int nIndex);
	bool IsStart();
	long IsEnableBet(long lUSN);
	bool IsAllLiveEnd(void);
	bool IsAllBetEnd(long lBetUSN);
	bool IsNextBet(long lUSN);
	bool IsNextBetDisconnect(int nIndex);
	bool IsAllOpenCard();
	long GetBetBtnNextType(long lUSN, long lBetBtnType);
	void OnBettingReq(long lUSN, long lBetType);
	void GameEnd(bool bGiveUp);
	void GameEndProcess();
	void GameEndTurn();
	void BanCheck();
	void SetPurgeMoney(CPurgeMoney purgemoney);
	__int64 GetPurgeMoney(long lUSN, bool bErase=false);
	void ErasePurgeMoney(long lUSN);
	void DB_Save(bool bFlags);
	void DB_DisconnectSave(const TempRCUser& tempRC, bool bObserve=false);
	void Proc_ExecuteQueryToDB();
	void DB_User_Log(long lUSN, string sUUID);
	void DB_Room_Log();
	void ExtMoneyCheck();
	bool JackpotCheck(int nWinIndex, long long &llJackpotMoney);
	string RoomTitle();
public:
	bool DB_Query_Jackpot(long lUSN, long long &llJackpotMoney);
	bool DB_Query_Event(long lUSN, long long &llEventMoney);
	bool DB_Query_UpdateMoney(long lUSN, long long &llEventMoney);
public:
	void PromotionCheck();
	void Promotion_Bonus500();
public:
	void SendUserJoinAns(long lUSN, int nEnter, int nSet);
	void SendEntryAns(long lUSN, int nIndex, bool bWelcomeSound);
	void SendCardData(long lUSN, CardTable &tblCard);
	void SendStartPrev();
	void SendStartReq();
	void SendStartAns();
	void SendNoStart();
	void SendNewGame();
	void SendContinueAns(long lUSN);
	virtual void SendContinue();
	void SendAnteMoney();
	void SendRuleQuaterHalf(long lUserState);
	void SendDealCards();
	void SendDealCard();
	void SendSpeedGame_DealCard();
	void SendShowCard(int nIndex);
	void SendSelectedCardAns(long lUSN, int nSelect, long lCardIndex, long lChoiceType);
	void SendDealOpenCard();
	void SendBetting(long lBetBtnType);
	void SendBettingAns(int nIndex, long lBetType);
	void SendBettingReq();
	void SendBettingWantEnd();
	void SendBettingAnsMsg(MsgSC_BettingAnsMsg& msg, long lBetType);
	void SendResultSelectReq();
	void SendResultSelectAns(long lUSN, int nIndex, long lResultIdx);
	void SendFinished(bool bGiveUp, int nWinIdx);
	void SendJackpotMoney(long lUSN, long long llJackpotMoney);
	void SendRePlay(int nIndex, int nWinIndex);
public:
	void UserJoin(long lUSN);
	void UserDisconnect(long lUSN, bool bReceive=false, bool bAbserveErase=true, bool bPugeErase=true);
	bool OnRcvEntry(PK_Plugin_Connection* pCon, long lUSN, s_req_entry* pMsg);
	void OnRcvObserve(long lUSN, s_req_observe * pMsg);
	void OnRcvStart(s_req_send_start * pMsg);
	void OnRcvChoiceRemoveCard(long lUSN, s_req_choiceremovecard * pMsg);
	void OnRcvSelectedCardReq(long lUSN, s_req_send_select_card * pMsg);
	void OnRcvBettingReq(long lUSN, s_req_betting * pMsg);
	void OnRcvContinue(long lUSN, s_req_continue * pMsg);
	void NotifyChangeGameOption(int nRuleIdx);
	void OnRcvRuleSet(long lUSN, s_req_ruleset * pMsg);
	void OnRcvJokboSet(long lUSN, s_req_jokboset* pMsg);
	void OnRcvTestKeySetting(long lUSN, MsgCS_TestKeySetting* pMsg);
	void OnRcvAck(long lUSN, s_req_ack* pMsg);
public:
	virtual long __stdcall OnCreateRoom(const char* szRoomOption, long lSize);
	//virtual long __stdcall OnAddUserInRoom(long lUSN, const char* szUserData, long lSize, long* plErrorCode);
	virtual long __stdcall OnAddUserInRoom(adl::RCUser *user);
	virtual long __stdcall OnReserveRemoveUserInRoom(long lUSN);
	virtual long __stdcall OnUserDisconnectInRoomNotify(long lUSN);
	virtual long __stdcall OnRemoveUser(long lUSN);
	virtual long __stdcall OnUserMsgToRoomNotify(long lUSN, long lSize);
	virtual long __stdcall OnTimerToRoomNotify(long lTimerIndex);
	//virtual long __stdcall OnChangeUserAvatarNotify(long lUSN, long lAvatar);
	//virtual long __stdcall OnChangeUserNicknameNotify(long lUSN, const char* szNickname, long lSize);
	virtual long __stdcall OnChangeUserItemNotify(long lUSN, const char* szItem, long lSize);
	virtual long __stdcall OnRecvMessageFromServer(long lMsgType, long lParam, const char* szContents, long lSize);
	virtual long __stdcall CanUseIBB(long lUSN);
	virtual long __stdcall OnAExcuteQueryToDBResult(long lResult, long lIndex, const char* szResult, long lSize, long lErrorCode);
	virtual long __stdcall CheckUserStateFromWeb(long lUSN);
	virtual long __stdcall GetRoomInfo(const char* szRoomInfo, long lSize);
public:
	void SetCardTbl(s_ans_deal_cards* pMsg, CardTable* tbltempCard);

};

#endif

#endif