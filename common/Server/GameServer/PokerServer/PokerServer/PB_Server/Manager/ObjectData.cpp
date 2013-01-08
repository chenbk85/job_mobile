//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"

#include "ObjectData.h"

#include "../util/util.h"
#include "../util/FileDebug.h"

//#include "../../Protocol Buffers/Poker/Game_Poker.pb.h"
#include "../../protobuf/gameLogic.pb.h"

#include "../../Protocol Buffers/Poker/AdlGameCommon.h"

//using namespace Game_Poker;

//----------------------------------------------------------------------------------------------------
bool CObjectData::CreateObject(void)
{
	CObjectBase::CreateObject();
	return true;
}
//----------------------------------------------------------------------------------------------------
void CObjectData::DestroyObject(void)
{


}
//----------------------------------------------------------------------------------------------------
string CObjectData::FindUserName(long lUSN)
{
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++){
		UserInfo& ui=GetUI(i);
		if(ui.m_lUSN==lUSN)
			return ui.m_sNickName;
	}
	string sTemp(_T(""));
	return sTemp;
}
//----------------------------------------------------------------------------------------------------
bool CObjectData::IsUI(long lUSN)
{
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++){
		if(GetUI(i).m_lUSN==lUSN)
			return true;
	}
	return false;
}
//----------------------------------------------------------------------------------------------------
int CObjectData::USNToIdx(long lUSN)
{
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++){
		if(GetUI(i).m_lUSN==lUSN){
			return i;
		}
	}
	return -1;
}
//----------------------------------------------------------------------------------------------------
long CObjectData::IdxToUSN(int nIndex)
{
	if(nIndex<0) return 0;
	UserInfo & ui=GetUI(nIndex);
	if(ui.m_lUSN<0){
	}
	return ui.m_lUSN;
}
//----------------------------------------------------------------------------------------------------
int CObjectData::GetUICount()
{
	int nTemp=0;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++){
		if(GetUI(i).m_lUSN!=EMPTY_USER){
			nTemp++;
		}
	}

	return nTemp;
}
//----------------------------------------------------------------------------------------------------
int CObjectData::GetTotalUserCnt()
{
	int nTemp=GetUICount();
	nTemp=nTemp + m_vtObserveUSN.size();

	return nTemp;
}
//----------------------------------------------------------------------------------------------------
bool CObjectData::IsObserve(long lUSN)
{
	ForEachElmt(vector<long>, m_vtObserveUSN, ia, ja){
		if((*ia)==lUSN) return true;
	}
	return false;
}
//----------------------------------------------------------------------------------------------------
bool CObjectData::IsBlackList(long lUSN)
{
	if(m_cPurge.IsPurge(lUSN)) return true;
	return false;
}
//----------------------------------------------------------------------------------------------------
bool CObjectData::IsMoney(RCUser *pUser)
{
	//	return true; //test
#ifdef _DEBUG
	return true;
#endif

	if(pUser->m_llCMoney>0)
	{
		__int64 llUsedMoney_Min=__CONST_::Get_UsedMoney( m_cGameInfo.m_lChannel_idx, 0 );
		__int64 llUsedMoney_Max=__CONST_::Get_UsedMoney( m_cGameInfo.m_lChannel_idx, 1 );
		if((pUser->m_llCMoney >= llUsedMoney_Min) && (pUser->m_llCMoney <= llUsedMoney_Max))
		{
			__int64 llAnteMoney=m_cRCRoomData.m_option.m_llAnteMoney;
			if( pUser->m_llCMoney >= llAnteMoney )
			{
				return true;
			}
		}
	}
	return false;
}
//----------------------------------------------------------------------------------------------------
bool CObjectData::IsGrade(RCUser *pUser)
{
#ifdef _DEBUG
	return true;
#endif
	return __CONST_::Verify_Entry_UserGrade( pUser->m_lCLevel, m_cGameInfo.m_lChannel_idx );
}
//----------------------------------------------------------------------------------------------------
bool CObjectData::IsSpace()
{
	for(int i=0; i<m_cRCRoomData.m_option.m_lMaxUserCnt; ++i){
		if(GetUI(i).IsEmpty())
			return true;
	}
	return false;
}
//----------------------------------------------------------------------------------------------------
bool CObjectData::IsIP(RCUser* pUser)
{
	//근접아이피 특정아이디 빼도록 처리
	//string strID=pUser->GetUserID();
	//if( Is_NO_IPCheck_ID( strID ) ) return true;

	//if( m_lLocalSettingIpCheckSkip ) return true;
	//if(!pUser->GetMacAddress().compare("000F23693B44")){
	//	return true;
	//}
	//int nTemp=0;

	//for(int i=0; i<m_cRCRoomData.m_option.m_lMaxUserCnt; ++i){
	//	UserInfo& ui=GetUI(i);
	//	if(ui.IsEmpty()) continue;
	//	RCUser* pTempUser=FindUser(ui.m_lUSN);
	//	if(pUser->m_lUSN==pTempUser->m_lUSN) continue;
	//	if((pTempUser->GetClientIP() & 0x00ffffff)==(pUser->GetClientIP() & 0x00ffffff))
	//	{
	//		++nTemp;
	//	}
	//	if( pUser->m_lUSN==32282351 ) return true;
	//}
	//if(m_cRCRoomData.m_option.m_sPassword.empty())
	//{
	//	if(nTemp >= 2) return false;
	//}
	//else
	//{
	//	if(nTemp >= 1) return false;
	//}
	return true;
}
//----------------------------------------------------------------------------------------------------
bool CObjectData::IsGameLimit(RCUser * pUser)
{
	//if(!pUser->IsItem(ITEM_INFINITYSPEED))
	//{
	//	if(pUser->m_GameLimit.m_lTodayCnt >= 300) //판수제한300판
	//		return false;
	//}

	return true;
}
//----------------------------------------------------------------------------------------------------
bool CObjectData::IsMiniCashBox(long lUSN)
{
	//__int64 lCurrentTime=GetCurrentSystemTime();

	//RCUser* pUser=FindUser(lUSN);
	//if(pUser==NULL) return false;

	//if(pUser->m_MiniCashBox.GetEndTime() >= lCurrentTime)
	//	return true;

	return false;
}
//----------------------------------------------------------------------------------------------------
bool CObjectData::IsExtMoneyUser(long lUSN)
{
	RCUser* pUser=FindUser(lUSN);
	if(pUser==NULL) return false;
	return (pUser->m_llCMoney)>__CONST_::Get_EXT_Money( pUser->m_ItemList );
	//return (pUser->m_llCMoney + pUser->GetCashBox() )>__CONST_::Get_EXT_Money( pUser->m_ItemList );
}

