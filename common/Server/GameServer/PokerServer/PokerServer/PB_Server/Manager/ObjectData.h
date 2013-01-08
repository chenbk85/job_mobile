//------------------------------------------------------------------------------------
// Module Name			: ObjectData(.h)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObjectData
//------------------------------------------------------------------------------------

#ifndef __ObjectData_H__
#define __ObjectData_H__

#pragma once

#include "../Data/GameData.h"
#include "../Manager/Object.h"

class CObjectData : public CGameData, public CObjectBase
{
public:
	/*
	CObjectData(ISGRCContainer* pGRCContainer):CGameData(),CObjectBase(pGRCContainer){
		InitObjectData();
	} 
	*/
	CObjectData():CGameData()
	{
		InitObjectData();
	} 
public:
	virtual ~CObjectData(void){ FreeObjectData(); }
	void InitObjectData(void){ InitGameData(); }
	void FreeObjectData(void){ FreeGameData(); }
public:
	virtual bool CreateObject(void);
	virtual void DestroyObject(void);
public:
	void UserStateSetting();
	string FindUserName(long lUSN);
	int GetTotalUserCnt();
	int GetUICount();
	bool IsUI(long lUSN);
	int USNToIdx(long lUSN);
	long IdxToUSN(int nIndex);
public:
	bool IsObserve(long lUSN);
	bool IsBlackList(long lUSN);
	bool IsMoney(RCUser *pUser);
	int	GetSpace();
	bool IsSpace();
	bool IsGrade(RCUser *pUser);
	bool IsIP(RCUser * pUser);
	bool IsGameLimit(RCUser * pUser);
	bool IsMiniCashBox(long lUSN);
	bool IsExtMoneyUser(long lUSN);
public:
	void JoinItem(long lUSN);
	void StartItem();
	void EndItem();
	long GetFindBossUSN();
public:
	int	GetStateCount(long lUserState);
	int	GetPlayerCount();
	int	GetPlayingCount();
	int	GetBetPlayerCount();
	int	Get49WaitingCount();
	int	GetSelectContinueCount();
	int	GetMinPlayerCount();
	void SetBetUSN();
	bool IsBettingMoney(Money & money, __int64 lMoney);
	__int64 SetBetttingMoney(long lUSN, long & lBetType, MsgSC_BettingAnsMsg & msg);
	__int64 GetMaxBettingMoney(long lUSN);
	__int64 GetMaxMoney();
	void SetCallMoney(int nIndex, __int64 lCallMoney);
	bool IsAllIn(long lUSN);
	bool IsExceptAllIn(long lUSN);
public:
	void MoneyDivision(vector<int> vtIdx, bool b49Replay);
	void Division_AddMoney();						// ��� ������ �Ӵϸ� �����Ѵ�.
	void Division_SideMoney_FindUser();				// ������ �������� �ִ� �Ӵϸ�ŭ vtUser�� �����Ѵ�(���̵�Ӵ�)
	void Division_DieUser_Money();					// ���� ������� �Ӵϸ� ����ؼ� �й��Ѵ�.
	// ��� ����� ������ vtUser�� take, deal.. ��� ������ �����Ѵ�.
	void Division_TakeMoney_Save(long lUSN, __int64 lTakeMoney, __int64 llDealMoney, __int64 llJackPot, int nDealerTax);
	void Division_AddTakeMoney_Save(long lUSN, __int64 lTakeMoney, __int64 llDealMoney, __int64 llJackPot, int nDealerTax);
	__int64 Division_TakeMoney(int nIdx);
	__int64 Division_TakeMoney(vector<int> vtIdx);
	void Division_RestMoney();
	void Division_RestMoneyOver();
};

#endif