//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"

#include "GameMgr_Poker.h"
#include "GameRule_Poker.h"

#if defined(_Poker)


int CGameMgr::GetRuleBet( const long lUSN )
{
	if(TRUE == m_cGameInfo.m_b49Rematch) return BETSTATE_NONE;
	int nIndex = USNToIdx( lUSN );
	if( nIndex<0 ) return BETSTATE_NONE;	//UserInfo가 존재치 않으면 관람자이거나 없는것임
	if( m_cRCRoomData.m_lState == GAMESTATE_READY || m_cRCRoomData.m_lState == GAMESTATE_SAVE ) return BETSTATE_NONE;
	if( IsRuleFree() ) return BETSTATE_NONE;
	return GetRule591( lUSN );
}

BOOL CGameMgr::IsRuleFree()
{
	if(TRUE == m_cGameInfo.m_b49Rematch) return FALSE;
	if( m_cRCRoomData.m_option.m_lBetRule == BETTING_FREE )
	{
		if( m_cGameInfo.m_lCardsDealt <= GetMaxDealCount() )
			return TRUE;
	}
	return FALSE;
}


int CGameMgr::GetRule591( const long lUSN )
{
	int nIndex = USNToIdx( lUSN );
	if( nIndex<0 ) return BETSTATE_NONE;	//UserInfo가 존재치 않으면 관람자이거나 없는것임
	if( m_cRCRoomData.m_option.m_lBetRule != FIRST_591 ) return BETSTATE_NONE;
	UserInfo & ui = GetUI(nIndex);
	Money &money = GetMoney(nIndex);
	if(ui.m_lUserState == USERSTATE_READY || ui.m_lUserState == USERSTATE_49WAITING || ui.m_lUserState == USERSTATE_WAITING || ui.m_lUserState == USERSTATE_DIE) return BETSTATE_NONE;
	if( m_cGameInfo.m_lCardsDealt <= 5 )
	{
		if(m_cGameInfo.m_lCardsDealt==4){
			if(money.m_lBetCount==0){
				if(money.m_llCMoney >= (((money.m_llCallMoney + m_cGameInfo.m_llPoolMoney) * 5 / 10) + money.m_llCallMoney)){
					return BETSTATE_HALF;
				}
				else{
					return BETSTATE_CHECK;
				}
			}
			else if(money.m_lBetCount<=GetRaiseCount()){
				int nTotal=GetUISize();
				if((money.m_llCallMoney==0) && (money.m_lBetState!=0)){
					for(int i=1; i<nTotal; ++i){
						UserInfo& ui1=GetUI(Seat[nIndex][i]);
						if(ui1.m_lUSN!=EMPTY_USER && ui1.m_lUserState==USERSTATE_PLAYING){
							Money & money1=GetMoney(ui1.m_nIndex);
							if((money1.m_llCallMoney==0) && (money1.m_lBetState!=0)) continue;
							return BETSTATE_CALL;
						}
					}
					return BETSTATE_DEAL;
				}
				else{
					return BETSTATE_CALL;
				}
				//if(lUSN == m_cGameInfo.m_lBossUSN){
				//	return BETSTATE_CALL;
				//}
				//else{
				//	return BETSTATE_DEAL;
				//}
			}
		}
		if(m_cGameInfo.m_lCardsDealt==5){
			if(money.m_lBetCount == 0){
				if(money.m_llCMoney >= (((money.m_llCallMoney + m_cGameInfo.m_llPoolMoney) * 5 / 10) + money.m_llCallMoney)){
					return BETSTATE_HALF;
				}
				else{
					return BETSTATE_CHECK;
				}
			}
			else{
				return BETSTATE_NONE;
			}
		}
	}
	return BETSTATE_NONE;
}
//****************************************************************************
//
//      현재 게임룰에 맞으면 나갈 수있게 함( 그전에 만약에 나가면 강퇴 )
//
//****************************************************************************
BOOL CGameMgr::IsRuleExit( const int nIndex )
{
	if( nIndex<0 )return TRUE;	//UserInfo가 존재치 않으면 관람자이거나 없는것임
	if( m_cRCRoomData.m_lState==GAMESTATE_READY || m_cRCRoomData.m_lState==GAMESTATE_SAVE )return TRUE;
	if(IsRuleFree_Free()) return TRUE;

	UserInfo & ui=GetUI(nIndex);

	if(ui.m_lUserState==USERSTATE_READY || ui.m_lUserState==USERSTATE_WAITING || ui.m_lUserState==USERSTATE_DIE) return TRUE;

	//if(m_cGameInfo.m_lCardsDealt<5) return FALSE; 
	// 문광부 2차 수정
	if(m_cGameInfo.m_lCardsDealt<4) return FALSE; 
	if( IsRule_Speed() )
	{
		// 스피드룰 따로 처리
		if( IsNow491(nIndex) )
			return FALSE;
	} else {
		if(IsRule491())
		{
			//if(IsNow491(nIndex) && !m_cGameInfo.b491AutoBettingFlag )
			if(IsNow491(nIndex))
				return FALSE;
		} else {
			// 기존룰
			if(IsNow591(nIndex))
				return FALSE;
			else if(IsNow592(nIndex))
			{
				if(IsRule591() && IsRule_NoDie()) // 591 노다이
					return FALSE;

				if(IsRule592())
					return FALSE;
				else
					return TRUE;
			
			}
			else if(IsNow593(nIndex))
			{
				if(IsRule591() || IsRule592())
				{
					if(IsRule_NoDie())
						return FALSE;
				}

				return TRUE;
			}
		}
	}
	return TRUE;
}
//----------------------------------------------------------------------------------------------------
BOOL CGameMgr::IsRuleFree_Free()
{
	if(m_cRCRoomData.m_option.m_lBetRule==FIRST_FREE && m_cRCRoomData.m_option.m_lAddRule==SECOND_FREE)
		return TRUE;

	return FALSE;
}
//----------------------------------------------------------------------------------------------------
BOOL CGameMgr::IsRule491()
{
	if((m_cRCRoomData.m_option.m_lBetRule==FIRST_491_1QUARTER ||
		m_cRCRoomData.m_option.m_lBetRule==FIRST_491_1HALF ||
		m_cRCRoomData.m_option.m_lBetRule==FIRST_491_2HALF)
		&& m_cRCRoomData.m_option.m_lAddRule==SECOND_FREE)
		return TRUE;

	return FALSE;
}
//----------------------------------------------------------------------------------------------------
BOOL CGameMgr::IsRule591()
{
	if(m_cRCRoomData.m_option.m_lBetRule==FIRST_591)
		return TRUE;

	return FALSE;
}
//----------------------------------------------------------------------------------------------------
BOOL CGameMgr::IsRule592()
{
	if(m_cRCRoomData.m_option.m_lBetRule==FIRST_592)
		return TRUE;

	return FALSE;
}
//----------------------------------------------------------------------------------------------------
BOOL CGameMgr::IsRule_Free()
{
	if(m_cRCRoomData.m_option.m_lAddRule==SECOND_FREE)
		return TRUE;

	return FALSE;
}
//----------------------------------------------------------------------------------------------------
BOOL CGameMgr::IsRule_NoDie()
{
	if(m_cRCRoomData.m_option.m_lAddRule==SECOND_NODIE)
		return TRUE;

	return FALSE;
}
//----------------------------------------------------------------------------------------------------
BOOL	CGameMgr::IsRule_Speed()
{
	if(m_cRCRoomData.m_option.m_lBetRule==FIRST_592_SPEED)		
		return TRUE;	
	return FALSE;
}
//----------------------------------------------------------------------------------------------------
BOOL CGameMgr::IsNow491(int nIndex)
{
	Money &money=GetMoney(nIndex);

	if(m_cGameInfo.m_lCardsDealt==4 && money.m_lBetCount==0)
		return TRUE;

	return FALSE;
}
//----------------------------------------------------------------------------------------------------
BOOL CGameMgr::IsNow492(int nIndex)
{
	Money &money=GetMoney(nIndex);

	if(m_cGameInfo.m_lCardsDealt==4 && money.m_lBetCount==1)
		return TRUE;

	return FALSE;
}
//----------------------------------------------------------------------------------------------------
BOOL CGameMgr::IsNow591(int nIndex)
{
	Money &money=GetMoney(nIndex);

	if(m_cGameInfo.m_lCardsDealt==5 && money.m_lBetCount==0)
		return TRUE;

	return FALSE;
}
//----------------------------------------------------------------------------------------------------
BOOL CGameMgr::IsNow592(int nIndex)
{
	Money &money=GetMoney(nIndex);

	if(m_cGameInfo.m_lCardsDealt==5 && money.m_lBetCount==1)
		return TRUE;

	return FALSE;
}
//----------------------------------------------------------------------------------------------------
BOOL CGameMgr::IsNow593(int nIndex)
{
	Money &money=GetMoney(nIndex);

	if(m_cGameInfo.m_lCardsDealt==5 && money.m_lBetCount==2)
		return TRUE;

	return FALSE;
}
//----------------------------------------------------------------------------------------------------
bool CGameMgr::IsErase()
{
	return CGameRule::IsErase(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode);
}
//----------------------------------------------------------------------------------------------------
bool CGameMgr::IsSelect()
{
	return CGameRule::IsSelect(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode);
}
//----------------------------------------------------------------------------------------------------
bool CGameMgr::IsDealCard()
{
	if(GetPlayerCount()	< 2)
		return false;
	return CGameRule::IsDealCard(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode, m_cGameInfo.m_lCardsDealt);
}
//----------------------------------------------------------------------------------------------------
bool CGameMgr::IsHiddenCard()
{
	return CGameRule::IsHiddenCard(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode, m_cGameInfo.m_lCardsDealt);
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::GetBettingType()
{
	return CGameRule::GetBettingType(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode, m_cGameInfo.m_lCardsDealt);
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::GetBettingTurn()
{
	return CGameRule::GetBettingTurn(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode, m_cGameInfo.m_lCardsDealt, m_cGameInfo.m_lBetCount);
}
//----------------------------------------------------------------------------------------------------
bool CGameMgr::IsOpenCard(int nCardsDealt, bool bIsDeal)
{
	return CGameRule::IsOpenCard(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode, m_cGameInfo.m_lCardsDealt, nCardsDealt, bIsDeal);
}
//----------------------------------------------------------------------------------------------------
int	CGameMgr::GetShuffleCount()
{
	return CGameRule::GetShuffleCount(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode);
}
//----------------------------------------------------------------------------------------------------
int	CGameMgr::GetMaxDealCount()
{
	return CGameRule::GetMaxDealCount(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode);
}
//----------------------------------------------------------------------------------------------------
int	CGameMgr::GetMaxCardCount()
{
	return CGameRule::GetMaxCardCount(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode);
}
//----------------------------------------------------------------------------------------------------
int	CGameMgr::GetHiddenCardCount()
{
	return CGameRule::GetHiddenCardCount(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode);
}
//----------------------------------------------------------------------------------------------------
int	CGameMgr::GetMaxDeckCount()
{
	return CGameRule::GetMaxDeckCount(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode);
}
//----------------------------------------------------------------------------------------------------
int	CGameMgr::GetMaxPlayerUserCount()
{
	return CGameRule::GetMaxPlayerUserCount(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode);
}
//----------------------------------------------------------------------------------------------------
int	CGameMgr::GetMaxPlayerCardCount()
{
	return CGameRule::GetMaxPlayerCardCount(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode);
}
//----------------------------------------------------------------------------------------------------
int	CGameMgr::GetRaiseCount()
{
	return CGameRule::GetRaiseCount(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode, m_cGameInfo.m_lCardsDealt);
}
//----------------------------------------------------------------------------------------------------
int	CGameMgr::Get_Velocity(long lTimerType, long lPlayCnt)
{
	return CGameRule::Get_Velocity(m_cRCRoomData.m_option.m_lRoomType, m_cRCRoomData.m_option.m_lChoiceMode, lTimerType, lPlayCnt);
}
//----------------------------------------------------------------------------------------------------
int	CGameMgr::FindBossIndex()
{	
	if (m_cRCRoomData.m_lState!=GAMESTATE_PLAY) {
		m_cFileLog.DebugLog("[ASSERT] FindBossIndex : m_cRCRoomData.m_lState!=GAMESTATE_PLAY");
		//		ASSERT(FALSE && "FindBossIndex() 에서 GAMESTATE_PLAY가 아니다");
		return -1;
	}
	CPokerRules cPokerRules;
	cPokerRules.CreatePokerRules();
	int nTotal=GetUISize();
	if(0>nTotal) return -1;
	//tHyperInt* ptHyperInt_Level=new tHyperInt[nTotal];
	vector<tHyperInt> tvHyperInt_Level;
	tHyperInt tHyperInt_Level;
	for(int i=0; i<nTotal; i++){
		tvHyperInt_Level.push_back(tHyperInt_Level);
	}
	//tHyperInt tHyperInt_Level[nTotal];
	CTVector<long> ctTemp;
	int nIndex=0;
	for(int i=0; i< nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUserState!=USERSTATE_PLAYING) continue;
		if(ui.m_lUSN<0) continue;
		if(ui.m_nIndex<0) continue;
		Cards & Card=GetCards(ui.m_nIndex);
		ctTemp.assign(Card.m_vtCards.begin(), Card.m_vtCards.end());
		cPokerRules.ClearPokerRules();
		cPokerRules.SetMakePokerRules(NULL, NULL, &ctTemp, 2, ctTemp.size()-1);
		if(true==IsInRange(ui.m_nIndex, 0, nTotal-1)){
			tvHyperInt_Level[ui.m_nIndex]=cPokerRules.m_tHyperInt_Level;
			if(tvHyperInt_Level[ui.m_nIndex].m_llHyperInt>tHyperInt_Level.m_llHyperInt){
				tHyperInt_Level=tvHyperInt_Level[ui.m_nIndex];
				nIndex=ui.m_nIndex;
			}
		}
	}
	//if(NULL!=ptHyperInt_Level){
	//	delete [] ptHyperInt_Level;
	//	ptHyperInt_Level=NULL;
	//}
	return nIndex;
}
//----------------------------------------------------------------------------------------------------
bool CGameMgr::DetermineResult(bool bGiveUp)
{
	char tmpString[256];
	m_cGameInfo.m_vtWinIndex.clear();
	CPokerRules cPokerRules;
	cPokerRules.CreatePokerRules();
	int nTotal=GetUISize();
	if(0>nTotal) return false;
	CTVector<long> ctTemp;
	tHyperInt tHyperInt_Level;
	m_cGameInfo.m_cvtHyperInt_Level.DelVector();
	int nIndex=0;
	string strCard;
	for(int i=0; i< nTotal; i++){
		UserInfo & ui=GetUI(i);
		if(ui.m_lUserState==USERSTATE_WAITING || ui.m_lUserState==USERSTATE_READY) continue;
		if(ui.m_lUSN<0) continue;
		if(ui.m_nIndex<0) continue;
		Cards & Card=GetCards(ui.m_nIndex);
		ctTemp.assign(Card.m_vtCards.begin(), Card.m_vtCards.end());
		cPokerRules.ClearPokerRules();
		cPokerRules.SetMakePokerRules(NULL, NULL, &ctTemp, 0, ctTemp.size()-1);
		if(ui.m_lUserState!=USERSTATE_DIE){
			m_cGameInfo.m_cvtHyperInt_Level.AddVector(ui.m_lUSN, cPokerRules.m_tHyperInt_Level);
			if(cPokerRules.m_tHyperInt_Level.m_llHyperInt>tHyperInt_Level.m_llHyperInt){
				tHyperInt_Level=cPokerRules.m_tHyperInt_Level;
				nIndex=ui.m_nIndex;
			}
		}
		Money & money=GetMoney(ui.m_nIndex);
		money.m_lBetState=PokerRulesToRankPrecedence(&cPokerRules);
		if(true==IsInRange(ui.m_nIndex, 0, m_cGameInfo.m_vResultOrder.size()-1)){
			m_cGameInfo.m_vResultOrder[ui.m_nIndex]=money.m_lBetState;
		}
		int nMakeTotal=cPokerRules.m_cvtMakeCard.TotalVector();
		switch(cPokerRules.m_ePokerType){
		case CPokerRules::POKERTYPE_NONE:
			{
				strCard=cPokerRules.MakeString(cPokerRules.m_ePokerType, &cPokerRules.m_cvtMakeCard, &cPokerRules.m_cvtRestCard, 1, ",");

				sprintf(tmpString, "[ %s ] TOP", strCard.c_str());

				money.m_sMoneyMsg.assign(tmpString);
				//money.m_sMoneyMsg=::format("[ %s ] TOP", strCard.c_str());
			}
			break;
		case CPokerRules::POKERTYPE_ONEPAIR:
			{
				strCard=cPokerRules.MakeString(cPokerRules.m_ePokerType, &cPokerRules.m_cvtMakeCard, &cPokerRules.m_cvtRestCard, 0, ",");

				sprintf(tmpString, "[ %s ] 원페어", strCard.c_str());

				money.m_sMoneyMsg.assign(tmpString);

				//money.m_sMoneyMsg=::format("[ %s ] 원페어", strCard.c_str());
			}
			break;
		case CPokerRules::POKERTYPE_TWOPAIR:
			{
				strCard=cPokerRules.MakeString(cPokerRules.m_ePokerType, &cPokerRules.m_cvtMakeCard, &cPokerRules.m_cvtRestCard, 0, ",");

				sprintf(tmpString, "[ %s ] 투페어", strCard.c_str());

				money.m_sMoneyMsg.assign(tmpString);

				//money.m_sMoneyMsg=::format("[ %s ] 투페어", strCard.c_str());
			}
			break;
		case CPokerRules::POKERTYPE_THREE:
			{
				strCard=cPokerRules.MakeString(cPokerRules.m_ePokerType, &cPokerRules.m_cvtMakeCard, &cPokerRules.m_cvtRestCard, 1, ",");

				sprintf(tmpString, "[ %s ] 트리플", strCard.c_str());

				money.m_sMoneyMsg.assign(tmpString);

				//money.m_sMoneyMsg=::format("[ %s ] 트리플", strCard.c_str());
			}
			break;
		case CPokerRules::POKERTYPE_STRAIGHT:
			{
				strCard=cPokerRules.MakeString(cPokerRules.m_ePokerType, &cPokerRules.m_cvtMakeCard, &cPokerRules.m_cvtRestCard, 0, ",");

				sprintf(tmpString, "[ %s ] 스트레이트", strCard.c_str());

				money.m_sMoneyMsg.assign(tmpString);

				//money.m_sMoneyMsg=::format("[ %s ]스트레이트", strCard.c_str());
			}
			break;
		case CPokerRules::POKERTYPE_BACKSTRAIGHT:
			{
				strCard=cPokerRules.MakeString(cPokerRules.m_ePokerType, &cPokerRules.m_cvtMakeCard, &cPokerRules.m_cvtRestCard, 0, ",");

				sprintf(tmpString, "[ %s ] 백스트레이트", strCard.c_str());

				money.m_sMoneyMsg.assign(tmpString);

				//money.m_sMoneyMsg=::format("[ %s ]백스트레이트", strCard.c_str());
			}
			break;
		case CPokerRules::POKERTYPE_MOUNTAIN:
			{
				strCard=cPokerRules.MakeString(cPokerRules.m_ePokerType, &cPokerRules.m_cvtMakeCard, &cPokerRules.m_cvtRestCard, 0, ",");

				sprintf(tmpString, "[ %s ] 마운틴", strCard.c_str());

				money.m_sMoneyMsg.assign(tmpString);

				//money.m_sMoneyMsg=::format("[ %s ]마운틴", strCard.c_str());
			}
			break;
		case CPokerRules::POKERTYPE_FLUSH:
			{
				strCard=cPokerRules.MakeString(cPokerRules.m_ePokerType, &cPokerRules.m_cvtMakeCard, &cPokerRules.m_cvtRestCard, 1, ",");

				sprintf(tmpString, "[ %s ] 플러시", strCard.c_str());

				money.m_sMoneyMsg.assign(tmpString);

				//money.m_sMoneyMsg=::format("[ %s ] 플러시", strCard.c_str());
			}
			break;
		case CPokerRules::POKERTYPE_FULLHOUSE:
			{
				strCard=cPokerRules.MakeString(cPokerRules.m_ePokerType, &cPokerRules.m_cvtMakeCard, &cPokerRules.m_cvtRestCard, 1, ",");

				sprintf(tmpString, "[ %s ] 풀하우스", strCard.c_str());

				money.m_sMoneyMsg.assign(tmpString);

				//money.m_sMoneyMsg=::format("[ %s ] 풀하우스", strCard.c_str());
			}
			break;
		case CPokerRules::POKERTYPE_FOUR:
			{
				strCard=cPokerRules.MakeString(cPokerRules.m_ePokerType, &cPokerRules.m_cvtMakeCard, &cPokerRules.m_cvtRestCard, 1, ",");

				sprintf(tmpString, "[ %s ] 포카드", strCard.c_str());

				money.m_sMoneyMsg.assign(tmpString);

				//money.m_sMoneyMsg=::format("[ %s ] 포카드", strCard.c_str());
			}
			break;
		case CPokerRules::POKERTYPE_STRAIGHTFLUSH:
			{
				strCard=cPokerRules.MakeString(cPokerRules.m_ePokerType, &cPokerRules.m_cvtMakeCard, &cPokerRules.m_cvtRestCard, 0, ",");

				sprintf(tmpString, "[ %s ] 스트레이트 플러시", strCard.c_str());

				money.m_sMoneyMsg.assign(tmpString);

				//money.m_sMoneyMsg=::format("[ %s ]스트레이트 플러시", strCard.c_str());
			}
			break;
		case CPokerRules::POKERTYPE_BACKSTRAIGHTFLUSH:
			{
				strCard=cPokerRules.MakeString(cPokerRules.m_ePokerType, &cPokerRules.m_cvtMakeCard, &cPokerRules.m_cvtRestCard, 0, ",");

				sprintf(tmpString, "[ %s ] 스트레이트 플러시", strCard.c_str());

				money.m_sMoneyMsg.assign(tmpString);

				//money.m_sMoneyMsg=::format("[ %s ]스트레이트 플러시", strCard.c_str());
			}
			break;
		case CPokerRules::POKERTYPE_ROYALSTRAIGHTFLUSH:
			{
				money.m_sMoneyMsg=_T("로얄 스트레이트 플러시");
			}
			break;
		}
	}
	m_cGameInfo.SortHyperInt();
	m_cGameInfo.m_vtWinIndex.push_back(nIndex);
	//if(NULL!=ptHyperInt_Level){
	//	delete [] ptHyperInt_Level;
	//	ptHyperInt_Level=NULL;
	//}
	return true;
}


#endif