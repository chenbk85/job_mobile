// GameInfo.h: interface for the CGameInfo class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __GameRoom_H__
#define __GameRoom_H__
#if _MSC_VER>1000
#pragma once
#endif // _MSC_VER>1000


class CGameRoom
{
public:
	RCRoomData m_cRCRoomData;
public:
	CGameRoom(void){ InitGameRoom(); }
	virtual ~CGameRoom(void){ FreeGameRoom(); }
	void InitGameRoom(void){ }
	void FreeGameRoom(void){ m_cRCRoomData.Clear(); }
public:
	RCRoomData& GetData(void){ return m_cRCRoomData; }
	void SwitchState(long lState){
		if(m_cRCRoomData.m_lState==lState) return;
		m_cRCRoomData.m_lState=lState;
	}
public:
	// USERINFO
	UITable& GetUITable(){ return m_cRCRoomData.m_tblUI; }
	int GetUISize(){ return m_cRCRoomData.GetUISize(); }
	UserInfo& GetUI(int nIndex){ ASSERT(_inrange(0, nIndex, m_cRCRoomData.GetUISize())); return m_cRCRoomData.GetUI(nIndex); }
//	const UserInfo& GetUI(int nIndex) const { ASSERT(_inrange(0, nIndex, m_cRCRoomData.GetUISize())); return m_cRCRoomData.GetUI(nIndex); }

	// CARDINFO
	CardTable& GetCardTable(){ return m_cRCRoomData.m_tblCard; }
	int GetCardSize(){ return m_cRCRoomData.GetCardsSize(); }
	Cards & GetCards(int idx){ return m_cRCRoomData.GetCards(idx); }
	const Cards & GetCards(int idx) const { return m_cRCRoomData.GetCards(idx); }

	// MONEYINFO
	MoneyTable & GetMoneyTable(){ return m_cRCRoomData.m_tblMoney; }
	int GetMoneySize(){ return m_cRCRoomData.GetMoneySize(); }
	Money & GetMoney(int idx){ return m_cRCRoomData.GetMoney(idx); }
	const Money & GetMoney(int idx) const { return m_cRCRoomData.GetMoney(idx); }
	int GetUserCnt(void){ return m_cRCRoomData.GetUserCnt(); }
	__int64 GetAvgMoney(void){ return m_cRCRoomData.GetAvgMoney(); }


	BettingMsg & GetBettingMsg(int idx){ return m_cRCRoomData.GetBettingMsg(idx); }
	int GetBettingMsgSize(void){ return m_cRCRoomData.GetBettingMsgSize(); }
	const BettingMsg & GetBettingMsg(int idx) const {return m_cRCRoomData.GetBettingMsg(idx);}
};


#endif
