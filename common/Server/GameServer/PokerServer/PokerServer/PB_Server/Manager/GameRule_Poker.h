// CGameInfo.h: interface for the CGameInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMERULE_H__E63C4669_A46B_48B8_A2E7_9EF3B9D20A1A__INCLUDED_)
#define AFX_GAMERULE_H__E63C4669_A46B_48B8_A2E7_9EF3B9D20A1A__INCLUDED_

#if _MSC_VER>1000
#pragma once
#endif // _MSC_VER>1000

#include "../../Protocol Buffers/Poker/AdlGameCommon.h"
#include "../util/PublicFunc.h"

using namespace adl;

#if defined(_Poker)

#define		INFOTEXT_COLOR1			RGB( 0,151,188 )
#define		INFOTEXT_COLOR2			RGB( 184, 164, 0 )
#define		INFOTEXT_COLOR3			RGB( 220, 50, 50 )
#define		INFOTEXT_COLOR4			RGB( 83,83,83 )

class CGameRule
{
public:
	CGameRule();
	virtual ~CGameRule();
public:
	static long GetBettingType(long lRoomType, long lChoiceMode, int nCardsDealt);
	static long GetBettingTurn(long lRoomType, long lChoiceMode, int nCardsDealt, long lBetCount);
	static bool IsErase(long lRoomType, long lChoiceMode);
	static bool IsSelect(long lRoomType, long lChoiceMode);
	static bool IsDealCard(long lRoomType, long lChoiceMode, int nCardsDealt);
	static bool IsHiddenCard(long lRoomType, long lChoiceMode, int nCardsDealt);
	static bool IsSameCard(long lRoomType, long lChoiceMode, int nCurCardsDealts);
	static bool IsOpenCard(long lRoomType, long lChoiceMode, int nCardsDealt, int nCurCardsDealts, bool bIsDeal);
	static int GetShuffleCount(long lRoomType, long lChoiceMode);
	static int GetMaxDealCount(long lRoomType, long lChoiceMode);
	static int GetMaxCardCount(long lRoomType, long lChoiceMode);
	static int GetHiddenCardCount(long lRoomType, long lChoiceMode);
	static int GetMaxDeckCount(long lRoomType, long lChoiceMode);
	static int GetMaxPlayerUserCount(long lRoomType, long lChoiceMode);
	static int GetMaxPlayerCardCount(long lRoomType, long lChoiceMode);
	static int GetRaiseCount(long lRoomType, long lChoiceMode, int nCardsDealt);
	static int Get_Velocity(long lRoomType, long lChoiceMode, long lTimerType, long lPlayCnt);
};

RankPrecedence PokerRulesToRankPrecedence(CPokerRules* pcPokerRules);
string PokerRulesToRankString(long lRankType);

#endif

#endif // !defined(AFX_GAMERULE_H__E63C4669_A46B_48B8_A2E7_9EF3B9D20A1A__INCLUDED_)