void CObjectData::JoinItem(long lUSN)
{
	__int64 lCurrentTime=GetCurrentSystemTime();

	RCUser* pUser=FindUser(lUSN);
	if(NULL==pUser) return;
	//24시간 지나 최초 로그인시 초기화 : 여기는 최초로그인때 초기화구, 아래SetLxp는 플레이중에 24시간지나 초기화이다 두군데다 초기화해야함
	//if(true==pUser->IsLogonDiffDay(lCurrentTime)){
	//	pUser->m_lDisCnt=0;
	//}
}

void CObjectData::StartItem()
{
	__int64 lCurrentTime=GetCurrentSystemTime();
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN==-1) continue;

		RCUser * pUser=FindUser(ui.m_lUSN);
		if(pUser==NULL) continue;
		if(true==pUser->IsPlayDiffDay(lCurrentTime)){
			//ui.m_lDisCnt=0;
			pUser->m_lGDisCnt=0;
			pUser->m_nReserve01=0;
			pUser->m_nReserve02=0;
			ui.m_lJackpot=0;
		}
	}

	//StartPromotion(); // 프로모션 때문에 필요해짐
	//SendItemNotify(lCurrentTime);
}
//----------------------------------------------------------------------------------------------------
void CObjectData::EndItem()
{
	__int64 lCurrentTime=GetCurrentSystemTime();
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++){
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN==-1) continue;
		RCUser * pUser=FindUser(ui.m_lUSN);
		if(pUser==NULL) continue;
		if((lCurrentTime/1000000)>(m_cGameInfo.m_llGameData/1000000)){
			ui.m_lJackpot=0;
			pUser->m_nReserve01=0;
			pUser->m_nReserve02=0;
		}
	}
}
//----------------------------------------------------------------------------------------------------
int CObjectData::GetSpace()
{
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		if(GetUI(i).m_lUSN<0)
			return i;
	}

	return GetUISize();
}
//----------------------------------------------------------------------------------------------------
long CObjectData::GetFindBossUSN()
{
	long lUSN=m_cGameInfo.m_lBossUSN;
	int nTotal=GetUISize();

	int nTemp=0;
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN==-1) continue;

		if(lUSN==ui.m_lUSN && ui.m_lUserState==USERSTATE_PLAYING)
			return lUSN;
		else if(lUSN==ui.m_lUSN && ui.m_lUserState==USERSTATE_DIE)
		{
			nTemp=i;
			break;
		}
	}

	for(int i=1; i<nTotal; i++)
	{
		int nTempIndex=Seat[nTemp][i];
		UserInfo & ui=GetUI(nTempIndex);
		if(ui.m_lUSN!=EMPTY_USER && ui.m_lUserState==USERSTATE_PLAYING)
		{
			return ui.m_lUSN;
		}
	}

	return 0;
}
//----------------------------------------------------------------------------------------------------
int CObjectData::GetStateCount(long lUserState)
{
	int nTemp=0;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;

		if(ui.m_lUserState==lUserState)
			nTemp++;
	}
	return nTemp;
}
//----------------------------------------------------------------------------------------------------
int CObjectData::GetPlayerCount()
{
	int nTemp=0;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;

		if(ui.m_lUserState==USERSTATE_SELECTBEGIN || ui.m_lUserState==USERSTATE_SELECTEND ||ui.m_lUserState==USERSTATE_PLAYING || ui.m_lUserState == USERSTATE_SELECTCONTINUE)
			nTemp++;
	}

	return nTemp;
}
//----------------------------------------------------------------------------------------------------
int CObjectData::GetPlayingCount()
{
	int nTemp=0;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;

		if(ui.m_lUserState==USERSTATE_DIE || ui.m_lUserState==USERSTATE_SELECTBEGIN || ui.m_lUserState==USERSTATE_SELECTEND ||ui.m_lUserState==USERSTATE_PLAYING || ui.m_lUserState == USERSTATE_SELECTCONTINUE)
			nTemp++;
	}

	return nTemp;
}
//----------------------------------------------------------------------------------------------------
int	CObjectData::GetBetPlayerCount()
{
	int nTemp=0;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;
		if(ui.m_lUserState==USERSTATE_SELECTBEGIN || ui.m_lUserState==USERSTATE_SELECTEND ||ui.m_lUserState==USERSTATE_PLAYING)
		{
			Money & money=GetMoney( ui.m_nIndex );
			if(0<money.m_llCMoney)
			{
				nTemp++;
			}
		}
	}
	return nTemp;
}
//----------------------------------------------------------------------------------------------------
int CObjectData::Get49WaitingCount()
{
	int nTemp=0;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;
		if(ui.m_lUserState==USERSTATE_49WAITING)
			nTemp++;
	}
	return nTemp;
}
//----------------------------------------------------------------------------------------------------
int CObjectData::GetSelectContinueCount()
{
	int nTemp=0;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;
		if(ui.m_lUserState==USERSTATE_SELECTCONTINUE)
			nTemp++;
	}
	return nTemp;
}
//----------------------------------------------------------------------------------------------------
int CObjectData::GetMinPlayerCount()
{
	return 2;
	//if(m_cGameInfo.m_lChannel_idx==__CONST_::CHANNEL_FREE)
	//	return 2;
	//else
	//	return 3;
}
//----------------------------------------------------------------------------------------------------
void CObjectData::SetBetUSN()
{
	int nIdx=USNToIdx(m_cGameInfo.m_lBossUSN);
	int nTotal=GetUISize();
	if(nIdx==-1)
	{
		m_cGameInfo.m_lBossUSN=GetFindBossUSN();
		nIdx=USNToIdx(m_cGameInfo.m_lBossUSN);
		if(nIdx==-1)
		{
			string str="";//::format("[ASSERT] SetBetUSN : BossUSN=%d", m_cGameInfo.m_lBossUSN);
			FileDebug(str.c_str());
			return;
		}
	}

	for(int i=0; i<nTotal; i++)
	{
		int nTempIndex=Seat[nIdx][i];

		UserInfo & ui=GetUI(nTempIndex);
		if(ui.m_lUSN==-1) continue;

		m_cGameInfo.m_lBetUSN=ui.m_lUSN;
		break;
	}
}
//----------------------------------------------------------------------------------------------------
bool CObjectData::IsBettingMoney(Money & money, __int64 lMoney)
{
	if(money.m_llCMoney >= lMoney)
		return true;

	return false;
}
//----------------------------------------------------------------------------------------------------
__int64 CObjectData::SetBetttingMoney(long lUSN, long & lBetType, MsgSC_BettingAnsMsg & msg)
{
	int nIndex=USNToIdx( lUSN );
	if(0>nIndex) return 0;
	Money& money=GetMoney(nIndex);
	if(money.m_lBetState==BETSTATE_DIE) return 0; //이미 다이됬는데 또 다이되는것을 막기위해서
	__int64 llPoolMoney=0;   //전체 금액
	__int64 llRaiseMoney=0;  //자신이 올린 총금액
	__int64 llSideMoney=0;   //베팅에 모자른 금액
	__int64 llMaxMoney=GetMaxBettingMoney( lUSN );   //베팅이 가능한 유저 최대 금액 
	__int64 llAnteMoney=m_cRCRoomData.m_option.m_llGameAnteMoney;
	msg.Clear();
	if(lBetType==BETSTATE_DOUBLE || lBetType==BETSTATE_QUARTER || lBetType==BETSTATE_HALF )
	{
		if(money.m_llCMoney <= 0)
		{
			lBetType=BETSTATE_CALL;
		}
		if(money.m_llCMoney<money.m_llCallMoney)
		{
			lBetType=BETSTATE_CALL;
		}
	}
	else if( lBetType==BETSTATE_SAMEPOINT || lBetType==BETSTATE_TENPOINT || lBetType==BETSTATE_TWENTYPOINT 
		|| lBetType==BETSTATE_FIFTYPOINT || lBetType==BETSTATE_NINETYPOINT )
	{
		if(money.m_llCMoney <= 0)
		{
			lBetType=BETSTATE_REST;
		}
		if(money.m_llCMoney<money.m_llCallMoney)
		{
			lBetType=BETSTATE_REST;
		}
	}
	if(lBetType==BETSTATE_CALL)
	{
		m_cGameInfo.m_llPrevBetMoney=money.m_llCallMoney;
		if( m_cGameInfo.m_llMaxBetMoney>money.m_llCMoney )
		{
			msg.m_bMoneyLack=true;
		}
		llPoolMoney=money.m_llCallMoney;
	}
	else if(lBetType==BETSTATE_BBING)
	{
		if( m_cGameInfo.m_llMaxBetMoney>money.m_llCMoney )
		{
			msg.m_bMoneyLack=true;
		}
		//llPoolMoney=money.m_llCallMoney + llAnteMoney;
		//llPoolMoney=((money.m_llCallMoney + m_cGameInfo.m_llPoolMoney) * 1 / 10) + money.m_llCallMoney;
		llPoolMoney=money.m_llCallMoney + llAnteMoney;
	}
	else if(lBetType==BETSTATE_DOUBLE)
	{
		if( m_cGameInfo.m_llMaxBetMoney>money.m_llCMoney )
		{
			msg.m_bMoneyLack=true;
		}
		llPoolMoney=money.m_llCallMoney * 2;
	}
	else if(lBetType==BETSTATE_QUARTER)
	{
		if( m_cGameInfo.m_llMaxBetMoney>money.m_llCMoney )
		{
			msg.m_bMoneyLack=true;
		}
		//llPoolMoney=((money.m_llCallMoney + m_cGameInfo.m_llPoolMoney) / 4) + money.m_llCallMoney;
		//llPoolMoney=((money.m_llCallMoney + m_cGameInfo.m_llPoolMoney) * 2 / 10) + money.m_llCallMoney;
		llPoolMoney=((money.m_llCallMoney + m_cGameInfo.m_llPoolMoney) / 4) + money.m_llCallMoney;
	}
	else if(lBetType==BETSTATE_HALF)
	{
		if( m_cGameInfo.m_llMaxBetMoney>money.m_llCMoney )
		{
			msg.m_bMoneyLack=true;
		}
		//llPoolMoney=((money.m_llCallMoney + m_cGameInfo.m_llPoolMoney) / 2) + money.m_llCallMoney;
		llPoolMoney=((money.m_llCallMoney + m_cGameInfo.m_llPoolMoney) * 5 / 10) + money.m_llCallMoney;
	}
	else if(lBetType==BETSTATE_FULL)
	{
		if( m_cGameInfo.m_llMaxBetMoney>money.m_llCMoney )
		{
			msg.m_bMoneyLack=true;
		}
		llPoolMoney=(money.m_llCallMoney + m_cGameInfo.m_llPoolMoney) + money.m_llCallMoney;
		//llPoolMoney=((money.m_llCallMoney + m_cGameInfo.m_llPoolMoney) * 9 / 10) + money.m_llCallMoney;
	}
	else if(lBetType==BETSTATE_SAMEPOINT)
	{
		llPoolMoney=m_cGameInfo.m_llPrevBetMoney + money.m_llCallMoney;
	}
	else if(lBetType==BETSTATE_TENPOINT)
	{
		llPoolMoney=((money.m_llCallMoney + m_cGameInfo.m_llPoolMoney) * 1 / 10) + money.m_llCallMoney;
	}
	else if(lBetType==BETSTATE_TWENTYPOINT)
	{
		llPoolMoney=((money.m_llCallMoney + m_cGameInfo.m_llPoolMoney) * 2 / 10) + money.m_llCallMoney;
	}
	else if(lBetType==BETSTATE_FIFTYPOINT)
	{
		llPoolMoney=((money.m_llCallMoney + m_cGameInfo.m_llPoolMoney) * 5 / 10) + money.m_llCallMoney;
	}
	else if(lBetType==BETSTATE_NINETYPOINT)
	{
		llPoolMoney=((money.m_llCallMoney + m_cGameInfo.m_llPoolMoney) * 9 / 10) + money.m_llCallMoney;
	}
	else if(lBetType==BETSTATE_RECEIVE)
	{
		llPoolMoney=money.m_llCallMoney;
		m_cGameInfo.m_llPrevBetMoney=money.m_llCallMoney;
		if( m_cGameInfo.m_llMaxBetMoney>money.m_llCMoney )
		{
			msg.m_bMoneyLack=true;
		}
	}
	else if(lBetType==BETSTATE_LIVE)
	{
		llPoolMoney=m_cGameInfo.m_llPrevBetMoney;
		if( m_cGameInfo.m_llPrevBetMoney>money.m_llCMoney )
		{
			msg.m_bMoneyLack=true;
		}
	}
	else if(lBetType==BETSTATE_DIE)
	{
		llPoolMoney=0;
	}
	else if(lBetType==BETSTATE_REST)
	{
		llPoolMoney=0;
	}
	llRaiseMoney=llPoolMoney - money.m_llCallMoney;
	if((lBetType!=BETSTATE_RECEIVE)&&(lBetType!=BETSTATE_LIVE)){
		money.m_lBetCount++;
		m_cGameInfo.m_llMaxBetMoney=llRaiseMoney;
	}
	//if( m_cGameInfo.m_lBetCount<money.m_lBetCount ) m_cGameInfo.m_lBetCount=money.m_lBetCount;
	if( llPoolMoney>0 )
	{
		msg.m_bCallMoneyZero=( (money.m_llCallMoney==0) ? ( true ) : ( false ) );
		if(money.m_llCMoney >= llPoolMoney)
		{
			if(llMaxMoney >= llRaiseMoney)
			{
				msg.m_bBettingMoney=true;
				msg.m_llCallMoney=money.m_llCallMoney;
				msg.m_llRaiseMoney=llRaiseMoney;
				msg.m_llSideMoney=0;
				money.m_llCMoney-=llPoolMoney;
				money.m_llCallHabMoney+=llPoolMoney;
				m_cGameInfo.AddPoolMoney(llPoolMoney);
				SetCallMoney(nIndex, llRaiseMoney);
				m_cFileLog.DebugLog("[%d] Money==%I64d", nIndex, llPoolMoney);
			}
			else if(llMaxMoney<llRaiseMoney)
			{
				msg.m_bBettingMoney=true;
				msg.m_llCallMoney=money.m_llCallMoney;
				msg.m_llRaiseMoney=llMaxMoney;
				__int64 llMaxCallMoney=llMaxMoney + money.m_llCallMoney;
				if(money.m_llCMoney >= llMaxCallMoney)
				{
					msg.m_llSideMoney=0;
					money.m_llCMoney-=llMaxCallMoney;
					money.m_llCallHabMoney+=llMaxCallMoney;
					m_cGameInfo.AddPoolMoney(llMaxCallMoney);
					SetCallMoney(nIndex, llMaxMoney);
					m_cFileLog.DebugLog("[%d] Money==%I64d", nIndex, llMaxCallMoney);
				}
				else if(money.m_llCMoney<llMaxCallMoney)
				{
					llSideMoney=llMaxCallMoney - money.m_llCMoney;
					msg.m_bMoneyLack=true;
					msg.m_llSideMoney=llSideMoney;
					money.m_llSideMoney+=llSideMoney;
					money.m_llCallHabMoney+=money.m_llCMoney;
					m_cGameInfo.AddPoolMoney(money.m_llCMoney);
					SetCallMoney(nIndex, money.m_llCMoney);
					money.m_llCMoney=0;
					m_cFileLog.DebugLog("BETSTATE_RAISE 1 : money.m_llCMoney<0 BETSTATE : %d", lBetType);
				}
			}
		}
		else if(money.m_llCMoney<llPoolMoney)
		{
			llRaiseMoney=money.m_llCMoney - money.m_llCallMoney;
			if(llMaxMoney >= llRaiseMoney)
			{
				if(money.m_llCMoney >= money.m_llCallMoney)
				{
					msg.m_bBettingMoney=true;
					msg.m_llCallMoney=money.m_llCallMoney;
					msg.m_llRaiseMoney=llRaiseMoney;
					msg.m_llSideMoney=0;
					SetCallMoney(nIndex, llRaiseMoney);
				}
				else if(money.m_llCMoney<money.m_llCallMoney)
				{
					msg.m_bBettingMoney=false;
					msg.m_bMoneyLack=true;
					msg.m_llCallMoney=money.m_llCallMoney;
					msg.m_llRaiseMoney=0;
					llSideMoney=money.m_llCallMoney - money.m_llCMoney;
					msg.m_llSideMoney=llSideMoney;
					money.m_llSideMoney+=llSideMoney;
				}
				money.m_llCallHabMoney+=money.m_llCMoney;
				m_cGameInfo.AddPoolMoney(money.m_llCMoney);
				money.m_llCMoney=0;
				m_cFileLog.DebugLog("[%d] Money==%I64d", nIndex, money.m_llCMoney);
			}
			else if(llMaxMoney<llRaiseMoney)
			{
				if(money.m_llCMoney >= money.m_llCallMoney)
				{
					msg.m_bBettingMoney=true;
					msg.m_llCallMoney=money.m_llCallMoney;
					msg.m_llRaiseMoney=llMaxMoney;
					msg.m_llSideMoney=0;
					__int64 llMaxCallMoney=llMaxMoney + money.m_llCallMoney;
					if(money.m_llCMoney >= llMaxCallMoney)
					{
						msg.m_llSideMoney=0;
						money.m_llCMoney-=llMaxCallMoney;
						money.m_llCallHabMoney+=llMaxCallMoney;
						m_cGameInfo.AddPoolMoney(llMaxCallMoney);
						SetCallMoney(nIndex, llMaxMoney);
						m_cFileLog.DebugLog("[%d] Money==%I64d", nIndex, llMaxCallMoney);
					}
					else if(money.m_llCMoney<llMaxCallMoney)
					{
						msg.m_bMoneyLack=true;
						llSideMoney=llMaxCallMoney - money.m_llCMoney;
						msg.m_llSideMoney=llSideMoney;
						money.m_llCallHabMoney+=money.m_llCMoney;
						m_cGameInfo.AddPoolMoney(money.m_llCMoney);
						SetCallMoney(nIndex, money.m_llCMoney);
						money.m_llCMoney=0;
						m_cFileLog.DebugLog("BETSTATE_RAISE 1 : money.m_llCMoney<0 BETSTATE : %d", lBetType);
					}
				}
				else if(money.m_llCMoney<money.m_llCallMoney)
				{
					msg.m_bBettingMoney=false;
					msg.m_bMoneyLack=true;
					msg.m_llCallMoney=money.m_llCallMoney;
					msg.m_llRaiseMoney=0;
					llSideMoney=money.m_llCallMoney - money.m_llCMoney;
					msg.m_llSideMoney=llSideMoney;
					money.m_llSideMoney+=llSideMoney;
					money.m_llCallHabMoney+=money.m_llCMoney;
					m_cGameInfo.AddPoolMoney(money.m_llCMoney);
					money.m_llCMoney=0;
					m_cFileLog.DebugLog("[%d] Money==%I64d", nIndex, money.m_llCMoney);
				}
			}
		}
	}

	if( lBetType==BETSTATE_BBING || lBetType==BETSTATE_DOUBLE || lBetType==BETSTATE_QUARTER || lBetType==BETSTATE_HALF || lBetType==BETSTATE_FULL )
	{
		m_cGameInfo.m_llPrevBetMoney=msg.m_llCallMoney + msg.m_llRaiseMoney;
	}
	money.m_llCallMoney=0;
	msg.m_BetType=lBetType;
	if(BETSTATE_RECEIVE==lBetType)
	{
		money.m_lBetReceive=lBetType;
	}
	else
	{
		money.m_lBetState=lBetType;
		m_cGameInfo.SetPreBetType(lBetType);
	}
	m_cBetLog.SetBetLogReceive(m_cGameInfo.m_lBetUSN, lUSN, m_cGameInfo.m_lBetTurn, lBetType);
	return m_cGameInfo.m_llPrevBetMoney;
}
//----------------------------------------------------------------------------------------------------
__int64 CObjectData::GetMaxBettingMoney(long lUSN)
{
	__int64 lTmpMoney=0;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;
		if(ui.m_lUserState!=USERSTATE_PLAYING) continue;
		if(ui.m_lUSN==lUSN) continue;

		Money & money=GetMoney(i);
		if(lTmpMoney<money.m_llCMoney - money.m_llCallMoney)
			lTmpMoney=money.m_llCMoney - money.m_llCallMoney;
	}
	return lTmpMoney;
}
//----------------------------------------------------------------------------------------------------
__int64 CObjectData::GetMaxMoney()
{
	__int64 lTmpMoney=0;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++){
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;
		if(ui.m_lUserState!=USERSTATE_PLAYING) continue;
		Money & money=GetMoney(i);
		if(lTmpMoney<money.m_llCMoney)
			lTmpMoney=money.m_llCMoney;
	}
	return lTmpMoney;
}
//----------------------------------------------------------------------------------------------------
bool CObjectData::IsAllIn(long lUSN)
{
	int nIndex=USNToIdx(lUSN);
	if(nIndex<0) return false;
	UserInfo & ui=GetUI(nIndex);
	if(ui.m_lUSN != lUSN) return false;
	Money & money=GetMoney(nIndex);
	return ((0 == money.m_llCMoney) ? (true) : (false));
}
//----------------------------------------------------------------------------------------------------
bool CObjectData::IsExceptAllIn(long lUSN)
{
	int nTotal=GetUISize();
	bool bAllIn=false;
	for(int i=0; i<nTotal; i++){
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;
		if(ui.m_lUSN == lUSN) continue;
		Money & money=GetMoney(i);
		if(0 == money.m_llCMoney){
			bAllIn=true;
			break;
		}
	}
	return bAllIn;
}
//----------------------------------------------------------------------------------------------------
void CObjectData::SetCallMoney(int nIndex, __int64 lCallMoney)
{
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++){
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;
		Money & money=GetMoney(ui.m_nIndex);
		if((ui.m_nIndex!=nIndex) && ui.m_lUserState==USERSTATE_PLAYING){
			if((0==money.m_llCallMoney) && (0==lCallMoney)){
				Sleep(0);
			}
			money.m_llCallMoney+=lCallMoney;
		}
	}
}
//----------------------------------------------------------------------------------------------------
void CObjectData::MoneyDivision(vector<int> vtIdx, bool b49Replay)
{
	//m_cGameInfo.m_CDivisionMoney.Clear();
	Division_AddMoney();

	if(b49Replay) return;

	Division_SideMoney_FindUser();
	Division_DieUser_Money();

	__int64 lTakeMoney=Division_TakeMoney(vtIdx);
	int nWinSize=(int)vtIdx.size();
	__int64 llDealMoney=0;
	__int64 llJackPot=0;
	int nDealerTax=0;
	int nTotal=GetUISize();
	for( int i=0; i<nWinSize; i++ )
	{
		long lUSN=IdxToUSN(vtIdx[i]);
		if(0>lUSN) continue;
		int nIdx=vtIdx[i];
		if(0>nIdx )
		{
			m_cFileLog.DebugLog("[ASSERT] MoneyDivision : nIndex==-1");
			continue;
		}
		RCUser* pUser=FindUser(lUSN);
		if(NULL==pUser) continue;
		Money& money=GetMoney(nIdx);
		llDealMoney=0;
		llJackPot=0;
		nDealerTax=__CONST_::Get_Dealer_Tax_Percentage(pUser->m_ItemList, m_cGameInfo.m_lChannel_idx, m_cGameInfo.m_nRealDealer);		
		if(money.m_llTakeMoney>money.m_llCallHabMoney)
		{
			llDealMoney=(money.m_llTakeMoney - money.m_llCallHabMoney) * nDealerTax / 1000;
			//			llJackPot=((lTakeMoney - money.m_llCallHabMoney) / 1000) * 1; //딴금액에 0.1%를 잭팟금액으로 적립
			//			lTakeMoney-=llJackPot; //※한번더 뺀이유:0.1%는 땡큐보너스 머니로 소진될머니(이것은 실제로 나눠주는것이 아니구 소진되버린다.)
			//			nDealerTax+=1;	// db에 딜러비가 몇% 계산이 되는지 저장하기 위해서 필요함
			//			if(nIdx >= 0 && nIdx<MAX_PLAYER_COUNT)
			//				lTakeMoney-=llDealMoney;
			// 잭팟 적립금을 모아서 서버에 알려야 한다.
			//			llJackpot_Hab+=llJackPot;
		}
		money.m_llTakeMoney-=llDealMoney;
		if((money.m_llCMoney+money.m_llTakeMoney)>9999999999999999){
			money.m_llTakeMoney=9999999999999999-money.m_llCMoney;
		}
		money.m_llCMoney+=money.m_llTakeMoney;
		if(money.m_llCMoney>9999999999999999){
			money.m_llCMoney=9999999999999999;//1000000000000000000;
		}
		m_cFileLog.DebugLog("[%d] Win==%I64d=%I64d=%I64d=%I64d", nIdx, money.m_llCMoney, money.m_llTakeMoney, money.m_llCallHabMoney, money.m_llTakeMoney - money.m_llCallHabMoney);

		Division_TakeMoney_Save(lUSN, money.m_llTakeMoney, llDealMoney, llJackPot, nDealerTax);
	}
#ifdef _DEBUG
	nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;
		Money & money=GetMoney(i);
		m_cFileLog.DebugLog("[%d] Prev Rest Money==%I64d=%I64d", ui.m_lUSN, money.m_llCMoney, money.m_llTakeMoney);
	}
