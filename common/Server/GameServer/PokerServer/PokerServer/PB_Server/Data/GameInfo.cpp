// GameInfo.cpp: implementation of the CGameInfo class.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GameInfo.h"


//----------------------------------------------------------------------------------------------------
void CGameInfo::ClearGameInfo(void)
{
	m_sGameMasterTime.clear();// 운영자 호출 시간
	m_sMakeRoomTime.clear();
	m_lCreateRoomOwner=0;
	
	m_lPreBetType=0;
	m_lWantBetType=0;
	m_lBetBtnType=0;
	m_nBetAddTime=0;
	m_lBetTurn=0;
	m_lOwnerUSN=0;
	m_lBossUSN=0;
	m_lBetUSN=0;
	m_lRoomId=0;
	m_dwStartTimer=0;
	m_llGameData=0;
	m_llPoolMoney=0;
	m_llPrevBetMoney=0;
	m_llMaxBetMoney=0;
	m_llJackpotMoney=0;
	m_llRematchAddMoney=0;
	m_lDealtCardCount=0;
	m_lCardsDealt=0;
	m_lBetCount=0;
	m_lCutCount=0;

	m_bGiveUp=false;
	m_bStart=false;
	m_b49Rematch=false;
	m_bJoinRematch=false;
	m_bBetUserMoney=false;
	m_nRuleIdx=0;
	m_nOldRuleIdx=0;
	m_nPlayCount=0;
	m_bStartReq=false;
	m_bStartPrev=false;
	m_sGameDate.clear();
	m_vJokbo.clear();
	m_vtWinIndex.clear();
	m_nRealDealer=0;
	m_bEnableChannelDeal=false;
}
//----------------------------------------------------------------------------------------------------
void CGameInfo::InitGameInfo(void)
{
	m_lPreBetType=BETSTATE_NONE;
	m_lWantBetType=0;
	m_lBetTurn=0;
	m_lBetBtnType=0;
	m_nBetAddTime=0;
	m_lBetUSN=0;
	m_dwStartTimer=0;
	m_llGameData=0; 


	m_lDealtCardCount=0;
	m_lCardsDealt=0;
	m_lBetCount=0;
	m_lCutCount	= 0;
	m_bGiveUp=false;
	m_bStart=false;
	ClearStartMoney();
	ClearGiveMoney(0);
	m_llPrevBetMoney=0;
	m_llMaxBetMoney=0;
	if(m_b49Rematch==false)
	{
		m_llJackpotMoney=0;
		m_llRematchAddMoney=0;
		m_bJoinRematch=false;
		m_llPoolMoney=0;
		m_CDivisionMoney.Clear();
	}
	if(m_b49Rematch)
		m_CDivisionMoney.SetRePlay();

}
//----------------------------------------------------------------------------------------------------
void CGameInfo::Init(int nUserSize, int nCardSize)
{
	ClearGameInfo();
	m_CDivisionMoney.Init( nUserSize);
	m_vllStartMoney.clear();
	for(int i=0; i<nUserSize; i++){
		m_vllStartMoney.push_back(0);
	}
	m_nBestAssa.clear();
	for(int i=0; i<nUserSize; i++){
		m_nBestAssa.push_back(0);
	}
	m_vlTimerDie.clear();
	for(int i=0; i<nUserSize; i++){
		m_vlTimerDie.push_back(0);
	}
	m_vResultOrder.clear();
	for(int i=0; i<nUserSize; i++){
		m_vResultOrder.push_back(0);
	}
	m_vllGiveMoney.clear();
	for(int i=0; i<nUserSize; i++){
		m_vllGiveMoney.push_back(0);
	}
}
//----------------------------------------------------------------------------------------------------
void CGameInfo::SortHyperInt(bool bAseOrDes)
{
	if(true==bAseOrDes){
		m_cvtHyperInt_Level.Sort_VectorAscend(GetHyperInt, SwapHyperInt);
	}
	else{
		m_cvtHyperInt_Level.Sort_VectorDescend(GetHyperInt, SwapHyperInt);
	}
}
//----------------------------------------------------------------------------------------------------
unsigned __int64 CGameInfo::GetHyperInt(CTPairVector<long, tHyperInt>* pVoid, int nArray)
{
	CTPairVector<long, tHyperInt>* pVoidVector=(CTPairVector<long, tHyperInt>*)(pVoid);
	if(NULL==pVoidVector) return 0;
	long lUSN=0;
	tHyperInt tHyperInt_Level;
	if(true==pVoidVector->GetVector(nArray, lUSN, tHyperInt_Level)){
		if(0<lUSN){
			return tHyperInt_Level.m_llHyperInt;
		}
		else{
			return 0;
		}
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------
void CGameInfo::SwapHyperInt(CTPairVector<long, tHyperInt>* pVoid, int nSwap1, int nSwap2)
{
	CTPairVector<long, tHyperInt>* pVoidVector=(CTPairVector<long, tHyperInt>*)(pVoid);
	if(NULL==pVoidVector) return;
	pVoidVector->SwapVector(nSwap1, nSwap2);
}
//----------------------------------------------------------------------------------------------------
//void CGameInfo::AddUser()
//{
//	m_nBestAssa.push_back(0);
//	m_vlTimerDie.push_back(0);
//	CIp cIp;
//	cIp.Clear();
//	string str;
//	str.clear();
//	m_vsReserved3.push_back(str);
//}
////----------------------------------------------------------------------------------------------------
//void CGameInfo::AddRemoveUser(int nSize)
//{
//	if((int)m_vlTimerDie.size()!=nSize){
//		if((int)m_vlTimerDie.size()>nSize){
//			m_vlTimerDie.erase(m_vlTimerDie.begin()+nSize, m_vlTimerDie.end());
//		}
//		else{
//			for(int i=(int)m_vlTimerDie.size(); i<nSize; i++){
//				m_vlTimerDie.push_back(0);
//			}
//		}	
//	}
//	if((int)m_nBestAssa.size()!=nSize){
//		if((int)m_nBestAssa.size()>nSize){
//			m_nBestAssa.erase(m_nBestAssa.begin()+nSize, m_nBestAssa.end());
//		}
//		else{
//			for(int i=(int)m_nBestAssa.size(); i<nSize; i++){
//				m_nBestAssa.push_back(0);
//			}
//		}	
//	}
//	if((int)m_vsReserved3.size()!=nSize){
//		if((int)m_vsReserved3.size()>nSize){
//			m_vsReserved3.erase(m_vsReserved3.begin()+nSize, m_vsReserved3.end());
//		}
//		else{
//			for(int i=(int)m_vsReserved3.size(); i<nSize; i++){
//				string str;
//				str.clear();
//				m_vsReserved3.push_back(str);
//			}
//		}	
//	}
//}
//----------------------------------------------------------------------------------------------------
//void CGameInfo::RemoveUser(int idx)
//{
//	if((0<=idx)&&((int)m_vlTimerDie.size()>idx)){
//		m_vlTimerDie.erase(&m_vlTimerDie[idx]);
//	}
//	if((0<=idx)&&((int)m_nBestAssa.size()>idx)){
//		m_nBestAssa.erase(&m_nBestAssa[idx]);
//	}
//	if((0<=idx)&&((int)m_vsReserved3.size()>idx)){
//		m_vsReserved3.erase(&m_vsReserved3[idx]);
//	}
//}
//----------------------------------------------------------------------------------------------------
void CGameInfo::ClearResultOrder(void)
{
	for(int i=0; i<(int)m_vResultOrder.size(); i++){
		m_vResultOrder[i]=0;
	}
}
//----------------------------------------------------------------------------------------------------
void CGameInfo::ClearStartMoney(void)
{
	for(int i=0; i<(int)m_vllStartMoney.size(); i++){
		m_vllStartMoney[i]=0;
	}
}
//----------------------------------------------------------------------------------------------------
void CGameInfo::ClearGiveMoney(int nPlayerCnt)
{
	//if(0!=nPlayerCnt){
	//	m_vllGiveMoney.clear();
	//	m_vllGiveMoney.resize(nPlayerCnt);
	//}
	for(int i=0; i<(int)m_vllGiveMoney.size(); i++){
		m_vllGiveMoney[i]=0;
	}
}
//----------------------------------------------------------------------------------------------------
void CGameInfo::Clear49Replay(void)
{
	m_b49Rematch=false;
	m_llJackpotMoney=0;
	m_llRematchAddMoney=0;
	m_bJoinRematch=false;
}
//----------------------------------------------------------------------------------------------------
void CGameInfo::SetPreBetType(long lBetType)
{
	if(m_lPreBetType==BETSTATE_NONE){
		if( (lBetType!=BETSTATE_CALL) && (lBetType!=BETSTATE_RECEIVE) && (lBetType!=BETSTATE_DIE) )
			m_lPreBetType=lBetType;
	}
	else{
		if( (lBetType!=BETSTATE_CHECK) && (lBetType !=BETSTATE_CALL) && (lBetType!=BETSTATE_DIE) && (lBetType!=BETSTATE_RECEIVE) )
			m_lPreBetType=lBetType;
	}
}
//----------------------------------------------------------------------------------------------------
__int64 CGameInfo::GetGiveMoneyHab()
{
	__int64 lHab=0;
	int nTotal=m_vllGiveMoney.size();
	for(int i=0; i<nTotal; i++){
		lHab+=m_vllGiveMoney[i];
	}
	return lHab;
}
//----------------------------------------------------------------------------------------------------
__int64 CGameInfo::GetDealMoney(long lUSN)
{
	ForEachElmt(vector<UserMoney>, m_CDivisionMoney.m_vtUser, ia, ib){
		if( lUSN==(*ia).m_lusn() ){
			if((*ia).m_lldealmoney()>0){
				return (*ia).m_lldealmoney();
			}
		}
		/*
		if( lUSN==(*ia).m_lUSN ){
			if((*ia).m_llDealMoney>0){
				return (*ia).m_llDealMoney;
			}
		}
		*/
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------
