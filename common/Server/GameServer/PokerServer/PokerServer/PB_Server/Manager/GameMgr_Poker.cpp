//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"


#include "GameMgr_Poker.h"
#include "../util/NeoRand.h"
#include "../include/xtmpl.h"
//#include "../include/GBuf.h"



#if defined(_Poker)
//----------------------------------------------------------------------------------------------------
#ifdef _DEBUG
void CGameMgr::CheckJokbo()
{
	for(int i=0; i<5; i++){
		if(false==m_ctCard[i].IsEmpty()){
			m_bJokbo=true;
		}
	}
}
#endif
//----------------------------------------------------------------------------------------------------
bool CGameMgr::CreateObject(void)
{
	if(false==CObjectMgr::CreateObject()) return false;

	return true;
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::DestroyObject(void)
{
	CObjectMgr::DestroyObject();
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SetUserPos(RCUser* pUser, room_user_id_t nIndex, long lSoundType)
{
	CObjectMgr::SetUserPos(pUser, nIndex, lSoundType);
	if(nIndex<0) return;
	if(GetUI(nIndex).m_lUSN==EMPTY_USER) return;
	UserInfo& ui=GetUI(nIndex);
	//ui.m_lFourCardCnt=pUser->m_lFourCardCnt;
	//ui.m_lStraightFlushCnt=pUser->m_lStraightFlushCnt;
	//ui.m_lRoyalStraightFlushCnt=pUser->m_lRoyalStraightFlushCnt;

	char tmpString[256];
	sprintf(tmpString, "%d$%d$%I64d", m_cRCRoomData.m_option.m_lMaxUserCnt, m_cRCRoomData.GetUserCnt(), m_cRCRoomData.GetAvgMoney());
	string str(tmpString);
	//string str=::format("%d$%d$%I64d", m_cRCRoomData.m_option.m_lMaxUserCnt, m_cRCRoomData.GetUserCnt(), m_cRCRoomData.GetAvgMoney());
	//long lReturn=m_pGRCContainer->SendMessageToServer(MSGTYPE_ODBGW_UPDATE_RECOMMEND_ROOM, 0, str.c_str(), (long)str.size());
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::OnUserMsg(long lUSN, PayloadCS &pld)
{
	CObjectMgr::OnUserMsg(lUSN, pld);
	switch (pld.mTagID)
	{
		/*
	case PayloadCS::msgStart_Tag:
		OnRcvStart(lUSN, pld.un.m_msgStart);
		break;
	case PayloadCS::msgSelectedCardReq_Tag:
		OnRcvSelectedCardReq(lUSN, pld.un.m_msgSelectedCardReq);
		break;
	case PayloadCS::msgChoiceRemoveCard_Tag:
		OnRcvChoiceRemoveCard(lUSN, pld.un.m_msgChoiceRemoveCard);
		break;
	case PayloadCS::msgBettingReq_Tag:
		OnRcvBettingReq(lUSN, pld.un.m_msgBettingReq);
		break;
	case PayloadCS::msgContinue_Tag:
		OnRcvContinue(lUSN, pld.un.m_msgContinue);
		break;
	case PayloadCS::msgRuleSet_Tag:
		OnRcvRuleSet(lUSN, pld.un.m_msgRuleSet);
		break;
	case PayloadCS::msgJokboSet_Tag:
		OnRcvJokboSet(lUSN, pld.un.m_msgJokboSet);
		break;
	case PayloadCS::msgTestKeySetting_Tag:
		OnRcvTestKeySetting(lUSN, pld.un.m_msgTestKeySetting);
		break;
	case PayloadCS::msgAck_Tag:
		OnRcvAck(lUSN, pld.un.m_msgAck);
		break;
		*/
	default:
		break;
	}
	return ERROR_CODE_OK;
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::OnTimer(long lTimerIndex)
{
	CObjectMgr::OnTimer(lTimerIndex);
	int nTotal=m_ctPair_Timer.TotalVector();
	long lTimer=0;
	long lTimerValue=0;
	for(int i=0; i<nTotal; i++){
		if(false==m_ctPair_Timer.GetVector(i, lTimerValue, lTimer)) continue;
		if(lTimerIndex==lTimer){
			switch(lTimerValue)
			{
			case TIMER_START:
				{
					RemoveTimer(TIMER_START);
					SendStartAns();
				}
				return ERROR_CODE_OK;
			case TIMER_DEALOPEN:
				{
					RemoveTimer(TIMER_DEALOPEN);
					SendDealOpenCard();
				}
				return ERROR_CODE_OK;
			case TIMER_AUTOBET:
				{
					RemoveTimer(TIMER_AUTOBET);
					SendBettingReq();
				}
				return ERROR_CODE_OK;
			case TIMER_BETTING:
				{
					RemoveTimer(TIMER_BETTING);
					SendBettingReq();
				}
				return ERROR_CODE_OK;
			case TIMER_SPEEDGAME:
				{
					RemoveTimer(TIMER_SPEEDGAME);
					SendSpeedGame_DealCard();	//스피드게임일때 카드 나눠주기
				}
				return ERROR_CODE_OK;
			case TIMER_GAMEEND:
				{
					RemoveTimer(TIMER_GAMEEND);
					GameEnd(false);
				}
				return ERROR_CODE_OK;
			case TIMER_NEWGAME:
				{
					RemoveTimer(TIMER_NEWGAME);
					SendNewGame();
				}
				return ERROR_CODE_OK;
			case TIMER_CONTINUE:
				{
					RemoveTimer(TIMER_CONTINUE);
					SendContinue();
				}
				return ERROR_CODE_OK;
			case TIMER_ECHO_DEALS:
				{
					RemoveTimer(TIMER_ECHO_DEALS);
					GetUITable().SetAck(0);
					int nSetTime=Get_Velocity(TIMER_DEALOPEN, -1);
					SetTimer(TIMER_DEALOPEN, nSetTime, 0);
				}
				return ERROR_CODE_OK;
			case TIMER_ECHO_BET:
				{
					RemoveTimer(TIMER_ECHO_BET);
					GetUITable().SetAck(0);
					int nSetTime=Get_Velocity(TIMER_BETTING, -1);
					SetTimer(TIMER_BETTING, nSetTime, NULL);
				}
				return ERROR_CODE_OK;
			case TIMER_ECHO_DEAL:
				{
					RemoveTimer(TIMER_ECHO_DEAL);
					GetUITable().SetAck(0);
					SendBetting(BET_TYPE_CHECK);
				}
				return ERROR_CODE_OK;
			case TIMER_ECHO_FINISH:
				{
					RemoveTimer(TIMER_ECHO_FINISH);
					GetUITable().SetAck(0);
					int nSetTime=Get_Velocity(TIMER_CONTINUE, GetPlayerCount());
					SetTimer(TIMER_CONTINUE, nSetTime, NULL);
				}
				return ERROR_CODE_OK;
			default: break;
			}
		}
	}
	return ERROR_CODE_OK;
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::UserStateSetting()
{
	int nTotal=GetUISize();
	switch(m_cRCRoomData.m_lState)
	{
	case GAMESTATE_READY:
		{
			for(int i=0; i<nTotal; i++)
			{
				UserInfo& ui=GetUI(i);
				ui.m_lUserState=USERSTATE_READY;
			}
		}
		break;
	case GAMESTATE_START:
		{
			for(int i=0; i<nTotal; i++)
			{
				UserInfo & ui=GetUI(i);
				if(ui.m_lUSN<0) continue;
				if(ui.m_lUserState==USERSTATE_READY)
				{
					ui.m_lUserState=((true==IsSelect()) ?(USERSTATE_SELECTBEGIN) :(USERSTATE_PLAYING));
				}
			}
		}
		break;
	case GAMESTATE_SELECT:
		{
			for(int i=0; i<nTotal; i++)
			{
				UserInfo & ui=GetUI(i);
				if(ui.m_lUSN<0) continue;

				if(ui.m_lUserState==USERSTATE_SELECTBEGIN)
					ui.m_lUserState=USERSTATE_SELECTEND;
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

				if(ui.m_lUserState==USERSTATE_SELECTEND || ui.m_lUserState==USERSTATE_SELECTBEGIN)
					ui.m_lUserState=USERSTATE_PLAYING;
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::InitGame()
{
	m_cGameInfo.InitGameInfo();
	InitBetClear();
	m_cRCRoomData.m_tblCard.Clear();

	int nTotal=GetUISize();
	for(int i=0; i<nTotal; ++i)
	{
		UserInfo& ui=GetUI(i);
		Money& money=GetMoney(i);
		ui.m_lUserState=USERSTATE_READY;
		ui.m_lDieCardsDealt=0;

		money.m_llTakeMoney=0;
		money.m_llCallHabMoney=0;
		money.m_llSideMoney=0;
		money.m_lBetCount=0;
		money.m_lBetReceive=0;
		money.m_lBetState=0;
		money.m_llCallMoney=0;
		money.m_sMoneyMsg.erase();
	}
	ShuffleCards( GetShuffleCount() );
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::InitBetClear()
{
	m_cGameInfo.m_lPreBetType=BETSTATE_NONE;
	m_cGameInfo.m_llPrevBetMoney=0;
	m_cGameInfo.m_llMaxBetMoney=0;
	m_cGameInfo.m_lBetCount=0;
	//	m_cGameInfo.m_lWantBetType=0;
	int nTotal=GetMoneySize();
	for(int i=0; i<nTotal; ++i)
	{
		Money& money=GetMoney(i);
		money.BetClear();
	}
	m_cRCRoomData.m_tblBettingMsg.Clear();
}
//----------------------------------------------------------------------------------------------------
string CGameMgr::GetIP(long lIP)
{
	
	string sIP;
	/*
	in_addr in;
	in.S_un.S_addr=lIP;
	char* szTemp=::inet_ntoa(in);
	sIP=szTemp;
	*/
	return sIP;
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::BanCheck()
{
	// 폴리스 방제 신고 변경안 작업
	// 신고된 게임중이었던 방은 한판 끝나고 다 쫓아낸다.
	if( m_cPoliceNotify.GetPoliceNotify()==true ){
		AllUserDisconnect();
		return;
	}
	string sTempName;
	bool bObserve=false;
	int nTotal=GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;
		Money & money=GetMoney(ui.m_nIndex);
		money.m_sMoneyMsg=_T("");
		long lUSN=ui.m_lUSN;
		int nIndex=ui.m_nIndex;
		bObserve=false;
		if(((__CONST_::TWOUSER_NUM==m_cRCRoomData.m_option.m_lMaxUserCnt) && (ui.m_lUSN==m_cGameInfo.m_lOwnerUSN)) || (__CONST_::TWOUSER_NUM!=m_cRCRoomData.m_option.m_lMaxUserCnt))
		{
			if(money.m_llCMoney<m_cRCRoomData.m_option.m_llAnteMoney)
			{
				ObserveProcesses(lUSN, true, false);
				//if(__CONST_::TWOUSER_NUM==m_cRCRoomData.m_option.m_lMaxUserCnt){
				//	SendSystemMsg(SYSMSG_TWOOWNER_NOMONEY, _T(""), lUSN); // 관전으로만 빠짐					
				//}
				//else{
				//	SendSystemMsg(SYSMSG_MONEYDEFICIT, _T(""), lUSN); // 요거 받으면 클라이언트 나가버리네
				//}
				//if(lUSN==m_cGameInfo.m_lOwnerUSN)
				//	NextOwner();
				//SendSystemMsg(SYSMSG_EXIT,  _T(""), lUSN);
				//UserDisconnect(lUSN, false);
				bObserve=true;
			}
		}
		if((USERSTATE_SELECTCONTINUE==ui.m_lUserState) && (bObserve==false)){
			ObserveProcesses(lUSN, true, false);
			//if(lUSN==m_cGameInfo.m_lOwnerUSN)
			//	NextOwner();
			//SendSystemMsg(SYSMSG_EXIT,  _T(""), lUSN);
			//UserDisconnect(lUSN, false);
			bObserve=true;
		}
		if((money.m_llCMoney <= 0) && (bObserve==false))
		{
			ObserveProcesses(lUSN, true, false);
			SendSystemMsg(SYSMSG_MONEYDEFICIT, _T(""), lUSN); // 요거 받으면 클라이언트 나가버리네
			//if(lUSN==m_cGameInfo.m_lOwnerUSN)
			//	NextOwner();
			//SendSystemMsg(SYSMSG_EXIT,  _T(""), lUSN);
			//UserDisconnect(lUSN, false);
		}
	}
	for(int i=0; i<(int)m_cGameInfo.m_vlTimerDie.size(); i++)
	{
		if(m_cGameInfo.m_vlTimerDie[i] >= 3)		//3번이상 다이하면 그 방에서 빼버리고 관전자로 바꿈
		{
			m_cGameInfo.m_vlTimerDie[i]=0;
			UserInfo & ui=GetUI(i);
			if(ui.m_lUSN<0) continue;
			long lUSN=ui.m_lUSN;
			int nIndex=ui.m_nIndex;
			//string sMsg=FindUserName(lUSN);
			//sMsg=::format("%s님 관전", FindUserName(lUSN).c_str());		
			//SendSystemMsg(SYSMSG_OBSERVE, sMsg);
			ObserveProcesses(lUSN, true, false);
			string sMsg=FindUserName(lUSN);
			SendSystemMsg(SYSMSG_OBSERVE, sMsg);
			//if(lUSN==m_cGameInfo.m_lOwnerUSN)
			//	NextOwner();
			//SendSystemMsg(SYSMSG_EXIT,  _T(""), lUSN);
			//UserDisconnect(lUSN, false);
		}
	}
	ForEachElmt(vector<long>, m_cPurge.vtPurgeList, ia, ja)
	{
		long lUSN=(*ia);
		RCUser* pUser=FindUser(lUSN);
		if(pUser)
		{
			sTempName=pUser->m_sNickName;
			if(IsUI(lUSN))
			{
				int nIndex=USNToIdx(lUSN);
				if(nIndex!=-1)
				{
					ObserveProcesses(lUSN, true, false);
					//if(lUSN==m_cGameInfo.m_lOwnerUSN)
					//	NextOwner();
					//SendSystemMsg(SYSMSG_EXIT,  _T(""), lUSN);
					//UserDisconnect(lUSN, false);
					if(true==m_cPurge.IsEmpty()){
						goto ExitPurge;
					}
				}
			}
			//msg.m_sMsg=::format("%s님이 강제 퇴장되었습니다", sTempName.c_str());
			SendSystemMsg(SYSMSG_PURGE, sTempName);
			SendPurgeAns(lUSN, true);
			SendPurgeInfo();
			//if(pUser->m_nPurge_BadmanCnt >= 2)	// 강제적으로 나가라고 했는데 클라이언트 조작으로 안 나가는 나쁜넘이 있다
			//{
			//	m_pGRCContainer->DisconnectUser(lUSN);
			//}
			//pUser->m_nPurge_BadmanCnt++;
		}
	}
ExitPurge:
	if(m_cGameInfo.m_lChannel_idx!=__CONST_::CHANNEL_FREE)
	{
		for(int i=0; i<nTotal; ++i)
		{
			UserInfo& ui=GetUI(i);
			if(ui.m_lUSN<0) continue;
			Money& money=GetMoney(ui.m_nIndex);
			long lUSN=ui.m_lUSN;
			int nIndex=ui.m_nIndex;
			long lLevel=m_cGameInfo.m_lChannel_idx;
			__int64 llUsedMoney_Max=__CONST_::Get_UsedMoney( lLevel, 1 );
			if(money.m_llCMoney>(llUsedMoney_Max * 3))
			{
				ObserveProcesses(lUSN, true, false);
				SendSystemMsg(SYSMSG_MONEYOVER,  _T(""), lUSN);
				//if(lUSN==m_cGameInfo.m_lOwnerUSN)
				//	NextOwner();
				//SendSystemMsg(SYSMSG_EXIT,  _T(""), lUSN);
				//UserDisconnect(lUSN, false);
			}
		}
	}
	//나가기,관람예약
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN==-1) continue;
		long lUSN=ui.m_lUSN;
		if(ui.m_lExit==EXIT_OBSERVE)
		{
			ObserveProcesses(lUSN, true, false);
		}
		else if(ui.m_lExit==EXIT_EXIT)
		{
			if(lUSN==m_cGameInfo.m_lOwnerUSN)
				NextOwner();
			SendSystemMsg(SYSMSG_EXIT,  _T(""), lUSN);
			UserDisconnect(lUSN, false);
		}
	}
#ifdef _DEBUG
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN<0) continue;
		Money & money=GetMoney(i);
		m_cFileLog.DebugLog("[%d] BanCheck==%I64d", ui.m_lUSN, money.m_llCMoney);
	}
#endif
	int nErasenTotal=(int)m_vtEraseUSN.size();
	for(int i=0; i<nErasenTotal; i++){
		if(m_vtEraseUSN[i]==m_cGameInfo.m_lOwnerUSN)
			NextOwner();
		SendSystemMsg(SYSMSG_EXIT,  _T(""), m_vtEraseUSN[i]);
		UserDisconnect(m_vtEraseUSN[i], false, true, true);
	}

	m_vtEraseUSN.clear();
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::SetPurgeMoney(CPurgeMoney purgemoney)
{
	if(purgemoney.llPurgeMoney>0)  // 강퇴 머니를 돌려 줘야 된다.
	{
		ForEachElmt(vector<CPurgeMoney>, m_vtCPurgeMoney, ia, ib)
		{
			if((*ia).lUSN==purgemoney.lUSN)
			{
				(*ia).llPurgeMoney+=purgemoney.llPurgeMoney;
				if((*ia).llPurgeMoney >= 0)
					m_vtCPurgeMoney.erase(ia);

				int nIndex=USNToIdx(purgemoney.lUSN);
				if(nIndex==-1) return;

				Money & money=GetMoney(nIndex);
				money.m_llCMoney+=purgemoney.llPurgeMoney;

				break;
			}
		}
	}
	else
	{
		bool bTemp=false;
		ForEachElmt(vector<CPurgeMoney>, m_vtCPurgeMoney, ia, ib)
		{
			if((*ia).lUSN==purgemoney.lUSN)
			{
				(*ia).llPurgeMoney+=purgemoney.llPurgeMoney;
				bTemp=true;

				int nIndex=USNToIdx(purgemoney.lUSN);
				if(nIndex==-1) return;

				Money & money=GetMoney(nIndex);
				money.m_llCMoney+=purgemoney.llPurgeMoney;
				break;
			}
		}

		if(bTemp==false)
		{
			m_vtCPurgeMoney.push_back(purgemoney);
			int nIndex=USNToIdx(purgemoney.lUSN);
			if(nIndex==-1) return;

			Money & money=GetMoney(nIndex);
			money.m_llCMoney+=purgemoney.llPurgeMoney;
		}
	}

	MsgSC_SetPurgeMoney msg;
	msg.m_lUSN=purgemoney.lUSN;
	msg.m_money=GetMoney(USNToIdx(purgemoney.lUSN));
	PayloadSC pld(PayloadSC::msgSetPurgeMoney_Tag, msg);
	SendToAll(pld);
}
//----------------------------------------------------------------------------------------------------
__int64 CGameMgr::GetPurgeMoney(long lUSN, bool bErase)
{
	__int64 llTemp=0;
	ForEachElmt(vector<CPurgeMoney>, m_vtCPurgeMoney, ia, ib)
	{
		if((*ia).lUSN==lUSN)
		{
			llTemp=(*ia).llPurgeMoney ;
			if(bErase){
				m_vtCPurgeMoney.erase(ia);
				//ErasePurgeMoney(lUSN);
			}
			return llTemp;
		}
	}

	return llTemp;
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::ErasePurgeMoney(long lUSN)
{
	ForEachElmt(vector<CPurgeMoney>, m_vtCPurgeMoney, ia, ib)
	{
		if((*ia).lUSN==lUSN)
		{
			m_vtCPurgeMoney.erase(ia);
			return;
		}
	}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::DB_Save(bool bFlags)
{
	int nIndex=0;
	//NDL_SetUserInDataInfo InGameDataList;
	int nTotal=GetUISize();
//PKG_Ph_120.update_userdate             
//|I_USN|I|INT                  |%ld
//|I_SSN|I|INT                  |%ld
//|I_LASTLOGONDATE|I|STR        |%s
//|I_PLAYTIME|I|INT             |%ld
//|I_PM_ROOMID|I|INT            |%ld
//|IO_PM_MONEY|IO|BIG           |%I64i
//|O_PM_DAYPLAYCOUNT|O|INT      |0
//|O_PM_DAYPLAYTIME|O|INT       |0
//|O_PM_MONTHPLAYCOUNT|O|INT    |0
//|O_PM_MONTHPLAYTIME|O|INT     |0
//|IO_PG_WIN|IO|INT             |%ld
//|IO_PG_LOSE|IO|INT		      |%ld
//|IO_PG_DISCNT|IO|INT          |%ld
//|O_PG_TODAYPLAYCOUNT|O|INT    |0
//|O_PG_TODAYPLAYTIME|O|INT     |0
//|O_PG_TOTALPLAYCOUNT|O|INT    |0
//|O_PG_TOTALPLAYTIME|O|INT     |0
//|IO_PG_ALLINCNT|IO|INT        |%ld
//|IO_PG_ALLINOUT|IO|INT        |%ld
//|O_PG_TODAYWIN|O|INT          |0
//|O_PG_TODAYLOSE|O|INT         |0
//|O_PG_TODAYMONEY|O|BIG        |0
//|IO_PG_FCCNT|IO|INT           |%ld
//|IO_PG_SFCNT|IO|INT           |%ld
//|IO_PG_RSFCNT|IO|INT          |%ld
//|IO_PG_RESERVE01|IO|INT       |%ld
//|IO_PG_RESERVE02|IO|INT       |%ld
//|O_RESULT|R|INT	

/*
	GBuf bufOut;
	long lResult=0;
	if(bFlags==false){ // 재시작
		for(int i=0; i<nTotal; ++i){
			UserInfo & ui=GetUI(i);
			if(ui.m_lUSN<0) continue;
			if(ui.m_lUserState==USERSTATE_WAITING) continue;
			RCUser*	pUser=FindUser(ui.m_lUSN);
			if(pUser==NULL) continue;
			Money & money=GetMoney(ui.m_nIndex);
			string sPlayLastLogondate=::GetCurrentSystemTime_s();
			long lPlayTime=time(0) - m_cGameInfo.m_dwStartTimer;
			__int64 llCMoney=0;
			long lWin=0;
			long lLose=0;
			long lAllInCnt=0;
			long lAllInOut=0;
			long lFCCnt=0;
			long lSFCnt=0;
			long lRSFCnt=0;
			switch(money.m_lBetState){
			case RANK_FOUROFAKIND:
				{
					lFCCnt=1;
					pUser->AddFourCard();
				}
				break;
			case RANK_STRAIGHTFLUSH:
				{
					lSFCnt=1;
					pUser->AddStraightFlush();
				}
				break;
			case RANK_ROYALSTRAIGHTFLUSH:
				{
					lRSFCnt=1;
					pUser->AddRoyalStraightFlush();
				}
				break;
			}
			pUser->AddPlayCount();
			//string sQuery=::format("S|pkg_ph_120.update_userdata|%ld|%ld|%s|%ld|%ld|%I64d|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld",
			//	pUser->m_lUSN, g_lSSN, sPlayLastLogondate.c_str(), lPlayTime, m_cGameInfo.m_lRoomId, llCMoney, lWin, lLose, 0, lAllInCnt, lAllInOut, lFCCnt, lSFCnt, lRSFCnt, 0, 0);
			string sMoney=::format("%I64d", llCMoney);
			string sQuery=::format("S|pkg_ph_120.update_userdata|%ld|%ld|%s|%ld|%ld|%s|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld",
				pUser->m_lUSN, g_lSSN, sPlayLastLogondate.c_str(), lPlayTime, m_cGameInfo.m_lRoomId, sMoney.c_str(), lWin, lLose, 0, lAllInCnt, lAllInOut, lFCCnt, lSFCnt, lRSFCnt, pUser->m_nReserve01, pUser->m_nReserve02);
			long lReturn=0;
			bufOut.Clear();
			if( (lReturn=m_pGRCContainer->ExecuteQueryToDB(1, DBTYPE_PHONE, sQuery.c_str(), sQuery.size(), bufOut, &lResult))<0 )
			{ // 에러처리
				//DB_SETUSERDATA
				//lResult의 값을 보고 실패 원인을 찾음!
				return;
			}
			CParser cCParserReceive;
			int nGBufLength=bufOut->GetLength();
			if((0!=nGBufLength)&&(0<=lResult)){
				string strRecv;
				strRecv.assign((char*)bufOut->GetData(), nGBufLength);
				//strRecv.resize(nGBufLength+1);
				//memcpy(strRecv.data(), (char*)bufOut->GetData(), nGBufLength);
				cCParserReceive.MakeStringToTable(strRecv, "|");
				int nStart=0;
				long long llUCMoney=pUser->m_llCMoney;
				long long llCMoney=money.m_llCMoney;

				pUser->m_llCMoney=money.m_llCMoney=cCParserReceive.GetHyper(nStart+0);
				pUser->m_lMTodayPlayCount=cCParserReceive.GetLong(nStart+1);
				pUser->m_lMTodayPlayTime=cCParserReceive.GetLong(nStart+2);
				pUser->m_lMMonthPlayCount=cCParserReceive.GetLong(nStart+3);
				pUser->m_lMMonthPlayTime=cCParserReceive.GetLong(nStart+4);
				pUser->m_cWinLose.m_lWin=ui.m_cWinLose.m_lWin=cCParserReceive.GetLong(nStart+5);
				pUser->m_cWinLose.m_lLose=ui.m_cWinLose.m_lLose=cCParserReceive.GetLong(nStart+6);
				pUser->m_lGDisCnt=cCParserReceive.GetLong(nStart+7);
				pUser->m_lGTodayPlayCount=cCParserReceive.GetLong(nStart+8);
				pUser->m_lGTodayPlayTime=cCParserReceive.GetLong(nStart+9);
				pUser->m_lGTotalPlayCount=cCParserReceive.GetLong(nStart+10);
				pUser->m_lGTotalPlayTime=cCParserReceive.GetLong(nStart+11);
				pUser->m_lGAllinCnt=cCParserReceive.GetLong(nStart+12);
				pUser->m_lGAllinOut=cCParserReceive.GetLong(nStart+13);
				pUser->m_cWinLose_Today.m_lWin=ui.m_cWinLose_Today.m_lWin=cCParserReceive.GetLong(nStart+14);
				pUser->m_cWinLose_Today.m_lLose=ui.m_cWinLose_Today.m_lLose=cCParserReceive.GetLong(nStart+15);
				pUser->m_llGTodayMoney=cCParserReceive.GetHyper(nStart+16);
				pUser->m_lFourCardCnt=cCParserReceive.GetHyper(nStart+17);
				pUser->m_lStraightFlushCnt=cCParserReceive.GetHyper(nStart+18);
				pUser->m_lRoyalStraightFlushCnt=cCParserReceive.GetHyper(nStart+19);
				pUser->m_nReserve01=cCParserReceive.GetHyper(nStart+20);
				pUser->m_nReserve02=cCParserReceive.GetHyper(nStart+21);
				m_cFileLog.DebugLog("[%d] DB_Save Money==%I64d=%I64d=%I64d=%I64d", pUser->m_lUSN, llUCMoney, llCMoney, pUser->m_llCMoney, money.m_llCMoney);

			}
		}
	}
	else{
		int nPlayerCount=GetPlayingCount();
		for(int i=0; i<nTotal; ++i){
			UserInfo & ui=GetUI(i);
			if(ui.m_lUSN<0) continue;
			if(ui.m_lUserState==USERSTATE_WAITING) continue;
			RCUser*	pUser=FindUser(ui.m_lUSN);
			if(pUser==NULL) continue;
			Money & money=GetMoney(ui.m_nIndex);
			string sPlayLastLogondate=::GetCurrentSystemTime_s();
			long lPlayTime=time(0) - m_cGameInfo.m_dwStartTimer;
			__int64 llCMoney=0;
			long lWin=0;
			long lLose=0;
			long lAllInCnt=0;
			long lAllInOut=0;
			long lFCCnt=0;
			long lSFCnt=0;
			long lRSFCnt=0;
			if(m_cGameInfo.m_lChannel_idx!=__CONST_::CHANNEL_FREE){
				if((3<=nPlayerCount)&&(money.m_llCallHabMoney>m_cRCRoomData.m_option.m_llGameAnteMoney)){
					pUser->m_nReserve01++;
				}
			}
			if(IsWin(ui.m_nIndex))
			{
				llCMoney=(money.m_llTakeMoney - money.m_llCallHabMoney) + GetPurgeMoney(ui.m_lUSN, true);
				lWin=1;
				if(true == IsExceptAllIn(ui.m_lUSN)){
					lAllInOut=1;
				}
				ui.m_cWinLose_Room.m_lWin++;
			}
			else
			{
				if(true==IsInRange(ui.m_nIndex, 0, m_cGameInfo.m_vllGiveMoney.size()-1)){
					llCMoney=(money.m_llTakeMoney - money.m_llCallHabMoney) +(-m_cGameInfo.m_vllGiveMoney[ui.m_nIndex]) + GetPurgeMoney(ui.m_lUSN, true);
				}
				else{
					llCMoney=(money.m_llTakeMoney - money.m_llCallHabMoney) + GetPurgeMoney(ui.m_lUSN, true);
				}
				lLose=1;
				if(true == IsAllIn(ui.m_lUSN)){
					lAllInCnt=1;
				}
				ui.m_cWinLose_Room.m_lLose++;
			}
			switch(money.m_lBetState){
			case RANK_FOUROFAKIND:
				{
					lFCCnt=1;
					pUser->AddFourCard();
				}
				break;
			case RANK_STRAIGHTFLUSH:
				{
					lSFCnt=1;
					pUser->AddStraightFlush();
				}
				break;
			case RANK_ROYALSTRAIGHTFLUSH:
				{
					lRSFCnt=1;
					pUser->AddRoyalStraightFlush();
				}
				break;
			}
			pUser->AddPlayCount();
			//string sQuery=::format("S|pkg_ph_120.update_userdata|%ld|%ld|%s|%ld|%ld|%I64d|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld",
			//	pUser->m_lUSN, g_lSSN, sPlayLastLogondate.c_str(), lPlayTime, m_cGameInfo.m_lRoomId, llCMoney, lWin, lLose, 0, lAllInCnt, lAllInOut, lFCCnt, lSFCnt, lRSFCnt, 0, 0);
			string sMoney=::format("%I64d", llCMoney);
			string sQuery=::format("S|pkg_ph_120.update_userdata|%ld|%ld|%s|%ld|%ld|%s|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld",
				pUser->m_lUSN, g_lSSN, sPlayLastLogondate.c_str(), lPlayTime, m_cGameInfo.m_lRoomId, sMoney.c_str(), lWin, lLose, 0, lAllInCnt, lAllInOut, lFCCnt, lSFCnt, lRSFCnt, pUser->m_nReserve01, pUser->m_nReserve02);
			long lReturn=0;
			bufOut.Clear();
			if( (lReturn=m_pGRCContainer->ExecuteQueryToDB(1, DBTYPE_PHONE, sQuery.c_str(), sQuery.size(), bufOut, &lResult))<0 )
			{ // 에러처리
				//DB_SETUSERDATA
				//lResult의 값을 보고 실패 원인을 찾음!
				return;
			}
			CParser cCParserReceive;
			int nGBufLength=bufOut->GetLength();
			if((0!=nGBufLength)&&(0<=lResult)){
				string strRecv;
				strRecv.assign((char*)bufOut->GetData(), nGBufLength);
				//strRecv.resize(nGBufLength+1);
				//memcpy(strRecv.data(), (char*)bufOut->GetData(), nGBufLength);
				cCParserReceive.MakeStringToTable(strRecv, "|");
				long long llUCMoney=pUser->m_llCMoney;
				long long llCMoney=money.m_llCMoney;
				int nStart=0;
				pUser->m_llCMoney=money.m_llCMoney=cCParserReceive.GetHyper(nStart+0);
				pUser->m_lMTodayPlayCount=cCParserReceive.GetLong(nStart+1);
				pUser->m_lMTodayPlayTime=cCParserReceive.GetLong(nStart+2);
				pUser->m_lMMonthPlayCount=cCParserReceive.GetLong(nStart+3);
				pUser->m_lMMonthPlayTime=cCParserReceive.GetLong(nStart+4);
				pUser->m_cWinLose.m_lWin=ui.m_cWinLose.m_lWin=cCParserReceive.GetLong(nStart+5);
				pUser->m_cWinLose.m_lLose=ui.m_cWinLose.m_lLose=cCParserReceive.GetLong(nStart+6);
				pUser->m_lGDisCnt=cCParserReceive.GetLong(nStart+7);
				pUser->m_lGTodayPlayCount=cCParserReceive.GetLong(nStart+8);
				pUser->m_lGTodayPlayTime=cCParserReceive.GetLong(nStart+9);
				pUser->m_lGTotalPlayCount=cCParserReceive.GetLong(nStart+10);
				pUser->m_lGTotalPlayTime=cCParserReceive.GetLong(nStart+11);
				pUser->m_lGAllinCnt=cCParserReceive.GetLong(nStart+12);
				pUser->m_lGAllinOut=cCParserReceive.GetLong(nStart+13);
				pUser->m_cWinLose_Today.m_lWin=ui.m_cWinLose_Today.m_lWin=cCParserReceive.GetLong(nStart+14);
				pUser->m_cWinLose_Today.m_lLose=ui.m_cWinLose_Today.m_lLose=cCParserReceive.GetLong(nStart+15);
				pUser->m_llGTodayMoney=cCParserReceive.GetHyper(nStart+16);
				pUser->m_lFourCardCnt=cCParserReceive.GetHyper(nStart+17);
				pUser->m_lStraightFlushCnt=cCParserReceive.GetHyper(nStart+18);
				pUser->m_lRoyalStraightFlushCnt=cCParserReceive.GetHyper(nStart+19);
				pUser->m_nReserve01=cCParserReceive.GetHyper(nStart+20);
				pUser->m_nReserve02=cCParserReceive.GetHyper(nStart+21);

				m_cFileLog.DebugLog("[%d] DB_Save Money==%I64d=%I64d=%I64d=%I64d, %d", pUser->m_lUSN, llUCMoney, llCMoney, pUser->m_llCMoney, money.m_llCMoney, pUser->m_nReserve01);

			}
		}
	}
	*/
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::DB_DisconnectSave(const TempRCUser& tempRC, bool bObserve)
{
	/*
	int nIndex=tempRC.nIndex;
	int nTodayCnt=tempRC.nTodayCnt;
	if(nIndex==-1) return;
	UserInfo& ui=GetUI(nIndex);
	if(ui.m_lUSN==-1) return;
	GBuf bufOut;
	long lResult=0;
	switch(m_cRCRoomData.m_lState)
	{
	case GAMESTATE_READY:
		break;
	case GAMESTATE_START:
	case GAMESTATE_SELECT:
	case GAMESTATE_PLAY:
	case GAMESTATE_RESULT:
	//case GAMESTATE_SAVE:
		{
			Money & money=GetMoney(nIndex);
			m_cGameInfo.m_CDivisionMoney.ADDMoney(ui.m_lUSN, money.m_llCallHabMoney, USER_EXIT, ui.m_sNickName);
			string sPlayLastLogondate=::GetCurrentSystemTime_s();
			long lPlayTime=time(0)-m_cGameInfo.m_dwStartTimer;
			__int64 llCMoney=0;
			long lWin=0;
			long lLose=0;
			long lAllInCnt=0;
			long lAllInOut=0;
			long lFCCnt=0;
			long lSFCnt=0;
			long lRSFCnt=0;
			if(bObserve){
				lPlayTime=0;
				//string sQuery=::format("S|pkg_ph_120.update_userdata|%ld|%ld|%s|%ld|%ld|%I64d|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld",
				//	ui.m_lUSN, g_lSSN, sPlayLastLogondate.c_str(), lPlayTime, m_cGameInfo.m_lRoomId, llCMoney, lWin, lLose, 0, lAllInCnt, lAllInOut, lFCCnt, lSFCnt, lRSFCnt, 0, 0);
				string sMoney=::format("%I64d", llCMoney);
				string sQuery=::format("S|pkg_ph_120.update_userdata|%ld|%ld|%s|%ld|%ld|%s|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld",
					ui.m_lUSN, g_lSSN, sPlayLastLogondate.c_str(), lPlayTime, m_cGameInfo.m_lRoomId, sMoney.c_str(), lWin, lLose, 0, lAllInCnt, lAllInOut, lFCCnt, lSFCnt, lRSFCnt, tempRC.nReserve01, tempRC.nReserve02);
				long lReturn=0;
				if( (lReturn=m_pGRCContainer->ExecuteQueryToDB(1, DBTYPE_PHONE, sQuery.c_str(), sQuery.size(), bufOut, &lResult))<0 )
				{ // 에러처리
					//DB_SETUSERDATA
					//lResult의 값을 보고 실패 원인을 찾음!
					return;
				}
			}
			else{
				llCMoney=-money.m_llCallHabMoney;
				lLose=1;
				if(0==money.m_llCMoney){
					lAllInCnt=1;
				}
				//string sQuery=::format("S|pkg_ph_120.update_userdata|%ld|%ld|%s|%ld|%ld|%I64d|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld",
				//	ui.m_lUSN, g_lSSN, sPlayLastLogondate.c_str(), lPlayTime, m_cGameInfo.m_lRoomId, llCMoney, lWin, lLose, 1, lAllInCnt, lAllInOut, lFCCnt, lSFCnt, lRSFCnt, 0, 0);
				string sMoney=::format("%I64d", llCMoney);
				string sQuery=::format("S|pkg_ph_120.update_userdata|%ld|%ld|%s|%ld|%ld|%s|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld|%ld",
					ui.m_lUSN, g_lSSN, sPlayLastLogondate.c_str(), lPlayTime, m_cGameInfo.m_lRoomId, sMoney.c_str(), lWin, lLose, 1, lAllInCnt, lAllInOut, lFCCnt, lSFCnt, lRSFCnt, tempRC.nReserve01, tempRC.nReserve02);
				long lReturn=0;
				bufOut.Clear();
				if( (lReturn=m_pGRCContainer->ExecuteQueryToDB(1, DBTYPE_PHONE, sQuery.c_str(), sQuery.size(), bufOut, &lResult))<0 )
				{ // 에러처리
					//DB_SETUSERDATA
					//lResult의 값을 보고 실패 원인을 찾음!
					return;
				}
			}
		}
		break;
	case GAMESTATE_SAVE:
		break;
	default:
		break;
	}

	m_cBetLog.DelBetLog(ui.m_lUSN);
	//철이가 강퇴 DB처리 추가
	Proc_ExecuteQueryToDB();
	//철이가 추가
	*/
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::Proc_ExecuteQueryToDB()
{ // ExecuteQueryToDB
//	CREATE OR REPLACE PROCEDURE sp_updatemoney(
//        lusn in number,	: User Serial Number
//        lmsn in number,	: Money Serial Number
//        lssn in number,	: Service Serial Number
//        ldmoney in number,: 변동 머니(증감)
//        ltype in number,	: Type - 1:강퇴비용, 2:?...
//        lremark in number,: Count
//        lcmoney out number,: 변경 후 머니
//        re out number	 :(1:성공, -1:실패)
//	)
	//int nTotal=GetUISize();
	//for(int i=0; i<nTotal; i++)
	//{
	//	UserInfo & ui=GetUI(i);
	//	if(ui.m_lUSN==-1) continue;

	//	__int64 llPurgeMoney=GetPurgeMoney(ui.m_lUSN, true);
	//	if(llPurgeMoney==0) continue;

	//	{
	//		CComVariant vtOutData;
	//		long lResult;
	//		long lUSN=ui.m_lUSN;
	//		long lMSN=1; // 고스톱류(1), 포커류(2), 훌라류(3), 캐쥬얼류(4), 섯다류(5)  머니고유넘버
	//		__int64 lMoney=llPurgeMoney; // 변동머니(증감);
	//		long lType=1; // 강퇴Type1
	//		long lCnt=1; // 강퇴 회수
	//		string sQuery=::format("S|PKG_MONEY_SERVICE.UPDATE_MONEY|%ld|%ld|%ld|%I64i|%ld|%ld", lUSN, lMSN, g_lSSN, lMoney, lType, lCnt);
	//	 
	//		//if( m_pGRCContainer->ExecuteQueryToDB(DB_QUERY, g_lSSN, sQuery.c_str(), sQuery.size(), &vtOutData, &lResult)<0 )
	//		//{ // 에러처리
	//		//	// lResult의 값을 보고 실패 원인을 찾음!
	//		//	return;
	//		//}

	//		GBuf bufOut;
	//		::VCopy(bufOut,vtOutData);
	//		DWORD dwSize=bufOut.GetLength();

	//		NDL_ResultStr result;
	//		if(BDecode_NDL_ResultStr(bufOut.GetData(), &dwSize, &result)==0)
	//		{ // 에러처리
	//			return;
	//		}

	//		// 만약 lQueryType을 DB_QUERY_LIST로 지정했다면 BDecode_NDL_ResultList()를 써서 디코딩합니다. 결과는 list<string>에 들어가게 되구요.
	//		// 만약 lQueryType을 DB_QUERY로 지정했다면 BDecode_NDL_ResultStr()를 써서 디코딩합니다. 결과값은 '|' 문자로 나뉘어진 string 하나에 들어가게 됩니다.

	//		__int64 lCMoney=::_atoi64(result.m_sResult.c_str()); // 머니만 리턴하기로 했음!
	//		
	//		Money & money=GetMoney(i);
	//		money.m_llCMoney=lCMoney;

	//		RCUser * pUser=FindUser(ui.m_lUSN);
	//		if(pUser!=NULL)
	//			pUser->SetCMoney(lCMoney);

	//	}
	//}
}
//----------------------------------------------------------------------------------------------------
bool CGameMgr::JackpotCheck(int nWinIndex, long long &llJackpotMoney)
{
	UserInfo & ui=GetUI(nWinIndex);
	if(ui.m_lUSN==-1) return false;
	if(ui.m_lUserState==USERSTATE_WAITING || ui.m_lUserState==USERSTATE_DIE || ui.m_lUserState==USERSTATE_READY) return false;
	Money & money=GetMoney(ui.m_nIndex);
	llJackpotMoney=0;
	bool bReturn=false;
	switch(m_cGameInfo.m_lChannel_idx){
	case __CONST_::CHANNEL_FREE:
		{
			llJackpotMoney=0;
		}
		break;
	case __CONST_::CHANNEL_1:
		{
			switch(money.m_lBetState){
			case RANK_FOUROFAKIND: llJackpotMoney=10*UK; break;
			case RANK_STRAIGHTFLUSH: llJackpotMoney=20*UK; break;
			case RANK_ROYALSTRAIGHTFLUSH: llJackpotMoney=100*UK; break;
			}
		}
		break;
	case __CONST_::CHANNEL_2:
		{
			switch(money.m_lBetState){
			case RANK_FOUROFAKIND: llJackpotMoney=50*UK; break;
			case RANK_STRAIGHTFLUSH: llJackpotMoney=100*UK; break;
			case RANK_ROYALSTRAIGHTFLUSH: llJackpotMoney=400*UK; break;
			}
		}
		break;
	case __CONST_::CHANNEL_3:
		{
			switch(money.m_lBetState){
			case RANK_FOUROFAKIND: llJackpotMoney=200*UK; break;
			case RANK_STRAIGHTFLUSH: llJackpotMoney=500*UK; break;
			case RANK_ROYALSTRAIGHTFLUSH: llJackpotMoney=2000*UK; break;
			}
		}
		break;
	case __CONST_::CHANNEL_4:
		{
			llJackpotMoney=0;
		}
		break;
	//case __CONST_::CHANNEL_5:
	//	{
	//		llJackpotMoney=0;
	//	}
	//	break;
	//case __CONST_::CHANNEL_6:
	//	{
	//		llJackpotMoney=0;
	//	}
	//	break;
	}
	if(0<llJackpotMoney){
		bReturn=DB_Query_Jackpot(ui.m_lUSN, llJackpotMoney);
	}
	return bReturn;
	//int nTotal=GetUISize();
	//long long llJackpotMoney=0;
	//for(int i=0; i<nTotal; i++)
	//{
	//	UserInfo & ui=GetUI(i);
	//	if(ui.m_lUSN==-1) continue;
	//	if(ui.m_lUserState==USERSTATE_WAITING || ui.m_lUserState==USERSTATE_DIE || ui.m_lUserState==USERSTATE_READY) continue;
	//	Money & money=GetMoney(ui.m_nIndex);
	//	llJackpotMoney=0;
	//	switch(m_cGameInfo.m_lChannel_idx){
	//	case __CONST_::CHANNEL_FREE: break;
	//	case __CONST_::CHANNEL_1:
	//		{
	//			switch(money.m_lBetState){
	//			case RANK_FOUROFAKIND: llJackpotMoney=5*UK; break;
	//			case RANK_STRAIGHTFLUSH: llJackpotMoney=15*UK; break;
	//			case RANK_ROYALSTRAIGHTFLUSH: llJackpotMoney=20*UK; break;
	//			}
	//		}
	//		break;
	//	case __CONST_::CHANNEL_2:
	//		{
	//			switch(money.m_lBetState){
	//			case RANK_FOUROFAKIND: llJackpotMoney=20*UK; break;
	//			case RANK_STRAIGHTFLUSH: llJackpotMoney=30*UK; break;
	//			case RANK_ROYALSTRAIGHTFLUSH: llJackpotMoney=50*UK; break;
	//			}
	//		}
	//		break;
	//	case __CONST_::CHANNEL_3:
	//		{
	//			switch(money.m_lBetState){
	//			case RANK_FOUROFAKIND: llJackpotMoney=50*UK; break;
	//			case RANK_STRAIGHTFLUSH: llJackpotMoney=150*UK; break;
	//			case RANK_ROYALSTRAIGHTFLUSH: llJackpotMoney=200*UK; break;
	//			}
	//		}
	//		break;
	//	case __CONST_::CHANNEL_4:
	//		{
	//			switch(money.m_lBetState){
	//			case RANK_FOUROFAKIND: llJackpotMoney=200*UK; break;
	//			case RANK_STRAIGHTFLUSH: llJackpotMoney=300*UK; break;
	//			case RANK_ROYALSTRAIGHTFLUSH: llJackpotMoney=500*UK; break;
	//			}
	//		}
	//		break;
	//	case __CONST_::CHANNEL_5:
	//		{
	//			switch(money.m_lBetState){
	//			case RANK_FOUROFAKIND: llJackpotMoney=500*UK; break;
	//			case RANK_STRAIGHTFLUSH: llJackpotMoney=1500*UK; break;
	//			case RANK_ROYALSTRAIGHTFLUSH: llJackpotMoney=2000*UK; break;
	//			}
	//		}
	//		break;
	//	case __CONST_::CHANNEL_6:
	//		{
	//			switch(money.m_lBetState){
	//			case RANK_FOUROFAKIND: llJackpotMoney=2000*UK; break;
	//			case RANK_STRAIGHTFLUSH: llJackpotMoney=3000*UK; break;
	//			case RANK_ROYALSTRAIGHTFLUSH: llJackpotMoney=5000*UK; break;
	//			}
	//		}
	//		break;
	//	}
	//	if(0<llJackpotMoney){
	//		DB_Query_Jackpot(ui.m_lUSN, llJackpotMoney);
	//	}
	//}
}
//----------------------------------------------------------------------------------------------------
void CGameMgr::ExtMoneyCheck()
{
	//bool bExistExtMoneyUser=false;
	//int nTotal=GetUISize();
	//for(int i=0; i<nTotal; i++)
	//{
	//	UserInfo & ui=GetUI(i);
	//	if(ui.m_lUSN==-1) continue;
	//	if(ui.m_lUserState!=USERSTATE_PLAYING) continue;

	//	if(IsExtMoneyUser(ui.m_lUSN))
	//	{
	//		bExistExtMoneyUser=true;
	//		//m_pGRCContainer->SaveExtMoney(ui.m_lUSN, 1);
	//	}
	//}

	//__int64 lCurrentTime=GetCurrentSystemTime();

	//if(bExistExtMoneyUser)
	//{
	//	DWORD dwSize2=0;
	//	//m_pGRCContainer->GetUserData(-1, NULL, &dwSize2);

	//	DWORD dwSize=dwSize2;
	//	char* pBuf2=new char[dwSize2 + 1];

	//	//m_pGRCContainer->GetUserData(-1, pBuf2, &dwSize2);

	//	NDL_SetUserOutDataInfo OutDataInfoList;
	//	OutDataInfoList.m_lstOutData.clear();
	//	BDecode_NDL_SetUserOutDataInfo((LPCBUF)pBuf2, &dwSize, &OutDataInfoList);
	//	delete[] pBuf2;


	//	ForEachElmt(list<DB_SetUserOutData>, OutDataInfoList.m_lstOutData, ia, ib)
	//	{
	//		long lUSN=(*ia).m_lUSN;
	//		int nIndex=USNToIdx(lUSN);
	//		UserInfo & ui=GetUI(nIndex);
	//		if(ui.m_lUserState!=USERSTATE_PLAYING) continue;

	//		Money & money=GetMoney(nIndex);
	//		money.m_llCMoney=(*ia).m_lCMoney;

	//		RCUser * pUser=FindUser(lUSN);
	//		if(pUser==NULL) continue;

	//		pUser->SetCMoney((*ia).m_lCMoney);
	//		pUser->SetExtMoney((*ia).m_lReservedLL1);
	//		pUser->SetExtDate(_atoi64((*ia).m_sReservedString2.c_str()));

	//		bool bExtType=false;
	//		if(pUser->m_llExtDate >= lCurrentTime)
	//			bExtType=true;

	//		SendExtMoneyNotify(lUSN, pUser, bExtType);
	//	}
	//}
	//else
	//{
	//	for(i=0; i<nTotal; i++)
	//	{
	//		UserInfo & ui=GetUI(i);
	//		if(ui.m_lUSN==-1) continue;
	//		if(ui.m_lUserState!=USERSTATE_PLAYING) continue;

	//		RCUser * pUser=FindUser(ui.m_lUSN);
	//		if(pUser==NULL) continue;

	//		bool bExtType=false;
	//		if(pUser->m_llExtDate >= lCurrentTime)
	//			bExtType=true;

	//		SendExtMoneyNotify(ui.m_lUSN, pUser, bExtType);
	//	}
	//}
}
//----------------------------------------------------------------------------------------------------
string CGameMgr::RoomTitle()
{
	std::replace(m_cRCRoomData.m_option.m_sRoomTitle.begin(), m_cRCRoomData.m_option.m_sRoomTitle.end(), '\'', ' ');
	std::replace(m_cRCRoomData.m_option.m_sRoomTitle.begin(), m_cRCRoomData.m_option.m_sRoomTitle.end(), '\\', ' ');
	std::replace(m_cRCRoomData.m_option.m_sRoomTitle.begin(), m_cRCRoomData.m_option.m_sRoomTitle.end(), '|', ' ');

	if(m_cRCRoomData.m_option.m_sRoomTitle=="")
		return "0";
	else
		return m_cRCRoomData.m_option.m_sRoomTitle.substr(0,50);
}
/*
CREATE TABLE "SAYPHONE"."PH_LT_120" 
(    "PARTKEY_DAY" VARCHAR2(2) DEFAULT to_char(sysdate,'dd'), 
"USN" NUMBER(10,0), 
"STARTDATE" VARCHAR2(14), 
"ENDDATE" VARCHAR2(14), 
"PLAYTIME" NUMBER(5,0), 
"ISWINNER" NUMBER(1,0), 
"CLEVEL" NUMBER(2,0), 
"DELTA_MONEY" NUMBER(20,0), 
"CUR_MONEY" NUMBER(20,0), 
"GAMELEVEL" NUMBER(2,0), 
"DEALMONEY" NUMBER(20,0), 
"ROOMID" NUMBER(10,0), 
"PLAYCOUNT" NUMBER(5,0), 
"UDID" VARCHAR2(50), 
"NICKNAME" VARCHAR2(50), 
"USERSTATE" NUMBER(1,0), 
"JOCKBO" VARCHAR2(20), 
"DIEPOINT" VARCHAR2(3), 
"CARDIDX" VARCHAR2(20), 
"DDANGMONEY" NUMBER(20,0) DEFAULT 0, 
"BETMONEY" NUMBER(20,0), 
"JACKPOTMONEY" NUMBER(20,0)
) PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
/**/
//----------------------------------------------------------------------------------------------------
void CGameMgr::DB_User_Log(long lUSN, string sUUID)
{
	/*
	string sChannel=format("%d", m_cRCRoomData.m_option.m_lChannelID);
	DWORD channel=atoi(sChannel.substr(sChannel.length() - 3, 3).c_str());
	DWORD server=m_cRCRoomData.m_option.m_lCategory;

	int nIdx=USNToIdx(lUSN);
	if(nIdx==-1) return;
	UserInfo & ui=GetUI(nIdx);

	Money & money=GetMoney(nIdx);
	Cards & Card=GetCards(ui.m_nIndex);

	string pdate="01";
	string startdate=m_cGameInfo.m_sGameDate;
	if(false==m_cGameInfo.m_sGameDate.empty()){
		pdate=m_cGameInfo.m_sGameDate.substr(6,2);
	}
	else{
		startdate=GetCurrentSystemTime_s();
	}
	string enddate=GetCurrentSystemTime_s();
	int	roomid=m_cGameInfo.m_lRoomId;
	long lPlayTime=time(0) - m_cGameInfo.m_dwStartTimer;
	long lWin=((IsWin(ui.m_nIndex))?(1):(0));
	string sJokbo=PokerRulesToRankString(money.m_lBetState);
	string sDiePoint=::format("%d", ui.m_lDieCardsDealt);
	string sCard=Card.CardStr();
	string sLog1; 
	string sLog2;

	sLog1=::format("Q|INSERT INTO PH_LT_%03d(PARTKEY_DAY,USN,STARTDATE,ENDDATE,PLAYTIME,ISWINNER,CLEVEL,DELTA_MONEY,CUR_MONEY,GAMELEVEL,DEALMONEY,ROOMID,PLAYCOUNT,UDID,NICKNAME,USERSTATE,JOCKBO,DIEPOINT,CARDIDX,DDANGMONEY,BETMONEY,JACKPOTMONEY) values", g_lSSN);
	sLog2=::format(" ('%s',%d,'%s','%s',%d,%d,%d,%I64i,%I64i,%d,%I64i,%d,%d,'%s','%s',%d,'%s','%s','%s',%I64i,%I64i,%I64i)",
		pdate.c_str(),lUSN,startdate.c_str(),enddate.c_str(), lPlayTime, lWin,ui.m_lCLevel,money.m_llTakeMoney,money.m_llCMoney,
		server,money.m_llCallHabMoney,roomid,1,sUUID.c_str(), "-",ui.m_lUserState,sJokbo.c_str(),
		sDiePoint.c_str(),sCard.c_str(),money.m_llJackpotMoney,m_cRCRoomData.m_option.m_llGameAnteMoney,money.m_llJackpotMoney);

	GBuf bufOut;

	long lResult=0;
	long lReturn=0;
	string sQuery=::format("%s%s",sLog1.c_str(),sLog2.c_str());

	if( (lReturn=m_pGRCContainer->ExecuteQueryToDB(1, DBTYPE_PHONE, sQuery.c_str(), sQuery.size(), bufOut, &lResult))<0 )
	{ // 에러처리
		//DB_SETUSERDATA
		//lResult의 값을 보고 실패 원인을 찾음!
		m_cFileLog.DebugLog("UserLog Failed!!!!");
		return;
	}
	*/
}
/*
CREATE TABLE "SAYPHONE"."PH_LT_120_ROOM" 
(    "PARTKEY_DAY" VARCHAR2(2) DEFAULT to_char(sysdate,'dd'), 
"ROOMID" NUMBER(10,0), 
"STARTDATE" VARCHAR2(14), 
"ENDDATE" VARCHAR2(14), 
"CHANNEL" NUMBER(2,0), 
"SERVER" NUMBER(3,0), 
"DEALMONEY" NUMBER(20,0), 
"CIRCULMONEY" NUMBER(20,0), 
"BBINGMONEY" NUMBER(20,0), 
"ROOMTITLE" VARCHAR2(50), 
"SIDEMONEY" NUMBER(20,0), 
"OPT1" NUMBER(2,0), 
"OPT2" NUMBER(2,0), 
"OPT3" NUMBER(2,0), 
"OPT4" NUMBER(2,0)
) PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 
/**/
//----------------------------------------------------------------------------------------------------
void CGameMgr::DB_Room_Log()
{
	/*
	string sChannel=format("%d", m_cRCRoomData.m_option.m_lChannelID);
	DWORD channel=atoi(sChannel.substr(sChannel.length() - 3, 3).c_str());
	DWORD server=m_cRCRoomData.m_option.m_lCategory;
	//m_pGRCContainer->GetRoomID(&channel, &server);  // success : 
	server=server%1000;
	channel=m_cGameInfo.m_lChannel_idx;

	string pdate="01";
	string startdate=m_cGameInfo.m_sGameDate;
	if(false==m_cGameInfo.m_sGameDate.empty()){
		pdate=m_cGameInfo.m_sGameDate.substr(6,2);
	}
	else{
		startdate=GetCurrentSystemTime_s();
	}
	string enddate=GetCurrentSystemTime_s();
	int	roomid=m_cGameInfo.m_lRoomId;
	__int64 bbingmoney=m_cRCRoomData.m_option.m_llGameAnteMoney;
	__int64 dealmoney=m_cGameInfo.m_CDivisionMoney.GetDealMoneyHab();
	__int64 circulmoney=(m_cGameInfo.m_llPoolMoney+m_cGameInfo.GetGiveMoneyHab());
	__int64 sidemoney=0;
	string roomtitle=RoomTitle();
	__int64 opt1=m_cRCRoomData.m_option.m_lChoiceMode;
	int opt2=m_cRCRoomData.m_option.m_lBetRule;
	int opt3=(int)((true==m_cRCRoomData.m_option.m_bEcho)?(1):(0));
	int opt4=0;


	string sLog1, sLog2;
	{
		sLog1=::format("Q|INSERT INTO PH_LT_%03d_ROOM(partkey_day,roomid,startdate,enddate,channel,server,dealmoney,circulmoney,bbingmoney,roomtitle,sidemoney,opt1,opt2,opt3,opt4) values", g_lSSN);
		sLog2=::format(" ('%s',%d,substrb('%s',1,14),substrb('%s',1,14),%d,%d,%I64i,%I64i,%I64i,substrb('%s',1,50),%I64i,%d,%d,%d,%d)",
			pdate.c_str(),roomid,startdate.c_str(),enddate.c_str(),channel,server,dealmoney,circulmoney,bbingmoney,"-",sidemoney,opt1,opt2,opt3,opt4);

		//sLog1=::format("INSERT INTO log_%03d_room(pdate,roomid,startdate,channel,server,bbingmoney,dealmoney,circulmoney,roomtitle,maxuser,secret,opt1,opt2,opt3,opt4,opt5) values", g_lSSN);
		//sLog2=::format("('%s',%d,'%s',%d,%d,%I64i,%I64i,%I64i,substrb('%s',1,28),%d,%d,%I64i,%d,%d,%d,%d)",pdate.c_str(),roomid,startdate.c_str(),channel,server,bbingmoney,dealmoney,circulmoney,roomtitle.c_str(),maxuser,secret, opt1, opt2, opt3, opt4, opt5);
	}

	string sQuery=::format("%s%s",sLog1.c_str(),sLog2.c_str());
	GBuf bufOut;
	long lResult=0;
	long lReturn=0;
	if( (lReturn=m_pGRCContainer->ExecuteQueryToDB(1, DBTYPE_PHONE, sQuery.c_str(), sQuery.size(), bufOut, &lResult))<0 )
	{ // 에러처리
		//DB_SETUSERDATA
		//lResult의 값을 보고 실패 원인을 찾음!
		m_cFileLog.DebugLog("RoomLog Failed!!!!");
		return;
	}
	*/
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
long CGameMgr::OnCreateRoom(const char* szRoomOption, long lSize)
{
	long lReturn=CObjectMgr::OnCreateRoom(szRoomOption, lSize);
	//SetAnteMoney(m_cGameInfo.m_lChannel_idx, m_cRCRoomData.m_option.m_lAnteMoney, m_cRCRoomData.m_option.m_lMaxUserCnt);
	NotifyChangeGameOption(0);
	m_cRCRoomData.m_option.m_lMaxUserCnt=m_cRCRoomData.m_option.m_lMaxPlayerUserCnt=GetMaxPlayerUserCount();
	m_cRCRoomData.m_option.m_lMaxPlayerCardCnt=GetMaxPlayerCardCount();
	if(0==m_cRCRoomData.m_option.m_lMaxUserCnt){
		m_cRCRoomData.m_option.m_lMaxUserCnt=5;
	}
	m_cRCRoomData.Init(m_cRCRoomData.m_option.m_lMaxUserCnt, m_cRCRoomData.m_option.m_lMaxUserCnt);
	m_cGameInfo.Init(m_cRCRoomData.m_option.m_lMaxUserCnt, m_cRCRoomData.m_option.m_lMaxUserCnt);
	return lReturn;
}
//----------------------------------------------------------------------------------------------------
//long CGameMgr::OnAddUserInRoom(long lUSN, const char* szUserData, long lSize, long* plErrorCode)
long CGameMgr::OnAddUserInRoom(adl::RCUser *user)
{
	//long lReturn=CObjectMgr::OnAddUserInRoom(lUSN, szUserData, lSize, plErrorCode);
	long lReturn=CObjectMgr::OnAddUserInRoom(user);
	return lReturn;
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::OnReserveRemoveUserInRoom(long lUSN)
{
	long lReturn=CObjectMgr::OnReserveRemoveUserInRoom(lUSN);

	return lReturn;
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::OnUserDisconnectInRoomNotify(long lUSN)
{
	long lReturn=CObjectMgr::OnUserDisconnectInRoomNotify(lUSN);

	return lReturn;
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::OnRemoveUser(long lUSN)
{
	long lReturn=CObjectMgr::OnRemoveUser(lUSN);

	return lReturn;
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::OnUserMsgToRoomNotify(long lUSN, long lSize)
{
	long lReturn=CObjectMgr::OnUserMsgToRoomNotify(lUSN, lSize);

	return lReturn;
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::OnTimerToRoomNotify(long lTimerIndex)
{
	long lReturn=CObjectMgr::OnTimerToRoomNotify(lTimerIndex);

	return lReturn;
}
////----------------------------------------------------------------------------------------------------
//long CGameMgr::OnChangeUserAvatarNotify(long lUSN, long lAvatar)
//{
//	long lReturn=CObjectMgr::OnChangeUserAvatarNotify(lUSN, lAvatar);
//
//	return lReturn;
//}
////----------------------------------------------------------------------------------------------------
//long CGameMgr::OnChangeUserNicknameNotify(long lUSN, const char* szNickname, long lSize)
//{
//	long lReturn=CObjectMgr::OnChangeUserNicknameNotify(lUSN, szNickname, lSize);
//
//	return lReturn;
//}
//----------------------------------------------------------------------------------------------------
long CGameMgr::OnChangeUserItemNotify(long lUSN, const char* szItem, long lSize)
{
	long lReturn=CObjectMgr::OnChangeUserItemNotify(lUSN, szItem, lSize);

	return lReturn;
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::OnRecvMessageFromServer(long lMsgType, long lParam, const char* szContents, long lSize)
{
	long lReturn=CObjectMgr::OnRecvMessageFromServer(lMsgType, lParam, szContents, lSize);

	return lReturn;
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::CanUseIBB(long lUSN)
{
	long lReturn=CObjectMgr::CanUseIBB(lUSN);

	return lReturn;
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::OnAExcuteQueryToDBResult(long lResult, long lIndex, const char* szResult, long lSize, long lErrorCode)
{
	long lReturn=CObjectMgr::OnAExcuteQueryToDBResult(lResult, lIndex, szResult, lSize, lErrorCode);

	return lReturn;
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::CheckUserStateFromWeb(long lUSN)
{
	long lReturn=CObjectMgr::CheckUserStateFromWeb(lUSN);

	return lReturn;
}
//----------------------------------------------------------------------------------------------------
long CGameMgr::GetRoomInfo(const char* szRoomInfo, long lSize)
{
	long lReturn=CObjectMgr::GetRoomInfo(szRoomInfo, lSize);

	return lReturn;
}


#endif
