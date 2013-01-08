// CGameRule.cpp: implementation of the CGameRule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GameRule_Poker.h"

#if defined(_Poker)




CGameRule::CGameRule()
{

}

CGameRule::~CGameRule()
{
}

long CGameRule::GetBettingType(long lRoomType, long lChoiceMode, int nCardsDealt)
{
	if(lRoomType==0){
		if(lChoiceMode==0){
			switch(nCardsDealt){
			case 0: return BET_TYPE_NONE;
			case 1: return BET_TYPE_BET;
			case 2: return BET_TYPE_BET;
			}
		}
		else if(lChoiceMode==1){
			switch(nCardsDealt){
			case 0: return BET_TYPE_NONE;
			case 1: return BET_TYPE_BET;
			case 2: return BET_TYPE_BET;
			}
		}
		return BET_TYPE_NONE;
	}
	return BET_TYPE_NONE;
}

long CGameRule::GetBettingTurn(long lRoomType, long lChoiceMode, int nCardsDealt, long lBetCount)
{
	if(lRoomType==0){
		if(lChoiceMode==0){
			switch(nCardsDealt){
			case 0: return BET_TURN_NONE;
			case 1: return BET_TURN_LIVE_1;
			case 2:
				{
				}
				break;
			}
		}
		else if(lChoiceMode==1){
			switch(nCardsDealt){
			case 0: return BET_TURN_NONE;
			case 1: return BET_TURN_NONE;
			case 2: return BET_TURN_LIVE_1;
			case 3:
				{
				}
				break;
			}
		}
	}
	return BET_TURN_NONE;
}

bool CGameRule::IsSelect(long lRoomType, long lChoiceMode)
{
	if(lRoomType==0){
		if(lChoiceMode==0){
			return true;
		}
		else if(lChoiceMode==1){
			return true;
		}
		return false;
	}
	return false;
}

bool CGameRule::IsErase(long lRoomType, long lChoiceMode)
{
	if(lRoomType==0){
		if(lChoiceMode==0){
			return false;
		}
		else if(lChoiceMode==1){
			return true;
		}
		return false;
	}
	return false;
}

bool CGameRule::IsDealCard(long lRoomType, long lChoiceMode, int nCardsDealt)
{
	if(nCardsDealt >= GetMaxCardCount(lRoomType, lChoiceMode))
		return false;
	return true;
}

bool CGameRule::IsHiddenCard(long lRoomType, long lChoiceMode, int nCardsDealt)
{
	if(nCardsDealt==GetHiddenCardCount(lRoomType, lChoiceMode))
		return true;
	return false;
}

bool CGameRule::IsSameCard(long lRoomType, long lChoiceMode, int nCurCardsDealts)
{
	if(lRoomType==0){
		if(lChoiceMode==0){
			return false;
		}
		else if(lChoiceMode==1){
			return false;
		}
		return false;
	}
	return false;
}

bool CGameRule::IsOpenCard(long lRoomType, long lChoiceMode, int nCardsDealt, int nCurCardsDealts, bool bIsDeal)
{
	if(lRoomType==0){
		if(lChoiceMode==0){
			return ((3<=nCurCardsDealts)&&(false==IsHiddenCard(lRoomType, lChoiceMode, nCurCardsDealts)));
		}
		else if(lChoiceMode==1){
			return ((3<=nCurCardsDealts)&&(false==IsHiddenCard(lRoomType, lChoiceMode, nCurCardsDealts)));
		}
		return false;
	}
	return false;
}

int	CGameRule::GetShuffleCount(long lRoomType, long lChoiceMode)
{
	if(lRoomType==0){
		if(lChoiceMode==0){
			return 4*13;
		}
		else if(lChoiceMode==1){
			return 4*13;
		}
		return 4*13;
	}
	return 4*13;
}

int	CGameRule::GetMaxDealCount(long lRoomType, long lChoiceMode)
{
	if(lRoomType==0){
		if(lChoiceMode==0){
			return 3;
		}
		else if(lChoiceMode==1){
			return 4;
		}
		return 3;
	}
	return 3;
}

int	CGameRule::GetMaxCardCount(long lRoomType, long lChoiceMode)
{
	if(lRoomType==0){
		if(lChoiceMode==0){
			return 7;
		}
		else if(lChoiceMode==1){
			return 7;
		}
		return 7;
	}
	return 7;
}

int	CGameRule::GetHiddenCardCount(long lRoomType, long lChoiceMode)
{
	if(lRoomType==0){
		if(lChoiceMode==0){
			return 7;
		}
		else if(lChoiceMode==1){
			return 7;
		}
		return 7;
	}
	return 7;
}

int	CGameRule::GetMaxDeckCount(long lRoomType, long lChoiceMode)
{
	if(lRoomType==0){
		if(lChoiceMode==0){
			return 7;
		}
		else if(lChoiceMode==1){
			return 7;
		}
		return 7;
	}
	return 7;
}

int CGameRule::GetMaxPlayerUserCount(long lRoomType, long lChoiceMode)
{
	if(lRoomType==0){
		if(lChoiceMode==0){
			return 5;
		}
		else if(lChoiceMode==1){
			return 5;
		}
		return 5;
	}
	return 5;
}

