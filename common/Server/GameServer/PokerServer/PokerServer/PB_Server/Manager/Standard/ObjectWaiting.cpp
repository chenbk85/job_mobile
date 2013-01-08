//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"
#include "ObjectWaiting.h"
#include "../ObjectMgr.h"

#include "../../../Protocol Buffers/Poker/adl.h"
//----------------------------------------------------------------------------------------------------
bool CObjectWaiting::CreateObject(void)
{
	CObjectBase::CreateObject();
	return true;
}
//----------------------------------------------------------------------------------------------------
bool CObjectWaiting::IsTicketUser( const long lUSN )
{
	std::vector<WAITINGUSERDATA>::iterator itWaitingUser;
	for( itWaitingUser=m_vtWaitingUser.begin() ; itWaitingUser!=m_vtWaitingUser.end() ; ++itWaitingUser )
	{
		if( (*itWaitingUser).m_lUSN==lUSN )
			return true; 
	}
	return false;
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
// 대기표받은 유저들의 정보를 클라이언트로 보내자
//
//****************************************************************************
void CObjectWaiting::SendWaitingUserData( const bool bSendData )
{
	if( bSendData ) //대기자정보보내는 경우
	{
		MsgSC_AllWaitingUserDataNtf msg;
		msg.m_bSendWaitingUser=true;
		msg.m_WaitingUserData.assign( m_vtWaitingUser.begin(), m_vtWaitingUser.end() );
		PayloadSC pld(PayloadSC::msgAllWaitingUserDataNtf_Tag, msg);
		GetObjectMgr()->SendToAll(pld);
	}
	else //웹콜유저정보 보내는경우
	{
		MsgSC_AllWaitingUserDataNtf msg;
		msg.m_bSendWaitingUser=false;
		msg.m_WaitingUserData.assign( m_vtWebCallUser.begin(), m_vtWebCallUser.end() );
		PayloadSC pld(PayloadSC::msgAllWaitingUserDataNtf_Tag, msg);
		GetObjectMgr()->SendToAll(pld);
	}
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
// 우선 방에 넣어놓고 사운드만 따로 처리하자
//
//****************************************************************************
void CObjectWaiting::SendAllowEntryWaitingUser( const long lUSN )
{
	//우선 방에 넣어야 된다, 클라이언트마다 속도가 틀려서 받아서 넣다간 못들어간다
	s_req_entry msg1;
	msg1.set_m_nversion(g_nVersion);
	msg1.set_m_bwelcomesound(true);
	msg1.set_m_lsoundtype(1); //우선디폴트처리해놓고선 나중에 받아서 세팅
	RCUser* pUser=GetObjectMgr()->FindUser(lUSN);
	if(NULL==pUser) return;
	msg1.set_m_snickname(pUser->m_sNickName);
	msg1.set_m_lclevel(pUser->m_lCLevel);
	msg1.set_m_lsex(pUser->m_lSex);
	if( GetObjectMgr()->OnRcvEntry(NULL, lUSN, &msg1) )
	{
		//디폴트사운드 세팅위해서 쓰게됨
		MsgSC_AllowEntryWaitingUser msg;
		PayloadSC pld(PayloadSC::msgAllowEntryWaitingUser_Tag, msg);
		GetObjectMgr()->SendToUser(lUSN, pld);
	}
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
// 티켓을 받음으로써 대기자로서 다음게임에 참여할수있도록 하자
//
//****************************************************************************
void CObjectWaiting::ReceiveTicket( const long lUSN, RCUser *pUser )
{
	if( !IsPossibleReceiveTicket( lUSN, pUser ) )
		return; //이부분이 걸리면 번호표를 받을수 없는 상황이다.

	if( IsEntryWithoutTicket( lUSN, GetObjectMgr()->IsSpace() ) ) //빈자리가 있으면 바로입장시키자
	{
		SendAllowEntryWaitingUser(lUSN);
		return;
	}

	std::vector<WAITINGUSERDATA>::iterator itWebCallUser;
	for( itWebCallUser=m_vtWebCallUser.begin() ; itWebCallUser!=m_vtWebCallUser.end() ; ++itWebCallUser )
	{
		if( (*itWebCallUser).m_lUSN==lUSN ) //웹콜유저이므로 티켓을 받을수없다.
			return;
	}

	if( IsTicketUser(lUSN) ) //이미 받은 유저는 받아서는 안된다.
	{
		SortTicketUser();
		SendWaitingUserData();
		return;
	}

	WAITINGUSERDATA WaitingUser;
	WaitingUser.m_lUSN=lUSN;
	WaitingUser.m_lTicketNum=static_cast<long>( m_vtWaitingUser.size() + 1 );
	WaitingUser.m_bCallWeb=false;
	WaitingUser.m_lBackColor=0;
	m_vtWaitingUser.push_back(WaitingUser);

	SortTicketUser();
	SendWaitingUserData();
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
// 티켓받은것을 취소해서 순수관람자로 빼기위해서
//
//****************************************************************************
void CObjectWaiting::CancelTicket( const long lUSN )
{
	std::vector<WAITINGUSERDATA>::iterator itWaitingUser;
	for( itWaitingUser=m_vtWaitingUser.begin() ; itWaitingUser!=m_vtWaitingUser.end() ; ++itWaitingUser )
	{
		if( (*itWaitingUser).m_lUSN==lUSN )
		{
			m_vtWaitingUser.erase(itWaitingUser);
			SortTicketUser();
			SendWaitingUserData();
			break;
		}
	}
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
// 실제적으로 번호보다 빨간티켓을 받은 유저가 플레이어로 들어가도록 매상황에 정렬하자
//
//****************************************************************************
void CObjectWaiting::SortTicketUser()
{
	int nNum=0;
	bool bNextUser=false; //다음유저색깔을 표시한안한상태
	std::vector<WAITINGUSERDATA>::iterator itWaitingUser;
	for( itWaitingUser=m_vtWaitingUser.begin() ; itWaitingUser!=m_vtWaitingUser.end() ; ++itWaitingUser )
	{
		(*itWaitingUser).m_lTicketNum=++nNum;
		if( !bNextUser && !(*itWaitingUser).m_bCallWeb )
		{
			(*itWaitingUser).m_lBackColor=1; //다음유저 빨간색표시
			bNextUser=true;
		}
		else
			(*itWaitingUser).m_lBackColor=0;	//나머지 유저초록색표시
	}
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
// 웹콜유저인지 체크
//
//****************************************************************************
bool CObjectWaiting::IsWebCallUser( const long lUSN )
{
	std::vector<WAITINGUSERDATA>::iterator itWebCallUser;
	for( itWebCallUser=m_vtWebCallUser.begin() ; itWebCallUser!=m_vtWebCallUser.end() ; ++itWebCallUser )
	{
		if( (*itWebCallUser).m_lUSN==lUSN && (*itWebCallUser).m_bCallWeb ) //웹콜한 유저중에 존재한다면 
			return true; 
	}
	return false;
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
// 웹콜을 하는동안은 방안으로 넣지 않기위해서 플래그를 둔다
//
//****************************************************************************
void CObjectWaiting::CallWebClient( const long lUSN, const bool bCallWeb )
{
	if( bCallWeb ) //웹콜한상태
	{
		if( IsWebCallUser(lUSN) ) //웹콜유저에 존재한다면
			return;
		else
		{
			WAITINGUSERDATA WebCallUser;
			WebCallUser.m_lUSN=lUSN;
			WebCallUser.m_lTicketNum=-1;
			WebCallUser.m_bCallWeb=true;
			WebCallUser.m_lBackColor=-1;
			m_vtWebCallUser.push_back(WebCallUser);
			SendWaitingUserData(false);
		}
	}
	else //해제상태
	{
		std::vector<WAITINGUSERDATA>::iterator itWebCallUser;
		for( itWebCallUser=m_vtWebCallUser.begin() ; itWebCallUser!=m_vtWebCallUser.end() ; ++itWebCallUser )
		{
			if( (*itWebCallUser).m_lUSN==lUSN )
			{
				m_vtWebCallUser.erase(itWebCallUser);
				SendWaitingUserData(false);
				break;
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
// 방에 입장시 가능여부를 통해서 바로 입장하거나 아니면 관전자로 빼서 대기표를 받도록 하자
//
//****************************************************************************
bool CObjectWaiting::IsEntryWithoutTicket( const long lUSN, const bool bSpace )
{
	if( !bSpace ) //빈자리 없으므로
		return false; //관전자로 빠져서 대기표받기해야함

	if( !m_vtWaitingUser.empty() ) //대기자가 있다는 말이므로 관람자로 빠져야한다.
	{
		std::vector<WAITINGUSERDATA>::iterator itWaitingUser;
		for( itWaitingUser=m_vtWaitingUser.begin() ; itWaitingUser!=m_vtWaitingUser.end() ; ++itWaitingUser )
		{
			if( (*itWaitingUser).m_lUSN==lUSN && (*itWaitingUser).m_lBackColor==1 ) //자기가 대기자중에 자신이있고, 다음번 유저로 되어있다면
				return true;
		}
		return false; //관전자로 빠져서 대기표받기해야함	
	}

	return true;	//플레이어로 참여해도 된다
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
//	게임방유저가 빠져나가거나 디스케넥트하면 여기 USN을 검색해서 그 유저를 플레이어로 넣어주자
//
//****************************************************************************
long CObjectWaiting::AddUserInGameRoom()
{
	std::vector<WAITINGUSERDATA>::iterator itWaitingUser;
	for( itWaitingUser=m_vtWaitingUser.begin() ; itWaitingUser!=m_vtWaitingUser.end() ; ++itWaitingUser )
	{
		if( (*itWaitingUser).m_lBackColor==1 ) //실제적으로 빨간색 티켓을 가지고 있는 유저가 플레이한다.
			return (*itWaitingUser).m_lUSN;
	}
	return -1;
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
//	번호표받을때도 입장가능유저만 번호표 받을수있다.
//
//****************************************************************************
bool CObjectWaiting::IsPossibleReceiveTicket( const long lUSN, RCUser *pUser )
{
	if(pUser==NULL) return false;

	bool bMoney=GetObjectMgr()->IsMoney(pUser);
	bool bIp	= GetObjectMgr()->IsIP(pUser);
//	// 채널 입장 등급 채크
	bool bGrade=GetObjectMgr()->IsGrade( pUser );

	bool bBlackList=GetObjectMgr()->IsBlackList(lUSN);
	bool bGameLimit=GetObjectMgr()->IsGameLimit(pUser);
	//	bool bPlayCheckInPowerChannel=GetObjectMgr()->IsPlayCheckInPowerChannel(lUSN); //철이가 파워채널입장가능여부 체크

	if(bMoney && bIp && (!bBlackList) && bGameLimit && bGrade )
		return true;	//입장이 가능하다
	else
	{
//		GetObjectMgr()->SendEntryReject(lUSN, ENTRY_NEEDTICKET); //철이가 대기표시스템:유저가 모두차서 관람자로우선뺌
		//if(!bPlayCheckInPowerChannel)	//철이가 파워채널입장가능여부 체크
		//	GetObjectMgr()->SendEntryReject(lUSN, ENTRY_POWERCHANNEL);
		if(!bMoney)
		{
			if(__CONST_::TWOUSER_NUM==GetObjectMgr()->GetData().m_option.m_lMaxUserCnt)
			{
				GetObjectMgr()->SendEntryReject(lUSN, ENTRY_TWOOWNER_NOMONEY);
			}
			else
			{
				GetObjectMgr()->SendEntryReject(lUSN, ENTRY_NOMONEY_OBSERVE);
			}
		}
		else if(!bGrade)
			GetObjectMgr()->SendEntryReject(lUSN, ENTRY_GRADE);
		else if(!bIp)
			GetObjectMgr()->SendEntryReject(lUSN, ENTRY_IP);
		else if(bBlackList)
			GetObjectMgr()->SendEntryReject(lUSN, ENTRY_BLACKLIST);
		else if(!bGameLimit)
			GetObjectMgr()->SendEntryReject(lUSN, ENTRY_GAMELIMIT);

		//else if(!bLocalJackPot)
		//	GetObjectMgr()->SendEntryReject(lUSN, ENTRY_LOCALJACKPOT_NOMONEY); //로컬 잭팟 : 유저 입장머니가 부족할때
	}
	return false;
}
//----------------------------------------------------------------------------------------------------
void CObjectWaiting::OnRcvWaitingUserTicketReq(long lUSN, MsgCS_WaitingUserTicketReq* pMsg)
{
	switch( pMsg->m_nType )
	{
	case 1: //대기표받음
		{
			RCUser *pUser=GetObjectMgr()->FindUser(lUSN);
			ReceiveTicket(lUSN, pUser);
		}
		break;
	case 2: //대기표취소
		CancelTicket(lUSN);
		break;
	case 3:	//웹콜사용여부
		CallWebClient(lUSN, pMsg->m_bValue);
		break;
	}
}
//----------------------------------------------------------------------------------------------------
void CObjectWaiting::OnRcvUpdateWaitingUserInfoReq(long lUSN, MsgCS_UpdateWaitingUserInfoReq* pMsg)
{
	RCUser *pUser=GetObjectMgr()->FindUser(lUSN);
	if( pUser!=NULL )
	{
		GetObjectMgr()->Proc_UpdateUserData(lUSN, true);
	}
	CallWebClient(lUSN, false); //유저업데이트 됐으므로 플래그를 풀어줘야한다.
}
//----------------------------------------------------------------------------------------------------