#endif
	Division_RestMoneyOver();

#ifdef _DEBUG
	nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;
		Money & money=GetMoney(i);
		m_cFileLog.DebugLog("[%d] Next Rest Money==%I64d=%I64d", ui.m_lUSN, money.m_llCMoney, money.m_llTakeMoney);
	}
#endif

	//for(i=0; i<(int)m_cGameInfo.m_CDivisionMoney.m_cvHabMoney.size(); i++)
	//{
	//	if(m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney!=0)
	//	{
	//		int nSize=m_cGameInfo.m_CDivisionMoney.GetStatePlayCnt(m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN);
	//		__int64 lTakeMoney=0;
	//		if(nSize!=0)
	//			lTakeMoney=m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney/nSize;
	//		else
	//			lTakeMoney=m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney;
	//		m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney=0;
	//		for(int nn=0; nn<(int)m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN.size(); nn++)
	//		{
	//			long lUSN=m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN[nn];
	//			if(m_cGameInfo.m_CDivisionMoney.IsStatePlay(lUSN)==false) continue;

	//			int nIdx=USNToIdx(lUSN);
	//			if(nIdx==-1) continue;

	//			Money & money=GetMoney(nIdx);
	//			money.m_llCMoney+=lTakeMoney;
	//			money.m_llTakeMoney+=lTakeMoney;

	//			ForEachElmt(vector<UserMoney>, m_cGameInfo.m_CDivisionMoney.m_vtUser, ia, ib)
	//			{
	//				if((*ia).m_lUSN==lUSN)
	//				{
	//					(*ia).m_llTakeMoney=money.m_llTakeMoney;
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}
	if(true==vtIdx.empty()) return;
	int nWinIndex=vtIdx[0];
	Money & Winmoney=GetMoney(nWinIndex);
	m_cGameInfo.ClearGiveMoney(nTotal);
	// 이부분에서 다른 유저에게 땡값을 뺏어 오는 처리
	//if(0==m_cRCRoomData.m_option.m_lBetType){
	//	float fMulti=0.0f;
	//	switch(m_cGameInfo.m_cResultOrder.FindCheck(nWinIndex))
	//	{
	//	case CResultFactor::RESULT_GHANGDDANG38:
	//		{
	//			fMulti=0.5f;
	//		}
	//		break;
	//	case CResultFactor::RESULT_GHANGDDANG138:
	//		{
	//			fMulti=0.3f;
	//		}
	//		break;
	//	case CResultFactor::RESULT_DDAND10:
	//		{
	//			fMulti=0.2f;
	//		}
	//		break;
	//	case CResultFactor::RESULT_DDAND19:
	//		{
	//			fMulti=0.1f;
	//		}
	//		break;
	//	}
	//	if(0.0f<fMulti)
	//	{
	//		for(int j=0; j<nTotal; j++)
	//		{
	//			UserInfo & ui=GetUI(j);
	//			if(0>ui.m_lUSN) continue;
	//			if(0>ui.m_nIndex) continue;
	//			if(ui.m_lUserState==USERSTATE_WAITING || ui.m_lUserState==USERSTATE_49WAITING || ui.m_lUserState==USERSTATE_DIE || ui.m_lUserState==USERSTATE_READY) continue;
	//			if(nWinIndex==ui.m_nIndex) continue;
	//			Money & money=GetMoney(ui.m_nIndex);
	//			__int64 lGiveMoney=(__int64)((money.m_llCallHabMoney + money.m_llJackpotMoney) * fMulti);
	//			if(money.m_llCMoney >= lGiveMoney)
	//			{
	//				money.m_llCMoney-=lGiveMoney;
	//				if(true==IsInRange(ui.m_nIndex, 0, m_cGameInfo.m_vllGiveMoney.size()-1)){
	//					m_cGameInfo.m_vllGiveMoney[ui.m_nIndex]=lGiveMoney;
	//				}
	//			}
	//			else
	//			{
	//				if(true==IsInRange(ui.m_nIndex, 0, m_cGameInfo.m_vllGiveMoney.size()-1)){
	//					m_cGameInfo.m_vllGiveMoney[ui.m_nIndex]=money.m_llCMoney;
	//				}
	//				money.m_llCMoney=0;
	//			}
	//		}
	//		nDealerTax=0;
	//		long lUSN=IdxToUSN(nWinIndex);
	//		RCUser* pUser=FindUser(lUSN);
	//		if(NULL!=pUser)
	//		{
	//			nDealerTax=__CONST_::Get_Dealer_Tax_Percentage(pUser->m_ItemList, m_cGameInfo.m_lChannel_idx, m_cGameInfo.m_nRealDealer);	
	//			if(m_cGameInfo.GetGiveMoneyHab()>0)
	//			{
	//				llDealMoney=m_cGameInfo.GetGiveMoneyHab() * nDealerTax / 1000;
	//			}
	//		}
	//		Winmoney.m_llCMoney+=(m_cGameInfo.GetGiveMoneyHab() - llDealMoney);
	//		Winmoney.m_llTakeMoney+=(m_cGameInfo.GetGiveMoneyHab() - llDealMoney);
	//		if(Winmoney.m_llCMoney>1000000000000000000)
	//			Winmoney.m_llCMoney=1000000000000000000;
	//		Division_AddTakeMoney_Save(lUSN, Winmoney.m_llTakeMoney, llDealMoney, llJackPot, nDealerTax);
	//	}
	//}
}


