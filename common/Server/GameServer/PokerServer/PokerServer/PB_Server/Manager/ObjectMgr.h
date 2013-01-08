//------------------------------------------------------------------------------------
// Module Name			: ObjectBase(.h)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObjectBase
//------------------------------------------------------------------------------------
#ifndef __ObjectMgr_H__
#define __ObjectMgr_H__

#pragma once

//#include "Object.h"
#include "ObjectData.h"
#include "Standard/Standard.h"
//#include "Standard/ObjectRefill.h"
#include "../Library/SRoomContextBase.h"
#include "../util/CTMap.h"

#include "../../Protocol Buffers/Poker/AdlGameCommon.h"

//#include "../Library/SGRCContainerBase.h"

typedef long KEY_OBJPOOL;

class CObjectMgr : public ISRoomContext, public CObjectData
{
protected:
	/*
	CObjectMgr(ISGRCContainer* pGRCContainer, char* szRoomID, long lRoomIDSize):CObjectData(pGRCContainer){
		InitObjectMgr();
	}
	*/

	
	CObjectMgr():CObjectData()
	{
		InitObjectMgr();
	}
	
public:
	virtual ~CObjectMgr(void){ FreeObjectMgr(); }
	void InitObjectMgr(void){}
	void FreeObjectMgr(void){ DestroyObject(); m_ctPair_Timer.clear(); }
private:
	//NC_NRC4_KEY	rc4key;
	//static CRITICAL_SECTION g_tCritical_Section;
	//static bool g_bCreate_CS;
public:
	CTPairVector<long, long> m_ctPair_Timer;
public:
	CTMap<KEY_OBJPOOL, CObjectBase*> m_vtObjectMgr;
	CObjectWaiting m_cObjectWaiting;
	CObjectItem m_cObjectItem;

	//20111226 임시 제거
	//CObjectRefill m_cObjectRefill;
public:
	virtual bool CreateObject(void);
	virtual void DestroyObject(void);
	virtual void SetUserPos(RCUser* pUser, int nIndex, long lSoundType);
	bool SetKey();
	void SetTimer(long lTimerIndex, long lDue, long lPeriod=NULL);
	void RemoveTimer(long lTimerIndex);
	bool IsTimer(long lTimerIndex);
	virtual long OnUserMsg(long lUSN, PayloadCS &pld);
	virtual long OnTimer(long lTimerIndex);
	virtual void SendStartReq(){}
	virtual void SendNoStart(){}
	virtual void UserJoin(long lUSN){}
	virtual void UserDisconnect(long lUSN, bool bReceive=false, bool bAbserveErase=true, bool bPugeErase=true){}
	virtual bool OnRcvEntry(PK_Plugin_Connection* pCon, long lUSN, s_req_entry* pMsg){ return false; }
	virtual void OnRcvObserve(long lUSN, s_req_observe * pMsg){}
public:
	void UIErase(long lUSN);
	void AddObserve(long lUSN);
	void ObserveErase(long lUSN);
	void ObserveProcesses(long lUSN, bool bEraseUser=false, bool bContinue=true);			// 재관 comment (2007-07-20) :  병도씨 강퇴 투표작업
	void AllUserDisconnect();
	bool RoomOwner(long lUSN, bool bPuge=true);
	void NextOwner();
	void NextBoss();
public:
	void SendToAll(GLAnsGameProtocol_Type type, void* msg);
	void SendToAll(const PayloadSC& pld, bool bCrypt=false, long lUSN=-1, long lExcept=-1L);
	void SendToUser(long lUSN, GLAnsGameProtocol_Type type, void* msg);
	void SendToUser(long lUSN, const PayloadSC& pld, bool bCrypt=false);
	void SendToObserver(const PayloadSC& pld);
	void SendSystemMsg(long lType, string str, long lUSN= -1);
	void Proc_UpdateUserData(long lUSN, bool bNotify);
	void DB_Purge_Log(long lUSN, bool bIsUI);
	bool IsUserJoinErr(long lUSN, long & lErrorCode);
	void SendUserJoinErr(long lUSN, long lErrorCode);
	void SendUserDisconnect(long lUSN, int nIndex);
	void Store_WinLoseCntVector( vecWinLoseCnt	&vecWLCnt );
	void SendEntryReject(long lUSN, long lType);
	void SendObserveAns(long lUSN, int nIndex);
	void SendBoss();
	void SendPurgeAns(long lUSN, bool bIsUI=false);
	void SendPurgeInfo();
	void SendFMoney(long lUSN=-1);
	void SendGameEndSystemMsg(long lType, long lUSN, bool bGiveUp, string sMsg, __int64 lMoney= 0);
	void SendChangeAvatarNotify(int nIndex);
	void SendExtMoneyNotify(long lUSN, RCUser * pUser, bool bExtType);
	void SendExitNtf(int nIndex, long lExit, bool bExit);
	void SendDisconnectMoneyNotify( const string& sNickName, __int64 llDisconnectMoney );	//접속중단머니 유저들에게 알림 추가
	void SendRefillMoneyNtf(long lUSN, int nRefillCnt, __int64 llRefillMoney);
	void SendObserverCnt();
	void SendPoliceNotify();
	void SendAssaItemNotify(long lUSN, int nIndex, string& sItem, long lRankType);
public:
	virtual void SendContinue(){}
public:
	void OnRcvPurge(long lUSN, s_req_purge * pMsg);
	void OnRcvAbuse(long lUSN, s_req_abuse * pMsg);
	void OnRcvSoundType(long lUSN, s_req_soundtype * pMsg);
	void OnRcvExitQue(long lUSN, s_req_exitque * pMsg);
	void OnRcvGameMasterCall(long lUSN, MsgCS_GameMasterCall * pMsg);
public:
	virtual long __stdcall OnCreateRoom(const char* szRoomOption, long lSize);
	//virtual long __stdcall OnAddUserInRoom(long lUSN, const char* szUserData, long lSize, long* plErrorCode);
	virtual long __stdcall OnAddUserInRoom(RCUser *user);
	virtual long __stdcall OnReserveRemoveUserInRoom(long lUSN);
	virtual long __stdcall OnUserDisconnectInRoomNotify(long lUSN);
	virtual long __stdcall OnRemoveUser(long lUSN);
	virtual long __stdcall OnUserMsgToRoomNotify(long lUSN, long lSize);
	virtual long __stdcall OnTimerToRoomNotify(long lTimerIndex);
	//virtual long __stdcall OnChangeUserAvatarNotify(long lUSN, long lAvatar);
	//virtual long __stdcall OnChangeUserNicknameNotify(long lUSN, const char* szNickname, long lSize);
	virtual long __stdcall OnChangeUserItemNotify(long lUSN, const char* szItem, long lSize);
	virtual long __stdcall OnRecvMessageFromServer(long lMsgType, long lParam, const char* szContents, long lSize);
	virtual long __stdcall CanUseIBB(long lUSN);
	virtual long __stdcall OnAExcuteQueryToDBResult(long lResult, long lIndex, const char* szResult, long lSize, long lErrorCode);
	virtual long __stdcall CheckUserStateFromWeb(long lUSN);
	virtual long __stdcall GetRoomInfo(const char* szRoomInfo, long lSize);
};


#endif