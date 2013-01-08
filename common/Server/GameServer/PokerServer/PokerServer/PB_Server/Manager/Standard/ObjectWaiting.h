//------------------------------------------------------------------------------------
// Module Name			: Object(.h)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#ifndef __ObjectWaiting_H__
#define __ObjectWaiting_H__

#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/stubs/common.h>
//#include "../../../Protocol Buffers/Poker/Game_Poker.pb.h"
#include "../../../protobuf/gameLogic.pb.h"
#include "../../../Protocol Buffers/Poker/AdlGameCommon.h"
#include "../../../Protocol Buffers/Poker/AdlGameUser_Poker.h"
#include "../../../Protocol Buffers/Poker/AdlGame_Poker.h"
#include  "../Object.h"

//using namespace Game_Poker;
using namespace adl;

#pragma once

class CObjectWaiting : public CObjectBase
{
public:
	CObjectWaiting(void):CObjectBase(){
		InitObjectWaiting();
	}
	/*
	CObjectWaiting(ISGRCContainer* pGRCContainer):CObjectBase(pGRCContainer){
		InitObjectWaiting();
	} 
	*/
public:
	virtual ~CObjectWaiting(void){ FreeObjectWaiting(); }
	void InitObjectWaiting(void){}
	void FreeObjectWaiting(void){}
public:
	virtual bool CreateObject(void);
public:
	bool IsTicketUser( const long lUSN );
	void ReceiveTicket( const long lUSN, RCUser *pUser );
	void CancelTicket( const long lUSN );
	void CallWebClient( const long lUSN, const bool bCallWeb );
	bool IsWebCallUser( const long lUSN );
	void SortTicketUser();
	void SendWaitingUserData( const bool bSendData=true );
	void SendAllowEntryWaitingUser( const long lUSN );
	bool IsEntryWithoutTicket( const long lUSN, const bool bSpace );
	long AddUserInGameRoom();
	bool IsPossibleReceiveTicket( const long lUSN, RCUser *pUser );
private:
	std::vector<WAITINGUSERDATA> m_vtWaitingUser; //대기표받고있는 유저
	std::vector<WAITINGUSERDATA> m_vtWebCallUser; //웹콜한 유저는 따로저장하고있자
public:
	void OnRcvWaitingUserTicketReq(long lUSN, MsgCS_WaitingUserTicketReq* pMsg); //철이가 대기표시스템
	void OnRcvUpdateWaitingUserInfoReq(long lUSN, MsgCS_UpdateWaitingUserInfoReq* pMsg); //철이가 대기표시스템
};

#endif