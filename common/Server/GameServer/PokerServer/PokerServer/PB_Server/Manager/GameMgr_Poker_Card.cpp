//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"

#include "GameMgr_Poker.h"
#include "../Library/NeoRand.h"

#include "../../Protocol Buffers/Poker/AdlGameCommon.h"

#if defined(_Poker)

//----------------------------------------------------------------------------------------------------
string CGameMgr::GetCardString(int nIndex)
{
	char tmpString[256];
	string sTmp;
	Cards & card=GetCards(nIndex);
	for(int i=0; i<(int)card.m_vtCards.size(); i++)
	{
		sprintf(tmpString, "%02d", card.m_vtCards[i]);
		sTmp.append(tmpString);
		//sTmp+=::format("%02d", card.m_vtCards[i]);
		//		sTmp+=::format("%02d ", (card.m_vtCards[i])%10+1 );
	}
	return sTmp;
}
struct iotaGen {
	iotaGen(int start=0) : current(start){}
	int operator () (){return current++; }
	int current;
};
//----------------------------------------------------------------------------------------------------
void CGameMgr::ShuffleCards(int nCardTotalNum)
{
	std::vector<int> vtCard;
	vtCard.clear() ;
	std::generate_n(std::inserter(vtCard, vtCard.begin()), nCardTotalNum, iotaGen(0));

	DWORD dwSeed=0;
	dwSeed=time(0);//::timeGetTime();
	{
		GUID guid;
		::CoCreateGuid(&guid);

		DWORD* p=(DWORD*)&guid;
		for(int i=0; i<16; ++i)
		{
			DWORD dw=p[i];
			dwSeed+=dw;
		}
	}

	{
		int _j=dwSeed % 257;
		for(int _i=0; _i<_j; ++_i)
			rand();
	}

	int j=7 + dwSeed % 7;
	for(int i=0 ; i<j; ++i)
	{
		std::random_shuffle( vtCard.begin(), vtCard.end(), NeoRand() );
	}

	copy(vtCard.begin(), vtCard.end(), &m_Cards[0]);

//#if defined(_DEBUG) || defined(TEST_RELEASE)
//	if(false==m_cGameInfo.m_vJokbo.empty()){
//		int nTotal=(int)m_cGameInfo.m_vJokbo.size();
//		if(2==GetMaxDealCount())
//		{
//			int nUser=nTotal/2;
//			for(int j=0; j<nUser; j++)
//			{
//				for(int i=0; i<2; i++)
//				{
//					m_Cards[i+j*2]=m_cGameInfo.m_vJokbo[i+j*2];
//				}
//			}
//		}
//		else
//		{
//			int nUser=GetUICount();
//			if(m_cGameInfo.m_b49Rematch==true)
//			{
//				nUser=GetPlayerCount();
//			}
//			int nMaxCard=(int)GetMaxCardCount();
//			int nSetUser=nTotal/2;
//			for(int j=0; j<nSetUser; j++)
//			{
//				for(int i=0; i<2; i++)
//				{
//					m_Cards[i*nUser+j]=m_cGameInfo.m_vJokbo[i+j*2];
//				}
//			}
//		}
//	}
//#endif
}
//----------------------------------------------------------------------------------------------------
int	CGameMgr::OpenCard(int nIndex, int nSelect)
{
	Cards& Card=GetCards(nIndex);
	if(Card.m_vtCards.size() <= 0)
		return 0;
	if((0>nSelect)||(Card.m_vtCards.size()<=nSelect)) return 0;
	int a1=Card.m_vtCards[nSelect];
	VecCard::iterator it = Card.m_vtCards.begin();
	Card.m_vtCards.erase(it + nSelect);
	//Card.m_vtCards.erase(&Card.m_vtCards[nSelect]);
	Card.m_vtCards.push_back(a1);
}
//----------------------------------------------------------------------------------------------------
int	CGameMgr::SwapCard(int nIndex, int nSwap1, int nSwap2)
{
	Cards& Card=GetCards(nIndex);
	if(Card.m_vtCards.size() <= 0)
		return 0;
	if((0>nSwap1)||(Card.m_vtCards.size()<=nSwap1)) return 0;
	if((0>nSwap2)||(Card.m_vtCards.size()<=nSwap2)) return 0;
	if(nSwap1==nSwap2) return 0;
	int a1=Card.m_vtCards[nSwap1];
	int a2=Card.m_vtCards[nSwap2];
	Card.m_vtCards[nSwap1]=a2;
	Card.m_vtCards[nSwap2]=a1;
	return 1;
}
//----------------------------------------------------------------------------------------------------
int CGameMgr::SwapOpenCard(int nIndex, int nSelect)
{
	Cards& Card=GetCards(nIndex);

	if(Card.m_vtCards.size()<3)
		return -1;

	int a0=Card.m_vtCards[0];
	int a1=Card.m_vtCards[1];
	int a2=Card.m_vtCards[2];

	if(nSelect==1)
	{
		Card.m_vtCards[0]=a1;
		Card.m_vtCards[1]=a0;
	}
	else if(nSelect==2)
	{
		Card.m_vtCards[0]=a2;
		Card.m_vtCards[2]=a0;
	}

	return Card.m_vtCards[0];
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::CardCompNumber(long card1, long card2)
{
	// return -1 if card1 is lower than card2.
	// return 0 if card1 is the same as card2.
	// return 1 if card1 is higher than card2.
	if(card1==card2) return 0;
	// Check number
	if((card1 % 11)<(card2 % 11)) return -1;
	if((card1 % 11)>(card2 % 11)) return 1;
	// Check pattern
	if((card1 / 11)<(card2 / 11)) return -1;
	if((card1 / 11)>(card2 / 11)) return 1;
	//	ASSERT(0);

	return -2; // not reached code;
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::CardCompPattern(long card1, long card2)
{
	// return -1 if card1 is lower than card2.
	// return 0 if card1 is the same as card2.
	// return 1 if card1 is higher than card2.
	if(card1==card2) return 0;
	// Check pattern
	if((card1 / 11)>(card2 / 11)) return -1;
	if((card1 / 11)<(card2 / 11)) return 1;
	// Check number
	if((card1 % 11)<(card2 % 11)) return -1;
	if((card1 % 11)>(card2 % 11)) return 1;
	//	ASSERT(0);
	return -2; // not reached code;
}
//----------------------------------------------------------------------------------------------------
bool CGameMgr::SortCardTop(int nIndex, long* const result, bool bNumber, int nType)
{
	typedef long (CGameMgr::* LPCOMPFUNC) (long, long);
	LPCOMPFUNC pcompfunc=NULL;
	if(bNumber) 
		pcompfunc=&CGameMgr::CardCompNumber;
	else 
		pcompfunc=&CGameMgr::CardCompPattern;

	long lSortCount=2;
	long lSortedCount=0;
	long ltmpCards[2];

	Cards & Card=GetCards(nIndex);
	if(nType==1)
	{
		ltmpCards[0]=Card.m_vtCards[0];
		ltmpCards[1]=Card.m_vtCards[1];
	}
	else if(nType==2)
	{
		ltmpCards[0]=Card.m_vtCards[1];
		ltmpCards[1]=Card.m_vtCards[2];
	}
	else if(nType==3)
	{
		ltmpCards[0]=Card.m_vtCards[0];
		ltmpCards[1]=Card.m_vtCards[2];
	}

	while(lSortedCount<lSortCount) 
	{
		long lTopIndex=0;
		for(long lIndex=1; lIndex<lSortCount; lIndex++) 
		{
			if((this->*pcompfunc)(ltmpCards[lTopIndex], ltmpCards[lIndex])==-1) 
			{
				lTopIndex=lIndex;
			}
		}
		if(lTopIndex>-1) 
		{
			result[lSortedCount]=Card.m_vtCards[lTopIndex];
			ltmpCards[lTopIndex]=-1;
			lSortedCount++;
		}
	}
	return true;
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::CardDataSet(CardTable & tblCard, long lState)
{
	tblCard.Clear();
	tblCard.Init(m_cRCRoomData.m_option.m_lMaxPlayerCardCnt);

	int nTotal=GetUISize();
	switch(lState)
	{
	case GAMESTATE_INVALID: break;
	case GAMESTATE_READY: break;
	case GAMESTATE_START: break;
	case GAMESTATE_SELECT:
		{
			for(int i=0; i<nTotal; i++)
			{
				UserInfo & ui=GetUI(i);
				if(ui.m_lUSN<0) continue;

				Cards & Card=GetCards(i);

				if((ui.m_lUserState==USERSTATE_SELECTBEGIN)||(ui.m_lUserState==USERSTATE_SELECTEND))
				{
					for(int j=0; j<(int)Card.m_vtCards.size(); j++)
					{
						tblCard.GetCards(ui.m_nIndex).m_vtCards.push_back(-1);
					}
				}
				else if(ui.m_lUserState==USERSTATE_PLAYING)
				{
					for(int j=0; j<(int)Card.m_vtCards.size(); j++)
					{
						if(true==IsOpenCard(j+1, false))
							tblCard.GetCards(ui.m_nIndex).m_vtCards.push_back(Card.m_vtCards[j]);
						else
							tblCard.GetCards(ui.m_nIndex).m_vtCards.push_back(-1);
					}
				}
				else if(ui.m_lUserState==USERSTATE_DIE)
				{
					for(int j=0; j<(int)Card.m_vtCards.size(); j++)
					{
						tblCard.GetCards(ui.m_nIndex).m_vtCards.push_back(-1);
					}
				}
			}
		}
		break;
	case GAMESTATE_PLAY:
	case GAMESTATE_RESULT:
		{
			for(int i=0; i<nTotal; i++)
			{
				UserInfo & ui=GetUI(i);
				if(ui.m_lUSN<0) continue;
				Cards & Card=GetCards(i);
				if(ui.m_lUserState==USERSTATE_PLAYING)
				{
					for(int j=0; j<(int)Card.m_vtCards.size(); j++)
					{
						if(true==IsOpenCard(j+1, false))
							tblCard.GetCards(ui.m_nIndex).m_vtCards.push_back(Card.m_vtCards[j]);
						else
							tblCard.GetCards(ui.m_nIndex).m_vtCards.push_back(-1);
					}
				}
				else if(ui.m_lUserState==USERSTATE_DIE)
				{
					for(int j=0; j<(int)Card.m_vtCards.size(); j++)
					{
						tblCard.GetCards(ui.m_nIndex).m_vtCards.push_back(-1);
					}
				}
			}
		}
		break;
	case GAMESTATE_SAVE:
		{
			for(int i=0; i< nTotal; i++)
			{
				UserInfo & ui=GetUI(i);
				if(ui.m_lUSN<0) continue;

				Cards & Card=GetCards(ui.m_nIndex);

				if(ui.m_lUserState==USERSTATE_DIE)
				{
					for(int j=0; j<(int)Card.m_vtCards.size(); j++)
					{
						tblCard.GetCards(ui.m_nIndex).m_vtCards.push_back(-1);
					}
				}
				else
				{
					for(int j=0; j<(int)Card.m_vtCards.size(); j++)
					{
						if(m_cGameInfo.m_bGiveUp)
						{
							tblCard.GetCards(ui.m_nIndex).m_vtCards.push_back(-1);
						}
						else
						{
							tblCard.GetCards(ui.m_nIndex).m_vtCards.push_back(Card.m_vtCards[j]);		
						}
					}
				}
			}
		}
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::DealCard(int nSize, long lUserState, bool bSameCard)
{
	if(m_cGameInfo.m_lCardsDealt >= GetMaxCardCount()) return;
#ifdef _DEBUG
 	if(true==m_bJokbo){
		int nTotal=GetUISize();
		long lCards=0;
		for(int i=0; i<nTotal; i++)
		{
			UserInfo & ui=GetUI(i);
			if(( ui.m_lUSN!=EMPTY_USER ) && ( ui.m_lUserState==lUserState ) && ( ui.m_nIndex!=-1 ) )
			{
				Cards & Card=GetCards(ui.m_nIndex);
				for(int j=0; j<nSize; ++j)
				{
					if(false==bSameCard)
					{
						if((true==IsInRange(ui.m_nIndex, 0, 4))&&(true==m_ctCard[ui.m_nIndex].GetVector(m_cGameInfo.m_lCardsDealt+j, lCards))){
							Card.m_vtCards.push_back(lCards);							
						}
						else{
							if(true==m_ctAllCard.VectorBegin(lCards)){
								Card.m_vtCards.push_back(lCards);
								m_ctAllCard.DelBeginVector();
							}
							else{
								Card.m_vtCards.push_back(m_Cards[m_cGameInfo.m_lDealtCardCount]);
							}
						}
						m_cGameInfo.m_lDealtCardCount++;
						if(m_cGameInfo.m_lDealtCardCount >= GetShuffleCount()){
							m_cGameInfo.m_lDealtCardCount=0;
						}
					}
					else
					{
						if((m_cGameInfo.m_lDealtCardCount+j) >= GetShuffleCount()){
							m_cGameInfo.m_lDealtCardCount=0;
						}
						if((true==IsInRange(ui.m_nIndex, 0, 4))&&(true==m_ctCard[ui.m_nIndex].GetVector(m_cGameInfo.m_lCardsDealt+j, lCards))){
							m_ctCard[0].GetVector(m_cGameInfo.m_lCardsDealt, lCards);
							Card.m_vtCards.push_back(lCards);							
						}
						else{
							if(true==m_ctAllCard.VectorBegin(lCards)){
								Card.m_vtCards.push_back(lCards);
								m_ctAllCard.DelBeginVector();
							}
							else{
								Card.m_vtCards.push_back(m_Cards[m_cGameInfo.m_lDealtCardCount+j]);
							}
						}
					}
				}
			}
		}
		if(true==bSameCard)
		{
			m_cGameInfo.m_lDealtCardCount+=nSize;
			if(m_cGameInfo.m_lDealtCardCount >= GetShuffleCount()){
				m_cGameInfo.m_lDealtCardCount=0;
			}
		}
		m_cGameInfo.m_lCardsDealt+=nSize;
		return;
	}
#endif
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(( ui.m_lUSN!=EMPTY_USER ) && ( ui.m_lUserState==lUserState ) && ( ui.m_nIndex!=-1 ) )
		{
			Cards & Card=GetCards(ui.m_nIndex);
			for(int j=0; j<nSize; ++j)
			{
				if(false==bSameCard)
				{
					Card.m_vtCards.push_back(m_Cards[m_cGameInfo.m_lDealtCardCount]);
					m_cGameInfo.m_lDealtCardCount++;
					if(m_cGameInfo.m_lDealtCardCount >= GetShuffleCount()){
						m_cGameInfo.m_lDealtCardCount=0;
					}
				}
				else
				{
					if((m_cGameInfo.m_lDealtCardCount+j) >= GetShuffleCount()){
						m_cGameInfo.m_lDealtCardCount=0;
					}
					Card.m_vtCards.push_back(m_Cards[m_cGameInfo.m_lDealtCardCount+j]);
				}
			}
		}
	}
	if(true==bSameCard)
	{
		m_cGameInfo.m_lDealtCardCount+=nSize;
		if(m_cGameInfo.m_lDealtCardCount >= GetShuffleCount()){
			m_cGameInfo.m_lDealtCardCount=0;
		}
	}
	m_cGameInfo.m_lCardsDealt+=nSize;
}
//----------------------------------------------------------------------------------------------------


#endif