void CObjectData::Division_AddMoney()
{
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;
		if(ui.m_lUserState==USERSTATE_WAITING || ui.m_lUserState==USERSTATE_READY) continue;

		Money & money=GetMoney(i);
		if(ui.m_lUserState==USERSTATE_PLAYING || ui.m_lUserState==USERSTATE_SELECTBEGIN || ui.m_lUserState==USERSTATE_SELECTEND)
			m_cGameInfo.m_CDivisionMoney.ADDMoney(ui.m_lUSN, money.m_llCallHabMoney, USER_PLAY, ui.m_sNickName);
		else
			m_cGameInfo.m_CDivisionMoney.ADDMoney(ui.m_lUSN, money.m_llCallHabMoney, USER_DIE, ui.m_sNickName);
	}
}

void CObjectData::Division_SideMoney_FindUser()
{
	int nTotal=GetUISize();
	for(int i=0; i<(int)m_cGameInfo.m_CDivisionMoney.m_cvHabMoney.size(); i++)
	{
		__int64 llSmall=m_cGameInfo.m_CDivisionMoney.GetSmallMoney();  //최고로 작은 머니를 찾는다.
		if(llSmall!=0)
		{
			__int64 llTemp=0;
			ForEachElmt(vector<UserMoney>, m_cGameInfo.m_CDivisionMoney.m_vtUser, ia, ib)
			{
				
				//if((*ia).m_llMoney>0)
				if((*ia).m_llmoney()>0)
				{
					//(*ia).m_llMoney-=llSmall;	//자신이 베팅한금액에서 가장 작은 머니를 뺀다.
					(*ia).set_m_llmoney((*ia).m_llmoney() - llSmall);	//자신이 베팅한금액에서 가장 작은 머니를 뺀다.
					llTemp+=llSmall;			
					m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN.push_back((*ia).m_lusn());	//돈 많이 낸사람은 계속 들어갈것이다
				}
			}
			m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney=llTemp;   //작은 금액을 뺀 모든 유저들의 금액을 합친금액을 넣는다.
		}
	}
	m_cGameInfo.m_CDivisionMoney.m_llHabRematchMoney=0;
	//ForEachElmt(vector<UserMoney>, m_cGameInfo.m_CDivisionMoney.m_vtUser, ia, ib)
	//{
	//	if((*ia).m_llJackpotMoney>0)
	//	{
	//		m_cGameInfo.m_CDivisionMoney.m_llHabRematchMoney+=(*ia).m_llJackpotMoney;
	//	}
	//}
}

