//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"

#include "GameMgr_Poker.h"


#if defined(_Poker)



//----------------------------------------------------------------------------------------------------
void CGameMgr::UserJoin(long lUSN)
{
	//long lErrorCode=0;
	//if(IsUserJoinErr(lUSN, lErrorCode))
	//{
	//	SendUserJoinErr(lUSN, lErrorCode);
	//	return;
	//}
//	JoinItem(lUSN);
	int nEnter=0;
	if (m_RCUserData.size()==1){
		SwitchState(GAMESTATE_READY);
		nEnter=1;
	}
	else{
		nEnter=2;
	}
	int nSet=0;
	int nTotal=GetUISize();
	//AddObserve(lUSN);
	//int nMax_Player_Count=min((int)m_cRCRoomData.m_option.m_lMaxUserCnt, MAX_PLAYER_COUNT);
	if(nEnter==1){
		nSet=0;
		//RoomOwner(lUSN);
		RoomOwner(lUSN, false);
		//m_cGameInfo.m_lOwnerUSN=lUSN;
		m_cGameInfo.m_lBossUSN=lUSN;
	}
	else
	{
		int nIndex=0;
		int nJoinTotal=0;
		bool bFind=false;
		for(int i=0; i<nTotal; i++){
			UserInfo & ui=GetUI(i);
			if(ui.m_lUSN<0){
				nJoinTotal=m_cGameInfo.m_cvtJoin.TotalVector();
				bFind=false;
				for(int j=0; j<nJoinTotal; j++){
					if(false==m_cGameInfo.m_cvtJoin.GetVector(j, nIndex)) continue;
					if(i==nIndex){
						bFind=true;
						break;
					}
				}
				if(false==bFind){
					nSet=i;
					break;
				}
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////
	SendUserJoinAns(lUSN, nEnter, nSet);	// join 유저의 data를 세팅
	//DBQGetRefillCnt(lUSN);					// refill count 받아오는 부분
	//m_cObjectWaiting.SendWaitingUserData(); //대기표 시스템:유저입장시 대기정보 보냄

	long lState=m_cRCRoomData.m_lState;
	//switch(lState)
	//{
	//case GAMESTATE_INVALID: break;
	//case GAMESTATE_READY: break;
	//case GAMESTATE_START: break;
	//case GAMESTATE_SELECT:
	//case GAMESTATE_PLAY:
	//case GAMESTATE_RESULT:
	//case GAMESTATE_SAVE:
	//	{
	//		CardTable tblCard;
	//		CardDataSet(tblCard, lState);
	//		SendCardData(lUSN, tblCard);
	//	}
	//	break;
	//default: break;
	//}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::UserDisconnect(long lUSN, bool bReceive, bool bAbserveErase, bool bPugeErase)
{
	RCUser* pUser=FindUser(lUSN);
	if(!pUser) return;
	int nIndex=pUser->m_nIndex;
	TempRCUser tempRC;
	tempRC.nIndex=nIndex;
	tempRC.nReserve01=pUser->m_nReserve01;
	tempRC.nReserve02=pUser->m_nReserve02;
//	tempRC.nTodayCnt=pUser->m_lMTodayPlayCount;
	// update context
	RemoveUser(lUSN);
	//=======================================================//
	// 나가는 사람이 지금 배팅하는 사람이면 다음 사람에게 배팅을 넘긴다.
	// 나가는 사람의 UserInfo는 clear한다.
	// 게임을 계속 할수 있냐을 체크한다.
	// 모든 사람이 다 나가면 STATE를 GAMESTATE_DEAD로 한다.
	// READY 일때 나가면 그냥 나가는 처리만 한다.
	// START,SELECT,PLAY,SAVE 일때 유저가 나감으로 했어.. 게임이 끝나면 머니 계산을 한다.
	int nTotal=GetUISize();
	if(IsUI(lUSN))
	{
		nIndex=USNToIdx(lUSN);
		if(nIndex<0) return;
		if(lUSN==m_cGameInfo.m_lOwnerUSN)
		{
			NextOwner();
		}
		bool bBossOut=false;
		if(lUSN==m_cGameInfo.m_lBossUSN)
		{
			NextBoss();
			bBossOut=true;
		}
		long lState=m_cRCRoomData.m_lState;
		UserInfo & ui=GetUI(nIndex);
		Money & money=GetMoney(nIndex);
		if(lState==GAMESTATE_START || lState==GAMESTATE_SELECT || lState==GAMESTATE_PLAY || lState==GAMESTATE_RESULT)
		{
			if(ui.m_lUserState!=USERSTATE_WAITING)
			{
				DB_DisconnectSave(tempRC, false);
				DB_User_Log(lUSN, "0000");
			}
			if(IsHiddenCard())
			{
				if(m_cGameInfo.m_lBossUSN==lUSN)
				{
					int nIndex=USNToIdx(lUSN);

					for(int i=1; i<nTotal; ++i)
					{
						if(nIndex <0) return;

						int nTempIndex=Seat[nIndex][i];
						UserInfo& ui=GetUI(nTempIndex);
						if(ui.m_lUSN!=EMPTY_USER)
						{
							m_cGameInfo.m_lBossUSN=ui.m_lUSN;
							break;
						}
					}					
				}
			}
		}
		else if(lState==GAMESTATE_READY || lState==GAMESTATE_SAVE)
		{
			if(money.m_llCallHabMoney!=0 || GetPurgeMoney(lUSN)!=0){
				DB_DisconnectSave(tempRC, false);
				DB_User_Log(lUSN, "0000");
			}
		}
		UIErase(lUSN);
		switch(m_cRCRoomData.m_lState)
		{
		case GAMESTATE_READY:
			{
				SendUserDisconnect(lUSN, nIndex);
				if(GetUICount()<GetMinPlayerCount() && m_cGameInfo.m_bStart==true){
					SendNoStart();
				}
				else{
					if(false==m_cGameInfo.m_bStartReq){
						if(m_cGameInfo.m_lBossUSN != 0){
							SendStartReq();
						}
					}
				}
			}
			break;
		case GAMESTATE_START:
		case GAMESTATE_SELECT:
		case GAMESTATE_PLAY:
			{
				SendUserDisconnect(lUSN, nIndex);
				int nPlayerCount=GetPlayerCount();
				if(nPlayerCount <= 1) // 게임을 진행 할수 없는 사항.
				{
					RemoveTimer(TIMER_BETTING);
					RemoveTimer(TIMER_DEALOPEN);
					m_cGameInfo.m_bStartReq=false;
					GameEnd(true);
				}
				else
				{
					if(lUSN==m_cGameInfo.m_lBetUSN)	// 배팅하는 사람이 나가면 
					{
						RemoveTimer(TIMER_BETTING);
						RemoveTimer(TIMER_DEALOPEN);
						if(IsNextBetDisconnect(nIndex))
						{
							long lBetBtnType=GetBetBtnNextType(m_cGameInfo.m_lBetUSN, BET_TYPE_NONE);
							SendBetting(lBetBtnType);
						}
						else
						{
							GameEndProcess();
						}
					}
				}
			}
			break;
		case GAMESTATE_SAVE:
			{
				RemoveTimer(TIMER_DEALOPEN);
				RemoveTimer(TIMER_BETTING);
				SendUserDisconnect(lUSN, nIndex);
				if((true==bReceive)&&(0==GetSelectContinueCount())){
					SendContinue();
				}
			}
			break;
		default:
			break;
		}
	}
	else
	{
		if(true==bAbserveErase){
			ObserveErase(lUSN);
		}
	}
	if(!m_RCUserData.ExistUser())
	{
		if(true==bPugeErase){
			m_cPurge.Clear();
		}
		RemoveTimer(TIMER_START);
		RemoveTimer(TIMER_STARTPREV);
		RemoveTimer(TIMER_AUTOBET);
		RemoveTimer(TIMER_DEALOPEN);
		RemoveTimer(TIMER_BETTING);
		RemoveTimer(TIMER_NEWGAME);
		RemoveTimer(TIMER_PURGE);
		switch(m_cRCRoomData.m_lState)
		{
		case GAMESTATE_INVALID: SwitchState(GAMESTATE_DEAD); break;		
		case GAMESTATE_READY:	SwitchState(GAMESTATE_DEAD); break;			
		case GAMESTATE_START:	SwitchState(GAMESTATE_DEAD); break;
		case GAMESTATE_SELECT:  SwitchState(GAMESTATE_DEAD); break;
		case GAMESTATE_PLAY:	SwitchState(GAMESTATE_DEAD); break;
		case GAMESTATE_RESULT:  SwitchState(GAMESTATE_DEAD); break;
		case GAMESTATE_SAVE:	SwitchState(GAMESTATE_DEAD); break;		
		default: break;
		}
	}
}
//----------------------------------------------------------------------------------------------------
bool CGameMgr::OnRcvEntry(PK_Plugin_Connection* pCon, long lUSN, s_req_entry* pMsg)
{
	RCUser* pUser=FindUser(lUSN);
	if(pUser==NULL) return false;
	pUser->m_sNickName=pMsg->m_snickname();
	pUser->m_lCLevel=pMsg->m_lclevel();
	pUser->m_lSex=pMsg->m_lsex();
	pUser->m_sAvt=pMsg->m_savt();

	pUser->m_pCon = pCon;

	bool bMoney=IsMoney(pUser);
	bool bSpace=IsSpace();
	bool bGrade=IsGrade(pUser);
	bool bIp	= IsIP(pUser);
	bool bGameLimit=IsGameLimit(pUser);
	bool bBlackList=IsBlackList(lUSN);
	bool bVersion=(pMsg->m_nversion()==g_nVersion)? 1 : 0;
	int nSpace=0;//=GetSpace();
	if(0>m_cGameInfo.m_cvtJoin.FindBeginVector(lUSN, nSpace)){
		return false;
	}
	m_cGameInfo.m_cvtJoin.FindBeginDelVector(lUSN);

	bool bEntryWithoutTicket=m_cObjectWaiting.IsEntryWithoutTicket( lUSN, bSpace ); //철이가 대기표시스템
	// 채널 입장 등급 채크
	if(bMoney && bSpace && bIp && bVersion && (!bBlackList) && bGameLimit && bGrade && bEntryWithoutTicket ) //철이가 대기표시스템 조건
	{
		if(IsUI(lUSN)) return false;
		SetUserPos(pUser, nSpace, pMsg->m_lsoundtype());
		if(m_cGameInfo.m_lOwnerUSN==0)  //방장이 없다면 방장을 최초로 넣어야 된다
		{
			if(true==RoomOwner(lUSN)){
				m_cGameInfo.m_lBossUSN=lUSN;
				//SendBoss();
			}
		}
		//철이가 짱구관련해서 추가
		if(	m_cGameInfo.m_lCreateRoomOwner==0 ){
			m_cGameInfo.m_lCreateRoomOwner=lUSN;
		}
		ObserveErase(lUSN);
		SendEntryAns(lUSN, nSpace, pMsg->m_bwelcomesound());
		string sMsg=FindUserName(lUSN);
		SendSystemMsg(SYSMSG_ENTRY, sMsg);
		m_cObjectWaiting.CancelTicket(lUSN); //철이가 대기표시스템:티켓받은것을 지움
		m_cObjectWaiting.CallWebClient(lUSN,false); //철이가 대기표시스템:대기자에서 빠져나가므로 웹콜유저에서 빼자
		if(IsStart())
		{
			switch(m_cRCRoomData.m_lState)
			{
			case GAMESTATE_READY:
				{
					if(m_cGameInfo.m_bStart) return false;

					long lStartUSN;
					if(m_cGameInfo.m_lBossUSN==0)
						lStartUSN=GetUI(0).m_lUSN;
					else
					{
						if(IsUI(m_cGameInfo.m_lBossUSN))
							lStartUSN=m_cGameInfo.m_lBossUSN;
						else
							lStartUSN=GetUI(0).m_lUSN;
					}
					m_cGameInfo.m_lBossUSN=lStartUSN;
					SendBoss();
					if(lStartUSN!=EMPTY_USER)
						SendStartReq();
				}
				break;
			default:
				break;
			}
		}
	}
	else
	{
		SendEntryReject(lUSN, ENTRY_NEEDTICKET); //철이가 대기표시스템:유저가 모두차서 관람자로우선뺌
		if(!bVersion)
			SendEntryReject(lUSN, ENTRY_VERSION);
		else if(!bMoney){
			if(__CONST_::TWOUSER_NUM==m_cRCRoomData.m_option.m_lMaxUserCnt){
				SendSystemMsg(SYSMSG_TWOOWNER_NOMONEY, _T("Two"), lUSN);
			}
			else{
				__int64 llUsedMoney_Max=__CONST_::Get_UsedMoney( m_cGameInfo.m_lChannel_idx, 1 );
				if(pUser->m_llCMoney>llUsedMoney_Max){
					SendEntryReject(lUSN, ENTRY_OVERMONEY);
				}
				else{
					SendEntryReject(lUSN, ENTRY_NOMONEY);
				}
			}
		}
		else if(!bGrade)
			SendEntryReject(lUSN, ENTRY_GRADE);
		else if(!bSpace)
			SendEntryReject(lUSN, ENTRY_SPACE);
		else if(!bIp)
			SendEntryReject(lUSN, ENTRY_IP);
		else if(bBlackList)
			SendEntryReject(lUSN, ENTRY_BLACKLIST);
		else if(!bGameLimit)
			SendEntryReject(lUSN, ENTRY_GAMELIMIT);
		SendFMoney(lUSN);
		return false;
	}
	return true;
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::OnRcvObserve(long lUSN, s_req_observe * pMsg)
{
	// 먼저 유저를 지운다.
	int nIndex=USNToIdx(lUSN);
	if(nIndex<0) return;
	RCUser* pUser=FindUser(lUSN);
	if(pUser==NULL) return;
	TempRCUser tempRC;
	tempRC.nIndex=nIndex;
	tempRC.nReserve01=pUser->m_nReserve01;
	tempRC.nReserve02=pUser->m_nReserve02;
	//tempRC.nTodayCnt=pUser->m_lMTodayPlayCount;
	int nTotal=GetUISize();
	if(nIndex>-1 && nIndex<nTotal){
		string sMsg=FindUserName(lUSN);
		SendSystemMsg(SYSMSG_OBSERVE, sMsg);

		UserInfo& ui=GetUI(nIndex);
		long lState=m_cRCRoomData.m_lState;
		if(lState==GAMESTATE_START || lState==GAMESTATE_SELECT || lState==GAMESTATE_PLAY)
		{
			if(ui.m_lUserState!=USERSTATE_WAITING)
				DB_DisconnectSave(tempRC, true);
		}

		ObserveProcesses(lUSN);

		switch(m_cRCRoomData.m_lState)
		{
		case GAMESTATE_READY:
			{
			}
			break;
		case GAMESTATE_START:
		case GAMESTATE_SELECT:
		case GAMESTATE_PLAY:
			{
				int nPlayerCount=GetPlayerCount();
				if(nPlayerCount <= 1) // 게임을 진행 할수 없는 사항.
				{
					RemoveTimer(TIMER_DEALOPEN);
					RemoveTimer(TIMER_BETTING);
					m_cGameInfo.m_bStartReq=false;
					GameEnd(true);
				}
				else
				{
					if(lUSN==m_cGameInfo.m_lBetUSN)	// 배팅하는 사람이 나가면 
					{
						RemoveTimer(TIMER_DEALOPEN);
						RemoveTimer(TIMER_BETTING);
						if(IsNextBetDisconnect(nIndex))
						{
							long lBetBtnType=GetBetBtnNextType(m_cGameInfo.m_lBetUSN, BET_TYPE_NONE);
							SendBetting(lBetBtnType);
						}
						else
						{
							GameEndProcess();
						}
					}
				}
			}
			break;
		case GAMESTATE_SAVE:
			{
				RemoveTimer(TIMER_DEALOPEN);
				RemoveTimer(TIMER_BETTING);
				if(0==GetSelectContinueCount()){
					SendContinue();
				}
			}
			break;
		default:
			break;
		}
	}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::OnRcvStart(s_req_send_start * pMsg)
{
	if(pMsg->gameid()!=m_cGameInfo.m_lBossUSN) return;
	if(m_cRCRoomData.m_lState!=GAMESTATE_READY) return;
	SendStartAns();
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::OnRcvChoiceRemoveCard(long lUSN, s_req_choiceremovecard * pMsg)
{
	// 4장 초이스중 타이아웃이 발생했을때, 취소한 카드라도 처리해주기 위해서

	if( lUSN==-1 )return;

	int nIndex=USNToIdx( lUSN );
	if( nIndex<0 ) return;

	UserInfo &ui=GetUI( nIndex );
	if( ui.m_lUSN==-1 ) return;
	if( ui.m_nIndex==-1 ) return;

	if( pMsg->m_lusn()==lUSN )
	{
		if( m_cRCRoomData.m_lState==GAMESTATE_SELECT )
		{
			//m_cGameInfo.m_nRemoveCard[nIndex]=pMsg->m_nRemoveCardIndex;
		}
	}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::OnRcvSelectedCardReq(long lUSN, s_req_send_select_card * pMsg)
{
	int i=0;

	if(m_cRCRoomData.m_lState!=GAMESTATE_SELECT) return;
	
	int nIndex=USNToIdx(lUSN);
	if(nIndex<0) return;
	Cards & Card=GetCards(nIndex);
	UserInfo & ui=GetUI(nIndex);
	if(ui.m_lUserState!=USERSTATE_SELECTBEGIN) return;
	int nSize=Card.m_vtCards.size();
	//if(((m_cRCRoomData.m_option.m_lRoomType==0)&&(m_cRCRoomData.m_option.m_lChoiceMode==2))||((m_cRCRoomData.m_option.m_lRoomType==1)&&(m_cRCRoomData.m_option.m_lChoiceMode==0)))
	if(Card.m_vtCards.size() == 4){
		
		for(i=0; i<(int)Card.m_vtCards.size(); i++)
		{
			if(Card.m_vtCards[i] == pMsg->m_lcardidx())
				break;
		}
		Card.m_vtCards.erase(remove(Card.m_vtCards.begin(), Card.m_vtCards.end(),pMsg->m_lcardidx()), Card.m_vtCards.end());
		SendSelectedCardAns(lUSN, i, pMsg->m_lcardidx(), 1);
	}
	else{	
		ui.m_lUserState=USERSTATE_SELECTEND;
		for(i=0; i<(int)Card.m_vtCards.size(); i++)
		{
			if(Card.m_vtCards[i]==pMsg->m_lcardidx())
				break;
		}
		int nCardIndex=OpenCard(nIndex, i);
		if(nCardIndex<0) return;
		SendSelectedCardAns(lUSN, i, pMsg->m_lcardidx(), 2);
		if(IsAllOpenCard()){
			//if(IsErase()){
			//	m_cGameInfo.m_lCardsDealt--;
			//}
			SendDealOpenCard();
		}
	}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::OnRcvBettingReq(long lUSN, s_req_betting * pMsg)
{
	OnBettingReq(lUSN, pMsg->m_lbettype());
	//OnBettingReq(lUSN, pMsg->m_lBetType);
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::OnRcvContinue(long lUSN, s_req_continue * pMsg)
{
	if(m_cRCRoomData.m_lState!=GAMESTATE_SAVE) return;
	int nIndex=USNToIdx(lUSN);
	if(nIndex==-1) return;
	UserInfo & ui=GetUI(nIndex);
	ui.m_lUserState=USERSTATE_READY;
	SendContinueAns(lUSN);
	if(0==GetSelectContinueCount()){
		SendContinue();
	}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::NotifyChangeGameOption(int nRuleIdx)
{
	//0 : 자유
	//1 : 초구 올하프
	//2 : 초구 올풀
	//3 : 3구 선하프
	//4 : 3구 선풀
	//5 : 3구 선담
	//6 : 3구 선담담
	//int nAnteMoney=__CONST_::Get_AnteToOption(__CONST_::GetChannelIndex( m_cGameInfo.m_lChannel_idx ), m_cRCRoomData.m_option.m_llAnteMoney);

	//string sTemp=::format("GM=%d|LEM=%d|AM=%d|FBR=%d|ABM=%d|GG=%d", m_cRCRoomData.m_option.m_lChoiceMode, m_cRCRoomData.m_option.m_lLimitMoney, m_cRCRoomData.m_option.m_lAnteMoney, m_cRCRoomData.m_option.m_lBetRule, m_cRCRoomData.m_option.m_lAddRule, m_cRCRoomData.m_option.m_lMaxUserCnt);
	//m_pGRCContainer->NotifyChangeGameOption(sTemp.c_str(), sTemp.length());
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::OnRcvRuleSet(long lUSN, s_req_ruleset* pMsg)
{
	if(lUSN!=m_cGameInfo.m_lOwnerUSN) return;

	MsgSC_RuleNotify msg;
	msg.m_nRuleIdx=pMsg->m_nruleidx();
	//PayloadSC pld(PayloadSC::msgRuleNotify_Tag, msg);
	//SendToAll(pld);
	SendToAll(GLAnsGameProtocol_Type_ans_ruleset, &msg);

	NotifyChangeGameOption(pMsg->m_nruleidx());

	m_cGameInfo.m_nRuleIdx=pMsg->m_nruleidx();

	if(m_cRCRoomData.m_lState==GAMESTATE_READY || m_cRCRoomData.m_lState==GAMESTATE_SAVE)
		m_cGameInfo.m_nOldRuleIdx=m_cGameInfo.m_nRuleIdx;
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::OnRcvJokboSet(long lUSN, s_req_jokboset* pMsg)
{
#ifdef _DEBUG
	if(m_cGameInfo.m_lOwnerUSN != lUSN) return;
	int nIndex=USNToIdx(m_cGameInfo.m_lOwnerUSN);
	if(nIndex<0) return;
	int i=0;
	if(0xffffffff==pMsg->m_lkey1()){
		m_cGameInfo.m_bBetUserMoney=!m_cGameInfo.m_bBetUserMoney;
		return;
	}
	long lJokbo[5]={pMsg->m_lkey1(), pMsg->m_lkey2(), pMsg->m_lkey3(), pMsg->m_lkey4(), pMsg->m_lkey5()};
	if((-1==pMsg->m_lkey1())&&(-1==pMsg->m_lkey1())&&(-1==pMsg->m_lkey1())&&(-1==pMsg->m_lkey1())&&(-1==pMsg->m_lkey1())){
		m_bJokbo=false;
		for(i=0; i<5; ++i){
			m_ctCard[i].DelVector();
		}
		return;
	}
	if(0xffffffff==pMsg->m_lkey2()){
		for(i=0; i<5; ++i){
			m_ctCard[i].DelVector();
		}
		UserInfo& ui=GetUI(nIndex);
		if(ui.m_lUSN!=EMPTY_USER){
			CPokerRules::MakeFullCard(&m_ctAllCard, 4*13);
			CPokerRules::MakePokerCard(&m_ctAllCard, (CPokerRules::ePokerType)pMsg->m_lkey1(), &m_ctCard[nIndex]);
			CPokerRules::MakePokerRestCard(&m_ctAllCard, &m_ctCard[nIndex], 7);
			CPokerRules::ShuffleFullCard(&m_ctAllCard);
		}
		return;
	}
	int nTotal=GetUISize();
	CPokerRules::MakeFullCard(&m_ctAllCard, 4*13);
	for(i=0; i<min(5, nTotal); ++i){
		int nTempIndex=Seat[nIndex][i];
		UserInfo& ui=GetUI(nTempIndex);
		if(ui.m_lUSN!=EMPTY_USER){
			CPokerRules::MakePokerCard((CPokerRules::ePokerType)lJokbo[i], &m_ctCard[nTempIndex], 7, -1);
			CPokerRules::RemoveFullCard(&m_ctAllCard, &m_ctCard[nTempIndex]);
		}
	}
	CPokerRules::ShuffleFullCard(&m_ctAllCard);
#endif
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::OnRcvTestKeySetting(long lUSN, MsgCS_TestKeySetting* pMsg)
{
#ifdef _ASSA_SET
	int nIndex=USNToIdx(lUSN);
	if(-1==nIndex) return;
	UserInfo & ui=GetUI(nIndex);
	m_cObjectItem.OnRcvTestKeySetting(long lUSN, MsgCS_TestKeySetting* pMsg);
	switch(pMsg->m_nChar)
	{
	case VK_F2:
		{
		}
		break;
	case VK_F11 :
		{
			if(0!=m_cGameInfo.m_nRealDealer){
				m_cGameInfo.m_nRealDealer=0;
			}
			else{
				SYSTEMTIME st; 
				GetLocalTime(&st);
				m_cGameInfo.m_nRealDealer=st.wHour*100;
			}
			string str=::format("딜러비  %d : %s", m_cGameInfo.m_nRealDealer, ((0!=m_cGameInfo.m_nRealDealer)?("셋팅"):("해제")));
			SendSystemMsg(SYSMSG_TEST, str, -1);
		}
		break;
	default:
		break;
	}
#endif
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::OnRcvAck(long lUSN, s_req_ack* pMsg)
{
	if(false==m_cRCRoomData.m_option.m_bEcho) return;
	switch(pMsg->m_ntagid()){
	case PayloadSC::msgDealCards_Tag:
		{
			if(true==IsTimer(TIMER_ECHO_DEALS)){
				GetUITable().SetAck(lUSN, 0);
				if(false==GetUITable().IsAck()){
					RemoveTimer(TIMER_ECHO_DEALS);
					GetUITable().SetAck(0);
					int nSetTime=Get_Velocity(TIMER_DEALOPEN, -1);
					SetTimer(TIMER_DEALOPEN, nSetTime, 0);
				}
			}
		}
		break;
	case PayloadSC::msgBetting_Tag:
		{
			if(true==IsTimer(TIMER_ECHO_BET)){
				GetUITable().SetAck(lUSN, 0);
				if(m_cGameInfo.m_lBetUSN==lUSN){
					RemoveTimer(TIMER_ECHO_BET);
					GetUITable().SetAck(0);
					int nSetTime=Get_Velocity(TIMER_BETTING, -1);
					SetTimer(TIMER_BETTING, nSetTime, NULL);
				}
			}
		}
		break;
	case PayloadSC::msgDealCard_Tag:
		{
			if(true==IsTimer(TIMER_ECHO_DEAL)){
				GetUITable().SetAck(lUSN, 0);
				if(false==GetUITable().IsAck()){
					RemoveTimer(TIMER_ECHO_DEAL);
					GetUITable().SetAck(0);
					SendBetting(BET_TYPE_CHECK);
				}
			}
		}
		break;
	case PayloadSC::msgFinished_Tag:
		{
			if(true==IsTimer(TIMER_ECHO_FINISH)){
				GetUITable().SetAck(lUSN, 0);
				if(false==GetUITable().IsAck()){
					RemoveTimer(TIMER_ECHO_FINISH);
					GetUITable().SetAck(0);
					int nSetTime=Get_Velocity(TIMER_CONTINUE, GetPlayerCount());
					SetTimer(TIMER_CONTINUE, nSetTime, NULL);
				}
			}
		}
		break;
	}
}
//----------------------------------------------------------------------------------------------------


#endif














