//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"

#include "ObjectMgr.h"

#include <stdio.h>

//----------------------------------------------------------------------------------------------------
bool CObjectMgr::IsUserJoinErr(long lUSN, long & lErrorCode)
{
	bool bTemp=false;
	if(m_cRCRoomData.m_lState==GAMESTATE_DEAD)
	{
		lErrorCode=ERR_INVALIDTARGET;
		bTemp=true;
	}
	if(0!=m_cRCRoomData.m_option.m_lMakeUSN){
		if(false==m_RCUserData.ExistUser()){
			if(lUSN!=m_cRCRoomData.m_option.m_lMakeUSN){
				lErrorCode=ERR_NOSEAT;
				return true;
			}
		}
	}
	if(IsBlackList(lUSN))
	{
		lErrorCode=ERR_NOACCESS;
		bTemp=true;
	}

	return bTemp;
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendUserJoinErr(long lUSN, long lErrorCode)
{
	MsgSC_UserJoinErr msg;
	msg.m_lErrorCode=lErrorCode;
	//PayloadSC pld(PayloadSC::msgUserJoinErr_Tag, msg);
	//SendToUser(lUSN, pld);
	SendToUser(lUSN, GLAnsGameProtocol_Type_userjoinerr, &msg);
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendUserDisconnect(long lUSN, int nIndex)
{
	MsgSC_UserDisconnect msg;
	msg.m_lUSN=lUSN;
	msg.m_uinfo=GetUI(nIndex);
	msg.m_lState=m_cRCRoomData.m_lState;
	msg.m_lOwnerUSN=m_cGameInfo.m_lOwnerUSN;
	//PayloadSC pld(PayloadSC::msgUserDisconnect_Tag, msg);
	//SendToAll(pld);
	SendToAll(GLAnsGameProtocol_Type_userdisconnect, &msg);
	//철이가 대기표시스템 : 나갈때나 디스커넥트일때 체크
	m_cObjectWaiting.CancelTicket(lUSN); //유저가 나갈때 데이터있는지체크해지움
	m_cObjectWaiting.CallWebClient(lUSN,false); //철이가 대기표시스템:대기자에서 빠져나가므로 웹콜유저에서 빼자
	long lTempUSN=m_cObjectWaiting.AddUserInGameRoom();
	if( m_cObjectWaiting.IsEntryWithoutTicket( lTempUSN, IsSpace() ) ) //빈자리가 있으면
	{
		if( lTempUSN >= 0 ) //대기표받은 유저를 강제로 방에 넣자
			m_cObjectWaiting.SendAllowEntryWaitingUser(lTempUSN);
	}
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::Store_WinLoseCntVector( vecWinLoseCnt	&vecWLCnt )
{
	vecWLCnt.clear();
	int nTotal=GetUISize();
	RCUser *pUser=NULL;
	for( int i=0;i<nTotal;i++){
		if( GetUI(i).m_lUSN>0 ){
			pUser=FindUser( GetUI(i).m_lUSN );
		}
		if( pUser ){
			vecWLCnt.push_back( pUser->m_cWinLose_Today );
		}
		else{
			CWinLose empty;
			empty.Clear();
			vecWLCnt.push_back( empty );
		}	
	}
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendEntryReject(long lUSN, long lType)
{
	RCUser* pUser=FindUser(lUSN);
	if(pUser==NULL) return;
	SendObserverCnt();
	MsgSC_EntryReject msg;
	msg.m_lType=lType;
	msg.m_llCMoney=pUser->m_llCMoney;
	//PayloadSC pld(PayloadSC::msgEntryReject_Tag, msg);
	//SendToUser(lUSN, pld);
	SendToUser(lUSN, GLAnsGameProtocol_Type_entryreject, &msg);
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendObserveAns(long lUSN, int nIndex) // 미사용
{
	MsgSC_ObserveAns msg;
	msg.m_lUSN=lUSN;
	msg.m_nIndex=nIndex;
	msg.m_lOwnerUSN=m_cGameInfo.m_lOwnerUSN;
	msg.m_uinfo=GetUI(nIndex);
	msg.m_money=GetMoney(nIndex);
	PayloadSC pld(PayloadSC::msgObserveAns_Tag, msg);
	SendToAll(pld);
	//철이가 대기표시스템 : 관람으로 빠질때 체크
	m_cObjectWaiting.CancelTicket(lUSN); //유저가 나갈때 데이터있는지체크해지움
	m_cObjectWaiting.CallWebClient(lUSN,false); //철이가 대기표시스템:대기자에서 빠져나가므로 웹콜유저에서 빼자
	long lTempUSN=m_cObjectWaiting.AddUserInGameRoom();
	if( m_cObjectWaiting.IsEntryWithoutTicket( lTempUSN, IsSpace() ) ) //빈자리가 있으면
	{
		if( lTempUSN >= 0 ) //대기표받은 유저를 강제로 방에 넣자
			m_cObjectWaiting.SendAllowEntryWaitingUser(lTempUSN);
	}
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendBoss()
{
	MsgSC_Boss msg;
	msg.m_lBossUSN=m_cGameInfo.m_lBossUSN;
	PayloadSC pld(PayloadSC::msgBoss_Tag, msg);
	//SendToAll(pld);
	SendToAll(GLAnsGameProtocol_Type_ans_boss, &msg);
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendPurgeAns(long lUSN, bool bIsUI)
{
	MsgSC_PurgeAns msg;
	//PayloadSC pld(PayloadSC::msgPurgeAns_Tag, msg);
	//SendToUser(lUSN, pld);
	SendToUser(lUSN, GLAnsGameProtocol_Type_ans_purge, &msg);

	DB_Purge_Log(lUSN, bIsUI);

	m_cPurge.nRoomPurgeCnt++;

	// 강퇴 5회 제공방 (문광부 3차)
	if( m_cPurge.nRoomPurgeCnt==5 )
	{
		int nSetTime=1800000;//Get_Velocity(m_cGameInfo.m_lChannel_idx, TIMER_PURGE, -1);
		SetTimer(TIMER_PURGE, nSetTime, NULL);
	}

	if(m_cPurge.nRoomPurgeCnt>5)
	{
		string str="";//::format("m_cPurge.nRoomPurgeCnt : %d", m_cPurge.nRoomPurgeCnt);
		m_cFileLog.Log(str.c_str());
		m_cPurge.nRoomPurgeCnt=5;
	}
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendPurgeInfo()
{
	MsgSC_PurgeInfo msg;
	msg.m_vtPurgeUSN=m_cPurge.vtPurgeList;
	msg.m_nCount=m_cPurge.nRoomPurgeCnt;
	//PayloadSC pld(PayloadSC::msgPurgeInfo_Tag, msg);
	//SendToAll(pld);
	SendToAll(GLAnsGameProtocol_Type_purgeinfo, &msg);
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendFMoney(long lUSN) // 미사용
{
	char tmpStr[256];
	string str;
	str="|";
	ForEachElmt(vector<RCUser>, m_RCUserData, i, j){
		//str+=::format("%d=%I64i,%I64i|", (*i).m_lUSN, (*i).m_llFMoney,(*i).m_llCMoney);
		sprintf(tmpStr, "%d=%I64i,%I64i|", (*i).m_lUSN, (*i).m_llFMoney,(*i).m_llCMoney);
		str.append(tmpStr);			
	}
	MsgSC_FMoney msg;
	msg.m_sFMoney.assign(str);
	PayloadSC pld(PayloadSC::msgFMoney_Tag, msg);
	if(lUSN==-1)
		SendToAll(pld);
	else
		SendToUser(lUSN, pld);
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendGameEndSystemMsg(long lType, long lUSN, bool bGiveUp, string sMsg, __int64 lMoney) // 미사용
{
	MsgSC_GameEndSystemMsg msg;
	msg.m_lType=lType;
	msg.m_lUSN=lUSN;
	msg.m_bGiveUp=bGiveUp;
	msg.m_sMsg=sMsg;
	msg.m_llMoney=lMoney;
	PayloadSC pld(PayloadSC::msgGameEndSystemMsg_Tag, msg);
	SendToAll(pld);
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendExtMoneyNotify(long lUSN, RCUser * pUser, bool bExtType) //미사용
{
	MsgSC_ExtMoneyNotify msg;
	msg.m_lUSN=lUSN;
	msg.m_bExtType=bExtType;
	msg.m_llCMoney=pUser->m_llCMoney;
	//msg.m_llCashBox=pUser->GetCashBox();
	//msg.m_llExtMoney=pUser->GetExtMoney();
	//msg.m_llExtDate=pUser->GetExtDate();
	PayloadSC pld(PayloadSC::msgExtMoneyNotify_Tag, msg);
	SendToAll(pld);
	//	SendToUser(lUSN, pld);
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendChangeAvatarNotify(int nIndex) // 미사용
{
	UserInfo & ui=GetUI(nIndex);
	if(ui.m_lUSN<0) return;

	MsgSC_ChangeAvatarNotify msg;
	msg.m_lUSN=ui.m_lUSN;
	msg.m_nIndex=nIndex;
	msg.m_uinfo=GetUI(nIndex);
	PayloadSC pld(PayloadSC::msgChangeAvatarNotify_Tag, msg);
	SendToAll(pld);
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendExitNtf(int nIndex, long lExit, bool bExit)
{
	if(nIndex==-1) return;
	UserInfo & ui=GetUI(nIndex);
	ui.m_lExit=lExit;
	if(bExit){
		long lUSN=ui.m_lUSN;
		ObserveProcesses(lUSN);

		MsgSC_ExitNtf msg;
		msg.m_nIndex=nIndex;
		msg.m_lUSN=lUSN;
		msg.m_lExit=lExit;
		msg.m_bExit=bExit;
		//PayloadSC pld(PayloadSC::msgExitNtf_Tag, msg);
		//SendToUser(lUSN, pld);
		SendToAll(GLAnsGameProtocol_Type_exitntf, &msg);
	}
	else{
		MsgSC_ExitNtf msg;
		msg.m_nIndex=nIndex;
		msg.m_lUSN=ui.m_lUSN;
		msg.m_lExit=lExit;
		msg.m_bExit=bExit;
		//PayloadSC pld(PayloadSC::msgExitNtf_Tag, msg);
		//SendToAll(pld);
		SendToAll(GLAnsGameProtocol_Type_exitntf, &msg);
	}
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendDisconnectMoneyNotify( const string& sNickName, __int64 llDisconnectMoney ) // 미사용
{
	MsgSC_DisconnectMoneyNotify msg;
	msg.m_sNickName=sNickName;
	msg.m_llDisconnectMoney=llDisconnectMoney;
	PayloadSC pld(PayloadSC::msgDisconnectMoneyNotify_Tag, msg);
	SendToAll(pld);
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendRefillMoneyNtf(long lUSN, int nRefillCnt, __int64 llRefillMoney)
{
	MsgSC_RefillMoneyNtf msg;
	msg.m_lUSN=lUSN;
	msg.m_nRefillCnt=nRefillCnt;
	msg.m_llRefillMoney=llRefillMoney;
	//PayloadSC pld(PayloadSC::msgRefillMoneyNtf_Tag, msg);
	//SendToAll(pld);
	SendToAll(GLAnsGameProtocol_Type_refillmoneyntf, &msg);
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendObserverCnt()
{
	MsgSC_ObserverCnt msg;	
	msg.m_nObserverCnt=m_vtObserveUSN.size();

	if( m_vtObserveUSN.size()<0 )	msg.m_nObserverCnt=0;

	PayloadSC pld(PayloadSC::msgObserverCnt_Tag, msg);
	SendToAll(pld);
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendPoliceNotify()
{
	// 다른 사람들 들어오면 안된다
	SwitchState(GAMESTATE_DEAD);
	// 폴리스 방제 신고 변경안 작업
	MsgSC_PoliceNotify msg;
	msg.m_policeMsg="[ 불건전 방제로 방이 삭제됩니다 ]";
	PayloadSC pld(PayloadSC::msgPoliceNotify_Tag, msg);
	SendToAll(pld);
}
//----------------------------------------------------------------------------------------------------