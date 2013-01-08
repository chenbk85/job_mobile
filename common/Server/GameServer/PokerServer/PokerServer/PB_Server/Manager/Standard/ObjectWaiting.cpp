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
// ���ǥ���� �������� ������ Ŭ���̾�Ʈ�� ������
//
//****************************************************************************
void CObjectWaiting::SendWaitingUserData( const bool bSendData )
{
	if( bSendData ) //��������������� ���
	{
		MsgSC_AllWaitingUserDataNtf msg;
		msg.m_bSendWaitingUser=true;
		msg.m_WaitingUserData.assign( m_vtWaitingUser.begin(), m_vtWaitingUser.end() );
		PayloadSC pld(PayloadSC::msgAllWaitingUserDataNtf_Tag, msg);
		GetObjectMgr()->SendToAll(pld);
	}
	else //������������ �����°��
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
// �켱 �濡 �־���� ���常 ���� ó������
//
//****************************************************************************
void CObjectWaiting::SendAllowEntryWaitingUser( const long lUSN )
{
	//�켱 �濡 �־�� �ȴ�, Ŭ���̾�Ʈ���� �ӵ��� Ʋ���� �޾Ƽ� �ִٰ� ������
	s_req_entry msg1;
	msg1.set_m_nversion(g_nVersion);
	msg1.set_m_bwelcomesound(true);
	msg1.set_m_lsoundtype(1); //�켱����Ʈó���س��� ���߿� �޾Ƽ� ����
	RCUser* pUser=GetObjectMgr()->FindUser(lUSN);
	if(NULL==pUser) return;
	msg1.set_m_snickname(pUser->m_sNickName);
	msg1.set_m_lclevel(pUser->m_lCLevel);
	msg1.set_m_lsex(pUser->m_lSex);
	if( GetObjectMgr()->OnRcvEntry(NULL, lUSN, &msg1) )
	{
		//����Ʈ���� �������ؼ� ���Ե�
		MsgSC_AllowEntryWaitingUser msg;
		PayloadSC pld(PayloadSC::msgAllowEntryWaitingUser_Tag, msg);
		GetObjectMgr()->SendToUser(lUSN, pld);
	}
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
// Ƽ���� �������ν� ����ڷμ� �������ӿ� �����Ҽ��ֵ��� ����
//
//****************************************************************************
void CObjectWaiting::ReceiveTicket( const long lUSN, RCUser *pUser )
{
	if( !IsPossibleReceiveTicket( lUSN, pUser ) )
		return; //�̺κ��� �ɸ��� ��ȣǥ�� ������ ���� ��Ȳ�̴�.

	if( IsEntryWithoutTicket( lUSN, GetObjectMgr()->IsSpace() ) ) //���ڸ��� ������ �ٷ������Ű��
	{
		SendAllowEntryWaitingUser(lUSN);
		return;
	}

	std::vector<WAITINGUSERDATA>::iterator itWebCallUser;
	for( itWebCallUser=m_vtWebCallUser.begin() ; itWebCallUser!=m_vtWebCallUser.end() ; ++itWebCallUser )
	{
		if( (*itWebCallUser).m_lUSN==lUSN ) //���������̹Ƿ� Ƽ���� ����������.
			return;
	}

	if( IsTicketUser(lUSN) ) //�̹� ���� ������ �޾Ƽ��� �ȵȴ�.
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
// Ƽ�Ϲ������� ����ؼ� ���������ڷ� �������ؼ�
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
// ���������� ��ȣ���� ����Ƽ���� ���� ������ �÷��̾�� ������ �Ż�Ȳ�� ��������
//
//****************************************************************************
void CObjectWaiting::SortTicketUser()
{
	int nNum=0;
	bool bNextUser=false; //�������������� ǥ���Ѿ��ѻ���
	std::vector<WAITINGUSERDATA>::iterator itWaitingUser;
	for( itWaitingUser=m_vtWaitingUser.begin() ; itWaitingUser!=m_vtWaitingUser.end() ; ++itWaitingUser )
	{
		(*itWaitingUser).m_lTicketNum=++nNum;
		if( !bNextUser && !(*itWaitingUser).m_bCallWeb )
		{
			(*itWaitingUser).m_lBackColor=1; //�������� ������ǥ��
			bNextUser=true;
		}
		else
			(*itWaitingUser).m_lBackColor=0;	//������ �����ʷϻ�ǥ��
	}
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
// ������������ üũ
//
//****************************************************************************
bool CObjectWaiting::IsWebCallUser( const long lUSN )
{
	std::vector<WAITINGUSERDATA>::iterator itWebCallUser;
	for( itWebCallUser=m_vtWebCallUser.begin() ; itWebCallUser!=m_vtWebCallUser.end() ; ++itWebCallUser )
	{
		if( (*itWebCallUser).m_lUSN==lUSN && (*itWebCallUser).m_bCallWeb ) //������ �����߿� �����Ѵٸ� 
			return true; 
	}
	return false;
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
// ������ �ϴµ����� ������� ���� �ʱ����ؼ� �÷��׸� �д�
//
//****************************************************************************
void CObjectWaiting::CallWebClient( const long lUSN, const bool bCallWeb )
{
	if( bCallWeb ) //�����ѻ���
	{
		if( IsWebCallUser(lUSN) ) //���������� �����Ѵٸ�
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
	else //��������
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
// �濡 ����� ���ɿ��θ� ���ؼ� �ٷ� �����ϰų� �ƴϸ� �����ڷ� ���� ���ǥ�� �޵��� ����
//
//****************************************************************************
bool CObjectWaiting::IsEntryWithoutTicket( const long lUSN, const bool bSpace )
{
	if( !bSpace ) //���ڸ� �����Ƿ�
		return false; //�����ڷ� ������ ���ǥ�ޱ��ؾ���

	if( !m_vtWaitingUser.empty() ) //����ڰ� �ִٴ� ���̹Ƿ� �����ڷ� �������Ѵ�.
	{
		std::vector<WAITINGUSERDATA>::iterator itWaitingUser;
		for( itWaitingUser=m_vtWaitingUser.begin() ; itWaitingUser!=m_vtWaitingUser.end() ; ++itWaitingUser )
		{
			if( (*itWaitingUser).m_lUSN==lUSN && (*itWaitingUser).m_lBackColor==1 ) //�ڱⰡ ������߿� �ڽ����ְ�, ������ ������ �Ǿ��ִٸ�
				return true;
		}
		return false; //�����ڷ� ������ ���ǥ�ޱ��ؾ���	
	}

	return true;	//�÷��̾�� �����ص� �ȴ�
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
//	���ӹ������� ���������ų� ���ɳ�Ʈ�ϸ� ���� USN�� �˻��ؼ� �� ������ �÷��̾�� �־�����
//
//****************************************************************************
long CObjectWaiting::AddUserInGameRoom()
{
	std::vector<WAITINGUSERDATA>::iterator itWaitingUser;
	for( itWaitingUser=m_vtWaitingUser.begin() ; itWaitingUser!=m_vtWaitingUser.end() ; ++itWaitingUser )
	{
		if( (*itWaitingUser).m_lBackColor==1 ) //���������� ������ Ƽ���� ������ �ִ� ������ �÷����Ѵ�.
			return (*itWaitingUser).m_lUSN;
	}
	return -1;
}
//----------------------------------------------------------------------------------------------------
//****************************************************************************
//
//	��ȣǥ�������� ���尡�������� ��ȣǥ �������ִ�.
//
//****************************************************************************
bool CObjectWaiting::IsPossibleReceiveTicket( const long lUSN, RCUser *pUser )
{
	if(pUser==NULL) return false;

	bool bMoney=GetObjectMgr()->IsMoney(pUser);
	bool bIp	= GetObjectMgr()->IsIP(pUser);
//	// ä�� ���� ��� äũ
	bool bGrade=GetObjectMgr()->IsGrade( pUser );

	bool bBlackList=GetObjectMgr()->IsBlackList(lUSN);
	bool bGameLimit=GetObjectMgr()->IsGameLimit(pUser);
	//	bool bPlayCheckInPowerChannel=GetObjectMgr()->IsPlayCheckInPowerChannel(lUSN); //ö�̰� �Ŀ�ä�����尡�ɿ��� üũ

	if(bMoney && bIp && (!bBlackList) && bGameLimit && bGrade )
		return true;	//������ �����ϴ�
	else
	{
//		GetObjectMgr()->SendEntryReject(lUSN, ENTRY_NEEDTICKET); //ö�̰� ���ǥ�ý���:������ ������� �����ڷο켱��
		//if(!bPlayCheckInPowerChannel)	//ö�̰� �Ŀ�ä�����尡�ɿ��� üũ
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
		//	GetObjectMgr()->SendEntryReject(lUSN, ENTRY_LOCALJACKPOT_NOMONEY); //���� ���� : ���� ����Ӵϰ� �����Ҷ�
	}
	return false;
}
//----------------------------------------------------------------------------------------------------
void CObjectWaiting::OnRcvWaitingUserTicketReq(long lUSN, MsgCS_WaitingUserTicketReq* pMsg)
{
	switch( pMsg->m_nType )
	{
	case 1: //���ǥ����
		{
			RCUser *pUser=GetObjectMgr()->FindUser(lUSN);
			ReceiveTicket(lUSN, pUser);
		}
		break;
	case 2: //���ǥ���
		CancelTicket(lUSN);
		break;
	case 3:	//���ݻ�뿩��
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
	CallWebClient(lUSN, false); //����������Ʈ �����Ƿ� �÷��׸� Ǯ������Ѵ�.
}
//----------------------------------------------------------------------------------------------------