void CObjectData::Division_DieUser_Money()
{
	__int64 llBabo=0;
	int nTotal=GetUISize();
	for(int i=(int)m_cGameInfo.m_CDivisionMoney.m_cvHabMoney.size()-1; i>=0; i--)
	{
		if(llBabo!=0)
		{
			m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney+=llBabo;
			llBabo=0;
		}

		if(m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney!=0)
		{
			if(m_cGameInfo.m_CDivisionMoney.IsDieExit(m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN))
			{
				llBabo=m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney;
				m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney=0;
			}
		}
	}
}

__int64 CObjectData::Division_TakeMoney(int nIdx)
{
	UserInfo & ui=GetUI(nIdx);

	__int64 llTakeMoney=0;
	int nTotal=GetUISize();
	for(int j=0; j<(int)m_cGameInfo.m_CDivisionMoney.m_cvHabMoney.size(); j++)
	{
		//돈 많이 낸사람은 cnt가 클것이다. 돈낸 것에 다 속하므로
		int cnt=std::count(m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[j].vtUSN.begin(), m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[j].vtUSN.end(), ui.m_lUSN);
		if(cnt!=0 && ui.m_lUserState!=USERSTATE_WAITING && ui.m_lUserState!=USERSTATE_DIE)
		{
			llTakeMoney+=m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[j].llHabMoney;	//베팅돈을 많이 낸사람은 다가져가고 작게 낸사람은 자기꺼에 관련된것만 갖는다.
			m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[j].llHabMoney=0;
		}
	}
	llTakeMoney+=m_cGameInfo.m_CDivisionMoney.m_llHabRematchMoney;
	return llTakeMoney;
}