int CGameRule::GetMaxPlayerCardCount(long lRoomType, long lChoiceMode)
{
	if(lRoomType==0){
		if(lChoiceMode==0){
			return 5;
		}
		else if(lChoiceMode==1){
			return 5;
		}
		return 5;
	}
	return 5;
}

int CGameRule::GetRaiseCount(long lRoomType, long lChoiceMode, int nCardsDealt)
{
	if(lRoomType==0){
		if(lChoiceMode==0){
			switch(nCardsDealt){
			case 4: return 1;
			case 5: return 2;
			case 6: return 2;
			case 7: return 2;
			}
		}
		else if(lChoiceMode==1){
			switch(nCardsDealt){
			case 4: return 1;
			case 5: return 2;
			case 6: return 2;
			case 7: return 2;
			}
		}
	}
	return 2;
}


int CGameRule::Get_Velocity(long lRoomType, long lChoiceMode, long lTimerType, long lTimerOpt)
{
	if(lRoomType==0){
		switch(lTimerType){
		case TIMER_START:
			{
				if(0>lTimerOpt) return 15500;
			}
			return (10000 + ( lTimerOpt - 1 ) * 1000);
		case TIMER_DEALOPEN:
			{
				if(0==lChoiceMode){
					if(0>lTimerOpt) return 15500;
				}
				else{
					if(0>lTimerOpt) return 25500;
				}
			}
			return (10000 + ( lTimerOpt - 1 ) * 1000);
		case TIMER_BETTING:
			{
				if(0>lTimerOpt) return 10500;
			}
			return 10500;
		case TIMER_AUTOBET:
			return 1200;
		case TIMER_SPEEDGAME:
			return 1200;
		case TIMER_GAMEEND:
			{
				if(0>lTimerOpt) return 8500;
			}
			return 8000 + ( lTimerOpt - 1 ) * 2000;
		case TIMER_NEWGAME:
			{
				if(0>lTimerOpt) return 9000;
			}
			return (5000 + ( lTimerOpt - 1 ) * 1000);
		case TIMER_CONTINUE:
			{
				if(0>lTimerOpt) return 9000 + 10000;
			}
			return (5000 + ( lTimerOpt - 1 ) * 1000 + 10000);
		case TIMER_PURGE: return 1800000;
		case TIMER_ECHO_DEALS: return 10500;
		case TIMER_ECHO_BET: return 10500;
		case TIMER_ECHO_DEAL: return 10500;
		case TIMER_ECHO_FINISH: return 10500;
		}
	}
	return 0;
}



//--------------------------------------------------------------//
//
//--------------------------------------------------------------//
RankPrecedence PokerRulesToRankPrecedence(CPokerRules* pcPokerRules)
{
	if(NULL==pcPokerRules) return RANK_NONE;
	switch(pcPokerRules->m_ePokerType){
	case CPokerRules::POKERTYPE_NONE: return RANK_TOP;
	case CPokerRules::POKERTYPE_ONEPAIR: return RANK_ONEPAIR;
	case CPokerRules::POKERTYPE_TWOPAIR: return RANK_TWOPAIR;
	case CPokerRules::POKERTYPE_THREE: return RANK_THREEOFAKIND;
	case CPokerRules::POKERTYPE_STRAIGHT: return RANK_STRAIGHT;
	case CPokerRules::POKERTYPE_BACKSTRAIGHT: return RANK_BACKSTRAIGHT;
	case CPokerRules::POKERTYPE_MOUNTAIN: return RANK_MOUNTAIN;
	case CPokerRules::POKERTYPE_FLUSH: return RANK_FLUSH;
	case CPokerRules::POKERTYPE_FULLHOUSE: return RANK_FULLHOUSE;
	case CPokerRules::POKERTYPE_FOUR: return RANK_FOUROFAKIND;
	case CPokerRules::POKERTYPE_STRAIGHTFLUSH: return RANK_STRAIGHTFLUSH;
	case CPokerRules::POKERTYPE_BACKSTRAIGHTFLUSH: return RANK_STRAIGHTFLUSH;
	case CPokerRules::POKERTYPE_ROYALSTRAIGHTFLUSH: return RANK_ROYALSTRAIGHTFLUSH;
	}
	return RANK_NONE;
}
//--------------------------------------------------------------//
//
//--------------------------------------------------------------//
string PokerRulesToRankString(long lRankType)
{
	switch(lRankType){
	case RANK_TOP: return "탑";
	case RANK_ONEPAIR: return "원페어";
	case RANK_TWOPAIR: return "투페어";
	case RANK_THREEOFAKIND: return "트리플";
	case RANK_STRAIGHT: return "스트레이트";
	case RANK_BACKSTRAIGHT: return "백스트레이트";
	case RANK_MOUNTAIN: return "마운틴";
	case RANK_FLUSH: return "플러시";
	case RANK_FULLHOUSE: return "풀하우스";
	case RANK_FOUROFAKIND: return "포커드";
	case RANK_STRAIGHTFLUSH: return "스트레이트플러시";
	case RANK_ROYALSTRAIGHTFLUSH: return "로얄스트레이트플러시";
	}
	return "-";
}
//--------------------------------------------------------------//
//
//--------------------------------------------------------------//

#endif