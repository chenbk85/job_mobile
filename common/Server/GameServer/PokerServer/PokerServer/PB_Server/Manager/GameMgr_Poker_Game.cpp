//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"

#include "GameMgr_Poker.h"
#include "../util/FileDebug.h"

#if defined(_Poker)

//----------------------------------------------------------------------------------------------------
long CGameMgr::IsWin(int nIndex)
{
	int nSize=m_cGameInfo.m_vtWinIndex.size();
	for(int i=0; i<nSize; i++)
	{
		if(nIndex==m_cGameInfo.m_vtWinIndex[i])
			return 1;
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::IsLose(int nIndex)
{
	int nSize=m_cGameInfo.m_vtWinIndex.size();
	for(int i=0; i<nSize; i++)
	{
		if(nIndex==m_cGameInfo.m_vtWinIndex[i])
			return 0;
	}
	return 1;
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SetAnteMoney(long lLevel, long lOption, long lMaxUserCnt)
{
	//m_cRCRoomData.m_option.m_llAnteMoney=__CONST_::Get_BasicAnte( lLevel, lOption, lMaxUserCnt );
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SetAnte(long lPlayerCount, long lUserState)
{
	__int64 llAnte=m_cRCRoomData.m_option.m_llGameAnteMoney;
	__int64 llPoolMoney=0;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; ++i)
	{
		UserInfo& ui=GetUI(i);
		if((ui.m_lUSN!=EMPTY_USER) && (ui.m_lUserState==lUserState) && ( ui.m_nIndex!=-1 ) )
		{
			Money& money=GetMoney(ui.m_nIndex);
			if( money.m_llCMoney <= llAnte )
			{
				llPoolMoney+=money.m_llCMoney;
				money.m_llCallHabMoney=money.m_llCMoney;
				money.m_llCMoney=0;
			}
			else
			{
				money.m_llCMoney-=llAnte;
				money.m_llCallHabMoney=llAnte;
				llPoolMoney+=llAnte;
			}
		}
	}
	m_cGameInfo.AddPoolMoney(llPoolMoney);
	SendAnteMoney();
	//	long lLevel=0;
	//	if(m_cGameInfo.m_lChannel_idx==__CONST_::CHANNEL_EXERCISE)
	//		lLevel=MAX_CHANNEL - 1;
	//	else
	//		lLevel=m_cGameInfo.m_lChannel_idx;
}
//----------------------------------------------------------------------------------------------------
bool CGameMgr::IsStart()
{
	int nTemp=0;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; ++i)
	{
		if(GetUI(i).m_lUSN!=EMPTY_USER)
			++nTemp;
	}
	if(nTemp>=GetMinPlayerCount())
		return true;

	return false;
}
//----------------------------------------------------------------------------------------------------
bool CGameMgr::IsNextBet(long lUSN)
{
	int nIndex=USNToIdx(lUSN);
	if(nIndex<0)	
		return false;	
	int nTemp=0;
	int nPlayerCount=0;
	long lBetCount=100;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN!=EMPTY_USER && ui.m_lUserState==USERSTATE_PLAYING)
		{
			nPlayerCount++;
			Money & money=GetMoney(ui.m_nIndex);
			money.m_lBetReceive=0;
			if( nIndex!=ui.m_nIndex ){
				lBetCount=min(lBetCount, money.m_lBetCount );
			}
			if((money.m_llCallMoney==0) && (money.m_lBetState!=0))
				nTemp++;
		}
	}
	if( IsRule491() && nTemp==nPlayerCount)
	{
		for(int i=0; i<nTotal; i++)
		{
			UserInfo & ui=GetUI(i);
			if(ui.m_lUSN!=EMPTY_USER && ui.m_lUserState==USERSTATE_PLAYING)
			{
				//if( IsNow491(ui.m_nIndex) )
				{
					Money & money=GetMoney(ui.m_nIndex);
					money.m_lBetState=0;
					money.m_lBetCount=0;
				}
			}
		}
		m_cGameInfo.m_lBetUSN=m_cGameInfo.m_lBossUSN;
		m_cGameInfo.m_lPreBetType=BETSTATE_NONE;
		return true;
	}
	else if(nTemp==nPlayerCount){
		return false;
	}	
	for(int i=1; i<nTotal; ++i)
	{
		UserInfo& ui=GetUI(Seat[nIndex][i]);
		if(ui.m_lUSN!=EMPTY_USER && ui.m_lUserState==USERSTATE_PLAYING)
		{
			m_cGameInfo.m_lBetUSN=ui.m_lUSN;
			return true;
		}
	}
	return false;
}
//----------------------------------------------------------------------------------------------------
bool CGameMgr::IsNextBetDisconnect(int nIndex)
{
	if(nIndex<0) return false;	
	int nTemp=0;
	int nPlayerCount=0;
	long lBetCount=100;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN!=EMPTY_USER && ui.m_lUserState==USERSTATE_PLAYING)
		{
			nPlayerCount++;
			Money & money=GetMoney(ui.m_nIndex);
			money.m_lBetReceive=0;
			if( nIndex!=ui.m_nIndex )
			{
				lBetCount=min(lBetCount, money.m_lBetCount );
			}
			if((money.m_llCallMoney==0) && (money.m_lBetState!=0))
				nTemp++;
		}
	}
	if( m_cGameInfo.m_lBetCount<lBetCount ) m_cGameInfo.m_lBetCount=lBetCount;
	if(nTemp==nPlayerCount)
		return false;
	for(int i=1; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(Seat[nIndex][i]);
		if(ui.m_lUSN!=EMPTY_USER && ui.m_lUserState==USERSTATE_PLAYING)
		{
			m_cGameInfo.m_lBetUSN=ui.m_lUSN;
			return true;
		}
	}
	return false;
}
//----------------------------------------------------------------------------------------------------
bool CGameMgr::IsAllOpenCard()
{
	int nPlayCount=GetPlayerCount();
	int nTemp=0;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;
		if(ui.m_lUserState==USERSTATE_SELECTEND)
			nTemp++;
	}

	if(nPlayCount==nTemp)
		return true;

	return false;
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::GetBetBtnNextType(long lUSN, long lBetBtnType)
{
	int nIndex=USNToIdx( lUSN );
	if( 0>nIndex ) return BET_TYPE_NONE;
	long level=0;
	level=m_cGameInfo.m_lChannel_idx;
	switch(m_cGameInfo.m_lPreBetType)
	{
	case BETSTATE_CALL:
		{
			Money & money=GetMoney(nIndex);
			if( IsRule491() )
			{
				if(money.m_lBetState==BETSTATE_CALL)
				{
					return BET_TYPE_CALL;
				}
				else if(money.m_lBetState==BETSTATE_CHECK)
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==4 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==5 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==6 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==7 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
			} else 
			{
				if(money.m_lBetState==BETSTATE_CALL)
				{
					return BET_TYPE_CALL;
				}
				else if(money.m_lBetState==BETSTATE_CHECK)
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==4 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==5 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==6 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==7 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
			}

			if((0<money.m_llCMoney)&&(money.m_llCallMoney<money.m_llCMoney)){
				return BET_TYPE_BET;
			}
			else{
				return BETSTATE_CALL;
			}
		}
		break;
	case BETSTATE_CHECK:
		{
			Money & money=GetMoney(nIndex);
			if(money.m_lBetState==BETSTATE_CALL)
			{
				return BET_TYPE_CALL;
			}
			if(0<money.m_llCMoney){
				return BET_TYPE_BBING;
			}
			else{
				return BET_TYPE_CHECK_ONLY;
			}
		}
		break;
	case BETSTATE_BBING:
	case BETSTATE_DOUBLE:
	case BETSTATE_HALF:
	case BETSTATE_QUARTER:
	case BETSTATE_FULL:
		{
			Money & money=GetMoney(nIndex);

			if( IsRule491() )
			{
				if(money.m_lBetState==BETSTATE_CALL)
				{
					return BET_TYPE_CALL;
				}
				else if(money.m_lBetState==BETSTATE_CHECK)
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==4 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==5 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==6 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==7 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
			} else {
				if(money.m_lBetState==BETSTATE_CALL)
				{
					return BET_TYPE_CALL;
				}
				else if(money.m_lBetState==BETSTATE_CHECK)
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==4 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==5 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==6 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
				else if(m_cGameInfo.m_lCardsDealt==7 && money.m_lBetCount >= GetRaiseCount())
				{
					return BET_TYPE_CALL;
				}
			}

			if((0<money.m_llCMoney)&&(money.m_llCallMoney<money.m_llCMoney)){
				return BET_TYPE_BET;
			}
			else{
				return BETSTATE_CALL;
			}
		}
		break;
	case BETSTATE_DIE:
		return BET_TYPE_CHECK;
		break;
	default:
		return BET_TYPE_CHECK;
		break;
	}

}
//----------------------------------------------------------------------------------------------------
void CGameMgr::OnBettingReq(long lUSN, long lBetType)
{
	// 해킹방지
	// 베팅 타입밸류가 범위외에 것이 들어 올때가 있음...
	switch( lBetType ){
	case BETSTATE_CALL://=1,
		break;
	case BETSTATE_BBING://,
	case BETSTATE_CHECK://,
	case BETSTATE_DOUBLE://,
	case BETSTATE_QUARTER://,
	case BETSTATE_HALF://,
		{

		}
		break;
	case BETSTATE_DIE://,
		break;
	default:
		FileDebug( "범위 외의 베팅 값이 들어왔습니다.=%d \n", lBetType );
		return;
	}

	int nIndex=USNToIdx(lUSN);
	if(m_cRCRoomData.m_lState!=GAMESTATE_PLAY) return;
	if(lUSN!=m_cGameInfo.m_lBetUSN) return;

	if(nIndex<0) return;
	UserInfo& ui=GetUI(nIndex);
	if(ui.m_lUserState!=USERSTATE_PLAYING) return;
	Money& money=GetMoney(nIndex);
	if(money.m_lBetState==BETSTATE_DIE) return;

	if(money.m_lBetState==BETSTATE_CHECK && lBetType==BETSTATE_CHECK) return;

	//BOOL bExitPossible=FALSE;
	//bExitPossible=IsRuleExit( nIndex );
	//if( !bExitPossible ) //룰게임중이다
	//{
	//	if( lBetType==BETSTATE_DIE )
	//		return;
	//}
	RemoveTimer(TIMER_BETTING);

	__int64 lTempCallMoney=0;
	lTempCallMoney=money.m_llCallMoney;

	if( lBetType==BETSTATE_DOUBLE || 
		lBetType==BETSTATE_QUARTER || 
		lBetType==BETSTATE_HALF || 
		lBetType==BETSTATE_FULL) 
	{
		if (money.m_llCMoney<lTempCallMoney)
		{
			lBetType=BETSTATE_CALL;

			char tmpString[256];
			sprintf(tmpString, "USN : %d, %s",lUSN," OnRcvBettingReq : money.m_lCMoney <= money.m_llCallMoney");
			string str(tmpString);
			//string str=::format("USN : %d, %s",lUSN," OnRcvBettingReq : money.m_lCMoney <= money.m_llCallMoney");
			m_cFileLog.DebugLog(str.c_str());
		}
	}

	MsgSC_BettingAnsMsg msg;


	msg.Clear();
	bool bGiveUp=false;
	long lBetBtnType=0;
	if(lBetType==BETSTATE_DIE)
	{
		msg.m_BetType=BETSTATE_DIE;
		ui.m_lUserState=USERSTATE_DIE;
		ui.m_lDieCardsDealt=m_cGameInfo.m_lCardsDealt; //다이시점에서카드수를 알고 있자
		money.m_llTakeMoney=0;
	}
	SetBetttingMoney(lUSN, lBetType, msg);

	//money.m_lBetState=lBetType;
	//if(m_cGameInfo.m_lPreBetType == BETSTATE_NONE){
	//	if(lBetType !=BETSTATE_CALL){
	//		m_cGameInfo.m_lPreBetType = lBetType;
	//	}
	//}
	//else{
	//	if(lBetType !=BETSTATE_CALL && lBetType != BETSTATE_DIE){
	//		m_cGameInfo.m_lPreBetType = lBetType;
	//	}
	//}
	msg.m_lUSN=lUSN;
	msg.m_nIndex=nIndex;
	SendBettingAnsMsg(msg, lBetType);
	bGiveUp=false;
	if(IsNextBet(m_cGameInfo.m_lBetUSN))
	{
		lBetBtnType=GetBetBtnNextType(m_cGameInfo.m_lBetUSN, BET_TYPE_NONE);
		if(GetPlayerCount()>1)
		{
			RemoveTimer(TIMER_BETTING);
			SendBetting(lBetBtnType);
			return;
		}
		bGiveUp=true;
	}
	GameEndProcess();
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::GameEnd(bool bGiveUp)
{
	//	__int64 lTempPoolMoney=m_cGameInfo.m_llPoolMoney;
	RemoveTimer(TIMER_AUTOBET);
	RemoveTimer(TIMER_GAMEEND);
	RemoveTimer(TIMER_DEALOPEN);
	RemoveTimer(TIMER_BETTING);
	if(m_cRCRoomData.m_lState==GAMESTATE_SAVE) return;
	m_cGameInfo.m_bGiveUp=bGiveUp;

	SwitchState(GAMESTATE_SAVE);
	bool b49Replay=false;
	EndItem();
	DetermineResult(bGiveUp);

	MoneyDivision(m_cGameInfo.m_vtWinIndex, b49Replay);

	if(0==m_cGameInfo.m_vtWinIndex.size()) return;
	int nWinIndex=m_cGameInfo.m_vtWinIndex[0];

	m_cGameInfo.m_lBossUSN=IdxToUSN(nWinIndex);
	m_cGameInfo.Clear49Replay();

	Money & Winmoney=GetMoney(nWinIndex);



	// typhon 2006/03/07
	// 프로모션 관련해서 내부에서 먼저 세이브하구 다시 돈을 넣어 주는 것으로...
	// 원래는 DB_Save가 먼저 처리되구 SendFinished가 처리된다.
	DB_Save(true);

	SendFinished(bGiveUp, nWinIndex);

	// 승자의 족보 결과 
	//UserInfo & ui=GetUI(nWinIndex);
	//if(ui.m_lUSN>0)
	//{
	//	string sMsg;
	//	if(bGiveUp)
	//		SendGameEndSystemMsg(SYSMSG_WINER, ui.m_lUSN, bGiveUp, ui.m_sNickName);
	//	else
	//	{
	//		sMsg=::format("[%s]님이 %s", ui.m_sNickName.c_str(), Winmoney.m_sMoneyMsg.c_str());
	//		SendGameEndSystemMsg(SYSMSG_WINER, ui.m_lUSN, bGiveUp, sMsg);
	//	}
	//}
	//else
	//{
	//	if(bGiveUp)
	//		SendGameEndSystemMsg(SYSMSG_WINER, IdxToUSN(nWinIndex), bGiveUp, _T(""));
	//	else
	//		SendGameEndSystemMsg(SYSMSG_WINER, IdxToUSN(nWinIndex), bGiveUp, Winmoney.m_sMoneyMsg);
	//}
	//// 딜러비 처리
	//ForEachElmt(vector<UserMoney>, m_cGameInfo.m_CDivisionMoney.m_vtUser, ia, ib)
	//{
	//	if((*ia).m_llDealMoney>0)
	//	{
	//		SendGameEndSystemMsg(SYSMSG_DEALER, (*ia).m_lUSN, false, (*ia).m_sNickName, (*ia).m_llDealMoney);
	//	}
	//}
	//// 잃은 돈
	//ForEachElmt(vector<UserMoney>, m_cGameInfo.m_CDivisionMoney.m_vtUser, iia, iib)
	//{
	//	if(((*iia).m_llTakeMoney - (*iia).m_llCallHabMoney)<0)
	//	{
	//		SendGameEndSystemMsg(SYSMSG_MONEYLOSER,(*iia).m_lUSN, bGiveUp,(*iia).m_sNickName,((*iia).m_llCallHabMoney - (*iia).m_llTakeMoney));
	//	}
	//}

	//// 획득한  돈
	//ForEachElmt(vector<UserMoney>, m_cGameInfo.m_CDivisionMoney.m_vtUser, ja, jb)
	//{
	//	if((*ja).m_llTakeMoney >= ((*ja).m_llCallHabMoney))
	//	{
	//		if((*ja).m_lUSN==GetUI(nWinIndex).m_lUSN)
	//			SendGameEndSystemMsg(SYSMSG_MONEYWINADD, (*ja).m_lUSN, bGiveUp, (*ja).m_sNickName, ((*ja).m_llTakeMoney - (*ja).m_llCallHabMoney));
	//		else
	//			SendGameEndSystemMsg(SYSMSG_MONEYADD, (*ja).m_lUSN, bGiveUp, (*ja).m_sNickName, ((*ja).m_llTakeMoney - (*ja).m_llCallHabMoney));
	//	}
	//}
	int nTotal=GetUISize();
	//for(int i=0; i<nTotal; i++)
	//{
	//	UserInfo & ui=GetUI(i);
	//	if(ui.m_lUSN==-1) continue;
	//	if(ui.m_lUserState==USERSTATE_WAITING || ui.m_lUserState==USERSTATE_DIE || ui.m_lUserState==USERSTATE_READY) continue;
	//	if(true==IsInRange(ui.m_nIndex, 0, m_cGameInfo.m_vllGiveMoney.size()-1)){
	//		if(m_cGameInfo.m_vllGiveMoney[ui.m_nIndex]>0){
	//			SendGameEndSystemMsg(SYSMSG_GIVEMONEY, ui.m_lUSN, bGiveUp, ui.m_sNickName, m_cGameInfo.m_vllGiveMoney[ui.m_nIndex]);
	//		}
	//	}
	//}
	m_cGameInfo.SetGameEnd();

	// DB_Save
	//GuardianAngelCheck(); //올인 구호자금
	ExtMoneyCheck();        // 제한머니 
	PromotionCheck();
	//20111226 임시 제거
	//m_cObjectRefill.RefillCheck();			// fefill check 해서 받아라
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN==-1) continue;
		if(ui.m_lUserState==USERSTATE_WAITING || ui.m_lUserState==USERSTATE_49WAITING || ui.m_lUserState==USERSTATE_READY) continue;
		DB_User_Log(ui.m_lUSN, "0000");
	}
	DB_Room_Log();			// 판로그	
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN==-1) continue;
		if(ui.m_lUserState==USERSTATE_WAITING || ui.m_lUserState==USERSTATE_49WAITING || ui.m_lUserState==USERSTATE_READY) continue;
		ui.m_lUserState=USERSTATE_SELECTCONTINUE;
	}
	if(true==m_cRCRoomData.m_option.m_bEcho){
		int nSetTime=Get_Velocity(TIMER_ECHO_FINISH, -1);
		GetUITable().SetAck(TIMER_ECHO_FINISH);
		SetTimer(TIMER_ECHO_FINISH, nSetTime, 0);
	}
	else{
		int nSetTime=Get_Velocity(TIMER_CONTINUE, GetPlayerCount());
		if(true==bGiveUp)
		{
			nSetTime=Get_Velocity(TIMER_CONTINUE, -1);
		}
		SetTimer(TIMER_CONTINUE, nSetTime, NULL);
	}

	char tmpString[256];
	sprintf(tmpString, "%d$%d$%I64d", m_cRCRoomData.m_option.m_lMaxUserCnt, m_cRCRoomData.GetUserCnt(), m_cRCRoomData.GetAvgMoney());
	string str(tmpString);
	//string str=::format("%d$%d$%I64d", m_cRCRoomData.m_option.m_lMaxUserCnt, m_cRCRoomData.GetUserCnt(), m_cRCRoomData.GetAvgMoney());


	//long lReturn=m_pGRCContainer->SendMessageToServer(MSGTYPE_ODBGW_UPDATE_RECOMMEND_ROOM, 0, str.c_str(), (long)str.size());
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::GameEndProcess(void)
{
	bool bGiveUp=false;
	if(GetPlayerCount()	< 2)
		bGiveUp=true;
	m_cGameInfo.m_bGiveUp=bGiveUp;
	// 게임을 종료 해야 한다.
	if(bGiveUp==false)
	{
		if(IsDealCard())
			SendDealCard();
		else{
			GameEnd(bGiveUp);
		}
	}
	else{
		GameEnd(bGiveUp);
	}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::GameEndTurn()
{
	int nSetTime=Get_Velocity(TIMER_GAMEEND, -1);
	SetTimer(TIMER_GAMEEND, nSetTime, NULL);
}


#endif