__int64	CObjectData::Division_TakeMoney(vector<int> vtIdx)
{
	int nWinSize=vtIdx.size();
	__int64 llTakeMoney=0;
	__int64 llRematchMoney=m_cGameInfo.m_CDivisionMoney.m_llHabRematchMoney / nWinSize;
	int nTotal=GetUISize();
	for(int i=0; i<(int)m_cGameInfo.m_CDivisionMoney.m_cvHabMoney.size(); i++)
	{
		int nTempCnt=0;
		for(int nn=0; nn<nWinSize; nn++)
		{
			int cnt=std::count(m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN.begin(), m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN.end(), IdxToUSN(vtIdx[nn]));
			if(cnt!=0)
				nTempCnt++;
		}
		if(nTempCnt!=0)
		{
			llTakeMoney=m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney/nTempCnt;
			m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney=0;
		}
		for(int nn=0; nn<nWinSize; ++nn)
		{
			int cnt=std::count(m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN.begin(), m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN.end(), IdxToUSN(vtIdx[nn]));
			if(cnt!=0)
			{
				Money& money=GetMoney(vtIdx[nn]);
				money.m_llTakeMoney +=llTakeMoney;
			}
		}
	}
	for(int j=0; j<nWinSize; ++j)
	{
		Money& money=GetMoney(vtIdx[j]);
		money.m_llTakeMoney +=llRematchMoney;
	}
	return llTakeMoney + llRematchMoney;
}


void CObjectData::Division_TakeMoney_Save(long lUSN, __int64 lTakeMoney, __int64 llDealMoney, __int64 llJackPot, int nDealerTax)
{
	ForEachElmt(vector<UserMoney>, m_cGameInfo.m_CDivisionMoney.m_vtUser, ia, ib)
	{
		/*
		if((*ia).m_lUSN==lUSN)
		{
			(*ia).m_llTakeMoney=lTakeMoney;
			(*ia).m_sDealerTax=::format("%d", nDealerTax);
			(*ia).m_llDealMoney=llDealMoney + (llJackPot);
			break;
		}
		*/

		if((*ia).m_lusn()==lUSN)
		{
			(*ia).set_m_lltakemoney(lTakeMoney);
			//(*ia).set_m_sdealertax(::format("%d", nDealerTax));

			//20111226 format함수 제거
			string tmpString;
			tmpString.push_back(nDealerTax);
			(*ia).set_m_sdealertax(tmpString);

			(*ia).set_m_lldealmoney(llDealMoney + (llJackPot));
			break;
		}
	}
}

void CObjectData::Division_AddTakeMoney_Save(long lUSN, __int64 lTakeMoney, __int64 llDealMoney, __int64 llJackPot, int nDealerTax)
{
	ForEachElmt(vector<UserMoney>, m_cGameInfo.m_CDivisionMoney.m_vtUser, ia, ib)
	{
		if((*ia).m_lusn()==lUSN)
		{
			(*ia).set_m_lltakemoney(lTakeMoney);
			
			//(*ia).set_m_sdealertax(::format("%d", nDealerTax));
			//20111226 format함수 제거
			string tmpString;
			tmpString.push_back(nDealerTax);
			(*ia).set_m_sdealertax(tmpString);

			(*ia).set_m_lldealmoney((*ia).m_lldealmoney() + llDealMoney + (llJackPot));
			break;
		}
	}
}

void CObjectData::Division_RestMoney()
{
	int i=0;
	for(i=0; i<(int)m_cGameInfo.m_CDivisionMoney.m_cvHabMoney.size(); i++)
	{
		if(m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney!=0)
		{
			int nSize=m_cGameInfo.m_CDivisionMoney.GetStatePlayCnt(m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN);
			__int64 lTakeMoney=0;
			if(nSize!=0)
				lTakeMoney=m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney/nSize;
			else
				lTakeMoney=m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney;
			m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney=0;
			for(int nn=0; nn<(int)m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN.size(); nn++)
			{
				long lUSN=m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN[nn];
				if(m_cGameInfo.m_CDivisionMoney.IsStatePlay(lUSN)==false) continue;

				int nIdx=USNToIdx(lUSN);
				if(nIdx==-1) continue;

				Money & money=GetMoney(nIdx);
				if(money.m_llCMoney+lTakeMoney>9999999999999999){
					lTakeMoney=9999999999999999-money.m_llCMoney;
				}
				money.m_llCMoney+=lTakeMoney;
				money.m_llTakeMoney+=lTakeMoney;
				if(money.m_llCMoney>9999999999999999){
					money.m_llCMoney=9999999999999999;//1000000000000000000;
				}

				ForEachElmt(vector<UserMoney>, m_cGameInfo.m_CDivisionMoney.m_vtUser, ia, ib)
				{
					if((*ia).m_lusn()==lUSN)
					{
						(*ia).set_m_lltakemoney(money.m_llTakeMoney);
						break;
					}
				}
			}
		}
	}
}

void CObjectData::Division_RestMoneyOver()
{
	int i=0;
	for(i=0; i<(int)m_cGameInfo.m_CDivisionMoney.m_cvHabMoney.size(); i++)
	{
		if(m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney!=0)
		{
			int nSize=m_cGameInfo.m_CDivisionMoney.GetStatePlayCnt(m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN);
			__int64 lTakeMoney=m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].llHabMoney;

			for(int nn=0; nn<(int)m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN.size(); nn++)
			{
				long lUSN=m_cGameInfo.m_CDivisionMoney.m_cvHabMoney[i].vtUSN[nn];
				if(m_cGameInfo.m_CDivisionMoney.IsStatePlay(lUSN)==false) continue;
				if(true==m_cGameInfo.m_cvtHyperInt_Level.FindBeginVector(lUSN)){
					int nIdx=USNToIdx(lUSN);
					if(nIdx==-1) continue;
					Money & money=GetMoney(nIdx);
					////////////////////////////////////////////////////////////
					if(money.m_llCMoney+lTakeMoney>9999999999999999){
					lTakeMoney=9999999999999999-money.m_llCMoney;
					}
					////////////////////////////////////////////////////////////
					money.m_llCMoney+=lTakeMoney;
					money.m_llTakeMoney+=lTakeMoney;
					////////////////////////////////////////////////////////////
					if(money.m_llCMoney>9999999999999999){
					money.m_llCMoney=9999999999999999;//1000000000000000000;
					}
					////////////////////////////////////////////////////////////

					ForEachElmt(vector<UserMoney>, m_cGameInfo.m_CDivisionMoney.m_vtUser, ia, ib)
					{
						if((*ia).m_lusn()==lUSN)
						{
							(*ia).set_m_lltakemoney(money.m_llTakeMoney);
							break;
						}
					}
				}
			}
		}
	}
}












